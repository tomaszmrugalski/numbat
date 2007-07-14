/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2006-12-29 01:50:38+0100
 * 
 * @brief  WMax MAC control layer
 * @licence GNU GPLv2 or later
 * 
 */

#define FSM_DEBUG
#include <omnetpp.h>
#include <vector>
#include "wmaxctrl.h"
#include "wmaxmsg_m.h"
#include "logger.h"
#include "hoinfo.h"
#include "wmaxradio.h"
#include "wmaxmac.h"
#include "ssinfo.h"

static uint32_t transactionID = 1;

// global function shared by all flows from all SSes
uint32_t GetNextTransactionID() { return transactionID++; }

ostream & operator <<(ostream & s, Transaction &trans)
{
  s << "TransID=" << trans.TransactionID << ", cid=" << trans.cid << ", qos.connType=" 
    << trans.qos.connType << endl;
  return s;
}

ostream & operator <<(ostream & s, WMaxFlowSS &f) 
{
  s << "transID=" << f.transactionID << " cid=" << f.cid;
  return s;
}

static int GetCidFromMsg(cMessage * msg)
{
    WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->controlInfo());
    if (!hdr) {
	opp_error("Unable to find MacHeader in message %s\n", msg->fullName());
    }
    return hdr->cid;
}

/********************************************************************************/
/*** WMax Ctrl SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxCtrlSS);

WMaxCtrlSS::WMaxCtrlSS()
{
}

void WMaxCtrlSS::fsmInit() {
    /// @todo - SS should perform network entry procedure (i.e. start in WAIT_FOR_CDMA state)
    //statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_WAIT_FOR_DLMAP);
    statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_POWER_DOWN);

    // state init
    std::string x = "Waiting for CDMA opportunity";
    stateInit(STATE_WAIT_FOR_DLMAP,    "Waiting for DL-MAP", onEventState_WaitForDlmap);
    stateInit(STATE_WAIT_FOR_UCD,      "Waiting for UCD", onEventState_WaitforUcd);
    stateInit(STATE_SEND_RNG_REQ,      "Sending RNG-REQ", STATE_WAIT_RNG_RSP, onEnterState_SendRngReq);
    stateInit(STATE_WAIT_RNG_RSP,      "Waiting for RNG-RSP", onEventState_WaitForRngRsp);
    stateInit(STATE_SEND_SBC_REQ,      "Sending SBC-REQ", STATE_WAIT_SBC_RSP, onEnterState_SendSbcReq);
    stateInit(STATE_WAIT_SBC_RSP,      "Waiting for SBC-RSP", onEventState_WaitForSbcRsp);

    stateInit(STATE_WAIT_SA_TEK_CHALLANGE, "Wait for SA-TEK-Challange", onEventState_WaitForSaTekChallange);
    stateInit(STATE_SEND_SA_TEK_REQ,   "Sending SA-TEK-REQ", STATE_WAIT_SA_TEK_RSP, onEnterState_SendSaTekReq);
    stateInit(STATE_WAIT_SA_TEK_RSP,   "Wating for SA-TEK-RSP", onEventState_WaitForSaTekRsp);

    stateInit(STATE_SEND_REG_REQ,      "Sending REG-REQ", STATE_WAIT_REG_RSP, onEnterState_SendRegReq);
    stateInit(STATE_WAIT_REG_RSP,      "Waiting for REG-RSP", onEventState_WaitForRegRsp);

    stateInit(STATE_SVC_FLOW_CREATION, "Initiate service flow creation", 
	      onEventState_SvcFlowCreation, onEnterState_SvcFlowCreation, 0);

    stateInit(STATE_OPERATIONAL,       "Operational", onEventState_Operational, onEnterState_Operational, 0);
    stateInit(STATE_SEND_MSHO_REQ,     "Sending MSHO-REQ", STATE_WAIT_BSHO_RSP, onEnterState_SendMshoReq);
    stateInit(STATE_WAIT_BSHO_RSP,     "Waiting for BSHO-RSP", onEventState_WaitForBshoRsp);
    stateInit(STATE_SEND_HO_IND,       "Sending HO-IND", onEventState_SendHoInd, onEnterState_SendHoInd, 0);
    stateInit(STATE_HANDOVER_COMPLETE, "Handover complete", STATE_WAIT_FOR_CDMA, onEnterState_HandoverComplete);

    stateInit(STATE_WAIT_FOR_CDMA,     "Waiting for CDMA opportunity", onEventState_WaitForCdma);
    stateInit(STATE_SEND_CDMA,         "Send CDMA code", STATE_WAIT_ANON_RNG_RSP, onEnterState_SendCdma);
    stateInit(STATE_WAIT_ANON_RNG_RSP, "Waiting for anonymous RNG-RSP", onEventState_WaitForAnonRngRsp);

    stateInit(STATE_POWER_DOWN,         "Power down", onEventState_PowerDown);

    stateVerify();

    // event init
    eventInit(EVENT_HANDOVER_START, "Begin handover procedure");
    eventInit(EVENT_REENTRY_START, "Begin reentry procedure");
    eventInit(EVENT_ENTRY_START, "Begin network entry procedure");

    eventInit(EVENT_DLMAP, "DL-MAP received");
    eventInit(EVENT_UCD, "UCD received");
    eventInit(EVENT_RNG_RSP_RECEIVED, "RNG-RSP received.");
    eventInit(EVENT_SBC_RSP_RECEIVED, "SBC-RSP received.");
    eventInit(EVENT_SA_TEK_CHALLENGE, "SA-TEK-CHALLANGE received.");
    eventInit(EVENT_SA_TEK_RSP,       "SA-TEK-RSP received.");
    eventInit(EVENT_REG_RSP_RECEIVED, "REG-RSP received.");
    eventInit(EVENT_CDMA_CODE, "(Initial ranging) CDMA opportunity received");
    eventInit(EVENT_BSHO_RSP_RECEIVED, "BSHO-RSP received");
    eventInit(EVENT_HO_CDMA_CODE, "(Handover ranging) CDMA opportunity received");
    eventInit(EVENT_SERVICE_FLOW_COMPLETE, "Service Flow complete");
    eventInit(EVENT_HO_IND_SENT,  "HO-IND transmitted");
    eventVerify();

    TIMER(NetworkEntry, 0.1, "Start Network entry");
    TIMER(Handover,     0.3, "Start handover");
    TIMER(Reentry,      0.1, "Network reentry");

    stringUpdate();
}

void WMaxCtrlSS::initialize() {
    hoInfo = new HoInfo_t();
    CLEAR(hoInfo);

    neType == WMAX_CTRL_NETWORK_ENTRY_INITIAL; // by default, use normal network entry

    fsmInit();

    // start with network entry
    TIMER_START(NetworkEntry);

    cModule * parent = parentModule();
    int initialBS;
    if (parent) {
	hoInfo->isMobile = parent->par("wmaxIsMobile");
	hoInfo->wmax.hoOptim = parent->par("wmaxHoOptim");
        initialBS = parent->par("initialBS");
    }

    connectBS(initialBS);

    char buf[80];
    sprintf(buf, "WMaxCtrlSS[%d]", parentModule()->index());
    if (ev.isGUI()) 
        setName(buf);

    Log(Notice) << "hoOptim=" << hoInfo->wmax.hoOptim << ", isMobile=" << hoInfo->isMobile 
		<< ", initialBS=" << initialBS << LogEnd;

    WATCH_PTRLIST(serviceFlows);
}

double WMaxCtrlSS::sendMsg(cMessage * msg, char * paramName, const char * gateName, int cid)
{
/*    char buf[80];
    sprintf(buf, "Min%s", paramName);
    double min = (double)par(buf);

    sprintf(buf, "Max%s", paramName);
    double max = (double)par(buf);

    double delay = uniform(min, max);*/

    double delay = 0;

    Log(Debug) << "Sending " << msg->name() << " in " << setiosflags(ios::fixed) << setprecision(3) << delay 
	       << "secs (cid=" << cid << ")." << LogEnd;

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = cid;
    msg->setControlInfo(hdr);

    sendDelayed(msg, delay, gateName);

    return delay;
}


