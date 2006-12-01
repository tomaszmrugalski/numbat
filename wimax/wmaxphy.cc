
/**
 * @file   wmaxphy.cc
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Sat Nov 18 18:52:36 2006
 * 
 * @brief  WMaxPHY implementation
 * 
 * 
 */

#include <omnetpp.h>
#include "wmaxphy.h"
#include "wmaxmsg_m.h"

/********************************************************************************/
/*** WMax PHY BS ****************************************************************/
/********************************************************************************/

Define_Module(WMaxPhyBS);

WMaxPhyBS::WMaxPhyBS()
{

}

WMaxPhyBS::~WMaxPhyBS()
{

}

void WMaxPhyBS::initialize()
{
    this->UlMap = 0;
    this->DlMap = 0;
    this->FrameCnt = 0;
}

void WMaxPhyBS::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();
    // uplink message
    ev << fullName() << ":Message " << msg->fullName() << " received on gate: " << gate->fullName() << ", id=" << gate->id() << endl;
    if (!strcmp(gate->fullName(),"rfIn")) {
	// deliver message immediately
	send(msg, "phyOut");
	return;
    }

    // downlink message
    if ( dynamic_cast<WMaxMsgDlMap*>(msg) ) {
	this->DlMap = check_and_cast<WMaxMsgDlMap*>(msg);
	ev << "DL-MAP ready to send." << endl;
	return;
    }
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	this->UlMap = check_and_cast<WMaxMsgUlMap*>(msg);
	ev << "UL-MAP ready to send." << endl;
	return;
    }
    if (dynamic_cast<WMaxPhyDummyFrameStart*>(msg)) {
	beginFrame();
	delete msg;
	return;
    }

    // store message for sending
    SendQueue.insert(msg);
}

void WMaxPhyBS::beginFrame()
{
    FrameCnt++;
    ev << fullName() << ": Frame number: " << FrameCnt << ", " << SendQueue.length() << " message(s) to send. " << endl;

    if (this->DlMap) {
	send(DlMap, "rfOut");
	this->DlMap = 0;
    } else {
	ev << "DL-MAP not set. Send skipped" << endl;
    }
    if (this->UlMap) {
	send(UlMap, "rfOut");
	this->UlMap = 0;
    } else {
	ev << "UL-MAP not set. Send skipped" << endl;
    }

    while (!SendQueue.empty()) {
	cMessage * msg = (cMessage*)SendQueue.pop();
	send(msg, "rfOut");
    }
}

/********************************************************************************/
/*** WMax PHY SS ****************************************************************/
/********************************************************************************/

Define_Module(WMaxPhySS);

WMaxPhySS::WMaxPhySS()
{

}

WMaxPhySS::~WMaxPhySS()
{

}

void WMaxPhySS::initialize()
{
    SendQueue.clear();
}

void WMaxPhySS::beginFrame()
{
    while (!SendQueue.empty()) {
	cMessage * msg = (cMessage*)SendQueue.pop();
	send(msg, "rfOut");
    }
}

void WMaxPhySS::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();

    // uplink message
    ev << fullName() << ":Message " << msg->fullName() << " received on gate: " << gate->fullName() << ", id=" << gate->id() << endl;
    if (!strcmp(gate->fullName(),"rfIn")) {
	// deliver message immediately
	send(msg, "phyOut");
	return;
    }

    if (dynamic_cast<WMaxPhyDummyFrameStart*>(msg)) {
	beginFrame();
	delete msg;
	return;
    }

    // downlink message
    SendQueue.insert(msg);
}
