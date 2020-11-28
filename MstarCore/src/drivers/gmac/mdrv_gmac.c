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

#include "mdrv_gmac.h"

u8 MY_MAC[6] = { 0x00, 0x30, 0x1B, 0xBA, 0x02, 0xDB };
#ifdef CONFIG_ETHERNET_ALBANY
unsigned char phy_id=0;
#else
unsigned char phy_id=1;
#endif

#define EMAC_DBG_TFTP_TX    (0)
#define EMAC_DBG_TFTP_RX    (0)
#define EMAC_DBG_MSG(x)     //x
#define RTK_OUI_MSB         (0x1C)
#if 1
s32 rxpre_seq = 0, txpre_seq = 0;
#endif

//For BIST
#define PHY_LOOPBACK    (1)
#define MAC_LOOPBACK    (2)

//--------------------------------------------------------------------------------------------------
//  Global variable
//--------------------------------------------------------------------------------------------------
u32 EMAC_MEM_BASE = 0, RAM_ADDR_BASE = 0, RX_BUFFER_BASE=0, RBQP_BASE=0, TX_BUFFER_BASE=0;
u8 *packet = (u8 *)packet_data;
struct eth_device nic_device;

static int MDrv_EMAC_tx(struct eth_device *nic, volatile void *tx_packet, int length);
void MDrv_EMAC_DumpMem(u32 addr, u32 len);
#if (SUPPORT_ALBANY)
u32 albany_read_reg(u32 reg);
void albany_write_reg(u32 reg, u32 val);
#endif

//-------------------------------------------------------------------------------------------------
//Initialize and start the Receiver and Transmit subsystems
//-------------------------------------------------------------------------------------------------
static void MDrv_EMAC_start (const struct eth_device *nic)
{
    struct emac_hw *hw = (struct emac_hw *) nic->priv;
    u32 uRegVal;
#ifdef SOFTWARE_DESCRIPTOR
    u32 i;
#endif

    // Initialize Receive Buffer Descriptors
    memset((u8*)(RBQP_BASE+RAM_ADDR_BASE),0x00,RBQP_SIZE);
#ifdef SOFTWARE_DESCRIPTOR
    for(i=0; i<RBQP_LENG;i++)
    {
        if(i<(RBQP_LENG-1))
            MHal_EMAC_WritRam32((RBQP_BASE+RAM_ADDR_BASE), i*16, (RX_BUFFER_BASE+0x600*i));
        else
            MHal_EMAC_WritRam32((RBQP_BASE+RAM_ADDR_BASE), i*16, (RX_BUFFER_BASE+0x600*i+EMAC_DESC_WRAP));
    }
#else
    MHal_EMAC_WritRam32((RBQP_BASE+RAM_ADDR_BASE),(RBQP_SIZE-0x08),0x00000002);
#endif

    Chip_Flush_Memory();

    // set offset of read and write pointers in the receive circular buffer //
    uRegVal = MHal_EMAC_Read_BUFF();
    uRegVal = (RX_BUFFER_BASE|RX_BUFFER_SEL);
    MHal_EMAC_Write_BUFF(uRegVal);
    MHal_EMAC_Write_RDPTR(0);
    MHal_EMAC_Write_WRPTR(0);

    // Program address of descriptor list in Rx Buffer Queue register //
    MHal_EMAC_Write_RBQP(RBQP_BASE);
    //Reset buffer index//
    hw->rxBuffIndex = 0;

    // Enable Receive and Transmit //
    uRegVal = MHal_EMAC_Read_CTL();
    uRegVal |= (EMAC_RE | EMAC_TE);
    MHal_EMAC_Write_CTL(uRegVal);
}

