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

/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include <MsCmdTable.h>
#include <MsCoreRegister.h>
#include <MsCustomerRegister.h>

#include <MsInit.h>
#include <ShareType.h>
#include <drvGPIO.h>
#include <drvIRQ.h>
#include <MsOS.h>
#include <MsDevice.h>
#include <common.h>
#include <command.h>
#include <drvSERFLASH.h>
#include <drvBDMA.h>
#include <drvSYS.h>
#include <drvPM.h>
#include <mmc.h>
#include <MsDebug.h>
#include <CusCB.h>
#include <drvWDT.h>
#include <miu/MsDrvMiu.h>

#if defined (CONFIG_USB_PREINIT)
#include <usb.h>
#endif
#if(ENABLE_URSA_8==1)
#include <drvMSPI.h>
#endif

#if (CONFIG_BINARY_RELEASE == 1)
#include <MsMBootConfig.h>
#endif

#if defined (CONFIG_USB_PREINIT)
void init_usb(void)
{
    usb_preinit(0);
#if defined(ENABLE_SECOND_EHC)
    usb_preinit(1);
#endif
#if defined(ENABLE_THIRD_EHC)
    usb_preinit(2);
#endif
}
#endif


extern int msI2C_init(void);
extern void msKeypad_Init(void);
extern void msIR_Initialize(U8 irclk_mhz);
extern MS_BOOL MDrv_MMIO_GetBASE(MS_U32 *u32Baseaddr, MS_U32 *u32Basesize, MS_U32 u32Module);
extern MS_BOOL MDrv_MMIO_Init(void);
extern int get_IR_Type_from_SPI(void);
extern void main_set_uart_status();
#ifdef STATIC_RELIABLE_TEST
extern int do_test_reliable_write(void);
#endif

unsigned long MS_RIU_MAP;

void msFlash_ActiveFlash_Set_HW_WP(BOOLEAN bEnable)
{
    if(bEnable)
    {
#if (CONFIG_BINARY_RELEASE == 1)
		mdrv_gpio_set_low( mboot_config.pin_flash_wp0);
#else
#if(PIN_FLASH_WP0)
        mdrv_gpio_set_low( PIN_FLASH_WP0);
#endif
#endif
        udelay (500);
    }
    else
    {
#if (CONFIG_BINARY_RELEASE == 1)
		mdrv_gpio_set_high( mboot_config.pin_flash_wp0);
#else
#if(PIN_FLASH_WP0)
        mdrv_gpio_set_high( PIN_FLASH_WP0);
#endif
#endif
        udelay (500);
    }
}
#if defined(CONFIG_TIMER_TEST)
void TimerISR(MS_U32 u32Tick)
{
    static unsigned int clk = 0;

    if(clk!=0)
    {
        printf("TIME COUNT %d\n", clk);
	}
    clk++;

    u32Tick=u32Tick;
}

void MDrv_Timer_ISR_Register(void)
{
    MS_U32 check_timer_status;
    check_timer_status = MsOS_CreateTimer( (TimerCb)TimerISR,
                                                  0,
                                                  1000,
                                                  TRUE,
                                                  "Check timer");
}
#endif


#if defined(__ARM__)

void MstarSysInit(void)
{
    uint u32Tmp;
    /*set up Mstar IRQ handler*/
    extern void mhal_fiq_merge(void);
    extern void MAsm_CPU_TimerStart(void);
    extern void dcache_init(void);
    extern void l2_cache_init(void);
    #if (ENABLE_MSTAR_TITANIA_BD_FPGA==0) 
    mhal_fiq_merge();
    #endif
    MsOS_Init();
    flush_cache_all();
#ifdef CONFIG_SYS_DCACHE
    dcache_init();
#endif

#ifndef CONFIG_L2_OFF
    l2_cache_init();
#endif
#if defined(CONFIG_TIMER_TEST)
    MDrv_Timer_ISR_Register();
#endif
    MsOS_CPU_EnableInterrupt();
    MAsm_CPU_TimerStart();


    MDrv_MMIO_Init();
    MDrv_MMIO_GetBASE((MS_U32 *)&MS_RIU_MAP, (MS_U32 *)&u32Tmp, MS_MODULE_PM);
    MDrv_SYS_Init();
    MDrv_WDT_Init(0);
    MsDrv_MiuInit();
#if (ENABLE_MODULE_ENV_IN_SERIAL==1)
#if (ENABLE_MODULE_SPI == 1)
    puts ("SPI:  ");
    {
        extern int spi_init (void);
        spi_init();		/* go init the SPI */
    }

    #if (CONFIG_MSTAR_BD_MST028B_10AFX_EAGLE||CONFIG_MSTAR_BD_MST038B_10AHT_EAGLE ||CONFIG_MSTAR_BD_MST049B_10AQV_NIKE || CONFIG_MSTAR_BD_MST049B_10AQV_NIKE_U)
    MDrv_SERFLASH_SetWPInfo(TRUE);
    #else
    ms_Flash_SetHWWP_CB pCB = msFlash_ActiveFlash_Set_HW_WP;
    MDrv_SERFLASH_SetFlashWPCallBack(pCB);
    FlashSetHWWPCB = FlashSetHWWPCB;
    McuChipSelectCB = McuChipSelectCB;
    #endif
#endif
#else
    #if (ENABLE_MODULE_SPI==1)
        MDrv_SERFLASH_Init();
    #endif
#endif

#if(ENABLE_URSA_8==1)
    MDrv_MSPI_Init_Ext(0x0);
#endif
    mdrv_gpio_init();
    MDrv_BDMA_Init(CONFIG_SYS_MIU_INTERVAL);
    
#if defined (CONFIG_USB_PREINIT)
        init_usb();  
#endif 
    #ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN
    run_command("init_raw_io" , 0);
    run_command("config_raw_io" , 0);
    #endif
    CusCallback();
}

