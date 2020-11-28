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
/// @file    drvTVEncoder.h
/// @brief  TVEncoder interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVTVENCODER_H
#define _DRVTVENCODER_H

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_VE_TAG                 {'M','S','I','F'}    //Version ID header
#define MSIF_VE_CLASS               {'0','0'}            //info Class code
#define MSIF_VE_CUS                 0x6666               //Customer ID
#define MSIF_VE_MOD                 0x6666               //Module ID
#define MSIF_VE_CHIP                0Xffff               //CHIP ID
#define MSIF_VE_CPU                 '1'                  //CPU
#define MSIF_VE_LIB_CODE            {'V','E','_','_'}    //Lib code
#define MSIF_VE_LIBVER              {'0','1'}            //LIB version
#define MSIF_VE_BUILDNUM            {'0','2'}            //Build Number
#define MSIF_VE_CHANGELIST          {'0','0','5','7','0','4','3','2'} //P4 ChangeList Number
//#define MSIF_OS                     '0'                  //OS

#define VE_DRV_VERSION                  /* Character String for DRV/API version             */  \
    MSIF_VE_TAG,                        /* 'MSIF'                                           */  \
    MSIF_VE_CLASS,                      /* '00'                                             */  \
    MSIF_VE_CUS,                        /* 0x0000                                           */  \
    MSIF_VE_MOD,                        /* 0x0000                                           */  \
    MSIF_VE_CHIP,                                                                               \
    MSIF_VE_CPU,                                                                                \
    MSIF_VE_LIB_CODE,                   /* IP__                                             */  \
    MSIF_VE_LIBVER,                     /* 0.0 ~ Z.Z                                        */  \
    MSIF_VE_BUILDNUM,                   /* 00 ~ 99                                          */  \
    MSIF_VE_CHANGELIST,                 /* CL#                                              */  \
    MSIF_OS

/// version of structure 'MS_VE_VECAPTURESTATE' of current VE lib
#define VE_VECAPTURESTATE_VERSION                          0 //Version number for compatibility with AP and VE driver
#define VE_INPUTSRC_INFO_VERSION                           0

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// Result of VE function
typedef enum _VE_Result
{
    E_VE_NOT_SUPPORT = -1,
    E_VE_FAIL = 0,
    E_VE_OK = 1,
    E_VE_TIMEOUT,
    E_VE_QUEUE_FULL,
    E_VE_BUSY
} VE_Result;

/// definition of video system
typedef enum
{
    MS_VE_NTSC,     ///< NTSC
    MS_VE_NTSC_443, ///< NTSC443
    MS_VE_NTSC_J,   ///< NTSC_J
    MS_VE_PAL_M,    ///< PAL_M
    MS_VE_PAL_N,    ///< PAL_N
    MS_VE_PAL_NC,   ///< PAL_Nc
    MS_VE_PAL,      ///< PAL_B
    MS_VE_SECAM,    ///< SECAM
    MS_VE_VIDEOSYS_NUM,
} MS_VE_VIDEOSYS;

/// VE cap's capability
typedef struct
{
    MS_BOOL bNTSC;
    MS_BOOL bPAL;
    MS_BOOL bVESupported;		///< supported VE or not
} VE_Caps;

/// VE extented capability: for STB chips, not all chips support up-scaling or
/// crop
typedef struct
{
    MS_BOOL bSupport_UpScale;
    MS_BOOL bSupport_CropMode;
} MS_VE_Ext_Cap;

/// VE driver info.
typedef struct
{
    VE_Caps stCaps;
} VE_DrvInfo;

/// VE DRV status
typedef struct
{
    MS_VE_VIDEOSYS         VideoSystem;         // video std of output signal
    MS_U16  u16H_CapStart;
    MS_U16  u16H_CapSize;
    MS_U16  u16V_CapStart;
    MS_U16  u16V_CapSize;

} VE_DrvStatus;

typedef struct
{
    MS_U8*     pVE_TBL;
    MS_U8*     pVE_Coef_TBL;
    MS_U8*     pVBI_TBL;
    MS_BOOL    bvtotal_525;
    MS_BOOL    bPALSwitch;
    MS_BOOL    bPALout;
}MS_VE_Out_VideoSYS, *PMS_VE_Out_VideoSYS;

