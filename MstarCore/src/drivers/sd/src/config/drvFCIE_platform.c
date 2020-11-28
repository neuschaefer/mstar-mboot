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
#ifndef SD_USE_FCIE5
#include <common.h>
#include <stdio.h>
#include "drvFCIE.h"

extern unsigned char mmc_ddr_mode;

/**************************************
* Config definition
**************************************/
#define DBG_CR_CLK(MSG)             MSG

/**************************************
* Local function definition
**************************************/
#if (MS_BOARD_TYPE_SEL == BD_MST029B_10AFVA_A3 || ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3 || ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3 || ENABLE_MSTAR_TITANIA_BD_CUS28_6A801 || ENABLE_MSTAR_TITANIA_BD_MST029B_BOX_A3)
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
    U16 reg;

    FCIE_RIU_16_OF(TEST_MODE, R_FCIE_SOFT_RST);
    FCIE_DELAY_US(10); // 10us
    //=================================================
    // PATCH write CIFC fail after FCIE reset
    //=================================================
    while(1)
    {
        FCIE_RIU_16_ON(TEST_MODE, R_FCIE_SOFT_RST);
        reg = FCIE_RIU_R16(TEST_MODE);
        if (reg & R_FCIE_SOFT_RST)
            break;
    }
    FCIE_DELAY_US(100); // 100us
    //==================================================
}

