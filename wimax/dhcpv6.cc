/**
 * @file    dhcpv6.h
 * @author  Tomasz Mrugalski <thomson@klub.com.pl>
 * @date    Sat Nov 18 18:42:04 2006
 *
 * @brief  DHCPv6 server/client
 * 
 * Published under GNU GPLv2 or later 
 */

#include <omnetpp.h>
#include <string>
#include "dhcpv6.h"
#include "logger.h"
#include "ssinfo.h"
#include "ipv6msg_m.h"
#include "mih_m.h"

using namespace std;

/********************************************************************************/
/*** DHCPv6 Client **************************************************************/
/********************************************************************************/

Define_Module(DHCPv6Cli);


void DHCPv6Cli::initialize()
{
    fsmInit();
    
    // register for MIH Events
    cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
    if (tmp) {
	// SS-side
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);
	info->addEventListener(this);
    }
}

void DHCPv6Cli::handleMessage(cMessage *msg)
{
    if (!strcmp(msg->fullName(),"dhcpStart")) {
	onEvent(EVENT_START, msg);
	delete msg;
	stringUpdate();
	return;
    }
    if (dynamic_cast<DHCPv6Advertise*>(msg)) {
	onEvent(EVENT_ADVERTISE_RECEIVED, msg);
	delete msg;
	stringUpdate();
	return;
    }
    if (dynamic_cast<DHCPv6Reply*>(msg)) {
	onEvent(EVENT_REPLY_RECEIVED, msg);
	delete msg;
	stringUpdate();
	return;
    }
    if (msg==TimerDelay) {
	onEvent(EVENT_TIMER, msg);
	stringUpdate();
	return;
    }

    cGate * gate = msg->arrivalGate();
    if (!gate || !strcmp(gate->fullName(), "eventIn")) {  
	Log(Info) << "MIH Event message received." << LogEnd;
    } else {
	opp_error("Unknown message type received %s in DHCPv6Cli", msg->fullName());
    }

    delete msg;
}

void DHCPv6Cli::fsmInit() 
{
    statesEventsInit(DHCPv6Cli::STATE_NUM, DHCPv6Cli::EVENT_NUM, STATE_IDLE);

    stateInit(STATE_IDLE,           "Idle",                                  onEventState_Idle);
    stateInit(STATE_SEND_SOLICIT,   "Sending SOLICIT", STATE_WAIT_ADVERTISE, onEnterState_SendSolicit);
    stateInit(STATE_WAIT_ADVERTISE, "Wait for ADVERTISE", onEventState_WaitForAdvertise,
	      onEnterState_WaitForAdvertise, onExitState_WaitForAdvertise);
    stateInit(STATE_SEND_REQUEST,   "Sending REQUEST", STATE_WAIT_REPLY,     onEnterState_SendRequest);
    stateInit(STATE_WAIT_REPLY,     "Wait for REPLY", onEventState_WaitForReply);
    stateInit(STATE_SEND_CONFIRM,   "Sending CONFIRM", STATE_WAIT_REPLY,     onEnterState_SendConfirm);
    stateInit(STATE_CONFIGURED,     "Configured",                            onEventState_Configured, onEnterState_Configured, 0);
    stateInit(STATE_PERFORMING_DAD, "Performing DAD", onEventState_PerformingDad, onEnterState_PerformingDad, 0);
    stateVerify();

    // event init
    eventInit(EVENT_START, "Begin DHCPv6 client operation");
    eventInit(EVENT_ADVERTISE_RECEIVED, "Advertise received");
    eventInit(EVENT_REPLY_RECEIVED, "Reply received");
    eventInit(EVENT_TIMER, "Timer"); // used for delaying SOLICIT and DAD
    eventVerify();
    
    TIMER(Delay, 1.0, "Delay"); // used for delaying SOLICIT and DAD

    stringUpdate();
}

ssInfo * DHCPv6Cli::ssInfoGet(Fsm * fsm)
{
    cModule * tmp = fsm->parentModule()->parentModule();
    ssInfo * info = dynamic_cast<ssInfo*>(tmp->submodule("ssInfo"));
    if (!info)
	opp_error("Unable to find ssInfo structure");
    return info;
}

void DHCPv6Cli::startTimer(double del)
{
    TIMER_SET(Delay, del);
    TIMER_START(Delay);
}

void DHCPv6Cli::stopTimer()
{
    TIMER_STOP(Delay);
}

