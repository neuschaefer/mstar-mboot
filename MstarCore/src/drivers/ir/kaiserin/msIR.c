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

#define MS_IR_C

/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include <common.h>
#include <MsTypes.h>
#include <ShareType.h>

#include <drvIR.h>
#include <MsIRQ.h>
#include <MsOS.h>
#include <MsUboot.h>
#include "msIR.h"

static void MDrv_IR_SW_Isr(MHAL_SavedRegisters *pHalReg, U32 vector);

/// MS Return Error
#define MSRET_ERROR     0
/// MS Return OK
#define MSRET_OK        1
/// MS Return Other
#define MSRET_OTHER     2

#ifndef UNUSED
#define UNUSED(x) ((x)=(x))
#endif

#define RIU_MAP  0xBF000000 // PM bank

#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
#define IR_NEW_METHOD   1
#if IR_NEW_METHOD
static MS_S32 u32Mutex_IR;
#define msIR_InitLock()     {\
                                u32Mutex_IR = OS_CREATE_MUTEX(IR_DEC);\
                                if(u32Mutex_IR<0) printf("!!!Acquire Send Mutex for SWI2C Failed!\n");\
                            }
#define msIR_DeInitLock()   OS_DELETE_MUTEX(u32Mutex_IR)
#define msIR_Lock()         OS_OBTAIN_MUTEX(u32Mutex_IR, MSOS_WAIT_FOREVER)
#define msIR_UnLock()       OS_RELEASE_MUTEX(u32Mutex_IR)

static U8 g_u8IRKey=0xFF;
static U8 g_u8IRRpt=0;
static BOOLEAN g_u8IRRes=MSRET_ERROR;
#define IR_NEC_INTERVAL 300
#else
#define IR_NEC_INTERVAL 108
#endif
#define IR_NEC_TIMEOUT  120
static U8 u8RepeatCount;
static U32 gIRTimeCount = 0;

U32 gIRTimeOutCount = 0;
U8 u8IRTimerBlockstatus;

//extern int putchar(int c);

#define IRPRINT(a)    //a
#define IRCHAR(a)     putc(a)

U8 g_ucIrPulseCntIndex = 0;
//U8 g_bIrHold = 0;
U16 g_wIrPulseCounter = 0;
U8 g_ucIrRepeatTimer = 0;

U8 g_ucIrByteIndex = 0;
//U8 g_ucIrCode[10];
U8 g_bIrStartReceived = FALSE;
U8 g_ucIrRepeatSkipCnt = IR_REPEAT_SKIP_COUNT;

//U8 g_bIrDetect = FALSE;//!<IR command detect flag
U8 g_bIrRepeat = FALSE;//!<IR Repeat code ¼ö½Å flag

static BOOLEAN g_bIsIrModeSwitchedToSWmode;

//U8 g_bIrKeypadMenuHold = FALSE; //test
//U8 g_bIrRcMenuHold = FALSE; // test

#elif (IR_MODE_SEL == IR_TYPE_RAWDATA_MODE)
static U8 u8IRRawModeDone;
static U8 u8IRRawModeCount;
static U8 u8IRRawModeBuf[IR_RAW_DATA_NUM];
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
#define IRCHAR(a)     putc(a)
// pulse width modulation format: Header(1)+CusterCode(8)+Data(8)+Stop(1)
#define IR_KON_DATA_BITS          18       //

#define IR_KON_DETECT_START         BIT0   // start to detect IR int
#define IR_KON_DETECT_END             BIT1   // end to detect IR int

#define IR_KON_COUNTER_ERROR        BIT6   // for temp use
#define IR_KON_REPEATE_TIMEOUT      BIT5

#define IRCHAR(a) //putc(a)

U8 volatile g_u8IrKonFlag;            // for store bit var
U8 volatile g_u8IrKonBits;                // for store bit count
U16 volatile g_u16IrKonCounter;         // for read counter from register
U16 volatile g_u16IrKonData;    // store shift data
U16 volatile g_u16IrKonDecode;    // store shift data
U8 g_u8IrKonRepeatCount;    // for repeat
U8 g_u8IrKonPreKey;
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
#define IRCHAR(a) //putc(a)
#define IRCHARVALUE(a) //putcharvalue(a)
#define BUF_LEN 10;
#if 1
U8 g_bIrDetect = FALSE;
static BOOLEAN g_bIsIrModeSwitchedToSWmode=TRUE;
U16 g_wIrPulseCounter = 0;
static U8 BufIdx=0;
static U16 BuffeRX=0;
static U16 BufferCurrent=0;
static U8 BufLenCurrent=0;
static U16 BufferPrev=0;
static U8 DataPlusExDat0;
static U8 DataPlusExDat1;
static U8 LastKeyData=0xFF;
static U8 IsRepeatData=0;
static U16 keyDatArray[10];
static U16 keyDatLenArray[10];
static U8 keyDatArrayWTIdx=0 ;
static U8 keyDatArrayRDIdx=0 ;
BOOLEAN CodeReceived=FALSE;
static BOOLEAN ExpetedTCome=FALSE;
BOOLEAN SystemBitOK=FALSE;
BOOLEAN DetectBitOK=FALSE;
static BOOLEAN    FirstRXFlag=FALSE;
BOOLEAN   SecondRXFlag=FALSE;
static BOOLEAN   DataMatched=FALSE;
U8 j;
static U32 RxTimeOutCount;
static U32 CurrentTime;
static BOOLEAN RxInProcess=FALSE;
static U32 KeyOffTimeOutCount;
static BOOLEAN ReceivingMode=FALSE;
static BOOLEAN SetToStandbyMode=FALSE;
U8 u8Cus21SHTableSize ;
U8 TableIdx;
BOOLEAN keyValueHit;
#else//moving to Sramvar.h when using Standby Mode SHA IR
/*
INTERFACE U8   g_bIrDetect ;
INTERFACE  bit  g_bIsIrModeSwitchedToSWmode;
INTERFACE U16 volatile  g_wIrPulseCounter;
INTERFACE  U8  volatile BufIdx;
INTERFACE  U16  volatile BuffeRX;
INTERFACE  U16  volatile  BufferCurrent;
INTERFACE  U8  volatile BufLenCurrent;
INTERFACE  U16 volatile BufferPrev;
INTERFACE  U8 volatile DataPlusExDat0;
INTERFACE  U8 volatile DataPlusExDat1;
INTERFACE  U8  LastKeyData;
INTERFACE  U8  IsRepeatData;
INTERFACE  U16  keyDatArray[10];
INTERFACE  U8  keyDatArrayWTIdx;
INTERFACE  U8  keyDatArrayRDIdx;
INTERFACE bit  CodeReceived;
INTERFACE  bit  ExpetedTCome;
INTERFACE bit  SystemBitOK;
INTERFACE bit  DetectBitOK;
INTERFACE  bit    FirstRXFlag;
INTERFACE bit   SecondRXFlag;
INTERFACE  bit   DataMatched;
INTERFACE U8  j;
INTERFACE  U32  RxTimeOutCount;
INTERFACE  U32  CurrentTime;
INTERFACE  bit  RxInProcess;
INTERFACE  U32  KeyOffTimeOutCount;
INTERFACE  bit  ReceivingMode;
INTERFACE  bit  SetToStandbyMode;
INTERFACE U8  u8Cus21SHTableSize ;
INTERFACE U8  TableIdx;
INTERFACE  bit keyValueHit;

*/
U8 temp;

#endif
U8 u8Key;
U8 u8Flag;
#else
U32 gIRKey;
U8 gIRCount;
//#endif

#endif

#define IR_DEBUG(x)    //x

#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
static U8 u8PrevIrKey = 0;
#endif
//*************************************************************************
//Function name:    msIR_ReadByte
//Passing parameter: U16 u16RegIndex:   register address
//Return parameter: U8 u8Value: value
//Description: read register value
//*************************************************************************
#if (ROBUST_TEST_ENABLE)
extern U8 RobustBuf[8], RobustIndex;
U8 msIR_ReadByte( U16 u16RegIndex )
{
    U8 RetVal, i;
    if (u16RegIndex == IR_RPT_FIFOEMPTY)
    {
        if(RobustIndex == 0)
        {
            RetVal = 0x02;
        }
        else
            RetVal = 0x00;
    }

    else if (u16RegIndex == IR_KEY)
    {
        if(RobustIndex == 0)
        {
            RetVal = 0xFF;
        }
        else
        {
            RetVal = RobustBuf[0];

            for(i=0; i<RobustIndex; i++)
            {
                RobustBuf[i] = RobustBuf[i+1];
            }
            RobustBuf[RobustIndex--] = 0;
        }
    }
    else
        RetVal = MDrv_ReadByte(u16RegIndex);

    return RetVal;
}
#else
U8 msIR_ReadByte( U16 u16RegIndex )
{
    return MDrv_ReadByte(u16RegIndex);
}
#endif

U8 msIR_GetIrKeyData( void )
{
    U8 IrKeyData;

    IrKeyData = MDrv_ReadByte(IR_KEY);
    MDrv_WriteByte(IR_FIFO_READ_PULSE, MDrv_ReadByte(IR_FIFO_READ_PULSE)| 0x01);

    return(IrKeyData);
}


//*************************************************************************
//Function name:    msIR_WriteByte
//Passing parameter: U16 u16RegIndex:   register address
//                   U8  u8Value:       value
//Return parameter:     none
//Description: write 2 register values
//*************************************************************************
void msIR_WriteByte(U16 u16RegIndex, U8 u8Value)
{
//    MDrv_WriteByte(u16RegIndex, u8Value);
    *((unsigned char volatile *) RIU_MAP + ((u16RegIndex << 1)-(u16RegIndex & 1))) = u8Value;
}

//*************************************************************************
//Function name:    msIR_Write2Byte
//Passing parameter: U16 u16RegIndex:   register address
//                   U16 u16Value:      value
//Return parameter:     none
//Description: write 2 register values
//*************************************************************************
void msIR_Write2Byte( U16 u16RegIndex, U16 u16Value )
{
    //MDrv_Write2Byte(u16RegIndex, u16Value);
    *((unsigned short volatile *) RIU_MAP + u16RegIndex) = u16Value;
}

//*************************************************************************
//Function name:    msIR_Write3Byte
//Passing parameter: U16 u16Regndex:   register address
//                   U32 u32Value:   value
//Return parameter:     none
//Description: write 3 register values
//*************************************************************************
void msIR_Write3Byte( U16 u16RegIndex, U32 u32Value )
{
    //MDrv_Write3Byte(u16RegIndex, u32Value);
    *((unsigned short volatile *) RIU_MAP + u16RegIndex) = (U16)(u32Value&0xFFFF);
    MDrv_WriteByte((u16RegIndex+2), (U8)((u32Value>>16)&0xff));
}

