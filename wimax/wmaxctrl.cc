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
#include <math.h>
#include "wmaxctrl.h"
#include "wmaxmsg_m.h"
#include "logger.h"
#include "hoinfo.h"
#include "wmaxradio.h"
#include "wmaxmac.h"
#include "ssinfo.h"
#include "mih_m.h"
#include "IPv6Address.h"//Adam
#include "InterfaceTableAccess.h" // Adam
#include "xMIPv6Access.h"
// #include "IPv6NeighbourDiscovery.h"

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
  s << "state=" << f.CurrentStateGet()->getFullName()
    << ", transID=" << f.transactionID << " cid=" << f.cid
    << " qos=[connType=" << f.qos.connType << ", msr=" << f.qos.msr << "]";
  return s;
}

static int GetCidFromMsg(cMessage * msg)
{
    WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->getControlInfo());
    if (!hdr) {
	opp_error("Unable to find MacHeader in message %s\n", msg->getFullName());
    }
    return hdr->cid;
}

/********************************************************************************/
/*** WMax Ctrl SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxCtrlSS);

WMaxCtrlSS::WMaxCtrlSS()
{
    serviceFlows.clear();
}

void WMaxCtrlSS::fsmInit() {
    /// @todo - SS should perform network entry procedure (i.e. start in WAIT_FOR_CDMA state)
    //statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_WAIT_FOR_DLMAP);
    statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_POWER_DOWN);

    // state init
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

    stateInit(STATE_SEND_MOB_SCN_REQ,     "Sending MOB_SCN-REQ", STATE_WAIT_MOB_SCN_RSP, onEnterState_SendMobScnReq);
    stateInit(STATE_WAIT_MOB_SCN_RSP,     "Waiting for MOB_SCN-RSP", onEventState_WaitForMobScnRsp);

    stateInit(STATE_WAIT_HANDOVER_ACK,     "Waiting for HANDOVER_ACK", onEventState_WaitForHandoverAck);//============= Adam 14-09-2011 =====================

    stateInit(STATE_SEND_MSHO_REQ,     "Sending MSHO-REQ", STATE_WAIT_BSHO_RSP, onEnterState_SendMshoReq);
    stateInit(STATE_WAIT_BSHO_RSP,     "Waiting for BSHO-RSP", onEventState_WaitForBshoRsp);
    stateInit(STATE_WAIT_L3_DETACH_READY,"Waiting for L3 detach", onEventState_WaitForL3Detach);
    stateInit(STATE_SEND_HO_IND,       "Sending HO-IND", onEventState_SendHoInd, onEnterState_SendHoInd, onExitState_SendHoInd);
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
    eventInit(EVENT_MOB_SCN_RSP_RECEIVED, "MOB_SCN-RSP received");
    
    eventInit(EVENT_HANDOVER_ACK_RECEIVED, "HANDOVER_ACK received");//============= Adam 14-09-2011 =====================
    
    eventInit(EVENT_BSHO_RSP_RECEIVED, "BSHO-RSP received");
    eventInit(EVENT_HO_CDMA_CODE, "(Handover ranging) CDMA opportunity received");
    eventInit(EVENT_SERVICE_FLOW_COMPLETE, "Service Flow complete");
    eventInit(EVENT_L3_DETACH_READY, "L3 is ready to detach");
    eventInit(EVENT_HO_IND_SENT,  "HO-IND transmitted");
    eventVerify();
    
    float ne = (double)SS->par("NetworkEntryTime");
    float ho = (double)SS->par("HandoverTime") + uniform(0,0.5); // + extra random delay 0 ... 500ms

    TIMER(NetworkEntry, ne, "Start Network entry");
    TIMER(Handover,     ho, "Start handover");
    TIMER(Reentry,      0.1, "Network reentry");
    Log(Notice) << "Timers: NetworkEntry=" << ne << ", Handover=" << ho << LogEnd;
    stringUpdate();
}

void WMaxCtrlSS::initialize() {
    SS = getParentModule()->getParentModule();
    hoInfo = new HoInfo_t();
    CLEAR(hoInfo);
    hoActionTimeData.setName("HO time length");
    neType = WMAX_CTRL_NETWORK_ENTRY_INITIAL; // by default, use normal network entry

    fsmInit();

    // start with network entry
    TIMER_START(NetworkEntry);

    cModule * tmp1 = SS->getSubmodule("ssInfo");
    ssInfo * tmp2  = dynamic_cast<ssInfo*>(tmp1);
    hoInfo = &tmp2->hoInfo;

    int initialBS = SS->par("initialBS");
//============= Adam 11-09-2011 =====================
    ift2 = InterfaceTableAccess2().get();
    Handover = 0;
    NieaktywnoscL3Duration.setName("Czas nieaktywnosci SS dla L3");
//============= Adam, end  11-09-2011==================    
    Log(Notice) << "Attaching to initial BS: " << initialBS << LogEnd;
    connectBS(initialBS);

    char buf[80];
    sprintf(buf, "%s%d", getFullName(), SS->getIndex());
    setName(buf);

    cModule * tmp = getParentModule()->getParentModule()->getSubmodule("ssInfo");
    if (tmp) {
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);
	info->addEventListener(this);
    }

    WATCH_PTRLIST(serviceFlows);
}

simtime_t /*double*/ WMaxCtrlSS::sendMsg(cMessage * msg, std::string paramName, const std::string &gateName, int cid, double extraDelay)
{
    double delay = 0;
    if (strlen(paramName.c_str())) {
        char buf[80];
        sprintf(buf, "Min%s", paramName.c_str());
        double min = (double)par(buf);
        
        sprintf(buf, "Max%s", paramName.c_str());
        double max = (double)par(buf);
        
        delay = uniform(min, max);
    }
    delay += extraDelay;

    Log(Debug) << "Sending " << msg->getName() << " in " << setiosflags(ios::fixed) << setprecision(3) << delay*1000
	       << "msecs (cid=" << cid << ")." << LogEnd;

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = cid;
    msg->setControlInfo(hdr);

    sendDelayed(msg, delay, gateName.c_str());

    return delay;
}