void halFCIE_Platform_InitChiptop(void)
{
#if ENABLE_AMBER3
    FCIE_RIU_16_OF(ALL_PAD_IN, WBIT15);
    FCIE_RIU_16_OF(NAND_TOP_CFG, WBIT06+WBIT07);
    FCIE_RIU_16_OF(PCMCIA_TOP_CFG, WBIT04);

		FCIE_RIU_16_OF(EMMC_TOP_CFG, CFG_EMMC_PAD_MASK);
    FCIE_RIU_16_ON(EMMC_TOP_CFG, CFG_EMMC_PAD);


    #if (MS_BOARD_TYPE_SEL == BD_MST029B_10AFVA_A3 || ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3 || ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3 || ENABLE_MSTAR_TITANIA_BD_CUS28_6A801 || ENABLE_MSTAR_TITANIA_BD_MST029B_BOX_A3)
    //===================================================
    // PATCH A3 U02 goto boot mode issue
    //===================================================
    FCIE_RIU_16_ON(EMMC_BOOT_CFG, FORCE_BOOT_FROM_EMMC2);
    _halFCIE_Platform_DisableBootMode();
    #endif


#elif ENABLE_AGATE

    FCIE_RIU_16_OF(PCMCIA_TOP_CFG, WBIT00+WBIT03+WBIT04);

    FCIE_RIU_16_OF(NAND_TOP_CFG, WBIT00+WBIT01+WBIT04+WBIT06+WBIT07);	
    FCIE_RIU_16_OF(EMMC_TOP_CFG, CFG_EMMC_PAD_MASK);
    FCIE_RIU_16_ON(EMMC_TOP_CFG, CFG_EMMC_PAD);

    FCIE_RIU_16_OF(SD_TOP_CFG, CFG_SD_PAD);
    FCIE_RIU_16_OF(ALL_PAD_IN, WBIT15);	
    
		FCIE_RIU_16_ON(NC_REORDER, WBIT14);	
		
    FCIE_RIU_16_ON(EMMC_BOOT_CFG, WBIT08);

    FCIE_RIU_16_OF(EMMC_CLOCK_4X_DIV, WBIT05);
    FCIE_RIU_16_ON(EMMC_CLOCK_4X_DIV, WBIT00 );
    FCIE_RIU_W16(EMMC_BOOT_CONFIG, 0x0D00);

    #elif ENABLE_EAGLE 
	
    FCIE_RIU_16_OF(ALL_PAD_IN, WBIT15);

  #if 1
    FCIE_RIU_16_ON(FCIE_MACRO_BYPASS,FCIE2MACRO_SD_BYPASS);
    //FCIE_RIU_W16(NAND_CONFIG, WBIT02);   //reg_sd0_config 1
    FCIE_RIU_W16(NAND_CONFIG, WBIT07);  //reg_sd1_config 1
	FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT10);
	
  #else
	
    FCIE_RIU_16_ON(FCIE_MACRO_BYPASS,SD_USE_BYPASS);
	#if 0 //bypass
	FCIE_RIU_16_ON(FCIE_MACRO_BYPASS,FCIE2MACRO_SD_BYPASS);
	#else//sdr
	FCIE_RIU_16_OF(FCIE_MACRO_BYPASS,FCIE2MACRO_SD_BYPASS);
	#endif
	FCIE_RIU_16_ON(EMMC_CONFIG,EMMC_MODE_1);
	FCIE_RIU_16_OF(NAND_CONFIG,NAND_CONFIG_MASK);//disable nand config
	FCIE_RIU_16_OF(EMMC_BOOT_CONFIG,R_SD_MODE_MASK);
    #if 0 //bypass 	
	FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, R_SD_MACRO_EN | R_SD_BYPASS_MODE | R_SD_SDRIN_BYPASS_MODE);
	#else //sdr
	FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, R_SD_MACRO_EN);
	#endif
  #endif

 #elif (ENABLE_KAISER)
  #ifdef USE_SD_MODE
      FCIE_RIU_16_OF(CHIPTOP6,BIT0|BIT1|BIT4|BIT5|BIT6|WBIT12|WBIT13);		//clear nand mode. eMMC mode
      FCIE_RIU_16_ON(CHIPTOP6,WBIT14|WBIT15);		//sd mode 3

     FCIE_RIU_16_ON(CHIPTOP35,BIT6);					//BLOCK EMMC
     FCIE_RIU_16_OF(CHIPTOP35,BIT7);					//BLOCK EMMC

     FCIE_RIU_16_ON(CHIPTOP25,BIT1);					//SDR mode

     FCIE_RIU_16_OF(ALL_PAD_IN, WBIT15);


  #else
      FCIE_RIU_16_OF(CHIPTOP6,BIT0|BIT1|BIT4|BIT5|BIT6|WBIT12|WBIT13);		//clear nand mode. eMMC mode
      
      FCIE_RIU_16_ON(CHIPTOP6, BIT4);			// choose SDIO mode 1
   //   FCIE_RIU_16_ON(FCIE_SETTING,BIT6);					//sd bypass mode

      FCIE_RIU_16_ON(CHIPTOP26,BIT0); 				// SDR MODE
      FCIE_RIU_16_OF(ALL_PAD_IN, WBIT15);

  //   FCIE_RIU_16_ON(CHIPTOP35,BIT6);					//BLOCK EMMC
//     FCIE_RIU_16_OF(CHIPTOP35,BIT7);					//BLOCK EMMC
  #endif
 #elif ENABLE_NIKE
   #ifdef USE_SD_MODE
	FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
 	FCIE_RIU_16_ON(CHIPTOP_42,BIT04|BIT05|BIT06);
	 FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
 	FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
 	FCIE_RIU_16_OF(CHIPTOP_5B,WBIT08|WBIT09);
 	FCIE_RIU_16_ON(CHIPTOP_5B,WBIT08);			//SD
 	FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14|WBIT13);			//SD 

   #else
   	FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
 	FCIE_RIU_16_ON(CHIPTOP_42,0x7f);
	 FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
 	FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
 	FCIE_RIU_16_OF(CHIPTOP_5B,WBIT10|WBIT11);
 	FCIE_RIU_16_ON(CHIPTOP_5B,WBIT10);			//SDIO PAD1
 	FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14);			//SDIO PAD1

   #endif

