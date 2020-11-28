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

#ifdef IP_FCIE_VERSION_5

#ifdef STATIC_RELIABLE_TEST
#include "drvWDT.h"
#include "MsCommon.h"
#include "drvPM.h"
#endif

#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER

//========================================================
// HAL pre-processors
//========================================================
#if IF_FCIE_SHARE_IP
    // re-config FCIE3 for NFIE mode
    #define eMMC_RECONFIG()       //eMMC_ReConfig();
#else
    // NULL to save CPU a JMP/RET time
    #define eMMC_RECONFIG()
#endif


#if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
    #define eMMC_KEEP_RSP(pu8_OneRspBuf, u8_CmdIdx)         \
        if(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_RSPFROMRAM_SAVE)\
            eMMC_KeepRsp(pu8_OneRspBuf, u8_CmdIdx)
#else
    #define eMMC_KEEP_RSP(pu8_OneRspBuf, u8_CmdIdx)  // NULL to save CPU a JMP/RET time
#endif


#define eMMC_FCIE_CLK_DIS()    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_CLK_EN)

#define eMMC_CMD1_RETRY_CNT    0x8000
#define eMMC_CMD3_RETRY_CNT    0x5


//========================================================
// HAL APIs
//========================================================
U32 eMMC_FCIE_WaitEvents(U32 u32_RegAddr, U16 u16_Events, U32 u32_MicroSec)
{
    //eMMC_debug(0, 0, "\033[32m%s\033[m\n", __FUNCTION__);
    #if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
    return eMMC_WaitCompleteIntr(u32_RegAddr, u16_Events, u32_MicroSec);
    #else
    return eMMC_FCIE_PollingEvents(u32_RegAddr, u16_Events, u32_MicroSec);
    #endif
}

U32 eMMC_FCIE_PollingEvents(U32 u32_RegAddr, U16 u16_Events, U32 u32_MicroSec)
{
    volatile U32 u32_i, u32_DelayX;
    volatile U16 u16_val;

    if(u32_MicroSec > HW_TIMER_DELAY_100us)
    {
        u32_DelayX = HW_TIMER_DELAY_100us/HW_TIMER_DELAY_1us;
        u32_MicroSec /= u32_DelayX;
    }
    else
        u32_DelayX = 1;

    for(u32_i=0; u32_i<u32_MicroSec; u32_i++)
    {
        eMMC_CheckPowerCut();
        eMMC_hw_timer_delay(HW_TIMER_DELAY_1us*u32_DelayX);
        REG_FCIE_R(u32_RegAddr, u16_val);
        if(u16_Events == (u16_val & u16_Events))
            break;
    }

    if(u32_i == u32_MicroSec)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: %u us, Reg.%04Xh: %04Xh, but wanted: %04Xh\n",
            u32_MicroSec*u32_DelayX,
            (u32_RegAddr-FCIE_MIE_EVENT)>>REG_OFFSET_SHIFT_BITS,
            u16_val, u16_Events);

        return eMMC_ST_ERR_TIMEOUT_WAIT_REG0;
    }

    return eMMC_ST_SUCCESS;

}


static U32 gu32Fcie5DebugBus[4];

static char *gStrDebugMode[] = {"CMD state",
                                "FIFO status",
                                "ADMA Address",
                                "ADMA blk cnt"};

//1: CMDstate
//2: {FIFOsts, WRstate, RDstate}l
//3: ADMA Address
//4: ADMA block cnt

void eMMC_FCIE_DumpDebugBus(void)
{
    U32 u32_reg;
    U16 u16_i;

    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n\n");
    eMMC_debug(eMMC_DEBUG_LEVEL, 1, "\n");

    REG_FCIE_CLRBIT(FCIE_EMMC_DEBUG_BUS1, BIT_DEBUG_MODE_MSK);
    REG_FCIE_SETBIT(FCIE_EMMC_DEBUG_BUS1, BIT_DEBUG_MODE_SET);

    for(u16_i=0; u16_i<4; u16_i++)
    {
        REG_FCIE_CLRBIT(FCIE_TEST_MODE, BIT_DEBUG_MODE_MASK);
        REG_FCIE_SETBIT(FCIE_TEST_MODE, (u16_i+1)<<BIT_DEBUG_MODE_SHIFT);

        eMMC_debug(1, 0, "0x15 = %Xh, ", REG_FCIE(FCIE_TEST_MODE));
        REG_FCIE_R(FCIE_EMMC_DEBUG_BUS0, u32_reg);
        eMMC_debug(1, 0, "0x38 = %Xh, ", u32_reg);
        gu32Fcie5DebugBus[u16_i] = u32_reg;

        REG_FCIE_R(FCIE_EMMC_DEBUG_BUS1, u32_reg);
        eMMC_debug(1, 0, "0x39 = %Xh\n", u32_reg);
        gu32Fcie5DebugBus[u16_i] |= (u32_reg&0x00FF)<<16;
    }

    for(u16_i=0; u16_i<4; u16_i++)
    {
        eMMC_debug(1, 0, "%s:\t %06Xh\n", gStrDebugMode[u16_i], gu32Fcie5DebugBus[u16_i]);
    }

    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n");

}


//static U16 sgau16_eMMCDebugReg[100];


void eMMC_FCIE_DumpRegisterBank(U32 u32Bank, U16 u16WordCount)
{
    U16 u16_i;
    volatile U16 u16_reg;

    for(u16_i=0 ; u16_i<u16WordCount; u16_i++)
    {
        if(0 == u16_i%8)
            eMMC_debug(1, 0, "\n%02Xh:| ", u16_i);

        REG_FCIE_R(GET_REG_ADDR(u32Bank, u16_i), u16_reg);
        eMMC_debug(1, 0, "%04Xh ", u16_reg);
    }
    eMMC_debug(1, 0, "\n");
}

void eMMC_FCIE_DumpRegisters(void)
{
    eMMC_debug(1, 0, "\nfcie reg:");
    eMMC_FCIE_DumpRegisterBank(FCIE_REG_BASE_ADDR, 0x40);

    eMMC_debug(1, 0, "\nchiptop reg:");
    eMMC_FCIE_DumpRegisterBank(PAD_CHIPTOP_BASE, 0x80);

    eMMC_debug(1, 0, "\nemmc_pll reg:");
    eMMC_FCIE_DumpRegisterBank(EMMC_PLL_BASE, 0x80);

    eMMC_debug(1, 0, "\nclkgen reg:");
    eMMC_FCIE_DumpRegisterBank(CLKGEN0_BASE, 0x80);

    eMMC_debug(1, 0, "\n");
}

void eMMC_FCIE_ErrHandler_Stop(void)
{
    if(0==eMMC_IF_DISABLE_RETRY())
    {
        eMMC_Dump_eMMCStatus();
        eMMC_DumpDriverStatus();
        eMMC_DumpPadClk();
        eMMC_FCIE_DumpRegisters();
        eMMC_FCIE_DumpDebugBus();
        eMMC_die("\n");
    }
    else
        eMMC_FCIE_Init();
}

void eMMC_FCIE_SymmetrySkew4(void)
{
    g_eMMCDrv.TimingTable_G_t.u8_CurSetIdx = 4-g_eMMCDrv.TimingTable_G_t.u8_CurSetIdx;
    eMMC_FCIE_ApplyTimingSet(g_eMMCDrv.TimingTable_G_t.u8_CurSetIdx);

    //eMMC_DumpTimingTable();
}

static U8 sgu8_IfNeedRestorePadType=0xFF;
U32 eMMC_FCIE_ErrHandler_Retry(void)
{
    U32 u32_err=eMMC_ST_SUCCESS;
    static U8 u8_sdr_retry_count = 0;

    eMMC_FCIE_Init();

    // -------------------------------------------------
    if(0 ==(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_INIT_DONE))
        return eMMC_ST_SUCCESS;

    // -------------------------------------------------    
    if( u8_sdr_retry_count < 2 && g_eMMCDrv.u8_PadType == FCIE_eMMC_HS400 && g_eMMCDrv.TimingTable_G_t.u8_SetCnt!= 0)
    {
        eMMC_FCIE_SymmetrySkew4();
        ++u8_sdr_retry_count;
    }
    else
    {
        if(!eMMC_IF_NORMAL_SDR())
        {
            sgu8_IfNeedRestorePadType = g_eMMCDrv.u8_PadType;
            u32_err = eMMC_FCIE_EnableSDRMode();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EnableSDRModefail: %Xh\n", u32_err);
            }
            u8_sdr_retry_count = 0;
        }
    }

    eMMC_debug(eMMC_DEBUG_LEVEL_WARNING,0,
        "eMMC Warn: slow clk to %u.%uMHz, %Xh\n", 
            g_eMMCDrv.u32_ClkKHz/1000, (g_eMMCDrv.u32_ClkKHz%1000)/100, g_eMMCDrv.u16_ClkRegVal);

    return u32_err;
}

void eMMC_FCIE_ErrHandler_RestoreClk(void)
{
    if(0xFF != sgu8_IfNeedRestorePadType)
    {
        U32 u32_err;
        u32_err = eMMC_FCIE_EnableFastMode_Ex(sgu8_IfNeedRestorePadType);
        if(u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EnableFastMode_Ex fail, %Xh\n", u32_err);
            return;
        }
        sgu8_IfNeedRestorePadType = 0xFF;
    }
}


void eMMC_FCIE_ErrHandler_ReInit(void)
{
    U32 u32_err;
    U32 u32_DrvFlag = g_eMMCDrv.u32_DrvFlag;
    U16 u16_Reg10 = g_eMMCDrv.u16_Reg10_Mode;
    U8  u8_OriPadType = g_eMMCDrv.u8_PadType;

    u32_err = eMMC_FCIE_Init();
    if(u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: FCIE_Init fail, %Xh\n", u32_err);
        goto LABEL_REINIT_END;
    }

    g_eMMCDrv.u32_DrvFlag = 0;
    eMMC_PlatformInit();
    u32_err = eMMC_Identify();
    if(u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: Identify fail, %Xh\n", u32_err);
        goto LABEL_REINIT_END;
    }

    eMMC_clock_setting(FCIE_SLOW_CLK);

    u32_err = eMMC_CMD3_CMD7(g_eMMCDrv.u16_RCA, 7);
    if(u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: CMD7 fail, %Xh\n", u32_err);
        goto LABEL_REINIT_END;
    }

    u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HIGH);
    if(eMMC_ST_SUCCESS != u32_err)
        goto  LABEL_REINIT_END;

    // ---------------------------------
    g_eMMCDrv.u32_DrvFlag = u32_DrvFlag;
    if(eMMC_IF_NORMAL_SDR())
    {
        u32_err = eMMC_FCIE_EnableSDRMode();
        if(u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EnableSDRMode fail, %Xh\n", u32_err);
            goto LABEL_REINIT_END;
        }
    }
    else
    {
        u32_err = eMMC_FCIE_EnableFastMode_Ex(u8_OriPadType);
        if(u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EnableFastMode_Ex fail, %Xh\n", u32_err);
            goto LABEL_REINIT_END;
        }
    }
    g_eMMCDrv.u16_Reg10_Mode = u16_Reg10;
    REG_FCIE_W(FCIE_SD_MODE, g_eMMCDrv.u16_Reg10_Mode);

    LABEL_REINIT_END:
    if(u32_err)
        eMMC_die("\n");
}



U32 eMMC_FCIE_Reset(void)
{
    U16 u16_clk = g_eMMCDrv.u16_ClkRegVal;
    U16 u16Cnt = 0;

    REG_FCIE_W(FCIE_RESERVED_FOR_SW, eMMC_DRIVER_VERSION);
    //eMMC_debug(1, 1, "1: %Xh\n", REG_FCIE(FCIE_RESERVED_FOR_SW));
    
    REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_JOB_START); // clear for safe

    eMMC_clock_setting(gau8_FCIEClkSel[0]); // speed up FCIE reset done

    REG_FCIE_CLRBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n); /* active low */

    while(1)
    {
        if((REG_FCIE(FCIE_RST)&BIT_RST_STS_MASK)==BIT_RST_STS_MASK); // reset success
            break;
        eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
        if(u16Cnt++>=1000)
            eMMC_debug(1, 0, "eMMC Err: FCIE reset fail!\n");
    }

    REG_FCIE_SETBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n);

    eMMC_clock_setting(u16_clk);
    //eMMC_debug(1, 1, "2: %Xh\n", REG_FCIE(FCIE_RESERVED_FOR_SW));
    
    return 0;

}


