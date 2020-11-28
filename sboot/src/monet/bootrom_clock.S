/*
 *#############################################################################
 *
 * Copyright (c) 2006-2015 MStar Semiconductor, Inc.
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

    mov         x29, x30
    
    ldr         x1, =(MS_BUS_RIU_ADDR + (0x100b00 << 1))
    ldr         w0, [x1, #(0x22 << 1)]
    ldr         w2, =0x8000
    orr         w0, w0, w2
    str         w0, [x1, #(0x22 << 1)]

                                            //PM51
    ldr         w0, =0x0001                 //Set CLK_MCU to 216MHz (Enabled)
    str         w0, [x1, #(0x20 << 1)]

                                            //UART
    ldr         w0, =0x0c00                 //Set CLK_UART0 to 123MHz (Enabled)
    str         w0, [x1, #(0x26 << 1)]
    ldr         w0, =0x0c0c                 //Set CLK_UART1/CLK_UART2 to 123MHz (Enabled)
    str         w0, [x1, #(0x28 << 1)]
    ldr         w0, =0x0c0c                 //Set CLK_FUART/CLK_FUART1 to 123MHz (Enabled)
    str         w0, [x1, #(0x2a << 1)]
    ldr         w0, =0x0c0c                 //Set CLK_UART3/CLK_UART4 to 123MHz (Enabled)
    str         w0, [x1, #(0x32 << 1)]

                                            //SPI Flash
    ldr         w0, =0x44                   //SPI Flash: Set CLK_SPI to 54MHz (Enabled)
    strb        w0, [x1, #(0x2c << 1)]
    ldr         w0, =0x04                   //SPI Flash: Set CLK_SPI_M to 48MHz (Enabled)
    strb        w0, [x1, #(0x2e << 1)]
    ldr         w0, =0x24                   //SPI Flash: Set CLK_SPI_M to 48MHz (Enabled)
    strb        w0, [x1, #(0x2e << 1)]

    ldr         w0, =0x0000                 //PCMCIA: Set CLK_PCM to 27MHz (Enabled)
                                            //DIG_MUX: Set CLK_TCK (Enabled)
    str         w0, [x1, #(0x34 << 1)]

                                            //MIU
    ldr         w0, =0x0808                 //Set CLK_MIU to MIU_128BUS_PLL_CLK_VCO_OUT (Enabled)
    str         w0, [x1, #(0x3a << 1)]

                                            //GE
    ldr         w0, =0x0000                 //Set CLK_GE to 216MHz (Enabled)
    str         w0, [x1, #(0x90 << 1)]

                                            //GOP
    ldr         w0, =0x0000                 //Set CLK_GOPG0 to clk_odclk_p (Enabled)
                                            //Set CLK_GOPG1 to clk_odclk_p (Enabled)
    str         w0, [x1, #(0x80 << 1)]
    ldr         w0, =0x0400                 //Set CLK_GOPG2 to clk_odclk_p (Enabled)
                                            //Set CLK_GOPD to CLK_ODCLK (Enabled)
    str         w0, [x1, #(0x82 << 1)]
    ldr         w0, =0x0000                 //Set CLK_GOPG3 to clk_odclk_p (Enabled)
    str         w0, [x1, #(0x84 << 1)]
    ldr         w0, =0x0000                 //Set CLK_PSRAM0 (Enabled)
                                            //Set CLK_PSRAM1 (Enabled)
    str         w0, [x1, #(0x86 << 1)]

                                            //EMAC
    ldr         w0, =0x0000                 //Set CLK_EMAC_AHB to 123MHz (Enabled)
                                            //Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    str         w0, [x1, #(0xc0 << 1)]
    ldr         w0, =0x0100                 //Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)
                                            //Set CLK_EMAC_TX_REF to CLK_EMAC_TX_IN (50MHz) (Disabled)
    str         w0, [x1, #(0xc2 << 1)]
    ldr         w0, =0x0001                 //Set CLK_EMAC_RX_REF to CLK_EMAC_RX_IN (50MHz) (Disabled)
    str         w0, [x1, #(0xc4 << 1)]

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
                                            //Secure R2
    ldr         w0, =0x00                   //Set CLK_R2_SECURE to 240MHz (Enabled)
    strb        w0, [x1, #(0x7a << 1)]

#if 0
                                                                //VD
    WREG        (MS_BUS_RIU_ADDR + (0x100B40 << 1)), 0x0100     //Set VD clock source to VD_ADC_CLK (Enabled)
                                                                //Set CLK_VD (Disabled)

                                                                //VDMCU
    WREG        (MS_BUS_RIU_ADDR + (0x100B42 << 1)), 0x0011     //Set CLK_VDMCU to 108MHz (Disabled)
                                                                //Set CLK_VD200 to 432MHz (Enabled)

    WREG        (MS_BUS_RIU_ADDR + (0x100B44 << 1)), 0x0101     //Set CLK_MCU_MAIL0 to CLK_MCU (Disabled)
                                                                //Set CLK_MCU_MAIL1 to CLK_MCU (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B46 << 1)), 0x0101     //Set CLK_VD2X (Disabled)
                                                                //Set CLK_VD32FSC to VD_ADC_CLK (Disabled)

                                                                //VE
    WREG        (MS_BUS_RIU_ADDR + (0x100B48 << 1)), 0x0901     //Set CLK_VE to 27MHz (Disabled)
                                                                //Set CLK_VEDAC to 108MHz (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B4A << 1)), 0x01       //Set CLK_VE_IN to CLK_ADC (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B4C << 1)), 0x0101     //Set CLK_DACA2 to VIF clock (Disabled)
                                                                //Set CLK_DACB2 to VIF clock (Disabled)

                                                                //TSP
    WREG        (MS_BUS_RIU_ADDR + (0x100B50 << 1)), 0x0501     //Set CLK_TS0 to TS0_CLK (Disabled)
                                                                //Set CLK_TS1 to TS1_CLK (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B52 << 1)), 0x4109     //Set CLK_TS2 to TS2_CLK (Disabled)
                                                                //Set CLK_TS_CB to TS0_CLK (Disabled), Gate CLK_TSP
    WREG        (MS_BUS_RIU_ADDR + (0x100B54 << 1)), 0x1110     //Set CLK_TSP to 172MHz (Enabled)
                                                                //Set CLK_STC0 to STC0 synthesizer output (Disabled)
                                                                //Set CLK_STC1 to STC1 synthesizer output (Disabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B56 << 1) + 1), 0x01   //Set CLK_STAMP to 27MHz (Disabled)

                                                                //VD_MHEG5
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B60 << 1)), 0x01       //Set CLK_VD_MHEG5 to 240MHz (Disabled)

                                                                //HVD
    WREG        (MS_BUS_RIU_ADDR + (0x100B62 << 1)), 0x010C     //Set CLK_HVD to 240MHz (Disabled)
                                                                //Set CLK_VP8 to 216MHz (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B64 << 1)), 0x0001     //Set CLK_VP6 to 192MHz (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B66 << 1)), 0x0101     //Set CLK_EVD_PPU to 480MHz (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B68 << 1)), 0x0101     //Set CLK_HVD_AEC to 288MHz (Disabled)
                                                                //Set CLK_EVD to 384MHz (Disabled)

                                                                //JPD
    WREG        (MS_BUS_RIU_ADDR + (0x100B6A << 1)), 0x0101     //Set CLK_OJPD to 216MHz (Disabled)
                                                                //Set CLK_NJPD to 144MHz (Disabled)

                                                                //MVD
    WREG        (MS_BUS_RIU_ADDR + (0x100B72 << 1)), 0x0101     //Set CLK_MVD to 216MHz (Disabled)
                                                                //Set CLK_MVD2 to 216MHz (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B74 << 1)), 0x0101     //Set CLK_MVD_LUMMA_A (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B76 << 1)), 0x0101     //Set CLK_MVD_LUMMA_B (Disabled)
                                                                //Set CLK_MVD_LUMMA_C (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B78 << 1)), 0x0101     //Set CLK_MVD_RMEM (Disabled)
                                                                //Set CLK_MVD_RMEM1 (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B7a << 1)), 0x0111     //Disable CLK_MVD_CHROMA_A
                                                                //Disable CLK_MVD_CHROMA_B
                                                                //Disable CLK_MVD_CHROMA_C
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B7c << 1)), 0x01       //Set CLK_MVD_RREFDAT (Disabled)

                                                                //MVOP
    WREG        (MS_BUS_RIU_ADDR + (0x100B98 << 1)), 0x0101     //Set CLK_DC0 to synchronous mode (Disabled)
                                                                //Set CLK_DC1 to synchronous mode (Disabled)
    WREG        (MS_BUS_RIU_ADDR + (0x100B9A << 1)), 0x0101     //Set CLK_SUB_DC0 to synchronous mode (Disabled)
                                                                //Set CLK_SUB_DC1 to synchronous mode (Disabled)

                                                                //Smart Card
    WREG        (MS_BUS_RIU_ADDR + (0x100BD8 << 1)), 0x0101     //Set CLK_SMART to 172MHz (Disabled)
                                                                //Set CLK_SMART_CA to switcher_no_jitter selection (Disabled)

                                                                //NAND Flash
    WREG        (MS_BUS_RIU_ADDR + (0x100BC8 << 1)), 0x050c     //Set CLK_NFIE to 36MHz (Enabled)
                                                                //Set CLK_EMMC to 108MHz (Disabled)
#endif

#if !defined(CONFIG_MSTAR_TITANIA_BD_FPGA) && \
    !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    bl          BootRom_InitSpiFlashClock
#endif

#if defined(CONFIG_MSTAR_GPU_MANUAL)
    bl          BootRom_SetGPUClock
#endif
 
    mov         x30, x29
    ret

#if defined(CONFIG_MSTAR_GPU_MANUAL)
//-------------------------------------------------------------------------------------------------
// BootRom_SetGPUClock
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
BootRom_SetGPUClock:
    //Set GPU Clock
    ldr         x1, =(MS_BUS_RIU_ADDR + (0x110800 << 1))
    ldr         w0, =CONFIG_GPU_CLOCK
    strb        w0, [x1, #(0x8c << 1)]
    ldr         w0, [x1, #(0xd2 << 1)]
    orr         w0, w0, #0x01
    strb        w0, [x1, #(0xd2 << 1)]

    ret
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

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x000a00 << 1))
    ldr         w0, =0x0fff                 //Set CSZ deselect time/CSZ setup time/CSZ hold time to 16 SPI clock cycles
    str         w0, [x1, #(0xe2 << 1)]
    ldr         w0, =0x01                   //Enable fast read mode
    strb        w0, [x1, #(0xe4 << 1)]

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x000e00 << 1))
    ldr         w0, =0x04                   //Set clock of clk_spi to 86MHz
    strb        w0, [x1, #((0x40 << 1) + 1)]
    ldr         w0, =0x44                   //Switch clk_spi between clk_mcu_p and clk_ext_xtali_buf
    strb        w0, [x1, #((0x40 << 1) + 1)]
    ldr         w0, =0x80                   //Set clock of MCU to 170MHz
    strb        w0, [x1, #(0x40 << 1)]

    ret

 #endif

    .end

