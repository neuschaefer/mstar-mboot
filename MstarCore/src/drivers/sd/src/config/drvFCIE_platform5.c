////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
#include <config.h>
#include "drvFCIE_config.h"

#ifdef SD_USE_FCIE5

#include <common.h>
//#include <stdio.h>
#include <mmc.h>
#include "drvFCIE5.h"

extern unsigned char mmc_ddr_mode;
extern void HalFcie_DumpDebugBus(void);

/**************************************
* Config definition
**************************************/
#define DBG_CR_CLK(MSG)             //MSG

/**************************************
* Local function definition
**************************************/

#if 0// (MS_BOARD_TYPE_SEL == BD_MST029B_10AFVA_A3 || ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3 || ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3 || ENABLE_MSTAR_TITANIA_BD_CUS28_6A801 || ENABLE_MSTAR_TITANIA_BD_MST029B_BOX_A3)
static U8 _halFCIE_Platform_DisableBootMode(void)
{
    U16 regval;

    FCIE_RIU_16_ON(TEST_MODE, WBIT08);
    udelay(100000);

    regval=FCIE_RIU_R16(NC_MISC);

    if( (regval != 0x1F) && (regval != 0x0F) )
    {
        if (regval == 0x0E)
        {
           FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT01);
           while(1)
           {
              udelay(1);
              regval=FCIE_RIU_R16(MIE_EVENT);
              if (regval&WBIT15)
                 break;
           }
           FCIE_RIU_W16(MIE_PATH_CTL, 0);
           FCIE_RIU_W16(JOB_BL_CNT, 0);
           regval=FCIE_RIU_R16(SD_STS);
           FCIE_RIU_W16(SD_STS, regval);
           regval=FCIE_RIU_R16(MIE_EVENT);
           FCIE_RIU_W16(MIE_EVENT, regval);
        }
        FCIE_RIU_W16(CARD_INT_EN, regval);
        return 1;
    }

    FCIE_RIU_W16(JOB_BL_CNT, 1);
    FCIE_RIU_16_ON(SD_MODE, WBIT09);
    udelay(100);
    FCIE_RIU_W16(SD_CTL, WBIT03);

    while(1)
    {
       udelay(10);
       regval=FCIE_RIU_R16(MIE_EVENT);
       if (regval&WBIT02)
           break;
    }

    udelay(1000);
    FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT01);

    while(1)
    {
       udelay(10);
       regval=FCIE_RIU_R16(MIE_EVENT);
       if (regval&WBIT15)
           break;
    }

    FCIE_RIU_W16(MIE_PATH_CTL, 0);
    FCIE_RIU_W16(JOB_BL_CNT, 0);
    regval=FCIE_RIU_R16(SD_STS);
    FCIE_RIU_W16(SD_STS, regval);
    regval=FCIE_RIU_R16(MIE_EVENT);
    FCIE_RIU_W16(MIE_EVENT, regval);

    FCIE_RIU_16_OF(SD_MODE, WBIT09);
    FCIE_RIU_W16(SD_CTL, 0);
    return 0;
}
#endif

/**************************************
* Global function definition
**************************************/
void halFCIE_Platform_Reset_Fcie(void)
{
       //U16 reg;
	U16 u16Reg, u16Cnt;

	//printf("fcie reset ");
	REG_FCIE_W(FCIE_MIE_FUNC_CTL, BIT_SDIO_MOD);

	REG_FCIE_CLRBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n); /* active low */
	REG_FCIE_CLRBIT(reg_sdiopll_0x6f, BIT1|BIT0);		//macro reset

	// FCIE reset - wait
	u16Cnt=0;

	do
	{
		udelay(HW_TIMER_DELAY_1us);

		REG_FCIE_R(FCIE_RST, u16Reg);

	  	if(0x1000 == u16Cnt++)
		{
			printf("FCIE Err: FCIE Reset fail!! :%x\n",u16Reg);
			while(1);
		}

	} while (BIT_RST_STS_MASK  != (u16Reg  & BIT_RST_STS_MASK));

	//[FIXME] is there any method to check that reseting FCIE is done?

	// FCIE reset - clear
	REG_FCIE_SETBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n);
	REG_FCIE_SETBIT(reg_sdiopll_0x6f, BIT1|BIT0);
	// FCIE reset - check

	u16Cnt=0;
	do
	{
		udelay(HW_TIMER_DELAY_1us);
	  	if(0x1000 == u16Cnt++)
		{
			printf("eMMC Err: FCIE Reset fail2:h \n");
			return ;
		}

		REG_FCIE_R(FCIE_RST, u16Reg);

	}while (0  != (u16Reg  & BIT_RST_STS_MASK));

	//printf("ok\n");
    //==================================================
}