#elif ENABLE_MADISON
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
        FCIE_RIU_16_ON(CHIPTOP_42,BIT04|BIT05|BIT06);
        FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
        FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
        FCIE_RIU_16_OF(CHIPTOP_5B,WBIT08|WBIT09);
        FCIE_RIU_16_ON(CHIPTOP_5B,WBIT08);			//SD mode 1
        FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14|WBIT13);			//SD 
    #else
	printf("init chiptop\n");
	
        FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
        FCIE_RIU_16_ON(CHIPTOP_42,0x7f);
        FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
        FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
        FCIE_RIU_16_OF(CHIPTOP_5B,WBIT10|WBIT11);
        FCIE_RIU_16_ON(CHIPTOP_5B,WBIT10);			//SDIO PAD1
        FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14);			//SDIO PAD1
 	FCIE_RIU_16_OF(CHIPTOP_12,0x77);			 
 	FCIE_RIU_16_OF(CHIPTOP_64,BIT00);			
 	FCIE_RIU_16_OF(CHIPTOP_1F,BIT01);		
 	FCIE_RIU_16_OF(CHIPTOP_6F,WBIT14|WBIT15);			
 	FCIE_RIU_16_OF(CHIPTOP_70,BIT00|BIT02);			

   #endif

#elif ENABLE_CLIPPERS
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
        FCIE_RIU_16_ON(CHIPTOP_42,BIT04|BIT05|BIT06);
        FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
        FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
        FCIE_RIU_16_OF(CHIPTOP_5B,WBIT08|WBIT09);
        FCIE_RIU_16_ON(CHIPTOP_5B,WBIT08);			//SD
        FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14|WBIT13);			//SD 
    #else
        FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
        FCIE_RIU_16_ON(CHIPTOP_42,0x7f);
        FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
        FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
        FCIE_RIU_16_OF(CHIPTOP_5B,WBIT10|WBIT11);
        FCIE_RIU_16_ON(CHIPTOP_5B,WBIT10);			//SDIO PAD1
        FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14);			//SDIO PAD1

#endif

#elif ENABLE_MIAMI
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
        FCIE_RIU_16_ON(CHIPTOP_42,BIT04|BIT05|BIT06);
        FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
        FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
        FCIE_RIU_16_OF(CHIPTOP_5B,WBIT08|WBIT09);
        FCIE_RIU_16_ON(CHIPTOP_5B,WBIT08);			//SD
        FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14|WBIT13);			//SD 
    #else
        FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
        FCIE_RIU_16_ON(CHIPTOP_42,0x7f);
        FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
        FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
        FCIE_RIU_16_OF(CHIPTOP_5B,WBIT10|WBIT11);
        FCIE_RIU_16_ON(CHIPTOP_5B,WBIT10);			//SDIO PAD1
        FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14);			//SDIO PAD1

   #endif

#elif ENABLE_NADAL
#ifdef USE_SD_MODE
    FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
    FCIE_RIU_16_ON(CHIPTOP_42,BIT04|BIT05|BIT06);
    FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
    FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
    FCIE_RIU_16_OF(CHIPTOP_5B,WBIT08|WBIT09);
    FCIE_RIU_16_ON(CHIPTOP_5B,WBIT08);          //SD
    FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14|WBIT13);           //SD 
#else
    FCIE_RIU_16_ON(CHIPTOP_0C,BIT04|BIT05|BIT06|BIT07);
    FCIE_RIU_16_ON(CHIPTOP_42,0x7f);
    FCIE_RIU_16_ON(CHIPTOP_43,BIT01);
    FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);
    FCIE_RIU_16_OF(CHIPTOP_5B,WBIT10|WBIT11);
    FCIE_RIU_16_ON(CHIPTOP_5B,WBIT10);          //SDIO PAD1
    FCIE_RIU_16_OF(CHIPTOP_4F,WBIT14);          //SDIO PAD1
#endif

