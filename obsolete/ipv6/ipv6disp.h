/**
 * @file   ipv6disp.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Tue Aug  7 12:55:16 CET 2007
 * 
 * @brief  IPv6 dispatcher
 * 
 * Published under GNU GPLv2 or later 
 */

#ifndef IPV6DISP_H
#define IPV6DISP_H

#include <omnetpp.h>

class IPv6Dispatch : public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleMihMessage(cMessage *msg);
    void dispatchMessage(cMessage *msg);
    virtual void updateString();
    virtual void writeStat();
    long int SentBytesPers;
    long int RcvdBytesPers;
    long int DroppedMsgs;
    
 private:
    void ipv6ReconfigureStart();
    void ipv6ReconfigureEnd();

    bool handleTraffic;     // is the L2 able to handle traffic?o
    bool routingConfigured; // is routing configured?
    bool addrConfigured;    // is the IPv6 address assigned?
    bool locationUpdated;   // did the node completed location update?
    cOutVector SentBytesVector;
    cOutVector RcvdBytesVector;
    cOutVector DroppedMsgsVector;
    cMessage * timer;

    bool BS;
};


#endif
