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

/*
 * SPI Read/Write Utilities
 */

#include <common.h>
#include <command.h>
#include <exports.h>
#include <spi.h>
// MSTAR start
#include <drvSERFLASH.h>
#include <MsDebug.h>
#include <MsApiSpi.h>
#if (ENABLE_BOOT_SPI_ECOS)
#include <drvBDMA.h>
#endif
// MSTAR end

/*-----------------------------------------------------------------------
 * Definitions
 */

#ifndef MAX_SPI_BYTES
#if 1 // MSTAR
#define MAX_SPI_BYTES 0x1000    /* Maximum number of bytes we can handle */
#else
#   define MAX_SPI_BYTES 32	/* Maximum number of bytes we can handle */
#endif
#endif

#ifndef CONFIG_DEFAULT_SPI_BUS
#   define CONFIG_DEFAULT_SPI_BUS	0
#endif
#ifndef CONFIG_DEFAULT_SPI_MODE
#   define CONFIG_DEFAULT_SPI_MODE	SPI_MODE_0
#endif

#if 1 // MSTAR
#define READ_ID_LENGTH 3

//input total char
#define BASE_CMD_INPUT_LEN             6
#define INIT_INPUT_LEN                 1
#define READ_ID_INPUT_LEN              1
#define READ_INPUT_LEN                 3
#define WRITE_INPUT_LEN                3
#define ERASE_CHIP_INPUT_LEN           1
#define ERASE_SEC_INPUT_LEN            3
#define WRITE_PRO_INPUT_LEN            2
#define WRITE_PRO_BOUND_INPUT_LEN      1
#define WRITE_BLK_PRO_INPUT_LEN        3
#define WRITE_BUFF_INPUT_LEN           3
#define READ_BUFF_INPUT_LEN            3
#define GET_CHIP_REV_INPUT_LEN         1
#define GET_FLASH_INFO_INPUT_LEN       1
#define READ_STATUS_INPUT_LEN          1
#define DMA_INPUT_LEN                  4
#define READ_CODE_INPUT_LEN            4
#define WRITE_CODE_INPUT_LEN           4
#define WRITE_PARTITION_INPUT_LEN      5
#define READ_PARTITION_INPUT_LEN       5
#define CREATE_PARTITION_INPUT_LEN     3
#define REMOVE_PARTITION_INPUT_LEN     2
#define ERASE_PARTITION_INPUT_LEN      2
#define RMGPT_INPUT_LEN 1


#define SERFLASH_PAGE_SIZE   (4*1024)
#define SERFLASH_BLOCK_SIZE (64 * 1024) // <-@@@ please sync with SERFLASH_BLOCK_SIZE @ spiflash.c



uchar ubuffer[MAX_SPI_BYTES];//uint *wbuffer;//uchar *ubuffer;//
const SERFLASH_Info *pFlashInfo;
static uchar spiInitFlag = 0;

int _spi_rdc(unsigned int dram_addr,unsigned int flash_addr, unsigned int len);
int _spi_wrc(unsigned int dram_addr,unsigned int flash_addr, unsigned int len);



static inline int str2long_nor(char *p, unsigned int *num)
{
	char *endptr;

	*num = simple_strtoul(p, &endptr, 16);
	return (*p != '\0' && *endptr == '\0') ? 1 : 0;
}

static int arg_off_size_nor(int argc, char * const argv[], unsigned int *off, unsigned int *size)
{
#if (CONFIG_COMMANDS & CFG_CMD_JFFS2) && defined(CONFIG_JFFS2_CMDLINE)
	struct mtd_device *dev;
	struct part_info *part;
	u8 pnum;

	if (argc >= 1 && !(str2long_nor(argv[0], off))) {
		if ((mtdparts_init() == 0) &&
		    (find_dev_and_part(argv[0], &dev, &pnum, &part) == 0)) {
			if (dev->id->type != MTD_DEV_TYPE_NOR) {
				puts("not a NOR device\n");
				return -1;
			}
			*off = part->offset;
			if (argc >= 2) {
				if (!(str2long_nor(argv[1], size))) {
					printf("'%s' is not a number\n", argv[1]);
					return -1;
				}
			} else {
				*size = part->size;
			}

			goto out;
		}
	}
#endif

	if (argc >= 1) {
		if (!(str2long_nor(argv[0], off))) {
			printf("'%s' is not a number\n", argv[0]);
			return -1;
		}
	} else {
		*off = 0;
	}

	if (argc >= 2) {
		if (!(str2long_nor(argv[1], size))) {
			printf("'%s' is not a number\n", argv[1]);
			return -1;
		}
	} else {
	       pFlashInfo = MDrv_SERFLASH_GetInfo();
		*size = pFlashInfo->u32TotalSize - *off;
	}

#if (CONFIG_COMMANDS & CFG_CMD_JFFS2) && defined(CONFIG_JFFS2_CMDLINE)
out:
#endif

	printf("offset 0x%x, size 0x%x\n", *off, *size);
	return 0;
}

static int spi_flash_init(void)
{
    if(spiInitFlag == 0)
    {
       MDrv_SERFLASH_Init();
       spiInitFlag = 1;
       printf("initialization done!\n");
    }
    return 0;
}
/*
 * SPI init
 * Syntax
 * spi_init"
 */

int do_spi_init ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    return spi_flash_init();
}