/** 
 * general dispatcher
 * 
 * @param msg 
 */
void WMaxCtrlSS::handleMessage(cMessage *msg) 

{
    stringstream tmp;
    tmp << "ssMac[" << SS->getIndex() << "]";
    
    if (ssMAC *mac = dynamic_cast<ssMAC*>(SS->getSubmodule(tmp.str().c_str())))
	mac->updateString();

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

	for (unsigned int i=0; i<ulmap->getIEArraySize(); i++) {
	    WMaxUlMapIE & ie = ulmap->getIE(i);
	    if ( (ie.uiuc == WMAX_ULMAP_UIUC_CDMA_BWR) ) {
		onEvent(EVENT_CDMA_CODE, msg);
	    }
	}

	delete msg;
	return;
    }

    if (dynamic_cast<MihEvent_L3AddrConfigured*>(msg)) {
	onEvent(EVENT_L3_DETACH_READY, msg);
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

    if (dynamic_cast<WMaxMsgMobScnRsp*>(msg)) {
        onEvent(EVENT_MOB_SCN_RSP_RECEIVED, msg);
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

        //WMaxFlowSS *flow; //unused variable (MiM)
	for (list<WMaxFlowSS*>::iterator it=serviceFlows.begin();it!=serviceFlows.end(); ++it)
	{
            if ( (*it)->transactionID == dsxrvd->getTransactionID()) {
                (*it)->handleMessage(msg);
                return;
            }
	}
        return;
    }

    if (dynamic_cast<WMaxMsgDsaRsp*>(msg)) 
    {
        WMaxMsgDsaRsp *dsarsp = dynamic_cast<WMaxMsgDsaRsp*>(msg);

        //WMaxFlowSS *flow; //unused variable (MiM)
	for (list<WMaxFlowSS*>::iterator it=serviceFlows.begin(); it!=serviceFlows.end(); ++it)
	{
            if ((*it)->transactionID == dsarsp->getTransactionID()) {
                (*it)->handleMessage(msg);
                return;
            }
        }
        return;
    }

    if (dynamic_cast<MihEvent_HandoverEnd*>(msg)) {
//============= Adam 11-09-2011 =====================
// wstawienie NCoA jako CoA
        // logger::EchoOn();   // wlaczenie logowania z Numbata
        Log(Notice) << endl << endl << "Handover end" << LogEnd;
        if( this->getParentModule()->getParentModule()->par("FMIP") ){
            InterfaceEntry *ie = ift2 -> getInterface(1);    // WiMAX MN
            
            if( ie -> ipv6Data() -> getNumAddresses() < 3 ){ // jesli jest tylko link-local i HoA
                IPv6Address removeCoA = ie ->ipv6Data() -> getAddress(0);
                // powinno sie usunac wczesniejszy CoA, POPRAWIC
                // ie->ipv6Data()->removeAddress( removeCoA );       // poprawic, nie bedzie dzialalo dla wiecej niz 2 ARow, a moze i bedzie ?    
                // IPv6Address CoA = ie->ipv6Data()->removeAddress( removeCoA );       // poprawic, nie bedzie dzialalo dla wiecej niz 2 ARow, a moze i bedzie ?
                ASSERT( !removeCoA.isUnspecified() );

                EV << "Handover End removing CoA = " << removeCoA.str() << "new CoA = " << ift2->getHandover_NCoA().str() << endl;

                IPv6Address linkLocalAddress = ie->ipv6Data()->getLinkLocalAddress();
                bool isLinkLocalTentative = ie->ipv6Data()->isTentativeAddress( linkLocalAddress );
                // if the link local address is tentative, then we make the global unicast address tentative as well
                ie->ipv6Data()->assignAddress( ift2->getHandover_NCoA(), isLinkLocalTentative, simTime(), simTime()+100, false);   // poprawic, nie wiem czy dobrze zrobione
            }
        }
        Handover = 1;
//============= Adam, end  11-09-2011==================
        onEvent(EVENT_HO_IND_SENT, msg);
        delete msg;
        return;
    }
    
    delete msg;
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
    string purpose = "initial";
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);

//     cModule *SS = ss->getParentModule();
    cModule *SSInfo = ss->SS->getSubmodule("ssInfo");
    if (!SSInfo)
        opp_error("Unable to obtain ssInfo submodule in SS[%d]\n", ss->SS->getIndex());
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(SSInfo);

    WMaxRngReq rngReq;
    rngReq.macAddr = ssinfo->info.macAddr;

    WMaxMsgRngReq * rng = new WMaxMsgRngReq();
    rng->setName("RNG-REQ");
    rng->setRngReq(rngReq);

    if (ss->neType == WMAX_CTRL_NETWORK_REENTRY) {
        purpose = "handover";

	// find our IPv6 if remote autoconf is used
	
//============= Adam 14-09-2011 ===================== nieuzywany parametr dhcp.remoteAutoconf
	// if (ssinfo->hoInfo.dhcp.remoteAutoconf)
	// {
	    // cModule * ss = fsm->getParentModule()->getParentModule();
	    // stringstream tmp;
	    // tmp << "ssIPv6.DHCPv6Cli" << ss->getIndex();
	    // cModule * dhcp = ss->getModuleByRelativePath(tmp.str().c_str());
	    // if (!dhcp)
		// opp_error("Failed to find DHCPv6 client: relative path:%s from module %s", tmp.str().c_str(), ss->getFullName());
	    // IPv6Address addr = IPv6Address(dhcp->par("nextIP"));	// Adam zmieniony kontruktor, przedtem byl z ipv6.h -> inet_pton
	    // SLog(fsm, Info) << "Remote AutoConf enabled, sending my next IP:" << addr.str() << LogEnd;
	    // rng->setMyIP(addr);
	// } else{
//============= Adam, end  14-09-2011==================    
	    rng->setMyIP(IPv6Address());//rng->setMyIP(IPv6Address("::",true));		//Adam prawdopodobnie wpisuje adres 0
    // }//============= Adam 14-09-2011 =====================
	if (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_FULL_STATE_TRANSFER) {
	    int cnt = 0;
	    for (list<WMaxFlowSS*>::iterator it = ss->serviceFlows.begin(); 
		 it!=ss->serviceFlows.end(); it++) {
		cnt++;
	    }
	    SLog(fsm, Info) << "Generating reentry RNG-REQ (" << cnt << " flows)." << LogEnd;
	    rng->setSfCidArraySize(cnt);
	    rng->setSfQosArraySize(cnt);
	    int i=0;
	    for (list<WMaxFlowSS*>::iterator it = ss->serviceFlows.begin(); 
		 it!=ss->serviceFlows.end(); it++) {
		cnt++;
		rng->setSfCid(i, (*it)->cid);
		rng->setSfQos(i, (*it)->qos);
		i++;
	    }
        }
    }

    ss->send(rng, "macOut"/*, 0*/); //0 --> -1 (MiM)

    SLog(fsm, Notice) << "Sending " << purpose << " RNG-REQ." << LogEnd;
    return fsm->State();
}

