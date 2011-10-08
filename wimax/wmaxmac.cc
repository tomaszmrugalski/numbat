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
#include <math.h>
#include "wmaxmac.h"
#include "wmaxmsg_m.h"
#include "wmaxctrl.h"
#include "logger.h"

#include "IInterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "InterfaceEntry.h"
#include "MACAddress.h"

#define MK_HANDOVER_NOTIFY_ACK      101 // Adam
using namespace std;

Register_Class(WMaxMacHeader);


ostream & operator<<(ostream & strum, WMaxMacCDMA &x) {
    strum << "code=" << x.code << " bandwidth=" << x.bandwidth << " cid=" << x.cid;
    return strum;
}

ostream & operator<<(ostream & s, WMaxConn &x) {
    s << "type=" << x.type << " sfid=" << x.sfid << " cid=" << x.cid;
    
    switch (x.type) {
    case WMAX_CONN_TYPE_BE:
	s << " qos=[BE, msr=" << x.qos.be.msr << "]";
	break;
    case WMAX_CONN_TYPE_UGS:
	s << " qos=[UGS, msr=" << x.qos.ugs.msr << ", latency=" << x.qos.ugs.latency << ", jitter=" << x.qos.ugs.jitter << "]";
	break;
    default:
	break;
    }

    s << " runtime:[ bandwidth=" << x.bandwidth << "] gateIndex=" << x.gateIndex << " controlConn=" << (x.controlConn?"YES":"NO");
    return s;
}

/********************************************************************************/
/*** ssMAC compound module ******************************************************/
/********************************************************************************/

Define_Module(ssMAC);

void ssMAC::updateString() {
    //cout << "a";
    if (!ev.isGUI()) 
	return;
    cModule *SS = getParentModule();
    cModule *macSS = getSubmodule("ssMac");
    char buf[80];
    sprintf(buf, "%s%d", getFullName(), SS->getIndex());
    cModule *ctrlSS = getSubmodule(buf);
    char buf1[80];
    sprintf(buf1, "%s\n%s", (macSS->getDisplayString()).getTagArg("t",0), (ctrlSS->getDisplayString()).getTagArg("t",0));
    getDisplayString().setTagArg("t",0, buf1);
    //cout << "b";
}

void ssMAC::initialize()
{
    //cout << "c";
    cModule *SS = getParentModule();
    char buf[80];
    sprintf(buf, "%s%d", getFullName(), SS->getIndex());
    setName(buf);
    //cout << "d";    
}

/********************************************************************************/
/*** WMax Mac (common for BS/SS) ************************************************/
/********************************************************************************/
WMaxMac::WMaxMac()
{
    //cout << "e";
    GateIndex = 0;
    queuedMsgsCnt = 0;
    this->CDMAQueue = new cQueue("CDMAQueue");

    WATCH_LIST(Conns);
    //cout << "f";    
}

void WMaxMac::stringUpdate() {
    //cout << "g";
    if (ev.isGUI()) {
	// count all messages in the queue

        stringstream displayIt;
        displayIt << queuedMsgsCnt << "msgs in " << (int)Conns.size() << " queues.";
        getDisplayString().setTagArg("t",0, (displayIt.str()).c_str());
    }
    //cout << "h";    
}

bool WMaxMac::addConn(WMaxConn conn)
{
    //cout << "i";
    std::stringstream ss_cid;
    std::string st_cid;
    ss_cid << conn.cid;
    ss_cid >> st_cid;
    std::string name = "SendQueue, CID: " + st_cid;
    conn.queue = new cQueue(name.c_str());

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
    target = target->getNextGate();
    cModule * owner = target->getOwnerModule();

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
		<< ", connected to: " << owner->getFullName() << LogEnd;

    /// @todo - check if CID and sfid are unique
    Conns.push_back(conn);

    //setDisplayString("Conns"); // this doesn't work. Strange
    //cout << "j";    
    return true;
}
 
bool WMaxMac::delConn(uint16_t cid)
{
    //cout << "k";
    for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	if (it->cid==cid) {
	    delete it->queue;
	    Conns.erase(it);
	    Log(Notice) << "Connection (cid=" << cid << ") removed." << LogEnd;
        //cout << "l";        
	    return true;
	}
    }
    //cout << "m";
    Log(Error) << "Unable to delete connection with cid=" << cid << "." << LogEnd;
    return false;
}


