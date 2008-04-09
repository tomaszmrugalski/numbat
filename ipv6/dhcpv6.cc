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
#include "ipv6.h"

using namespace std;

/********************************************************************************/
/*** DHCPv6 Client **************************************************************/
/********************************************************************************/

Define_Module(DHCPv6Cli);

//#define DEBUG_FORCE_REMOTECONF

void DHCPv6Cli::initialize()
{
    fsmInit();

    // name vectors properly
    cModule * ss = parentModule()->parentModule();
    string x;
    x = ss->fullName() + string(" DHCP errors");
    DhcpErrors.setName(x.c_str());

    x = ss->fullName() + string(" DHCP conf. complete");
    DhcpComplete.setName(x.c_str());

    x = ss->fullName() + string(" DHCP conf. time");
    DhcpDuration.setName(x.c_str());

    // register for MIH Events
    cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
    ssInfo * info = dynamic_cast<ssInfo*>(tmp);
    info->addEventListener(this);

    GotAddrForNextLocation = false;
    PurposeNextLocation = false;
    NextLocationBS = 2;
}

void DHCPv6Cli::handleMessage(cMessage *msg)
{
    cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
    ssInfo * info = dynamic_cast<ssInfo*>(tmp);

    if (dynamic_cast<MihEvent_ReentryEnd*>(msg) ||
	dynamic_cast<MihEvent_EntryEnd*>(msg)) {
	Log(Notice) << "Starting DHCPv6 operation." << LogEnd;
	PurposeNextLocation = false;
	onEvent(EVENT_START, msg);
	DhcpStartTime = simTime();
	stringUpdate();
	return;
    }

    if (dynamic_cast<MihEvent_HandoverStart*>(msg)) 
    {
	if (info->hoInfo.dhcp.remoteAutoconf) {
	    MihEvent_HandoverStart *hoStart = dynamic_cast<MihEvent_HandoverStart*>(msg);
	    NextLocationBS = hoStart->getTargetBS();

	    Log(Notice) << "Triggering remote DHCP procedure. RemoteAutoconf is true: State()=" << State() 
			<< ", targetBS=" << NextLocationBS << LogEnd;
	    if ( this->CurrentState == DHCPv6Cli::STATE_CONFIGURED) {
		PurposeNextLocation = true;

		DhcpStartTime = simTime();
		onEvent(EVENT_START, msg);
	    }
	}
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
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);

    if (cli->GotAddrForNextLocation) {
	SLog(fsm, Notice) << "Already got address " << cli->AddrForNextLocation << " for this location (remote autoconf used)." << LogEnd;
	cli->Addr = cli->AddrForNextLocation;
	cli->GotAddrForNextLocation = false;
	return DHCPv6Cli::STATE_CONFIGURED;
    }

    ssInfo * info = ssInfoGet(fsm);
    DHCPv6Solicit * sol = new DHCPv6Solicit();
    sol->setAddrParams(info->hoInfo.dhcp.addrParams);

    string x;

    if (info->hoInfo.dhcp.rapidCommit) {
	x = "with rapid-commit,";
	sol->setRapidCommit(true);
    } else {
	x= " without rapid-commit,";
	sol->setRapidCommit(false);
    }

    if (info->hoInfo.dhcp.addrParams) {
	x += "with addr-params,";
	sol->setAddrParams(true);
    } else {
	x += "without addr-params,";
	sol->setAddrParams(false);
    }

    if (info->hoInfo.dhcp.remoteAutoconf
// TEMPORARY
#ifndef DEBUG_REMOTECONF
 && cli->PurposeNextLocation
#endif
) {
	x += " via relays (remote autoconf)";
	sol->setRemoteConf(true);
	sol->setRemoteBS(cli->NextLocationBS);
    } else {
	x += " (without remote autoconf)";
	sol->setRemoteConf(false);
    }
    
    SLog(fsm, Info) << "Sending SOLICIT " << x << LogEnd;

    fsm->send(sol, "dhcpOut", 0);

    if (info->hoInfo.dhcp.rapidCommit) {
	return STATE_WAIT_REPLY;
    }
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
    case EVENT_START:
    {
	SLog(fsm, Warning) << "Current operation aborted. Restarting operation." << LogEnd;
	cli->DhcpErrorCnt++;
	cli->DhcpErrors.record(cli->DhcpErrorCnt);
	return STATE_SEND_SOLICIT;

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
    req->setRemoteConf(info->hoInfo.dhcp.remoteAutoconf);

    SLog(fsm, Info) << "Sending REQUEST." << LogEnd;
    fsm->send(req, "dhcpOut", 0);

    return fsm->State();
}

// state wait for Reply
FsmStateType DHCPv6Cli::onEventState_WaitForReply(Fsm * fsm, FsmEventType e, cMessage * msg)
{
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);

    switch (e) {
    case EVENT_START:
    {
	SLog(fsm, Warning) << "Current operation aborted. Restarting operation." << LogEnd;
	cli->DhcpErrorCnt++;
	cli->DhcpErrors.record(cli->DhcpErrorCnt);
	return STATE_SEND_SOLICIT;
    }
    case EVENT_REPLY_RECEIVED:
    {
	DHCPv6Reply * reply = dynamic_cast<DHCPv6Reply*>(msg);
	cli->Addr = reply->getAddr();

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

    SLog(fsm, Info) << "REPLY received, completing " << type << " DAD in " << del << ", addr=" << cli->Addr.plain() << LogEnd;

    return fsm->State();
}

// state Wait for Advertise
FsmStateType DHCPv6Cli::onEventState_PerformingDad(Fsm * fsm, FsmEventType e, cMessage * msg)
{
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);
    switch (e) {
    case EVENT_START:
    {
	DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);
	SLog(fsm, Warning) << "Current operation aborted. Restarting operation." << LogEnd;
	cli->DhcpErrorCnt++;
	cli->DhcpErrors.record(cli->DhcpErrorCnt);
	return STATE_SEND_SOLICIT;
    }
    case EVENT_TIMER:
    {
	if (!cli->PurposeNextLocation) {
	    SLog(fsm, Info) << "DAD complete, addr " << cli->Addr.plain() << " is ready to use in this location." << LogEnd;
	} else {
	    SLog(fsm, Info) << "DAD complete, addr " << cli->Addr.plain() << " will be ready for use in next location." << LogEnd;
	}
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
    DHCPv6Cli * cli = dynamic_cast<DHCPv6Cli*>(fsm);

    simtime_t length = cli->simTime() - cli->DhcpStartTime;
    cli->DhcpDuration.record(length);
    cli->DhcpCompleteCnt++;
    cli->DhcpComplete.record(cli->DhcpCompleteCnt);

    SLog(fsm, Info) << "DHCPv6 configuration complete (configuration took " << length << " secs).";

    if (cli->PurposeNextLocation) {
	SLog(fsm, Cont) << "(remote autoconf: address will be used after handover)." << LogEnd;
	cli->AddrForNextLocation = cli->Addr;
	cli->GotAddrForNextLocation = true;
    }
    SLog(fsm, Cont) << LogEnd;

    ssInfo * info = dynamic_cast<ssInfo*>(fsm->parentModule()->parentModule()->submodule("ssInfo"));
    SLog(fsm, Notice) << "Notifying other layers: IPv6 address obtained." << LogEnd;

    MihEvent_L3AddrConfigured * confOK = new MihEvent_L3AddrConfigured();
    confOK->setAddr(cli->Addr);
    info->sendEvent(confOK);

    if (info->hoInfo.dhcp.addrParams) {
	ssInfo * info = dynamic_cast<ssInfo*>(fsm->parentModule()->parentModule()->submodule("ssInfo"));
	SLog(fsm, Notice) << "Notifying other layers: IPv6 routing configured (addrParams used)." << LogEnd;
	info->sendEvent(new MihEvent_L3RoutingConfigured());
    }

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
    nextAddr=1;
}

double DHCPv6Srv::sendMsg(cMessage * msg, char * paramName, double extraDelay)
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

    if (HandlingRelay) {
	IPv6 * ip = new IPv6("DHCPv6 Relay");
	ip->encapsulate(msg);
	ip->setSrcIP(SrcIP);
	ip->setDstIP(DstIP);
	ip->setDhcpv6Relay(true);

	msg = ip;
    }

    sendDelayed(msg, delay+extraDelay, "dhcpOut");

    return delay+extraDelay;
}

void DHCPv6Srv::sendReply(string x, bool addrParams, bool viaRelays)
{
    DHCPv6Reply * reply = new DHCPv6Reply();
    string addr = par("prefix").stringValue();
    char buf[32];
    sprintf(buf, "%x", ++nextAddr);
    addr = addr + string(buf);
    reply->setAddr(IPv6Addr(addr.c_str(), true));

    reply->setAddrParams(addrParams);
    double extraDelay = 0.0;
    if (viaRelays) {
	double min = (double)par("MinDelayRelay");
	double max = (double)par("MaxDelayRelay");
	extraDelay = uniform(min, max);
	Log(Info) << x << " relays will be used (extra " << extraDelay << "secs delay), sending REPLY (addr="
		  << addr << ")" << LogEnd;
    } else {
	Log(Info) << x << "sending REPLY (addr=" << addr << ")." << LogEnd;
    }

    sendMsg(reply, "DelayReply", extraDelay);
}

void DHCPv6Srv::handleMessage(cMessage *msg)
{
    if (dynamic_cast<IPv6*>(msg)) {
	handleRelay(msg);
	delete msg;
	return;
    }

    if (dynamic_cast<DHCPv6Solicit*>(msg)) {
	DHCPv6Solicit * sol = dynamic_cast<DHCPv6Solicit*>(msg);
	if (sol->getRemoteConf() && !HandlingRelay)
	{
	    sendRelay(msg, sol->getRemoteBS());
	    return;
	}

	if (sol->getRapidCommit()) {
	    sendReply("SOLICIT with rapid-commit received, ", sol->getAddrParams(), sol->getRemoteConf() && !HandlingRelay );
	    delete msg;
	    return;
	} else {
	    DHCPv6Advertise * adv = new DHCPv6Advertise();
	    int pref = par("preference");
	    double extraDelay = 0.0;

	    adv->setPreference(pref);
	    adv->setAddrParams(sol->getAddrParams());
	    Log(Info) << "SOLICIT received,";

	    Log(Cont) << " sending ADVERTISE (preference=" << pref << ")." << LogEnd;
	    sendMsg(adv, "DelayAdvertise", extraDelay);
	    delete msg;
	    return;
	}
    }

    if (dynamic_cast<DHCPv6Request*>(msg)) {
	DHCPv6Request * req = dynamic_cast<DHCPv6Request*>(msg);
	if (req->getRemoteConf() && !HandlingRelay)
	{
	    sendRelay(msg, req->getRemoteBS());
	    return;
	}

	sendReply("REQUEST received,", req->getAddrParams(), req->getRemoteConf() && !HandlingRelay);
	delete msg;
	return;
    }

    if (dynamic_cast<DHCPv6Confirm*>(msg)) {
	DHCPv6Confirm * conf = dynamic_cast<DHCPv6Confirm*>(msg);
	if (conf->getRemoteConf() && !HandlingRelay)
	{
	    sendRelay(msg, conf->getRemoteBS());
	    return;
	}

	sendReply("CONFIRM received,", conf->getAddrParams(), conf->getRemoteConf() && !HandlingRelay);
	delete msg;
	return;
    }

    opp_error("Invalid message %s received in DHCPv6Srv.", msg->fullName());
}

void DHCPv6Srv::sendRelay(cMessage * msg, int remoteBS)
{
    int thisBS = parentModule()->parentModule()->index();
    
    Log(Notice) << "Relays will be used (this BS[" << thisBS << "], target: BS[" << remoteBS << "])." << LogEnd;
    IPv6 * ip = new IPv6("DHCPv6 relay");
    ip->setSrcIP( getIPofBS(thisBS) );
    ip->setDstIP( getIPofBS(remoteBS) );
    ip->encapsulate(msg);
    ip->setDhcpv6Relay(true);

    Log(Notice) << "Transmitting RELAY-FORW: srcIP=" << ip->getSrcIP() << ", dstIP=" << ip->getDstIP() << LogEnd;

    sendMsg(ip, "", 0.0);
		  
}

void DHCPv6Srv::handleRelay(cMessage * msg)
{
    IPv6 * ip = dynamic_cast<IPv6*>(msg);
    cMessage * dhcp = msg->decapsulate();

    if (dynamic_cast<DHCPv6Advertise*>(dhcp) ||
	dynamic_cast<DHCPv6Reply*>(dhcp)) {

	Log(Info) << "Decapsulating relay message." << LogEnd;
	sendMsg(dhcp, "", 0.0);
	return;
    }

    HandlingRelay = true;
    SrcIP = ip->getDstIP();
    DstIP = ip->getSrcIP();

    Log(Info) << "Handling relayed message." << LogEnd;

    handleMessage(dhcp);
    HandlingRelay = false;
    
    return;
}

IPv6Addr DHCPv6Srv::getIPofBS(int bs)
{
    char buf[512];
    sprintf(buf, "BS[%d].bsIPv6.mobIPv6ha", bs);
    cModule * m = parentModule()->parentModule()->parentModule(); // whole network
    m = m->moduleByRelativePath(buf);
    string x = m->par("prefix").stringValue();

    return IPv6Addr(x.c_str(), true);
}
