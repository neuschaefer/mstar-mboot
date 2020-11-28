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

#include <exports.h>
#include <config.h>
#include <CusSystem.h>
#include <uboot_mmap.h>
#include <ShareType.h>
#include <MsVfs.h>
#include <MsUtility.h>
#include <MsApiMiu.h>
#include <MsDebug.h>
#if defined (CONFIG_SET_4K2K_MODE)
#include <apiPNL.h>
#include <apiGOP.h>
#include <MsBoot.h>
#endif
#if defined (CONFIG_URSA_6M40)
#include <ursa/ursa_6m40.h>
#endif
#if defined (CONFIG_URSA_8)
#include <ursa/ursa_8.h>
#endif
#if (ENABLE_MODULE_BOOT_IR == 1)
#include <MsOS.h>
#endif
#include <CusConfig.h>
#if defined (CONFIG_INX_VB1)
#include <panel/panel_INX_vb1.h>
#elif defined (CONFIG_INX_NOVA_VB1)
#include <panel/panel_INX_NOVA_vb1.h>
#endif

#if defined (CONFIG_URSA6_VB1)
#include <apiPNL.h>
#include <MsMmap.h>
#include <MsSystem.h>
#include <mstarstr.h>
#include <ursa/ursa_6m38.h>
#include <bootlogo/MsPoolDB.h>
#endif

extern int snprintf(char *str, size_t size, const char *fmt, ...);

#if CONFIG_RESCUE_ENV
char *CUS_BOOT_RECOVER_ENV_LIST[] =
{
    NULL
};
#endif

#if CONFIG_MSTAR_STR_ENABLE

#ifdef CONFIG_MSTAR_STR_CRC //calculate CRC for STR dbg
#define BIT0 0x01
#define BIT3 0x08
#define BDMA_BANK 0x1f201200
#define MEM_REGION1_ST 0x00200000
#define MEM_REGION1_SZ 0x9F00000
#define MEM_REGION2_ST 0x10E00000
#define MEM_REGION2_SZ 0xC200000

#define MB_BANK 0x1F206600
#define PM_SLEEP 0x1F001C00

#define Check_STR_CRC 0x1F002090 // 0x1048

extern BOOLEAN get_poweroff_flag(void);