//-------------------------------------------------------------------------------------------------
// Open the ethernet interface
//-------------------------------------------------------------------------------------------------
static int MDrv_EMAC_open (struct eth_device *nic, bd_t * bis)
{
    // struct emac_hw *hw = (struct emac_hw *) nic->priv;
    u32 uRegVal;

    //ato  EMAC_SYS->PMC_PCER = 1 << EMAC_ID_EMAC;   //Re-enable Peripheral clock //
    uRegVal = MHal_EMAC_Read_CTL();
    uRegVal |= EMAC_CSR;
    MHal_EMAC_Write_CTL(uRegVal);
    // Enable PHY interrupt //
    MHal_EMAC_enable_phyirq ();

    // Enable MAC interrupts //
    uRegVal = EMAC_INT_RCOM |EMAC_INT_RBNA
    | EMAC_INT_TUND | EMAC_INT_RTRY | EMAC_INT_TCOM
    | EMAC_INT_ROVR | EMAC_INT_HRESP;
    MHal_EMAC_Write_IER(uRegVal);

    MDrv_EMAC_start (nic);
    return 0;
}

/**************************************************************************
POLL - Wait for a frame
***************************************************************************/
static int MDrv_EMAC_rx(struct eth_device *nic)
{
    struct emac_hw *hw = (struct emac_hw *) nic->priv;
    struct recv_desc_bufs *dlist;
    unsigned char *p_recv;

    u32 pktlen;
    u32 uRegVal=0;
    u32 wrap_bit;
#if (EMAC_DBG_TFTP_RX)
    u8 type = 0;
    u16 block = 0;
#endif
    dlist = hw->dlist ;
    // If any Ownership bit is 1, frame received.

    Chip_Flush_Memory();

    while ( (dlist->descriptors[hw->rxBuffIndex].addr )& EMAC_DESC_DONE)
    {
        p_recv = (unsigned char *) ((((dlist->descriptors[hw->rxBuffIndex].addr)&0x1FFFFFFF) + RAM_ADDR_BASE) &~(EMAC_DESC_DONE | EMAC_DESC_WRAP));
        pktlen = (u32)(((dlist->descriptors[hw->rxBuffIndex].high_tag & 0x7) << 11) | (dlist->descriptors[hw->rxBuffIndex].low_tag & 0x7ff));    /* Length of frame including FCS */

        Chip_Flush_Memory();

        if ((unsigned char *) (dlist->recv_buf + RX_BUFFER_SIZE) >
        (p_recv + ROUND_SUP_4 (pktlen)))
        {
            // the frame is not splitted in two parts //
            memcpy(packet, p_recv, pktlen);
            // update consumer pointer//
            uRegVal = MHal_EMAC_Read_RDPTR();
            uRegVal += ROUND_SUP_4(pktlen);
            MHal_EMAC_Write_RDPTR(uRegVal);
        }
        else
        {
            //the frame is splitted in two parts //
            int firstPacketPartSize =
            (unsigned char *) dlist->recv_buf + RX_BUFFER_SIZE - p_recv;
            int secondPacketSize =(ROUND_SUP_4(pktlen) - firstPacketPartSize);
            memcpy((unsigned char *)packet, p_recv, firstPacketPartSize);
            memcpy((unsigned char *)(packet+firstPacketPartSize), (unsigned char *) dlist->recv_buf, secondPacketSize);

            // update consumer pointer and toggle the wrap bit //
            wrap_bit = (MHal_EMAC_Read_RDPTR() & EMAC_WRAP_R) ^ EMAC_WRAP_R;
            MHal_EMAC_Write_RDPTR(secondPacketSize | wrap_bit);
        }

#if (EMAC_DBG_TFTP_RX)
        block = *(p_recv+0x2d) | (*(p_recv+0x2c) << 8);
        type = *(p_recv+0x2b);
        if (3 == type && block >0)
        {
            if (block == rxpre_seq)
            {
                EMAC_DBG_MSG(printf("xxxxxx Rx tftp Packet:%lx Type:%u block:%u again!!!\n", p_recv, type, block));
            }
            else
                rxpre_seq++;
        }
        else if (4 == type)
        {
            EMAC_DBG_MSG(printf("Rx tftp ACK Packet:%lx Type:%u block:%u\n", p_recv, type, block));
        }
        else if (6 == type)
        {
            EMAC_DBG_MSG(printf("\nRx tftp Opt ACK Packet:%lx Type:%u\n", p_recv, type));
            EMAC_DBG_MSG(printf("Ready to tftp transaction!!!!!!!\n"));
        }
        else if (block != (rxpre_seq+1) && rxpre_seq > 0)
        {
            EMAC_DBG_MSG(printf("\nError tftp packet block:%u rsr:%x tsr:%x\n", (rxpre_seq+1), MHal_EMAC_Read_RSR(), MHal_EMAC_Read_TSR()));
            EMAC_DBG_MSG(printf("\ndescriptor:%lx size:%lx\n", &(dlist->descriptors[hw->rxBuffIndex]), pktlen));
            //MDrv_EMAC_DumpMem(p_recv, 0x40);
            //MDev_EMAC_stats();
        }

        //MDrv_EMAC_DumpMem(p_recv, pktlen);
#endif

        Chip_Flush_Memory();

        if (ThisBCE.loopback == PHY_LOOPBACK)
        {
            printf("Rx Data");
            MDrv_EMAC_DumpMem((u32)packet, 0x40);
        }
        else if (ThisBCE.loopback == MAC_LOOPBACK)
        {
            MDrv_EMAC_tx(nic, (void *)packet, pktlen);
        }
        else
            NetReceive((uchar *)packet, pktlen);

        dlist->descriptors[hw->rxBuffIndex].addr  &= ~EMAC_DESC_DONE;  /* reset ownership bit */
        Chip_Flush_Memory();

        //wrap after last buffer //
        hw->rxBuffIndex++;
        if (hw->rxBuffIndex == MAX_RX_DESCR)
        {
            hw->rxBuffIndex = 0;
        }
    }
#if defined(CONFIG_KRONUS)
    Chip_Read_Memory();
#endif

    return 1;
}

