////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if 1
typedef unsigned char   U8;
typedef unsigned int   U16;
typedef unsigned long  U32;
#ifndef BOOL
typedef unsigned int BOOL;
#endif
/// defination for FALSE
#define FALSE           0
/// defination for TRUE
#define TRUE            1

#define NULL 0
#if defined(ENABLE_MSTAR_TITANIA_BD_MSD380B_D01A) || defined(ENABLE_MSTAR_TITANIA_BD_MSD523B_D01A) || defined(ENABLE_MSTAR_JANUS_BD_MST216A_JNS_10A_9463)
#if (ENABLE_MSTAR_TITANIA_BD_MSD380B_D01A || ENABLE_MSTAR_TITANIA_BD_MSD523B_D01A || ENABLE_MSTAR_JANUS_BD_MST216A_JNS_10A_9463)
#define USE_BDMA_FOR_CRC_CHECK 1
#endif
#endif

#if (ENABLE_MSTAR_MARIA10 || ENABLE_MSTAR_MACAW12 || ENABLE_MSTAR_EDEN || ENABLE_MSTAR_EULER || ENABLE_MSTAR_NASA)
#define USE_BDMA_FOR_CRC_CHECK 1
#endif

#if (ENABLE_SBOOT_USE_BDMA_TO_CHECK_CRC)
#define USE_BDMA_FOR_CRC_CHECK 1
#endif

#ifndef USE_BDMA_FOR_CRC_CHECK
#define USE_BDMA_FOR_CRC_CHECK 0
#endif

#define UBOOT_IDENTIFIER    0x0000B007

#if defined(__mips__)
    #define RIU_MAP 0xBF200000
    #define LOCAL_BDMA_REG_BASE 0x900
#elif defined(__aeon__)
    #define RIU_MAP 0xA0000000
#elif defined(__arm__) || defined(__arm64__) 
    #define RIU_MAP 0x1F000000
    #define LOCAL_BDMA_REG_BASE    0x900
    #define USE_BDMA_MOVE_CODE 1
#else
    #error not define
#endif

#if defined(__aeon__)
    #define RIU     ((unsigned short volatile *) RIU_MAP)
    #define RIU8    ((unsigned char  volatile *) RIU_MAP)
#endif

#include "zlib.h"
#include "ms_decompress_priv.h"
#include "version.h"



#ifdef __mips__
    #if (ENABLE_BOOTING_FROM_OTP_WITH_PM51==1)
    #define AP_IN_FLASH_ADDR    0xB4030000      //This address should be 4' alignment
    #else
        #ifdef CONFIG_MSTAR_KAISERIN
            #define AP_IN_FLASH_ADDR    0x94020000      //This address should be 4' alignment
        #else
          #if defined(CONFIG_PM_SIZE_KB_FORCED) && (CONFIG_PM_SIZE_KB_FORCED!=0)
            #define AP_IN_FLASH_ADDR    (0xBFC10000+(CONFIG_PM_SIZE_KB_FORCED*0x400))      //This address should be 4' alignment
          #else
		  	#if defined(CONFIG_MSTAR_RT_PM_IN_SPI)
				#define AP_IN_FLASH_ADDR    0xBFC30000      //This address should be 4' alignment
			#else
				#if defined(CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT)
					#define AP_IN_FLASH_ADDR    0xA51F0180//CONFIG_UBOOT_LOADADDR//0xBFC20000      //This address should be 4' alignment
					#define AP_IN_FLASH_ADDR_CACHE    0x851F0180//CONFIG_UBOOT_LOADADDR//0xBFC20000      //This address should be 4' alignment
				#else
	            	#define AP_IN_FLASH_ADDR    0xBFC20000      //This address should be 4' alignment
				#endif
            #endif
          #endif
        #endif
    #endif
#elif defined(__arm__) || defined(__arm64__)
    #if (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51)
        #define AP_IN_FLASH_ADDR    0x14020000+0x10000      //This address should be 4' alignment
    #else
        #if defined(CONFIG_MSTAR_RT_PM_IN_SPI)
        #define AP_IN_FLASH_ADDR    0x14030000      //This address should be 4' alignment
        #else
        #if (ENABLE_MSTAR_PUMABOOT)
        #define AP_IN_FLASH_ADDR    (0x14020000+CONFIG_PUMABOOT_SIZE)      //This address should be 4' alignment
        #else
        #define AP_IN_FLASH_ADDR    0x14020000      //This address should be 4' alignment
        #endif
        #endif
    #endif
#else
    #ifdef __AEONR2__
        #if (ENABLE_MSTAR_MARIA10)
        #include "maria10/hwreg.h"
        #elif (ENABLE_MSTAR_MACAW12)
        #include "macaw12/hwreg.h"
        #elif (ENABLE_MSTAR_EDEN)
        #include "eden/hwreg.h"
        #elif (ENABLE_MSTAR_EULER)
        #include "euler/hwreg.h"
        #elif (ENABLE_MSTAR_NASA)
        #include "nasa/hwreg.h"
        #else
        #include "janus/hwreg.h"
        #endif
    #endif

    #define AP_IN_FLASH_ADDR    0x00020000      //This address should be 4' alignment
#endif

#if defined(__mips__) || defined(__arm__) || defined(__arm64__)
    #define __loader_2nd
    #define __loader_2nd_bss
#else
    #define __loader_2nd __attribute__ ((__section__ (".loader_2nd.text")))
    #define __loader_2nd_bss __attribute__ ((__section__ (".loader_2nd.bss")))
#endif

unsigned char __loader_2nd_bss *pDecompressionBuf = NULL;
unsigned char __loader_2nd_bss *pEndofDecompressionBuf = NULL;
unsigned char __loader_2nd_bss *pCurrentBufPtr = NULL;

void MemoryAllocatorInit(unsigned char *ptr, unsigned long nSize);
extern void __BDMA_FlashCopy2MIU0(U32 FlashPA, U32 DRAMPA, U32 Len);
extern void mhal_dcache_flush(U32 u32Base, U32 u32Size);
void *zalloc(void *ptr, unsigned long nNum, unsigned long nSize);
void zfree(void *x, void *address, unsigned nbytes);
U8 MsDecompress(U8 *pSrc, U8 *pDst, U32 srclen, U32 dstlen, U32 *pDecompressionLength);
void DoMSDecompression(void);
/*void init_version(void);

void __loader_2nd init_version(void)
{
    //Init version
    static U8 tmpVar;
    tmpVar = _sbt_version.APP.tag[0];
}
*/

void __loader_2nd MemoryAllocatorInit(unsigned char *ptr, unsigned long nSize)
{
   pDecompressionBuf = ptr;
   pEndofDecompressionBuf = pDecompressionBuf + nSize*sizeof(unsigned char);
   pCurrentBufPtr = pDecompressionBuf;
}

void __loader_2nd *zalloc(void *ptr, unsigned long nNum, unsigned long nSize)
{
// Because C language use call by value
// so if we modify ptr value, it will not afftect the caller value
// Considering decompression performance, we don't do memory pool
// region check here
#if 0
    nSize = ( nSize*nNum + 3 ) & ~3;

    ptr = (void *)pCurrentBufPtr;
    pCurrentBufPtr += nSize;

    if (pCurrentBufPtr > pEndofDecompressionBuf)
    {
        printf("Memory Allocate Fail\n");
        ptr = NULL;
    }
#else
    ptr = (void *)pCurrentBufPtr;
    // 4' alignment
    pCurrentBufPtr += ( nSize*nNum + 3 ) & ~3;
#endif
    return ptr;
}

void __loader_2nd zfree(void *x, void *address, unsigned nbytes)
{
    // Considering decompression performance, we don't
    // do memory free operation here
    // This will cause a lot of memory usage, but I think we can
    // afford this, because our target files are not so big
    x = x;
    address = address;
    nbytes = nbytes;
}

/*inline void _HaltCPU(void)
{
    //halt cpu
    __asm__ __volatile__(
        "\tSDBBP");
}*/

