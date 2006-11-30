cplusplus {{
#include "wmaxmsg.h"
}};

struct WMaxMapIE;

// ********************************************************************************
// *** real WiMAX MAC messages ****************************************************
// ********************************************************************************

message WMaxMsgDlMap
{
    fields:
	WMaxMapIE IE[];
};


message WMaxMsgUlMap
{
    fields:
	WMaxMapIE IE[];
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
