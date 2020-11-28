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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ( ß¡±MStar Confidential Information ßÆØ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "datatype.h"
#include "drvGlobal.h"
#include "drvAeonUART.h"
#include "risc32_spr.h"
#include "hwreg.h"
#include "Board.h"
#include "drv_miu_init.h"

///////////////////////////////////////////////////////////////////////////////
// power up and turn on clock
///////////////////////////////////////////////////////////////////////////////
#define MIU0_SIZE 0x4000000
#define EULER_MIU_UNIT 0x8
#define EULER_FPGA_VERIFY 0
#define RTL_SIMULATION  0

#if(MIU_SPEED == DDR2_1066MHz)//MCP : Internal DDR2 1066MHz
#define DRAM_VDOR_WB         1
#define DRAM_VDOR_ESMT       2
#define DRAM_VDOR_TYPE       DRAM_VDOR_WB//DRAM_VDOR_ESMT
#endif
///////////////////////////////////////////////////////////////////////////////
// power up and turn on clock
///////////////////////////////////////////////////////////////////////////////
#define  MDrv_MaskAllMiuRequest()   do{\
                              } while(0)

#define  MDrv_UnMaskAllMiuRequest()   do{\
                              } while(0)


#define MDrv_OpenAllMiumask()  do{\
                                MDrv_Write2Byte(0x10121a, 0x0001);   /* turn on report counter*/\
                                MDrv_Write2Byte(0x101246, 0x0000);   /* de_mask all miu_0 request & reset */\
                                MDrv_Write2Byte(0x101266, 0x0000);   /* de_mask all miu_0 request & reset */\
                                MDrv_Write2Byte(0x101286, 0x0000);   /* de_mask all miu_0 request & reset */\
                                MDrv_Write2Byte(0x1012a6, 0x0000);   /* de_mask all miu_0 request & reset */\
                              } while(0)

#define MDrv_CloseAllMiumask()  do{\
                                MDrv_Write2Byte(0x10121a, 0x0000);   /* turn off report counter*/\
                                MDrv_Write2Byte(0x101246, 0x7FFE);   /* mask all miu_0 request & reset but G(0,0) & G(0,15)*/\
                                MDrv_Write2Byte(0x101266, 0xFFFF);   /* mask all miu_0 request & reset */\
                                MDrv_Write2Byte(0x101286, 0xFFFF);   /* mask all miu_0 request & reset */\
                                MDrv_Write2Byte(0x1012a6, 0xFFFF);   /* mask all miu_0 request & reset */\
                              } while(0)

// Auto DQS phase detection
#define ENABLE_AUTO_DQS             1
#define AUTO_DQS_START_ADDRESS      0x1FFF000
#define SET_AUTO_DQS_START_ADDR     (AUTO_DQS_START_ADDRESS/0x1000)  //4kbyte/unit in register setting
#define AUTO_DQS_VERIFY_SIZE        0x80000
#define SET_AUTO_DQS_VERIFY_SIZE    (AUTO_DQS_VERIFY_SIZE/0x8)      //16 byte/unit in register setting

// Auto DQS phase detection
#define AUTO_DQS_DUMP(x) x

U8 hex[] = "0123456789ABCDEF";
//const U8 g_MemTestMode[] = { 0x07, 0x09, 0x05, 0x03, 0x0B };
U8 g_MemTestMode[] = { 0x83,0x87, 0x85};  //, 0x05, 0x03, 0x0B };
U8 g_MemTestMask[] = { (U8)~33, (U8)~0xCC };

#define DQSN(step)  (1 - step / 16) // (step / 16)


static U8 MDrv_MIU_AutoDQSPhase( U8 u8Miu )
{
#if ENABLE_AUTO_DQS
    U8 u8Step;
    U8 u8Mode;
    U8 u8DqsSum;
    U8 u8DqsCnt,u8TotalGoodPhase;
    U8 u8DqsPhase;
    U8 u8DefDqsPhase;
    U8 bUseDefDqsPh;
    U32 u32DqsPhAddr = 0;
    U32 u32PhaseResult = 0;
    u32DqsPhAddr = 0x110d6e;
    u8Miu=u8Miu;
    
    //set test area here
    MDrv_Write2Byte(0x1012e2, SET_AUTO_DQS_START_ADDR);  //0x3FFF );     //(4kbytes)/unit
    MDrv_Write4Byte(0x1012e4, SET_AUTO_DQS_VERIFY_SIZE); //0x8000 );     //(16 byte)/unit
    MDrv_Write2Byte(0x1012e8, 0x5aa5);   //test data

    u8DqsSum = 0;
    u8DqsCnt = 0;
    u8DqsPhase = 0;
    bUseDefDqsPh = 0;
    u8TotalGoodPhase=0;

    u8DefDqsPhase = MDrv_ReadByte( u32DqsPhAddr );
    printf("\n\r%02X\n",MDrv_ReadByte(u32DqsPhAddr));

    for ( u8Step = 0; u8Step < 32; u8Step++ )
    {
       // MDrv_WriteByte( 0x1012e7, g_MemTestMask[DQSN(u8Step)] );

        AUTO_DQS_DUMP( if (!(u8Step & 0x0F)) uart_putc( '[' ) );

        MDrv_WriteByte( u32DqsPhAddr, DQSN(u8Step) ? ((u8Step & 0x0F) << 4 | 0x07) : ((u8Step & 0x0F) | 0x70));

        for ( u8Mode = 0 ; u8Mode < sizeof(g_MemTestMode) ; ++u8Mode )
        {
            // enable test, order (high byte then low byte) is important
            MDrv_WriteByte(0x1012e1, 0x00);
            MDrv_WriteByte(0x1012e0, g_MemTestMode[u8Mode]);  // pattern from data
            while ( !MDrv_ReadRegBit(0x1012e1, BIT7) ) ;
            if ( MDrv_ReadRegBit(0x1012e1, BIT6) )
            {
                break;
            }
            MDrv_WriteByte(0x1012e0, 0x00);
        }
        MDrv_WriteByte(0x1012e0, 0x00);

        if ( u8Mode ==  sizeof( g_MemTestMode ) )
        {
            AUTO_DQS_DUMP( uart_putc( (u8Step % 16) < 10 ? ('0' + (u8Step % 16)) : ('A' + (u8Step % 16) - 10)) );
            u8DqsSum += (u8Step & 0x0F);
            ++u8DqsCnt;
            u32PhaseResult |= (1 << u8Step);
        }

        if ( (u8Step % 16 == 15) )
        {
            if (u8DqsCnt == 0)
            {
                bUseDefDqsPh = 1;
            }
            else
            {
                u8DqsPhase |= ((u8DqsSum / u8DqsCnt) << (DQSN( u8Step ) * 4));
                u8DqsSum = 0;
                u8TotalGoodPhase+=u8DqsCnt;
                u8DqsCnt = 0;
            }
            AUTO_DQS_DUMP( uart_putc( ']' ) );
        }
    }
    MDrv_WriteByte( u32DqsPhAddr, bUseDefDqsPh ? u8DefDqsPhase : u8DqsPhase );
    MDrv_Write4Byte(0x103390, u32PhaseResult);
    //clear miu1 result
    MDrv_Write4Byte(0x103394, 0);

    AUTO_DQS_DUMP( uart_putc( ' ' );
                   printf( "\n\r%04X\n", MDrv_ReadByte(u32DqsPhAddr) );
                   uart_putc( '\n' ) );
    return( u8TotalGoodPhase );
#else
    u8Miu=u8Miu;
    return 0;
#endif
}

