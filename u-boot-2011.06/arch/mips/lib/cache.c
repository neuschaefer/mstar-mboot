/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 *
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 */
#include "config.h"
//#include "chip_setup.h"

#ifdef __MIPS__ //The functions in this file are only for MIPS not for AeonR2.

#define _BITMASK(loc_msb, loc_lsb) ((1U << (loc_msb)) - (1U << (loc_lsb)) + (1U << (loc_msb)))
#define BITMASK(x) _BITMASK(1?x, 0?x)
#define _BIT(x)                      (1<<(x))


#define BIT0       0x01
#define BIT1       0x02
#define BIT2       0x04
#define BIT3       0x08
#define BIT4       0x10
#define BIT5       0x20
#define BIT6       0x40
#define BIT7       0x80

#define MIU1_BUS_BASE    (0x60000000)
#define HIGH_MEM_BUS_BASE    (0x50000000)
#define HIGH_MEM_PHY_BASE    (0x10000000)
#define HIGH_MEM_MAX_BUS_ADDR           (0x80000000)


#define NULL 0
#define spin_lock_irq(x)
#define spin_unlock_irq(x)

#if defined(CONFIG_JANUS2) || \
    defined(CONFIG_AMBER5)
static unsigned int dwCacheLineSize = 0;
#endif

/*
 * Cache Operations available on all MIPS processors with R4000-style caches
 */
#define Index_Invalidate_I      0x00
#define Index_Writeback_Inv_D   0x01
#define Index_Load_Tag_I 0x04
#define Index_Load_Tag_D 0x05
#define Index_Store_Tag_I 0x08
#define Index_Store_Tag_D 0x09
#if defined(CONFIG_CPU_LOONGSON2)
#define Hit_Invalidate_I 0x00
#else
#define Hit_Invalidate_I 0x10
#endif
#define Hit_Invalidate_D 0x11
#define Hit_Writeback_Inv_D 0x15
// From kernel cacheops.h end

// From kernel mipsregs.h start
#ifdef __ASSEMBLY__
#define _ULCAST_
#else
#define _ULCAST_ (unsigned long)
#endif

extern int printf(const char *fmt, ...);

inline unsigned long Chip_mphy_bus( unsigned long phyaddress )
{
    //Check Address Range in MIU Interval 512MB
    if(phyaddress >= (CONFIG_SYS_MIU_INTERVAL << 1))
    {
        return -1;
    }
    else
    {
        return phyaddress;
    }
}

inline unsigned long Chip_bus_mphy( unsigned long busaddress )
{

    if(busaddress >= HIGH_MEM_MAX_BUS_ADDR)
    {
        return -1;
    }
    else
    {
        return busaddress;
    }

}


inline void _chip_flush_miu_pipe(void)
{
#if defined(CONFIG_AMBER1) || \
    defined(CONFIG_AMBER6) || \
    defined(CONFIG_AMBER7) || \
    defined(CONFIG_EMERALD)

    unsigned int    dwReadData = 0;

    dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
    *(volatile unsigned int *)(0xbf203104) = 0x02;          //Flush Pipe Data
    dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
    *(volatile unsigned int *)(0xbf203104) = 0x12;

    do
    {
        dwReadData = *(volatile unsigned int *)(0xbf203104);
        dwReadData &= _BIT(9);

    } while(dwReadData == 0);

    dwReadData = *(volatile unsigned int *)(0xbf201600);   //Dummy Read

#elif defined(CONFIG_AMBER2) || \
      defined(CONFIG_AMBER5)

	unsigned int    dwReadData = 0;

    //Flush Pipe Data
    dwReadData = *(volatile unsigned int *)(0xbf203104);
    dwReadData &= 0xFFFFFFF0;
    dwReadData &= ~_BIT(4);
    dwReadData |= 0x02;    //Flush Pipe Data
    *(volatile unsigned int *)(0xbf203104) = dwReadData;

    *(volatile unsigned int *)(0xbf203104) |= _BIT(4);

    do
    {
        dwReadData = *(volatile unsigned int *)(0xbf20317c);
        dwReadData &= _BIT(9);  //Check Status of Flush Pipe Finish

    } while(dwReadData == 0);

#elif defined(CONFIG_AMETHYST) || \
      defined(CONFIG_NUGGET) || \
      defined(CONFIG_NIKON) || \
      defined(CONFIG_MILAN)

    unsigned int    dwReadData = 0;

    spin_lock_irq(&l2prefetch_lock);

    dwReadData = *(volatile unsigned int *)(0xbf203104);
    dwReadData &= ~(0x1F);
    dwReadData |= 0x02;         //Flush MIU Pipe
    *(volatile unsigned int *)(0xbf203104) = dwReadData;

    dwReadData = *(volatile unsigned int *)(0xbf203104);
    dwReadData |= _BIT(4);
    *(volatile unsigned int *)(0xbf203104) = dwReadData;

    do
    {
        dwReadData = *(volatile unsigned int *)(0xbf20317c);
        dwReadData &= _BIT(9);  //Check Status of Flush MIU Pipe Finish

    } while(dwReadData == 0);

    spin_unlock_irq(&l2prefetch_lock);

#elif defined(CONFIG_KENYA) || defined(CONFIG_KERES)|| defined(CONFIG_KRITI)|| defined(CONFIG_KRIS)

    unsigned int    dwReadData = 0;

    spin_lock_irq(&l2prefetch_lock);

    dwReadData = *(volatile unsigned int *)(0xbf203104);
    dwReadData &= ~(0x1F);
    dwReadData |= 0x02;         //Flush MIU Pipe

    *(volatile unsigned int *)(0xbf203104) = dwReadData;
    *(volatile unsigned int *)(0xbf203104) |= _BIT(4);

    do
    {
        dwReadData = *(volatile unsigned int *)(0xbf203104);
        dwReadData &= _BIT(9);  //Check Status of Flush MIU Pipe Finish

    } while(dwReadData == 0);

    spin_unlock_irq(&l2prefetch_lock);

#else
    static unsigned int u8_4Lines[1];
    volatile unsigned int *pu8;
    volatile unsigned int tmp ;

    // Transfer the memory to noncache memory
    pu8 = ((volatile unsigned int *)(((unsigned int)u8_4Lines) | 0xa0000000));
    pu8[0] = 1;

    //mb();
    asm volatile("sync;");

    // final read back
    tmp = pu8[0];
#endif
}


