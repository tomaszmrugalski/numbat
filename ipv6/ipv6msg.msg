cplusplus {{

// #include "ipv6msg.h"

}};


message IPv6
{
fields:
  int srcIP;
  int dstIP;
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
    bool addrParams;

    bool remoteConf;
};

message DHCPv6Confirm
{
fields:
    bool addrParams;

    bool remoteConf;
};

