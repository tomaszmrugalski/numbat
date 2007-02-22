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
    statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_POWER_DOWN);

    // state init
    std::string x = "Waiting for CDMA opportunity";
    stateInit(STATE_WAIT_FOR_CDMA,     "Waiting for CDMA opportunity", onEventState_WaitForCdma);
    stateInit(STATE_SEND_CDMA,         "Send CDMA code", STATE_WAIT_ANON_RNG_RSP, onEnterState_WaitAnonRngRsp);
    stateInit(STATE_WAIT_ANON_RNG_RSP, "Waiting for anonymous RNG-RSP", onEventState_WaitForAnonRngRsp);
    stateInit(STATE_SEND_RNG_REQ,      "Sending RNG-REQ", STATE_WAIT_RNG_RSP, onEnterState_SendRngReq);
    stateInit(STATE_WAIT_RNG_RSP,      "Waiting for RNG-RSP", onEventState_WaitForRngRsp);
    stateInit(STATE_SEND_SBC_REQ,      "Sending SBC-REQ", STATE_WAIT_SBC_RSP, onEnterState_SendSbcReq);
    stateInit(STATE_WAIT_SBC_RSP,      "Waiting for SBC-RSP", onEventState_WaitForSbcRsp);
    stateInit(STATE_SEND_REG_REQ,      "Sending REG-REQ", STATE_WAIT_REG_RSP, onEnterState_SendRegReq);
    stateInit(STATE_WAIT_REG_RSP,      "Waiting for REG-RSP", onEventState_WaitForRegRsp);
    stateInit(STATE_OPERATIONAL,       "Operational", onEventState_Operational);
    stateInit(STATE_SEND_MSHO_REQ,     "Sending MSHO-REQ", STATE_WAIT_BSHO_RSP, onEnterState_SendMshoReq);
    stateInit(STATE_WAIT_BSHO_RSP,     "Waiting for BSHO-RSP", onEventState_WaitForBshoRsp);
    stateInit(STATE_SEND_HO_IND,       "Sending HO-IND", STATE_HANDOVER_COMPLETE, onEnterState_SendHoInd);
    stateInit(STATE_HANDOVER_COMPLETE, "Handover complete", onEventState_HandoverComplete);

    stateInit(STATE_HO_WAIT_FOR_CDMA,   "Wait for handover CDMA opportunity", onEventState_hoWaitForCdma);
    stateInit(STATE_HO_SEND_CDMA,       "Sending HO CDMA code", STATE_HO_WAIT_FOR_ANON_RNG_RSP, onEnterState_hoSendCdma);
    stateInit(STATE_HO_WAIT_FOR_ANON_RNG_RSP, "Wait for anonymous RNG-RSP", onEventState_hoWaitForAnonRngRsp);
    stateInit(STATE_HO_SEND_RNG_REQ,    "Sending (handover) RNG-REQ", STATE_HO_WAIT_FOR_RNG_RSP, onEnterState_hoSendRngReq);
    stateInit(STATE_HO_WAIT_FOR_RNG_RSP,"Wait for (handover) RNG-RSP", onEventState_hoWaitForRngRsp);

    stateInit(STATE_POWER_DOWN,         "Power down", onEventState_PowerDown);

    stateVerify();

    // event init
    eventInit(EVENT_HANDOVER_START, "Begin handover procedure");
    eventInit(EVENT_REENTRY_START, "Begin reentry procedure");

    eventInit(EVENT_CDMA_CODE, "(Initial ranging) CDMA opportunity received");
    eventInit(EVENT_BSHO_RSP_RECEIVED, "BSHO-RSP received");
    eventInit(EVENT_HO_CDMA_CODE, "(Handover ranging) CDMA opportunity received");
    eventInit(EVENT_RNG_RSP_RECEIVED, "RNG-RSP received");
    eventVerify();

    TIMER(NetworkEntry, 0.0, "Start Network entry");
    TIMER(Handover, 0.1, "Start handover");

    //TIMER_START(NetworkEntry);
    TIMER_START(Handover);

}

void WMaxCtrlSS::initialize() {
    fsmInit();
}

void WMaxCtrlSS::handleMessage(cMessage *msg) 
{
    if (msg==TimerHandover) {
	onEvent(EVENT_REENTRY_START, msg);
	return;
    }

    if (dynamic_cast<WMaxMsgBSHORSP*>(msg)) {
	onEvent(EVENT_BSHO_RSP_RECEIVED, msg);
	return;
    }

    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	WMaxMsgUlMap* ulmap = dynamic_cast<WMaxMsgUlMap*>(msg);
	int i;
	for (i=0; i<ulmap->getIEArraySize(); i++) {
	    WMaxUlMapIE & ie = ulmap->getIE(i);
	    if ( (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_BWR) &&
		 (ie.cdmaIE.rangingMethod == WMAX_RANGING_METHOD_INITIAL) )
		onEvent(EVENT_CDMA_CODE, msg);

	    /// @todo - fix this CDMA code transmission
	    if ( (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_BWR) &&
		 (ie.cdmaIE.rangingMethod == WMAX_RANGING_METHOD_BWR) )
		onEvent(EVENT_HO_CDMA_CODE, msg);
	}

	ev << "UL-MAP received." << endl;
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

FsmStateType WMaxCtrlSS::onEnterState_WaitAnonRngRsp(Fsm* fsm)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_WaitForAnonRngRsp(Fsm* fsm, FsmEventType e , cMessage* msg)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEvent_CdmaCode(cMessage *msg)
{
    return WMaxCtrlSS::STATE_SEND_CDMA;
}

FsmStateType WMaxCtrlSS::onEnterState_SendRngReq(Fsm * fsm)
{
    return fsm->State();
}

// wait for RNG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType s, cMessage *msg)
{
    return fsm->State();
}

// send SBC-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendSbcReq(Fsm * fsm)
{
    return fsm->State();
}

// wait for SBC-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForSbcRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    return fsm->State();
}

// send REG-REQ state
FsmStateType WMaxCtrlSS::onEnterState_SendRegReq(Fsm * fsm)
{
    return fsm->State();
}

// wait for REG-RSP state
FsmStateType WMaxCtrlSS::onEventState_WaitForRegRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
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
FsmStateType WMaxCtrlSS::onEventState_HandoverComplete(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_hoWaitForCdma(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_HO_CDMA_CODE:
	return STATE_HO_SEND_CDMA;
    default:
	CASE_IGNORE(e);
    }
}

FsmStateType WMaxCtrlSS::onEnterState_hoSendCdma(Fsm *fsm)
{
    Log << "Sending CDMA code" << endl;
    WMaxMsgCDMA * cdma = new WMaxMsgCDMA();
    cdma->setName("CDMA code");
    fsm->send(cdma, "macOut");
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_hoWaitForAnonRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEnterState_hoSendRngReq(Fsm *fsm)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_hoWaitForRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_PowerDown(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_REENTRY_START:
	return STATE_HO_WAIT_FOR_CDMA;
    default:
	CASE_IGNORE(e);
    }
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
	ev << fullName() << ":CDMA code received." << endl;
	delete msg;
	return;
    }
}