void Chip_L2_cache_wback_inv( unsigned long addr, unsigned long size)
{
#if defined(CONFIG_TITANIA8) || defined(CONFIG_TITANIA12)

    volatile unsigned int temp=0;
    static unsigned int CacheLineSize=0;
    if( !CacheLineSize )
    {
        CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(4)|_BIT(5)))>>4;  // H40 L2 cache line size 00: 32-bytes    01: 64-bytes    1x: 128-bytes
        //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
        switch(CacheLineSize  )
        {
         case 0:
            CacheLineSize=~(32-1);
            break;
         case 1:
            CacheLineSize=~(64-1);
            break;
         case 2:
         case 3:
            CacheLineSize=~(128-1);
            break;
        default:
            //printf("Chip_L2_cache_wback_inv Failed: Unknown cache line size:%x \n"  , CacheLineSize);
            return;
            break;
        }
    }

    if( (addr > 0x40000000) || (size == 0) )
    {
        _chip_flush_miu_pipe();
        return;
    }

    // TODO: U01 only
    size = 0x20000;

    // L2 disabled
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        _chip_flush_miu_pipe();
        spin_unlock_irq(&l2prefetch_lock);
    }
    else if( size >= 0x20000 )
    {
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = 0x4; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x4; // H41 all
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(10);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = 0; // H41
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        // invalid all
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4); // H41
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(8);//all
        }while(temp == 0);
        // ^JL^ necessary read
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMBER1) || \
      defined(CONFIG_AMBER6) || \
      defined(CONFIG_AMBER7) || \
      defined(CONFIG_EMERALD)

    unsigned int    dwReadData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & _BIT(1)) != 0)
    {
        _chip_flush_miu_pipe();
    }
    else
    {
        spin_lock_irq(&l2prefetch_lock);
        dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
        *(volatile unsigned int *)(0xbf203104) = 0x04;          //Flush All and Keep Valid
        dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
        *(volatile unsigned int *)(0xbf203104) = 0x14;

        do
        {
            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData &= _BIT(10);

        } while(dwReadData == 0);

        dwReadData = *(volatile unsigned int *)(0xbf201600);   //Dummy Read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_JANUS2) || \
      defined(CONFIG_AMBER5)

    unsigned int    dwTempData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
    {
        //L2 Cache Disable
        spin_lock_irq(&l2prefetch_lock);

        //Flush Pipe Data
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x02;                                     //Set cache_op_mode
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf20317c);
            dwTempData &= _BIT(9);  //Check Status of Flush Pipe Finish

        } while(dwTempData == 0);

        spin_unlock_irq(&l2prefetch_lock);

    }
    else //if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) == 0)
    {
        if(dwCacheLineSize == 0)
        {
            //Read Bank 0x101840[6:5] to get cache line size
            dwCacheLineSize = (*(volatile unsigned int *)(0xbf203100));
            dwCacheLineSize &= (_BIT(5) | _BIT(6));
            dwCacheLineSize >>= 5;

            switch(dwCacheLineSize)
            {
                case 0:
                {
                    printf("[INFO] Cache Line Size: 64 Bytes\n");
                    dwCacheLineSize = ~(64-1);
                }
                break;

                case 1:
                {
                    printf("[INFO] Cache Line Size: 128 Bytes\n");
                    dwCacheLineSize = ~(128-1);
                }
                break;

                case 2:
                {
                    printf("[INFO] Cache Line Size: 256 Bytes\n");
                    dwCacheLineSize = ~(256-1);
                }
                break;

                default:
                {
                    printf("[INFO] Cache Line Size: Invalid\n");
                    dwCacheLineSize = 0;
                    return;
                }
                break;
            }
        }

        if(addr > 0x40000000)
        {
            printf("[ERROR] Out of Range\n");
            return;
        }

        spin_lock_irq(&l2prefetch_lock);

        dwTempData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read

        //Flush All and Invalid
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x04;                                     //Set cache_op_mode
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf20317c);
            dwTempData &= _BIT(10);  //Check Status of Flush All Finish

        } while(dwTempData == 0);

        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMETHYST) || \
      defined(CONFIG_NUGGET) || \
      defined(CONFIG_NIKON) || \
      defined(CONFIG_MILAN)

    unsigned int    dwReadData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
    {
        _chip_flush_miu_pipe();
    }
    else
    {
        if(addr > 0x40000000)
        {
            printf("[ERROR] Out of Range\n");
        }
        else
        {
            spin_lock_irq(&l2prefetch_lock);

            //Flush All and Invalid
            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData &= ~(0x1F);
            dwReadData |= 0x04;     //Flush All and Invalid
            *(volatile unsigned int *)(0xbf203104) = dwReadData;

            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwReadData;

            do
            {
                dwReadData = *(volatile unsigned int *)(0xbf20317c);
                dwReadData &= _BIT(10);  //Check Status of Flush All Finish

            } while(dwReadData == 0);

            spin_unlock_irq(&l2prefetch_lock);
        }
    }

#elif defined(CONFIG_KAISERIN) || \
	  defined(CONFIG_KENYA)    || \
	  defined(CONFIG_KRITI)    || \
	  defined(CONFIG_KERES)    || \
      defined(CONFIG_KRIS)


        #if defined(CONFIG_KAISERIN)
        static unsigned int CacheLineSize = 0;
		#endif
        unsigned int dwTempData = 0;

        if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)  //L2 Cache Disable
        {
            spin_lock_irq(&l2prefetch_lock);

            //Flush Pipe Data
            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData |= 0x02;                                     //Set cache_op_mode
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            do
            {
                dwTempData = *(volatile unsigned int *)(0xbf203104);
                dwTempData &= _BIT(9);  //Check Status of Flush Pipe Finish

            } while(dwTempData == 0);

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            spin_unlock_irq(&l2prefetch_lock);

        }
        else //if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) == 0)
        {
            #if defined(CONFIG_KAISERIN)
            if(!CacheLineSize)
            {
                CacheLineSize = ((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(4)|_BIT(5)))>>4;  // H40 L2 cache line size 00: 32-bytes    01: 64-bytes    1x: 128-bytes
                switch(CacheLineSize)
                {
                 case 0:
                    CacheLineSize =~ (32-1);
                    break;
                 case 1:
                    CacheLineSize =~ (64-1);
                    break;
                 case 2:
                 case 3:
                    CacheLineSize =~ (128-1);
                    break;
                default:
                    //printf("Chip_L2_cache_wback_inv Failed: Unknown cache line size:%x \n"  , CacheLineSize);
                    return;
                    break;
                }
            }
            #endif

            spin_lock_irq(&l2prefetch_lock);

            dwTempData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read

            //Flush All and Invalid
            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData |= 0x04;                                     //Set cache_op_mode
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            do
            {
                dwTempData = *(volatile unsigned int *)(0xbf203104);
                dwTempData &= _BIT(10);  //Check Status of Flush All Finish

            } while(dwTempData == 0);

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            spin_unlock_irq(&l2prefetch_lock);
        }