void WMaxMac::printDlMap(WMaxMsgDlMap * dlmap)
{
    //cout << "n";            
    Log(Debug) << " --- DL-MAP (" << dlmap->getIEArraySize() << " IE(s) ---" << LogEnd;
    if (!logger::willPrint(logger::Debug)){
        //cout << "o";            
        return;
    }

    for (unsigned int i=0; i<dlmap->getIEArraySize(); i++) {
	WMaxDlMapIE &ie = dlmap->getIE(i);
	Log(Debug) << "IE[" << i << "]: cid=" << ie.cid << ", length=" << ie.length << ", symbols=" << ie.symbols << LogEnd;
    }
    //cout << "p";            
}

void WMaxMac::printUlMap(WMaxMsgUlMap * ulmap)
{
    //cout << "r";        
    Log(Debug) << " --- UL-MAP: " << ulmap->getIEArraySize() << " IE(s) ---" << LogEnd;
    if (!logger::willPrint(logger::Debug)){
        //cout << "s";                
        return;
    }

    for (unsigned int i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE &ie = ulmap->getIE(i);
	Log(Debug) << "IE[" << i << "]: cid=" << ie.cid << ", uiuc=" << ie.uiuc;

	switch (ie.uiuc) {
	case WMAX_ULMAP_UIUC_FAST_FEEDBACK:
	case WMAX_ULMAP_UIUC_EXTENDED2:
	case WMAX_ULMAP_UIUC_PAPR:
	case WMAX_ULMAP_UIUC_EXTENDED:
	    Log(Cont) << " NOT SUPPORTED IE TYPE";
	    break;
	case WMAX_ULMAP_UIUC_CDMA_BWR: {
	    int a = (int)ie.cdmaIE.symbolOffset;
	    int b = (int)ie.cdmaIE.ofdmaSymbols;
	    int c = (int)ie.cdmaIE.subchannels;
	    int d = (int)ie.cdmaIE.rangingMethod;
	    Log(Cont) << "(CDMA BWR): symbolOffset=" << a << " ofdmaSymbols=" << b
		      << " subchannels=" << c << " rangingMethod=" << d;
	    switch (ie.cdmaIE.rangingMethod) {
	    case WMAX_RANGING_METHOD_INITIAL: 
		Log(Cont) << "initial ranging";
		break;
	    case WMAX_RANGING_METHOD_BWR:
		Log(Cont) << "bandwidth request";
		break;
	    default:
		Log(Cont) << "[unknown ranging method]";
	    }
	    break;
	}
	case WMAX_ULMAP_UIUC_CDMA_ALLOC:
	    Log(Cont) << "(CDMA ALLOCATION): duration=" << (int)ie.cdmaAllocIE.duration << " uiuc=" << (int)ie.cdmaAllocIE.uiuc
		      << " rangingCode=" << (int)ie.cdmaAllocIE.rangingCode << " rangingSymbol=" << (int)ie.cdmaAllocIE.rangingSymbol
		      << " rangingSubchannel=" << (int)ie.cdmaAllocIE.rangingSubchannel;
	    break;
	default:
	    Log(Cont) << "(DATA): duration=" << (int)ie.dataIE.duration;
	    break;
	}
	Log(Cont) << LogEnd;
    }
    //cout << "t";            
}