// state idle
FsmStateType DHCPv6Cli::onEventState_Idle(Fsm * fsm, FsmEventType e, cMessage * msg)
{
    ssInfo * info = ssInfoGet(fsm);
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);

    switch (e) {

    case EVENT_START:
    {
	double del;
	if (info->hoInfo.dhcp.skipInitialDelay)
	    del = 0.0f;
	else 
	    del = uniform(0, 1.0);
	SLog(fsm, Info) << "Delay: Starting operation in " << del << LogEnd;
	cli->startTimer(del);
	break;
    }

    case EVENT_TIMER: {
	if (info->hoInfo.dhcp.sendConfirm) {
	    SLog(fsm, Info) << "Timeout reached, sending CONFIRM." << LogEnd;
	    return STATE_SEND_CONFIRM;
	} else {
	    SLog(fsm, Info) << "Timeout reached, sending SOLICIT." << LogEnd;
	    return STATE_SEND_SOLICIT;
	}
    }
    default:
	CASE_IGNORE(fsm, e);
    }
}

// state send solicit
FsmStateType DHCPv6Cli::onEnterState_SendSolicit(Fsm * fsm)
{
    ssInfo * info = ssInfoGet(fsm);
    DHCPv6Solicit * sol = new DHCPv6Solicit();
    sol->setAddrParams(info->hoInfo.dhcp.addrParams);

    if (info->hoInfo.dhcp.rapidCommit) {
	SLog(fsm, Info) << "Sending SOLICIT (with rapid-commit)." << LogEnd;
	sol->setRapidCommit(true);
    } else {
	SLog(fsm, Info) << "Sending SOLICIT (without rapid-commit)." << LogEnd;
	sol->setRapidCommit(false);
    }

    fsm->send(sol, "dhcpOut", 0);
    return fsm->State();
}

FsmStateType DHCPv6Cli::onEnterState_WaitForAdvertise(Fsm * fsm)
{
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);
    cli->startTimer(1.0);
    cli->AdvCount = 0;

    return fsm->State();
}

// state Wait for Advertise
FsmStateType DHCPv6Cli::onEventState_WaitForAdvertise(Fsm * fsm, FsmEventType e, cMessage * msg)
{
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);

    switch (e) {
    case EVENT_TIMER:
    {
	if (cli->AdvCount) {
	    SLog(fsm, Info) << "Timeout reached, waiting for ADVERTISE has ended." << LogEnd;
	    return STATE_SEND_REQUEST;
	} else {
	    SLog(fsm, Warning) << "Timeout reached, but no ADVERTISE received, retransmitting SOLICIT" << LogEnd;
	    return STATE_SEND_SOLICIT;
	}
    }
    case EVENT_ADVERTISE_RECEIVED:
    {
	DHCPv6Advertise * adv = dynamic_cast<DHCPv6Advertise *>(msg);
	SLog(fsm, Info) << "ADVERTISE with prerefence=" << adv->getPreference() << " received." << LogEnd;
	if (adv->getPreference()==255) {
	    return STATE_SEND_REQUEST;
	}
	cli->AdvCount++;
	return fsm->State();
    }
    default:
	CASE_IGNORE(fsm, e);
    }
}

FsmStateType DHCPv6Cli::onExitState_WaitForAdvertise(Fsm * fsm)
{
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);
    cli->stopTimer();
}


// state send Request
FsmStateType DHCPv6Cli::onEnterState_SendRequest(Fsm * fsm)
{
    ssInfo * info = ssInfoGet(fsm);
    DHCPv6Request * req = new DHCPv6Request();
    req->setAddrParams(info->hoInfo.dhcp.addrParams);

    SLog(fsm, Info) << "Sending REQUEST." << LogEnd;
    fsm->send(req, "dhcpOut", 0);

    return fsm->State();
}

// state wait for Reply
FsmStateType DHCPv6Cli::onEventState_WaitForReply(Fsm * fsm, FsmEventType e, cMessage * msg)
{

    switch (e) {
    case EVENT_REPLY_RECEIVED:
    {
	return STATE_PERFORMING_DAD;
    }
    default:
	CASE_IGNORE(fsm, e);
    }
}