/// type of output destination for TV encoder
typedef enum
{
    MS_VE_DEST_NONE = 0,
    MS_VE_DEST_SCART,     ///< output destination is SCART
    MS_VE_DEST_CVBS,      ///< output destination is CVBS
    MS_VE_DEST_SVIDEO,    ///< output destination is S-Video
    MS_VE_DEST_YPBPR,     ///< output destination is YPbPr
    MS_VE_DEST_NUM,
} MS_VE_OUTPUT_DEST_TYPE;

/// type of input source for TV encoder
typedef enum
{
    MS_VE_SRC_DTV       = 0x00, ///< input source is DTV
    MS_VE_SRC_ATV       = 0x01, ///< input source is ATV
    MS_VE_SRC_CVBS0     = 0x02, ///< input source is CVBS0
    MS_VE_SRC_CVBS1     = 0x03, ///< input source is CVBS1
    MS_VE_SRC_CVBS2     = 0x04, ///< input source is CVBS2
    MS_VE_SRC_CVBS3     = 0x05, ///< input source is CVBS3
    MS_VE_SRC_SVIDEO    = 0x06, ///< input source is SVIDEO
    MS_VE_SRC_DSUB      = 0x07, ///< input source is DSUB
    MS_VE_SRC_COMP      = 0x08, ///< input source is COMP
    MS_VE_SRC_HDMI_A    = 0x09, ///< input source is COMP
    MS_VE_SRC_HDMI_B    = 0x0A, ///< input source is COMP
    MS_VE_SRC_HDMI_C    = 0x0B, ///< input source is COMP
    MS_VE_SRC_MAIN      = 0x0C, ///< input source is from main window
    MS_VE_SRC_SUB       = 0x0D, ///< input source is from sub window
    MS_VE_SRC_SCALER    = 0x0E, ///< input source is scaler op2
    MS_VE_SRC_DI        = 0x0F, ///< input source is DI
    MS_VE_SRC_BT656     = 0x10, ///< input source is BT656
    MS_VE_SRC_DTV_FROM_MVOP = 0x11,  ///< input source is DTV but from MVOP
    MS_VE_SRC_DNR       = 0x12,  ///< input source is DNR
    MS_VE_SRC_NONE      = 0xFF,
}MS_VE_INPUT_SRC_TYPE;

typedef struct
{
    MS_U32 PreHScalingRatio;
    MS_U32 PreVScalingRatio;
    MS_U32 PostHScalingRatio;
    MS_U32 PostVScalingRatio;
}MS_VE_Backup_Reg, *PMS_VE_Backup_Reg;

/// status of switchinging output destination
typedef enum
{
    MS_VE_SWITCH_DST_SUCCESS,               ///< success
    MS_VE_SWITCH_DST_INVALID_COMBINATION,   ///< invalid combination
    MS_VE_SWITCH_DST_INVALID_PARAM,         ///< invalid parameter
    MS_VE_SWITCH_DST_FAIL,                  ///< fail
}MS_SWITCH_VE_DST_STATUS;


/// VE output Type
typedef enum
{
    MS_VE_OUT_CCIR656,  ///< output signal is CCIR656
    MS_VE_OUT_TVENCODER,///< output signal from TVEncoder
    MS_VE_OUT_CAPTURE,///<   output signal from VE Capture
}MS_VE_OUT_TYPE;

typedef struct
{
    MS_U16  u16Width;
    MS_U16  u16height;
    MS_U32  u32MiuBaseAddr;
    MS_U32  u32MemSize;
    MS_BOOL bVECapture; ///< TRUE/FALSE, enable/disable VE capture
}MS_VE_Output_CAPTURE, *PMS_VE_Output_CAPTURE;

/// the information of switching ouput destination for TV encoder
typedef struct
{
    MS_VE_OUTPUT_DEST_TYPE OutputDstType; ///< type of output destination
    MS_SWITCH_VE_DST_STATUS Status;     ///< the returning status of switching output destination
}MS_Switch_VE_Dest_Info, *PMS_Switch_VE_Dest_Info;


/// status of switchinging input source
typedef enum
{
    MS_VE_SWITCH_SRC_SUCCESS,           ///< success
    MS_VE_SWITCH_SRC_INVALID_PARAM,     ///< invalid parameter
    MS_VE_SWITCH_SRC_FAIL,              ///< fail
}MS_SWITCH_VE_SRC_STATUS;

/// the information of switching output destination for TV encoder
typedef struct
{
    MS_VE_INPUT_SRC_TYPE InputSrcType; ///< type of input source
    MS_SWITCH_VE_SRC_STATUS Status; ///< the returning status of switching input source
}MS_Switch_VE_Src_Info, *PMS_Switch_VE_Src_Info;