/********************************************************************************/
/*** WMax Mac BS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacBS);

void WMaxMacBS::setInitialPosition() {
    //cout << "u";        
    cDisplayString dispstr = BS->getDisplayString();
    long int x = BS->par("x");
    long int y = BS->par("y");
    dispstr.setTagArg("p", 0, x);
    dispstr.setTagArg("p", 1, y);
    BS->setDisplayString(dispstr);

    char buf[80];
    sprintf(buf, "(%s,%s)", (BS->getDisplayString()).getTagArg("p",0), (BS->getDisplayString()).getTagArg("p",1));
    BS->getDisplayString().setTagArg("t",0, buf);
    //cout << "w";            
}

void WMaxMacBS::initialize()
{
    //cout << "x";        
    BS = getParentModule()->getParentModule();

    setInitialPosition();

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

    char buf[80];
    sprintf(buf, "%s%d", getFullName(), BS->getIndex());
    setName(buf);

    // Create permanent INITIAL-RANGING connection
    addRangingConn();
    registerInterface(75.0);
    //cout << "y";        
}

void WMaxMacBS::registerInterface(double txrate)
{
    //cout << "z";    
    ssInfo ssinfo;
    IInterfaceTable *ift = InterfaceTableAccess().getIfExists();
    if (!ift){
        //cout << "A";            
        return;
    }

    InterfaceEntry * interfaceEntry = new InterfaceEntry();


    // interface name: our module name without special characters ([])
    char *interfaceName = new char[strlen(getParentModule()->getParentModule()->getFullName())+1];
    char *d=interfaceName;
    for (const char *s=getParentModule()->getParentModule()->getFullName(); *s; s++)
        if (isalnum(*s))
            *d++ = *s;
    *d = '\0';

    interfaceEntry->setName(interfaceName);
	string masterifname =  interfaceName;
    delete [] interfaceName;

    // data rate
    interfaceEntry->setDatarate(txrate);

    interfaceEntry->setMtu(1500);

    // capabilities
    interfaceEntry->setMulticast(true);
    interfaceEntry->setBroadcast(true);

    MACAddress addr = MACAddress::generateAutoAddress();
    interfaceEntry->setMACAddress(addr);
    interfaceEntry->setInterfaceToken(addr.formInterfaceIdentifier());

    // add
    ift->addInterface(interfaceEntry, this);
    //cout << "B";
}

void WMaxMacBS::handleMessage(cMessage *msg)
{
    //cout << "C";
    if (msg==TxStart) {
        schedule();
        scheduleAt(simTime()+FrameLength, TxStart);
        // cout << "D";    
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
        addConn(conn);

        send(msg, "macOut", 0);  // send add conn msg to CS

        //delete msg;
        //cout << "E";
        return;
    }

    if (WMaxMacAddMngmntConn *addconn = dynamic_cast<WMaxMacAddMngmntConn*>(msg)) {
        uint16_t cid = addconn->getCid();
        addManagementConn(cid);
        delete msg;
        //cout << "F";        
        return;
    }

    if (WMaxEvent_DelConn* delconn = dynamic_cast<WMaxEvent_DelConn*>(msg)) {
        delConn(delconn->getCid());
	
        send(msg, "macOut", 0); // send delConn to CS
        //cout << "G";    
        return;
    }

    cGate * gate = msg->getArrivalGate();
    if (!strcmp(gate->getFullName(),"phyIn")) {
        handleRxMessage(msg);
        //cout << "H";
        return;
    }

    // remaining gates must be downlink
    handleTxMessage(msg);
    //cout << "I";
}

void WMaxMacBS::handleRxMessage(cMessage *msg)
{
    //cout << "J";
    if (dynamic_cast<WMaxMsgCDMA*>(msg))
    {
	WMaxMsgCDMA * cdma = dynamic_cast<WMaxMsgCDMA*>(msg);
        if (cdma->getPurpose()==WMAX_CDMA_PURPOSE_BWR) 
	{
            Log(Debug) << "Received CDMA code " << cdma->getCode() << " (purpose=BWR)." << LogEnd;
            CDMAQueue->insert(msg);
            //cout << "K";
            return;
        }
    }

    WMaxMac::handleRxMessage(msg);
    //cout << "L";
}

void WMaxMacBS::schedule()
{
    //cout << "7";
    int symbols = 48; // 48 symbols per frame
    int dlSymbols = symbols/2;
    int ulSymbols = symbols - dlSymbols;
    int subchannels = 60;

    scheduleBcastMessages();

    WMaxMsgDlMap * dlmap = scheduleDL(dlSymbols*subchannels);
    WMaxMsgUlMap * ulmap = scheduleUL(ulSymbols*subchannels);

    printDlMap(dlmap);
    printUlMap(ulmap);

    send(dlmap, "phyOut");
    send(ulmap, "phyOut");

    // trigger PHY to start frame
    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    // Log(Debug) << "Generating FrameStart trigger for PHY" << LogEnd;
    send(frameStart, "phyOut");
    //cout << "8";
}

void WMaxMacBS::scheduleBcastMessages()
{
    //cout << "5";
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
	queuedMsgsCnt++;
    }

    if (schedUcdFreq && schedUcdFreq<=schedUcdCnt++) {
	schedUcdCnt = 0;
	WMaxMsgUCD * ucd = new WMaxMsgUCD("UCD");
	ucd->setName("UCD");
	WMaxMacHeader * hdr = new WMaxMacHeader();
	hdr->cid = WMAX_CID_BROADCAST;
	ucd->setControlInfo(hdr);
	SendQueue.insert(ucd);
	queuedMsgsCnt++;
    }
    //cout << "6";    
}


/** 
 * schedules downlink traffic
 * 
 * 
 * @return 
 */
