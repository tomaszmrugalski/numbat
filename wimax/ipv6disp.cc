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

using namespace std;

/********************************************************************************/
/*** IPv6 Dispatch **************************************************************/
/********************************************************************************/

Define_Module(IPv6Dispatch);


void IPv6Dispatch::initialize()
{
}

void IPv6Dispatch::dispatchMessage(cMessage *msg)
{
  /// @TODO

  send(msg, "genOut", 0); // send to generator directly
}

void IPv6Dispatch::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();

    if (!strcmp(gate->fullName(),"ipIn")) {
      dispatchMessage(msg);
    } else {
      send(msg, "ipOut", 0);
      Log(Debug) << "Message " << msg->fullName() << " received and dispatched to ipOut gate." << endl;
    }
}