void HAL_MBOOT_Write2Byte( unsigned long u32Reg, unsigned short u16Val )
{
    *((volatile unsigned long *)u32Reg)=u16Val;
}
unsigned short HAL_MBOOT_Read2Byte( unsigned long u32Reg )
{
    return (unsigned short)(*(volatile unsigned long *)u32Reg);
}
unsigned long BDMACRCCalc(int miu, unsigned long u32Addr, unsigned long u32Len)
{
    UBOOT_TRACE("IN\n");
    unsigned long u32CRC=0;
    unsigned long u32Timeout=0;
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x0c*4,0);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x0d*4,0);
    if(miu)
    {
        HAL_MBOOT_Write2Byte(BDMA_BANK+0x02*4,0x0341);    //miu 1
    }else{
        HAL_MBOOT_Write2Byte(BDMA_BANK+0x02*4,0x0340);    //miu 0
    }
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x04*4,u32Addr&0x0FFFF);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x05*4,(u32Addr>>16)&0x0FFFF);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x06*4,u32Addr&0x0FFFF);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x07*4,(u32Addr>>16)&0x0FFFF);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x08*4,u32Len&0x0FFFF);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x09*4,(u32Len>>16)&0x0FFFF);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x0a*4, 0x1DB7);
    HAL_MBOOT_Write2Byte(BDMA_BANK+0x0b*4, 0x04c1);
    HAL_MBOOT_Write2Byte(BDMA_BANK, HAL_MBOOT_Read2Byte(BDMA_BANK)|BIT0);
    //while(0==(HAL_MBOOT_Read2Byte(BDMA_BANK+0x01*4)&BIT3));
    while(1)
    {
        if((HAL_MBOOT_Read2Byte(BDMA_BANK+0x01*4)&BIT3)== 0x08 )
            break;
        if(u32Timeout>0xA00000)
        {
                printf("TIME OUT BDAM 0x%x \n",HAL_MBOOT_Read2Byte(BDMA_BANK+(0x01*4)));
                printf("----CRC TIME OUT ----\n");

                break;
        }
        udelay(10000);
        u32Timeout++;
    }
    u32CRC=HAL_MBOOT_Read2Byte(BDMA_BANK+0x0d*4);
    u32CRC=((u32CRC<<16) | HAL_MBOOT_Read2Byte(BDMA_BANK+0x0c*4));
    UBOOT_TRACE("OK\n");
    return u32CRC;
}
void getTheMemInfo(char* info, int LxMem, unsigned long *addr, unsigned long *size)
{
    char *strLxMem = NULL;
    char *endp = NULL;
    char buf[256]={0};
    switch(LxMem)
    {
        case 1:
            if ((strLxMem = strstr(info, "LX_MEM=")) != NULL)
            {
                *addr = CONFIG_KERNEL_START_ADDRESS;
                *addr = ((*addr) & (0x40000000 - 1));

                strncpy(buf, strchr(strLxMem, '0') , 10);
                buf[10] = 0;
                *size = simple_strtoul(buf, NULL, NULL);
            }
        break;
        case 2:
            if ((strLxMem = strstr(info, "LX_MEM2=")) != NULL)
            {
                endp = strchr(strLxMem, ',');
                strncpy(buf, strchr(strLxMem, '0') , endp-info+1);
                buf[endp-info+1] = 0;
                *addr = simple_strtoul(buf, NULL, NULL);
                if((*addr)>=0xA0000000)
                {
                    *addr = ((*addr) - (0xA0000000));
                }
                else
                {
                    *addr = ((*addr) & (0x40000000 - 1));
                }
                strncpy(buf, strchr(strLxMem, ',') + 1 , (endp+1)-info+1);
                buf[(endp+1)-info+1] = 0;
                *size = simple_strtoul(buf, NULL, NULL);
            }
        break;
        case 3:
            if ((strLxMem = strstr(info, "LX_MEM3=")) != NULL)
            {
                endp = strchr(strLxMem, ',');
                strncpy(buf, strchr(strLxMem, '0') ,  endp-info+1);
                buf[ endp-info+1] = 0;
                *addr = simple_strtoul(buf, NULL, NULL);
                *addr = ((*addr) & 0xFFFFFFF);
                strncpy(buf, strchr(strLxMem, ',') + 1 , (endp+1)-info+1);
                buf[(endp+1)-info+1] = 0;
                *size = simple_strtoul(buf, NULL, NULL);
            }
        break;
        default:
            UBOOT_DEBUG("exception lxmem number %d\n",LxMem);
        break;
    }
}
void CRCCheck(void)
{
    char crclevel[20];
    char *startp=NULL, *endp = NULL;
    U16 STR_CRC_num = 0;
    int len=0;
    unsigned long lx_mem_addr = 0, lx_mem_size = 0 , lx_mem2_addr = 0, lx_mem2_size = 0 , lx_mem3_addr = 0, lx_mem3_size = 0;
    unsigned long crc_result_1 = 0, crc_result_2 = 0, crc_result_3 = 0, pm_crc_1 = 0, pm_crc_2 = 0, pm_crc_3 = 0;
    UBOOT_TRACE("IN\n");
    U16 RegTemp1;
    U16 RegTemp2;
    char *bootargs = getenv("bootargs");

    if (bootargs)
    {
        if ((startp = strstr(bootargs, "str_crc=")) != NULL)
        {
            endp = strchr(startp, ' ');
            if(NULL==endp)len=strlen(startp);
            else len=endp-startp;
            if(len>19)len=19;
            memcpy(crclevel, startp, len);
            crclevel[len]=0;
            if ((strchr(crclevel, '1') != NULL) || (strchr(crclevel, '2') != NULL) || (strchr(crclevel, '3') != NULL))
            {
                RegTemp1 = HAL_MBOOT_Read2Byte(0x1F202400 + 0xF0*2);
                HAL_MBOOT_Write2Byte(0x1F202400 + 0xF0*2, RegTemp1 & ~0x80);
                RegTemp2 = HAL_MBOOT_Read2Byte(0x1F200C00 + 0xF0*2);
                HAL_MBOOT_Write2Byte(0x1F200C00 + 0xF0*2, RegTemp2 & ~0x80);
                // check pattern first
        /*        if ((0x9987 != HAL_MBOOT_Read2Byte(MB_BANK + 0xA0*2)) || (0x8887 != HAL_MBOOT_Read2Byte(MB_BANK + 0xA2*2)))
                {
                    UBOOT_INFO("[WARNING]pattern failed, 99878887 != %04lx%04lx\n",(long unsigned int)HAL_MBOOT_Read2Byte(MB_BANK + 0xA0*2),
                                                                                (long unsigned int)HAL_MBOOT_Read2Byte(MB_BANK + 0xA2*2));
                    setenv("dc_poweroff", "0");
                    saveenv();
                    run_command("reset", 0);
                }
        */

                // get lx_mem  address and size
                getTheMemInfo(bootargs, 1, &lx_mem_addr, &lx_mem_size);
                getTheMemInfo(bootargs, 2, &lx_mem2_addr, &lx_mem2_size);
                getTheMemInfo(bootargs, 3, &lx_mem3_addr, &lx_mem3_size);

                // calculate crc
                //crc_result_1 = BDMACRCCalc(0,lx_mem_addr + 0x10000, lx_mem_size - 0x10000);
                //pm_crc_1 = HAL_MBOOT_Read2Byte(MB_BANK + 0xA6*2) << 16 | HAL_MBOOT_Read2Byte(MB_BANK + 0xA4*2);

                if (lx_mem_size != 0 && lx_mem2_size != 0)
                {
                    if(CONFIG_MSTAR_STR_CRC_SIZE != 0x0)
                    {
                        lx_mem_size = CONFIG_MSTAR_STR_CRC_SIZE;
                        lx_mem2_size = CONFIG_MSTAR_STR_CRC_SIZE;
                    }
                    crc_result_1 = BDMACRCCalc(0,lx_mem_addr+ 0x10000, lx_mem_size- 0x10000);
                    pm_crc_1 = HAL_MBOOT_Read2Byte(MB_BANK + 0xA6*2) << 16 | HAL_MBOOT_Read2Byte(MB_BANK + 0xA4*2);
                    crc_result_2 = BDMACRCCalc(1,lx_mem2_addr, lx_mem2_size);
                    pm_crc_2 = HAL_MBOOT_Read2Byte(MB_BANK + 0xAA*2) << 16 | HAL_MBOOT_Read2Byte(MB_BANK + 0xA8*2);
                 
                    STR_CRC_num = (U16)(pm_crc_1) + (U16)(pm_crc_1>>16) + (U16)(pm_crc_2) + (U16)(pm_crc_2>>16);
                    if(HAL_MBOOT_Read2Byte(Check_STR_CRC)!=STR_CRC_num)
                    {
                    	printf("CRC Check Fail !!!!\n");
                    }
                }
                HAL_MBOOT_Write2Byte(0x1F202400 + 0xF0*2, RegTemp1);
                HAL_MBOOT_Write2Byte(0x1F200C00 + 0xF0*2, RegTemp2);
                
                /*
                else if(lx_mem3_size == 0 && lx_mem2_size != 0)
                {
                    crc_result_2 = BDMACRCCalc(0,lx_mem2_addr, lx_mem2_size);
                    pm_crc_2 = HAL_MBOOT_Read2Byte(MB_BANK + 0xAA*2) << 16 | HAL_MBOOT_Read2Byte(MB_BANK + 0xA8*2);
                }
                else if(lx_mem3_size != 0 && lx_mem2_size == 0)
                {
                    crc_result_3 = BDMACRCCalc(1,lx_mem3_addr, lx_mem3_size);
                    pm_crc_3 = HAL_MBOOT_Read2Byte(MB_BANK + 0xAA*2) << 16 | HAL_MBOOT_Read2Byte(MB_BANK + 0xA8*2);
                }*/

                UBOOT_ERROR("MemRegion[%08lx,%08lx] CRC is %08lx, pmCRC is %08lx\n",lx_mem_addr,lx_mem_size,crc_result_1, pm_crc_1);
                UBOOT_ERROR("MemRegion[%08lx,%08lx] CRC is %08lx, pmCRC is %08lx\n",lx_mem2_addr,lx_mem2_size,crc_result_2, pm_crc_2);
	            printf("\033[31m ########################## \n");    
				printf("MemRegion[%08lx,%08lx] CRC is %08lx \n", lx_mem_addr, lx_mem_size, crc_result_1);
                printf("MemRegion[%08lx,%08lx] CRC is %08lx \n", lx_mem2_addr, lx_mem2_size, crc_result_2);
                printf("########################## \033[0m\n"); 
		/*
                if ((crc_result_1 != pm_crc_1) ||
                    (crc_result_2 != pm_crc_2) ||
                    (crc_result_3 != pm_crc_3))
                {
                    UBOOT_ERROR("Check CRC fail :\n");
                    UBOOT_ERROR("MemRegion[%08lx,%08lx] CRC is %08lx, pmCRC is %08lx\n",lx_mem_addr,lx_mem_size,crc_result_1, pm_crc_1);
                    UBOOT_ERROR("MemRegion[%08lx,%08lx] CRC is %08lx, pmCRC is %08lx\n",lx_mem2_addr,lx_mem2_size,crc_result_2, pm_crc_2);
                    UBOOT_ERROR("MemRegion[%08lx,%08lx] CRC is %08lx, pmCRC is %08lx\n",lx_mem3_addr,lx_mem3_size,crc_result_3, pm_crc_3);

                    if (strchr(crclevel, '2') != NULL)
                    {
                        // system reset
                        setenv("dc_poweroff", "0");
                        saveenv();
                        UBOOT_ERROR("system reset due to crc error!!!!!\n");
                        run_command("reset", 0);
                    }
                    else if (strchr(crclevel, '3') != NULL)
                    {
                        // system hang
                        setenv("dc_poweroff", "0");
                        saveenv();
                        UBOOT_ERROR("system hang due to crc error!!!!!\n");
                        while(1);
                    }
                }*/
            }
            else
            {
                // do nothing
            }
        }
        else
        {
            UBOOT_INFO("warning: can not get crclevel !!!!!!\n");
        }
    }
    else
    {
        UBOOT_ERROR("error: can not get bootargs !!!!!!\n");
    }
     UBOOT_TRACE("OK\n");
}