/** 
 * general dispatcher
 * 
 * @param msg 
 */
void WMaxCtrlSS::handleMessage(cMessage *msg) 
{

    if (dynamic_cast<WMaxMsgDlMap*>(msg)) {
        onEvent(EVENT_DLMAP, msg);
        delete msg;
        return;
    }
    if (dynamic_cast<WMaxMsgDCD*>(msg))   {
        delete msg;
        return;
    }
    if (dynamic_cast<WMaxMsgUCD*>(msg))   {
        onEvent(EVENT_UCD, msg);
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	WMaxMsgUlMap * ulmap = dynamic_cast<WMaxMsgUlMap*>(msg);

	for (int i=0; i<ulmap->getIEArraySize(); i++) {
	    WMaxUlMapIE & ie = ulmap->getIE(i);
	    if ( (ie.uiuc == WMAX_ULMAP_UIUC_CDMA_BWR) ) {
		onEvent(EVENT_CDMA_CODE, msg);
	    }
	}

	delete msg;
	return;
    }

    // messages
    if (dynamic_cast<WMaxMsgRngRsp*>(msg)) {
	onEvent(EVENT_RNG_RSP_RECEIVED, msg);
	delete msg;
	return;
    }
    if (dynamic_cast<WMaxMsgSbcRsp*>(msg)) {
	onEvent(EVENT_SBC_RSP_RECEIVED, msg);
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgPkmRsp*>(msg)) {
	WMaxMsgPkmRsp * pkm = dynamic_cast<WMaxMsgPkmRsp*>(msg);
	if (pkm->getCode() == WMAX_PKM_SA_TEK_CHALLENGE)
	    onEvent(EVENT_SA_TEK_CHALLENGE, msg);
	if (pkm->getCode() == WMAX_PKM_SA_TEK_RSP)
	    onEvent(EVENT_SA_TEK_RSP, msg);
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgRegRsp*>(msg)) {
	onEvent(EVENT_REG_RSP_RECEIVED, msg);
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgBSHORSP*>(msg)) {
	onEvent(EVENT_BSHO_RSP_RECEIVED, msg);
	delete msg;
	return;
    }

    // timers
    if (msg==TimerHandover) {
	onEvent(EVENT_HANDOVER_START, msg);
	return;
    }

    if (msg==TimerReentry) {
	onEvent(EVENT_REENTRY_START, msg);
	return;
    }
    
    if (msg==TimerNetworkEntry) {
	onEvent(EVENT_ENTRY_START, msg);
	return;
    }

    if (dynamic_cast<WMaxMsgDsxRvd*>(msg)) {
        WMaxMsgDsxRvd *dsxrvd = dynamic_cast<WMaxMsgDsxRvd*>(msg);

        WMaxFlowSS *flow;
        for (int i=0; i!= serviceFlows.size(); i++) {
            flow = serviceFlows.front();
            serviceFlows.pop_front();

            if (flow->transactionID == dsxrvd->getTransactionID()) {
                flow->handleMessage(msg);
                serviceFlows.push_back(flow);
                return;
            }
            serviceFlows.push_back(flow);
        }

// 	list<WMaxFlowSS*>::iterator it;
// 	for (it = serviceFlows.begin(); it!=serviceFlows.end(); it++) {
// 	    if (it->transactionID == dsxrvd->getTransactionID()) {
// 		it->handleMessage(msg);
// 		return;
// 	    }
//   	}

        return;
    }

    if (dynamic_cast<WMaxMsgDsaRsp*>(msg)) {
        WMaxMsgDsaRsp *dsarsp = dynamic_cast<WMaxMsgDsaRsp*>(msg);

        WMaxFlowSS *flow;
        for (int i=0; i!= serviceFlows.size(); i++) {
            flow = serviceFlows.front();
            serviceFlows.pop_front();
            if (flow->transactionID == dsarsp->getTransactionID()) {
                flow->handleMessage(msg);
                serviceFlows.push_back(flow);
                return;
            }
            serviceFlows.push_back(flow);
        }


// 	list<WMaxFlowSS*>::iterator it;
// 	for (it = serviceFlows.begin(); it!=serviceFlows.end(); it++) {
// 	    if (it->transactionID == dsarsp->getTransactionID()) {
// 		it->handleMessage(msg);
// 		return;
// 	    }
// 	}

        return;
    }

    if (dynamic_cast<WMaxEvent_HoIndSent*>(msg)) {
	onEvent(EVENT_HO_IND_SENT, msg);
	delete msg;
	return;
    }
}

