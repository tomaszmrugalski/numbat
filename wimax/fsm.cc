
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

std::string FsmState::fullName() {
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
    States[type].onEnter = 0;
    States[type].onExit  = 0;
    States[type].transitive = false;
}

void Fsm::stateInit(FsmStateType type, std::string name, onEventFunc onEvent, onEnterFunc onEnter, onExitFunc onExit)
{
    States[type].inited = true;
    States[type].type = type;
    States[type].name = name;
    States[type].onEvent = onEvent;
    States[type].onEnter = onEnter;
    States[type].onExit  = onExit;
    States[type].transitive = false;
}

// transitive state
void Fsm::stateInit(FsmStateType type, std::string name, int targetState, onEnterFunc onEnter)
{
    States[type].inited = true;
    States[type].type = type;
    States[type].name = name;
    States[type].onEvent = 0;
    States[type].onEnter = onEnter;
    States[type].onExit  = 0;
    States[type].transitive = true;
    States[type].transitiveTo = targetState;
}

void Fsm::eventInit(FsmEventType type, std::string name)
{
    Events[type].inited = true;
    Events[type].type   = type;
    Events[type].name   = name;

}

void Fsm::statesEventsInit(int statesCnt, int eventsCnt, FsmStateType state)
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

    ev << fullName() << ": " << statesCnt << " state(s), " << eventsCnt << " event(s) inited." << endl;
    StatesCnt = statesCnt;
    EventsCnt = eventsCnt;

    CurrentState = state;
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
    if ( (e<0) || (e>StatesCnt) ) {
	opp_error("%s: Invalid event type %d specified (0..%d allowed).\n", fullName(), e, StatesCnt);
    }
    FsmStateType newState;

    ev << fullName() << ": Event " << Events[e].fullName() << " received." << endl;

    newState = States[CurrentState].onEvent(this, e, msg);
    if (newState>StatesCnt) {
	opp_error("%s: Invalid state (%d) returned duing %s event processing in state %s.", fullName(),
		  newState, Events[e].fullName().c_str(), States[CurrentState].fullName().c_str() );
    }

    if (newState != CurrentState) {
	ev << fullName() << ": State change: " << States[CurrentState].fullName() << "->" << States[newState].fullName() 
	   << ", triggered by the " << Events[e].fullName().c_str() << " event." << endl;
	stateSet(newState);
    }
}

void Fsm::stateSet(FsmStateType newState)
{
    FsmState *from;
    FsmState *to;
    int transitionsCnt = 0; // how many state changes? (by default, after transition, it should be set to 1,
                            // unless there were some transitive states)

    // skip changes to current state
    if (newState==State())
	return;

    // state transition

    do {
	from = &States[State()];
	to   = &States[newState];

	if (from->onExit)
	    from->onExit(this);
	
	CurrentState = newState;

	char buf[80];
	sprintf(buf, "state:%s", to->fullName().c_str() );
	if (ev.isGUI()) 
	    displayString().setTagArg("t",0,buf);

	if (to->onEnter)
	    to->onEnter(this);

	if (to->transitive) {
	    newState = to->transitiveTo;
	    ev << fullName() << ": State change: " << States[State()].fullName() << "->" << States[newState].fullName() 
	       << ", because " << States[State()].fullName() << " is transitive." << endl;
	}
	transitionsCnt++;
	if (transitionsCnt > FSM_MAX_TRANSITIONS)
	    opp_error("%s: probably state transitions loop detected: %d transitions occured without stationary state.\n", fullName(), transitionsCnt);
    } while (to->transitive);
}