void msIR_Clear_FIFO(void)
{
    #if((IR_MODE_SEL==IR_TYPE_RAWDATA_MODE) || (IR_MODE_SEL==IR_TYPE_FULLDECODE_MODE))
    U8 i;

    for ( i = 0; i < 8; i++ )
    {
        U8 garbage;

        if ( MDrv_ReadByte(IR_RPT_FIFOEMPTY) & 0x2 )
        {
            break;
        }

        garbage = msIR_GetIrKeyData();

        garbage = MDrv_ReadByte(IR_RPT_FIFOEMPTY);
    }
    #endif
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#if (IR_MODE_SEL == IR_TYPE_HWDECODE_RC)
//#######################################
//#  For Hardware RC Decode
//#  IR RC Operation Frequency(<5M) :  1 ~ 2MHz
//#     ==> Based on 3/2=1.5 MHz
//#######################################
#define IR_RC5_BIT_TIME             1778 //us
#define IR_RC6_BIT_TIME             889 //us
#define IR_RC_CLK_DIV(ClkMhz)       (ClkMhz*2/3-1)
#define IR_RC_LGPS_THR(UnitTime)    ((UnitTime)*9/8)        //(UnitTime)*(3/2)*(3/4)
#define IR_RC_INTG_THR(UnitTime)    (((UnitTime)*3/4-7)/8) //((UnitTime)*(3/2)*(1/2)-7)/8
#define IR_RC_WDOG_CNT(UnitTime)    ((UnitTime)*3/2048)     //(UnitTime)*(3/2)/1024
#define IR_RC_TMOUT_CNT(UnitTime)   ((UnitTime)*3/4096)     //(UnitTime)*(3/2)/2048
#define IR_RC6_LDPS_THR(UnitTime)   ((UnitTime)-31)         //(UnitTime)*(3/2)*(2/3)
#define IR_RC6_LGPS_MAR(UnitTime)   ((UnitTime)*3/4)        //(UnitTime)*(3/2)*(1/2)

void HAL_IR_CfgHwDecode(U8 u8Enable)//for Full/Raw decode mode
{
    HAL_IR_CfgSetControl(REG_IR_CTRL0, ((u8Enable)? _IR_HWDEC_EN : 0), _IR_HWDEC_EN);
}

void HAL_IR_CfgIntrMask(U8 u8Enable)
{
    HAL_IR_CfgSetControl(REG_IR_CTRL0, ((u8Enable)? _IR_INT_MSK:0), _IR_INT_MSK);
}

U32 HAL_IR_GetTimeInerval(void)
{
    U8 u8RCDecode;

    u8RCDecode = HAL_IR_RC_GetDecode();
    switch(u8RCDecode)
    {
        case HAL_IR_RC_RC5:
            return HAL_IR_RC5_INTERVAL;
        case HAL_IR_RC_RC6:
            return HAL_IR_RC6_INTERVAL;
        case HAL_IR_RC_DISABLE:
            return HAL_IR_NEC_INTERVAL;
        default:
            break;
    }
    return 0xFFFF;
}

U32 HAL_IR_GetTimeout(void)
{
    U8 u8RCDecode;

    u8RCDecode = HAL_IR_RC_GetDecode();
    switch(u8RCDecode)
    {
        case HAL_IR_RC_RC5:
            return HAL_IR_RC5_TIMEOUT;
        case HAL_IR_RC_RC6:
            return HAL_IR_RC6_TIMEOUT;
        case HAL_IR_RC_DISABLE:
            return HAL_IR_NEC_TIMEOUT;
        default:
            break;
    }
    return 0xFFFF;
}

void HAL_IR_CfgSetControl(U32 u32Reg,U8 u8CtrlData,U8 u8Mask)
{
    MDrv_WriteByte(u32Reg, ((MDrv_ReadByte(u32Reg) & (~u8Mask)) | (u8CtrlData & u8Mask)));
}

void HAL_IR_CfgControl(U8 u8Index, U8 u8CtrlData,U8 u8Mask)
{
    //IR control
    switch(u8Index)
    {
        case HAL_IR_RC_CTRL_0:
            HAL_IR_CfgSetControl(REG_IR_RC_CTRL0,u8CtrlData,u8Mask);
            break;
        case HAL_IR_RC_CTRL_1:
            HAL_IR_CfgSetControl(REG_IR_RC_CTRL1,u8CtrlData,u8Mask);
            break;
        default:
            break;
    }
}

U8 HAL_IR_RC_GetDecode(void)
{
    U8 u8CtlVal,u8Decode;

    u8CtlVal = MDrv_ReadByte(REG_IR_RC_CTRL1);
    if(!(u8CtlVal & _IR_RC_ENABLE))
        return HAL_IR_RC_DISABLE;
    if(u8CtlVal & _IR_RC_RC6_EN)
    {
        u8Decode = HAL_IR_RC_RC6;
    }
    else
    {
        if(u8CtlVal & _IR_RC_RC5X_EN)
            u8Decode = HAL_IR_RC_RC5X;
        else
            u8Decode = HAL_IR_RC_RC5;
    }
    return u8Decode;
}

void HAL_IR_RC_CfgClkDiv(U8 u8ClkMhz)
{
    U8 u8Value;

    u8Value = (MDrv_ReadByte(REG_IR_RC_CLK_DIV) & (~_IR_RC_CLK_DIV_MSK)) | (IR_RC_CLK_DIV(u8ClkMhz) & _IR_RC_CLK_DIV_MSK);
    MDrv_WriteByte(REG_IR_RC_CLK_DIV,u8Value);
}

void HAL_IR_RC_CfgAutoConfig(U8 u8Enable)
{
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL0, ((u8Enable)? _IR_RC_AUTOCONFIG : 0), _IR_RC_AUTOCONFIG);
}

void HAL_IR_RC_CfgFifoClear(U8 u8Enable)
{
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL0, ((u8Enable)? _IR_RC_FIFO_CLR : 0), _IR_RC_FIFO_CLR);
}

void HAL_IR_RC_CfgFifoWFirst(U8 u8Enable)
{
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL0, ((u8Enable)? _IR_RC_FIFO_WFST : 0), _IR_RC_FIFO_WFST);
}

void HAL_IR_RC_CfgDecMode(U8 u8DecMode)
{
    U8 u8CtrlData;

    switch(u8DecMode)
    {
        case HAL_IR_RC_RC5:
            u8CtrlData = (_IR_RC_ENABLE);
            break;
        case HAL_IR_RC_RC5X:
            u8CtrlData = (_IR_RC_RC5X_EN|_IR_RC_ENABLE);
            break;
        case HAL_IR_RC_RC6:
            u8CtrlData = (_IR_RC_RC6_EN|_IR_RC_ENABLE);
            break;
        case HAL_IR_RC_DISABLE:
        default:
            u8CtrlData = 0;
            break;
    }
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL1, u8CtrlData, _IR_RC_MODE_MSK);
}

void HAL_IR_RC_CfgWakeup(U8 u8Enable)
{
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL1, ((u8Enable)? _IR_RC_WKUP_EN : 0), _IR_RC_WKUP_EN);
}

void HAL_IR_RC_CfgOutputSelect(U8 u8OutputSel)
{
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL1, u8OutputSel, _IR_RC_DGB_SEL);
}

void HAL_IR_RC_CfgInputInvert(U8 u8Enable)
{
    HAL_IR_CfgSetControl(REG_IR_RC_CTRL1, ((u8Enable)? _IR_RC_IN_INV : 0), _IR_RC_IN_INV);
}

void HAL_IR_RC_CfgLgpsThr(void)
{
    U16 u16RefTime,u16LongPulseThr;
    //U8 u8Value,u8LgpsThr;
    U8 u8RCDecode;

    //get rc decode type
    u8RCDecode = HAL_IR_RC_GetDecode();
    if(u8RCDecode==HAL_IR_RC_DISABLE)
        return;
    //setup unit time
    switch(u8RCDecode)
    {
        case HAL_IR_RC_RC5:
        case HAL_IR_RC_RC5X: u16RefTime = IR_RC5_BIT_TIME; break;
        case HAL_IR_RC_RC6: u16RefTime = IR_RC6_BIT_TIME; break;
        default: u16RefTime = 0; break;
    }
    //get config value
    u16LongPulseThr = (U16)IR_RC_LGPS_THR(u16RefTime);
    printf("[LGPS]: u16LongPulseThr = %04X\n",u16LongPulseThr);
    //configure
    //u8LgpsThr = (U8)(u16LongPulseThr & _IR_RC_LGPS_THR_L_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_LGPS_THR_L) | u8LgpsThr;
    //MDrv_WriteByte(REG_IR_RC_LGPS_THR_L, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_LGPS_THR_L, (U8)u16LongPulseThr, _IR_RC_LGPS_THR_L_MSK);

    //u8LgpsThr = (U8)((u16LongPulseThr>>8) & _IR_RC_LGPS_THR_H_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_LGPS_THR_H) | u8LgpsThr;
    //MDrv_WriteByte(REG_IR_RC_LGPS_THR_H, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_LGPS_THR_H, (U8)(u16LongPulseThr>>8), _IR_RC_LGPS_THR_H_MSK);
}

void HAL_IR_RC_CfgIntgThr(void)
{
    U16 u16RefTime,u16IntegrationThr;
    //U8 u8Value,u8IntgThr;
    U8 u8RCDecode;

    //get rc decode type
    u8RCDecode = HAL_IR_RC_GetDecode();
    if(u8RCDecode==HAL_IR_RC_DISABLE)
        return;
    //setup unit time
    switch(u8RCDecode)
    {
        case HAL_IR_RC_RC5:
        case HAL_IR_RC_RC5X: u16RefTime = (IR_RC5_BIT_TIME / 2); break;
        case HAL_IR_RC_RC6: u16RefTime = (IR_RC6_BIT_TIME / 2); break;
        default: u16RefTime = 0; break;
    }
    //get config value
    u16IntegrationThr = (U16)IR_RC_INTG_THR(u16RefTime);
    printf("[INTG]: u16IntegrationThr = %04X\n",u16IntegrationThr);
    //configure
    //u8IntgThr = (U8)((u16IntegrationThr<<1) & _IR_RC_INTG_THR_MSK);
    //u8IntgThr = (U8)((u16IntegrationThr) & _IR_RC_INTG_THR_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_INTG_THR) | u8IntgThr;
    //MDrv_WriteByte(REG_IR_RC_INTG_THR, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_INTG_THR, (U8)(u16IntegrationThr<<1), _IR_RC_INTG_THR_MSK);
}

void HAL_IR_RC_CfgWdogCount(void)
{
    U16 u16RefTime;
    U8 u8WatchDogCount;
    U8 u8RCDecode;

    //get rc decode type
    u8RCDecode = HAL_IR_RC_GetDecode();
    if(u8RCDecode==HAL_IR_RC_DISABLE)
        return;
    //setup unit time
    switch(u8RCDecode)
    {
        case HAL_IR_RC_RC5:
        case HAL_IR_RC_RC5X: u16RefTime = (IR_RC5_BIT_TIME * 14); break;
        case HAL_IR_RC_RC6: u16RefTime = (IR_RC6_BIT_TIME * 29); break;
        default: u16RefTime = 0; break;
    }
    //get config value
    u8WatchDogCount = (U8)IR_RC_WDOG_CNT(u16RefTime);
    printf("[WDOG]: u8WatchDogCount = %04X\n",u8WatchDogCount);
    //configure
    MDrv_WriteByte(REG_IR_RC_WDOG_COUNT, u8WatchDogCount);
}

