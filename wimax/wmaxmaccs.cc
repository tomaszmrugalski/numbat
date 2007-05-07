/**
 * @file   wmaxmaccs.cc
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-04-20 23:09:38+0100
 * 
 * @brief  WMax MAC convergence sublayer
 * @licence GNU GPLv2 or later
 *
 */

#include <omnetpp.h>
#include "wmaxmaccs.h"
#include "ipv6node.h"
#include "wmaxmac.h"

using namespace std;

/********************************************************************************/
/*** WMaxMacCS ******************************************************************/
/********************************************************************************/

Define_Module(WMaxMacCS);

void WMaxMacCS::initialize() {

}


void WMaxMacCS::handleMessage(cMessage *msg) {


    if (dynamic_cast<WMaxMacTerminateAllConns*>(msg)) {
        ev << fullName() << ": ALL CONNECTION TERMINATED" << endl;
        csTable.clear();
        delete msg;
        return;
    }

    if (WMaxMacAddConn *addconn = dynamic_cast<WMaxMacAddConn*>(msg)) {
        WMaxMacCSRule rule;
        rule.cid  = addconn->getCid();

        list<WMaxMacCSRule>::iterator it;

        csTable.push_front(rule);

        ev << fullName() <<": New Covergence Sublayer table:" << endl;
        for(it=csTable.begin(); it!=csTable.end(); it++) {
            ev << "    CID=" << it->cid << endl;
        }

        delete msg;
        return;
    }


    cGate * gate = msg->arrivalGate();
    if(!strcmp(gate->fullName(),"macIn")) {
        handleUlMessage(msg);
        return;
    }

    handleDlMessage(msg);
}


void WMaxMacCS::handleUlMessage(cMessage *msg) {
    // reconstruction
    cMessage *ipv6packet = msg->decapsulate();
    delete msg;
    send(ipv6packet, "ipOut", 0);
    ev << fullName() << ": Message send to upper layer." << endl;
}


void WMaxMacCS::handleDlMessage(cMessage *msg) {
    list<WMaxMacCSRule>::iterator it;
    cGate * gate = msg->arrivalGate();
    for(it=csTable.begin(); it!=csTable.end(); it++) {
        /// @todo clasifier
        if((it->cid != 0)) {
            break;
        }
    }
    if(it == csTable.end()) {
        ev << fullName() << ": Unable to find a proper connection. Message has been droped." << endl;
        delete msg;
        return;
    }

     cMessage *wmaxmacmsg = new cMessage("IPv6 Packet");
     wmaxmacmsg->encapsulate(msg);

     WMaxMacHeader * hdr = new WMaxMacHeader();
     hdr->cid = it->cid;
     wmaxmacmsg->setControlInfo(hdr);

     ev << fullName() << ": New message. CID=" << it->cid << endl;

     send(wmaxmacmsg, "macOut");
}
