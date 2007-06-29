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
#include "logger.h"

using namespace std;

ostream & operator<<(ostream & strum, WMaxMacCDMA &x) {
    strum << "code=" << x.code << " bandwidth=" << x.bandwidth << " cid=" << x.cid;
    return strum;
}

/********************************************************************************/
/*** WMax Mac (common for BS/SS) ************************************************/
/********************************************************************************/
WMaxMac::WMaxMac()
{
    GateIndex = 0;
    this->CDMAQueue = new cQueue("CDMAQueue");
}

bool WMaxMac::addConn(WMaxConn conn)
{
    stringstream tmp;
    
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
	tmp << "BestEffort: msr=" << conn.qos.be.msr;
	break;
    }
    cGate *target = gate("macOut", conn.gateIndex);
    target = target->toGate();
    cModule * owner = target->ownerModule();

    if (dynamic_cast<WMaxCtrlSS*>(owner)) {
	conn.controlConn = true;
    }
    else if (dynamic_cast<WMaxCtrlBS*>(owner)) {
	conn.controlConn = true;
    } else {
        conn.controlConn = false;
    }

    Log(Notice) << "Adding connection: sfid=" << conn.sfid << ", cid=" << conn.cid << ", type="
		<< tmp.str() << ", controlConn=" << (conn.controlConn?"YES":"NO") 
		<< ", connected to: " << owner->fullName() << LogEnd;

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
    Log(Debug) << " --- DL-MAP (" << dlmap->getIEArraySize() << " IE(s) ---" << LogEnd;
    if (!logger::willPrint(logger::Debug))
	return;

    for (int i=0; i<dlmap->getIEArraySize(); i++) {
	WMaxDlMapIE &ie = dlmap->getIE(i);
	Log(Debug) << "IE[" << i << "]: cid=" << ie.cid << ", length=" << ie.length << ", symbols=" << ie.symbols << LogEnd;
    }
}

