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
/// @file   drvAUDIO.h
/// @author MStar Semiconductor Inc.
/// @brief   Audio common driver
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVAUDIO_H_
#define _DRVAUDIO_H_

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#include "MsTypes.h"
#include "drvAUDIO_if.h"

#ifdef __cplusplus
extern "C"
{
#endif

////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////
/// Version string.
#define MSIF_AUDIO_LIB_CODE             {'A','U','D','-'}    //Lib code
#define MSIF_AUDIO_LIBVER               {'0','0'}            //LIB version
#define MSIF_AUDIO_BUILDNUM             {'5','B'}            //Build Number
#define MSIF_AUDIO_CHANGELIST           {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define AUD_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_AUDIO_LIB_CODE,                /* IP__                                             */  \
    MSIF_AUDIO_LIBVER,                  /* 0.0 ~ Z.Z                                        */  \
    MSIF_AUDIO_BUILDNUM,                /* 00 ~ 99                                          */  \
    MSIF_AUDIO_CHANGELIST,              /* CL#                                              */  \
    MSIF_OS

#define AU_memcpy(  pDstAddr, pSrcAddr, u32Size) \
    do { \
        register unsigned long u32I=0; \
        register unsigned long u32Dst = (unsigned long)pDstAddr; \
        void * pSrc = (void *)pSrcAddr; \
        if( (u32Dst % 4) || ((unsigned long)pSrc % 4) ) \
        { \
            for( u32I=0; u32I< (unsigned long)(u32Size); u32I++) \
            { \
                ((volatile unsigned char *)u32Dst)[u32I] = ((volatile unsigned char *)pSrc)[u32I]; \
            } \
        } \
        else \
        { \
            for( u32I=0; u32I < ((unsigned long)(u32Size)/4); u32I++) \
            { \
                ((volatile unsigned long *)u32Dst)[u32I] = ((volatile unsigned long *)pSrc)[u32I]; \
            } \
            u32Dst += u32I*4; \
            pSrc = (void *)((unsigned long)pSrc + u32I*4); \
            if((u32Size)%4) \
            { \
                for( u32I=0; u32I<((unsigned long)(u32Size)%4); u32I++) \
                { \
                    ((volatile unsigned char *)u32Dst)[u32I] = ((volatile unsigned char *)pSrc)[u32I]; \
                } \
            } \
        } \
    }while(0)

#define AU_Memset(pDstAddr, u8value, u32Size)                   \
    do {                                                        \
        MS_U32 i = 0;                                           \
        volatile MS_U8 *dst = (volatile MS_U8 *)(pDstAddr);     \
        for (i = 0; i < (u32Size); i++)                         \
        {                                                       \
            dst[i] = (u8value);                                 \
        }                                                       \
    } while (0)

//================================================================
//  AUDIO version informtion functions
//================================================================
 extern MS_BOOL MDrv_AUD_GetLibVer(const MSIF_Version **ppVersion);

//================================================================
//  Basic Register read/write function
//================================================================
 MS_U16 MDrv_AUDIO_ReadReg(MS_U32 u32RegAddr);
 void   MDrv_AUDIO_WriteReg(MS_U32 u32RegAddr, MS_U16  u16Val);
 void   MDrv_AUDIO_WriteMaskReg(MS_U32 u32RegAddr, MS_U16  u16Mask, MS_U16  u16Val);

 MS_U8  MDrv_AUDIO_ReadByte(MS_U32 addr);
 MS_U8  MDrv_AUDIO_DecReadByte(MS_U32 addr);
 MS_U8  MDrv_AUDIO_SeReadByte(MS_U32 addr);

 void   MDrv_AUDIO_WriteByte(MS_U32 addr, MS_U8 value);
 void   MDrv_AUDIO_DecWriteByte(MS_U32 addr, MS_U8 value);
 void   MDrv_AUDIO_SeWriteByte(MS_U32 addr, MS_U8 value);

 void   MDrv_AUDIO_WriteMaskByte(MS_U32 u32RegAddr, MS_U8  u8Mask, MS_U8  u8Val);
 void   MDrv_AUDIO_DecWriteMaskByte(MS_U32 u32RegAddr, MS_U8  u8Mask, MS_U8  u8Val);
 void   MDrv_AUDIO_SeWriteMaskByte(MS_U32 u32RegAddr, MS_U8  u8Mask, MS_U8  u8Val);

 MS_U16 MDrv_AUDIO_ReadDecMailBox(MS_U8 paramNum);
 void   MDrv_AUDIO_WriteDecMailBox(MS_U8 paramNum, MS_U16 data1);
 MS_U16 MDrv_AUDIO_ReadSeMailBox(MS_U8 paramNum);
 void   MDrv_AUDIO_WriteSeMailBox(MS_U8 paramNum, MS_U16 data1);

//================================================================
//  For Audio initialize
//================================================================
void    MDrv_AUDIO_InitMMIO(void);
MS_BOOL MDrv_AUDIO_AttachInterrupt(MS_BOOL bEnable);
MS_BOOL MDrv_AUDIO_SHM_Init(void);
MS_BOOL MDrv_AUDIO_Init(void);
MS_BOOL MDrv_AUDIO_Close(void);
MS_BOOL MDrv_AUDIO_Open(void);
void    MDrv_AUDIO_WriteInitTable(void);
void    MDrv_AUDIO_WritePreInitTable(void);                //Refine power on sequence for earphone & DAC pop noise issue
void    MDrv_AUDIO_EnaEarphone_LowPower_Stage(void);    //Refine power on sequence for earphone & DAC pop noise issue
void    MDrv_AUDIO_EnaEarphone_HighDriving_Stage(void);    //Refine power on sequence for earphone & DAC pop noise issue
void    MDrv_AUDIO_SwResetMAD(void);
void    MDrv_AUDIO_SetPowerOn(MS_BOOL bPowerOn);
void    MDrv_AUDIO_SetDspBaseAddr(MS_U8 u8Index, MS_U32 u32Bin_Base_Address, MS_U32 u32Mad_Base_Buffer_Adr);
MS_U32  MDrv_AUDIO_GetDspBinBaseAddr(MS_U8 u8Iindex);
MS_U32  MDrv_AUDIO_GetDspMadBaseAddr(MS_U8 u8Index) ;
void    MDrv_AUDIO_DspBootOnDDR(MS_BOOL bEnable);
MS_BOOL MDrv_AUDIO_DecoderLoadCode(void);
MS_BOOL MDrv_AUDIO_SeSystemLoadCode(void);
void    MDrv_AUDIO_SetSystem(En_DVB_decSystemType enDecSystem);
MS_BOOL MDrv_AUDIO_GetDecSysSupportStatus(En_DVB_decSystemType enDecSystem);
void    MDrv_AUDIO_DspReboot(MS_U8 param);
void    MDrv_AUDIO_RebootDecDSP(void);
void    MDrv_AUDIO_RebootDSP(MS_BOOL bDspType);
void    MDrv_AUDIO_TriggerSifPLL(void);
void    MDrv_AUDIO_SetPlayFileFlag(MS_BOOL bDspType, MS_BOOL bSet);
MS_BOOL MDrv_AUDIO_GetPlayFileFlag(MS_BOOL bDspType);
MS_BOOL MDrv_AUDIO_GetEncodeDoneFlag(void);
MS_BOOL MDrv_AUDIO_InitialVars(void);
void MDrv_AUDIO_SET_INIT_FLAG(MS_BOOL bSet);
MS_BOOL MDrv_AUDIO_GET_INIT_FLAG(void);

//================================================================
// Audio I/O Config. function
//================================================================
AUDIO_PATH_GROUP_TYPE  MDrv_AUDIO_GetPathGroup(void);
void    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_TYPE u8Path, AUDIO_INPUT_TYPE u8Input, AUDIO_OUTPUT_TYPE output);
void    MDrv_AUDIO_SetInputPath( AUDIO_INPUT_TYPE u8Input, AUDIO_PATH_TYPE u8Path);
void    MDrv_AUDIO_SetOutputPath( AUDIO_PATH_TYPE u8Path, AUDIO_OUTPUT_TYPE u8Output);
void    MDrv_AUDIO_SetInternalPath(AUDIO_INTERNAL_PATH_TYPE u8Path,  AUDIO_OUTPUT_TYPE u8Output);
void    MDrv_AUDIO_FwTriggerDSP(MS_U16 u16Cmd);
void    MDrv_AUDIO_I2S_SetMode(MS_U8 u8Mode, MS_U8 u8Value);

