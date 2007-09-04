/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2006-12-29 01:50:38+0100
 * 
 * @brief  WMax MAC control layer
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>
#include <vector>
#include "wmaxmsg_m.h"
#include "fsm.h"
#include "hoinfo.h"
#include "ssinfo.h"

using namespace std;

#ifndef WMAXCTRL_H
#define WMAXCTRL_H

/**************************************************************/
/*** WIMAX CONSTANTS ******************************************/
/**************************************************************/

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

typedef struct {
    int TransactionID;
    uint16_t cid;
    WMaxQos qos;
} Transaction;


/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class WMaxFlowSS;


class WMaxCtrlSS : public Fsm
{
    typedef enum {
	WMAX_CTRL_NETWORK_ENTRY_INITIAL,
	WMAX_CTRL_NETWORK_REENTRY,
	WMAX_CTRL_NERWORK_SCAN
    } WMaxCtrlNetworkEntryType;

public:
    WMaxCtrlSS();
    cModule *SS;
    void initialize();
    void finish();
    void handleMessage(cMessage *msg);
    list<WMaxFlowSS*> serviceFlows;

    // -- handover related info --
    HoInfo_t * hoInfo;
    WMaxCtrlNetworkEntryType neType;

    // --- STATES ---
    typedef enum {
	// 1. network entry phase
	STATE_WAIT_FOR_DLMAP,             // wait for DL-MAP
	STATE_WAIT_FOR_UCD,               // wait for UCD
	STATE_SEND_RNG_REQ,               // send RNG-REQ
	STATE_WAIT_RNG_RSP,               // wait for RNG-RSP
	STATE_SEND_SBC_REQ,               // send SBC-REQ
	STATE_WAIT_SBC_RSP,               // wait for SBC-RSP
	STATE_WAIT_SA_TEK_CHALLANGE,      // wait for PKM-RSP (SA-TEK-Challange)
	STATE_SEND_SA_TEK_REQ,            // send PKM-REQ (SA-TEK-Request)
	STATE_WAIT_SA_TEK_RSP,            // wait for PKM-RSP (SA-TEK-Response)
	STATE_SEND_REG_REQ,               // send REG-REQ
	STATE_WAIT_REG_RSP,               // wait for REG-RSP

	// 2. service flow creation phase
	STATE_SVC_FLOW_CREATION,             // initialize service flow creation (i.e. start new FSMs for each flow)

	STATE_OPERATIONAL,                // network entry completed, service flows created, normal operation

	/// @todo - implement neighbor advertisements support

        // 3. scanning
        STATE_SEND_MOB_SCN_REQ,
        STATE_WAIT_MOB_SCN_RSP,
	/// @todo - implement scanning

	// handover
	STATE_SEND_MSHO_REQ,              // send MSHO-REQ
	STATE_WAIT_BSHO_RSP,              // wait for BSHO-RSP
	STATE_SEND_HO_IND,                // send HO-IND
	STATE_HANDOVER_COMPLETE,          // handover complete
	
	// network reentry
	STATE_WAIT_FOR_CDMA,              // wait for CDMA opportunity
	STATE_SEND_CDMA,                  // send CDMA code
	STATE_WAIT_ANON_RNG_RSP,          // wait for anonymous RNG-RSP

	STATE_POWER_DOWN,
	STATE_NUM
    } State;

    // --- EVENTS ---
    typedef enum {
	EVENT_HANDOVER_START,
	EVENT_REENTRY_START,
	EVENT_ENTRY_START,
	EVENT_DLMAP,
	EVENT_UCD,
	EVENT_CDMA_CODE,
	EVENT_MOB_SCN_RSP_RECEIVED,
	EVENT_BSHO_RSP_RECEIVED,
	EVENT_HO_CDMA_CODE,
	EVENT_RNG_RSP_RECEIVED,
	EVENT_SBC_RSP_RECEIVED,
	EVENT_SA_TEK_CHALLENGE,
	EVENT_SA_TEK_RSP,
	EVENT_REG_RSP_RECEIVED,
	EVENT_SERVICE_FLOW_COMPLETE, // service flow created
	EVENT_HO_IND_SENT,
	EVENT_NUM
    } Event;

    double hoStartTimestamp;   // timestamp of handover start
    double hoReentryTimestamp; // timestamp of the reentry start
    double hoReentryCompleteTimestamp; // timestamp of the reentry completion
    double hoActionTime; //time of handover idle
    double sendMsg(cMessage * msg, char * paramName, const char * gateName, int cid);
    cStdDev hoActionTimeData;
protected:
    void fsmInit();
  
    void connectNextBS();
    void connectBS(int x); // connect (i.e. make Omnet connections) to BS[x]
    void disconnect();
   
    // wait for DL-MAP state
    static FsmStateType onEventState_WaitForDlmap(Fsm * fsm, FsmEventType e, cMessage *msg);

    // wait for UCD state
    static FsmStateType onEventState_WaitforUcd(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send CDMA code state
    static FsmStateType onEnterState_WaitAnonRngRsp(Fsm * fsm);
    static FsmStateType onExitState_WaitAnonRngRsp(Fsm * fsm);

    // send RNG-REQ state
    static FsmStateType onEnterState_SendRngReq(Fsm * fsm);

    // wait for RNG-RSP state
    static FsmStateType onEventState_WaitForRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg);
    
