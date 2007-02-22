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
#include "wmaxctrl.h"

#define SCHED ev << fullName() << ":"

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
    cGate *target = gate("macOut", conn.gateIndex);
    target = target->toGate();
    cModule * owner = target->ownerModule();

    if (dynamic_cast<WMaxCtrlSS*>(owner)) {
	conn.controlConn = true;
    }
    if (dynamic_cast<WMaxCtrlBS*>(owner)) {
	conn.controlConn = true;
    }
    
    ev << tmp.str() << " gateIndex=" << conn.gateIndex << ", controlConn=" << (conn.controlConn?"YES":"NO") 
       << ", connected to: ";
    ev << owner->fullName() << endl;

    /// @todo - check if CID and sfid are unique
    Conns.push_back(conn);

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
    string x = fullName();
    ev << x << ": --- DL-MAP (" << dlmap->getIEArraySize() << " IE(s) ---" << endl;

    for (int i=0; i<dlmap->getIEArraySize(); i++) {
	WMaxDlMapIE &ie = dlmap->getIE(i);
	ev << x << ": IE[" << i << "]: cid=" << ie.cid << ", length=" << ie.length << ", symbols=" << ie.symbols << endl;
    }
}

void WMaxMac::printUlMap(WMaxMsgUlMap * ulmap)
{
    string x = fullName();
    ev << x << ": --- UL-MAP: " << ulmap->getIEArraySize() << " IE(s) ---" << endl;

    for (int i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE &ie = ulmap->getIE(i);
	ev << x << ": IE[" << i << "]: cid=" << ie.cid << ", uiuc=" << ie.uiuc;

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
	       << " rangingCode=" << (int)ie.cdmaAllocIE.rangingCode << " rangingSymbol=" << (int)ie.cdmaAllocIE.rangingSymbol
	       << " rangingSubchannel=" << (int)ie.cdmaAllocIE.rangingSubchannel;
	    break;
	default:
	    ev << "(DATA): duration=" << (int)ie.dataIE.duration;
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
    int symbols = 300; /// @todo - check/calculate how many symbols are available in each frame
    int dlSymbols = symbols/2;
    int ulSymbols = symbols - dlSymbols;

    WMaxMsgDlMap * dlmap = scheduleDL(dlSymbols);
    WMaxMsgUlMap * ulmap = scheduleUL(ulSymbols);

    printDlMap(dlmap);
    printUlMap(ulmap);

    send(dlmap, "phyOut");
    send(ulmap, "phyOut");

    // trigger PHY to start frame
    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    ev << fullName() << ": Generating FrameStart trigger for PHY" << endl;
    send(frameStart, "phyOut");
}

/** 
 * schedules downlink traffic
 * 
 * 
 * @return 
 */
WMaxMsgDlMap * WMaxMacBS::scheduleDL(int symbols)
{
    int i;
    int ieCnt = 0;
    WMaxDlMapIE ie; // map element

    int bytesPerPS = WMAX_BYTES_PER_SYMBOL; // this depends on modulation used, use 12 bytes/symbol for now
    int lengthInPS;
    cMessage * msg;

    WMaxMsgDlMap * dlmap = new WMaxMsgDlMap("DL-MAP");
    dlmap->setName("DL-MAP");
    ieCnt = 0;

    while (true) {
	SCHED << symbols << " symbols left." << endl;
	
	if (!SendQueue.length()) // nothing more to send
	    break;

	if (symbols <=0)
	    break;

	msg = (cMessage*) SendQueue.tail();

	if (msg->length() > symbols*bytesPerPS) {
	    // message won't fit in this frame. What should we do in such case?

	    SCHED << " tried to schedule message (len=" << msg->length() << ", but there are only "
		  << symbols*bytesPerPS << " bytes left." << endl;

	    if (ieCnt) // something has been scheduled - ok, end scheduling
		break;

	    // what to do, if we have not scheduled anything and the message still doesn't fit?

	    // possible solutions:
	    // a) implement fragmentation (the best one)
	    // b) send message and end scheduling (flaw: sending more than possible)
	    // c) ignore this message and try to scheduler next message, possibly smaller (flaw: message will never be sent)
	    // d) abort simulation as there is no way to send this message

	    // currently used: d)
	    opp_error("Unable to send %d-byte long message(%s), because it won't fit in DL subframe (%d symbols *%dB/PS=%d bytes)",
		      msg->length(), msg->fullName(), symbols, bytesPerPS, symbols*bytesPerPS);
	    break;
	}
	
	// message will fit in this frame, send it
	ieCnt++;
	dlmap->setIEArraySize(ieCnt);
	
	/// @todo - DL-MAP generation
	
	msg = (cMessage*)SendQueue.pop();
	lengthInPS = (int)ceil(double(msg->length())/bytesPerPS);
	
	symbols -= lengthInPS;
	
	WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->controlInfo());
	if (!hdr)
	    opp_error("Unable to obtain header information for message: %s\n", msg->fullName());
	CLEAR(&ie);
	ie.length  = msg->length();
	ie.cid     = hdr->cid;
	ie.symbols = lengthInPS;
	dlmap->setIE(ieCnt-1,ie);

	SCHED << "Sent msg: length=" << ie.length << ", used " << lengthInPS << " symbols, " 
	   << symbols << " symbol(s) left" << endl;
	
	send(msg, "phyOut");
    }

    return dlmap;
}

