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

#include "eMMC.h"


#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER

/* frequency bases */
/* divided by 10 to be nice to platforms without floating point */
int fbase[] = {
    10000,
    100000,
    1000000,
    10000000,
};

/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
 * to platforms without floating point.
 */
int multipliers[] = {
    0,  /* reserved */
    10,
    12,
    13,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    70,
    80,
};

//========================================================
U32 eMMC_LoadImages(U32 *pu32_Addr, U32 u32_ByteCnt,U32 u32_HashStage)
{
    #ifndef IP_FCIE_VERSION_5
    *pu32_Addr=0;
    u32_ByteCnt=0;
    u32_HashStage=0;
    
    return eMMC_ST_SUCCESS;
    #else
    U32 u32_err,u32_dma_addr;
    U16 u16_reg;
    

    eMMC_FCIE_ClearEvents();
    if(u32_HashStage == 0)
    {       
        eMMC_clock_setting(BIT_CLK_XTAL_12M);
        eMMC_pads_switch(FCIE_eMMC_BYPASS);  
        REG_FCIE_CLRBIT(FCIE_DDR_MODE,BIT_PAD_IN_SEL_SD|BIT_FALL_LATCH);

        REG_FCIE_SETBIT(FCIE_BOOT, BIT_NAND_BOOT_EN);  
        REG_FCIE_CLRBIT(FCIE_BOOT, BIT_BOOTSRAM_ACCESS_SEL);
        REG_FCIE_CLRBIT(FCIE_BOOT_CONFIG, BIT_BOOT_MODE_EN); // DMA to DRAM            
        eMMC_FCIE_Init();         
        eMMC_RST_L();        
        eMMC_hw_timer_delay(HW_TIMER_DELAY_5ms);        
        eMMC_RST_H();       
        eMMC_hw_timer_delay(HW_TIMER_DELAY_5ms);        
        u32_err = eMMC_ROM_BOOT_CMD0(0xFFFFFFFA, (U32)pu32_Addr, (U16)(u32_ByteCnt>>eMMC_SECTOR_512BYTE_BITS));        
        if(eMMC_ST_SUCCESS != u32_err)        
            goto  LABEL_LOAD_IMAGE_END;  
    }
    else
    {
        REG_FCIE_W(FCIE_JOB_BL_CNT, u32_ByteCnt>>eMMC_SECTOR_512BYTE_BITS);
        u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu32_Addr, u32_ByteCnt);
        
        REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
        REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);      
        REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, u32_ByteCnt & 0xFFFF);
        REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,u32_ByteCnt >> 16);
        REG_FCIE_CLRBIT(FCIE_BOOT, BIT_BOOTSRAM_ACCESS_SEL);
        REG_FCIE_CLRBIT(FCIE_BOOT_CONFIG, BIT_BOOT_MODE_EN); // DMA to DRAM  

        REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_JOB_START);
        u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(u32_ByteCnt>>20)));
        
        if(eMMC_ST_SUCCESS != u32_err)
            goto LABEL_LOAD_IMAGE_END;
    }
    // check status
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if( u16_reg & BIT_SD_FCIE_ERR_FLAGS )
    {
        u32_err = eMMC_ST_ERR_FCIE_STS_ERR;
        if(eMMC_ST_SUCCESS != u32_err)
            goto LABEL_LOAD_IMAGE_END;
    }    
    if(u32_HashStage == 2)
    { 
        u32_err = eMMC_CMD0(0);
        if(eMMC_ST_SUCCESS != u32_err)
            goto LABEL_LOAD_IMAGE_END;
        
        REG_FCIE_CLRBIT(FCIE_BOOT, BIT_NAND_BOOT_EN); 
    }
    return eMMC_ST_SUCCESS;
    LABEL_LOAD_IMAGE_END:
    REG_FCIE_CLRBIT(FCIE_BOOT, BIT_NAND_BOOT_EN);
    return u32_err;
    #endif
}



//========================================================
U32 eMMC_GetID(U8 *pu8IDByteCnt, U8 *pu8ID)
{
    eMMC_debug(eMMC_DEBUG_LEVEL_HIGH, 1, "\n");

    *pu8IDByteCnt = g_eMMCDrv.u8_IDByteCnt;
    memcpy(pu8ID, g_eMMCDrv.au8_ID, eMMC_ID_BYTE_CNT);

    return eMMC_ST_SUCCESS;
}


U32 eMMC_EraseAll(void)
{
    U32 u32_err;

    u32_err = eMMC_EraseBlock(0, g_eMMCDrv.u32_SEC_COUNT-1);
    if(eMMC_ST_SUCCESS != u32_err)
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
            "eMMC Err: fail: %Xh \n", u32_err);

    return u32_err;
}


U32 eMMC_EraseBootPart(U32 u32_eMMCBlkAddr_start, U32 u32_eMMCBlkAddr_end, U8 u8_PartNo)
{
    U32 u32_err, u32_SectorCnt, u32_i, u32_j;

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh\n", u32_err);
        return u32_err;
    }

    // set Access Boot Partition 1
    if(u8_PartNo == 1)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT0);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT0);
        #endif
    }
    else if(u8_PartNo == 2)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT1); 
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT1); // still boot from BP1
        #endif
    }
    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3|BIT0);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3|BIT0);
        #endif
        return u32_err;
    }

    if(g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_TRIM)
    {
        u32_err =  eMMC_EraseBlock(u32_eMMCBlkAddr_start, u32_eMMCBlkAddr_end);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_EraseBlock fail: %Xh \n", u32_err);
            return u32_err;
        }
    }
    else
    {
        for(u32_i=0; u32_i<eMMC_SECTOR_BUF_BYTECTN; u32_i++)
            gau8_eMMC_SectorBuf[u32_i] = 0xFF;

        // erase blocks before EraseUnitSize
        u32_SectorCnt = u32_eMMCBlkAddr_start / g_eMMCDrv.u32_EraseUnitSize;
        u32_SectorCnt = (u32_SectorCnt+1) * g_eMMCDrv.u32_EraseUnitSize;
        u32_SectorCnt -= u32_eMMCBlkAddr_start;
        u32_SectorCnt =
            u32_SectorCnt > (u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start) ?
            (u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start) : u32_SectorCnt;

        for(u32_i=0; u32_i<u32_SectorCnt; u32_i++)
        {
            u32_j = ((u32_SectorCnt-u32_i)<<eMMC_SECTOR_512BYTE_BITS)>eMMC_SECTOR_BUF_BYTECTN?
                eMMC_SECTOR_BUF_BYTECTN:((u32_SectorCnt-u32_i)<<eMMC_SECTOR_512BYTE_BITS);

            u32_err = eMMC_WriteData(gau8_eMMC_SectorBuf, u32_j,
                u32_eMMCBlkAddr_start + u32_i);
            if(eMMC_ST_SUCCESS != u32_err){
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: CMD24 fail 0, %Xh\n", u32_err);
                return u32_err;
            }

            u32_i += u32_j>>eMMC_SECTOR_512BYTE_BITS;
        }
        if((u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start) == u32_SectorCnt)
            goto LABEL_END_OF_ERASE;

        // erase blocks
        u32_i =
            (u32_eMMCBlkAddr_end - (u32_eMMCBlkAddr_start+u32_SectorCnt))
            /g_eMMCDrv.u32_EraseUnitSize;
        if(u32_i)
        {
            u32_err = eMMC_EraseBlock(
                (u32_eMMCBlkAddr_start+u32_SectorCnt),
                (u32_eMMCBlkAddr_start+u32_SectorCnt)+u32_i*g_eMMCDrv.u32_EraseUnitSize);
            if(eMMC_ST_SUCCESS != u32_err){
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: CMD24 fail 0, %Xh\n", u32_err);
                return u32_err;
            }
        }

        // erase blocks after EraseUnitSize
        u32_eMMCBlkAddr_start =
            (u32_eMMCBlkAddr_start+u32_SectorCnt) + u32_i*g_eMMCDrv.u32_EraseUnitSize;

        while(u32_eMMCBlkAddr_start < u32_eMMCBlkAddr_end)
        {
            u32_j = ((u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start)<<eMMC_SECTOR_512BYTE_BITS)>eMMC_SECTOR_BUF_BYTECTN?
                eMMC_SECTOR_BUF_BYTECTN:((u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start)<<eMMC_SECTOR_512BYTE_BITS);

            u32_err = eMMC_WriteData(gau8_eMMC_SectorBuf, u32_j, u32_eMMCBlkAddr_start);
            if(eMMC_ST_SUCCESS != u32_err){
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: CMD24 fail 1, %Xh\n", u32_err);
                return u32_err;
            }
            u32_eMMCBlkAddr_start += u32_j>>eMMC_SECTOR_512BYTE_BITS;
        }
    }

    LABEL_END_OF_ERASE:
    // clear Access Boot Partition
    #ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3);
    #else
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3);
    #endif 
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3);
        return u32_err;
    }

    return u32_err;
}

