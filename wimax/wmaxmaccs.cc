/**
 * @file    wmaxmaccs.cc
 * @author  Maciej Jureko <maciek01@gmail.com>
 * @changes Tomasz Mrugalski <thomson@klub.com.pl>
 * @date    2007-04-20 23:09:38+0100
 * 
 * @brief   WMax MAC convergence sublayer
 * @licence GNU GPLv2 or later
 *
 */

#include <omnetpp.h>
#include <string>
#include "wmaxmaccs.h"
//#include "ipv6.h"
#include "wmaxmac.h"
#include "logger.h"
#include "ssinfo.h"
// Adam

// Adam end
using namespace std;

ostream & operator <<(ostream & s, WMaxMacCSRule &rule)
{
    s << "cid=" << rule.cid << ", dstAddr=" << rule.dstAddr.str();
	s << ", mac=" << MacToString(rule.macAddr);
    return s;
}

/********************************************************************************/
/*** WMaxMacCS ******************************************************************/
/********************************************************************************/

Define_Module(WMaxMacCS);

void WMaxMacCS::initialize() {
  WATCH_LIST(csTable);
  std::string name=getFullName();
  if (!name.find("ss")) {
      BS = false;
  } else {
      BS = true;
  }

	ipv6nd = IPv6NeighbourDiscoveryAccess().get();

  
    // add number prefix to the module name
    cModule * ss = getParentModule()->getParentModule();
    char buf[80];
    sprintf(buf, "%s%d", getFullName(), ss->getIndex());
    setName(buf);
}


void WMaxMacCS::handleMessage(cMessage *msg) {
    if (dynamic_cast<WMaxMacTerminateAllConns*>(msg)) {
        Log(Notice) << "All connections terminated." << LogEnd;
        EV << "All connections terminated." << endl;
        csTable.clear();
        delete msg;
        return;
    }

    if (WMaxMacAddConn *addconn = dynamic_cast<WMaxMacAddConn*>(msg)) {
        WMaxMacCSRule rule = {0};
        EV << "Adding connection " << endl;
        EV << "cid = "<<addconn->getCid()<<"  dstAddr = "<<addconn->getDstAddr()<<"  macAddr = "<< addconn->getMacAddr() << endl;
        rule.cid     = addconn->getCid();
        rule.dstAddr = addconn->getDstAddr();
        rule.macAddr = addconn->getMacAddr();
	
        list<WMaxMacCSRule>::iterator it;
        csTable.push_back(rule);
        updateLog();
        delete msg;
        return;
    }

    if (WMaxEvent_DelConn *delcon = dynamic_cast<WMaxEvent_DelConn*>(msg)) {
        if (delcon->getIsBasic())
        {
            // there are no CS rules for basic connections
            delete msg; 
            return;
        }
        list<WMaxMacCSRule>::iterator it;
        for(it=csTable.begin(); it!=csTable.end(); it++) {
            if((it->cid == delcon->getCid())) {
                csTable.erase(it);
                EV << "Connection cid=" << delcon->getCid() << " removed." << endl;
                Log(Notice) << "Connection cid=" << delcon->getCid() << " removed." << LogEnd;
                updateLog();
                delete msg;
                return;
            }
        }
        EV << "Unable to delete connection with cid=" << delcon->getCid() << "." << endl;
        Log(Error) << "Unable to delete connection with cid=" << delcon->getCid() << "." << LogEnd;
        delete msg;
        return;
    }

    cGate * gate = msg->getArrivalGate();
    if(!strcmp(gate->getFullName(),"macIn")) {
        handleUlMessage(msg);
        return;
    }

    handleDlMessage(msg);
}


void WMaxMacCS::handleUlMessage(cMessage *msg) {
    // reconstruction
    cMessage *ipv6packet = check_and_cast<cPacket *>(msg)->decapsulate();//MiM
    delete msg;
    send(ipv6packet, "ipOut", 0);
}

uint64_t MacAddrFromLinkLocal(IPv6Address IN_addr)		//		zamienic to na jakas inna funkcje, ta jest wpisana z ipv6.h z numbata
{
    unsigned char addr[16];
	uint32 *ip;
	
	ip = IN_addr.words();
	
	addr[0] = ip[0]>>24;
	addr[1] = (ip[0]<<8)>>24;
	addr[2] = (ip[0]<<16)>>24;
	addr[3] = (ip[0]<<24)>>24;
	addr[4] = ip[1]>>24;
	addr[5] = (ip[1]<<8)>>24;
	addr[6] = (ip[1]<<16)>>24;
	addr[7] = (ip[1]<<24)>>24;
	addr[8] = ip[2]>>24;
	addr[9] = (ip[2]<<8)>>24;
	addr[10] = (ip[2]<<16)>>24;
	addr[11] = (ip[2]<<24)>>24;
	addr[12] = ip[3]>>24;
	addr[13] = (ip[3]<<8)>>24;
	addr[14] = (ip[3]<<16)>>24;
	addr[15] = (ip[3]<<24)>>24;
	
    if ( (addr[0]!=0xfe) || (addr[1]!=0x80) ){	// sprawdzenie czy addr jest link-local
		return 0;
    }	
	
    unsigned char tbl[6];
    memcpy(tbl+3, addr+13,3);
    memcpy(tbl, addr+8,3);

    uint64_t m = ((uint64_t)tbl[5]) 
	+ ((uint64_t)tbl[4] << 8)
	+ ((uint64_t)tbl[3] << 16)
	+ ((uint64_t)tbl[2] << 24)
	+ ((uint64_t)tbl[1] << 32)
	+ ((uint64_t)tbl[0] << 40);
    return m;
}

