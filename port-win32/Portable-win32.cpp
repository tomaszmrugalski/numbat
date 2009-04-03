
#include "Portable.h"

int inet_pton6(const unsigned char* src, char* dst)
{
    return 0;
}

char * inet_ntop6(const unsigned char* src, char* dst, int dstSize)
{
    return 0;
}

#if 0
extern "C" {
  //CRTIMP 
    void __cdecl _invalid_parameter_noinfo(void) {  }
}
#endif
