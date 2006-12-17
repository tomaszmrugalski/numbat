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

    sentBytes = 0;
    sentPkts  = 0;
    rcvdBytes = 0;
    rcvdPkts  = 0;
}

void IPv6Node::handleMessage(cMessage *msg)
{
    if (msg==sendTimer) {
	generateTraffic();
	return;
    }
    
    ev << fullName() << ": Message " << msg->fullName() << " received." << endl;
    rcvdPkts++;
    rcvdBytes += msg->length();
    updateStats();

    delete msg;
}

void IPv6Node::generateTraffic()
{
    cMessage *m = new cMessage("IPv6 packet");
    m->setLength(30);
    sentPkts++;
    sentBytes += m->length();
    send(m, "ipOut");

    m = new cMessage("IPv6 packet");
    m->setLength(40);
    sentPkts++;
    sentBytes += m->length();
    send(m, "ipOut");

    m = new cMessage("IPv6 packet");
    m->setLength(50);
    sentPkts++;
    sentBytes += m->length();
    send(m, "ipOut");

    updateStats();

    scheduleAt(simTime()+(double)(0.025), sendTimer);

    // reschedule this timer
}

void IPv6Node::updateStats()
{
    char buf[80];
    sprintf(buf, "sent=%ld(%ld), rcvd=%ld(%ld)", 
	    sentPkts, sentBytes, rcvdPkts, rcvdBytes);
    if (ev.isGUI()) 
	displayString().setTagArg("t",0,buf);
}
