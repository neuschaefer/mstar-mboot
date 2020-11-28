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
#include <stdio.h>
#include <assert.h>
//#include "datatype.h"
//#include "mhal_arch.h"

typedef unsigned int   U16;
typedef unsigned long  U32;

#define RIU_MAP  0x1F000000
//#define RIU      ((unsigned short volatile *) RIU_MAP)

#define BIT0        0x0001
#define BIT1        0x0002
#define BIT2        0x0004
#define BIT3        0x0008
#define BIT4        0x0010
#define BIT5        0x0020
#define BIT6        0x0040
#define BIT7        0x0080
#define BIT8        0x0100
#define BIT9        0x0200
#define BIT10       0x0400
#define BIT11       0x0800
#define BIT12       0x1000
#define BIT13       0x2000
#define BIT14       0x4000
#define BIT15       0x8000



#if 1



#define CREATE_MASK(msb, lsb)               (((1U << ((msb) - (lsb) + 1)) - 1) << (lsb))
#define MASK_BITS(arg, msb, lsb)            ((arg) & CREATE_MASK(msb, lsb))
#define EXTRACT_BITS(arg, msb, lsb)         (MASK_BITS(arg, msb, lsb) >> (lsb))
#define INSERT_BITS(arg, msb, lsb, value) \
    ((arg) = ((arg) & ~CREATE_MASK(msb, lsb)) | (((value) << (lsb)) & CREATE_MASK(msb, lsb)))

#define MASK_FIELD(arg, field)              MASK_BITS(arg, field##_MSB, field##_LSB)
#define EXTRACT_FIELD(arg, field)           EXTRACT_BITS(arg, field##_MSB, field##_LSB)
#define INSERT_FIELD(arg, field, value)     INSERT_BITS(arg, field##_MSB, field##_LSB, value)

#define SET_BIT(arg, bit)                   ((arg) |= (1 << (bit)))
#define CLEAR_BIT(arg, bit)                 ((arg) &= ~(1 << (bit)))
#define TEST_BIT(arg, bit)                  ((arg) & (1 << (bit)))

typedef struct
{
    unsigned int va;
    unsigned int pa;
    unsigned int size;
    int         access;
    int         attributes;
}
_cpu_memory_t;

#define MMU_AP_NONE         0
#define MMU_AP_PRIVILEGED   1
#define MMU_AP_READ         2
#define MMU_AP_FULL         3

#define MMU_BUFFERED        1
#define MMU_CACHED          2


void mhal_dcache_flush(U32 u32Base, U32 u32Size)
{
    unsigned long info,end,linelen,address;

    /* get cache info  */
    asm volatile ("mrc p15, 0, %0, c0, c0, 1"
                   : "=r" (info)
                   :
                   : "memory");

    linelen = 1 << ((info & 3) + 3);
    end = u32Base + u32Size;
    address = u32Base;

    do
    {
        /* Cleans and invalidates a Data Cache entry based on a virtual address */
        asm volatile ("mcr p15, 0, %0, c7, c14, 1"
                       : "=r"(address)
                       :
                       : "memory");
        address += linelen;
    }while(address < end);
}

#define LEVEL_1_ADDRESS(va,ttb) (MASK_BITS(ttb, 31, 14) | (EXTRACT_BITS(va, 31, 20) << 2))


/*! \brief  Reads the translation table base address
 *
 *  \return Translation table base address
 *
 */
static unsigned int __cpu_mmu_ttb_read (void)
{
    unsigned int ttb;

    asm volatile ("mrc p15, 0, %0, c2, c0, 0"
                   : "=r" (ttb)
                   :
                   : "memory");

    return ttb;
}

/*! \brief  Writes the domain register
 *
 *  \param  domains The domain access control register data
 *
 */
/*static void __cpu_mmu_domains_write (unsigned int domains)
{
    asm volatile ("mcr p15, 0, %0, c3, c0, 0"
                   : "=r" (domains)
                   :
                   : "memory");
}
*/
/*! \brief  Creates a section translation table entry.
 *
 * Taking the virtual section address, physical address, access permissions and attributes
 * a level 1 section entry is defined in the translation table.
 *
 *  \param  va          Virtual Address
 *  \param  pa          Physical Address
 *  \param  access      Access Permissions
 *  \param  attributes  Cacheable / Bufferable
 *
 */
