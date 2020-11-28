//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#include <common.h>
#include <MsTypes.h>
#include <MsUboot.h>
#include <ShareType.h>
#include <MsDrvCache.h>

#if CONFIG_MIPS32

#define _BITMASK(loc_msb, loc_lsb) ((1U << (loc_msb)) - (1U << (loc_lsb)) + (1U << (loc_msb)))
#define BITMASK(x) _BITMASK(1?x, 0?x)

// for Run in cache

#define CONFIG_KSEG0_MASK (0x00000007)
#define KSEG0_UNCACHED (0x2)
#define KSEG0_CACHE (0x3) // Cacheable, noncoherent, write-back, write allocate
#define KSEG0_BASE  (0x80000000)
#define KSEG1_BASE  (0xA0000000)

#define MIPS_CLOCK_FREQ_XTAL 12000000

#define HAL_MIPS_CACHE_INDEX_LOAD_TAG_I      0x04 /* 1 0 */
#define HAL_MIPS_CACHE_INDEX_LOAD_TAG_D      0x05 /* 1 1 */
#define HAL_MIPS_CACHE_INDEX_STORE_TAG_I     0x08 /* 2 0 */
#define HAL_MIPS_CACHE_INDEX_STORE_TAG_D     0x09 /* 2 1 */
#define HAL_MIPS_CACHE_INDEX_STORE_DATA_I    0x0c /* 7 0 */
#define HAL_MIPS_CACHE_INDEX_STORE_DATA_D    0x0d /* 7 1 */

#define hazard_barrier() ({ asm volatile(".set push\n"\
                                         ".set mips32r2\n"\
                                         "ehb\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"\
                                         ".set pop\n"); 0; })


typedef struct {
        unsigned int waysize;   /* Bytes per way */
        unsigned short sets;    /* Number of lines per set */
        unsigned char ways;     /* Number of ways */
        unsigned char linesz;   /* Size of line in bytes */
        unsigned char waybit;   /* Bits to select in a cache set */
        unsigned char flags;    /* Flags describing cache properties */
}cache_desc;

    
void read_icache_config(cache_desc *icache_dsc)
{
    unsigned int config1;
    unsigned int lsize;
    unsigned int icache_size;

    asm volatile (       \
            ".set\tmips32\n\t"   \
            "mfc0 %0, $16, 1\n\t"\
            ".set\tmips0\n\t"    \
            : "=r" (config1));
    printf("icache config = %x\n", config1);

    if ((lsize = ((config1 >> 19) & 7)))
    {
        icache_dsc->linesz = 2 << lsize;
    }
    else
    {
        icache_dsc->linesz = lsize;
    }
    icache_dsc->sets = 64 << ((config1 >> 22) & 7);
    icache_dsc->ways = 1 + ((config1 >> 16) & 7);

    icache_size = icache_dsc->sets *
                  icache_dsc->ways *
                  icache_dsc->linesz;
    //icache_dsc->waybit = ffs(icache_size/icache_dsc->ways) - 1;
    icache_dsc->waybit =  __builtin_ffs(icache_size/icache_dsc->ways) - 1;
    printf("icache_dsc->linesz = %x\n", icache_dsc->linesz);
    printf("icache_dsc->sets = %x\n", icache_dsc->sets);
    printf("icache_dsc->ways = %x\n", icache_dsc->ways);
    printf("icache_dsc->waybit = %x\n", icache_dsc->waybit);
    printf("icache_size = %x\n", icache_size);
}

void read_dcache_config(cache_desc *dcache_dsc)
{
    unsigned int config1;
    unsigned int lsize;
    unsigned int dcache_size;

    asm volatile (       \
            ".set\tmips32\n\t"   \
            "mfc0 %0, $16, 1\n\t"\
            ".set\tmips0\n\t"    \
            : "=r" (config1));
    printf("dcache config = %x\n", config1);

    if ((lsize = ((config1 >> 10) & 7)))
    {
        dcache_dsc->linesz = 2 << lsize;
    }
    else
    {
        dcache_dsc->linesz = lsize;
    }
    dcache_dsc->sets = 64 << ((config1 >> 13) & 7);
    dcache_dsc->ways = 1 + ((config1 >> 7) & 7);

    dcache_size = dcache_dsc->sets *
                  dcache_dsc->ways *
                  dcache_dsc->linesz;
    //icache_dsc->waybit = ffs(icache_size/icache_dsc->ways) - 1;
    dcache_dsc->waybit =  __builtin_ffs(dcache_size/dcache_dsc->ways) - 1;
    printf("dcache_dsc->linesz = %x\n", dcache_dsc->linesz);
    printf("dcache_dsc->sets = %x\n", dcache_dsc->sets);
    printf("dcache_dsc->ways = %x\n", dcache_dsc->ways);
    printf("dcache_dsc->waybit = %x\n", dcache_dsc->waybit);
    printf("dcache_size = %x\n", dcache_size);
}

