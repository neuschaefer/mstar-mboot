/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

    .text
    .global     BootRom_InitClock

BootRom_InitClock:

#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)

    WREG        (MS_BUS_RIU_ADDR + (0x100B20 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100B20 << 1)), 0x0001     @//reg_ckg_mcu=216MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100B26 << 1)), 0x0C00     @//reg_ckg_uart0=123MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100B28 << 1)), 0x000C     @//reg_ckg_uart1=123MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100B2C << 1)), 0x0044     @//reg_clk_spi=54MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100B34 << 1)), 0x0000     @//reg_ckg_pcm=27MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100B38 << 1)), 0x0100     @//reg_ckg_mpll_syn=432MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100B3A << 1)), 0x0808     @//reg_ckg_miu
    WREG        (MS_BUS_RIU_ADDR + (0x100B3C << 1)), 0x0000     @//reg_ckg_miu_rec=XTAL div 8
    WREG        (MS_BUS_RIU_ADDR + (0x100B54 << 1)), 0x1100     @//reg_ckg_tsp and stc0/stc1 = disable clk
    WREG        (MS_BUS_RIU_ADDR + (0x100B80 << 1)), 0x0000     @//reg_ckg_gopg0/gopg1=odlck
    WREG        (MS_BUS_RIU_ADDR + (0x100B82 << 1)), 0x0400     @//reg_ckg_gopg2/gopd=odclk
    WREG        (MS_BUS_RIU_ADDR + (0x100B84 << 1)), 0x0000     @//reg_ckg_gopg3=odclk
    WREG        (MS_BUS_RIU_ADDR + (0x100B86 << 1)), 0x0000     @//reg_ckg_psram0/1 clock on
    WREG        (MS_BUS_RIU_ADDR + (0x100B90 << 1)), 0x0000     @//reg_clk_ge=216MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100BC0 << 1)), 0x0400     @//reg_ckg_emac_rx and reg_ckg_emac_ahb = 123MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100BC2 << 1)), 0x0004     @//reg_ckg_emac_tx_ref,reg_ckg_emac_tx
    WREG        (MS_BUS_RIU_ADDR + (0x100BC4 << 1)), 0x0000     @//reg_ckg_emac_rx_ref
    WREG        (MS_BUS_RIU_ADDR + (0x100BC8 << 1)), 0x0014     @//reg_ckg_nfie=40MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100BCC << 1)), 0x000C     @//reg_ckg_onif=54MHz
    WREG        (MS_BUS_RIU_ADDR + (0x100BD0 << 1)), 0x001C     @//reg_ckg_mpif=13.5MHz
    WREG        (MS_BUS_RIU_ADDR + (0x10331E << 1)), 0x0010     @//reg_ckg_dmdmcu=108MHz
    WREG        (MS_BUS_RIU_ADDR + (0x103338 << 1)), 0x0004     @//reg_ckg_disp_ipath=80MHz

#else

                                                                @//MCU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B20 << 1) + 1), 0x00   @//Set CLK_MCU to 216MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B20 << 1)), 0x01       @//Set MCU clock to CLK_MCU