#endif

#define MSTAR_SLEEP_MAGIC         0x4D535452

#if ENABLE_MSTAR_EAGLE
#define PMU_WAKEUP_ADDR_REGL     0x1F001CE0
#define PMU_WAKEUP_ADDR_REGH     0x1F001CE4
#elif ENABLE_MSTAR_KENYA
#define PMU_WAKEUP_ADDR_REGL     0xBF001CF0
#define PMU_WAKEUP_ADDR_REGH     0xBF001CF0
#else
#define PMU_WAKEUP_ADDR_REGL     0x1F001D48
#define PMU_WAKEUP_ADDR_REGH     0x1F001D48
#endif
#define PMU_WAKEUP_ADDR_LMASK    0x000000FF
#define PMU_WAKEUP_ADDR_HMASK    0x0000FF00



#define WAKEUP_ADDR_MASK          0x0000FFF0
#define WAKEUP_FLAG_MASK          0x0000000F
#define WAKEUP_FLAG_INVALID       0
#define WAKEUP_FLAG_SLEPT         1
#define WAKEUP_FLAG_WKUP          2

#if CONFIG_MCU_MIPS32
#define MIU0_VIRTBASE1   0x80000000
#define MIU1_BASE_ADDR1  0x60000000
#define MIU1_BASE_ADDR2  0x70000000
#define MIU1_VIRTBASE1   0x00000000
#define MIU1_VIRTBASE2   0x20000000
#define _PHY_TO_VIRT(x) ((x<MIU1_BASE_ADDR1)?(x+MIU0_VIRTBASE1):    \
                          ((x<MIU1_BASE_ADDR2)?(x-MIU1_BASE_ADDR1+MIU1_VIRTBASE1):(x-MIU1_BASE_ADDR2+MIU1_VIRTBASE2)) )
