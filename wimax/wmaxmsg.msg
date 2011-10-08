cplusplus {{
#include "wmaxmsg.h"
//#include "ipv6.h"
#include "IPv6Address.h"	//Adam
}}


struct WMaxUlMapIE;

struct WMaxDlMapIE;

struct WMaxBSFull;

struct WMaxQos;

struct WMaxRngReq;

struct WMaxRngRsp;

struct IPv6Address;

//struct uint64_t;//MiM removed

// ********************************************************************************
// *** real WiMAX MAC messages ****************************************************
// ********************************************************************************


class WMaxMacHeader
{
    @customize(true);
    abstract int cid;
    abstract bool ht;
    abstract int bwr;
}

//message --> packet changes (MiM)
//message WMaxMsgDlMap
packet WMaxMsgDlMap
{
    WMaxDlMapIE IE[];
}


packet WMaxMsgUlMap
{
    WMaxUlMapIE IE[];
}

packet WMaxMsgDCD
{
    int confChangeCount;
}

packet WMaxMsgUCD
{
    int confChangeCount;
}

packet WMaxMsgRngReq
{
    int purpose;
    WMaxRngReq rngReq;
    IPv6Address myIP; // used in remote autoconf

    // used during HO (to perform CID update and recreate connections at target BS)
    WMaxQos SfQos[];
    int SfCid[];
}

packet WMaxMsgRngRsp
{
    int purpose;
    WMaxRngRsp rngRsp;

    // used during HO (to perform CID update and recreate connections at target BS)
    int oldCid[];
    int newCid[];
}

packet WMaxMsgSbcReq
{
}
packet WMaxMsgSbcRsp
{
}

packet WMaxMsgPkmReq
{
    int code;
}

packet WMaxMsgPkmRsp
{
    int code;
}

packet WMaxMsgRegReq
{
}
packet WMaxMsgRegRsp
{
}

packet WMaxMsgMobScnReq
{
}

packet WMaxMsgMobScnRsp
{
}

packet WMaxMsgMSHOREQ
{
    WMaxBSFull BSFull[];
}

packet WMaxMsgBSHORSP
{
    WMaxBSFull BSFull[];
}

packet WMaxMsgHOIND
{
    int status;
    WMaxBSFull target;
}

packet WMaxMsgCDMA
{
    int code;
    int purpose; // use WMaxCdmaPurpose type here

    /// @todo - add other parameters
}

packet WMaxMsgBWR
{
}

// Table 38
packet WMaxMsgDsaReq
{
    int transactionID;
    WMaxQos qos[];
}

// Table 56
packet WMaxMsgDsxRvd
{
    int transactionID;
    int confirmationCode; // Table 384
}

// Table 39
packet WMaxMsgDsaRsp
{
    int transactionID;
    int confirmationCode; // Table 384
    WMaxQos qos[];
    int cid;
}

// Table 40
packet WMaxMsgDsaAck
{
    int transactionID;
    int confirmationCode; // Table 384
    WMaxQos qos[];
}

// ********************************************************************************
// *** fake packets used to communicate between modules **************************
// ********************************************************************************

// this packet is sent once every 5ms from MAC to PHY to initiate next frame
packet WMaxPhyDummyFrameStart
{
}

packet WMaxEvent_FlowCreationStart
{
    int skipDSA;
    int gateIndex;
    WMaxQos qos[];
}

packet WMaxMacAddConn
{
    int gateIndex;
    int cid;
    WMaxQos qos[];
    IPv6Address dstAddr;
    uint64_t macAddr;
}

packet WMaxMacAddMngmntConn
{
    int cid;
}

packet WMaxEvent_DelConn
{
    int cid;
    bool isBasic;
}

packet WMaxEvent_FlowEnable
{
}

packet WMaxEvent_FlowDisable
{
}

packet WMaxMacTerminateAllConns
{
}

packet WMaxHandoverNotify // L2 informing L3 about incoming handover
{
    int BS_index;    // should be AP-ID, BSID
}

packet WMaxHandoverNotifyAcknowledge
{
}