MS_U8   MDrv_AUDIO_ReadDspCodeType(void);

void    MDrv_AUDIO_BT_SetUploadRate(MS_BOOL bEnable, MS_U8 u8Samprate);
void    MDrv_AUDIO_BT_SetBufferCounter(MS_U32 u32Counter);

void    MDrv_AUDIO_USBPCM_Enable(MS_BOOL bEnable);
void    MDrv_AUDIO_USBPCM_SetFlag(MS_BOOL bEnable);
MS_BOOL MDrv_AUDIO_USBPCM_GetFlag(void);
void    MDrv_AUDIO_USBPCM_GetMemInfo(AUDIO_UPLOAD_INFO *uploadInfo);

MS_U8   MDrv_AUDIO_ReadDspCounter(AUDIO_DSP_COUNTER_TYPE CounterType);
void    MDrv_AUDIO_SetPowerDownWait(MS_BOOL bEnable);
MS_BOOL MDrv_AUDIO_IsDTV(void);
void    MDrv_AUDIO_SetFading(MS_U32 u32VolFading);
void    MDrv_AUDIO_SendIntrupt(MS_BOOL bDspType,MS_U16 u8Cmd);

//=====================================================
// AUDIO SPDIF Relational Hal Function
//=====================================================
void    MDrv_AUDIO_SPDIF_HWEN(MS_U8 spdif_hwen);
void    MDrv_AUDIO_SPDIF_SetMute(MS_U8 mute_en);
void    MDrv_AUDIO_SPDIF_SetMode(MS_U8 spdif_mode, MS_U8 input_src);
MS_U8   MDrv_AUDIO_SPDIF_GetMode(void);
void    MDrv_AUDIO_SPDIF_ByPassChannel(MS_BOOL u8Enable);
void    MDrv_AUDIO_SPDIF_SetSCMS(MS_U8 C_bit_en, MS_U8 L_bit_en);
MS_U8   MDrv_AUDIO_SPDIF_GetSCMS(void);
void    MDrv_AUDIO_SPDIF_SetChannelStatus(SPDIF_CS_MODE_TYPE eType, SPDIF_CS_MODE_VALUE eValue);
MS_BOOL MDrv_AUDIO_SPDIF_ChannelStatus_CTRL(AUDIO_SPDIF_CS_TYPE cs_mode, AUDIO_SPDIF_CS_TYPE_STATUS status);
void    MDrv_AUDIO_SPDIF_Monitor_SamplingRate(void);

