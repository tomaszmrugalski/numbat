/**
 * @file   ipv6node.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Sat Nov 18 18:42:04 2006
 * 
 * @brief  IPv6 transmitter/receiver
 * 
 * Published under GNU GPLv2 or later 
 */

#ifndef IPV6NODE_H
#define IPV6NODE_H

#include <omnetpp.h>
#include "Portable.h"

class IPv6Node : public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void generateTraffic();
    virtual void updateStats();

    void trafficTruncNormal();
    void trafficBeta();
 private:
    cMessage * sendTimer;

    int TrafficType;

    // how often packets should be sent?
    double BurstInterval;

    // how many packets should be sent each time?
    int BurstSize;

    // how large packets can be?
    int MaxPacketSize; // maximum packet size (configurable)
    int MinPacketSize; // minimum packet size (sizeof(ip6hdr)+sizeof(udphdr)
    
    double Mean;
    double StdDev; 

    // stats 
    uint32_t SentBytes;
    uint32_t SentPkts;
    uint32_t RcvdBytes;
    uint32_t RcvdPkts;

    cOutVector SentPktsVector;
    cOutVector SentBytesVector;
    cOutVector RcvdPktsVector;
    cOutVector RcvdBytesVector;
    cOutVector SentPktSizeVector;
    cOutVector RcvdPktSizeVector;
};

#endif
