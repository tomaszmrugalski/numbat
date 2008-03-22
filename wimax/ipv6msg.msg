cplusplus {{

// #include "ipv6msg.h"

}};

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
};

message DHCPv6Advertise
{
fields:
    int preference;
    bool addrParams;
};

message DHCPv6Request
{
fields:
    bool addrParams;
};

message DHCPv6Reply
{
fields:
    bool addrParams;
};

message DHCPv6Confirm
{
fields:
    bool addrParams;
};

