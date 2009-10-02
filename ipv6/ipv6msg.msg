cplusplus {{
#include "ipv6.h"
}}


struct IPv6Addr;

//message --> packet due to migration to v4.0 (MiM)
//In other files: cMessage* pointer replaced by cPacket* (MiM)

//message IPv6
packet IPv6
{
    IPv6Addr srcIP;
    IPv6Addr dstIP;

    bool BindingUpdate;
    bool BindingAck;
    bool Dhcpv6Relay;
}

packet IPv6Ra extends IPv6
{
}


// ********************************************************************************
// *** DHCPv6 packets ************************************************************
// ********************************************************************************

packet DHCPv6Solicit extends IPv6
{
    bool rapidCommit;
    bool addrParams;

    bool remoteConf;
    int remoteBS;
}

packet DHCPv6Advertise extends IPv6
{
    int preference;
    bool addrParams;

    bool remoteConf;
}

packet DHCPv6Request extends IPv6
{
    bool addrParams;

    bool remoteConf;
    int remoteBS;
}

packet DHCPv6Reply extends IPv6
{
    IPv6Addr addr;
    bool addrParams;
    bool remoteConf;
}

packet DHCPv6Confirm extends IPv6
{
    bool addrParams;

    bool remoteConf;
    int remoteBS;
}