extern U16 risc32_regbase[];

unsigned char *loader_2nd_lma;
unsigned char *loader_2nd_vma;
unsigned char *loader_2nd_len;
extern void loadAP(void);
extern void CopyFLH2MIU(U32 dst, U32 src, U32 size);
void MDrv_WriteRegTbl32( const U16 * pRegTable );
//================================================
void MDrv_WriteRegTbl32( const U16 * pRegTable )
{
   U16 u16Index; // register index
   U16 u16Dummy;

   u16Dummy = 2000;

   u16Index=0;
   while( u16Dummy )
   {
       if ( pRegTable[u16Index] == 0xffff )
          break;
       RIU[ (0x100000ul+pRegTable[u16Index]) ]=pRegTable [u16Index+1];
       u16Index+=2;
   }
}

static void MDrv_SysDelayUs(U32 u32InputTime)
{
    U32 u32DelayTime;
    U16 u16TMRStatus;

    u32DelayTime = 12 * u32InputTime;
    MDrv_Write2Byte(0x003024, u32DelayTime & 0x0000FFFF);
    MDrv_Write2Byte(0x003026, u32DelayTime >>16);
    MDrv_Write2Byte(0x003020, (MDrv_Read2Byte(0x003020) | BIT1));

    do{
        u16TMRStatus = MDrv_Read2Byte(0x003022);
        u16TMRStatus &= BIT0;
    }while(u16TMRStatus == 0);
}

void BL_Init(void);
#define UART0_BAUDRATE 115200
#define UART0_BAUDRATE_FPGA     38400


//#################################
// Step 1. Turn On Required Clocks
//#################################
static const MS_REG_INIT TurnOnAllClk[] =
{
    //adcpll_top
    _RV32_1(0x10250E,  0x3F),    //soft-reset atop/pllb/adcb/adca/plla
    _RV32_1(0x10250E,  0x00),
    _RV32_1(0x102508,  0x00),    //power on adc_atop
    _RV32_1(0x102509,  0x00),
    _RV32_1(0x1025B4,  0x00),
    _RV32_1(0x10250A,  0x00),
    _RV32_1(0x10250B,  0x00),
    _RV32_1(0x10250C,  0x00),
    _RV32_1(0x10250D,  0x00),
    _RV32_1(0x1025BC,  0x00),
    _RV32_1(0x1025BD,  0x00),
    _RV32_1(0x102590,  0x08),    //Enable the IDAC(Ch1), Control the output voltage range of IDAC(Ch1): 2'b00 (1.3V)
    _RV32_1(0x10257E,  0x30),    //Enable SOG MUX
    _RV32_1(0x1025BD,  0x00),    //Power on : reg_pdn_adcpla_pdac_y

    //dvi_atop
    _RV32_1(0x11090C,  0x00),    //power on xtal/plla/adca/pllb/adb.....
    _RV32_1(0x11090D,  0x00),
    _RV32_1(0x1109C0,  0x00),    //power on DVI PLL,bias ....
    _RV32_1(0x1109C1,  0x00),
    _RV32_1(0x1109D2,  0x00),    //power on DVI_2 PLL,bias ....
    _RV32_1(0x1109D3,  0x00),
    _RV32_1(0x110906,  0x00),    //dummy?
    _RV32_1(0x110907,  0x00),    //dummy?

    //clk_dvi in pm_sleep
    _RV32_1(0x000E94,  0x00),
    _RV32_1(0x000E95,  0x00),
    _RV32_1(0x000E96,  0x00),
    _RV32_1(0x000E97,  0x00),
    _END_OF_TBL32_

};

