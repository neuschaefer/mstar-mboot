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

// -----------------------------------------------------------------------------
// Linux EMAC.h define start
// -----------------------------------------------------------------------------
#ifndef __DRV_EMAC__
#define __DRV_EMAC__

#include <common.h>
#include <command.h>
#include <configs/uboot_board_config.h>
//-------------------------------------------------------------------------------------------------
//  Define Enable or Compiler Switches
//-------------------------------------------------------------------------------------------------
//#define RX_SOFTWARE_DESCRIPTOR
#define SOFTWARE_DESCRIPTOR
//#define CONFIG_ETHERNET_ALBANY

//#define RX_CHECKSUM
//#define INT_DELAY
//#define CHECKSUM_TEST
// Compiler Switches
#define REG_BIT_MAP
#define URANUS_ETHER_ADDR_CONFIGURABLE	/* MAC address can be changed? */
//#define CHIP_FLUSH_READ
//--------------------------------------------------------------------------------------------------
//  Constant definition
//--------------------------------------------------------------------------------------------------
#define TRUE                                1
#define FALSE                               0

#define BIT(x)                              (1<<x)

#define PHY_REG_BASIC	                    (0)
#define PHY_REG_STATUS	                    (1)
#define PHY_REG_LINK_PARTNER	            (5)

#define EMAC_ALLFF                          0xFFFFFFFF

// Base address here:
#define REG_ADDR_BASE						0xBF204000 		// The register address base. Depends on system define.
#define MAX_INT_COUNTER                     100
#define BUS_MIU0_BASE_CACHE                 0x80000000      //Beginning cachable bus address of MIU0
#define BUS_MIU0_BASE_NONCACHE              0xA0000000      //Beginning non-cachable bus address of MIU0 



#define barrier()       __asm__ __volatile__("": : :"memory")
#define _DLine()        {printf("%s line:%u\n",__FILE__, __LINE__);}

/* The forced speed, 10Mb, 100Mb. */
#define SPEED_10		10
#define SPEED_100		100


/* Duplex, half or full. */
#define DUPLEX_HALF		0x00
#define DUPLEX_FULL		0x01

#define PHY_CODE_SHIFT	    (16)
#define PHY_REG_SHIFT	    (18)
#define PHY_ADDR_SHIFT	    (23)
#define PHY_RW_SHIFT		(28)
#define PHY_LOW_HIGH_SHIFT	(30)

#define PHY_CODE		    (0x02)
#define PHY_LOW_HIGH		(0x01)
#define PHY_WRITE_OP		(0x01)
#define PHY_READ_OP			(0x02)

#define PHY_AN_DONE (0x1 << 5)
#define PHY_LINK_UP (0x1 << 2)

//0x100
#define EMAC_MIU_WP_EN              BIT(6)
#define EMAC_MIU_WP_INT_EN          BIT(7)
//0x102
#define EMAC_MIU_WP_INT_STATUS      BIT(4)
//0x11E
#define MIU_MIU_WP_UB               (0x11E)
//0x122
#define MIU_MIU_WP_LB               (0x122)
#define MIU_ADDR_UNIT               (8)

//-------------------------------------------------------------------------------------------------
//  Bit Define
//-------------------------------------------------------------------------------------------------
#define EMAC_MIU_RW       (0x3 <<  10)   //EMAC power on clk

