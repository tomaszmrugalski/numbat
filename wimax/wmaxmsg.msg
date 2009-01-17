cplusplus {{
#include "wmaxmsg.h"
#include "ipv6.h"
}};

struct WMaxUlMapIE;
struct WMaxDlMapIE;
struct WMaxBSFull;
struct WMaxQos;
struct WMaxRngReq;
struct WMaxRngRsp;
struct IPv6Addr;
struct uint64_t;

// ********************************************************************************
// *** real WiMAX MAC messages ****************************************************
// ********************************************************************************

class WMaxMacHeader
{
properties:
    customize=true;
fields:
    abstract int cid;
    abstract bool ht;
    abstract int bwr;
};

message WMaxMsgDlMap
{
fields:
    WMaxDlMapIE IE[];
};


message WMaxMsgUlMap
{
fields:
    WMaxUlMapIE IE[];
};

message WMaxMsgDCD
{
fields:
    int confChangeCount;
};

message WMaxMsgUCD
{
fields:
    int confChangeCount;
};

message WMaxMsgRngReq
{
fields:
    int purpose;
    WMaxRngReq rngReq;

// used during HO (to perform CID update and recreate connections at target BS)
    WMaxQos SfQos[];
    int     SfCid[];
};

message WMaxMsgRngRsp
{
fields:
    int purpose;
    WMaxRngRsp rngRsp;

// used during HO (to perform CID update and recreate connections at target BS)
    int oldCid[];
    int newCid[];
};

message WMaxMsgSbcReq
{

};
message WMaxMsgSbcRsp
{

};

message WMaxMsgPkmReq
{
fields:
    int code;
};

message WMaxMsgPkmRsp
{
fields:
    int code;
};

message WMaxMsgRegReq
{

};
message WMaxMsgRegRsp
{
};

message WMaxMsgMobScnReq
{

};

message WMaxMsgMobScnRsp
{

};

message WMaxMsgMSHOREQ
{
fields:
    WMaxBSFull BSFull[];
}

message WMaxMsgBSHORSP
{
fields:
    WMaxBSFull BSFull[];
}

message WMaxMsgHOIND
{
fields:
    int status;
    WMaxBSFull target;
}

message WMaxMsgCDMA
{
fields:
    int code;
    int purpose; // use WMaxCdmaPurpose type here

    /// @todo - add other parameters
}

message WMaxMsgBWR
{

}

// Table 38
message WMaxMsgDsaReq
{
fields:
    int transactionID;
    WMaxQos qos[];
}

// Table 56
message WMaxMsgDsxRvd
{
fields:
    int transactionID;
    int confirmationCode; // Table 384
}

// Table 39
message WMaxMsgDsaRsp
{
fields:
    int transactionID;
    int confirmationCode; // Table 384
    WMaxQos qos[];
    int cid;
}

// Table 40
message WMaxMsgDsaAck
{
fields:
    int transactionID;
    int confirmationCode; // Table 384
    WMaxQos qos[];
}

// ********************************************************************************
// *** fake messages used to communicate between modules **************************
// ********************************************************************************

// this message is sent once every 5ms from MAC to PHY to initiate next frame
message WMaxPhyDummyFrameStart
{

};

message WMaxEvent_FlowCreationStart
{
fields:
    int skipDSA;
    int gateIndex;
    WMaxQos qos[];
}

message WMaxMacAddConn
{
fields:
    int gateIndex;
    int cid;
    WMaxQos qos[];
    IPv6Addr dstAddr;
    uint64_t macAddr;
}

message WMaxMacAddMngmntConn
{
fields:
    int cid;
};

message WMaxEvent_DelConn
{
fields:
    int cid;
};

message WMaxEvent_FlowEnable
{

};

message WMaxEvent_FlowDisable
{

};

message WMaxMacTerminateAllConns
{

};