//#################################
// Step 2. System MPLL Initialization
//#################################
static void MDrv_SysInitMPLL( void )
{
    // DMOD ATOP XTAL Setting
    MDrv_WriteByte(0x101E38, 0x00); //turn on bit0=0 : mpll power on, bit1 =0: MIPSPLL and bit 2: USB PLL
    MDrv_WriteByte(0x101E39, 0x00);
    MDrv_WriteByte(0x101ED2, 0x00); //Enable MPLL input reference clock

    MDrv_WriteByte(0x112003, 0x00);
    MDrv_WriteByte(0x11286B, 0x24);
    MDrv_WriteByte(0x11286D, 0x00);

    // MPLL Setting
    MDrv_WriteByte(0x110C02, 0x00); //[0]: mpll_in_select=0, selec 1.2v clock in
    MDrv_WriteByte(0x110C03, 0x00); //[8]: mpll_pd = 0,[9]: adc216_pd = 0,[10]: adc413_pd = 0,

    // DSP PLL Setting
    MDrv_WriteByte(0x110c40, 0x40);
    MDrv_WriteByte(0x110c41, 0x00);
    //MIPSPLL_TEST             0x110C40[15:0]  = 16'd0 (default) => 16'h40

    MDrv_WriteByte(0x110c44, 0x21);
    MDrv_WriteByte(0x110c45, 0x05);
    //MIPSPLL_LOOP_DIV_FIRST   0x110C44[9:8]   = 2'b01 (default)
    //MIPSPLL_INPUT_DIV_FIRST  0x110C44[5:4]   = 2'b00 (default) => 2'b10
    //MIPSPLL_CLK33_IN_DIV2_EN 0x110C44[0]     = 1'b1  (default)

    MDrv_WriteByte(0x110c46, 0x2c);
    MDrv_WriteByte(0x110c47, 0x11);
    //MIPSPLL_OUTPUT_DIV_FIRST 0x110C46[13:12] = 2'd0  (default) => 2'b01
    //MIPSPLL_VCO_DIV2_DISABLE 0x110C46[8]     = 1'b0  (default) => 1'b1
    //MIPSPLL_LOOP_DIV_SECOND  0x110C46[7:0]   = 8'h16 (default) => 8'h2C

  	MDrv_WriteByte(0x110c48, 0x80);
  	MDrv_WriteByte(0x110c49, 0x00);
  	//MIPSPLL_ENDISC           0x110C48[9]     = 1'd0  (default)
  	//MIPSPLL_ENFRUN           0x110C48[8]     = 1'd0  (default)
  	//MIPSPLL_IBIAS_ICTRL      0x110C48[7:6]   = 2'd2  (default)
  	//MIPSPLL_ICP_ICTRL        0x110C48[5:4]   = 2'd2  (default) => 2'b00
  	//MIPSPLL_TEST_EN          0x110C48[0]     = 1'd0  (default)

  	MDrv_WriteByte(0x110c42, 0x01);
  	MDrv_WriteByte(0x110c43, 0x06);
  	//MIPSPLL_CLK_ADC432M_PD   0x110C42[10]    = 1'b1  (Power Down unused output)
  	//MIPSPLL_CLK_ADC216M_PD   0x110C42[9]     = 1'b1  (Power Down unused output)
  	//MIPSPLL_PD               0x110C42[8]     = 1'd1  (default, DFT Gated)
  	//MIPSPLL_IN_SELECT        0x110C42[0]     = 1'b1  (default, Ref. clock from MPLL_CLK_IN_33; Designer prefered)

}


//#################################
// Step 3. USB PLL Initialization
///#################################
static void MDrv_USBPLL_Init( void )
{
    // turn 480Mhz in USB
    // USBC0 <--> UTMI0
    MDrv_WriteByte(0x100700, 0x0a);    // Disable MAC initial suspend, Reset UHC
    MDrv_WriteByte(0x100700, 0x28);    // Release UHC reset, enable UHC and OTG XIU function

    MDrv_WriteByte(0x103aa2, 0x88);    // PLL_TEST[30:28]: 3'b010 for IBIAS current select
    MDrv_WriteByte(0x103aa3, 0x20);    // PLL_TEST[23] CLK480 to digital output source selection
    // PLL_TEST[15]: Bypass 480MHz clock divider
    MDrv_WriteByte(0x103aa0, 0x51);    // PLL_TEST[7:4]: 5'b0101_0 for 1.0x
    MDrv_WriteByte(0x103aa1, 0x80);    // PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C
    MDrv_SysDelayUs(1000);             // delay 1ms
    MDrv_WriteByte(0x103a82, 0x84);    // Enable CLK12_SEL bit <2> for select low voltage crystal clock
    MDrv_WriteByte(0x103a83, 0x20);    // Enable CLK12_SEL bit <2> for select low voltage crystal clock
    MDrv_WriteByte(0x103a89, 0x00);    //
    MDrv_WriteByte(0x103a88, MDrv_ReadByte(0x103a88) & ~(0x80));    // #7=0 Enable band-gap current
    MDrv_WriteByte(0x103a81, 0x6b);    // Turn on reference voltage and regulator
    MDrv_WriteByte(0x103a80, 0xc3);    // reg_pdn: bit<15>, bit <2> ref_pdn
    MDrv_SysDelayUs(1000);             // delay 1ms
    MDrv_WriteByte(0x103a81, 0x69);    // Turn on UPLL, reg_pdn: bit<9>
    MDrv_WriteByte(0x103a80, 0xc3);    // Turn all (including hs_current) use override mode
    MDrv_SysDelayUs(2000);             // delay 2ms
    MDrv_WriteByte(0x103a81, 0x00);
    MDrv_WriteByte(0x103a80, 0x01);    //#7=0

}