// wait for RNG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));

    switch (e) {
    case EVENT_RNG_RSP_RECEIVED: 
      {
        WMaxMsgRngRsp * rng = dynamic_cast<WMaxMsgRngRsp*>(msg); 
        WMaxRngRsp rngRsp = rng->getRngRsp();
        if (rngRsp.ssMacAddr == ssinfo->info.macAddr && rng->getPurpose() == WMAX_CDMA_PURPOSE_INITIAL_RNG && rngRsp.basicCid>0) { //added the second and third condition checks in order to avoid receiving anonymous (handover) RNG-RSP when waiting for RNG-RSP for network (re-)entry (MiM)
          ssinfo->info.basicCid = rngRsp.basicCid;
          ssinfo->stringUpdate();

          SLog(ss, Notice) << "RNG-RSP received, basicCid="<<rngRsp.basicCid << LogEnd;

          WMaxMacAddMngmntConn *addConn = new WMaxMacAddMngmntConn();
          addConn->setCid(rngRsp.basicCid);
          ss->send(addConn,"macOut");
          
          for (unsigned int i=0; i<rng->getOldCidArraySize(); i++) {
              int oldCid = rng->getOldCid(i);
              int newCid = rng->getNewCid(i);

              for (list<WMaxFlowSS*>::iterator it = ss->serviceFlows.begin(); it!=ss->serviceFlows.end(); it++) {
		  SLog(ss, Debug) << "Trying to update cid " << oldCid << "->" << newCid << LogEnd;
		  
		  if ((*it)->cid == oldCid) {
		      SLog(ss, Debug) << "SF found. Performing update." << LogEnd;
		      (*it)->cid = newCid;
		      WMaxEvent_FlowEnable * en = new WMaxEvent_FlowEnable();
		      (*it)->handleMessage(en);
		      
		      SLog(ss, Info) << "Creating SF cid=" << newCid << LogEnd;
		      WMaxMacAddConn *addConn = new WMaxMacAddConn();
		      addConn->setName("Add connection");
		      addConn->setMacAddr(ssinfo->info.macAddr);
		      addConn->setGateIndex(0);
		      addConn->setCid((*it)->cid);
		      addConn->setQosArraySize(1);
		      addConn->setQos(0,(*it)->qos);
		      ss->send(addConn, "macOut");
		  }
              }
          }

          SLog(ss, Debug) << "Switching to 'send SBC-REQ'." << LogEnd;
          return STATE_SEND_SBC_REQ;
        }
      }
    default:
	CASE_IGNORE(fsm, e);
    }
}

// send SBC-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendSbcReq(Fsm * fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));
    
    if ( (ss->neType == WMAX_CTRL_NETWORK_REENTRY) && (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_OMIT_SBC_REQ)) {
	SLog(fsm, Notice) << "Reentry: omit-sbc-req flag set, skipping SBC-REQ." << LogEnd;
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
	    SLog(fsm, Notice) << "Reentry: skip-sa-tek flag set, skipping SA-TEK exchange." << LogEnd;
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
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));
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
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));
    if ( (ss->neType == WMAX_CTRL_NETWORK_REENTRY) && (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_OMIT_REG_REQ)) {
	SLog(fsm, Notice) << "Reentry: omit-reg-req flag set, skipping REG-REQ." << LogEnd;
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
	SLog(fsm, Notice) << "Reentry: full-state-transfer flag set, skipping service flow creation." << LogEnd;
	return STATE_OPERATIONAL; /* state override: switch to SEND_REG_REQ */
    }

    //WMaxFlowSS *flow = new WMaxFlowSS(fsm); //here the WMaxFlowSS is created... not using the cModuleType::create() (MiM)
    //MiM ........................
    cModuleType *mtype = cModuleType::get("WMaxFlowSS");
    
    cModule *flowmodule = mtype->create("WMaxFlowSS", fsm);
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(flowmodule);
    flow->setParentFsm(fsm);
    flow->finalizeParameters();
    flow->buildInside();
    //end of MiM...............................
    flow->handleMessage( ss->createNewFlowEvent() );
    ss->serviceFlows.push_back(flow);
    ss->sfCnt = 1;
    // @todo - there is only one flow, for now it's ok, but support for more service flow must be added
    
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

    //double x, y;
    simtime_t x, y;//MiM

    switch (ss->neType) {
    case WMAX_CTRL_NETWORK_REENTRY:
      x = simTime() - ss->hoReentryTimestamp;
      ss->hoReentryCompleteTimestamp=simTime();
      y = ss->hoReentryCompleteTimestamp - ss->hoStartTimestamp;
      ss->hoActionTimeData.collect(y);
      SLog(fsm, Notice) << "Network reentry complete: " << x << "secs (" 
                         << ss->hoReentryTimestamp << "-" << simTime() << ")." << LogEnd;
      ss->mihNotify(MIH_EVENT_REENTRY_END);
      break;
    case WMAX_CTRL_NETWORK_ENTRY_INITIAL:
      SLog(fsm, Notice) << "Initial network entry complete." << LogEnd;
      ss->mihNotify(MIH_EVENT_ENTRY_END);
      break;
    case WMAX_CTRL_NERWORK_SCAN:
      ss->neType = WMAX_CTRL_NETWORK_REENTRY;
    }
    
    if (ss->hoInfo->isMobile)
      STATIC_TIMER_START(ss, Handover);
    
    return fsm->State();
}