U32 eMMC_WriteBootPart(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr, U8 u8_PartNo)
{
    U32 u32_err;
    U16 u16_SecCnt, u16_i ,u16_j;

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh\n", u32_err);
        return u32_err;
    }

    // set Access Boot Partition 1
    if(u8_PartNo == 1)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT0);
        #else   
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT0);
        #endif  
    }
    else if(u8_PartNo == 2)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT1);  // still boot from BP1
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT1); // still boot from BP1
        #endif
    }
    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3|BIT0);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3|BIT0);
        #endif
        return u32_err;
    }

    // write Boot Code
    u16_SecCnt = (u32_DataByteCnt>>9) + ((u32_DataByteCnt&0x1FF)?1:0);
    //eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Boot Data keeps %Xh sectors, ChkSum: %Xh \n",
    //    u16_SecCnt, eMMC_ChkSum(pu8_DataBuf, u16_SecCnt<<9));
    //    u16_SecCnt, eMMC_ChkSum(pu8_DataBuf, BOOT_PART_TOTAL_CNT<<9));

    u32_err = eMMC_WriteData(pu8_DataBuf,
                  u16_SecCnt<<eMMC_SECTOR_512BYTE_BITS,
                  u32_BlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
            "eMMC Err: write Boot Partition fail, %Xh\n", u32_err);
        return u32_err;
    }
    #if 0
    // patch for U01 ROM code (clk not stop)
    for(u16_i=0; u16_i<eMMC_SECTOR_512BYTE; u16_i++)
        gau8_eMMC_SectorBuf[u16_i] = 0xFF;
    u32_err = eMMC_CMD24(BOOT_PART_TOTAL_CNT, gau8_eMMC_SectorBuf);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: U01 patch fail, %Xh\n", u32_err);
        return u32_err;
    }
    #endif
    // verify Boot Code
    u16_j =0;
    for(u16_i=(U16)u32_BlkAddr; u16_i<u16_SecCnt; u16_i++)
    {
        //eMMC_debug(eMMC_DEBUG_LEVEL,0,"\r checking: %03u%% ", (u16_i+1)*100/u16_SecCnt);
        //u32_err = eMMC_CMD17_CIFD(u16_i<<9, gau8_eMMC_SectorBuf);
        u32_err = eMMC_CMD17(u16_i, gau8_eMMC_SectorBuf);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
                "eMMC Err: read Boot Partition Sector %u fail, %Xh\n",
                u16_i, u32_err);
            return u32_err;
        }

        u32_err = eMMC_ComapreData(pu8_DataBuf+(u16_j<<9), gau8_eMMC_SectorBuf, eMMC_SECTOR_512BYTE);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
                "eMMC Err: check Boot Partition Sector %u fail, %Xh\n",
                u16_i, u32_err);
            eMMC_dump_mem(gau8_eMMC_SectorBuf, 0x200);
            return u32_err;
        }
        u16_j++;
    }

    // set Boot Bus
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 177, BIT1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[177]: %Xh fail\n",
            u32_err, BIT3|BIT1);
        return u32_err;
    }

    // clear Access Boot Partition
    #ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3);
    #else
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3);
    #endif
    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3);
        #endif
        return u32_err;
    }

    // set HW RST
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 162, BIT0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[162]: %Xh fail\n",
            u32_err, BIT0);
        return u32_err;
    }

    //eMMC_debug(eMMC_DEBUG_LEVEL,1,"ok\n");
    return u32_err;
}


U32 eMMC_ReadBootPart(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr, U8 u8_PartNo)
{
    U32 u32_err;
    U16 u16_SecCnt;

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh\n", u32_err);
        return u32_err;
    }

    // set Access Boot Partition 1
    if(u8_PartNo == 1)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT0); 
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT0);
        #endif
    }
    else if(u8_PartNo == 2)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT1);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT1);
        #endif
    }
    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3|BIT0);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3|BIT0);
        #endif      
        return u32_err;
    }

    // read Boot Code
    u16_SecCnt = (u32_DataByteCnt>>9) + ((u32_DataByteCnt&0x1FF)?1:0);

    u32_err = eMMC_ReadData(pu8_DataBuf,
                  u16_SecCnt<<eMMC_SECTOR_512BYTE_BITS,
                  u32_BlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
            "eMMC Err: read Boot Partition fail, %Xh\n", u32_err);
        return u32_err;
    }

    // clear Access Boot Partition
    #ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3);
    #else
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3);
    #endif
    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3);
        #endif
        return u32_err;
    }

    return u32_err;
}

U32 eMMC_WriteGPPart(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr, U8 u8_PartNo)
{
    U32 u32_err;
    U16 u16_SecCnt;

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh\n", u32_err);
        return u32_err;
    }

    if((g_eMMCDrv.u8_u8_ECSD155_PartSetComplete & BIT0) != BIT0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Partition setting has not been done yet.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    //set to HC Erase Define
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 175, BIT0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[175]: %Xh fail\n",
            u32_err, BIT0);
        return u32_err;
    }

    // set Access GP Partition 1
    if(u8_PartNo == 0)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2);
        #endif
    }
    else if(u8_PartNo == 1)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2|BIT0);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2|BIT0);
        #endif
    }
    else if(u8_PartNo == 2)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2|BIT1);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2|BIT1);
        #endif
    }
    else if(u8_PartNo == 3)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2|BIT1|BIT0);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2|BIT1|BIT0);
        #endif
    }
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3|BIT0);
        return u32_err;
    }

    // write Boot Code
    u16_SecCnt = (u32_DataByteCnt>>9) + ((u32_DataByteCnt&0x1FF)?1:0);
    //eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Boot Data keeps %Xh sectors, ChkSum: %Xh \n",
    //    u16_SecCnt, eMMC_ChkSum(pu8_DataBuf, u16_SecCnt<<9));
    //    u16_SecCnt, eMMC_ChkSum(pu8_DataBuf, BOOT_PART_TOTAL_CNT<<9));

    u32_err = eMMC_WriteData(pu8_DataBuf,
                  u16_SecCnt<<eMMC_SECTOR_512BYTE_BITS,
                  u32_BlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
            "eMMC Err: write Boot Partition fail, %Xh\n", u32_err);
        return u32_err;
    }
    #if 0
    // patch for U01 ROM code (clk not stop)
    for(u16_i=0; u16_i<eMMC_SECTOR_512BYTE; u16_i++)
        gau8_eMMC_SectorBuf[u16_i] = 0xFF;
    u32_err = eMMC_CMD24(BOOT_PART_TOTAL_CNT, gau8_eMMC_SectorBuf);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: U01 patch fail, %Xh\n", u32_err);
        return u32_err;
    }
    #endif

    // clear Access Boot Partition
    #ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3);
    #else
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3);
    #endif
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3);
        return u32_err;
    }

    // set HW RST
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 162, BIT0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[162]: %Xh fail\n",
            u32_err, BIT0);
        return u32_err;
    }

    //eMMC_debug(eMMC_DEBUG_LEVEL,1,"ok\n");
    return u32_err;
}