#elif CONFIG_MCU_ARM
#define M512M (512*1024*1024)
#define _PHY_TO_VIRT(x) ( (((x)>=(CONFIG_MIU0_BUSADDR)&&(x)<(CONFIG_MIU0_BUSADDR+M512M)) \
                            ||((x)>=(CONFIG_MIU1_BUSADDR)&&(x)<(CONFIG_MIU1_BUSADDR+M512M)))? \
                            (x):(0) )
#else
#define _PHY_TO_VIRT(x) (x)
#endif
#define PHY_TO_VIRT(x) _PHY_TO_VIRT((unsigned long)(x))

unsigned long read_wkup_pmu(void)
{
    volatile unsigned long *preg=0;
    unsigned long val=0;

    preg=(volatile unsigned long *)PMU_WAKEUP_ADDR_REGL;
    val = ((*preg)&PMU_WAKEUP_ADDR_LMASK);
    preg=(volatile unsigned long *)PMU_WAKEUP_ADDR_REGH;
    val |= ((*preg)&PMU_WAKEUP_ADDR_HMASK);

    return val;
}
void write_wkup_pmu(unsigned long val)
{
    volatile unsigned long *preg=0;
    unsigned long oldval;

    preg=(volatile unsigned long *)PMU_WAKEUP_ADDR_REGL;
    oldval = ((*preg) & ~PMU_WAKEUP_ADDR_LMASK);
    oldval |= (val&PMU_WAKEUP_ADDR_LMASK);
    (*preg) = oldval;

    preg=(volatile unsigned long *)PMU_WAKEUP_ADDR_REGH;
    oldval = ((*preg) & ~PMU_WAKEUP_ADDR_HMASK);
    oldval |= (val&PMU_WAKEUP_ADDR_HMASK);
    (*preg) = oldval;

}

int _is_str_resume(void)
{
    unsigned long pmu_str_reg=0,*pwkupsave=0;
    pmu_str_reg=read_wkup_pmu();
    pwkupsave = (unsigned long*)((pmu_str_reg&WAKEUP_ADDR_MASK)<<16);
#if CONFIG_MCU_MIPS32
    pwkupsave = (unsigned long*)PHY_TO_VIRT(pwkupsave);
#endif
    if((pmu_str_reg & WAKEUP_FLAG_MASK) == WAKEUP_FLAG_SLEPT && pwkupsave
    	&& pwkupsave[0]==MSTAR_SLEEP_MAGIC && pwkupsave[1])
    {
		return 1;
    }
    return 0;
}

int check_str_resume(void)
{
#ifdef CONFIG_MSTAR_STR_CRC
    if(!((HAL_MBOOT_Read2Byte(PM_SLEEP + 0x70*2) & 0xFF00) == 0xFF00) &&
        (get_poweroff_flag()))
    {
        CRCCheck();
    }
#endif
    return _is_str_resume();
}