typedef struct
{
    MS_U16  u16Version;   //< Version number for this structure
    MS_VE_INPUT_SRC_TYPE eInputSrcType; ///< type of input source for Video encoder
    MS_VE_INPUT_SRC_TYPE eInputSrcOfMixedSrc;  // The real input source for mixed "InputSrcType" of VE,
                                              // eg. Real InputSrc of "MS_VE_SRC_MAIN", "MS_VE_SRC_SUB", "MS_VE_SRC_SCALER" etc.
}MS_VE_InputSrc_Info, *PMS_VE_InputSrc_Info;

/// output control for VE
typedef struct
{
    MS_BOOL bEnable; ///< TRUE/FALSE, enable/disable VE
    MS_VE_OUT_TYPE OutputType; ///< VE output type
}MS_VE_Output_Ctrl, *PMS_VE_Output_Ctrl;

/// VE set mode type
typedef struct
{
    MS_U16 u16H_CapStart;
    MS_U16 u16H_CapSize;
    MS_U16 u16V_CapStart;
    MS_U16 u16V_CapSize;
    MS_U16 u16H_SC_CapStart;
    MS_U16 u16H_SC_CapSize;
    MS_U16 u16V_SC_CapStart;
    MS_U16 u16V_SC_CapSize;
    MS_U16 u16InputVFreq;
    MS_BOOL bHDuplicate;
    MS_BOOL bSrcInterlace;
}MS_VE_Set_Mode_Type;

//VE_ApiStatus
typedef struct
{
    PMS_VE_Output_Ctrl      output_ctrl;
    MS_Switch_VE_Src_Info   src_info;
    MS_Switch_VE_Dest_Info  dst_info;
}MS_VE_ApiStatus;

/// Define Window position and size attribute
typedef struct
{
    MS_U16 x;    ///<start x of the window
    MS_U16 y;    ///<start y of the window
    MS_U16 width;    ///<width of the window
    MS_U16 height;    ///<height of the window
} MS_VE_WINDOW_TYPE;

//Display information
typedef struct
{
    MS_U32 VDTOT; //Output vertical total
    MS_U32 DEVST; //Output DE vertical start
    MS_U32 DEVEND;//Output DE Vertical end
    MS_U32 HDTOT;// Output horizontal total
    MS_U32 DEHST; //Output DE horizontal start
    MS_U32 DEHEND;// Output DE horizontal end
    MS_BOOL bInterlaceMode;
} MS_VE_DST_DispInfo;

//VE register bank
typedef enum
{
    MS_VE_REG_BANK_3B,
    MS_VE_REG_BANK_3E,
    MS_VE_REG_BANK_3F,
} MS_VE_REG_BANK;

//External Info
typedef struct
{
    //op to ve timing
    MS_U16 u16VttIn;
    MS_U16 u16HttIn;
    MS_U16 u16HdeIn;
    MS_U16 u16VdeIn;

    MS_U16 u16Vde_St;
    MS_U16 u16Hde_St;

}MS_VE_PLL_InCfg;

//VE customer scaling setting
typedef struct
{
    MS_U16   u16HScalingsrc; ///< H Source size for VE scaling
    MS_U16   u16HScalingdst;///< H Dest size for VE scaling
    MS_U16   u16VScalingsrc;///< V Source size for VE scaling
    MS_U16   u16VScalingdst;///< V Dest size for VE scaling
    MS_BOOL  bHCusScalingEnable; ///< Enable/Disable H customer scaling
    MS_BOOL  bVCusScalingEnable; ///< Enable/Disable V customer scaling
}MS_VE_CusScalingInfo, *PMS_VE_CusScalingInfo;

//Structure AP use
typedef struct
{
    MS_U16  u16Version;   //< Version number for this structure
    MS_U16  u16Length;    //< Length of this structure, unit: byte
    MS_BOOL bEnable;      //< InOut, VE capture enable state
    MS_U8   u8FrameCount; //< Out, Current captured frame number,value range: 0~3
    MS_U8   u8Result;     //< Out, Function return status
}MS_VE_VECAPTURESTATE, *PMS_VE_VECAPTURESTATE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// @brief \b Function \b Name: MDrv_VE_GetLibVer
/// @brief \b Function \b Description: Show the VE driver version
/// @param ppVersion \b Out: Library version string
/// @return             @ref  VE_Result
//-------------------------------------------------------------------------------------------------
VE_Result MDrv_VE_GetLibVer(const MSIF_Version **ppVersion);

