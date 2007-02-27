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
    typedef enum {
	WMAX_CTRL_NETWORK_ENTRY_INITIAL,
	WMAX_CTRL_NETWORK_REENTRY
    } WMaxCtrlNetworkEntryType;

public:
    WMaxCtrlSS();

    void initialize();
    void handleMessage(cMessage *msg);

protected:
    void fsmInit();

    // --- STATES ---
    typedef enum {
	// 1. network entry phase
	STATE_WAIT_FOR_DLMAP,             // wait for DL-MAP
	STATE_WAIT_FOR_UCD,               // wait for UCD
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
	
	// network reentry
	STATE_WAIT_FOR_CDMA,              // wait for CDMA opportunity
	STATE_SEND_CDMA,                  // send CDMA code
	STATE_WAIT_ANON_RNG_RSP,          // wait for anonymous RNG-RSP

	STATE_POWER_DOWN,
	STATE_NUM
    } State;

    // wait for DL-MAP state
    static FsmStateType onEventState_WaitForDlmap(Fsm * fsm, FsmEventType e, cMessage *msg);

    // wait for UCD state
    static FsmStateType onEventState_WaitforUcd(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send CDMA code state
    static FsmStateType onEnterState_WaitAnonRngRsp(Fsm * fsm);
    static FsmStateType onExitState_WaitAnonRngRsp(Fsm * fsm);

    // send RNG-REQ state
    static FsmStateType onEnterState_SendRngReq(Fsm * fsm);

    // wait for RNG-RSP state
    static FsmStateType onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg);
    
    // send SBC-REQ state
    static FsmStateType onEnterState_SendSbcReq(Fsm * fsm);

    // wait for SBC-RSP state
    static FsmStateType onEventState_WaitForSbcRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send REG-REQ state
    static FsmStateType onEnterState_SendRegReq(Fsm * fsm);

    // wait for REG-RSP state
    static FsmStateType onEventState_WaitForRegRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // operational state
    static FsmStateType onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send MSHO-REQ state
    static FsmStateType onEnterState_SendMshoReq(Fsm *fsm);

    // wait for BSHO-RSP state
    static FsmStateType onEventState_WaitForBshoRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // sent HO-IND state
    static FsmStateType onEnterState_SendHoInd(Fsm *fsm);
    
    // handover complete state
    static FsmStateType onEventState_HandoverComplete(Fsm * fsm, FsmEventType e, cMessage *msg);

    // wait for CDMA opportunity state
    static FsmStateType onEventState_WaitForCdma(Fsm * fsm, FsmEventType e, cMessage *msg);

    static FsmStateType onEnterState_SendCdma(Fsm *fsm);

    // wait for anonymous RNG-RSP state
    static FsmStateType onEventState_WaitForAnonRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg);
    
    static FsmStateType onEventState_PowerDown(Fsm * fsm, FsmEventType e, cMessage *msg);

    // --- EVENTS ---
    typedef enum {
	EVENT_HANDOVER_START,
	EVENT_REENTRY_START,
	EVENT_ENTRY_START,
	EVENT_DLMAP,
	EVENT_UCD,
	EVENT_CDMA_CODE,
	EVENT_BSHO_RSP_RECEIVED,
	EVENT_HO_CDMA_CODE,
	EVENT_RNG_RSP_RECEIVED,
	EVENT_SBC_RSP_RECEIVED,
	EVENT_REG_RSP_RECEIVED,
	EVENT_NUM
    } Event;

    FsmStateType onEvent_CdmaCode(cMessage *msg);

    // --- TIMERS ---
    TIMER_DEF(Handover);
    TIMER_DEF(NetworkEntry);


    WMaxCtrlNetworkEntryType neType;
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
