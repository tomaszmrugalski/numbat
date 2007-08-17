/**
 * @file    ipv6disp.h
 * @author  Tomasz Mrugalski <thomson@klub.com.pl>
 * @date    Tue Aug  7 12:56:47 CET 2007
 *
 * @brief  DHCPv6 server/client
 * 
 * Published under GNU GPLv2 or later 
 */

#include <omnetpp.h>
#include <string>
#include "ipv6disp.h"
#include "logger.h"
#include "hoinfo.h"
#include "ssinfo.h"
#include "wmaxmsg_m.h"

using namespace std;

/********************************************************************************/
/*** IPv6 Dispatch **************************************************************/
/********************************************************************************/

Define_Module(IPv6Dispatch);

void IPv6Dispatch::initialize()
{
  handleTraffic = false;
  updateString();
  SentBytesPers=0;
  RcvdBytesPers=0;
  SentBytesVector.setName("Sent B/s");
  RcvdBytesVector.setName("Received B/s");
  timer = new cMessage();
  scheduleAt(0.1, timer);

}




void IPv6Dispatch::dispatchMessage(cMessage *msg)
{
    /// @TODO
    if (handleTraffic) {
	send(msg, "genOut", 0); // send to generator directly
	Log(Debug) << "Message " << msg->fullName() << " received and dispatched to ??? gate." << endl;
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
    Log(Debug) << "MIH message received: disabling traffic." << LogEnd;
    handleTraffic = false;
  }

  if (dynamic_cast<MihEvent_EntryEnd*>(msg) ||
      dynamic_cast<MihEvent_HandoverStart*>(msg) ||
      dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
    Log(Debug) << "MIH message received: enabling traffic." << LogEnd;
    handleTraffic = true;
  }

  /* TBD */
  if (dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
      cModule * tmp0 = parentModule()->parentModule();
      cModule * tmp1 = tmp0->submodule("ssInfo");
      ssInfo  * tmp2 = dynamic_cast<ssInfo*>(tmp1);
      HoInfo_t * hoInfo = &tmp2->hoInfo;

      double ipDelay = 1.0; 
      if (hoInfo->ip.skipDad)
	  ipDelay = 0;

      double dhcpDelay = 0.010; /* solicit-adv/reply = ~est. 10ms */
      if (!hoInfo->dhcp.skipInitialDelay)
	  dhcpDelay += uniform(0, 1.0); /* 0..1 s */

      if (!hoInfo->dhcp.rapidCommit) {

	  if (hoInfo->dhcp.pref255) 
	      dhcpDelay += 0.010 /* REQUEST/REPLY wait */;
	  else
	      dhcpDelay += 1.000 /* ADV wait */;
      } 

      cMessage * resume = new MihEvent_EntryEnd();
      scheduleAt(simTime() + dhcpDelay + ipDelay, resume);
      Log(Notice) << "IPv6 layer delay: ipDelay=" << ipDelay << ", dhcpDelay=" << dhcpDelay << LogEnd;

      handleTraffic = false;
  }
  /* TBD */

  updateString();
}

void IPv6Dispatch::updateString()
{
  char buf[80];
  sprintf(buf, "%s", handleTraffic?"trf":"no trf");
  if (ev.isGUI())
    displayString().setTagArg("t", 0, buf);
}

void IPv6Dispatch::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();
    
    if (msg==timer)
    {    writeStat();
         SentBytesPers=0;
         RcvdBytesPers=0;
                         return; 
                }
     

    if (!gate || !strcmp(gate->fullName(), "eventIn")) {  
        handleMihMessage(msg);
        return;
    }
    
    if (!strcmp(gate->fullName(),"ipIn")) {
      RcvdBytesPers += msg->length();                                     
      dispatchMessage(msg);
    } else {
      if (handleTraffic) { 
        SentBytesPers += msg->length();                 
        send(msg, "ipOut", 0);
        Log(Debug) << "Message " << msg->fullName() << " received and dispatched to ipOut gate." << endl;
      } else {
        Log(Debug) << "Message " << msg->fullName() << " dropped, traffic is not supported right now." << LogEnd;
	delete msg;
      }
    }
    
    
    
}


void IPv6Dispatch::writeStat()
{   SentBytesPers = SentBytesPers/0.05;
    RcvdBytesPers = RcvdBytesPers/0.05;
    SentBytesVector.record(SentBytesPers);
    RcvdBytesVector.record(RcvdBytesPers);
        timer = new cMessage();
        scheduleAt(simTime()+0.05, timer);
     }
