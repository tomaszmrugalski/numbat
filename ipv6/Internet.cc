/**
 * @file    ipv6node.h
 * @author  Tomasz Mrugalski <thomson@klub.com.pl>
 * @date    Sat Nov 18 18:42:04 2006
 *
 * @brief  IPv6 transmitter/receiver
 * 
 * Published under GNU GPLv2 or later 
 */

#include <omnetpp.h>
#include <string>
#include "Internet.h"
#include "logger.h"
#include "ipv6msg_m.h"

using namespace std;

/********************************************************************************/
/*** IPv6 Node ******************************************************************/
/********************************************************************************/

Define_Module(Internet);

void Internet::initialize()
{
    int logLevel = parentModule()->par("LogLevel");
    if ( (logLevel<1) || (logLevel>8) )
	opp_error("Invalid LogLevel: %d. Accepted values: 1..8\n", logLevel);
    logger::setLogLevel(logLevel);
    Log(Crit) << "LogLevel has been set to " << logLevel << "." << LogEnd;
    logger::setEv(&ev);

    int size = gateSize("ipOut");
    Log(Notice) << "There are " << size << " object(s) connected." << LogEnd;
    
    for (int i=0;i<size;i++) {
	cGate * g = gate("ipOut", i);
	cGate * toGate = g->destinationGate();
	cModule * mod = toGate->ownerModule();
	string prefix = mod->par("prefix").stringValue();
	Log(Notice) << i << ": localGate=" << g->fullName() << ", remote=" << mod->fullName() << ", prefix=" << prefix << LogEnd;
	RouteEntry * entry = new RouteEntry;
	entry->prefix = IPv6Addr(prefix.c_str(), true);
	entry->gateIndex = i;
	RoutingTable.push_back(*entry);
    }


    WATCH_LIST(RoutingTable);
}

double Internet::calculateDelay(IPv6 *msg)
{
    double min = (double)par("MinDelay");
    double max = (double)par("MaxDelay");

    double delay = uniform(min, max);

    return delay;
}

void Internet::handleMessage(cMessage *msg)
{
    // message received. Let's route that.
    IPv6 * ip = check_and_cast<IPv6*>(msg);
    IPv6Addr dst = ip->getDstIP();
    
    double delay = calculateDelay(ip);

    list<RouteEntry>::iterator it;
    for (it=RoutingTable.begin(); it!=RoutingTable.end(); it++) 
    {
	if (!memcmp(dst.addr, it->prefix.addr, 8)) {
	    Log(Debug) << "Route for dst addr=" << dst << " found: " << *it << LogEnd;
	    sendDelayed(msg, delay, "ipOut", it->gateIndex);
	    return;
	}
    }
    
    Log(Error) << "Received message, but failed to find route for it (dstIP=" << dst << ")." << LogEnd;
}

ostream & operator << (ostream &s, RouteEntry e)
{
    s << e.prefix.plain() << " -> gate " << e.gateIndex;
    return s;
}