static void __cpu_mmu_create_section (unsigned int va, unsigned int pa, int access, int attributes)
{
    unsigned int ttb;
    unsigned int *ptr;

    ttb  = __cpu_mmu_ttb_read ();
    ptr  = (unsigned int *)LEVEL_1_ADDRESS(va,ttb);
    *ptr = pa | (access << 10) | (attributes << 2) | 2;
}

/*
** TO BE IMPLEMENTED
*/
/*
static void __cpu_mmu_create_large_page (unsigned int va, unsigned int pa, int access, int attributes)
{
    va = va;
    pa = pa;
    access = access;
    attributes = attributes;
}
*/
/*
** TO BE IMPLEMENTED
*/
/*
static void __cpu_mmu_create_small_page (unsigned int va, unsigned int pa, int access, int attributes)
{
    va = va;
    pa = pa;
    access = access;
    attributes = attributes;
}
*/
/*! \brief  Creates a MMU table entry
 *
 * Takes a pointer to a memory descriptor (size, virtual address, physical address,
 * access permissions and attributes) and creates the required translation table
 * entries.
 *
 *  \param  entry   Pointer to the table entry
 *
 */
void _cpu_mmu_map_memory (_cpu_memory_t *entry)
{
    unsigned int size;
    unsigned int va;
    unsigned int pa;
    int access;
    int attributes;

    size        = entry->size;
    va          = entry->va;
    pa          = entry->pa;
    access      = entry->access;
    attributes  = entry->attributes;

#if 1
    /*
    ** Round up to MB so that we only use sections
    */
    size += 0x000FFFFF;
    size &= ~0x000FFFFF;
#endif

    while (size > 0)
    {   // Generate the page tables
        int temp = 0;

//        if (((va & 0x000FFFFF) == 0) && (size >= 0x00100000))
        {   // Create a 1 MB section
            __cpu_mmu_create_section (va, pa, access, attributes);
            temp = 0x00100000;
        }
//        else if (((va & 0x0000FFFF) == 0) && (size >= 0x00010000))
//        {
//            __cpu_mmu_create_large_page (va, pa, access, attributes);
//            temp = 0x00010000;
//        }
//        else if (((va & 0x00000FFF) == 0) && (size >= 0x00001000))
//        {
//            __cpu_mmu_create_small_page (va, pa, access, attributes);
//            temp = 0x00001000;
//        }

        va += temp;
        pa += temp;
        size -= temp;
    }
}

/*! \brief  Initializes the MMU
 *
 * Initializes the MMU, generating a background 4GB flat mapped full access,
 * non cacheable non bufferable page table then overlay that with cached and
 * buffered SDRAM entries.
 *
 */
void _mmu_mapping(void)
{
    _cpu_memory_t entry;

    entry.pa            = 0x1F000000;
    entry.va            = 0xFD000000;
    entry.size          = 0x01000000; // RIU(16M)
    entry.access        = MMU_AP_FULL;
    entry.attributes    = 0;

    _cpu_mmu_map_memory (&entry);

    entry.pa            = 0x15000000;
    entry.va            = 0xFB000000;
    entry.size          = 0x00001000; // L2C (4K)
    entry.access        = MMU_AP_FULL;
    entry.attributes    = 0;

    _cpu_mmu_map_memory (&entry);


    entry.pa            = 0x20000000;
    entry.va            = 0xC0000000;
    entry.size          = 0x8000000; // MIU0 - cached
    entry.access        = MMU_AP_FULL;
    entry.attributes    = MMU_CACHED | MMU_BUFFERED;
    //entry.attributes    = 0;

    _cpu_mmu_map_memory (&entry);

/*
    entry.pa            = 0x40000000;
    entry.va            = 0x20000000;
    entry.size          = 0x20000000; // MIU0 - uncached
    entry.access        = MMU_AP_FULL;
    entry.attributes    = 0;

    _cpu_mmu_map_memory (&entry);

    entry.pa            = 0xA0000000;
    entry.va            = 0x40000000;
    entry.size          = 0x20000000; // MIU1 - cached
    entry.access        = MMU_AP_FULL;
    entry.attributes    = MMU_CACHED | MMU_BUFFERED;

    _cpu_mmu_map_memory (&entry);

    entry.pa            = 0xA0000000;
    entry.va            = 0x60000000;
    entry.size          = 0x20000000; // MIU1 - uncached
    entry.access        = MMU_AP_FULL;
    entry.attributes    = 0;

    _cpu_mmu_map_memory (&entry);
*/

    /*
    ** We are only using domain 0.
    */
    //__cpu_mmu_domains_write (1);

}




#endif

#if 1