/**************************************************************************
TRANSMIT - Transmit a frame
***************************************************************************/

static char t_packet[2096+32];

static int MDrv_EMAC_tx(struct eth_device *nic, volatile void *tx_packet, int length)
{
#if (EMAC_DBG_TFTP_TX)
    //u8 *ptr = (u8 *)tx_packet, type;
    u16 block = 0;
    u16 type = 0;
#endif
    u8 *ptr ;
    u32 tx_base;
    //Patch h/w bug TX DRAM Must O256bit alignment
    tx_base = ALIGN(((u32)t_packet & 0x1FFFFFFF) | BUS_MIU0_BASE_NONCACHE,32);
    
    //shift 0x40 to patch Kaiser HW bug
    ptr = (u8 *)(tx_base + 0x40);

    while (length < 60)         //padding to 60 bytes
    {
        *((u8*)tx_packet+length)=0;
        length++;
    }

#if (EMAC_DBG_TFTP_TX)
    type = *(ptr+0x2b);
    block = *(ptr+0x2d) | (*(ptr+0x2c) << 8);
    if (1 == type)
     {
        EMAC_DBG_MSG(printf("\nTx tftp Request Type:%u\n", ptr, type));
     }
    else if (3 == type)
    {
        EMAC_DBG_MSG(printf("Tx tftp Packet:%lx Type:%u block:%u\n", ptr, type, block));
    }
    else if (4 == type && block >0)
    {
        if (block == txpre_seq)
            EMAC_DBG_MSG(printf("xxxxxxx Tx tftp ACK Packet:%lx Type:%u block:%u again!!!!\n", ptr, type, block));
        else
            block++;
    }
#endif

    MHal_EMAC_CheckTSR();

#if defined(CONFIG_JANUS) || defined(CONFIG_MARIA10)
    memcpy((void *)t_packet, (void *)tx_packet, length);
    MHal_EMAC_Write_TAR((u32)t_packet);
#else
    memcpy((void *)ptr, (void *)tx_packet, length);
    Chip_Flush_Memory();
    MHal_EMAC_Write_TAR((u32)ptr & 0x1FFFFFFF);
#endif

    if (ThisBCE.loopback == PHY_LOOPBACK)
    {
        printf("Tx Data");
        MDrv_EMAC_DumpMem((u32)tx_packet, 0x40);
    }
    // Set length of the packet in the Transmit Control register //
    MHal_EMAC_Write_TCR(length);

    return 1;
}

