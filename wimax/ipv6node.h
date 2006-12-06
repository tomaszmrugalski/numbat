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


class IPv6Node : public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void generateTraffic();
 private:
    cMessage * sendTimer;
};

#endif
