/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2006-12-29 01:50:38+0100
 * 
 * @brief  Generic Finite State Machine implementation
 * @licence GNU GPLv2 or later
 * 
 */

#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#ifndef FSM_H
#define FSM_H

using namespace std;

#include <omnetpp.h>

#define TIMER(name, time, descr)                              \
    Timer##name##Value = time;			              \
    Timer##name        = new cMessage(descr);

#define TIMER_START(name)                                     \
    scheduleAt(simTime() + Timer##name##Value, Timer##name);

#define TIMER_STOP(name)                                      \
    if (Timer##name ->isScheduled())                          \
        cancelEvent(Timer##name);

#define TIMER_DEL(name) \
    cancelEvent(Timer##name); \
    delete Timer##name;

#define TIMER_SET(name, time) Timer##name##Value = time;

#define TIMER_DEF(name)    \
    double Timer##name##Value; \
    cMessage* Timer##name;

#define IF_TIMER(name, event)                                  \
    if (msg==Timer##name)                                      \
       onEvent(event, msg);

#define STATIC_TIMER_START(obj, name) \
    obj->scheduleAt(simTime() + obj->Timer##name##Value, obj->Timer##name);

#define CASE_IGNORE(fsm,e)					       \
    SLog(fsm, Debug) << fsm->getFullName() << ": event "		       \
	   << fsm->Events[e].getFullName() << " ignored in state " \
 	   << fsm->CurrentStateGet()->getFullName() << LogEnd; \
        return fsm->State();

#define FSM_MAX_TRANSITIONS 64

typedef int FsmStateType;
typedef int FsmEventType;

class Fsm;
class FsmEvent;
class FsmState;

typedef FsmStateType onEventFunc(Fsm *fsm, FsmEventType e, cMessage *msg);
typedef FsmStateType onEnterFunc(Fsm *fsm);
typedef FsmStateType onExitFunc (Fsm *fsm);


class FsmEvent
{
public:
    std::string getFullName();
    FsmEventType type;
    std::string name;
    bool inited;
};


class FsmState
{
public:
    bool inited;
    FsmStateType type;
    std::string name;
    onEventFunc *onEvent;
    onEnterFunc *onEnter;
    onExitFunc  *onExit;
    std::string getFullName();
    bool transitive;
    FsmStateType transitiveTo;
};

class Fsm : public cSimpleModule { 
public:
    Fsm();
    FsmStateType State() { return CurrentState; }
    FsmState * CurrentStateGet() { return &States[CurrentState]; }
    std::vector<FsmState> States;
    std::vector<FsmEvent> Events;

    virtual void onEvent(FsmEventType e, cMessage *msg);

protected:
    virtual void fsmInit() = 0;
    virtual ~Fsm();
    bool stateVerify();
    bool eventVerify();
    void statesEventsInit(int statesCnt, int eventsCnt, FsmStateType s);
    virtual void stateInit(FsmStateType type, std::string name, onEventFunc func); // stationary state
    virtual void stateInit(FsmStateType type, std::string name, onEventFunc onEvent, onEnterFunc onEnter, onExitFunc onExit); // stationary state
    virtual void stateInit(FsmStateType type, std::string name, int targetState, onEnterFunc onEnter); // transitive state
    void eventInit(FsmEventType type, std::string name);
    void stateSet(FsmStateType state);
    void stringUpdate();

    int StatesCnt;
    int EventsCnt;

    FsmStateType CurrentState;

private:
};



#endif