void WMaxMac::printUlMap(WMaxMsgUlMap * ulmap)
{
    Log(Debug) << " --- UL-MAP: " << ulmap->getIEArraySize() << " IE(s) ---" << LogEnd;
    if (!logger::willPrint(logger::Debug))
	return;

    for (int i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE &ie = ulmap->getIE(i);
	Log(Debug) << "IE[" << i << "]: cid=" << ie.cid << ", uiuc=" << ie.uiuc;

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
	Log(Cont) << LogEnd;
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
    schedDcdFreq         = WMAX_DCD_FREQ;
    schedUcdFreq         = WMAX_UCD_FREQ;

    schedCdmaInitRngCnt  = 0;
    schedCdmaHoRngCnt    = 0;
    schedCdmaBwrCnt      = 0;
    schedDcdCnt          = 0;
    schedUcdCnt          = 0;

    // Create permanent INITIAL-RANGING connection
    addRangingConn();
}

void WMaxMacBS::handleMessage(cMessage *msg)
{
    if (msg==TxStart) {
	schedule();
	scheduleAt(simTime()+FrameLength, TxStart);
	return;
    }

    if (WMaxMacAddConn *addconn = dynamic_cast<WMaxMacAddConn*>(msg)) {
        WMaxQos qos = addconn->getQos(0);

        WMaxConn conn;
        conn.type= qos.connType;
        conn.sfid = 2; /// @todo set sfid
        conn.cid  = addconn->getCid();
        conn.gateIndex = addconn->getGateIndex();
        conn.qos.be.msr = qos.msr; // 100kbps
        conn.qos.be.reqbw = 0;
        conn.bandwidth = 0;
        std::stringstream ss_cid;
        std::string st_cid;
        ss_cid << conn.cid;
        ss_cid >> st_cid;
        std::string name = "SendQueue, CID: " + st_cid;
        conn.queue = new cQueue(name.c_str());
        addConn(conn);

        send(msg, "macOut", 0);  // send add conn msg to CS

        //delete msg;
        return;
    }

    cGate * gate = msg->arrivalGate();
    if (!strcmp(gate->fullName(),"phyIn")) {
	handleRxMessage(msg);
	return;
    }

    // remaining gates must be downlink
    handleTxMessage(msg);
}

void WMaxMacBS::handleRxMessage(cMessage *msg)
{
    if (dynamic_cast<WMaxMsgCDMA*>(msg))
    {
        if (dynamic_cast<WMaxMsgCDMA*>(msg)->getPurpose()==WMAX_CDMA_PURPOSE_BWR) {
            Log(Debug) << " Received CDMA code (purpose=BWR)." << LogEnd;
            CDMAQueue->insert(msg);
            return;
        }
    }

    WMaxMac::handleRxMessage(msg);
}

void WMaxMacBS::schedule()
{
    int symbols = 300; /// @todo - check/calculate how many symbols are available in each frame
    int dlSymbols = symbols/2;
    int ulSymbols = symbols - dlSymbols;

    scheduleBcastMessages();

    WMaxMsgDlMap * dlmap = scheduleDL(dlSymbols);
    WMaxMsgUlMap * ulmap = scheduleUL(ulSymbols);

    printDlMap(dlmap);
    printUlMap(ulmap);

    send(dlmap, "phyOut");
    send(ulmap, "phyOut");

    // trigger PHY to start frame
    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    Log(Debug) << ": Generating FrameStart trigger for PHY" << LogEnd;
    send(frameStart, "phyOut");
}

void WMaxMacBS::scheduleBcastMessages() 
{
    schedDcdCnt++;
    schedUcdCnt++;

    if (schedDcdFreq && schedDcdFreq<=schedDcdCnt++) {
	schedDcdCnt = 0;
	WMaxMsgDCD * dcd = new WMaxMsgDCD("DCD");
	dcd->setName("DCD");
	WMaxMacHeader * hdr = new WMaxMacHeader();
	hdr->cid = WMAX_CID_BROADCAST;
	dcd->setControlInfo(hdr);
	SendQueue.insert(dcd);
    }

    if (schedUcdFreq && schedUcdFreq<=schedUcdCnt++) {
	schedUcdCnt = 0;
	WMaxMsgUCD * ucd = new WMaxMsgUCD("UCD");
	ucd->setName("UCD");
	WMaxMacHeader * hdr = new WMaxMacHeader();
	hdr->cid = WMAX_CID_BROADCAST;
	ucd->setControlInfo(hdr);
	SendQueue.insert(ucd);
    }
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
	Log(Debug) << symbols << " symbols left." << LogEnd;
	
	if (!SendQueue.length()) // nothing more to send
	    break;

	if (symbols <=0)
	    break;

	msg = (cMessage*) SendQueue.tail();

	if (msg->length() > symbols*bytesPerPS) {
	    // message won't fit in this frame. What should we do in such case?

	    Log(Info) << "Tried to schedule message (len=" << msg->length() << ", but there are only "
		      << symbols*bytesPerPS << " bytes left." << LogEnd;

	    if (ieCnt) // something has been scheduled - ok, end scheduling
		break;

	    // what to do, if we have not scheduled anything and the message still doesn't fit?

	    // possible solutions:
	    // a) implement fragmentation (the best one)
	    // b) send message and end scheduling (flaw: sending more than possible)
	    // c) ignore this message and try to scheduler next message, possibly smaller (flaw: message will never be sent)
	    // d) abort simulation as there is no way to send this message

            // currently used: c)
            msg = (cMessage*) SendQueue.pop();
            Log(Error) << "Unable to send " << msg->length() << "-byte message(" << msg->fullName() 
		       << "), because it won't fit in DL subframe. Message is dropped." << endl;
            delete msg;
            continue;

	    // currently used: d)
	    /*opp_error("Unable to send %d-byte long message(%s), because it won't fit in DL subframe (%d symbols *%dB/PS=%d bytes)",
		      msg->length(), msg->fullName(), symbols, bytesPerPS, symbols*bytesPerPS);
	    break;*/
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

	Log(Debug) << "Sent msg: length=" << ie.length << ", used " << lengthInPS << " symbols, " 
		   << symbols << " symbol(s) left" << endl;
	
	send(msg, "phyOut");
    }

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = WMAX_CID_BROADCAST;
    dlmap->setControlInfo(hdr);

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
	ie.cdmaIE.purpose = WMAX_CDMA_PURPOSE_BWR;

	/// @todo - full symbolOffset, ofdmaSymbols, subchannels
	ulmap->setIE(ieCnt-1,ie);
	symbols--; // use just 1 symbol for Bandwidth Requests
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
	ie.cdmaIE.purpose       = WMAX_CDMA_PURPOSE_INITIAL_RNG;
	/// @todo - full symbolOffset, ofdmaSymbols, subchannels
	ulmap->setIE(ieCnt-1,ie);
	symbols--; // use just 1 symbol for Initial Ranging
    }

    if (CDMAQueue->length()) {
	// append IE for allocation of bandwidth to a user that requested bandwidth using a CDMA code
	ieCnt++;
	schedCdmaInitRngCnt=0;
	ulmap->setIEArraySize(ieCnt);
	CLEAR(&ie);
	ie.cid  = WMAX_CID_BROADCAST;
	ie.uiuc = WMAX_ULMAP_UIUC_CDMA_ALLOC;
	WMaxMsgCDMA *msgcdma = (WMaxMsgCDMA*)CDMAQueue->pop();
	ie.cdmaAllocIE.rangingCode = msgcdma->getCode();
	/// @todo - duration, rangingSymbol, rangingSubchannel
	ulmap->setIE(ieCnt-1,ie);
	symbols--; // use just 1 symbol
	delete msgcdma;
    }

    if (schedCdmaHoRngFreq && schedCdmaHoRngFreq<=schedCdmaHoRngCnt++) {
	// append IE for handover ranging
	ieCnt++;
	schedCdmaHoRngCnt=0;
	ulmap->setIEArraySize(ieCnt);
	CLEAR(&ie);
	ie.cid  = WMAX_CID_BROADCAST;
	ie.uiuc = WMAX_ULMAP_UIUC_CDMA_BWR;
	ie.cdmaIE.rangingMethod = WMAX_RANGING_METHOD_INITIAL;
	ie.cdmaIE.purpose       = WMAX_CDMA_PURPOSE_HO_RNG;
	/// @todo - full symbolOffset, ofdmaSymbols, subchannels
	ulmap->setIE(ieCnt-1,ie);
	symbols--; // use just 1 symbol for Initial Ranging
    }
    
    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); it++) {
	if (symbols <=0) {
	    Log(Debug) << "No symbols left, scheduling aborted." << LogEnd;
	    break;
	}

	// for each configured service flow, grant some bandwidth (if necessary)
	switch (it->type) {
/*	case WMAX_CONN_TYPE_BE:
	    /// @todo - best effort not supported yet
	    break;*/
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
		Log(Debug) << ": Adding UGS grant: cid=" << ie.cid << ", bandwith=" << ie.dataIE.duration << ", " 
			   << symbolLength << " symbols." << LogEnd;
		break;
	    }
	    
	}
	}
    }

    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); it++) {
	if (symbols <=0) {
	    Log(Debug) << "No symbols left, scheduling aborted." << LogEnd;
	    break;
	}
	switch (it->type) {

        case WMAX_CONN_TYPE_BE:
	    it->bandwidth += it->qos.be.reqbw;
            it->qos.be.reqbw = 0;
	    int symbolLength = (int)ceil(double(it->bandwidth)/bytesPerPS);
	    if ( (it->bandwidth>=WMAX_SCHED_MIN_GRANT_SIZE) && (symbols>=symbolLength) ) {
		symbols -= symbolLength;

		ieCnt++;
		ulmap->setIEArraySize(ieCnt);
		WMaxUlMapIE ie;
		CLEAR(&ie);
		ie.uiuc = WMAX_ULMAP_UIUC_DATA_2;
		ie.cid = it->cid;
		ie.dataIE.duration = it->bandwidth;
		ulmap->setIE(ieCnt-1, ie);
		it->bandwidth = 0;
		Log(Debug) << ": Adding BE grant: cid=" << ie.cid << ", bandwith=" << ie.dataIE.duration << ", " 
			   << symbolLength << " symbols." << LogEnd;
		break;
	    }

	}
    }    

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = WMAX_CID_BROADCAST;
    ulmap->setControlInfo(hdr);

    return ulmap;
}