// -------- EMAC_CTL : (EMAC Offset: 0x0)  --------
#define EMAC_LB           ( 0x1 <<  0) // (EMAC) Loopback. Optional. When set, loopback signal is at high level.
#define EMAC_LBL          ( 0x1 <<  1) // (EMAC) Loopback local.
#define EMAC_RE           ( 0x1 <<  2) // (EMAC) Receive enable.
#define EMAC_TE           ( 0x1 <<  3) // (EMAC) Transmit enable.
#define EMAC_MPE          ( 0x1 <<  4) // (EMAC) Management port enable.
#define EMAC_CSR          ( 0x1 <<  5) // (EMAC) Clear statistics registers.
#define EMAC_ISR          ( 0x1 <<  6) // (EMAC) Increment statistics registers.
#define EMAC_WES          ( 0x1 <<  7) // (EMAC) Write enable for statistics registers.
#define EMAC_BP           ( 0x1 <<  8) // (EMAC) Back pressure.
// -------- EMAC_CFG : (EMAC Offset: 0x4) Network Configuration Register --------
#define EMAC_SPD          ( 0x1 <<  0) // (EMAC) Speed.
#define EMAC_FD           ( 0x1 <<  1) // (EMAC) Full duplex.
#define EMAC_BR           ( 0x1 <<  2) // (EMAC) Bit rate.
#define EMAC_CAF          ( 0x1 <<  4) // (EMAC) Copy all frames.
#define EMAC_NBC          ( 0x1 <<  5) // (EMAC) No broadcast.
#define EMAC_MTI          ( 0x1 <<  6) // (EMAC) Multicast hash enable
#define EMAC_UNI          ( 0x1 <<  7) // (EMAC) Unicast hash enable.
#define EMAC_RLF          ( 0x1 <<  8) // (EMAC) Receive Long Frame.
#define EMAC_EAE          ( 0x1 <<  9) // (EMAC) External address match enable.
#define EMAC_CLK          ( 0x3 << 10) // (EMAC)
#define EMAC_CLK_HCLK_8   ( 0x0 << 10) // (EMAC) HCLK divided by 8
#define EMAC_CLK_HCLK_16  ( 0x1 << 10) // (EMAC) HCLK divided by 16
#define EMAC_CLK_HCLK_32  ( 0x2 << 10) // (EMAC) HCLK divided by 32
#define EMAC_CLK_HCLK_64  ( 0x3 << 10) // (EMAC) HCLK divided by 64
#define EMAC_RT           ( 0x1 << 12) // (EMAC) Retry test
#define EMAC_CAMMEG       ( 0x1 << 13) // (EMAC)
// -------- EMAC_SR : (EMAC Offset: 0x8) Network Status Register --------
#define EMAC_MDIO         ( 0x1 <<  1) // (EMAC)
#define EMAC_IDLE         ( 0x1 <<  2) // (EMAC)
// -------- EMAC_TCR : (EMAC Offset: 0x10) Transmit Control Register --------
#define EMAC_LEN          ( 0x7FF <<  0) // (EMAC)
#define EMAC_NCRC         ( 0x1 << 15) // (EMAC)
// -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Control Register --------
#define EMAC_OVR          ( 0x1 <<  0) // (EMAC)
#define EMAC_COL          ( 0x1 <<  1) // (EMAC)
#define EMAC_RLE          ( 0x1 <<  2) // (EMAC)
//#define EMAC_TXIDLE     ( 0x1 <<  3) // (EMAC)
#define EMAC_IDLETSR      ( 0x1 <<  3) // (EMAC)
#define EMAC_BNQ          ( 0x1 <<  4) // (EMAC)
#define EMAC_COMP         ( 0x1 <<  5) // (EMAC)
#define EMAC_UND          ( 0x1 <<  6) // (EMAC)
// -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register --------
#define EMAC_DNA          ( 0x1 <<  0) // (EMAC)
#define EMAC_REC          ( 0x1 <<  1) // (EMAC)
#define EMAC_RSROVR       ( 0x1 <<  2) // (EMAC)
#define EMAC_BNA          ( 0x1 <<  3) // (EMAC)
// -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register --------
#define EMAC_INT_DONE     ( 0x1 <<  0) // (EMAC)
#define EMAC_INT_RCOM     ( 0x1 <<  1) // (EMAC)
#define EMAC_INT_RBNA     ( 0x1 <<  2) // (EMAC)
#define EMAC_INT_TOVR     ( 0x1 <<  3) // (EMAC)
#define EMAC_INT_TUND     ( 0x1 <<  4) // (EMAC)
#define EMAC_INT_RTRY     ( 0x1 <<  5) // (EMAC)
#define EMAC_INT_TBRE     ( 0x1 <<  6) // (EMAC)
#define EMAC_INT_TCOM     ( 0x1 <<  7) // (EMAC)
#define EMAC_INT_TIDLE    ( 0x1 <<  8) // (EMAC)
#define EMAC_INT_LINK     ( 0x1 <<  9) // (EMAC)
#define EMAC_INT_ROVR     ( 0x1 << 10) // (EMAC)
#define EMAC_INT_HRESP    ( 0x1 << 11) // (EMAC)
// -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register --------
// -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register --------
// -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register --------
// -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register --------
#define EMAC_DATA         ( 0xFFFF <<  0) // (EMAC)
#define EMAC_CODE         ( 0x3 << 16) // (EMAC)
#define EMAC_CODE_802_3   ( 0x2 << 16) // (EMAC) Write Operation
#define EMAC_REGA         ( 0x1F << 18) // (EMAC)
#define EMAC_PHYA         ( 0x1F << 23) // (EMAC)
#define EMAC_RW           ( 0x3 << 28) // (EMAC)
#define EMAC_RW_R         ( 0x2 << 28) // (EMAC) Read Operation
#define EMAC_RW_W         ( 0x1 << 28) // (EMAC) Write Operation
#define EMAC_HIGH         ( 0x1 << 30) // (EMAC)
#define EMAC_LOW          ( 0x1 << 31) // (EMAC)
// -------- EMAC_RBRP: (EMAC Offset: 0x38) Receive Buffer First full pointer--------
#define EMAC_WRAP_R       ( 0x1 << 14) // Wrap bit
// -------- EMAC_RBWP: (EMAC Offset: 0x3C) Receive Buffer Current pointer--------
#define EMAC_WRAP_W       ( 0x1 << 14) // Wrap bit
// ........................................................................ //
//URANUS PHY //
#define MII_URANUS_ID                   0x01111//Test value
//URANUS specific registers //
#define MII_USCR_REG	                16
#define MII_USCSR_REG                   17
#define MII_USINTR_REG                  21
/* ........................................................................ */
#define EMAC_DESC_DONE                  0x00000001  /* bit for if DMA is done */
#define EMAC_DESC_WRAP                  0x00000002  /* bit for wrap */
#define EMAC_BROADCAST                  0x80000000  /* broadcast address */
#define EMAC_MULTICAST                  0x40000000  /* multicast address */
#define EMAC_UNICAST                    0x20000000  /* unicast address */

