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
/*------------------------------------------------------------------------------*/
/*  INCLUDE                                                                     */
/*------------------------------------------------------------------------------*/
#include "datatype.h"
#include "hwreg.h"
#include "drvGlobal.h"
#include "drvAeonUART.h"
#include "risc32_spr.h"
#include "drvPadConf.h"
#include "drvISR.h"
#include "MApp_Wakeup.h"


//*******************
//
//  utopia include files
//
//*******************
#include "MsCommon.h"
#include "drvMMIO.h"
#include "drvBDMA.h"
#include "drvWDT.h"
#include "drvGPIO.h"
#include "drvUART.h"
#include "drvRTC.h"

//*******************
//
//  other include files
//
//*******************
#include "msIIC.h"



//***********************************************************
//              Macro Definitions
//***********************************************************
#define QMEM     ((unsigned  short volatile *) 0xB0000000ul)
#define UART0_BAUDRATE_PM               38400
#define _SPI_BOOTLOADER_RESET_VECTOR    0x00000


//***********************************************************
//              External Veriables
//***********************************************************


//***********************************************************
//              Local Veriables
//***********************************************************


//***********************************************************
//              Global Veriables
//***********************************************************


//***********************************************************
//              External Functions
//***********************************************************
extern MS_BOOL MDrv_XC_SetIOMapBase_i(void);
extern void InitialSystemPowerDown(void);
extern void MDrv_Sync_ConfigWakeup(void);
extern void MDrv_RTC_ConfigWakeup(void);
extern void MDrv_UART_ConfigWakeup(void);
extern int main(void);
#if BLOCK_POWER_FUNC
extern void MDrv_Block_PowerUp(void);
#endif


//***********************************************************
//              Global Functions Declaration
//***********************************************************
void SystemBootFromSPI(U32 u32BootAddr);
void SystemWholeChipReset(void);
void MDrv_Init_Varilabe(void);
void MDrv_Power_TurnOffStandby(void);
void start(void);


//***********************************************************
//              Local Functions Definition
//***********************************************************
static void MDrv_InitConsole( void )
{
    uart_init(12000000, UART0_BAUDRATE_PM);
    mtspr( SPR_TTMR, 0x40000000 | 12000 );
}


//***********************************************************
//              Global Functions Definition
//***********************************************************
//
//  Boot from BootLoader
//  SPI boot from offset u32BootAddr
//
void SystemBootFromSPI(U32 u32BootAddr)
{

    //(1) Disable MIU0 first
    MDrv_Write2Byte(0x101200, MDrv_Read2Byte(0x101200)&(~BIT0));
    //(2) Set up reset vector base
    MDrv_Write2Byte(0x1002B4, (U16)(u32BootAddr >> 16));
    //(3) Set wtd_mcu_rst passwd
    MDrv_Write2Byte(0x002E54, 0x829f);
    //(4) Reset R2
    MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)&(~BIT8));
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    //(5) Set SPI Boot
    MDrv_Write2Byte(0x100280, 0x001B);  // set spi_boot=1, riu_sw_rstz=1, miu_sw_rstz=0, r2_sw_rstz=1, r2_enable=1
    //(6) Release R2
    MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)|(BIT8));  // fire wtd_mcu_rst
}

//
//  Boot from BootLoader
//  System whole chip reset
//
void SystemWholeChipReset(void)
{
    printf("\r\n ======= Whole Chip Reset ======= \r\n");
    #if 0
    //This GPIO controlling DDR2 1.8volt power must be pulled HIGH before whole chip reset
    //because PAD_SARx (analog pads) cannot be auto-pull high by whole chip reset
    #endif

    #if BLOCK_POWER_FUNC
    MDrv_Block_PowerUp();
    #endif
    MDrv_Write2Byte(REG_PM_GCR_SWCK, MDrv_Read2Byte(REG_PM_GCR_SWCK) & (~0x0100));
    MDrv_Write4Byte(0x0EA0, 0x51685168);
    MDrv_WriteRegBit(0x2E52, 1, BIT7);
    MDrv_WriteRegBit(0x2E52, 1, BIT6);
    MDrv_WriteByte(0x2E5C,0xFF);
    MDrv_WriteByte(0x2E5C,0x79);

    while(1);
}

void MDrv_Init_Varilabe(void)
{
    gSyncDetect = FALSE;
    u8HDMIWakeUpDelayCount = 25;
}

void MDrv_Power_TurnOffStandby(void)
{
#if((MS_BOARD_TYPE_SEL == BD_MST195A_D01A_S_NASA))
    mdrv_gpio_set_low(PAD_TCON1);
#elif((MS_BOARD_TYPE_SEL == BD_MST195B_D01A_S_NASA))
    mdrv_gpio_set_low(PAD_GPIO10);
#elif((MS_BOARD_TYPE_SEL == BD_MST195C_D01A_S_NASA))
    mdrv_gpio_set_low(PAD_GPIO10);
#elif((MS_BOARD_TYPE_SEL == BD_MST186A_D01A_S_NASA))
    mdrv_gpio_set_low(PAD_TCON1);
#elif((MS_BOARD_TYPE_SEL == BD_MST186E_D01A_S_NASA))
    mdrv_gpio_set_low(PAD_INT);
#elif((MS_BOARD_TYPE_SEL == BD_MST060B_10AZBT_13502))
    mdrv_gpio_set_low(PAD_GPIO10);
#elif((MS_BOARD_TYPE_SEL == BD_MST061B_10AZU_14014))
    mdrv_gpio_set_low(PAD_TCON1);
#elif((MS_BOARD_TYPE_SEL == BD_XL3_MEGA_NASA))
    mdrv_gpio_set_low(PAD_GPIO21);
#else
  #error "Please select correct boards"
#endif
}

void start(void)
{
    MDrv_WDT_Init(E_WDT_DBGLV_NONE);
    MDrv_WDT_Stop(E_WDT_DBGLV_NONE);

    InitialSystemPowerDown();
    MDrv_InitConsole();

    printf("\r\n Hello Nasa standby mode \r\n");
    printf("\r\n Console Initial OK (PM) \r\n");

    MDrv_XC_SetIOMapBase_i();
    mdrv_gpio_init();
    //MDrv_IIC_Init();

    //Initialize MsOS, Register Interrupt
    MsOS_CPU_AttachException( E_EXCEPTION_TRAP, ProcessSysTrap, E_EXCEPTION_TRAP );
    MsOS_Init();
    MDrv_ISR_Init();

    //Register & Initialize Timer
    MDrv_Timer_ISR_Register();
    MDrv_Timer_Init();
    MDrv_Interrupt_Init();

    MDrv_Init_Varilabe();

    // Init Wakeup Device
    MDrv_CheckWakeupDeviceFromAP();

    // Turn off standby power
    MDrv_Power_TurnOffStandby();

    // jump to main() should never return
    main();

    while(1);

}