#elif ENABLE_EINSTEIN || ENABLE_NAPOLI || ENABLE_MONACO || \
	ENABLE_MUJI || ENABLE_CELTICS

	#ifdef USE_SD_MODE
	 FCIE_RIU_16_ON(CHIPTOP_10,WBIT08);		//by pass mode
	 FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);		//by pass mode
	 FCIE_RIU_16_ON(CHIPTOP_0A,0xf0);		//by pass mode
 	 FCIE_RIU_16_OF(CHIPTOP_40,BIT00);		//by pass mode
 	 FCIE_RIU_16_OF(CHIPTOP_6F,BIT06|BIT07);		 
	 FCIE_RIU_16_OF(CHIPTOP_5A,WBIT08|WBIT09);		 
	 FCIE_RIU_16_ON(CHIPTOP_5A,WBIT09);		//SD mode 2		 
	// FCIE_RIU_16_OF(CHIPTOP_7B,BIT04|BIT05);		//clr SDIO pad	 
	// FCIE_RIU_16_OF(CHIPTOP_6E,BIT06|BIT07);		//clr SDIO pad	 
	 FCIE_RIU_16_OF(CHIPTOP_64,BIT00|BIT03|BIT04);		//	 

	#else
	 FCIE_RIU_16_OF(CHIPTOP_50,WBIT15);		//by pass mode
	 FCIE_RIU_16_ON(CHIPTOP_0A,0xf00);		//
 //	 FCIE_RIU_16_OF(CHIPTOP_6F,BIT06|BIT07);		 
	// FCIE_RIU_16_OF(CHIPTOP_5A,WBIT08|WBIT09);		 
	 FCIE_RIU_16_OF(CHIPTOP_7B,BIT04|BIT05);		//clr SDIO pad	 
	 FCIE_RIU_16_ON(CHIPTOP_7B,BIT04);		//SDIO pad 1 
	// FCIE_RIU_16_OF(CHIPTOP_6E,BIT06|BIT07);		//clr SDIO pad	 
	 FCIE_RIU_16_OF(CHIPTOP_64,BIT00|BIT03|BIT04);		//	 
	 FCIE_RIU_16_OF(CHIPTOP_52,WBIT08|WBIT10);		//	 

	#endif
#endif
}

void halFCIE_Disable_Stop_Clock(void)
{
#if ENABLE_AMBER3
    FCIE_RIU_W16(NC_MISC, WBIT14);
#elif ENABLE_AGATE || ENABLE_EAGLE || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_CLIPPERS) || (ENABLE_MIAMI) || (ENABLE_NADAL)
    FCIE_RIU_W16(DEBUG_BUS1, WBIT06 );
#endif
}

void halFCIE_Reset_Toggle_Count(void)
{
#if ENABLE_AMBER3
    FCIE_RIU_W16(NC_MISC, WBIT15);
    udelay(1);
    FCIE_RIU_W16(NC_MISC, 0x0000);
#elif ENABLE_AGATE || ENABLE_EAGLE || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_CLIPPERS) || (ENABLE_MIAMI) || (ENABLE_NADAL)
    FCIE_RIU_W16(DEBUG_BUS1, WBIT07 );
    udelay(1);
    FCIE_RIU_W16(DEBUG_BUS1, 0x0000);
#endif	
}

void halFCIE_Set_Read_Toggle_Count(void)
{
    FCIE_RIU_W16(SD_DDR_CNT, 0x111);
}

void halFCIE_Set_Write_Toggle_Count(void)
{
    FCIE_RIU_W16(SD_DDR_CNT, 0x11A);
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

    #elif ENABLE_EAGLE || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_CLIPPERS) || (ENABLE_MIAMI) || (ENABLE_NADAL)


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
    40000, //  1
    36000, //  2
    27000, //  3
    20000, //  4
      150, //  5
        0, //  6
};