//-------------------------------------------------------------------------------------------------
// Close the interface
//-------------------------------------------------------------------------------------------------
void MDrv_EMAC_close(struct eth_device *nic)
{
    u32 uRegVal;
    //Disable Receiver and Transmitter //
    uRegVal = MHal_EMAC_Read_CTL();
    //uRegVal &= ~(EMAC_TE | EMAC_RE);
    MHal_EMAC_Write_CTL(uRegVal);
    // Disable PHY interrupt //
    MHal_EMAC_disable_phyirq ();

    //Disable MAC interrupts //
    uRegVal = EMAC_INT_RCOM | EMAC_INT_RBNA
    | EMAC_INT_TUND | EMAC_INT_RTRY | EMAC_INT_TCOM
    | EMAC_INT_ROVR | EMAC_INT_HRESP;
    MHal_EMAC_Write_IDR(uRegVal);
    netif_stop_queue (nic);
}

void MDev_EMAC_stats(void)
{
    printf("Rx Ok:%u\n", MHal_EMAC_Read_OK());       /* Good frames received */
    printf("ALE:%u\n", MHal_EMAC_Read_ALE());
    printf("ELR:%u\n", MHal_EMAC_Read_ELR());        /* Excessive Length or Undersize Frame error */
    printf("SEQE:%u\n", MHal_EMAC_Read_SEQE());      /* Excessive Length or Undersize Frame error */
    printf("ROVR:%u\n", MHal_EMAC_Read_ROVR());      //rx fifo error
    printf("SE:%u\n", MHal_EMAC_Read_SE());
    printf("RJB:%u\n", MHal_EMAC_Read_RJB());

    printf("Tx Ok:%u\n", MHal_EMAC_Read_FRA());
    printf("TUE:%u\n", MHal_EMAC_Read_TUE());        /* Transmit FIFO underruns */
    printf("CSE:%u\n", MHal_EMAC_Read_CSE());      /* Carrier Sense errors */
    printf("SQEE:%u\n", MHal_EMAC_Read_SQEE());      /* Heartbeat error */
 }

void MDrv_EMAC_PhyAddrScan(void)
{
    u32 word_ETH_MAN  = 0x00000000;

#ifdef CONFIG_ETHERNET_ALBANY
    MHal_EMAC_Write_JULIAN_0100(0x0000F001);
#else
    MHal_EMAC_Write_JULIAN_0100(0x0000F007);
#endif

    ThisUVE.flagISR_INT_DONE = 0x00;
    MHal_EMAC_read_phy(phy_id, PHY_REG_STATUS, &word_ETH_MAN);
    if((0xffff != word_ETH_MAN)&&(0x0000 != word_ETH_MAN))
    {
        printf("phy [%d]=%x\n",phy_id, word_ETH_MAN);
        return;
    }

    for (phy_id = 1; phy_id < 32; phy_id++)
    {
        MHal_EMAC_read_phy(phy_id, PHY_REG_STATUS, &word_ETH_MAN);
        printf("phy [%d]=%x\n",phy_id, word_ETH_MAN);
        if((0xffff != word_ETH_MAN)&&(0x0000 != word_ETH_MAN))
        {
            return;
        }
    }
    printf("Can't get correct PHY Addr and reset to 0\n");
    phy_id = 0;
}