FsmStateType WMaxCtrlSS::onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    int isMobile = (int)ss->SS->par("wmaxIsMobile");
    
    switch (e) {
      case EVENT_HANDOVER_START:
	  switch (isMobile)
	  {
	  case 1:
	  case 3:
	      return STATE_SEND_MSHO_REQ; // isMobile == 1 -> handover executed after certain timeout
	  case 2:
	      return STATE_SEND_MOB_SCN_REQ; // isMobile == 2 -> SS changes location and handover is based on distance
	  }
      default:
        CASE_IGNORE(fsm, e);
    }
}

// send MOB_SCN-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendMobScnReq(Fsm *fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));
    WMaxMsgMobScnReq * mobScnReq = new WMaxMsgMobScnReq();
    mobScnReq->setName("MOB_SCN-REQ");
    SLog(fsm, Notice) << "Sending MOB_SCN-REQ message." << LogEnd;
    ss->sendMsg(mobScnReq, "", "macOut", ssinfo->info.basicCid);
    ss->neType = WMAX_CTRL_NERWORK_SCAN;
    return fsm->State();
}

//============= Adam 10-09-2011 =====================
void WMaxCtrlSS::HandoverAck(cMessage *msg)
{
    Enter_Method("HandoverAck");
    take(msg);
    onEvent(EVENT_HANDOVER_ACK_RECEIVED, msg);
}
FsmStateType WMaxCtrlSS::onEventState_WaitForHandoverAck(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    // WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    
    switch (e) {
      case EVENT_HANDOVER_ACK_RECEIVED:
	      return STATE_SEND_MSHO_REQ; 
      default:
        CASE_IGNORE(fsm, e);
    }
}
//============= Adam, end  10-09-2011==================
// wait for MOB_SCN-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForMobScnRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS*>(fsm);
int actBS, nearestBS;
long int x1, y1, x2, y2;
double minR;
cModule *physim, *BS;

    switch (e) {
    case EVENT_MOB_SCN_RSP_RECEIVED:

        // fake scan
        /// @todo improve scanning

//         SS = fsm->getParentModule();
        physim = ss->SS->getParentModule();
        BS = ss->SS->gate( "out" )->getNextGate()->getOwnerModule();
        actBS = BS->getIndex();
        nearestBS = actBS;

        x1 = atoi((ss->SS->getDisplayString()).getTagArg("p",0));
        y1 = atoi((ss->SS->getDisplayString()).getTagArg("p",1));
        x2 = atoi((BS->getDisplayString()).getTagArg("p",0));
        y2 = atoi((BS->getDisplayString()).getTagArg("p",1));

        minR = sqrt(pow(float(x1-x2),float(2.0))+pow(float(y1-y2),float(2.0)));

        for(int i=0; i < (int)physim->par("numBS"); i++) {
            cModule *targetBS = physim->getSubmodule("BS",i);
            x2 = atoi((targetBS->getDisplayString()).getTagArg("p",0));
            y2 = atoi((targetBS->getDisplayString()).getTagArg("p",1));
            double R = sqrt(pow(float(x1-x2),float(2.0))+pow(float(y1-y2),float(2.0)));
            if(R < minR) {
                minR = R;
                nearestBS = targetBS->getIndex();
            }
        }

        SLog(fsm, Notice) << "Currently associated with BS: " << actBS << ", the nearest BS :" << nearestBS << LogEnd;

        if(nearestBS == actBS) {
            return STATE_OPERATIONAL;
        } else {
            ss->hoInfo->wmax.nextBS = nearestBS;
        //============= Adam 10-09-2011 =====================
            if( ss->getParentModule()->getParentModule()->par("FMIP") ){
                ss->xmipv6 = xMIPv6Access().get();  // WiMAX MN
                ss->xmipv6->CreateAndSendRtSolPr( nearestBS );
                return STATE_WAIT_HANDOVER_ACK;
            }else{
                return STATE_SEND_MSHO_REQ;
            }
        //============= Adam, end  10-09-2011==================s
        }

    default:
	CASE_IGNORE(fsm, e);
    }
}

// send MSHO-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendMshoReq(Fsm *fsm)
{
    WMaxCtrlSS * ctrlSS = dynamic_cast<WMaxCtrlSS*>(fsm);

    //cModule *physim = ctrlSS->SS->getParentModule(); //unused variable (MiM)
    cModule *BS =ctrlSS->SS->gate( "out" )->getNextGate()->getOwnerModule();
    int actBS = BS->getIndex();
    int isMobile = ctrlSS->SS->par("wmaxIsMobile");

    if (isMobile == 1) // mobility model 1: time based handover
      ctrlSS->hoInfo->wmax.nextBS = (actBS+1)%(BS->size());
    else if (isMobile == 3) // mobility model 3: time based, random target
    {
	do {
	    ctrlSS->hoInfo->wmax.nextBS = uniform(0,BS->size());
	} while (ctrlSS->hoInfo->wmax.nextBS==actBS);
    }

    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    ss->hoStartTimestamp = simTime();
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));
    WMaxMsgMSHOREQ * mshoReq = new WMaxMsgMSHOREQ("MSHO-REQ");
    mshoReq->setName("MSHO-REQ");
    SLog(fsm, Notice) << "Staring handover to BS[" << ctrlSS->hoInfo->wmax.nextBS << "], sending MSHO-REQ message." << LogEnd;
    ss->sendMsg(mshoReq, "", "macOut", ssinfo->info.basicCid);

    // notify upper layer
    ss->mihNotify(MIH_EVENT_HANDOVER_START, ctrlSS->hoInfo->wmax.nextBS);
    return fsm->State();
}