U8 __loader_2nd MsDecompress(U8 *pSrc, U8 *pDst, U32 srclen, U32 dstlen, U32 *pDecompressionLength)
{
    z_stream z;
    z.opaque=NULL;
    z.zalloc = (alloc_func)zalloc;
    z.zfree = zfree;
    z.next_in = pSrc;
    z.avail_in = srclen;
    z.next_out = pDst;
    z.avail_out = dstlen;

    if ( inflateInit2(&z, -MAX_WBITS) != Z_OK )
    {
        //printf("Z Error:%s\n", z.msg);
        inflateEnd(&z);
        return 1;
    }

    if ( inflate(&z, Z_FINISH) < Z_OK )
    {
        //printf("Z Error:%s\n", z.msg);
        inflateEnd(&z);
        return 1;
    }

    *pDecompressionLength = z.total_out;

    inflateEnd(&z);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
/* 2009-08-14 : Igor Pavlov : Public domain */

#include "7types.h"
#include "7alloc.h"
#include "lzmadec.h"

__loader_2nd void *SzAlloc(void *p, size_t size);
__loader_2nd void SzFree(void *p, void *address);
U8 __loader_2nd MsDecompress7(U8 *pSrc, U8 *pDst, U32 srclen);

__loader_2nd void *SzAlloc(void *p, size_t size) { p = p; return MyAlloc(size); }
__loader_2nd void SzFree(void *p, void *address) { p = p; MyFree(address); }
__loader_2nd_bss ISzAlloc g_Alloc = { SzAlloc, SzFree };
/////////////////////////////////////////////////////////////////////////////

#if (ENABLE_BOOTING_FROM_EXT_EMMC_WITH_CPU == 0)
U8 __loader_2nd MsDecompress7(U8 *pSrc, U8 *pDst, U32 srclen)
{
    U32 OriginalFileLength = 0;
    int result = SZ_OK;
    U8 i;
    ELzmaStatus estatus;
    SizeT destLen, srcLen;

    #define LZMA_PROPS_SIZE 5
    estatus=LZMA_STATUS_NOT_SPECIFIED;

    /* header: 5 bytes of LZMA properties and 8 bytes of uncompressed size */
    srclen -= (LZMA_PROPS_SIZE + 8);

    // It seems that in our system, we never have a chance to have a compressed data which needs to use U64 integer to store its file size
    // So we use just U32 here to instead of U64
    /* Read and parse header */
    for (i = 0; i < 8; i++)
        OriginalFileLength += ( (U32)pSrc[LZMA_PROPS_SIZE + i] << (i << 3) );

    destLen = OriginalFileLength;
    srcLen = srclen;

    result = LzmaDecode(pDst, &destLen, pSrc + (LZMA_PROPS_SIZE + 8), &srcLen, pSrc, LZMA_PROPS_SIZE, LZMA_FINISH_ANY, &estatus, &g_Alloc);

    switch( estatus )
    {
    case LZMA_STATUS_FINISHED_WITH_MARK:
    case LZMA_STATUS_NOT_FINISHED:
    case LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK:
        break;
    default:
    //LZMA_STATUS_NOT_SPECIFIED,               /* use main error code instead */
    //LZMA_STATUS_NEEDS_MORE_INPUT,            /* you must provide more input bytes */
        //printf("ELzmaStatus = %d\n", estatus);
        //Decompression fail!
        return FALSE;
    }

    if (result != SZ_OK)
    {
    //  SZ_ERROR_DATA - Data error
    //  SZ_ERROR_MEM  - Memory allocation error
    //  SZ_ERROR_UNSUPPORTED - Unsupported properties
    //  SZ_ERROR_INPUT_EOF - It needs more bytes in input buffer (src).
    //#define SZ_ERROR_DATA 1
    //#define SZ_ERROR_MEM 2
    //#define SZ_ERROR_CRC 3
    //#define SZ_ERROR_UNSUPPORTED 4
    //#define SZ_ERROR_PARAM 5
    //#define SZ_ERROR_INPUT_EOF 6
    //#define SZ_ERROR_OUTPUT_EOF 7
    //#define SZ_ERROR_READ 8
    //#define SZ_ERROR_WRITE 9
    //#define SZ_ERROR_PROGRESS 10
    //#define SZ_ERROR_FAIL 11
    //#define SZ_ERROR_THREAD 12
    //#define SZ_ERROR_ARCHIVE 16
    //#define SZ_ERROR_NO_ARCHIVE 17
        //printf("error code:%d\n", result);
        //Decompression fail!
        return FALSE;
    }

    if ( destLen != OriginalFileLength )
    {
        //Decompression fail!
        return FALSE;
    }

    if ( srcLen != srclen )
    {
        //Decompression fail!
        return FALSE;
    }
    //Decompression OK!
    return TRUE;
}
#endif //#if (ENABLE_BOOTING_FROM_EXT_EMMC_WITH_CPU == 0)

#ifdef __AEONR2__
#if (ENABLE_MSTAR_MARIA10 || ENABLE_MSTAR_MACAW12 || ENABLE_MSTAR_EDEN || ENABLE_MSTAR_EULER || ENABLE_MSTAR_NASA)
#if(ENABLE_MSTAR_EULER)
#if defined(CONFIG_MSTAR_EULER_MMAP_128MB)
#define _DRAM_RESET_VECTOR_BASE_ADDR  0x400000
#else
#define _DRAM_RESET_VECTOR_BASE_ADDR  0x200000
#endif
#else
#define _DRAM_RESET_VECTOR_BASE_ADDR  0x200000
#endif
void __loader_2nd Boot2DRAM(void);
void __loader_2nd Boot2DRAM(void)
{
    U32 u32Addr = _DRAM_RESET_VECTOR_BASE_ADDR;

    //set up reset vector base

    RIU[0x1002B4] = (U16)(u32Addr >> 16);
    RIU[0x002E54] = (U16)(0x829f);  // set wtd_mcu_rst passwd
    RIU[0x002E52] &= (~0x0100); // non-fire wtd_mcu_rst
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    RIU[0x100280] |= (0x002F); // set sdr_boot=1, release rstz_miu
    RIU[0x002E52] |= (0x0100); // fire wtd_mcu_rst

    //########################################
    //#
    //# Due to the fact that __loader_2nd is a specified section
    //# Have to avoid to use some api functions out of this section
    //#
    //########################################
    //MDrv_Write2Byte(0x1002B4, (U16)(u32Addr >> 16));
    //MDrv_Write2Byte(0x002E54, 0x829f);  // set wtd_mcu_rst passwd
    //MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)&(~BIT8));  // non-fire wtd_mcu_rst
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    //MDrv_Write2Byte(0x100280, MDrv_Read2Byte(0x100280)|(0x002F));  // set sdr_boot=1, release rstz_miu
    //MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)|(BIT8));  // fire wtd_mcu_rst
}
#endif

void __loader_2nd ReBootAtDRAM(U32 u32MemAddr);
void __loader_2nd ReBootAtDRAM(U32 u32MemAddr)
{
    //U32 u32Addr = _DRAM_RESET_VECTOR_BASE_ADDR;

    //set up reset vector base

    RIU[0x1002B4] = (U16)(u32MemAddr >> 16);
    RIU[0x002E54] = (U16)(0x829f);  // set wtd_mcu_rst passwd
    RIU[0x002E52] &= (~0x0100); // non-fire wtd_mcu_rst
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    RIU[0x100280] |= (0x002F); // set sdr_boot=1, release rstz_miu
    RIU[0x002E52] |= (0x0100); // fire wtd_mcu_rst

    //########################################
    //#
    //# Due to the fact that __loader_2nd is a specified section
    //# Have to avoid to use some api functions out of this section
    //#
    //########################################
    //MDrv_Write2Byte(0x1002B4, (U16)(u32Addr >> 16));
    //MDrv_Write2Byte(0x002E54, 0x829f);  // set wtd_mcu_rst passwd
    //MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)&(~BIT8));  // non-fire wtd_mcu_rst
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    //MDrv_Write2Byte(0x100280, MDrv_Read2Byte(0x100280)|(0x002F));  // set sdr_boot=1, release rstz_miu
    //MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)|(BIT8));  // fire wtd_mcu_rst
}

#endif // __AEONR2__

//===============================================================================

#if defined(__mips__) || defined(__arm__) || defined(__arm64__)
void __loader_2nd uart_putc(char ch);
void __loader_2nd uart_putc(char ch)
#if (!ENABLE_SECURE_BOOT)
{
#if defined(__arm__) || defined(__arm64__)
    *(volatile U32*)(0x1f201300) = ch;
#else
    *(volatile U32*)(0xbf201300) = ch;
#endif
}
#else
{
  char tmp;
  tmp = ch;
}
#endif

void __loader_2nd DoMSDecompression(void)
{
#if (ENABLE_BOOTING_FROM_EXT_EMMC_WITH_CPU == 0 && ENABLE_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 0)
    U8 IsCompressMagicNumber = 0;
    U32 CompressedFileLength = 0;
    U32 OriginalFileLength = 0;
    U32 nOutputLength=0;

#if (USE_BDMA_FOR_CRC_CHECK!=1)
    U32 u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
    U32 u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 0xC));    //This address should be 4' alignment
    U32 i = 0;
    U32 u32MagicNoOfBin = *((U32 *)(AP_IN_FLASH_ADDR + 0x1C));    //This address should be 4' alignment
    BOOL bIsUBoot = FALSE;

    //Check whether the following binary is U-Boot or non-OS AP.
    if (u32MagicNoOfBin == UBOOT_IDENTIFIER)
    {
        bIsUBoot = TRUE;
    }
    else
    {
        bIsUBoot = FALSE;
    }

    if (bIsUBoot == TRUE) //The following binary is U-Boot.
    {
        U32 u32RAM_START, u32RAM_END;

        //Compressed Format
        u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
        u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));

        CompressedFileLength = (u32ROM_END - u32ROM_START);
        OriginalFileLength = (u32RAM_END - u32RAM_START);
        if (CompressedFileLength != OriginalFileLength) //It implys that U-Boot is compressed.
        {
#if (defined(ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51) && (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51==1) && defined(__mips__) )
                    u32ROM_START-=0x10000;
                    u32ROM_END-=0x10000;
#endif
            //Copy compressed UBoot from SPI flash to RAM
#if defined(CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT)
#else
            for(i=0;i<((CompressedFileLength + 7) & ~7UL);i+=4)
            {
                #if (ENABLE_BOOTING_FROM_OTP_WITH_PM51==1)
                *((U32 *)(DECOMPRESS_BUF + i)) = *((U32 *)(u32RAM_START + i));
                #else
                *((U32 *)(DECOMPRESS_BUF + i)) = *((U32 *)(u32ROM_START + i));
                #endif
            }
#endif
            // Start to decompress
            MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);