WMaxMsgDlMap * WMaxMacBS::scheduleDL(int symbols)
{
    //cout << "3";
    int startSymbols = symbols;
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

	msg = (cMessage*) SendQueue.front();
	
	//msg does not have getByteLenght() so cast it to cPacket.... (MiM)

	if (check_and_cast<cPacket *>(msg)->getByteLength() > symbols*bytesPerPS) {
	    // message won't fit in this frame. What should we do in such case?

	  Log(Debug) << "Tried to schedule message (len=" << check_and_cast<cPacket *>(msg)->getByteLength() << "), but there are only "
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
	    queuedMsgsCnt--;
            Log(Error) << "Unable to send " << check_and_cast<cPacket *>(msg)->getByteLength() << "-byte message(" << msg->getFullName() 
		       << "), because it won't fit in DL subframe. Message is dropped." << endl;
            delete msg;
            continue;

	    // currently used: d)
	    /*opp_error("Unable to send %d-byte long message(%s), because it won't fit in DL subframe (%d symbols *%dB/PS=%d bytes)",
		      msg->getByteLength(), msg->getFullName(), symbols, bytesPerPS, symbols*bytesPerPS);
	    break;*/
	}
	
	// message will fit in this frame, send it
	ieCnt++;
	dlmap->setIEArraySize(ieCnt);
	
	/// @todo - DL-MAP generation
	
	msg = (cMessage*)SendQueue.pop();
	queuedMsgsCnt--;

	lengthInPS = (int)ceil(double(check_and_cast<cPacket *>(msg)->getByteLength())/bytesPerPS);
	symbols -= lengthInPS;
	
	WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->getControlInfo());
	if (!hdr)
	    opp_error("Unable to obtain header information for message: %s\n", msg->getFullName());
	CLEAR(&ie);
	ie.length  = check_and_cast<cPacket *>(msg)->getByteLength();
	ie.cid     = hdr->cid;
	ie.symbols = lengthInPS;
	dlmap->setIE(ieCnt-1,ie);

	Log(Debug) << "Sent msg: length=" << ie.length << ", used " << lengthInPS << " symbols, " 
		   << symbols << " symbol(s) left" << endl;
	
	send(msg, "phyOut");
    }

    Log(Debug) << "DL schedule: " << startSymbols << " symbols available for DL, " << startSymbols-symbols << " used." << LogEnd;
    if (symbols<=0)
    {
	Log(Warning) << "Full DL frame, " << startSymbols << " were available, " << symbols << " left." << LogEnd;
    }

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = WMAX_CID_BROADCAST;
    dlmap->setControlInfo(hdr);

    stringUpdate();
    //cout << "4";
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
    //cout << "M";
    int startSymbols = symbols;
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
	for (i=0; i<CDMAQueue->length(); i++) {
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
	    delete msgcdma;
	    symbols--; // use just 1 symbol
	    if (symbols==0)
		break;
	}
    }

    if (symbols && schedCdmaHoRngFreq && schedCdmaHoRngFreq<=schedCdmaHoRngCnt++) {
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
        case WMAX_CONN_TYPE_BE:
        {
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
            Log(Debug) << "Adding BE grant: cid=" << ie.cid << ", bandwith=" << ie.dataIE.duration << ", " 
                   << symbolLength << " symbols." << LogEnd;
            }
            break;
        }
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
        default:
            // other traffic types are not supproted
            break;
	}
    }    

    Log(Debug) << "UL schedule: " << startSymbols << " symbols available for DL, " << startSymbols-symbols << " used." << LogEnd;
    if (symbols<=0)
    {
	Log(Warning) << "Full UL frame, " << startSymbols << " were available, " << symbols << " used." << LogEnd;
    }

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = WMAX_CID_BROADCAST;
    ulmap->setControlInfo(hdr);
    //cout <<"2";
    return ulmap;
}

void WMaxMacBS::finish()
{
    //cout << "1";
    delete CDMAQueue;
    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); ++it)
    {
	delete it->queue;
    }
    Conns.clear();
    //cout << "N";
}


/** 
 * method used to process received (RX) message (i.e. received from PHY, handled to MAC)
 * 
 * @param msg 
 */
void WMaxMac::handleRxMessage(cMessage *msg)
{
    //cout << "O";
    int cid = -1;
    int gateIndex = -1;
    if (dynamic_cast<WMaxMacHeader*>(msg->getControlInfo())) {
        WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->getControlInfo());
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
            //cout << "R";
            return;
        }
    } else {
        Log(Error) << "Malformed message received: " << msg->getFullName() 
		   << ". WMaxMacHeader structure missing." << LogEnd;
        return;
    }

    if (cid==WMAX_CID_BROADCAST){
        //cout << "P";
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
        Log(Debug) << "Sending message to upper (IPv6) layer (CID=" << cid << ", gateIndex=" 
           << gateIndex << ")" << LogEnd;
        send(msg, "macOut", gateIndex);
    } else {
        Log(Debug) << "Unable to find connection for CID=" << cid << ", message dropped." << LogEnd;
        STAT_INC(dropInvalidCid);
        delete msg;
    }
    //cout << "S";
}