//-------------------------------------------------------------------------------------------------
// EMAC Hardware register set
//-------------------------------------------------------------------------------------------------
static int MDrv_EMAC_HW_init(const struct eth_device *nic)
{
    u32 word_ETH_CTL = 0x00000000;
    u32 word_ETH_CFG = 0x00000800;
    u32 uJulian104Value=0;
    s32 uNegPhyVal = 0;

    // (20071026_CHARLES) Disable TX, RX and MDIO:   (If RX still enabled, the RX buffer will be overwrited)
    MHal_EMAC_Write_CTL(word_ETH_CTL);
    // Init RX --------------------------------------------------------------
    memset((u8*)(RAM_ADDR_BASE + RX_BUFFER_BASE),0x00,RX_BUFFER_SIZE);

    MHal_EMAC_Write_BUFF(RX_BUFFER_BASE|RX_BUFFER_SEL);
    MHal_EMAC_Write_RDPTR(0x00000000);
    MHal_EMAC_Write_WRPTR(0x00000000);
    // Initialize "Receive Buffer Queue Pointer"
    MHal_EMAC_Write_RBQP(RBQP_BASE);

    // Enable Interrupts ----------------------------------------------------
    MHal_EMAC_Write_IER(0x0000FFFF);
    printf("MAC Address %02X:%02X:%02X:%02X:%02X:%02X\n",ThisBCE.sa1[0],ThisBCE.sa1[1],
    ThisBCE.sa1[2],ThisBCE.sa1[3],ThisBCE.sa1[4],ThisBCE.sa1[5]);
    // Set MAC address ------------------------------------------------------
    MHal_EMAC_Write_SA1_MAC_Address(ThisBCE.sa1[0],ThisBCE.sa1[1],ThisBCE.sa1[2],ThisBCE.sa1[3],ThisBCE.sa1[4],ThisBCE.sa1[5]);
    MHal_EMAC_Write_SA2_MAC_Address(ThisBCE.sa2[0],ThisBCE.sa2[1],ThisBCE.sa2[2],ThisBCE.sa2[3],ThisBCE.sa2[4],ThisBCE.sa2[5]);
    MHal_EMAC_Write_SA3_MAC_Address(ThisBCE.sa3[0],ThisBCE.sa3[1],ThisBCE.sa3[2],ThisBCE.sa3[3],ThisBCE.sa3[4],ThisBCE.sa3[5]);
    MHal_EMAC_Write_SA4_MAC_Address(ThisBCE.sa4[0],ThisBCE.sa4[1],ThisBCE.sa4[2],ThisBCE.sa4[3],ThisBCE.sa4[4],ThisBCE.sa4[5]);

#ifdef SOFTWARE_DESCRIPTOR
    #ifdef CHECKSUM
        uJulian104Value=uJulian104Value|(CHECKSUM_ENABLE|SOFTWARE_DESCRIPTOR_ENABLE);
    #else
        uJulian104Value=uJulian104Value|SOFTWARE_DESCRIPTOR_ENABLE;
    #endif
        MHal_EMAC_Write_JULIAN_0104(uJulian104Value);//Disable interrupt delay
#else
    #if defined(CONFIG_URANUS4) || defined(CONFIG_KRONUS)
        MHal_EMAC_Write_JULIAN_0100(0x0000F007);
        MHal_EMAC_Write_JULIAN_0104(0x00);
    #else
        uJulian104Value=0x00000000;
        MHal_EMAC_Write_JULIAN_0104(uJulian104Value);
    #endif
#endif //#ifdef SOFTWARE_DESCRIPTOR

    // IMPORTANT: Run NegotiationPHY() before writing REG_ETH_CFG.
    ThisBCE.duplex = DUPLEX_FULL;
    ThisBCE.speed = SPEED_10;
    uNegPhyVal = MHal_EMAC_NegotiationPHY();

    ThisUVE.flagMacTxPermit = 0x01;
    switch(uNegPhyVal)
    {
    case 1:
        ThisBCE.duplex = DUPLEX_HALF;
        ThisBCE.speed = SPEED_10;
        break;

    case 2:
        ThisBCE.duplex = DUPLEX_FULL;
        ThisBCE.speed = SPEED_10;
        word_ETH_CFG |= (EMAC_FD);
        break;

    case 3:
        ThisBCE.duplex = DUPLEX_HALF;
        ThisBCE.speed = SPEED_100;
        word_ETH_CFG |= (EMAC_SPD);
        break;

    case 4:
        ThisBCE.duplex = DUPLEX_FULL;
        ThisBCE.speed = SPEED_100;
        word_ETH_CFG |= (EMAC_SPD|EMAC_FD);
        break;
    
    case 5:
        ThisBCE.duplex = 1;
        ThisBCE.speed = SPEED_1000;
        word_ETH_CFG |= (EMAC_FD);
        break;

    default:
        printf("Status Error!\n");
        break;
    }

    printf("word_ETH_CFG %x", word_ETH_CFG);
    MHal_EMAC_Write_CFG(word_ETH_CFG);
    // ETH_CTL Register -----------------------------------------------------
    word_ETH_CTL = 0x0000010;  // Enable MDIO
    if(ThisBCE.wes == 1) word_ETH_CTL |= 0x00000080;
    MHal_EMAC_Write_CTL(word_ETH_CTL);

#ifdef SOFTWARE_DESCRIPTOR
#if (SUPPORT_ALBANY)
    MHal_EMAC_Write_JULIAN_0100(0x0000F001);    //MII
#else
    MHal_EMAC_Write_JULIAN_0100(0x0000F007);    //RMII
#endif
#else
    MHal_EMAC_Write_JULIAN_0100(0x00000107);
#endif

#ifdef CONFIG_ETHERNET_ALBANY
    MHal_EMAC_Write_JULIAN_0100(0x0000F001);
#endif

    ThisUVE.flagPowerOn = 1;
    ThisUVE.initedEMAC  = 1;

    return 1;
}

