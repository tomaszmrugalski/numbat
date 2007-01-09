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
#include "wmaxmsg_m.h"

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

class WMaxCtrl : public cSimpleModule
{
public:
    WMaxCtrl();
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

protected:

};

class WMaxCtrlSS : public WMaxCtrl
{
public:
    WMaxCtrlSS();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    /******************************************/
    /*** Finite State Machine *****************/
    /******************************************/
    cFSM fsm;
    typedef enum {
	INIT = 0,

	// notice: transitive and steady states are numbered separately

	// network entry
	SEND_CDMA         = FSM_Transient(1),    // send CDMA code
	WAIT_ANON_RNG_RSP = FSM_Steady(1),       // wait for anonymous RNG-RSP
	SEND_RNG_REQ      = FSM_Transient(2),    // send RNG-REQ
	WAIT_RNG_RSP      = FSM_Steady(2),       // wait for RNG-RSP
	SEND_SBC_REQ      = FSM_Transient(3),    // send SBC-REQ
	WAIT_SBC_RSP      = FSM_Steady(3),       // wait for SBC-RSP

	/// @todo: PKM (TEKs)
	SEND_REG_REQ      = FSM_Transient(4),    // send REG-REQ
	WAIT_REG_RSP      = FSM_Steady(4),       // wait for REG-RSP

	// service flow creation
	INITIATE_SVC_FLOW_CREATION = FSM_Transient(5), // initialize service flow creation (i.e. start new FSMs for each flow)
	WAIT_FOR_SVC_FLOW_COMPLETE = FSM_Steady(5),    // wait for service flow creation completion

	OPERATIONAL       = FSM_Steady(6),             // network entry completed, service flows created, normal operation

	// scanning
	/// @todo - implement scanning

	// handover
	SEND_MSHO_REQ     = FSM_Transient(6),    // send MSHO-REQ
	WAIT_BSHO_RSP     = FSM_Steady(7),       // wait for BSHO-RSP
	SEND_HO_IND       = FSM_Transient(7),    // send HO-IND
	HANDOVER_COMPLETE = FSM_Steady(8)        // handover complete
    } State;

    State OperationalOnEnter();
    State OperationalOnExit();
    State SendMshoReqOnEnter();
    State SendMshoReqOnExit();

    /******************************************/
    /*** Finite State Machine *****************/
    /******************************************/

    double TimerHandoverValue; // when should the handover procedure start?
    double TimerNetworkEntryValue;

    cMessage * TimerNetworkEntry;
    cMessage * TimerHandover;
};

class WMaxCtrlBS : public WMaxCtrl
{
public:
    WMaxCtrlBS();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
