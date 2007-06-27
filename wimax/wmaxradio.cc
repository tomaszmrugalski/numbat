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

void WMaxRadio::initialize()
{
}

void WMaxRadio::handleMessage(cMessage *msg)
{
    // radioOut, radioIn, phyOut, phyIn
    cGate * g = msg->arrivalGate();
    if (!strcmp(g->fullName(),"phyIn")) {
	// Broadcast transmission (BS->all SSes)
	g = gate("radioIn", 0);
	for (int i=0; i<g->size(); i++) {
	    g = gate("radioOut", i);
	    if (g->isConnected()) {
		cMessage * copy = (cMessage*)msg->dup();
		if (msg->controlInfo()) {
		    cPolymorphic * hdr = msg->controlInfo();
		    cPolymorphic * hdr2 = hdr->dup();
		    copy->setControlInfo(hdr2);
		}
		send(copy, "radioOut", i);
	    }
	}
	delete msg;
	return;
    }

    // unicast transmission (SS -> BS)
    send(msg, "phyOut");	
}

void WMaxRadio::connect(cModule * ss)
{
    Log(Debug) << "Connecting SS " << ss->fullName() << " to this radio." << LogEnd;
    int maxSS = gate("radioOut",0)->size();
    
    cModule * bs = parentModule();

    for (int i=0; i < maxSS; i++) {
	cGate * g = gate("radioOut", i);
	Log(Debug) << "Checking gate: radioOut[" << i << "]: " << (g->isConnected()?"CONNECTED":"NOT CONN") << LogEnd;
	if (!g->isConnected()) {

	    // BS->SS
	    cGate * bsGate = bs->gate("out",i);
	    bsGate->disconnect();
	    g->connectTo(bsGate);
	    bsGate->connectTo(ss->gate("in"));

	    // SS->BS
	    bsGate = bs->gate("in", i);
	    bsGate->disconnect();
	    g = gate("radioIn", i);
	    ss->gate("out")->disconnect();
	    ss->gate("out")->connectTo(bsGate);
	    bsGate->connectTo(g);
	    return;
				       
	} else {

	}
    }
}

void WMaxRadio::disconnect(cModule * ss)
{
    if (!ss->gate("out")->isConnected()) {
	return;
    }
    
    cGate * bsGate = ss->gate("out")->toGate();
    cModule * bs = bsGate->ownerModule();
    Log(Debug) << "Disconnecting SS " << ss->fullName() << " from BS[" << bs->index() << "." << LogEnd;
    if (bs!=parentModule()) {
	opp_error("Attempted to disconnect from the wrong BS.\n");
    }
    int ind = bsGate->index();
    
    gate("radioOut", ind)->disconnect();
    gate("radioIn", ind)->disconnect();

    bs->gate("in", ind)->disconnect();
    bs->gate("out", ind)->disconnect();

}
