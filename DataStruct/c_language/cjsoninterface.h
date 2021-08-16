#ifndef CJSONINTERFACE_H
#define CJSONINTERFACE_H

#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

uint8_t * fun_GetCjsonBuf( uint32_t & pRetBufSize );
void sub_CjsonMemoryChanage( void );

void sub_TestQuickSort( void );

#if __cplusplus
}
#endif

#endif // CJSONINTERFACE_H