int do_spi_get_Chip_Rev ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uchar uGetChipRev = 0;
    //TODO: uGetChipRev=MDrv_SERFLASH_GetChipRev();
    printf("Get Chip Rev:\t0x%02x\n", uGetChipRev);
    return 0;
}

int do_spi_get_flash_info ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    pFlashInfo = MDrv_SERFLASH_GetInfo();
    printf(" Section Num:\t0x%04x\n",   (unsigned int)pFlashInfo->u32SecNum);
    printf(" Section Size:\t0x%08x\n",  (unsigned int)pFlashInfo->u32SecSize);
    printf(" Total Size:\t0x%08x\n",    (unsigned int)pFlashInfo->u32TotalSize);
    printf(" Access Width:\t0x%02x\n",  (unsigned int)pFlashInfo->u32AccessWidth);
    return 0;
}

int do_spi_read_status ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uchar u8StatusReg1=0,u8StatusReg2=0;
    MDrv_SERFLASH_ReadStatusRegister(&u8StatusReg1);
    MDrv_SERFLASH_ReadStatusRegister2(&u8StatusReg2);
    printf(" StatusReg:\t0x%02X%02X\n", u8StatusReg2,u8StatusReg1);
    return 0;

}

int do_spi_write_status ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned short int u16StatusReg=0;
    if (argc<2)
    {
        printf ("Usage:spi_ws [value(16bits)]\n");
        return 1;
    }
    u16StatusReg=simple_strtoul(argv[1], NULL, 16);
    MDrv_SERFLASH_WriteStatusRegister(u16StatusReg);
    return 0;
}

int do_spi_dma ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

#if 1
    printf("DMA mode doesn't supported\n");
    return 1;
#else
    uint uflhaddr,udmaaddr;
    uint len;
#ifdef DMA_TEST
    uint idx;
    uchar buffer[MAX_SPI_BYTES];
