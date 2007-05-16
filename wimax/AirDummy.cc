/**
 * @file   AirDummy.cc
 * @author Andrzej Bojarski
 * @date   ???
 * 
 * @brief  Dummy Air cloud (broadcast packet sink), similar to /dev/null
 * 
 * published under GNU GPLv2 or later
 */

#include <omnetpp.h>
#include "AirDummy.h"
#include "logger.h"

Define_Module(AirDummy);
 
void AirDummy::initialize()
{
    int logLevel = par("LogLevel");
    if ( (logLevel<1) || (logLevel>8) )
	opp_error("Invalid LogLevel: %d. Accepted values: 1..8\n", logLevel);
    logger::setLogLevel(logLevel);
    Log(Crit) << "LogLevel has been set to " << logLevel << "." << LogEnd;
}

void AirDummy::handleMessage(cMessage *msg)
{
      delete msg;
}