int do_check_str_resume(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]){

    unsigned long pmu_str_reg=0,*pwkupsave=0;
    char* s = NULL;
#ifdef CONFIG_MSTAR_STR_CRC
    if(!((HAL_MBOOT_Read2Byte(PM_SLEEP + 0x70*2) & 0xFF00) == 0xFF00) &&
        (get_poweroff_flag()))
    {
        CRCCheck();
    }
#endif

    pmu_str_reg=read_wkup_pmu();
    pwkupsave = (unsigned long*)((pmu_str_reg&WAKEUP_ADDR_MASK)<<16);
#if CONFIG_MCU_MIPS32
    pwkupsave = (unsigned long*)PHY_TO_VIRT(pwkupsave);
#endif
    if((pmu_str_reg & WAKEUP_FLAG_MASK) == WAKEUP_FLAG_SLEPT && pwkupsave
    && pwkupsave[0]==MSTAR_SLEEP_MAGIC && pwkupsave[1])
    {
        s = getenv("KERNEL_PROTECT");
        if (s != NULL)
            MsApi_kernelProtect();
        s = getenv("kernelProtectBist");
        if (s != NULL)
            MsApi_kernelProtectBist();

        write_wkup_pmu((pmu_str_reg&~WAKEUP_FLAG_MASK)|WAKEUP_FLAG_WKUP);
#if CONFIG_MCU_MIPS32
        {
        	  void (*resume)(void);
        	  resume = (void *)PHY_TO_VIRT(pwkupsave[1]);
        	  if(resume)
        	      resume();
        }
#elif CONFIG_MCU_ARM
        __asm__ volatile (
            "ldr r1, %0\n"
            "ldr r1, [r1, #4]\n"
            "cpsid if, #0x13\n"
            //; Disable MMU
            "MRC   p15, 0, r0, c1, c0, 0\n"
            "BIC   r0, r0, #0x1\n"
            "MCR   p15, 0, r0, c1, c0, 0\n"
            //; jump to wakeup address
            "mov pc, r1\n"
            ::"m"(pwkupsave):"r0","r1","memory","cc");
#endif
    }
    else
    {
        write_wkup_pmu(0);
    }
    return 0;
}
#endif


int do_envload (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uchar bReloadEnv = 0;
    char *envbuffer;
    envbuffer=NULL;

#if defined(CONFIG_ENV_IS_IN_SPIFLASH)
    extern int env_isempty(void);
    if(env_isempty())
    {
        printf("\n <env reload for CRC>\n");
        bReloadEnv = 1;
    }
#endif

#if defined(CONFIG_LOAD_ENV_FROM_SN)
    envbuffer = getenv ("mboot_default_env");
    if(envbuffer)
    {
        if(simple_strtoul (envbuffer, NULL, 10))
        {
            printf("\n <env reload for CHECK_IF_MBOOT_DEFAULT_ENV>\n");
            bReloadEnv = 1;
        }
    }

    if (getenv("bootargs") == NULL || getenv("recoverycmd") == NULL)
    {
        UBOOT_DEBUG("get env configs from SN\n");
        bReloadEnv = 1;
    }
#endif

    if(bReloadEnv)
    {
        char cmd[128]="\0";
        snprintf(cmd,sizeof(cmd)-1,"loadenv %s %s/set_env",CONFIG,CONFIG_PATH);
        run_command(cmd,0);
    }
    else
	{
        // reload env after reboot in recovery mode.
        extern int get_boot_status_from_mtd0(void);
        get_boot_status_from_mtd0();
	}

     return 0;
}

#if defined (CONFIG_MBOOT_VERSION)
int do_setmbootver (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]){
    char *s;
    if((s = getenv (USB_MBOOT_VERSION))!= NULL)
    {
        if(strcmp(s,USB_MBOOT_CURRENT_VERSION))
        {
            setenv(USB_MBOOT_VERSION, USB_MBOOT_CURRENT_VERSION);
            saveenv();
        }
    }
    else
    {
        setenv(USB_MBOOT_VERSION, USB_MBOOT_CURRENT_VERSION);
        saveenv();
    }
    return 0;
}
#endif



#define BOOT_IF_ACTION(c, b)                ((c) & (b))

