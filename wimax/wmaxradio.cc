/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2007-06-25 01:27:46+0200
 * 
 * @brief  WMax Radio connector (used to connect multiple SSes to one BS)
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>
#include <string>
#include "wmaxradio.h"
#include "logger.h"

/********************************************************************************/
/*** IPv6 Node ******************************************************************/
/********************************************************************************/

Define_Module(WMaxRadio);
using namespace std;
void WMaxRadio::initialize()
{
}

void WMaxRadio::handleMessage(cMessage *msg)
{
    Log(Debug) << "WMaxRadio::handleMessage_start" << LogEnd;
    // radioOut, radioIn, phyOut, phyIn
    cGate * g = msg->getArrivalGate();
    if (!strcmp(g->getFullName(),"phyIn")) {
        // Broadcast transmission (BS->all SSes)
        g = gate("radioIn", 0);
        for (int i=0; i<g->size(); i++) {
            g = gate("radioOut", i);
            if (g->isConnected()) {
            cMessage * copy = (cMessage*)msg->dup();
            if (msg->getControlInfo()) {
                cPolymorphic * hdr = msg->getControlInfo();
                cPolymorphic * hdr2 = hdr->dup();
                copy->setControlInfo(hdr2);
            }
            send(copy, "radioOut", i);
            }
        }
        delete msg;
        Log(Debug) << "WMaxRadio::handleMessage_stop1" << LogEnd;
        return;
    }

    // unicast transmission (SS -> BS)
    send(msg, "phyOut");	
    Log(Debug) << "WMaxRadio::handleMessage_stop2" << LogEnd;
}

void WMaxRadio::connect(cModule * ss)
{
    Log(Debug) << "Connecting SS " << ss->getFullName() << " to this radio." << LogEnd;
    int maxSS = gate("radioOut",0)->size();
    
    cModule * bs = getParentModule();

    for (int i=0; i < maxSS; i++) {
        cGate * g = gate("radioOut", i);
        Log(Debug) << "Checking gate: radioOut[" << i << "]: " << (g->isConnected()?"CONNECTED":"NOT CONN") << LogEnd;
        if (!g->isConnected()) {

            // BS->SS
            cGate * bsGate = bs->gate("out",i);
            bsGate->disconnect();
			// radioOut --> BS out
            g->connectTo(bsGate);
			// BS out --> SS radioIn
            bsGate->connectTo(ss->gate("in"));

            // SS->BS
            bsGate = bs->gate("in", i);
			// radioIn <-- BS in
            bsGate->disconnect();
            g = gate("radioIn", i);
            ss->gate("out")->disconnect();
            ss->gate("out")->connectTo(bsGate);
            bsGate->connectTo(g);
            Log(Debug) << "WMaxRadio::connect_stop1" << LogEnd;
            return;
        }
    }
    Log(Debug) << "WMaxRadio::connect_stop2" << LogEnd;
}

void WMaxRadio::disconnect(cModule * ss)
{
    Log(Debug) << "WMaxRadio::disconnect_start" << LogEnd;
    if (!ss->gate("out")->isConnected()) {
	return;
    }
    
    cGate * bsGate = ss->gate("out")->getNextGate();
    cModule * bs = bsGate->getOwnerModule();
    Log(Debug) << "Disconnecting SS " << ss->getFullName() << " from BS[" << bs->getIndex() << "." << LogEnd;
    if (bs!=getParentModule()) {
	opp_error("Attempted to disconnect from the wrong BS.\n");
    }
    int ind = bsGate->getIndex();
    
    gate("radioOut", ind)->disconnect();
    gate("radioIn", ind)->disconnect();

    bs->gate("in", ind)->disconnect();
    bs->gate("out", ind)->disconnect();
    Log(Debug) << "WMaxRadio::disconnect_stop" << LogEnd;
}
