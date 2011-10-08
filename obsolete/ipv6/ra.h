/**
 * @file   dhcpbv6.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Tue Aug  7 12:55:16 CET 2007
 * 
 * @brief  IPv6 Router Advertisement generator/receiver
 * 
 * Published under GNU GPLv2 or later 
 */

#ifndef IPV6RA_H
#define IPV6RA_H

#include <omnetpp.h>
#include "fsm.h"

class RaRcv : public Fsm
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void fsmInit();
 private:
    int RaRcvCnt;
    void updateString();
};

class RaGen : public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
 private:
    void sendRA();
    cMessage * sendTimer;
    double     RaInterval;
};


#endif