U32 eMMC_ReadGPPart(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr, U8 u8_PartNo)
{
    U32 u32_err;
    U16 u16_SecCnt;

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh\n", u32_err);
        return u32_err;
    }

    if((g_eMMCDrv.u8_u8_ECSD155_PartSetComplete & BIT0) != BIT0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Partition setting has not been done yet.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    //set to HC Erase Define
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 175, BIT0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[175]: %Xh fail\n",
            u32_err, BIT0);
        return u32_err;
    }

    // set Access GP Partition 1
    if(u8_PartNo == 0)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2);
        #endif
    }
    else if(u8_PartNo == 1)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2|BIT0);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2|BIT0);
        #endif
    }
    else if(u8_PartNo == 2)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2|BIT1);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2|BIT1);
        #endif
    }
    else if(u8_PartNo == 3)
    {
        #ifdef IP_FCIE_VERSION_5
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT2|BIT1|BIT0);
        #else
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT2|BIT1|BIT0);
        #endif
    }

    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3|BIT0);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3|BIT0);
        #endif
        return u32_err;
    }

    // read Boot Code
    u16_SecCnt = (u32_DataByteCnt>>9) + ((u32_DataByteCnt&0x1FF)?1:0);

    u32_err = eMMC_ReadData(pu8_DataBuf,
                  u16_SecCnt<<eMMC_SECTOR_512BYTE_BITS,
                  u32_BlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
            "eMMC Err: read Boot Partition fail, %Xh\n", u32_err);
        return u32_err;
    }

    // clear Access Boot Partition
    #ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3);
    #else
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3);
    #endif
    if(eMMC_ST_SUCCESS != u32_err)
    {
        #ifdef IP_FCIE_VERSION_5
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT3);
        #else
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[179]: %Xh fail\n",
            u32_err, BIT6|BIT3);
        #endif
        return u32_err;
    }

    return u32_err;
}

void eMMC_PrintGPPartition(void)
{
    U8 u8_i;
    eMMC_debug(eMMC_DEBUG_LEVEL, 0,"eMMC Gerneral Purpose Partition\n");
    eMMC_debug(eMMC_DEBUG_LEVEL, 0,"No.          Size\n");
    for(u8_i = 0; u8_i < 4; u8_i ++)
        eMMC_debug(eMMC_DEBUG_LEVEL, 0,"%d          0x%X\n", u8_i, g_eMMCDrv.GP_Part[u8_i].u32_PartSize);
}

//store partition setting in ram

U32 eMMC_SetGPPartition(U8 u8_PartNo, U32 u32_PartSize, U8 u8_EnAttr, U8 u8_ExtAttr, U8 u8_RelW)
{
    U32 u32_HC_WP_Size = g_eMMCDrv.u8_ECSD224_HCEraseGRPSize * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000;

    if((g_eMMCDrv.u8_u8_ECSD155_PartSetComplete & BIT0) == BIT0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Partition setting is already configured.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    if((g_eMMCDrv.u8_ECSD160_PartSupField & BIT0) == 0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC doesn't support GP and enhance partitions.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    if(u8_PartNo < 4)
    {
        if(u32_PartSize % u32_HC_WP_Size)
        {
            g_eMMCDrv.GP_Part[u8_PartNo].u32_PartSize = ((u32_PartSize / u32_HC_WP_Size) + 1) * u32_HC_WP_Size;
            eMMC_debug(0, 1, "Warning GP size: 0x%X does not align to 0x%X, adjust to 0x%X\n",
                u32_PartSize, u32_HC_WP_Size, g_eMMCDrv.GP_Part[u8_PartNo].u32_PartSize);
        }
        else
            g_eMMCDrv.GP_Part[u8_PartNo].u32_PartSize = u32_PartSize;
        g_eMMCDrv.GP_Part[u8_PartNo].u8_EnAttr = u8_EnAttr;
        g_eMMCDrv.GP_Part[u8_PartNo].u8_ExtAttr = u8_ExtAttr;
        g_eMMCDrv.GP_Part[u8_PartNo].u8_RelW = u8_RelW;
        return eMMC_ST_SUCCESS;
    }

    return eMMC_ST_ERR_INVALID_PARAM;
}

U32 eMMC_SetEnhanceUserPartition(U32 u32_StartAddr, U32 u32_Size, U8 u8_EnAttr, U8 u8_RelW)
{
    U32 u32_HC_WP_Size = g_eMMCDrv.u8_ECSD224_HCEraseGRPSize * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000;

    if((g_eMMCDrv.u8_u8_ECSD155_PartSetComplete & BIT0) == BIT0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Partition setting is already configured.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    if((g_eMMCDrv.u8_ECSD160_PartSupField & BIT0) == 0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC doesn't support GP and enhance partitions.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    if(g_eMMCDrv.u8_ECSD160_PartSupField & BIT1)
    {
        if(u32_Size % u32_HC_WP_Size)
        {

            g_eMMCDrv.u32_EnUserSize = ((u32_Size / u32_HC_WP_Size) + 1) * u32_HC_WP_Size;
            eMMC_debug(0, 1, "Warning Enhance Size: 0x%X does not align to 0x%X, adjust to 0x%X\n",
                u32_Size, u32_HC_WP_Size, g_eMMCDrv.u32_EnUserSize);
        }
        else
            g_eMMCDrv.u32_EnUserSize= u32_Size;

        if(g_eMMCDrv.u8_IfSectorMode)
            g_eMMCDrv.u32_EnUserStartAddr = u32_StartAddr >> 9 ;
        else
            g_eMMCDrv.u32_EnUserStartAddr = u32_StartAddr;
        g_eMMCDrv.u8_EnUserEnAttr= u8_EnAttr;
        g_eMMCDrv.u8_EnUserRelW= u8_RelW;
        return eMMC_ST_SUCCESS;
    }
    return eMMC_ST_ERR_INVALID_PARAM;
}

U32 eMMC_SetPartitionComplete(void)
{
    U64 u64_MaxEnhSize, u64_tmp;
    U32 u32_err, u32_HC_WP_Size, u32_tmp;
    U8  u8_i, u8_j, u8_tmp, u16_tmp;

    if((g_eMMCDrv.u8_ECSD160_PartSupField & BIT0) == 0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC doesn't support GP and enhance partitions.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    if((g_eMMCDrv.u8_u8_ECSD155_PartSetComplete & BIT0) == BIT0)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Partition setting is already configured.\n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    u32_HC_WP_Size = g_eMMCDrv.u8_ECSD224_HCEraseGRPSize * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000;

    //set to HC Erase Define
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 175, BIT0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[175]: %Xh fail\n",
            u32_err, BIT0);
        return u32_err;
    }

    //set Enhance Attribute for each partition
    if(g_eMMCDrv.u8_ECSD160_PartSupField & BIT1)
    {
        u64_MaxEnhSize = (U64)((((U32)(g_eMMCDrv.u8_ECSD159_MaxEnhSize_2) << 16)|
                            ((U32)(g_eMMCDrv.u8_ECSD158_MaxEnhSize_1) << 8) |
                            (U32)(g_eMMCDrv.u8_ECSD157_MaxEnhSize_0)) * u32_HC_WP_Size);


        u8_tmp = 0;
        u64_tmp = 0;
        if(g_eMMCDrv.u8_EnUserEnAttr == 1)
        {
            u64_tmp = (U64)g_eMMCDrv.u32_EnUserSize;
            u8_tmp |= BIT0;
        }

        for(u8_i = 0; u8_i < 4; u8_i ++)
        {
            if(g_eMMCDrv.GP_Part[u8_i].u8_EnAttr == 1)
            {
                u64_tmp += (U64)g_eMMCDrv.GP_Part[u8_i].u32_PartSize;
                u8_tmp |= (1 << (u8_i + 1));
            }
        }

        if(u64_MaxEnhSize < u64_tmp)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "Sum of all enhance partition size shell be less than 0x%llX, but get 0x%llX\n", u64_MaxEnhSize, u64_tmp);
            return eMMC_ST_ERR_INVALID_PARAM;
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [156], Partition Attribute, to 0x%X\n", u8_tmp);

        #if 1
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 156, u8_tmp);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[156]: %Xh fail\n",
                u32_err, u8_tmp);
            return u32_err;
        }
        #endif

        //set enhance user partition, if defined
        if(g_eMMCDrv.u32_EnUserSize)
        {
            //size enhance user partition size
            u32_tmp = g_eMMCDrv.u32_EnUserSize / u32_HC_WP_Size;

            for(u8_i = 3; u8_i > 0; u8_i --)
            {
                u8_tmp = (u32_tmp >> (8 * (u8_i - 1))) & 0xFF;
                eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], Enhance User Size, to 0x%X\n", 140 + (u8_i - 1), u8_tmp);
                #if 1
                u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 140 + (u8_i - 1), u8_tmp);
                if(eMMC_ST_SUCCESS != u32_err)
                {
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
                        u32_err, 140 + (u8_i - 1), u8_tmp);
                    return u32_err;
                }
                #endif
            }
            //set enhance user partition start address
            u32_tmp = g_eMMCDrv.u32_EnUserStartAddr;

            for(u8_i = 4; u8_i > 0 ;u8_i --)
            {
                u8_tmp = (u32_tmp >> (8 * (u8_i - 1))) & 0xFF;
                eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], Enhance Start Address, to 0x%X\n", 136 + u8_i - 1, u8_tmp);
                #if 1
                u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 136 + u8_i - 1, u8_tmp);
                if(eMMC_ST_SUCCESS != u32_err)
                {
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
                        u32_err, 136 + u8_i - 1, u8_tmp);
                    return u32_err;
                }
                #endif
            }
        }
    }

    //set GP partition size
    for(u8_i = 0; u8_i < 4; u8_i ++)
    {
        u32_tmp = g_eMMCDrv.GP_Part[u8_i].u32_PartSize / u32_HC_WP_Size;
        u16_tmp = 143 + u8_i * 3;
        for(u8_j = 3; u8_j > 0; u8_j --)
        {
            u8_tmp = (u32_tmp >> (8 * (u8_j - 1))) & 0xFF;
            eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], GP Part %d, to 0x%X\n", u16_tmp + (u8_j - 1), u8_i, u8_tmp);

            #if 1
            u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, u16_tmp + (u8_j - 1), u8_tmp);
            if(eMMC_ST_SUCCESS != u32_err)
            {
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
                    u32_err, u16_tmp + (u8_j - 1), u8_tmp);
                return u32_err;
            }
            #endif
        }
    }
    //set GP partition extend attribute

    if(g_eMMCDrv.u8_ECSD160_PartSupField & BIT2)
    {
        u8_tmp = 0;
        if(g_eMMCDrv.GP_Part[0].u8_ExtAttr > 0 && g_eMMCDrv.GP_Part[0].u8_ExtAttr < 3)
        {
            u8_tmp  |= (g_eMMCDrv.GP_Part[0].u8_ExtAttr & 0xF);
        }
        if(g_eMMCDrv.GP_Part[1].u8_ExtAttr > 0 && g_eMMCDrv.GP_Part[1].u8_ExtAttr < 3)
        {
            u8_tmp  |= ((g_eMMCDrv.GP_Part[1].u8_ExtAttr << 4) & 0xF0);
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], Extend Attr, to 0x%X\n", 52, u8_tmp);

        #if 1
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 52, u8_tmp);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
                u32_err, 52, u8_tmp);
            return u32_err;
        }
        #endif

        u8_tmp = 0;
        if(g_eMMCDrv.GP_Part[2].u8_ExtAttr > 0 && g_eMMCDrv.GP_Part[2].u8_ExtAttr < 3)
        {
            u8_tmp  |= (g_eMMCDrv.GP_Part[2].u8_ExtAttr & 0xF);
        }
        if(g_eMMCDrv.GP_Part[3].u8_ExtAttr > 0 && g_eMMCDrv.GP_Part[3].u8_ExtAttr < 3)
        {
            u8_tmp  |= ((g_eMMCDrv.GP_Part[3].u8_ExtAttr << 4) & 0xF0);
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], Extend Attr, to 0x%X\n", 53, u8_tmp);

        #if 1
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 53, u8_tmp);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
                u32_err, 53, u8_tmp);
            return u32_err;
        }
        #endif
    }
    else
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Warning: eMMC doesn't support GP ext Attribute\n")
        ;
    }
    //set reliable write

    if((g_eMMCDrv.u8_ECSD166_WrRelParam & (BIT0|BIT2)) == BIT0)     //if BIT2 is set -> device support reliable write by default
    {
        u8_tmp = 0;
        if(g_eMMCDrv.u8_EnUserRelW== 1)
        {
            u8_tmp |= BIT0;
        }

        for(u8_i = 0; u8_i < 4; u8_i ++)
        {
            if(g_eMMCDrv.GP_Part[u8_i].u8_RelW == 1)
            {
                u8_tmp |= (1 << (u8_i + 1));
            }
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], Reliable Write Setting, to 0x%X\n", 167, u8_tmp);
        #if 1
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 167, u8_tmp);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
                u32_err, 167, u8_tmp);
            return u32_err;
        }
        #endif
    }
    eMMC_debug(eMMC_DEBUG_LEVEL_WARNING, 1, "Set Ext_CSD [%d], Complete Setting, to 0x%X\n", 155, BIT0);

    //finally set partition setting completed bit
    #if 1
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 155, BIT0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[%d]: %Xh fail\n",
            u32_err, 155, BIT0);
        return u32_err;
    }
    #endif
    return eMMC_ST_SUCCESS;
}