/** 
 * method used to process received (RX) message (i.e. received from PHY, handled to MAC)
 * 
 * @param msg 
 */
void WMaxMac::handleRxMessage(cMessage *msg)
{
    int cid = -1;
    int gateIndex = -1;
    if (dynamic_cast<WMaxMacHeader*>(msg->controlInfo())) {
	WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->controlInfo());
	cid = hdr->cid;

        // bandwidth request
        if (hdr->ht == true) {
	    Log(Debug) << "Received bandwidth request, CID=" << hdr->cid << " bandwidth: " << hdr->bwr << LogEnd;
            for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	        if (it->cid == hdr->cid) {
	            it->qos.be.reqbw = hdr->bwr;
		    delete msg;
		    return;
	        }
            }
	    Log(Error) << "Received BWR for unknown (cid=" << hdr->cid << ") connection. Ignored." << LogEnd;
            delete msg;
            return;
        }
    } else {
	Log(Error) << "Malformed message received: " << msg->fullName() 
		   << ". WMaxMacHeader structure missing." << LogEnd;
	return;
    }

    if (cid==WMAX_CID_BROADCAST)
	return;

    // check if there is such connection (cid has to match)
    for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	if (it->cid == cid) {
	    gateIndex = it->gateIndex;
	    break;
	}
    }

    if (gateIndex != -1) {
	Log(Debug) << "Sending message to upper (IPv6) layer (CID=" << cid << ", gateIndex=" 
	   << gateIndex << ")" << LogEnd;
	send(msg, "macOut", gateIndex);
    } else {
	Log(Warning) << "Unable to find connection for CID=" << cid << ", message dropped." << LogEnd;
        delete msg;
    }
}

