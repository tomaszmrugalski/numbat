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

using namespace std;

/********************************************************************************/
/*** WMax Mac (common for BS/SS) ************************************************/
/********************************************************************************/

bool WMaxMac::addConn(WMaxConn conn)
{
    /// @todo - check if CID and sfid are unique
    Conns.push_back(conn);
    ev << "Adding sfid=" << conn.sfid << endl;
    //setDisplayString("Conns"); // this doesn't work. Strange
    return true;
}
 
bool WMaxMac::delConn(uint32_t sfid)
{
    /// @todo - implement this
    return false;
}

/********************************************************************************/
/*** WMax Mac BS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacBS);

void WMaxMacBS::initialize()
{
    TxStart = new cMessage("TxStart");
    scheduleAt(0.0, TxStart);

    Conns.clear();


    WMaxConn conn;
    conn.type= WMAX_CONN_TYPE_UGS;
    conn.sfid = 1;
    conn.cid = 1024;
    addConn(conn);
    
    conn.type= WMAX_CONN_TYPE_BE;
    conn.sfid = 2;
    conn.cid = 1025;
    addConn(conn);
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

    // prepare DL 
    WMaxMsgDlMap * dlmap = new WMaxMsgDlMap("DL-MAP");
    dlmap->setName("DL-MAP");
    ev << "Generating DL-MAP: " << dlmap->getIEArraySize() << "IE(s)" << endl;
    send(dlmap, "phyOut");

    // prepare UL
    WMaxMsgUlMap * ulmap = new WMaxMsgUlMap("UL-MAP");
    int ieCnt = 0;
    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); it++) {
	// for each configured service flow, grant some bandwidth (if necessary)
	ev << "#### type=" << it->type << ", sfid=" << it->sfid << ", cid=" << it->cid << endl;
	switch (it->type) {
	case WMAX_CONN_TYPE_BE:
	    /// @todo - best effort not supported yet
	    break;
	case WMAX_CONN_TYPE_UGS:
	    ieCnt++;
	    ulmap->setIEArraySize(ieCnt);
	    WMaxMapIE ie;
	    ie.cid = it->cid;
	    ie.dataLen = it->dataLen;
	    ulmap->setIE(ieCnt-1, ie);
	    break;
	}
    }

    ev << fullName() << ": Generating UL-MAP: " << ulmap->getIEArraySize() << "IE(s)" << endl;
    send(ulmap, "phyOut");

    // trigger PHY to start frame
    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    ev << fullName() << ": Generating FrameStart trigger for PHY" << endl;
    send(frameStart, "phyOut");
}

void WMaxMacBS::handleDlMessage(cMessage *msg)
{

}

void WMaxMacBS::handleUlMessage(cMessage *msg)
{

}

/********************************************************************************/
/*** WMax Mac SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacSS);

void WMaxMacSS::initialize()
{
    Conns.clear();


    WMaxConn conn;
    conn.type= WMAX_CONN_TYPE_UGS;
    conn.sfid = 1;
    conn.cid = 1024;
    addConn(conn);
    
    conn.type= WMAX_CONN_TYPE_BE;
    conn.sfid = 2;
    conn.cid = 1025;
    addConn(conn);
}

void WMaxMacSS::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();
    ev << fullName() << ":Message " << msg->fullName() << " received on gate: " << gate->fullName() << endl;
    if (!strcmp(gate->fullName(),"phyIn")) {
	handleUlMessage(msg);
    }
}

void WMaxMacSS::handleDlMessage(cMessage *msg)
{

}

void WMaxMacSS::handleUlMessage(cMessage *msg)
{
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	handleUlMap(dynamic_cast<WMaxMsgUlMap*>(msg));
	return;
    }

    delete msg;
}

void WMaxMacSS::handleUlMap(WMaxMsgUlMap * ulmap)
{
    ev << "UL-MAP received with " << ulmap->getIEArraySize() << "IE(s)" << endl;
    int i;
    for (i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxMapIE & ie = ulmap->getIE(i);
	for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->cid==ie.cid) {
		ev << "#### entry found for this SS" << endl;
	    }
	    
	}
    }

    delete ulmap;
}
