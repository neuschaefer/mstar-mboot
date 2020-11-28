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

//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------#include "e1000.h"

/* e1000_hw.h
 * Structures, enums, and macros for the MAC
 */

#ifndef _EMAC_HW_H_
#define _EMAC_HW_H_

#include <common.h>
#include <malloc.h>
#include <linux/mtd/compat.h>
#include <net.h>
#include <asm/io.h>

#include <pci.h>
#include "mhal_emac.h"

//--------------------------------------------------------------------------------------------------
//  Constant definition
//--------------------------------------------------------------------------------------------------
#define __GFP_WAIT  0x10    /* Can wait and reschedule? */
#define __GFP_IO    0x40    /* Can start physical IO? */
#define __GFP_FS    0x80    /* Can call down to low-level FS? */

#define GFP_KERNEL	(__GFP_WAIT | __GFP_IO | __GFP_FS)

#define SOFTWARE_DESCRIPTOR_ENABLE          0x0001
#define CHECKSUM_ENABLE                     0x0FE
#define CONFIG_EMAC_MOA                     1      // System Type
#define EMAC_SPEED_100                      100
#define EMAC_MEM_GAP                        (0x400)
//2MB size
#define EMAC_ABSO_MEM_SIZE                  0x200000
#define EMAC_MAX_TX_QUEUE                   30

#define RBQP_LENG                           (0x80)
#ifdef SOFTWARE_DESCRIPTOR
#define RX_BUFFER_SEL                       0x0001          // 0x0=2KB,0x1=4KB,0x2=8KB,0x3=16KB, 0x09=1MB
#define RX_BUFFER_SIZE                      (RBQP_LENG*0x600)  //0x10000//0x20000//
#else
#define RX_BUFFER_SEL						0x0003		// 0x0=2KB,0x1=4KB,0x2=8KB,0x3=16KB, 0x09=1MB
#define RX_BUFFER_SIZE                      0x4000		//0x10000//0x20000//
#endif
//Descriptor part
#define RBQP_SIZE                           (0x0008*RBQP_LENG)      // ==8bytes*?==?descriptors
#define MAX_RX_DESCR                        RBQP_LENG       //32   /* max number of receive buffers */

#define netif_stop_queue(x)
#define ROUND_SUP_4(x) (((x)+3)&~3)
extern u8 MY_MAC[6];
u8 ustart = 0;
/* NIC specific static variables go here */
static u32 packet_data[524];
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

struct rbf_t
{
  unsigned int  addr;
  unsigned long size;
};

struct recv_desc_bufs
{
  char recv_buf[RX_BUFFER_SIZE];              /* must be on MAX_RBUFF_SZ boundary */
  struct rbf_t descriptors[MAX_RX_DESCR];     /* must be on sizeof (rbf_t) boundary */
};

#if 0
typedef enum {
    FALSE = 0,
    TRUE = 1
} boolean_t;
#endif
/* Structure containing variables used by the shared code (e1000_hw.c) */
struct emac_hw {
    pci_dev_t pdev;
    u8 *hw_addr;
    u8 revision_id;
    u32 phy_id;
    u32 phy_addr;
    u32 original_fc;
    u32 txcw;
    u32 autoneg_failed;
    u16 autoneg_advertised;
    u16 pci_cmd_word;
    u16 fc_high_water;
    u16 fc_low_water;
    u16 fc_pause_time;
    u16 device_id;
    u16 vendor_id;
    u16 subsystem_id;
    u16 subsystem_vendor_id;

    u8  get_link_status;
    u8  tbi_compatibility_en;
    u8  tbi_compatibility_on;
    u8  fc_send_xon;
    u8  report_tx_early;

    int rxBuffIndex;                    /* index into receive descriptor list */
    struct recv_desc_bufs *dlist;       /* descriptor list address */
    struct recv_desc_bufs *dlist_phys;  /* descriptor list physical address */
};

struct _BasicConfigEMAC
{
    u8                  connected;          // 0:No, 1:Yes    <== (20070515) Wait for Julian's reply
    u8                  speed;              // 10:10Mbps, 100:100Mbps
	// ETH_CTL Register:
    u8                  wes;                // 0:Disable, 1:Enable (WR_ENABLE_STATISTICS_REGS)
	// ETH_CFG Register:
    u8					duplex;             // 1:Half-duplex, 2:Full-duplex
    u8					cam;                // 0:No CAM, 1:Yes
    u8 					rcv_bcast;          // 0:No, 1:Yes
    u8                  rlf;                // 0:No, 1:Yes receive long frame(1522)
    // MAC Address:
    u8                  sa1[6];             // Specific Addr 1 (MAC Address)
    u8                  sa2[6];             // Specific Addr 2
    u8                  sa3[6];             // Specific Addr 3
    u8                  sa4[6];             // Specific Addr 4
    u8                  loopback;
};
typedef struct _BasicConfigEMAC BasicConfigEMAC;

struct _UtilityVarsEMAC
{
    u32                 cntChkINTCounter;
    u32 				readIdxRBQP;        // Reset = 0x00000000
    u32 				rxOneFrameAddr;     // Reset = 0x00000000 (Store the Addr of "ReadONE_RX_Frame")
    // Statistics Counters : (accumulated)
    u32                 cntREG_ETH_FRA;
    u32                 cntREG_ETH_SCOL;
    u32                 cntREG_ETH_MCOL;
    u32                 cntREG_ETH_OK;
    u32                 cntREG_ETH_SEQE;
    u32                 cntREG_ETH_ALE;
    u32                 cntREG_ETH_DTE;
    u32                 cntREG_ETH_LCOL;
    u32                 cntREG_ETH_ECOL;
    u32                 cntREG_ETH_TUE;
    u32                 cntREG_ETH_CSE;
    u32                 cntREG_ETH_RE;
    u32                 cntREG_ETH_ROVR;
    u32                 cntREG_ETH_SE;
    u32                 cntREG_ETH_ELR;
    u32                 cntREG_ETH_RJB;
    u32                 cntREG_ETH_USF;
    u32                 cntREG_ETH_SQEE;
    // Interrupt Counter :
    u32                 cntHRESP;
    u32                 cntROVR;
    u32                 cntLINK;
    u32                 cntTIDLE;
    u32                 cntTCOM;
    u32                 cntTBRE;
    u32                 cntRTRY;
    u32                 cntTUND;
    u32                 cntTOVR;
    u32                 cntRBNA;
    u32                 cntRCOM;
    u32                 cntDONE;
    // Flags:
    u8                  flagMacTxPermit;    // 0:No,1:Permitted.  Initialize as "permitted"
    u8                  flagISR_INT_RCOM;
    u8                  flagISR_INT_RBNA;
    u8                  flagISR_INT_DONE;
    u8                  flagPowerOn;        // 0:Poweroff, 1:Poweron
    u8                  initedEMAC;         // 0:Not initialized, 1:Initialized.
    u8                  flagRBNA;
    // Misc Counter:
    u32                 cntRxFrames;        // Reset = 0x00000000 (Counter of RX frames,no matter it's me or not)
    u32                 cntReadONE_RX;      // Counter for ReadONE_RX_Frame
    u32                 cntCase20070806;
    u32                 cntChkToTransmit;
    // Misc Variables:
    u32                 mainThreadTasks;    // (20071029_CHARLES) b0=Poweroff,b1=Poweron
};
typedef struct _UtilityVarsEMAC UtilityVarsEMAC;

BasicConfigEMAC ThisBCE;
UtilityVarsEMAC ThisUVE;

typedef volatile unsigned int EMAC_REG;

#endif				/* _EMAC_HW_H_ */