U8 halFCIE_Platform_SetFcieClock(U32 u32Clock)
{
    U8 u8ClockSlector;
	static U32 u32_OldClock=0xFFFFFFFF;

	if(u32_OldClock == u32Clock)
		return 0;
	else
		u32_OldClock = u32Clock;

    if(u32Clock>1000)
    {
        DBG_CR_CLK(printf("Set FCIE clock as %lx.%lx MHz, ", (u32Clock/1000), (u32Clock%1000)/100 ) );
    }
    else
    {
        DBG_CR_CLK(printf("Set FCIE clock as %lx KHz, ", u32Clock));
    }

    for(u8ClockSlector=0; u8ClockSlector<FcieClockIdxNum; u8ClockSlector++)
    {
        if( FCIE_CLOCK[u8ClockSlector] <= u32Clock ) break;
    }

    if(u8ClockSlector==FcieClockIdxNum)
    {
        DBG_CR_CLK(printf("Error!!! Can not find proper clock!\r\n"));
        return 0x01;
    }

    if(u32Clock>1000)
    {
        DBG_CR_CLK(printf("select FCIE clock as %lx.%lx MHz\r\n", FCIE_CLOCK[u8ClockSlector]/1000, (FCIE_CLOCK[u8ClockSlector]%1000)/100));
    }
    else
    {
        DBG_CR_CLK(printf("select FCIE clock as %lx KHz\r\n", FCIE_CLOCK[u8ClockSlector]));
    }

    FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT06);
    FCIE_RIU_16_OF(REG_CLK_NFIE, WBIT05+WBIT04+WBIT03+WBIT02); // mask all clock select

printf("switch to clock:%x\n", u8ClockSlector);

    switch(u8ClockSlector)
    {
#if 0
    
        case 0:

            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT05+WBIT04+WBIT03+WBIT02);
            DBG_CR_CLK(printf("FCIE clock 48M\r\n"));
            if( mmc_ddr_mode )
                FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT12);
            break;
			
        case 1:
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT04+WBIT02);
            DBG_CR_CLK(printf("FCIE clock 40M\r\n"));
            if( mmc_ddr_mode )
                FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT11+WBIT10);
            break;
        case 2:
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT04);
            DBG_CR_CLK(printf("FCIE clock 36M\r\n"));
            if( mmc_ddr_mode )
                FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT11);
            break;
        case 3:
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT03);
            DBG_CR_CLK(printf("FCIE clock 27M\r\n"));
            if( mmc_ddr_mode )
                FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT10);
            break;
        case 4:
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02);
            DBG_CR_CLK(printf("FCIE clock 20M\r\n"));
            break;
        case 5:
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);
            DBG_CR_CLK(printf("FCIE clock 150K\r\n"));
            break;
		#else
		case 5:
#if ENABLE_AMBER3 || ENABLE_EAGLE 		
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);
#elif ENABLE_AGATE
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);
            FCIE_RIU_16_OF(EMMC_CLOCK_4X_DIV, WBIT01);
#elif ENABLE_NIKE
     #ifdef USE_SD_MODE
	 	FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
	 	FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
		FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11);
		FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12|WBIT13);	// 12 - 75K

     #else
	    FCIE_RIU_16_OF(REG_CLK_NFIE, BIT01|BIT00);
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);		//13->300K
	#endif

#elif ENABLE_MADISON
    #ifdef USE_SD_MODE
	FCIE_RIU_16_ON(REG_CLK_64,WBIT06);
        FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11);
        FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12|WBIT13);	// 12 - 75K
    #else
        FCIE_RIU_16_OF(REG_CLK_NFIE, BIT01|BIT00);

        FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);		//13->300K
    #endif
	
#elif ENABLE_CLIPPERS
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11);
        FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12|WBIT13);	// 12 - 75K
    #else
        FCIE_RIU_16_OF(REG_CLK_NFIE, BIT01|BIT00);
        FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);		//13->300K
    #endif
	
#elif ENABLE_MIAMI
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11);
        FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12|WBIT13);	// 12 - 75K
    #else
        FCIE_RIU_16_OF(REG_CLK_NFIE, BIT01|BIT00);
        FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);		//13->300K
    #endif

