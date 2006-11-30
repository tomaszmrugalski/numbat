/**
 * @file   wmaxmac.c
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Mon Nov 20 00:26:38 2006
 * 
 * @brief  WMaxMAC implementation
 * 
 * 
 */

#include <omnetpp.h>
#include "wmaxmac.h"
#include "wmaxmsg_m.h"

Define_Module(WMaxMacBS);



void WMaxMacBS::initialize()
{
    TxStart = new cMessage("TxStart");
    scheduleAt(0.0, TxStart);
}

void WMaxMacBS::handleMessage(cMessage *msg)
{
    if (msg==TxStart) {
	schedule();
	scheduleAt(0.005, TxStart);
    }
}

void WMaxMacBS::schedule()
{
    /// @todo - write some scheduling module

    WMaxMsgDlMap * dlmap = new WMaxMsgDlMap();
    ev << "Generating DL-MAP" << endl;
    send(dlmap, "phyOut");

    WMaxMsgUlMap * ulmap = new WMaxMsgUlMap();
    ev << "Generating UL-MAP" << endl;
    send(ulmap, "phyOut");

    // trigger PHY to start frame
    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    ev << "Generating FrameStart trigger for PHY" << endl;
    send(frameStart, "phyOut");
}