void enable_cache(MS_BOOL bEnable)
{
    unsigned int config;

    asm volatile("mfc0 %0, $16\n" \
             ".set push\n"    \
             ".set mips32r2\n"\
             "ehb\n"          \
             ".set pop\n" : "=r" (config) : );

    config = (config & ~CONFIG_KSEG0_MASK) | (bEnable ? KSEG0_CACHE : KSEG0_UNCACHED);

    asm volatile("mtc0 %0, $16\n" \
             ".set push\n"    \
             ".set mips32r2\n"\
             "ehb\n"          \
             ".set pop\n" : : "r" (config) );
}

#if 0
void invalidate_icache(void)
{
    cache_desc c;
    MS_U32 linesize;
    MS_U32 start;
    MS_U32 end;

    MS_U32 addr;
    MS_U8  u8OffsetBit, u8IndexBit, u8WayBit;
    MS_U32 u32Way, u32Index;

    read_icache_config(&c);
    linesize = c.linesz;

    u8OffsetBit = __builtin_ffs(c.linesz) - 1;
    u8IndexBit = __builtin_ffs( (c.sets * c.ways * c.linesz)/ c.ways) - 1;
    u8WayBit = u8IndexBit + (__builtin_ffs(c.ways) - 1);

    start = KSEG0_BASE;
    end = start + (c.sets * c.ways * c.linesz); // cache size

    // Invalidate lines
    asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
    hazard_barrier();

    for(addr = start; addr < end; addr += linesize)
    {

        unsigned int taglo;

        u32Way = addr & BITMASK(u8WayBit-1 : u8IndexBit);
        u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);

        taglo = (__pa(addr) & 0xFFFFF800) & ~(1 << 7) & ~(1 << 5); // PTaglo[31:11], V[7], L[5]
        asm volatile("mtc0  %0, $28, 0" : : "r" (taglo));
        hazard_barrier();

        asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_I),
                "r" (u32Way | u32Index));
        hazard_barrier();
    }
}
#endif
MS_BOOL ric_fill_icache(MS_U32 insts[], MS_U32 size)
{
    cache_desc c;
    MS_U32 linesize;
    MS_U32 start;
    MS_U32 end;
    MS_U32 ws_inc;
    MS_U32 ws_end;
    MS_U32 ws, bytes, addr, i;
    MS_U8  u8OffsetBit, u8IndexBit, u8WayBit;
    MS_U32 u32Way, u32Index;

    read_icache_config(&c);
    linesize = c.linesz;

    start = (MS_U32)(((MS_U32)insts&0x1FFFFFFF)|KSEG0_BASE);//0x83412000;
    end = (MS_U32)  (start+size);

    printf("start = 0x%x, end = 0x%x\n", (unsigned int)start, (unsigned int)end);

    ws_inc = 1U << c.waybit;
    ws_end = c.ways << c.waybit;

    u8OffsetBit = __builtin_ffs(c.linesz) - 1;
    u8IndexBit = __builtin_ffs( (c.sets * c.ways * c.linesz)/ c.ways) - 1;
    u8WayBit = u8IndexBit + (__builtin_ffs(c.ways) - 1);
    printf("u8OffsetBit = %d \n", u8OffsetBit);
    printf("u8IndexBit = %d \n", u8IndexBit);
    printf("u8WayBit = %d \n", u8WayBit);

    if(size % 4)
    {
        printf("The size is unalignment\n");
        return FALSE;
    }

    // Fill instruction to each way
    i = 0;
    for(addr = start; addr < end; addr += linesize)
    {
        unsigned int taglo;

        asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
        hazard_barrier();

        u32Way = addr & BITMASK(u8WayBit-1 : u8IndexBit);
        u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);

        for(bytes = 0; bytes < linesize; bytes += 8)
        {
            unsigned int lo = insts[i++];
            unsigned int hi = insts[i++];
            asm volatile("mtc0  %0, $28, 1" : : "r" (lo));
            asm volatile("mtc0  %0, $29, 1" : : "r" (hi));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_DATA_I),
                "r" (u32Way | u32Index | bytes));
            hazard_barrier();
        }

        // Lock line

        asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
        hazard_barrier();

        taglo = (VA2PA(addr) & 0xFFFFF800) | (1 << 7) | (1 << 5); // PTaglo[31:11], V[7], L[5]
        asm volatile("mtc0  %0, $28, 0" : : "r" (taglo));
        hazard_barrier();

        //u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);
        asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_I),
                "r" (u32Way | u32Index));
        hazard_barrier();
    }


    printf("Clear Way-Select\n");
    // Clear Way-Select
    asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
    hazard_barrier();
    for(addr = start; addr < end; addr += linesize)
    {
        for(ws = 0; ws < ws_end; ws += ws_inc)
        {
            asm volatile("mtc0  %0, $28, 0" : : "r" (0));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                    "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_I),
                    "r" (addr ^ ws));
            hazard_barrier();
        }
    }
    // Disable WST test mode
    asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
    hazard_barrier();

    printf("Disable WST test mode\n");

    return TRUE;
}