U32 eMMC_FCIE_Init(void)
{
    U32 u32_err;

    eMMC_PlatformResetPre();

    // ------------------------------------------
    #if 0 //eMMC_TEST_IN_DESIGN
    {
        volatile U16 u16_i, u16_reg;
        // check timer clock
        eMMC_debug(eMMC_DEBUG_LEVEL, 1, "Timer test, for 6 sec: ");
        for(u16_i = 6; u16_i > 0; u16_i--)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL, 1, "%u ", u16_i);
            eMMC_hw_timer_delay(HW_TIMER_DELAY_1s);
        }
        eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n");

        // check FCIE reg.30h
        REG_FCIE_R(FCIE_TEST_MODE, u16_reg);
        if(0)//u16_reg & BIT_FCIE_BIST_FAIL) /* Andersen: "don't care." */
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Reg0x30h BIST fail: %04Xh \r\n", u16_reg);
            return eMMC_ST_ERR_BIST_FAIL;
        }
        if(u16_reg & BIT_FCIE_DEBUG_MODE_MASK)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Reg0x30h Debug Mode: %04Xh \r\n", u16_reg);
            return eMMC_ST_ERR_DEBUG_MODE;
        }

        u32_err = eMMC_FCIE_Reset();
        if(eMMC_ST_SUCCESS != u32_err){
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: reset fail\n");
            eMMC_FCIE_ErrHandler_Stop();
            return u32_err;
        }
    }
    #endif // eMMC_TEST_IN_DESIGN

    // ------------------------------------------
    u32_err = eMMC_FCIE_Reset();
    if(eMMC_ST_SUCCESS != u32_err){
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: reset fail: %Xh\n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        return u32_err;
    }

    REG_FCIE_W(FCIE_MIE_INT_EN, 0);
    REG_FCIE_W(FCIE_MIE_FUNC_CTL, BIT_EMMC_EN);
    REG_FCIE_CLRBIT(FCIE_CMD_RSP_SIZE, BIT_CMD_SIZE_MASK);
    REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, (eMMC_CMD_BYTE_CNT)<< BIT_CMD_SIZE_SHIFT);   
    REG_FCIE_W(FCIE_SD_CTRL, 0);
    REG_FCIE_W(FCIE_SD_MODE, g_eMMCDrv.u16_Reg10_Mode);
    // default sector size: 0x200
    REG_FCIE_W(FCIE_BLK_SIZE,  eMMC_SECTOR_512BYTE);

    REG_FCIE_W(FCIE_RSP_SHIFT_CNT, 0);
    REG_FCIE_W(FCIE_RX_SHIFT_CNT, 0);
 
    REG_FCIE_W(FCIE_WR_SBIT_TIMER, 0);
    REG_FCIE_W(FCIE_RD_SBIT_TIMER, 0);

    eMMC_FCIE_ClearEvents();
    eMMC_PlatformResetPost();

    return eMMC_ST_SUCCESS; // ok
}

void eMMC_FCIE_ClearEvents(void)
{
    volatile U16 u16_reg;
    while(1){
        REG_FCIE_W(FCIE_MIE_EVENT, BIT_ALL_CARD_INT_EVENTS);
        REG_FCIE_R(FCIE_MIE_EVENT, u16_reg);
        if(0==(u16_reg&BIT_ALL_CARD_INT_EVENTS))
            break;
        REG_FCIE_W(FCIE_MIE_EVENT, 0);
        REG_FCIE_W(FCIE_MIE_EVENT, 0);
    }
    REG_FCIE_W1C(FCIE_SD_STATUS, BIT_SD_FCIE_ERR_FLAGS); // W1C
}


void eMMC_FCIE_ClearEvents_Reg0(void)
{
    volatile U16 u16_reg;

    while(1){
        REG_FCIE_W(FCIE_MIE_EVENT, BIT_ALL_CARD_INT_EVENTS);
        REG_FCIE_R(FCIE_MIE_EVENT, u16_reg);
        if(0==(u16_reg&BIT_ALL_CARD_INT_EVENTS))
            break;
        REG_FCIE_W(FCIE_MIE_EVENT, 0);
        REG_FCIE_W(FCIE_MIE_EVENT, 0);
    }
}

U32 eMMC_FCIE_WaitD0High_Ex(U32 u32_us)
{
    volatile U32 u32_cnt;
    volatile U16 u16_read0=0, u16_read1=0;
    
    for(u32_cnt=0; u32_cnt < u32_us; u32_cnt++)
    {
        REG_FCIE_R(FCIE_SD_STATUS, u16_read0);
        eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
        REG_FCIE_R(FCIE_SD_STATUS, u16_read1);
    
        if((u16_read0&BIT_SD_CARD_BUSY) ==0 && (u16_read1&BIT_SD_CARD_BUSY) ==0)
            break;
    
        if(u32_cnt > 500 && u32_us-u32_cnt > 1000)
        {
            eMMC_hw_timer_sleep(1);
            u32_cnt += 1000-2;
        }
    }
    
    return u32_cnt;

}

U32 eMMC_FCIE_WaitD0High(U32 u32_us)
{
    volatile U32 u32_cnt;

    REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_CLK_EN);
    u32_cnt = eMMC_FCIE_WaitD0High_Ex(u32_us);

    if(u32_us == u32_cnt)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: wait D0 H timeout %u us\n", u32_cnt);
        return eMMC_ST_ERR_TIMEOUT_WAITD0HIGH;
    }
//  eMMC_hw_timer_delay(HW_TIMER_DELAY_1s  * 2);

    return eMMC_ST_SUCCESS;

}

U32 eMMC_FCIE_SendCmd
(
    U16 u16_Mode, U16 u16_Ctrl, U32 u32_Arg, U8 u8_CmdIdx, U8 u8_RspByteCnt
)
{
    U32 u32_err, u32_Timeout = TIME_WAIT_DAT0_HIGH;
    U16 au16_tmp[3];

    if(38 == u8_CmdIdx)
        u32_Timeout = TIME_WAIT_ERASE_DAT0_HIGH;

    #if 0
    eMMC_debug(0,1,"\n");
    eMMC_debug(0,1,"cmd:%u, arg:%Xh, rspb:%Xh, mode:%Xh, ctrl:%Xh \n",
        u8_CmdIdx, u32_Arg, u8_RspByteCnt, u16_Mode, u16_Ctrl);
    #endif
    REG_FCIE_CLRBIT(FCIE_CMD_RSP_SIZE, BIT_RSP_SIZE_MASK);
    REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, u8_RspByteCnt & BIT_RSP_SIZE_MASK);
    REG_FCIE_W(FCIE_SD_MODE, u16_Mode);
    // set cmd
    //   CIFC(0) = 39:32 | 47:40
    //   CIFC(1) = 23:16 | 31:24
    //   CIFC(2) = (CIFC(2) & 0xFF00) | 15:8, ignore (CRC7 | end_bit).
    REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);
    while(1)
    {
        REG_FCIE_W(FCIE_CMDFIFO_ADDR(0),((u32_Arg>>24)<<8) | (0x40|u8_CmdIdx));
        REG_FCIE_W(FCIE_CMDFIFO_ADDR(1), (u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF));
        REG_FCIE_W(FCIE_CMDFIFO_ADDR(2),  u32_Arg&0xFF);

        REG_FCIE_R(FCIE_CMDFIFO_ADDR(0),au16_tmp[0]);
        REG_FCIE_R(FCIE_CMDFIFO_ADDR(1),au16_tmp[1]);
        REG_FCIE_R(FCIE_CMDFIFO_ADDR(2),au16_tmp[2]);

        if(au16_tmp[0] == (((u32_Arg>>24)<<8) | (0x40|u8_CmdIdx))&&
            au16_tmp[1] == ((u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF))&&
            au16_tmp[2] == (u32_Arg&0xFF))
            break;
    }
    REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

    if(12 != u8_CmdIdx)
    {
        u32_err = eMMC_FCIE_WaitD0High(u32_Timeout);
        if(eMMC_ST_SUCCESS != u32_err)
            goto LABEL_SEND_CMD_ERROR;
    }

    if((u8_CmdIdx==12)||(u8_CmdIdx==24)||(u8_CmdIdx==25))
    {
        eMMC_CheckPowerCut();
    }

    REG_FCIE_W(FCIE_SD_CTRL, u16_Ctrl|BIT_JOB_START);

    #if defined(ENABLE_eMMC_INTERRUPT_MODE) && ENABLE_eMMC_INTERRUPT_MODE
    REG_FCIE_W(FCIE_MIE_INT_EN, BIT_CMD_END);
    #endif
    if(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_RSP_WAIT_D0H){
        u32_err = eMMC_FCIE_WaitD0High(u32_Timeout);
        if(eMMC_ST_SUCCESS != u32_err)
            goto LABEL_SEND_CMD_ERROR;
    }

    // wait event
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_CMD_END, TIME_WAIT_CMDRSP_END);

    LABEL_SEND_CMD_ERROR:
    return u32_err;


}

void HalFcie_SetFlag4Kernel2RuneMMC(void)
{
    REG_FCIE_CLRBIT(FCIE_MIE_FUNC_CTL, BIT_KERN_CHK_NAND_EMMC_MSK);
    REG_FCIE_SETBIT(FCIE_MIE_FUNC_CTL, BIT_KERN_EMMC);
}

U8 HalFcie_CheckIfeMMCRun4Kernel(void)
{
    #if defined(CONFIG_MSTAR_ARM_BD_FPGA)

        return 1;

    #else

        u16 u16_regval = 0;

        u16_regval = REG_FCIE(FCIE_MIE_FUNC_CTL);

        if( (u16_regval & BIT_KERN_CHK_NAND_EMMC) == BIT_KERN_CHK_NAND_EMMC )
        {
            return ( (u16_regval & BIT_KERN_EMMC) != BIT_KERN_EMMC ) ? 0 : 1;
        }
        return 0;

    #endif
}


void eMMC_FCIE_GetCMDFIFO(U16 u16_WordPos, U16 u16_WordCnt, U16 *pu16_Buf)
{
    U16 u16_i;

    if(u16_WordPos==0x55) eMMC_debug(1, 1, "\n"); // remove warning

    for(u16_i=0; u16_i<u16_WordCnt; u16_i++)
        REG_FCIE_R(FCIE_CMDFIFO_ADDR(u16_i), pu16_Buf[u16_i]);
}

U32 eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec)
{
    volatile U32 u32_Count;
    volatile U16 u16_Reg;

    for (u32_Count=0; u32_Count < u32_MicroSec; u32_Count++)
    {
        REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
        if ((u16_Reg & u16_WaitEvent) == u16_WaitEvent)
            break;

        eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
    }
    if (u32_Count >= u32_MicroSec)
    {
        REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "CIFD Event Timout %X\n", u16_Reg);
    }
    return u32_Count;
}

U32 eMMC_WaitSetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt)
{
    U16 u16_i, *pu16_Data = (U16*)pu8_DataBuf;

    if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
    {
        return eMMC_ST_ERR_INVALID_PARAM;
    }

    for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
        REG_FCIE_W(NC_RBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

    REG_FCIE_SETBIT(NC_CIFD_EVENT, BIT_RBUF_FULL_TRI);

    if (eMMC_WaitCIFD_Event(BIT_RBUF_EMPTY, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: set CIFD timeout 0, ErrCode:%Xh\r\n", eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT);
        return eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT; // timeout
    }

    REG_FCIE_SETBIT(NC_CIFD_EVENT, BIT_RBUF_EMPTY); // W1C

    return eMMC_ST_SUCCESS;
}


U32 eMMC_WaitGetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt)
{
    U16 u16_i, *pu16_Data = (U16*)pu8_DataBuf;

    //eMMC_debug(1, 1, "wait 64 bytes CIFD and copy to %08X\n", (U32)pu32_DataBuf);

    if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
    {
        return eMMC_ST_ERR_INVALID_PARAM;
    }
    if (eMMC_WaitCIFD_Event(BIT_WBUF_FULL, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
    {
        eMMC_debug(1, 1, "eMMC Err: get CIFD timeout 0, ErrCode:%Xh\r\n", eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT);
        return eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT; // timeout
    }

    for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
        REG_FCIE_R(NC_WBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

    REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_FULL); // W1C

    REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_EMPTY_TRI);

    return eMMC_ST_SUCCESS;
}

//===================================================
#if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
void eMMC_KeepRsp(U8 *pu8_OneRspBuf, U8 u8_CmdIdx)
{
    U16 u16_idx;
    U8  u8_ByteCnt;

    u16_idx = u8_CmdIdx * eMMC_CMD_BYTE_CNT;
    u8_ByteCnt = eMMC_CMD_BYTE_CNT;

    if(u8_CmdIdx > 10)
        u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*3;
    else if(u8_CmdIdx > 9)
        u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*2;
    else if(u8_CmdIdx > 2)
        u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*1;

    if(10==u8_CmdIdx || 9==u8_CmdIdx || 2==u8_CmdIdx)
        u8_ByteCnt = eMMC_R2_BYTE_CNT;

    if(u16_idx+u8_ByteCnt > eMMC_SECTOR_512BYTE-4) // last 4 bytes are CRC
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: KeepRsp over 512B, %Xh, %Xh, %Xh\n",
            u8_CmdIdx, u16_idx, u8_ByteCnt);
        eMMC_die("\n"); // should be system fatal error, not eMMC driver
    }

    memcpy(g_eMMCDrv.au8_AllRsp + u16_idx, pu8_OneRspBuf, u8_ByteCnt);

}


