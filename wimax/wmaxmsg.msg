cplusplus {{
#include "wmaxmsg.h"
}};

struct WMaxUlMapIE;
struct WMaxDlMapIE;

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


// ********************************************************************************
// *** fake messages used to communicate between modules **************************
// ********************************************************************************

// this message is sent once every 5ms from MAC to PHY to initiate next frame
message WMaxPhyDummyFrameStart
{

};