// ==============================================================
void eMMC_DumpSpeedStatus(void)
{
    if(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_DDR_MODE)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,0,"  DDR Mode\n");
        eMMC_DumpTimingTable();
        eMMC_debug(eMMC_DEBUG_LEVEL,0," \n");
    }
    else
        eMMC_debug(eMMC_DEBUG_LEVEL,0,"  SDR Mode\n");

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  FCIE Clk: %u.%u MHz, %Xh\n",
        g_eMMCDrv.u32_ClkKHz/1000, (g_eMMCDrv.u32_ClkKHz/100)%10, g_eMMCDrv.u16_ClkRegVal);

    switch(g_eMMCDrv.u8_BUS_WIDTH)
    {
        case BIT_SD_DATA_WIDTH_1:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"  1-bit ");
            break;
        case BIT_SD_DATA_WIDTH_4:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"  4-bits ");
            break;
        case BIT_SD_DATA_WIDTH_8:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"  8-bits ");
            break;
    }
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"width\n");

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  Bus Speed:");
    switch(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_SPEED_MASK)
    {
        case DRV_FLAG_SPEED_HIGH:
            eMMC_debug(eMMC_DEBUG_LEVEL,0," HIGH\n");
            break;
        case DRV_FLAG_SPEED_HS200:
            eMMC_debug(eMMC_DEBUG_LEVEL,0," HS200\n");
            eMMC_DumpTimingTable();
            eMMC_debug(eMMC_DEBUG_LEVEL,0," \n");
            break;
        case DRV_FLAG_SPEED_HS400:
            eMMC_debug(eMMC_DEBUG_LEVEL,0," HS400\n");
            //eMMC_DumpTimingTable();
            eMMC_debug(eMMC_DEBUG_LEVEL,0," \n");
            break;
        default:
            eMMC_debug(eMMC_DEBUG_LEVEL,0," LOW\n");
    }
}


