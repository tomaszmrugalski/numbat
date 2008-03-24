#ifndef INTERNET_H
#define INTERNET_H

#include <stdint.h>
#include <omnetpp.h>

class Internet: public cSimpleModule
{
 public:
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
 private:
};

#endif
