#include <ostream>
#include "ipv6.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

IPv6Addr::IPv6Addr() 
{ 
    memset(addr, 0, 16); 
}

IPv6Addr::IPv6Addr(const char * a, bool plain)
{
    if (!plain)
	memcpy(addr, a, 16);
    else
	inet_pton(AF_INET6, a, addr);
}

IPv6Addr::IPv6Addr(unsigned int a, unsigned int b, unsigned int c, unsigned int d) 
{
    unsigned int x;
    x = htonl(a); memcpy(addr,   &x, 4);
    x = htonl(b); memcpy(addr+4, &x, 4);
    x = htonl(c); memcpy(addr+8, &x, 4);
    x = htonl(d); memcpy(addr+12,&x, 4);
} 

string IPv6Addr::plain()
{
    char buf[80];
    inet_ntop(AF_INET6, addr, buf, 80);
    return string(buf);
}

ostream & operator <<(ostream & s, IPv6Addr a) {

    char buf[80];
    inet_ntop(AF_INET6, a.addr, buf, 80);
    s << string(buf);

    return s;
}
