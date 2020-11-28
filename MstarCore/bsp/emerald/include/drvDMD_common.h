////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDMD_common.h
/// @brief  DVBC Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_DMD_COMMON_H_
#define _DRV_DMD_COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    _QPSK        = 0x0,
    _16QAM        = 0x1,
    _64QAM        = 0x2,
    _UNKNOW_QAM   = 0xff,    
}DMD_CONSTEL;

typedef enum
{
    _CR1Y2        = 0x0,
    _CR2Y3        = 0x1,
    _CR3Y4        = 0x2,
    _CR5Y6        = 0x3,
    _CR7Y8        = 0x4,
    _UNKNOW_CR   = 0xff,    
}DMD_CODERATE;

typedef struct
{
    float   power_db;
    MS_U8   sar3_val;
}DMD_RFAGC_SSI;

typedef struct
{
    float   power_db;
    MS_U8   agc_val;
}DMD_IFAGC_SSI;

typedef struct
{
    float   attn_db;
    MS_U8   agc_err;
}DMD_IFAGC_ERR;

typedef struct
{
    DMD_CONSTEL         constel;
    DMD_CODERATE        code_rate;
    float               p_ref;
}DMD_SSI_DBM_NORDIGP1;

typedef struct
{
    DMD_CONSTEL   constel;
    DMD_CODERATE   code_rate;
    float   cn_ref;
}DMD_SQI_CN_NORDIGP1;

typedef struct
{
    DMD_RFAGC_SSI *pRfagcSsi;
    MS_U16 u16RfagcSsi_Size;
    DMD_IFAGC_SSI *pIfagcSsi_LoRef; 
    MS_U16 u16IfagcSsi_LoRef_Size;    
    DMD_IFAGC_SSI *pIfagcSsi_HiRef;   
    MS_U16 u16IfagcSsi_HiRef_Size;    
    DMD_IFAGC_ERR *pIfagcErr_LoRef;  
    MS_U16 u16IfagcErr_LoRef_Size;    
    DMD_IFAGC_ERR *pIfagcErr_HiRef;    
    MS_U16 u16IfagcErr_HiRef_Size;    
}DMD_SSI_TABLE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_DMD_PreInit(void);
void MDrv_DMD_RFAGC_Tristate(MS_BOOL bEnable);
void MDrv_DMD_IFAGC_Tristate(MS_BOOL bEnable);
MS_BOOL MDrv_DMD_TS_GetClockRate(float *fTS_CLK);

/************************************************************************************************
  Subject:    MDrv_DMD_TSO_Clk_Control
  Function:   ts output clock frequency and phase configure
  Parmeter:   u8cmd_array, clock div,           0x01, div (0x00~0x1f), 
                           clock phase inv,     0x02, inv_en (0,1),
                           clock phase tuning,  0x03, phase_tuning_en (0,1), tuning_num (0x00~0x1f)
  Return:     MS_BOOL     
  Remark:
*************************************************************************************************/
MS_BOOL MDrv_DMD_TSO_Clk_Control(MS_U8 *u8cmd_array);

#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBC_H_