void MHal_EMAC_WritReg32( u32 xoffset, u32 xval );
u32 MHal_EMAC_ReadReg32( u32 xoffset );
s32 MHal_EMAC_NegotiationPHY(void);
s32 MHal_EMAC_CableConnection(void);
u32 MHal_EMAC_get_SA1H_addr(void);
u32 MHal_EMAC_get_SA1L_addr(void);
u32 MHal_EMAC_get_SA2H_addr(void);
u32 MHal_EMAC_get_SA2L_addr(void);
u32 MHal_EMAC_Read_CTL(void);
u32 MHal_EMAC_Read_CFG(void);
u32 MHal_EMAC_Read_RBQP(void);
u32 MHal_EMAC_Read_ISR(void);
u32 MHal_EMAC_Read_IDR(void);
u32 MHal_EMAC_Read_IER(void);
u32 MHal_EMAC_Read_IMR(void);
u32 MHal_EMAC_Read_RDPTR(void);
u32 MHal_EMAC_Read_BUFF(void);
u32 MHal_EMAC_Read_FRA(void);
u32 MHal_EMAC_Read_SCOL(void);
u32 MHal_EMAC_Read_MCOL(void);
u32 MHal_EMAC_Read_OK(void);
u32 MHal_EMAC_Read_SEQE(void);
u32 MHal_EMAC_Read_ALE(void);
u32 MHal_EMAC_Read_LCOL(void);
u32 MHal_EMAC_Read_ECOL(void);
u32 MHal_EMAC_Read_TUE(void);
u32 MHal_EMAC_Read_TSR(void);
u32 MHal_EMAC_Read_RSR(void);
u32 MHal_EMAC_Read_CSE(void);
u32 MHal_EMAC_Read_RE(void);
u32 MHal_EMAC_Read_ROVR(void);
u32 MHal_EMAC_Read_MAN(void);
u32 MHal_EMAC_Read_SE(void);
u32 MHal_EMAC_Read_ELR(void);
u32 MHal_EMAC_Read_RJB(void);
u32 MHal_EMAC_Read_USF(void);
u32 MHal_EMAC_Read_SQEE(void);
u32 MHal_EMAC_Read_JULIAN_0100(void);
u32 MHal_EMAC_Read_JULIAN_0104(void);
u32 MHal_EMAC_Read_JULIAN_0108(void);

