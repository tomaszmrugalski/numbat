/**
 * @file   dhcpbv6.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Tue Aug  7 12:55:16 CET 2007
 * 
 * @brief  DHCPv6 server/client
 * 
 * Published under GNU GPLv2 or later 
 */

#ifndef DHCPV6_H
#define DHCPV6_H

#include <omnetpp.h>
#include "fsm.h"


class MobIPv6mn : public Fsm
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleMihMessage(cMessage *msg);
    virtual void handleBindingAck(cMessage *msg);
    void updateString();
    void fsmInit();
 private:
    bool connected;
    int  index;
};

class MobIPv6ha : public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
 private:
};

class MobIPv6cn: public cSimpleModule
{
 public:
 protected:
    void updateString();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleBindingUpdate(cMessage * msg);
 private:
    bool connected;
    int  index;
};

#endif