void HAL_IR_RC_CfgTimeoutCount(void)
{
    U16 u16RefTime;
    U8 u8TimeoutCount;

    //setup unit time
    u16RefTime = (U16)HAL_IR_GetTimeout();
    //get config value
    u8TimeoutCount = (U8)IR_RC_TMOUT_CNT(u16RefTime);
    //configure
    MDrv_WriteByte(REG_IR_RC_TIMEOUT_COUNT, u8TimeoutCount);
}

void HAL_IR_RC_CfgLgpsMar(void)//Only for RC6
{
    U16 u16RefTime,u16LongPulseMar;
    //U8 u8Value,u8LgpsMar;

    //get rc decode type
    if(HAL_IR_RC_GetDecode()!=HAL_IR_RC_RC6)
        return;
    //setup unit time
    u16RefTime = (IR_RC6_BIT_TIME / 2);
    //get config value
    u16LongPulseMar = (U16)IR_RC6_LGPS_MAR(u16RefTime);
    //configure
    //u8LgpsMar = (U8)(u16LongPulseMar & _IR_RC_RC6_LGPS_MAR_L_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_RC6_LGPS_MAR_L) | u8LgpsMar;
    //MDrv_WriteByte(REG_IR_RC_RC6_LGPS_MAR_L, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_RC6_LGPS_MAR_L, (U8)u16LongPulseMar, _IR_RC_RC6_LGPS_MAR_L_MSK);

    //u8LgpsMar = (U8)((u16LongPulseMar>>8) & _IR_RC_RC6_LGPS_MAR_H_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_RC6_LGPS_MAR_H) | u8LgpsMar;
    //MDrv_WriteByte(REG_IR_RC_RC6_LGPS_MAR_H, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_RC6_LGPS_MAR_H, (U8)(u16LongPulseMar>>8), _IR_RC_RC6_LGPS_MAR_H_MSK);
}

void HAL_IR_RC_CfgLdpsThr(void)//Only for RC6
{
    U16 u16RefTime,u16LeadPulseThr;
    //U8 u8Value,u8LdpsThr;

    //get rc decode type
    if(HAL_IR_RC_GetDecode()!=HAL_IR_RC_RC6)
        return;
    //setup unit time
    u16RefTime = (IR_RC6_BIT_TIME * 3);
    //get config value
    u16LeadPulseThr = (U16)IR_RC6_LDPS_THR(u16RefTime);
    //configure
    //u8LdpsThr = (U8)((u16LeadPulseThr>>5) & _IR_RC_RC6_LDPS_THR_L_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_RC6_LDPS_THR_L) | u8LdpsThr;
    //MDrv_WriteByte(REG_IR_RC_RC6_LDPS_THR_L, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_RC6_LDPS_THR_L, (U8)(u16LeadPulseThr>>5), _IR_RC_RC6_LDPS_THR_L_MSK);

    //u8LdpsThr = (U8)((u16LeadPulseThr>>8) & _IR_RC_RC6_LDPS_THR_H_MSK);
    //u8Value = MDrv_ReadByte(REG_IR_RC_RC6_LDPS_THR_H) | u8LdpsThr;
    //MDrv_WriteByte(REG_IR_RC_RC6_LDPS_THR_H, u8Value);
    HAL_IR_CfgSetControl(REG_IR_RC_RC6_LDPS_THR_H, (U8)(u16LeadPulseThr>>8), _IR_RC_RC6_LDPS_THR_H_MSK);
}

void HAL_IR_RC_CfgEcoFunc(BOOLEAN bEnable)//Only for RC6
{
    U8 u8Value;

    //get rc decode type
    if(HAL_IR_RC_GetDecode()!=HAL_IR_RC_RC6)
        return;
    if(bEnable)
        u8Value = MDrv_ReadByte(REG_IR_RC_RC6_ECO_EN) | _IR_RC_RC6_ECO_EN;
    else
        u8Value = MDrv_ReadByte(REG_IR_RC_RC6_ECO_EN) & (~_IR_RC_RC6_ECO_EN);
    MDrv_WriteByte(REG_IR_RC_RC6_ECO_EN, u8Value);
}

BOOLEAN HAL_IR_RC_IsTimeout(void)
{
    return (MDrv_ReadByte(REG_IR_RC_FIFO_STATUS1) & _IR_RC_TIMEOUT_FLAG)? TRUE : FALSE;
}

BOOLEAN HAL_IR_RC_IsFIFOEmpty(void)
{
    return (MDrv_ReadByte(REG_IR_RC_FIFO_STATUS1) & _IR_RC_FIFO_EMPTY)? TRUE : FALSE;
}

BOOLEAN HAL_IR_RC_IsFIFOFull(void)
{
    return (MDrv_ReadByte(REG_IR_RC_FIFO_STATUS1) & _IR_RC_FIFO_FULL)? TRUE : FALSE;
}

void HAL_IR_RC_ClearFIFO(void)
{
#if 1
    HAL_IR_RC_KeyData IRRCKeyData;
    U8 i,u8Garbage;
    U8 u8FifoDepth=HAL_IR_RC_FIFO_DEPTH_MAX;

    for ( i=0; i<=u8FifoDepth; i++ )
    {
        if (HAL_IR_RC_IsFIFOEmpty())
        {
            break;
        }
        #if 1
        HAL_IR_RC_GetKeyData(&IRRCKeyData);
        u8Garbage = MDrv_ReadByte(REG_IR_RC_FIFO_STATUS1);
        #else
        MDrv_WriteByte(REG_IR_RC_FIFO_READ_PULSE, MDrv_ReadByte(REG_IR_RC_FIFO_READ_PULSE)|_IR_RC_FIFO_RD_PULSE);
        #endif
    }
 #else
    HAL_IR_RC_CfgFifoClear(ENABLE);
 #endif
}

U8 HAL_IR_RC_GetWakeupKey(U8 u8KeyNum)
{
    switch(u8KeyNum)
    {
        case HAL_IR_RC_WKUP_KEY1:
            return MDrv_ReadByte(REG_IR_RC_COMP_KEY1);
        case HAL_IR_RC_WKUP_KEY2:
            return MDrv_ReadByte(REG_IR_RC_COMP_KEY2);
        default:
            break;
    }
    return 0xFF;
}

void HAL_IR_RC_GetKeyData(HAL_IR_RC_KeyData *pIRRCKeyData)
{
    U8 u8KeyAddr,u8KeyCmd,u8RC6KeyMisc;
    U8 u8RCDecode;

    //get rc decode type
    u8RCDecode = HAL_IR_RC_GetDecode();
    if(u8RCDecode==HAL_IR_RC_DISABLE)
    {
        pIRRCKeyData->u8Valid =0;
        return;
    }
    //get key address
    u8KeyAddr = MDrv_ReadByte(REG_IR_RC_KEY_ADDR);
    u8KeyCmd = MDrv_ReadByte(REG_IR_RC_KEY_CMD);
    u8RC6KeyMisc = MDrv_ReadByte(REG_IR_RC_RC6_KEY_MISC);
    switch(u8RCDecode)
    {
        case HAL_IR_RC_RC5:
        case HAL_IR_RC_RC5X:
            //if(u8RCDecode==HAL_IR_RC_RC5)
            //    printf("HAL_IR_RC_RC5\n");
            //else
            //    printf("HAL_IR_RC_RC5X\n");
            pIRRCKeyData->u8Address = u8KeyAddr & _IR_RC_RC5_KEY_ADDR_MSK;
            pIRRCKeyData->u8Toggle = (u8KeyAddr & _IR_RC_RC5_KEY_ADDR_TGL)? 1:0;
            if(u8RCDecode==HAL_IR_RC_RC5)
                pIRRCKeyData->u8Command = u8KeyCmd & _IR_RC_RC5_KEY_CMD_MSK;
            else
                pIRRCKeyData->u8Command = u8KeyCmd & _IR_RC_RC5X_KEY_CMD_MSK;
            pIRRCKeyData->u8Repeat =  (u8KeyCmd & _IR_RC_RC5_KEY_CMD_RPT)? 1:0;
            pIRRCKeyData->u8Valid =1;
            break;
        case HAL_IR_RC_RC6:
            //printf("HAL_IR_RC_RC6\n");
            pIRRCKeyData->u8Address = u8KeyAddr & _IR_RC_RC6_KEY_ADDR_MSK;
            pIRRCKeyData->u8Command = u8KeyCmd & _IR_RC_RC6_KEY_CMD_MSK;
            pIRRCKeyData->u8Toggle = (u8RC6KeyMisc & _IR_RC_RC6_KEY_MISC_TGL)? 1:0;
            pIRRCKeyData->u8Repeat =  (u8RC6KeyMisc & _IR_RC_RC6_KEY_MISC_RPT)? 1:0;
            pIRRCKeyData->u8RC6Mode =  u8RC6KeyMisc & _IR_RC_RC6_KEY_MISC_MOD_MSK;
            pIRRCKeyData->u8Valid =1;
            break;
        default:
            pIRRCKeyData->u8Valid =0;
            break;
    }
    //write rc read pulse gen
    MDrv_WriteByte(REG_IR_RC_FIFO_READ_PULSE, MDrv_ReadByte(REG_IR_RC_FIFO_READ_PULSE)|_IR_RC_FIFO_RD_PULSE);

}
#endif


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void msIR_Initialize(U8 irclk_mhz)
{
    //printf("msIR_Initialize\n");
    // initialize variables
#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
    u8RepeatCount = 0;
    u8IRTimerBlockstatus = 0;
    gIRTimeOutCount = 0;
   g_bIsIrModeSwitchedToSWmode = FALSE;
    /* SW IR */
    msIR_ResetSoftWareModeVariables();

#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
    g_u8IrKonBits = 0;
    g_u8IrKonFlag  = 0;
    g_u8IrKonRepeatCount = 10;
    g_u8IrKonRepeatTimeout = 0;
    g_u8IrKonPreKey = 0xFF;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
    g_u16IrRc5Data = 0;
    g_u8IrRc5Bits = 0;
    g_u8IrRc5Flag = 0;
    g_u8IrRc5RepeatCount = 10;
#elif(IR_MODE_SEL == IR_TYPE_RAWDATA_MODE)
    u8IRRawModeDone = 0;
    u8IRRawModeCount = 0;
    g_bIsIrModeSwitchedToSWmode = FALSE;
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)

