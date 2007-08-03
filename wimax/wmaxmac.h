/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Mon Nov 20 00:23:08 2006
 * 
 * @brief  WMax MAC layer definitions
 * @licence GNU GPLv2
 * 
 */

#include <stdint.h>
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

// define frequency of the BWR CDMA slots (2 = one alloc per 2 frames) (in # of frames)
#define WMAX_CDMA_BWR_FREQ 2

// define frequency of the initial ranging CDMA slots (in # of frames)
#define WMAX_CDMA_INIT_RNG_FREQ 3

// define frequency of the handover CDMA slots (in # of frames)
#define WMAX_CDMA_HO_RNG_FREQ 10 

// define frequency of DCD transmissions (in # of frames)
#define WMAX_DCD_FREQ 5

// define frequenct of UCD transmissions (in # of frames)
#define WMAX_UCD_FREQ 5

// minimal UGS grant, which can be assigned
#define WMAX_SCHEDULER_MIN_UGS_GRANT 120

// bytes per symbol (simplification, this value may be different for each modulation)
#define WMAX_BYTES_PER_SYMBOL 12 


#define WMAX_CID_RANGING   0
#define WMAX_CID_BROADCAST 0xffff

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

// typedef enum
// {
//     WMAX_CONN_TYPE_BE,    // best effort
//     WMAX_CONN_TYPE_RTPS,
//     WMAX_CONN_TYPE_NRTPS, // Non-Real Time Packet Switched
//     WMAX_CONN_TYPE_UGS    // Unsolicited Grant Interval
// } WMaxConnType;

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
    int reqbw; // required bandwidth
} WMaxConnBe;


typedef struct {
    int code;
    int bandwidth;
    uint16_t cid;
} WMaxMacCDMA;

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
    cQueue * queue;
    uint32_t bandwidth;

    int gateIndex; // index of a gate associated with this connection
    bool controlConn; // is this a control connection? (i.e. send DL-MAP,UL-MAP there?)
} WMaxConn;

class WMaxMacHeader : public WMaxMacHeader_Base //public cPolymorphic
{
public:
    WMaxMacHeader() { cid=0xffff; ht=0; bwr=0; }
    virtual WMaxMacHeader_Base *dup() const  {return new WMaxMacHeader(*this);}
    uint16_t cid;
    bool ht;
    int bwr;

    virtual int getCid() const { return cid; }
    virtual void setCid(int cid_var) { cid=cid_var; }
    virtual bool getHt() const { return ht; }
    virtual void setHt(bool ht_var) { ht=ht_var; }
    virtual int getBwr() const { return bwr; }
    virtual void setBwr(int bwr_var) { bwr=bwr_var; }

};

ostream & operator<<(ostream & strum, WMaxMacCDMA &x);
ostream & operator<<(ostream & s, WMaxConn &x);

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/
class WMaxStatsSS 
{
public:
    int rcvdGrants;    /* number of grants received */
    int rcvdBandwidth; /* total bandwidth granted */
    int rcvdDlmaps;    /* number of dlmaps received */
    int rcvdUlmaps;    /* number of ulmaps received */
    
    int dropInvalidCid; /* number of dropped messages due to invalid cid (missing connection?) */
};

#define STAT_INC(a) this->Stats. a ++;
#define STAT_ADD(a, x) this->Stats. a += x;

class WMaxMac : public cSimpleModule
{
 public:
    WMaxMac();
    void addManagementConn(uint16_t cid);

 protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
    bool addConn(WMaxConn conn);
    bool delConn(uint16_t cid);
    void addRangingConn();

    // --- runtime parameters ---
    cQueue SendQueue;
    cQueue * CDMAQueue;
    int GateIndex;

    // --- configuration parameters ---
    list<WMaxConn> Conns;
    double FrameLength;

    virtual void handleRxMessage(cMessage *msg);
    virtual void handleTxMessage(cMessage *msg);
    virtual void printDlMap(WMaxMsgDlMap * dlmap);
    virtual void printUlMap(WMaxMsgUlMap * ulmap);
    virtual void stringUpdate();
    int queuedMsgsCnt;

    WMaxStatsSS Stats;
};


class WMaxMacBS: public WMaxMac
{
 protected:
    void setInitialPosition();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    //void handleUlMessage(cMessage* msg);
    void handleRxMessage(cMessage* msg);

    void schedule();
    void scheduleBcastMessages(); // prepare broadcast messages sent periodically (DCD, UCD, Neighbor-Advertisements)
    WMaxMsgDlMap * scheduleDL(int symbols);
    WMaxMsgUlMap * scheduleUL(int symbols);

    // --- configuration parameters ---
    uint32_t schedUgsMinGrantSize; // minimal size of granted bandwidth on UGS connection
    uint32_t schedCdmaInitRngFreq; // frequency of the initial ranging CDMA regions
    uint32_t schedCdmaHoRngFreq;   // frequency of the handover ranging CDMA regions
    uint32_t schedCdmaBwrFreq;     // frequency of the bandwidth request CDMA regions
    uint32_t schedUcdFreq;         // frequency of UCD transmissions
    uint32_t schedDcdFreq;         // frequency of DCD transmissions

    // --- runtime parameters ---
    uint32_t schedCdmaInitRngCnt; // counter
    uint32_t schedCdmaHoRngCnt;
    uint32_t schedCdmaBwrCnt;
    uint32_t schedDcdCnt;
    uint32_t schedUcdCnt;

    cMessage * TxStart;
};

class WMaxMacSS: public WMaxMac
{

 protected:
    void setInitialPosition();
    void changePosition();
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);
    virtual void finish();

    list<WMaxMacCDMA> CDMAlist; //WMaxMac::cdmaQueue is used instead
    int BEpoint;
    cMessage * ChangePosition;

 private:
    virtual void schedule(WMaxMsgUlMap* ulmap);
    void         handleRxMessage(cMessage* msg);
};

#endif
