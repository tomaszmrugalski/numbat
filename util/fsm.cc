
#include <iostream>
#include <sstream>
#include "fsm.h"
#include "logger.h"

/********************************************************************************/
/*** Generic FSM class **********************************************************/
/********************************************************************************/
Fsm::Fsm()
{
}

std::string FsmEvent::getFullName() {
    std::ostringstream x;
    x << type;
    return std::string(name) 
	+ "(" 
	+ x.str() 
	+ ")";
}

std::string FsmState::getFullName() {
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

    StatesCnt = statesCnt;
    EventsCnt = eventsCnt;

    CurrentState = state;
}


bool Fsm::stateVerify() {
    bool error = false;
    for (int i=0; i<StatesCnt; i++) {
	if (!States[i].inited) {
	    Log(Error) << "State " << i << " has not been inited properly." << LogEnd;
	    error = true;
	}
    }
    if (error)
	opp_error("%s: Not all states have been inited properly.", getFullName() );
    return true;
}

bool Fsm::eventVerify() {
    bool error = false;
    for (int i=0; i<EventsCnt; i++) {
	if (!Events[i].inited) {
	    Log(Error) << "Event " << i << " has not been inited properly." << LogEnd;
	    error = true;
	}
    }
    if (error)
	opp_error("%s: Not all events have been inited properly.", getFullName() );

    return true;
}

void Fsm::onEvent(FsmEventType e, cMessage *msg)
{
    if ( (e<0) || (e>EventsCnt) ) {
	opp_error("%s: Invalid event type %d specified (0..%d allowed).\n", getFullName(), e, StatesCnt);
    }
    FsmStateType newState;

    Log(Debug) << "Event " << Events[e].getFullName() << " received." << LogEnd;

    newState = States[CurrentState].onEvent(this, e, msg);
    if ((unsigned)newState>(unsigned)StatesCnt) {
	opp_error("%s: Invalid state (%d) returned duing %s event processing in state %s.", getFullName(),
		  newState, Events[e].getFullName().c_str(), States[CurrentState].getFullName().c_str() );
    }

    if (newState != CurrentState) {
      Log(Debug) << "State change: " << States[CurrentState].getFullName() << "->" << States[newState].getFullName() << ", triggered by the " << Events[e].getFullName() << " event." << LogEnd;
      stateSet(newState);
    }
}

void Fsm::stateSet(FsmStateType newState)
{
    FsmState *from;
    FsmState *to;
    FsmStateType tmp;
    int transitionsCnt = 0; // how many state changes? (by default, after transition, it should be set to 1,
                            // unless there were some transitive states)

    // skip changes to current state
    if (newState==State())
	return;

    // state transition
    bool override;

    do {
	override = false;
	if (transitionsCnt > FSM_MAX_TRANSITIONS)
	    opp_error("%s: probably state transitions loop detected: %d transitions occured without stationary state.\n", 
		      getFullName(), transitionsCnt);

	from = &States[State()];
	to   = &States[newState];

	if (from->onExit)
	    from->onExit(this);
	
	CurrentState = newState;
	if(!parametersFinalized())
	  finalizeParameters(); //MiM
	stringUpdate();

	if (to->onEnter) {
	    tmp = to->onEnter(this);

	    if ( (tmp<0) || (tmp>StatesCnt) ) {
	    opp_error("%s: Invalid state type %d returned in %s::onEnter() (0..%d allowed).\n", getFullName(), tmp, 
		      to->getFullName().c_str(), StatesCnt);
	    }
	    
	    if (tmp != newState) {
		Log(Debug) << to->getFullName() << "::onEnter override: switching to "
			   << States[tmp].getFullName() << " instead of " << to->getFullName() << LogEnd;
		transitionsCnt++;
		newState = tmp;
		override = true;
		continue;
	    }
	}

	if (to->transitive) {
	    newState = to->transitiveTo;
	    Log(Debug) << "State change: " << States[State()].getFullName() << "->" << States[newState].getFullName() 
		       << ", because " << States[State()].getFullName() << " is transitive." << LogEnd;
	}
	transitionsCnt++;
    } while (to->transitive || override);
}

void Fsm::stringUpdate()
{
    char buf[80];
    sprintf(buf, "%s", States[CurrentState].getFullName().c_str());
       
    if (ev.isGUI()) 
      getDisplayString().setTagArg("t",0,buf);
 
}

Fsm::~Fsm()
{
    States.clear();
    Events.clear();
}