void WMaxCtrlSS::mihNotify(MihInfo_t notifyType, int data)
{
    string str = "";
    cMessage * x = 0;
    switch (notifyType) {
      case MIH_EVENT_ENTRY_START:
        x = (cMessage*) new MihEvent_EntryStart();
        str = "Network Entry Start";
        break;
      case MIH_EVENT_ENTRY_END:
        x = (cMessage*) new MihEvent_EntryEnd();
        str = "Network Entry End";
        break;
      case MIH_EVENT_HANDOVER_START:
      {
	  MihEvent_HandoverStart * hoStart = new MihEvent_HandoverStart();
	hoStart->setTargetBS(data);
        x = (cMessage*) hoStart;
	char buf[16];
	sprintf(buf, "%d", data);
        str = "Handover Start (target BS[" + string(buf) + "]";
        NieaktywnoscL3StartTime = simTime();
        break;
      }
      case MIH_EVENT_HANDOVER_END:
        x = (cMessage*) new MihEvent_HandoverEnd();
        str = "Handover End";
        break;
      case MIH_EVENT_REENTRY_START:
        x = (cMessage*) new MihEvent_ReentryStart();
        str = "Network Reentry Start";
        break;
      case MIH_EVENT_REENTRY_END:
        x = (cMessage*) new MihEvent_ReentryEnd();
        str = "Network Reentry End";
        if( Handover == 1){
            if( this->getParentModule()->getParentModule()->par("FMIP") ){
                InterfaceEntry *ie = ift2 -> getInterface(1); //    WiMAX SS
                IPv6ND = IPv6NeighbourDiscoveryAccess().get();
                IPv6ND -> sendUnsolicitedNA(ie);  
                xmipv6 = xMIPv6Access().get();  // WiMAX MN
                IPv6Address temp =  ift2->getHandover_NCoA();
                xmipv6->initiateMIPv6Protocol( ie, temp );        
            }
            L3Gotowe = simTime();
            NieaktywnoscL3Duration.record(simTime() - NieaktywnoscL3StartTime );
        }
        Handover = 0;
        break;
    }

    ssInfo * info = dynamic_cast<ssInfo*>(SS->getSubmodule("ssInfo"));
    Log(Notice) << "Notifying upper layer: " << str << LogEnd;
    info->sendEvent(x);

}


// wait for BSHO-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForBshoRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    WMaxCtrlSS * ctrlSS = dynamic_cast<WMaxCtrlSS*>(fsm);
    switch (e) {
    case EVENT_BSHO_RSP_RECEIVED:
    {
//============= Adam 14-09-2011 ===================== nieuzywany parametr dhcp.remoteAutoconf
	// if (ctrlSS->hoInfo->dhcp.remoteAutoconf) {
	    // SLog(fsm, Info) << "BSHO-RSP received, waiting for L3 before sending HO-IND." << LogEnd;
	    // return STATE_WAIT_L3_DETACH_READY;
	// } else {
//============= Adam, end  14-09-2011==================    
	    SLog(fsm, Info) << "BSHO-RSP received, (not waiting for L3), sending HO-IND." << LogEnd;
	    return STATE_SEND_HO_IND;
	// }//============= Adam 14-09-2011 =====================
    }
    default:
	CASE_IGNORE(fsm, e);
    }
}

// wait for L3 detach readiness
FsmStateType WMaxCtrlSS::onEventState_WaitForL3Detach(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_L3_DETACH_READY:
	SLog(fsm, Info) << "L3 is ready to detach. Proceeding with handover." << LogEnd;
	return STATE_SEND_HO_IND;
    default:
	CASE_IGNORE(fsm, e);
    }
}

