/**
 * @file   ssinfo.cc
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-06-30 21:01:52+0200
 * 
 * @brief  SS parameters
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>
#include <string>
#include <math.h>
#include "logger.h"
#include "ssinfo.h"
#include "mih_m.h"

using namespace std;

ostream & operator<<(ostream & str, SSInfo_t &ss) {
    str << "MAC=" << ss.getMac() << ", basicCid=" << ss.basicCid << " sfCnt="
        << ss.sfCnt;
    for (int i=0; i < ss.sfCnt; i++) {
      str << " sf[" << i << "].cid=" << ss.sf[i].cid;
    }
    return str;
}

std::string SSInfo_t::getMac() {
    return MacToString(macAddr);
}

/********************************************************************************/
/*** ssInfo  ********************************************************************/
/********************************************************************************/

Define_Module(ssInfo);

void ssInfo::initialize() {
    info.macAddr = ((uint64_t)0x0018de << 24) + (rand()%(((uint64_t)1 << 24) - 1));
    info.basicCid = 0;

    CLEAR(&hoInfo);

    hoInfo.isMobile = getParentModule()->par("wmaxIsMobile");
    hoInfo.wmax.hoOptim = getParentModule()->par("wmaxHoOptim");

    hoInfo.dhcp.DadType = (DhcpDadType)(int)getParentModule()->par("dadType");
    hoInfo.dhcp.skipInitialDelay = getParentModule()->par("dhcpSkipInitialDelay");
    hoInfo.dhcp.pref255 = getParentModule()->par("dhcpPref255");
    hoInfo.dhcp.rapidCommit = getParentModule()->par("dhcpRapidCommit");
    hoInfo.dhcp.remoteAutoconf = getParentModule()->par("dhcpRemoteAutoconf");
    hoInfo.dhcp.addrParams = getParentModule()->par("dhcpAddrParams");

    hoInfo.mip.remoteLocUpdate = getParentModule()->par("mipRemoteLocUpdate");
    
    int initialBS = getParentModule()->par("initialBS");

    int index = getParentModule()->getIndex();

    stringUpdate();
    Log(Notice) << "New SS[" << index << "] [802.16]: " << info.getMac() << ", hoOptim=" << hoInfo.wmax.hoOptim 
		<< ", isMobile=" << hoInfo.isMobile << ", initialBS=" << initialBS << LogEnd;
    Log(Notice) << "New SS[" << index << "] [IPv6]: " << info.getMac() << ", dadType=" << hoInfo.dhcp.DadType 
		<< ", dhcpSkipInitialDelay=" << hoInfo.dhcp.skipInitialDelay << ", dhcpPref255=" << hoInfo.dhcp.pref255
		<< ", dhcpRapidCommit=" << hoInfo.dhcp.rapidCommit 
		<< ", dhcpRemoteAutoconf=" << hoInfo.dhcp.remoteAutoconf 
		<< ", dhcpAddrParams=" << hoInfo.dhcp.addrParams
		<< ", mipRemoteLocUpdate=" << hoInfo.mip.remoteLocUpdate
		<< LogEnd;

    hoPrepVector.setName("HO Preparation time");
    hoReentryVector.setName("HO Reentry time");
    hoReconfVector.setName("HO IP reconfigure time");
    hoLackOfCommVector.setName("HO Lack of comm. capab. time");

    hoPrep = 0;
    hoReentry = 0;
    hoReconf = 0;
    hoLackOfComm = 0;
}

void ssInfo::stringUpdate() {

    if (ev.isGUI()) {
        stringstream displayIt;
        displayIt << "macAddr=" << info.getMac() << endl;
        displayIt << "basicCID=" << dec << info.basicCid;

        getDisplayString().setTagArg("t",0, (displayIt.str()).c_str());
    }
}

void ssInfo::addEventListener(cModule * addMe)
{
    Log(Debug) << "Registering new event listener: " << addMe->getFullName() << LogEnd;
    EventListenersLst.push_back(addMe);
}