#define L2X0_CACHE_ID			0x000
#define   L2X0_CACHE_ID_PART_MASK	(0xf << 6)
#define   L2X0_CACHE_ID_PART_L210	(1 << 6)
#define   L2X0_CACHE_ID_PART_L310	(3 << 6)
#define L2X0_CACHE_TYPE			0x004
#define L2X0_CTRL			0x100
#define L2X0_AUX_CTRL			0x104
#define L2X0_TAG_LATENCY_CTRL		0x108
#define L2X0_DATA_LATENCY_CTRL		0x10C
#define L2X0_EVENT_CNT_CTRL		0x200
#define L2X0_EVENT_CNT1_CFG		0x204
#define L2X0_EVENT_CNT0_CFG		0x208
#define L2X0_EVENT_CNT1_VAL		0x20C
#define L2X0_EVENT_CNT0_VAL		0x210
#define L2X0_INTR_MASK			0x214
#define L2X0_MASKED_INTR_STAT		0x218
#define L2X0_RAW_INTR_STAT		0x21C
#define L2X0_INTR_CLEAR			0x220
#define L2X0_CACHE_SYNC			0x730
#define L2X0_INV_LINE_PA		0x770
#define L2X0_INV_WAY			0x77C
#define L2X0_CLEAN_LINE_PA		0x7B0
#define L2X0_CLEAN_LINE_IDX		0x7B8
#define L2X0_CLEAN_WAY			0x7BC
#define L2X0_CLEAN_INV_LINE_PA		0x7F0
#define L2X0_CLEAN_INV_LINE_IDX		0x7F8
#define L2X0_CLEAN_INV_WAY		0x7FC
#define L2X0_LOCKDOWN_WAY_D		0x900
#define L2X0_LOCKDOWN_WAY_I		0x904
#define L2X0_TEST_OPERATION		0xF00
#define L2X0_LINE_DATA			0xF10
#define L2X0_LINE_TAG			0xF30
#define L2X0_DEBUG_CTRL			0xF40

#define __user
#define __kernel
#define __safe
#define __force
#define __nocast
#define __iomem
#define __chk_user_ptr(x) (void)0
#define __chk_io_ptr(x) (void)0
#define __builtin_warning(x, y...) (1)
#define __acquires(x)
#define __releases(x)
#define __acquire(x) (void)0
#define __release(x) (void)0
#define __cond_lock(x,c) (c)
#define __percpu

#define __mem_pci(a) (a)
#define barrier() __asm__ __volatile__("": : :"memory")
#define mb()	do { barrier(); } while (0)
#define rmb()	do { barrier(); } while (0)
#define wmb()	do { barrier(); } while (0)
#define __iormb()		rmb()
#define __iowmb()		wmb()

#define __bitwise

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned int __u32;
typedef unsigned short __u16;
typedef __u32 __bitwise __le32;
typedef __u16 __bitwise __le16;
#define __le32_to_cpu(x) ((__force __u32)(__le32)(x))
#define __le16_to_cpu(x) ((__force __u16)(__le16)(x))
#define le32_to_cpu(x) ((__force __u32)(__le32)(x))
#define le16_to_cpu(x) ((__force __u16)(__le16)(x))
#define __cpu_to_le16(x) ((__force __le16)(__u16)(x))
#define __cpu_to_le32(x) ((__force __le32)(__u32)(x))
#define cpu_to_le16(x) ((__force __le16)(__u16)(x))
#define cpu_to_le32(x) ((__force __le32)(__u32)(x))


#define readb_relaxed(c) ({ u8  __v = __raw_readb(__mem_pci(c)); __v; })
#define readw_relaxed(c) ({ u16 __v = le16_to_cpu((__force __le16) \
					__raw_readw(__mem_pci(c))); __v; })
#define readl_relaxed(c) ({ u32 __v = le32_to_cpu((__force __le32) \
					__raw_readl(__mem_pci(c))); __v; })

#define writeb_relaxed(v,c)	((void)__raw_writeb(v,__mem_pci(c)))
#define writew_relaxed(v,c)	((void)__raw_writew((__force u16) \
					cpu_to_le16(v),__mem_pci(c)))
#define writel_relaxed(v,c)	((void)__raw_writel((__force u32) \
					cpu_to_le32(v),__mem_pci(c)))



#define __raw_writeb(v,a)	(__chk_io_ptr(a), *(volatile unsigned char __force  *)(a) = (v))
#define __raw_writew(v,a)	(__chk_io_ptr(a), *(volatile unsigned short __force *)(a) = (v))
#define __raw_writel(v,a)	(__chk_io_ptr(a), *(volatile unsigned int __force   *)(a) = (v))

