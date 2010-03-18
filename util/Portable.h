#ifndef PORTABLE_H
#define PORTABLE_H

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

int    inet_pton6(const char* src, char* dst);
const char * inet_ntop6(const char* src, char* dst, int dstSize); 

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
}
#endif



#ifdef WIN32
typedef signed char int8_t;
typedef signed short int16_t;
//typedef signed long int32_t;
typedef signed long long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;
typedef unsigned long long int uint64_t;


#else

#include <sys/socket.h>
#include <arpa/inet.h>

#endif

#endif