#elif ENABLE_NADAL
#ifdef USE_SD_MODE
            FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
            FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
            FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11);
            FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12|WBIT13);	// 12 - 75K
#else
            FCIE_RIU_16_OF(REG_CLK_NFIE, BIT01|BIT00);
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT04+WBIT05);		//13->300K
#endif
#elif ENABLE_EINSTEIN || ENABLE_NAPOLI || ENABLE_MONACO || \
	ENABLE_MUJI || ENABLE_CELTICS

     #ifdef USE_SD_MODE
		FCIE_RIU_16_OF(REG_CLK_64,0x7f);		// 1X
		FCIE_RIU_16_ON(REG_CLK_64,WBIT06);		// 1X
		FCIE_RIU_16_ON(REG_CLK_64,WBIT02|WBIT04|WBIT05);		// 0x0D->300K
     #else
		FCIE_RIU_16_OF(REG_CLK_69,0x7f);		// 1X
		FCIE_RIU_16_ON(REG_CLK_69,BIT06);		// 1X
			//0->300K

     #endif		
	
#endif

            DBG_CR_CLK(printf("FCIE clock 150K\r\n"));
            break;

		default:
#if ENABLE_AMBER3			
		  #if (ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3)
            FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02);
            DBG_CR_CLK(printf("FCIE clock 20M\r\n"));
		  #else
			FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT03);
            DBG_CR_CLK(printf("FCIE clock 32M\r\n"));
          #endif
#elif ENABLE_AGATE
			FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT03);
            FCIE_RIU_16_OF(EMMC_CLOCK_4X_DIV, WBIT01);
            DBG_CR_CLK(printf("FCIE clock 32M\r\n"));
#elif ENABLE_NIKE
     #ifdef USE_SD_MODE
	 	FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
	 	FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
		FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11|WBIT13);
		FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12);	// 4 - 21M

     #else

	    FCIE_RIU_16_OF(REG_CLK_NFIE,WBIT05|WBIT04|WBIT03|WBIT02| BIT01|BIT00);
            FCIE_RIU_16_ON(REG_CLK_NFIE, BIT02);   //20M
      #endif

#elif ENABLE_MADISON
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11|WBIT13);
        FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12);	// 4 - 21M
    #else
        FCIE_RIU_16_OF(REG_CLK_NFIE,WBIT05|WBIT04|WBIT03|WBIT02| BIT01|BIT00);
        FCIE_RIU_16_ON(REG_CLK_NFIE, BIT02);   //20M
    #endif      

#elif ENABLE_CLIPPERS
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11|WBIT13);
        FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12);	// 4 - 21M
    #else
        FCIE_RIU_16_OF(REG_CLK_NFIE,WBIT05|WBIT04|WBIT03|WBIT02| BIT01|BIT00);
        FCIE_RIU_16_ON(REG_CLK_NFIE, BIT02);   //20M
    #endif
 	
#elif ENABLE_MIAMI
    #ifdef USE_SD_MODE
        FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
        FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11|WBIT13);
        FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12);	// 4 - 21M
    #else
        FCIE_RIU_16_OF(REG_CLK_NFIE,WBIT05|WBIT04|WBIT03|WBIT02| BIT01|BIT00);
        FCIE_RIU_16_ON(REG_CLK_NFIE, BIT02);   //20M
    #endif 

#elif ENABLE_NADAL
#ifdef USE_SD_MODE
                FCIE_RIU_16_ON(REG_CLK_65,WBIT14);		// 1X
                FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT09|WBIT08);
                FCIE_RIU_16_OF(REG_CLK_EMMC,WBIT10|WBIT11|WBIT13);
                FCIE_RIU_16_ON(REG_CLK_EMMC,WBIT12);	// 4 - 21M
#else
                FCIE_RIU_16_OF(REG_CLK_NFIE,WBIT05|WBIT04|WBIT03|WBIT02| BIT01|BIT00);
                FCIE_RIU_16_ON(REG_CLK_NFIE, BIT02);   //20M
