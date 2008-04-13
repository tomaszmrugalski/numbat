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
#include "mip6.h"
#include "logger.h"
#include "ipv6msg_m.h"
#include "ipv6.h"
#include "ssinfo.h"
#include "mih_m.h"

using namespace std;

/********************************************************************************/
/*** Mobile IPv6 Mobile Node ****************************************************/
/********************************************************************************/

Define_Module(MobIPv6mn);


void MobIPv6mn::initialize()
{
    // register for MIH Events
    cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
    ssInfo * info = dynamic_cast<ssInfo*>(tmp);
    if (info)
	info->addEventListener(this);

    updateString();
}

void MobIPv6mn::handleMihMessage(cMessage *msg)
{

    if (dynamic_cast<MihEvent_L3AddrConfigured *>(msg)) {
	MihEvent_L3AddrConfigured * conf = dynamic_cast<MihEvent_L3AddrConfigured *>(msg);

	cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);

	if (conf->getRemoteAutoconf() == true) {
	    Log(Notice) << "MIPv6: This is a remote LocUpdate." << LogEnd;
	}
	
	if ( (conf->getRemoteAutoconf() == true) && (!info->hoInfo.mip.remoteLocUpdate) ) {
	    Log(Notice) << "New addr " << conf->getAddr() << " obtained, but it is a remote autoconf and support "
			<< " for remote location update is disabled. Doing nothing." << LogEnd;
	    return;
	}

	string myIP = conf->getAddr().plain();

	if (!conf->getRemoteAutoconf()) {
	    Log(Notice) << "Setting my IP to " << myIP << LogEnd;
	    par("myIP") = myIP.c_str();
	}

	IPv6 * locUpdate = new IPv6("BindingUpdate");

	IPv6Addr * src = new IPv6Addr(myIP.c_str(), true);
	locUpdate->setSrcIP( *src );
	IPv6Addr * dst = new IPv6Addr(par("corrIP").stringValue(), true);
	locUpdate->setDstIP( *dst );
	locUpdate->setBindingUpdate(true);

	send(locUpdate, "lowerOut", 0);
	Log(Notice) << "MIPv6: Sending Location update (myIP=" << src->plain() << ", corrIP=" << dst->plain() << ")." << LogEnd;

	delete src;
	delete dst;

	updateString();
    }
}

void MobIPv6mn::handleBindingAck(cMessage * msg)
{
    IPv6 * ip = check_and_cast<IPv6*>(msg);
    par("corrIP") = ip->getSrcIP().plain().c_str();
    Log(Notice) << "MIPv6: BindingAck received. corrIP=" << ip->getSrcIP().plain() << LogEnd;

    ssInfo * info = dynamic_cast<ssInfo*>(parentModule()->parentModule()->submodule("ssInfo"));
    if (info) {
	MihEvent_L3LocationUpdated * locUpd = new MihEvent_L3LocationUpdated();
	Log(Notice) << "MIH: Location Update complete. Other layers notified." << LogEnd;
	info->sendEvent(locUpd);
    } else 
	opp_error("Unable to obtain ssInfo structure.");
}

void MobIPv6mn::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();
    if (!gate || !strcmp(gate->fullName(), "eventIn")) {  
        handleMihMessage(msg);
	delete msg;
        return;
    }

    // add addressing
    cGate * inGate = msg->arrivalGate();
    string outGate;
    if (!strcmp(inGate->fullName(),"lowerIn")) {
	// uplink (receiving data)
	outGate = "upperOut";
	cMessage * pkt = msg->decapsulate();
	if (!pkt) {
	    IPv6 *ip = dynamic_cast<IPv6*>(msg);
	    if (ip && ip->getBindingAck()) {
		handleBindingAck(msg);
		delete msg;
		return;
	    } else {
		opp_error("Unable to decapsulate message");
	    }
	}
	send(pkt, "upperOut", 0);

	delete msg;
	return;
    } else {
	// downlink (sending data)
	IPv6 * ip = new IPv6("");
	ip->encapsulate(msg);

	IPv6Addr * addr = new IPv6Addr(par("myIP").stringValue(), true);
	ip->setSrcIP( *addr );
	delete addr;

	addr = new IPv6Addr(par("corrIP").stringValue(), true);
	ip->setDstIP( *addr );
	delete addr;

	outGate = "lowerOut";
	send(ip, "lowerOut", 0);
    }
    Log(Debug) << "Message " << msg->fullName() << " received via " << inGate->fullName() << ", sending to " << outGate <<  LogEnd;
}