#if defined(CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT)
			MsDecompress((U8 *)AP_IN_FLASH_ADDR_CACHE+0x400, (U8 *)(u32RAM_START & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength, OriginalFileLength, &nOutputLength);
#else
            MsDecompress((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)(u32RAM_START & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength, OriginalFileLength, &nOutputLength);
#endif
            if ( nOutputLength != OriginalFileLength )
            {
                //Decompression fail! Jump to boot loader to recover FW
            }
        }
        else //It implys that U-Boot is not compressed.
        {
#if defined(__arm__) && (USE_BDMA_MOVE_CODE == 0)
            // Uncompressed format
            asm volatile (
            // Load ROM_START, RAM_START, RAM_END, ROM_END from 0x00020000, jc_db: need to remove magic number
            #if (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51)
                "ldr     r0, =0x14030000\n"
            #else
                "ldr     r0, =0x14020000\n"
            #endif
                "ldr     r1, [r0,#0]\n"
                "ldr     r2, [r0,#4]\n"
                "ldr     r3, [r0,#8]\n"
                "ldr     r4, [r0,#12]\n"
          "1:\n"
                "LDR     r5, [r1], #4\n"
                "STR     r5, [r2], #4\n"
                "CMP     r1, r4\n"
                "BNE     1b\n"
                :::"r0", "r1", "r2", "r3", "r4", "r5","memory"
            );
            // Uncompressed format
#elif defined(__arm64__) && (USE_BDMA_MOVE_CODE == 0)
            // Uncompressed format
            asm volatile (
            // Load ROM_START, RAM_START, RAM_END, ROM_END from 0x00020000, jc_db: need to remove magic number
            #if (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51)
                "ldr     x0, =0x14030000\n"
            #else
                "ldr     x0, =0x14020000\n"
            #endif
                "ldr     x1, [r0,#0]\n"
                "ldr     x2, [r0,#4]\n"
                "ldr     x3, [r0,#8]\n"
                "ldr     x4, [r0,#12]\n"
          "1:\n"
                "ldr     w5, [x1], #4\n"
                "str     w5, [x2], #4\n"
                "cmp     x1, x4\n"
                "b.ne     1b\n"
                :::"r0", "r1", "r2", "r3", "r4", "r5","memory"
            );
            // Uncompressed format
#elif ( (ENABLE_MSTAR_KRONUS==1) || (ENABLE_MSTAR_KAISERIN==1) || (ENABLE_MSTAR_KENYA == 1)|| (ENABLE_MSTAR_KRITI == 1))
            asm volatile (
            // Load ROM_START, RAM_START, RAM_END, ROM_END from 0xBFC20000
            #ifdef CONFIG_MSTAR_KAISERIN
                "li      $15, 0x94020000;"
            #else
                "li      $15, 0xbfc20000;"
            #endif
                "lw      $8, 0($15);"
                "lw      $9, 4($15);"
                "lw      $10, 8($15);"
                "lw      $11, 12($15);"

            "1:;"
                "ld      $12, 0($8);"      //#ld=lw lw to save time
                "ld      $14, 8($8);"
                "sd      $12, 0($9);"
                "sd      $14, 8($9);"
                "addu    $8, $8, 16;"
                "addu    $9, $9, 16;"
                "bltu    $9, $10, 1b;"
                "nop;"
                :::"$15", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "memory"
            );
#else
            // Use BDMA to move code from SPI to DRAM
        #if( (ENABLE_BOOTING_FROM_EXT_SPI_WITH_CPU) || (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51))
            #if (ENABLE_MSTAR_PUMABOOT)
            __BDMA_FlashCopy2MIU0(u32ROM_START&0x7fffff, u32RAM_START&(CONFIG_MIU0_BUSADDR-1), (u32ROM_END-u32ROM_START));
            #else
            __BDMA_FlashCopy2MIU0(u32ROM_START&0x3fffff, u32RAM_START&(CONFIG_MIU0_BUSADDR-1), (u32ROM_END-u32ROM_START));
            #endif
        #endif
#endif

#if 0
            {
                extern unsigned char AuthenticationTest(unsigned char *Signature, unsigned char *Public_N, unsigned char *Public_E, unsigned char *Data, unsigned int Len);
                U32 u32AP_LEN;

                u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
                u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
                u32AP_LEN = u32RAM_END - u32RAM_START;
                AuthenticationTest((U8 *)(AP_IN_FLASH_ADDR+128+260), (U8 *)(AP_IN_FLASH_ADDR+128), (U8 *)(AP_IN_FLASH_ADDR+128+256), (U8 *)u32RAM_START, u32AP_LEN);
            }
#endif
        }
    }
    else //The following binary is non-OS AP.
    {
        // Check if this bin file is compressed format, find compress format magic number
        if ( ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+3)) == 0xDE )
        && ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+2)) == 0xAD ) )
        {
            U8 nCompressFormat = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+1));

            if ( nCompressFormat == 0xBE )
                IsCompressMagicNumber = 1;
            else if ( nCompressFormat == 0xEF )
                IsCompressMagicNumber = 2;
            else
                IsCompressMagicNumber = 0;
        }
        else
        {
            IsCompressMagicNumber = 0;
        }

        if ( IsCompressMagicNumber )
        {
            U32 u32RAM_START, u32RAM_END;

            //Compressed Format
            u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
            u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));

            //Copy uncompressed part first
            for(i=0;i<((UNCOMPRESSED_LENGTH + 7) & ~7UL);i+=4)
            {
                *((U32 *)(u32RAM_START+i)) = *((U32 *)((U32)(u32ROM_START+i)));
            }

            //Copy compressed part second
            for(i=0;i<(((u32RAM_END-u32RAM_START-UNCOMPRESSED_LENGTH) + 7) & ~7UL);i+=4)
            {
                *((U32 *)(DECOMPRESS_BUF + i)) = *((U32 *)(u32ROM_START + UNCOMPRESSED_LENGTH + i));
            }

            CompressedFileLength = *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+3));
            CompressedFileLength <<= 8;
            CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+2));
            CompressedFileLength <<= 8;
            CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+1));
            CompressedFileLength <<= 8;
            CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+0));
            CompressedFileLength -= 6;

            OriginalFileLength = *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+3));
            OriginalFileLength <<= 8;
            OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+2));
            OriginalFileLength <<= 8;
            OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+1));
            OriginalFileLength <<= 8;
            OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+0));

            // Start to decompress
            if ( IsCompressMagicNumber == 1 )
            {
                MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);
                MsDecompress((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength, OriginalFileLength, &nOutputLength);

                if ( nOutputLength != OriginalFileLength )
                {
                    //Decompression fail! Jump to boot loader to recover FW
                }
            }
            else    // IsCompressMagicNumber == 2
            {
                MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);

                if ( MsDecompress7((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength+4-UNCOMPRESSED_LENGTH) != TRUE )
                {
                    //Decompression fail! Jump to boot loader to recover FW
                }
            }
        }
        else
        {
#if defined(__arm__)
            // Uncompressed format
            asm volatile (
            // Load ROM_START, RAM_START, RAM_END, ROM_END from 0x00020000, jc_db: need to remove magic number
            #if (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51)
                "ldr     r0, =0x14020000+0x10000\n"
            #else
                "ldr     r0, =0x14020000\n"
            #endif
                "ldr     r1, [r0,#0]\n"
                "ldr     r2, [r0,#4]\n"
                "ldr     r3, [r0,#8]\n"
                "ldr     r4, [r0,#12]\n"
          "1:\n"
                "LDR     r5, [r1], #4\n"
                "STR     r5, [r2], #4\n"
                "CMP     r1, r4\n"
                "BNE     1b\n"
                :::"r0", "r1", "r2", "r3", "r4", "r5","memory"
            );
#elif defined(__arm64__)
            // Uncompressed format
            asm volatile (
            // Load ROM_START, RAM_START, RAM_END, ROM_END from 0x00020000, jc_db: need to remove magic number
            #if (ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51)
                "ldr     x0, =0x14020000+0x10000\n"
            #else
                "ldr     x0, =0x14020000\n"
            #endif
                "ldr     x1, [x0,#0]\n"
                "ldr     x2, [x0,#4]\n"
                "ldr     x3, [x0,#8]\n"
                "ldr     x4, [x0,#12]\n"
          "1:\n"
                "ldr     w5, [x1], #4\n"
                "str     w5, [x2], #4\n"
                "cmp     x1, x4\n"
                "b.ne    1b\n"
                :::"r0", "r1", "r2", "r3", "r4", "r5","memory"
            );
#else
            // Uncompressed format
            asm volatile (
            // Load ROM_START, RAM_START, RAM_END, ROM_END from 0xBFC20000
            #ifdef CONFIG_MSTAR_KAISERIN
                "li      $15, 0x94020000;"
            #else
                "li      $15, 0xbfc20000;"
            #endif
                "lw      $8, 0($15);"
                "lw      $9, 4($15);"
                "lw      $10, 8($15);"
                "lw      $11, 12($15);"

            "1:;"
                "ld      $12, 0($8);"      //#ld=lw lw to save time
                "ld      $14, 8($8);"
                "sd      $12, 0($9);"
                "sd      $14, 8($9);"
                "addu    $8, $8, 16;"
                "addu    $9, $9, 16;"
                "bltu    $9, $10, 1b;"
                "nop;"
                :::"$15", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "memory"
            );
#endif
        }
    }