// wait for DL-MAP state
FsmStateType WMaxCtrlSS::onEventState_WaitForDlmap(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_DLMAP:
	return STATE_WAIT_FOR_UCD;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// wait for UCD state
FsmStateType WMaxCtrlSS::onEventState_WaitforUcd(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_UCD:
	return STATE_SEND_RNG_REQ;
    default:
	CASE_IGNORE(fsm, e);
    }
}

/* *** STATE: WAIT FOR CDMA ************************************************************ */
FsmStateType WMaxCtrlSS::onEventState_WaitForCdma(Fsm * fsm, FsmEventType e, cMessage *msg) 
{
    WMaxCtrlSS * f = dynamic_cast<WMaxCtrlSS*>(fsm);

    switch (e) {
	case EVENT_CDMA_CODE:
	return f->onEvent_CdmaCode(msg);
	
    default:
	CASE_IGNORE(fsm, e);
    }
}

FsmStateType WMaxCtrlSS::onEvent_CdmaCode(cMessage *msg)
{
    return WMaxCtrlSS::STATE_SEND_CDMA;
}

FsmStateType WMaxCtrlSS::onEnterState_SendRngReq(Fsm * fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);

    cModule *SS = ss->parentModule();
    cModule *SSInfo = SS->submodule("ssInfo");
    if (!SSInfo)
        opp_error("Unable to obtain ssInfo submodule in SS[%d]\n", SS->index());
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(SSInfo);

    WMaxRngReq rngReq;
    rngReq.macAddr = ssinfo->info.macAddr;

    WMaxMsgRngReq * rng = new WMaxMsgRngReq();
    rng->setName("RNG-REQ");
    rng->setRngReq(rngReq);
    ss->sendMsg(rng, "", "macOut", 0);

    SLog(fsm, Notice) << "Sending RNG-REQ." << LogEnd;
    return fsm->State();
}

// wait for RNG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->parentModule()->submodule("ssInfo"));
    WMaxMsgRngRsp * rng = dynamic_cast<WMaxMsgRngRsp*>(msg);
    WMaxRngRsp rngRsp;
    WMaxMacAddMngmntConn *addConn = new WMaxMacAddMngmntConn();

    switch (e) {
    case EVENT_RNG_RSP_RECEIVED: 
        rngRsp = rng->getRngRsp();
        if (rngRsp.ssMacAddr == ssinfo->info.macAddr) {
            ssinfo->info.basicCid = rngRsp.basicCid;
            ssinfo->stringUpdate();
            addConn->setCid(rngRsp.basicCid);
            ss->send(addConn,"macOut");
	    SLog(ss, Debug) << "Switching to 'send SBC-REQ'." << LogEnd;
	    return STATE_SEND_SBC_REQ;
        }
    default:
	CASE_IGNORE(fsm, e);
    }
}

// send SBC-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendSbcReq(Fsm * fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->parentModule()->submodule("ssInfo"));

    if ( (ss->neType == WMAX_CTRL_NETWORK_REENTRY) && (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_OMIT_SBC_REQ)) {
	SLog(fsm, Warning) << "Reentry: omit-sbc-req flag set, skipping SBC-REQ." << LogEnd;
	return STATE_SEND_REG_REQ; /* state override: switch to SEND_REG_REQ */
    }
    
    WMaxMsgSbcReq * req = new WMaxMsgSbcReq();
    req->setName("SBC-REQ");
    ss->sendMsg(req, "", "macOut", ssinfo->info.basicCid);
    SLog(fsm, Notice) << "Sending SBC-REQ." << LogEnd;
    return fsm->State();
}

// wait for SBC-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForSbcRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    switch (e) {
    case EVENT_SBC_RSP_RECEIVED:
	if ( (ss->neType == WMAX_CTRL_NETWORK_REENTRY) && (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_SKIP_SA_TEK)) {
	    SLog(fsm, Warning) << "Reentry: skip-sa-tek flag set, skipping SA-TEK exchange." << LogEnd;
	    return STATE_SEND_REG_REQ; /* state override: switch to SEND_REG_REQ */
	}
	return STATE_WAIT_SA_TEK_CHALLANGE;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// wait for SA-TEK-CHALLANGE