void halFCIE_Platform_InitChiptop(void)
{
	//FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
	//FCIE_RIU_16_OF(CHIPTOP_5A,WBIT08|WBIT09);
	//FCIE_RIU_16_ON(CHIPTOP_5A,WBIT08);

	#ifdef BY_PASS_MODE

	FCIE_RIU_16_OF(CHIPTOP_7B,BIT06|BIT07);
	FCIE_RIU_16_ON(CHIPTOP_7B,BIT06);

	FCIE_RIU_16_OF(CHIPTOP_42,0x3F); // bit 0~6 driving mask
	FCIE_RIU_16_ON(CHIPTOP_42,0x0C); // more driving power suggest by Irwin

	FCIE_RIU_16_ON(CHIPTOP_42,0x3f00);
	FCIE_RIU_16_ON(CHIPTOP_43,0x1f);

	FCIE_RIU_16_ON(CHIPTOP_4F,BIT02);			//SDIO PAD1
	FCIE_RIU_16_OF(CHIPTOP_43,WBIT08);
	FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);

	#endif
}

void halFCIE_Disable_Stop_Clock(void)
{
#if ENABLE_AMBER3
    FCIE_RIU_W16(NC_MISC, WBIT14);
#elif ENABLE_AGATE || ENABLE_EAGLE || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_NADAL)
    FCIE_RIU_W16(DEBUG_BUS1, WBIT06 );
#endif
}

void halFCIE_Reset_Toggle_Count(void)
{
#if ENABLE_AMBER3
    FCIE_RIU_W16(NC_MISC, WBIT15);
    udelay(1);
    FCIE_RIU_W16(NC_MISC, 0x0000);
#elif ENABLE_AGATE || ENABLE_EAGLE || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_NADAL)
    FCIE_RIU_W16(DEBUG_BUS1, WBIT07 );
    udelay(1);
    FCIE_RIU_W16(DEBUG_BUS1, 0x0000);
#endif
}

void halFCIE_Set_Read_Toggle_Count(void)
{
 //   FCIE_RIU_W16(SD_DDR_CNT, 0x111);
}

void halFCIE_Set_Write_Toggle_Count(void)
{
  //  FCIE_RIU_W16(SD_DDR_CNT, 0x11A);
}

void halFCIE_Config_DDR_Mode(void)
{

    #if ENABLE_AMBER3

	// Set eMMC SDR/DDR mode pad mux
    FCIE_RIU_16_OF(EMMC_TOP_CFG, CFG_EMMC_PAD_MASK);
    FCIE_RIU_16_ON(EMMC_TOP_CFG, CFG_EMMC_DDR_PAD);

    // Set DDR mode of FCIE
    FCIE_RIU_W16(EMMC_BOOT_CONFIG, 0x0300);


    // Disable DataSync
    FCIE_RIU_16_OF(SD_MODE, R_SD_DATSYNC);

    // Set DQS delay
    FCIE_RIU_W16(DQS_MODE, (2<<10));

    // Set delay cell, this value might changed by each eMMC
    FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, (0xA<<12));

    #elif ENABLE_AGATE


	// Set eMMC SDR/DDR mode pad mux
    FCIE_RIU_16_OF(EMMC_TOP_CFG, CFG_EMMC_PAD_MASK);
    FCIE_RIU_16_ON(EMMC_TOP_CFG, CFG_EMMC_DDR_PAD);

    FCIE_RIU_16_OF(EMMC_BOOT_CFG, WBIT08);


    // Set DDR mode of FCIE
    FCIE_RIU_W16(EMMC_BOOT_CONFIG, 0x0300);

    // Disable DataSync
    FCIE_RIU_16_OF(SD_MODE, R_SD_DATSYNC);

    // Set DQS delay & delay cell
    FCIE_RIU_W16(SM_STS, (2<<12)|(0xc<<8));

    #elif ENABLE_EAGLE || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_NADAL)


    FCIE_RIU_16_ON(FCIE_MACRO_BYPASS,SD_USE_BYPASS);
	FCIE_RIU_16_OF(FCIE_MACRO_BYPASS,FCIE2MACRO_SD_BYPASS);

	// Set DDR mode of FCIE
	FCIE_RIU_16_OF(EMMC_BOOT_CONFIG,R_SD_MODE_MASK);
	FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, R_SD_MACRO_EN | R_SD_DDR_MODE);

	// Disable DataSync
    FCIE_RIU_16_OF(SD_MODE, R_SD_DATSYNC);
	// Set DQS delay & delay cell
	FCIE_RIU_W16(SM_STS, (2<<12)|(0xc<<8));
	#endif
}

const U8 FcieClockIdxNum = 6;

const U32 FCIE_CLOCK[] =
{
    48000, //  0
    43200, //  1
    40000, //  2
    36000, //  3
    32000, //  4
    20000, //  5
      300, //  6
};

#if 0
U8 halFCIE_Platform_SetFcieClock(U32 u32Clock)
{


	//FPGA mode
	//if(u32Clock == FCIE_SLOWEST_CLK)
	//printf("set clock :%x\n",u32Clock);
	//if (u32Clock < 400000)
	//   REG_FCIE_SETBIT(reg_emmcpll_0x1d, BIT0);
	//else
	//{
	 //  printf("set fast clock\n");
	//   REG_FCIE_CLRBIT(reg_emmcpll_0x1d, BIT0);
//	}

	REG_FCIE_SETBIT(FCIE_SD_MODE,BIT_CLK_EN);			//enable clk
	//printf("SD mode:%x\n",REG_FCIE(FCIE_SD_MODE));
	//else
	//	REG_FCIE_CLRBIT(reg_emmcpll_0x1d, BIT0);

	//g_eMMCDrv.u16_ClkRegVal = (U16)u16_ClkParam;


	return 0;
}
#endif


