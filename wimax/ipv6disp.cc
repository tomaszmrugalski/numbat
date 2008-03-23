/**
 * @file    ipv6disp.h
 * @author  Tomasz Mrugalski <thomson@klub.com.pl>
 * @date    Tue Aug  7 12:56:47 CET 2007
 *
 * @brief  DHCPv6 server/client
 * 
 * Published under GNU GPLv2 or later 
 */

#include <assert.h>
#include <omnetpp.h>
#include <string>
#include "ipv6disp.h"
#include "logger.h"
#include "hoinfo.h"
#include "ssinfo.h"
#include "mih_m.h"
#include "ipv6msg_m.h"

using namespace std;

/********************************************************************************/
/*** IPv6 Dispatch **************************************************************/
/********************************************************************************/

Define_Module(IPv6Dispatch);

void IPv6Dispatch::initialize()
{
    handleTraffic = false; // L2 is not ready
    routingConfigured = false; // IPv6 routing is not configured
    SentBytesPers=0;
    RcvdBytesPers=0;
    SentBytesVector.setName("Sent B/s");
    RcvdBytesVector.setName("Received B/s");
    timer = new cMessage();
    scheduleAt(0.1, timer);
    BS = false;
    
    cModule * tmp0 = parentModule();
    if (!strcmp(tmp0->fullName(), "bsIPv6")) {
	BS = true;
	handleTraffic = true;
	routingConfigured = true;
    }


    // register for MIH events
    assert(parentModule());
    assert(parentModule()->parentModule());
    cModule * tmp = parentModule()->parentModule()->submodule("ssInfo");
    if (tmp) {
	// SS-side
	assert(tmp);
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);
	assert(info);
	info->addEventListener(this);
    }

    updateString();
}

void IPv6Dispatch::dispatchMessage(cMessage *msg)
{
    if (dynamic_cast<IPv6Ra*>(msg)) {
	Log(Debug) << "RA received." << LogEnd;
	send(msg, "raOut", 0);
	routingConfigured = true;
	updateString();

	return;
    }

    if (dynamic_cast<DHCPv6Solicit*>(msg) ||
	dynamic_cast<DHCPv6Advertise*>(msg) ||
	dynamic_cast<DHCPv6Request*>(msg) ||
	dynamic_cast<DHCPv6Reply*>(msg) ||
	dynamic_cast<DHCPv6Confirm*>(msg)) {
	Log(Debug) << "DHCPv6 message " << msg->fullName() << " received." << LogEnd;
	send(msg, "dhcpOut", 0);
	return;
    };

    /// @TODO - MIPv6

    if (handleTraffic) {
	send(msg, "genOut", 0); // send to generator directly
	Log(Debug) << "Message " << msg->fullName() << " received and sent to upper layer." << endl;
    } else {
	Log(Debug) << "Message " << msg->fullName() << " dropped, traffic is not supported right now." << LogEnd;
	delete msg;
    }
}

void IPv6Dispatch::handleMihMessage(cMessage *msg)
{
  if (dynamic_cast<MihEvent_EntryStart*>(msg) ||
      dynamic_cast<MihEvent_HandoverEnd*>(msg) ||
      dynamic_cast<MihEvent_ReentryStart*>(msg)) {
    Log(Info) << "MIH message received: disabling traffic." << LogEnd;
    handleTraffic = false;
    if (dynamic_cast<MihEvent_HandoverEnd*>(msg)) {
        IPv6HoStart = simTime();
	return;
    }
  }

  if (dynamic_cast<MihEvent_EntryEnd*>(msg) ||
      dynamic_cast<MihEvent_HandoverStart*>(msg) ||
      dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
      Log(Info) << "MIH message received: enabling traffic." << LogEnd;
      handleTraffic = true;
      return;
  }
  
  if (dynamic_cast<MihEvent_EntryEnd*>(msg) ||
      dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
      Log(Info) << "(Re)entry finished, starting IPv6 reconfiguration." << LogEnd;
      ipv6ReconfigureStart();
      return;
  }

}

/** 
 * this method is called after L2 handover is complete
 * i.e. when IPv6 handover begins
 * 
 */
void IPv6Dispatch::ipv6ReconfigureStart()
{
    // TBD: GET_STATS here
    Log(Notice) << "L2 handover completed, starting IPv6 reconfiguration." << LogEnd;
    handleTraffic = false;
    routingConfigured = false;
    updateString();
}


/** 
 * this method is called when IPv6 handover is complete
 * 
 */
void IPv6Dispatch::ipv6ReconfigureEnd()
{
    // TBD: GET_STATS here
    Log(Notice) << "IPv6 reconfiguration complete." << LogEnd;
    IPv6HoFinish = simTime();
    IPv6HoTime.collect(IPv6HoFinish - IPv6HoStart);
    updateString();
}

void IPv6Dispatch::updateString()
{
  char buf[80];
  sprintf(buf, "%s/%s", handleTraffic?"trf":"no trf", routingConfigured?"rt":"no rt");
  if (ev.isGUI())
    displayString().setTagArg("t", 0, buf);
}

void IPv6Dispatch::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();
    
    if (msg==timer)
    {    
	writeStat();
	SentBytesPers=0;
	RcvdBytesPers=0;
	delete msg;
	return; 
    }

    if (!gate || !strcmp(gate->fullName(), "eventIn")) {  
        handleMihMessage(msg);
        return;
    }
    
    // relay RAs all the time
    if (!strcmp(gate->fullName(),"raIn") ||
	!strcmp(gate->fullName(), "dhcpIn")) {
	send(msg, "ipOut", 0);
	return;
    }

    if (!strcmp(gate->fullName(),"ipIn")) {
	// handle IPv6 data from L2 at any time
	RcvdBytesPers += msg->length();                                     
	dispatchMessage(msg);
	return;
    } else {
	if (handleTraffic) { 
	    if (routingConfigured) {
		SentBytesPers += msg->length();                 
		send(msg, "ipOut", 0);
		Log(Debug) << "Message " << msg->fullName() << " received and dispatched to ipOut gate." << LogEnd;
	    } else {
		Log(Notice) << "Message " << msg->fullName() << " dropped: no routing configured." << LogEnd;
		delete msg;
	    }
	} else {
	    Log(Notice) << "Message " << msg->fullName() << " dropped, traffic is not supported right now." << LogEnd;
	    delete msg;
	}
    }
}

void IPv6Dispatch::writeStat()
{   SentBytesPers = (long int)(SentBytesPers/0.05);
    RcvdBytesPers = (long int)(RcvdBytesPers/0.05);
    SentBytesVector.record(SentBytesPers);
    RcvdBytesVector.record(RcvdBytesPers);

    timer = new cMessage();
    scheduleAt(simTime()+0.05, timer);
}