// sent HO-IND state
FsmStateType WMaxCtrlSS::onEnterState_SendHoInd(Fsm *fsm)
{
    WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm);
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ss->SS->getSubmodule("ssInfo"));
    WMaxMsgHOIND * hoInd = new WMaxMsgHOIND();
    hoInd->setName("HO-IND");
    ss->sendMsg(hoInd, "", "macOut", ssinfo->info.basicCid, 0.005); 
    /* HO-IND is delayed by 5ms. It is required to make sure that HO-IND is sent after
       Location update (in case if dhcp.remoteAutoconf=1 and mip.remoteLocationUpdate = 1) */
    ssinfo->info.basicCid = 0;
    ssinfo->stringUpdate();
    SLog(fsm, Notice) << "Sending HO-IND message." << LogEnd;

    // disable all service flows
    if (ss->hoInfo->wmax.hoOptim & WMAX_HO_OPTIM_FULL_STATE_TRANSFER) {
	// disable all flows
	for (list<WMaxFlowSS*>::iterator it=ss->serviceFlows.begin(); it!=ss->serviceFlows.end(); ++it) {
	    WMaxEvent_FlowDisable * dis = new WMaxEvent_FlowDisable();
	    (*it)->handleMessage(dis);
	} 
    } else {
	// delete flow objects
	for (list<WMaxFlowSS*>::iterator it=ss->serviceFlows.begin(); it!=ss->serviceFlows.end(); ++it) {
	    delete *it;
	} 
	// remove pointers to those objects
	ss->serviceFlows.clear();
    }
    
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onExitState_SendHoInd(Fsm * fsm)
{
    WMaxMacTerminateAllConns *terminateAll = new WMaxMacTerminateAllConns();
    fsm->send(terminateAll, "macOut");
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_SendHoInd(Fsm * fsm, FsmEventType e, cMessage *msg)
{
  //WMaxCtrlSS * ss = dynamic_cast<WMaxCtrlSS *>(fsm); //unused variable (MiM)
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
		<< simTime() << LogEnd;

    ss->mihNotify(MIH_EVENT_HANDOVER_END);

    ss->connectNextBS();
    ss->hoReentryTimestamp = simTime();

    ss->mihNotify(MIH_EVENT_REENTRY_START);
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

    SLog(fsm, Notice) << "Sending " << cdma->getName() << LogEnd;
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

    switch (e) {
      case EVENT_ENTRY_START:
        ss->neType = WMAX_CTRL_NETWORK_ENTRY_INITIAL;
        ss->mihNotify(MIH_EVENT_ENTRY_START);
        return STATE_WAIT_FOR_DLMAP;
      case EVENT_REENTRY_START:
        ss->neType = WMAX_CTRL_NETWORK_REENTRY;
        ss->hoReentryTimestamp = simTime();
        ss->mihNotify(MIH_EVENT_REENTRY_START);
        return STATE_WAIT_FOR_CDMA;
      default:
        CASE_IGNORE(fsm, e);
    }
}

void WMaxCtrlSS::connectBS(int x) {
    
    /* sanity checks */
//     cModule *SS = getParentModule();
    cModule *physim = SS->getParentModule();
    
    int maxBS = physim->par("numBS");
    if (x> maxBS) {
	opp_error("Unable to connect to BS[%d]: there are only %d BS(es)\n",
		  x, maxBS);
    }
    
    cModule * targetBS = physim->getSubmodule("BS",x);
    if (!targetBS) {
	opp_error("Unable to find BS[%d]\n", x);
    } 

    disconnect(); // disconnect from current BS (if any)

    /* connect to the next BS */
    cModule *radio = targetBS->getSubmodule("radio");
    if (!radio)
	opp_error("Unable to obtain radio submodule in BS[%d]\n",
		  x);

    WMaxRadio * wmaxRadio = check_and_cast<WMaxRadio*>(radio);

    wmaxRadio->connect(SS);
}

void WMaxCtrlSS::disconnect() {

//     cModule *SS = getParentModule();
    if (!SS->gate("out")->isConnected()) {
	// not connected
	return;
    }
    
    cModule *BS =SS->gate( "out" )->getNextGate()->getOwnerModule();
    cModule *radio = BS->getSubmodule("radio");
    if (!radio)
	opp_error("Unable to obtain radio submodule in BS[%d]\n",
		  BS->getIndex());
    WMaxRadio * wmaxRadio = check_and_cast<WMaxRadio*>(radio);
    wmaxRadio->disconnect(SS);
}

/** 
 * this method reconnects (creates Omnet module-module connections) to the next BS
 * 
 */
void WMaxCtrlSS::connectNextBS() {

    cModule *physim = SS->getParentModule();
    cModule *BS =SS->gate( "out" )->getNextGate()->getOwnerModule();
    int actBS = BS->getIndex();

    Log(Notice) << "Currently associated with BS[" << actBS << "], switching to BS[" << hoInfo->wmax.nextBS << "]." << LogEnd;
    cModule *BSnext = physim->getSubmodule("BS", hoInfo->wmax.nextBS);
    if (!BSnext)
        opp_error("Unable to find BS:%d\n", hoInfo->wmax.nextBS);

    disconnect(); // disconnect from current BS
    connectBS(hoInfo->wmax.nextBS); // connect to the next BS

    // after reconnecting to other BS, perform Reentry, not normal entry
    neType = WMAX_CTRL_NETWORK_REENTRY; 
}

void WMaxCtrlSS::finish()
{
    hoActionTimeData.record();
    
    TIMER_DEL(NetworkEntry);
    TIMER_DEL(Handover);
    TIMER_DEL(Reentry);


    for (list<WMaxFlowSS*>::iterator it=serviceFlows.begin(); it!=serviceFlows.end(); ++it)
    {
	delete *it;
    }
    serviceFlows.clear();
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
    BS = getParentModule()->getParentModule();
    cid = 1024;
    pkmSupport = true;
    Transactions.clear();
    ssList.clear();

    char buf[80];
    sprintf(buf, "%s%d", getFullName(), BS->getIndex());
    setName(buf);

    WATCH_LIST(ssList);
    WATCH_LIST(Transactions);
}

bool WMaxCtrlBS::pkmEnabled()
{
    return (pkmSupport>0);
}

double WMaxCtrlBS::sendMsg(cMessage * msg, const char * paramName, const char * gateName, int cid)
{
    char buf[80];
    sprintf(buf, "Min%s", paramName);
    double min = (double)par(buf);

    sprintf(buf, "Max%s", paramName);
    double max = (double)par(buf);

    double delay = uniform(min, max);
    
    Log(Debug) << "Sending " << msg->getName() << " in " << setiosflags(ios::fixed) << setprecision(3) << delay 
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
  return 0; // just to avoid compilation warning
}

void WMaxCtrlBS::deleteSS(uint16_t basicCid)
{
  list<SSInfo_t>::iterator ss;
  for (ss = ssList.begin(); ss!=ssList.end(); ss++) {
    if (basicCid == ss->basicCid) {
      ssList.erase(ss);
      return;
    }
  }
   
  opp_error("Unable to delete SS with cid=%d. SS not found.\n", basicCid);
}

void WMaxCtrlBS::handleMessage(cMessage *msg) 
{
    if (dynamic_cast<WMaxMsgRngReq*>(msg)) {
      int basicCid;
      if (GetCidFromMsg(msg) != WMAX_CID_RANGING )
        opp_error("Received RNG-REQ on non-ranging connection (cid=%d)", GetCidFromMsg(msg));

      WMaxMsgRngReq * req = dynamic_cast<WMaxMsgRngReq*>(msg);
      WMaxRngReq rngReq = req->getRngReq();
      WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp("RNG-RSP (initial rng)");
      
      // remember that this SS is being supported
      basicCid = getNextCid();
      SSInfo_t * ss  = new SSInfo_t();
      ss->macAddr  = rngReq.macAddr;
      ss->basicCid = basicCid;
      Log(Notice) << "New SS with mac=" << ss->getMac() << " has been added (basicCid=" 
		  << ss->basicCid << ")." << LogEnd;
      
      rsp->setOldCidArraySize(req->getSfCidArraySize());
      rsp->setNewCidArraySize(req->getSfCidArraySize());
      
      for (unsigned int i=0; i<req->getSfCidArraySize(); i++) {
	  int oldCid = 0, newCid = 0;
	  
	  WMaxMacAddConn *addConn = new WMaxMacAddConn();
	  
	  oldCid = req->getSfCid(i);
	  newCid = getNextCid();
	  
	  addConn->setMacAddr(ss->macAddr);
	  addConn->setName("Add connection");
	  addConn->setGateIndex(0);
            addConn->setCid( newCid );
            addConn->setQosArraySize(1);
            WMaxQos qos = req->getSfQos(i);
            addConn->setQos(0, qos);

	    addConn->setDstAddr(req->getMyIP());

            Log(Info) << "Creating new connection: oldCid=" << oldCid << ", newCid=" << newCid 
		      << ", qos[connType=" << qos.connType << ", msr=" << qos.msr << "], dstIP="
		      << req->getMyIP() << "." << LogEnd;
            send(addConn, "macOut");

            rsp->setOldCid(i, oldCid);
            rsp->setNewCid(i, newCid);

            ss->sf[ss->sfCnt].cid = newCid;
            ss->sfCnt++;
        }

        ssList.push_back(*ss);
	
        WMaxRngRsp rngRsp;
        rngRsp.ssMacAddr = rngReq.macAddr;
        rngRsp.basicCid = basicCid;

        rsp->setName("RNG-RSP");
        rsp->setRngRsp(rngRsp);
        rsp->setPurpose(WMAX_CDMA_PURPOSE_INITIAL_RNG);
        double x = sendMsg(rsp, "DelayRng", "macOut", GetCidFromMsg(msg) );

        WMaxMacAddMngmntConn *addConn = new WMaxMacAddMngmntConn();
        addConn->setCid(basicCid);
        Log(Notice) << "RNG-REQ (" << req->getSfCidArraySize() << " SFs updated) received, sending RNG-RSP in " 
		    << x << "secs (new basic connection created, cid=" << basicCid << ")." << LogEnd;
        send(addConn,"macOut");
        
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

    if (dynamic_cast<WMaxMsgMobScnReq*>(msg)) {
        getSS( GetCidFromMsg(msg), "MOB_SCN-REQ received");

        WMaxMsgMobScnRsp * mobScnRsp = new WMaxMsgMobScnRsp();
        mobScnRsp->setName("MOB_SCN-RSP");
        double x = sendMsg(mobScnRsp, "DelayScn", "macOut", GetCidFromMsg(msg));
        Log(Notice) << "MOB_SCN-REQ received, sending MOB_SCN-RSP in " << x << "secs." << LogEnd;
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
	delConn->setIsBasic(true);
        send(delConn, "macOut");
        
        for (int i=0;i <ss->sfCnt; i++) {
          x << " " << ss->sf[i].cid;
          WMaxEvent_DelConn * delConn = new WMaxEvent_DelConn();
          delConn->setCid(ss->sf[i].cid);
          send(delConn, "macOut");
        }

        Log(Notice) << x.str() << LogEnd;

        Log(Debug) << "Deleting SS " << ss->getMac() << LogEnd;
        deleteSS(ss->basicCid);

        delete msg;
        return;
    }

    if (dynamic_cast<WMaxMsgCDMA*>(msg)) {
        WMaxMsgCDMA * cdma = dynamic_cast<WMaxMsgCDMA*>(msg);
        Log(Notice) << msg->getFullName() << " (purpose=" << int(cdma->getPurpose()) << ") received";
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
        SSInfo_t * ss = getSS( GetCidFromMsg(msg), "DSA-ACK received");

        WMaxMsgDsaAck *dsaack = dynamic_cast<WMaxMsgDsaAck*>(msg);
        Log(Notice) << "DSA-ACK received (transID=" << dsaack->getTransactionID() << "),";
        
        list<Transaction>::iterator it;
        for (it = Transactions.begin(); it!=Transactions.end(); it++) {
          if (it->TransactionID == dsaack->getTransactionID()) {
            Log(Cont) << " transaction found, creating new connection (cid=" << it->cid << ")" << LogEnd;
            WMaxMacAddConn *addConn = new WMaxMacAddConn();
            addConn->setName("Add connection");
	    addConn->setMacAddr(ss->macAddr);
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

    Log(Debug) << "Received " << msg->getFullName() << " message." << LogEnd;
}


/********************************************************************************/
/*** WMax Service Flow Creation SS***********************************************/
/********************************************************************************/

Define_Module(WMaxFlowSS);

WMaxFlowSS::WMaxFlowSS(Fsm * fsm) {
    parentFsm = fsm;
    fsmInit();
    cid = 0;
    gate = 0;
    transactionID = 0; // it doesn't matter now, it will be set in WMaxFlowSS::onEventState_Start()
}

//MiM..........
WMaxFlowSS::WMaxFlowSS(){
  parentFsm = 0;
  cid=0;
  gate=0;
  transactionID=0;
}//...........MiM

//MiM
void WMaxFlowSS::setParentFsm(Fsm *parent){
  parentFsm = parent;
  fsmInit();
}//MiM

void WMaxFlowSS::fsmInit() {
    setName("WMaxFlowSS");
    statesEventsInit(WMaxFlowSS::STATE_NUM, WMaxFlowSS::EVENT_NUM, STATE_START);

    stateInit(STATE_START, "Start", onEventState_Start);
    stateInit(STATE_SEND_DSA_REQ, "Sending DSA-REQ", STATE_WAITING_DSX_RVD, onEnterState_SendDsaReq);
    stateInit(STATE_WAITING_DSX_RVD, "Waiting for DSX-RVD", onEventState_WaitingDsxRvd);
    stateInit(STATE_WAITING_DSA_RSP, "Waiting for DSA-RSP", onEventState_WaitingDsaRsp);
    stateInit(STATE_SEND_DSA_ACK, "Sending DSA-ACK", STATE_OPERATIONAL, onEnterState_SendDsaAck);
    stateInit(STATE_DISABLED, "Flow disabled", onEventState_Disabled);
    stateInit(STATE_OPERATIONAL, "Operational", onEventState_Operational);

    stateVerify();

    eventInit(EVENT_START, "Service flow creation started");
    eventInit(EVENT_DSX_RVD_RECEIVED, "Received DSX-RVD");
    eventInit(EVENT_DSA_RSP_RECEIVED, "Received DSA-RSP");
    eventInit(EVENT_FLOW_DISABLE, "Flow disable");
    eventInit(EVENT_FLOW_ENABLE, "Flow enable");

    eventVerify();
}

WMaxFlowSS::~WMaxFlowSS()
{
    parentFsm = 0;
}

void WMaxFlowSS::handleMessage(cMessage *msg) {
    if(dynamic_cast<WMaxEvent_FlowCreationStart*>(msg)) {
        WMaxEvent_FlowCreationStart* start = dynamic_cast<WMaxEvent_FlowCreationStart*>(msg);
        if (!start->getSkipDSA()) {
          // normal init (during network entry)
          onEvent(EVENT_START, msg); 
          delete msg;
        } else {
          // handover reentry (skip DSA procedure)
          onEvent(EVENT_FLOW_DISABLE, msg);
          delete msg;
        }
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

    if (dynamic_cast<WMaxEvent_FlowEnable*>(msg)) {
        onEvent(EVENT_FLOW_ENABLE, msg);
        Log(Debug) <<  "Enabling SF." << LogEnd;
        delete msg;
        return;
    }

    if (dynamic_cast<WMaxEvent_FlowDisable*>(msg)) {
        Log(Debug) <<  "Disabling SF." << LogEnd;
        onEvent(EVENT_FLOW_DISABLE, msg);
        delete msg;
        return;
    }
}

// Start state
FsmStateType WMaxFlowSS::onEventState_Start(Fsm * fsm, FsmEventType e, cMessage * msg){
    WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm);
    WMaxEvent_FlowCreationStart *flowcrstart = dynamic_cast<WMaxEvent_FlowCreationStart*>(msg);
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
    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ctrlSS->SS->getSubmodule("ssInfo"));
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

    ssInfo *ssinfo = dynamic_cast<ssInfo*>(ctrlSS->SS->getSubmodule("ssInfo"));
    SLog(fsm, Notice) << "Received DSA-RSP, sending DSA-ACK (transID=" << msg->getTransactionID() << ")." << LogEnd;
    ctrlSS->sendMsg(msg, "", "macOut", ssinfo->info.basicCid);

    WMaxMacAddConn *addConn = new WMaxMacAddConn();
    addConn->setName("Add connection");
    addConn->setMacAddr(ssinfo->info.macAddr);
    addConn->setGateIndex(flow->gate);
    addConn->setCid(flow->cid);
    addConn->setQosArraySize(1);
    addConn->setQos(0,flow->qos);
    ctrlSS->send(addConn, "macOut");

    ctrlSS->onEvent(WMaxCtrlSS::EVENT_SERVICE_FLOW_COMPLETE, 0);

    //============= Adam 13-09-2011 =====================
    if( ctrlSS->Handover == 1 && ctrlSS->getParentModule()->getParentModule()->par("FMIP")){
        InterfaceEntry &ie = *ctrlSS->ift2 -> getInterface(1); //    WiMAX SS
        ctrlSS->IPv6ND = IPv6NeighbourDiscoveryAccess().get();
        ctrlSS->IPv6ND -> sendUnsolicitedNA(&ie);  
        ctrlSS->xmipv6 = xMIPv6Access().get();  // WiMAX MN
        IPv6Address temp = ctrlSS->ift2->getHandover_NCoA();
        ctrlSS->xmipv6->initiateMIPv6Protocol( &ie, temp );        
    }
    ctrlSS->Handover = 0;
    //============= Adam, end  13-09-2011==================s    
    
    return fsm->State();
}

// Operational state
FsmStateType WMaxFlowSS::onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage * msg) {
    switch (e) {
    case EVENT_FLOW_DISABLE:
        /// @todo - disable this flow
        return STATE_DISABLED;
    default:
        CASE_IGNORE(fsm, e);
    }

    return fsm->State();
}

FsmStateType WMaxFlowSS::onEventState_Disabled(Fsm * fsm, FsmEventType e, cMessage *msg)
{
  //WMaxFlowSS *flow = dynamic_cast<WMaxFlowSS*>(fsm); //unused variable (MiM)

    switch (e) {
    case EVENT_FLOW_ENABLE:
        return STATE_OPERATIONAL;
    default:
        CASE_IGNORE(fsm, e);
    }
}


/** 
 * this method creates ne WMaxEvent_FlowCreationStart event, which is used
 * during service flow creation
 * 
 * @return 
 */
WMaxEvent_FlowCreationStart * WMaxCtrlSS::createNewFlowEvent()
{
    WMaxEvent_FlowCreationStart *msg = new WMaxEvent_FlowCreationStart();
    msg->setGateIndex(0);
    WMaxQos qos;

    int type = getParentModule()->getParentModule()->par("connType");
    switch (type)
    {
    case 2: qos.connType = WMAX_CONN_TYPE_BE; break;
    case 6: qos.connType = WMAX_CONN_TYPE_UGS; break;
    default: opp_error("Invalid connection type for %s: %d (allowed: 2=BE, 6=UGS)", getFullName(), type);
    }

    qos.msr = getParentModule()->getParentModule()->par("connMsr"); // 80000;
    msg->setQosArraySize(1);
    msg->setQos(0,qos);
    msg->setGateIndex(0);
    msg->setSkipDSA(0);

    return msg;
}
