
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
    TxStart = new cMessage("TxStart");
    ev << "FrameLength=" << par("FrameLength") << endl;
    this->FrameCnt = 0;
    this->UlMap = 0;
    this->DlMap = 0;
}

void WMaxPhyBS::handleMessage(cMessage *msg)
{
    if ( dynamic_cast<WMaxMsgDlMap*>(msg) ) {
	this->DlMap = check_and_cast<WMaxMsgDlMap*>(msg);
	ev << "DL-MAP ready to send." << endl;
	return;
    }
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	this->UlMap = check_and_cast<WMaxMsgUlMap*>(msg);
	ev << "UL-MAP ready to send." << endl;

	if (this->FrameCnt==0) {
	    // this is first frame (initiate transmission)
	    scheduleAt(0.0, TxStart);
	}

	return;
    }
    if (msg==TxStart) {
	beginFrame();
	return;
    }

    ev << "Received message: " << *msg << endl;
    delete msg;
}

void WMaxPhyBS::beginFrame()
{
    scheduleAt(par("FrameLength"), TxStart);

    FrameCnt++;
    ev << "Frame number: " << FrameCnt << endl;

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

}

void WMaxPhySS::handleMessage(cMessage *msg)
{
    //@todo - if this message is received via RF gate,
    // then deliver it immediately.
    ev << "Received message: " << *msg << endl;
    delete msg;
}