#else //(USE_BDMA_FOR_CRC_CHECK!=1)
    U32 u32BOOT_LOADER_LENGTH = BOOT_LOADER_LENGTH;
    U32 u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH + 0));    //This address should be 4' alignment
    U32 u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH + 12));    //This address should be 4' alignment
    U32 i = 0;
    U32 u32CRC32_HW = 0, u32CRC32_SW = 0;
    U32 u32RAM_START, u32RAM_END;
    BOOL bIsBootToBL = FALSE; // Not AP

    {
        //set u32BOOT_LOADER_LENGTH from flash
        u32BOOT_LOADER_LENGTH = *((U32 *)(AP_IN_FLASH_ADDR + 0x18)) - 0x20000; //minus 64k for sboot and 64k for pm code
        u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH + 0));    //This address should be 4' alignment
        u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH + 12));    //This address should be 4' alignment
    }
    //Compressed Format
    if((u32ROM_START>=AP_IN_FLASH_ADDR)
        && (u32ROM_START<(AP_IN_FLASH_ADDR+0x800000))
        && (u32ROM_END>=AP_IN_FLASH_ADDR)
        && (u32ROM_END<(AP_IN_FLASH_ADDR+0x800000))) //8MB flash
    {
        // Main AP
        u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH + 4));    //This address should be 4' alignment
        u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH + 8));

        // Check magic end/start
        {
            U32 u32MAGIC_END_ADDR, u32MAGIC_END, u32MAGIC_START;
            u32MAGIC_END_ADDR = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+3));
            u32MAGIC_END_ADDR <<= 8;
            u32MAGIC_END_ADDR |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+2));
            u32MAGIC_END_ADDR <<= 8;
            u32MAGIC_END_ADDR |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+1));
            u32MAGIC_END_ADDR <<= 8;
            u32MAGIC_END_ADDR |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+0));

            u32MAGIC_END = *((U8 *)(u32MAGIC_END_ADDR+3));
            u32MAGIC_END <<= 8;
            u32MAGIC_END |= *((U8 *)(u32MAGIC_END_ADDR+2));
            u32MAGIC_END <<= 8;
            u32MAGIC_END |= *((U8 *)(u32MAGIC_END_ADDR+1));
            u32MAGIC_END <<= 8;
            u32MAGIC_END |= *((U8 *)(u32MAGIC_END_ADDR+0));
            if(u32MAGIC_END != 0x55AAABCD)
            {
                goto LOAD_LOADER_AP;
            }
            u32MAGIC_START = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+3));
            u32MAGIC_START <<= 8;
            u32MAGIC_START |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+2));
            u32MAGIC_START <<= 8;
            u32MAGIC_START |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+1));
            u32MAGIC_START <<= 8;
            u32MAGIC_START |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+0));
            if(u32MAGIC_START != 0x55AA5678)
            {
                goto LOAD_LOADER_AP;
            }
        }
    }
    else
    {
        // Loader AP
LOAD_LOADER_AP:
        bIsBootToBL = TRUE;
        u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
        u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
        u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
        u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 12));    //This address should be 4' alignment
    }
    u32CRC32_SW = *((U8 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH +CRC32_POS+3));
    u32CRC32_SW <<= 8;
    u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH +CRC32_POS+2));
    u32CRC32_SW <<= 8;
    u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH +CRC32_POS+1));
    u32CRC32_SW <<= 8;
    u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR + u32BOOT_LOADER_LENGTH +CRC32_POS+0));

LOAD_CODE_POINT:

    // Check if this bin file is compressed format, find compress format magic number
    if ( ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+3)) == 0xDE )
    && ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+2)) == 0xAD ) )
    {
        U8 nCompressFormat = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+1));

        if ( nCompressFormat == 0xBE )
            IsCompressMagicNumber = 1;
        else if ( nCompressFormat == 0xEF )
            IsCompressMagicNumber = 2;
        else
            IsCompressMagicNumber = 0;
    }
    else
    {
        IsCompressMagicNumber = 0;
    }

    if ( IsCompressMagicNumber )
    {
        CompressedFileLength = *((U8 *)(u32ROM_START+COMPRESSED_LENGTH_POS+3));
        CompressedFileLength <<= 8;
        CompressedFileLength |= *((U8 *)(u32ROM_START+COMPRESSED_LENGTH_POS+2));
        CompressedFileLength <<= 8;
        CompressedFileLength |= *((U8 *)(u32ROM_START+COMPRESSED_LENGTH_POS+1));
        CompressedFileLength <<= 8;
        CompressedFileLength |= *((U8 *)(u32ROM_START+COMPRESSED_LENGTH_POS+0));
        CompressedFileLength -= 6; /*6: 2 for crc16 and 4 for length*/

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //Calculate CRC32 from flash
        while (RIU8[(LOCAL_BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(LOCAL_BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START&0x3fffff));
        RIU[(LOCAL_BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START&0x3fffff)) >> 16);
        RIU[(LOCAL_BDMA_REG_BASE + 0x0C )] = 0;
        RIU[(LOCAL_BDMA_REG_BASE + 0x0E )] = 0;
        RIU[(LOCAL_BDMA_REG_BASE + 0x10 )] = (U16)((U32)(u32ROM_END-u32ROM_START));
        RIU[(LOCAL_BDMA_REG_BASE + 0x12 )] = (U16)((U32)((u32ROM_END-u32ROM_START) >> 16));
        //polynomial
        RIU[(LOCAL_BDMA_REG_BASE + 0x14 )] = (U16)(0x1DB7);
        RIU[(LOCAL_BDMA_REG_BASE + 0x16 )] = (U16)(0x04C1);
        //seed
        RIU[(LOCAL_BDMA_REG_BASE + 0x18 )] = 0;
        RIU[(LOCAL_BDMA_REG_BASE + 0x1a )] = 0;

        RIU8[(LOCAL_BDMA_REG_BASE + 0x06)*2] = 0x0;   //increasing
        RIU[(LOCAL_BDMA_REG_BASE+0x04)] = 0x0335;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;

        RIU8[ (LOCAL_BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(LOCAL_BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }

        //Get CRC32 result
        u32CRC32_HW = RIU[(LOCAL_BDMA_REG_BASE + 0x18 )] ;      //low word
        u32CRC32_HW |= (RIU[(LOCAL_BDMA_REG_BASE + 0x1a )]  <<  16);        //high word

        if ( u32CRC32_HW != u32CRC32_SW )
        {
            //AP in flash is bad, load boot loader instead
            u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
            u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
            u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
            u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 12));    //This address should be 4' alignment

            u32CRC32_SW = *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+3));
            u32CRC32_SW <<= 8;
            u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+2));
            u32CRC32_SW <<= 8;
            u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+1));
            u32CRC32_SW <<= 8;
            u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+0));
            goto LOAD_CODE_POINT;
        }
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if (ENABLE_SECURE_BOOT) // secure boot test
        if ( (bIsBootToBL == FALSE) && (IsCompressMagicNumber == 1) )
        {
            uart_putc('\r');
            uart_putc('\n');
            uart_putc('1');
            uart_putc('\r');
            uart_putc('\n');
            //Copy uncompressed part first
            for(i=0;i<(((u32ROM_END-u32ROM_START) + 7) & ~7UL);i+=4)
            {
                *((U32 *)(u32RAM_START+i)) = *((U32 *)((U32)(u32ROM_START+i)));
            }
            uart_putc('\r');
            uart_putc('\n');
            uart_putc('2');
            uart_putc('\r');
            uart_putc('\n');
         {
                extern unsigned char AuthenticationTest(unsigned char *Signature, unsigned char *Public_N, unsigned char *Public_E, unsigned char *Data, unsigned int Len);
                U32 u32AP_LEN;
                U32 secure_header = AP_IN_FLASH_ADDR+0x40000;
                u32AP_LEN = u32ROM_END - u32ROM_START;
                //while(1){}
                if(0 == AuthenticationTest((U8 *)(secure_header+128+260), (U8 *)(secure_header+128), (U8 *)(secure_header+128+256), (U8 *)u32RAM_START, u32AP_LEN))
                {
                    // AuthenticationTest failed
                    //AP in flash is bad, load boot loader instead
                    u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
                    u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
                    u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
                    u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 12));    //This address should be 4' alignment

                    u32CRC32_SW = *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+3));
                    u32CRC32_SW <<= 8;
                    u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+2));
                    u32CRC32_SW <<= 8;
                    u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+1));
                    u32CRC32_SW <<= 8;
                    u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+0));
                    bIsBootToBL = TRUE;
                    goto LOAD_CODE_POINT;
                }
            }
            uart_putc('\r');
            uart_putc('\n');
            uart_putc('3');
            uart_putc('\r');
            uart_putc('\n');
        }