#else


void MstarSysInit(void)
{
    uint u32Tmp;
    extern MS_BOOL MDrv_MIU_SetIOMapBase(void);
    extern MS_BOOL MDrv_SEM_Init(void);

    MsOS_Init();
    MDrv_MMIO_Init();
    MDrv_MMIO_GetBASE((MS_U32 *)&MS_RIU_MAP, (MS_U32 *)&u32Tmp, MS_MODULE_PM);
    MDrv_SEM_Init();
    MDrv_MIU_SetIOMapBase();
    MsOS_CPU_EnableInterrupt();
    MDrv_WDT_Init(0);
    MsDrv_MiuInit();
#if (ENABLE_MODULE_SPI == 1)
#if (ENABLE_MODULE_ENV_IN_SERIAL==1)
    puts ("SPI:  ");
    {
        extern int spi_init (void);
        spi_init();     /* go init the SPI */
    }
    ms_Flash_SetHWWP_CB pCB = msFlash_ActiveFlash_Set_HW_WP;
    MDrv_SERFLASH_SetFlashWPCallBack(pCB);
#else
    MDrv_SERFLASH_Init();
#if (CONFIG_VESTEL_MB97 == 1)
    //move pm code by mips to wakeup PM
    run_command("spi rdc 0xA0000000 0x0 0x10000" , 0);
    WriteByte(0x0ea4, 0x55);
#endif
#endif
#endif
    MDrv_BDMA_Init(CONFIG_SYS_MIU_INTERVAL);
    mdrv_gpio_init();

#if defined (CONFIG_USB_PREINIT)
    init_usb();  
#endif
#ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN
    run_command("init_raw_io" , 0);
    run_command("config_raw_io" , 0);
#endif
    CusCallback();
}


#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @Functino Name :  MstarInit
/// @brief         :  This function is specially for device init via function.
/// @author        :  MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

void MstarInitByFun(void)
{

//for Customer keypad init to set in board_r
#ifdef CONFIG_KEYPAD
    msKeypad_Init();
#endif

#if(CONFIG_MSTARI2C == 1)
    msI2C_init();
#endif

#ifdef CONFIG_IR
    msIR_Initialize(12);
#endif

    main_set_uart_status();
    get_IR_Type_from_SPI();

}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @Functino Name :  MstarInit
/// @brief         :  This function is specially for device init via cmd.
/// @author        :  MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

int MstarDrvInit(void)
{
    int reval=0;
#if CONFIG_MINIUBOOT
#else
    ST_CMD_RECORED *pCmd=NULL;
    UBOOT_DEBUG("\n \033[0;35m ===========================================================\033[0m\n");
    UBOOT_DEBUG("\n \033[0;35m -------------------MstarDrvInit----------------------------\033[0m\n");
    UBOOT_DEBUG("\n \033[0;35m ===========================================================\033[0m\n");

    Table_Init();

    Core_Register_MsInit();
    Customer_Register_MsInit();

    pCmd=getFirstCmd();
    if(pCmd!=NULL)
    {
        while(1)
        {

            if(pCmd->stage == STAGE_MSINIT)
            {
                run_command(pCmd->cmd,  pCmd->flag);
            }

            pCmd=getNextCmd(pCmd);
            if(pCmd==NULL)
            {                
                break;
            }
        }
    }
    else
    {
        printf("There are no any commands in table\n");
    }


    MstarInitByFun();
#endif
    #ifdef STATIC_RELIABLE_TEST
    do_test_reliable_write();
    #endif

    return reval;
}


