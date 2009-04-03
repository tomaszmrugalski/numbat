#ifndef INTERNET_H
#define INTERNET_H

#include <omnetpp.h>
#include "ipv6msg_m.h"
#include "ipv6.h"

typedef struct {
    IPv6Addr prefix;
    int gateIndex;
} RouteEntry;

class Internet: public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
 private:
    double calculateDelay(IPv6 *msg);
    list<RouteEntry> RoutingTable;

    long int MsgsTransmittedCnt;
    long int DroppedMsgsCnt;
    cOutVector MsgsTransmittedVector;
    cOutVector DroppedMsgsVector;
    cOutVector DelayVector;
};

ostream & operator << (ostream &s, RouteEntry e);

#endif