#endif
    if ((argc < DMA_INPUT_LEN) || (argc > DMA_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    uflhaddr = simple_strtoul(argv[1], NULL, 16);
    udmaaddr = simple_strtoul(argv[2], NULL, 16);
    len      = simple_strtoul(argv[3], NULL, 16);

    printf ("SPI flash start addr:\t0x%4x\n",uflhaddr);
    printf ("SPI DMA start addr:\t0x%4x\n",udmaaddr);
    printf ("SPI DMA length:\t0x%4x\n",len);

    if (len > MAX_SPI_BYTES)
    {
        printf ("SPI DMA: length is out of range\n");
        return 1;
    }
#ifdef DMA_TEST
        //////DMA Test start
        for( idx=0; idx<len; idx++)
        {
            buffer[idx] = (uchar)idx;
        }
        MDrv_SERFLASH_Write(uflhaddr, len, buffer);

        flush_cache(udmaaddr,len);
        MDrv_SERFLASH_DMA (uflhaddr, udmaaddr, len);

        for( idx=0; idx<len; idx++)
        {
            if( *(volatile uchar *)( (uint)KSEG02KSEG1(udmaaddr)+idx ) != (uchar)idx )
            {
                printf ("SPI DMA fail!\n");
            }
        }
        printf ("SPI DMA compare pass!\n");
        //////DMA Test end
#else
        MDrv_SERFLASH_DMA (uflhaddr, udmaaddr, len);
        printf ("SPI DMA Done!\n");
#endif

    return 0;
#endif
}

int do_spi_readID( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uchar buffer[READ_ID_LENGTH];
    uint len;

    if ((argc < READ_ID_INPUT_LEN) || (argc > READ_ID_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    len = READ_ID_LENGTH;
    MDrv_SERFLASH_ReadID (buffer, len);

    printf("Manufacturer ID:\t0x%02X\n", buffer[0]);
    printf("Device ID:\t0x%02X 0x%02X\n", buffer[1], buffer[2]);

    return 0;
}

/*
 * SPI read
 * Syntax
 * spi_r ID(hex) addr(hex) len(hex)\n"
 */
int do_spi_read ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uint addr;
    uint len;
    uint idx;

    if ((argc < READ_INPUT_LEN) || (argc > READ_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    addr = simple_strtoul(argv[1], NULL, 16);
    len  = simple_strtoul(argv[2], NULL, 16);

    printf ("SPI read addr:0x%08x and len:0x%08x\n",addr,len);

    if (len > MAX_SPI_BYTES)
    {
        printf ("SPI read: length is out of range\n");
        return 1;
    }

    if(0!=MDrv_SERFLASH_Read ((uint)addr, len, ubuffer)){//uID
	    for(idx=0;idx<len;idx++)
	    {
	        if((idx%16)==0)
	        {
	            printf("[0x%08x~0x%08x]: ", (addr+idx), (addr+idx+15));
	        }

	        printf("%02X ", ubuffer[idx]);

	        if(((idx+1)%16)==0)
	        {
	            printf("\n");
	        }
	    }
    }
	else{
		printf("ERROR: SPI DMA fail !!!\n");
        return 1;
	}
    printf("Read SPI flash done!\n");

    return 0;
}

int do_spi_read_buff ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uint addr;
    uint len;
    uint idx;

    if ((argc < READ_BUFF_INPUT_LEN) || (argc > READ_BUFF_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    addr = simple_strtoul(argv[1], NULL, 16);
    len  = simple_strtoul(argv[2], NULL, 16);

    for(idx=0;idx<len;idx++)
    {
        if((idx%16)==0)
        {
            printf("[0x%08x~0x%08x]: ", (addr+idx), (addr+idx+15));
        }

        printf("%02X ",ubuffer[idx]);

        if(((idx+1)%16)==0)
        {
            printf("\n");
        }
    }
    printf("Read buffer done!\n");

    return 0;
}
int do_spi_write_protect_boundry ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
 #ifndef CONFIG_SECURE_SPI_PROTECT
    printf ("[%s] not support!!! \n",__FUNCTION__);
    return 1;
#else
    printf("spi_wpb (0x%08x) \n",MDrv_SERFLASH_WriteProtect_Area_Boundary());
    return 0;
#endif
}

int do_spi_block_write_protect ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#ifndef CONFIG_SECURE_SPI_PROTECT
    printf ("[%s] not support!!! \n",__FUNCTION__);
    return 1;
#else // wait new driver api
    uint protect_length;
    uint non_protect_length;
    if ((argc < WRITE_BLK_PRO_INPUT_LEN) || (argc > WRITE_BLK_PRO_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    const SERFLASH_Info *pSerialFlashInfo = MDrv_SERFLASH_GetInfo();    
    protect_length = simple_strtoul(argv[1], NULL, 16);
    non_protect_length = simple_strtoul(argv[2], NULL, 16);

    if( 0 == protect_length )
    {
        printf ("protect_length  == (%lu) no effect!!! \n",(MS_U32)protect_length);
        return 1;
    }
    
    if( (protect_length + non_protect_length) > pSerialFlashInfo->u32TotalSize )
    {
        printf ("protect_length + non_protect_length (%lu) > pSerialFlashInfo->u32TotalSize (%lu)\n",(protect_length + non_protect_length),pSerialFlashInfo->u32TotalSize);
        return 1;
    }
    
    printf(" Section Num:\t0x%04x\n",   (unsigned int)pSerialFlashInfo->u32SecNum);
    printf(" Section Size:\t0x%08x\n",  (unsigned int)pSerialFlashInfo->u32SecSize);
    printf(" Total Size:\t0x%08x\n",    (unsigned int)pSerialFlashInfo->u32TotalSize);
    printf(" Access Width:\t0x%02x\n",  (unsigned int)pSerialFlashInfo->u32AccessWidth);
    printf(" protect_length:\t%lu\n",        protect_length      );
    printf(" non_protect_length:\t%lu\n",    non_protect_length  );
    
    MS_U8 u8BlockProtectBits = 0xFF;

    if(FALSE == MDrv_SERFLASH_WriteProtect_Area_Lookup((MS_U32)protect_length, (MS_U32)non_protect_length, &u8BlockProtectBits))
    {
        printf ("spi_bwp : MDrv_SERFLASH_WriteProtect_Area_Lookup (0x%08x , 0x%08x) fail\n",protect_length, non_protect_length);
        return 1;
    }
    else if(FALSE == MDrv_SERFLASH_WriteProtect_Area(FALSE,u8BlockProtectBits))
    {
        printf ("spi_bwp : MDrv_SERFLASH_WriteProtect_Area (0x%02x) fail\n",u8BlockProtectBits);
        return 1;
        
    }
    else
    {
        printf("spi_bwp success : u8BlockProtectBits:\t(0x%02x)\n",u8BlockProtectBits);
        printf("spi_bwp success : MDrv_SERFLASH_WriteProtect_Area_Boundary (0x%08x) \n",MDrv_SERFLASH_WriteProtect_Area_Boundary());
    }
    return 0;
#endif
}

int do_spi_write_protect ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uchar uEnable;
    if ((argc < WRITE_PRO_INPUT_LEN) || (argc > WRITE_PRO_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    uEnable = simple_strtoul(argv[1], NULL, 16);

    if(MDrv_SERFLASH_WriteProtect(uEnable)==0)
    {
        printf ("SPI write protect fail\n");
    }
    else
    {
        printf ("SPI write protect pass\n");
    }

    return 0;
}

int  do_spi_write_buff ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uint addr;
    uint len;


    if ((argc < WRITE_BUFF_INPUT_LEN) || (argc > WRITE_BUFF_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    addr    = simple_strtoul(argv[1], NULL, 16);
    len     = simple_strtoul(argv[2], NULL, 16);

    if (len > MAX_SPI_BYTES)
    {
        printf ("SPI write: length is out of range\n");
        return 1;
    }
    
    memset(ubuffer,0,sizeof(ubuffer));
    memcpy(ubuffer,(char *)addr, len);
    

    return 0;
}

/*
 * SPI write
 */
int do_spi_write ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uint flash_addr;
    uint len;


    if ((argc < WRITE_INPUT_LEN) || (argc > WRITE_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    flash_addr    = simple_strtoul(argv[1], NULL, 16);
    len     = simple_strtoul(argv[2], NULL, 16);

    if (len > MAX_SPI_BYTES)
    {
        printf ("SPI write: length is out of range\n");
        return 1;
    }

   

    MDrv_SERFLASH_Write ((uint)flash_addr, len, (MS_U8 *)ubuffer);


    
    printf("write SPI flash done!\n");

    return 0;
}

int do_spi_erase_chip ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MDrv_SERFLASH_EraseChip ();

    return 0;
}

int do_spi_erase_block ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

#ifdef CONFIG_64BIT_TO_32BIT_MODE
    return 0;
#endif

    if ((argc < ERASE_SEC_INPUT_LEN) || (argc > ERASE_SEC_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    uint ustartAddr = simple_strtoul(argv[1], NULL, 16);
    uint uendAddr = simple_strtoul(argv[2], NULL, 16);

    if (ustartAddr > uendAddr)
    {
        printf("Start Addr > End Addr");
        return 1;
    }

    printf("ustartAddr = 0x%X, uendAddr = 0x%X\n", ustartAddr, uendAddr);
    return MDrv_SERFLASH_AddressErase (ustartAddr, uendAddr - ustartAddr, TRUE) ? 0 : -1;
}

int do_spi_erase_sector( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_64BIT_TO_32BIT_MODE
    return 0;
#endif

    if ((argc < ERASE_SEC_INPUT_LEN) || (argc > ERASE_SEC_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    extern MS_BOOL MDrv_SERFLASH_SectorErase(MS_U32 u32StartAddr, MS_U32 u32EndAddr);

    uint ustartAddr = simple_strtoul(argv[1], NULL, 16);
    uint uendAddr = simple_strtoul(argv[2], NULL, 16);

    if (ustartAddr > uendAddr)
    {
        printf("Start Addr > End Addr");
        return 1;
    }

    printf("ustartAddr = 0x%X, uendAddr = 0x%X\n", ustartAddr, uendAddr);
    return MDrv_SERFLASH_SectorErase (ustartAddr, uendAddr) ? 0 : -1;
}

int do_spi_rdc_partition (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    #define DRAM_ADDR argv[1]
    #define PARTITION_NAME argv[2]
    #define READ_OFFSET argv[3]
    #define READ_LEN argv[4]

    unsigned int dram_addr;
    unsigned int flash_addr;
    unsigned int roffset;
    unsigned int rlen;
    unsigned int partiton_offset=0;
    unsigned int partiton_size=0;    
    int ret=0;
    
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("DRAM_ADDR=%s\n",DRAM_ADDR);    
    UBOOT_DEBUG("PARTITION_NAME=%s\n",PARTITION_NAME);
    UBOOT_DEBUG("READ_OFFSET=%s\n",READ_OFFSET);    
    UBOOT_DEBUG("READ_LEN=%s\n",READ_LEN);    
    
    /* check argc */
    if (argc != READ_PARTITION_INPUT_LEN)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    rlen=simple_strtoul(READ_LEN,NULL,16);
    roffset=simple_strtoul(READ_OFFSET,NULL,16);    
    dram_addr = (0 == strncmp(DRAM_ADDR, UPGRADE_ADDR_STR, strlen(UPGRADE_ADDR_STR))) ? UPGRADE_BUFFER_ADDR : simple_strtoul(DRAM_ADDR, NULL, 16);
    ret=get_spi_partition_info(PARTITION_NAME,&partiton_offset,&partiton_size);

    if(ret!=0)
    {
        UBOOT_ERROR("get %s info fail\n",PARTITION_NAME);
        return -1;
    }

    if((roffset+rlen)>partiton_size)
    {
        UBOOT_ERROR("The read area is over this partition range\n");
        return -1;
    }
     
    flash_addr=roffset+partiton_offset;
     
    UBOOT_DEBUG("flash addr=0x%x\n",flash_addr);


    ret=_spi_rdc(dram_addr,flash_addr,rlen);
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("spi read fail\n");
    }
    return ret;

    #undef DRAM_ADDR 
    #undef PARTITION_NAME  
    #undef READ_OFFSET  
    #undef READ_LEN 
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}


int do_spi_rdc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int flash_addr;
    unsigned int dram_addr;
    unsigned int len=0;
    int ret=0;
    UBOOT_TRACE("IN\n");
    /* check argc */
    if (argc != READ_CODE_INPUT_LEN)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    arg_off_size_nor(argc - 2, argv + 2, &flash_addr, &len);
    //flash_addr = simple_strtoul(argv[2], NULL, 16);
	dram_addr = (0 == strncmp(argv[1], UPGRADE_ADDR_STR, strlen(UPGRADE_ADDR_STR))) ? UPGRADE_BUFFER_ADDR : simple_strtoul(argv[1], NULL, 16);

    ret=_spi_rdc(dram_addr,flash_addr,len);
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("spi read fail\n");
    }
    return ret;
}

int _spi_rdc(unsigned int dram_addr,unsigned int flash_addr, unsigned int len)
{
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("dram_addr=0x%x\n",dram_addr);
    UBOOT_DEBUG("flash_addr=0x%x\n",flash_addr);    
    UBOOT_DEBUG("len=0x%x\n",len);     

    /* check alignment and show warning*/
    if (flash_addr % SERFLASH_BLOCK_SIZE)
    {
        //printf("WARNING: it is better to set flash start addr aligned to %d !!!\n", SERFLASH_BLOCK_SIZE);
    }

    if (dram_addr % SERFLASH_BLOCK_SIZE)
    {
        //printf("WARNING: it is better to set dram start addr aligned to %d !!!\n", SERFLASH_BLOCK_SIZE);
    }

    if (len % SERFLASH_BLOCK_SIZE)
    {
        //printf("WARNING: it is better to set total length aligned to %d !!!\n", SERFLASH_BLOCK_SIZE);
    }
    
    
    /* init SPI flash first */
    if (0 == spiInitFlag)
    {
        spi_flash_init();
    }

#if (ENABLE_BOOT_SPI_ECOS)
    BDMA_Result ret;

    MDrv_BDMA_Init(0);
    ret = MDrv_BDMA_CopyHnd(flash_addr, dram_addr, len, E_BDMA_FLASH2SDRAM, 0x8);
	UBOOT_INFO("Start read %lx data from serial device... \n", len);
    if (ret != E_BDMA_OK)
    {
        UBOOT_ERROR("ERROR: BDMA fail and change to use spi load code!!!\n");
        /* read from flash to dram */
        if (0 == MDrv_SERFLASH_Read(flash_addr, len, (MS_U8 *)dram_addr))
        {
            UBOOT_ERROR("ERROR: SPI DMA fail !!!\n");
            return 1;
        }
        else
        {
            UBOOT_TRACE("OK\n");
            return 0;
        }
    }
    else
    {
        MsOS_Dcache_Flush(dram_addr, len);
        MsOS_FlushMemory();
        return 0;
    }
#else
    /* read from flash to dram */
    if (0 == MDrv_SERFLASH_Read(flash_addr, len, (MS_U8 *)dram_addr))
    {
        UBOOT_ERROR("ERROR: SPI DMA fail !!!\n");
        return 1;
    }
    else
    {
        UBOOT_TRACE("OK\n");        
        return 0;
    }
#endif
}
int do_spi_wrc_partition (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    #define DRAM_ADDR argv[1]
    #define PARTITION_NAME argv[2]
    #define WRITE_OFFSET argv[3]
    #define WRITE_LEN argv[4]
    
    unsigned int dram_addr;
    unsigned int flash_addr;
    unsigned int woffset;
    unsigned int wlen;
    unsigned int partiton_offset=0;
    unsigned int partiton_size=0;    
    int ret=0;
    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("DRAM_ADDR=%s\n",DRAM_ADDR);
    UBOOT_DEBUG("PARTITION_NAME=%s\n",PARTITION_NAME);
    UBOOT_DEBUG("WRITE_OFFSET=%s\n",WRITE_OFFSET);
    UBOOT_DEBUG("WRITE_LEN=%s\n",WRITE_LEN);
    
    /* check argc */
    if (argc != WRITE_PARTITION_INPUT_LEN)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    dram_addr = (0 == strncmp(DRAM_ADDR, UPGRADE_ADDR_STR, strlen(UPGRADE_ADDR_STR))) ? UPGRADE_BUFFER_ADDR : simple_strtoul(DRAM_ADDR, NULL, 16);
    wlen=simple_strtoul(WRITE_LEN,NULL,16);
    woffset=simple_strtoul(WRITE_OFFSET,NULL,16);    
    ret=get_spi_partition_info(PARTITION_NAME,&partiton_offset,&partiton_size);
    if(ret!=0)
    {
        UBOOT_ERROR("get %s info fail\n",PARTITION_NAME);
        return -1;
    }
    
    if((woffset+wlen)>partiton_size)
    {
        UBOOT_ERROR("The write area is over this partition range\n");
        return -1;
    }
    
    flash_addr=woffset+partiton_offset;
    UBOOT_DEBUG("flash addr=0x%x\n",flash_addr);
    ret=_spi_wrc(dram_addr,flash_addr,wlen);
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");    
    }
    else
    {
        UBOOT_ERROR("write partition fail\n");    
    }
    return ret;
    
    #undef DRAM_ADDR 
    #undef PARTITION_NAME  
    #undef WRITE_OFFSET  
    #undef WRITE_LEN 
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}


int do_spi_wrc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int dram_addr=0;
    unsigned int flash_addr=0;
    unsigned int len=0;
    int ret=0;
    UBOOT_TRACE("IN\n");


    /* check argc */
    if (argc != WRITE_CODE_INPUT_LEN)
    {
        UBOOT_ERROR("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    arg_off_size_nor(argc - 2, argv + 2, &flash_addr, &len);
	dram_addr = (0 == strncmp(argv[1], UPGRADE_ADDR_STR, strlen(UPGRADE_ADDR_STR))) ? UPGRADE_BUFFER_ADDR : simple_strtoul(argv[1], NULL, 16);

    ret=_spi_wrc(dram_addr,flash_addr,len);

    if(ret==0)
    {
        UBOOT_TRACE("OK\n");    
    }
    else
    {
        UBOOT_ERROR("write partition fail\n");    
    }
    return ret;
}

int _spi_wrc(unsigned int dram_addr,unsigned int flash_addr, unsigned int len)
{
    MS_U8 *dram_addr_for_verify=NULL;
    UBOOT_TRACE("IN\n");
    
    UBOOT_DEBUG("dram_addr=0x%x\n",dram_addr);
    UBOOT_DEBUG("flash_addr=0x%x\n",flash_addr);    
    UBOOT_DEBUG("len=0x%x\n",len);    
   
    /* init SPI flash first */
    if (0 == spiInitFlag)
    {
        spi_flash_init();
    }

    /* SPI erase */
    UBOOT_INFO("Erasing...\n");
    MDrv_SERFLASH_WriteProtect(FALSE);
    
    if(len>=0x10000) // a bank size is 64KBytes
    {
        UBOOT_INFO("block erase\n");
        if (0==MDrv_SERFLASH_AddressErase(flash_addr, len, TRUE))
        {
            UBOOT_ERROR("FAIL !!!\n");
            return 1;
        }
    }
    else
    {
        if (len % 0x1000 != 0) // Check 4K alignment
        {
            printf("Wrong Alignment Length, FAIL !!!\n");
            return 1;
        }
        UBOOT_INFO("sector erase\n");
        if (0==MDrv_SERFLASH_SectorErase(flash_addr, flash_addr+len-1))
        {
            UBOOT_ERROR("FAIL !!!\n");
            return 1;
        }
    }
    
    /* SPI write */
    UBOOT_INFO("Writing...\n");
    MDrv_SERFLASH_Write(flash_addr, len, (MS_U8 *)dram_addr);
    MDrv_SERFLASH_WriteProtect(TRUE);

    /* SPI verify */
    unsigned int u32VerifySize = 0;
    unsigned int u32VerifyOffset = 0;
    UBOOT_INFO("Verifying...\n");
    dram_addr_for_verify = malloc(SERFLASH_BLOCK_SIZE);//((dram_addr+len-1+SERFLASH_BLOCK_SIZE) / SERFLASH_BLOCK_SIZE) * SERFLASH_BLOCK_SIZE;/* fix expression of dram_end_address for readability */
    if(dram_addr_for_verify==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    while(len > 0)
    {
        if(len >= SERFLASH_BLOCK_SIZE)
        {
            u32VerifySize = SERFLASH_BLOCK_SIZE;
        }
        else
        {
            u32VerifySize=len;
        }
        
        if(0 != MDrv_SERFLASH_Read(flash_addr+u32VerifyOffset, u32VerifySize, dram_addr_for_verify))
        {
            if(memcmp((void*)(dram_addr+u32VerifyOffset),dram_addr_for_verify,u32VerifySize)!=0)
            {
               free(dram_addr_for_verify);  
               UBOOT_ERROR("FAIL !!!\n"); 
               return -1;
            }
        }
        len-=u32VerifySize;
        u32VerifyOffset+=SERFLASH_BLOCK_SIZE;        
    }
    free(dram_addr_for_verify);     
    UBOOT_TRACE("OK\n");
    return 0;

}
int do_spi_create (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    unsigned int size=0;
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(argc!=CREATE_PARTITION_INPUT_LEN)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    size=simple_strtol(argv[2], NULL,16);
    ret=add_partition(argv[1],size);
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");    
    }
    else
    {
        UBOOT_ERROR("create partition fail\n");
    }
    return ret;
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}

int do_spi_remove (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(argc!=REMOVE_PARTITION_INPUT_LEN)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    
    ret=del_partition(argv[1]);
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");    
    }
    else
    {
        UBOOT_ERROR("remove partition fail\n");
    }
    return ret;
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}

int do_spi_rmgpt(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(argc!=RMGPT_INPUT_LEN)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    
    ret=del_all_partitions();
    if(ret==0)
    {
        ret=add_mboot_partition();
        if(ret==-1)
        {
            UBOOT_ERROR("add mboot partition fail\n");
            return -1;
        }    
    }
    else
    {
        UBOOT_ERROR("remove partition fail\n");
    }
    
    return ret;
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}


int do_spi_part (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    int ret=0;
    UBOOT_TRACE("IN\n");
    
    if(argc!=1)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    ret=list_partition();
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {   UBOOT_ERROR("spi part fail\n");
    }
    return ret;
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
    
}

int do_spi_init_partition (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(argc!=1)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    ret=init_spi_partition();
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {   UBOOT_ERROR("init spi partition fail\n");
    }
    return ret;
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}

int do_spi_erase_partition ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_APP_IN_SPI)
    #define PARTITION_NAME argv[1]
    int ret=0;
    unsigned int partiton_size=0;
    unsigned int partiton_offset=0;
    UBOOT_TRACE("IN\n");
    if(argc!=ERASE_PARTITION_INPUT_LEN)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    ret=get_spi_partition_info(PARTITION_NAME,&partiton_offset,&partiton_size);
    if(ret!=0)
    {
        UBOOT_ERROR("get %s info fail\n",PARTITION_NAME);
        return -1;
    }
    UBOOT_DEBUG("partiton_offset=0x%x\n",partiton_offset);
    UBOOT_DEBUG("partiton_size=0x%x\n",partiton_size);    

    if(MDrv_SERFLASH_WriteProtect(0)==0)
    {
        UBOOT_ERROR ("SPI write protect diable fail\n");
        return -1;
    }
   
    ret=MDrv_SERFLASH_AddressErase (partiton_offset, partiton_size, TRUE) ? 0 : -1;
    if(ret!=0)
    {
        UBOOT_ERROR("erase partition fail\n");
    }

    // even erase fail, we still have to enable write protect function
    if(MDrv_SERFLASH_WriteProtect(1)==0)
    {
        UBOOT_ERROR ("SPI write protect enable fail\n");
        return -1;
    }
    
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    
    return ret;

   #undef PARTITION_NAME
#else
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function doesn't support\n");
    return -1;
#endif
}

int do_spi (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char* cmdtail = NULL;
    UBOOT_TRACE("IN\n");
    //char TmpStr[5];
    if (argc < 2)
    {
       return cmd_usage(cmdtp);
    }    
    if(strncmp(argv[1], "init", 4) == 0)
    {
        do_spi_init(cmdtp,flag,argc-1,&argv[1]);
    }    
    else if(strncmp(argv[1], "id", 2) == 0)
    {
        do_spi_readID(cmdtp,flag,argc-1,&argv[1]);
    }    
    else if(strncmp(argv[1], "read", 4) == 0)
    {
        do_spi_read(cmdtp,flag,argc-1,&argv[1]);
    }    
    else if(strncmp(argv[1], "writ", 4) == 0)
    {
        do_spi_write(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "ea", 2) == 0)
    {
        do_spi_erase_chip(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "eb", 2) == 0)
    {
        do_spi_erase_block(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "es", 2) == 0)
    {
        do_spi_erase_sector(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "bwp", 3) == 0)
    {
        do_spi_block_write_protect(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1],"wpb", 3) == 0)
    {
        do_spi_write_protect_boundry(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "wp", 2) == 0)
    {
        do_spi_write_protect(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "vers", 4) == 0)
    {
        do_spi_get_Chip_Rev(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "info", 4) == 0)
    {
        do_spi_get_flash_info(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "rs", 2) == 0)
    {
        do_spi_read_status(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "ws", 2) == 0)
    {
        do_spi_write_status(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "dma", 3) == 0)
    {
        do_spi_dma(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "wb", 2) == 0)
    {
        do_spi_write_buff(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "rb", 2) == 0)
    {
        do_spi_read_buff(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "rdc", 3) == 0)
    {
        cmdtail=strchr(argv[1], '.');
        if((cmdtail)&&(!strncmp(cmdtail, ".p", 2)))
        {
            do_spi_rdc_partition(cmdtp,flag,argc-1,&argv[1]);
        }
        else
        {
            do_spi_rdc(cmdtp,flag,argc-1,&argv[1]);
        }
        
    }
    else if(strncmp(argv[1], "wrc", 3) == 0)
    {
        cmdtail=strchr(argv[1], '.');
        if((cmdtail)&&(!strncmp(cmdtail, ".p", 2)))
        {
            do_spi_wrc_partition(cmdtp,flag,argc-1,&argv[1]);
        }
        else
        {
            do_spi_wrc(cmdtp,flag,argc-1,&argv[1]);
        }
    }
    else if(strncmp(argv[1], "create", 6) == 0)
    {
        do_spi_create(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "rmgpt", 6) == 0)
    {
        do_spi_rmgpt(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "remove", 6) == 0)
    {
        do_spi_remove(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "part", 4) == 0)
    {
        do_spi_part(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "ptinit", 6) == 0) 
    {
        do_spi_init_partition(cmdtp,flag,argc-1,&argv[1]);
    }
    else if(strncmp(argv[1], "ep", 2) == 0)  
    {
        do_spi_erase_partition(cmdtp,flag,argc-1,&argv[1]);
    }
    else
    {
        UBOOT_ERROR("Please see usage\n");
        return 1;
    }
    UBOOT_TRACE("OK\n");
    return 0;
}
#if (ENABLE_MODULE_SPI == 1)
U_BOOT_CMD(
    spi,     BASE_CMD_INPUT_LEN,               1,    do_spi,
    "See SPI commands",
    "init  : initialization \n"
    "spi id   : read ID\n"
    "spi read : Laddr(hex) len(hex)\n"
    "spi write: addr(hex) len(hex) \n"
    "spi ea   : erase all\n"
    "spi eb   : erase block\n"
    "spi es   : erase sector  -  start addr(hex) end addr(hex)\n"
    "spi wp   : write protect\n"
          " - spi wp 1 :enable(1)\n"
    "spi bwp  : SPI block write protect \n"
             " - protect_blocks(hex) non_protect_blocks(hex)\n"
    "spi wpb  : SPI write protect boundry \n"             
    "spi ver  : get Chip Rev\n"
    "spi info : get flash info\n"
    "spi rs   : read status\n"
    "spi ws   : write status\n"
    "spi dma  : copy data from flash to DRAM by PIU DMA\n"
             " - flash start addr(hex) DRAM start addr(hex) len(hex)\n"
    "spi wb   : write buffer"
             " - spi wb edit addr(hex) len(hex)\n"
    "spi rb   : read buffer"
             " - spi_rb addr(hex) len(hex)\n"
    "spi rdc  : read code from SPI flash to DRAM\n"
    "      to_dram_addr(hex) from_flash_addr(hex) len(hex)\n"
    "    - to_dram_addr: dram start address (hex, flash erase size aligned)\n"
    "    - from_flash_addr: flash start address (hex, flash erase size aligned)\n"
    "    - len: total lenght to move data (hex, flash erase size aligned)\n"
    "spi rdc.p  : read data from DRAM to SPI partiton\n"
    "    [dram_addr(hex)] [partition name][offset(hex)] [len(hex)]\n"
    "    - dram_addr: dram start address (hex, flash erase size aligned)\n"
    "    - partition name: The partition name\n"    
    "    - offset: offset in partition (hex, flash erase size aligned)\n"
    "    - len: total lenght to move data (hex, flash erase size aligned)\n"    
    "spi wrc  : write code from DRAM to SPI flash\n"
    "    from_dram_addr(hex) to_flash_addr(hex) len(hex)\n"
    "    - from_dram_addr: dram start address (hex, flash erase size aligned)\n"
    "    - to_flash_addr: flash start address (hex, flash erase size aligned)\n"
    "    - len: total lenght to move data (hex, flash erase size aligned)\n"
    "spi wrc.p  : write data from DRAM to SPI partiton\n"
    "    [dram_addr(hex)] [partition name][offset(hex)] [len(hex)]\n"
    "    - dram_addr: dram start address (hex, flash erase size aligned)\n"
    "    - partition name: The partition name\n"    
    "    - offset: offset in partition (hex, flash erase size aligned)\n"
    "    - len: total lenght to move data (hex, flash erase size aligned)\n"    
    "spi create : create a partition\n"
    "   -spi create [name] [size(hex)]\n"    
    "spi remove : remove a partition\n"
    "   -spi remove [name]\n"    
    "spi rmgpt : remove all partition\n"
    "spi part : list all partition info\n"
    "spi ptinit : init partition table\n"
);


U_BOOT_CMD(
    spi_wrc,    WRITE_CODE_INPUT_LEN,   1,  do_spi_wrc,
    "spi_wrc - SPI write code from DRAM to SPI flash\n",
    "from_dram_addr(hex) to_flash_addr(hex) len(hex)\n"
    "    - from_dram_addr: dram start address (hex, flash erase size aligned)\n"
    "    - to_flash_addr: flash start address (hex, flash erase size aligned)\n"
    "    - len: total lenght to move data (hex, flash erase size aligned)\n"
);
U_BOOT_CMD(
    spi_rdc,    READ_CODE_INPUT_LEN,    1,  do_spi_rdc,
    "spi_rdc - SPI read code from SPI flash to DRAM\n",
    "to_dram_addr(hex) from_flash_addr(hex) len(hex)\n"
    "    - to_dram_addr: dram start address (hex, flash erase size aligned)\n"
    "    - from_flash_addr: flash start address (hex, flash erase size aligned)\n"
    "    - len: total lenght to move data (hex, flash erase size aligned)\n"
);


#endif
#else
/*
 * Values from last command.
 */
static unsigned int	bus;
static unsigned int	cs;
static unsigned int	mode;
static int   		bitlen;
static uchar 		dout[MAX_SPI_BYTES];
static uchar 		din[MAX_SPI_BYTES];

/*
 * SPI read/write
 *
 * Syntax:
 *   spi {dev} {num_bits} {dout}
 *     {dev} is the device number for controlling chip select (see TBD)
 *     {num_bits} is the number of bits to send & receive (base 10)
 *     {dout} is a hexadecimal string of data to send
 * The command prints out the hexadecimal string received via SPI.
 */

int do_spi (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct spi_slave *slave;
	char  *cp = 0;
	uchar tmp;
	int   j;
	int   rcode = 0;

	/*
	 * We use the last specified parameters, unless new ones are
	 * entered.
	 */

	if ((flag & CMD_FLAG_REPEAT) == 0)
	{
		if (argc >= 2) {
			mode = CONFIG_DEFAULT_SPI_MODE;
			bus = simple_strtoul(argv[1], &cp, 10);
			if (*cp == ':') {
				cs = simple_strtoul(cp+1, &cp, 10);
			} else {
				cs = bus;
				bus = CONFIG_DEFAULT_SPI_BUS;
			}
			if (*cp == '.');
				mode = simple_strtoul(cp+1, NULL, 10);
		}
		if (argc >= 3)
			bitlen = simple_strtoul(argv[2], NULL, 10);
		if (argc >= 4) {
			cp = argv[3];
			for(j = 0; *cp; j++, cp++) {
				tmp = *cp - '0';
				if(tmp > 9)
					tmp -= ('A' - '0') - 10;
				if(tmp > 15)
					tmp -= ('a' - 'A');
				if(tmp > 15) {
					printf("Hex conversion error on %c\n", *cp);
					return 1;
				}
				if((j % 2) == 0)
					dout[j / 2] = (tmp << 4);
				else
					dout[j / 2] |= tmp;
			}
		}
	}

	if ((bitlen < 0) || (bitlen >  (MAX_SPI_BYTES * 8))) {
		printf("Invalid bitlen %d\n", bitlen);
		return 1;
	}

	slave = spi_setup_slave(bus, cs, 1000000, mode);
	if (!slave) {
		printf("Invalid device %d:%d\n", bus, cs);
		return 1;
	}

	spi_claim_bus(slave);
	if(spi_xfer(slave, bitlen, dout, din,
				SPI_XFER_BEGIN | SPI_XFER_END) != 0) {
		printf("Error during SPI transaction\n");
		rcode = 1;
	} else {
		for(j = 0; j < ((bitlen + 7) / 8); j++) {
			printf("%02X", din[j]);
		}
		printf("\n");
	}
	spi_release_bus(slave);
	spi_free_slave(slave);

	return rcode;
}

/***************************************************/

U_BOOT_CMD(
	sspi,	5,	1,	do_spi,
	"SPI utility command",
	"[<bus>:]<cs>[.<mode>] <bit_len> <dout> - Send and receive bits\n"
	"<bus>     - Identifies the SPI bus\n"
	"<cs>      - Identifies the chip select\n"
	"<mode>    - Identifies the SPI mode to use\n"
	"<bit_len> - Number of bits to send (base 10)\n"
	"<dout>    - Hexadecimal string that gets sent"
);
#endif // MSTAR end