#endif

    // flush MIU pipe
    _chip_flush_miu_pipe();
}

void Chip_L2_cache_wback( unsigned long addr, unsigned long size)
{
#if defined(CONFIG_TITANIA8) || defined(CONFIG_TITANIA12)
    volatile unsigned int temp=0;
    static unsigned int CacheLineSize=0;
    if( !CacheLineSize )
    {
        CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(4)|_BIT(5)))>>4;  // H40 L2 cache line size 00: 32-bytes    01: 64-bytes    1x: 128-bytes
        //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
        switch(CacheLineSize  )
        {
         case 0:
            CacheLineSize=~(32-1);
            break;
         case 1:
            CacheLineSize=~(64-1);
            break;
         case 2:
         case 3:
            CacheLineSize=~(128-1);
            break;
        default:
            //printf("Chip_L2_cache_wback Failed: Unknown cache line size:%x \n"  , CacheLineSize);
            return;
            break;
        }
    }

    if( (addr > 0x40000000) || (size == 0) )
    {
         _chip_flush_miu_pipe();
         return;
    }

    // L2 disabled
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        _chip_flush_miu_pipe();
        spin_unlock_irq(&l2prefetch_lock);
    }
    else
    {
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x3; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x3; // H41 all
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(10);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMBER2)

    volatile unsigned int temp=0;
    static unsigned int CacheLineSize=0;
    if( !CacheLineSize )
    {
        CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(5)|_BIT(6)))>>5;  // H40 L2 cache line size 00: 64-bytes    01: 128-bytes    1x: 256-bytes
        //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
        switch(CacheLineSize  )
        {
         case 0:
            CacheLineSize=~(64-1);
            break;
         case 1:
            CacheLineSize=~(128-1);
            break;
         case 2:
         case 3:
            CacheLineSize=~(256-1);
            break;
        default:
            //printf("Chip_L2_cache_wback Failed: Unknown cache line size:%x \n"  , CacheLineSize);
            return;
            break;
        }
    }

    if( (addr > 0x40000000) || (size == 0) )
    {
         _chip_flush_miu_pipe();
         return;
    }

    // L2 disabled
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        _chip_flush_miu_pipe();
        spin_unlock_irq(&l2prefetch_lock);
    }
    else
    {
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf203104) = ((*(volatile unsigned int *)(0xBF203104) & 0xFFF0) | 0x0003);  //mode 3:Flush all and keep valid
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf203104) = ((*(volatile unsigned int *)(0xBF203104) & 0xFFE0) | 0x0013);  //mode 3:Fire
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x20317C);
            temp &= _BIT(10);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }
#elif defined(CONFIG_TITANIA9) || defined(CONFIG_TITANIA13)

    volatile unsigned int temp=0;
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
    // L2 disabled
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x2; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x2; // H41 all

        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(9);//pipe
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }
    else
    {
    // L2 enabled
        // flush all and keep valid
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x3; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x3; // H41 all
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(10);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMBER1) || defined(CONFIG_AMBER6) || defined(CONFIG_AMBER7) || defined(CONFIG_EMERALD)

    unsigned int    dwReadData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & _BIT(1)) != 0)
    {
        _chip_flush_miu_pipe();
    }
    else
    {
        spin_lock_irq(&l2prefetch_lock);
        dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
        *(volatile unsigned int *)(0xbf203104) = 0x03;          //Flush All and Keep Valid
        dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
        *(volatile unsigned int *)(0xbf203104) = 0x13;

        do
        {
            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData &= _BIT(10);

        } while(dwReadData == 0);

        dwReadData = *(volatile unsigned int *)(0xbf201600);   //Dummy Read
        spin_unlock_irq(&l2prefetch_lock);
    }


#elif defined(CONFIG_JANUS2)|| defined(CONFIG_AMBER5)

    unsigned int    dwTempData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
    {
        //L2 Cache Disable
        spin_lock_irq(&l2prefetch_lock);

        //Flush Pipe Data
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x02;       //Flush Pipe Data
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf20317c);
            dwTempData &= _BIT(9);  //Check Status of Flush Pipe Finish

        } while(dwTempData == 0);

        spin_unlock_irq(&l2prefetch_lock);

    }
    else //if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) == 0)
    {
        if(dwCacheLineSize == 0)
        {
            //Read Bank 0x101840[6:5] to get cache line size
            dwCacheLineSize = (*(volatile unsigned int *)(0xbf203100));
            dwCacheLineSize &= (_BIT(5) | _BIT(6));
            dwCacheLineSize >>= 5;

            switch(dwCacheLineSize)
            {
                case 0:
                {
                    printf("[INFO] Cache Line Size: 64 Bytes\n");
                    dwCacheLineSize = ~(64-1);
                }
                break;

                case 1:
                {
                    printf("[INFO] Cache Line Size: 128 Bytes\n");
                    dwCacheLineSize = ~(128-1);
                }
                break;

                case 2:
                {
                    printf("[INFO] Cache Line Size: 256 Bytes\n");
                    dwCacheLineSize = ~(256-1);
                }
                break;

                default:
                {
                    printf("[INFO] Cache Line Size: Invalid\n");
                    dwCacheLineSize = 0;
                    return;
                }
                break;
            }
        }

        if(addr > 0x40000000)
        {
            printf("[ERROR] Out of Range\n");
            return;
        }

        spin_lock_irq(&l2prefetch_lock);

        //Flush All and Keep Valid
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x03;     //Flush All and Keep Valid
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf20317c);
            dwTempData &= _BIT(10); //Check Status of Flush All Finish

        } while(dwTempData == 0);

        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMETHYST) || \
      defined(CONFIG_NUGGET) || \
      defined(CONFIG_NIKON) || \
      defined(CONFIG_MILAN)

    unsigned int    dwReadData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
    {
        _chip_flush_miu_pipe();
    }
    else
    {
        if(addr > 0x40000000)
        {
            printf("[ERROR] Out of Range\n");
        }
        else
        {
            spin_lock_irq(&l2prefetch_lock);

            //Flush All and Keep Valid
            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData &= ~(0x1F);
            dwReadData |= 0x03;     //Flush All and Keep Valid
            *(volatile unsigned int *)(0xbf203104) = dwReadData;

            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwReadData;

            do
            {
                dwReadData = *(volatile unsigned int *)(0xbf20317c);
                dwReadData &= _BIT(10); //Check Status of Flush All Finish

            } while(dwReadData == 0);

            spin_unlock_irq(&l2prefetch_lock);
        }
    }

