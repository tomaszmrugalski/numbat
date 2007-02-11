/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2006-12-29 01:50:38+0100
 * 
 * @brief  WMax MAC control layer
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>
#include <vector>
#include "wmaxmsg_m.h"
#include "fsm.h"

using namespace std;

#ifndef WMAXCTRL_H
#define WMAXCTRL_H

/**************************************************************/
/*** WIMAX CONSTANTS ******************************************/
/**************************************************************/

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class WMaxCtrlSS : public Fsm
{
public:
    WMaxCtrlSS();

    void initialize();
    void handleMessage(cMessage *msg);

protected:
    void fsmInit();

    // --- STATES ---
    typedef enum {
	// 1. network entry phase
	STATE_WAIT_FOR_CDMA,
	STATE_SEND_CDMA,            // send CDMA code
	STATE_WAIT_ANON_RNG_RSP,    // wait for anonymous RNG-RSP
	STATE_SEND_RNG_REQ,               // send RNG-REQ
	STATE_WAIT_RNG_RSP,               // wait for RNG-RSP
	STATE_SEND_SBC_REQ,               // send SBC-REQ
	STATE_WAIT_SBC_RSP,               // wait for SBC-RSP
	/// @todo: implement PKM (TEKs) support
	STATE_SEND_REG_REQ,               // send REG-REQ
	STATE_WAIT_REG_RSP,               // wait for REG-RSP

	// 2. service flow creation phase
	/// @todo - implement service flow creation
	// STATE_INITIATE_SVC_FLOW_CREATION, // initialize service flow creation (i.e. start new FSMs for each flow)
	// STATE_WAIT_FOR_SVC_FLOW_COMPLETE, // wait for service flow creation completion

	STATE_OPERATIONAL,                // network entry completed, service flows created, normal operation

	/// @todo - implement neighbor advertisements support

	/// @todo - implement scanning

	// handover
	STATE_SEND_MSHO_REQ,              // send MSHO-REQ
	STATE_WAIT_BSHO_RSP,              // wait for BSHO-RSP
	STATE_SEND_HO_IND,                // send HO-IND
	STATE_HANDOVER_COMPLETE,          // handover complete
	
	STATE_NUM
    } State;

    // wait for CDMA opportunity state
    static FsmStateType onEventState_WaitForCdma(Fsm * fsm, FsmEventType s, cMessage *msg);

    // send CDMA code state
    static FsmStateType onEnterState_WaitAnonRngRsp(Fsm * fsm);
    static FsmStateType onExitState_WaitAnonRngRsp(Fsm * fsm);

    // wait for anonymous RNG-RSP state
    static FsmStateType onEventState_WaitForAnonRngRsp(Fsm * fsm, FsmEventType s, cMessage *msg);

    // send RNG-REQ state
    static FsmStateType onEnterState_SendRngReq(Fsm * fsm);

    // wait for RNG-RSP state
    static FsmStateType onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType s, cMessage *msg);
    
    // send SBC-REQ state
    static FsmStateType onEnterState_SendSbcReq(Fsm * fsm);

    // wait for SBC-RSP state
    static FsmStateType onEventState_WaitForSbcRsp(Fsm * fsm, FsmEventType s, cMessage *msg);

    // send REG-REQ state
    static FsmStateType onEnterState_SendRegReq(Fsm * fsm);

    // wait for REG-RSP state
    static FsmStateType onEventState_WaitForRegRsp(Fsm * fsm, FsmEventType s, cMessage *msg);

    // operational state
    static FsmStateType onEventState_Operational(Fsm * fsm, FsmEventType s, cMessage *msg);

    // send MSHO-REQ state
    static FsmStateType onEnterState_SendMshoReq(Fsm *fsm);

    // wait for BSHO-RSP state
    static FsmStateType onEventState_WaitForBshoRsp(Fsm * fsm, FsmEventType s, cMessage *msg);

    // sent HO-IND state
    static FsmStateType onEnterState_SendHoInd(Fsm *fsm);
    
    // handover complete state
    static FsmStateType onEventState_HandoverComplete(Fsm * fsm, FsmEventType s, cMessage *msg);

    // --- EVENTS ---
    typedef enum {
	EVENT_CDMA_CODE,
	EVENT_HANDOVER_START,
	EVENT_BSHO_RSP_RECEIVED,
	EVENT_NUM
    } Event;

    FsmStateType onEvent_CdmaCode(cMessage *msg);

    // --- TIMERS ---
    TIMER_DEF(Handover);
    TIMER_DEF(NetworkEntry);
};

class WMaxCtrlBS : public Fsm
{
public:
    WMaxCtrlBS();
protected:
    void fsmInit();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};


#endif
