/* Alloc.c -- Memory allocation functions
2008-09-24
Igor Pavlov
Public domain */

#include <stdlib.h>

#include "7alloc.h"

#if defined(__mips__) || defined(__arm__)
    #define __loader_2nd
    #define __loader_2nd_bss
    #define __loader_2nd_rodata
    #define __loader_2nd_data
    #define __loader_2nd_common
#else
    #define __loader_2nd __attribute__ ((__section__ (".loader_2nd.text")))
    #define __loader_2nd_bss __attribute__ ((__section__ (".loader_2nd.bss")))
    #define __loader_2nd_rodata __attribute__ ((__section__ (".loader_2nd.rodata")))
    #define __loader_2nd_data __attribute__ ((__section__ (".loader_2nd.data")))
    #define __loader_2nd_common __attribute__ ((__section__ (".loader_2nd.common")))
#endif

// #define _SZ_ALLOC_DEBUG

/* use _SZ_ALLOC_DEBUG to debug alloc/free operations */
#ifdef _SZ_ALLOC_DEBUG
#include <stdio.h>
int g_allocCount = 0;
#endif

extern void __loader_2nd *zalloc(void *ptr, unsigned long nNum, unsigned long nSize);
extern void __loader_2nd zfree(void *x, void *address, unsigned nbytes);

void __loader_2nd *MyAlloc(size_t size)
{
  void *ptr = NULL;
  
  if (size == 0)
    return 0;
  #ifdef _SZ_ALLOC_DEBUG
  {
    void *p = zalloc(ptr, 1, size);
	printf("\nAlloc %10d bytes, count = %10d,  addr = %8X", (int)size, g_allocCount++, (unsigned)p);
    return p;
  }
  #else
  return zalloc(ptr, 1, size);
  #endif
}

void __loader_2nd MyFree(void *address)
{
  #ifdef _SZ_ALLOC_DEBUG
  if (address != 0)
	printf("\nFree; count = %10d,  addr = %8X", --g_allocCount, (unsigned)address);
  #endif
  zfree(address, address, 4);
}

