/**
 * @file   dhcpbv6.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Tue Aug  7 12:55:16 CET 2007
 * 
 * @brief  DHCPv6 server/client
 * 
 * Published under GNU GPLv2 or later 
 */

#ifndef DHCPV6_H
#define DHCPV6_H

#include <stdint.h>
#include <omnetpp.h>
#include "fsm.h"
#include "ssinfo.h"

class DHCPv6Cli : public Fsm
{
 public:
    int AdvCount;
 protected:
    // --- STATES --
    typedef enum {
	STATE_IDLE,
	STATE_SEND_SOLICIT,
	STATE_WAIT_ADVERTISE,
	STATE_SEND_REQUEST,
	STATE_WAIT_REPLY,
	STATE_SEND_CONFIRM,
	STATE_PERFORMING_DAD,
	STATE_CONFIGURED,
	STATE_NUM // last dummy state
    } State;

    typedef enum {
	EVENT_START,
	EVENT_TIMER, // used for initial delay, also in PERFORMING_DAD
	EVENT_ADVERTISE_RECEIVED,
	EVENT_REPLY_RECEIVED,
	EVENT_NUM // last dummy event
    } Event;

    // state idle
    static FsmStateType onEventState_Idle(Fsm * fsm, FsmEventType e, cMessage * msg);

    // state send solicit
    static FsmStateType onEnterState_SendSolicit(Fsm * fsm);

    // state Wait for Advertise
    static FsmStateType onEnterState_WaitForAdvertise(Fsm * fsm);
    static FsmStateType onEventState_WaitForAdvertise(Fsm * fsm, FsmEventType e, cMessage * msg);
    static FsmStateType onExitState_WaitForAdvertise(Fsm * fsm);

    // state send Request
    static FsmStateType onEnterState_SendRequest(Fsm * fsm);

    // state wait for Reply
    static FsmStateType onEventState_WaitForReply(Fsm * fsm, FsmEventType e, cMessage * msg);

    // state send Confirm
    static FsmStateType onEnterState_SendConfirm(Fsm * fsm);

    // state Performing DAD
    static FsmStateType onEnterState_PerformingDad(Fsm * fsm);
    static FsmStateType onEventState_PerformingDad(Fsm * fsm, FsmEventType e, cMessage * msg);

    // state configured
    static FsmStateType onEnterState_Configured(Fsm * fsm);
    static FsmStateType onEventState_Configured(Fsm * fsm, FsmEventType e, cMessage * msg);
    
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void fsmInit();
 private:
    void startTimer(double del);
    void stopTimer();
    static ssInfo * ssInfoGet(Fsm * fsm);

    TIMER_DEF(Delay);

};

class DHCPv6Srv : public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
 private:
    double sendMsg(cMessage * msg, char * paramName);
    void   sendReply(string x, bool addrParams);
};


#endif
