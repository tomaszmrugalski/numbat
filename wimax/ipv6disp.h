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

#include <stdint.h>
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
 private:
    bool handleTraffic;
};


#endif
