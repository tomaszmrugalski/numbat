/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Mon Nov 20 00:23:08 2006
 * 
 * @brief  WMax MAC layer definitions
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>

#ifndef WMAXMAC_H
#define WMAXMAC_H

class WMaxMac : public cSimpleModule
{
 public:

 protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
};


class WMaxMacBS: public WMaxMac
{
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void schedule();

    cMessage * TxStart;
};

#endif
