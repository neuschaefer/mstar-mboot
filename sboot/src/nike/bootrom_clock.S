/*
 *#############################################################################
 *
 * Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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

    mov         r13, lr

@// WREG        (MS_BUS_RIU_ADDR + (0x100B22 << 1)), 0x0000
@// WREG        (MS_BUS_RIU_ADDR + (0x100B22 << 1)), 0x8000     @//Enable MIPS PLL
    RREG        r0, (MS_BUS_RIU_ADDR + (0x100B22 << 1))
    ldr         r1, =0x8000
    orr         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100B22 << 1))

                                                                @//MCU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B20 << 1) + 1), 0x00   @//Set CLK_MCU to 216MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B20 << 1)), 0x01       @//Set MCU clock to CLK_MCU

    WREG_B      (MS_BUS_RIU_ADDR + (0x100B94 << 1)), 0x00       @//Set CLK_R2_SECURE to 240MHz (Enabled)

    WREG_B      (MS_BUS_RIU_ADDR + (0x100B26 << 1) + 1), 0x0C   @//Set CLK_UART0 to 123MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B28 << 1)), 0x0C       @//Set CLK_UART1 to 123MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B28 << 1) + 1), 0x0C   @//Set CLK_UART2 to 123MHz (Enabled)

                                                                @//SPI Flash
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B2C << 1)), 0x14       @//Set CLK_SPI to 54MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B2E << 1)), 0x04       @//Set CLK_SPI_M to 48MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B2E << 1)), 0x24       @//Set CLK_SPI_M to 48MHz

                                                                @//PCMCIA
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B34 << 1)), 0x00       @//Set CLK_PCM to 27MHz (Enabled)

                                                                @//DIG_MUX
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B34 << 1) + 1), 0x00   @//Set CLK_TCK (Enabled)

                                                                @//MIU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3C << 1)), 0x02       @//Set MEMPLL_CLK_BUF to mempll0_clk05x(Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3C << 1) + 1), 0x01   @//Set CLK_MPLL_SYN to 432MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3E << 1)), 0x00       @//Set CLK_MIU to 216MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B3E << 1) + 1), 0x00   @//Set CLK_MIU_REC to XTAL div 8 (Enabled)

                                                                @//VD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B40 << 1)), 0x00       @//Set VD clock source to VD_ADC_CLK (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B40 << 1) + 1), 0x01   @//Set CLK_VD (Disabled)

                                                                @//VDMCU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B42 << 1)), 0x11       @//Set CLK_VDMCU to 108MHz (Disabled)

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    WREG_B      (MS_BUS_RIU_ADDR + (0x100B44 << 1)), 0x01       @//Set CLK_MCU_MAIL0 to CLK_MCU (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B44 << 1) + 1), 0x01   @//Set CLK_MCU_MAIL1 to CLK_MCU (Disabled)
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
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B52 << 1) + 1), 0xC0   @//Set Gating CLK_TSP / CLK_AESDMA
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B54 << 1)), 0x21       @//Set CLK_TSP to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B54 << 1) + 1), 0x01   @//Set CLK_STC0 to STC0 synthesizer output (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B56 << 1) + 1), 0x01   @//Set CLK_STAMP to 27MHz (Disabled)

                                                                @//VP8
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B5E << 1)), 0x01       @//Set CLK_VP8 to 216MHz (Disabled)

                                                                @//GPD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B5E << 1) + 1), 0x01   @//Set CLK_GPD to 216MHz (Disabled)

                                                                @//VD_MHEG5
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B60 << 1)), 0x01       @//Set CLK_VD_MHEG5 to 240MHz (Disabled)

                                                                @//HVD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B62 << 1)), 0x0C       @//Set CLK_HVD to 345MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B68 << 1)), 0x01       @//Set CLK_HVD_AEC to 288MHz (Disabled)

                                                                @//JPD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B6A << 1)), 0x01       @//Set CLK_JPD to 216MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B6A << 1) + 1), 0x01   @//Set CLK_NJPD to 144MHz (Disabled)

                                                                @//MVD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B72 << 1)), 0x01       @//Set CLK_MVD to 160MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B72 << 1) + 1), 0x01   @//Set CLK_MVD2 to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B74 << 1) + 1), 0x01   @//Set CLK_MVD_LUMMA_A (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B76 << 1)), 0x01       @//Set CLK_MVD_LUMMA_B (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B76 << 1) + 1), 0x01   @//Set CLK_MVD_LUMMA_C (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B78 << 1)), 0x01       @//Set CLK_MVD_RMEM_C (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B78 << 1) + 1), 0x01   @//Set CLK_MVD_RMEM1_C (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B7C << 1)), 0x01       @//Set CLK_MVD_RREFDAT (Disabled)

                                                                @//MVOP
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B98 << 1)), 0x01       @//Set CLK_DC0 to synchronous mode (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B98 << 1) + 1), 0x01   @//Set CLK_DC1 to synchronous mode (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B9A << 1)), 0x01       @//Set CLK_SUB_DC0 to synchronous mode (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B9A << 1) + 1), 0x01   @//Set CLK_SUB_DC1 to synchronous mode (Disabled)

                                                                @//Smart Card
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD8 << 1)), 0x01       @//Set CLK_SMART to 172MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD8 << 1) + 1), 0x01   @//Set CLK_SMART_CA to switcher_no_jitter selection (Disabled)
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

                                                                @//EMAC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC0 << 1)), 0x00       @//Set CLK_EMAC_AHB to 123MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC0 << 1) + 1), 0x00   @//Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC2 << 1)), 0x00       @//Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC2 << 1) + 1), 0x00   @//Set CLK_EMAC_TX_REF to CLK_EMAC_TX_IN (50MHz) (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BC4 << 1)), 0x00       @//Set CLK_EMAC_RX_REF to CLK_EMAC_RX_IN (50MHz) (Enabled)

                                                                @//eMMC and NAND Flash
@// WREG_B      (MS_BUS_RIU_ADDR + (0x100B62 << 1) + 1), 0x05   @//Set CLK_NFIE to 48MHz (Disabled)

                                                                @//SDIO
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD2 << 1)), 0x01       @//Set CLK_SDIO to XTAL (Disabled)

    bl          BootRom_SetL3Clock

    mov         lr, r13
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetL3Clock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_SetL3Clock:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         r1, =0x0080
    orr         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101882 << 1))

    bx          lr

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
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

    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1) + 1), 0x04   @//Set clock of clk_spi to 86MHz
    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1) + 1), 0x44   @//Switch clk_spi between clk_mcu_p and clk_ext_xtali_buf
    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1)), 0x80       @//Set clock of MCU to 170MHz

    bx          lr

 #endif

    .end

