cplusplus {{
#include "ipv6.h"
}};

struct IPv6Addr;

message IPv6
{
fields:
  IPv6Addr srcIP;
  IPv6Addr dstIP;

  bool BindingUpdate;
  bool BindingAck;
  bool Dhcpv6Relay;
};

message IPv6Ra extends IPv6
{


};


// ********************************************************************************
// *** DHCPv6 messages ************************************************************
// ********************************************************************************

message DHCPv6Solicit extends IPv6
{
fields:
    bool rapidCommit;
    bool addrParams;

    bool remoteConf;
    int  remoteBS;
};

message DHCPv6Advertise extends IPv6
{
fields:
    int preference;
    bool addrParams;

    bool remoteConf;
};

message DHCPv6Request extends IPv6
{
fields:
    bool addrParams;

    bool remoteConf;
    int  remoteBS;
};

message DHCPv6Reply extends IPv6
{
fields:
    IPv6Addr addr;
    bool addrParams;
    bool remoteConf;
};

message DHCPv6Confirm extends IPv6
{
fields:
    bool addrParams;

    bool remoteConf;
    int  remoteBS;
};
