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
#include "mih_m.h"
#include "logger.h"
#include "ssinfo.h"

using namespace std;

/********************************************************************************/
/*** Router Advertisement Receiver **********************************************/
/********************************************************************************/

Define_Module(RaRcv);

void RaRcv::initialize()
{
    RaRcvCnt = 0;

    // register for MIH Events
    cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
    if (tmp) {
	// SS-side
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);
	info->addEventListener(this);
    }

    updateString();
}

void RaRcv::handleMessage(cMessage *msg)
{
    if (dynamic_cast<IPv6Ra*>(msg)) {
	if (!RaRcvCnt) {
	    ssInfo * info = dynamic_cast<ssInfo*>(parentModule()->parentModule()->submodule("ssInfo"));
	    Log(Notice) << "Notifying other layers: IPv6 routing configured." << LogEnd;
	    info->sendEvent(new MihEvent_L3RoutingConfigured());
	}
	
	RaRcvCnt++;
	updateString();
    } 
    if (dynamic_cast<MihEvent_HandoverEnd*>(msg)) {
	RaRcvCnt = 0;
	updateString();
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
    Log(Notice) << "RA to be transmitted in " << RaInterval << " secs." << LogEnd;
    scheduleAt(RaInterval, sendTimer);
}

void RaGen::handleMessage(cMessage *msg)
{
    if (msg==sendTimer) {
	sendRA();
	scheduleAt(simTime()+(double)(RaInterval), sendTimer);
	return;
    }

    Log(Debug) << "Message " << msg->fullName() << " received." << LogEnd;
    delete msg;
}

void RaGen::sendRA() 
{
    IPv6Ra * msg = new IPv6Ra("RA");
    Log(Debug) << "Transmitting RA message." << LogEnd;
    send (msg, "raOut");
}