@// WREG_B      (MS_BUS_RIU_ADDR + (0x100B22 << 1)), 0x00       @//Set CLK_OCP (Enabled)
@// WREG_B      (MS_BUS_RIU_ADDR + (0x100B22 << 1) + 1), 0x80   @//Set CLK_MIPS to clk_mipspll_vco (Enabled)

    WREG_B      (MS_BUS_RIU_ADDR + (0x100B24 << 1)), 0x88       @//Set CLK_AEON to 216MHz (Enabled)

    WREG_B      (MS_BUS_RIU_ADDR + (0x100B26 << 1) + 1), 0x0C   @//Set CLK_UART0 to 123MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B28 << 1)), 0x0C       @//Set CLK_UART1 to 123MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B28 << 1) + 1), 0x0C   @//Set CLK_UART2 to 123MHz (Enabled)

                                                                @//SPI Flash
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B2C << 1)), 0x14       @//Set CLK_SPI to 54MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B2E << 1)), 0x04       @//Set CLK_SPI_M to 48MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B2E << 1)), 0x24       @//Set CLK_SPI_M to 48MHz

                                                                @//PCM / DIG_MUX
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B34 << 1)), 0x00       @//Set CLK_PCM to 27MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B34 << 1) + 1), 0x00   @//Set CLK_TCK (Enabled)

                                                                @//MIU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3C << 1)), 0x02       @//Set MEMPLL_CLK_BUF to mempll0_clk05x(Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3C << 1) + 1), 0x01   @//Set CLK_MPLL_SYN to 432MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3E << 1)), 0x04       @//Set CLK_MIU2x to 480MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3E << 1) + 1), 0x00   @//Set CLK_MIU_REC to XTAL div 8 (Enabled)

                                                                @//VD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B40 << 1)), 0x00       @//Set VD clock source to VD_ADC_CLK (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B40 << 1) + 1), 0x01   @//Set CLK_VD (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B42 << 1)), 0x11       @//Set CLK_VDMCU to 108MHz (Disabled)
@// WREG_B      (MS_BUS_RIU_ADDR + (0x100B42 << 1) + 1), 0x05   @//Set CLK_VD200 to 216MHz (Disabled)

#ifndef CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B44 << 1)), 0x01       @//Set CLK_MCU_MAIL0 to CLK_MCU (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B44 << 1) + 1), 0x05   @//Set CLK_MCU_MAIL1 to CLK_MCU (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B46 << 1)), 0x01       @//Set CLK_VD2X (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B46 << 1) + 1), 0x01   @//Set CLK_VD32FSC to VD_ADC_CLK (Disabled)

                                                                @//VE
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B48 << 1)), 0x01       @//Set CLK_VE to 27MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B48 << 1) + 1), 0x09   @//Set CLK_VEDAC to 108MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B4A << 1)), 0x01       @//Set CLK_VE_IN to CLK_ADC (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B4C << 1)), 0x01       @//Set CLK_DACA2 to VIF clock (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B4C << 1) + 1), 0x01   @//Set CLK_DACB2 to VIF clock (Disabled)

                                                                @//TSP
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B50 << 1)), 0x01       @//Set CLK_TS0 to TS0_CLK (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B50 << 1) + 1), 0x05   @//Set CLK_TS1 to TS1_CLK (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B54 << 1)), 0x01       @//Set CLK_TSP to 144MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B54 << 1) + 1), 0x01   @//Set CLK_STC0 to STC0 synthesizer output (Disabled)

                                                                @//GPU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B5C << 1)), 0x01       @//Set CLK_GPU to G3DPLL (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B5E << 1)), 0x01       @//Set CLK_VP8 to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B5E << 1) + 1), 0x01   @//Set CLK_GPD to 216MHz (Disabled)

                                                                @//VD_MHEG5
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B60 << 1)), 0x05       @//Set CLK_VD_MHEG5 to 216MHz (Disabled)

                                                                @//HVD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B62 << 1)), 0x05       @//Set CLK_HVD to 216MHz (Disabled)

                                                                @//eMMC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B62 << 1) + 1), 0x00   @//Set CLK_HVD to XTAL (Enabled)

                                                                @//JPD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B6A << 1)), 0x01       @//Set CLK_JPD to 216MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B6A << 1) + 1), 0x01   @//Set CLK_NJPD to 144MHz (Disabled)

                                                                @//MVD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B72 << 1)), 0x1D       @//Set CLK_MVD to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B72 << 1) + 1), 0x01   @//Set CLK_MVD2 to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B74 << 1)), 0x01       @//Set CLK_MVD_CHROMA (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B74 << 1) + 1), 0x01   @//Set CLK_MVD_LUMMA_A (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B76 << 1)), 0x01       @//Set CLK_MVD_LUMMA_B (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B76 << 1) + 1), 0x01   @//Set CLK_MVD_LUMMA_C (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B78 << 1)), 0x01       @//Set CLK_MVD_RMEM_C (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B78 << 1) + 1), 0x01   @//Set CLK_MVD_RMEM1_C (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B7C << 1)), 0x01       @//Set CLK_MVD_RREFDAT (Disabled)