#if ENABLE_CLIPPERS

// find clock close to target but not over

U32 HalSdio_pll_setting(U16 u16_ClkParam)
{
	static U16 u16_OldClkParam=0xFFFF;
	U32 u32_value_reg_emmc_pll_pdiv;

	if(u16_ClkParam == u16_OldClkParam)
		return 0;
	else
		u16_OldClkParam = u16_ClkParam;

	// 1. reset emmc pll
	FCIE_RIU_16_ON(reg_emmc_pll_reset, BIT0);
	FCIE_RIU_16_OF(reg_emmc_pll_reset, BIT0);

	// 2. synth clock
	switch(u16_ClkParam) {
	    case eMMC_PLL_CLK_200M: // 200M
		    FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			#if 0
			CARD_REG16_ON(reg_ddfset_23_16,0x22); // 20xMHz
			CARD_REG16_ON(reg_ddfset_15_00,0x8F5C);
			#else
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x24); // 195MHz
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x03D8);
			#endif
			u32_value_reg_emmc_pll_pdiv =1;// PostDIV: 2
			break;
		case eMMC_PLL_CLK_160M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x2B);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x3333);
			u32_value_reg_emmc_pll_pdiv =1;// PostDIV: 2
			break;
		case eMMC_PLL_CLK_140M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x31);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x5F15);
			u32_value_reg_emmc_pll_pdiv = 1;// PostDIV: 2
			break;
		case eMMC_PLL_CLK_120M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x39);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x9999);
			u32_value_reg_emmc_pll_pdiv = 1;// PostDIV: 2
			break;
		case eMMC_PLL_CLK_100M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x45);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x1EB8);
			u32_value_reg_emmc_pll_pdiv = 1;// PostDIV: 2
			break;
		case eMMC_PLL_CLK__86M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x28);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x2FA0);
			u32_value_reg_emmc_pll_pdiv = 2;// PostDIV: 4
			break;
		case eMMC_PLL_CLK__80M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x2B);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x3333);
			u32_value_reg_emmc_pll_pdiv = 2;// PostDIV: 4
			break;
		case eMMC_PLL_CLK__72M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x30);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x0000);
			u32_value_reg_emmc_pll_pdiv = 2;// PostDIV: 4
			break;
		case eMMC_PLL_CLK__62M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x37);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0xBDEF);
			u32_value_reg_emmc_pll_pdiv = 2;// PostDIV: 4
			break;
		case eMMC_PLL_CLK__52M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x42);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x7627);
			u32_value_reg_emmc_pll_pdiv = 2;// PostDIV: 4
			break;
		case eMMC_PLL_CLK__48M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x48);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x0000);
			u32_value_reg_emmc_pll_pdiv = 2;// PostDIV: 4
			break;
		case eMMC_PLL_CLK__40M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x2B);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x3333);
			u32_value_reg_emmc_pll_pdiv = 4;// PostDIV: 8
			break;
		case eMMC_PLL_CLK__36M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x30);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x0000);
			u32_value_reg_emmc_pll_pdiv = 4;// PostDIV: 8
			break;
		case eMMC_PLL_CLK__32M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x36);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x0000);
			u32_value_reg_emmc_pll_pdiv = 4;// PostDIV: 8
			break;
		case eMMC_PLL_CLK__27M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x40);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x0000);
			u32_value_reg_emmc_pll_pdiv = 4;// PostDIV: 8
			break;
		case eMMC_PLL_CLK__20M:
			FCIE_RIU_16_OF(reg_ddfset_23_16,0xffff);
			FCIE_RIU_16_OF(reg_ddfset_15_00,0xffff);
			FCIE_RIU_16_ON(reg_ddfset_23_16,0x2B);
			FCIE_RIU_16_ON(reg_ddfset_15_00,0x3333);
			u32_value_reg_emmc_pll_pdiv = 7;// PostDIV: 16
			break;
		default:
			printf("eMMC Err: emmc PLL not configed %x\n", u16_ClkParam);
			return 0xff;
			break;
	}

	// 3. VCO clock ( loop N = 4 )
	FCIE_RIU_16_OF(reg_sdiopll_fbdiv, 0xFFFF);
	FCIE_RIU_16_ON(reg_sdiopll_fbdiv, 0x6);// PostDIV: 8

	// 4. 1X clock
	FCIE_RIU_16_OF(reg_sdiopll_pdiv, BIT2|BIT1|BIT0);
	FCIE_RIU_16_ON(reg_sdiopll_pdiv, u32_value_reg_emmc_pll_pdiv);// PostDIV: 8

	if(u16_ClkParam==eMMC_PLL_CLK__20M) {
	    FCIE_RIU_16_ON(reg_emmc_pll_test, BIT10);
	}
	else {
		FCIE_RIU_16_OF(reg_emmc_pll_test, BIT10);
	}

	mdelay(1); // asked by Irwin

	return 0;
}

