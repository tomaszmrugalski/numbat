/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2006-12-29 01:50:38+0100
 * 
 * @brief  WMax MAC control layer
 * @licence GNU GPLv2
 * 
 */

#define FSM_DEBUG
#include <omnetpp.h>
#include <vector>
#include "wmaxctrl.h"
#include "wmaxmsg_m.h"

/********************************************************************************/
/*** WMax Ctrl SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxCtrlSS);

WMaxCtrlSS::WMaxCtrlSS()
{

}

void WMaxCtrlSS::fsmInit() {
    /// @todo - SS should perform network entry procedure (i.e. start in WAIT_FOR_CDMA state)
    statesEventsInit(WMaxCtrlSS::STATE_NUM, WMaxCtrlSS::EVENT_NUM, STATE_OPERATIONAL);

    // state init
    std::string x = "Waiting for CDMA opportunity";
    stateInit(STATE_WAIT_FOR_CDMA,     "Waiting for CDMA opportunity", onEventState_WaitForCdma);
    stateInit(STATE_SEND_CDMA,         "Send CDMA code", STATE_WAIT_ANON_RNG_RSP, onEnterState_WaitAnonRngRsp, onExitState_WaitAnonRngRsp);
    stateInit(STATE_WAIT_ANON_RNG_RSP, "Waiting for anonymous RNG-RSP", onEventState_WaitForAnonRngRsp);
    stateInit(STATE_SEND_RNG_REQ,      "Sending RNG-REQ", STATE_WAIT_RNG_RSP, onEnterState_SendRngReq, 0);
    stateInit(STATE_WAIT_RNG_RSP,      "Waiting for RNG-RSP", onEventState_WaitForRngRsp);
    stateInit(STATE_SEND_SBC_REQ,      "Sending SBC-REQ", STATE_WAIT_SBC_RSP, onEnterState_SendSbcReq, 0);
    stateInit(STATE_WAIT_SBC_RSP,      "Waiting for SBC-RSP", onEventState_WaitForSbcRsp);
    stateInit(STATE_SEND_REG_REQ,      "Sending REG-REQ", STATE_WAIT_REG_RSP, onEnterState_SendRegReq, 0);
    stateInit(STATE_WAIT_REG_RSP,      "Waiting for REG-RSP", onEventState_WaitForRegRsp);
    stateInit(STATE_OPERATIONAL,       "Operational", onEventState_Operational);
    stateInit(STATE_SEND_MSHO_REQ,     "Sending MSHO-REQ", STATE_WAIT_BSHO_RSP, onEnterState_SendMshoReq, 0);
    stateInit(STATE_WAIT_BSHO_RSP,     "Waiting for BSHO-RSP", onEventState_WaitForBshoRsp);
    stateInit(STATE_SEND_HO_IND,       "Sending HO-IND", STATE_HANDOVER_COMPLETE, onEnterState_SendHoInd, 0);
    stateInit(STATE_HANDOVER_COMPLETE, "Handover complete", onEventState_HandoverComplete);

    stateVerify();

    // event init
    eventInit(EVENT_CDMA_CODE, "CDMA code received");
    eventInit(EVENT_HANDOVER_START, "Begin handover procedure");
    eventInit(EVENT_BSHO_RSP_RECEIVED, "BSHO-RSP received");
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
    //IF_TIMER(name, EVENT_TIMEOUT);
    if (msg==TimerHandover) {
	onEvent(EVENT_HANDOVER_START, msg);
	return;
    }

    if (dynamic_cast<WMaxMsgBSHORSP*>(msg)) {
	onEvent(EVENT_BSHO_RSP_RECEIVED, msg);
	return;
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


FsmStateType WMaxCtrlSS::onExitState_WaitAnonRngRsp(Fsm* fsm)
{
    return fsm->State();
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
    ev << fsm->fullName() << "Sending MSHO-REQ message." << endl;
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
    return fsm->State();
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
FsmStateType WMaxCtrlSS::onEventState_HandoverComplete(Fsm * fsm, FsmEventType s, cMessage *msg)
{
    return fsm->State();
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
	ev << fullName() << ": MSHO-REQ received, sending BSHO-RSP." << endl;
	WMaxMsgBSHORSP * bshoRsp = new WMaxMsgBSHORSP();
	bshoRsp->setName("BSHO-RSP");
	send(bshoRsp, "macOut");
	delete msg;
	return;
    }
    if (dynamic_cast<WMaxMsgHOIND*>(msg)) {
	ev << fullName() << ": HO-IND received." << endl;
	delete msg;
	return;
    }
}