#endif
                                                                @//GOP
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B80 << 1)), 0x00       @//Set CLK_GOPG0 to clk_odclk_p (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B80 << 1) + 1), 0x00   @//Set CLK_GOPG1 to clk_odclk_p (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B82 << 1)), 0x00       @//Set CLK_GOPG2 to clk_odclk_p (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B82 << 1) + 1), 0x04   @//Set CLK_GOPD to CLK_ODCLK (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B84 << 1)), 0x00       @//Set CLK_GOPG3 to clk_odclk_p (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B86 << 1)), 0x00       @//Set CLK_PSRAM0 (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B86 << 1) + 1), 0x00   @//Set CLK_PSRAM1 (Enabled)

                                                                @//GE
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B90 << 1)), 0x00       @//Set CLK_GE to 216MHz (Enabled)

#ifndef CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH
                                                                @//Secure R2
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B94 << 1)), 0x05       @//Set CLK_SecureR2 to 192MHz (Disabled)

                                                                @//MVOP
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B98 << 1)), 0x01       @//Set CLK_DC0 to synchronous mode (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B98 << 1) + 1), 0x01   @//Set CLK_DC1 to synchronous mode (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B9A << 1)), 0x01       @//Set CLK_SUB_DC0 to synchronous mode (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B9A << 1) + 1), 0x01   @//Set CLK_SUB_DC1 to synchronous mode (Disabled)
#endif

                                                                @//EMAC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC0 << 1)), 0x00       @//Set CLK_EMAC_AHB to 123MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC0 << 1) + 1), 0x00   @//Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC2 << 1)), 0x00       @//Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)

                                                                @//NAND Flash
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC8 << 1)), 0x0C       @//Set CLK_NFIE to 32MHz (Enabled)
@// WREG_B      (MS_BUS_RIU_ADDR + (0x100BCC << 1)), 0x09       @//Set CLK_ONIF to 27MHz (Disabled)

#ifndef CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH
                                                                @//MPIF
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD0 << 1)), 0x01       @//Set CLK_MPIF to 72MHz (Disabled)

                                                                @//Smart Card
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD8 << 1)), 0x01       @//Set CLK_SMART to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD8 << 1) + 1), 0x01   @//Set CLK_SMART_CA to switcher_no_jitter selection (Disabled)
#endif

                                                                @//Scaler
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BB0 << 1)), 0x01       @//Set CLK_LPLL_SYN to 432MHz (Enabled)

    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA2 << 1)), 0x44       @//Set CLK_FICLK_F1 to CLK_FCLK and Set CLK_FICLK_3D to CLK_FCLK (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA2 << 1) + 1), 0x04   @//Set CLK_FICLK_F2 to CLK_FCLK (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA4 << 1)), 0x04       @//Set CLK_FODCLK to XTAL (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA4 << 1) + 1), 0x1C   @//Set CLK_VCLK to XTAL (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA6 << 1)), 0x1C       @//Set CLK_ODCLK to LPLL output clock (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA6 << 1) + 1), 0x1C   @//Set CLK_BT656 to LPLL output clock (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA8 << 1)), 0x20       @//Set CLK_IDCLK_F0 to XTAL (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BA8 << 1) + 1), 0x20   @//Set CLK_IDCLK_F1 to XTAL (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BAA << 1)), 0x20       @//Set CLK_IDCLK_F2 to XTAL (Enabled)