//-------------------------------------------------------------------------------------------------
// EMAC init Variable
//-------------------------------------------------------------------------------------------------
static volatile u8 emac_var[EMAC_ABSO_MEM_SIZE];
u32 MDrv_EMAC_VarInit(void)
{
    u32 alloRAM_ADDR_BASE;
    int i;
    char *s, *e;

    alloRAM_ADDR_BASE = ((u32)emac_var & 0x1fffffff) | BUS_MIU0_BASE_NONCACHE; //transfer to non-cachable
    memset((u32 *)alloRAM_ADDR_BASE,0x00,EMAC_ABSO_MEM_SIZE);
    Chip_Flush_Memory();
    EMAC_MEM_BASE = (alloRAM_ADDR_BASE + 0x3FFF) & ~0x3FFF;   // IMPORTANT: Let lowest 14 bits as zero.
    RAM_ADDR_BASE = BUS_MIU0_BASE_NONCACHE;
    printf("EMAC Mem Base:%x\n", EMAC_MEM_BASE);

    RX_BUFFER_BASE   = EMAC_MEM_BASE - RAM_ADDR_BASE;
    RBQP_BASE        = RX_BUFFER_BASE + RX_BUFFER_SIZE;
    if ((RBQP_BASE + RBQP_SIZE+ EMAC_MEM_GAP) > (alloRAM_ADDR_BASE + EMAC_ABSO_MEM_SIZE))
    {
        printf("MMAP overflow: %x > %x\n", (RBQP_BASE + RBQP_SIZE+ EMAC_MEM_GAP), (alloRAM_ADDR_BASE + EMAC_ABSO_MEM_SIZE));
        return 0;
    }

    printf("Rx buff:%x\nRBQP:%x\n", RX_BUFFER_BASE, RBQP_BASE);
    memset(&ThisBCE,0x00,sizeof(BasicConfigEMAC));
    memset(&ThisUVE,0x00,sizeof(UtilityVarsEMAC));

    ThisBCE.wes         = 0;					// 0:Disable, 1:Enable (WR_ENABLE_STATISTICS_REGS)
    ThisBCE.duplex      = 2;					// 1:Half-duplex, 2:Full-duplex
    ThisBCE.cam         = 0;                 // 0:No CAM, 1:Yes
    ThisBCE.rcv_bcast   = 0;      			// 0:No, 1:Yes
    ThisBCE.rlf         = 0;                 // 0:No, 1:Yes receive long frame(1522)
    ThisBCE.rcv_bcast   = 1;
    ThisBCE.speed       = EMAC_SPEED_100;

    s = getenv ("ethaddr");
    if (s)
    {
        for (i = 0; i < 6; ++i)
        {
            ThisBCE.sa1[i] = s ? simple_strtoul (s, &e, 16) : 0;
            if (s)
            {
                s = (*e) ? e + 1 : e;
            }
        }
    }
    else
    {
        ThisBCE.sa1[0]      = MY_MAC[0];
        ThisBCE.sa1[1]      = MY_MAC[1];
        ThisBCE.sa1[2]      = MY_MAC[2];
        ThisBCE.sa1[3]      = MY_MAC[3];
        ThisBCE.sa1[4]      = MY_MAC[4];
        ThisBCE.sa1[5]      = MY_MAC[5];
    }

    ThisBCE.loopback = 0;
    //if (!((u32)packet_data% 4))
    //    packet +=2;
    printf("Packet buffer:%lx\n", (long unsigned int)packet);

    return alloRAM_ADDR_BASE;
}