static U8 u8CurrentPadType = SDIO_MODE_GPIO_PAD_BPS;

U8 halFCIE_Platform_SetFcieClock(U32 u32Clock)
{
    U8 u8ClockSlector;
	static U32 u32_OldClock=0xFFFFFFFF;

	//printf("halFCIE_Platform_SetFcieClock(%ld)\n", u32Clock);

	if(u32_OldClock == u32Clock)
		return 0;
	else
		u32_OldClock = u32Clock;


    if(u32Clock>1000)
    {
        DBG_CR_CLK(printf("Set FCIE clock as %d.%d MHz, ", u32Clock/1000, (u32Clock%1000)/100 ) );
    }
    else
    {
        DBG_CR_CLK(printf("Set FCIE clock as %d KHz, ", u32Clock));
    }

    for(u8ClockSlector=0; u8ClockSlector<=FcieClockIdxNum; u8ClockSlector++)
    {
        if( FCIE_CLOCK[u8ClockSlector] <= u32Clock )
		{
			break;
        }
    }

    if(u8ClockSlector>FcieClockIdxNum)
    {
        DBG_CR_CLK(printf("Error!!! Can not find proper clock!\r\n"));
		while(1);
        return 0x01;
    }

    if(u32Clock>1000)
    {
        DBG_CR_CLK(printf("select FCIE clock as %d.%d MHz\r\n", FCIE_CLOCK[u8ClockSlector]/1000, (FCIE_CLOCK[u8ClockSlector]%1000)/100));
    }
    else
    {
        DBG_CR_CLK(printf("select FCIE clock as %d KHz\r\n", FCIE_CLOCK[u8ClockSlector]));
    }

    FCIE_RIU_16_ON(REG_CLK_SDIO, WBIT06);
    FCIE_RIU_16_OF(REG_CLK_SDIO, WBIT05+WBIT04+WBIT03+WBIT02); // mask all clock select

	//printf("switch to clock: %d\n", u8ClockSlector);

    switch(u8ClockSlector)
    {
		case 0: // 48M
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0xF<<2);
			break;

		case 1: // 43.2M
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0x5<<2);
			break;

		case 2: // 40M
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0x4<<2);
			break;

		case 3: // 36M
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0x3<<2);
			break;

		case 4: // 32M
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0x2<<2);
			break;

		case 5: // 20M
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0x1<<2);
			break;

		case 6: // 300K
		    FCIE_RIU_16_ON(REG_CLK_SDIO, 0xD<<2);
			break;

		default:
			printf("SDIO Err: wrong clock selector!\n");
			while(1);
			break;

	}

	//DBG_CR_CLK(printf("REG_CLK_NFIE = 0x%04X\r\n", FCIE_RIU_R16(REG_CLK_SDIO)));

    return 0x00;

}

static U32 gu32SdClock = 0;

#define BUS_SPEED_SDR12		1
#define BUS_SPEED_SDR25		2
#define BUS_SPEED_DDR50		3
#define BUS_SPEED_SDR50		4
#define BUS_SPEED_SDR104	5

//static U32 gu8BusSpeed = BUS_SPEED_SDR12;


U32 HalFcie_clock_setting(U16 u16_ClkParam)
{
    DBG_CR_CLK(printf("HalFcie_clock_setting(%Xh)\n", u16_ClkParam));

    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_CLK_EN);

    switch(u16_ClkParam)
    {
		// emmc_pll clock
		case eMMC_PLL_CLK__20M	: gu32SdClock =  20000; break;
		case eMMC_PLL_CLK__27M	: gu32SdClock =  27000; break;
		case eMMC_PLL_CLK__32M	: gu32SdClock =  32000; break;
		case eMMC_PLL_CLK__36M	: gu32SdClock =  36000; break;
		case eMMC_PLL_CLK__40M	: gu32SdClock =  40000; break;
		case eMMC_PLL_CLK__48M	: gu32SdClock =  48000; break;
		case eMMC_PLL_CLK__52M	: gu32SdClock =  52000; break;
		case eMMC_PLL_CLK__62M	: gu32SdClock =  62000; break;
		case eMMC_PLL_CLK__72M	: gu32SdClock =  72000; break;
		case eMMC_PLL_CLK__80M	: gu32SdClock =  80000; break;
		case eMMC_PLL_CLK__86M	: gu32SdClock =  86000; break;
		case eMMC_PLL_CLK_100M	: gu32SdClock = 100000; break;
		case eMMC_PLL_CLK_120M	: gu32SdClock = 120000; break;
		case eMMC_PLL_CLK_140M	: gu32SdClock = 140000; break;
		case eMMC_PLL_CLK_160M	: gu32SdClock = 160000; break;
		case eMMC_PLL_CLK_200M	: gu32SdClock = 200000; break;

		// clock_gen fcie clock
        //case BIT_FCIE_CLK_12M	: gu32SdClock =  12000; break;
		case BIT_FCIE_CLK_20M	: gu32SdClock =  20000; break;
		case BIT_FCIE_CLK_32M	: gu32SdClock =  32000; break;
		case BIT_FCIE_CLK_36M	: gu32SdClock =  36000; break;
		case BIT_FCIE_CLK_40M	: gu32SdClock =  40000; break;
		case BIT_FCIE_CLK_43M	: gu32SdClock =  43200; break;
		case BIT_FCIE_CLK_300K	: gu32SdClock =    300; break;
        //case BIT_FCIE_CLK_24M	: gu32SdClock =  24000; break;
		case BIT_FCIE_CLK_48M	: gu32SdClock =  48000; break;

        default:
            printf("SdErr: wrong clock parameter\n");
            return 1;;
    }

	//printf("set clock to %d KHz\n", gu32SdClock);

    if(u16_ClkParam & eMMC_PLL_FLAG)
    {
		//printf("sdio pll clock\n");

        REG_FCIE_CLRBIT(REG_CLK_SDIO, BIT_SDIO_CLK_GATING|BIT_SDIO_CLK_INVERSE|BIT_CLKGEN_SDIO_MASK);

        HalSdio_pll_setting(u16_ClkParam);

        //if( gu8BusSpeed == BUS_SPEED_SDR104 ) // HS200
        {
            REG_FCIE_SETBIT(REG_CLK_SDIO, BIT_SDIO_CLK_SRC_SEL|0xB<<2);
        }
    }
    else
    {
		printf("clkgen clock\n");

        REG_FCIE_CLRBIT(REG_CLK_SDIO, BIT_SDIO_CLK_GATING|BIT_SDIO_CLK_INVERSE|BIT_CLKGEN_SDIO_MASK);
        REG_FCIE_SETBIT(REG_CLK_SDIO, BIT_SDIO_CLK_SRC_SEL|u16_ClkParam<<2);
    }


    return 0;
}

