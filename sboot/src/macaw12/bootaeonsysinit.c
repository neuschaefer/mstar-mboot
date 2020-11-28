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
/*------------------------------------------------------------------------------*/
/*  INCLUDE                                                                     */
/*------------------------------------------------------------------------------*/
#include "datatype.h"
#include "hwreg.h"
#include "drvGlobal.h"
#include "drvAeonUART.h"
#include "risc32_spr.h"
#include "drvPadConf.h"
#include "Board.h"

/*------------------------------------------------------------------------------*/
/*  VARAIBLES DECLARED IN LINKER SCRIPT                                         */
/*------------------------------------------------------------------------------*/
U16 *risc32_regbase;

extern unsigned char _text_length[];
extern unsigned char loader_2nd_lma[];
extern unsigned char loader_2nd_vma[];

extern unsigned char loader_2nd_len[];

#define BEON_MEM_ADR            0x200000
#define chunk_header_addr       0x20000
#define chunk_header_len        0x80

#define MHAL_DCACHE_SIZE        4096//(8192*4)
#ifdef __AEONR2__
#define MHAL_DCACHE_WAYS        2 // 4
#else
#define MHAL_DCACHE_WAYS        2
#endif
#define MHAL_DCACHE_LINE_SIZE   16

/*------------------------------------------------------------------------------*/
/*  LOCAL FUNCTIONS DECLARATION                                                 */
/*------------------------------------------------------------------------------*/
void load2ndLoader(U32 dst, U32 src, U32 size);

/*------------------------------------------------------------------------------*/
/*  LOCAL FUNCTIONS IMPLEMENTATION                                              */
/*------------------------------------------------------------------------------*/
void SetBdmaSrcDstDevice( U8 SrcDEv,U8 SrcDataWidth, U8 DstDEv , U8 DstDataWidth);
void SetBdmaSrcDstDevice( U8 SrcDEv,U8 SrcDataWidth, U8 DstDEv , U8 DstDataWidth)
{
   MDrv_Write2Byte( (BDMA_REG_BASE+0x04) ,  ( (DstDEv|DstDataWidth)  <<8) |(SrcDataWidth|SrcDEv) );

   //Both with 1 byte data width for FPGA test
}

/*------------------------------------------------------------------------------*/
/*  Copy binary image from SPI to DRAM                                          */
/*------------------------------------------------------------------------------*/
//#define REG8(a)       RIU8[((a) * 2) - ((a) & 1)]
void CopyFLH2MIU(U32 dst, U32 src, U32 size);
void CopyFLH2MIU(U32 dst, U32 src, U32 size)
{
    //printf("SPI %lx -> MIU %lx  length: %lx\n", spi_addr, miu_addr, length);

    while ( RIU8[(BDMA_REG_BASE + 0x02)*2]  & 0x01);   ///queue ==0?
    MDrv_Write4Byte((BDMA_REG_BASE + 0x08 ) , src  );
    MDrv_Write4Byte((BDMA_REG_BASE + 0x0c ),  dst  );
    MDrv_Write4Byte((BDMA_REG_BASE + 0x10 ), (size + 0x0f) & ~0x0fuL);
    MDrv_WriteByte((BDMA_REG_BASE + 0x06),0x00);   //increasing
    MDrv_WriteByte((BDMA_REG_BASE + 0x07),0x02);   //Set Dummy write count
    SetBdmaSrcDstDevice( SPI_FLASH , DW_8BYTE, DRAM_MIU_0, DW_8BYTE);
    MDrv_WriteByte( (BDMA_REG_BASE + 0x00), 0x01 );
    while(1) //for(k=0;k<12000;k++)
    {
        if ( (RIU8[(BDMA_REG_BASE+0x02)*2] & 0x08) == 0x08 )
        {
            return;        //pass
        }
    }
}

void BootFromDRAM(U32 u32BootAddr);
void BootFromDRAM(U32 u32BootAddr)
{
    //set up reset vector base
    MDrv_Write2Byte(0x1002B4, (U16)(u32BootAddr >> 16));
    MDrv_Write2Byte(0x002E54, 0x829f);  // set wtd_mcu_rst passwd
    MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)&(~BIT8));  // non-fire wtd_mcu_rst
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    MDrv_Write2Byte(0x100280, MDrv_Read2Byte(0x100280)|(0x002F));  // set sdr_boot=1, release rstz_miu
    MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)|(BIT8));  // fire wtd_mcu_rst
}