/**************************************************************************
PROBE - Look for an adapter, this routine's visible to the outside
You should omit the last argument struct pci_device * for a non-PCI NIC
***************************************************************************/
struct emac_hw hw_device;
int emac_init=0;

void MDrv_EMAC_DumpMem(u32 addr, u32 len)
{
    u8 *ptr = (u8 *)addr;
    u32 i;

    printf("\n ===== Dump %lx =====\n", (long unsigned int)ptr);
    for (i=0; i<len; i++)
    {
        if ((u32)i%0x10 ==0)
            printf("%lx: ", (long unsigned int)ptr);
        if (*ptr < 0x10)
            printf("0%x ", *ptr);
        else
            printf("%x ", *ptr);
        if ((u32)i%0x10 == 0x0f)
            printf("\n");
	ptr++;
    }
    printf("\n");
}

void MDrv_EMAC_DumpReg(void)
{
    u32 idx, val = 0;

    printf("======= PHY Reg =======\n");
    for (idx = 0; idx < 0x20; idx++)
    {
        MHal_EMAC_read_phy(phy_id, idx, &val);
        printf("  Reg-%-3X=%-4x   ",idx, val);
        if (idx%5 == 4)
            printf("\n");
    }

    printf("\n======= EMAC Reg =======\n");
    for (idx = 0; idx < 0x120; idx+=4)
    {
        printf("  Reg-%-3X=%-8x   ",idx, MHal_EMAC_ReadReg32(idx));
        if (idx%0x10 == 0x0c)
            printf("\n");
    }
}

u8 MDrv_EMAC_Bist(u8 mode)
{
    u16 timeout = 0;
    u32 status = 0;
    volatile u8 endless_loop = 1;

    ThisBCE.loopback = mode;
    switch(mode)
    {
    case PHY_LOOPBACK:
        MHal_EMAC_write_phy(phy_id, PHY_REG_BASIC, 0x6100);
        do
        {
            MHal_EMAC_read_phy(phy_id, PHY_REG_STATUS, &status);
            timeout++;
        } while((!(status & 0x0004)) && (timeout < 25000));
        if (timeout == 50000)
        {
            printf("Open PHY loopback mode timeout!!\n");
            MHal_EMAC_NegotiationPHY();
            return FALSE;
        }
        else
            printf("Open PHY loopback mode!\n");
        break;

    case MAC_LOOPBACK:
        MDrv_EMAC_open(&nic_device, NULL);
        printf("Long loopback test\n");
        // It's really an infinite loop
        // But it's done this way to "cheat" Dropzone/Parasoft, forbidding infinite loops
        do
        {
           MDrv_EMAC_rx(&nic_device);
        }
        while (endless_loop);
        break;

    default:
        MHal_EMAC_NegotiationPHY();
        printf("EMAC normal mode!\n");
        break;
    }

    return TRUE;
}

