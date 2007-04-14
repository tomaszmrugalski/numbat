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

#define Log ev << fsm->fullName() << ":" 

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
    stateInit(STATE_SEND_REG_REQ,      "Sending REG-REQ", STATE_WAIT_REG_RSP, onEnterState_SendRegReq);
    stateInit(STATE_WAIT_REG_RSP,      "Waiting for REG-RSP", onEventState_WaitForRegRsp);

    stateInit(STATE_INITIATE_SVC_FLOW_CREATION, "Initiate service flow creation", STATE_OPERATIONAL, onEnterState_InitiateSvcFlowCreation);

    stateInit(STATE_OPERATIONAL,       "Operational", onEventState_Operational);
    stateInit(STATE_SEND_MSHO_REQ,     "Sending MSHO-REQ", STATE_WAIT_BSHO_RSP, onEnterState_SendMshoReq);
    stateInit(STATE_WAIT_BSHO_RSP,     "Waiting for BSHO-RSP", onEventState_WaitForBshoRsp);
    stateInit(STATE_SEND_HO_IND,       "Sending HO-IND", STATE_HANDOVER_COMPLETE, onEnterState_SendHoInd);
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
    eventInit(EVENT_REG_RSP_RECEIVED, "REG-RSP received.");
    eventInit(EVENT_CDMA_CODE, "(Initial ranging) CDMA opportunity received");
    eventInit(EVENT_BSHO_RSP_RECEIVED, "BSHO-RSP received");
    eventInit(EVENT_HO_CDMA_CODE, "(Handover ranging) CDMA opportunity received");
    eventVerify();

    TIMER(NetworkEntry, 0.1, "Start Network entry");
    TIMER(Handover,     0.2, "Start handover");
    TIMER(Reentry,      0.1, "Network reentry");

    stringUpdate();

    neType == WMAX_CTRL_NETWORK_ENTRY_INITIAL; // by default, use normal network entry
}

void WMaxCtrlSS::initialize() {
    fsmInit();
    // uncomment ONLY ONE of the following:
    TIMER_START(NetworkEntry);  // Option 1: normal network entry (after SS boot)
    //TIMER_START(Reentry);     // Option 2: network reentry (at target BS)
    
    // Option 1+bonus: if NetworkEntry is chosen, it is also possible, to perform handover
    TIMER_START(Handover);
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

}

// wait for DL-MAP state
FsmStateType WMaxCtrlSS::onEventState_WaitForDlmap(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_DLMAP:
	return STATE_WAIT_FOR_UCD;
    default:
	CASE_IGNORE(e);
    }
}

// wait for UCD state
FsmStateType WMaxCtrlSS::onEventState_WaitforUcd(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_UCD:
	return STATE_SEND_RNG_REQ;
    default:
	CASE_IGNORE(e);
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
	CASE_IGNORE(e);
    }
}

FsmStateType WMaxCtrlSS::onEvent_CdmaCode(cMessage *msg)
{
    return WMaxCtrlSS::STATE_SEND_CDMA;
}

FsmStateType WMaxCtrlSS::onEnterState_SendRngReq(Fsm * fsm)
{
    WMaxMsgRngReq * rng = new WMaxMsgRngReq();
    rng->setName("RNG-REQ");
    fsm->send(rng, "macOut");
    return fsm->State();
}

// wait for RNG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);

    switch (e) {
    case EVENT_RNG_RSP_RECEIVED: 
	if (ss->neType == WMAX_CTRL_NETWORK_ENTRY_INITIAL) {
	    ev << ss->fullName() << ": Network entry type: initial, switching to 'send SBC-REQ'." << endl;
	    return STATE_SEND_SBC_REQ;
	} else {
	    ev << ss->fullName() << ":Network entry type: reentry, switching to 'OPERATIONAL'." << endl;
	    return STATE_OPERATIONAL;
	}
    default:
	CASE_IGNORE(e);
    }
}

// send SBC-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendSbcReq(Fsm * fsm)
{
    WMaxMsgSbcReq * req = new WMaxMsgSbcReq();
    req->setName("SBC-REQ");
    fsm->send(req, "macOut");
    return fsm->State();
}

// wait for SBC-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForSbcRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_SBC_RSP_RECEIVED:
	return STATE_SEND_REG_REQ;
    default:
	CASE_IGNORE(e);
    }
    return fsm->State();
}

// send REG-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendRegReq(Fsm * fsm)
{
    WMaxMsgRegReq * reg = new WMaxMsgRegReq();
    reg->setName("SBC-REQ");
    fsm->send(reg, "macOut");
    return fsm->State();
}

// wait for REG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRegRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_REG_RSP_RECEIVED:
//	return STATE_OPERATIONAL;
        return STATE_INITIATE_SVC_FLOW_CREATION;
    default:
	CASE_IGNORE(e);
    }
    return fsm->State();
}