/********************************************************************************/
/*** WMax Mac SS ****************************************************************/
/********************************************************************************/
Define_Module(WMaxMacSS);

void WMaxMacSS::initialize()
{
    //cout << "T";
    SS = getParentModule()->getParentModule();
    BEpoint = 0;
    SendQueue.setName("SendQueue");
    CLEAR(&Stats);

    ChangePosition = 0;

    // Create permanent INITIAL-RANGING connection
    addRangingConn();

    WATCH_LIST(CDMAlist);

    setInitialPosition();

    int isMobile = (int)SS->par("wmaxIsMobile");
    if (isMobile>0) {
        SS->getDisplayString().setTagArg("i",0,"device/laptop_s");

        if(isMobile==2) { // 2 = SS movement
          ChangePosition = new cMessage("ChangePosition");
          scheduleAt(0.0, ChangePosition);
        }
    }

    char buf[80];
    sprintf(buf, "%s%d", getFullName(), SS->getIndex());
    setName(buf);
    
    registerInterface(75.0);
    //cout << "T";
}

void WMaxMacSS::setInitialPosition() {
    //cout << "U";
    cDisplayString dispstr = SS->getDisplayString();
    long int x,y;
    if ((long int)SS->par("x")) {
        x = (long int)SS->par("x");
    } else {
	// expand 50,50,p,300 in physim.ned
	int multi = atoi(SS->getDisplayString().getTagArg("p",3));
        x = atoi(SS->getDisplayString().getTagArg("p", 0));
	x = x + multi*SS->getIndex();
    }
    if ((long int)SS->par("y")) {
        y = (long int)SS->par("y");
    } else {
        y = atoi(SS->getDisplayString().getTagArg("p", 1));
    }
    dispstr.setTagArg("p", 0, x);
    dispstr.setTagArg("p", 1, y);
    dispstr.setTagArg("p", 2, "");
    dispstr.setTagArg("p", 3, "");
    SS->setDisplayString(dispstr);

    char buf[80];
    sprintf(buf, "(%ld,%ld)", x, y );

    SS->getDisplayString().setTagArg("t",0, buf);
    //cout << "W";
}

void WMaxMacSS::registerInterface(double txrate)
{
    //cout << "Y";
    ssInfo ssinfo;
    IInterfaceTable *ift = InterfaceTableAccess().getIfExists();
    if (!ift)
        return;

    InterfaceEntry * interfaceEntry = new InterfaceEntry();


    // interface name: our module name without special characters ([])
    char *interfaceName = new char[strlen(getParentModule()->getParentModule()->getFullName())+1];
    char *d=interfaceName;
    for (const char *s=getParentModule()->getParentModule()->getFullName(); *s; s++)
        if (isalnum(*s))
            *d++ = *s;
    *d = '\0';

    interfaceEntry->setName(interfaceName);
	string masterifname =  interfaceName;
    delete [] interfaceName;

    // data rate
    interfaceEntry->setDatarate(txrate);

    interfaceEntry->setMtu(1500);

    // capabilities
    interfaceEntry->setMulticast(true);
    interfaceEntry->setBroadcast(true);

    char* ch = new char[ strlen(ssinfo.info.getMac().c_str()) ];
    strcpy (ch, ssinfo.info.getMac().c_str());
    MACAddress addr = MACAddress(ch);
    interfaceEntry->setMACAddress(addr);
    interfaceEntry->setInterfaceToken(addr.formInterfaceIdentifier());
    // add
    ift->addInterface(interfaceEntry, this);
    //cout << "X";
}

void WMaxMac::addRangingConn()
{
    //cout << "Z";
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
    addConn(conn);
    
    Log(Debug) << "Initial-ranging connection added." << LogEnd;
    //cout << "~";
}

void WMaxMac::addManagementConn(uint16_t cid)
{
    //cout << "`";
    int conns = gateSize("macOut");
    int i = conns - 1; // control connection
    WMaxConn conn;
    CLEAR(&conn);
    conn.type= WMAX_CONN_TYPE_BE;
    conn.sfid = 0; // not important/not used
    conn.cid = cid;
    conn.gateIndex = i;
    conn.qos.be.msr = 80000; // 100kbps
    conn.qos.be.reqbw = 0;
    conn.bandwidth = 0;
    addConn(conn);
    Log(Notice) << "Management connection added. CID: " << cid << LogEnd;
    //cout << "!";
}