#define __raw_readb(a)		(__chk_io_ptr(a), *(volatile unsigned char __force  *)(a))
#define __raw_readw(a)		(__chk_io_ptr(a), *(volatile unsigned short __force *)(a))
#define __raw_readl(a)		(__chk_io_ptr(a), *(volatile unsigned int __force   *)(a))


#define readb(c)		({ u8  __v = readb_relaxed(c); __iormb(); __v; })
#define readw(c)		({ u16 __v = readw_relaxed(c); __iormb(); __v; })
#define readl(c)		({ u32 __v = readl_relaxed(c); __iormb(); __v; })

#define writeb(v,c)		({ __iowmb(); writeb_relaxed(v,c); })
#define writew(v,c)		({ __iowmb(); writew_relaxed(v,c); })
#define writel(v,c)		({ __iowmb(); writel_relaxed(v,c); })

#define readsb(p,d,l)		__raw_readsb(__mem_pci(p),d,l)
#define readsw(p,d,l)		__raw_readsw(__mem_pci(p),d,l)
#define readsl(p,d,l)		__raw_readsl(__mem_pci(p),d,l)

#define writesb(p,d,l)		__raw_writesb(__mem_pci(p),d,l)
#define writesw(p,d,l)		__raw_writesw(__mem_pci(p),d,l)
#define writesl(p,d,l)		__raw_writesl(__mem_pci(p),d,l)

#define memset_io(c,v,l)	_memset_io(__mem_pci(c),(v),(l))
#define memcpy_fromio(a,c,l)	_memcpy_fromio((a),__mem_pci(c),(l))
#define memcpy_toio(c,a,l)	_memcpy_toio(__mem_pci(c),(a),(l))

#define L2CC_VIRT 0xFB000000
static void __iomem *l2x0_base;
static u32 l2x0_way_mask;	/* Bitmask of active ways */

static inline void cache_wait(void __iomem *reg, unsigned long mask)
{
	/* cache operations by line are atomic on PL310 */
}

static inline void cache_sync(void)
{
	void __iomem *base = l2x0_base;
	writel_relaxed(0, base + L2X0_CACHE_SYNC);
	cache_wait(base + L2X0_CACHE_SYNC, 1);
}


static inline void cache_wait_way(void __iomem *reg, unsigned long mask)
{
	/* wait for cache operation by line or way to complete */
	while (readl_relaxed(reg) & mask)
		;
}


static inline void l2x0_inv_all(void)
{
	//unsigned long flags;

	/* invalidate all ways */
	writel_relaxed(l2x0_way_mask, l2x0_base + L2X0_INV_WAY);
	cache_wait_way(l2x0_base + L2X0_INV_WAY, l2x0_way_mask);
	cache_sync();

}


void l2x0_init(void __iomem *base, __u32 aux_val, __u32 aux_mask)
{
	__u32 aux;
	__u32 cache_id;
	int ways;
	const char *type;

	l2x0_base = base;

	cache_id = readl_relaxed(l2x0_base + L2X0_CACHE_ID);
	aux = readl_relaxed(l2x0_base + L2X0_AUX_CTRL);
//printk("cache id : 0x%08X\n",cache_id);
//printk("aux : 0x%08X\n",aux);

	aux &= aux_mask;
	aux |= aux_val;

	/* Determine the number of ways */
	switch (cache_id & L2X0_CACHE_ID_PART_MASK) {
	case L2X0_CACHE_ID_PART_L310:
		if (aux & (1 << 16))
			ways = 16;
		else
			ways = 8;
		type = "L310";
		break;
	case L2X0_CACHE_ID_PART_L210:
		ways = (aux >> 13) & 0xf;
		type = "L210";
		break;
	default:
		/* Assume unknown chips have 8 ways */
		ways = 8;
		type = "L2x0 series";
		break;
	}

	l2x0_way_mask = (1 << ways) - 1;

	/*
	 * Check if l2x0 controller is already enabled.
	 * If you are booting from non-secure mode
	 * accessing the below registers will fault.
	 */
	if (!(readl_relaxed(l2x0_base + L2X0_CTRL) & 1)) {
//printk("L2 disable \n");
		/* l2x0 controller is disabled */
		writel_relaxed(aux, l2x0_base + L2X0_AUX_CTRL);

		l2x0_inv_all();

		/* enable L2X0 */
		writel_relaxed(1, l2x0_base + L2X0_CTRL);
	}
#if 0
	outer_cache.inv_range = l2x0_inv_range;
	outer_cache.clean_range = l2x0_clean_range;
	outer_cache.flush_range = l2x0_flush_range;
	outer_cache.sync = l2x0_cache_sync;

	printk(KERN_INFO "%s cache controller enabled\n", type);
	printk(KERN_INFO "l2x0: %d ways, CACHE_ID 0x%08x, AUX_CTRL 0x%08x\n",
			 ways, cache_id, aux);
#endif
}

