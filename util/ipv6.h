#ifndef IPV6MSG_H
#define IPV6MSG_H

#include <ostream>
#include <netinet/in.h>

using namespace std;

class IPv6Addr {
public:
    IPv6Addr();
    IPv6Addr(const char a[16], bool plain);
    IPv6Addr(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
    char addr[16];
    
    string plain();
};

ostream & operator <<(ostream & s, IPv6Addr);

#endif
