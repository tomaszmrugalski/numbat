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
#include "ra.h"
#include "logger.h"

using namespace std;

/********************************************************************************/
/*** Router Advertisement Receiver **********************************************/
/********************************************************************************/

Define_Module(RaRcv);

void RaRcv::initialize()
{
}

void RaRcv::handleMessage(cMessage *msg)
{
    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}

void RaRcv::fsmInit() 
{
  
}

/********************************************************************************/
/*** Router Advertisement Generator *********************************************/
/********************************************************************************/

Define_Module(RaGen);


void RaGen::initialize()
{
}

void RaGen::handleMessage(cMessage *msg)
{
    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}