MS_BOOL ric_fill_dcache(MS_U32 insts[], MS_U32 size)
{
    cache_desc c;
    MS_U32 linesize;
    MS_U32 start;
    MS_U32 end;
    MS_U32 ws_inc;
    MS_U32 ws_end;
    MS_U32 ws, bytes, addr, i;
    MS_U8  u8OffsetBit, u8IndexBit, u8WayBit;
    MS_U32 u32Way, u32Index;

    read_dcache_config(&c);
    linesize = c.linesz;

    start = (MS_U32)(((MS_U32)insts&0x1FFFFFFF)|KSEG0_BASE);//0x8341A000;
    end = (MS_U32)  (start+size);

    printf("start = 0x%x, end = 0x%x\n", (unsigned int)start, (unsigned int)end);

    ws_inc = 1U << c.waybit;
    ws_end = c.ways << c.waybit;

    u8OffsetBit = __builtin_ffs(c.linesz) - 1;
    u8IndexBit = __builtin_ffs( (c.sets * c.ways * c.linesz)/ c.ways) - 1;
    u8WayBit = u8IndexBit + (__builtin_ffs(c.ways) - 1);
    printf("u8OffsetBit = %d \n", u8OffsetBit);
    printf("u8IndexBit = %d \n", u8IndexBit);
    printf("u8WayBit = %d \n", u8WayBit);

    if(size % 4)
    {
        printf("The size is unalignment\n");
        return FALSE;
    }

    // Fill instruction to each way
    i = 0;
    for(addr = start; addr < end; addr += linesize)
    {
        unsigned int taglo;

        asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
        hazard_barrier();

        u32Way = addr & BITMASK(u8WayBit-1 : u8IndexBit);
        u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);

        for(bytes = 0; bytes < linesize; bytes += 4)
        {
            unsigned int lo = insts[i++];
            //unsigned int hi = insts[i++];
            asm volatile("mtc0  %0, $28, 3" : : "r" (lo));
            //asm volatile("mtc0  %0, $29, 1" : : "r" (hi));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_DATA_D),
                "r" (u32Way | u32Index | bytes));
            hazard_barrier();
        }

        // Lock line

        asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
        hazard_barrier();

        taglo = (VA2PA(addr) & 0xFFFFF800) | (1 << 7);// | (1 << 5); // PTaglo[31:11], V[7], L[5]
        asm volatile("mtc0  %0, $28, 2" : : "r" (taglo));
        hazard_barrier();

        //u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);
        asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_D),
                "r" (u32Way | u32Index));
        hazard_barrier();
    }


    printf("Clear Way-Select\n");
    // Clear Way-Select
    asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
    hazard_barrier();
    for(addr = start; addr < end; addr += linesize)
    {
        for(ws = 0; ws < ws_end; ws += ws_inc)
        {
            asm volatile("mtc0  %0, $28, 2" : : "r" (0));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                    "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_D),
                    "r" (addr ^ ws));
            hazard_barrier();
        }
    }
    // Disable WST test mode
    asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
    hazard_barrier();

    printf("Disable WST test mode\n");

    return TRUE;
}

#endif
