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

/**************************************************************/
/*** WIMAX CONSTANTS ******************************************/
/**************************************************************/

// minimum number of bytes in UGS allocation
#define WMAX_SCHED_MIN_GRANT_SIZE 12

// define frequency of the BWR CDMA slots (2 = one alloc per 2 frames)
#define WMAX_CDMA_BWR_FREQ 2

// define frequency of the initial ranging CDMA slots
#define WMAX_CDMA_INIT_RNG_FREQ 3

// define frequency of the handover CDMA slots
#define WMAX_CDMA_HO_RNG_FREQ 10

// minimal UGS grant, which can be assigned
#define WMAX_SCHEDULER_MIN_UGS_GRANT 120

// bytes per symbol (simplification, this value may be different for each modulation)
#define WMAX_BYTES_PER_SYMBOL 12 


#define WMAX_CID_RANGING   0
#define WMAX_CID_BROADCAST 0xffff

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

typedef enum
{
    WMAX_CONN_TYPE_BE,    // best effort
    WMAX_CONN_TYPE_RTPS,
    WMAX_CONN_TYPE_NRTPS, // Non-Real Time Packet Switched
    WMAX_CONN_TYPE_UGS    // Unsolicited Grant Interval
} WMaxConnType;

typedef enum
{
    WMAX_DIRECTION_UL,
    WMAX_DIRECTION_DL
} WMaxConnDirection;

// see 6.3.5.2.1, 802.16-2005 UGS connection
typedef struct {
    uint32_t msr; // maximum sustained traffic rate (bps)
    uint32_t latency; // in ms
    uint32_t jitter;
} WMaxConnUgs;

// see 6.3.5.2.2, 802.16-2005 rtPS connection
typedef struct {
    uint32_t msr; // maximum sustained traffic rate (bps)
    uint32_t mrr; // minimum reserver traffic rate (bps)
    uint32_t latency; // max latency
} WMaxConnRtps;

// see 6.3.5.2.3, 802.16-2005
typedef struct {
    uint32_t msr;
    uint32_t mrr;
    uint8_t  priority;
} WMaxConnNrtps;

// 6.3.5.2.4, 802.16-2005 Best Effort connection
typedef struct {
    uint32_t msr; // maximum sustained traffic rate rate
} WMaxConnBe;

/** 
 * this structure represents connection
 * 
 */
typedef struct {

    // configuration parameters
    WMaxConnType type;
    uint32_t sfid;
    uint16_t cid;

    union {
	WMaxConnUgs   ugs;
	WMaxConnRtps  rtps;
	WMaxConnNrtps nrtps;
	WMaxConnBe    be;
    } qos;

    // --- runtime parameters ---
    uint32_t bandwidth;

    int gateIndex; // index of a gate associated with this connection
    bool controlConn; // is this a control connection? (i.e. send DL-MAP,UL-MAP there?)
} WMaxConn;

class WMaxMacHeader : public cPolymorphic
{
public:
    uint16_t cid;
};

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class WMaxMac : public cSimpleModule
{
 public:
    WMaxMac();

 protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
    bool addConn(WMaxConn conn);
    bool delConn(uint32_t sfid);

    // --- runtime parameters ---
    cQueue SendQueue;
    int GateIndex;

    // --- configuration parameters ---
    list<WMaxConn> Conns;
    double FrameLength;

    virtual void handleUlMessage(cMessage *msg);
    virtual void handleDlMessage(cMessage *msg);
    virtual void printDlMap(WMaxMsgDlMap * dlmap);
    virtual void printUlMap(WMaxMsgUlMap * ulmap);
};


class WMaxMacBS: public WMaxMac
{
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void schedule();
    WMaxMsgDlMap * scheduleDL(int symbols);
    WMaxMsgUlMap * scheduleUL(int symbols);

    // --- configuration parameters ---
    /// minimal size of granted bandwidth on UGS connection
    uint32_t schedUgsMinGrantSize;

    /// frequency of the initial ranging CDMA regions
    uint32_t schedCdmaInitRngFreq;

    /// frequency of the handover ranging CDMA regions
    uint32_t schedCdmaHoRngFreq;

    /// frequency of the bandwidth request CDMA regions
    uint32_t schedCdmaBwrFreq;

    // --- runtime parameters ---
    uint32_t schedCdmaInitRngCnt; // counter
    uint32_t schedCdmaHoRngCnt;
    uint32_t schedCdmaBwrCnt;


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
    void         handleUlMessage(cMessage* msg);

    WMaxStatsSS Stats;
};

#endif
