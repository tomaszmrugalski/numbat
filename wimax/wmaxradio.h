/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2007-06-25 01:27:46+0200
 * 
 * @brief  WMax Radio connector (used to connect multiple SSes to one BS)
 * @licence GNU GPLv2
 * 
 */

#ifndef WMAXRADIO_H
#define WMAXRADIO_H

#include <omnetpp.h>
#include <vector>
#include "fsm.h"

class WMaxRadio : public cSimpleModule
{
public:
    void connect(cModule * ss);
    void disconnect(cModule * ss);
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
