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
}

void IPv6Dispatch::dispatchMessage(cMessage *msg)
{
  /// @TODO
  if (handleTraffic) {
    send(msg, "genOut", 0); // send to generator directly
    Log(Debug) << "Message " << msg->fullName() << " received and dispatched to ??? gate." << endl;
  } else {
    Log(Debug) << "Message " << msg->fullName() << " dropped, traffic is not supported right now." << LogEnd;

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

    if (!strcmp(gate->fullName(), "eventIn")) {
        handleMihMessage(msg);
        return;
    }
    
    if (!strcmp(gate->fullName(),"ipIn")) {
      dispatchMessage(msg);
    } else {
      if (handleTraffic) { 
        send(msg, "ipOut", 0);
        Log(Debug) << "Message " << msg->fullName() << " received and dispatched to ipOut gate." << endl;
      } else {
        Log(Debug) << "Message " << msg->fullName() << " dropped, traffic is not supported right now." << LogEnd;
      }
    }
}