/** 
 * scheduler uplink traffic
 * 
 * 
 * @return 
 */
WMaxMsgUlMap * WMaxMacBS::scheduleUL(int symbols)
{
    int i;
    int ieCnt = 0;
    WMaxUlMapIE ie;
    int bytesPerPS = WMAX_BYTES_PER_SYMBOL; // this depends on modulation used, use 12 bytes/symbol for now

    WMaxMsgUlMap * ulmap = new WMaxMsgUlMap("UL-MAP");

    schedCdmaInitRngCnt++;
    schedCdmaHoRngCnt++;
    schedCdmaBwrCnt++;

    if (schedCdmaBwrFreq && schedCdmaBwrFreq<=schedCdmaBwrCnt++) {
	// append IE for CDMA bandwidth request
	ieCnt++;
	schedCdmaBwrCnt=0;
	ulmap->setIEArraySize(ieCnt);
	CLEAR(&ie);
	ie.cid  = WMAX_CID_BROADCAST;
	ie.uiuc = WMAX_ULMAP_UIUC_CDMA_BWR;
	ie.cdmaIE.rangingMethod = WMAX_RANGING_METHOD_BWR;
	/// @todo - full symbolOffset, ofdmaSymbols, subchannels
	ulmap->setIE(ieCnt-1,ie);
	symbols /= 1; // use just 1 symbol for Bandwidth Requests
    }

    if (schedCdmaInitRngFreq && schedCdmaInitRngFreq<=schedCdmaInitRngCnt++) {
	// append IE for CDMA bandwidth request
	ieCnt++;
	schedCdmaInitRngCnt=0;
	ulmap->setIEArraySize(ieCnt);
	CLEAR(&ie);
	ie.cid  = WMAX_CID_BROADCAST;
	ie.uiuc = WMAX_ULMAP_UIUC_CDMA_BWR;
	ie.cdmaIE.rangingMethod = WMAX_RANGING_METHOD_INITIAL;
	/// @todo - full symbolOffset, ofdmaSymbols, subchannels
	ulmap->setIE(ieCnt-1,ie);
	symbols /= 1; // use just 1 symbol for Initial Ranging
    }

    if (schedCdmaHoRngFreq && schedCdmaHoRngFreq<=schedCdmaHoRngCnt++) {
	/// @todo - implement sending Handover ranging opportunities
    }
    
    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); it++) {
	if (symbols <=0) {
	    SCHED << "No symbols left, scheduling aborted." << endl;
	    break;
	}

	// for each configured service flow, grant some bandwidth (if necessary)
	switch (it->type) {
	case WMAX_CONN_TYPE_BE:
	    /// @todo - best effort not supported yet
	    break;
	case WMAX_CONN_TYPE_UGS:
	{
	    uint32_t x = uint32_t(double(it->qos.ugs.msr)/8.0*FrameLength);
	    it->bandwidth += x;
	    int symbolLength = (int)ceil(double(it->bandwidth)/bytesPerPS);

	    if ( (it->bandwidth>WMAX_SCHEDULER_MIN_UGS_GRANT) && (symbols>=symbolLength) ) {
		symbols -= symbolLength;

		ieCnt++;
		ulmap->setIEArraySize(ieCnt);
		WMaxUlMapIE ie;
		CLEAR(&ie);
		ie.uiuc = WMAX_ULMAP_UIUC_DATA_1;
		ie.cid = it->cid;
		ie.dataIE.duration = it->bandwidth;
		ulmap->setIE(ieCnt-1, ie);
		it->bandwidth = 0;
		ev << fullName() << ": Adding UGS grant: cid=" << ie.cid << ", bandwith=" << ie.dataIE.duration << ", " 
		   << symbolLength << " symbols." << endl;
		break;
	    }
	    
	}
	}
    }
    return ulmap;
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

    ev << fullName() << ": Queueing message (CID=" << it->cid << ", gateIndex=" << gate->index() << ", length=" << msg->length() << ")." << endl;
    SendQueue.insert(msg);
}

void WMaxMacSS::handleUlMessage(cMessage *msg)
{
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	WMaxMsgUlMap * ulmap = dynamic_cast<WMaxMsgUlMap*>(msg);
	printUlMap(ulmap);
	Stats.ulmaps++;

	// handle this map to WMaxCtrl
	list<WMaxConn>::iterator it;
	for (it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->controlConn) {
		ev << "Dispatching ulmap to gate " << it->gateIndex << ", ctrl=" << ((int)(it->controlConn)) << endl;
		//WMaxMsgUlMap * copy = (WMaxMsgUlMap *) ulmap->dup();
		send(msg, "macOut", it->gateIndex);
	    }
	}

	schedule(ulmap);

	/// @todo - delete ulmap, but before to do so, create and send copies to control clients
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