#endif

    #if (ROBUST_TEST_ENABLE)
    memset(RobustBuf, 0x00, sizeof(RobustBuf));
    RobustIndex = 0;
    ES = 1;
    #endif

    msIR_WriteByte(IR_CTRL, IR_LEADER_CODE_CHECKING_OPTION);     // enable control
    msIR_WriteByte(IR_CHECK, 0X01);    // enable timerout

    #define msIR_GetCnt(time, tolerance) \
    ((time) * (100UL + (tolerance)) * (irclk_mhz) / ((irclk_mhz) + 1) / 100)

    // header code upper bound
    msIR_Write2Byte(IR_HDC_UPB_L, msIR_GetCnt(IR_HEADER_CODE_TIME, IR_HEADER_CODE_TIME_UB));
    // header code lower bound
    msIR_Write2Byte(IR_HDC_LOB_L, msIR_GetCnt(IR_HEADER_CODE_TIME, IR_HEADER_CODE_TIME_LB));
    // off code upper bound
    msIR_Write2Byte(IR_OFC_UPB_L, msIR_GetCnt(IR_OFF_CODE_TIME, IR_OFF_CODE_TIME_UB));
    // off code lower bound
    msIR_Write2Byte(IR_OFC_LOB_L, msIR_GetCnt(IR_OFF_CODE_TIME, IR_OFF_CODE_TIME_LB));
    // off code repeat upper bound
    msIR_Write2Byte(IR_OFC_RP_UPB_L, msIR_GetCnt(IR_OFF_CODE_RP_TIME, IR_OFF_CODE_RP_TIME_UB));
    // off code repeat lower bound
    msIR_Write2Byte(IR_OFC_RP_LOB_L, msIR_GetCnt(IR_OFF_CODE_RP_TIME, IR_OFF_CODE_RP_TIME_LB));
    // logical 0/1 high upper bound
    msIR_Write2Byte(IR_LG01H_UPB_L, msIR_GetCnt(IR_LOGI_01H_TIME, IR_LOGI_01H_TIME_UB));
    // logical 0/1 high lower bound
    msIR_Write2Byte(IR_LG01H_LOB_L, msIR_GetCnt(IR_LOGI_01H_TIME, IR_LOGI_01H_TIME_LB));
    // logical 0 upper bound
    msIR_Write2Byte(IR_LG0_UPB_L, msIR_GetCnt(IR_LOGI_0_TIME, IR_LOGI_0_TIME_UB));
    // logical 0 lower bound
    msIR_Write2Byte(IR_LG0_LOB_L, msIR_GetCnt(IR_LOGI_0_TIME, IR_LOGI_0_TIME_LB));
    // logical 1 upper bound
    msIR_Write2Byte(IR_LG1_UPB_L, msIR_GetCnt(IR_LOGI_1_TIME, IR_LOGI_1_TIME_UB));
    // logical 1 lower bound
    msIR_Write2Byte(IR_LG1_LOB_L, msIR_GetCnt(IR_LOGI_1_TIME, IR_LOGI_1_TIME_LB));
    // Ir timerout counter
    msIR_Write3Byte(IR_TIMEOUT_CYC_0, msIR_GetCnt(IR_TIMEOUT_CYC, 0) + 0x300000UL);

    msIR_WriteByte(IR_CKDIV_NUM_REG, irclk_mhz);

    msIR_WriteByte(IR_CCODE_L, IR_HEADER_CODE0);
    msIR_WriteByte(IR_CCODE_H, IR_HEADER_CODE1);

    msIR_WriteByte(IR_CODEBYTE, 0x9F);      //ir cc code byte enable=1(2 customer codes), ir_code bits = 0x1F(32 bits)
    msIR_WriteByte(IR_GLHRM_NUM_L, 0x04);   // GLHRM number[7:0]

#if(IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
    msIR_WriteByte(IR_FIFO_CTRL, 0x0F);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x38);   // {IR_DECOMODE[1:0], GLHRM_EN,GLHRM_NUM[10:8]}
#elif(IR_MODE_SEL == IR_TYPE_RAWDATA_MODE)
    msIR_WriteByte(IR_FIFO_CTRL, 0x0F);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x28);   // {IR_DECOMODE[1:0], GLHRM_EN,GLHRM_NUM[10:8]}
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
    msIR_WriteByte(IR_FIFO_CTRL, 0x17);  // Only PSHOT edge detect for counter
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x1F);
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
    msIR_WriteByte(IR_CTRL, 0x00);// NEC clear
    msIR_WriteByte(IR_CHECK, 0x00);    // disable timerout
    msIR_WriteByte(IR_FIFO_CTRL, 0x30);// pos_neg 0x20);     // Only NSHOT edge detect for counter
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x18);
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)
    msIR_WriteByte(IR_FIFO_CTRL, 0x2F);     // Only NSHOT edge detect for counter
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x18);
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
    msIR_WriteByte(IR_FIFO_CTRL, 0x2F);     // Only NSHOT edge detect for counter
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x18);
    u8Cus21SHTableSize = sizeof(IR_CUS21SH_RAWDATA_TABLE)/sizeof(U8);
    #if 0 //Enable when Standby Mode SHA IR moving to Sramvar.h
    gStandbyInto=FALSE;
    g_bIrDetect = FALSE;
    g_bIsIrModeSwitchedToSWmode=TRUE;
    g_wIrPulseCounter = 0;
    BufIdx=0;
    BuffeRX=0;
    BufferCurrent=0;
    BufLenCurrent=0;
    BufferPrev=0;
    LastKeyData=0xFF;
    IsRepeatData=0;
    keyDatArrayWTIdx=0 ;
    keyDatArrayRDIdx=0 ;
    CodeReceived=FALSE;
    ExpetedTCome=FALSE;
    SystemBitOK=FALSE;
    DetectBitOK=FALSE;
    FirstRXFlag=FALSE;
    SecondRXFlag=FALSE;
    DataMatched=FALSE;
    RxInProcess=FALSE;
    ReceivingMode=FALSE;
    SetToStandbyMode=FALSE;
    #endif
#elif (IR_MODE_SEL == IR_TYPE_HWDECODE_RC)
//normal configuration
//config RC mode
{
    U8 u8ModeSel=HAL_IR_RC_RC5;

    if(HAL_IR_RC_RC5 == u8ModeSel)//RC5
    {
        HAL_IR_CfgControl(HAL_IR_RC_CTRL_0,0x00,0xFF);
        HAL_IR_CfgControl(HAL_IR_RC_CTRL_1,0x01,0xFF);
    }
    if(HAL_IR_RC_RC5X == u8ModeSel)//RC5X
    {
        HAL_IR_CfgControl(HAL_IR_RC_CTRL_0,0x00,0xFF);
        HAL_IR_CfgControl(HAL_IR_RC_CTRL_1,0x05,0xFF);
    }
    if(HAL_IR_RC_RC6 == u8ModeSel)//RC6
    {
        HAL_IR_CfgControl(HAL_IR_RC_CTRL_0,0x20,0xE0);//auto config
        HAL_IR_CfgControl(HAL_IR_RC_CTRL_1,0x03,0xFF);
    }
    //configure RC timing
    HAL_IR_RC_CfgClkDiv(12);
    HAL_IR_RC_CfgLgpsThr();
    HAL_IR_RC_CfgIntgThr();
    HAL_IR_RC_CfgWdogCount();
    HAL_IR_RC_CfgLgpsMar();
    HAL_IR_RC_CfgLdpsThr();
    HAL_IR_RC_CfgEcoFunc(ENABLE);
    //HAL_IR_RC_CfgInputInvert(ENABLE);
    //HAL_IR_CfgIntrMask(ENABLE);//enable mask
    //HAL_IR_CfgHwDecode(DISABLE);//disable Full/Raw decode
}
#endif

    MsOS_AttachInterrupt(E_INT_FIQ_IR, (InterruptCb)MDrv_IR_SW_Isr);
    MsOS_EnableInterrupt(E_INT_FIQ_IR);

    #if(IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
    #if IR_NEW_METHOD
    if(u32Mutex_IR<=0)
    {
        msIR_InitLock();
    }
    #endif
    #endif

}

#if (IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
//*************************************************************************
//Function name:    msIR_ReadByte
//Passing parameter: U16 u16RegIndex:   register address
//Return parameter: U8 u8Value: value
//Description: read register value
//*************************************************************************
void putcharvalue(U8 u8value)
{
    if ((u8value>>4) <= 9)
        putchar((u8value>>4)+'0');
    else
        putchar((u8value>>4)-0x0A+'A');

    if ((u8value&0x0F) <= 9)
        putchar((u8value&0x0F)+'0');
    else
        putchar((u8value&0x0F)-0x0A+'A');
}
//*************************************************************************
//Function name:    msIR_ReadByte
//Passing parameter: U16 u16RegIndex:   register address
//Return parameter: U8 u8Value: value
//Description: read register value
//*************************************************************************
void ResetKeyoffTimer(void)
{
    KeyOffTimeOutCount=gSystemTimeCount;
}
#endif

/******************************************************************************/
/// IR get key value and repeat flag
/// @param pkey \b IN return the key value
/// @param pu8flag \b IN return the repeat flag(1:Repeat)
/******************************************************************************/
#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
#if IR_NEW_METHOD
void msIR_DelayTime(U32 u32Delay)
{
    // volatile is necessary to avoid optimization
    U32 volatile u32Dummy = 0;

    while (u32Delay-- > 0)
    {
        u32Dummy++;
    }
}

BOOLEAN msIR_GetIRKeyCodeISR(U8 *pkey, U8 *pu8flag)
{
    U8 j;

    if(FALSE == g_bIsIrModeSwitchedToSWmode)
    {
        *pkey = 0xff;
        *pu8flag = 0;
        //if (MsOS_Timer_DiffTimeFromNow(gIRTimeCount) >= IR_NEC_INTERVAL)
        if(1)//we needn't repeat key on the MBoot
        {
            *pkey = msIR_ReadByte(IR_KEY); //msIR_GetIrKeyData();
            MDrv_WriteByte(IR_FIFO_READ_PULSE, MDrv_ReadByte(IR_FIFO_READ_PULSE)| 0x01);
            msIR_DelayTime(10);
            *pu8flag = 0;
            u8RepeatCount = 0;
            u8PrevIrKey = *pkey;
            u8IRTimerBlockstatus = 0;
            gIRTimeCount = MsOS_GetSystemTime();
            return MSRET_OK;
        }
        else
        {
            if(u8IRTimerBlockstatus==0)
            {
                u8IRTimerBlockstatus = 0xff;
                gIRTimeCount = MsOS_GetSystemTime();
                return MSRET_OTHER;
            }
            u8IRTimerBlockstatus = 0xff;
            for(j=0; j<IR_FILTER_REPEAT_NUM; j++)
            {
                    *pkey = msIR_ReadByte(IR_KEY);
                    MDrv_WriteByte(IR_FIFO_READ_PULSE, MDrv_ReadByte(IR_FIFO_READ_PULSE)| 0x01);
                    msIR_DelayTime(10);
                    *pu8flag = msIR_ReadByte(IR_RPT_FIFOEMPTY) & 0x1;
                    //printf("# flag=%d,(PrevKey=%x, pkey=%x)\n",*pu8flag,u8PrevIrKey,*pkey);
                    if ( (*pu8flag == 1) && (u8PrevIrKey == *pkey))
                    {
                        u8RepeatCount++;
                        gIRTimeCount = MsOS_GetSystemTime();
                        if (u8RepeatCount >= IR_FILTER_REPEAT_NUM)
                        {
                            //printf("# u8RepeatCount=%d\n",u8RepeatCount);
                            u8PrevIrKey = *pkey;
                            u8RepeatCount = 0;
                            return MSRET_OK;
                        }
                    }
            }
        }
        return MSRET_ERROR;
    }
    return MSRET_ERROR;
}
#endif
#endif

