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
    addrConfigured = false;
    locationUpdated = false;
    SentBytesPers=0;
    RcvdBytesPers=0;
    DroppedMsgs = 0;
    SentBytesVector.setName("Sent B/s");
    RcvdBytesVector.setName("Received B/s");
    DroppedMsgsVector.setName("Dropped msgs");
    timer = new cMessage();
    scheduleAt(0.1, timer);
    BS = false;
    
    cModule * tmp0 = getParentModule();
    if (!strcmp(tmp0->getFullName(), "bsIPv6")) {
	BS = true;
	handleTraffic = true;
	routingConfigured = true;
	addrConfigured = true;
	locationUpdated = true;
    }

    // register for MIH events
    assert(getParentModule());
    assert(getParentModule()->getParentModule());
    cModule * tmp = getParentModule()->getParentModule()->getSubmodule("ssInfo");
    if (tmp) {
	// SS-side
	assert(tmp);
	ssInfo * info = dynamic_cast<ssInfo*>(tmp);
	assert(info);
	info->addEventListener(this);
    }

    // add number prefix to the module name
    cModule * ss = getParentModule()->getParentModule();
    char buf[80];
    sprintf(buf, "%s[%d]", getFullName(), ss->getIndex());
    setName(buf);

    updateString();
}

void IPv6Dispatch::dispatchMessage(cMessage *msg)
{
    if (dynamic_cast<IPv6Ra*>(msg)) {
	if (handleTraffic) {
	  send(msg, "raOut", -1); //was: 0, changed to -1 (MiM)
	    return;
	} else {
	    Log(Warning) << "RA received, but traffic is not supported right now. Message dropped." << LogEnd;
	    DroppedMsgs++;
	    delete msg;
	    return;
	}
    }

    if (dynamic_cast<DHCPv6Solicit*>(msg) ||
	dynamic_cast<DHCPv6Advertise*>(msg) ||
	dynamic_cast<DHCPv6Request*>(msg) ||
	dynamic_cast<DHCPv6Reply*>(msg) ||
	dynamic_cast<DHCPv6Confirm*>(msg)) {
	Log(Debug) << "DHCPv6 message " << msg->getFullName() << " received." << LogEnd;
	send(msg, "dhcpOut", -1);  //was 0, changed to -1 (MiM)
	return;
    };

    if (handleTraffic) {
      send(msg, "genOut"/*, 0*/); // send to generator directly
      //genOut is scalar gate, 0 should be removed or replaced by -1 (MiM)
	Log(Debug) << "Message " << msg->getFullName() << " received and sent to upper layer." << endl;
	return;
    } else {
	Log(Debug) << "Message " << msg->getFullName() << " dropped, traffic is not supported right now." << LogEnd;
	DroppedMsgs++;
	delete msg;
	return;
    }

    opp_error("Message not handled by IPv6dispatch: %s", msg->getFullName());
}

void IPv6Dispatch::handleMihMessage(cMessage *msg)
{
    bool changed = false;
    
    if (dynamic_cast<MihEvent_EntryStart*>(msg) ||
	dynamic_cast<MihEvent_HandoverEnd*>(msg) ||
	dynamic_cast<MihEvent_ReentryStart*>(msg)) {
	Log(Info) << "MIH L2 message received: disabling traffic." << LogEnd;
	handleTraffic = false;
	
	changed = true;
    }
    
    if (dynamic_cast<MihEvent_EntryEnd*>(msg) ||
	dynamic_cast<MihEvent_HandoverStart*>(msg) ||
	dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
	Log(Info) << "MIH L2 message received: enabling traffic." << LogEnd;
	handleTraffic = true;

	changed = true;
    }
  
  if (dynamic_cast<MihEvent_EntryEnd*>(msg) ||
      dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
      Log(Info) << "(Re)entry finished, starting IPv6 reconfiguration." << LogEnd;
      routingConfigured = false;
      addrConfigured    = false;
      locationUpdated   = false;

      changed = true;
  }

  if (dynamic_cast<MihEvent_L3AddrConfigured*>(msg)) {
      addrConfigured = true;

      changed = true;
  }
  
  if (dynamic_cast<MihEvent_L3RoutingConfigured*>(msg)) {
      routingConfigured = true;

      changed = true;
  }
  
  if (dynamic_cast<MihEvent_L3LocationUpdated*>(msg)) {
      locationUpdated = true;
      
      changed = true;
  }

  if (changed) {
      updateString();
  }
}

