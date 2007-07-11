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
#include <string>
#include "wmaxmaccs.h"
#include "ipv6node.h"
#include "wmaxmac.h"
#include "logger.h"

using namespace std;

ostream & operator <<(ostream & s, WMaxMacCSRule &rule)
{
  s << "cid=" << rule.cid;
  return s;
}

/********************************************************************************/
/*** WMaxMacCS ******************************************************************/
/********************************************************************************/

Define_Module(WMaxMacCS);

void WMaxMacCS::initialize() {
  WATCH_LIST(csTable);
}


void WMaxMacCS::handleMessage(cMessage *msg) {


    if (dynamic_cast<WMaxMacTerminateAllConns*>(msg)) {
        Log(Notice) << "All connections terminated." << LogEnd;
        csTable.clear();
        delete msg;
        return;
    }

    if (WMaxMacAddConn *addconn = dynamic_cast<WMaxMacAddConn*>(msg)) {
        WMaxMacCSRule rule;
        rule.cid  = addconn->getCid();

        list<WMaxMacCSRule>::iterator it;

        csTable.push_front(rule);

        string log;
        log = "New Convergence Sublayer clasifier: ";
        for(it=csTable.begin(); it!=csTable.end(); it++) {
              stringstream ss_cid;
              string st_cid;
              ss_cid << it->cid;
              ss_cid >> st_cid;
              log = log + "CID=" + st_cid + " | ";
        }
        
        Log(Notice) << log << LogEnd;

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
    Log(Debug) << "Message send to upper layer." << LogEnd;
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
        Log(Debug) << "Unable to find a proper connection. Message has been droped." << LogEnd;
        delete msg;
        return;
    }

     cMessage *wmaxmacmsg = new cMessage("IPv6 Packet");
     wmaxmacmsg->encapsulate(msg);

     WMaxMacHeader * hdr = new WMaxMacHeader();
     hdr->cid = it->cid;
     wmaxmacmsg->setControlInfo(hdr);

     Log(Debug) << "New message. CID=" << it->cid << LogEnd;

     send(wmaxmacmsg, "macOut");
}