BOOLEAN msIR_GetIRKeyCode(U8 *pkey, U8 *pu8flag)
{
#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
    if(FALSE == g_bIsIrModeSwitchedToSWmode)
    {
      #if IR_NEW_METHOD
        BOOLEAN u8IRRes=MSRET_ERROR;

        msIR_Lock();
        *pkey = g_u8IRKey;
        *pu8flag = g_u8IRRpt;
        u8IRRes = g_u8IRRes;
        g_u8IRKey = 0xFF;
        g_u8IRRpt = 0;
        g_u8IRRes = MSRET_ERROR;
        msIR_UnLock();
        return u8IRRes;
      #else
        U8 j;

        *pkey = 0xff;
        *pu8flag = 0;
        if (MsOS_Timer_DiffTimeFromNow(gIRTimeCount) >= IR_NEC_INTERVAL)
        {
            u8IRTimerBlockstatus = 0;
            gIRTimeCount = MsOS_GetSystemTime();
        }
        else
        {
            u8IRTimerBlockstatus = 0xff;
            return MSRET_ERROR;
        }

        for(j=0; j<IR_FILTER_REPEAT_NUM; j++)
        {
            if((msIR_ReadByte(IR_RPT_FIFOEMPTY) & 0x2))
            {
                return MSRET_ERROR;
            }
            else
            {
                *pkey = msIR_ReadByte(IR_KEY); //msIR_GetIrKeyData();

                MDrv_WriteByte(IR_FIFO_READ_PULSE, MDrv_ReadByte(IR_FIFO_READ_PULSE)| 0x01);

                MsOS_DelayTask(1);

                *pu8flag = msIR_ReadByte(IR_RPT_FIFOEMPTY) & 0x1;

                if ( ( MsOS_Timer_DiffTimeFromNow( gIRTimeOutCount ) >= IR_NEC_TIMEOUT ) && ( gIRTimeOutCount != 0xffffffff ) )
                {
                    gIRTimeOutCount = 0xffffffff;
                    msIR_Clear_FIFO();
                    if( *pu8flag == 1 && (u8PrevIrKey == *pkey))
                    {
//                        printf("\n MSRET_ERROR\n");
                        return MSRET_ERROR;
                    }
                }

                if ( (*pu8flag == 0) ||(u8PrevIrKey != *pkey))
                {
                    u8RepeatCount = 0;
                    u8PrevIrKey = *pkey;
                    //printf("\n IrKey=%x,%x\n",u8PrevIrKey,*pu8flag);

                    return MSRET_OK;
                }
                else
                {
                    u8RepeatCount++;
                    if (u8RepeatCount >= IR_FILTER_REPEAT_NUM)
                    {
                        //printf("\n REPET=%x,%x",u8PrevIrKey,*pu8flag);
                        u8PrevIrKey = *pkey;
                        return MSRET_OK;
                    }
                }
            }
        }
      #endif
    }
    else    /* SW IR */ //
    {
        if(g_bIrDetect)
        {
            g_bIrDetect = FALSE;
    //       g_bIrHold = TRUE;

            IRPRINT(printf("RP:%bx\n", g_bIrRepeat));
            IRPRINT(printf("C0:%bx\n", g_ucIrCode[0]));
            IRPRINT(printf("C1:%bx\n", g_ucIrCode[1]));
            IRPRINT(printf("C2:%bx\n", g_ucIrCode[2]));
            IRPRINT(printf("C3:%bx\n", g_ucIrCode[3]));

            if(g_bIrRepeat)
            {
                if(g_ucIrRepeatSkipCnt > 0)
                {
                    g_ucIrRepeatSkipCnt--;
                g_bIrRepeat = FALSE;
                g_bIrStartReceived = FALSE;
                g_ucIrRepeatTimer = IR_SW_REPEAT_TIMEOUT;

                    IRPRINT(printf("g_ucIrRepeatSkipCnt:%bu\n", g_ucIrRepeatSkipCnt));

                    return MSRET_ERROR;
                }
                else
                {
                    *pkey = IR_CODE;
                    *pu8flag = g_bIrRepeat;
                    //printf("\n1 Tmp Pulse(%u) ", g_wIrPulseCounter_tmp);
    //                g_ucIrRepeatSkipCnt = IR_REPEAT_SKIP_COUNT;//Skip Repeat Periodically enable this.
                }
            }
            else
            {
                    *pkey = IR_CODE;
                    *pu8flag = g_bIrRepeat;
                    g_ucIrRepeatSkipCnt = IR_REPEAT_SKIP_COUNT;
                    //printf("\n2 Tmp Pulse(%u) ", g_wIrPulseCounter_tmp);
            }

            g_bIrRepeat = FALSE;
            g_bIrStartReceived = FALSE;
            g_ucIrRepeatTimer = IR_SW_REPEAT_TIMEOUT;

            //g_bIrHold = FALSE;

            return MSRET_OK;
        }
    }

    return MSRET_ERROR;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
    U8 u8System;
    U8 u8Data;

    if(g_u8IrRc5Flag & IR_RC5_DETECT_END)
    {
        g_u8IrRc5Flag |= IR_RC5_DECODING;
        g_u8IrRc5Flag &= (~IR_RC5_DETECT_END);

        if ((g_u16IrRc5Data & 0xF000) == 0x3000)
        {
            u8Data = (U8)(g_u16IrRc5Data & 0x003F);
            u8System = (U8)((g_u16IrRc5Data >> 6) & 0x001F);
            if (u8System == IR_HEADER_CODE0)
            {
                *pkey = u8Data;
                if ((g_u8IrRc5Flag & IR_RC5_TOGGLE_BIT) == (U8)((g_u16IrRc5Data >> 4) & BIT7))
                    *pu8flag = 1;
                else
                {
                    if (g_u16IrRc5Data & BIT11)
                        g_u8IrRc5Flag |= IR_RC5_TOGGLE_BIT;
                    else
                        g_u8IrRc5Flag &= (~IR_RC5_TOGGLE_BIT);
                    *pu8flag = 0;
                }
                //printf("\r\n key=0x%x", (U16)(*pkey));
                //printf("\r\n rpt=%d", (U16)(*pu8flag));
                g_u8IrRc5Flag &= IR_RC5_TOGGLE_BIT;
                if (*pu8flag == 0)
                {
                    g_u8IrRc5RepeatCount = 0;
                    return MSRET_OK;
                }
                else
                {
                    g_u8IrRc5RepeatCount++;
                    if (g_u8IrRc5RepeatCount >= 4)//IR_FILTER_REPEAT_NUM)
                        return MSRET_OK;
                }
            }
        }
        g_u8IrRc5Flag &= (~IR_RC5_DECODING);
    }
    return MSRET_ERROR;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
    U8 u8Temp;
    if(g_u8IrKonFlag & IR_KON_DETECT_END)
    {
        if (((g_u16IrKonDecode >> 8) & 0xFF) != IR_HEADER_CODE0)
        {
            g_u8IrKonFlag &= (~IR_KON_DETECT_END);
            return MSRET_ERROR;
        }

        u8Temp = (U8)(g_u16IrKonDecode & 0x00FF);
        *pkey = u8Temp;

        if ( (g_u8IrKonFlag & IR_KON_REPEATE_TIMEOUT) || (g_u8IrKonPreKey != u8Temp))
        {
            *pu8flag = 0;
            g_u8IrKonPreKey = u8Temp;
        }
        else
        {
            *pu8flag = 1;
        }
        //printf("\n0x%x(%d)\n", (U16)(*pkey), (U16)(*pu8flag));
        g_u8IrKonFlag &= (~IR_KON_DETECT_END);

        if (*pu8flag == 0)
        {
            g_u8IrKonRepeatCount = 0;
            return MSRET_OK;
        }
        else
        {
            g_u8IrKonRepeatCount++;
            if (g_u8IrKonRepeatCount >= 10)//IR_FILTER_REPEAT_NUM)
                return MSRET_OK;
        }
    }
    return MSRET_ERROR;
#elif (IR_MODE_SEL == IR_TYPE_RAWDATA_MODE)

    if(!(msIR_ReadByte(IR_RPT_FIFOEMPTY) & BIT1)) // check FIFO not empty
    {
        u8IRRawModeBuf[u8IRRawModeCount] = msIR_ReadByte(IR_KEY);

        MDrv_WriteByte(IR_FIFO_READ_PULSE, MDrv_ReadByte(IR_FIFO_READ_PULSE)| 0x01);

        IR_DEBUG(printf("IR D%bu = 0x%02bx\n", u8IRRawModeCount, u8IRRawModeBuf[u8IRRawModeCount]));
        u8IRRawModeCount++;

        if ( u8IRRawModeCount == IR_RAW_DATA_NUM )
        {
            u8IRRawModeCount = 0;
            u8IRRawModeDone = 1;
        }
    }

    if ( u8IRRawModeDone )
    {
        u8IRRawModeDone = 0;
        if(u8IRRawModeBuf[0] == IR_HEADER_CODE0)
        {
            if(u8IRRawModeBuf[1] == IR_HEADER_CODE1)
            {
                if(u8IRRawModeBuf[2] == ~u8IRRawModeBuf[3])
                {
                    *pkey = u8IRRawModeBuf[2];
                    *pu8flag = 0;
                    return MSRET_OK;
                }
            }
        }
    }
    return MSRET_ERROR;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)

    #if 1

    if(g_bIrDetect)
    {
        //g_bIrDetect = FALSE;
//       g_bIrHold = TRUE;

        IRPRINT(printf("RP:%bx\n", g_bIrRepeat));
        IRPRINT(printf("C0:%bx\n", g_ucIrCode[0]));
        IRPRINT(printf("C1:%bx\n", g_ucIrCode[1]));
        IRPRINT(printf("C2:%bx\n", g_ucIrCode[2]));
        IRPRINT(printf("C3:%bx\n", g_ucIrCode[3]));

        if(g_bIrRepeat)
        {
            if(g_ucIrRepeatSkipCnt > 0)
            {
                g_ucIrRepeatSkipCnt--;

            g_bIrRepeat = FALSE;
            g_bIrStartReceived = FALSE;
            g_ucIrRepeatTimer = IR_SW_REPEAT_TIMEOUT;
                IRPRINT(printf("g_ucIrRepeatSkipCnt:%bu\n", g_ucIrRepeatSkipCnt));
                return MSRET_ERROR;
            }
            else
            {
                printf("RP!\n");
                *pkey = IR_CODE;
                *pu8flag = g_bIrRepeat;
                //g_ucIrRepeatSkipCnt = IR_REPEAT_SKIP_COUNT;
            }
        }
    else
    {
            *pkey = IR_CODE;
            *pu8flag = g_bIrRepeat;
            g_ucIrRepeatSkipCnt = IR_REPEAT_SKIP_COUNT;
        }

        g_bIrRepeat = FALSE;
        g_bIrStartReceived = FALSE;
        g_ucIrRepeatTimer = IR_SW_REPEAT_TIMEOUT;

        //g_bIrHold = FALSE;
    g_bIrDetect = FALSE;
        return MSRET_OK;
    }


    #else
    if (gIRCount >  0x00)
    {
        if(LOWBYTE(gIRKey) == IR_HEADER_CODE0)
        {
            if(HIGHBYTE(gIRKey) == IR_HEADER_CODE1)
            {
                if(LOWBYTE(gIRKey >> 16) == ~(HIGHBYTE(gIRKey >> 16)))
                {
                    *pkey = LOWBYTE(gIRKey >> 16);
                    *pu8flag = 0;
                    gIRCount = 0;
                    gIRKey = 0;
                    return MSRET_OK;
                }
            }
        }
    }
    #endif
    return MSRET_ERROR;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
    if(MDrv_CheckSWIRKey())
    {
        *pkey=u8Key;
        *pu8flag=u8Flag;
        return MSRET_OK;
    }
 return MSRET_ERROR;
