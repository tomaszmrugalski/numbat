cplusplus {{
#include "ipv6.h"
}}


struct IPv6Addr;

// ********************************************************************************
// *** Media Independent Handover: messages used to notify other layers ***********
// ********************************************************************************

//message -> packet changes (MiM)
// used to report that L2 entry started
packet MihEvent_EntryStart
{
}

// used to report that L2 entry finished
packet MihEvent_EntryEnd
{
}

// used to report that L2 handover started
packet MihEvent_HandoverStart
{
    int targetBS;
}

// used to report by WMaxPhySS to WMaxCtrlSS that HO-IND was actually transmitted
packet MihEvent_HandoverEnd
{
}

// used to report that L2 reentry started
packet MihEvent_ReentryStart
{
}

// used to report that L2 reentry finished
packet MihEvent_ReentryEnd
{
}

// used to report that IPv6 address has been obtained
packet MihEvent_L3AddrConfigured
{
    IPv6Addr Addr;
    bool RemoteAutoconf;
}

packet MihEvent_L3RoutingConfigured
{
}

// support for this is not implemented yet
packet MihEvent_L3LocationUpdated
{
}
