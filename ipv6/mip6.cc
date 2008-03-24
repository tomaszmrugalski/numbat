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

using namespace std;

/********************************************************************************/
/*** Mobile IPv6 Mobile Node ****************************************************/
/********************************************************************************/

Define_Module(MobIPv6mn);


void MobIPv6mn::initialize()
{
}

void MobIPv6mn::handleMessage(cMessage *msg)
{

    // add addressing
    cGate * inGate = msg->arrivalGate();
    string outGate;
    if (!strcmp(inGate->fullName(),"lowerIn")) {
	// uplink (receiving data)
	outGate = "upperOut";
	cMessage * pkt = msg->decapsulate();
	if (!pkt)
	    opp_error("Unable to decapsulate message");
	send(pkt, "upperOut", 0);
    } else {
	// downlink (sending data)
	IPv6 * ip = new IPv6("");
	ip->encapsulate(msg);
	ip->setSrcIP( (int)par("myIP") );
	ip->setDstIP( (int)par("corrIP") );
	outGate = "lowerOut";
	send(ip, "lowerOut", 0);
    }
    Log(Crit) << "Message " << msg->fullName() << " received via " << inGate->fullName() << ", sending to " << outGate <<  LogEnd;
}

void MobIPv6mn::fsmInit() 
{
  
}

/********************************************************************************/
/*** Mobile IPv6 Corresponding Node *********************************************/
/********************************************************************************/

Define_Module(MobIPv6cn);

void MobIPv6cn::initialize()
{
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
	if (!pkt)
	    opp_error("Unable to decapsulate message");
	send(pkt, "upperOut", 0);
    } else {
	// downlink (sending data)
	IPv6 * ip = new IPv6("");
	ip->encapsulate(msg);
	ip->setSrcIP( (int)par("myIP") );
	ip->setDstIP( (int)par("corrIP") );
	outGate = "lowerOut";
	send(ip, "lowerOut", 0);
    }
    Log(Crit) << "Message " << msg->fullName() << " received via " << inGate->fullName() << ", sending to " << outGate <<  LogEnd;
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
    Log(Debug) << "Message " << msg->fullName() << " received." << LogEnd;
    delete msg;
}
