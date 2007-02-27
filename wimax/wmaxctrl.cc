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
    statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_WAIT_FOR_DLMAP);
    //statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_WAIT_FOR_CDMA);

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
    stateInit(STATE_OPERATIONAL,       "Operational", onEventState_Operational);
    stateInit(STATE_SEND_MSHO_REQ,     "Sending MSHO-REQ", STATE_WAIT_BSHO_RSP, onEnterState_SendMshoReq);
    stateInit(STATE_WAIT_BSHO_RSP,     "Waiting for BSHO-RSP", onEventState_WaitForBshoRsp);
    stateInit(STATE_SEND_HO_IND,       "Sending HO-IND", STATE_HANDOVER_COMPLETE, onEnterState_SendHoInd);
    stateInit(STATE_HANDOVER_COMPLETE, "Handover complete", onEventState_HandoverComplete);

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

    TIMER(NetworkEntry, 0.0, "Start Network entry");
    TIMER(Handover, 0.1, "Start handover");

    //TIMER_START(NetworkEntry);
    //TIMER_START(Handover);

    stringUpdate();
}

void WMaxCtrlSS::initialize() {
    fsmInit();
}


/** 
 * general dispatcher
 * 
 * @param msg 
 */
void WMaxCtrlSS::handleMessage(cMessage *msg) 
{
    if (dynamic_cast<WMaxMsgDlMap*>(msg)) { onEvent(EVENT_DLMAP, msg); return;  }
    // if (dynamic_cast<WMaxMsgDCD*>(dcd))   { onEvent(EVENT_DCD, msg);   return;  } ignore for now
    if (dynamic_cast<WMaxMsgUCD*>(msg))   { onEvent(EVENT_UCD, msg);   return;  }

    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	WMaxMsgUlMap * ulmap = dynamic_cast<WMaxMsgUlMap*>(msg);

	for (int i=0; i<ulmap->getIEArraySize(); i++) {
	    WMaxUlMapIE & ie = ulmap->getIE(i);
	    if ( (ie.uiuc == WMAX_ULMAP_UIUC_CDMA_BWR) ) {
		onEvent(EVENT_CDMA_CODE, msg);
		return;
	    }
	    
	}
    }
    if (dynamic_cast<WMaxMsgRngRsp*>(msg)) {
	onEvent(EVENT_RNG_RSP_RECEIVED, msg);
	return;
    }
    if (dynamic_cast<WMaxMsgSbcRsp*>(msg)) {
	onEvent(EVENT_SBC_RSP_RECEIVED, msg);
	return;
    }
    if (dynamic_cast<WMaxMsgRegRsp*>(msg)) {
	onEvent(EVENT_REG_RSP_RECEIVED, msg);
	return;
    }

    if (msg==TimerHandover) {
	onEvent(EVENT_REENTRY_START, msg);
	return;
    }

    if (dynamic_cast<WMaxMsgBSHORSP*>(msg)) {
	onEvent(EVENT_BSHO_RSP_RECEIVED, msg);
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
    switch (e) {
    case EVENT_RNG_RSP_RECEIVED:
	return STATE_SEND_SBC_REQ;
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
	return STATE_OPERATIONAL;
    default:
	CASE_IGNORE(e);
    }
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

FsmStateType WMaxCtrlSS::onEnterState_SendCdma(Fsm *fsm)
{
    Log << " Sending CDMA code" << endl;
    WMaxMsgCDMA * cdma = new WMaxMsgCDMA();
    cdma->setName("CDMA code");
    cdma->setPurpose(WMAX_CDMA_PURPOSE_HO_RNG);
    fsm->send(cdma, "macOut");
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_WaitForAnonRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    return fsm->State();
}

FsmStateType WMaxCtrlSS::onEventState_PowerDown(Fsm * fsm, FsmEventType e, cMessage *msg)
{
    switch (e) {
    case EVENT_REENTRY_START:
	return STATE_WAIT_FOR_CDMA;
    case EVENT_ENTRY_START:
	return STATE_WAIT_FOR_DLMAP;
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
    if (dynamic_cast<WMaxMsgRngReq*>(msg)) {
	ev << fullName() << ": RNG-REQ received, sending RNG-RSP." << endl;
	WMaxMsgRngRsp * rsp = new WMaxMsgRngRsp("RNG-RSP");
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



    ev << "Received " << msg->fullName() << " message." << endl;

    if (dynamic_cast<WMaxMsgHOIND*>(msg)) {
	ev << fullName() << ":HO-IND received." << endl;
	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgCDMA*>(msg)) {
	ev << fullName() << ":CDMA code received.";
	WMaxMsgCDMA * cdma = dynamic_cast<WMaxMsgCDMA*>(msg);
	switch (cdma->getPurpose()) {
	case WMAX_CDMA_PURPOSE_HO_RNG:
	{
	    ev << fullName() << ": CDMA code received, sending anonymous RNG-RSP." << endl;
	    break;
	}
	case WMAX_CDMA_PURPOSE_INITIAL_RNG:
	case WMAX_CDMA_PURPOSE_BWR:
	    /// @todo - Best effort traffic.
	    break;
	}
	
	delete msg;
	return;
    }
}