void eMMC_DumpDriverStatus(void)
{
    eMMC_debug(0,1,"\n  eMMCDrvExtFlag: %Xh \n\n", gu32_eMMCDrvExtFlag);

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"eMMC Status: 2014/03/25 \n");

    // ------------------------------------------------------
    // helpful debug info
    // ------------------------------------------------------
    #if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  RIU Mode\n");
    #else
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  MIU Mode\n");
    #endif

    #if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  Interrupt Mode\n");
    #else
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  Polling Mode\n");
    #endif

    #if defined(FICE_BYTE_MODE_ENABLE)&&FICE_BYTE_MODE_ENABLE
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  FCIE Byte Mode\n");
    #else
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  FCIE Block Mode\n");
    #endif

    eMMC_DumpSpeedStatus();

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  PwrOff Notification: ");
    switch(g_eMMCDrv.u32_DrvFlag&DRV_FLAG_PwrOffNotif_MASK)
    {
        case DRV_FLAG_PwrOffNotif_OFF:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"OFF\n");  break;
        case DRV_FLAG_PwrOffNotif_ON:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"ON\n");  break;
        case DRV_FLAG_PwrOffNotif_SHORT:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"SHORT\n");  break;
        case DRV_FLAG_PwrOffNotif_LONG:
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"LONG\n");  break;
        default:
            eMMC_debug(eMMC_DEBUG_LEVEL,0," eMMC Err: unknown: %Xh\n",
                g_eMMCDrv.u32_DrvFlag&DRV_FLAG_PwrOffNotif_MASK);
    }

    #if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
    eMMC_DumpBurstLenTable();
    #endif

}


U32 eMMC_Init(void)
{
    U32 u32_err;

    #if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
    eMMC_enable_intr_mode();
    #endif

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err)
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh\n", u32_err);

    return u32_err;
}

#ifdef CONFIG_GENERIC_MMC

extern int fbase[];
extern int multipliers[];


U32 eMMC_GetExtCSD(U8* pu8_Ext_CSD)
{
    return eMMC_CMD8(pu8_Ext_CSD);
}

U32 eMMC_SetExtCSD(U8 u8_AccessMode, U8 u8_ByteIdx, U8 u8_Value)
{
    return eMMC_ModifyExtCSD(u8_AccessMode, u8_ByteIdx,u8_Value);
}
static ulong eMMC_bread(int dev_num, ulong start, lbaint_t blkcnt, void *dst)
{
    U32 u32_Err;
        if( blkcnt == 0)
            return 0;
    u32_Err = eMMC_ReadData(dst, blkcnt << 9, start);
    if (u32_Err == eMMC_ST_SUCCESS)
        return blkcnt;
    else
        return 0;
}

static ulong eMMC_bwrite(int dev_num, ulong start, lbaint_t blkcnt, const void *src)
{
    U32 u32_Err, u32_blkcnt, u32_start = start;
    U8* pu8_src = (U8*) src;

    u32_blkcnt = blkcnt;

    u32_Err = eMMC_WriteData(pu8_src, u32_blkcnt << 9, u32_start);

    if (u32_Err == eMMC_ST_SUCCESS)
        return blkcnt;
    else
        return 0;
}

static ulong eMMC_berase(int dev_num, ulong start, lbaint_t blkcnt)
{

    U32 u32_Err;
    u32_Err = eMMC_EraseBlock (start, start + blkcnt - 1);
    if (u32_Err == eMMC_ST_SUCCESS)
        return blkcnt;
    else
        return 0;
}

int eMMC_mmc_Init(struct mmc* mmc)
{

    eMMC_Init();

    sprintf(mmc->name, "Mstar-eMMC");
    mmc->has_init = 1;
    mmc->capacity = (u64)g_eMMCDrv.u32_SEC_COUNT << 9;

#ifndef CONFIG_TSD

    eMMC_GetExtCSD((U8*)mmc->ext_csd);

    mmc->high_capacity = g_eMMCDrv.u8_IfSectorMode;
    mmc->bus_width = g_eMMCDrv.u8_BUS_WIDTH << 1;

    switch (g_eMMCDrv.u8_SPEC_VERS) {
        case 0:
            mmc->version = MMC_VERSION_1_2;
            break;
        case 1:
            mmc->version = MMC_VERSION_1_4;
            break;
        case 2:
            mmc->version = MMC_VERSION_2_2;
            break;
        case 3:
            mmc->version = MMC_VERSION_3;
            break;
        case 4:
            mmc->version = MMC_VERSION_4;
            break;
        default:
            mmc->version = MMC_VERSION_1_2;
            break;
    }

    /* divide frequency by 10, since the mults are 10x bigger */

    mmc->tran_speed = fbase[( g_eMMCDrv.u8_Tran_Speed & 0x7)] * multipliers[((g_eMMCDrv.u8_Tran_Speed >> 3) & 0xf)];

        // reliable write is supported
    if ((mmc->ext_csd[EXT_CSD_WR_REL_SET] & 0x01) == 1) // reliable write is configured
        mmc->reliable_write = 2;
    else if((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[EXT_CSD_WR_REL_PARAM] & BIT0) == BIT0))
    {
        mmc->reliable_write = 1;  // reliable write is supported but not configured
        //eMMC_debug(0,0,"[%s]\treliable write is supported\n", __func__);
    }
    else if((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[EXT_CSD_WR_REL_PARAM] & BIT2) == BIT2))
    {
        mmc->reliable_write = 3;  // reliable write is supported but not configurable
        //eMMC_debug(0,0,"[%s]\treliable write is supported\n", __func__);
    }
    else
    {
        mmc->reliable_write = 0;  // reliable write is unsupported
        //eMMC_debug(0,0,"[%s]\treliable write is unsupported\n", __func__);
    }

    if ((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[160] & 0x3) == 3))
    {
        mmc->slc_size = ((u64)(mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_0]
               | ((u32)(mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_1]) << 8)
               | ((u32)(mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_2]) << 16)) << 19)
               * mmc->ext_csd[221] * mmc->ext_csd[224];
        mmc->max_slc_size = ((u64)(mmc->ext_csd[157]
               | ((u32)(mmc->ext_csd[158]) << 8)
               | ((u32)(mmc->ext_csd[159]) << 16)) << 19)
               * mmc->ext_csd[221] * mmc->ext_csd[224];
        //eMMC_debug(0,0,"[%s]\t slc_size = %lld, max_slc_size = %lld\n",__func__, mmc->slc_size, mmc->max_slc_size);
    }
    else // slc mode is unsupported
    {
        mmc->slc_size = mmc->max_slc_size = 0;
        //eMMC_debug(0,0,"[%s]\t slc mode is unsupported\n",__func__);
    }
#endif

    {
        U16 u16_i;
        for(u16_i = 0; u16_i < 4; u16_i ++)
        {
            if(u16_i < 3)
                mmc->cid[u16_i] =
                    g_eMMCDrv.au8_CID[u16_i * 4 + 1] << 24 |  g_eMMCDrv.au8_CID[u16_i * 4 + 2] << 16|
                    g_eMMCDrv.au8_CID[u16_i * 4 + 3] << 8 | g_eMMCDrv.au8_CID[u16_i * 4 + 4];
            else
                mmc->cid[u16_i] =
                    g_eMMCDrv.au8_CID[u16_i * 4 + 1] << 24 |  g_eMMCDrv.au8_CID[u16_i * 4 + 2] << 16|
                    g_eMMCDrv.au8_CID[u16_i * 4 + 3] << 8;
        }
    }

    mmc->read_bl_len = 512;
    mmc->write_bl_len = 512;
    mmc->block_dev.lun = 0;
    mmc->block_dev.type = 0;
    mmc->block_dev.blksz = 512;
    mmc->block_dev.lba = g_eMMCDrv.u32_SEC_COUNT;
    mmc->block_dev.part_type = PART_TYPE_EMMC;
    sprintf(mmc->block_dev.vendor, "Man %06x Snr %08x", mmc->cid[0] >> 8,
            (mmc->cid[2] << 8) | (mmc->cid[3] >> 24));
    sprintf(mmc->block_dev.product, "%c%c%c%c%c", mmc->cid[0] & 0xff,
            (mmc->cid[1] >> 24), (mmc->cid[1] >> 16) & 0xff,
            (mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);
    sprintf(mmc->block_dev.revision, "%d.%d", mmc->cid[2] >> 28,
            (mmc->cid[2] >> 24) & 0xf);

//  init_part(&mmc->block_dev);
    return 0;
}

int board_mmc_init(bd_t *bis)
{
    struct mmc* mmc = NULL;

    mmc = malloc(sizeof(struct mmc)); // uboot origianl design, don't free it.
    if (!mmc)
        return -ENOMEM;
    memset(mmc, 0, sizeof(struct mmc));

    eMMC_mmc_Init(mmc);

    mmc_register(mmc);

    mmc->block_dev.block_read = eMMC_bread;
    mmc->block_dev.block_write = eMMC_bwrite;
    mmc->block_dev.block_erase = eMMC_berase;

    return 0; // uboot origianl design, don't free mmc.
}