void HalFcie_SwitchPad(unsigned char u32Mode)
{

	// chiptop

	// sdio
	REG_FCIE_CLRBIT(FCIE_DDR_MODE, BIT_FALL_LATCH|BIT_PAD_IN_SEL_SD|BIT_32BIT_MACRO_EN|BIT_DDR_EN|BIT_8BIT_MACRO_EN);
	//REG_FCIE_W(FCIE_DDR_TOGGLE_CNT, 0x0000);

	// sdio_pll
	REG_FCIE_CLRBIT(R_SDIO_PLL_0x68, BIT0|BIT1);
	//REG_FCIE_CLRBIT(reg_sdiopll_0x69, BIT7|BIT6|BIT5|BIT4|BIT3); // TODO: tuning after IC back
	REG_FCIE_CLRBIT(R_SDIO_PLL_0x6A, BIT0|BIT1); // 0 --> 1 bits
	REG_FCIE_W(R_SDIO_PLL_0x6B, 0x0000);

	// TODO: overcome the share register 0x6C trouble
	//REG_FCIE_CLRBIT(reg_sdiopll_0x6c, BIT7|BIT6|BIT5|BIT2|BIT1|BIT0); // TODO: tuning for 8 bit macro DQS, delay cell

	REG_FCIE_CLRBIT(reg_sdiopll_0x6d, BIT0);
	REG_FCIE_CLRBIT(reg_sdiopll_0x70, BIT8); // reg_sel_flash_32bit_macro_interface
	REG_FCIE_W(reg_sdiopll_0x71, 0xFFFF);
	REG_FCIE_W(reg_sdiopll_0x73, 0xFFFF);
	REG_FCIE_SETBIT(reg_sdiopll_0x74, BIT15);

	switch(u32Mode)
	{
		case SDIO_MODE_GPIO_PAD_BPS:
			printf("SDIO_MODE_GPIO_PAD_BPS\n");
			u8CurrentPadType = SDIO_MODE_GPIO_PAD_BPS;
			break;

		/*case SDIO_MODE_GPIO_PAD_SDR:
			printf"SDIO_MODE_GPIO_PAD_SDR\n");
			// fcie
			REG_FCIE_SETBIT(FCIE_DDR_MODE, BIT_FALL_LATCH|BIT_PAD_IN_SEL_SD);
			break;*/

		////////////////////////////////////////////////////////////////////////////////////////////
		case SDIO_MODE_8BITS_MACRO_SDR:
			printf("SDIO_MODE_8BITS_MACRO_SDR\n");
			u8CurrentPadType = SDIO_MODE_8BITS_MACRO_SDR;
			// fcie
			REG_FCIE_SETBIT(FCIE_DDR_MODE, BIT_8BIT_MACRO_EN);
			// sdio_pll
			REG_FCIE_SETBIT(R_SDIO_PLL_0x68, BIT0);
			REG_FCIE_SETBIT(R_SDIO_PLL_0x6A, BIT0);
			REG_FCIE_W(R_SDIO_PLL_0x6B, 0x0413); // 4 bits
			break;

		case SDIO_MODE_8BITS_MACRO_DDR:
			u8CurrentPadType = SDIO_MODE_8BITS_MACRO_DDR;
			printf("FCIE_MODE_8BITS_MACRO_DDR52\n");
			// fcie
			REG_FCIE_SETBIT(FCIE_DDR_MODE, BIT_DDR_EN|BIT_8BIT_MACRO_EN);

			// sdio_pll
			REG_FCIE_SETBIT(R_SDIO_PLL_0x68, BIT0);
			REG_FCIE_SETBIT(R_SDIO_PLL_0x6A, BIT0);
			REG_FCIE_W(R_SDIO_PLL_0x6B, 0x0213); // 4 bits
			REG_FCIE_SETBIT(reg_sdiopll_0x6d, BIT0);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////
		case SDIO_MODE_32BITS_MACRO_DDR:
			u8CurrentPadType = SDIO_MODE_32BITS_MACRO_DDR;
			printf("SDIO_MODE_32BITS_MACRO_DDR\n");
			// fcie
			REG_FCIE_SETBIT(FCIE_DDR_MODE, BIT_32BIT_MACRO_EN|BIT_DDR_EN);

			// sdio_pll
			//REG_FCIE_SETBIT(reg_emmcpll_0x03, 0x0004);
			REG_FCIE_W(R_SDIO_PLL_0x6B, 0x0213);


			REG_FCIE_SETBIT(R_SDIO_PLL_0x68, BIT0|BIT1);

			// TODO: tuning after IC back
			REG_FCIE_CLRBIT(reg_sdiopll_0x69, 0xF<<4);
			REG_FCIE_SETBIT(reg_sdiopll_0x69, 4<<4);

			REG_FCIE_SETBIT(reg_sdiopll_0x69, BIT3);

			REG_FCIE_SETBIT(R_SDIO_PLL_0x6A, BIT1);
			REG_FCIE_SETBIT(reg_sdiopll_0x70, BIT8);
			REG_FCIE_W(reg_sdiopll_0x71, 0x0000);
			break;

		case SDIO_MODE_32BITS_MACRO_HS200:
			u8CurrentPadType = SDIO_MODE_32BITS_MACRO_HS200;
			printf("SDIO_MODE_32BITS_MACRO_HS200\n");
			// fcie
			REG_FCIE_SETBIT(FCIE_DDR_MODE, BIT_32BIT_MACRO_EN);
			REG_FCIE_W(FCIE_DDR_TOGGLE_CNT, 0x0410);

			// emmc_pll
			REG_FCIE_W(reg_sdiopll_0x03, 0x0000);
			HalSdio_SetSkew(1, 0);
			HalSdio_SetSkew(2, 0);
			HalSdio_SetSkew(3, 0);
			HalSdio_SetSkew(4, 0);
			HalSdio_SetTriggerLevel(0);

			REG_FCIE_W(R_SDIO_PLL_0x6B, 0x0413); // 4 bits

			REG_FCIE_SETBIT(R_SDIO_PLL_0x68, BIT0);

			// TODO: tuning after IC back
			REG_FCIE_CLRBIT(reg_sdiopll_0x69, 0xF<<4);
			REG_FCIE_SETBIT(reg_sdiopll_0x69, 4<<4);

			//REG_FCIE_SETBIT(reg_sdiopll_0x69, BIT3);

			REG_FCIE_SETBIT(R_SDIO_PLL_0x6A, BIT0);
			REG_FCIE_SETBIT(reg_sdiopll_0x70, BIT8);
			REG_FCIE_W(reg_sdiopll_0x71, 0x0000);


			REG_FCIE_SETBIT(reg_sdiopll_0x1a,BIT00); // driving

			REG_FCIE_CLRBIT(reg_sdiopll_0x1d,BIT04|BIT05|BIT06);
			REG_FCIE_SETBIT(reg_sdiopll_0x1d,BIT05);		// response latch

			REG_FCIE_SETBIT(reg_emmc_test, BIT2); // helps in voltage & temp variation

			break;

		default:
			u8CurrentPadType = SDIO_MODE_UNKNOWN;
			printf("SDIO Err: wrong parameter for switch pad func\n");
			//return 0x01;
			break;
	}

	// 8 bits macro reset + 32 bits macro reset
	REG_FCIE_CLRBIT(reg_sdiopll_0x6f, BIT1|BIT0);
	REG_FCIE_SETBIT(reg_sdiopll_0x6f, BIT1|BIT0);

	//return 0x00;

//ErrorHandle:

	//printf("SDIO Err: set bus width before pad switch\n");
	//return 0x02;

}