    // send SBC-REQ state
    static FsmStateType onEnterState_SendSbcReq(Fsm * fsm);

    // wait for SBC-RSP state
    static FsmStateType onEventState_WaitForSbcRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // wait for SA-TEK-CHALLANGE
    static FsmStateType onEventState_WaitForSaTekChallange(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send SA-TEK-REQ
    static FsmStateType onEnterState_SendSaTekReq(Fsm * fsm);

    // wait for SA-TEK-RSP
    static FsmStateType onEventState_WaitForSaTekRsp(Fsm *fsm, FsmEventType e, cMessage *msg);

    // send REG-REQ state
    static FsmStateType onEnterState_SendRegReq(Fsm * fsm);

    // wait for REG-RSP state
    static FsmStateType onEventState_WaitForRegRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // initiate service flow creation state
    static FsmStateType onEnterState_SvcFlowCreation(Fsm * fsm);
    static FsmStateType onEventState_SvcFlowCreation(Fsm * fsm, FsmEventType e, cMessage *msg);

    // operational state
    static FsmStateType onEnterState_Operational(Fsm * fsm);
    static FsmStateType onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send MOB_SCN-REQ
    static FsmStateType onEnterState_SendMobScnReq(Fsm *fsm);

    // wait for MOB_SCN-RSP
    static FsmStateType onEventState_WaitForMobScnRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // send MSHO-REQ state
    static FsmStateType onEnterState_SendMshoReq(Fsm *fsm);

    // wait for BSHO-RSP state
    static FsmStateType onEventState_WaitForBshoRsp(Fsm * fsm, FsmEventType e, cMessage *msg);

    // sent HO-IND state
    static FsmStateType onEventState_SendHoInd(Fsm * fsm, FsmEventType e, cMessage *msg);
    static FsmStateType onEnterState_SendHoInd(Fsm *fsm);
    static FsmStateType onExitState_SendHoInd(Fsm * fsm);
    
    // handover complete state
    static FsmStateType onEnterState_HandoverComplete(Fsm * fsm);

    // wait for CDMA opportunity state
    static FsmStateType onEventState_WaitForCdma(Fsm * fsm, FsmEventType e, cMessage *msg);

    static FsmStateType onEnterState_SendCdma(Fsm *fsm);

    // wait for anonymous RNG-RSP state
    static FsmStateType onEventState_WaitForAnonRngRsp(Fsm * fsm, FsmEventType e, cMessage *msg);
    
    static FsmStateType onEventState_PowerDown(Fsm * fsm, FsmEventType e, cMessage *msg);

    FsmStateType onEvent_CdmaCode(cMessage *msg);

    // --- TIMERS ---
    TIMER_DEF(Handover);
    TIMER_DEF(NetworkEntry);
    TIMER_DEF(Reentry);

private:
    int sfCnt; // number of service flows
    void mihNotify(MihInfo_t notifyType);

    WMaxEvent_FlowCreationStart * createNewFlowEvent();
};

class WMaxCtrlBS : public Fsm
{
public:
    WMaxCtrlBS();
    cModule *BS;
private:
    list<Transaction> Transactions;
    list<SSInfo_t> ssList;
    uint16_t cid;
    int pkmSupport;
    bool pkmEnabled();
protected:
    void fsmInit();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    double sendMsg(cMessage * msg, char * paramName, const char * gateName, int cid);
    uint16_t getNextCid() { return cid++; };
    SSInfo_t * getSS(uint16_t basicCid, string reason);
    void deleteSS(uint16_t basicCid);
};

class WMaxFlowSS : public Fsm
{
public:
    WMaxFlowSS(Fsm * fsm);
    uint16_t cid;
    int gate;
    int transactionID;
    WMaxQos qos;
    void handleMessage(cMessage *msg);
    Fsm *parentFsm;

protected:
    void fsmInit();
//    virtual void initialize();
    

    typedef enum {
        STATE_START,
        STATE_SEND_DSA_REQ,
        STATE_WAITING_DSX_RVD,
        STATE_WAITING_DSA_RSP,
        STATE_SEND_DSA_ACK,
        STATE_OPERATIONAL,
        STATE_DISABLED, 
        STATE_NUM
    } State;

    static FsmStateType onEventState_Start(Fsm * fsm, FsmEventType e, cMessage * msg);
    static FsmStateType onEnterState_SendDsaReq(Fsm * fsm);
    static FsmStateType onEventState_WaitingDsxRvd(Fsm * fsm, FsmEventType e, cMessage * msg);
    static FsmStateType onEventState_WaitingDsaRsp(Fsm * fsm, FsmEventType e, cMessage * msg);
    static FsmStateType onEnterState_SendDsaAck(Fsm * fsm);
    static FsmStateType onEventState_Operational(Fsm * fsm, FsmEventType e, cMessage * msg);
    static FsmStateType onEventState_Disabled(Fsm * fsm, FsmEventType e, cMessage *msg);

    typedef enum {
        EVENT_START,
        EVENT_DSX_RVD_RECEIVED,
        EVENT_DSA_RSP_RECEIVED,
        EVENT_FLOW_DISABLE,
        EVENT_FLOW_ENABLE,
        EVENT_NUM
    } Event;

};

ostream & operator <<(ostream & s, Transaction &trans);
ostream & operator <<(ostream & s, WMaxFlowSS &f);

/// @todo class WMaxFlowBS
#endif