#endif

#define eMMC_NOT_READY_MARK    ~(('e'<<24)|('M'<<16)|('M'<<8)|'C')
static U32 sgu32_IfReadyGuard = eMMC_NOT_READY_MARK;

static U32 eMMC_Init_Ex(void)
{
    U32 u32_err;

    // ---------------------------------
    u32_err = eMMC_CheckAlignPack(eMMC_CACHE_LINE);
    if(u32_err)
        goto  LABEL_INIT_END;

    memset((void*)&g_eMMCDrv, '\0', sizeof(eMMC_DRIVER));

    g_eMMCDrv.u16_Reg10_Mode = BIT_SD_DEFAULT_MODE_REG;

    // ---------------------------------
    // init platform & FCIE
    eMMC_PlatformInit();
    u32_err = eMMC_FCIE_Init();
    if(u32_err)
        goto  LABEL_INIT_END;

    // ---------------------------------
    #ifndef CONFIG_TSD
    u32_err = eMMC_Init_Device();
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "eMMC ");
    #else
    u32_err = tSD_Init_Device();
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\33[1;36mtSD\33[m ");
    #endif
    if(u32_err)
        goto LABEL_INIT_END;

    // Set flag to inform the kernel that only eMMC driver is enabled

    #ifdef IP_FCIE_VERSION_5
        extern void HalFcie_SetFlag4Kernel2RuneMMC(void);
        HalFcie_SetFlag4Kernel2RuneMMC();
    #else
        REG_FCIE_CLRBIT(FCIE_REG16h, BIT_KERN_CHK_NAND_EMMC_MSK);
        REG_FCIE_SETBIT(FCIE_REG16h, BIT_KERN_EMMC);
    #endif

    sgu32_IfReadyGuard = ~eMMC_NOT_READY_MARK;

    LABEL_INIT_END:
    g_eMMCDrv.u32_LastErrCode = u32_err;

    // ---------------------------------
    // setup ID
    // use first 10 bytes of CID
    memcpy(g_eMMCDrv.au8_ID, &g_eMMCDrv.au8_CID[1], eMMC_ID_FROM_CID_BYTE_CNT);
    g_eMMCDrv.u8_IDByteCnt = eMMC_ID_DEFAULT_BYTE_CNT;
    // add a 11-th byte for number of GB
    g_eMMCDrv.au8_ID[eMMC_ID_FROM_CID_BYTE_CNT] =
        (g_eMMCDrv.u32_SEC_COUNT >> (1+10+10)) + 1;
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "%u.%u GB [%Xh]\n",
        g_eMMCDrv.u32_SEC_COUNT>>11>>10,
        (g_eMMCDrv.u32_SEC_COUNT>>11)*100/1024%100,
        g_eMMCDrv.u32_SEC_COUNT);
    //eMMC_dump_mem(g_eMMCDrv.au8_ID, 0x10);
    #if 0
    u32_err = eMMC_ReadPartitionInfo_Ex();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL, 1, "eMMC Err: eMMC Init, no pni, :%Xh\n", u32_err);
        return eMMC_ST_ERR_NO_CIS;
    }
    //eMMC_DumpDriverStatus();
    #endif

    return u32_err;
}

//#ifndef CONFIG_TSD


U32 eMMC_Init_Device_Ex(void)
{
    U32 u32_err;

    #if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSPFROMRAM_SAVE;
    #endif

    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_INIT_DONE;

    // init eMMC device
    u32_err = eMMC_Identify();
    if(u32_err)
        return u32_err;

    eMMC_clock_setting(FCIE_SLOW_CLK);

    // determine device parameters, from CSD
    u32_err = eMMC_CSD_Config();
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    // setup eMMC device
    // CMD7
    u32_err = eMMC_CMD3_CMD7(g_eMMCDrv.u16_RCA, 7);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    #if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
    u32_err = eMMC_CMD16(eMMC_SECTOR_512BYTE);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;
    #endif

    // determine device parameters, from Ext_CSD
    u32_err = eMMC_ExtCSD_Config();
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    //eMMC_debug(0,0,"set bus witdth 8 bits\n");
    u32_err = eMMC_SetBusWidth(8, 0);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;
    
    //eMMC_debug(0,0,"set to high speed\n");
    u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HIGH);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    eMMC_clock_setting(FCIE_DEFAULT_CLK);
    #ifdef IP_FCIE_VERSION_5
    eMMC_pads_switch(FCIE_eMMC_SDR);
    #endif

    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_INIT_DONE;

    return u32_err;
}


U32 eMMC_Init_Device(void)
{
    U32 u32_err;

    u32_err = eMMC_Init_Device_Ex();
    if(eMMC_ST_SUCCESS != u32_err)
        goto  LABEL_INIT_END;

    // ----------------------------------------
    u32_err = eMMC_FCIE_ChooseSpeedMode();
    if(eMMC_ST_SUCCESS != u32_err)
            goto  LABEL_INIT_END;
    //while(1);

    // ----------------------------------------
    #if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
    u32_err = eMMC_LoadBurstLenTable();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u32_err = eMMC_SaveBurstLenTable();
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: save Burst Len: %Xh\n", u32_err);
            goto LABEL_INIT_END;
        }
        else
            eMMC_DumpBurstLenTable();
    }
    #endif

    //eMMC_dump_mem(g_eMMCDrv.au8_AllRsp, 0x100);
    LABEL_INIT_END:

    return u32_err;

}

//#else

/*void mstar_dump_fcie_register(void)
{
    U32 i;
    for(i=0; i<0x60; i++) {
        eMMC_debug(0,0,"%04X ", REG_FCIE(GET_REG_ADDR(FCIE_REG_BASE_ADDR, i)));
        if(i%8==7) eMMC_debug(0,0,"\n");
    }
}*/
#ifdef CONFIG_TSD