#elif (IR_MODE_SEL == IR_TYPE_HWDECODE_RC)
{
    HAL_IR_RC_KeyData IRRCKeyData;

    *pkey = 0xFF;
    *pu8flag = 0;

    if(HAL_IR_RC_IsFIFOEmpty()==TRUE)
        return MSRET_ERROR;
    HAL_IR_RC_GetKeyData(&IRRCKeyData);
    HAL_IR_RC_ClearFIFO();
    if(IRRCKeyData.u8Valid)
    {
        *pkey = IRRCKeyData.u8Command;
        *pu8flag = IRRCKeyData.u8Repeat;
        printf("[HW_RC]: pkey=0x%X, pu8flag=%X\n",*pkey,*pu8flag);
        return MSRET_OK;
    }
    else
    {
        return MSRET_ERROR;
    }
}
#else
    return MSRET_ERROR;
#endif
}

//#if (IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)
U8 u8ir_pressed;
static void MDrv_IR_SW_Isr(MHAL_SavedRegisters *pHalReg, U32 u32Data)
{
    UNUSED(pHalReg);
    UNUSED(u32Data);

    IRCHAR('@');
    u8ir_pressed = 1;

    #if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
      #if IR_NEW_METHOD
        U8 u8IRKey=0xFF;
        U8 u8IRRpt=0;
        BOOLEAN u8IRRes=MSRET_ERROR;

        u8IRRes = msIR_GetIRKeyCodeISR(&u8IRKey,&u8IRRpt);
        msIR_Clear_FIFO();
        msIR_Lock();
        if(u8IRRes<=MSRET_OK)
        {
            g_u8IRKey = (u8IRRes)? u8IRKey : 0xFF;
            g_u8IRRpt = (u8IRRes)? u8IRRpt : 0;
            g_u8IRRes = u8IRRes;
        }
        msIR_UnLock();
      #else
        gIRTimeOutCount = gTimerCount0;
      #endif
    #endif
#if 1

#if (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
    // get a ir counter value
    g_u16IrKonCounter = (U16)MDrv_ReadByte(IR_SHOT_CNT_1);
    g_u16IrKonCounter <<= 8;
    g_u16IrKonCounter |= (U16)MDrv_ReadByte(IR_SHOT_CNT_0);

    g_u8IrKonFlag |= IR_KON_COUNTER_ERROR;
    // IR_KONKA_DETECT_START means detected header code(here g_u8IrKonkaBits==1), and ready to detect system/data code
    if (MDrv_ReadByte(IR_SHOT_CNT_2) & 0x07)
    {

    }
    else if (g_u16IrKonCounter > IR_KON_PWS3_HEADER_CNT_LB && g_u16IrKonCounter < IR_KON_PWS3_HEADER_CNT_UB)
    {
        g_u8IrKonFlag  |= IR_KON_DETECT_START;
        g_u16IrKonData = 0;
        g_u8IrKonBits = 1;
        goto SW_ISR_LAST;
    }
    else if (g_u8IrKonFlag & IR_KON_DETECT_START )
    {
        if (g_u16IrKonCounter > IR_KON_PWS3_LOGIC0_CNT_LB && g_u16IrKonCounter < IR_KON_PWS3_STOP_CNT_UB)
            g_u8IrKonFlag &= ~IR_KON_COUNTER_ERROR;
    }

    if (g_u8IrKonFlag & IR_KON_COUNTER_ERROR)
    {
        g_u8IrKonFlag &= ~IR_KON_DETECT_START;
        g_u16IrKonData = 0;
        g_u8IrKonBits = 0;
        goto SW_ISR_LAST;
    }

    if (g_u8IrKonBits > 0)
    {
        if (g_u16IrKonCounter > IR_KON_PWS3_LOGIC1_CNT_LB && g_u16IrKonCounter < IR_KON_PWS3_LOGIC1_CNT_UB)
        {
            g_u16IrKonData <<= 1;
            g_u16IrKonData |= 1;
            g_u8IrKonBits++;
        }
        else if (g_u16IrKonCounter > IR_KON_PWS3_LOGIC0_CNT_LB && g_u16IrKonCounter <  IR_KON_PWS3_LOGIC0_CNT_UB)
        {
            g_u16IrKonData <<= 1;
            g_u8IrKonBits++;
        }
        else if (g_u16IrKonCounter > IR_KON_PWS3_STOP_CNT_LB && g_u16IrKonCounter <  IR_KON_PWS3_STOP_CNT_UB)
        {
            g_u8IrKonBits++;
            if(g_u8IrKonBits >= IR_KON_DATA_BITS)
            {
                if(!(g_u8IrKonFlag & IR_KON_DETECT_END))
                {
                    g_u8IrKonFlag |= IR_KON_DETECT_END;
                    g_u16IrKonDecode = g_u16IrKonData;
                }
                g_u8IrKonBits = 0;
                if (g_u8IrKonRepeatTimeout == 0)
                    g_u8IrKonFlag |= IR_KON_REPEATE_TIMEOUT;
                else
                    g_u8IrKonFlag &= (~IR_KON_REPEATE_TIMEOUT);
                g_u8IrKonRepeatTimeout = IR_KON_PWS3_REPEATE_TIMEOUT;
            }
            else
            {
                 g_u8IrKonFlag &= ~IR_KON_DETECT_START;
                g_u16IrKonData = 0;
                g_u8IrKonBits = 0;
            }
        }
    }
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
    // if ir is decoding or int detect done, return
    if (g_u8IrRc5Flag & (IR_RC5_DECODING | IR_RC5_DETECT_END))
        goto SW_ISR_LAST;

    // get a ir counter value
    g_u16IrRc5Counter = MDrv_ReadByte(IR_SHOT_CNT_1);
    g_u16IrRc5Counter <<= 8;
    g_u16IrRc5Counter |= MDrv_ReadByte(IR_SHOT_CNT_0);
    // if ir counter so big, then reset and return
    if ((MDrv_ReadByte(IR_SHOT_CNT_2) & 0x07) || (g_u16IrRc5Counter > ONE_BIT_UB || g_u16IrRc5Counter < HALF_BIT_LB))
    {
        g_u8IrRc5Flag &= IR_RC5_TOGGLE_BIT;     // clear all bits except IR_RC5_TOGGLE_BIT
        g_u8IrRc5Flag |= (IR_RC5_DETECT_START | IR_RC5_LAST_BIT);
        g_u16IrRc5Data = 0;
        g_u8IrRc5Bits = 0;
        goto SW_ISR_LAST;
    }

    // if ir is not start to detect, start it
    if ((g_u8IrRc5Flag & IR_RC5_DETECT_START) == 0)
    {
        if (MDrv_ReadByte(IR_SHOT_CNT_2) & BIT4) // nshot
        {
            g_u8IrRc5Flag |= (IR_RC5_DETECT_START | IR_RC5_LAST_BIT);
            g_u16IrRc5Data = 0;
            g_u8IrRc5Bits = 0;
        }
        goto SW_ISR_LAST;
    }

    // detect
    if (g_u16IrRc5Counter >= HALF_BIT_LB && g_u16IrRc5Counter <= HALF_BIT_UB)
    {
        g_u8IrRc5Bits++;
        if (g_u8IrRc5Flag & IR_RC5_LAST_BIT)
        {
            g_u8IrRc5Flag &= (~IR_RC5_LAST_BIT);    // clear IR_RC5_LAST_BIT
            g_u16IrRc5Data <<= 1;
            if (MDrv_ReadByte(IR_SHOT_CNT_2) & BIT4) // nshot
                g_u16IrRc5Data |= 1;
        }
        else
        {
            g_u8IrRc5Flag |= IR_RC5_LAST_BIT;
        }
    }
    else if (g_u16IrRc5Counter >= ONE_BIT_LB && g_u16IrRc5Counter <= ONE_BIT_UB)
    {
        if (g_u8IrRc5Flag & IR_RC5_LAST_BIT)
        {
            g_u16IrRc5Data <<= 1;
            if (MDrv_ReadByte(IR_SHOT_CNT_2) & BIT4) // nshot
                g_u16IrRc5Data |= 1;
            g_u8IrRc5Bits += 2;
        }
        else
        {
            // error!
            g_u8IrRc5Flag &= IR_RC5_TOGGLE_BIT;     // clear all bits except IR_RC5_TOGGLE_BIT
            g_u16IrRc5Data = 0;
            g_u8IrRc5Bits = 0;
            goto SW_ISR_LAST;
        }
    }

    if(g_u8IrRc5Bits > IR_RC5_DATA_BITS)
    {
        g_u8IrRc5Flag &= (~IR_RC5_DETECT_START);
        g_u8IrRc5Flag |= IR_RC5_DETECT_END;
    }
    else if (g_u8IrRc5Bits == IR_RC5_DATA_BITS)
    {
        if (MDrv_ReadByte(IR_SHOT_CNT_2) & BIT4) // nshot
        {
            g_u16IrRc5Data <<= 1;
            g_u8IrRc5Flag &= (~IR_RC5_DETECT_START);
            g_u8IrRc5Flag |= IR_RC5_DETECT_END;
        }
    }
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
    g_wIrPulseCounter = 0;
    g_wIrPulseCounter |=  ((MDrv_ReadByte(IR_SHOT_CNT_1)) << 8);
    g_wIrPulseCounter |=  (MDrv_ReadByte(IR_SHOT_CNT_0));
    if(g_wIrPulseCounter<420L)
    {
        IRCHAR('N');
        //putchar('N');
        if(ExpetedTCome)
        ExpetedTCome=FALSE;

        if(RxInProcess)
        {
            if(BufIdx>0)
            {
                  if(BufIdx==15)
                  {
                      IRCHAR('M');
                      keyDatArray[keyDatArrayWTIdx]=BuffeRX;
                      keyDatArrayWTIdx++;
                      keyDatArrayWTIdx%=10;
                  }
                  else
                  {
                     if(BufLenCurrent>=11)
                     {
                         KeyOffTimeOutCount=gSystemTimeCount;
                     }
                     else
                     {
                         SetToStandbyMode=TRUE;
                     }
                  }
                  IRCHAR('K');
                  IRCHARVALUE((BuffeRX>>8));
                  IRCHARVALUE(BuffeRX&0xFF);
                  IRCHAR('K');
                  IRCHARVALUE(keyDatArrayWTIdx);
                  IRCHAR('K');
                  BufIdx=0;
                  BuffeRX=0;
                  CodeReceived=TRUE;
                  RxInProcess=FALSE;
            }
        }
    }
    else if(g_wIrPulseCounter >=420L && g_wIrPulseCounter < 1580L)
    {
          IRCHAR('0');
          //putchar('0');
          if(ExpetedTCome)
          {
              ExpetedTCome=FALSE;
          }
          else
          {
            BufIdx++;
            #if 0
            if(gStandbyInto==FALSE)
            #endif
            {
                RxInProcess=TRUE;
                ReceivingMode=TRUE;
                RxTimeOutCount = gSystemTimeCount;
                KeyOffTimeOutCount=gSystemTimeCount;
            }
        }
    }
    else if(g_wIrPulseCounter >=1580L && g_wIrPulseCounter < 2048L)
    {
          IRCHAR('1');
        // putchar('1');
        if(ExpetedTCome)
          {
              ExpetedTCome=FALSE;
          }
          else
          {
            BuffeRX|=(1<<BufIdx);
            BufIdx++;
            #if 0
            if(gStandbyInto==FALSE)
            #endif
            {
                ReceivingMode=TRUE;
                RxInProcess=TRUE;
                RxTimeOutCount = gSystemTimeCount;
                KeyOffTimeOutCount=gSystemTimeCount;
            }

        }
    }
    else if(g_wIrPulseCounter >=2048L && g_wIrPulseCounter < 100000L)
    {
         IRCHAR('T');

    //  putchar('T');

        if(ExpetedTCome)
        {
            ExpetedTCome=FALSE;
        }

        if((RxInProcess)/*||(gStandbyInto==TRUE)*/)//When Standby mode , permitting to process anyway
        {
            if(BufIdx>0)
            {
                  if(BufIdx==15)
                  {
                      IRCHAR('M');
                      keyDatArray[keyDatArrayWTIdx]=BuffeRX;
                      keyDatArrayWTIdx++;
                      keyDatArrayWTIdx%=10;
                    RxInProcess=TRUE;
                    ReceivingMode=TRUE;
                    RxTimeOutCount = gSystemTimeCount;
                    KeyOffTimeOutCount=gSystemTimeCount;
                  }
                  else
                  {
                     if(BufLenCurrent>=11)
                     {
                         KeyOffTimeOutCount=gSystemTimeCount;
                     }
                     else
                     {
                         SetToStandbyMode=TRUE;
                     }
                  }
                  IRCHAR('K');
                  IRCHARVALUE((BuffeRX>>8));
                  IRCHARVALUE(BuffeRX&0xFF);
                  IRCHAR('K');
                  IRCHARVALUE(keyDatArrayWTIdx);
                  IRCHAR('K');
                  /*
                  if(gStandbyInto==TRUE)
                  {
                  temp=BuffeRX>>8;


                if ((temp>>4) <= 9)
                    putchar((temp>>4)+'0');
                else
                    putchar((temp>>4)-0x0A+'A');

                if ((temp&0x0F) <= 9)
                    putchar((temp&0x0F)+'0');
                else
                    putchar((temp&0x0F)-0x0A+'A');

                temp=BuffeRX&0xFF;

                if ((temp>>4) <= 9)
                    putchar((temp>>4)+'0');
                else
                    putchar((temp>>4)-0x0A+'A');

                if ((temp&0x0F) <= 9)
                    putchar((temp&0x0F)+'0');
                else
                    putchar((temp&0x0F)-0x0A+'A');
                }
                */
               }
                  BufIdx=0;
                  BuffeRX=0;
                  CodeReceived=TRUE;
                  RxInProcess=FALSE;
            }
        }

    else
    {
        IRCHAR('K');
    }

#elif (IR_MODE_SEL == IR_TYPE_HWDECODE_RC)

#else
    //if(TRUE == g_bIrHold)
    if(FALSE == g_bIsIrModeSwitchedToSWmode)
    {
        goto SW_ISR_LAST;
    }

    //g_wIrPulseCounter = (U32)((((U32)msIR_ReadByte(IR_SHOT_CNT_2) << 16)&0x70000L)
    //                                        + (((U32)msIR_ReadByte(IR_SHOT_CNT_1) << 8)&0xFF00L)
    //                                        + ((U32)msIR_ReadByte(IR_SHOT_CNT_0)&0xFF));
    //g_wIrPulseCounter = (U32)((((U32)msIR_ReadByte(IR_SHOT_CNT_1) << 8)&0xFF00)
    //                                    + ((U32)msIR_ReadByte(IR_SHOT_CNT_0)&0xFF));
    g_wIrPulseCounter = 0;
    //g_wIrPulseCounter |= ( U32 ) (( MDrv_ReadByte(IR_SHOT_CNT_2) & 0x07 ) << 16);
    g_wIrPulseCounter |=  ((MDrv_ReadByte(IR_SHOT_CNT_1)) << 8);
    g_wIrPulseCounter |=  (MDrv_ReadByte(IR_SHOT_CNT_0));

    if(g_bIrStartReceived == FALSE)
    {
        if(g_ucIrPulseCntIndex == 0 && g_ucIrByteIndex == 0)
        {
            if(g_ucIrRepeatTimer > 0)
            {
                if(g_wIrPulseCounter > 1800L && g_wIrPulseCounter < 2600L)//Repeat Negative Period 2.25ms After Leader signal.
                {
                    IRCHAR('R');
                    g_bIrDetect = TRUE;
                    g_bIrRepeat = TRUE;
                    g_ucIrPulseCntIndex = 0;
                    g_ucIrRepeatTimer = IR_SW_REPEAT_TIMEOUT;
                    g_bIrStartReceived = FALSE;
                    goto SW_ISR_LAST;
                }
            }

            //if(g_wIrPulseCounter < HEADER_UPPER_BOND && g_wIrPulseCounter > HEADER_LOWER_BOND)
            if(g_wIrPulseCounter > 4000L && g_wIrPulseCounter < 5000L)//Leader code - Low 4500us(4.5ms)
            {
                IRCHAR('L');
                g_bIrStartReceived = TRUE;
                g_ucIrRepeatTimer = IR_SW_REPEAT_TIMEOUT;
                g_ucIrPulseCntIndex = 0;
                g_ucIrByteIndex = 0;
                g_ucIrCode[g_ucIrByteIndex] = 0;
                goto SW_ISR_LAST;
            }
            else
            {
                IRCHAR('3');
                g_ucIrByteIndex = 0;
                g_ucIrPulseCntIndex = 0;
                g_bIrStartReceived = FALSE;

                g_bIrDetect = FALSE;
                g_bIrRepeat = FALSE;
                goto SW_ISR_LAST;
            }
        }
    }
    else
    {
        //Decode Bit
        g_ucIrCode[g_ucIrByteIndex] >>= 1;

        //if((g_wIrPulseCounter > 400) && (g_wIrPulseCounter < 1400))//Negative period 560us(5.6ms)
        if(g_wIrPulseCounter < 1400)//Negative period 560us(5.6ms)
        {
            g_ucIrCode[g_ucIrByteIndex] &= ~(BIT7);//Set 0
        }
        //else if((g_wIrPulseCounter > 1399) && (g_wIrPulseCounter < 2750))//Negative period 2250us(2.25ms)
        else if(g_wIrPulseCounter < 2750)//Negative period 2250us(2.25ms)
        {
            g_ucIrCode[g_ucIrByteIndex] |= BIT7;//Set 1
        }
        else
        {
            IRCHAR('\n');IRCHAR('E');IRCHAR('R');IRCHAR('\n');//Pulse Count Error!.
        }

        g_ucIrPulseCntIndex ++;

        if(g_ucIrPulseCntIndex >= IR_SW_COUNT_BIT_NUM)
        {
            IRCHAR('4');
            g_ucIrPulseCntIndex = 0;

            if(g_ucIrByteIndex < IR_MAX_IR_DATA_NUM)
            {
                g_ucIrByteIndex ++;
                g_ucIrCode[g_ucIrByteIndex] = 0;
            }
        }
    }
    #endif
    #else

    gIRCount ++;

    if(MDrv_ReadByte(IR_SHOT_CNT_1) & 0x08)
        gIRKey = gIRKey >> 1 | 0x80000000;
    else
        gIRKey = gIRKey >> 1;

    #endif

SW_ISR_LAST:
    //enable interrupt again
    MsOS_EnableInterrupt(E_INT_FIQ_IR);

}

