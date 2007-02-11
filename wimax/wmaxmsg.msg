cplusplus {{
#include "wmaxmsg.h"
}};

struct WMaxUlMapIE;
struct WMaxDlMapIE;
struct WMaxBSFull;

// ********************************************************************************
// *** real WiMAX MAC messages ****************************************************
// ********************************************************************************

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

// ********************************************************************************
// *** fake messages used to communicate between modules **************************
// ********************************************************************************

// this message is sent once every 5ms from MAC to PHY to initiate next frame
message WMaxPhyDummyFrameStart
{

};
