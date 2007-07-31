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

using namespace std;

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

typedef struct {
     uint16_t cid;
     //int gateIndex; 
     /// @todo IPv6 source and destination addr
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

    list<WMaxMacCSRule> csTable;
};

ostream & operator <<(ostream & s, WMaxMacCSRule &f);

#endif