FsmStateType WMaxCtrlSS::onEventState_WaitForSaTekChallange(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_SA_TEK_CHALLENGE:
	return STATE_SEND_SA_TEK_REQ;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// send SA-TEK-REQ
FsmStateType WMaxCtrlSS::onEnterState_SendSaTekReq(Fsm * fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->parentModule()->submodule("ssInfo"));
    WMaxMsgPkmReq * pkm = new WMaxMsgPkmReq("PKM-REQ(SA-TEK-REQ)");
    pkm->setCode(WMAX_PKM_SA_TEK_REQ);
    ss->sendMsg(pkm, "", "macOut", ssinfo->info.basicCid);
    SLog(fsm, Notice) << "Sending PKM-REQ(SA-TEK-REQ)." << LogEnd;
    return fsm->State();
}

// wait for SA-TEK-RSP
FsmStateType WMaxCtrlSS::onEventState_WaitForSaTekRsp(Fsm *fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_SA_TEK_RSP:
	return STATE_SEND_REG_REQ;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// send REG-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendRegReq(Fsm * fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->parentModule()->submodule("ssInfo"));
    if ( (ss->neType == WMAX_CTRL_NETWORK_REENTRY) && (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_OMIT_REG_REQ)) {
	SLog(fsm, Warning) << "Reentry: omit-reg-req flag set, skipping REG-REQ." << LogEnd;
        return STATE_SVC_FLOW_CREATION; /* state override: switch to Service flow creation */
    }

    WMaxMsgRegReq * reg = new WMaxMsgRegReq();
    reg->setName("REG-REQ");
    ss->sendMsg(reg, "", "macOut", ssinfo->info.basicCid);
    SLog(fsm, Notice) << "Sending REG-REQ." << LogEnd;
    return fsm->State();
}

// wait for REG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRegRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_REG_RSP_RECEIVED:
//	return STATE_OPERATIONAL;
        return STATE_SVC_FLOW_CREATION;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// inititae service flow creation state
FsmStateType WMaxCtrlSS::onEnterState_SvcFlowCreation(Fsm * fsm) {

    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    if ( (ss->neType == WMAX_CTRL_NETWORK_REENTRY) && (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_FULL_STATE_TRANSFER)) {
	SLog(fsm, Warning) << "Reentry: full-state-transfer flag set, skipping service flow creation." << LogEnd;
	return STATE_OPERATIONAL; /* state override: switch to SEND_REG_REQ */
    }

    WMaxFlowSS *flow;
    
    flow = new WMaxFlowSS(fsm);

/// @todo WMacCtrlFlowCreationStart should be send by WMaxMac ??
    WMaxCtrlFlowCreationStart *msg = new WMaxCtrlFlowCreationStart();
    msg->setGateIndex(0);
    WMaxQos qos;
    qos.connType = WMAX_CONN_TYPE_BE;
    qos.msr = 80000;
    msg->setQosArraySize(1);
    msg->setQos(0,qos);
    msg->setGateIndex(0);
    flow->handleMessage(msg);

    ss->serviceFlows.push_back(flow);

    ss->sfCnt = 1; // @todo - there is only one flow, for now it's ok, but support for more service flow must be added
    
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_SvcFlowCreation(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    switch (e) {
    case EVENT_SERVICE_FLOW_COMPLETE:
	SLog(fsm, Notice) << "Service flow creation complete." << LogEnd;
	if (!--ss->sfCnt) {
	    SLog(fsm, Notice) << "All service flows created." << LogEnd;
	    return STATE_OPERATIONAL;
	}
    default:
	CASE_IGNORE(fsm, e);
    }
}


FsmStateType WMaxCtrlSS::onEnterState_Operational(Fsm * fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);

    if (ss->neType == WMAX_CTRL_NETWORK_REENTRY) {
	double x = ss->simTime() - ss->hoReentryTimestamp;
	SLog(fsm, Warning) << "Network reentry complete: " << x << "secs (" 
			  << ss->hoReentryTimestamp << "-" << ss->simTime() << ")." << LogEnd;
    } else {
	SLog(fsm, Notice) << "Initial network entry complete." << LogEnd;
    }

    if (ss->hoInfo->isMobile)
        STATIC_TIMER_START(ss, Handover);
    
    return fsm->State();
}


FsmStateType WMaxCtrlSS::onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_HANDOVER_START:
	return STATE_SEND_MSHO_REQ;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// send MSHO-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendMshoReq(Fsm *fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->parentModule()->submodule("ssInfo"));
    WMaxMsgMSHOREQ * mshoReq = new WMaxMsgMSHOREQ("MSHO-REQ");
    mshoReq->setName("MSHO-REQ");
    SLog(fsm, Notice) << "Sending MSHO-REQ message." << LogEnd;
    ss->sendMsg(mshoReq, "", "macOut", ssinfo->info.basicCid);
    return fsm->State();
}

// wait for BSHO-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForBshoRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_BSHO_RSP_RECEIVED:
	return STATE_SEND_HO_IND;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// sent HO-IND state
FsmStateType WMaxCtrlSS::onEnterState_SendHoInd(Fsm *fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->parentModule()->submodule("ssInfo"));
    WMaxMsgHOIND * hoInd = new WMaxMsgHOIND();
    hoInd->setName("HO-IND");
    ss->sendMsg(hoInd, "", "macOut", ssinfo->info.basicCid);
    ssinfo->info.basicCid = 0;
    ssinfo->stringUpdate();
    SLog(fsm, Notice) << "Sending HO-IND message." << LogEnd;
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onExitState_SendHoInd(Fsm * fsm)
{
    SLog(fsm, Notice) << "#### onExit: SendHoInd" << LogEnd;
    WMaxMacTerminateAllConns *terminateAll = new WMaxMacTerminateAllConns();
    fsm->send(terminateAll, "macOut");
}