void WMaxMacSS::handleMessage(cMessage *msg)
{
    //cout << "@";
    stringstream tmp;
    tmp << "ssMac[" << SS->getIndex() << "]";
    if (ssMAC *mac = dynamic_cast<ssMAC*>(SS->getSubmodule(tmp.str().c_str())))
	mac->updateString();

    if (msg==ChangePosition) {
        changePosition();
        scheduleAt(simTime()+1, ChangePosition);
        //cout << "#";
        return;
    }
    cGate * gate = msg->getArrivalGate();
    
//== Adam ,obsluga HandoverNotify ======================================
    
    // cMessage *temp = check_and_cast<cPacket *>(msg)->decapsulate();//MiM
    // if(temp){
    if (  dynamic_cast<WMaxHandoverNotify*>(msg)  ) {
        EV << "Sending HandoverNotify upper" << endl;
        handleRxMessage(msg);   // msg from WMaxCtrl to IP Layer
        //cout << "$";
        return;
    }
    
    if (  msg->getKind() == MK_HANDOVER_NOTIFY_ACK  ) {
        EV << "Sending Handover Notify Acknowledge to WmaxCtrl" << endl;
        handleRxMessage(msg);   // msg from WMaxCtrl to IP Layer
        //cout << "%";
        return;
    }
    
    // }
//== Adam, end =============================================================
    if (dynamic_cast<WMaxMacTerminateAllConns*>(msg)) {
        Log(Notice) << "All connections terminated." << LogEnd;

	int droppedCnt = 0;
        list<WMaxConn>::iterator it;
        for (it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->queue->getFullName()) {
		Log(Warning) << it->queue->length() << " msg(s) dropped in queue " << it->queue->getFullName() << " during handover." << LogEnd;
		droppedCnt += it->queue->length();
	    }
            it->queue->clear();
            delete it->queue;
        }
	queuedMsgsCnt -= droppedCnt;
        Conns.clear();
        CDMAlist.clear();
        send(msg, "macOut", 0);

	stringUpdate();

        //initialize();
        addRangingConn();
        //cout << "^";
        return;
    }

    if (WMaxMacAddMngmntConn *addconn = dynamic_cast<WMaxMacAddMngmntConn*>(msg)) {
        uint16_t cid = addconn->getCid();
        addManagementConn(cid);
        delete msg;
        //cout << "&";
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
        addConn(conn);

        send(msg, "macOut", 0);  // send add conn msg to CS
        //cout << "*";
        return;
    }

    Log(Debug) << "Message " << msg->getFullName() << " received on gate: " << gate->getFullName() << LogEnd;
    if (strcmp(gate->getFullName(),"phyIn")) {   
        // "macIn" remaining gates must be uplink (SS -> BS)
        handleTxMessage(msg);
        //cout << "(";
        return;
    } else{
        //"phyIn gate: downlink (BS->SS)
        handleRxMessage(msg);
        //cout << ")";
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
    //cout << "-";
    EV << endl << "WMaxMac::handleTxMessage" << endl;
    cGate * gate = msg->getArrivalGate();
    list<WMaxConn>::iterator it;
    
    // message from WMaxCtrl - add header
     if (!msg->getControlInfo()) {
         for (it = Conns.begin(); it!=Conns.end(); it++) {
             if ((it->gateIndex == gate->getIndex()) && (it->controlConn == true)) {
                 WMaxMacHeader * hdr = new WMaxMacHeader();
                 hdr->cid = it->cid;
                 msg->setControlInfo(hdr);
                 break;
             }
         }
     }
     
     WMaxMacHeader * hdr = 0;
     hdr = dynamic_cast<WMaxMacHeader*>(msg->getControlInfo());
     if (!hdr)
        opp_error("Unable to handle %s message: no header included", msg->getFullName());
     // find proper connection, not just get first one
     for (it = Conns.begin(); it!=Conns.end(); it++) {
         if (it->cid == hdr->cid) {
             break;
         }
     }
     if (it==Conns.end()) {
         Log(Error) << "Unable to find connection for CID=" << hdr->cid << LogEnd;
         delete msg;
         //cout << "_";
         return;
     }
     
     if (dynamic_cast<WMaxMacSS*>(this)) {
         switch(it->type) {
             case WMAX_CONN_TYPE_BE:
             {
               Log(Debug) << "Received BE message (CID=" << it->cid << ", len=" << check_and_cast<cPacket *>(msg)->getByteLength() << ") ";
               int symbolLength = (int)ceil(double(check_and_cast<cPacket *>(msg)->getByteLength())/WMAX_BYTES_PER_SYMBOL);
                 it->qos.be.reqbw += symbolLength*WMAX_BYTES_PER_SYMBOL;
                 if(check_and_cast<cPacket *>(msg)->getByteLength() == 0) { /// @todo sending messages with length == 0
                 it->qos.be.reqbw += 12;
                 }
                 Log(Cont) << "CID=" << it->cid << " Required bandwidth: " << symbolLength << " (" << symbolLength*WMAX_BYTES_PER_SYMBOL << ")" 
                       << ", " << it->qos.be.reqbw << " required so far" << LogEnd; 
                 it->queue->insert(msg);
                 break;
             }
             case WMAX_CONN_TYPE_UGS:
               Log(Debug) << "Queueing message (CID=" << it->cid << ", gateIndex=" << gate->getIndex() << ", length=" << check_and_cast<cPacket *>(msg)->getByteLength() << ")." << LogEnd;
                 SendQueue.insert(msg);
                 break;
             default:
                 opp_error("Unsupported traffic type: %d", it->type);
         }
     } else {
        Log(Debug) << "Queueing message (CID=" << it->cid << ", gateIndex=" << gate->getIndex() << ", length=" << check_and_cast<cPacket *>(msg)->getByteLength() << ")." << LogEnd;
        SendQueue.insert(msg);
     }
     queuedMsgsCnt++;
     stringUpdate();
     //cout << "+";

}