#elif defined(CONFIG_KAISERIN) || \
	  defined(CONFIG_KENYA)    || \
	  defined(CONFIG_KRITI)    || \
	  defined(CONFIG_KERES)    || \
      defined(CONFIG_KRIS)

      
        unsigned int    dwTempData = 0;
        static unsigned int CacheLineSize=0;

        if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
        {
            //L2 Cache Disable
            spin_lock_irq(&l2prefetch_lock);

            //Flush Pipe Data
            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData |= 0x02;       //Flush Pipe Data
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            do
            {
                dwTempData = *(volatile unsigned int *)(0xbf203104);
                dwTempData &= _BIT(9);  //Check Status of Flush Pipe Finish

            } while(dwTempData == 0);

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            spin_unlock_irq(&l2prefetch_lock);

        }
        else //if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) == 0)
        {
            if(!CacheLineSize)
            {
                CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(4)|_BIT(5)))>>4;  // H40 L2 cache line size 00: 32-bytes    01: 64-bytes    1x: 128-bytes
                //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
                switch(CacheLineSize  )
                {
                    case 0:
                        CacheLineSize =~ (32-1);
                        break;
                    case 1:
                        CacheLineSize =~ (64-1);
                        break;
                    case 2:
                    case 3:
                        CacheLineSize =~ (128-1);
                        break;
                    default:
                        //printf("Chip_L2_cache_wback Failed: Unknown cache line size:%x \n"  , CacheLineSize);
                        return;
                        break;
                }
            }

            spin_lock_irq(&l2prefetch_lock);

            //Flush All and Keep Valid
            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData |= 0x03;     //Flush All and Keep Valid
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            //printf("*(volatile unsigned int *)(0xbf203104) = 0x%x \n",*(volatile unsigned int *)(0xbf203104));
            //dwTempData = *(volatile unsigned int *)(0xbf203104);
            //dwTempData &= ~_BIT(4);
            //*(volatile unsigned int *)(0xbf203104) = dwTempData;

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData |= 0x03;     //Flush All and Keep Valid
            dwTempData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;
            //printf("*(volatile unsigned int *)(0xbf203104) = 0x%x \n",*(volatile unsigned int *)(0xbf203104));

            do
            {
                dwTempData = *(volatile unsigned int *)(0xbf203104);
                dwTempData &= _BIT(10); //Check Status of Flush All Finish

            } while(dwTempData == 0);

            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= ~(0x0F);
            dwTempData &= ~_BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwTempData;

            spin_unlock_irq(&l2prefetch_lock);
        }

#endif

    // flush MIU pipe
    _chip_flush_miu_pipe();

}

void Chip_L2_cache_inv( unsigned long addr, unsigned long size)
{
#if defined(CONFIG_TITANIA8) || defined(CONFIG_TITANIA12)
    volatile unsigned int temp=0;
    static unsigned int CacheLineSize=0;
    if( !CacheLineSize )
    {
        CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(4)|_BIT(5)))>>4;  // H40 L2 cache line size 00: 32-bytes    01: 64-bytes    1x: 128-bytes
        //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
        switch(CacheLineSize  )
        {
         case 0:
            CacheLineSize=~(32-1);
            break;
         case 1:
            CacheLineSize=~(64-1);
            break;
         case 2:
         case 3:
            CacheLineSize=~(128-1);
            break;
        default:
            //printf("Chip_L2_cache_wback_inv Failed: Unknown cache line size:%x \n"  , CacheLineSize);
            return;
            break;
        }
    }

    if( (addr > 0x40000000) || (size == 0) )
    {
        _chip_flush_miu_pipe();
        return;
    }

    // TODO: U01 only
    size = 0x20000;

    // L2 disabled
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        _chip_flush_miu_pipe();
        spin_unlock_irq(&l2prefetch_lock);
    }
    else if( size >= 0x20000 )
    {
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x4; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x3; // H41 all
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(10);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = 0; // H41
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        // invalid all
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4); // H41
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(8);//all
        }while(temp == 0);
        // ^JL^ necessary read
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMBER2)

    volatile unsigned int temp=0;
    static unsigned int CacheLineSize=0;
    if( !CacheLineSize )
    {
        CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(5)|_BIT(6)))>>5;  // H40 L2 cache line size 00: 64-bytes    01: 128-bytes    1x: 256-bytes
        //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
        switch(CacheLineSize  )
        {
         case 0:
            CacheLineSize=~(64-1);
            break;
         case 1:
            CacheLineSize=~(128-1);
            break;
         case 2:
         case 3:
            CacheLineSize=~(256-1);
            break;
        default:
            //printf("Chip_L2_cache_wback_inv Failed: Unknown cache line size:%x \n"  , CacheLineSize);
            return;
            break;
        }
    }

    if( (addr > 0x40000000) || (size == 0) )
    {
        _chip_flush_miu_pipe();
        return;
    }

    // TODO: U01 only
    size = 0x20000;

    // L2 disabled
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        _chip_flush_miu_pipe();
        spin_unlock_irq(&l2prefetch_lock);
    }
    else if( size >= 0x20000 )
    {
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf203104) = ((*(volatile unsigned int *)(0xBF203104) & 0xFFF0) | 0x0004);  //mode 4:Flush all and invalid cache
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf203104) = ((*(volatile unsigned int *)(0xBF203104) & 0xFFE0) | 0x0014);  //mode 4:Fire
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x20317C);
            temp &= _BIT(10);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf203104) = ((*(volatile unsigned int *)(0xBF203104) & 0xFFF0) | 0x0000);  //mode 0:Initial all invalid
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf203104) = ((*(volatile unsigned int *)(0xBF203104) & 0xFFE0) | 0x0010);  //mode 0:Fire
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(8);//all
        }while(temp == 0);
        // ^JL^ necessary read
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_TITANIA9) || defined(CONFIG_TITANIA13)

    volatile unsigned int temp=0;
    if( (*(volatile unsigned int *)(0xbf000000+0x203100)) & _BIT(1) )  // H40
    {
    // L2 disabled
        // flush pipe
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x2; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x2; // H41 all

        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(9);//pipe
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }
    else
    {
    // L2 enabled
        // flush all and keep valid
        spin_lock_irq(&l2prefetch_lock);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x2; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x2; // H41 all
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(9);//pipe
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) =  0x0; // H41 all
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        *(volatile unsigned int *)(0xbf000000+0x203104) = _BIT(4) | 0x0; // H41 all
        do
        {
            temp = *(volatile unsigned int *)(0xbf000000+0x203104);
            temp &= _BIT(8);//all
        }while(temp == 0);
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMBER1) || defined(CONFIG_AMBER6) || defined(CONFIG_AMBER7) || defined(CONFIG_EMERALD)

    unsigned int    dwReadData = 0;

    if(((*(volatile unsigned int *)(0xbf203100)) & _BIT(1)) != 0)
    {
        _chip_flush_miu_pipe();
    }
    else
    {
        spin_lock_irq(&l2prefetch_lock);
        dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
        *(volatile unsigned int *)(0xbf203104) = 0x04;          //Flush All and Keep Valid
        dwReadData = *(volatile unsigned int *)(0xbf201600);    //Dummy Read
        *(volatile unsigned int *)(0xbf203104) = 0x14;

        do
        {
            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData &= _BIT(10);

        } while(dwReadData == 0);

        dwReadData = *(volatile unsigned int *)(0xbf201600);   //Dummy Read
        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_JANUS2)|| defined(CONFIG_AMBER5)

    unsigned int    dwTempData = 0;

    if(dwCacheLineSize == 0)
    {
        //Read Bank 0x101840[6:5] to get cache line size
        dwCacheLineSize = (*(volatile unsigned int *)(0xbf203100));
        dwCacheLineSize &= (_BIT(5) | _BIT(6));
        dwCacheLineSize >>= 5;

        switch(dwCacheLineSize)
        {
            case 0:
            {
                printf("[INFO] Cache Line Size: 64 Bytes\n");
                dwCacheLineSize = ~(64-1);
            }
            break;

            case 1:
            {
                printf("[INFO] Cache Line Size: 128 Bytes\n");
                dwCacheLineSize = ~(128-1);
            }
            break;

            case 2:
            {
                printf("[INFO] Cache Line Size: 256 Bytes\n");
                dwCacheLineSize = ~(256-1);
            }
            break;

            default:
            {
                printf("[INFO] Cache Line Size: Invalid\n");
                dwCacheLineSize = 0;
                return;
            }
            break;
        }
    }

    if(addr > 0x40000000)
    {
        printf("[ERROR] Out of Range\n");
        return;
    }

    if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
    {
        //L2 Cache Disable
        spin_lock_irq(&l2prefetch_lock);

        //Flush Pipe Data
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x02;     //Flush Pipe Data
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf20317c);
            dwTempData &= _BIT(9);  //Check Status of Flush Pipe Finish

        } while(dwTempData == 0);

        spin_unlock_irq(&l2prefetch_lock);

    }
    else //if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) == 0)
    {
        spin_lock_irq(&l2prefetch_lock);

        //Flush All and Invalid
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x04;     //Flush All and Invalid
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf20317c);
            dwTempData &= _BIT(10);  //Check Status of Flush All Finish

        } while(dwTempData == 0);

        spin_unlock_irq(&l2prefetch_lock);
    }