int get_boot_status_from_mtd0(void)
{
    int ret = 0;
    struct bootloader_message *p_msg = NULL;
    p_msg = (struct bootloader_message*)BOOT_MODE_TMP_BUF_ADDR;
    char cmd[128];

    memset(cmd, 0, sizeof(cmd));
#if (ENABLE_MODULE_MMC == 1)
    snprintf(cmd, sizeof(cmd)-1, "mmc read.p 0x%08lX misc 40", (unsigned long)BOOT_MODE_TMP_BUF_ADDR);
#else
    snprintf(cmd, sizeof(cmd)-1, "nand read.e 0x%08lX misc 40", (unsigned long)BOOT_MODE_TMP_BUF_ADDR);
#endif
    if(-1 != run_command(cmd, 0))
    {
        UBOOT_DEBUG("read the misc partion data\n");
        memset(cmd, 0, sizeof(cmd));
        if ((strlen(p_msg->command) == strlen(BOOT_STATUS_CUSTOMER_ACTIONS_STR)) && (0==strncmp(p_msg->command, BOOT_STATUS_CUSTOMER_ACTIONS_STR, strlen(BOOT_STATUS_CUSTOMER_ACTIONS_STR))))
        {
            int reloadEnv   = 0;
            int reloadPanel = 0;
            char actionByte = p_msg->status[0];
            if (BOOT_IF_ACTION(actionByte, BOOT_STATUS_ACTION_RELOADPANEL_BIT))
            {
                reloadPanel = 1;
            }
            if (BOOT_IF_ACTION(actionByte, BOOT_STATUS_ACTION_RELOADENV_BIT))
            {
                reloadEnv = 1;
            }

            memset(p_msg->command, 0, sizeof(p_msg->command));
            memset(p_msg->status, 0, sizeof(p_msg->status));
            memset(cmd, 0, sizeof(cmd));
#if (ENABLE_MODULE_MMC == 1)
            snprintf(cmd, sizeof(cmd)-1, "mmc write.p 0x%08lX misc 40", (unsigned long)BOOT_MODE_TMP_BUF_ADDR);
#else
            snprintf(cmd, sizeof(cmd)-1, "nand write.e 0x%08lX misc 40", (unsigned long)BOOT_MODE_TMP_BUF_ADDR);
#endif
            run_command(cmd, 0);

            if (reloadPanel)
            {
                setenv("db_table","0");
                saveenv();
            }

            if (reloadEnv)
            {
                // reload env
                char cmd[128]="\0";
                snprintf(cmd,sizeof(cmd)-1,"loadenv %s %s/set_env",CONFIG,CONFIG_PATH);
                run_command(cmd,0);
            }
        }
    }
    else
    {
        UBOOT_ERROR("read misc partition data failed\n");
        ret = -1;
    }
    return ret;
}


int do_loadenv(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if ENABLE_MODULE_LOAD_ENV_FROM_SN
    #ifdef CONFIG_UBI
    int ret=0;
    #endif
#endif
    UBOOT_TRACE("IN\n");
    if(argc < 3)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(argv[1] == NULL)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(argv[2] == NULL)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    UBOOT_DEBUG("load env from partition -> %s path -> %s\n",argv[1],argv[2]);
#if ENABLE_MODULE_LOAD_ENV_FROM_SN
    #ifdef CONFIG_UBI
    ret = run_command("dynpart edb64M-nand:0x00100000(misc),0x00600000(recovery),0x00400000(boot),0x1ee00000(ubi),3m(CTRL),3m(TBL),-(reserved)", 0);
    if(ret==-1)
    {
        UBOOT_ERROR("dynpart fail\n");
        return -1;
    }
    #endif
    vfs_mount(argv[1]);
    runscript_linebyline(argv[2]);
    vfs_umount();
#endif
    UBOOT_TRACE("OK\n");

    return 0;

}

#if defined (CONFIG_SET_4K2K_MODE)
extern U8 g_logoGopIdx;

MS_BOOL __Sc_is_interlace(void)
{
    return 0;
}

MS_U16 __Sc_get_h_cap_start(void)
{
    return 0x60;
}

void __Sys_PQ_ReduceBW_ForOSD(MS_U8 PqWin, MS_BOOL bOSD_On)
{

}

int do_setFRC(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    GOP_InitInfo pGopInit;

    if(get_poweroff_flag())
    {
        memset((void *)&pGopInit, 0, sizeof(pGopInit));
        MApi_GOP_RegisterXCIsInterlaceCB(__Sc_is_interlace);
        MApi_GOP_RegisterXCGetCapHStartCB(__Sc_get_h_cap_start);
        MApi_GOP_RegisterXCReduceBWForOSDCB(__Sys_PQ_ReduceBW_ForOSD);
        pGopInit.u16PanelWidth = g_IPanel.Width();
        pGopInit.u16PanelHeight = g_IPanel.Height();
        pGopInit.u16PanelHStr = g_IPanel.HStart();
        pGopInit.u32GOPRBAdr = 0x0;
        pGopInit.u32GOPRBLen = 0x0;

        pGopInit.u32GOPRegdmaAdr = 0;
        pGopInit.u32GOPRegdmaLen = 0;
        pGopInit.bEnableVsyncIntFlip = FALSE;

        MApi_GOP_InitByGOP(&pGopInit, g_logoGopIdx);
        MApi_GOP_GWIN_SetGOPDst(g_logoGopIdx, E_GOP_DST_FRC);
    }
    return 0;
}

