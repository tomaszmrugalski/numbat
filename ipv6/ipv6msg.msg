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
};

message IPv6Ra
{


};


// ********************************************************************************
// *** DHCPv6 messages ************************************************************
// ********************************************************************************

message DHCPv6Solicit
{
fields:
    bool rapidCommit;
    bool addrParams;

    bool remoteConf;
};

message DHCPv6Advertise
{
fields:
    int preference;
    bool addrParams;

    bool remoteConf;
};

message DHCPv6Request
{
fields:
    bool addrParams;

    bool remoteConf;
};

message DHCPv6Reply
{
fields:
    IPv6Addr addr;
    bool addrParams;
    bool remoteConf;
};

message DHCPv6Confirm
{
fields:
    bool addrParams;

    bool remoteConf;
};