#endif
        //Copy uncompressed part first
        for(i=0;i<((UNCOMPRESSED_LENGTH + 7) & ~7UL);i+=4)
        {
            *((U32 *)(u32RAM_START+i)) = *((U32 *)((U32)(u32ROM_START+i)));
        }

        //Copy compressed part second
        for(i=0;i<(((u32ROM_END-u32ROM_START-UNCOMPRESSED_LENGTH) + 7) & ~7UL);i+=4)
        {
            *((U32 *)(DECOMPRESS_BUF + i)) = *((U32 *)(u32ROM_START + UNCOMPRESSED_LENGTH + i));
        }

//        CompressedFileLength = *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+3));
//        CompressedFileLength <<= 8;
//        CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+2));
//        CompressedFileLength <<= 8;
//        CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+1));
//        CompressedFileLength <<= 8;
//        CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+0));
//        CompressedFileLength -= 6;

        OriginalFileLength = *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+3));
        OriginalFileLength <<= 8;
        OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+2));
        OriginalFileLength <<= 8;
        OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+1));
        OriginalFileLength <<= 8;
        OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+0));

        // Start to decompress
        if ( IsCompressMagicNumber == 1 )
        {
            MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);
            MsDecompress((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength, OriginalFileLength, &nOutputLength);

            if ( nOutputLength != OriginalFileLength )
            {
                //Decompression fail! Jump to boot loader to recover FW
                u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
                u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
                u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
                u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 12));    //This address should be 4' alignment

                u32CRC32_SW = *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+3));
                u32CRC32_SW <<= 8;
                u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+2));
                u32CRC32_SW <<= 8;
                u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+1));
                u32CRC32_SW <<= 8;
                u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+0));
                goto LOAD_CODE_POINT;
            }
        }
        else    // IsCompressMagicNumber == 2
        {
            MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);

            if ( MsDecompress7((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength+4-UNCOMPRESSED_LENGTH) != TRUE )
            {
                //Decompression fail! Jump to boot loader to recover FW
                u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
                u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
                u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
                u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 12));    //This address should be 4' alignment

                u32CRC32_SW = *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+3));
                u32CRC32_SW <<= 8;
                u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+2));
                u32CRC32_SW <<= 8;
                u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+1));
                u32CRC32_SW <<= 8;
                u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+0));
                goto LOAD_CODE_POINT;
            }
        }
    }
    else
    {
        // Uncompressed format
#if 1 /*enable HW crc32 check*/
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //Calculate CRC32 from flash
        while (RIU8[(LOCAL_BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(LOCAL_BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START&0x3fffff));
        RIU[(LOCAL_BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START&0x3fffff)) >> 16);
        RIU[(LOCAL_BDMA_REG_BASE + 0x0C )] = 0;
        RIU[(LOCAL_BDMA_REG_BASE + 0x0E )] = 0;
        RIU[(LOCAL_BDMA_REG_BASE + 0x10 )] = (U16)((U32)(u32ROM_END-u32ROM_START)) ;
        RIU[(LOCAL_BDMA_REG_BASE + 0x12 )] = (U16)(((U32)(u32ROM_END-u32ROM_START))>>16);
        //polynomial
        RIU[(LOCAL_BDMA_REG_BASE + 0x14 )] = (U16)(0x1DB7);
        RIU[(LOCAL_BDMA_REG_BASE + 0x16 )] = (U16)(0x04C1);
        //seed
        RIU[(LOCAL_BDMA_REG_BASE + 0x18 )] = 0;
        RIU[(LOCAL_BDMA_REG_BASE + 0x1a )] = 0;

        RIU8[(LOCAL_BDMA_REG_BASE + 0x06)*2] = 0x00;   //increasing
        RIU[(LOCAL_BDMA_REG_BASE+0x04)] = 0x0335;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;

        RIU8[ (LOCAL_BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(LOCAL_BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }

        //Get CRC32 result
        u32CRC32_HW = RIU[(LOCAL_BDMA_REG_BASE + 0x18 )] ;      //low word
        u32CRC32_HW |= (RIU[(LOCAL_BDMA_REG_BASE + 0x1a )]  <<  16);        //high word

        //u32CRC32_SW = *((U8 *)(u32ROM_START+CRC32_POS+3));
        //u32CRC32_SW <<= 8;
        //u32CRC32_SW |= *((U8 *)(u32ROM_START+CRC32_POS+2));
        //u32CRC32_SW <<= 8;
        //u32CRC32_SW |= *((U8 *)(u32ROM_START+CRC32_POS+1));
        //u32CRC32_SW <<= 8;
        //u32CRC32_SW |= *((U8 *)(u32ROM_START+CRC32_POS+0));

        if ( u32CRC32_HW != u32CRC32_SW )
        {
            //AP in flash is bad, load boot loader instead
            u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
            u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
            u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));
            u32ROM_END = *((U32 *)(AP_IN_FLASH_ADDR + 12));    //This address should be 4' alignment

            u32CRC32_SW = *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+3));
            u32CRC32_SW <<= 8;
            u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+2));
            u32CRC32_SW <<= 8;
            u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+1));
            u32CRC32_SW <<= 8;
            u32CRC32_SW |= *((U8 *)(AP_IN_FLASH_ADDR+CRC32_POS+0));
            goto LOAD_CODE_POINT;
        }
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        asm volatile (
        // Load ROM_START, RAM_START, RAM_END, ROM_END from 0xBFC20000
        #ifdef CONFIG_MSTAR_KAISERIN
            "li      $15, 0x94050000;" /*0xBFC20000 + u32BOOT_LOADER_LENGTH*/
        #else
            "li      $15, 0xbfc50000;" /*0xBFC20000 + u32BOOT_LOADER_LENGTH*/
        #endif
#else
        asm volatile (
        // Load ROM_START, RAM_START, RAM_END, ROM_END from 0xBFC20000
        #ifdef CONFIG_MSTAR_KAISERIN
            "li      $15, 0x94020000;"
        #else
            "li      $15, 0xBFC20000;"
        #endif
#endif
            "lw      $8, 0($15);"
            "lw      $9, 4($15);"
            "lw      $10, 8($15);"
            "lw      $11, 12($15);"

        "1:;"
            "ld      $12, 0($8);"      //#ld=lw lw to save time
            "ld      $14, 8($8);"
            "sd      $12, 0($9);"
            "sd      $14, 8($9);"
            "addu    $8, $8, 16;"
            "addu    $9, $9, 16;"
            "bltu    $9, $10, 1b;"
            "nop;"
            :::"$15", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "memory"
        );
    }