/********************************************************************************/
/*** WMax Mac SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacSS);

void WMaxMacSS::initialize()
{
    BEpoint = 0;
    SendQueue.setName("SendQueue");
    CLEAR(&Stats);

    // Create permanent INITIAL-RANGING connection
    addRangingConn();


    WATCH_LIST(CDMAlist);
}

void WMaxMac::addRangingConn()
{
    int conns = gateSize("macOut");
    int i = conns - 1; // control connection
    WMaxConn conn;
    CLEAR(&conn);
    conn.type= WMAX_CONN_TYPE_BE;
    conn.sfid = 0; // not important/not used
    conn.cid = 0; // CID=0 (well known CID for initial ranging)
    conn.gateIndex = i;
    conn.qos.be.msr = 80000; // 100kbps
    conn.qos.be.reqbw = 0;
    conn.bandwidth = 0;
    std::stringstream ss_cid;
    std::string st_cid;
    ss_cid << conn.cid;
    ss_cid >> st_cid;
    std::string name = "SendQueue, CID: " + st_cid;
    conn.queue = new cQueue(name.c_str());
    addConn(conn);
    Log(Debug) << "Initial-ranging connection added." << LogEnd;
}

void WMaxMacSS::handleMessage(cMessage *msg)
{
    cGate * gate = msg->arrivalGate();

    if (dynamic_cast<WMaxMacTerminateAllConns*>(msg)) {
        Log(Notice) << "All connections terminated." << LogEnd;

        list<WMaxConn>::iterator it;
        for (it = Conns.begin(); it!=Conns.end(); it++) {
            it->queue->clear();
            delete it->queue;
        }
        Conns.clear();
        send(msg, "macOut", 0);
        initialize();
        return;
    }

    if (WMaxMacAddConn *addconn = dynamic_cast<WMaxMacAddConn*>(msg)) {
        WMaxQos qos = addconn->getQos(0);

        WMaxConn conn;
        conn.type= qos.connType;
        conn.sfid = 2; /// @todo set sfid
        conn.cid  = addconn->getCid();
        conn.gateIndex = addconn->getGateIndex();
        conn.qos.be.msr = qos.msr; // 100kbps
        conn.qos.be.reqbw = 0;
        conn.bandwidth = 0;
        std::stringstream ss_cid;
        std::string st_cid;
        ss_cid << conn.cid;
        ss_cid >> st_cid;
        std::string name = "SednQueue, CID: " + st_cid;
        conn.queue = new cQueue(name.c_str());
        addConn(conn);

        send(msg, "macOut", 0);  // send add conn msg to CS
        return;
    }

    Log(Debug) << "Message " << msg->fullName() << " received on gate: " << gate->fullName() << endl;
    if (strcmp(gate->fullName(),"phyIn")) {
        //"phyIn gate: downlink (BS->SS)
	handleTxMessage(msg);
	return;
    } else
    { // "macIn" remaining gates must be uplink (SS -> BS)
	handleRxMessage(msg);
	return;
    }
}

/** 
 * method used to handle to-be-transmitted (TX) message (i.e. received from MAC, to be sent to PHY)
 * 
 * @param msg 
 */