void MDrv_EMAC_PatchPHY(void)
{
    u32 val = 0;
    MHal_EMAC_read_phy(phy_id, 2, &val);
    if (RTK_OUI_MSB == val)
    {
        MHal_EMAC_read_phy(phy_id, 25, &val);
        MHal_EMAC_write_phy(phy_id, 25, 0x400);
        MHal_EMAC_read_phy(phy_id, 25, &val);
    }
#if (SUPPORT_ALBANY)
    albany_patch();
#endif
}

int MDrv_EMAC_initialize(const bd_t * bis)
{
    struct eth_device *nic = NULL;
    struct emac_hw *hw = NULL;
    char* phy_id_string=NULL;

    phy_id_string = getenv ("PHY_ID");
    if (phy_id_string != NULL)
    {

        //phy_id =phy_id_string ? (int)simple_strtol(phy_id_string, NULL, 10) : 0;
        phy_id =(int)simple_strtol(phy_id_string, NULL, 10);
    }

    if(emac_init)
    {
#ifndef CONFIG_ETHERNET_ALBANY        
        MDrv_EMAC_PhyAddrScan();
#endif
#if (EMAC_DBG_TFTP)
        rxpre_seq = txpre_seq = 0;
#endif
        return -1;
    }

    if (!MDrv_EMAC_VarInit())
        return -1;
    nic=&nic_device;
    hw=&hw_device;

    hw->dlist_phys = hw->dlist = (struct recv_desc_bufs *) (RX_BUFFER_BASE|RAM_ADDR_BASE);

    printf("%s->%d\n",__FILE__,__LINE__);
    //asm __volatile__ ("abc: ; b abc;");
    MHal_EMAC_Power_On_Clk();
    printf("%s->%d\n",__FILE__,__LINE__);
    //asm __volatile__ ("abc: ; b abc;");
#ifndef CONFIG_ETHERNET_ALBANY        
    MDrv_EMAC_PhyAddrScan();
#endif
    printf("%s->%d\n",__FILE__,__LINE__);
    MDrv_EMAC_PatchPHY();
    nic->priv = hw;
    MDrv_EMAC_HW_init(nic);

    /* EMAC HW init */
    nic->init = MDrv_EMAC_open;
    nic->recv = MDrv_EMAC_rx;
    nic->send = MDrv_EMAC_tx;
    nic->halt = MDrv_EMAC_close;

    memcpy(nic->enetaddr, ThisBCE.sa1, sizeof(ThisBCE.sa1));
    eth_register(nic);
    emac_init=1;
    return 0;

    //test start
}

void MDrv_EMAC_PowerMode(u8 mode)
{
    if (mode == 1)
        MHal_EMAC_Power_On_Clk();
    else
        MHal_EMAC_Power_Off_Clk();
}

void MDrv_EMAC_WaveTest(u8 mode)
{
    switch (mode)
    {
#if defined(CONFIG_MSTAR_KERES) || defined(CONFIG_MSTAR_KIRIN)
        case 0:
            MHal_EMAC_Ewavetest_100M();
            break;
#endif

        default:
            printf("ewavetest mode:%d not support...\n", mode);
            break;
    }
}

void MDrv_EMAC_SwReset(void)
{
    extern void MHal_EMAC_PHY_reset(void) __attribute__((weak)); 

    if(MHal_EMAC_PHY_reset)
    {
        MHal_EMAC_PHY_reset();
    }
}
