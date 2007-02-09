
#include <iostream>
#include <sstream>
#include "fsm.h"

/********************************************************************************/
/*** Generic FSM class **********************************************************/
/********************************************************************************/

std::string FsmEvent::fullName() {
    std::ostringstream x;
    x << type;
    return std::string(name) 
	+ "(" 
	+ x.str() 
	+ ")";
}


void Fsm::stateInit(int type, std::string name, onEventFunc func)
{
    States[type].inited = true;
    States[type].type = type;
    States[type].name = name;
    States[type].onEvent = func;
}

void Fsm::statesEventsInit(int statesCnt, int eventsCnt)
{
    States.clear();
    Events.clear();
    States.reserve(statesCnt);
    Events.reserve(eventsCnt);

    StatesCnt = statesCnt;
    EventsCnt = eventsCnt;
}

void WMaxCtrlSSFsm::initialize() {
    statesEventsInit(WMaxCtrlSSFsm::STATE_NUM, WMaxCtrlSSFsm::EVENT_NUM);

    // state init
    stateInit(STATE_WAIT_FOR_CDMA, "Waiting for CDMA opportunity", onEventState_WaitForCdma);
    stateInit(STATE_SEND_CDMA,     "Send CDMA code", STATE_WAIT_ANON_RNG_RSP,
 	      onEnterState_WaitAnonRngRsp, onExitState_WaitAnonRngRsp);
    stateInit(STATE_WAIT_ANON_RNG_RSP, "Waiting for anonymous RNG-RSP", onEventState_WaitForAnonRngRsp);
    stateVerify();

    // event init
    eventInit(EVENT_CDMA_CODE, "CDMA code received");
    eventVerify();
}


bool Fsm::stateVerify() {

    for (int i=0; i<StatesCnt; i++) {
	if (!States[i].inited) {
	    ev << fullName() << ": State " << i << " has not been inited properly." << endl;
	    /// @todo: throw exception here
	}
    }
}

bool Fsm::eventVerify() {

    return true;
}

void Fsm::onEvent(FsmEventType e, cMessage *msg)
{
    FsmStateType newState;
    newState = States[CurrentState].onEvent(this, e, msg);

    if (newState != CurrentState) {
	// state transition
	if (States[CurrentState].onExit)
	    States[CurrentState].onExit(this);
	CurrentState = newState;

	if (States[CurrentState].onEnter)
	    States[CurrentState].onEnter(this);
    }
}

/********************************************************************************/
/*** CtrlSS FSM implementation **************************************************/
/********************************************************************************/

void WMaxCtrlSSFsm::handleMessage(cMessage *msg) 
{

    if (1) {
	onEvent(EVENT_CDMA_CODE, msg);
	return;
    }
}

FsmStateType WMaxCtrlSSFsm::onEventState_WaitForCdma(Fsm * fsm, FsmEventType e, cMessage *msg) 
{
    WMaxCtrlSSFsm * f = dynamic_cast<WMaxCtrlSSFsm*>(fsm);

    switch (e) {
	case EVENT_CDMA_CODE:
	return f->onEvent_CdmaCode(msg);
    default:
	std::cout << f->fullName() << ": event " 
		  << f->Events[e].fullName() << " ignored in state " 
		  << f->CurrentState << endl;
	return f->CurrentState;
	int x;
    }
}

FsmStateType WMaxCtrlSSFsm::onEvent_CdmaCode(cMessage *msg)
{
    return WMaxCtrlSSFsm::STATE_SEND_CDMA;
}