//#endif

#if (IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)
BOOLEAN MDrv_Power_CheckPowerOnSWIRKey(void)
{
    if(g_bIrDetect)
    {
        if(IR_CODE == IRKEY_POWER)
            return MSRET_OK;

        #if 0
        if(g_ucIrCode[0] == IR_HEADER_CODE0)
        {
            if(g_ucIrCode[1] == IR_HEADER_CODE1)
            {
                if(g_ucIrCode[2] == IRKEY_POWER) {
                    //gIRCount = 0;
                    g_ucIrCode[2]  = 0;
                    return MSRET_OK;
                }
            }
        }
        #endif
        g_bIrDetect = FALSE;
    }

    return MSRET_ERROR;
}
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
BOOLEAN MDrv_Power_CheckPowerOnSWIRKey(void)
{
    U8 u8Key;
    U8 u8Flag;

    //if (MDrv_IR_GetKeyCode(&u8Key, &u8Flag))
    if(msIR_GetIRKeyCode(&u8Key, &u8Flag))
    {
        if (u8Key == IRKEY_POWER)
            return TRUE;
        else if (g_u8IrKonPreKey == IRKEY_POWER)
            return TRUE;
    }
    return FALSE;
}
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
BOOLEAN MDrv_Power_CheckPowerOnSWIRKey(void)
{
    U8 u8Key;
    U8 u8Flag;

    //if (MDrv_IR_GetKeyCode(&u8Key, &u8Flag))
    if(msIR_GetIRKeyCode(&u8Key, &u8Flag))
    {
        if (u8Key == IRKEY_POWER)
            return TRUE;
        else if (g_u16IrRc5Data  == IRKEY_POWER)
            return TRUE;
    }
    return FALSE;
}
#endif
#if (IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
BOOLEAN MDrv_CheckSWIRKey(void)
{

    CurrentTime = gSystemTimeCount;
    if(RxInProcess)
    {
        if((CurrentTime-RxTimeOutCount)>6)
        {
              if(BufIdx==15)
              {
                  IRCHAR('Z');
                  keyDatArray[keyDatArrayWTIdx]=BuffeRX;
                  keyDatArrayWTIdx++;
                  keyDatArrayWTIdx%=10;
              }
              else
              {
                 if(BufLenCurrent>=11)
                 {
                     KeyOffTimeOutCount=gSystemTimeCount;
                 }
                 else
                 {
                     SetToStandbyMode=TRUE;
                 }
              }

              IRCHAR('X');
              IRCHARVALUE((BuffeRX>>8));
              IRCHARVALUE(BuffeRX&0xFF);
              IRCHAR('X');
              IRCHARVALUE(keyDatArrayWTIdx);
              IRCHAR('X');

              BufIdx=0;
              BuffeRX=0;
              CodeReceived=TRUE;
              RxInProcess=FALSE;
        }
    }
    if(ReceivingMode)
        {
            if(keyDatArrayRDIdx!=keyDatArrayWTIdx)
            {
                BufferCurrent=keyDatArray[keyDatArrayRDIdx];
                keyDatArrayRDIdx++;
                keyDatArrayRDIdx%=BUF_LEN;


                IRCHAR('V');
                IRCHARVALUE(BufLenCurrent);
                IRCHAR('V');
                IRCHARVALUE(keyDatArrayRDIdx);
                IRCHAR('V');
                if(((BufferCurrent&0x1F)==0x01)||((BufferCurrent&0x1F)==0x11)||((BufferCurrent&0x1F)==0x1E))
                {
                    SystemBitOK=TRUE;
                    IRCHAR('U');
                }
                else
                {
                     FirstRXFlag=FALSE;
                     BufferPrev=0;
                     BufferCurrent=0;
                     ResetKeyoffTimer();
                     return MSRET_ERROR;
                }
                if(SystemBitOK)
                {
                       SystemBitOK=FALSE;
                       if((((BufferCurrent>>13)&0x03)==0x01)||(((BufferCurrent>>13)&0x03)==0x02))
                       {
                           DetectBitOK=TRUE;
                           IRCHAR('M');
                       }
                       else
                       {
                           FirstRXFlag=FALSE;
                           BufferPrev=0;
                           BufferCurrent=0;
                           ResetKeyoffTimer();
                           return MSRET_ERROR;
                       }
                }
                if(DetectBitOK)
                {
                    DetectBitOK=FALSE;
                    if(FirstRXFlag==TRUE)
                    {
                        SecondRXFlag=TRUE;
                        IRCHAR('K');
                    }
                    else
                    {
                        FirstRXFlag=TRUE;
                        BufferPrev=BufferCurrent;
                        BufferCurrent=0;
                        ResetKeyoffTimer();
                        IRCHAR('C');
                        IRCHARVALUE((BufferPrev>>8));
                        IRCHARVALUE(BufferPrev&0xFF);
                        IRCHAR('C');
                    }
                }
                if(SecondRXFlag)
                {
                    SecondRXFlag=FALSE;


                    IRCHAR('Y');
                    IRCHARVALUE((BufferCurrent>>8));
                    IRCHARVALUE(BufferCurrent&0xFF);
                    DataPlusExDat0=(U8)((BufferCurrent&0x1FE0)>>5);
                    IRCHAR('Y');
                    IRCHARVALUE(DataPlusExDat0);
                    IRCHAR('Y');
                    IRCHAR('W');
                    IRCHARVALUE((BufferPrev>>8));
                    IRCHARVALUE(BufferPrev&0xFF);
                    DataPlusExDat1=(U8)((BufferPrev&0x1FE0)>>5);
                    IRCHAR('W');
                    IRCHARVALUE(DataPlusExDat1);
                    IRCHAR('W');
                    if(DataPlusExDat0==(~DataPlusExDat1))
                    {
                          IRCHAR('Q');
                          IRCHARVALUE(DataPlusExDat0);
                          IRCHAR('Q');
                          DataMatched=TRUE;
                    }
                     if(DataMatched)
                    {
                        DataMatched=FALSE;
                        g_bIrDetect=TRUE;

                        FirstRXFlag=FALSE;

                        keyValueHit = FALSE;
                        TableIdx=0;
                        keyValueHit=FALSE;
                        IRCHAR('A');
                        IRCHARVALUE(u8Cus21SHTableSize);
                        IRCHAR('A');
                        while((TableIdx<u8Cus21SHTableSize)&&(!keyValueHit))
                        {
                               IRCHAR('P');
                               IRCHARVALUE(IR_CUS21SH_RAWDATA_TABLE[TableIdx]);
                               IRCHAR('P');
                               IRCHARVALUE(BufferPrev);
                               IRCHAR('P');
                            if((IR_CUS21SH_RAWDATA_TABLE[TableIdx]&0x1FFF)==(BufferPrev&0x1FFF))
                            {
                                keyValueHit=TRUE;
                                IRCHAR('H');
                                IRCHARVALUE(TableIdx);
                                IRCHAR('H');
                                continue;
                                IRCHAR('H');
                            }
                            TableIdx++;
                        }
                        if(LastKeyData==TableIdx)
                        {
                            IsRepeatData=1;
                        }
                        else
                        {
                            IsRepeatData=0;
                        }
                        u8Key=TableIdx;
                        u8Flag=IsRepeatData;
                        LastKeyData=TableIdx;
                        BufferCurrent=0;
                        BufferPrev=0;
                        IRCHAR('B');
                        IRCHARVALUE(IsRepeatData);
                        IRCHAR('B');
                        /*
                        if(gStandbyInto==TRUE)
                        {
                        putchar('G');
                        temp=TableIdx;


                        if ((temp>>4) <= 9)
                              putchar((temp>>4)+'0');
                        else
                              putchar((temp>>4)-0x0A+'A');

                        if ((temp&0x0F) <= 9)
                              putchar((temp&0x0F)+'0');
                        else
                              putchar((temp&0x0F)-0x0A+'A');

                        putchar('G');
                        }
                        */
                        /*

                        */

                        IRCHAR('U');
                        IRCHARVALUE(u8Key);
                        IRCHAR('U');
                        IRCHARVALUE(IsRepeatData);
                        IRCHAR('U');
                        //printf("\n");
                        #if 0//SHA Standby Using Codes
                        if((gStandbyInto==TRUE)&&(u8Key!=IRKEY_POWER))
                        {
                            return MSRET_ERROR;
                        }
                        #endif
                        return MSRET_OK;
                     }
                    else
                    {
                        BufferPrev=BufferCurrent;
                        BufferCurrent=0;
                        ResetKeyoffTimer();
                        IRCHAR('A');
                    }
                }
            }
            else
            {
                 if((CurrentTime-KeyOffTimeOutCount)>100)
                 {
                     SetToStandbyMode=TRUE;
                 }
                 if(SetToStandbyMode)
                 {
                     IRCHAR('R');
                     IRCHAR('E');
                     IRCHAR('S');
                     IRCHAR('E');
                     IRCHAR('T');
                     SetToStandbyMode=FALSE;
                     ReceivingMode=FALSE;
                     keyDatArrayRDIdx=0;
                     keyDatArrayWTIdx=0;
                     for(j=0;j++;j<10)
                     {
                          keyDatArray[j]=0;
                     }
                     FirstRXFlag=FALSE;
                     BufferPrev=0;
                     BufferCurrent=0;
                     LastKeyData=0xFF;
                     ExpetedTCome=TRUE;
                 }
            }
        }
   return FALSE;
}
#endif

