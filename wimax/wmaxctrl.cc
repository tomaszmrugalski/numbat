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

#define TIMER(name, time, descr)  \
    Timer##name##Value = time;			\
    Timer##name        = new cMessage(descr);

#define TIMER_START(name) \
    scheduleAt(simTime() + Timer##name##Value, Timer##name);

#define TIMER_STOP(name) \
    if (Timer##name ->isScheduled()) \
        cancelEvent(Timer##name);

/********************************************************************************/
/*** WMax Ctrl SS ****************************************************************/
/********************************************************************************/
WMaxCtrl::WMaxCtrl()
{

}

void WMaxCtrl::initialize()
{

}



/********************************************************************************/
/*** WMax Ctrl SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxCtrlSS);

WMaxCtrlSS::WMaxCtrlSS()
{

}

void WMaxCtrlSS::initialize()
{
    TIMER(NetworkEntry, 0.0, "Start Network entry");
    TIMER(Handover, 0.1, "Start handover");

    TIMER_START(NetworkEntry);
    TIMER_STOP(Handover);
}

void WMaxCtrlSS::handleMessage(cMessage *msg) 
{

    FSM_Switch(fsm)
    {
    case FSM_Exit(INIT):
	/// @todo - network entry should be performed, not just jump to operational state
	FSM_Goto(fsm, OPERATIONAL);
    break;
    case FSM_Enter(OPERATIONAL):
    {
        ev << "Network entry and service flows creation completed. SS is operational." << endl;
        //scheduleAt(simTime()+TimerHandoverValue, TimerHandover);
	break;
    }
    default: 
    {

    }
  }
}

/********************************************************************************/
/*** WMax Ctrl BS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxCtrlBS);

WMaxCtrlBS::WMaxCtrlBS()
{

}

void WMaxCtrlBS::initialize()
{

}

void WMaxCtrlBS::handleMessage(cMessage *msg) 
{

}