//#################################
// Step 4. System Clock Initialization
//#################################
static const MS_REG_INIT InitialSystemClk[] =    //CLK_GEN_0
{
    _RV32_1(0x100b00, 0x10),  // turn xtal clk  #4 = 1 (CKg_RIU must be "1" in VIF input)
    _RV32_1(0x100b02, 0x07),  // SRAM bist test clk 7:xtal, 6:54M, 5:62M 4:72M 3:86M 2:108M 1:123M 0:144M
    // Dig_top_pm mcu clock
    _RV32_1(0x000f40, 0x00),      // step 1/2:set hk51 to 216M
    _RV32_1(0x000f40, 0x80),      // step 2/2:set hk51 to 216M
    // dig_top
    _RV32_1(0x100b21, 0x00),      //turn ckg_mcu for turn riu_bridge,db_bus....,db_bus....
    _RV32_1(0x100b20, 0x01),      //change to fast clock
    // clk_aeon
    _RV32_1(0x100b24, 0x00),      // aeon clk aeon to 216Mhz
    _RV32_1(0x100b24, 0x80),      // change to fast clock
    // clk_R2
    _RV32_1(0x100b25, 0x08),      // aeon clk r2 to 216Mhz
    _RV32_1(0x100b25, 0x28),      // change to fast clock
    // clk_UART
    _RV32_1(0x100b27, 0x0C),      // uart0 clk to 123Mhz
    _RV32_1(0x100b28, 0x0C),      // uart1 clk to 123Mhz
    //_RV32_1(0x100b29, 0x0C),      // uart2 clk to 123Mhz
    // clk_spi
    // Dig_top_pm clk_spi
    _RV32_1(0x000F41, 0x14),      // clk spi to 72Mhz
    _RV32_1(0x000F41, 0x54),      // change to fast clock
    // dig_top clk_spi
    _RV32_1(0x100b2c, 0x14),      // clk spi to 72Mhz
    _RV32_1(0x100b2c, 0x34),      // change to fast clock
    // clk_pcm
    _RV32_1(0x100b34, 0x00),      // set pcm clk to 27Mhz,  pcmcia
    // clk_jtag
    _RV32_1(0x100b35, 0x00),      // turn tck clk on
    // MIU relative
    _RV32_1(0x100b3d, 0x00),      // MPLL syn = 216MHz ???
    
    _RV32_1(0x100b3e, 0x0c),      // CLK_MIU = 216MHz (fixed)

    _RV32_1(0x100bfc, 0x01),      // reg_clkgen0_reserved0 ??
    // clk_vd
    _RV32_1(0x100b40, 0x00),      //clk vd_sel, 0: vd_adc_clk(Y), 1: adc_clk(RGB)
    _RV32_1(0x100b41, 0x00),      //ckg_vd= vd_sel
    // clk_vd mcu
    _RV32_1(0x100b42, 0x10),      //ckg_vdmcu = 108Mhz , need fine tune in demod
    _RV32_1(0x100b43, 0x04),      //clk vd_200=216Mhz
    // clk_mail
    _RV32_1(0x100b44, 0x0c),      //clk mail box0 =xtal  <<hk51 <--mail box 0--> aeon
    _RV32_1(0x100b45, 0x0c),      //clk mail box1 =xtal  <<hk51 <--mail box 1--> aeon
    _RV32_1(0x100b46, 0x00),      //tur on vd2x
    _RV32_1(0x100b47, 0x00),      //tur on vd_32fsc
    // clk_ve
    _RV32_1(0x100b48, 0x00),      //ckg_Ve=27M, remove
    _RV32_1(0x100b49, 0x00),      //ckg_Vedec=27M, remove
    _RV32_1(0x100b4a, 0x0c),      //ckg_Ve_in=clk_DC0, remove
    _RV32_1(0x100b4c, 0x04),      //clk_daca2=VD_clk
    // clk_dscb2
    _RV32_1(0x100b4d, 0x04),      //clk_dscb2=VD_CLK
    // clk_tsp
    _RV32_1(0x100b50, 0x08),      //clk_ts0=demode, CLK_TS1= gating
    _RV32_1(0x100b54, 0x00),      //CLK_TSP = 144M
    _RV32_1(0x100b55, 0x00),      //Ckg_stc0 = stc0_sync_output
    _RV32_1(0x100b60, 0x00),      //ckg_vd_mheg5 =160Mhz
    _RV32_1(0x100b62, 0x08),      //ckg_HVD =144Mhz
    _RV32_1(0x100b6a, 0x0c),      //ckg_jpg=160M  0:72m 4:108m c:123m c:160m
    // clk_mvdxx
    _RV32_1(0x100b72, 0x00),      //mvd_clk=144m ON
    _RV32_1(0x100b73, 0x00),      //mvd2_clk=172m ON
    _RV32_1(0x100b74, 0x00),      //mvd_chroma ON
    _RV32_1(0x100b75, 0x00),      //mvd_luma_a ON
    _RV32_1(0x100b76, 0x00),      //mvd_luma_b ON
    _RV32_1(0x100b77, 0x00),      //mvd_luma_c ON
    _RV32_1(0x100b78, 0x00),      //mvd_rmem ON
    _RV32_1(0x100b79, 0x00),      //mvd_rmem1 ON
    // clk_gop and clk_ge
    _RV32_1(0x100b80, 0x00),      //clk_gop_0 ==odclk_p
    _RV32_1(0x100b81, 0x00),      //clk_gop_1 ==odclk_p
    _RV32_1(0x100b83, 0x01),      //gating first, ((clk_gopd (DWIN) = CLK_ODCLK))
    _RV32_1(0x100b86, 0x00),      //psram0=on, select gop0
    _RV32_1(0x100b87, 0x00),      //psram1=on, select gop0
    _RV32_1(0x100b90, 0x00),      //ckg_ge=216M
    // clk_dc
    _RV32_1(0x100b98, 0x00),      //ckg_dc0=synchronous mode      #TBD: what is synchronous mode?
    _RV32_1(0x100b99, 0x00),      //ckg_dc1=synchronous mode
    // SC
    _RV32_1(0x100ba3, 0x04),      //main_window fclk_f2, and select fclk
    _RV32_1(0x100ba4, 0x04),      //main_window ficlk2_f2, and select fclk
    _RV32_1(0x100ba5, 0x00),      //flck=170M
    _RV32_1(0x100ba6, 0x1c),      //odclk (output pixel clock) = LPLL
    _RV32_1(0x100ba7, 0x1c),      //bt656 = LPLL
    // clk_mod
    _RV32_1(0x103200, 0x00),      //switch bank
    _RV32_1(0x103241, 0x00),      //dot_mini_* clk= clk_lpll_buf
    _RV32_1(0x100bae, 0x00),      //fifo mmini = LPLL   //LVDS   fifo_clk=mini_lvds         #TBD: not found (the same as T3, by jeff)
    _RV32_1(0x103362, 0x00),      //ckg_tx_mod
    // clk_vif
    _RV32_1(0x103314, 0x00),      // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    _RV32_1(0x103315, 0x01),      // reg_ckg_dvbtc_innc@0x0a[11:8]
    _RV32_1(0x10330a, 0x00),      // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    _RV32_1(0x10330b, 0x00),
    _RV32_1(0x10331a, 0x04),      // reg_ckg_vifdbb_dac@0x0d[3:0] : MPLLDIV10/2=43MHz
    _RV32_1(0x10331b, 0x04),      // reg_ckg_vifdbb_vdac@0x0d[11:8]: MPLLDIV10/2=43MHz
    _RV32_1(0x10331c, 0x00),      // reg_ckg_vifdbb_43m@0x0e[3:0] : MPLLDIV10/2=43MHz
    _RV32_1(0x10331d, 0x00),      // reg_ckg_vifdbb_144m@0x0e[11:8]: ADC_CLKOUT=144MHz
    // ckg_idclk_lpll
    _RV32_1(0x103364, 0x04),      // reg_ckg_idclk_lpll and select clk_idclk2

    _END_OF_TBL32_
};

