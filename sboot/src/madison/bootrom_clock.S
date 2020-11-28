/*
 *#############################################################################
 *
 * Copyright (c) 2006-2014 MStar Semiconductor, Inc.
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

    RREG        r0, (MS_BUS_RIU_ADDR + (0x100B22 << 1))
    ldr         r1, =0x8000
    orr         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100B22 << 1))

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100b00 << 1))
    ldr         r0, =0x0001                 @//Set CLK_MCU to 216MHz (Enabled)
    str         r0, [r1, #(0x20 << 1)]

    ldr         r0, =0x0000                 @//Set CLK_R2_SECURE to 240MHz (Enabled)
    str         r0, [r1, #(0x94 << 1)]

    ldr         r0, =0x0c00                 @//Set CLK_UART0 to 123MHz (Enabled)
    str         r0, [r1, #(0x26 << 1)]
    ldr         r0, =0x0c0c                 @//Set CLK_UART1/CLK_UART2 to 123MHz (Enabled)
    str         r0, [r1, #(0x28 << 1)]

    ldr         r0, =0x0014                 @//Set CLK_SPI to 54MHz (Enabled)
    str         r0, [r1, #(0x2c << 1)]
    ldr         r0, =0x0004                 @//Set CLK_SPI_M to 48MHzz (Enabled)
    str         r0, [r1, #(0x2e << 1)]
    ldr         r0, =0x0024                 @//Set CLK_SPI_M to 48MHz (Enabled)
    str         r0, [r1, #(0x2e << 1)]

    ldr         r0, =0x0000                 @//Set CLK_PCM to 27MHz (Enabled)
    str         r0, [r1, #(0x34 << 1)]

    ldr         r0, =0x0102                 @//Set MEMPLL_CLK_BUF to mempll0_clk05x(Enabled)
                                            @//Set CLK_MPLL_SYN to 432MHz (Enabled)
    str         r0, [r1, #(0x3c << 1)]
    ldr         r0, =0x0000                 @//Set CLK_MIU to 216MHz (Enabled)
                                            @//Set CLK_MIU_REC to XTAL div 8 (Enabled)
    str         r0, [r1, #(0x3e << 1)]

    ldr         r0, =0x0000                 @//Set CLK_GE to 216MHz (Enabled)
    str         r0, [r1, #(0x90 << 1)]

    ldr         r0, =0x0000                 @//Set CLK_GOPG0 to clk_odclk_p (Enabled)
                                            @//Set CLK_GOPG1 to clk_odclk_p (Enabled)
    str         r0, [r1, #(0x80 << 1)]
    ldr         r0, =0x0400                 @//Set CLK_GOPG2 to clk_odclk_p (Enabled)
                                            @//Set CLK_GOPD to CLK_ODCLK (Enabled)
    str         r0, [r1, #(0x82 << 1)]
    ldr         r0, =0x0000                 @//Set CLK_GOPG3 to clk_odclk_p (Enabled)
    str         r0, [r1, #(0x84 << 1)]
    ldr         r0, =0x0000                 @//Set CLK_PSRAM0 (Enabled)
                                            @//Set CLK_PSRAM1 (Enabled)
    str         r0, [r1, #(0x86 << 1)]

    ldr         r0, =0x0000                 @//Set CLK_EMAC_AHB to 123MHz (Enabled)
                                            @//Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    str         r0, [r1, #(0xc0 << 1)]
    ldr         r0, =0x0000                 @//Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)
                                            @//Set CLK_EMAC_TX_REF to CLK_EMAC_TX_IN (50MHz) (Enabled)
    str         r0, [r1, #(0xc2 << 1)]
    ldr         r0, =0x0000                 @//Set CLK_EMAC_RX_REF to CLK_EMAC_RX_IN (50MHz) (Enabled)
    str         r0, [r1, #(0xc4 << 1)]

#if 0
                                                                @//VD
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B40 << 1)), 0x00       @//Set VD clock source to VD_ADC_CLK (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B40 << 1) + 1), 0x01   @//Set CLK_VD (Disabled)

                                                                @//VDMCU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B42 << 1)), 0x11       @//Set CLK_VDMCU to 108MHz (Disabled)

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

                                                                @//eMMC and NAND Flash
@// WREG_B      (MS_BUS_RIU_ADDR + (0x100B62 << 1) + 1), 0x05   @//Set CLK_NFIE to 48MHz (Disabled)

                                                                @//SDIO
    WREG_B      (MS_BUS_RIU_ADDR + (0x100BD2 << 1)), 0x01       @//Set CLK_SDIO to XTAL (Disabled)
#endif

    bl          BootRom_SetL3Clock

#if !defined(CONFIG_MSTAR_TITANIA_BD_FPGA) && \
    !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    bl          BootRom_InitSpiFlashClock
#endif

#if defined(CONFIG_MSTAR_GPU_MANUAL)

    bl          BootRom_SetGPUClock
#endif       
       
    mov         lr, r13
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetL3Clock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_SetL3Clock:

    @//Set MIU1x Mode
    RREG        r0, (MS_BUS_RIU_ADDR + (0x101e20 << 1))
    bic         r0, r0, #0x10
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101e20 << 1))

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101800 << 1))
    ldr         r0, [r1, #(0x82 << 1)]
    orr         r0, r0, #0x0080
    str         r0, [r1, #(0x82 << 1)]

    bx          lr

#if defined(CONFIG_MSTAR_GPU_MANUAL) 
@//-------------------------------------------------------------------------------------------------
@// BootRom_SetGPUClock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_SetGPUClock:

    @//Set MIU1x Mode
    WREG_B      (MS_BUS_RIU_ADDR + (0x11088C << 1)), CONFIG_GPU_CLOCK       @//Set GPU Clock
    

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1108D2 << 1))
    add         r0,r0, #0x1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1108D2 << 1))
    
    bx          lr

#endif  

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
BootRom_InitSpiFlashClock:

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x000a00 << 1))
    ldr         r0, =0x0fff                 @//Set CSZ deselect time/CSZ setup time/CSZ hold time to 16 SPI clock cycles
    str         r0, [r1, #(0xe2 << 1)]
    ldr         r0, =0x01                   @//Enable fast read mode
    strb        r0, [r1, #(0xe4 << 1)]

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x000e00 << 1))
    ldr         r0, =0x04                   @//Set clock of clk_spi to 86MHz
    strb        r0, [r1, #((0x40 << 1) + 1)]
    ldr         r0, =0x44                   @//Switch clk_spi between clk_mcu_p and clk_ext_xtali_buf
    strb        r0, [r1, #((0x40 << 1) + 1)]
    ldr         r0, =0x80                   @//Set clock of MCU to 170MHz
    strb        r0, [r1, #(0x40 << 1)]

    bx          lr

 #endif

    .end

