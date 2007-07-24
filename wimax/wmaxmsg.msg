cplusplus {{
#include "wmaxmsg.h"
}};

struct WMaxUlMapIE;
struct WMaxDlMapIE;
struct WMaxBSFull;
struct WMaxQos;
struct WMaxRngReq;
struct WMaxRngRsp;

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
};

message WMaxMsgRngRsp
{
fields:
    int purpose;
    WMaxRngRsp rngRsp;
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

message WMaxCtrlFlowCreationStart
{
fields:
    int gateIndex;
    WMaxQos qos[];
}

message WMaxMacAddConn
{
fields:
    int gateIndex;
    int cid;
    WMaxQos qos[];
}

message WMaxMacAddMngmntConn
{
fields:
    int cid;
}

message WMaxEvent_DelConn
{
fields:
    int cid;
}

message WMaxMacTerminateAllConns
{

};

// used to report by WMaxPhySS to WMaxCtrlSS that HO-IND was actually transmitted
message WMaxEvent_HoIndSent
{

};