FsmStateType DHCPv6Cli::onEnterState_PerformingDad(Fsm * fsm)
{
    ssInfo * info = ssInfoGet(fsm);
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);
    double del;
    string type;
    switch (info->hoInfo.dhcp.DadType)
    {
    case DHCP_DAD_TYPE_NORMAL:
	type = "normal";
	del = 1.0;
	break;
    case DHCP_DAD_TYPE_NONE:
	type = "none";
	del = 0.0;
	break;
    case DHCP_DAD_TYPE_OPTIMISTIC:
	type = "optimistic";
	del = 1.0; // set this to some meaningful value
	break;
    case DHCP_DAD_TYPE_SERVER_SIDE:
	type = "server side";
	del = 0.0;
	break;
    }
    
    cli->startTimer(del);

    SLog(fsm, Info) << "REPLY received, completing " << type << " DAD in " << del << LogEnd;

    return fsm->State();
}

// state Wait for Advertise
FsmStateType DHCPv6Cli::onEventState_PerformingDad(Fsm * fsm, FsmEventType e, cMessage * msg)
{
    switch (e) {
    case EVENT_TIMER:
    {
	SLog(fsm, Info) << "DAD complete." << LogEnd;
	return STATE_CONFIGURED;
    }
    CASE_IGNORE(fsm, e);
    }
}


// state send Confirm
FsmStateType DHCPv6Cli::onEnterState_SendConfirm(Fsm * fsm)
{
    opp_error("CONFIRM not implemented yet.");
    return fsm->State();
}

// state configured
FsmStateType DHCPv6Cli::onEnterState_Configured(Fsm * fsm)
{
    SLog(fsm, Info) << "DHCPv6 configuration complete." << LogEnd;
    return fsm->State();
}

FsmStateType DHCPv6Cli::onEventState_Configured(Fsm * fsm, FsmEventType e, cMessage * msg)
{
    ssInfo * info = ssInfoGet(fsm);
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);

    switch (e) {
    case EVENT_START:
	SLog(fsm, Info) << "DHCPv6 procedure initiated." << LogEnd;
	return STATE_SEND_SOLICIT;
    default:
	CASE_IGNORE(fsm, e);
    }
}

/********************************************************************************/
/*** DHCPv6 Server **************************************************************/
/********************************************************************************/

Define_Module(DHCPv6Srv);


void DHCPv6Srv::initialize()
{
}

double DHCPv6Srv::sendMsg(cMessage * msg, char * paramName)
{
    double delay = 0;
    if (strlen(paramName)) {
	char buf[80];
	sprintf(buf, "Min%s", paramName);
	double min = (double)par(buf);
	
	sprintf(buf, "Max%s", paramName);
	double max = (double)par(buf);
	
	delay = uniform(min, max);
    }

    Log(Debug) << "Sending " << msg->name() << " in " << setiosflags(ios::fixed) << setprecision(3) << delay*1000
	       << "msecs." << LogEnd;

    sendDelayed(msg, delay, "dhcpOut");

    return delay;
}

void DHCPv6Srv::sendReply(string x, bool addrParams)
{
    DHCPv6Reply * reply = new DHCPv6Reply();
    reply->setAddrParams(addrParams);
    Log(Info) << x << "sending REPLY" << LogEnd;
    sendMsg(reply, "DelayReply");
}

void DHCPv6Srv::handleMessage(cMessage *msg)
{
    if (dynamic_cast<DHCPv6Solicit*>(msg)) {
	DHCPv6Solicit * sol = dynamic_cast<DHCPv6Solicit*>(msg);
	if (sol->getRapidCommit()) {
	    sendReply("SOLICIT with rapid-commit received, ", sol->getAddrParams());
	    delete msg;
	    return;
	} else {
	    DHCPv6Advertise * adv = new DHCPv6Advertise();
	    int pref = par("preference");
	    adv->setPreference(pref);
	    adv->setAddrParams(sol->getAddrParams());
	    Log(Info) << "SOLICIT received, sending ADVERTISE (preference=" << pref << ")." << LogEnd;
	    sendMsg(adv, "DelayAdvertise");
	    delete msg;
	    return;
	}
    }

    if (dynamic_cast<DHCPv6Request*>(msg)) {
	DHCPv6Request * req = dynamic_cast<DHCPv6Request*>(msg);
	sendReply("REQUEST received,", req->getAddrParams());
	delete msg;
	return;
    }

    if (dynamic_cast<DHCPv6Confirm*>(msg)) {
	DHCPv6Confirm * conf = dynamic_cast<DHCPv6Confirm*>(msg);
	sendReply("CONFIRM received,", conf->getAddrParams());
	delete msg;
	return;
    }

    opp_error("Invalid message %s received in DHCPv6Srv.", msg->fullName());
}