// inititae service flow creation state
FsmStateType WMaxCtrlSS::onEnterState_InitiateSvcFlowCreation(Fsm * fsm) {
    WMaxFlowSS *flow;
    WMaxCtrlSS *ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    
    flow = new WMaxFlowSS(fsm);
    ss->serviceFlows.push_back(flow);
    
    return fsm->State();
}


FsmStateType WMaxCtrlSS::onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_HANDOVER_START:
	return STATE_SEND_MSHO_REQ;
    default:
	CASE_IGNORE(e);
    }
}

// send MSHO-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendMshoReq(Fsm *fsm)
{
    WMaxMsgMSHOREQ * mshoReq = new WMaxMsgMSHOREQ("MSHO-REQ");
    mshoReq->setName("MSHO-REQ");
    ev << fsm->fullName() << ": Sending MSHO-REQ message." << endl;
    fsm->send(mshoReq, "macOut");
    return fsm->State();
}

// wait for BSHO-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForBshoRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_BSHO_RSP_RECEIVED:
	return STATE_SEND_HO_IND;
    default:
	CASE_IGNORE(e);
    }
}

// sent HO-IND state
FsmStateType WMaxCtrlSS::onEnterState_SendHoInd(Fsm *fsm)
{
    WMaxMsgHOIND * hoInd = new WMaxMsgHOIND();
    hoInd->setName("HO-IND");
    fsm->send(hoInd, "macOut");
    return fsm->State();
}
    