#elif defined(CONFIG_AMETHYST) || \
      defined(CONFIG_NUGGET) || \
      defined(CONFIG_NIKON) || \
      defined(CONFIG_MILAN)

    unsigned int    dwReadData = 0;

    if(addr > 0x40000000)
    {
        printf("[ERROR] Out of Range\n");
    }
    else
    {
        if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
        {
            _chip_flush_miu_pipe();
        }
        else
        {
            spin_lock_irq(&l2prefetch_lock);

            //Flush All and Invalid
            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData &= ~(0x1F);
            dwReadData |= 0x04;     //Flush All and Invalid
            *(volatile unsigned int *)(0xbf203104) = dwReadData;

            dwReadData = *(volatile unsigned int *)(0xbf203104);
            dwReadData |= _BIT(4);
            *(volatile unsigned int *)(0xbf203104) = dwReadData;

            do
            {
                dwReadData = *(volatile unsigned int *)(0xbf20317c);
                dwReadData &= _BIT(10);  //Check Status of Flush All Finish

            } while(dwReadData == 0);

            spin_unlock_irq(&l2prefetch_lock);
        }
    }

#elif defined(CONFIG_KAISERIN) || \
	  defined(CONFIG_KENYA)    || \
	  defined(CONFIG_KRITI)    || \
	  defined(CONFIG_KERES)    || \
      defined(CONFIG_KRIS)


    volatile unsigned int dwTempData=0;
    static unsigned int CacheLineSize=0;

    if( !CacheLineSize )
    {
        CacheLineSize=((*(volatile unsigned int *)(0xbf000000+0x203100))&(_BIT(4)|_BIT(5)))>>4;  // H40 L2 cache line size 00: 32-bytes    01: 64-bytes    1x: 128-bytes
        //printf("Read_Memory_Range: %lx \n"  , CacheLineSize);
        switch(CacheLineSize  )
        {
         case 0:
            CacheLineSize=~(32-1);
            break;
         case 1:
            CacheLineSize=~(64-1);
            break;
         case 2:
         case 3:
            CacheLineSize=~(128-1);
            break;
        default:
            //printf("Chip_L2_cache_wback_inv Failed: Unknown cache line size:%x \n"  , CacheLineSize);
            return;
            break;
        }
    }


    if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) != 0)
    {
        //L2 Cache Disable
        spin_lock_irq(&l2prefetch_lock);

        //Flush Pipe Data
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x02;     //Flush Pipe Data
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= _BIT(9);  //Check Status of Flush Pipe Finish

        } while(dwTempData == 0);

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        spin_unlock_irq(&l2prefetch_lock);

    }
    else //if(((*(volatile unsigned int *)(0xbf203100)) & BIT1) == 0)
    {
        spin_lock_irq(&l2prefetch_lock);

        //Flush All and Invalid
        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData |= 0x04;     //Flush All and Invalid
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData |= _BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        do
        {
            dwTempData = *(volatile unsigned int *)(0xbf203104);
            dwTempData &= _BIT(10);  //Check Status of Flush All Finish

        } while(dwTempData == 0);

        dwTempData = *(volatile unsigned int *)(0xbf203104);
        dwTempData &= ~(0x0F);
        dwTempData &= ~_BIT(4);
        *(volatile unsigned int *)(0xbf203104) = dwTempData;

        spin_unlock_irq(&l2prefetch_lock);
    }

#endif

    // flush MIU pipe
    _chip_flush_miu_pipe();

    return;
}

