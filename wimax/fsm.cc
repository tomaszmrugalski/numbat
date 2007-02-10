
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

void Fsm::stateInit(FsmStateType type, std::string name, onEventFunc onEvent, onEnterFunc onEnter, onExitFunc onExit)
{
    States[type].inited = true;
    States[type].type = type;
    States[type].name = name;
    States[type].onEvent = onEvent;
}

// transitive state
void Fsm::stateInit(FsmStateType type, std::string name, int targetState, onEnterFunc onEnter, onExitFunc onExit)
{
    States[type].inited = true;
    States[type].type = type;
    States[type].name = name;
    States[type].onEvent = 0;
}

void Fsm::eventInit(FsmEventType type, std::string name)
{
    Events[type].inited = true;
    Events[type].type   = type;
    Events[type].name   = name;

}

void Fsm::statesEventsInit(int statesCnt, int eventsCnt)
{
    int i;
    States.clear();
    Events.clear();

    for (i=0; i<statesCnt; i++) {
	FsmState * s = new FsmState();
	s->inited = false;
	States.push_back( *s );
    }
    for (i=0; i<eventsCnt; i++) {
	FsmEvent * e = new FsmEvent();
	e->inited = false;
	Events.push_back( *e );
    }

    StatesCnt = statesCnt;
    EventsCnt = eventsCnt;
}


bool Fsm::stateVerify() {
    bool error = false;
    for (int i=0; i<StatesCnt; i++) {
	if (!States[i].inited) {
	    ev << fullName() << ": State " << i << " has not been inited properly." << endl;
	    error = true;
	}
    }
    if (error)
	opp_error("%s: Not all states have been inited properly.", fullName() );
    return true;
}

bool Fsm::eventVerify() {
    bool error = false;
    for (int i=0; i<EventsCnt; i++) {
	if (!Events[i].inited) {
	    ev << fullName() << ": Event " << i << " has not been inited properly." << endl;
	    error = true;
	}
    }
    if (error)
	opp_error("%s: Not all events have been inited properly.", fullName() );

    return true;
}

void Fsm::onEvent(FsmEventType e, cMessage *msg)
{
    FsmStateType newState;
    if ( (e<0) || (e>StatesCnt) ) {
	opp_error("%s: Invalid event type %d specified (0..%d allowed)\n", fullName(), e, StatesCnt);
    }

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