U32 eMMC_ReturnRsp(U8 *pu8_OneRspBuf, U8 u8_CmdIdx)
{
    U16 u16_idx;
    U8  u8_ByteCnt;

    u16_idx = u8_CmdIdx * eMMC_CMD_BYTE_CNT;
    u8_ByteCnt = eMMC_CMD_BYTE_CNT;

    if(u8_CmdIdx > 10)
        u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*3;
    else if(u8_CmdIdx > 9)
        u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*2;
    else if(u8_CmdIdx > 2)
        u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*1;

    if(10==u8_CmdIdx || 9==u8_CmdIdx || 2==u8_CmdIdx)
        u8_ByteCnt = eMMC_R2_BYTE_CNT;

    if(u16_idx+u8_ByteCnt > eMMC_SECTOR_512BYTE-4) // last 4 bytes are CRC
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: KeepRsp over 512B, %Xh, %Xh, %Xh\n",
            u8_CmdIdx, u16_idx, u8_ByteCnt);
        return eMMC_ST_ERR_NO_RSP_IN_RAM;
    }

    if(0 == g_eMMCDrv.au8_AllRsp[u16_idx])
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_LOW,1,"eMMC Info: no rsp, %u %u \n", u8_CmdIdx, u16_idx);
        return eMMC_ST_ERR_NO_RSP_IN_RAM;
    }

    memcpy(pu8_OneRspBuf, g_eMMCDrv.au8_AllRsp + u16_idx, u8_ByteCnt);

    return eMMC_ST_SUCCESS;
}


// -------------------------------
U32 eMMC_SaveRsp(void)
{

    return eMMC_ST_SUCCESS;
}

U32 eMMC_SaveDriverContext(void)
{

    return eMMC_ST_SUCCESS;
}


U32 eMMC_LoadRsp(U8 *pu8_AllRspBuf)
{

    return eMMC_ST_SUCCESS;
}

U32 eMMC_LoadDriverContext(U8 *pu8_Buf)
{

    return eMMC_ST_SUCCESS;
}

#endif
//========================================================
// Send CMD HAL APIs
//========================================================
U32 eMMC_Identify(void)
{
    U32 u32_err = eMMC_ST_SUCCESS;
    U16 u16_i, u16_retry=0;

    g_eMMCDrv.u16_RCA=1;
    g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_1;
    g_eMMCDrv.u16_Reg10_Mode &= ~BIT_SD_DATA_WIDTH_MASK;

    LABEL_IDENTIFY_CMD0:
    if(eMMC_ST_SUCCESS != eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: WaitD0High TO\n");
        eMMC_FCIE_ErrHandler_Stop();
    }
    eMMC_RST_L();  eMMC_hw_timer_sleep(1);
    eMMC_RST_H();  eMMC_hw_timer_sleep(1);

    if(u16_retry > 10)
    {
        eMMC_FCIE_ErrHandler_Stop();
        return u32_err;
    }

    if(u16_retry)
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Warn: retry: %u\n", u16_retry);

    // CMD0
    u32_err = eMMC_CMD0(0); // reset to idle state
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u16_retry++;
        goto LABEL_IDENTIFY_CMD0;
    }

    // CMD1
    for(u16_i=0; u16_i<eMMC_CMD1_RETRY_CNT; u16_i++)
    {
        //eMMC_debug(eMMC_DEBUG_LEVEL, 1, "CMD1 try: %02Xh \n", u16_i);
        u32_err = eMMC_CMD1();
        if(eMMC_ST_SUCCESS == u32_err)
            break;

        eMMC_hw_timer_sleep(2);

        if(eMMC_ST_ERR_CMD1_DEV_NOT_RDY != u32_err)
        {
            u16_retry++;
            goto LABEL_IDENTIFY_CMD0;
        }
    }

    //eMMC_debug(eMMC_DEBUG_LEVEL, 1, "CMD1 try: %02Xh \n", u16_i);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u16_retry++;
        goto LABEL_IDENTIFY_CMD0;
    }

    // CMD2
    u32_err = eMMC_CMD2();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u16_retry++;
        goto LABEL_IDENTIFY_CMD0;
    }

    // CMD3
    u32_err = eMMC_CMD3_CMD7(g_eMMCDrv.u16_RCA,3);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u16_retry++;
        g_eMMCDrv.u16_RCA++;
        goto LABEL_IDENTIFY_CMD0;
    }

    return eMMC_ST_SUCCESS;
}
U32 eMMC_ROM_BOOT_CMD0(U32 u32_Arg, U32 u32_Addr, U16 u16_BlkCnt)
{
    U32 u32_err,u32_dma_addr;
    U16 u16_mode,u16_ctrl;
    
    u16_mode = BIT_SD_DEFAULT_MODE_REG|BIT_SD_DATA_WIDTH_8|BIT_SD_DMA_R_CLK_STOP;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_DTRX_EN;

    REG_FCIE_W(FCIE_JOB_BL_CNT, u16_BlkCnt);
    u32_dma_addr = eMMC_translate_DMA_address_Ex(u32_Addr, eMMC_SECTOR_512BYTE*u16_BlkCnt);

    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, (eMMC_SECTOR_512BYTE*u16_BlkCnt) & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,(eMMC_SECTOR_512BYTE*u16_BlkCnt) >> 16);

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32_Arg, 0, 0);

    if(eMMC_ST_SUCCESS != u32_err)
        goto LABEL_END;

    // wait event
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(u16_BlkCnt>>11)));

    if(eMMC_ST_SUCCESS != u32_err)
        goto LABEL_END;

    LABEL_END:
    return u32_err;
}

U32 eMMC_CMD0(U32 u32_Arg)
{
    U32 u32_err;
    U16 u16_ctrl;
    U8  u8_retry_cmd=0;

    u16_ctrl = BIT_SD_CMD_EN;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_Arg, 0, 0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT)
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD0 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_Init();
            goto LABEL_SEND_CMD;
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD0 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }

    //eMMC_FCIE_CLK_DIS();
    return u32_err;

}

// send OCR
U32 eMMC_CMD1(void)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;


    // (sector mode | byte mode) | (3.0|3.1|3.2|3.3|3.4 V)
    u32_arg = BIT30 | (BIT23|BIT22|BIT21|BIT20|BIT19|BIT18|BIT17|BIT16|BIT15|BIT7);
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;


    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 1, eMMC_R3_BYTE_CNT);


    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Warn: CMD1 send CMD fail: %08Xh \n", u32_err);
        return u32_err;
    }

    // check status
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    // R3 has no CRC, so does not check BIT_SD_RSP_CRC_ERR
    if(u16_reg & BIT_SD_RSP_TIMEOUT)
    {
        u32_err = eMMC_ST_ERR_CMD1;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Warn: CMD1 no Rsp, Reg.12: %04Xh \n", u16_reg);

        return u32_err;
    }
    else
    {   // CMD1 ok, do things here
        eMMC_FCIE_GetCMDFIFO(0, 3, (U16*)g_eMMCDrv.au8_Rsp);
        //eMMC_dump_mem(g_eMMCDrv.au8_Rsp, eMMC_R3_BYTE_CNT);

        if(0 == (g_eMMCDrv.au8_Rsp[1] & 0x80))
            u32_err =  eMMC_ST_ERR_CMD1_DEV_NOT_RDY;
        else
        {
            g_eMMCDrv.u8_IfSectorMode = (g_eMMCDrv.au8_Rsp[1]&BIT6)>>6;
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 1);
        }
    }
    return u32_err;
}


// send CID
U32 eMMC_CMD2(void)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;

    u32_arg = 0;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_RSPR2_EN;

    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 2, eMMC_R2_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD2, %Xh \n", u32_err);
        return u32_err;
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            u32_err = eMMC_ST_ERR_CMD2;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD2 Reg.12: %04Xh\n", u16_reg);
            return u32_err;
        }
        else
        {   // CMD2 ok, do things here (get CID)
            eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CID);
            //eMMC_dump_mem(g_eMMCDrv.au8_CID, eMMC_R2_BYTE_CNT);
            eMMC_KEEP_RSP(g_eMMCDrv.au8_CID, 2);
        }
    }
    //eMMC_FCIE_CLK_DIS();
    return u32_err;
}

U32 eMMC_CMD3_CMD7(U16 u16_RCA, U8 u8_CmdIdx)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    if(7 == u8_CmdIdx)
        g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSP_WAIT_D0H;
    else{
        u8_retry_fcie = 0xF0; // CMD3: not retry
    }

    u32_arg = u16_RCA<<16;

    if(7==u8_CmdIdx && u16_RCA!=g_eMMCDrv.u16_RCA)
        u16_ctrl = BIT_SD_CMD_EN;
    else
        u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, u8_CmdIdx, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(3 == u8_CmdIdx)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD%u retry:%u, %Xh \n",
                u8_CmdIdx, u8_retry_cmd, u32_err);
            return u32_err;
        }
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD%u retry:%u, %Xh \n",
                u8_CmdIdx, u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD%u retry:%u, %Xh \n",
            u8_CmdIdx, u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {
        // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        // de-select has no rsp
        if(!(7==u8_CmdIdx && u16_RCA!=g_eMMCDrv.u16_RCA))
        {
            if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
            {
                if(3 == u8_CmdIdx)
                {
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD%u Reg.12: %04Xh, Retry: %u\n", u8_CmdIdx, u16_reg, u8_retry_fcie);
                    return u32_err;
                }
                if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
                {
                    u8_retry_fcie++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD%u Reg.12: %04Xh, Retry: %u\n", u8_CmdIdx, u16_reg, u8_retry_fcie);
                    eMMC_FCIE_ErrHandler_Retry();
                    goto LABEL_SEND_CMD;
                }

                u32_err = eMMC_ST_ERR_CMD3_CMD7;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD%u Reg.12: %04Xh, Retry: %u\n", u8_CmdIdx, u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_Stop();
            }
            else
            {   // CMD3 ok, do things here
                u32_err = eMMC_CheckR1Error();
                if(eMMC_ST_SUCCESS != u32_err)
                {
                    if(3 == u8_CmdIdx)
                    {
                        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                            "eMMC WARN: CMD%u check R1 error: %Xh, retry: %u\n",
                            u8_CmdIdx, u32_err, u8_retry_r1);
                        return u32_err;
                    }

                    if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
                    {
                        u8_retry_r1++;
                        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                            "eMMC WARN: CMD%u check R1 error: %Xh, retry: %u\n",
                            u8_CmdIdx, u32_err, u8_retry_r1);
                        eMMC_FCIE_ErrHandler_Retry();
                        goto LABEL_SEND_CMD;
                    }
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC Err: CMD%u check R1 error: %Xh, retry: %u\n",
                        u8_CmdIdx, u32_err, u8_retry_r1);
                    eMMC_FCIE_ErrHandler_Stop();
                }
                eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, u8_CmdIdx);
            }
        }
    }

    eMMC_FCIE_CLK_DIS();
    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_RSP_WAIT_D0H;
    return u32_err;

}

//------------------------------------------------
U32 eMMC_CSD_Config(void)
{
    U32 u32_err = eMMC_ST_SUCCESS;

    u32_err = eMMC_CMD9(g_eMMCDrv.u16_RCA);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    // ------------------------------
    g_eMMCDrv.u8_SPEC_VERS = (g_eMMCDrv.au8_CSD[1]&0x3C)>>2;
    g_eMMCDrv.u8_R_BL_LEN = g_eMMCDrv.au8_CSD[6] & 0xF;
    g_eMMCDrv.u8_W_BL_LEN = ((g_eMMCDrv.au8_CSD[13]&0x3)<<2)+
        ((g_eMMCDrv.au8_CSD[14]&0xC0)>>6);

    // ------------------------------
    g_eMMCDrv.u16_C_SIZE = (g_eMMCDrv.au8_CSD[7] & 3)<<10;
    g_eMMCDrv.u16_C_SIZE += g_eMMCDrv.au8_CSD[8] << 2;
    g_eMMCDrv.u16_C_SIZE +=(g_eMMCDrv.au8_CSD[9] & 0xC0) >> 6;
    if(0xFFF == g_eMMCDrv.u16_C_SIZE)
    {
        g_eMMCDrv.u32_SEC_COUNT = 0;
    }
    else
    {
        g_eMMCDrv.u8_C_SIZE_MULT = ((g_eMMCDrv.au8_CSD[10]&3)<<1)+
            ((g_eMMCDrv.au8_CSD[11]&0x80)>>7);

        g_eMMCDrv.u32_SEC_COUNT =
            (g_eMMCDrv.u16_C_SIZE+1)*
            (1<<(g_eMMCDrv.u8_C_SIZE_MULT+2))*
            ((1<<g_eMMCDrv.u8_R_BL_LEN)>>9) - 8; // -8: //Toshiba CMD18 access the last block report out of range error
    }

    //printf("g_eMMCDrv.u32_SEC_COUNT = %X\n", g_eMMCDrv.u32_SEC_COUNT);

    // ------------------------------
    g_eMMCDrv.u8_ERASE_GRP_SIZE = (g_eMMCDrv.au8_CSD[10]&0x7C)>>2;
    g_eMMCDrv.u8_ERASE_GRP_MULT = ((g_eMMCDrv.au8_CSD[10]&0x03)<<3)+
        ((g_eMMCDrv.au8_CSD[11]&0xE0)>>5);
    g_eMMCDrv.u32_EraseUnitSize = (g_eMMCDrv.u8_ERASE_GRP_SIZE+1)*
        (g_eMMCDrv.u8_ERASE_GRP_MULT+1);
    // ------------------------------
    // others
    g_eMMCDrv.u8_TAAC = g_eMMCDrv.au8_CSD[2];
    g_eMMCDrv.u8_NSAC = g_eMMCDrv.au8_CSD[3];
    g_eMMCDrv.u8_Tran_Speed = g_eMMCDrv.au8_CSD[4];
    g_eMMCDrv.u8_R2W_FACTOR = (g_eMMCDrv.au8_CSD[13]&0x1C)>>2;

    return eMMC_ST_SUCCESS;
}


