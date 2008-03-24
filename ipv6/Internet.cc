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
}

void Internet::handleMessage(cMessage *msg)
{
    cMessage * msg2 = msg->decapsulate();
    if (!msg2) {
	Log(Debug) << "Received message (NOT encapsulated)." << LogEnd;
    } else {
	Log(Debug) << "Received message (encapsulated)." << LogEnd;
    }
}

