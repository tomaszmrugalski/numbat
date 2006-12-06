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
#include "ipv6node.h"

/********************************************************************************/
/*** IPv6 Node ******************************************************************/
/********************************************************************************/

Define_Module(IPv6Node);


void IPv6Node::initialize()
{
    sendTimer = new cMessage("IPv6 send");
    scheduleAt(0.010, sendTimer);
}

void IPv6Node::handleMessage(cMessage *msg)
{
    if (msg==sendTimer)
	generateTraffic();
    
    ev << "Message " << msg->fullName() << " received." << endl;
}

void IPv6Node::generateTraffic()
{
    cMessage *m = new cMessage("IPv6 packet");
    send(m, "ipOut");

    scheduleAt(0.012, sendTimer);

    // reschedule this timer
}