// send CSD (in R2)
U32 eMMC_CMD9(U16 u16_RCA)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_cmd=0;

    u32_arg = u16_RCA<<16;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_RSPR2_EN;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 9, eMMC_R2_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD9 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD9 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD9 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_Retry();
                goto LABEL_SEND_CMD;
            }

            u32_err = eMMC_ST_ERR_CMD9;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD9 Reg.12: %04Xh, Retry fail: %u\n", u16_reg, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   // CMD2 ok, do things here
            eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CSD);
            //eMMC_dump_mem(g_eMMCDrv.au8_CSD, eMMC_R2_BYTE_CNT);
            eMMC_KEEP_RSP(g_eMMCDrv.au8_CSD, 9);
        }
    }

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}

//------------------------------------------------
U32 eMMC_ExtCSD_Config(void)
{
    U32 u32_err = eMMC_ST_SUCCESS;

    u32_err = eMMC_CMD8(gau8_eMMC_SectorBuf);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    //eMMC_dump_mem(gau8_eMMC_SectorBuf, 0x200);

    g_eMMCDrv.u32_SEC_COUNT = 0;

    //--------------------------------
    if(0 == g_eMMCDrv.u32_SEC_COUNT)
         g_eMMCDrv.u32_SEC_COUNT = ((gau8_eMMC_SectorBuf[215]<<24)|
                                   (gau8_eMMC_SectorBuf[214]<<16)|
                                   (gau8_eMMC_SectorBuf[213]<< 8)|
                                   (gau8_eMMC_SectorBuf[212])) - 8; //-8: Toshiba CMD18 access the last block report out of range error
    eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 0, "g_eMMCDrv.u32_SEC_COUNT = %X\n", g_eMMCDrv.u32_SEC_COUNT);

    //-------------------------------
    if(0 == g_eMMCDrv.u32_BOOT_SEC_COUNT)
         g_eMMCDrv.u32_BOOT_SEC_COUNT = gau8_eMMC_SectorBuf[226] * 128 * 2;

    g_eMMCDrv.u8_BOOT_SIZE_MULT = gau8_eMMC_SectorBuf[226];
    
    //--------------------------------
    if(!g_eMMCDrv.u8_BUS_WIDTH) {
        g_eMMCDrv.u8_BUS_WIDTH = gau8_eMMC_SectorBuf[183];
        switch(g_eMMCDrv.u8_BUS_WIDTH)
        {
            case 0:  g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_1;  break;
            case 1:  g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_4;  break;
            case 2:  g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_8;  break;
            default: eMMC_debug(0,1,"eMMC Err: eMMC BUS_WIDTH not support \n");
                while(1);
        }
    }
    //--------------------------------
    if(gau8_eMMC_SectorBuf[231]&BIT4) // TRIM
        g_eMMCDrv.u32_eMMCFlag |= eMMC_FLAG_TRIM;
    else
        g_eMMCDrv.u32_eMMCFlag &= ~eMMC_FLAG_TRIM;

    //--------------------------------
    if(gau8_eMMC_SectorBuf[503]&BIT0) // HPI
    {
        if(gau8_eMMC_SectorBuf[503]&BIT1)
            g_eMMCDrv.u32_eMMCFlag |= eMMC_FLAG_HPI_CMD12;
        else
            g_eMMCDrv.u32_eMMCFlag |= eMMC_FLAG_HPI_CMD13;
    }else
        g_eMMCDrv.u32_eMMCFlag &= ~(eMMC_FLAG_HPI_CMD12|eMMC_FLAG_HPI_CMD13);

    //--------------------------------
    if(gau8_eMMC_SectorBuf[166]&BIT2) // Reliable Write
        g_eMMCDrv.u16_ReliableWBlkCnt = BIT_SD_JOB_BLK_CNT_MASK;
    else
    {
        #if 0
        g_eMMCDrv.u16_ReliableWBlkCnt = gau8_eMMC_SectorBuf[222];
        #else
        if((gau8_eMMC_SectorBuf[503]&BIT0) && 1==gau8_eMMC_SectorBuf[222])
            g_eMMCDrv.u16_ReliableWBlkCnt = 1;
        else if(0==(gau8_eMMC_SectorBuf[503]&BIT0))
            g_eMMCDrv.u16_ReliableWBlkCnt = gau8_eMMC_SectorBuf[222];
        else
        {
            //eMMC_debug(0,1,"eMMC Warn: not support dynamic  Reliable-W\n");
            g_eMMCDrv.u16_ReliableWBlkCnt = 0; // can not support Reliable Write
        }
        #endif
    }

    //--------------------------------
    g_eMMCDrv.u8_ErasedMemContent = gau8_eMMC_SectorBuf[181];

    //--------------------------------
    g_eMMCDrv.u8_ECSD185_HsTiming = gau8_eMMC_SectorBuf[185];
    g_eMMCDrv.u8_ECSD192_Ver = gau8_eMMC_SectorBuf[192];
    g_eMMCDrv.u8_ECSD196_DevType = gau8_eMMC_SectorBuf[196];
    g_eMMCDrv.u8_ECSD197_DriverStrength = gau8_eMMC_SectorBuf[197];
    g_eMMCDrv.u8_ECSD248_CMD6TO = gau8_eMMC_SectorBuf[248];
    g_eMMCDrv.u8_ECSD247_PwrOffLongTO = gau8_eMMC_SectorBuf[247];
    g_eMMCDrv.u8_ECSD34_PwrOffCtrl = gau8_eMMC_SectorBuf[34];

    //for GP Partition
    g_eMMCDrv.u8_ECSD160_PartSupField = gau8_eMMC_SectorBuf[160];
    g_eMMCDrv.u8_ECSD224_HCEraseGRPSize= gau8_eMMC_SectorBuf[224];
    g_eMMCDrv.u8_ECSD221_HCWpGRPSize= gau8_eMMC_SectorBuf[221];

    g_eMMCDrv.GP_Part[0].u32_PartSize = ((gau8_eMMC_SectorBuf[145] << 16) |
                                             (gau8_eMMC_SectorBuf[144] << 8) |
                                             (gau8_eMMC_SectorBuf[143])) *
                                             (g_eMMCDrv.u8_ECSD224_HCEraseGRPSize  * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000);

    g_eMMCDrv.GP_Part[1].u32_PartSize = ((gau8_eMMC_SectorBuf[148] << 16) |
                                             (gau8_eMMC_SectorBuf[147] << 8) |
                                             (gau8_eMMC_SectorBuf[146])) *
                                             (g_eMMCDrv.u8_ECSD224_HCEraseGRPSize  * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000);

    g_eMMCDrv.GP_Part[2].u32_PartSize = ((gau8_eMMC_SectorBuf[151] << 16) |
                                             (gau8_eMMC_SectorBuf[150] << 8) |
                                             (gau8_eMMC_SectorBuf[149])) *
                                             (g_eMMCDrv.u8_ECSD224_HCEraseGRPSize  * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000);

    g_eMMCDrv.GP_Part[3].u32_PartSize = ((gau8_eMMC_SectorBuf[154] << 16) |
                                             (gau8_eMMC_SectorBuf[153] << 8) |
                                             (gau8_eMMC_SectorBuf[152])) *
                                             (g_eMMCDrv.u8_ECSD224_HCEraseGRPSize  * g_eMMCDrv.u8_ECSD221_HCWpGRPSize * 0x80000);

    //for Max Enhance Size
    g_eMMCDrv.u8_ECSD157_MaxEnhSize_0= gau8_eMMC_SectorBuf[157];
    g_eMMCDrv.u8_ECSD158_MaxEnhSize_1= gau8_eMMC_SectorBuf[158];
    g_eMMCDrv.u8_ECSD159_MaxEnhSize_2= gau8_eMMC_SectorBuf[159];

    g_eMMCDrv.u8_u8_ECSD155_PartSetComplete = gau8_eMMC_SectorBuf[155];
    g_eMMCDrv.u8_ECSD166_WrRelParam = gau8_eMMC_SectorBuf[166];

    //--------------------------------
    // preset for WP
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 175, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: set ERASE_GROUP_DEF fail: %Xh \n", u32_err);
        return u32_err;
    }
    #if 0
    // set CLASS_6_CTRL to WP
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_ClrBit, 59, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: set CLASS_6_CTRL to WP fail: %Xh \n", u32_err);
        return u32_err;
    }
    #endif
    
    //--------------------------------
    // set HW RST
    if(0 == gau8_eMMC_SectorBuf[162])
    {
        u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 162, BIT0); // RST_FUNC
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[162]: %Xh fail\n",
            u32_err, BIT0);
            return u32_err;
        }
    }

    return eMMC_ST_SUCCESS;
}


U32 eMMC_CMD8(U8 *pu8_DataBuf)
{
    #if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
        return eMMC_CMD8_CIFD(pu8_DataBuf);
    #else
        return eMMC_CMD8_MIU(pu8_DataBuf);
    #endif
}

// CMD8: send EXT_CSD
U32 eMMC_CMD8_MIU(U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    #if 0
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();
    #endif
    // -------------------------------
    // send cmd
    u32_arg =  0;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

    LABEL_SEND_CMD:
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);

    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32_arg, 8, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD8 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }

        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD8 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }


    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD8 Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD8_MIU;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD8 Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD8 check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD8_MIU;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD8 check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}

// CMD8: send EXT_CSD
U32 eMMC_CMD8_CIFD(U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    volatile U16 u16_mode, u16_ctrl, u16_reg, u16_i;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;;

    // -------------------------------
    // send cmd
    u32_arg =  0;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

    LABEL_SEND_CMD:
    u16_mode = BIT_DATA_DEST | g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;
    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(
        u16_mode, u16_ctrl, u32_arg, 8, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD8 CIFD retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD8 CIFD retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }
    //read for data
    for (u16_i=0; u16_i< (eMMC_SECTOR_512BYTE >> 6); u16_i++)
    {   // read data
        u32_err = eMMC_WaitGetCIFD((U8*)((U32)pu8_DataBuf + (u16_i << 6)), 0x40);
        if(u32_err != eMMC_ST_SUCCESS)
        {
            eMMC_FCIE_ErrHandler_Stop();
            goto LABEL_END;
        }
    }

    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
        BIT_DMA_END, TIME_WAIT_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

    if(eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD8 CIFD Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }

        u32_err = eMMC_ST_ERR_CMD8_CIFD;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD8 CIFD Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD8 CIFD check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }

        u32_err = eMMC_ST_ERR_CMD8_CIFD;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD8 CIFD check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }
    //eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 8);


    LABEL_END:
    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


U32 eMMC_SetPwrOffNotification(U8 u8_SetECSD34)
{
    U32 u32_err;
    static U8 u8_OldECSD34=0;

    if(eMMC_PwrOffNotif_SHORT==u8_OldECSD34 || eMMC_PwrOffNotif_LONG==u8_OldECSD34)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: PwrOffNotif already set: %u, now: %u\n",
            u8_OldECSD34, u8_SetECSD34);
        return eMMC_ST_SUCCESS;
    }

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 34, u8_SetECSD34); // PWR_OFF_NOTIFICATION
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_PwrOffNotif_MASK;
    switch(u8_SetECSD34)
    {
        case eMMC_PwrOffNotif_OFF:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_OFF;  break;
        case eMMC_PwrOffNotif_ON:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_ON;  break;
        case eMMC_PwrOffNotif_SHORT:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_SHORT;  break;
        case eMMC_PwrOffNotif_LONG:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_LONG;  break;
    }

    return u32_err;
}


U32 eMMC_Sanitize(U8 u8_ECSD165)
{
    U32 u32_err;

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 165, u8_ECSD165);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH<<2);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    return eMMC_ST_SUCCESS;
}


#define BITS_MSK_DRIVER_STRENGTH    0xF0
#define BITS_MSK_TIMING             0x0F

U32 eMMC_SetBusSpeed(U8 u8_BusSpeed)
{
    U32 u32_err;

    g_eMMCDrv.u8_ECSD185_HsTiming &= ~BITS_MSK_TIMING;
    g_eMMCDrv.u8_ECSD185_HsTiming |= u8_BusSpeed;

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 185, g_eMMCDrv.u8_ECSD185_HsTiming);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_SPEED_MASK;
    switch(u8_BusSpeed)
    {
        case eMMC_SPEED_HIGH:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HIGH;
            break;
        case eMMC_SPEED_HS200:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HS200;
            break;
        case eMMC_SPEED_HS400:
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HS400;
            break;
        default:
            break;
    } 

    return u32_err;
}


