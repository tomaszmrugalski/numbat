/**
 * @file   wmaxmac.c
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Mon Nov 20 00:26:38 2006
 * 
 * @brief  WMaxMAC implementation
 * 
 * published under GNU GPLv2 or later
 */

#include <omnetpp.h>
#include <sstream>
#include "wmaxmac.h"
#include "wmaxmsg_m.h"

using namespace std;

/********************************************************************************/
/*** WMax Mac (common for BS/SS) ************************************************/
/********************************************************************************/
WMaxMac::WMaxMac()
{
    GateIndex = 0;
}


bool WMaxMac::addConn(WMaxConn conn)
{
    conn.gateIndex = GateIndex++;

    stringstream tmp;
    /// @todo - check if CID and sfid are unique
    Conns.push_back(conn);

    
    ev << fullName() << ": adding connection: sfid=" << conn.sfid << ", cid=" << conn.cid << ", connection type=";
    switch (conn.type) {
    case WMAX_CONN_TYPE_UGS:
	tmp << "UGS: msr=" << conn.qos.ugs.msr << ", latency=" << conn.qos.ugs.latency 
	    << ", jitter=" << conn.qos.ugs.jitter;
	break;
    case WMAX_CONN_TYPE_RTPS:
	tmp << "rtPS: msr=" << conn.qos.rtps.msr << ", mrr=" << conn.qos.rtps.mrr 
	    << ", latency=" << conn.qos.rtps.latency;
	break;
    case WMAX_CONN_TYPE_NRTPS:
	tmp << "nrtPS: msr=" << conn.qos.nrtps.msr << ", mrr=" << conn.qos.nrtps.mrr
	    << ", priority=" << conn.qos.nrtps.priority;
    case WMAX_CONN_TYPE_BE:
	ev << "BestEffort: msr=" << conn.qos.be.msr;
	break;
    }
    ev << tmp.str() << " gateIndex=" << conn.gateIndex << endl;
    //setDisplayString("Conns"); // this doesn't work. Strange
    return true;
}
 
bool WMaxMac::delConn(uint32_t sfid)
{
    /// @todo - implement this
    return false;
}


void WMaxMac::printDlMap(WMaxMsgDlMap * dlmap)
{
    ev << fullName() << ": --- DL-MAP (" << dlmap->getIEArraySize() << " IE(s) ---" << endl;

    for (int i=0; i<dlmap->getIEArraySize(); i++) {
	WMaxDlMapIE &ie = dlmap->getIE(i);
	ev << "IE[" << i << "]:";
    }
}

void WMaxMac::printUlMap(WMaxMsgUlMap * ulmap)
{
    ev << fullName() << ": --- UL-MAP: " << ulmap->getIEArraySize() << " IE(s) ---" << endl;

    for (int i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE &ie = ulmap->getIE(i);
	ev << "IE[" << i << "]: cid=" << ie.cid << ", uiuc=" << ie.uiuc;

	switch (ie.uiuc) {
	case WMAX_ULMAP_UIUC_FAST_FEEDBACK:
	case WMAX_ULMAP_UIUC_EXTENDED2:
	case WMAX_ULMAP_UIUC_PAPR:
	case WMAX_ULMAP_UIUC_EXTENDED:
	    ev << " NOT SUPPORTED IE TYPE";
	    break;
	case WMAX_ULMAP_UIUC_CDMA_BWR: {
	    ev << "(CDMA BWR): symbolOffset=" << (int)ie.cdmaIE.symbolOffset << " ofdmaSymbols=" << (int)ie.cdmaIE.ofdmaSymbols 
	       << " subchannels=" << (int)ie.cdmaIE.subchannels << " rangingMethod=" << (int)ie.cdmaIE.rangingMethod;
	    switch (ie.cdmaIE.rangingMethod) {
	    case WMAX_RANGING_METHOD_INITIAL: 
		ev << "initial ranging";
		break;
	    case WMAX_RANGING_METHOD_BWR:
		ev << "bandwidth request";
		break;
	    default:
		ev << "[unknown ranging method]";
	    }
	    break;
	}
	case WMAX_ULMAP_UIUC_CDMA_ALLOC:
	    ev << "(CDMA ALLOCATION): duration=" << ie.cdmaAllocIE.duration << " uiuc=" << (int)ie.cdmaAllocIE.uiuc
	       << " rangingCode=" << ie.cdmaAllocIE.rangingCode << " rangingSymbol=" << ie.cdmaAllocIE.rangingSymbol
	       << " rangingSubchannel=" << ie.cdmaAllocIE.rangingSubchannel;
	    break;
	default:
	    ev << "(DATA): duration=" << ie.dataIE.duration;
	    break;
	}
	ev << endl;
    }
}

