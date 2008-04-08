#ifndef INTERNET_H
#define INTERNET_H

#include <stdint.h>
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
 private:
    double calculateDelay(IPv6 *msg);
    list<RouteEntry> RoutingTable;
};

ostream & operator << (ostream &s, RouteEntry e);

#endif