U32 eMMC_SetDrivingStrength(U8 u8Driving)
{
    U32 u32_err;

    g_eMMCDrv.u8_ECSD185_HsTiming &= ~BITS_MSK_DRIVER_STRENGTH;
    g_eMMCDrv.u8_ECSD185_HsTiming |= u8Driving<<4;

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 185, g_eMMCDrv.u8_ECSD185_HsTiming); // HS_TIMING, HS200
    if(eMMC_ST_SUCCESS != u32_err) {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: fail: %Xh\n", u32_err);
        return eMMC_ST_ERR_SET_DRV_STRENGTH;
    }
    return eMMC_ST_SUCCESS;
}

// Use CMD6 to set ExtCSD[183] BUS_WIDTH
U32 eMMC_SetBusWidth(U8 u8_BusWidth, U8 u8_IfDDR)
{
    U8  u8_value;
    U32 u32_err;

    // -------------------------------
    switch(u8_BusWidth)
    {
        case 1:  u8_value=0; break;
        case 4:  u8_value=1; break;
        case 8:  u8_value=2; break;
        default: return eMMC_ST_ERR_PARAMETER;
    }

    if(u8_IfDDR)
    {
        u8_value |= BIT2;
        g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_DDR_MODE;
    }
    else
        g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_DDR_MODE;


    // -------------------------------
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 183, u8_value); // BUS_WIDTH
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    // -------------------------------
    g_eMMCDrv.u16_Reg10_Mode &= ~BIT_SD_DATA_WIDTH_MASK;
    switch(u8_BusWidth)
    {
        case 1:
            g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_1;
            g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_1;
            break;
        case 4:
            g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_4;
            g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_4;
            break;
        case 8:
            g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_8;
            g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_8;
            break;
    }

    //eMMC_debug(eMMC_DEBUG_LEVEL,1,"set %u bus width\n", u8_BusWidth);
    return u32_err;
}

U32 eMMC_ModifyExtCSD(U8 u8_AccessMode, U8 u8_ByteIdx, U8 u8_Value)
{
    U32 u32_arg, u32_err;

    //eMMC_debug(0, 1, "ByteIdx: %d(%03X), value %02X\n", u8_ByteIdx, u8_ByteIdx, u8_Value);

    u32_arg = ((u8_AccessMode&3)<<24) | (u8_ByteIdx<<16) |
              (u8_Value<<8);

    u32_err = eMMC_CMD6(u32_arg);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC: %Xh \n", u32_err);
        return u32_err;
    }

    u32_err = eMMC_CMD13(g_eMMCDrv.u16_RCA);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC: %Xh \n", u32_err);
        return u32_err;
    }

    return u32_err;
}

// SWITCH cmd
U32 eMMC_CMD6(U32 u32_Arg)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    u32_arg = u32_Arg;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSP_WAIT_D0H;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 6, eMMC_R1b_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD6 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD6 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD6 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_ReInit();
                eMMC_FCIE_ErrHandler_Retry();
                goto LABEL_SEND_CMD;
            }
            u32_err = eMMC_ST_ERR_CMD6;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD6 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   // CMD3 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY()){
                    u8_retry_r1++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD6 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                    eMMC_FCIE_ErrHandler_ReInit();
                    eMMC_FCIE_ErrHandler_Retry();
                    goto LABEL_SEND_CMD;
                }
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD6 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                eMMC_FCIE_ErrHandler_Stop();
            }
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 6);
        }
    }

    eMMC_FCIE_CLK_DIS();
    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_RSP_WAIT_D0H;
    return u32_err;

}

U32 eMMC_EraseCMDSeq(U32 u32_eMMCBlkAddr_start, U32 u32_eMMCBlkAddr_end)
{
    U32 u32_err;

    u32_err = eMMC_CMD35_CMD36(u32_eMMCBlkAddr_start, 35);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    u32_err = eMMC_CMD35_CMD36(u32_eMMCBlkAddr_end, 36);
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    u32_err = eMMC_CMD38();
    if(eMMC_ST_SUCCESS != u32_err)
        return u32_err;

    return eMMC_ST_SUCCESS;
}

U32 eMMC_CMD35_CMD36(U32 u32_eMMCBlkAddr, U8 u8_CmdIdx)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;

    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, u8_CmdIdx, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD%u fail, %Xh \n",
            u8_CmdIdx, u32_err);
        return u32_err;
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD%u Reg.12: %04Xh \n", u8_CmdIdx, u16_reg);
            return eMMC_ST_ERR_CMD3536_ERR;
        }
        else
        {   // CMD3 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD%u check R1 error: %Xh\n", u8_CmdIdx, u32_err);
                return u32_err;
            }
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, u8_CmdIdx);
        }
    }

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}

U32 eMMC_CMD38(void)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;

    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
    if(g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_TRIM)
        u32_arg =  0x1;
    else
        u32_arg =  0x0;

    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSP_WAIT_D0H;

    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 38, eMMC_R1b_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD38 fail: %Xh \n", u32_err);
        return u32_err;
    }
    else
    {
        // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            u32_err = eMMC_ST_ERR_CMD38_ERR;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD38 Reg.12: %04Xh\n", u16_reg);
            return u32_err;
        }
        else
        {   // CMD38 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD38 check R1 error: %Xh\n", u32_err);
                return u32_err;
            }
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 38);
        }
    }

    eMMC_FCIE_CLK_DIS();
    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_RSP_WAIT_D0H;
    return u32_err;

}


U32 eMMC_Dump_eMMCStatus(void)
{
    eMMC_CMD13(g_eMMCDrv.u16_RCA);
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n");
    eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC St: %Xh %Xh %Xh %Xh \n",
        g_eMMCDrv.au8_Rsp[1], g_eMMCDrv.au8_Rsp[2], g_eMMCDrv.au8_Rsp[3], g_eMMCDrv.au8_Rsp[4]);
    return eMMC_ST_SUCCESS;
}


// CMD13: send Status
U32 eMMC_CMD13(U16 u16_RCA)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_cmd=0;// ,u8_retry_r1=0;

    u32_arg = (u16_RCA<<16); // |
    //  ((g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_HPI_CMD13)?1:0);
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 13, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD13 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD13 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD13 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_ReInit();
                eMMC_FCIE_ErrHandler_Retry();
                goto LABEL_SEND_CMD;
            }

            u32_err = eMMC_ST_ERR_CMD13;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD13 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   // CMD13 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                #if 0
                if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY()){
                    u8_retry_r1++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD13 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                    eMMC_FCIE_ErrHandler_Retry();
                    goto LABEL_SEND_CMD;
                }
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD13 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                eMMC_FCIE_ErrHandler_Stop();
                #else
                eMMC_debug(0, 1,
                    "eMMC: CMD13 check R1 error: %Xh, should not retry\n", u32_err);
                #endif
            }
            else
                eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 13);
        }
    }

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


U32 eMMC_CMD16(U32 u32_BlkLength)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    u32_arg = u32_BlkLength;
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 16, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD16 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD16 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD16 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_Retry();
                goto LABEL_SEND_CMD;
            }

            u32_err = eMMC_ST_ERR_CMD16;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD16 Reg.12: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   // CMD16 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY()){
                    u8_retry_r1++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD16 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                    eMMC_FCIE_ErrHandler_Retry();
                    goto LABEL_SEND_CMD;
                }
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD16 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                eMMC_FCIE_ErrHandler_Stop();
            }
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 16);
        }
    }

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


//------------------------------------------------

U32 eMMC_CMD17(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{

    #if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    return eMMC_CMD17_CIFD(u32_eMMCBlkAddr, pu8_DataBuf);
    #else
    return eMMC_CMD17_MIU(u32_eMMCBlkAddr, pu8_DataBuf);
    #endif
}
#if 0
static  U32 u32_TestCnt=0;
#define IF_TEST_RETRY_FCIE5(x)  (0==++u32_TestCnt%x)
#else
#define IF_TEST_RETRY_FCIE5(x)  (0)//==++u32_TestCnt%x)
#endif

U32 eMMC_CMD17_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH | BIT_SD_DMA_R_CLK_STOP;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    REG_FCIE_W(FCIE_BLK_SIZE, 0x200); // 64 bytes tuning pattern

    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(
        u16_mode, u16_ctrl, u32_arg, 17, eMMC_R1_BYTE_CNT);
    if(IF_TEST_RETRY_FCIE5(17) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD17 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD17_RSP; 
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD17 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_R_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(33) ||  eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD17 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD17_MIU;
        if(u16_reg & BIT_SD_RSP_CRC_ERR)
            u32_err = eMMC_ST_ERR_CMD17_RSP;        
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD17 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if(IF_TEST_RETRY_FCIE5(7) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD17 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        else
        {   
            u32_err = eMMC_ST_ERR_CMD17_MIU;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD17 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_Stop();
            goto LABEL_END;
        }
    }

    LABEL_END:
    REG_FCIE_CLRBIT(FCIE_SD_MODE,BIT_SD_DMA_R_CLK_STOP);    
    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


U32 eMMC_CMD17_CIFD(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg, u16_i;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    //if(0 == eMMC_IF_DISABLE_RETRY())
    //  eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = BIT_DATA_DEST | g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32_arg, 17, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT  && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD17 CIFD retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD17 CIFD retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    //read for data
    for (u16_i=0; u16_i< (eMMC_SECTOR_512BYTE >> 6); u16_i++)
    {   // read data
        u32_err = eMMC_WaitGetCIFD((U8*)((U32)pu8_DataBuf + (u16_i << 6)), 0x40);
        if(u32_err != eMMC_ST_SUCCESS)
        {
            eMMC_FCIE_ErrHandler_Stop();
            goto LABEL_END;
        }
    }

    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
        BIT_DMA_END, TIME_WAIT_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if( eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD17 CIFD Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD17_CIFD;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD17 CIFD Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if( eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD17 CIFD check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }

        u32_err = eMMC_ST_ERR_CMD17_CIFD;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD17 CIFD check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


U32 eMMC_CMD31_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    REG_FCIE_W(FCIE_BLK_SIZE, 0x200); // 64 bytes tuning pattern

    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(
        u16_mode, u16_ctrl, u32_arg, 31, eMMC_R1_BYTE_CNT);
    if(IF_TEST_RETRY_FCIE5(17) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD31 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD31 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, TIME_WAIT_R_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(33) ||  eMMC_ST_SUCCESS != u32_err || (u16_reg & (BIT_CMD_NO_RSP|BIT_CMD_RSP_CERR|BIT_DAT_RD_TOUT|BIT_SD_CARD_BUSY)))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD31 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD17_MIU;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD31 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if(IF_TEST_RETRY_FCIE5(7) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD31 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        else
        {   u32_err = eMMC_ST_ERR_CMD17_MIU;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD31 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_Stop();
            goto LABEL_END;
        }
    }

    LABEL_END:
    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


U32 eMMC_CMD12(U16 u16_RCA)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;

    #if 1
    u32_arg = (u16_RCA<<16)|
        ((g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_HPI_CMD12)?1:0);
    #else
    u32_arg = (u16_RCA<<16);
    #endif

    #if defined(eMMC_UPDATE_FIRMWARE) && (eMMC_UPDATE_FIRMWARE)
    u32_arg = 0;
    #endif

    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSP_WAIT_D0H;

    //LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 12, eMMC_R1b_BYTE_CNT);
    if(IF_TEST_RETRY_FCIE5(10) ||  eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD12 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_ReInit();
            //eMMC_FCIE_ErrHandler_Retry();
            //goto LABEL_SEND_CMD;
            return u32_err;
        }
        u32_err = eMMC_ST_ERR_CMD12_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD12 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(IF_TEST_RETRY_FCIE5(3) || u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD12 check Reg.12: %Xh, %Xh, retry: %u\n",
                    u16_reg, u32_err, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_ReInit();
                //eMMC_FCIE_ErrHandler_Retry();
                //goto LABEL_SEND_CMD;
                return u32_err;
            }

            u32_err = eMMC_ST_ERR_CMD12;
            if(u16_reg & BIT_SD_RSP_CRC_ERR)
                u32_err = eMMC_ST_ERR_CMD12_RSP;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Err: CMD12 check Reg.12: %Xh, %Xh, retry: %u\n",
                u16_reg, u32_err, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   u32_err = eMMC_CheckR1Error();
            if(IF_TEST_RETRY_FCIE5(13) || eMMC_ST_SUCCESS != u32_err)
            {
                if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
                {
                    u8_retry_r1++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD12 check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
                    //eMMC_FCIE_ErrHandler_Retry();
                    //goto LABEL_SEND_CMD;
                    return u32_err;
                }
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD12 check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
                eMMC_FCIE_ErrHandler_Stop();
            }
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 12);
        }
    }

    eMMC_FCIE_CLK_DIS();
    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_RSP_WAIT_D0H;
    return u32_err;

}


U32 eMMC_CMD12_NoCheck(U16 u16_RCA)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl;

    #if 1
    u32_arg = (u16_RCA<<16)|
        ((g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_HPI_CMD12)?1:0);
    #else
    u32_arg = (u16_RCA<<16);
    #endif

    #if defined(eMMC_UPDATE_FIRMWARE) && (eMMC_UPDATE_FIRMWARE)
    u32_arg = 0;
    #endif

    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
    g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSP_WAIT_D0H;

    //LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 12, eMMC_R1b_BYTE_CNT);

    g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_RSP_WAIT_D0H;
    return u32_err;

}