//=====================================================
// AUDIO HDMI Relational Hal Function
//=====================================================
void    MDrv_AUDIO_HDMI_Tx_SetMute(MS_U8 bEnMute);
void    MDrv_AUDIO_HDMI_Tx_GetStatus(MS_BOOL *onOff, AUDIO_FS_TYPE *hdmi_SmpFreq, HDMI_TX_OUTPUT_TYPE *outType );
MS_BOOL MDrv_AUDIO_HDMI_NonpcmMonitor(void);
MS_U8   MDrv_AUDIO_HDMI_DolbyMonitor(void);
AUDIO_HDMI_RX_TYPE MDrv_AUDIO_HDMI_SetNonpcm(MS_U8 u8NonPCM_en);
void    MDrv_AUDIO_HDMI_AC3_PathCFG(MS_U8 u8Ctrl);
MS_U16  MDrv_AUDIO_HDMI_GetSynthFreq(void);
void    MDrv_AUDIO_HDMI_SetDownSample(MS_U8 ratio);
void    MDrv_AUDIO_HDMI_TX_SetMode(HDMI_TX_OUTPUT_TYPE outType, AUDIO_SOURCE_INFO_TYPE eSource);
MS_BOOL MDrv_AUDIO_HDMI_RX_GetHdmiInAudioStatus( ST_HDMI_AUDIO_STATUS *p_hdmiAudioSts);
//================================================================
// for audio driver internal use function
//================================================================
void    MDrv_AUDIO_AdcInit(void);
MS_U8   MDrv_AUDIO_GetDecoderStatus(void);
void    MDrv_AUDIO_DmaReader_Init(SAMPLE_RATE sampleRate);
void    MDrv_AUDIO_DmaReader_AllInput_Init(void);
MS_BOOL MDrv_AUDIO_DmaReader_WritePCM(void* buffer, MS_U32 bytes);
void    MDrv_AUDIO_DmaWriter_Init(void);

MS_U16  MDrv_AUDIO_GetUniDecodeDoneTag(void);

//================================================================
// Audio VoIP Interface Relational Function
//================================================================
MS_BOOL MDrv_AUDIO_VoIP_Config(AUDIO_VoIP_CONFIG_TYPE configType, MS_U32 param1, MS_U32 param2);

//================================================================
// Audio ALSA Interface Relational Function
//================================================================
MS_BOOL MDrv_AUDIO_ALSA_Check(void);
MS_BOOL MDrv_AUDIO_ALSA_Enable(MS_BOOL bEnable);

//====== STAOS PIP START 2012/02/02 ========

En_DVB_decSystemType MDrv_AUDIO_CheckHashkey2(AUDIO_DEC_ID DecId, MMA_AudioType Param);

//====== STAOS PIP END 2012/02/02 ========

#ifdef __cplusplus
}
#endif

#endif