void IPv6Dispatch::updateString()
{
    if (BS)
	return;
    char buf[80];
    sprintf(buf, "%s\n%s\n%s\n%s", handleTraffic?"trf":"no trf", 
	    routingConfigured?"rt":"no rt", 
	    addrConfigured?"addr":"no addr", 
	    locationUpdated?"loc upd":"no loc upd");
    if (ev.isGUI())
	getDisplayString().setTagArg("t", 0, buf);
    
  // getDisplayString().setTagArg("i",1,"yellow");
}

void IPv6Dispatch::handleMessage(cMessage *msg)
{
    cGate * gate = msg->getArrivalGate();
    
    if (msg==timer)
    {    
	writeStat();
	SentBytesPers=0;
	RcvdBytesPers=0;
	delete msg;
	return; 
    }

    if (!gate || !strcmp(gate->getFullName(), "eventIn")) {  
        handleMihMessage(msg);
	delete msg;
        return;
    }

    IPv6 * ip = dynamic_cast<IPv6*>(msg);
    if (!strcmp(gate->getFullName(), "dhcpIn")) {
	if (ip->getDhcpv6Relay() && BS)
	{
	    // this is relay, route it via backbone
	    Log(Info) << "Forwarding outgoing relay message (src=" 
		      << ip->getSrcIP() << ",dst=" << ip->getDstIP()
		      << ")" << LogEnd;
	    send (msg, "genOut"/*, 0*/); //MiM
	    return;
	} 

	// this is normal message, route it to SS/BS via radio
	Log(Debug) << "Forwarding outgoing DHCPv6 message." << LogEnd;
	send(msg, "ipOut",-1);//was 0, changed to -1 (MiM)
	return;
    }

    if (!strcmp(gate->getFullName(), "genIn") && ip && ip->getDhcpv6Relay()) {
	Log(Info) << "Forwarding incoming DHCPv6 relay message (src=" 
		  << ip->getSrcIP() << ",dst=" << ip->getDstIP() << ")" << LogEnd;
	send(msg, "dhcpOut", -1); //was 0, changed to -1 (MiM)
	return;
    }
    
    // relay RAs all the time
    if (!strcmp(gate->getFullName(),"raIn"))
    {
      send(msg, "ipOut"/*, -1*//*0*/); //ipOut is scalar gate, use -1 instead of 0 or just delete the gateIndex (== the last argument) (MiM)
	return;
    }

    if (!strcmp(gate->getFullName(),"ipIn")) {
	// handle IPv6 data from L2 at any time
	//RcvdBytesPers += msg->getBitLength(); 
      RcvdBytesPers += (check_and_cast<cPacket *>(msg))->getBitLength(); //MiM
                                    
	dispatchMessage(msg);
	return;
    } 

    if (ip && ip->getBindingUpdate()) { // accept binding update at any time
      send(msg, "ipOut", -1); //was 0, changed to -1 (MiM)
	return;
    }

    if (handleTraffic) { 
	if (routingConfigured) {
	  //SentBytesPers += msg->getBitLength(); 
	  SentBytesPers += (check_and_cast<cPacket *>(msg))->getBitLength();//MiM 
	  send(msg, "ipOut", -1); //MiM -1
	    Log(Debug) << "Message (" << msg->getFullName() << ") received and dispatched to ipOut gate." << LogEnd;
	} else {
	    Log(Notice) << "Message (" << msg->getFullName() << ") dropped: no routing configured." << LogEnd;
	    DroppedMsgs++;
	    delete msg;
	}
    } else {
	Log(Notice) << "Message (" << msg->getFullName() << ") dropped, traffic is not supported right now." << LogEnd;
	DroppedMsgs++;
	delete msg;
    }
}

void IPv6Dispatch::writeStat()
{   SentBytesPers = (long int)(SentBytesPers/0.05);
    RcvdBytesPers = (long int)(RcvdBytesPers/0.05);
    SentBytesVector.record(SentBytesPers);
    RcvdBytesVector.record(RcvdBytesPers);
    DroppedMsgsVector.record(DroppedMsgs);

    timer = new cMessage();
    scheduleAt(simTime()+0.05, timer);
}