void loadAP(void);
void BL_Init(void);

//#define QMEM     ((unsigned  short volatile *) 0xc0000000ul)    //T2
#define QMEM     ((unsigned  short volatile *) 0xB0000000ul)    //T3

void start(void);
void start(void)
{
    //(1) disable watch dog
    MDrv_Write2Byte(0x3008, 0x0000);
    MDrv_Write2Byte(0x300A, 0x0000);

    //(2) boot initialization
    BL_Init();


    //(3)Pad Init
    MDrv_Pad_Init();

    //(4) copy 2nd loader here
    CopyFLH2MIU( (U32)loader_2nd_vma, (U32)loader_2nd_lma, (U32)loader_2nd_len );

    MDrv_Write2Byte(0x1002AC, 0xA100);  //SPI
    MDrv_Write2Byte(0x100290, 0xA100);  //SPI

    //(5) load and execute application
    BootFromDRAM((U32)loadAP);

    while(1);

}

#define __loader_start __attribute__ ((__section__ (".loader_2nd_start.text")))
#define __loader_2nd __attribute__ ((__section__ (".loader_2nd.text")))
extern void __loader_2nd DoMSDecompression(void);
//########################################
//#
//# Especially use  __loader_start specified section to
//# let it run at address 64Kx N+0x100
//#   Ex:  0x1000000+0x100 (see sboot.lds.S) => N=0x100
//########################################
void __loader_start loadAP(void)
{
	// Enable I-Cache to speed up the load code process
    __asm__ __volatile__ (
        /* Invalidate I-Cache */
        "\tl.addi  r13,r0,0\n"
        "1:\n"
        "\tl.mtspr %2,r13,0\n"
        "\tl.sfne  r13,%3\n"
        #ifdef __AEONR2__
        "\tl.addi  r13,r13,%4\n"
        "\tl.bf    1b\n"
        #else
        "\tl.bf    1b\n"
        "\tl.addi  r13,r13,%4\n"
        #endif

        /* Enable I-Cache */
        "\tl.mfspr r13,%0,0\n"
        "\tl.ori   r13,r13,%1\n"
        "\tl.mtspr %0,r13,0\n"

        /* Flush instructions out of instruction buffer */
        "\tl.nop\n"
        "\tl.nop\n"
        "\tl.nop\n"
        "\tl.nop\n"
        "\tl.nop\n"
        :
        : "r" (SPR_SR), "i" (SPR_SR_ICE), "r" (SPR_ICBIR),
          "r" (8192*2), "i" (16)
        : "r13");

	// Enable D-Cache to speed up decompress
    __asm__ __volatile__ (
        /* Invalidate DC    */
        "\tl.addi  r13,r0,0\n"
        "1:\n"

        "\tl.invalidate_line  0(r13), 0\n"
        "\tl.invalidate_line  0(r13), 1\n"

        "\tl.sfne  r13,%2\n"
        #ifdef __AEONR2__
        "\tl.addi  r13,r13,%3\n"
        "\tl.bf    1b\n"
        #else
        "\tl.bf    1b\n"
        "\tl.addi  r13,r13,%3\n"
        #endif

        /* Enable D-Cache */
        "\tl.mfspr r13,%0,0\n"
        "\tl.ori   r13,r13,%1\n"
        "\tl.mtspr %0,r13,0\n"
        :
        : "r" (SPR_SR), "i" (SPR_SR_DCE),
          "r" ((MHAL_DCACHE_SIZE/MHAL_DCACHE_WAYS) - MHAL_DCACHE_LINE_SIZE),
          "i" (MHAL_DCACHE_LINE_SIZE)
        : "r13");

    //start to do decompress task
    DoMSDecompression();

    #ifdef __AEONR2__
    while(1);
    #else
    __asm__ __volatile__ (
        "\tl.syncwritebuffer\n"
        "\tl.jr     %0\n"
        "\tl.syncwritebuffer\n"
        : : "r" (0x100));
    #endif
}

