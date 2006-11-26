cplusplus {{
#include "wmaxmsg.h"
}};

struct WMaxMapIE;

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