static int InitialSystemPowerUp( void )
{
    int i;

    #if EULER_FPGA_VERIFY
    return 0;
    #endif

	//########################################
    //
    // Very important for SPI fast read mode
    //
    MDrv_WriteByte(0x0008e2, 0xFF);
    MDrv_WriteByte(0x0008e3, 0x0F);
    MDrv_WriteByte(0x000E6A, 0x30);      // max SPI pad driving
    MDrv_WriteByte(0x0008e4, 0x01);      //Enable fast read mode, (SPI command is 0x0B)

    for (i = 0; i < 500; i++)
        __asm__ __volatile__("l.nop");

    // Need a branch for fast mode to take effect,
    // use inline assembly to avoid eliminated by compiler or linker
    __asm__ __volatile__ (
        "\tl.j      1f\n"
        "\tl.nop    0\n"
        "\tl.nop    0\n"
        "1:");
	//########################################

    MDrv_WriteRegTbl_32( TurnOnAllClk );
    MDrv_SysInitMPLL();
    MDrv_USBPLL_Init();
    MDrv_WriteRegTbl_32( InitialSystemClk );
    //read revision id from chiptop 0x101e_67[15:8]
    if(MDrv_ReadByte(0x101ecf)>=(U8)0x01)//above U02
    {
        MDrv_WriteRegBit(0x1032f1,1,BIT0); //enable Bank MOD LDO 0x1032_78[8] =1
    }
    return 1;
}

static void MDrv_WriteMiuAtopTbl( const MS_REG_INIT * pRegTable )
{
    U32 u32Index; // register index
    while( 1 )
    {
        u32Index = (((U32)pRegTable[0] << 16) + ((U32)pRegTable[1] << 8) + pRegTable[2] );
        if (u32Index == 0xFFFFFF) // check end of table
            break;
        u32Index &= 0x1FFFFF;
        MDrv_Write2Byte( u32Index         , ( pRegTable[3] + (pRegTable[4] << 8))  );   //miu0_atop
        pRegTable += 5;
    }
}

static void MDrv_WriteMiuTbl( const MS_REG_INIT * pRegTable )
{
    U32 u32Index; // register index
    while( 1 )
    {
        u32Index = (((U32)pRegTable[0] << 16) + ((U32)pRegTable[1] << 8) + pRegTable[2] );
        if (u32Index == 0xFFFFFF) // check end of table
            break;
        u32Index &= 0x1FFFFF;
        MDrv_Write2Byte(u32Index           , ( pRegTable[3] + (pRegTable[4] << 8))  ); //miu0
        pRegTable += 5;
    }
}