#endif
#elif ENABLE_EAGLE 
            if(mmc_ddr_mode)
            {
                FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT03+WBIT04+WBIT05); 
				FCIE_RIU_16_ON(REG_CLK_EMMC, WBIT10+WBIT12);
				DBG_CR_CLK(printf("FCIE clock 48M\r\n"));
            }
			else
			{
			    FCIE_RIU_16_ON(REG_CLK_NFIE, WBIT02+WBIT03);
		        DBG_CR_CLK(printf("FCIE clock 32M\r\n"));
			}

#elif ENABLE_EINSTEIN || ENABLE_NAPOLI || ENABLE_MONACO || \
	ENABLE_MUJI || ENABLE_CELTICS

     #ifdef USE_SD_MODE
	             DBG_CR_CLK(printf("FCIE clock 20M\r\n"));

	       FCIE_RIU_16_OF(REG_CLK_64,0x7f);		// 1X
		FCIE_RIU_16_ON(REG_CLK_64,WBIT06);		// 1X
		FCIE_RIU_16_ON(REG_CLK_64,WBIT02);		// 1->20M
	#else
		FCIE_RIU_16_OF(REG_CLK_69,0x7f);		// 1X
		FCIE_RIU_16_ON(REG_CLK_69,BIT06);		// 1X
		#ifdef SDR_MODE
		FCIE_RIU_16_ON(REG_CLK_69,BIT03|BIT05);		// 5->48M
		#else
		FCIE_RIU_16_ON(REG_CLK_69,BIT02|BIT04);		// 5->20M
		#endif

     #endif		
#endif


		  
            break;
		#endif
    }

   // DBG_CR_CLK(printf("REG_CLK_NFIE = 0x%04X\r\n", FCIE_RIU_R16(REG_CLK_NFIE)));

    return 0x00;

}

U8 halFCIE_Platform_ClearEvent(U16 nReq)
{
    U16  u16Tmp;

    u16Tmp = 0x0080;
    while((FCIE_RIU_R16(MIE_EVENT)& nReq) != 0x00)
    {
        FCIE_RIU_W16(MIE_EVENT, nReq); // write 1 clear register
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
E_IO_STS halFCIE_Platform_WaitMieEvent(U16 u16ReqVal, U32 u32WaitMs)
{
    U32 u32Count = 0;
    u32WaitMs *= 100;

    while(1)
    {
        if((FCIE_RIU_R16(MIE_EVENT)&u16ReqVal)==u16ReqVal) // ignore mma_data_end for speed up
        {
            break;
        }

        //FCIE_DELAY_US(10);
        udelay(1000);
        u32Count++;
        if(u32Count>u32WaitMs)
        {
           printf("u32Counter=%ld\r\n", u32Count);
           printf("\r\n");
           printf("------------------------------------------\r\n");
           printf("ERROR!!! MIE EVENT TIME OUT!!!\r\n");
           printf("------------------------------------------\r\n");

           halFCIE_DumpRegister();

           while(1);
           if(FCIE_RIU_R16(MIE_EVENT)==u16ReqVal)
           {
               if(u16ReqVal & R_MMA_DATA_END)
               {
                   printf("mma data end\r\n");
                   if(FCIE_RIU_R16(CARD_EVENT)&R_CARD_DMA_END)
                   {
                       printf("BOTH MIU & CARD DMA END\r\n");
                   }
               }
           }
           else
           {
               printf("mie event 0x%04X not match request 0x%04X\r\n", FCIE_RIU_R16(MIE_EVENT), u16ReqVal);
           }
           return(IO_TIME_OUT);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Clear mie event
    // Only can clear request value,
    // because read operation might enable command and data transfer at the same time
    if (halFCIE_Platform_ClearEvent(u16ReqVal))
        return (IO_TIME_OUT);

    return(IO_SUCCESS);
} // wait MIE Event End

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

#if 1
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

