#include "../../inc/common/drvNAND.h"

//=============================================================
#if (defined(NAND_DRV_TV_SBOOT) && NAND_DRV_TV_SBOOT)


U32 nand_clock_setting(U32 u32ClkParam)
{
	u32ClkParam = FCIE3_SW_DEFAULT_CLK;

	if(REG(NC_DDR_CTRL) & BIT_DDR_MASM)
		return UNFD_ST_SUCCESS;

    #if defined(CONFIG_MSTAR_NIKE) || defined(CONFIG_MSTAR_MADISON) || \
        defined(CONFIG_MSTAR_NADAL) || defined(CONFIG_MSTAR_NUGGET)

    /*div4 enable*/
    REG_SET_BITS_UINT16(REG_CLK_NFIE, BIT_CLK_ENABLE);

   #if defined(CONFIG_MSTAR_MADISON)
   REG_SET_BITS_UINT16(REG_CLK_NFIE_DIV4_EN, BIT_CLK_SEL_1X);
   #endif

    /*set FCIE 4x clock*/
    REG_CLR_BITS_UINT16(REG_CLK_EMMC, BIT9|BIT8|EMMC_CLK_MASK);
    REG_SET_BITS_UINT16(REG_CLK_EMMC, u32ClkParam << 8);

    #elif defined(CONFIG_MSTAR_EINSTEIN) || defined(CONFIG_MSTAR_NAPOLI)

    /*div4 enable*/
    REG_SET_BITS_UINT16(REG_CLK_NFIE, BIT_CLK_ENABLE);

    /*set FCIE 4x clock*/
    REG_CLR_BITS_UINT16(REG_CLK_EMMC, BIT1|BIT0|EMMC_CLK_MASK);
    REG_SET_BITS_UINT16(REG_CLK_EMMC, u32ClkParam << 2);

    #elif defined(CONFIG_MSTAR_NIKON) || defined(CONFIG_MSTAR_KENYA) || defined(CONFIG_MSTAR_KRITI)

    /*div4 enable*/
    REG_SET_BITS_UINT16(REG_CLK_NFIE, BIT_CLK_ENABLE);

    /*set FCIE 4x clock*/
    REG_CLR_BITS_UINT16(REG_CLK_EMMC, BIT1|BIT0);
    REG_CLR_BITS_UINT16(REG_CLK_EMMC, EMMC_CLK_MASK);
    REG_SET_BITS_UINT16(REG_CLK_EMMC, u32ClkParam << 0);

	#elif defined(CONFIG_MSTAR_MONACO) || defined(CONFIG_MSTAR_MIAMI) || \
		defined(CONFIG_MSTAR_CLIPPERS) || defined(CONFIG_MSTAR_MUJI) || \
		defined(CONFIG_MSTAR_CELTICS)

	REG_SET_BITS_UINT16(REG_CLK_NFIE, BIT_CLK_ENABLE);
	REG_CLR_BITS_UINT16(REG_CLK_NFIE, BIT1|BIT0);
	REG_SET_BITS_UINT16(REG_CLK_NFIE, u32ClkParam);

    #else
	REG_CLR_BITS_UINT16(reg_ckg_fcie, BIT6-1); // enable FCIE clk, set to lowest clk

	REG_SET_BITS_UINT16(reg_ckg_fcie, u32ClkParam);

	#if defined(CONFIG_MSTAR_EIFFEL)
	//Default clock is 32MHz
	//u32ClkParam = sgau16_FCIEClk_1X_To_4X_[(u32ClkParam>>2)&0x0F];
	u32ClkParam = 0;
	/*set FCIE 4x clock*/
	REG_CLR_BITS_UINT16(REG_CLK_EMMC, BIT9|BIT8);
    REG_CLR_BITS_UINT16(REG_CLK_EMMC, EMMC_CLK_MASK);
    REG_SET_BITS_UINT16(REG_CLK_EMMC, u32ClkParam << 8);
	#endif

    #endif  // (ENABLE_NIKE) || defined(CONFIG_MSTAR_MADISON) || defined(CONFIG_MSTAR_MIAMI) || defined(CONFIG_MSTAR_MONACO) || defined(ENABLE_NADAL) || (ENABLE_NUGGET)  || defined(CONFIG_MSTAR_CLIPPERS) || defined(CONFIG_MSTAR_MUJI)

	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	REG_WRITE_UINT16(NC_LATCH_DATA, BIT_RE_DATA_LATCH_SEL_1T);
	#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	REG_WRITE_UINT16(NC_LATCH_DATA, BIT_NC_LATCH_DATA_2_0_T|BIT_NC_LATCH_STS_2_0_T);
	#endif

    return UNFD_ST_SUCCESS;
}

#endif