void WMaxMacSS::handleRxMessage(cMessage *msg)
{
    //cout << "=";
    EV << endl << "WMaxMac::handleRxMessage" << endl;    
    bool bcastMsg = false; // is this a broadcast message?
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	WMaxMsgUlMap * ulmap = dynamic_cast<WMaxMsgUlMap*>(msg);
	printUlMap(ulmap);
	STAT_INC(rcvdUlmaps);
	bcastMsg = true;

	schedule(ulmap);
    }
    if( msg->getKind() == MK_HANDOVER_NOTIFY_ACK ){
        bcastMsg = true;    
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
		// ev << getFullName() << "Dispatching " << msg->getFullName() << " to gate " << it->gateIndex 
		// << ", ctrl=" << ((int)(it->controlConn)) << endl;
		cMessage * copy = (cMessage*)msg->dup();
		send(copy, "macOut", it->gateIndex);
		break;
	    }
	}

	delete msg;
    //cout << "[";
	return;
    }

    if (dynamic_cast<WMaxMsgDlMap*>(msg)) {
        printDlMap(dynamic_cast<WMaxMsgDlMap*>(msg));
        STAT_INC(rcvdDlmaps);
        WMaxMsgDlMap* dlmap = dynamic_cast<WMaxMsgDlMap*>(msg);
        Log(Debug) << "DL-MAP received: expecting " << dlmap->getIEArraySize() << " messages in this frame." << LogEnd;

        // handle this map to WMaxCtrl
        list<WMaxConn>::iterator it;
        for (it = Conns.begin(); it!=Conns.end(); it++) {
            if (it->controlConn) {
            Log(Debug) << "Dispatching dlmap to gate " << it->gateIndex << ", ctrl=" << ((int)(it->controlConn)) << LogEnd;
            send(msg, "macOut", it->gateIndex);
            break;
            }
        }

        // @todo - delete dlmap
        //cout << "{";
        return;
    }

    WMaxMac::handleRxMessage(msg);
    //cout << "]";
}

void WMaxMacSS::changePosition() {
    //cout << "}";
    cDisplayString dispstr = SS->getDisplayString();
    long int x = atoi(dispstr.getTagArg("p",0));
    long int y = atoi(dispstr.getTagArg("p",1));

    switch ((int)SS->par("movementType")) {
    case 0:
        x++;
        break;
    case 1:
        float centerx=(double)SS->par("SStrace_centerx");
        float centery=(double)SS->par("SStrace_centery");
        float radius=(double)SS->par("SStrace_radius");
        float radstep=(double)SS->par("SStrace_step");
        x=(long int)(sin(radian)*radius+centerx);
        y=(long int)(cos(radian)*radius+centery);
        radian=radian+radstep;
        break;
    }

    dispstr.setTagArg("p",0,x);
    dispstr.setTagArg("p",1,y);
    SS->setDisplayString(dispstr);

    char buf[80];
    sprintf(buf, "(%s,%s)", (SS->getDisplayString()).getTagArg("p",0), (SS->getDisplayString()).getTagArg("p",1));
    SS->getDisplayString().setTagArg("t",0, buf);
    //cout << "?";
}

