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
#ifndef _MACRO_INC_
#include "macro.inc"
#endif

    .text
    .global     BootRom_InitClock

BootRom_InitClock:

    @CLKGEN0
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG    0x1F201640, 0x0000
    WREG    0x1F201640, 0x0001      @reg_ckg_mcu=216MHz
    WREG_B  0x1F001C80, 0x00	    @Set MCU clock to XTAL
    WREG_B  0x1F001C80, 0x38	    @Set CLK_MCU_P to 216MHz
    WREG_B  0x1F001C80, 0xb8	    @Set MCU clock to CLK_MCU_P
    .endif
    WREG    0x1F20164C, 0x0C00      @reg_ckg_uart0=123MHz
    WREG    0x1F201650, 0x000C      @reg_ckg_uart1=123MHz
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG    0x1F201658, 0x0044      @reg_clk_spi=54MHz
    .endif
    WREG    0x1F201668, 0x0000      @reg_ckg_pcm=27MHz
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG    0x1F201670, 0x0100      @reg_ckg_mpll_syn=432MHz
    //WREG    0x1F201674, 0x0808      @reg_ckg_miu
    WREG    0x1F201678, 0x0000      @reg_ckg_miu_rec=XTAL div 8
    .endif
    WREG    0x1F2016A8, 0x1100      @reg_ckg_tsp and stc0/stc1 = disable clk
    WREG    0x1F201700, 0x0000      @reg_ckg_gopg0/gopg1=odlck
    WREG    0x1F201704, 0x0400      @reg_ckg_gopg2/gopd=odclk
    WREG    0x1F201708, 0x0000      @reg_ckg_gopg3=odclk
    WREG    0x1F20170C, 0x0000      @reg_ckg_psram0/1 clock on
    WREG    0x1F201720, 0x0000      @reg_clk_ge=216MHz
    WREG    0x1F201780, 0x0400      @reg_ckg_emac_rx and reg_ckg_emac_ahb = 123MHz
    WREG    0x1F201784, 0x0004      @reg_ckg_emac_tx_ref,reg_ckg_emac_tx
    WREG    0x1F201788, 0x0000      @reg_ckg_emac_rx_ref
    @//WREG    0x1F201790, 0x0014      @reg_ckg_nfie=40MHz
    WREG    0x1F201798, 0x000C      @reg_ckg_onif=54MHz

    @CLKGEN1
    WREG    0x1F20663C, 0x0010      @reg_ckg_dmdmcu=108MHz
    WREG    0x1F206670, 0x0004      @reg_ckg_disp_ipath=80MHz

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetClockRatio
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetClockRatio
BootRom_SetClockRatio:

    WREG_B    0x1F203ADC, 0x04      @mcu:L2 = 2:1
    WREG_B    0x1F203ADC, 0x05

    DELAYUS     10
    
    WREG      0x1F201644, 0x8000    @switch to CPU CLK

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetL3Clock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetL3Clock
BootRom_SetL3Clock:
#if 0
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
#endif

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         r4, =0x00000080
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))

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

