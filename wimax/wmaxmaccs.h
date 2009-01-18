/**
 * @file   wmaxmaccs.h
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-04-20 23:09:38+0100
 * 
 * @brief  WMax MAC convergence sublayer
 * @licence GNU GPLv2 or later
 * 
 */

#ifndef WMAXMACCS_H
#define WMAXMACCS_H

#include <stdint.h>
#include <omnetpp.h>
#include <string>
#include "ipv6msg_m.h"

using namespace std;

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

typedef struct {
     uint16_t cid;
     //int gateIndex; 
     /// @todo IPv6 source and destination addr
     uint64_t macAddr;
     IPv6Addr dstAddr;
} WMaxMacCSRule;


/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class WMaxMacCS : public cSimpleModule {
public:

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleUlMessage(cMessage *msg);
    virtual void handleDlMessage(cMessage *msg);
    virtual void updateLog();

    IPv6Addr DstAddrGet(cMessage *msg);
    list<WMaxMacCSRule> csTable;
    bool BS;
};

ostream & operator <<(ostream & s, WMaxMacCSRule &f);

#endif
