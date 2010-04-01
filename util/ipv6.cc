#include <ostream>
#include "ipv6.h"
#include <sys/types.h>
#include "Portable.h"
#include "logger.h"

using namespace std;

#if 0
int inet_pton6(const char *plain, char *dst)
{
    return inet_pton(AF_INET6, plain, dst);
}

const char * inet_ntop6(const char* src, char* dst, int dstSize)
{
    return inet_ntop(AF_INET6, src, dst, dstSize);
}
#endif


IPv6Addr::IPv6Addr() 
{ 
    memset(addr, 0, 16); 
}

IPv6Addr::IPv6Addr(const char * a, bool plain)
{
    if (!plain)
	memcpy(addr, a, 16);
    else
    inet_pton6(a, (char*)addr);
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
    //inet_ntop(AF_INET6, addr, buf, 80);
    inet_ntop6((const char*)addr, buf, 80);
    return string(buf);
}

void IPv6Addr::LinkLocalFromMAC(const uint64_t macAddr)
{
    memset(addr, 0, 16);
    addr[15] = (unsigned char)((macAddr )      & 0xff);
    addr[14] = (unsigned char)((macAddr >>  8) & 0xff);
    addr[13] = (unsigned char)((macAddr >> 16) & 0xff);
    addr[12] = 0xfe;
    addr[11] = 0xff;
    addr[10] = (unsigned char)((macAddr >> 24) & 0xff);
    addr[9] = (unsigned char)((macAddr >> 32) & 0xff);
    addr[8] = (unsigned char)((macAddr >> 40) & 0xff);
    addr[1] = 0x80;
    addr[0] = 0xfe;
}

uint64_t IPv6Addr::MacAddrFromLinkLocal()
{
    if ( (addr[0]!=0xfe) || (addr[1]!=0x80) )
    {
	return 0;
    }
    unsigned char tbl[6];
    memcpy(tbl+3, addr+13,3);
    memcpy(tbl, addr+8,3);

    uint64_t m = ((uint64_t)tbl[5]) 
	+ ((uint64_t)tbl[4] << 8)
	+ ((uint64_t)tbl[3] << 16)
	+ ((uint64_t)tbl[2] << 24)
	+ ((uint64_t)tbl[1] << 32)
	+ ((uint64_t)tbl[0] << 40);
    return m;
}

bool IPv6Addr::isMulticast()
{
    return (addr[0]==0xff);
}

ostream & operator <<(ostream & s, IPv6Addr a) 
{
    char buf[80];
    // inet_ntop(AF_INET6, a.addr, buf, 80);
    inet_ntop6((const char*)a.addr, buf, 80);
    s << string(buf);

    return s;
}

bool IPv6Addr::operator==(const IPv6Addr &b)
{
    if (!memcmp(addr, b.addr, 16))
	return true;
    return false;
}