void WMaxMac::handleTxMessage(cMessage *msg)
{

/// @todo find proper connection 
     cGate * gate = msg->arrivalGate();
     list<WMaxConn>::iterator it;

     // message from WMaxCtrl - add header
     if (!msg->controlInfo()) {
	 for (it = Conns.begin(); it!=Conns.end(); it++) {
	     if ((it->gateIndex == gate->index()) && (it->controlConn == true)) {
		 WMaxMacHeader * hdr = new WMaxMacHeader();
		 hdr->cid = it->cid;
		 msg->setControlInfo(hdr);
		 break;
	     }
	 }
     }

    WMaxMacHeader * hdr = 0;
    hdr = dynamic_cast<WMaxMacHeader*>(msg->controlInfo());

    // find proper connection, not just get first one
    for (it = Conns.begin(); it!=Conns.end(); it++) {
	if (it->cid == hdr->cid) {
	    break;
	}
    }
    if (it==Conns.end()) {
	Log(Error) << "Unable to find connection for CID=" << hdr->cid << LogEnd;
        delete msg;
	return;
    }

//    if (dynamic_cast<WMaxMacSS*>(this)) {
    if (!strcmp(fullName(), "ssMac")) {
	switch(it->type) {
	case WMAX_CONN_TYPE_BE:
	    Log(Debug) << "Received BE message (CID=" << it->cid << ", gateIndex=" << gate->index() << ", length=" << msg->length() << ") ";
	    it->qos.be.reqbw += msg->length();
	    if(msg->length() == 0) { /// @todo sending messages with length == 0
		it->qos.be.reqbw += 12;
	    }
	    Log(Cont) << "CID=" << it->cid << " Required bandwidth: " << it->qos.be.reqbw << LogEnd; 
	    it->queue->insert(msg);
	    break;
	case WMAX_CONN_TYPE_UGS:
	    Log(Debug) << "Queueing message (CID=" << it->cid << ", gateIndex=" << gate->index() << ", length=" << msg->length() << ")." << LogEnd;
	    SendQueue.insert(msg);
	    break;
	}
    } else {
        Log(Debug) << "Queueing message (CID=" << it->cid << ", gateIndex=" << gate->index() << ", length=" << msg->length() << ")." << LogEnd;
        SendQueue.insert(msg);
    }

}

