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
    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}

void MobIPv6mn::fsmInit() 
{
  
}

/********************************************************************************/
/*** DHCPv6 Server **************************************************************/
/********************************************************************************/

Define_Module(MobIPv6ha);


void MobIPv6ha::initialize()
{
}

void MobIPv6ha::handleMessage(cMessage *msg)
{
    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}