//-------------------------------------------------------------------------------------------------
/// Get VE Information
/// @return @ref VE_DrvInfo return the VE information in this member
//-------------------------------------------------------------------------------------------------
const VE_DrvInfo * MDrv_VE_GetInfo(void);

//-------------------------------------------------------------------------------------------------
/// Get VE Status
/// @param  pDrvStatus                  \b OUT: store the status
/// @return @ref VE_Result
//-------------------------------------------------------------------------------------------------
VE_Result MDrv_VE_GetStatus(VE_DrvStatus *pDrvStatus);

void MDrv_VE_SetDbgLevel(MS_U16 level);
void MDrv_VE_GetCaps(VE_Caps* pCaps);

//------------------------------------------------------------------------------
/// set the input source of video encoder
///
/// @param  -pSwitchInfo \b IN/OUT: the information of switching input destination of TV encodeer
/// @return None
//------------------------------------------------------------------------------
void MDrv_VE_SwitchInputSource(PMS_Switch_VE_Src_Info pSwitchInfo);

//------------------------------------------------------------------------------
/// Extended API for set the input source of video encoder(To Expand&Replace MDrv_VE_SwitchInputSource)
///
/// @param  -pSwitchInfo \b IN/OUT: the information of switching input destination of TV encodeer
/// @return @ref MS_SWITCH_VE_SRC_STATUS
//------------------------------------------------------------------------------
MS_SWITCH_VE_SRC_STATUS MDrv_VE_SetInputSource(PMS_VE_InputSrc_Info pInputSrcInfo);

//------------------------------------------------------------------------------
/// set the output destination of video encoder
///
///              None SCART CVBS SVIDEO YPbPr
///       None    O     O     O     O     O
///       SCART O      -     X     X     X
///        CVBS  O     X      -     O     O
///     S_VIDE  O     O     X      O     -     X
///       YPbPr   O     X     O      X     -
///
/// @param  -pSwitchInfo \b IN/OUT: the information of switching output destination of TV encodeer
/// @return None
//------------------------------------------------------------------------------
void MDrv_VE_SwitchOuputDest(PMS_Switch_VE_Dest_Info pSwitchInfo);

//------------------------------------------------------------------------------
/// control the output of video encoder
///
/// @param  -pOutputCtrl \b IN: the control information of VE
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetOutputCtrl(PMS_VE_Output_Ctrl pOutputCtrl);

//------------------------------------------------------------------------------
/// set the output video standard of video encoder
///
/// @param  -VideoSystem \b IN: the video standard
/// @return TRUE: supported and success,  FALSE: unsupported or unsuccess
//------------------------------------------------------------------------------
MS_BOOL MDrv_VE_SetOutputVideoStd(MS_VE_VIDEOSYS VideoSystem);

void MDrv_VE_PowerOn(void);
void MDrv_VE_PowerOff(void);
MS_BOOL MDrv_VE_SetIOMapBase(void);

//------------------------------------------------------------------------------
/// Initiate VE
/// @param[in]  u32MIUAddress  \b IN: The address reserved for VE
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_Init(MS_PHYADDR u32MIUAddress);

MS_BOOL MDrv_VE_Exit(void);
void MDrv_VE_SetWSSData(MS_BOOL bEn, MS_U16 u16WSSData);
MS_U16 MDrv_VE_GetWSSData(void);

//------------------------------------------------------------------------------
/// VE Setmode. Configurate VE for CVBS out.
/// @param[in]  pVESetMode  \b IN: The parameter for VE
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetMode(MS_VE_Set_Mode_Type * pVESetMode);

//------------------------------------------------------------------------------
/// Output black screen from VE. This function is not for disabling VE.
/// @param[in]  pVESetMode  \b IN: The parameter for VE
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetBlackScreen(MS_BOOL bEn);

//------------------------------------------------------------------------------
/// Return true if VE output black video right now.
/// @param[in]  pVESetMode  \b IN: The parameter for VE
/// @return none
//------------------------------------------------------------------------------
MS_BOOL MDrv_VE_IsBlackScreenEnabled(void);