#ifndef CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH
                                                                @//DEMOD
    WREG_B      (MS_BUS_RIU_ADDR + (0x10331E << 1)), 0x0D       @//Set CLK_DMDMCU to 123MHz (Disabled)

    WREG_B      (MS_BUS_RIU_ADDR + (0x103300 << 1)), 0x11       @//Set CLK_ATSC_DVB_DIV divider factor to 0x11
    WREG_B      (MS_BUS_RIU_ADDR + (0x103300 << 1) + 1), 0x05   @//Set CLK_ATSC_DVB_DIV to clk_dmplldiv3

                                                                @//DVB-T/C
    WREG_B      (MS_BUS_RIU_ADDR + (0x103314 << 1)), 0x01       @//Set CLK_DVBTC_ADC to clk_demod_adcout (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x10331A << 1)), 0x01       @//Set CLK_VIFDBB_DAC to clk_dmplldiv10 (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x10331A << 1) + 1), 0x01   @//Set CLK_VIFDBB_VDAC to clk_dmplldiv10 (Disabled)

                                                                @//ATSC
    WREG_B      (MS_BUS_RIU_ADDR + (0x103308 << 1)), 0x01       @//Set CLK_ATSC_TS to clk_atsc_dvb_div (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x103308 << 1) + 1), 0x01   @//Set CLK_DVBTC_TS to clk_atsc_dvb_div (Disabled)

@// WREG_B      (MS_BUS_RIU_ADDR + (0x10326E << 1)), 0x40       @//Patch for 2.5V MOD Setting
#endif

#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetClockRatio
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetClockRatio
BootRom_SetClockRatio:
    WREG_B      (MS_BUS_RIU_ADDR + (0x101D6E << 1)), 0x04
    WREG_B      (MS_BUS_RIU_ADDR + (0x101D6E << 1)), 0x05      @//Set Clock Ratio to 2:1
@// WREG_B      (MS_BUS_RIU_ADDR + (0x101D6E << 1)), 0x07      @//Set Clock Ratio to 3:1
@// WREG_B      (MS_BUS_RIU_ADDR + (0x101D6E << 1)), 0x09      @//Set Clock Ratio to 4:1
    WREG        (MS_BUS_RIU_ADDR + (0x100B22 << 1)), 0x8000

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetL3Clock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetL3Clock
BootRom_SetL3Clock:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
    ldr         r4, =0x0000EFFF
    and         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
    ldr         r4, =0x00001000
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
    ldr         r4, =0x0000EFFF
    and         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         r4, =0x00000080
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))

    bx          lr

#ifndef CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH
/*
 *#############################################################################
 * BootRom_InitSpiFlashClock SPI Clock init
 * @param  None
 * @return None
 * @note   do SPI Clock init
 *#############################################################################
 */
    .global     BootRom_InitSpiFlashClock
BootRom_InitSpiFlashClock:

    WREG_B      (MS_BUS_RIU_ADDR + (0x0008E2 << 1)), 0xFF       @//Set CSZ deselect time to 16 SPI clock cycles
                                                                @//Set CSZ setup time to 16 SPI clock cycles
    WREG_B      (MS_BUS_RIU_ADDR + (0x0008E2 << 1) + 1), 0x0F   @//Set CSZ hold time to 16 SPI clock cycles
    WREG_B      (MS_BUS_RIU_ADDR + (0x0008E4 << 1)), 0x01       @//Enable fast read mode

    bx          lr

    .size       BootRom_InitSpiFlashClock,.-BootRom_InitSpiFlashClock

    .text
    .global     BootRom_ChangeSpiFlashClock

BootRom_ChangeSpiFlashClock:

    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1) + 1), 0x04   @//Set clock of clk_spi to 86MHz
    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1) + 1), 0x44   @//Switch clk_spi between clk_mcu_p and clk_ext_xtali_buf
    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1)), 0x80   @//Set clock of MCU to 170MHz

    bx          lr

 #endif

    .end

