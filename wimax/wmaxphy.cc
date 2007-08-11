
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
#include "logger.h"

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
    cGate * gate = msg->arrivalGate();
    // uplink message
    Log(Debug) << "Message " << msg->fullName() << " received on gate: " << gate->fullName() << ", id=" 
	       << gate->id() << LogEnd;
    //checks if message is UL - i is the string to compare with the incoming gate
  
    if (!strcmp("rfIn",gate->fullName())) {
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
	send(DlMap,"rfOut");
	this->DlMap = 0;
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
    SendQueue.setName("SendQueue");
}

void WMaxPhySS::beginFrame()
{
    while (!SendQueue.empty()) {
        cMessage * msg = (cMessage*)SendQueue.pop();
        send(msg, "rfOut");

        if (dynamic_cast<WMaxMsgHOIND*>(msg)) {
            Log(Notice) << "HO-IND was actually transmitted." << LogEnd;
            cModule * ss = parentModule();
            char buf[80];
            sprintf(buf, "WMaxCtrlSS[%d]", ss->index());
            cModule * ctrlSS = ss->submodule("ssMac")->submodule(buf);
            MihEvent_HandoverEnd * x = new MihEvent_HandoverEnd();
            sendDirect(x, 0.0, ctrlSS, "eventIn");
        }
    }
}

void WMaxPhySS::handleMessage(cMessage *msg)
{
    static int licz ; // test
    cGate * gate = msg->arrivalGate();
    // uplink message
    Log(Debug) << "Message " << msg->fullName() << " received on gate: " << gate->fullName() << ", id=" 
               << gate->id() << LogEnd;
    if (!strcmp(gate->fullName(),"rfIn")) {
        // deliver message immediately
        send(msg, "phyOut");
        licz=licz+1 ; //test
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
