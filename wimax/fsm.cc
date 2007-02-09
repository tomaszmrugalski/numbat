
#include <iostream>
#include "fsm.h"

/********************************************************************************/
/*** Generic FSM class **********************************************************/
/********************************************************************************/

void Fsm::stateInit(int type, std::string name, onEventFunc func)
{
    FsmState * s = new FsmState(type, name, func);
    //States[type]
}

void WMaxCtrlSsFsm::fsmInit() {

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

#if 0
    for (int i=0; i<STATE_NUM; i++) {
	if (!StateArray[i].onEvent) {
	    cout << gullName() << ": State " << state << " has not been inited properly." << endl;
	}

    }
#endif

}

bool Fsm::eventVerify() {

    return true;
}

#if 0
void WMaxCtrlSS::handleMessage(cMessage *msg) 
{

    if (...) {
	fsm->onEvent(EVENT_CDMA_CODE, msg);
	return;
    }
}
#endif

void Fsm::onEvent(FsmEvent s, cMessage *msg)
{
    FsmState *tmp;
    FsmStateType old;
    tmp = &States[State->type].onEvent(this, s, msg);

    if (tmp->type != State->type) {
	// state transition
	if (States[State->type].onExit)
	    States[State->type].onExit(this, tmp->type);
	old   = State->type;
	State = &States[tmp->type];

	if (States[State->type].onEnter)
	    States[State->type].onEnter(this, old);
    }
}

/********************************************************************************/
/*** CtrlSS FSM implementation **************************************************/
/********************************************************************************/


FsmState &WMaxCtrlSsFsm::onEventState_WaitForCdma(Fsm * fsm, FsmEvent s, cMessage *msg) 
{
    WMaxCtrlSsFsm * f = dynamic_cast<WMaxCtrlSsFsm*>(fsm);

    switch (s.type) {
	case EVENT_CDMA_CODE:
	return f->onEvent_CdmaCode(msg);
    default:
	//cout << getName() << ": event " << s << " ignored in state " << State << endl;
	//return State;
	int x;
    }
}

FsmState& WMaxCtrlSsFsm::onEvent_CdmaCode(cMessage *msg)
{
    return States[STATE_SEND_CDMA];
}
