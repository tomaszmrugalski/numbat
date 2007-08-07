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

using namespace std;

/********************************************************************************/
/*** DHCPv6 Client **************************************************************/
/********************************************************************************/

Define_Module(DHCPv6Cli);


void DHCPv6Cli::initialize()
{
}

void DHCPv6Cli::handleMessage(cMessage *msg)
{
    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}

void DHCPv6Cli::fsmInit() 
{
  
}

/********************************************************************************/
/*** DHCPv6 Server **************************************************************/
/********************************************************************************/

Define_Module(DHCPv6Srv);


void DHCPv6Srv::initialize()
{
}

void DHCPv6Srv::handleMessage(cMessage *msg)
{
    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}