#define DBG_SD_INIT(MSG)    //MSG   // enable to know tSD identify fail at witch step
U32 tSD_Init_Device(void)
{
    U32 u32_err;

    DBG_SD_INIT(eMMC_debug(0,0,"[%s] L: %d --> %s()\n", __FILE__, __LINE__, __FUNCTION__);)

    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_INIT_DONE;

    eMMC_clock_setting(FCIE_SLOWEST_CLK);

    // CMD0
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCMD0\33[m\n");)
    u32_err = eMMC_CMD0(0);
    if(u32_err) goto ErrorHandle;

    // CMD8, SDHC need this before ACMD41. Really old card will fail here, but should not meet in tSD.
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCM8\33[m\n");)
    u32_err = tSD_CMD8();
    if(u32_err) goto ErrorHandle;

    // ACMD41, ORC in R3
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mACMD41\33[m\n");)
    u32_err = tSD_WaitCardPowerUp();
    if(u32_err) goto ErrorHandle;

    // CMD2, all send CID. Let card enter ident state
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCMD2\33[m\n");)
    u32_err = eMMC_CMD2();
    if(u32_err) goto ErrorHandle;

    // CMD3, send RCA
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCMD3\33[m\n");)
    u32_err = tSD_CMD3();
    if(u32_err) goto ErrorHandle;

    // CMD9 get CSD
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCMD9\33[m\n");)
    u32_err = tSD_CSD_Config();
    if(u32_err) goto ErrorHandle;

    // CMD7, select card
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCMD7\33[m\n");)
    u32_err = eMMC_CMD3_CMD7(g_eMMCDrv.u16_RCA, 7);
    if(u32_err) goto ErrorHandle;

    //tSD_ACMD13(); // debug & development use

    // ACMD6, set 4 bits bus
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mACMD6\33[m\n");)
    u32_err = tSD_SetBusCondition(4);
    if(u32_err) goto ErrorHandle;

    // ACMD13 -> confirm 4 bits data bus & get AU_SIZE, ERASE_SIZE, and ERASE_TO
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mACMD13\33[m\n");)
    u32_err = tSD_ACMD13();
    if(u32_err) goto ErrorHandle;

    // ACMD51, send SCR
    // to get the SD version, it should be later than 2.0 in tSD application case
    // need for erase content definition
    u32_err = tSD_ACMD51();
    if(u32_err) goto ErrorHandle;

    // CMD6, switch to high speed
    DBG_SD_INIT(eMMC_debug(0,0,"\33[1;31mCMD6\33[m\n");)
    u32_err = tSD_SetBusSpeed(eMMC_SPEED_HIGH);
    if(u32_err==eMMC_ST_ERR_CMD6_HS_NOT_SRPO)
    {
        eMMC_clock_setting(FCIE_SLOW_CLK); // for debug default speed card use. tSD should be high speed
        printf(" 12MHz\n");
        u32_err=0;
    }
    else if(u32_err)
        goto ErrorHandle;
    else
        eMMC_clock_setting(FCIE_DEFAULT_CLK); // actually not all SD support 50 MHz, but tSD shoudl be OK.

    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_INIT_DONE;

#if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
    u32_err = eMMC_LoadBurstLenTable();
    if(eMMC_ST_SUCCESS != u32_err) {
        u32_err = eMMC_SaveBurstLenTable();
        if(eMMC_ST_SUCCESS != u32_err) {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: save Burst Len: %Xh\n", u32_err);
            goto ErrorHandle;
        } else {
            eMMC_DumpBurstLenTable();
        }
    }
#endif

ErrorHandle:

    if(u32_err) eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %s() fail %08Xh\n", __FUNCTION__, u32_err);

    return u32_err;
}

#endif

U32 eMMC_CheckIfReady(void)
{
    if(eMMC_NOT_READY_MARK != sgu32_IfReadyGuard)
        return eMMC_ST_SUCCESS;
    else
        return eMMC_Init_Ex();
}

void eMMC_ResetReadyFlag(void)
{
    sgu32_IfReadyGuard = eMMC_NOT_READY_MARK;
}


// =======================================================
// u32_DataByteCnt: has to be 512B-boundary !
// =======================================================

U32 eMMC_EraseBlock(U32 u32_eMMCBlkAddr_start, U32 u32_eMMCBlkAddr_end)
{
    #ifndef CONFIG_TSD
    U32 u32_err, u32_SectorCnt, u32_i, u32_j;

    if(g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_TRIM)
    {
        u32_err =  eMMC_EraseCMDSeq(u32_eMMCBlkAddr_start, u32_eMMCBlkAddr_end);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EraseCMDSeq fail 0: %Xh \n", u32_err);
            return u32_err;
        }
    }
    else
    {
        for(u32_i=0; u32_i<eMMC_SECTOR_BUF_BYTECTN; u32_i++)
            gau8_eMMC_SectorBuf[u32_i] = g_eMMCDrv.u8_ErasedMemContent;

        // erase blocks before EraseUnitSize
        u32_SectorCnt = u32_eMMCBlkAddr_start / g_eMMCDrv.u32_EraseUnitSize;
        u32_SectorCnt = (u32_SectorCnt+1) * g_eMMCDrv.u32_EraseUnitSize;
        u32_SectorCnt -= u32_eMMCBlkAddr_start;
        u32_SectorCnt =
            u32_SectorCnt > (u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start) ?
            (u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start) : u32_SectorCnt;

        for(u32_i=0; u32_i<u32_SectorCnt; u32_i++)
        {
            u32_j = ((u32_SectorCnt-u32_i)<<eMMC_SECTOR_512BYTE_BITS)>eMMC_SECTOR_BUF_BYTECTN?
                eMMC_SECTOR_BUF_BYTECTN:((u32_SectorCnt-u32_i)<<eMMC_SECTOR_512BYTE_BITS);

            u32_err = eMMC_WriteData(gau8_eMMC_SectorBuf, u32_j,
                u32_eMMCBlkAddr_start + u32_i);
            if(eMMC_ST_SUCCESS != u32_err){
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: WriteData fail 0, %Xh\n", u32_err);
                return u32_err;
            }

            u32_i += u32_j>>eMMC_SECTOR_512BYTE_BITS;
        }
        if((u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start) == u32_SectorCnt)
            goto LABEL_END_OF_ERASE;

        // erase blocks
        u32_i =
            (u32_eMMCBlkAddr_end - (u32_eMMCBlkAddr_start+u32_SectorCnt))
            /g_eMMCDrv.u32_EraseUnitSize;
        if(u32_i)
        {
            u32_err = eMMC_EraseCMDSeq(
                (u32_eMMCBlkAddr_start+u32_SectorCnt),
                (u32_eMMCBlkAddr_start+u32_SectorCnt)+u32_i*g_eMMCDrv.u32_EraseUnitSize);
            if(eMMC_ST_SUCCESS != u32_err){
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EraseCMDSeq fail 1, %Xh\n", u32_err);
                return u32_err;
            }
        }

        // erase blocks after EraseUnitSize
        u32_eMMCBlkAddr_start =
            (u32_eMMCBlkAddr_start+u32_SectorCnt) + u32_i*g_eMMCDrv.u32_EraseUnitSize;

        while(u32_eMMCBlkAddr_start < u32_eMMCBlkAddr_end)
        {
            u32_j = ((u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start)<<eMMC_SECTOR_512BYTE_BITS)>eMMC_SECTOR_BUF_BYTECTN?
                eMMC_SECTOR_BUF_BYTECTN:((u32_eMMCBlkAddr_end-u32_eMMCBlkAddr_start)<<eMMC_SECTOR_512BYTE_BITS);

            u32_err = eMMC_WriteData(gau8_eMMC_SectorBuf, u32_j, u32_eMMCBlkAddr_start);
            if(eMMC_ST_SUCCESS != u32_err){
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: WriteData fail 1, %Xh\n", u32_err);
                return u32_err;
            }
            u32_eMMCBlkAddr_start += u32_j>>eMMC_SECTOR_512BYTE_BITS;
        }
    }

    LABEL_END_OF_ERASE:
    return u32_err;
    #else
    return tSD_EraseCMDSeq(u32_eMMCBlkAddr_start, u32_eMMCBlkAddr_end);
    #endif
}

// ok: return 0
U32 eMMC_WriteData(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
    U32 u32_err;
    eMMC_LockFCIE(NULL);
    #if defined(MSOS_TYPE_ECOS)
    u32_BlkAddr += eMMC_TOTAL_RESERVED_BLK_CNT;
    #endif
    u32_err = eMMC_WriteData_Ex(pu8_DataBuf, u32_DataByteCnt, u32_BlkAddr);
    eMMC_UnlockFCIE(NULL);
    return u32_err;
}

U32 eMMC_WriteData_Ex(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
    U32 u32_err=eMMC_ST_SUCCESS;
    volatile U16 u16_BlkCnt;

    // check if eMMC Init
    if(eMMC_NOT_READY_MARK == sgu32_IfReadyGuard)
    {
        u32_err = eMMC_Init();
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC not ready (init) \n");
            return eMMC_ST_ERR_NOT_INIT;
        }
    }

    if(NULL == pu8_DataBuf)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: w data buf is NULL: %Xh \n", (U32)pu8_DataBuf);
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    // check if u32_DataByteCnt is 512B boundary
    if(u32_DataByteCnt & (eMMC_SECTOR_512BYTE-1))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: data not 512B boundary \n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    if(u32_BlkAddr + (u32_DataByteCnt>>9) > g_eMMCDrv.u32_SEC_COUNT)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: invalid data range, %Xh > %Xh \n",
            u32_BlkAddr + (u32_DataByteCnt>>9), g_eMMCDrv.u32_SEC_COUNT);
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    // write data
    while(u32_DataByteCnt)
    {
        if(u32_DataByteCnt > eMMC_SECTOR_512BYTE)
        {
            if((u32_DataByteCnt>>eMMC_SECTOR_512BYTE_BITS) < BIT_SD_JOB_BLK_CNT_MASK)
                u16_BlkCnt = (u32_DataByteCnt>>eMMC_SECTOR_512BYTE_BITS);
            else
                u16_BlkCnt = BIT_SD_JOB_BLK_CNT_MASK;

            u32_err = eMMC_CMD25(u32_BlkAddr, pu8_DataBuf, u16_BlkCnt);
        }
        else
        {
            u16_BlkCnt = 1;
            u32_err = eMMC_CMD24(u32_BlkAddr, pu8_DataBuf);
        }

        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: W fail: %Xh\n", u32_err);
            g_eMMCDrv.u32_LastErrCode = u32_err;
            break;
        }

        u32_BlkAddr += u16_BlkCnt;
        pu8_DataBuf += u16_BlkCnt << eMMC_SECTOR_512BYTE_BITS;
        u32_DataByteCnt -= u16_BlkCnt << eMMC_SECTOR_512BYTE_BITS;
    }

    return u32_err;
}


// =======================================================
// u32_DataByteCnt: has to be 512B-boundary !
// =======================================================
// ok: return 0
U32 eMMC_ReadData(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
    U32 u32_err;
    eMMC_LockFCIE(NULL);
    #if defined(MSOS_TYPE_ECOS)
    u32_BlkAddr += eMMC_TOTAL_RESERVED_BLK_CNT;
    #endif
    u32_err = eMMC_ReadData_Ex(pu8_DataBuf, u32_DataByteCnt, u32_BlkAddr);
    eMMC_UnlockFCIE(NULL);
    return u32_err;
}

U32 eMMC_ReadData_Ex(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
    U32 u32_err;
    volatile U16 u16_BlkCnt;
    U8  u8_IfNotCacheLineAligned=0;

    //eMMC_debug(eMMC_DEBUG_LEVEL,1,"\n");

    // check if eMMC Init
    if(eMMC_NOT_READY_MARK == sgu32_IfReadyGuard)
    {
        u32_err = eMMC_Init();
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC not ready (init) \n");
            return eMMC_ST_ERR_NOT_INIT;
        }
    }
    // check if u32_DataByteCnt is 512B boundary
    if(u32_DataByteCnt & (eMMC_SECTOR_512BYTE-1))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: data not 512B boundary \n");
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    if(u32_BlkAddr + (u32_DataByteCnt>>9) > g_eMMCDrv.u32_SEC_COUNT)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: invalid data range, %Xh > %Xh \n",
            u32_BlkAddr + (u32_DataByteCnt>>9), g_eMMCDrv.u32_SEC_COUNT);
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    // read data
    // first 512 bytes, special handle if not cache line aligned
    if((U32)pu8_DataBuf & (eMMC_CACHE_LINE-1))
    {
        #if 0
        eMMC_debug(eMMC_DEBUG_LEVEL_WARNING,1,
            "eMMC Warn: R, buffer not Cache Line aligned: %Xh \n",
            (U32)pu8_DataBuf);
        #endif

        u32_err = eMMC_CMD17(u32_BlkAddr, gau8_eMMC_SectorBuf);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: R fail.0: %Xh\n", u32_err);
            g_eMMCDrv.u32_LastErrCode = u32_err;
            return u32_err;
        }
        memcpy(pu8_DataBuf, gau8_eMMC_SectorBuf, eMMC_SECTOR_512BYTE);
        u32_BlkAddr += 1;
        pu8_DataBuf += eMMC_SECTOR_512BYTE;
        u32_DataByteCnt -= eMMC_SECTOR_512BYTE;

        // last 512B must be not cache line aligned,
        // reserved for last eMMC_CMD17_CIFD
        if(u32_DataByteCnt){
            u8_IfNotCacheLineAligned = 1;
            u32_DataByteCnt -= eMMC_SECTOR_512BYTE;
        }
    }

    while(u32_DataByteCnt)
    {
        if(u32_DataByteCnt > eMMC_SECTOR_512BYTE)
        {
            if((u32_DataByteCnt>>eMMC_SECTOR_512BYTE_BITS) < BIT_SD_JOB_BLK_CNT_MASK)
                u16_BlkCnt = (u32_DataByteCnt>>eMMC_SECTOR_512BYTE_BITS);
            else
                u16_BlkCnt = BIT_SD_JOB_BLK_CNT_MASK;

            u32_err = eMMC_CMD18(u32_BlkAddr, pu8_DataBuf, u16_BlkCnt);
        }
        else
        {
            u16_BlkCnt = 1;
            u32_err = eMMC_CMD17(u32_BlkAddr, pu8_DataBuf);
        }

        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: R fail.1: %Xh\n", u32_err);
            g_eMMCDrv.u32_LastErrCode = u32_err;
            break;
        }

        u32_BlkAddr += u16_BlkCnt;
        pu8_DataBuf += u16_BlkCnt << eMMC_SECTOR_512BYTE_BITS;
        u32_DataByteCnt -= u16_BlkCnt << eMMC_SECTOR_512BYTE_BITS;
    }

    // last 512 bytes, special handle if not cache line aligned
    if(u8_IfNotCacheLineAligned)
    {
        u32_err = eMMC_CMD17(u32_BlkAddr, gau8_eMMC_SectorBuf);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: R fail.2: %Xh\n", u32_err);
            g_eMMCDrv.u32_LastErrCode = u32_err;
        }
        memcpy(pu8_DataBuf, gau8_eMMC_SectorBuf, eMMC_SECTOR_512BYTE);
    }

    return u32_err;
}