#endif //(USE_BDMA_FOR_CRC_CHECK!=1)

#else   // (ENABLE_BOOTING_FROM_EXT_EMMC_WITH_CPU == 0 && ENABLE_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 0)
    // Load Code from EMMC
 #include "mmc/inc/common/eMMC.h"
 #include "aesdma/src/drvAESDMA.h"
 #include "part_emmc.h"
 #define CHUNK_HEADER_SIZE 1024
 #define MMC_SECTOR_SIZE 512
 #define SIG_SIZE 256
 #define SECURITY_INFO_SIZE 16
 emmc_partition_t    mpart;

    U32 u32TempLoadAddr =  0x40000000 + ((CONFIG_DRAM_SIZE_MB_RELOCATE + 1) * 1024 * 1024);

    U32 u32_i;
    U32 u32TmpBufferAddr = u32TempLoadAddr;
    U32 u32_Err = 0;
    U32 u32_AutResult =0;
    U32 u32_RomAuthen = 0;
    U32 u32UbootLen = 0;
    U32 u32UbootRomStart = 0;
    U32 u32UbootRamStart = 0;
    U32 u32UbootRamEnd = 0;
    U32 u32PlaintextStart = 0;
    U32 u32PLaintextLen = 0;
    U32 u32SignatureStart = 0;

    uart_putc('\n');
    uart_putc('\r');
    uart_putc('E');
    uart_putc('M');
    uart_putc('M');
    uart_putc('C');

    //read rom_authen info from bank:0x0038E0[0]
    u32_RomAuthen = (*(volatile U32*)(ROM_AUTHEN_REG))&BIT0;

#if 0
    u32_Err = eMMC_Init();
    if(u32_Err)
        goto HANDLE_FAIL;
#endif

    for(u32_i=0;u32_i<= EMMC_RESERVED_FOR_MAP_V2;u32_i++)
    {
        u32_Err = eMMC_ReadData_MIU((U8*)&mpart,MMC_SECTOR_SIZE, u32_i);
         if(u32_Err)
            goto HANDLE_FAIL;

         if((mpart.name[0]=='M')&&(mpart.name[1]=='B')&&(mpart.name[2]=='O')&&(mpart.name[3]=='O')&&(mpart.name[4]=='T'))
            break;
    }
    //Read chunk Header
    u32_Err = eMMC_ReadData_MIU((U8*) u32TmpBufferAddr,CHUNK_HEADER_SIZE, mpart.start_block);

    if(u32_Err)
        goto HANDLE_FAIL;

    //authenticate chunk header
    if(u32_RomAuthen)
    {
        uart_putc('\n');
        uart_putc('\r');
        uart_putc('C');
        uart_putc('H');
        uart_putc('U');
        uart_putc('N');
        uart_putc('K');
        uart_putc('_');
        uart_putc('A');
        uart_putc('U');
        uart_putc('T');
        u32PlaintextStart = u32TmpBufferAddr;//chunk header ram start
        u32PLaintextLen = CHUNK_HEADER_SIZE - SIG_SIZE -SECURITY_INFO_SIZE;//chunk header size
        u32SignatureStart = u32PlaintextStart + u32PLaintextLen + SECURITY_INFO_SIZE;//chunk header sig start
        u32_AutResult = MDrv_AESDMA_SecureMain(u32PlaintextStart,u32PLaintextLen,u32SignatureStart,0);
        if(!u32_AutResult)
            goto HANDLE_FAIL;
        uart_putc('_');
        uart_putc('O');
        uart_putc('K');
    }

    u32UbootRomStart = *((U32 *)(u32TmpBufferAddr + 0));
    u32UbootRamStart = *((U32 *)(u32TmpBufferAddr + 4));
    u32UbootRamEnd   = *((U32 *)(u32TmpBufferAddr + 8));
    u32UbootLen = u32UbootRamEnd - u32UbootRamStart;
    u32UbootRomStart = u32UbootRomStart / 512;

    //Load uboot to DRAM
    u32UbootRomStart = u32UbootRomStart + mpart.start_block;
    u32UbootLen = ((u32UbootLen >> 9) + 2) << 9;//truncation + signature

    //for debug
    #if 0
    *(volatile U32*)(0x1f206700) = u32UbootRomStart>>16;
    *(volatile U32*)(0x1f206704) = u32UbootRomStart;
    *(volatile U32*)(0x1f206708) = u32UbootLen>>16;
    *(volatile U32*)(0x1f20670C) = u32UbootLen;
    *(volatile U32*)(0x1f206710) = u32UbootRamStart>>16;
    *(volatile U32*)(0x1f206714) = u32UbootRamStart;
    *(volatile U32*)(0x1f206718) = u32UbootRamEnd>>16;
    *(volatile U32*)(0x1f20671C) = u32UbootRamEnd;
    #endif

    u32_Err = eMMC_ReadData_MIU((U8 *)CONFIG_UBOOT_LOADADDR, u32UbootLen, u32UbootRomStart);
    if(u32_Err)
        goto HANDLE_FAIL;

    //authenticate u-boot
    if(u32_RomAuthen)
    {
        uart_putc('\n');
        uart_putc('\r');
        uart_putc('U');
        uart_putc('B');
        uart_putc('O');
        uart_putc('O');
        uart_putc('T');
        uart_putc('_');
        uart_putc('A');
        uart_putc('U');
        uart_putc('T');
        u32PlaintextStart = CONFIG_UBOOT_LOADADDR;//uboot ram start
        u32PLaintextLen = u32UbootRamEnd - u32UbootRamStart;//uboot size
        u32SignatureStart = u32PlaintextStart + u32PLaintextLen + SECURITY_INFO_SIZE;//uboot sig start
        u32_AutResult = MDrv_AESDMA_SecureMain(u32PlaintextStart, u32PLaintextLen, u32SignatureStart, 0);
        if(!u32_AutResult)
            goto HANDLE_FAIL;
        uart_putc('_');
        uart_putc('O');
        uart_putc('K');
    }

    #if defined(CONFIG_MSTAR_CLEANBOOT)
   #define CONFIG_CLEANBOOT_LOADADDR u32TempLoadAddr + 0x500000

    U32 u32CleanBootPlaintextLen = 0;
    U32 u32CleanBootRomStart = *((U32 *)(u32TmpBufferAddr + 0x78));
    U32 u32CleanBootLen = *((U32 *)(u32TmpBufferAddr + 0x7C));
    u32CleanBootPlaintextLen = u32CleanBootLen;

    //Load cleanboot to DRAM
    u32CleanBootRomStart = u32CleanBootRomStart / 512;
    u32CleanBootRomStart = u32CleanBootRomStart + mpart.start_block;
    u32CleanBootLen = ((u32CleanBootLen >> 9) + 2) << 9;//truncation + signature

    u32_Err = eMMC_ReadData_MIU((U8 *)CONFIG_CLEANBOOT_LOADADDR, u32CleanBootLen, u32CleanBootRomStart);
    if(u32_Err)
        goto HANDLE_FAIL;

    //authenticate cleanboot
    if(u32_RomAuthen)
    {
        uart_putc('\n');
        uart_putc('\r');
        uart_putc('C');
        uart_putc('L');
        uart_putc('E');
        uart_putc('A');
        uart_putc('B');
        uart_putc('O');
        uart_putc('O');
        uart_putc('T');
        uart_putc('_');
        uart_putc('A');
        uart_putc('U');
        uart_putc('T');
        u32PlaintextStart = CONFIG_CLEANBOOT_LOADADDR;//CleanBoot ram start
        u32PLaintextLen = u32CleanBootPlaintextLen;//CleanBoot size
        u32SignatureStart = u32PlaintextStart + u32PLaintextLen + SECURITY_INFO_SIZE;//uboot sig start
        u32_AutResult = MDrv_AESDMA_SecureMain(u32PlaintextStart, u32PLaintextLen, u32SignatureStart, 0);
        if(!u32_AutResult)
            goto HANDLE_FAIL;
        uart_putc('_');
        uart_putc('O');
        uart_putc('K');
    }
    #endif
    uart_putc('\n');
    uart_putc('\r');
    uart_putc('d');
    uart_putc('o');
    uart_putc('n');
    uart_putc('e');
    uart_putc('\n');
    uart_putc('\r');

    return;

