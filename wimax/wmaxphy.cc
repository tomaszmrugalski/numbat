
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
#include "mih_m.h"
#include "logger.h"
#include "ssinfo.h"

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
    SendQueue.clear();
    SendQueue.setName("SendQueue");

    this->UlMap = 0;
    this->DlMap = 0;
    this->FrameCnt = 0;
}

void WMaxPhyBS::handleMessage(cMessage *msg)
{   
    cGate * gate = msg->getArrivalGate();
    // uplink message
    Log(Debug) << "Message " << msg->getFullName() << " received on gate: " << gate->getFullName() << ", id=" 
	       << gate->getId() << LogEnd;
    //checks if message is UL - i is the string to compare with the incoming gate
  
    if (!strcmp("rfIn",gate->getFullName())) {
	// deliver message immediately
	send(msg,"phyOut");
	return;
    }

    // downlink message
    if ( dynamic_cast<WMaxMsgDlMap*>(msg) ) {
	this->DlMap = check_and_cast<WMaxMsgDlMap*>(msg);
	Log(Debug) << "DL-MAP ready to send." << LogEnd;
	return;
    }
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	this->UlMap = check_and_cast<WMaxMsgUlMap*>(msg);
	Log(Debug) << "UL-MAP ready to send." << LogEnd;
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
    Log(Debug) << "Frame number: " << FrameCnt << ", " << SendQueue.length() << " message(s) to send. " << LogEnd;

    if (this->DlMap) {
        Log(Debug) << "Frame is DL-MAP" << LogEnd;
        send(DlMap,"rfOut");
        this->DlMap = 0;
        Log(Debug) << "Frame DL-MAP is sent" << LogEnd;
    } else {
        Log(Debug) << "DL-MAP not set. Send skipped." << LogEnd;
    }
    if (this->UlMap) {
        send(UlMap,"rfOut");
        this->UlMap = 0;
    } else {
        Log(Debug) << "UL-MAP not set. Send skipped" << LogEnd;
    }
    
    while (!SendQueue.empty()) {
        Log(Debug) << "!SendQueue.empty()" << LogEnd;
        cMessage * msg = (cMessage*)SendQueue.pop();
        send(msg, "rfOut");
        Log(Debug) << "send msg while queue is not empty" << LogEnd;
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
    SendQueue.setName("SendQueue");
}

void WMaxPhySS::beginFrame()
{
    Log(Debug) << "WMaxPhySS::beginFrame_start" << LogEnd;
    while (!SendQueue.empty()) {
        cMessage * msg = (cMessage*)SendQueue.pop();
        send(msg, "rfOut");

        if (dynamic_cast<WMaxMsgHOIND*>(msg)) {
            Log(Notice) << "MIH event: Notifying other layers: HO-IND was actually transmitted." << LogEnd;
            ssInfo * info = dynamic_cast<ssInfo*>(getParentModule()->getSubmodule("ssInfo"));
            MihEvent_HandoverEnd * x = new MihEvent_HandoverEnd();
            info->sendEvent(x);
        }
    }
    Log(Debug) << "WMaxPhySS::beginFrame_stop" << LogEnd;
}

void WMaxPhySS::handleMessage(cMessage *msg)
{
    Log(Debug) << "WMaxPhySS::handleMessage_start" << LogEnd;
    static int licz ; // test
    cGate * gate = msg->getArrivalGate();
    // uplink message
    Log(Debug) << "Message " << msg->getFullName() << " received on gate: " << gate->getFullName() << ", id=" 
               << gate->getId() << LogEnd;
    if (!strcmp(gate->getFullName(),"rfIn")) {
        // deliver message immediately
        send(msg, "phyOut");
        licz=licz+1 ; //test
        Log(Debug) << "WMaxPhySS::handleMessage_stop" << LogEnd;
        return;
    }

    if (dynamic_cast<WMaxPhyDummyFrameStart*>(msg)) {
        beginFrame();
        delete msg;
        Log(Debug) << "WMaxPhySS::handleMessage_stop" << LogEnd;
        return;
    }

    // downlink message
    SendQueue.insert(msg);
    Log(Debug) << "WMaxPhySS::handleMessage_stop" << LogEnd;    
}