static void  MDrv_AutoInitMiuCycle(void)
{
    MDrv_Write2Byte( 0x101200, 0x0000);  /*reg_0x1200= 0x0000,*/
    MDrv_Write2Byte( 0x101200, 0x0008);  //reg_0x1200= 0x0008, DRAM reset
    MDrv_Write2Byte( 0x101200, 0x000c);  //reg_0x1200= 0x000c, DRAmreset+DRAM chip select
    MDrv_SysDelayUs(1000);               //delay 1ms
    MDrv_Write2Byte( 0x101200, 0x000e);  //reg_0x1200= 0x000E,DRAmreset+DRAM chip select+enable CKE + ODT ON
    MDrv_SysDelayUs(1000);               //delay 1ms
    #if (MIU_SPEED == DDR2_800MHz)//MCP DDR2
    MDrv_Write2Byte((0x101200 ), 0x001f);//reg_0x1200= 0x000F,DRAmreset+DRAM chip select+enable CKE +auto initial dram cycle
    #elif(MIU_SPEED == DDR2_1066MHz)//MCP DDR2
    MDrv_Write2Byte((0x101200 ), 0x001f);//0x001f//reg_0x1200= 0x001F,DRAmreset+DRAM chip select+enable CKE +auto initial dram cycle + ODT ON
    #elif(MIU_SPEED == DDR3_1333MHz)//MCP DDR3
    MDrv_Write2Byte((0x101200 ), 0x000f);//reg_0x1200= 0x001F,DRAmreset+DRAM chip select+enable CKE +auto initial dram cycle + ODT OFF
    //MDrv_Write2Byte((0x101200 ), 0x001f);//reg_0x1200= 0x001F,DRAmreset+DRAM chip select+enable CKE +auto initial dram cycle + ODT ON
    #else
    #error "MIU interface isn't defined"
    #endif

    MDrv_SysDelayUs(10*1000);            // delay 10ms : wait initial done
    while( (MDrv_Read2Byte(0x101200)&0x8000) == 0x0000 );

    MDrv_Write2Byte( 0x101246, 0x7ffe);
    MDrv_Write2Byte( 0x10121e, 0x0c08);
    MDrv_Write2Byte( 0x1012e0, 0x0000);
    MDrv_Write2Byte( 0x1012e2, 0x0000);
    MDrv_Write2Byte( 0x1012e4, 0x0001);
    MDrv_Write2Byte( 0x1012e6, 0x0000);
    MDrv_Write2Byte( 0x1012e8, 0x5aa5);
    MDrv_WriteRegBit( 0x110d0e, 1, BIT6);
    MDrv_Write2Byte( 0x1012e0, 0x0200);
    MDrv_Write2Byte( 0x1012e0, 0x0201);
    MDrv_Write2Byte( 0x1012e8, 0xffff);
    MDrv_Write2Byte( 0x1012e8, 0xffff);
    MDrv_WriteRegBit (0x110d0e, 0, BIT6);

}

static void MDrv_MiuReset( void )
{
    MDrv_Write2Byte( 0x10121e, 0x0c01 );
    MDrv_Write2Byte( 0x10121e, 0x0c00 );
    MDrv_SysDelayUs(1000);  // delay 1ms
    //PKG type select ( 0:DDR3 ; 1:DDR2_MCP ; 2:DDR2(External) )
  #if (MIU_SPEED == DDR2_800MHz) //DDR2_MCP
    MDrv_Write2Byte( 0x110d7c, 0x0200 ); //reg_sel_vref : [15:8]
    MDrv_Write2Byte( 0x110d7e, 0x0088 );
    MDrv_Write2Byte( 0x110d00, 0x0019 );
    MDrv_SysDelayUs(1000);  // delay 1ms
    MDrv_Write2Byte( 0x110d00, 0x0011 ); //package MCP DDR2
    MDrv_Write2Byte( 0x110d00, 0x0001 ); //package MCP DDR2
    MDrv_Write2Byte( 0x110d02, 0xaaaa );
    MDrv_Write2Byte( 0x110d08, 0x00ff );
    MDrv_Write2Byte( 0x110d74, 0x0077 ); //trig lvl
    MDrv_Write2Byte( 0x110d5c, 0x3333 ); //drvn
    MDrv_Write2Byte( 0x110d5e, 0x3333 ); //drvp
  #elif (MIU_SPEED == DDR2_1066MHz) //DDR2_MCP
    MDrv_Write2Byte( 0x110d7c, 0x0200 ); //reg_sel_vref : [15:8]
    MDrv_Write2Byte( 0x110d7e, 0x0000 );
    MDrv_Write2Byte( 0x110d00, 0x0019 );
    MDrv_SysDelayUs(1000);  // delay 1ms
    MDrv_Write2Byte( 0x110d00, 0x0011 ); //package MCP DDR2
    MDrv_Write2Byte( 0x110d00, 0x0001 ); //package MCP DDR2
    MDrv_Write2Byte( 0x110d02, 0xaaaa );
    MDrv_Write2Byte( 0x110d08, 0x00ff );
    MDrv_Write2Byte( 0x110d74, 0x0077 ); //trig lvl
    MDrv_Write2Byte( 0x110d5c, 0xaaaa ); //drvn
    MDrv_Write2Byte( 0x110d5e, 0xaaaa ); //drvp
  #elif (MIU_SPEED == DDR3_1333MHz)//DDR3 MCP
    #ifdef DDR3_1000MHz
    MDrv_Write2Byte( 0x110d7e, 0x0000 );
    #else
    MDrv_Write2Byte( 0x110d7c, 0x0200 );
    if((MDrv_Read2Byte(0x2008)&BIT7))//check ZQ valid BK_04[7]
        MDrv_Write2Byte( 0x110d7e, (MDrv_Read2Byte(0x2008)&0x3F) ); //ZQ value BK_04[5:0]
    else
        MDrv_Write2Byte( 0x110d7e, 0x0038 );
    #endif
    MDrv_Write2Byte( 0x110d00, 0x0018 );
    MDrv_SysDelayUs(1000);  // delay 1ms
    MDrv_Write2Byte( 0x110d00, 0x0010 ); //package MCP DDR3
    MDrv_Write2Byte( 0x110d00, 0x0800 ); //package MCP DDR3

    MDrv_Write2Byte( 0x110d02, 0xaaaa );
    MDrv_Write2Byte( 0x101202, 0x03a3 );
    MDrv_Write2Byte( 0x110d08, 0x00ff );
    MDrv_Write2Byte( 0x110d74, 0x0044 ); //trig lvl
    MDrv_Write2Byte( 0x110d5c, 0xbbbb ); //drvn
    MDrv_Write2Byte( 0x110d5e, 0xbbbb ); //drvp
  #else
    #error "MIU clock speed isn't defined"
  #endif

}