#define VA 1
#ifdef VA
    #define RIU(a) *(volatile unsigned short *)(a+(0xDE000000))
    #define MIU(a) *(volatile unsigned int *)(a+(0x80000000))
#else
    #define RIU(a) *(volatile unsigned short *)(a)
    #define MIU(a) *(volatile unsigned int *)(a)
#endif





void L2CC(void)
{

	void __iomem *l2x0_base = L2CC_VIRT;
    //void __iomem *l2x0_base = 0x15000000;

    //disable L2 cache
    *(volatile unsigned int *)( l2x0_base + L2X0_CTRL)=0x0;

	/* set RAM latencies to 1 cycle for this core tile. */
	*(volatile unsigned int *)( l2x0_base + L2X0_TAG_LATENCY_CTRL)=0x0;
	*(volatile unsigned int *)( l2x0_base + L2X0_DATA_LATENCY_CTRL)=0x0;
	//writel(0x1,l2x0_base + L2X0_TAG_LATENCY_CTRL);
    //writel(0x1,l2x0_base + L2X0_DATA_LATENCY_CTRL);

 //   *(volatile unsigned int *)( l2x0_base + L2X0_AUX_CTRL)=0x02420000;//L2 size = 128K
#if 0
    //way size
    *(volatile unsigned int *)( l2x0_base + L2X0_AUX_CTRL)=0x00420000;

    //interrupt clear & mask
	*(volatile unsigned int *)( l2x0_base + L2X0_INTR_CLEAR)=0x1ff;
	*(volatile unsigned int *)( l2x0_base + L2X0_INTR_MASK)=0x1ff;

    //invalidate cache by way
    *(volatile unsigned int *)( l2x0_base + L2X0_INV_WAY)=0xff;
    while(*(volatile unsigned int *)( l2x0_base + L2X0_INV_WAY)!=0)  {};  //wait complete

    //enable L2 cache
    *(volatile unsigned int *)( l2x0_base + L2X0_CTRL)=0x1;
#else
	l2x0_init(l2x0_base, 0x00400000, 0xfe0fffff);//shared attribute override enable
#endif
	//l2x0_init(l2x0_base, 0x00000000, 0xfe0fffff);

	RIU(0x1f206744)=*(volatile unsigned int *)( l2x0_base + 0x100);
	RIU(0x1f206748)=(*(volatile unsigned int *)( l2x0_base + 0x104))>>16;
	RIU(0x1f20674c)=*(volatile unsigned int *)( l2x0_base + L2X0_TAG_LATENCY_CTRL);
	RIU(0x1f206750)=*(volatile unsigned int *)( l2x0_base + L2X0_DATA_LATENCY_CTRL);
}




//----------------------------------------------------


void RIU_WTEST(void)
{
    RIU(0x1F206700)=0x5678;
}

void RIU_READ(void)
{
    unsigned int tmp;
    tmp=RIU(0x1F206700);
}

void RIU_WTEST2(void)
{
    RIU(0x1F206700)=0xABCD;
}


void READ_TEST1(void)
{
    unsigned int tmp;
    tmp=MIU(0x40100000);
}

void WRITE_TEST1(void)
{
    MIU(0x40100000)=0xA5A5A5A5;
}


void READ_TEST2(void)
{
    unsigned int tmp;
    tmp=MIU(0x40300000);
}

void WRITE_TEST2(void)
{
    MIU(0x40300000)=0x78787878;
}

#endif

static int a;
int abc(void)
{
a++;
return a;
}


//#define tdelay {t=100; while(t>0){t--;} }
#define tdelay
// {asm volatile ("": : :"memory");}
//#define mb()	asm volatile ("": : :"memory")


void putk(unsigned char k)
{
  *(volatile unsigned short *)(0x1f201300)=k;
}