#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
/******************************************************************************/
/// Switch SW IR to Hardware decode mode
/// @param switch \b
/******************************************************************************/
static void msIR_SwitchToFullDecodeMode(void)
{
    msIR_WriteByte(IR_FIFO_CTRL, 0x0F);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
       msIR_WriteByte(IR_GLHRM_NUM_H, 0x38);   // {IR_DECOMODE[1:0], GLHRM_EN,GLHRM_NUM[10:8]}

    //printf("\n##############Switch to Full Decode IR\n");
}

static void msIR_SwitchToSWMode(void)
{
    msIR_WriteByte(IR_FIFO_CTRL, 0x2F);     // Only NSHOT edge detect for counter
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x18);

    //printf("\n****************Switch to SW IR\n");
}

void msIR_SwitchIRMode(U8 mode)
{
    if(IR_TYPE_SWDECODE_MODE == mode)
    {
        g_bIsIrModeSwitchedToSWmode = TRUE;
        msIR_SwitchToSWMode();
    }
    else
    {
        g_bIsIrModeSwitchedToSWmode = FALSE;
        msIR_SwitchToFullDecodeMode();
    }
}

void msIR_ResetSoftWareModeVariables(void)
{
    g_ucIrRepeatSkipCnt = IR_REPEAT_SKIP_COUNT;

    g_ucIrByteIndex = 0;
    g_ucIrPulseCntIndex = 0;
    g_bIrStartReceived = FALSE;

    g_bIrDetect = FALSE;
    g_bIrRepeat = FALSE;
    memset(g_ucIrCode, 0, sizeof(U8)*10);//init ir buffer.
}
#endif
BOOLEAN MDrv_IR_CheckPowerOnKey(void)
{
    if (MDrv_ReadByte(IR_KEY) == IRDA_KEY_MAPPING_POWER ||
        MDrv_ReadByte(IR_KEY) == IRKEY_CHANNEL_PLUS ||
        MDrv_ReadByte(IR_KEY) == IRKEY_CHANNEL_MINUS ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_0 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_1 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_2 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_3 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_4 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_5 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_6 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_7 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_8 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_9 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_NUM_0 ||
        MDrv_ReadByte(IR_KEY) == IRKEY_INPUT_SOURCE
        #if (IR_MODE_SEL != IR_TYPE_SWDECODE_SHA_MODE)
        ||MDrv_ReadByte(IR_KEY) == IRKEY_TV_INPUT
        #endif
        )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

BOOLEAN MDrv_IR_IsIRkeyEnabled(U8 u8IRkey)
{
    switch(u8IRkey)
    {

        #if (IR_MODE_SEL != IR_TYPE_SWDECODE_SHA_MODE)
        case IRKEY_P_CHECK:
        case IRKEY_S_CHECK:
        case IRKEY_ADJUST:
            return TRUE;
        #endif
        case IRKEY_POWER:
            {
                return TRUE;
            }
        default:
            {
                return TRUE;
            }
    }
}

#undef MS_IR_C
