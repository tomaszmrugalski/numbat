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
#include "ipv6.h"
#include "wmaxmac.h"
#include "logger.h"
#include "ssinfo.h"

using namespace std;

ostream & operator <<(ostream & s, WMaxMacCSRule &rule)
{
    s << "cid=" << rule.cid << ", dstAddr=" << rule.dstAddr.plain() << ", mac=" << MacToString(rule.macAddr);
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

    // add number prefix to the module name
    cModule * ss = getParentModule()->getParentModule();
    char buf[80];
    sprintf(buf, "%s%d", getFullName(), ss->getIndex());
    setName(buf);
}


void WMaxMacCS::handleMessage(cMessage *msg) {


    if (dynamic_cast<WMaxMacTerminateAllConns*>(msg)) {
        Log(Notice) << "All connections terminated." << LogEnd;
        csTable.clear();
        delete msg;
        return;
    }

    if (WMaxMacAddConn *addconn = dynamic_cast<WMaxMacAddConn*>(msg)) {
        WMaxMacCSRule rule = {0};
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
                Log(Notice) << "Connection cid=" << delcon->getCid() << " removed." << LogEnd;
                updateLog();
                delete msg;
                return;
            }
        }
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
    Log(Debug) << "Message send to upper layer." << LogEnd;
}

IPv6Addr WMaxMacCS::DstAddrGet(cMessage *msg)
{
    if (dynamic_cast<IPv6*>(msg))
    {
      IPv6* ipMsg = dynamic_cast<IPv6*>(msg);
      return ipMsg->getDstIP();
    }
    opp_error("Non-IPv6 message is trying to sneak thru WMaxMacCS module: %s", getFullName());
    return IPv6Addr();
}

void WMaxMacCS::handleDlMessage(cMessage *msg) {
    list<WMaxMacCSRule>::iterator it;
    cGate * gate = msg->getArrivalGate();
    IPv6Addr dstAddr = DstAddrGet(msg);
    uint64_t macAddr = dstAddr.MacAddrFromLinkLocal();
    Log(Debug) << "Trying to forward DL msg (" << msg->getFullName() << ") to ipv6=" << dstAddr.plain()
	       << ", MAC=" << (macAddr?MacToString(macAddr):"unknown") << LogEnd;

    // try to find appropriate route for this dst address
    int mcastReceiversCnt = 0; // how many SSes are going to receive this message?

    if (csTable.size() == 0)
    {
	if (!dstAddr.isMulticast()) // don't complain about multicasts so loud
	{
	    Log(Info); 
	} else {
	    Log(Debug);
	}
	Log(Cont)  << "Unable to forward message(" << msg->getFullName() << "), no CS rules defined." << LogEnd;
	delete msg;
	return;
    }
    
    for(it=csTable.begin(); it!=csTable.end(); it++) {
	// on SS side, just use first connection available
	if (BS==false) {
	    dlMsgSend(msg, it->cid);
	    return;
	}

	if (it->macAddr==macAddr)
	{
	    // found on MAC based criteria
	    if (dynamic_cast<DHCPv6Reply*>(msg))
	    {
		DHCPv6Reply * reply = dynamic_cast<DHCPv6Reply*>(msg);
		Log(Info) << "DHCPv6 Reply: updating rule for CID=" << it->cid << ", MAC=" << MacToString(it->macAddr) 
			  << " to dstAddr=" << reply->getAddr() << LogEnd;
		it->dstAddr = reply->getAddr();
	    }
	    dlMsgSend(msg, it->cid);
	    return;
	}
	if (it->dstAddr == dstAddr)
	{
	    // found expected IPv6 address
	    dlMsgSend(msg, it->cid);
	    return;
	}
	if (dstAddr.isMulticast()) {
	    mcastReceiversCnt++;
	    dlMsgSend((cMessage*)msg->dup(), it->cid);
	}
    }

    if (!dstAddr.isMulticast())
    {
	Log(Info) << "Unable to find a proper connection for msg(" << msg->getFullName() << ") to ipv6=" << dstAddr.plain()
		    << ", MAC=" << (macAddr?MacToString(macAddr):"unknown") << ", dropped." << LogEnd;
    } else {
	Log(Debug) << "Multicast message (" << msg->getFullName() << ") sent to " << mcastReceiversCnt << " nodes." << LogEnd;
    }
    delete msg;
    return;
}

void WMaxMacCS::dlMsgSend(cMessage * msg, int cid)
{
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
