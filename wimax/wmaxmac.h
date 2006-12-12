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
#include <vector>
#include "wmaxmsg_m.h"

using namespace std;

#ifndef WMAXMAC_H
#define WMAXMAC_H

#define CLEAR(x) memset(x, 0, sizeof(*x));

typedef enum
{
    WMAX_CONN_TYPE_BE,  // best effort
    WMAX_CONN_TYPE_UGS  // ugs
} WMaxConnType;

/** 
 * this structure represents connection
 * 
 */
typedef struct {
    WMaxConnType type;
    uint32_t sfid;
    uint16_t cid;

    uint32_t dataLen; /* per frame */
} WMaxConn;


class WMaxMac : public cSimpleModule
{
 public:

 protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
    bool addConn(WMaxConn conn);
    bool delConn(uint32_t sfid);

    cQueue SendQueue;
    list<WMaxConn> Conns;
};


class WMaxMacBS: public WMaxMac
{
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

 private:
    virtual void schedule();
    virtual void handleDlMessage(cMessage *msg);
    virtual void handleUlMessage(cMessage *msg);
    cMessage * TxStart;
};

class WMaxStatsSS 
{
public:
    int grants;    /* number of grants received */
    int bandwidth; /* total bandwidth granted */
    int dlmaps;    /* number of dlmaps received */
    int ulmaps;    /* number of ulmaps received */
};

class WMaxMacSS: public WMaxMac
{

 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);
    virtual void finish();
 private:
    virtual void schedule(WMaxMsgUlMap* ulmap);
    virtual void handleDlMessage(cMessage* msg);
    void         handleUlMessage(cMessage* msg);

    WMaxStatsSS Stats;
};

#endif
