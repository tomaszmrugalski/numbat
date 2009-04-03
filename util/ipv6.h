#ifndef IPV6MSG_H
#define IPV6MSG_H

#include <ostream>
#include "Portable.h"

using namespace std;

class IPv6Addr {
public:
    IPv6Addr();
    IPv6Addr(const char *a, bool plain);
    IPv6Addr(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
    uint64_t MacAddrFromLinkLocal();
    void LinkLocalFromMAC(uint64_t mac);
    bool isMulticast();
    unsigned char addr[16];
    
    string plain();

    bool operator ==(const IPv6Addr &b);
};

ostream & operator <<(ostream & s, IPv6Addr);


#endif