U32 eMMC_CMD18(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
    #if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    U16 u16_cnt;
    U32 u32_err;

    for(u16_cnt=0; u16_cnt<u16_BlkCnt; u16_cnt++)
    {
        u32_err = eMMC_CMD17_CIFD(u32_eMMCBlkAddr+u16_cnt, pu8_DataBuf+(u16_cnt<<9));
        if(eMMC_ST_SUCCESS != u32_err)
            return u32_err;
    }
    #else
    return eMMC_CMD18_MIU(u32_eMMCBlkAddr, pu8_DataBuf, u16_BlkCnt);
    #endif
}

U32 eMMC_CMD18_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH | BIT_SD_DMA_R_CLK_STOP;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, u16_BlkCnt);
    REG_FCIE_W(FCIE_BLK_SIZE, 0x200); // 64 bytes tuning pattern

    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE*u16_BlkCnt);

    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, (eMMC_SECTOR_512BYTE*u16_BlkCnt) & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,(eMMC_SECTOR_512BYTE*u16_BlkCnt) >> 16);

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32_arg, 18, eMMC_R1_BYTE_CNT);
    if(IF_TEST_RETRY_FCIE5(20) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD18 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD18_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD18 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(u16_BlkCnt>>11)));

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(13) || eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD18 Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);

            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();

            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD18;
        if(u16_reg & BIT_SD_RSP_CRC_ERR)
            u32_err = eMMC_ST_ERR_CMD18_RSP;        
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD18 Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if(IF_TEST_RETRY_FCIE5(24) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);

            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD18;
        eMMC_debug(1, 1, "eMMC Err: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    eMMC_FCIE_CLK_DIS();    
    if(eMMC_ST_SUCCESS == u32_err)
    {
        u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
        if(eMMC_ST_SUCCESS == u32_err)
            u32_err = eMMC_CMD13(g_eMMCDrv.u16_RCA);
    }
    else
        eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);  

    REG_FCIE_CLRBIT(FCIE_SD_MODE,BIT_SD_DMA_R_CLK_STOP);
    eMMC_FCIE_CLK_DIS();
    return u32_err;

}

U32 eMMC_CMD18_ADMA(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 len)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN | BIT_ADMA_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, len);

    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 0x0010);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,0x0000);

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32_arg, 18, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD18 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD18 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check FCIE
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(len>>20)));

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if( eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD18 Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);

            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();

            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD18;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD18 Reg.12: %04Xh, Err: %Xh, Retry: %u\n", u16_reg, u32_err, u8_retry_fcie);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    u32_err = eMMC_CheckR1Error();
    if( eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);

            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD18;
        eMMC_debug(1, 1, "eMMC Err: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    if(eMMC_ST_SUCCESS != eMMC_CMD12(g_eMMCDrv.u16_RCA))
        eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}


U32 eMMC_CMD28(U32 u32_eMMCBlkAddr)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
    u32_arg = u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 28, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD8 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD28 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD28 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_Retry();
                goto LABEL_SEND_CMD;
            }

            u32_err = eMMC_ST_ERR_CMD28;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD28 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   // CMD28 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY()){
                    u8_retry_r1++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD28 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                    eMMC_FCIE_ErrHandler_Retry();
                    goto LABEL_SEND_CMD;
                }
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD28 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                eMMC_FCIE_ErrHandler_Stop();
            }
        }
    }

    eMMC_FCIE_CLK_DIS();
    return u32_err;
}


// enable Reliable Write
U32 eMMC_CMD23(U16 u16_BlkCnt)
{
    U32 u32_err, u32_arg;
    U16 u16_ctrl, u16_reg;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    u32_arg = u16_BlkCnt&0xFFFF; // don't set BIT24
    #if eMMC_FEATURE_RELIABLE_WRITE
    u32_arg |= BIT31; // don't set BIT24
    #endif
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 23, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD23 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD23 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
        eMMC_FCIE_ErrHandler_Stop();
    }
    else
    {   // check status
        REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

        if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
        {
            if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
            {
                u8_retry_fcie++;
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC WARN: CMD23 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
                eMMC_FCIE_ErrHandler_Retry();
                goto LABEL_SEND_CMD;
            }

            u32_err = eMMC_ST_ERR_CMD23;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD23 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
            eMMC_FCIE_ErrHandler_Stop();
        }
        else
        {   // CMD13 ok, do things here
            u32_err = eMMC_CheckR1Error();
            if(eMMC_ST_SUCCESS != u32_err)
            {
                if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY()){
                    u8_retry_r1++;
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                        "eMMC WARN: CMD23 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                    eMMC_FCIE_ErrHandler_Retry();
                    goto LABEL_SEND_CMD;
                }
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                    "eMMC Err: CMD23 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
                eMMC_FCIE_ErrHandler_Stop();
            }
            eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 23);

        }
    }

    eMMC_FCIE_CLK_DIS();
    return u32_err;
}


U32 eMMC_CMD25(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
    U32 u32_err=eMMC_ST_SUCCESS;
    #if defined(ENABLE_eMMC_RIU_MODE) && ENABLE_eMMC_RIU_MODE
    U16 u16_cnt;
    #endif
    #if eMMC_BURST_LEN_AUTOCFG || ENABLE_eMMC_RIU_MODE
    U16 u16_RetryCnt=0;
    LABEL_CMD25:
    #endif


    // ------------------------------RIU mode
    #if defined(ENABLE_eMMC_RIU_MODE) && ENABLE_eMMC_RIU_MODE
    for(u16_cnt=0; u16_cnt<u16_BlkCnt; u16_cnt++)
    {
        u32_err = eMMC_CMD24_CIFD(u32_eMMCBlkAddr+u16_cnt, pu8_DataBuf+(u16_cnt<<eMMC_SECTOR_BYTECNT_BITS));
        if(eMMC_ST_SUCCESS != u32_err)
            goto LABEL_CMD25_END;
    }
    #else
    // ------------------------------MIU mode
        #if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
    {
        U16 u16_blk_cnt, u16_blk_pos;

        u16_blk_pos = 0;

        if(g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen)
            while(u16_blk_pos < u16_BlkCnt)
            {
                u16_blk_cnt = u16_BlkCnt-u16_blk_pos > g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen ?
                    g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen : u16_BlkCnt-u16_blk_pos;
                u16_blk_cnt = u16_blk_cnt == g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen ?
                    u16_blk_cnt/2 : u16_blk_cnt;

                u32_err = eMMC_CMD25_MIU(u32_eMMCBlkAddr+u16_blk_pos,
                    pu8_DataBuf+(u16_blk_pos<<eMMC_SECTOR_BYTECNT_BITS),
                    u16_blk_cnt);
                if(eMMC_ST_SUCCESS != u32_err)
                    goto LABEL_CMD25_END;

                u16_blk_pos += u16_blk_cnt;
            }
        else
            u32_err = eMMC_CMD25_MIU(u32_eMMCBlkAddr, pu8_DataBuf, u16_BlkCnt);
    }
        #else
    u32_err = eMMC_CMD25_MIU(u32_eMMCBlkAddr, pu8_DataBuf, u16_BlkCnt);
        #endif
    #endif

    #if eMMC_BURST_LEN_AUTOCFG || ENABLE_eMMC_RIU_MODE
    LABEL_CMD25_END:
    if(eMMC_ST_SUCCESS!=u32_err && u16_RetryCnt<eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT)
    {
        u16_RetryCnt++;
        goto LABEL_CMD25;
    }
    #endif

    return u32_err;
}

#ifdef STATIC_RELIABLE_TEST
extern int reliable_test_sleep; //ms
extern int enable_pm_sleep_flag;
int WDT_enable = 0;
#endif
U32 eMMC_CMD25_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    // restore clock to max
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    #if 0 //defined(eMMC_FEATURE_RELIABLE_WRITE) && eMMC_FEATURE_RELIABLE_WRITE
    eMMC_CMD23(u16_BlkCnt);
    #endif

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, u16_BlkCnt);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE*u16_BlkCnt);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);
    
    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, (eMMC_SECTOR_512BYTE*u16_BlkCnt) & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,(eMMC_SECTOR_512BYTE*u16_BlkCnt) >> 16);

    u32_err = eMMC_FCIE_SendCmd(
        u16_mode, u16_ctrl, u32_arg, 25, eMMC_R1_BYTE_CNT);
    if(IF_TEST_RETRY_FCIE5(23) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD25 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD25 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(13) || (u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) )
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD25 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25;
        if(u16_reg & BIT_SD_RSP_CRC_ERR)
            u32_err = eMMC_ST_ERR_CMD25_RSP;        
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD25 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    u32_err = eMMC_CheckR1Error();
    if(IF_TEST_RETRY_FCIE5(31) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(1, 1, "eMMC WARN: CMD25 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25_CHK_R1;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD25 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // send data
    u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u32_err = eMMC_ST_ERR_CMD25_WAIT_D0H;
        goto LABEL_END;
    }

    eMMC_CheckPowerCut();
    REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_SD_DAT_DIR_W|BIT_JOB_START);


    #if defined(ENABLE_eMMC_INTERRUPT_MODE) && ENABLE_eMMC_INTERRUPT_MODE
    REG_FCIE_W(FCIE_MIE_INT_EN, BIT_DMA_END);
    #endif

    #ifdef STATIC_RELIABLE_TEST
    //cut off power for eMMC
    if(enable_pm_sleep_flag == 1)
    {
        if(reliable_test_sleep>0)
            udelay(reliable_test_sleep*1000);
        if(WDT_enable == 0)
        {
            MDrv_WDT_ClearRstFlag();
            MDrv_WDT_SetTimer(1, 5);
            WDT_enable = 1;
        }
        if(E_PM_FAIL == MDrv_PM_GPIO4_SetPower(FALSE))
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "reliable write test: cut power fail\n");
    }
    #endif

    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
        BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(u16_BlkCnt>>9)));

    #ifdef STATIC_RELIABLE_TEST
    if(enable_pm_sleep_flag == 1)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL, 1, "write done\n");
    }
    #endif

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(43) || eMMC_ST_SUCCESS != u32_err || (u16_reg & (BIT_SD_W_FAIL|BIT_SD_W_CRC_ERR)))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD25 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD25 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    #if 0 //!(defined(eMMC_FEATURE_RELIABLE_WRITE) && eMMC_FEATURE_RELIABLE_WRITE)
    u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
    if(eMMC_ST_SUCCESS != u32_err)
        eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
    #else
    if(eMMC_ST_SUCCESS == u32_err)
    {
        u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
        if(eMMC_ST_SUCCESS == u32_err)
            u32_err = eMMC_CMD13(g_eMMCDrv.u16_RCA);
    }
    else
        eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);    
    #endif

    eMMC_FCIE_CLK_DIS();
    return u32_err;

}

U32 eMMC_CMD25_ADMA(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U32 len)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
    
    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, len);

    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 0x0010);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,0x0000);

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32_arg, 25, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD25 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD25 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }
    // -------------------------------
    // check device
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) )
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD25 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD25 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }
    
    u32_err = eMMC_CheckR1Error();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD24 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25_CHK_R1;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD25 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // send data
    u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u32_err = eMMC_ST_ERR_CMD25_WAIT_D0H;
        goto LABEL_END;
    }

    eMMC_CheckPowerCut();
    REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_SD_DAT_DIR_W|BIT_ADMA_EN|BIT_JOB_START);

    #if defined(ENABLE_eMMC_INTERRUPT_MODE) && ENABLE_eMMC_INTERRUPT_MODE
    REG_FCIE_W(FCIE_MIE_INT_EN, BIT_DMA_END);
    #endif

    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
        BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(len>>20)));

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(eMMC_ST_SUCCESS != u32_err || (u16_reg & (BIT_SD_W_FAIL|BIT_SD_W_CRC_ERR)))
    {
        u32_err = eMMC_ST_ERR_CMD25;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD25 Reg.12: %04Xh, Err: %Xh, Arg: %Xh\n", u16_reg, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    #if 0 //!(defined(eMMC_FEATURE_RELIABLE_WRITE) && eMMC_FEATURE_RELIABLE_WRITE)
    u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
    if(eMMC_ST_SUCCESS != u32_err)
        eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
    #else
    if(eMMC_ST_SUCCESS == u32_err)
    {
        u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
        if(eMMC_ST_SUCCESS == u32_err)
            u32_err = eMMC_CMD13(g_eMMCDrv.u16_RCA);
    }
    else
        eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);  
    #endif

    eMMC_FCIE_CLK_DIS();
    return u32_err;


}