void MobIPv6mn::fsmInit() 
{
  
}

void MobIPv6mn::updateString()
{
    char buf[512];
    const char * myIP = par("myIP").stringValue();
    const char  * corrIP = par("corrIP").stringValue();
    sprintf(buf, "myIP=%s\ncorrIP=%s", myIP, corrIP);
    if (ev.isGUI())
	displayString().setTagArg("t",0,buf);
}


/********************************************************************************/
/*** Mobile IPv6 Corresponding Node *********************************************/
/********************************************************************************/

Define_Module(MobIPv6cn);

void MobIPv6cn::initialize()
{
    updateString();
}

void MobIPv6cn::handleBindingUpdate(cMessage *msg)
{
    IPv6 * ip = check_and_cast<IPv6*>(msg);
    par("corrIP") = ip->getSrcIP().plain().c_str();
    Log(Notice) << "MIPv6: BindingUpdate received. New CorrIP=" << ip->getSrcIP().plain() << LogEnd;

    ip = new IPv6("BindingAck");
    ip->setSrcIP(IPv6Addr(par("myIP").stringValue(), true));
    ip->setDstIP(IPv6Addr(par("corrIP").stringValue(), true));
    ip->setBindingAck(true);

    send(ip, "lowerOut", 0);

    updateString();
}

void MobIPv6cn::handleMessage(cMessage *msg)
{
    // add addressing
    cGate * inGate = msg->arrivalGate();
    string outGate;
    if (!strcmp(inGate->fullName(),"lowerIn")) {
	// uplink (receiving data)
	outGate = "upperOut";
	cMessage * pkt = msg->decapsulate();
	if (!pkt) {
	    IPv6 * ip = dynamic_cast<IPv6*>(msg);
	    if (ip && ip->getBindingUpdate()) {
		handleBindingUpdate(msg);
		delete msg;
		return;
	    } else {
		opp_error("Unable to decapsulate message");
	    }
	}
	send(pkt, "upperOut", 0);
	delete msg;
	return;
    } else {
	// downlink (sending data)
	IPv6 * ip = new IPv6("");
	ip->encapsulate(msg);

	IPv6Addr * addr1 = new IPv6Addr(par("myIP").stringValue(), true);
	ip->setSrcIP( *addr1 );

	IPv6Addr * addr2 = new IPv6Addr(par("corrIP").stringValue(), true);
	ip->setDstIP( *addr2 );

	Log(Debug) << "Transmitting msg: src=" << addr1->plain() << " -> "
		   << addr2->plain() << LogEnd;

	delete addr1;
	delete addr2;

	outGate = "lowerOut";
	send(ip, "lowerOut", 0);
    }
    Log(Debug) << "Message " << msg->fullName() << " received via " << inGate->fullName() << ", sending to " << outGate <<  LogEnd;
}

void MobIPv6cn::updateString()
{
    char buf[128];
    sprintf(buf, "myIP=%s\ncorrIP=%s", par("myIP").stringValue(), par("corrIP").stringValue());
    if (ev.isGUI())
	displayString().setTagArg("t",0,buf);
}


/********************************************************************************/
/*** Mobile IPv6 Home Agent *****************************************************/
/********************************************************************************/

Define_Module(MobIPv6ha);


void MobIPv6ha::initialize()
{
}

void MobIPv6ha::handleMessage(cMessage *msg)
{
    cGate *inGate = msg->arrivalGate();
    string outGate ="";
    if (!strcmp(inGate->fullName(), "mipIn")) {
	outGate = "networkOut";
    } else {
	outGate = "mipOut";
    }
    Log(Debug) << "Message " << msg->fullName() << " received via " << inGate->fullName() << ", sending to " 
	       << outGate << LogEnd;
    send(msg, outGate.c_str(), 0);
}