HANDLE_FAIL:
    uart_putc('_');
    uart_putc('f');
    uart_putc('a');
    uart_putc('i');
    uart_putc('l');
    uart_putc('\n');
    uart_putc('\r');
    while(1);

#endif // (ENABLE_BOOTING_FROM_EXT_EMMC_WITH_CPU == 0)
   // init_version();
}

#else
void __loader_2nd DoMSDecompression(void)
{

#define CHUNK_HEADER_ADDR       0x20000
#define CHUNK_HEADER_LEN        0x80

    U8 IsCompressMagicNumber = 0;
    U32 CompressedFileLength = 0;
    U32 OriginalFileLength = 0;
    U32 nOutputLength;
    U32 u32FlashAddr;
    U32 u32ROM_START = 0;    //This address should be 4' alignment
    U32 u32RAM_START = 0, u32RAM_END = 0;
    U32 u32BOOT_LOADER_LENGTH = 0;
    U32 u32ROM_END = 0;
    U32 u32CRC32_HW = 0, u32CRC32_SW = 0;
    U32 u32REV_FLASH_SIZE=0, u32BINARY_ID=0;

    // Check if this bin file is compressed format, find compress format magic number
    u32FlashAddr = RIU[0x1002AC];
    u32FlashAddr <<= 16;

    u32BOOT_LOADER_LENGTH = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 0x18));
    u32BINARY_ID = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 0x1C));
    u32ROM_START = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH)) + u32FlashAddr;
    u32ROM_END = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + 12)) + u32FlashAddr;

    if(u32BINARY_ID != 0) // should be u-boot
    {
        u32REV_FLASH_SIZE = 0x400000;
    }
    else
    {
        u32REV_FLASH_SIZE = *((U8 *)((u32ROM_START+0x2000+8)+0)); //.img_info
        u32REV_FLASH_SIZE <<= 8;
        u32REV_FLASH_SIZE |= *((U8 *)((u32ROM_START+0x2000+8)+1));
        u32REV_FLASH_SIZE <<= 8;
        u32REV_FLASH_SIZE |= *((U8 *)((u32ROM_START+0x2000+8)+2));
        u32REV_FLASH_SIZE <<= 8;
        u32REV_FLASH_SIZE |= *((U8 *)((u32ROM_START+0x2000+8)+3));
    }

    // Check magic end/start
    if((u32ROM_START>=AP_IN_FLASH_ADDR+u32FlashAddr)
        && (u32ROM_START<(AP_IN_FLASH_ADDR+u32REV_FLASH_SIZE+u32FlashAddr))
        && (u32ROM_END>=AP_IN_FLASH_ADDR+u32FlashAddr)
        && (u32ROM_END<(AP_IN_FLASH_ADDR+u32REV_FLASH_SIZE+u32FlashAddr))) //u32REV_FLASH_SIZE: flash reserved size
    {
        // Main AP
        u32RAM_START = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + 4));    //This address should be 4' alignment
        u32RAM_END = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + 8));

        // Check magic end/start
        {
            U32 u32MAGIC_END_ADDR, u32MAGIC_END, u32MAGIC_START;
            u32MAGIC_END_ADDR = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+3));
            u32MAGIC_END_ADDR <<= 8;
            u32MAGIC_END_ADDR |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+2));
            u32MAGIC_END_ADDR <<= 8;
            u32MAGIC_END_ADDR |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+1));
            u32MAGIC_END_ADDR <<= 8;
            u32MAGIC_END_ADDR |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS+4)+0));

            u32MAGIC_END_ADDR += u32FlashAddr;

            u32MAGIC_END = *((U8 *)(u32MAGIC_END_ADDR+3));
            u32MAGIC_END <<= 8;
            u32MAGIC_END |= *((U8 *)(u32MAGIC_END_ADDR+2));
            u32MAGIC_END <<= 8;
            u32MAGIC_END |= *((U8 *)(u32MAGIC_END_ADDR+1));
            u32MAGIC_END <<= 8;
            u32MAGIC_END |= *((U8 *)(u32MAGIC_END_ADDR+0));
            if(u32MAGIC_END != 0x55AAABCD)
            {
                goto LOAD_LOADER_AP;
            }
            u32MAGIC_START = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+3));
            u32MAGIC_START <<= 8;
            u32MAGIC_START |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+2));
            u32MAGIC_START <<= 8;
            u32MAGIC_START |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+1));
            u32MAGIC_START <<= 8;
            u32MAGIC_START |= *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-0x4A)+0));
            if(u32MAGIC_START != 0x55AA5678)
            {
                goto LOAD_LOADER_AP;
            }
        }
    }
    else
    {
        // Loader AP
LOAD_LOADER_AP:
        u32ROM_START = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR)) + u32FlashAddr;
        u32RAM_START = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 4));
        u32RAM_END = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 8));
        u32ROM_END = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 12)) + u32FlashAddr;
    }

    u32CRC32_SW = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + CRC32_POS+3));
    u32CRC32_SW <<= 8;
    u32CRC32_SW = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + CRC32_POS+2));
    u32CRC32_SW <<= 8;
    u32CRC32_SW = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + CRC32_POS+1));
    u32CRC32_SW <<= 8;
    u32CRC32_SW = *((U32 *)(u32FlashAddr + u32BOOT_LOADER_LENGTH + CRC32_POS+0));