/********************************************************************************/
/*** WMax Mac BS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacBS);

void WMaxMacBS::initialize()
{
    SendQueue.setName("SendQueue");
    FrameLength = par("FrameLength");

    TxStart = new cMessage("TxStart");
    scheduleAt(0.0, TxStart);

    Conns.clear();

    // configure scheduler
    schedUgsMinGrantSize = WMAX_SCHED_MIN_GRANT_SIZE;
    schedCdmaInitRngFreq = WMAX_CDMA_INIT_RNG_FREQ;
    schedCdmaBwrFreq     = WMAX_CDMA_BWR_FREQ;
    schedCdmaHoRngFreq   = WMAX_CDMA_HO_RNG_FREQ;

    // configure connections
    int conns = gateSize("macOut");
    int cid  = 1024;
    int sfid = 1;
    ev << fullName() << ": " << conns << " objects connected to this MAC, creating connections." << endl;
    for (int i=0; i<conns; i++) {
	WMaxConn conn;
	CLEAR(&conn);
	conn.type= WMAX_CONN_TYPE_UGS;
	conn.sfid = sfid++;
	conn.cid  = cid++;
	conn.gateIndex = i;
	conn.qos.ugs.msr = 80000; // 100kbps
	addConn(conn);
    }

#if 0
    /// @todo - Best Effort is not supported yet
    CLEAR(&conn);
    conn.type= WMAX_CONN_TYPE_BE;
    conn.sfid = 2;
    conn.cid = 1025;
    conn.qos.ugs.msr = 100000; // 100kbps
    addConn(conn);
#endif
}

void WMaxMacBS::handleMessage(cMessage *msg)
{
    if (msg==TxStart) {
	schedule();
	scheduleAt(simTime()+FrameLength, TxStart);
	return;
    }

    cGate * gate = msg->arrivalGate();
    if (!strcmp(gate->fullName(),"phyIn")) {
	handleUlMessage(msg);
	return;
    }

    // remaining gates must be downlink
    handleDlMessage(msg);
}


void WMaxMacBS::schedule()
{
    int i;
    int ieCnt = 0;
    /// @todo - write some scheduling module

    // prepare DL 
    WMaxMsgDlMap * dlmap = new WMaxMsgDlMap("DL-MAP");
    dlmap->setName("DL-MAP");
    ieCnt = 0;
    if (SendQueue.length()) {
	for (i=0;i<SendQueue.length(); i++) {
	    /// @todo - fix this condition: use frame length instead of sending one simple frame
	    ieCnt++;
	    dlmap->setIEArraySize(ieCnt);

	    /// @todo - DL-MAP gemeration
	    WMaxDlMapIE ie;
 	    ie.cid    = 0;

	    cMessage * msg = (cMessage*)SendQueue.pop();
 	    ie.length = msg->length();
	    dlmap->setIE(ieCnt-1,ie);

 	    send(msg, "phyOut");
	}
    }

    ev << "Generating DL-MAP: " << dlmap->getIEArraySize() << " IE(s)" << endl;
    send(dlmap, "phyOut");

    // prepare UL
    WMaxMsgUlMap * ulmap = new WMaxMsgUlMap("UL-MAP");
    ieCnt = 0;

    schedCdmaInitRngCnt++;
    schedCdmaHoRngCnt++;
    schedCdmaBwrCnt++;

    if (schedCdmaBwrFreq && schedCdmaBwrFreq<=schedCdmaBwrCnt++) {
	// append IE for CDMA bandwidth request
	ieCnt++;
	schedCdmaBwrCnt=0;
	ulmap->setIEArraySize(ieCnt);
	WMaxUlMapIE ie;
	CLEAR(&ie);
	ie.cid  = WMAX_CID_BROADCAST;
	ie.uiuc = WMAX_ULMAP_UIUC_CDMA_BWR;
	ie.cdmaIE.rangingMethod = WMAX_RANGING_METHOD_BWR;
	/// @todo - full symbolOffset, ofdmaSymbols, subchannels
	ulmap->setIE(ieCnt-1,ie);
    }

    if (schedCdmaHoRngFreq && schedCdmaHoRngFreq<=schedCdmaHoRngCnt++) {
	
    }
    
    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); it++) {
	// for each configured service flow, grant some bandwidth (if necessary)
	switch (it->type) {
	case WMAX_CONN_TYPE_BE:
	    /// @todo - best effort not supported yet
	    break;
	case WMAX_CONN_TYPE_UGS:
	{
	    uint32_t x = uint32_t(double(it->qos.ugs.msr)/8.0*FrameLength);
	    it->bandwidth += x;

	    if (it->bandwidth>WMAX_SCHEDULER_MIN_UGS_GRANT) {
		ev << fullName() << ": Adding UGS grant." << endl;
		ieCnt++;
		ulmap->setIEArraySize(ieCnt);
		WMaxUlMapIE ie;
		CLEAR(&ie);
		ie.uiuc = WMAX_ULMAP_UIUC_DATA_1;
		ie.cid = it->cid;
		ie.dataIE.duration = it->bandwidth;
		ulmap->setIE(ieCnt-1, ie);
		it->bandwidth = 0;
		break;
	    }
	}
	}
    }

    ev << fullName() << ": Generating UL-MAP: " << ulmap->getIEArraySize() << "IE(s)" << endl;
    printUlMap(ulmap);
    send(ulmap, "phyOut");

    // trigger PHY to start frame
    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    ev << fullName() << ": Generating FrameStart trigger for PHY" << endl;
    send(frameStart, "phyOut");
}

void WMaxMac::handleUlMessage(cMessage *msg)
{
    int cid = -1;
    int gateIndex = -1;
    if (dynamic_cast<WMaxMacHeader*>(msg->controlInfo())) {
	WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->removeControlInfo());
	cid = hdr->cid;
	delete hdr;
    } else {
	ev << fullName() << ": malformed message received. Uplink message without WMaxMacHeader structure" << endl;
	return;
    }

    // check if there is such connection (cid has to match)
    for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	if (it->cid == cid) {
	    gateIndex = it->gateIndex;
	    break;
	}
    }

    if (gateIndex != -1) {
	ev << fullName() << ": sending message to upper (IPv6) layer (CID=" << cid << ", gateIndex=" 
	   << gateIndex << ")" << endl;
	send(msg, "macOut", gateIndex);
    } else {
	ev << fullName() << ": Unable to find connection for CID=" << cid << ", message dropped." << endl;
    }
}

/********************************************************************************/
/*** WMax Mac SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacSS);

void WMaxMacSS::initialize()
{
    SendQueue.setName("SendQueue");

    CLEAR(&Stats);

    int conns = gateSize("macOut");
    int cid  = 1024;
    int sfid = 1;
    ev << fullName() << ": " << conns << " objects connected to this MAC, creating connections." << endl;
    for (int i=0; i<conns; i++) {
	WMaxConn conn;
	CLEAR(&conn);
	conn.type= WMAX_CONN_TYPE_UGS;
	conn.sfid = sfid++;
	conn.cid  = cid++;
	conn.gateIndex = i;
	conn.qos.ugs.msr = 80000; // 100kbps
	addConn(conn);
    }
}

void WMaxMacSS::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();
    ev << fullName() << ":Message " << msg->fullName() << " received on gate: " << gate->fullName() << endl;
    if (!strcmp(gate->fullName(),"phyIn")) {
	handleUlMessage(msg);
	return;
    }

    // remaining gates must be downlink
    handleDlMessage(msg);
    return;
}

void WMaxMac::handleDlMessage(cMessage *msg)
{
    WMaxMacHeader * hdr = new WMaxMacHeader();

    // find proper connection, not just get first one
    cGate * gate = msg->arrivalGate();
    list<WMaxConn>::iterator it;
    for (it = Conns.begin(); it!=Conns.end(); it++) {
	if (it->gateIndex == gate->index()) {
	    break;
	}
    }
    if (it==Conns.end()) {
	ev << fullName() << ": Unable to find connection for gateIndex=" << gate->index() << endl;
	return;
    }

    hdr->cid = it->cid;
    msg->setControlInfo(hdr);

    ev << fullName() << ": Queueing message (CID=" << it->cid << ", gateIndex=" << gate->index() << ")." << endl;
    SendQueue.insert(msg);
}

void WMaxMacSS::handleUlMessage(cMessage *msg)
{
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	printUlMap(dynamic_cast<WMaxMsgUlMap*>(msg));
	Stats.ulmaps++;
	schedule(dynamic_cast<WMaxMsgUlMap*>(msg));
	return;
    }

    if (dynamic_cast<WMaxMsgDlMap*>(msg)) {
	printDlMap(dynamic_cast<WMaxMsgDlMap*>(msg));
	Stats.dlmaps++;
	WMaxMsgDlMap* dlmap = dynamic_cast<WMaxMsgDlMap*>(msg);
	ev << fullName() << "DL-MAP received: expecting " << dlmap->getIEArraySize() << " messages in this frame." << endl;
	delete msg;
	return;
    }

    WMaxMac::handleUlMessage(msg);
}

void WMaxMacSS::schedule(WMaxMsgUlMap * ulmap)
{
    int bandwidth = 0;
    ev << fullName() << ": UL-MAP received with " << ulmap->getIEArraySize() << " IE(s)" << endl;
    int i;
    for (i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE & ie = ulmap->getIE(i);
	for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->cid==ie.cid) {
		if (ie.uiuc>=WMAX_ULMAP_UIUC_DATA_1 || ie.uiuc<=WMAX_ULMAP_UIUC_DATA_10) {
		    bandwidth = ie.dataIE.duration;
		    Stats.grants++;
		} else 
                if (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_BWR) {


		} else
                if (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_ALLOC) {


		}
	    }
	    
	}
    }

    if (SendQueue.length()) {
	ev << fullName() << ": Sending message" << endl;
	cMessage * msg = (cMessage*)SendQueue.pop();
	send(msg, "phyOut");
    }

    delete ulmap;
    Stats.bandwidth += bandwidth;

    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    ev << fullName() << ": Generating FrameStart trigger for PHY" << endl;
    send(frameStart, "phyOut");
}

void WMaxMacSS::finish()
{
    ev << " Stats for " << fullName() << endl;
    ev << "-----------------------" << endl;
    ev << "Grants            : " << Stats.grants << endl;
    ev << "Bandwidth granted : " << Stats.bandwidth << endl;
    ev << "UL-MAPs received  : " << Stats.ulmaps << endl;
    ev << "DL-MAPs received  : " << Stats.dlmaps << endl;
}