#endif



U8 halFCIE_Platform_ClearEvent(U16 nReq)
{
    U16  u16Tmp;

    u16Tmp = 0x0080;
    while((FCIE_RIU_R16(FCIE_MIE_EVENT)& nReq) != 0x00)
    {
        FCIE_RIU_W16(FCIE_MIE_EVENT, nReq); // write 1 clear register
        if (u16Tmp==0)
        {
            printf("Error!!! Can not clear MIE event.\r\n");
            return(1);
        }
        else
        {
            u16Tmp--;
        }
    }

    return 0;
}


E_IO_STS HalFcie_WaitMieEvent(U16 u16ReqVal, U32 u32WaitMs)
{
    U32 u32Count = 0;
    //u32WaitMs *= 100;
	U16 u16Event;

	while(1)
	{
		u16Event = FCIE_RIU_R16(FCIE_MIE_EVENT);

		if(u16Event&BIT_ERR_STS)
		{
			//printf("\33[1;31mSDIO detect error, SD_STATUS = %04Xh\33[m\n", FCIE_RIU_R16(FCIE_SD_STATUS));
			halFCIE_Platform_ClearEvent(BIT_ERR_STS);
			return IO_ERROR;
		}
		else if((u16Event&u16ReqVal)==u16ReqVal)
		{
			//printf(" Got event %04X ", u16Event);
			break;
		}

		udelay(1000);

		u32Count++;

		if(u32Count>u32WaitMs)
		{
			printf("u32Counter=%d\r\n", u32Count);
			printf("\r\n");
			printf("------------------------------------------\r\n");
			printf("ERROR!!! MIE EVENT TIME OUT!!!\n");
			printf("request event = %04Xh, event = %04Xh\n", u16ReqVal, u16Event);
			printf("------------------------------------------\r\n");

			HalFcie_DumpRegister();
			HalFcie_DumpDebugBus();
			//while(1);

			return(IO_TIME_OUT);
		}
	}

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Clear mie event
    // Only can clear request value,
    // because read operation might enable command and data transfer at the same time

    if (halFCIE_Platform_ClearEvent(u16ReqVal))
    {
	    return (IO_TIME_OUT);
    }

    return(IO_SUCCESS);
} // wait MIE Event End