void WMaxMacSS::handleRxMessage(cMessage *msg)
{
    bool bcastMsg = false; // is this a broadcast message?
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	WMaxMsgUlMap * ulmap = dynamic_cast<WMaxMsgUlMap*>(msg);
	printUlMap(ulmap);
	Stats.ulmaps++;
	bcastMsg = true;

	schedule(ulmap);
    }
    if (dynamic_cast<WMaxMsgDCD*>(msg)) {
	bcastMsg = true;
    }
    if (dynamic_cast<WMaxMsgUCD*>(msg)) {
	bcastMsg = true;
    }

    if (bcastMsg) {
	// handle this map to WMaxCtrl
	list<WMaxConn>::iterator it;
	for (it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->controlConn) {
		// ev << fullName() << "Dispatching " << msg->fullName() << " to gate " << it->gateIndex 
		// << ", ctrl=" << ((int)(it->controlConn)) << endl;
		cMessage * copy = (cMessage*)msg->dup();
		send(copy, "macOut", it->gateIndex);
	    }
	}

	delete msg;
	return;
    }

    if (dynamic_cast<WMaxMsgDlMap*>(msg)) {
	printDlMap(dynamic_cast<WMaxMsgDlMap*>(msg));
	Stats.dlmaps++;
	WMaxMsgDlMap* dlmap = dynamic_cast<WMaxMsgDlMap*>(msg);
	Log(Debug) << "DL-MAP received: expecting " << dlmap->getIEArraySize() << " messages in this frame." << LogEnd;

	// handle this map to WMaxCtrl
	list<WMaxConn>::iterator it;
	for (it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->controlConn) {
		Log(Debug) << "Dispatching dlmap to gate " << it->gateIndex << ", ctrl=" << ((int)(it->controlConn)) << LogEnd;
		send(msg, "macOut", it->gateIndex);
	    }
	}

	// @todo - delete dlmap
	// delete msg;
	return;
    }

    WMaxMac::handleRxMessage(msg);
}