void ssInfo::delEventListener(cModule * deleteMe)
{
    list<cModule*>::iterator it;

    for (it=EventListenersLst.begin(); it!=EventListenersLst.end(); it++) {
	cModule * module = *it;
	if (module==deleteMe) {
	    EventListenersLst.erase(it);
	    return;
	}
    }

}

string ssInfo::getMsgName(cMessage * msg)
{
    if (dynamic_cast<MihEvent_EntryStart*>(msg))
	return "MihEvent EntryStart";
    if (dynamic_cast<MihEvent_EntryEnd*>(msg))
	return "MihEvent EntryEnd";
    if (dynamic_cast<MihEvent_HandoverStart*>(msg))
	return "MihEvent HandoverStart";
    if (dynamic_cast<MihEvent_HandoverEnd*>(msg))
	return "MihEvent HandoverEnd";
    if (dynamic_cast<MihEvent_ReentryStart*>(msg))
	return "MihEvent ReentryStart";
    if (dynamic_cast<MihEvent_ReentryEnd*>(msg))
	return "MihEvent ReentryEnd";
    if (dynamic_cast<MihEvent_L3AddrConfigured*>(msg))
	return "MihEvent L3AddrConfigured";
    if (dynamic_cast<MihEvent_L3RoutingConfigured*>(msg))
	return "MihEvent_L3RoutingConfigured";
    if (dynamic_cast<MihEvent_L3LocationUpdated*>(msg))
	return "MihEvent_L3LocationUpdated";

    return "unknown event";
}

void ssInfo::sendEvent(cMessage * msg)
{
    Enter_Method("sendEvent()");
    take(msg);
    list<cModule*>::iterator it;

    updateStats(msg);

    Log(Debug) << "Sending event " << getMsgName(msg) << " to " << (int)EventListenersLst.size() << " listeners:";

    for (it=EventListenersLst.begin(); it!=EventListenersLst.end(); it++) {
	cModule * module = *it;
	Log(Cont) << module->getFullName() << " ";
	//sendDirect((cMessage*)msg->dup(), 0.0, module, "eventIn"); 
	sendDirect((cMessage *)msg->dup(), module, "eventIn"/*, int gateIndex=-1*/); //MiM
    }
    Log(Cont) << "." << LogEnd;
    delete msg;
}

void ssInfo::updateStats(cMessage * msg)
{
    if (dynamic_cast<MihEvent_HandoverStart*>(msg)) {
	hoPrep = simTime();
	return;
    }

    if (dynamic_cast<MihEvent_HandoverEnd*>(msg)) {
	hoPrepVector.record(simTime() - hoPrep);
	hoLackOfComm = simTime();
	return;
    }

    if (dynamic_cast<MihEvent_ReentryStart*>(msg)) {
	hoReentry = simTime();
	return;
    }

    if (dynamic_cast<MihEvent_ReentryEnd*>(msg)) {
	hoReentryVector.record(simTime() - hoReentry);
	hoReconf = simTime();
	return;
    }


    /*
    if (dynamic_cast<MihEvent_L3AddrConfigured*>(msg)) 
    if (dynamic_cast<MihEvent_L3RoutingConfigured*>(msg)) */

    if (dynamic_cast<MihEvent_L3LocationUpdated*>(msg)) {
	hoReconfVector.record(simTime() - hoReconf);
	hoLackOfCommVector.record(simTime() - hoLackOfComm);
	return;
    }
}

string MacToString(uint64_t macAddr)
{
    char buf[30];
    sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", 
	    (unsigned char)((macAddr >> 40) & 0xff),
	    (unsigned char)((macAddr >> 32) & 0xff),
	    (unsigned char)((macAddr >> 24) & 0xff),
	    (unsigned char)((macAddr >> 16) & 0xff),
	    (unsigned char)((macAddr >>  8) & 0xff),
	    (unsigned char)((macAddr )      & 0xff));
    return string(buf);
}
