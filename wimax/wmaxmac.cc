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
    WMaxMsgDlMap * dlmap = new WMaxMsgDlMap();
    send(dlmap, "phyOut");

    WMaxMsgUlMap * ulmap = new WMaxMsgUlMap();
    send(ulmap, "phyOut");

}