int Set_4K2K_OP0(void)
{
    GOP_InitInfo pGopInit;

    //close lvds
    MDrv_Ursa_6M40_Set_Lvds_Off();

    //disable osd
    MDrv_Ursa_6M40_Set_Osd_Off();

    //set OP0
    memset((void *)&pGopInit, 0, sizeof(pGopInit));
    MApi_GOP_RegisterXCIsInterlaceCB(__Sc_is_interlace);
    MApi_GOP_RegisterXCGetCapHStartCB(__Sc_get_h_cap_start);
    MApi_GOP_RegisterXCReduceBWForOSDCB(__Sys_PQ_ReduceBW_ForOSD);
    pGopInit.u16PanelWidth = g_IPanel.Width();
    pGopInit.u16PanelHeight = g_IPanel.Height();
    pGopInit.u16PanelHStr = g_IPanel.HStart();
    pGopInit.u32GOPRBAdr = 0x0;
    pGopInit.u32GOPRBLen = 0x0;

    pGopInit.u32GOPRegdmaAdr = 0;
    pGopInit.u32GOPRegdmaLen = 0;
    pGopInit.bEnableVsyncIntFlip = FALSE;

    MApi_GOP_InitByGOP(&pGopInit, g_logoGopIdx);
    MApi_GOP_GWIN_SetGOPDst(g_logoGopIdx, E_GOP_DST_OP0);

    //open lvds
    MDrv_Ursa_6M40_Set_Lvds_On();

    return 0;
}
#endif

#if defined (CONFIG_URSA_6M40)
int do_ursa_lvds_on (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_BOOL bRet = FALSE;
    bRet = MDrv_Ursa_6M40_Set_Lvds_On();
    return 0;
}
int do_ursa_lvds_off(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_BOOL bRet = FALSE;
    bRet = MDrv_Ursa_6M40_Set_Lvds_Off();
    return 0;
}

int do_ursa_osd_unmute (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_BOOL bRet = FALSE;
    bRet = MDrv_Ursa_6M40_Set_Osd_Unmute();
    return 0;
}
int do_ursa_2k_mode_on (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_BOOL bRet = FALSE;
    bRet = MDrv_Ursa_6M40_Set_2K_Mode_On();
    return 0;
}

int do_ursa_set_osd_mode(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u16 protect_mode =0;
    int ret =0;

    protect_mode = g_UrsaCMDGenSetting.g_OsdMode.protect_mode;
    if(protect_mode>=0 && protect_mode < 3)
    {

        printf("osd_protect_mode = %d\n",protect_mode);
            switch(protect_mode)
                {
                case URSA_6M40_OSD_PROTECT_OFF:
                    {
                        MDrv_Ursa_6M40_SendCmd(CMD_6M40_OSD_PROTECT_OFF);
                    }
                    break;
                case URSA_6M40_OSD_PROTECT_ON:
                    {
                        MDrv_Ursa_6M40_SendCmd(CMD_6M40_OSD_PROTECT_ON);
                    }
                    break;
                case URSA_6M40_OSD_PROTECT_ON_EMMC:
                    {
                        MDrv_Ursa_6M40_SendCmd(CMD_6M40_OSD_PROTECT_ON_EMMC);
                    }
                    break;
                default:
                         break;
                }
        }
        else
		{
            UBOOT_ERROR("OSD protect Mode setting not correct\n");
            ret = -1;
        }
    return ret;
}

#endif

#if defined (CONFIG_ENABLE_4K2K_PANEL)
int do_inx_panel_set_init (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_INX_VB1)
    MDrv_Panel_INX_VB1_Set_Pre_Init();
#elif defined(CONFIG_INX_NOVA_VB1)
    MDrv_Panel_INX_NOVA_VB1_Unlock_AHB();
#endif
    return 0;
}

int do_inx_panel_set_fhd (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_INX_VB1)
    MDrv_Panel_INX_VB1_Set_FHD();
#elif defined (CONFIG_INX_LVDS)
    MDrv_PANEL_INX_LVDS_Set_FHD();
#endif
    return 0;
}

int do_inx_panel_set_4k2k (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined (CONFIG_INX_VB1)
    MDrv_Panel_INX_VB1_Set_4K2K();
#elif defined (CONFIG_INX_LVDS)
    MDrv_PANEL_INX_LVDS_Set_4K2K();
#elif defined (CONFIG_INX_NOVA_VB1)
    MDrv_Panel_INX_NOVA_VB1_Set_UHD_DIVISION(UHD_2_DIVISION);
#endif
    return 0;
}

#if defined (CONFIG_INX_NOVA_VB1)
int do_inx_nova_set_4k2k_2division (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MDrv_Panel_INX_NOVA_VB1_Set_UHD_DIVISION(UHD_2_DIVISION);
    return 0;
}
#endif

#if defined (CONFIG_INX_VB1)
int do_panel_inx_vb1_init (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if defined(CONFIG_BOOTLOGO_4K2K)
    MDrv_Panel_INX_VB1_RX_INIT();
#endif
    return 0;
}
#endif
#endif

#if defined (CONFIG_URSA_8)
int do_ursa8_lvds_on (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_BOOL bRet = FALSE;
    bRet = MDrv_Ursa_8_Set_Lvds_On();
    return 0;
}


