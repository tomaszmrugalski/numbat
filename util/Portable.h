#ifdef WIN32

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed long int32_t;
typedef signed long long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long int uint64_t;

extern int    inet_pton6(const unsigned char* src, char* dst);
extern char * inet_ntop6(const unsigned char* src, char* dst, int dstSize); 

#else

#include <sys/socket.h>
#include <arpa/inet.h>

#endif

#ifdef LINUX
inet_pton6(const char *plain, char *dst)
{
    inet_pton(AF_INET6, a, addr);
}
#endif