void WMaxMacSS::schedule(WMaxMsgUlMap * ulmap)
{
    //cout << "|";
    int bandwidth = 0;
    Log(Debug) << "UL-MAP received with " << ulmap->getIEArraySize() << " IE(s)." << LogEnd;
    unsigned int i;
    for (i=0; i<ulmap->getIEArraySize(); i++) {
	WMaxUlMapIE & ie = ulmap->getIE(i);
	for (list<WMaxConn>::iterator it = Conns.begin(); it!=Conns.end(); it++) {
	    if (it->cid==ie.cid) {
		if (ie.uiuc>=WMAX_ULMAP_UIUC_DATA_1 || ie.uiuc<=WMAX_ULMAP_UIUC_DATA_10) {
		    bandwidth = ie.dataIE.duration;
		    STAT_INC(rcvdGrants);

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

	                 msg = (cMessage*) it->queue->front();

	                 if (check_and_cast<cPacket *>(msg)->getByteLength() > symbols*bytesPerPS) {
	                 // message won't fit in this frame. What should we do in such case?
			   Log(Debug) << "Tried to schedule message (len=" << check_and_cast<cPacket *>(msg)->getByteLength() << "), but there are only " 
				       << symbols*bytesPerPS << " bytes left." << LogEnd;

	                     if (ieCnt) // something has been scheduled - ok, end scheduling
		                 break;

                             // currently used: c)
                             msg = (cMessage*) it->queue->pop();
                             Log(Error) << "Unable to send " << check_and_cast<cPacket *>(msg)->getByteLength() << "-byte message(" << msg->getFullName() 
					<<"), because it won't fit in UL subframe. Message is dropped." << LogEnd;
			     queuedMsgsCnt--;
                             delete msg;
                             continue;

                             // currently used: d)
	                     /*opp_error("Unable to send %d-byte long message(%s), because it won't fit in UL subframe (%d symbols *%dB/PS=%d bytes)",
		             msg->getByteLength(), msg->getFullName(), symbols, bytesPerPS, symbols*bytesPerPS);
	                     break;*/
	                 }

	                 // message will fit in this frame, send it
	                 ieCnt++;

                         msg = (cMessage*)it->queue->pop();
			 queuedMsgsCnt--;

                         lengthInPS = (int)ceil(double(check_and_cast<cPacket *>(msg)->getByteLength())/bytesPerPS);
	
                         symbols -= lengthInPS;
	
                         WMaxMacHeader * hdr = dynamic_cast<WMaxMacHeader*>(msg->getControlInfo());
	                 if (!hdr)
	                      opp_error("Unable to obtain header information for message: %s\n", msg->getFullName());

	                 Log(Debug) << "Sent msg: length=" << check_and_cast<cPacket *>(msg)->getByteLength() << ", used " << lengthInPS << " symbols, " 
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

            for (unsigned int i=0; i!=Conns.size(); i++) {

                list<WMaxConn>::iterator BEit = Conns.begin();
                for (int j=0; j!=BEpoint; j++){
                    BEit++;
                    if (BEit == Conns.end())
                        BEit = Conns.begin();
                }

                BEpoint++;
                BEpoint = BEpoint%(int)Conns.size();

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
                               cMessage * msg = (cMessage*) it2->queue->front();
                               if(hdr->bwr < check_and_cast<cPacket *>(msg)->getByteLength())
				 hdr->bwr = check_and_cast<cPacket *>(msg)->getByteLength();
                           }
                       }
                   }

                   hdr->cid = it->cid;
                   WMaxMsgBWR *msg = new WMaxMsgBWR("Bandwidth request");
                   msg->setControlInfo(hdr);
                   Log(Info) << "Sending Bandwidth request (bandwidth: " << hdr->bwr << ", cid: "  << hdr->cid << ")" << LogEnd;
                   send(msg, "phyOut");
                   CDMAlist.erase(it);
                   break;
               }
           }
	}

    }


    if (SendQueue.length()) {
	cMessage * msg = (cMessage*)SendQueue.pop();
	queuedMsgsCnt--;
	send(msg, "phyOut");
    }

    STAT_ADD(rcvdBandwidth, bandwidth);

    WMaxPhyDummyFrameStart * frameStart = new WMaxPhyDummyFrameStart();
    send(frameStart, "phyOut");

    stringUpdate();
    //cout << ";";
}

void WMaxMacSS::finish()
{
    //cout << ":";
    delete CDMAQueue;
    for (list<WMaxConn>::iterator it=Conns.begin(); it!=Conns.end(); ++it)
    {
	delete it->queue;
    }
    Conns.clear();
    //cout << "'";
}