int do_ursa8_set_osd_mode(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u16 protect_mode =0;
    int ret =0;

    protect_mode = g_UrsaCMDGenSetting.g_OsdMode.protect_mode;
    if(protect_mode>=0 && protect_mode < 3)
    {

        printf("osd_protect_mode = %d\n",protect_mode);
            switch(protect_mode)
                {
                case URSA_8_OSD_PROTECT_OFF:
                    {
                        MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_PROTECT_OFF);
                    }
                    break;
                case URSA_8_OSD_PROTECT_ON:
                    {
                        MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_PROTECT_ON);
                    }
                    break;
                case URSA_8_OSD_PROTECT_ON_EMMC:
                    {
                        MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_PROTECT_ON_EMMC);
                    }
                    break;
                default:
                         break;
                }
        }
        else{
            UBOOT_ERROR("OSD protect Mode setting not correct\n");
            ret = -1;
            }


    return ret;

}

#endif
#if (ENABLE_MODULE_BOOT_IR == 1)
int do_ir_delay(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	mdelay(300); //sleep 300ms
	return 0;
}
#endif

#if defined (CONFIG_URSA6_VB1)
int do_send_I2C_cmd_to_ursa6(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    #if defined(CONFIG_MSTAR_MONACO)
	MDrv_Ursa_6M38_SWI2C_Init();
	MDrv_Ursa_6M38_4K2K60_init();
	MDrv_Ursa_6M38_4K2K_DisableAutoMute();
	#else
	PanelType panel_data;
	memset(&panel_data, 0, sizeof(panel_data));
	
	if(is_str_resume())
	{
		U32 u32PanelConfigsAddr;
		if(get_addr_from_mmap("E_MMAP_ID_VDEC_CPU", &u32PanelConfigsAddr)!=0)
		{
			UBOOT_ERROR("get E_MMAP_ID_VDEC_CPU mmap fail\n");
			return -1;
		}
		UBOOT_DEBUG("E_MMAP_ID_VDEC_CPU = 0x%x\n", u32PanelConfigsAddr);
		UBOOT_DEBUG("(U32)(PA2NVA(u32PanelConfigsAddr)) = 0x%x\n", (U32)(PA2NVA(u32PanelConfigsAddr)));
		memcpy(&panel_data, (U32*)(PA2NVA(u32PanelConfigsAddr)), sizeof(PanelType));
	}
	else 
	{
		if(Read_PanelParaFromflash(&panel_data)!=0)
		{
			UBOOT_ERROR("%s: Read_PanelParaFromflash() failed, at %d\n", __func__, __LINE__);
			return -1;
		}
	}
	
	if(panel_data.m_wPanelWidth == 3840 && panel_data.m_wPanelHeight == 2160)
        MDrv_Ursa_6M38_4K2K_init();
    else
        MDrv_Ursa_6M38_Set_2_lane_VB1_per_init();
		
	if(panel_data.m_wPanelWidth == 1920 && panel_data.m_wPanelHeight == 1080)
        MDrv_Ursa_6M38_Set_2_lane_VB1();

	#endif
	return 0;
}
#endif 


int do_load_environment_first_time(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char strCommand[CMD_BUF];
    char *pEnv=NULL;
    unsigned char sync_environment=0;

    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("flag is %u\n", flag);


    pEnv = getenv("sync_environment");
    if(NULL != pEnv) //if the flag was already set, check its value first
    {
        sync_environment=simple_strtol(pEnv, NULL, 16);
        UBOOT_DEBUG("sync_environment is %u\n", sync_environment);
    }
    else //if it is first boot, then load environment
    {
        UBOOT_DEBUG("sync_environment was not set, setting it to 1\n");
        sync_environment=1; 
    }
    
    if(1 == sync_environment) //if it is first boot or if sync_environment == 1, then load environment
    {

        #if (CONFIG_VESTEL_MB97 == 1)
        UBOOT_TRACE("Loading environment from %s%s/%s\n",CONF,CONFIG_PATH,ENVIRONMENT_NAME);
        if(vfs_mount(CONF)!=0)
        {
            UBOOT_ERROR("mount %s fail\n",CONF);
            return -1;
        }
        #else
        UBOOT_TRACE("Loading environment from %s%s/%s\n",CONFIG,CONFIG_PATH,ENVIRONMENT_NAME);
        if(vfs_mount(CONFIG)!=0)
        {
            UBOOT_ERROR("mount %s fail\n",CONFIG);
            return -1;
        }
        #endif

        memset(strCommand,0,CMD_BUF);
        snprintf(strCommand,CMD_BUF,"%s/%s",CONFIG_PATH,ENVIRONMENT_NAME);
        runscript_linebyline(strCommand);
        vfs_umount();

        run_command("setenv sync_environment 0;saveenv", 0); //set the flag to 0x00 so that we don't load environment.txt again
    }

    UBOOT_TRACE("OK\n");

return 0;
}