U32 eMMC_CMD24(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{

    #if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    return eMMC_CMD24_CIFD(u32_eMMCBlkAddr, pu8_DataBuf);
    #else
    return eMMC_CMD24_MIU(u32_eMMCBlkAddr, pu8_DataBuf);
    #endif
}

U32 eMMC_CMD24_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg;
    U8  u8_retry_fcie=0, u8_retry_r1=0, u8_retry_cmd=0;
    U32 u32_dma_addr;

    // -------------------------------
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();

    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);
    
    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(
        u16_mode, u16_ctrl, u32_arg, 24, eMMC_R1_BYTE_CNT);
    if(IF_TEST_RETRY_FCIE5(25) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD24 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD24_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD24 retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(34) || (u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) )
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD24 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD24_MIU;
        if(u16_reg & BIT_SD_RSP_CRC_ERR)
            u32_err = eMMC_ST_ERR_CMD24_RSP;        
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD24 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }
    
    u32_err = eMMC_CheckR1Error();
    if(IF_TEST_RETRY_FCIE5(31) || eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD24 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD24_MIU_CHK_R1;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD24 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // send data
    u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u32_err = eMMC_ST_ERR_CMD24_MIU_WAIT_D0H;
        goto LABEL_END;
    }

    eMMC_CheckPowerCut();

    REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_SD_DAT_DIR_W|BIT_JOB_START);

    #if defined(ENABLE_eMMC_INTERRUPT_MODE) && ENABLE_eMMC_INTERRUPT_MODE
    REG_FCIE_W(FCIE_MIE_INT_EN, BIT_DMA_END);
    #endif

    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
        BIT_DMA_END, TIME_WAIT_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(IF_TEST_RETRY_FCIE5(31) || eMMC_ST_SUCCESS != u32_err || (u16_reg & (BIT_SD_W_FAIL|BIT_SD_W_CRC_ERR)))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC Warn: CMD24 %sReg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n",
                (eMMC_ST_SUCCESS!=u32_err)?"TO ":"", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD24_MIU;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD24 %sReg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n",
            (eMMC_ST_SUCCESS!=u32_err)?"TO ":"", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    eMMC_FCIE_CLK_DIS();
    return u32_err;


}

U32 eMMC_CMD24_CIFD(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
    U32 u32_err, u32_arg;
    U16 u16_mode, u16_ctrl, u16_reg, u16_i;
    U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    // -------------------------------
    #if 0
    if(0 == eMMC_IF_DISABLE_RETRY())
        eMMC_FCIE_ErrHandler_RestoreClk();
    #endif
    // -------------------------------
    // send cmd
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    LABEL_SEND_CMD:
    u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
    u16_mode = BIT_DATA_DEST | g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    eMMC_FCIE_ClearEvents();
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

    u32_err = eMMC_FCIE_SendCmd(
        u16_mode, u16_ctrl, u32_arg, 24, eMMC_R1_BYTE_CNT);
    if( eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_cmd++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD24 CIFD retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD24 CIFD retry:%u, %Xh, Arg: %Xh \n", u8_retry_cmd, u32_err, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // check device
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) )
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD24 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD25;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD24 Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    
    u32_err = eMMC_CheckR1Error();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_r1++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD24 CIFD check R1 error: %Xh, Retry: %u, Arg: %Xh \n", u32_err, u8_retry_r1, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD24_CIFD_CHK_R1;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD24 CIFD check R1 error: %Xh, Retry: %u, Arg: %Xh \n", u32_err, u8_retry_r1, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    // -------------------------------
    // send data
    u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u32_err = eMMC_ST_ERR_CMD24_CIFD_WAIT_D0H;
        goto LABEL_END;
    }

    REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_SD_DAT_DIR_W|BIT_JOB_START);

    for (u16_i=0; u16_i< (eMMC_SECTOR_512BYTE >> 6); u16_i++)
    {
        u32_err = eMMC_WaitSetCIFD( (U8*)( (U32) pu8_DataBuf + (u16_i << 6)), 0x40);
        if(u32_err != eMMC_ST_SUCCESS)
        {
            eMMC_FCIE_ErrHandler_Stop();
            goto LABEL_END;
        }
    }
    
    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
        BIT_DMA_END, TIME_WAIT_1_BLK_END);

    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if( eMMC_ST_SUCCESS != u32_err || (u16_reg & (BIT_SD_W_FAIL|BIT_SD_W_CRC_ERR)))
    {
        if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_DISABLE_RETRY())
        {
            u8_retry_fcie++;
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
                "eMMC WARN: CMD24 TO Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
            eMMC_FCIE_ErrHandler_ReInit();
            eMMC_FCIE_ErrHandler_Retry();
            goto LABEL_SEND_CMD;
        }
        u32_err = eMMC_ST_ERR_CMD24_CIFD;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
            "eMMC Err: CMD24 CIFD Reg.12: %04Xh, Err: %Xh, Retry: %u, Arg: %Xh\n", u16_reg, u32_err, u8_retry_fcie, u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END;
    }

    LABEL_END:
    if(u8_retry_fcie)
        eMMC_debug(0,1,"eMMC Info: retry ok\n");
    eMMC_FCIE_CLK_DIS();
    return u32_err;


}



static const U8 hs200_tunning_pattern_128[128] = {
    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xCC, 0xCC, 0xCC, 0x33, 0xCC, 0xCC,
    0xCC, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xFF, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF, 0xEE, 0xEE, 0xFF,
    0xFF, 0xFF, 0xDD, 0xFF, 0xFF, 0xFF, 0xDD, 0xDD, 0xFF, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0xFF, 0xBB,
    0xBB, 0xFF, 0xFF, 0xFF, 0x77, 0xFF, 0xFF, 0xFF, 0x77, 0x77, 0xFF, 0x77, 0xBB, 0xDD, 0xEE, 0xFF,
    0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xCC, 0xCC, 0xCC, 0x33, 0xCC,
    0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xFF, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF, 0xEE, 0xEE,
    0xFF, 0xFF, 0xFF, 0xDD, 0xFF, 0xFF, 0xFF, 0xDD, 0xDD, 0xFF, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0xFF,
    0xBB, 0xBB, 0xFF, 0xFF, 0xFF, 0x77, 0xFF, 0xFF, 0xFF, 0x77, 0x77, 0xFF, 0x77, 0xBB, 0xDD, 0xEE
};

static const U8 hs200_tunning_pattern_64[64] = {
    0xFF, 0x0F, 0xFF, 0x00, 0xFF, 0xCC, 0xC3, 0xCC, 0xC3, 0x3C, 0xCC, 0xFF, 0xFE, 0xFF, 0xFE, 0xEF,
    0xFF, 0xDF, 0xFF, 0xDD, 0xFF, 0xFB, 0xFF, 0xFB, 0xBF, 0xFF, 0x7F, 0xFF, 0x77, 0xF7, 0xBD, 0xEF,
    0xFF, 0xF0, 0xFF, 0xF0, 0x0F, 0xFC, 0xCC, 0x3C, 0xCC, 0x33, 0xCC, 0xCF, 0xFF, 0xEF, 0xFF, 0xEE,
    0xFF, 0xFD, 0xFF, 0xFD, 0xDF, 0xFF, 0xBF, 0xFF, 0xBB, 0xFF, 0xF7, 0xFF, 0xF7, 0x7F, 0x7B, 0xDE
};


// read out from RIU then compare pattern is slow
U32 eMMC_CMD21_CIFD(void)
{
    U32 u32_err = 0;
    U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN, u16_reg;
    U16 u16_mode, u16_i;
    U8 i;

    //eMMC_debug(0,0,"%s()\n", __FUNCTION__);

    eMMC_FCIE_ClearEvents();

    if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_4) {
        REG_FCIE_W(FCIE_BLK_SIZE, 64); // 64 bytes tuning pattern
        REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 64 & 0xFFFF);
        REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 64 >> 16);       
    } else if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_8) {
        REG_FCIE_W(FCIE_BLK_SIZE, 128); // 128 bytes tuning pattern
        REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 128 & 0xFFFF);
        REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 128 >> 16);      
    } else {
        u32_err = eMMC_ST_ERR_CMD21_ONE_BIT;
        eMMC_debug(0,0,"eMMC Warn: g_eMMCDrv.u8_BUS_WIDTH = %02Xh\n", g_eMMCDrv.u8_BUS_WIDTH);
        goto ErrorHandle;
    }
    if(!(g_eMMCDrv.u8_ECSD196_DevType & BIT4)) {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: eMMC not support HS200 1.8V\n");
        u32_err = eMMC_ST_ERR_CMD21_NO_HS200_1_8V;
        goto ErrorHandle;
    }   
    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);

    u16_mode = BIT_DATA_DEST | g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, 0, 21, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err) {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 send CMD fail: %08Xh\n", u32_err);
        goto ErrorHandle;
    }

    //read for data
    for (u16_i=0; u16_i< (128 >> 6); u16_i++)
    {   // read data
        u32_err = eMMC_WaitGetCIFD((U8*)((U32)gau8_eMMC_SectorBuf + (u16_i << 6)), 0x40);
        if(u32_err != eMMC_ST_SUCCESS)
        {
            eMMC_FCIE_ErrHandler_Stop();
            goto ErrorHandle;
        }
    }

    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, TIME_WAIT_1_BLK_END);
    if(u32_err)
        goto ErrorHandle;

    // check status
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

    if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) {

        u32_err = eMMC_ST_ERR_CMD21_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD21 no Rsp, Reg.12: %04Xh \n", u16_reg);
        goto ErrorHandle;

    } else if(u16_reg &BIT_SD_R_CRC_ERR) {

        u32_err = eMMC_ST_ERR_CMD21_DATA_CRC;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD21 data CRC err, Reg.12: %04Xh \n", u16_reg);
        goto ErrorHandle;

    } else {
        if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_4)
        {
            if(memcmp((void*)hs200_tunning_pattern_64, (void*)gau8_eMMC_SectorBuf, 64)) {
                printf("tuning pattern 4bit width:");
                for(i=0; i<64; i++) {
                    if(i%16==0) printf("\n\t");
                    printf("%02X ", gau8_eMMC_SectorBuf[i]);
                }
                printf("\n");
                u32_err = eMMC_ST_ERR_CMD21_DATA_CMP;
                goto ErrorHandle;
            }
        }
        else if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_8)
        {
            if(memcmp((void*)hs200_tunning_pattern_128, (void*)gau8_eMMC_SectorBuf, 128)) {
                printf("tuning pattern 8bit width:");
                for(i=0; i<128; i++) {
                    if(i%16==0) printf("\n\t");
                    printf("%02X ", gau8_eMMC_SectorBuf[i]);
                }
                printf("\n");
                u32_err = eMMC_ST_ERR_CMD21_DATA_CMP;
                goto ErrorHandle;
            }
        }

    }

    ErrorHandle:
    REG_FCIE_W(FCIE_BLK_SIZE, eMMC_SECTOR_512BYTE); // restore anyway...

    if(u32_err)
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %08Xh\n", u32_err);

    return u32_err;

}

// use memcmp to confirm tuning pattern
U32 eMMC_CMD21_MIU(void)
{
    U32 u32_err = 0;
    U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN, u16_reg;
    U16 u16_mode;
    U8 i;
    U32 u32_dma_addr;

    eMMC_FCIE_ClearEvents();

    if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_4) {
        REG_FCIE_W(FCIE_BLK_SIZE, 64); // 64 bytes tuning pattern
        REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 64 & 0xFFFF);
        REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 64 >> 16);       
    } else if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_8) {
        REG_FCIE_W(FCIE_BLK_SIZE, 128); // 128 bytes tuning pattern
        REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 128 & 0xFFFF);
        REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 128 >> 16);      
    } else {
        u32_err = eMMC_ST_ERR_CMD21_ONE_BIT;
        eMMC_debug(0,0,"eMMC Warn: g_eMMCDrv.u8_BUS_WIDTH = %02Xh\n", g_eMMCDrv.u8_BUS_WIDTH);
        goto ErrorHandle;
    }
    if(!(g_eMMCDrv.u8_ECSD196_DevType & BIT4)) {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: eMMC not support HS200 1.8V\n");
        u32_err = eMMC_ST_ERR_CMD21_NO_HS200_1_8V;
        goto ErrorHandle;
    }

    REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)gau8_eMMC_SectorBuf, eMMC_SECTOR_512BYTE);

    REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
    REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

    u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;
    u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, 0, 21, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        u32_err = eMMC_ST_ERR_CMD21_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD21 send CMD fail: %08Xh\n", u32_err);
        goto ErrorHandle;
    }

    u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, HW_TIMER_DELAY_100ms);
    if(u32_err)
        goto ErrorHandle;

    // check status
    REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
    if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) {

        u32_err = eMMC_ST_ERR_CMD21_RSP;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err:CMD21 no Rsp/CRC err, SD_STS: %04Xh \n", u16_reg);
        goto ErrorHandle;

    } else if(u16_reg &BIT_SD_R_CRC_ERR) {

        u32_err = eMMC_ST_ERR_CMD21_DATA_CRC;
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD21 data CRC err, Reg.12: %04Xh \n", u16_reg);
        goto ErrorHandle;

    } else {
        if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_4)
        {
            if(memcmp((void*)hs200_tunning_pattern_64, (void*)gau8_eMMC_SectorBuf, 64)) {
                printf("tuning pattern 4bit width:");
                for(i=0; i<64; i++) {
                    if(i%16==0) printf("\n\t");
                    printf("%02X ", gau8_eMMC_SectorBuf[i]);
                }
                printf("\n");
                u32_err = eMMC_ST_ERR_CMD21_DATA_CMP;
                goto ErrorHandle;
            }
        }
        else if(g_eMMCDrv.u8_BUS_WIDTH == BIT_SD_DATA_WIDTH_8)
        {
            if(memcmp((void*)hs200_tunning_pattern_128, (void*)gau8_eMMC_SectorBuf, 128)) {
                printf("tuning pattern 8bit width:");
                for(i=0; i<128; i++) {
                    if(i%16==0) printf("\n\t");
                    printf("%02X ", gau8_eMMC_SectorBuf[i]);
                }
                printf("\n");
                u32_err = eMMC_ST_ERR_CMD21_DATA_CMP;
                goto ErrorHandle;
            }
        }
    }

    ErrorHandle:
    REG_FCIE_W(FCIE_BLK_SIZE, eMMC_SECTOR_512BYTE); // restore anyway...
    if(u32_err)
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %08Xh\n", u32_err);

    return u32_err;


}