// handover complete state
FsmStateType WMaxCtrlSS::onEnterState_HandoverComplete(Fsm * fsm)
{   WMaxCtrlSS *wskSS = dynamic_cast<WMaxCtrlSS*>(fsm);
    wskSS->reConnect();
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEnterState_SendCdma(Fsm *fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    Log << " Sending CDMA code" << endl;
    WMaxMsgCDMA * cdma = new WMaxMsgCDMA();
    if (ss->neType == WMAX_CTRL_NETWORK_REENTRY) {
	cdma->setPurpose(WMAX_CDMA_PURPOSE_HO_RNG);
	cdma->setName("CDMA code (ho rng)");
    } else {
	cdma->setPurpose(WMAX_CDMA_PURPOSE_INITIAL_RNG);
	cdma->setName("CDMA code (initial rng)");
    }
    fsm->send(cdma, "macOut");
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_WaitForAnonRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_RNG_RSP_RECEIVED:
	return STATE_SEND_RNG_REQ;
    default:
	CASE_IGNORE(e);
    }
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_PowerDown(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    switch (e) {
    case EVENT_ENTRY_START:
	ss->neType = WMAX_CTRL_NETWORK_ENTRY_INITIAL;
	return STATE_WAIT_FOR_DLMAP;
    case EVENT_REENTRY_START:
	ss->neType = WMAX_CTRL_NETWORK_REENTRY;
	return STATE_WAIT_FOR_CDMA;
    default:
	CASE_IGNORE(e);
    }
}
void WMaxCtrlSS::reConnect() {
    
    cModule *SS = parentModule();
    cModule *physim = parentModule()->parentModule();
    cModule *BS =SS->gate( "out" )->toGate()->ownerModule();
    int actBS = BS->index();
    int nextBS = (actBS+1)%(BS->size());
    ev << fullName() << ": Currently associated with BS: " << actBS << ", switching to BS :" << nextBS << endl;
    cModule *BSnext = physim->submodule("BS", nextBS);
    if (!BSnext)
	opp_error("Unable to find BS:%d\n", nextBS);
    
    SS->gate("out")->disconnect();
    BS->gate("out")->disconnect();
    BSnext->gate("out")->disconnect();
    SS->gate("out")->connectTo(BSnext->gate("in")) ; 
    BSnext->gate("out")->connectTo(SS->gate("in")) ;

    // after reconnecting to other BS, perform Reentry, not normal entry
    neType = WMAX_CTRL_NETWORK_REENTRY; 

    // uncomment this to perform another handover
    TIMER_START(Handover);
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

}

void WMaxCtrlBS::handleMessage(cMessage *msg) 
{
    if (dynamic_cast<WMaxMsgRngReq*>(msg)) {
	ev << fullName() << ": RNG-REQ received, sending RNG-RSP." << endl;
	WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp("RNG-RSP (initial rng)");
	rsp->setName("RNG-RSP");
	rsp->setPurpose(WMAX_CDMA_PURPOSE_INITIAL_RNG);
	send(rsp, "macOut");
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgSbcReq*>(msg)) {
	ev << fullName() << ": SBC-REQ received, sending SBC-RSP." << endl;
	WMaxMsgSbcRsp * rsp = new WMaxMsgSbcRsp("SBC-RSP");
	rsp->setName("SBC-RSP");
	send(rsp, "macOut");
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgRegReq*>(msg)) {
	ev << fullName() << ": REG-REQ received, sending REG-RSP." << endl;
	WMaxMsgRegRsp * rsp = new WMaxMsgRegRsp("REG-RSP");
	rsp->setName("REG-RSP");
	send(rsp, "macOut");
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgMSHOREQ*>(msg)) {
	ev << fullName() << ":MSHO-REQ received, sending BSHO-RSP." << endl;
	WMaxMsgBSHORSP * bshoRsp = new WMaxMsgBSHORSP();
	bshoRsp->setName("BSHO-RSP");
	send(bshoRsp, "macOut");
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgHOIND*>(msg)) {
	ev << fullName() << ":HO-IND received." << endl;
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgCDMA*>(msg)) {
	WMaxMsgCDMA * cdma = dynamic_cast<WMaxMsgCDMA*>(msg);
	ev << fullName() << ": " << msg->fullName() << " (purpose=" << int(cdma->getPurpose()) << ") received";
	switch (cdma->getPurpose()) {
	case WMAX_CDMA_PURPOSE_HO_RNG:
	{
	    ev << ", sending Anonymous (handover) RNG-RSP." << endl;
	    WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp();
	    rsp->setName("Anonymous RNG-RSP");
	    send(rsp, "macOut");
	    break;
	}
	case WMAX_CDMA_PURPOSE_INITIAL_RNG:
	{
	    ev << ", sending Anonymous (initial) RNG-RSP." << endl;
	    WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp();
	    rsp->setName("Anonymous (initial) RNG-RSP");
	    send(rsp, "macOut");
	    break;
	}
	case WMAX_CDMA_PURPOSE_BWR:
	default:
	    /// @todo - Best effort traffic.
	    ev << ", not supported." << endl;
	    opp_error("That type of CDMA code is not supported yet (purpose=%d).", cdma->getPurpose());
	    break;
	}
	
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgDsaReq*>(msg)) {
        WMaxMsgDsaReq *dsareq = dynamic_cast<WMaxMsgDsaReq*>(msg);

        WMaxMsgDsxRvd *dsxrvd = new WMaxMsgDsxRvd();
        dsxrvd->setName("DSX-RVD");
        dsxrvd->setTransactionID(dsareq->getTransactionID());
        dsxrvd->setConfirmationCode(0);
        send(dsxrvd, "macOut");

        WMaxMsgDsaRsp *dsarsp = new WMaxMsgDsaRsp();
        dsarsp->setName("DSA-RSP");
        dsarsp->setTransactionID(dsareq->getTransactionID());
        dsarsp->setQosArraySize(1);
        dsarsp->setQos(0,dsareq->getQos(0));
        dsarsp->setCid(1024); /// @todo generate CID
        send(dsarsp, "macOut");

        delete msg;
        return;
    }

    ev << "Received " << msg->fullName() << " message." << endl;
}


/********************************************************************************/
/*** WMax Service Flow Creation SS***********************************************/
/********************************************************************************/

//Define_Module(WMaxFlowSS);

WMaxFlowSS::WMaxFlowSS(Fsm * fsm) {
    parentFsm = fsm;
    fsmInit();
    WMaxCtrlFlowCreationStart *msg = new WMaxCtrlFlowCreationStart();
    handleMessage(msg);
}

void WMaxFlowSS::fsmInit() {
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
    flow->transactionID=rand();
    switch (e) {
    case EVENT_START:
        return STATE_SEND_DSA_REQ;
    default:
        CASE_IGNORE(e);
    }
}

// Send DSA-REQ state
FsmStateType WMaxFlowSS::onEnterState_SendDsaReq(Fsm * fsm) {
    WMaxMsgDsaReq *msg = new WMaxMsgDsaReq();
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    msg->setName("DSA-REQ");
    msg->setTransactionID(flow->transactionID);
    flow->qos.msr=800000;
    msg->setQosArraySize(1);
    msg->setQos(0,flow->qos);
    WMaxCtrlSS *ctrlSS = dynamic_cast<WMaxCtrlSS*>(flow->parentFsm);
    ctrlSS->send(msg, "macOut");
    return fsm->State();
}

// Waiting for DSX-RVD state
FsmStateType WMaxFlowSS::onEventState_WaitingDsxRvd(Fsm * fsm, FsmEventType e, cMessage * msg) {
    switch (e) {
    case EVENT_DSX_RVD_RECEIVED:
        return STATE_WAITING_DSA_RSP;
    default:
        CASE_IGNORE(e);
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
        CASE_IGNORE(e);
    }
}

// Send DSA-ACK state
FsmStateType WMaxFlowSS::onEnterState_SendDsaAck(Fsm * fsm) {
    WMaxMsgDsaAck *msg = new WMaxMsgDsaAck();
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    msg->setName("DSA-ACK");
    msg->setTransactionID(flow->transactionID);
    msg->setQosArraySize(1);
    msg->setQos(0,flow->qos);
    WMaxCtrlSS *ctrlSS = dynamic_cast<WMaxCtrlSS*>(flow->parentFsm);
    ctrlSS->send(msg, "macOut");
    return fsm->State();
}

// Operational state
FsmStateType WMaxFlowSS::onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage * msg) {

}