U32 HalSdio_FindSkewer(U32 u32_Candidate, SKEWER * st_skewer)
{
	U32 u32_i;
	st_skewer->u32LatchOKStart = 0xBEEF;
	st_skewer->u32LatchOKEnd = 0xBEEF;
	st_skewer->u8_edge = 0;

	//printf("%s(%05Xh)\n", __FUNCTION__, u32_Candidate);

	for(u32_i=0; u32_i<20; u32_i++) {
		if( (u32_Candidate&(1<<u32_i)) ^ ((u32_Candidate>>1)&(1<<u32_i)) ) { // use XOR to find 0b01/0b10 edge
			st_skewer->u8_edge++;
			//printf("%d [%04Xh ^ %04Xh] = %04Xh, ", u32_i, (u32_Candidate&(1<<u32_i)), ((u32_Candidate>>1)&(1<<u32_i)),
			//	( (u32_Candidate&(1<<u32_i)) ^ ((u32_Candidate>>1)&(1<<u32_i)) ) );
			if(st_skewer->u32LatchOKStart==0xBEEF) {
				st_skewer->u32LatchOKStart = u32_i;
			} else if(st_skewer->u32LatchOKEnd==0xBEEF) {
				st_skewer->u32LatchOKEnd = u32_i;
			}
		}
	}

	st_skewer->u32LatchOKEnd--;

	//eMMC_printf("u8_edge = %d, ", st_skewer->u8_edge);
	//eMMC_printf("start = %d, ", st_skewer->u32LatchOKStart);
	//eMMC_printf("end = %d\n", st_skewer->u32LatchOKEnd);

	return 0;
}

