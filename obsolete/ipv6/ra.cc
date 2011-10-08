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

const IPv6Addr allNodesMulticast = IPv6Addr("ff02::1", true);

/********************************************************************************/
/*** Router Advertisement Receiver **********************************************/
/********************************************************************************/

Define_Module(RaRcv);

void RaRcv::initialize()
{
    RaRcvCnt = 0;

    // register for MIH Events
    cModule * tmp = getParentModule()->getParentModule()->getSubmodule("ssInfo");
    if (tmp) {
	// SS-side
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);
	info->addEventListener(this);
    }

    // add number prefix to the module name
    cModule * ss = getParentModule()->getParentModule();
    char buf[80];
    sprintf(buf, "%s%d", getFullName(), ss->getIndex());
    setName(buf);

    updateString();
}

void RaRcv::handleMessage(cMessage *msg)
{
    if (dynamic_cast<IPv6Ra*>(msg)) {
	if (!RaRcvCnt) {
	    ssInfo * info = dynamic_cast<ssInfo*>(getParentModule()->getParentModule()->getSubmodule("ssInfo"));
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
    getDisplayString().setTagArg("t", 0, buf);

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

    // add number prefix to the module name
    cModule * ss = getParentModule()->getParentModule();
    char buf[80];
    sprintf(buf, "%s%d", getFullName(), ss->getIndex());
    setName(buf);
}

void RaGen::handleMessage(cMessage *msg)
{
    if (msg==sendTimer) {
	sendRA();
	scheduleAt(simTime()+(double)(RaInterval), sendTimer);
	return;
    }

    Log(Debug) << "Message " << msg->getFullName() << " received." << LogEnd;
    delete msg;
}

void RaGen::sendRA() 
{
    IPv6Ra * msg = new IPv6Ra("RA");
    msg->setByteLength(100);
    msg->setDstIP(allNodesMulticast);
    Log(Debug) << "Transmitting RA message." << LogEnd;
    send (msg, "raOut");
}