U32  eMMC_GetCapacity(U32 *pu32_TotalSectorCnt) // 1 sector = 512B
{
    U32 u32_err;

    eMMC_LockFCIE(NULL);
    // check if eMMC Init
    if(eMMC_NOT_READY_MARK == sgu32_IfReadyGuard)
    {
        u32_err = eMMC_Init();
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC not ready (init) \n");
            eMMC_UnlockFCIE(NULL);
            return eMMC_ST_ERR_NOT_INIT;
        }
    }

    *pu32_TotalSectorCnt = g_eMMCDrv.u32_SEC_COUNT;
    #if defined(MSOS_TYPE_ECOS)
    *pu32_TotalSectorCnt -= eMMC_TOTAL_RESERVED_BLK_CNT;
    #endif
    eMMC_UnlockFCIE(NULL);
    return eMMC_ST_SUCCESS;
}

// pu8_CID needs to hold 16 bytes
U32 eMMC_GetCID(U8 *pu8_CID)
{
    if(NULL==pu8_CID)
        return eMMC_ST_ERR_INVALID_PARAM;

    memcpy(pu8_CID, &g_eMMCDrv.au8_CID[1], 15);
    pu8_CID[15] = 0; // no CRC
    return eMMC_ST_SUCCESS;
}

  #if defined(eMMC_FCIE_LINUX_DRIVER) && eMMC_FCIE_LINUX_DRIVER
U32 eMMC_SearchDevNodeStartSector(void)
{
    U32 u32_err;
    volatile U16 u16_PartIdx;
    eMMC_PNI_t *pPartInfo = (eMMC_PNI_t*)gau8_eMMC_PartInfoBuf;

    u32_err = eMMC_CheckIfReady();
    if(eMMC_ST_SUCCESS != u32_err){
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: init fail: %Xh\n", u32_err);
        return u32_err;
    }

    u32_err = eMMC_GetPartitionIndex(eMMC_PART_DEV_NODE, 0, &u16_PartIdx);
    if(eMMC_ST_SUCCESS != u32_err){
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: GetPartitionIndex fail: %Xh\n", u32_err);
        return u32_err;
    }

    g_eMMCDrv.u32_PartDevNodeStartSector = pPartInfo->records[u16_PartIdx].u16_StartBlk;
    g_eMMCDrv.u32_PartDevNodeStartSector *= pPartInfo->u16_BlkPageCnt;
    g_eMMCDrv.u16_PartDevNodeSectorCnt = pPartInfo->records[u16_PartIdx].u16_BlkCnt;
    g_eMMCDrv.u16_PartDevNodeSectorCnt *= pPartInfo->u16_BlkPageCnt;

    return eMMC_ST_SUCCESS;

}

  #endif
#endif