static void MDrv_Euler_BandWidth_Adjustment(void)
{
  #if (MIU_SPEED == DDR2_800MHz)
    MDrv_Write2Byte(0x101240,0x8001);
    MDrv_Write2Byte(0x101260,0x8001);
    MDrv_Write2Byte(0x101280,0x8001);
    MDrv_Write2Byte(0x1012a0,0x8001);
  #elif (MIU_SPEED == DDR2_1066MHz)
    MDrv_Write2Byte(0x101240,0x8001);
    MDrv_Write2Byte(0x101260,0x8001);
    MDrv_Write2Byte(0x101280,0x8001);
    MDrv_Write2Byte(0x1012a0,0x8001);
  #elif (MIU_SPEED == DDR3_1333MHz)
    MDrv_Write2Byte(0x101240,0x8001);
    MDrv_Write2Byte(0x101260,0x8001);
    MDrv_Write2Byte(0x101280,0x8001);
    MDrv_Write2Byte(0x1012a0,0x8001);
  #else
    #error "MIU interface isn't defined"
  #endif

  #if 1//default bandwidth settings
    //Let these IPs HVD/MVD/G3D(removed in Euler) use MIU Act 2 bank function to improve DRAM total Bandwidth utilization
    MDrv_Write2Byte(0x10122a, 0xa3a4); //act 2 bank for HVD/MVD
    //MDrv_Write2Byte(0x10123e, 0x4000); //reg_post_order_ctrl_en (Removed for U01 / U02 compatible issue)
    MDrv_Write2Byte(0x101242, 0x0020); //limit 128 burst length
    MDrv_Write2Byte(0x101244, 0x0200); //timeout = 512T
    MDrv_Write2Byte(0x101240, 0x8415); //enable round_robin ; member_limit ; timeout ; skip_on
    MDrv_Write2Byte(0x101262, 0x0020); //limit 128 burst length
    MDrv_Write2Byte(0x101264, 0x0200); //timeout = 512T
    MDrv_Write2Byte(0x101260, 0x8415); //enable round_robin ; member_limit ; timeout ; skip_on
    MDrv_Write2Byte(0x101282, 0x0020); //limit 128 burst length
    MDrv_Write2Byte(0x101284, 0x0200); //timeout = 512T
    MDrv_Write2Byte(0x101280, 0x8415); //enable round_robin ; member_limit ; timeout ; skip_on
  #endif
}

static void MDrv_MiuAtopProgramDLL0(void)
{
    //start to program DLL0
    MDrv_Write2Byte(0x110d60,0x000c);
    MDrv_Write2Byte(0x110d60,0x0008);
  #if (MIU_SPEED == DDR2_800MHz)
    MDrv_Write2Byte(0x110d62,0x0c7f); //U02 ECO setting for reg_dll_test[15:8]=0x0c
    MDrv_Write2Byte(0x110d64,0xf200);
    MDrv_Write2Byte(0x110d60,0x2738);
  #elif (MIU_SPEED == DDR2_1066MHz)
    MDrv_Write2Byte(0x110d62,0x007f); //U02 ECO setting for reg_dll_test[15:8]=0x0c
    MDrv_Write2Byte(0x110d64,0xf200);
    MDrv_Write2Byte(0x110d60,0x2738);
  #elif (MIU_SPEED == DDR3_1333MHz)
    MDrv_Write2Byte(0x110d62,0x007f);
    MDrv_Write2Byte(0x110d64,0xf200);
    MDrv_Write2Byte(0x110d60,0x2738);
  #else
    #error "MIU interface isn't defined"
  #endif
    
}

static void MDrv_MiuBistTest( void )
{
    MDrv_Write2Byte(0x1012e0, 0x0000); //disable test
    MDrv_Write2Byte(0x1012e2, 0x0000); //test base address
    MDrv_Write4Byte(0x1012e4, (MIU0_SIZE/EULER_MIU_UNIT)); //test length
    MDrv_Write2Byte(0x1012e8, 0x5aa5);   //test data
    MDrv_Write2Byte(0x1012e0, 0x0003);   //enable test
    while (!MDrv_ReadRegBit(0x1012e1, BIT7));
    if( MDrv_Read2Byte(0x1012e0) & 0x6000 )
        printf("BIST_0 error.\n");
    else
        printf("BIST_0 PASS.\n");
}

static void MDrv_MiuDDRInitMakeup(void)
{
  #if (MIU_SPEED == DDR2_800MHz)
  #elif (MIU_SPEED == DDR2_1066MHz)
  #elif (MIU_SPEED == DDR3_1333MHz)
  #else
  #error "MIU interface isn't defined"
  #endif

}

