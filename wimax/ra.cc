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
#include "ipv6msg_m.h"
#include "logger.h"

using namespace std;

/********************************************************************************/
/*** Router Advertisement Receiver **********************************************/
/********************************************************************************/

Define_Module(RaRcv);

void RaRcv::initialize()
{
    RaRcvCnt = 0;
    updateString();
}

void RaRcv::handleMessage(cMessage *msg)
{
    Log(Notice) << "Message " << msg->fullName() << " received." << endl;
    if (dynamic_cast<IPv6Ra*>(msg)) {
	RaRcvCnt++;
	updateString();
    } else {
	opp_error("Message %s is not supposed to be received by RaRcv object.", msg->fullName());
    }
    delete msg;
}

void RaRcv::fsmInit() 
{
  
}

void RaRcv::updateString()
{
  char buf[80];
  sprintf(buf, "%d RAs rcvd.", RaRcvCnt);
  if (ev.isGUI())
    displayString().setTagArg("t", 0, buf);

}

/********************************************************************************/
/*** Router Advertisement Generator *********************************************/
/********************************************************************************/

Define_Module(RaGen);


void RaGen::initialize()
{
    sendTimer = new cMessage("RA Send Timer");
    RaInterval = (double)par("RaInterval");
    Log(Notice) << "First RA to be transmitted in " << RaInterval << LogEnd;
    scheduleAt(RaInterval, sendTimer);
}

void RaGen::handleMessage(cMessage *msg)
{
    if (msg==sendTimer) {
	sendRA();
	scheduleAt(simTime()+(double)(RaInterval), sendTimer);
	return;
    }

    Log(Debug) << "Message " << msg->fullName() << " received." << endl;
    delete msg;
}

void RaGen::sendRA() 
{
    IPv6Ra * msg = new IPv6Ra("");
    Log(Notice) << "Transmitting RA message." << LogEnd;
    send (msg, "raOut");
}