void MHal_EMAC_update_HSH(u8 mc0, u8 mc1);
void MHal_EMAC_Write_CTL(u32 xval);
void MHal_EMAC_Write_CFG(u32 xval);
void MHal_EMAC_Write_RBQP(u32 u32des);
void MHal_EMAC_Write_BUFF(u32 xval);
void MHal_EMAC_Write_MAN(u32 xval);
void MHal_EMAC_Write_TAR(u32 xval);
void MHal_EMAC_Write_TCR(u32 xval);
void MHal_EMAC_Write_RDPTR(u32 xval);
void MHal_EMAC_Write_WRPTR(u32 xval);
void MHal_EMAC_Write_IER(u32 xval);
void MHal_EMAC_Write_IDR(u32 xval);
void MHal_EMAC_Write_IMR(u32 xval);
void MHal_EMAC_Write_SA1H(u32 xval);
void MHal_EMAC_Write_SA1L(u32 xval);
void MHal_EMAC_Write_SA2H(u32 xval);
void MHal_EMAC_Write_SA2L(u32 xval);
void MHal_EMAC_Write_JULIAN_0100(u32 xval);
void MHal_EMAC_Write_JULIAN_0104(u32 xval);
void MHal_EMAC_Write_JULIAN_0108(u32 xval);
void MHal_EMAC_Power_On_Clk(void);
void MHal_EMAC_Power_Off_Clk(void);
void MHal_EMAC_timer_callback(unsigned long value);
void MHal_EMAC_WritRam32(u32 uRamAddr, u32 xoffset,u32 xval);
void MHal_EMAC_enable_mdi(void);
void MHal_EMAC_disable_mdi(void);
void MHal_EMAC_write_phy (unsigned char phy_addr, unsigned char address, u32 value);
void MHal_EMAC_read_phy(unsigned char phy_addr, unsigned char address,u32 *value);
void MHal_EMAC_enable_phyirq (void);
void MHal_EMAC_disable_phyirq (void);
void MHal_EMAC_update_speed_duplex(u32 uspeed, u32 uduplex);
void MHal_EMAC_Write_SA1_MAC_Address(u8 m0,u8 m1,u8 m2,u8 m3,u8 m4,u8 m5);
void MHal_EMAC_Write_SA2_MAC_Address(u8 m0,u8 m1,u8 m2,u8 m3,u8 m4,u8 m5);
void MHal_EMAC_Write_SA3_MAC_Address(u8 m0,u8 m1,u8 m2,u8 m3,u8 m4,u8 m5);
void MHal_EMAC_Write_SA4_MAC_Address(u8 m0,u8 m1,u8 m2,u8 m3,u8 m4,u8 m5);
void MHal_EMAC_WritCAM_Address(u32 addr,u8 m0,u8 m1,u8 m2,u8 m3,u8 m4,u8 m5);
void MHal_EMAC_ReadCAM_Address(u32 addr,u32 *w0,u32 *w1);
void MHal_EMAC_WriteProtect(u8 bEnable, u32 u32AddrUB, u32 u32AddrLB);
void MHal_EMAC_CheckTSR(void);
void MHal_EMAC_Ewavetest_100M(void);
#if (SUPPORT_ALBANY)
void MHal_EMAC_Albany_I2C(u8 enable);
#endif
#endif
// -----------------------------------------------------------------------------
// Linux EMAC.c End
// -----------------------------------------------------------------------------