static int MDrv_Euler_MiuInitial(void)
{
    #if EULER_FPGA_VERIFY
    {
        MDrv_Write2Byte((0x2bc6 ) , 0x3c11);
        MDrv_Write2Byte((0x2bca ) , 0x403c);
        MDrv_Write2Byte((0x2bc4 ) , 0x0004);

        MDrv_Write2Byte((0x101202 ) , 0x0000);
        MDrv_Write2Byte((0x101202 ) , 0x0818);
        MDrv_Write2Byte((0x101204 ) , 0x0185);
        MDrv_Write2Byte((0x101206 ) , 0x0120);
        MDrv_Write2Byte((0x101208 ) , 0x0833);
        MDrv_Write2Byte((0x10120a ) , 0x0c33);
        MDrv_Write2Byte((0x10120c ) , 0x7111);
        MDrv_Write2Byte((0x10120e ) , 0x100e);
        MDrv_Write2Byte((0x101210 ) , 0x0031);

        MDrv_Write2Byte((0x10121e ) , 0x0C01);
        MDrv_Write2Byte((0x10121e ) , 0x0C00);
        MDrv_Write2Byte((0x101200 ) , 0x0008);
        MDrv_Write2Byte((0x101200 ) , 0x000c);

        MDrv_Write2Byte((0x101200 ) , 0x000e);
        MDrv_Write2Byte((0x101200 ) , 0x001f);
        MDrv_Write2Byte((0x10121e ) , 0x0C08);
        return 1;
    }
    #endif

    MDrv_Write2Byte((0x10121e ) , 0x0c00);
    MDrv_Write2Byte((0x10121e ) , 0x0c00);
    MDrv_Write2Byte((0x10121e ) , 0x0c00);
    MDrv_Write2Byte((0x10121e ) , 0x0c01);
    MDrv_Write2Byte((0x10121e ) , 0x0c00);
    MDrv_Write2Byte((0x101202 ) , 0x0000);
    MDrv_Write2Byte((0x101246 ) , 0xFFFE);   //Mask MIU0_group_0
    MDrv_Write2Byte((0x101266 ) , 0xFFFF);   //Mask MIU0_group_1
    MDrv_Write2Byte((0x101286 ) , 0xFFFF);   //Mask MIU0_group_2
    MDrv_Write2Byte((0x1012a6 ) , 0xFFFF);   //Mask MIU0_group_3

    MDrv_WriteMiuAtopTbl (  MIU_ATOP_Init );
    MDrv_SysDelayUs(1000);  // delay 1ms
    MDrv_WriteMiuTbl ( MIU_DDR_Init );
    // compensate DDR initialized settings for U01/U02
    MDrv_MiuDDRInitMakeup();
    MDrv_MiuReset();
    MDrv_AutoInitMiuCycle();
    MDrv_Euler_BandWidth_Adjustment();
    MDrv_MiuAtopProgramDLL0();

    //Pack setting
    MDrv_Write2Byte(0x101228,0x4000);
    //Reduce latency setting

  #if (MIU_SPEED == DDR2_800MHz)
    MDrv_Write2Byte(0x10122a,0x4080);
  #elif (MIU_SPEED == DDR2_1066MHz)
    MDrv_Write2Byte(0x10122a,0x4080);
  #elif (MIU_SPEED == DDR3_1333MHz)
    #ifdef DDR3_1000MHz
    MDrv_Write2Byte(0x10122a,0x0080);
    #else
    MDrv_Write2Byte(0x10122a,0x4080);
    #endif
  #else
    #error "MIU interface isn't defined"
  #endif

    //set dram size //0x1012_69[15:12]
  #if ((MIU_SPEED == DDR2_800MHz) || (MIU_SPEED == DDR2_1066MHz)) //DDR2_MCP
    MDrv_Write2Byte(0x1012d2, 0x6000 ); //reg_dram_size = 64MB
  #else
    MDrv_Write2Byte(0x1012d2, 0x7000 ); //reg_dram_size = 128MB
  #endif

    //mask all
    MDrv_CloseAllMiumask();
    MDrv_MIU_AutoDQSPhase( 0 );
    MDrv_MiuBistTest();
    //unmask all
    MDrv_OpenAllMiumask();
    MDrv_Write2Byte(0x10121e, 0x0c08);
    MDrv_Write2Byte(0x1012fc, 0x4400);

    //for tvtool miu access
    MDrv_Write2Byte(0x002bc6, 0x3c11);
    MDrv_Write2Byte(0x002bca, 0x403c);
    MDrv_Write2Byte(0x002bc4, 0x0004);

    return 1;
}

static void MDrv_InitConsole( void )
{
    #if EULER_FPGA_VERIFY
    {
        uart_init(12000000, UART0_BAUDRATE_FPGA);
        mtspr( SPR_TTMR, 0x40000000 | 12000 );
    }
    #else
    {
      #ifdef __AEONR2__
        uart_init(216000000, UART0_BAUDRATE);
        mtspr( SPR_TTMR, 0x40000000 | 216000 );
      #else
        uart_init(172800000, UART0_BAUDRATE);
        mtspr( SPR_TTMR, 0x40000000 | 172800 );
      #endif
    }
    #endif

}

void BL_Init(void);
void BL_Init(void)
{
    U16 temp=0;
	
    // system MPLL & CLKs initialization
    InitialSystemPowerUp();

    // console initialization
    MDrv_InitConsole();

  #if (RTL_SIMULATION == 0)
    printf("\r\n Euler: %s \r\n", BOARD_NAME);
    printf(" SPI BOOT \r\n");
    printf(" Console Initial OK \r\n");
  #endif

    // disable AVD before MIU init 
    temp = MDrv_Read2Byte(0x10362a);
    temp = temp | 0x0010;
    MDrv_Write2Byte(0x10362a, temp);

    // MIU initialization
    MDrv_Euler_MiuInitial();

  #if (RTL_SIMULATION == 0)
    printf("\n\r MIU Initial OK \n\r");
  #endif

  #if (RTL_SIMULATION == 1)
    while(1);
  #endif

  // Other initialization
  // Configure floating state for MHL
  MDrv_Write2Byte(0x2F2E, 0x0020);

}