//------------------------------------------------------------------------------
/// VE restart TVE to read data from TT buffer
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_EnableTtx(MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// VE set TT buffer address
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetTtxBuffer(MS_U32 u32StartAddr, MS_U32 u32Size);

//------------------------------------------------------------------------------
/// VE clear TT buffer read done status
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_ClearTtxReadDoneStatus(void);

//------------------------------------------------------------------------------
/// VE TT buffer read done status
/// @return TRUE/FALSE
//------------------------------------------------------------------------------
MS_BOOL MDrv_VE_GetTtxReadDoneStatus(void);

//------------------------------------------------------------------------------
/// VE Set VBI TT active Lines
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetVbiTtxActiveLines(MS_U8 u8LinePerField);

//------------------------------------------------------------------------------
/// VE Set VBI TT active Lines by the given bitmap
/// @param <IN>\b u32Bitmap: a bitmap that defines whick physical lines the teletext lines are to be inserted.
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetVbiTtxActiveLinesBitmap(MS_U32 u32Bitmap);

//------------------------------------------------------------------------------
/// VE Set VBI ttx active line
/// @param <IN>\b odd_start: odd page start line
/// @param <IN>\b odd_end: odd page end line
/// @param <IN>\b even_start: even page start line
/// @param <IN>\b even_end: even page end line
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetVbiTtxRange(MS_U16 odd_start, MS_U16 odd_end,
                            MS_U16 even_start, MS_U16 enen_end);
//------------------------------------------------------------------------------
/// VE Set VBI CC
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_EnableCcSw(MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// VE Set VBI CC active line
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetCcRange(MS_U16 odd_start, MS_U16 odd_end, MS_U16 even_start, MS_U16 enen_end);

//------------------------------------------------------------------------------
/// VE Set VBI CC data
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SendCcData(MS_BOOL bIsOdd, MS_U16 data);

//------------------------------------------------------------------------------
/// VE Set display windows
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_set_display_window(MS_VE_WINDOW_TYPE stDispWin);

//------------------------------------------------------------------------------
/// VE Set output with OSD
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetOSD(MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// VE Set RGB In
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetRGBIn(MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// VE Get output video standard
/// @param <RET>       \b VideoSystem : the video standard: PAL or NTSC
//------------------------------------------------------------------------------
MS_VE_VIDEOSYS MDrv_VE_Get_Output_Video_Std(void);

//------------------------------------------------------------------------------
/// VE Set Capture Mode
/// @return none
//------------------------------------------------------------------------------
void MDrv_VE_SetCaptureMode(MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// VE Get Destination Information for GOP mixer
/// @return TRUE/FALSE
//------------------------------------------------------------------------------
MS_BOOL MApi_VE_GetDstInfo(MS_VE_DST_DispInfo *pDstInfo, MS_U32 u32SizeofDstInfo);

void MDrv_VE_Set_TestPattern(MS_BOOL bEn);

void MApi_VE_W2BYTE_MSK(MS_VE_REG_BANK VE_BK, MS_U32 u32Reg, MS_U16 u16Val, MS_U16 u16Mask);
MS_U16 MApi_VE_R2BYTE_MSK(MS_VE_REG_BANK VE_BK, MS_U32 u32Reg, MS_U16 u16Mask);

//------------------------------------------------------------------------------
/// VE Dump Table Interfac
/// @return TRUE/FALSE
//------------------------------------------------------------------------------
void MDrv_VE_DumpTable(MS_U8 *pVETable, MS_U8 u8TableType);

//------------------------------------------------------------------------------
/// @brief This routine set flag to mask register write for special case \n
///			e.g. MBoot to APP with logo display
/// @argument:
///              - bFlag: TRUE: Mask register write, FALSE: not Mask
/// @return None
//------------------------------------------------------------------------------
VE_Result MDrv_VE_DisableRegWrite(MS_BOOL bFlag);

//------------------------------------------------------------------------------
/// VE show internal color bar (test pattern)
/// @param  - bEnable IN: TRUE to enable color; false to disable color bar
/// @return None
//------------------------------------------------------------------------------
void MDrv_VE_ShowColorBar(MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// @brief This routine set read/write addjustment to centralize VE display window.\n
///        Set the adjustment and it works after MDrv_VE_set_display_window() API is invoked. \n
///
/// @argument:
///              - s32WAddrAdjustment: the pixel units to adjust on write address
///              - s32RAddrAdjustment: the pixel units to adjust on read address
/// @return VE_Result
//------------------------------------------------------------------------------
VE_Result MDrv_VE_AdjustPositionBase(MS_S32 s32WAddrAdjustment, MS_S32 s32RAddrAdjustment);

//------------------------------------------------------------------------------
/// @brief In STB Chip, VE needs to set vepll to lock frame rate with HD Path.\n
///
/// @argument:
///              - MS_VE_PLL_InCfg: Information of HD path
///              - MS_BOOL: enable/disable frame lock
/// @return VE_Result
//------------------------------------------------------------------------------
VE_Result MDrv_VE_SetFrameLock(MS_VE_PLL_InCfg *pInCfg, MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// @brief Provide the capability of Customer scaling for VE.\n
///
/// @argument:
///              - MS_VE_CusScalingInfo : Src and Dest info for customer scaling, @ref MS_VE_CusScalingInfo
/// @return @ref VE_Result
//------------------------------------------------------------------------------
VE_Result  MDrv_VE_Set_Customer_Scaling(MS_VE_CusScalingInfo *pstVECusScalingInfo);
//------------------------------------------------------------------------------
/// @brief MDrv_VE_set_crop_window, set up crop window (crop video frame in MIU)
///
/// @argument:
///          - MS_VE_WINDOW_TYPE - crop window
/// @return VE_Result
//------------------------------------------------------------------------------
VE_Result MDrv_VE_set_crop_window(MS_VE_WINDOW_TYPE stCropWin);
//------------------------------------------------------------------------------
/// @brief VE be set display window (backend), after MIU
///
/// @argument:
///          - MS_VE_WINDOW_TYPE - display window
/// @return VE_Result
//------------------------------------------------------------------------------
VE_Result MDrv_VE_set_be_display_window(MS_VE_WINDOW_TYPE stDispWin);
//------------------------------------------------------------------------------
/// @brief MDrv_VE_Get_Ext_Caps: get VE extented capability
///
/// @argument:
/// @return VE_Result
//------------------------------------------------------------------------------
VE_Result MDrv_VE_Get_Ext_Caps(MS_VE_Ext_Cap *cap);
//------------------------------------------------------------------------------
/// @brief MDrv_VE_SetWindow, set crop window and display window in one API.
///
/// @argument:
///     - a pointer to MS_VE_WINDOW_TYPE - source window, depends on input size
///     - a pointer to MS_VE_WINDOW_TYPE - crop window, depends on source window size
///     - a pointer to MS_VE_WINDOW_TYPE - display window, depends on output size
/// @return VE_Result
//------------------------------------------------------------------------------
VE_Result MDrv_VE_SetWindow(MS_VE_WINDOW_TYPE *stSrcWin, MS_VE_WINDOW_TYPE *stCropWin,
        MS_VE_WINDOW_TYPE *stDispWin);

/******************************************************************************/
/// Init and config the VE capture
/// @param pVECapture \b IN : @ref PMS_VE_Output_CAPTURE
/// @return TRUE: success
/// @return FALSE: fail
/******************************************************************************/
void MDrv_VE_InitVECapture(PMS_VE_Output_CAPTURE pVECapture);

/******************************************************************************/
/// Enable VE capture
/// @param pstVECapState \b IN : @ref PMS_VE_VECAPTURESTATE
/// @return TRUE: success
/// @return FALSE: fail
/******************************************************************************/
MS_BOOL MDrv_VE_EnaVECapture(PMS_VE_VECAPTURESTATE pstVECapState);

/******************************************************************************/
/// Get VE capture state
/// @param pstVECapState \b OUT : @ref PMS_VE_VECAPTURESTATE
/// @return TRUE: success
/// @return FALSE: fail
/******************************************************************************/
MS_BOOL MDrv_VE_GetVECaptureState(PMS_VE_VECAPTURESTATE pstVECapState);

//-------------------------------------------------------------------------------------------------
/// Wait on the finish of specified frame: Check if the frame is captured,
/// if Yes, return TRUE, otherwise sleep until the next Vsync ISR
/// @param  pstVECapState          \b IN : @ref PMS_VE_VECAPTURESTATE
/// @return TRUE: success
/// @return FALSE: fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_VE_VECaptureWaitOnFrame(PMS_VE_VECAPTURESTATE pstVECapState);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MDrv_VE_Adjust_FrameStart
/// @brief \b Function \b Description : the frame start is used to adjust output video
///                                     (in pixel)
///
/// @param <IN>        \b stSrcWin :source window, depends on input size
/// @param <IN>        \b pixel_offset
/// @return VE_Result
////////////////////////////////////////////////////////////////////////////////
VE_Result MDrv_VE_Adjust_FrameStart(MS_VE_WINDOW_TYPE *stSrcWin,MS_S16 pixel_offset);

#ifdef __cplusplus
}
#endif

#endif  // _DRVTVENCODER_H