U32 HalSdio_SlectBestSkew4(U32 u32_Candidate, SKEWER * pSkewer)
{
	SKEWER st_skewer1 = {0};
	SKEWER st_skewer2 = {0};
	U32 u32_LatchBestSelect = 0;
	U32 u32_Temp;
	U32 u32Ret = 0;

	//printf("\n%s(%05Xh)\n", __FUNCTION__, u32_Candidate);

	if(!u32_Candidate) {
		printf("ATOP fail: no workable skew4\n");
		u32Ret = 1;
		goto ErrorHandle;
	}

	u32_Candidate<<=1; // bit 0~17 --> bit 1~18, add 0 former and later
	HalSdio_FindSkewer(u32_Candidate, &st_skewer1);

	u32_Candidate |= 0x00180001; // add 1 former and later
	HalSdio_FindSkewer(u32_Candidate, &st_skewer2);

	u32_Candidate &= ~0x00180001; // bit 1~18
	u32_Candidate>>=1; // bit 1~18 --> bit 0~17, shift back

	if( (st_skewer1.u8_edge==2) || (st_skewer2.u8_edge==2) ) { // only 1 continuous workable skew4 group

		if(st_skewer1.u8_edge==2) {
			// select best skew4
			if((st_skewer1.u32LatchOKStart + st_skewer1.u32LatchOKEnd)%2) { // odd

				u32_LatchBestSelect = (st_skewer1.u32LatchOKStart + st_skewer1.u32LatchOKEnd) >> 1;
				//u32_LatchBestSelect++; // select later
			}
			else { // even

				u32_LatchBestSelect = (st_skewer1.u32LatchOKStart + st_skewer1.u32LatchOKEnd) >> 1;
			}
		}
		else {
			memcpy(&st_skewer1, &st_skewer2, sizeof(SKEWER));
			//eMMC_printf("ring type:\n");
			st_skewer1.u32LatchOKStart--;
			st_skewer1.u32LatchOKEnd++;

			//eMMC_printf("start = %d, ", st_skewer1.u32LatchOKStart);
			//eMMC_printf("end = %d\n", st_skewer1.u32LatchOKEnd);

			u32_Temp = ((st_skewer1.u32LatchOKStart+1)+(18-st_skewer1.u32LatchOKEnd)) >> 1;
			if(st_skewer1.u32LatchOKStart>=u32_Temp) {
				//printf("enough\n");
				u32_LatchBestSelect = st_skewer1.u32LatchOKStart - u32_Temp;
			}
			else {
				u32_LatchBestSelect = st_skewer1.u32LatchOKEnd + u32_Temp;
			}
			if(u32_LatchBestSelect==18) u32_LatchBestSelect = 0;
			// swap start & end
			u32_Temp = st_skewer1.u32LatchOKStart; st_skewer1.u32LatchOKStart = st_skewer1.u32LatchOKEnd; st_skewer1.u32LatchOKEnd = u32_Temp;
		}

		if( st_skewer1.u32LatchOKStart == st_skewer1.u32LatchOKEnd ) {
			printf("ATOP warn: %05Xh (", u32_Candidate);
			printf("%d ~ ", st_skewer1.u32LatchOKStart);
			printf("%d)\n", st_skewer1.u32LatchOKEnd);
			u32Ret = 2;
			goto ErrorHandle;
		}
		else {
			printf("ATOP success: %05Xh (", u32_Candidate);
			printf("%d ~ ", st_skewer1.u32LatchOKStart);
			printf("%d)\n", st_skewer1.u32LatchOKEnd);
		}
	}
	else {
		printf("ATOP fail: not continuous: %05Xh, u8_edge: ", u32_Candidate);
		printf("%d (", st_skewer1.u8_edge);
		printf("%d ~ ", st_skewer1.u32LatchOKStart);
		printf("%d)\n", st_skewer1.u32LatchOKEnd);
		u32Ret = 3;
		goto ErrorHandle;
	}

	printf("Best skew4: %d\n", u32_LatchBestSelect);


	pSkewer->u32LatchOKStart = st_skewer1.u32LatchOKStart;
	pSkewer->u32LatchOKEnd = st_skewer1.u32LatchOKEnd;
	pSkewer->u32LatchBest = u32_LatchBestSelect;

ErrorHandle:

	return u32Ret;
}


#if (CONFIG_ICE_BRING_UP==1)
u8 halFCIE_Platform_DisableBootMode(void)
{
	u16 regval;

	FCIE_RIU_16_ON(TEST_MODE, WBIT08);
	udelay(5000000);

	regval = FCIE_RIU_R16(NC_MISC);

	if( regval != 0x1F )
	{
		if( regval == 0x0E )
		{
			FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT01);

			while(1)
			{
				udelay(1000);

				regval = FCIE_RIU_R16(MIE_EVENT);

				if( regval & WBIT15 )
					break;
			}

			FCIE_RIU_W16(MIE_PATH_CTL, 0);
			FCIE_RIU_W16(JOB_BL_CNT, 0);
			regval = FCIE_RIU_R16(SD_STS);
			FCIE_RIU_W16(SD_STS, regval);
			regval = FCIE_RIU_R16(MIE_EVENT);
			FCIE_RIU_W16(MIE_EVENT, regval);
		}

		FCIE_RIU_W16(CARD_INT_EN, regval);

		return 1;
	}

	FCIE_RIU_W16(JOB_BL_CNT, 1);
	FCIE_RIU_16_ON(SD_MODE, WBIT09);
	udelay(1000000);
	FCIE_RIU_W16(SD_CTL, WBIT03);

	udelay(1000000);
	FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT01);

	FCIE_RIU_16_OF(SD_MODE, WBIT09);

	udelay(5000000);

	while(1)
	{
		udelay(1000);

		regval = FCIE_RIU_R16(MIE_EVENT);
		if( regval & WBIT15 )
			break;
	}

	FCIE_RIU_W16(MIE_PATH_CTL, 0);
	FCIE_RIU_W16(JOB_BL_CNT, 0);
	regval = FCIE_RIU_R16(SD_STS);
	FCIE_RIU_W16(SD_STS, regval);
	regval = FCIE_RIU_R16(MIE_EVENT);
	FCIE_RIU_W16(MIE_EVENT, regval);


	return 0;

}
#endif

#if 0
void FCIE_HWTimer_Start(void)
{
    // reset HW timer
    FCIE_RIU_W16(TIMER0_MAX_LOW, 0xFFFF);
    FCIE_RIU_W16(TIMER0_MAX_HIGH, 0xFFFF);
    FCIE_RIU_W16(TIMER0_ENABLE, 0);

    // start HW timer
    FCIE_RIU_16_ON(TIMER0_ENABLE, 0x0001);

}

U32 FCIE_HWTimer_End(void)
{
    U32 u32HWTimer = 0;
    U16 u16TimerLow = 0;
    U16 u16TimerHigh = 0;

    // Get HW timer
    u16TimerLow = FCIE_RIU_R16(TIMER0_CAP_LOW);
    u16TimerHigh = FCIE_RIU_R16(TIMER0_CAP_HIGH);

    u32HWTimer = (u16TimerHigh<<16) | u16TimerLow;

    return u32HWTimer;
}
#endif
#endif