void Chip_Flush_Memory_Range(unsigned long pAddress , unsigned long  size)
{
#if defined(CONFIG_TITANIA8) || \
    defined(CONFIG_TITANIA12) || \
    defined(CONFIG_AMBER2) || \
    defined(CONFIG_AMBER5) || \
    defined(CONFIG_TITANIA9) || \
    defined(CONFIG_JANUS2) || \
    defined(CONFIG_TITANIA13) || \
    defined(CONFIG_AMBER1) || \
    defined(CONFIG_AMBER6) || \
    defined(CONFIG_AMBER7) || \
    defined(CONFIG_AMETHYST) || \
    defined(CONFIG_EMERALD) || \
    defined(CONFIG_NUGGET) || \
    defined(CONFIG_NIKON)  || \
    defined(CONFIG_KENYA)  || \
    defined(CONFIG_KRITI)  || \
    defined(CONFIG_KERES)  || \
    defined(CONFIG_KRIS)
    

    volatile unsigned int temp = 0;
    if(*(volatile unsigned int*)(0xbf203100) & _BIT(2))
    {
        temp = *(volatile unsigned int *)(0xbf201600) ; // dummy read
        Chip_L2_cache_wback( pAddress , size );
    }
    else
    {
        temp = *(volatile unsigned int *)(0xbf201600) ; // dummy read
        // flush MIU pipe
        _chip_flush_miu_pipe();
    }
#endif

#if defined(CONFIG_KAISERIN)
    volatile unsigned int temp = 0;
    temp = *(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
    Chip_L2_cache_wback(pAddress , size);
#endif

#if defined(CONFIG_KRONUS) //FIXME!!
    // kronus_mips_L2_cache_reg.xls
    if((*(volatile unsigned int *)(0xBF203104) & 0x0100) != 0)
    {
        // @FIXME: the chiptop dummy reead should be turn off since HW should fix this in T12/T13
        *(volatile unsigned int *) (0xBF003C00);        //Dummy Read
        *(volatile unsigned int *) 0xBF203104 = 0x04;
        // @FIXME: the chiptop dummy reead should be turn off since HW should fix this in T12/T13
        *(volatile unsigned int *) (0xBF003C00);        //Dummy Read
        *(volatile unsigned int *) 0xBF203104 = 0x14;
        while(1)
        {
            // @FIXME: the chiptop dummy reead should be turn off since HW should fix this in T12/T13
            *(volatile unsigned int *) (0xBF003C00);    //Dummy Read
            if((*(volatile unsigned int *)(0xBF203104) & 0x0400) != 0)
            {
                break;
            }
        }
    }
#endif
}
void Chip_Read_Memory_Range(unsigned long pAddress , unsigned long  size)
{
#if defined(CONFIG_TITANIA8) || \
    defined(CONFIG_TITANIA12) || \
    defined(CONFIG_AMBER2) || \
    defined(CONFIG_TITANIA9) || \
    defined(CONFIG_TITANIA13) || \
    defined(CONFIG_AMBER1) || \
    defined(CONFIG_AMBER6) || \
    defined(CONFIG_AMBER7) || \
    defined(CONFIG_EMERALD)

    volatile unsigned int temp=0;
    if( *(volatile unsigned int*)(0xbf000000+0x203100) & _BIT(2)  )
    {
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        Chip_L2_cache_inv( pAddress , size );
    }
    else
    {
        temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
        // flush MIU pipe
        _chip_flush_miu_pipe();
    }

#elif defined(CONFIG_JANUS2)|| \
      defined(CONFIG_AMBER5) || \
      defined(CONFIG_AMETHYST) || \
      defined(CONFIG_NUGGET) || \
      defined(CONFIG_NIKON) || \
      defined(CONFIG_MILAN)


    if(*(volatile unsigned int*)(0xbf203100) & _BIT(2))
    {
        Chip_L2_cache_inv( pAddress , size );
    }
    else
    {
        // flush MIU pipe
        _chip_flush_miu_pipe();
    }

#elif defined(CONFIG_KAISERIN) || \
	  defined(CONFIG_KENYA)  || \
	  defined(CONFIG_KRITI)  || \
	  defined(CONFIG_KERES)  || \
      defined(CONFIG_KRIS)
    volatile unsigned int temp=0;
    temp=*(volatile unsigned int *)(0xbf000000+0x201600) ; // dummy read
    Chip_L2_cache_inv( pAddress , size );

#else
	volatile unsigned int *pu8;
    volatile unsigned int t ;

    // Transfer the memory to noncache memory
    pu8 = ((volatile unsigned int *)0xA0380000);
    t = pu8[0] ;
    t = pu8[64] ;

#endif

}
void Chip_Read_Memory(void)
{
	Chip_Read_Memory_Range(0, 0x8000); //32KB
}
void Chip_Flush_Memory(void)
{
	Chip_Flush_Memory_Range(0, 0xFFFFFFFF);
}

#if 1 // for i cache flush, d cache flush
#include <asm/system.h>
#define CKSEG0 0x80000000
#define INDEX_BASE CKSEG0


// From kernel hazards.h start
/*
 * TLB hazards
 */
#if 1 // defined(CONFIG_CPU_MIPSR2)

#ifdef __ASSEMBLY__
#define ASMMACRO(name, code...) .macro name; code; .endm
#else

//#include <asm/cpu-features.h>

#define ASMMACRO(name, code...) \
__asm__(".macro " #name "; " #code "; .endm"); \
 \
static inline void name(void) \
{ \
 __asm__ __volatile__ (#name); \
}

/*
 * MIPS R2 instruction hazard barrier.   Needs to be called as a subroutine.
 */
extern void mips_ihb(void);

#endif

/*
 * MIPSR2 defines ehb for hazard avoidance
 */

ASMMACRO(mtc0_tlbw_hazard,
        _ehb
    )
ASMMACRO(tlbw_use_hazard,
        _ehb
    )
ASMMACRO(tlb_probe_hazard,
        _ehb
    )
ASMMACRO(irq_enable_hazard,
        _ehb
    )
ASMMACRO(irq_disable_hazard,
        _ehb
    )
ASMMACRO(back_to_back_c0_hazard,
        _ehb
    )
/*
 * gcc has a tradition of misscompiling the previous construct using the
 * address of a label as argument to inline assembler.  Gas otoh has the
 * annoying difference between la and dla which are only usable for 32-bit
 * rsp. 64-bit code, so can't be used without conditional compilation.
 * The alterantive is switching the assembler to 64-bit code which happens
 * to work right even for 32-bit code ...
 */
#define instruction_hazard() \
do { \
 unsigned long tmp; \
 \
    __asm__ __volatile__( \
    " .set mips64r2 \n" \
    " dla %0, 1f \n" \
    " jr.hb %0 \n" \
    " .set mips0 \n" \
    "1: \n" \
    : "=r" (tmp)); \
} while (0)
#endif
// From kernel hazards.h end

// From kernel cacheops.h start


/*
 * SMTC Linux requires shutting-down microthread scheduling
 * during CP0 register read-modify-write sequences.
 */
#define __BUILD_SET_C0(name) \
static inline unsigned int \
set_c0_##name(unsigned int set) \
{ \
    unsigned int res; \
    \
    res = read_c0_##name(); \
    res |= set; \
    write_c0_##name(res); \
    \
    return res; \
} \
 \
static inline unsigned int \
clear_c0_##name(unsigned int clear) \
{ \
    unsigned int res; \
    \
    res = read_c0_##name(); \
    res &= ~clear; \
    write_c0_##name(res); \
    \
    return res; \
} \
 \
static inline unsigned int \
change_c0_##name(unsigned int change, unsigned int new) \
{ \
    unsigned int res; \
    \
    res = read_c0_##name(); \
    res &= ~change; \
    res |= (new & change); \
    write_c0_##name(res); \
    \
    return res; \
}
// From kernel mipsregs.h end

// From kernel mipsmtregs.h start
#define MVPCONTROL_EVP  (_ULCAST_(1))

#ifndef __ASSEMBLY__

static inline unsigned int dvpe(void);
static inline unsigned int dvpe(void)
{
    int res = 0;

    __asm__ __volatile__(
    " .set push \n"
    " .set noreorder \n"
    " .set noat \n"
    " .set mips32r2 \n"
    " .word 0x41610001 # dvpe $1 \n"
    " move %0, $1 \n"
    " ehb \n"
    " .set pop \n"
    : "=r" (res));

    instruction_hazard();

    return res;
}

static inline void __raw_evpe(void);
static inline void __raw_evpe(void)
{
    __asm__ __volatile__(
    "   .set push \n"
    "   .set noreorder \n"
    "   .set noat \n"
    "   .set mips32r2 \n"
    "   .word 0x41600021 # evpe \n"
    "   ehb \n"
    "   .set pop \n");
}

/* Enable virtual processor execution if previous suggested it should be.
   EVPE_ENABLE to force */

#define EVPE_ENABLE MVPCONTROL_EVP

static inline void evpe(int previous);
static inline void evpe(int previous)
{
    if ((previous & MVPCONTROL_EVP))
        __raw_evpe();
}

static inline unsigned int dmt(void);
static inline unsigned int dmt(void)
{
    int res;

    __asm__ __volatile__(
    "   .set    push \n"
    "   .set    mips32r2 \n"
    "   .set    noat \n"
    "   .word   0x41610BC1 # dmt $1 \n"
    "   ehb \n"
    "   move    %0, $1 \n"
    "   .set    pop \n"
    : "=r" (res));

    instruction_hazard();

    return res;
}

static inline void __raw_emt(void);
static inline void __raw_emt(void)
{
    __asm__ __volatile__(
    " .set  noreorder \n"
    " .set  mips32r2 \n"
    " .word 0x41600be1 # emt\n"
    " ehb \n"
    " .set  mips0 \n"
    " .set  reorder");
}

static inline void ehb(void);
static inline void ehb(void)
{
__asm__ __volatile__(
"   .set    mips32r2    \n"
"   ehb \n"
"   .set    mips0   \n");
}

#define mftc0(rt,sel) \
({ \
     unsigned long  __res; \
     \
    __asm__ __volatile__( \
    " .set push \n" \
    " .set mips32r2 \n" \
    " .set noat \n" \
    " # mftc0 $1, $" #rt ", " #sel " \n" \
    " .word 0x41000800 | (" #rt " << 16) | " #sel " \n" \
    " move %0, $1 \n" \
    " .set pop \n" \
    : "=r" (__res)); \
     \
    __res; \
})

#define mftgpr(rt) \
({ \
    unsigned long __res; \
     \
    __asm__ __volatile__( \
    " .set push  n" \
    " .set noat \n" \
    " .set mips32r2 \n" \
    " # mftgpr $1," #rt " \n" \
    " .word 0x41000820 | (" #rt " << 16) \n" \
    " move %0, $1 \n" \
    " .set pop \n" \
    : "=r" (__res));\
     \
    __res; \
})

#define mftr(rt, u, sel) \
({ \
    unsigned long __res; \
         \
 __asm__ __volatile__(      \
 " mftr %0, " #rt ", " #u ", " #sel "  \n" \
 : "=r" (__res));      \
         \
 __res;        \
})

#define mttgpr(rd,v)       \
do {         \
 __asm__ __volatile__(      \
 " .set push     \n" \
 " .set mips32r2    \n" \
 " .set noat     \n" \
 " move $1, %0     \n" \
 " # mttgpr $1, " #rd "    \n" \
 " .word 0x41810020 | (" #rd " << 11)  \n" \
 " .set pop     \n" \
 : : "r" (v));       \
} while (0)

#define mttc0(rd, sel, v)       \
({         \
 __asm__ __volatile__(      \
 " .set push     \n" \
 " .set mips32r2    \n" \
 " .set noat     \n" \
 " move $1, %0     \n" \
 " # mttc0 %0," #rd ", " #sel "   \n" \
 " .word 0x41810000 | (" #rd " << 11) | " #sel " \n" \
 " .set pop     \n" \
 :        \
 : "r" (v));       \
})


#define mttr(rd, u, sel, v)      \
({         \
 __asm__ __volatile__(      \
 "mttr %0," #rd ", " #u ", " #sel    \
 : : "r" (v));       \
})


#define settc(tc)       \
do {         \
 write_c0_vpecontrol((read_c0_vpecontrol()&~VPECONTROL_TARGTC) | (tc)); \
 ehb();        \
} while (0)


/* you *must* set the target tc (settc) before trying to use these */
#define read_vpe_c0_vpecontrol() mftc0(1, 1)
#define write_vpe_c0_vpecontrol(val) mttc0(1, 1, val)
#define read_vpe_c0_vpeconf0()  mftc0(1, 2)
#define write_vpe_c0_vpeconf0(val) mttc0(1, 2, val)
#define read_vpe_c0_count()  mftc0(9, 0)
#define write_vpe_c0_count(val)  mttc0(9, 0, val)
#define read_vpe_c0_status()  mftc0(12, 0)
#define write_vpe_c0_status(val) mttc0(12, 0, val)
#define read_vpe_c0_cause()  mftc0(13, 0)
#define write_vpe_c0_cause(val)  mttc0(13, 0, val)
#define read_vpe_c0_config()  mftc0(16, 0)
#define write_vpe_c0_config(val) mttc0(16, 0, val)
#define read_vpe_c0_config1()  mftc0(16, 1)
#define write_vpe_c0_config1(val) mttc0(16, 1, val)
#define read_vpe_c0_config7()  mftc0(16, 7)
#define write_vpe_c0_config7(val) mttc0(16, 7, val)
#define read_vpe_c0_ebase()  mftc0(15, 1)
#define write_vpe_c0_ebase(val)  mttc0(15, 1, val)
#define write_vpe_c0_compare(val) mttc0(11, 0, val)
#define read_vpe_c0_badvaddr()  mftc0(8, 0)
#define read_vpe_c0_epc()  mftc0(14, 0)
#define write_vpe_c0_epc(val)  mttc0(14, 0, val)


/* TC */
#define read_tc_c0_tcstatus()  mftc0(2, 1)
#define write_tc_c0_tcstatus(val) mttc0(2, 1, val)
#define read_tc_c0_tcbind()  mftc0(2, 2)
#define write_tc_c0_tcbind(val)  mttc0(2, 2, val)
#define read_tc_c0_tcrestart()  mftc0(2, 3)
#define write_tc_c0_tcrestart(val) mttc0(2, 3, val)
#define read_tc_c0_tchalt()  mftc0(2, 4)
#define write_tc_c0_tchalt(val)  mttc0(2, 4, val)
#define read_tc_c0_tccontext()  mftc0(2, 5)
#define write_tc_c0_tccontext(val) mttc0(2, 5, val)

/* GPR */
#define read_tc_gpr_sp()  mftgpr(29)
#define write_tc_gpr_sp(val)  mttgpr(29, val)
#define read_tc_gpr_gp()  mftgpr(28)
#define write_tc_gpr_gp(val)  mttgpr(28, val)

//__BUILD_SET_C0(mvpcontrol)

#endif /* Not __ASSEMBLY__ */

// From kernel mipsmtregs.h end

// From kernel mips-mt.c start
void mt_cflush_lockdown(void);
void mt_cflush_lockdown(void)
{
#ifdef CONFIG_MIPS_MT_SMTC
 void smtc_cflush_lockdown(void);

 smtc_cflush_lockdown();
#endif /* CONFIG_MIPS_MT_SMTC */
 /* FILL IN VSMP and AP/SP VERSIONS HERE */
}

void mt_cflush_release(void);
void mt_cflush_release(void)
{
#ifdef CONFIG_MIPS_MT_SMTC
 void smtc_cflush_release(void);

 smtc_cflush_release();
#endif /* CONFIG_MIPS_MT_SMTC */
 /* FILL IN VSMP and AP/SP VERSIONS HERE */
}
// From kernel mips-mt.c end

// From kernel r4kcache.h start
#define PROTECT_CACHE_FLUSHES 1

#ifdef PROTECT_CACHE_FLUSHES

int mt_protiflush = 0;
int mt_protdflush = 0;
int mt_n_iflushes = 1;
int mt_n_dflushes = 1;

//extern int mt_protiflush;
//extern int mt_protdflush;
//extern void mt_cflush_lockdown(void);
//extern void mt_cflush_release(void);

#define BEGIN_MT_IPROT \
 unsigned long flags = 0;   \
 unsigned long mtflags = 0;   \
 if(mt_protiflush) {    \
  local_irq_save(flags);   \
  ehb();     \
  mtflags = dvpe();   \
  mt_cflush_lockdown();   \
 }

#define END_MT_IPROT \
 if(mt_protiflush) {    \
  mt_cflush_release();   \
  evpe(mtflags);    \
  local_irq_restore(flags);  \
 }

#define BEGIN_MT_DPROT \
 unsigned long flags = 0;   \
 unsigned long mtflags = 0;   \
 if(mt_protdflush) {    \
  local_irq_save(flags);   \
  ehb();     \
  mtflags = dvpe();   \
  mt_cflush_lockdown();   \
 }

#define END_MT_DPROT \
 if(mt_protdflush) {    \
  mt_cflush_release();   \
  evpe(mtflags);    \
  local_irq_restore(flags);  \
 }

#else

#define BEGIN_MT_IPROT
#define BEGIN_MT_DPROT
#define END_MT_IPROT
#define END_MT_DPROT

#endif /* PROTECT_CACHE_FLUSHES */

#define __iflush_prologue      \
 unsigned long redundance;     \
 extern int mt_n_iflushes;     \
 BEGIN_MT_IPROT       \
 for (redundance = 0; redundance < mt_n_iflushes; redundance++) {

#define __iflush_epilogue      \
 END_MT_IPROT       \
 }

#define __dflush_prologue      \
 unsigned long redundance;     \
 extern int mt_n_dflushes;     \
 BEGIN_MT_DPROT       \
 for (redundance = 0; redundance < mt_n_dflushes; redundance++) {

#define __dflush_epilogue \
 END_MT_DPROT  \
 }

#define cache32_unroll32(base,op)     \
 __asm__ __volatile__(      \
 " .set push     \n" \
 " .set noreorder     \n" \
 " .set mips3     \n" \
 " cache %1, 0x000(%0); cache %1, 0x020(%0) \n" \
 " cache %1, 0x040(%0); cache %1, 0x060(%0) \n" \
 " cache %1, 0x080(%0); cache %1, 0x0a0(%0) \n" \
 " cache %1, 0x0c0(%0); cache %1, 0x0e0(%0) \n" \
 " cache %1, 0x100(%0); cache %1, 0x120(%0) \n" \
 " cache %1, 0x140(%0); cache %1, 0x160(%0) \n" \
 " cache %1, 0x180(%0); cache %1, 0x1a0(%0) \n" \
 " cache %1, 0x1c0(%0); cache %1, 0x1e0(%0) \n" \
 " cache %1, 0x200(%0); cache %1, 0x220(%0) \n" \
 " cache %1, 0x240(%0); cache %1, 0x260(%0) \n" \
 " cache %1, 0x280(%0); cache %1, 0x2a0(%0) \n" \
 " cache %1, 0x2c0(%0); cache %1, 0x2e0(%0) \n" \
 " cache %1, 0x300(%0); cache %1, 0x320(%0) \n" \
 " cache %1, 0x340(%0); cache %1, 0x360(%0) \n" \
 " cache %1, 0x380(%0); cache %1, 0x3a0(%0) \n" \
 " cache %1, 0x3c0(%0); cache %1, 0x3e0(%0) \n" \
 " .set pop     \n" \
  :       \
  : "r" (base),      \
    "i" (op));


// TODO: check waysize: 8192
// TODO: check waybit: 13
// TODO: check ways: 4
#define __BUILD_BLAST_CACHE(pfx, desc, indexop, hitop, lsize) \
inline void blast_##pfx##cache##lsize(void)                            \
{                                                                                               \
           unsigned long start = INDEX_BASE;                                         \
           unsigned long end = start + 8192;        \
           unsigned long ws_inc = 1UL << 13;   \
           unsigned long ws_end = 4 <<             \
                                  13;                  \
           unsigned long ws, addr;                                                               \
                                                                                                \
           __##pfx##flush_prologue                                                            \
                                                                                                \
           for (ws = 0; ws < ws_end; ws += ws_inc)                                 \
                     for (addr = start; addr < end; addr += lsize * 32) \
                                cache##lsize##_unroll32(addr|ws, indexop);     \
                                                                                                \
           __##pfx##flush_epilogue                                                            \
}

__BUILD_BLAST_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 32)
__BUILD_BLAST_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D, 32)
// From kernel r4kcache.h end
#endif // for i cache flush, d cache flush

#endif //__MIPS__