void WMaxMacCS::handleDlMessage(cMessage *msg) {
    RoutingTable6* RTable = RoutingTable6Access().get();   //============= Adam 14-09-2011 =====================
    
    list<WMaxMacCSRule>::iterator it;
    cGate * gate = msg->getArrivalGate();
	IPv6Datagram_Base* ipMsg = dynamic_cast<IPv6Datagram_Base*>(msg);
    IPv6Address dstAddr = ipMsg->getDestAddress();// = msg->getDstIP();
    uint64_t macAddr = 0;
    if( dstAddr.isLinkLocal() )
        macAddr = MacAddrFromLinkLocal(dstAddr);	//==== Adam =====

    Log(Debug) << "Trying to forward DL msg (" << msg->getFullName() << ") to ipv6=" << dstAddr.str();//-----------Adam ================================
    Log(Debug) << ", MAC=" << (macAddr?MacToString(macAddr):"unknown") << LogEnd;
    
    // try to find appropriate route for this dst address
    int mcastReceiversCnt = 0; // how many SSes are going to receive this message?
    if (csTable.size() == 0){
        if (!dstAddr.isMulticast()){ // don't complain about multicasts so loud
            Log(Info); 
        } else {
            Log(Debug);
        }
        EV << "Unable to forward message(" << msg->getFullName() << "), no CS rules defined." << endl;
        Log(Cont)  << "Unable to forward message(" << msg->getFullName() << "), no CS rules defined." << LogEnd;
        delete msg;
        return;
    }
    for(it=csTable.begin(); it!=csTable.end(); it++) {
	// on SS side, just use first connection available
        if (BS==false) {	// jesli wezel nie jest BS, czyli jest SS
            EV << "BS==false" << endl;
            dlMsgSend(msg, it->cid);
            return;
        }

		//Adam
		if( !dstAddr.isMulticast() ){
			IPv6NeighbourDiscovery::Neighbour *nce = ipv6nd->neighbourCache.lookup(dstAddr, 101); // 101 bo if id WiMAX SS i BS = 101
			if( nce ){
				if( !nce->macAddress.isUnspecified() ){
					Log(Debug) << it->macAddr << LogEnd;
					char buf[30];
					sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", 
						(unsigned char)((it->macAddr >> 40) & 0xff),
						(unsigned char)((it->macAddr >> 32) & 0xff),
						(unsigned char)((it->macAddr >> 24) & 0xff),
						(unsigned char)((it->macAddr >> 16) & 0xff),
						(unsigned char)((it->macAddr >>  8) & 0xff),
						(unsigned char)((it->macAddr )      & 0xff));
				    char* ch = new char[ strlen(string(buf).c_str()) ];
					strcpy (ch, string(buf).c_str());
					MACAddress temp_mac = MACAddress(ch);

					Log(Debug) << temp_mac << LogEnd;
					Log(Debug) << nce->macAddress << LogEnd;
					Log(Debug) << nce->macAddress.compareTo(temp_mac) << LogEnd;
					if( nce->macAddress.equals(temp_mac) ){
						dlMsgSend(msg, it->cid);
						return;
					}
				}
			}
		}
		//Adam end

        if (it->macAddr == macAddr){
            EV << "it->macAddr == macAddr ";
            // found on MAC based criteria
            dlMsgSend(msg, it->cid);
            return;
        }
        if (it->dstAddr == dstAddr){
            // found expected IPv6 address
            EV << "it->dstAddr == dstAddr ";
            dlMsgSend(msg, it->cid);
            return;
        }
        if (dstAddr.isMulticast()) {
            EV << "dstAddr.isMulticast()";
            mcastReceiversCnt++;
            dlMsgSend((cMessage*)msg->dup(), it->cid);
        }
//============= Adam 14-09-2011 =====================        
        // if( RTable -> doLongestPrefixMatch( dstAddr ) ){
            // EV << "doLongestPrefixMatch ";
            // dlMsgSend(msg, it->cid);
            // return;
        // }
//============= Adam, end  14-09-2011==================s
    }

    if (!dstAddr.isMulticast()){
        Log(Info) << "Unable to find a proper connection for msg(" << msg->getFullName() << ") to ipv6=" << dstAddr.str()
                  << ", MAC=" << (macAddr?MacToString(macAddr):"unknown") << ", dropped." << LogEnd;
    } else {
        Log(Debug) << "Multicast message (" << msg->getFullName() << ") sent to " << mcastReceiversCnt << " nodes." << LogEnd;
    }
    delete msg;
    return;
}

void WMaxMacCS::dlMsgSend(cMessage * msg, int cid)
{
    EV << " -> sending DL msg" << endl;
    list<WMaxMacCSRule>::iterator it;
    
  /*cMessage*/ cPacket *wmaxmacmsg = new cPacket/*Message*/(msg->getFullName());//MiM
    wmaxmacmsg->encapsulate(check_and_cast<cPacket *>(msg)); //MiM

    WMaxMacHeader * hdr = new WMaxMacHeader();
    hdr->cid = cid;
    wmaxmacmsg->setControlInfo(hdr);
    
    send(wmaxmacmsg, "macOut");
}

void WMaxMacCS::updateLog() {
    list<WMaxMacCSRule>::iterator it;
    string log;
    log = "Convergence Sublayer clasifier: ";
    for(it=csTable.begin(); it!=csTable.end(); it++) {
        stringstream ss_cid;
        string st_cid;
        ss_cid << it->cid;
        ss_cid >> st_cid;
        log = log + "CID=" + st_cid + " | ";
    }
    Log(Notice) << log << LogEnd;
}