void mainc()
{

    //core_init();
    putk(0x6f);//o
    putk(0x6b);//k

    _mmu_mapping(); //create mapping: RIU, MIU, L2


#if 1
    __asm__ volatile
    (
        "MRC   p15, 0, r0, c1, c0, 0\n\t"
        "ORR   r0, r0, #(0x1 << 12)\n\t"
        "ORR   r0, r0, #(0x1 << 2)\n\t"
        "MCR   p15, 0, r0, c1, c0, 0\n\t"
    );
#endif

//asm volatile ("": : :"memory");

#if 0
putk(0x61);//a
    //_mmu_mapping(); //create mapping: RIU, MIU, L2
putk(0x62);//b
    //RIU_WTEST();
putk(0x63);//1
    WRITE_TEST1();
putk(0x64);//d
    READ_TEST1();
putk(0x65);//e
    WRITE_TEST2();
putk(0x66);//f
    READ_TEST2();
#endif

//asm volatile ("": : :"memory");



unsigned int addr,tmp,err;
unsigned int cnt,i;
/***********************
  L1 cache test
************************/
#if 0
//write test
addr=0x40500000;
err=0;
for(i=0;i<0x500;i++)
{
    addr=addr+(0x10000);
    for(cnt=0;cnt<0x1000;cnt++)
    {
        MIU(addr)=0xA5A51234;
        addr+=4;
    }
}

//asm volatile ("": : :"memory");
putk(0x67);//g
addr=0x40500000;
//putk(0xd);//new line
putk(0xa);//new line
RIU(0x1f001d48)=0xaaaa;
RIU(0x1f001d4C)=0xaaaa;
RIU(0x1f001d50)=0xaaaa;
RIU(0x1f001d54)=0xaaaa;
//read test
for(i=0;i<0x500;i++)
{
    addr=addr+(0x10000);
    for(cnt=0;cnt<0x1000;cnt++)
    {
        tmp=MIU(addr);
        if(tmp!=0xA5A51234)
        {
            RIU(0x1f001d48)=(unsigned short)(i);
            RIU(0x1f001d4c)=(unsigned short)(cnt);
            RIU(0x1f001d50)=(unsigned short)((tmp>>16)&0xffff);
            RIU(0x1f001d54)=(unsigned short)((tmp)&0xffff);
            while(1);

        }
        addr+=4;
    }
}

putk(0x68);//h
//mhal_dcache_flush(0x40500000,0x100000);
#endif

#if 0
/***********************
  L2 cache test
************************/
    L2CC();  //L2 cache init
RIU(0x1f001d48)=0xbbbb;
RIU(0x1f001d4C)=0xbbbb;
RIU(0x1f001d50)=0xbbbb;
RIU(0x1f001d54)=0xbbbb;
putk(0x69);//i
err=0;

abc();

#if 1
//write test
addr=0x40700000;
for(i=0;i<0x500;i++)
{
    //putk(0x30+(unsigned char)(i));
    RIU(0x1f206704)=(unsigned short)(i);
    addr=addr+(0x10000);
    for(cnt=0;cnt<0x1000;cnt++)
    {
        RIU(0x1f206708)=(unsigned short)(cnt);
        MIU(addr+(cnt*4))=0xA5A56789;

    }
}

abc();
//asm volatile ("": : :"memory");
putk(0x6a);//j


//putk(0xd);//new line
putk(0xa);//new line


//read test
addr=0x40700000;
for(i=0;i<0x500;i++) //> 8 way
{
    addr=addr+(0x10000);//8k :way size
    RIU(0x1f206724)=(unsigned short)(i);
    for(cnt=0;cnt<0x1000;cnt++)
    {
        RIU(0x1f206728)=(unsigned short)(cnt);
        tmp=MIU(addr+(cnt*4));
        if(tmp!=0xA5A56789)
        {
            RIU(0x1f206740)=0x3697;
            RIU(0x1f001d48)=(unsigned short)(i);
            RIU(0x1f001d4c)=(unsigned short)(cnt);
            RIU(0x1f001d50)=(unsigned short)((tmp>>16)&0xffff);
            RIU(0x1f001d54)=(unsigned short)((tmp)&0xffff);
            RIU(0x1f20672c)=(unsigned short)((addr>>16)&0xffff);
            RIU(0x1f206730)=(unsigned short)((addr)&0xffff);
            while(1);

        }
        //asm volatile ("": : :"memory");
    }
}
#endif
RIU(0x1f001d48)=0xcccc;
RIU(0x1f001d4C)=0xcccc;
RIU(0x1f001d50)=0xcccc;
RIU(0x1f001d54)=0xcccc;
//RIU(0x1f206708)=err;

putk(0x6b);//k
while(1);
#endif

}