// eMMC CMD21 adtc, R1, fix 128 clock, for HS200 only
//  64 bytes in 4 bits mode
// 128 bytes in 8 bits mode

U32 eMMC_CMD21(void) // send tuning block
{
    #if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
        return eMMC_CMD21_CIFD(); // slow
    #else
        return eMMC_CMD21_MIU(); // fast
    #endif
}



#if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
void eMMC_DumpBurstLenTable(void)
{
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"eMMC Burst Len: \n");
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  best:  %4u blks, %4u.%u MB/s \n",
        g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen,
        g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSec, g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSecPoint);
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  worst: %4u blks, %4u.%u MB/s \n",
        g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen,
        g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSec, g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSecPoint);
}

U32 eMMC_LoadBurstLenTable(void)
{
    U32 u32_err, u32_ErrRetry=0;
    U32 u32_ChkSum;

    LABEL_RETRY:
    u32_err = eMMC_CMD18(eMMC_BURST_LEN_BLK_0, gau8_eMMC_SectorBuf, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC WARN: load Burst Len Table fail, %Xh\n", u32_err);
        goto LABEL_END_OF_NO_TABLE;
    }

    memcpy((U8*)&g_eMMCDrv.BurstWriteLen_t, gau8_eMMC_SectorBuf, sizeof(g_eMMCDrv.BurstWriteLen_t));
    u32_ChkSum = eMMC_ChkSum((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t)-4);
    if(u32_ChkSum != g_eMMCDrv.BurstWriteLen_t.u32_ChkSum ||
        0 == g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: no Burst Len Table. ChkSum: %Xh, BestLen: %Xh\n",
            g_eMMCDrv.BurstWriteLen_t.u32_ChkSum, g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen);
        u32_err = eMMC_ST_ERR_BLEN_CHKSUM;
        goto LABEL_END_OF_NO_TABLE;
    }

    if(u32_ErrRetry)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,0,"eMMC: retry ok\n");
        //eMMC_dump_mem((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t));
    }
    return u32_err;

    // ---------------------------------
    LABEL_END_OF_NO_TABLE:

    if(0==u32_ErrRetry)
    {
        //eMMC_dump_mem((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t));
        u32_ErrRetry++;
        goto LABEL_RETRY;
    }
    return u32_err;
}

#define MAX_DETECT_BLK_CNT   2048 // 0.5MB
U32 eMMC_SaveBurstLenTable(void)
{
    U32 u32_Err;
    U32 u32_t0, u32_t1, u32_tMax=0, u32_tMin=(U32)(0-1), u32_tmp;
    U16 u16_BurstBlkCnt, u16_BestBlkCnt=0, u16_WorstBlkCnt=0;
    U16 u16_i;

    //eMMC_debug(eMMC_DEBUG_LEVEL,0,"\neMMC: burst len...\n");
    // --------------------------
    g_eMMCDrv.BurstWriteLen_t.u32_ChkSum = ~g_eMMCDrv.BurstWriteLen_t.u32_ChkSum;
    g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen = 0;
    g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen = 0;

    //eMMC_CMD25(eMMC_TEST_BLK_0, gau8_eMMC_SectorBuf, eMMC_TEST_BLK_CNT);

    // --------------------------
    u16_BurstBlkCnt = 0;
    LABEL_DETECT:
    switch(u16_BurstBlkCnt)
    {
        //case 0:   u16_BurstBlkCnt = 8;  break; // 4KB
        case 0:   u16_BurstBlkCnt = 16;  break;// 8KB
        case 16:  u16_BurstBlkCnt = 32;  break;//16KB
        case 32:  u16_BurstBlkCnt = 64;  break;//32KB
        case 64:  u16_BurstBlkCnt = 128;  break;//64KB
        case 128: u16_BurstBlkCnt = 256;  break;//128KB
        case 256: u16_BurstBlkCnt = MAX_DETECT_BLK_CNT;
    }
    eMMC_hw_timer_start();
    u32_t0 = eMMC_hw_timer_tick();
    for(u16_i=0; u16_i<MAX_DETECT_BLK_CNT/u16_BurstBlkCnt; u16_i++)
    {
        u32_Err= eMMC_CMD25(eMMC_TEST_BLK_0, gau8_eMMC_SectorBuf, u16_BurstBlkCnt);
        if(eMMC_ST_SUCCESS != u32_Err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: w fail: %Xh\n", u32_Err);
            goto LABEL_END;
        }
    }
    eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
    u32_t1 = eMMC_hw_timer_tick();
    //eMMC_debug(0,0,"\n%u-%u=%8u, %3u ", u32_t1, u32_t0, u32_t1-u32_t0, u16_BurstBlkCnt);

    if(u32_tMin > u32_t1-u32_t0)
    {
        u32_tMin = u32_t1-u32_t0;
        u16_BestBlkCnt = u16_BurstBlkCnt;
    }
    if(u32_tMax < u32_t1-u32_t0)
    {
        u32_tMax = u32_t1-u32_t0;
        u16_WorstBlkCnt = u16_BurstBlkCnt;
    }

    if(MAX_DETECT_BLK_CNT != u16_BurstBlkCnt)
        goto LABEL_DETECT;

    // --------------------------
    g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen = u16_BestBlkCnt;
    g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen = u16_WorstBlkCnt;

    u32_tmp = (U32)(MAX_DETECT_BLK_CNT<<eMMC_SECTOR_512BYTE_BITS)*4000 /
        (u32_tMin/(eMMC_HW_TIMER_HZ/4000));
    u32_tmp /= 0x100000/10;
    g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSec = u32_tmp/10;
    g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSecPoint = u32_tmp%10;

    u32_tmp = (U32)(MAX_DETECT_BLK_CNT<<eMMC_SECTOR_512BYTE_BITS)*4000 /
        (u32_tMax/(eMMC_HW_TIMER_HZ/4000));
    u32_tmp /= 0x100000/10;
    g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSec = u32_tmp/10;
    g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSecPoint = u32_tmp%10;

    g_eMMCDrv.BurstWriteLen_t.u32_ChkSum =
        eMMC_ChkSum((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t)-4);

    u32_Err= eMMC_CMD25(eMMC_BURST_LEN_BLK_0, (U8*)&g_eMMCDrv.BurstWriteLen_t, 1);
    if(eMMC_ST_SUCCESS != u32_Err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: save fail: %Xh\n", u32_Err);
        goto LABEL_END;
    }

    // --------------------------
    LABEL_END:
    return u32_Err;

}
#endif

#ifdef STATIC_RELIABLE_TEST
extern int reliable_test_sleep; //ms
extern int enable_pm_sleep_flag;
#endif

U32 eMMC_GetR1(void)
{
    return (g_eMMCDrv.au8_Rsp[1]<<24) | (g_eMMCDrv.au8_Rsp[2]<<16)
        | (g_eMMCDrv.au8_Rsp[3]<<8) | g_eMMCDrv.au8_Rsp[4];
}

U32 eMMC_CheckR1Error(void)
{
    U32 u32_err = eMMC_ST_SUCCESS;
    //U8 u8_cs = 0;

    eMMC_FCIE_GetCMDFIFO(0, 3, (U16*)g_eMMCDrv.au8_Rsp);

    if(g_eMMCDrv.au8_Rsp[1] & (eMMC_ERR_R1_31_24>>24))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_31_24 \n ");
        u32_err = eMMC_ST_ERR_R1_31_24;
        goto LABEL_CHECK_R1_END;
    }

    if(g_eMMCDrv.au8_Rsp[2] & (eMMC_ERR_R1_23_16>>16))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_23_16 \n ");
        u32_err = eMMC_ST_ERR_R1_23_16;
        goto LABEL_CHECK_R1_END;
    }

    if(g_eMMCDrv.au8_Rsp[3] & (eMMC_ERR_R1_15_8>>8))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_15_8 \n ");
        u32_err = eMMC_ST_ERR_R1_15_8;
        goto LABEL_CHECK_R1_END;
    }

    if(g_eMMCDrv.au8_Rsp[4] & (eMMC_ERR_R1_7_0>>0))
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_7_0 \n ");
        u32_err = eMMC_ST_ERR_R1_7_0;
        goto LABEL_CHECK_R1_END;
    }

LABEL_CHECK_R1_END:

    /*u8_cs = (eMMC_FCIE_CmdRspBufGet(3) & (eMMC_R1_CURRENT_STATE>>8))>>1;
    printf("card state: %d ", u8_cs);
    switch(u8_cs) {
        case 0:     printf("(idle)\n"); break;
        case 1:     printf("(ready)\n");    break;
        case 2:     printf("(ident)\n");    break;
        case 3:     printf("(stby)\n"); break;
        case 4:     printf("(tran)\n"); break;
        case 5:     printf("(data)\n"); break;
        case 6:     printf("(rcv)\n");  break;
        case 7:     printf("(prg)\n");  break;
        case 8:     printf("(dis)\n");  break;
        default:    printf("(?)\n");    break;
    }*/

    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_dump_mem(g_eMMCDrv.au8_Rsp, eMMC_R1_BYTE_CNT);

        if(24==g_eMMCDrv.au8_Rsp[0] || 25==g_eMMCDrv.au8_Rsp[0] ||
           18==g_eMMCDrv.au8_Rsp[0] || 12==g_eMMCDrv.au8_Rsp[0])
            eMMC_FCIE_ErrHandler_ReInit();
    }
    return u32_err;
}


// ====================================================
#if defined(eMMC_UPDATE_FIRMWARE) && (eMMC_UPDATE_FIRMWARE)
#define  UPFW_SEC_WIAT_CNT   0x1000000
#define  UPFW_SEC_BYTE_CNT   (128*1024)
static U32 eMMC_UpFW_Samsung_Wait(void)
{
    U32 u32_err, u32_cnt, u32_st;

    for(u32_cnt=0; u32_cnt<UPFW_SEC_WIAT_CNT; u32_cnt++)
    {
        eMMC_CMD13(g_eMMCDrv.u16_RCA);
        //eMMC_dump_mem(g_eMMCDrv.au8_Rsp, 6);
        u32_st = (g_eMMCDrv.au8_Rsp[1]<<24) | (g_eMMCDrv.au8_Rsp[2]<<16) |
            (g_eMMCDrv.au8_Rsp[3]<<8) | (g_eMMCDrv.au8_Rsp[4]<<0);
        if(0x900 == u32_st)
            break;
        else
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"st: %Xh\n", u32_st);
        eMMC_hw_timer_delay(HW_TIMER_DELAY_1ms);
    }

    if(UPFW_SEC_WIAT_CNT == u32_cnt)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh\n", eMMC_ST_ERR_SEC_UPFW_TO);
        return eMMC_ST_ERR_SEC_UPFW_TO;
    }
    return eMMC_ST_SUCCESS;
}

U32 eMMC_UpFW_Samsung(U8 *pu8_FWBin)
{
    U16 u16_ctrl;
    U32 u32_err, u32_arg=0xEFAC60FC;

    // ---------------------------
    LABEL_CMD60:
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"CMD60: %Xh\n", u32_arg);
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 60, eMMC_R1b_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD60 fail, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }
    u32_err = eMMC_UpFW_Samsung_Wait();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 1, Arg:%Xh \n", u32_arg);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }
    if(0xEFAC60FC == u32_arg)
    {
        u32_arg=0xCBAD1160;
        goto LABEL_CMD60;
    }

    #if 1
    // ---------------------------
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"erase ... \n");
    g_eMMCDrv.u32_eMMCFlag &= ~eMMC_FLAG_TRIM;
    u32_err = eMMC_EraseCMDSeq(0, 0);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: erase fail, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }
    u32_err = eMMC_UpFW_Samsung_Wait();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 2, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }
    #endif

    // ---------------------------
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"write ... \n");
    u32_err = eMMC_CMD25_MIU(0, pu8_FWBin, UPFW_SEC_BYTE_CNT>>eMMC_SECTOR_512BYTE_BITS);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: write fail, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }
    u32_err = eMMC_UpFW_Samsung_Wait();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 3, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }

    // ---------------------------
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"close ... \n");
    u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

    eMMC_FCIE_ClearEvents();
    u32_err = eMMC_FCIE_SendCmd(
        g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, 0, 28, eMMC_R1b_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD28 fail, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }
    u32_err = eMMC_UpFW_Samsung_Wait();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 4, %Xh \n", u32_err);
        eMMC_FCIE_ErrHandler_Stop();
        goto LABEL_END_OF_UPFW;
    }

    LABEL_END_OF_UPFW:
    return u32_err;

}
#endif 

#endif 
#endif