LOAD_CODE_POINT:

    // Check if this bin file is compressed format, find compress format magic number
    if ( ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+3)) == 0xDE )
    && ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+2)) == 0xAD ) )
    {
        U8 nCompressFormat = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+1));

        if ( nCompressFormat == 0xBE )
        {
            IsCompressMagicNumber = 1;
        }
        else if ( nCompressFormat == 0xEF )
        {
            IsCompressMagicNumber = 2;
        }
        else
        {
            IsCompressMagicNumber = 0;
        }
    }
    else
    {
        IsCompressMagicNumber = 0;
    }

    u32ROM_START -= u32FlashAddr;
    u32ROM_END -= u32FlashAddr;

    //Compressed Format
    if ( IsCompressMagicNumber )
    {
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //Calculate CRC32 from flash
        while (RIU8[(BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START&0x3fffff));
        RIU[(BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START&0x3fffff)) >> 16);
        RIU[(BDMA_REG_BASE + 0x0C )] = 0;
        RIU[(BDMA_REG_BASE + 0x0E )] = 0;
        RIU[(BDMA_REG_BASE + 0x10 )] = (U16)((U32)(u32ROM_END-u32ROM_START));
        RIU[(BDMA_REG_BASE + 0x12 )] = (U16)((U32)((u32ROM_END-u32ROM_START) >> 16));
        //polynomial
        RIU[(BDMA_REG_BASE + 0x14 )] = (U16)(0x1DB7);
        RIU[(BDMA_REG_BASE + 0x16 )] = (U16)(0x04C1);
        //seed
        RIU[(BDMA_REG_BASE + 0x18 )] = 0;
        RIU[(BDMA_REG_BASE + 0x1a )] = 0;

        RIU8[(BDMA_REG_BASE + 0x06)*2] = 0x0;   //increasing
        #if (ENABLE_MSTAR_EULER)
        RIU[(BDMA_REG_BASE+0x04)] = 0x0345;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #else
        RIU[(BDMA_REG_BASE+0x04)] = 0x0335;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #endif

        RIU8[ (BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }

        //Get CRC32 result
        u32CRC32_HW = RIU[(BDMA_REG_BASE + 0x18 )] ;        //low word
        u32CRC32_HW |= (RIU[(BDMA_REG_BASE + 0x1a )]  <<  16);      //high word

        if ( u32CRC32_HW != u32CRC32_SW )
        {
            //AP in flash is bad, load boot loader instead
            u32ROM_START = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR)) + u32FlashAddr;
            u32RAM_START = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 4));
            u32RAM_END = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 8));
            u32ROM_END = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 12)) + u32FlashAddr;

            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+3));
            u32CRC32_SW <<= 8;
            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+2));
            u32CRC32_SW <<= 8;
            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+1));
            u32CRC32_SW <<= 8;
            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+0));
            goto LOAD_CODE_POINT;
        }

        //Copy uncompressed part first
        while (RIU8[(BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START));
        RIU[(BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START)) >> 16);
        RIU[(BDMA_REG_BASE + 0x0C )] = (U16)((U32)u32RAM_START);
        RIU[(BDMA_REG_BASE + 0x0E )] = (U16)((U32)(u32RAM_START) >> 16);
        RIU[(BDMA_REG_BASE + 0x10 )] = (U16)(((U32)(UNCOMPRESSED_LENGTH) + 0x0f ) & ~ 0x0ful);
        RIU[(BDMA_REG_BASE + 0x12 )] = (U16)(((((U32)(UNCOMPRESSED_LENGTH)) + 0x0f ) & ~ 0x0ful)>>16);

        RIU8[(BDMA_REG_BASE + 0x06)*2] = 0x00;   //increasing
        #if (ENABLE_MSTAR_EULER)
        RIU[(BDMA_REG_BASE+0x04)] = 0x4045;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #else
        RIU[(BDMA_REG_BASE+0x04)] = 0x3035;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #endif

        RIU8[ (BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }

        //Copy compressed part second
        while (RIU8[(BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START + UNCOMPRESSED_LENGTH));
        RIU[(BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START + UNCOMPRESSED_LENGTH)) >> 16);
        RIU[(BDMA_REG_BASE + 0x0C )] = (U16)((U32)(DECOMPRESS_BUF) & 0x0000FFFF);
        RIU[(BDMA_REG_BASE + 0x0E )] = (U16)((U32)(DECOMPRESS_BUF) >> 16);
        RIU[(BDMA_REG_BASE + 0x10 )] = (U16)(((U32)(u32RAM_END-u32RAM_START-UNCOMPRESSED_LENGTH) + 0x0f ) & ~ 0x0ful);
        RIU[(BDMA_REG_BASE + 0x12 )] = (U16)(((((U32)(u32RAM_END-u32RAM_START-UNCOMPRESSED_LENGTH)) + 0x0f ) & ~ 0x0ful)>>16);

        RIU8[(BDMA_REG_BASE + 0x06)*2] = 0x00;   //increasing
        #if (ENABLE_MSTAR_EULER)
        RIU[(BDMA_REG_BASE+0x04)] = 0x4045;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #else
        RIU[(BDMA_REG_BASE+0x04)] = 0x3035;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #endif

        RIU8[ (BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }

        CompressedFileLength = *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+3));
        CompressedFileLength <<= 8;
        CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+2));
        CompressedFileLength <<= 8;
        CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+1));
        CompressedFileLength <<= 8;
        CompressedFileLength |= *((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+0));
        CompressedFileLength -= 6;

        OriginalFileLength = *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+3));
        OriginalFileLength <<= 8;
        OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+2));
        OriginalFileLength <<= 8;
        OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+1));
        OriginalFileLength <<= 8;
        OriginalFileLength |= *((U8 *)(DECOMPRESS_BUF+CompressedFileLength-UNCOMPRESSED_LENGTH+0));

        // Start to decompress
        if ( IsCompressMagicNumber == 1 )
        {
            MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);
            MsDecompress((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength, OriginalFileLength, &nOutputLength);

            if ( nOutputLength != OriginalFileLength )
            {
                //Decompression fail! Jump to boot loader to recover FW
            }
        }
        else
        {
            MemoryAllocatorInit((U8 *)MEMORY_POOL_CACHEABLE, MEMORY_POOL_SIZE);

            if ( MsDecompress7((U8 *)DECOMPRESS_BUF_CACHEABLE, (U8 *)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK), CompressedFileLength+4-UNCOMPRESSED_LENGTH) != TRUE )
            {
                //Decompression fail! Jump to boot loader to recover FW
            }
            else
            { //do d-cache flush
                U32 u32DstAddr, u32Len;

                u32DstAddr = (U32)((u32RAM_START + UNCOMPRESSED_LENGTH) & NON_CACHEABLE_TO_CACHEABLE_MASK);
                u32Len = (U32)(CompressedFileLength+4-UNCOMPRESSED_LENGTH);
                mhal_dcache_flush(u32DstAddr,u32Len);
            }
        }
    }
    else
    {
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Calculate CRC32 from flash
        while (RIU8[(BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START&0x3fffff));
        RIU[(BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START&0x3fffff)) >> 16);
        RIU[(BDMA_REG_BASE + 0x0C )] = 0;
        RIU[(BDMA_REG_BASE + 0x0E )] = 0;
        RIU[(BDMA_REG_BASE + 0x10 )] = (U16)((U32)(u32ROM_END-u32ROM_START));
        RIU[(BDMA_REG_BASE + 0x12 )] = (U16)((U32)((u32ROM_END-u32ROM_START) >> 16));
        //polynomial
        RIU[(BDMA_REG_BASE + 0x14 )] = (U16)(0x1DB7);
        RIU[(BDMA_REG_BASE + 0x16 )] = (U16)(0x04C1);
        //seed
        RIU[(BDMA_REG_BASE + 0x18 )] = 0;
        RIU[(BDMA_REG_BASE + 0x1a )] = 0;

        RIU8[(BDMA_REG_BASE + 0x06)*2] = 0x0;   //increasing
        #if (ENABLE_MSTAR_EULER)
        RIU[(BDMA_REG_BASE+0x04)] = 0x0345;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #else
        RIU[(BDMA_REG_BASE+0x04)] = 0x0335;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #endif

        RIU8[ (BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }

        //Get CRC32 result
        u32CRC32_HW = RIU[(BDMA_REG_BASE + 0x18 )] ;        //low word
        u32CRC32_HW |= (RIU[(BDMA_REG_BASE + 0x1a )]  <<  16);      //high word

        if ( u32CRC32_HW != u32CRC32_SW )
        {
            //AP in flash is bad, load boot loader instead
            u32ROM_START = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR)) + u32FlashAddr;
            u32RAM_START = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 4));
            u32RAM_END = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 8));
            u32ROM_END = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + 12)) + u32FlashAddr;

            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+3));
            u32CRC32_SW <<= 8;
            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+2));
            u32CRC32_SW <<= 8;
            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+1));
            u32CRC32_SW <<= 8;
            u32CRC32_SW = *((U32 *)(u32FlashAddr + CHUNK_HEADER_ADDR + CRC32_POS+0));

            goto LOAD_CODE_POINT;
        }

        // Uncompressed format
        while (RIU8[(BDMA_REG_BASE + 0x02)*2] & 0x01);
        RIU[(BDMA_REG_BASE + 0x08 )] = (U16)((U32)(u32ROM_START));
        RIU[(BDMA_REG_BASE + 0x0A )] = (U16)(((U32)(u32ROM_START)) >> 16);
        RIU[(BDMA_REG_BASE + 0x0C )] = (U16)((U32)u32RAM_START);
        RIU[(BDMA_REG_BASE + 0x0E )] = (U16)((U32)(u32RAM_START) >> 16);
        RIU[(BDMA_REG_BASE + 0x10 )] = (U16)(((U32)(u32RAM_END - u32RAM_START) + 0x0f ) & ~ 0x0ful);
        RIU[(BDMA_REG_BASE + 0x12 )] = (U16)(((((U32)(u32RAM_END - u32RAM_START)) + 0x0f ) & ~ 0x0ful)>>16);

        RIU8[(BDMA_REG_BASE + 0x06)*2] = 0x00;   //increasing
        #if (ENABLE_MSTAR_EULER)
        RIU[(BDMA_REG_BASE+0x04)] = 0x4045;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #else
        RIU[(BDMA_REG_BASE+0x04)] = 0x3035;  //((DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) ;
        #endif

        RIU8[ (BDMA_REG_BASE*2)] = 0x01 ;
        while( 1 )
        {
            if ( (RIU8[(BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
                break;
        }
    }
   // init_version();

#ifdef __AEONR2__

  #if 1//(ENABLE_MSTAR_NASA||ENABLE_MSTAR_EDEN)
    ReBootAtDRAM(u32RAM_START);
  #elif (ENABLE_MSTAR_MARIA10 || ENABLE_MSTAR_MACAW12 || ENABLE_MSTAR_EDEN || ENABLE_MSTAR_EULER || ENABLE_MSTAR_NASA)
    Boot2DRAM();
  #else
    // Move from bootaeonsysinit.c
    // wait 51 polling this register and then reset to new vector table address.
    if(u32RAM_START==0)
    {
        __asm__ __volatile__ (
            "\tl.syncwritebuffer\n"
            "\tl.jr     %0\n"
            "\tl.syncwritebuffer\n"
            : : "r" (0x100));
    }
    else
    {
        RIU[0x1002B4] = u32RAM_START >> 16;
    }
  #endif

    while(1);
#endif

}

#endif
#endif