void WMaxMacSS::schedule(WMaxMsgUlMap * ulmap)
{
    int bandwidth = 0;
    Log(Debug) << "UL-MAP received with " << ulmap->getIEArraySize() << " IE(s)." << LogEnd;
    int i;
    for (i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE & ie = ulmap->getIE(i);
	for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->cid==ie.cid) {
		if (ie.uiuc>=WMAX_ULMAP_UIUC_DATA_1 || ie.uiuc<=WMAX_ULMAP_UIUC_DATA_10) {
		    bandwidth = ie.dataIE.duration;
		    Stats.grants++;

                    int bytesPerPS = WMAX_BYTES_PER_SYMBOL; // this depends on modulation used, use 12 bytes/symbol for now
                    int lengthInPS;
                    cMessage * msg;
                    int ieCnt = 0;
                    int symbols = (int)ceil(double(bandwidth)/bytesPerPS);

                    if (it->type == WMAX_CONN_TYPE_BE && it->queue->length() && bandwidth){

                    while (true) {
			Log(Debug) << symbols << " symbols left." << LogEnd;

	                 if (!it->queue->length()) // nothing more to send
	                 break;

	                 if (symbols <=0)
	                 break;

	                 msg = (cMessage*) it->queue->tail();

	                 if (msg->length() > symbols*bytesPerPS) {
	                 // message won't fit in this frame. What should we do in such case?
	                     Log(Info) << "Tried to schedule message (len=" << msg->length() << ", but there are only " 
				       << symbols*bytesPerPS << " bytes left." << LogEnd;

	                     if (ieCnt) // something has been scheduled - ok, end scheduling
		                 break;

                             // currently used: c)
                             msg = (cMessage*) it->queue->pop();
                             Log(Error) << "Unable to send " << msg->length() << "-byte message(" << msg->fullName() 
					<<"), because it won't fit in UL subframe. Message is dropped." << LogEnd;
                             delete msg;
                             continue;

                             // currently used: d)
	                     /*opp_error("Unable to send %d-byte long message(%s), because it won't fit in UL subframe (%d symbols *%dB/PS=%d bytes)",
		             msg->length(), msg->fullName(), symbols, bytesPerPS, symbols*bytesPerPS);
	                     break;*/
	                 }

	                 // message will fit in this frame, send it
	                 ieCnt++;

                         msg = (cMessage*)it->queue->pop();
                         lengthInPS = (int)ceil(double(msg->length())/bytesPerPS);
	
                         symbols -= lengthInPS;
	
                         WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->controlInfo());
	                 if (!hdr)
	                      opp_error("Unable to obtain header information for message: %s\n", msg->fullName());

	                 Log(Debug) << "Sent msg: length=" << msg->length() << ", used " << lengthInPS << " symbols, " 
				    << symbols << " symbol(s) left" << LogEnd;
	
	                 send(msg, "phyOut");
                    }
                    }

		}/* else 
                if (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_BWR) {


		} else
                if (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_ALLOC) {


		}*/
	    }
	    
	}

        if (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_BWR && ie.cdmaIE.rangingMethod==WMAX_RANGING_METHOD_BWR) { 

            for (int i=0; i!=Conns.size(); i++) {

                list<WMaxConn>::iterator BEit = Conns.begin();
                for (int j=0; j!=BEpoint; j++){
                    BEit++;
                    if (BEit == Conns.end())
                        BEit = Conns.begin();
                }

                BEpoint++;
                BEpoint = BEpoint%Conns.size();

                if (BEit->type == WMAX_CONN_TYPE_BE) {
                    if (BEit->qos.be.reqbw) {
                        WMaxMacCDMA cdma;
                        cdma.code = rand()%256;
                        cdma.bandwidth = BEit->qos.be.reqbw;
                        BEit->qos.be.reqbw = 0;
                        cdma.cid = BEit->cid;
                        CDMAlist.push_back(cdma);
                        WMaxMsgCDMA *cdmamsg = new WMaxMsgCDMA("CDMA");
                        cdmamsg->setCode(cdma.code);
                        cdmamsg->setPurpose(WMAX_CDMA_PURPOSE_BWR);
                        Log(Debug) << "Sending CDMA code: " << cdma.code <<" (cid: " << cdma.cid << ", bandwidth: "
				   << cdma.bandwidth << ")" << LogEnd;
                        send(cdmamsg, "phyOut");
                        break;
                    }
                }
            }


        }

        if (ie.uiuc==WMAX_ULMAP_UIUC_CDMA_ALLOC) {
           for (list<WMaxMacCDMA>::iterator it = CDMAlist.begin(); it!=CDMAlist.end(); it++) {
               if (it->code == ie.cdmaAllocIE.rangingCode){
                   WMaxMacHeader *hdr = new WMaxMacHeader();
                   hdr->ht = true;
                   hdr->bwr = it->bandwidth;

                   for (list<WMaxConn>::iterator it2=Conns.begin(); it2!=Conns.end(); it2++) {
                       if (it2->cid == it->cid){
                           if (!it2->queue->empty()) {
                               cMessage * msg = (cMessage*) it2->queue->tail();
                               if(hdr->bwr < msg->length())
                                   hdr->bwr = msg->length();
                           }
                       }
                   }

                   hdr->cid = it->cid;
                   WMaxMsgBWR *msg = new WMaxMsgBWR("Bandwidth request");
                   msg->setControlInfo(hdr);
                   Log(Debug) << "Sending Bandwidth request (bandwidth: " << hdr->bwr << ", cid: "  << hdr->cid << ")" << LogEnd;
                   send(msg, "phyOut");
                   CDMAlist.erase(it);
                   break;
               }
           }
	}

    }


    if (SendQueue.length()) {
	cMessage * msg = (cMessage*)SendQueue.pop();
	send(msg, "phyOut");
    }

    Stats.bandwidth += bandwidth;

    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
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