FsmStateType WMaxCtrlSS::onEventState_SendHoInd(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    switch (e) {
    case EVENT_HO_IND_SENT:
	return STATE_HANDOVER_COMPLETE;
    default:
	CASE_IGNORE(fsm, e);
    }
}
    
// handover complete state
FsmStateType WMaxCtrlSS::onEnterState_HandoverComplete(Fsm * fsm)
{   WMaxCtrlSS *ss = dynamic_cast<WMaxCtrlSS*>(fsm);

    SLog(fsm, Notice) << "Handover (on serving BS) complete: " << ss->hoStartTimestamp << "-" 
		<< ss->simTime() << LogEnd;
    ss->connectNextBS();
    ss->hoReentryTimestamp = ss->simTime();

    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEnterState_SendCdma(Fsm *fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    WMaxMsgCDMA * cdma = new WMaxMsgCDMA();
    if (ss->neType == WMAX_CTRL_NETWORK_REENTRY) {
	cdma->setPurpose(WMAX_CDMA_PURPOSE_HO_RNG);
	cdma->setName("CDMA code (ho rng)");
    } else {
	cdma->setPurpose(WMAX_CDMA_PURPOSE_INITIAL_RNG);
	cdma->setName("CDMA code (initial rng)");
    }

    SLog(fsm, Notice) << "Sending " << cdma->name() << LogEnd;
    fsm->send(cdma, "macOut");
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_WaitForAnonRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_RNG_RSP_RECEIVED:
	return STATE_SEND_RNG_REQ;
    default:
	CASE_IGNORE(fsm, e);
    }
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_PowerDown(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    ss->hoStartTimestamp = fsm->simTime();
    switch (e) {
    case EVENT_ENTRY_START:
	ss->neType = WMAX_CTRL_NETWORK_ENTRY_INITIAL;
	return STATE_WAIT_FOR_DLMAP;
    case EVENT_REENTRY_START:
	ss->neType = WMAX_CTRL_NETWORK_REENTRY;
	ss->hoReentryTimestamp = ss->simTime();
	return STATE_WAIT_FOR_CDMA;
    default:
	CASE_IGNORE(fsm, e);
    }
}

void WMaxCtrlSS::connectBS(int x) {
    
    /* sanity checks */
    cModule *SS = parentModule();
    cModule *physim = parentModule()->parentModule();
    int maxBS = physim->par("numBS");
    if (x> maxBS) {
	opp_error("Unable to connect to BS[%d]: there are only %d BS(es)\n",
		  x, maxBS);
    }
    
    cModule * targetBS = physim->submodule("BS",x);
    if (!targetBS) {
	opp_error("Unable to find BS[%d]\n", x);
    } 

    disconnect(); // disconnect from current BS (if any)

    /* connect to the next BS */
    cModule *radio = targetBS->submodule("radio");
    if (!radio)
	opp_error("Unable to obtain radio submodule in BS[%d]\n",
		  x);

    WMaxRadio * wmaxRadio = check_and_cast<WMaxRadio*>(radio);

    wmaxRadio->connect(SS);
}

void WMaxCtrlSS::disconnect() {

    cModule *SS = parentModule();
    if (!SS->gate("out")->isConnected()) {
	// not connected
	return;
    }
    
    cModule *BS =SS->gate( "out" )->toGate()->ownerModule();
    cModule *radio = BS->submodule("radio");
    if (!radio)
	opp_error("Unable to obtain radio submodule in BS[%d]\n",
		  BS->index());
    WMaxRadio * wmaxRadio = check_and_cast<WMaxRadio*>(radio);
    wmaxRadio->disconnect(SS);
}

/** 
 * thie method reconnects (creates Omnet module-module connections) to the next BS
 * 
 */
void WMaxCtrlSS::connectNextBS() {
    
    cModule *SS = parentModule();
    cModule *physim = parentModule()->parentModule();
    cModule *BS =SS->gate( "out" )->toGate()->ownerModule();
    int actBS = BS->index();
    int nextBS = (actBS+1)%(BS->size());
    Log(Notice) << "Currently associated with BS: " << actBS << ", switching to BS :" << nextBS << LogEnd;
    cModule *BSnext = physim->submodule("BS", nextBS);
    if (!BSnext)
	opp_error("Unable to find BS:%d\n", nextBS);

    disconnect(); // disconnect from current BS
    connectBS(nextBS); // connect to the next BS

    // after reconnecting to other BS, perform Reentry, not normal entry
    neType = WMAX_CTRL_NETWORK_REENTRY; 
}

/********************************************************************************/
/*** WMax Ctrl BS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxCtrlBS);

WMaxCtrlBS::WMaxCtrlBS()
{

}

void WMaxCtrlBS::fsmInit()
{

}

void WMaxCtrlBS::initialize()
{
    cid = 1024;
    pkmSupport = true;
    Transactions.clear();
    ssList.clear();

    char buf[80];
    sprintf(buf, "WMaxCtrlBS[%d]", parentModule()->index());
    if (ev.isGUI()) 
        setName(buf);

    WATCH_LIST(ssList);
    WATCH_LIST(Transactions);
}

bool WMaxCtrlBS::pkmEnabled()
{
    return pkmSupport;
}

double WMaxCtrlBS::sendMsg(cMessage * msg, char * paramName, const char * gateName, int cid)
{
    char buf[80];
    sprintf(buf, "Min%s", paramName);
    double min = (double)par(buf);

    sprintf(buf, "Max%s", paramName);
    double max = (double)par(buf);

    double delay = uniform(min, max);
    
    Log(Debug) << "Sending " << msg->name() << " in " << setiosflags(ios::fixed) << setprecision(3) << delay 
	       << "secs (cid=" << cid << ")." << LogEnd;

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = cid;
    msg->setControlInfo(hdr);

    sendDelayed(msg, delay, gateName);

    return delay;
}

SSInfo_t * WMaxCtrlBS::getSS(uint16_t basicCid, string reason)
{
  list<SSInfo_t>::iterator ss;
  for (ss = ssList.begin(); ss!=ssList.end(); ss++) {
    if (basicCid == ss->basicCid) {
      return &(*ss);
    }
  }
   
  opp_error("Unable to find SS with cid=%d while %s\n", basicCid, reason.c_str());
}

void WMaxCtrlBS::handleMessage(cMessage *msg) 
{
    if (dynamic_cast<WMaxMsgRngReq*>(msg)) {
      if (GetCidFromMsg(msg) != WMAX_CID_RANGING )
        opp_error("Received RNG-REQ on non-ranging connection (cid=%d)", GetCidFromMsg(msg));

        WMaxMsgRngReq * req = dynamic_cast<WMaxMsgRngReq*>(msg);
        WMaxRngReq rngReq = req->getRngReq();

        WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp("RNG-RSP (initial rng)");
        WMaxRngRsp rngRsp;
        rngRsp.ssMacAddr = rngReq.macAddr;
        rngRsp.basicCid = cid;
        rsp->setName("RNG-RSP");
        rsp->setRngRsp(rngRsp);
        rsp->setPurpose(WMAX_CDMA_PURPOSE_INITIAL_RNG);
        double x = sendMsg(rsp, "DelayCdma", "macOut", GetCidFromMsg(msg) );

        WMaxMacAddMngmntConn *addConn = new WMaxMacAddMngmntConn();
        addConn->setCid(cid);
        Log(Notice) << "RNG-REQ received, sending RNG-RSP in " << x << "secs (new basic connection created, cid=" 
                    << cid << ")." << LogEnd;
        send(addConn,"macOut");
        cid++;

        // remember that this SS is being supported
        SSInfo_t * ss  = new SSInfo_t();
        ss->macAddr  = rngReq.macAddr;
        ss->basicCid = addConn->getCid();
        ssList.push_back(*ss);
        Log(Notice) << "New SS with mac=" << ss->getMac() << " has been added." << LogEnd;
        
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgSbcReq*>(msg)) {
        WMaxMsgSbcRsp * rsp = new WMaxMsgSbcRsp("SBC-RSP");
        getSS( GetCidFromMsg(msg), "SBC-REQ received");
        
        rsp->setName("SBC-RSP");
        double x = sendMsg(rsp, "DelaySbc", "macOut", GetCidFromMsg(msg));
        Log(Notice) << "SBC-REQ received, sending SBC-RSP in " << x << "secs." << LogEnd;
        
        if (pkmEnabled()) {
            Log(Notice) << "Initiating PKMv2: SA-TEK 3way handshake, sending PKM-RSP" << LogEnd;
            WMaxMsgPkmRsp * pkm = new WMaxMsgPkmRsp("PKM-RSP (SA-TEK-Challange)");
            pkm->setCode(WMAX_PKM_SA_TEK_CHALLENGE);
            sendMsg(pkm, "DelaySaTek", "macOut", GetCidFromMsg(msg));
        }
        delete msg;

        return;
    }

    if (dynamic_cast<WMaxMsgPkmReq*>(msg)) {
        getSS( GetCidFromMsg(msg), "PKM-REQ received");
      
        WMaxMsgPkmReq* req = dynamic_cast<WMaxMsgPkmReq*>(msg);
        WMaxMsgPkmRsp * rsp = new WMaxMsgPkmRsp("PKM-RSP(SA-TEK-RSP)");
        
        if (req->getCode() == WMAX_PKM_SA_TEK_REQ)
          rsp->setCode(WMAX_PKM_SA_TEK_RSP);
        
        double x = sendMsg(rsp, "DelaySaTek", "macOut", GetCidFromMsg(msg));
        Log(Notice) << "PKM-REQ received, sending PKM-RSP in " << x << "secs." << LogEnd;
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgRegReq*>(msg)) {
        getSS( GetCidFromMsg(msg), "REG-REQ received");

        WMaxMsgRegRsp * rsp = new WMaxMsgRegRsp("REG-RSP");
        rsp->setName("REG-RSP");
        double x = sendMsg(rsp, "DelayReg", "macOut", GetCidFromMsg(msg));
        Log(Notice) << "REG-REQ received, sending REG-RSP in " << x << "secs." << LogEnd;
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgMSHOREQ*>(msg)) {
        getSS( GetCidFromMsg(msg), "MSHO-REQ received");

        WMaxMsgBSHORSP * bshoRsp = new WMaxMsgBSHORSP();
        bshoRsp->setName("BSHO-RSP");
        double x = sendMsg(bshoRsp, "DelayHoRsp", "macOut", GetCidFromMsg(msg));
        Log(Notice) << "MSHO-REQ received, sending BSHO-RSP in " << x << "secs." << LogEnd;
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgHOIND*>(msg)) {
        SSInfo_t * ss = getSS( GetCidFromMsg(msg), "HO-IND received");
	std::stringstream x;
	x << "HO-IND received (SS " << ss->getMac() << "), removing connections (cid=):"
	  << ss->basicCid << "(basic)";

	WMaxEvent_DelConn * delConn;
	delConn = new WMaxEvent_DelConn();
	delConn->setCid(ss->basicCid);
	send(delConn, "macOut");

	for (int i=0;i <ss->sfCnt; i++) {
	    x << " " << ss->sf[i].cid;
	    WMaxEvent_DelConn * delConn = new WMaxEvent_DelConn();
	    delConn->setCid(ss->sf[i].cid);
            send(delConn, "macOut");
	}

	Log(Notice) << x.str() << LogEnd;
        
        delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgCDMA*>(msg)) {
        WMaxMsgCDMA * cdma = dynamic_cast<WMaxMsgCDMA*>(msg);
        Log(Notice) << msg->fullName() << " (purpose=" << int(cdma->getPurpose()) << ") received";
        switch (cdma->getPurpose()) {
          case WMAX_CDMA_PURPOSE_HO_RNG:
            {
              Log(Cont) << ", sending Anonymous (handover) RNG-RSP." << LogEnd;
              WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp();
              rsp->setName("Anonymous RNG-RSP");
              send(rsp, "macOut");
              break;
            }
          case WMAX_CDMA_PURPOSE_INITIAL_RNG:
            {
              Log(Cont) << ", sending Anonymous (initial) RNG-RSP." << LogEnd;
              WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp();
              rsp->setName("Anonymous (initial) RNG-RSP");
              send(rsp, "macOut");
              break;
            }
          case WMAX_CDMA_PURPOSE_BWR:
          default:
            /// @todo - Best effort traffic.
            Log(Cont) << ", not supported." << LogEnd;
            opp_error("That type of CDMA code is not supported yet (purpose=%d).", cdma->getPurpose());
            break;
        }
        
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgDsaReq*>(msg)) {
        getSS( GetCidFromMsg(msg), "DSA-REQ received");

        WMaxMsgDsaReq *dsareq = dynamic_cast<WMaxMsgDsaReq*>(msg);

        Transaction Trans;

        WMaxMsgDsxRvd *dsxrvd = new WMaxMsgDsxRvd();
        dsxrvd->setName("DSX-RVD");
        dsxrvd->setTransactionID(dsareq->getTransactionID());
        dsxrvd->setConfirmationCode(0);
        double x = sendMsg(dsxrvd, "DelayDsxRvd", "macOut", GetCidFromMsg(msg));

        WMaxMsgDsaRsp *dsarsp = new WMaxMsgDsaRsp();
        dsarsp->setName("DSA-RSP");
        dsarsp->setTransactionID(dsareq->getTransactionID());
        Trans.TransactionID = dsareq->getTransactionID();
        dsarsp->setQosArraySize(1);
        dsarsp->setQos(0,dsareq->getQos(0));
        Trans.qos = dsareq->getQos(0);
        dsarsp->setCid( getNextCid() );
        Trans.cid = dsarsp->getCid();

        double y = sendMsg(dsarsp, "DelayDsxRsp", "macOut", GetCidFromMsg(msg));

        Log(Notice) << "DSA-REQ received, sending DSX-RVD (after " << x << "secs) and DSA-RSP (after " 
                    << y << "secs), cid=" << GetCidFromMsg(msg) << " (added transaction: transID=" 
                    << dsareq->getTransactionID() << ", cid=" << Trans.cid << ")." << LogEnd;

        Transactions.push_back(Trans);

        delete msg;
        return;
    }

    bool transFound = false;

    if (dynamic_cast<WMaxMsgDsaAck*>(msg)) {
        getSS( GetCidFromMsg(msg), "DSA-ACK received");

        WMaxMsgDsaAck *dsaack = dynamic_cast<WMaxMsgDsaAck*>(msg);
        Log(Notice) << "DSA-ACK received (transID=" << dsaack->getTransactionID() << "),";
        
        list<Transaction>::iterator it;
        for (it = Transactions.begin(); it!=Transactions.end(); it++) {
          if (it->TransactionID == dsaack->getTransactionID()) {
            Log(Cont) << " transaction found, creating new connection (cid=" << it->cid << ")" << LogEnd;
            WMaxMacAddConn *addConn = new WMaxMacAddConn();
            addConn->setName("Add connection");
            addConn->setGateIndex(0);
            addConn->setCid(it->cid);
            addConn->setQosArraySize(1);
            addConn->setQos(0,it->qos);
            send(addConn, "macOut");

            transFound = true;

            // find this SS
            SSInfo_t * ss = getSS( GetCidFromMsg(msg), "Received DSA-ACK" );
            ss->sf[ss->sfCnt].cid = it->cid;
            ss->sfCnt++;
            Log(Notice) << "Assigning connection (cid=" << it->cid << ") to SS " << ss->getMac() 
                        << " (SS has " << ss->sfCnt << " conns)." << LogEnd;

            Transactions.erase(it);
            delete msg;
            return;
          }
        }
        
        Log(Cont) << ", transaction NOT found." << LogEnd;
        Log(Error) << "Received DSA-ACK for unknown transaction (cid=" << GetCidFromMsg(msg) 
                   << ", transID=" << dsaack->getTransactionID() << ")." << LogEnd;

        delete msg;
        return;
    }

    Log(Debug) << "Received " << msg->fullName() << " message." << LogEnd;
}


/********************************************************************************/
/*** WMax Service Flow Creation SS***********************************************/
/********************************************************************************/

//Define_Module(WMaxFlowSS);

WMaxFlowSS::WMaxFlowSS(Fsm * fsm) {
    parentFsm = fsm;
    fsmInit();

    transactionID = 0; // it doesn't matter now, it will be set in WMaxFlowSS::onEventState_Start()
}

void WMaxFlowSS::fsmInit() {
    setName("WMaxFlowSS");
    statesEventsInit(WMaxFlowSS::STATE_NUM, WMaxFlowSS::EVENT_NUM, STATE_START);

    stateInit(STATE_START, "Start", onEventState_Start);
    stateInit(STATE_SEND_DSA_REQ, "Sending DSA-REQ", STATE_WAITING_DSX_RVD, onEnterState_SendDsaReq);
    stateInit(STATE_WAITING_DSX_RVD, "Waiting for DSX-RVD", onEventState_WaitingDsxRvd);
    stateInit(STATE_WAITING_DSA_RSP, "Waiting for DSA-RSP", onEventState_WaitingDsaRsp);
    stateInit(STATE_SEND_DSA_ACK, "Sending DSA-ACK", STATE_OPERATIONAL, onEnterState_SendDsaAck);
    stateInit(STATE_OPERATIONAL, "Operational", onEventState_Operational);

    stateVerify();

    eventInit(EVENT_START, "Service flow creation started");
    eventInit(EVENT_DSX_RVD_RECEIVED, "Received DSX-RVD");
    eventInit(EVENT_DSA_RSP_RECEIVED, "Received DSA-RSP");

    eventVerify();
}


void WMaxFlowSS::handleMessage(cMessage *msg) {
    if(dynamic_cast<WMaxCtrlFlowCreationStart*>(msg)) {
        onEvent(EVENT_START, msg);
        delete msg;
        return;
    }

    if(dynamic_cast<WMaxMsgDsxRvd*>(msg)) {
        onEvent(EVENT_DSX_RVD_RECEIVED, msg);
        delete msg;
        return;
    }

    if(dynamic_cast<WMaxMsgDsaRsp*>(msg)) {
        onEvent(EVENT_DSA_RSP_RECEIVED, msg);
        delete msg;
        return;
    }
}

// Start state
FsmStateType WMaxFlowSS::onEventState_Start(Fsm * fsm, FsmEventType e, cMessage * msg){
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    WMaxCtrlFlowCreationStart *flowcrstart = dynamic_cast<WMaxCtrlFlowCreationStart*>(msg);
    flow->qos           = flowcrstart->getQos(0);
    flow->gate          = flowcrstart->getGateIndex();
    flow->transactionID = GetNextTransactionID();
    switch (e) {
      case EVENT_START:
        return STATE_SEND_DSA_REQ;
      default:
        CASE_IGNORE(fsm, e);
    }
}

// Send DSA-REQ state
FsmStateType WMaxFlowSS::onEnterState_SendDsaReq(Fsm * fsm) {
    WMaxMsgDsaReq *msg = new WMaxMsgDsaReq();
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    msg->setName("DSA-REQ");
    msg->setTransactionID(flow->transactionID);
    //flow->qos.msr=800000;
    msg->setQosArraySize(1);
    msg->setQos(0,flow->qos);

    WMaxCtrlSS *ctrlSS = dynamic_cast<WMaxCtrlSS*>(flow->parentFsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ctrlSS->parentModule()->submodule("ssInfo"));
    SLog(fsm, Notice) << "Sending DSA-REQ (cid=" << ssinfo->info.basicCid << ", transID=" << msg->getTransactionID() 
              << ")" << LogEnd;
    ctrlSS->sendMsg(msg, "", "macOut", ssinfo->info.basicCid);

    return fsm->State();
}

// Waiting for DSX-RVD state
FsmStateType WMaxFlowSS::onEventState_WaitingDsxRvd(Fsm * fsm, FsmEventType e, cMessage * msg) {
    switch (e) {
    case EVENT_DSX_RVD_RECEIVED:
        return STATE_WAITING_DSA_RSP;
    default:
        CASE_IGNORE(fsm, e);
    }
}

// Waiting for DSA-RSP state
FsmStateType WMaxFlowSS::onEventState_WaitingDsaRsp(Fsm * fsm, FsmEventType e, cMessage * msg) {
    WMaxMsgDsaRsp *dsarsp = dynamic_cast<WMaxMsgDsaRsp*>(msg);
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    flow->cid = dsarsp->getCid();
    switch (e) {
    case EVENT_DSA_RSP_RECEIVED:
        return STATE_SEND_DSA_ACK;
    default:
        CASE_IGNORE(fsm, e);
    }
}

// Send DSA-ACK state
FsmStateType WMaxFlowSS::onEnterState_SendDsaAck(Fsm * fsm) {
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    WMaxCtrlSS *ctrlSS = dynamic_cast<WMaxCtrlSS*>(flow->parentFsm);

    WMaxMsgDsaAck *msg = new WMaxMsgDsaAck();
    msg->setName("DSA-ACK");
    msg->setTransactionID(flow->transactionID);
    msg->setQosArraySize(1);
    msg->setQos(0,flow->qos);

    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ctrlSS->parentModule()->submodule("ssInfo"));
    SLog(fsm, Notice) << "Received DSA-RSP, sending DSA-ACK (transID=" << msg->getTransactionID() << ")." << LogEnd;
    ctrlSS->sendMsg(msg, "", "macOut", ssinfo->info.basicCid);

    WMaxMacAddConn *addConn = new WMaxMacAddConn();
    addConn->setName("Add connection");
    addConn->setGateIndex(flow->gate);
    addConn->setCid(flow->cid);
    addConn->setQosArraySize(1);
    addConn->setQos(0,flow->qos);
    ctrlSS->send(addConn, "macOut");

    ctrlSS->onEvent(WMaxCtrlSS::EVENT_SERVICE_FLOW_COMPLETE, 0);

    return fsm->State();
}

// Operational state
FsmStateType WMaxFlowSS::onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage * msg) {
return fsm->State();
}

