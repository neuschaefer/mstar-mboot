////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _DRV_VBI_H
#define _DRV_VBI_H

#include "MsTypes.h"
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
#define VBI_TTX_DATA_LENGTH 48

#define MSIF_VBI_LIB_CODE                   {'V','B','I','_'} //Lib code
#define MSIF_VBI_LIBVER                        {'0','0'}      //LIB version
#define MSIF_VBI_BUILDNUM                 {'0','2' }    //Build Number
#define MSIF_VBI_CHANGELIST             {'0','0','5','6','5','9','8','0'} //P4 ChangeList Number
#define VBI_VER                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_VBI_LIB_CODE,                  /* IP__                                             */  \
    MSIF_VBI_LIBVER,                       /* 0.0 ~ Z.Z                                        */  \
    MSIF_VBI_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_VBI_CHANGELIST,             /* CL#                                              */  \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    VBI_VIDEO_SECAM,
    VBI_VIDEO_PAL_NC,
    VBI_VIDEO_OTHERS
} VBI_VIDEO_STANDARD;

typedef enum
{
    E_VBI_TELETEXT,
    E_VBI_CC
} VBI_INIT_TYPE;

typedef struct
{
    MS_U8   u8NoInfo;
} VBI_DrvInfo;

typedef struct
{
    VBI_INIT_TYPE   eInitType;
} VBI_DrvStatus;

/*
 * ClosedCaption
 */
typedef enum
{
    VBI_CC_PACKET_COUNT,
    VBI_CC_BYTE_FOUND_INDICATION,
    VBI_CC_DATA_GET

} EN_VBI_INFO;

/* Error code */
typedef enum
{
    VBI_ERRORCODE_SUCCESS            = 0x0000,
    VBI_ERRORCODE_FAIL               = 0x0001

} EN_VBI_ERRORCODE;

typedef enum
{
    EN_TTX_DMA_HEADER,
    EN_TTX_DMA_PACKET1_TO_25,
    EN_TTX_DMA_PACKET26_28_29,
    EN_TTX_DMA_PACKET27,
    EN_TTX_DMA_BTT,
    EN_TTX_DMA_AIT,
} EN_TTX_DMA_TYPE;

typedef MS_U32(*VBI_CB_FN)(MS_U8 *pVBILine, MS_U32 length);
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

// must have functions
MS_BOOL MDrv_VBI_GetLibVer(const MSIF_Version **ppVersion);                  ///< Get version (without Mutex protect)
const VBI_DrvInfo * MDrv_VBI_GetInfo(void);              ///< Get info from driver (without Mutex protect)
MS_BOOL MDrv_VBI_GetStatus(VBI_DrvStatus *pDrvStatus);   ///< Get VBI current status
MS_BOOL MDrv_VBI_SetDbgLevel(MS_U16 u16DbgSwitch);       ///< Set debug level (without Mutex protect)

/****************************************************************************
 *@brief            : Initialize VBI
 *@param type       : [IN] VBI type (Teletext/CC)
 *@return
 *  - TRUE : initialize VBI successfully.
 *  - FALSE: initialize VBI unsuccessfully.
 ****************************************************************************/
MS_BOOL MDrv_VBI_Init(VBI_INIT_TYPE type);

/****************************************************************************
 *@brief            : Set Callback to VBI driver, the CB will be called if VBI interrupt is catched
 *@param pFN : [IN] call back function pointer.
 *@param bufferAddr : [IN] the physical address of buffer which will store VBI data and pass pointer to CB
 *@param length : [IN] the data lebgth of th input buffer. Note: it should be the multiple of VBI_TTX_DATA_LENGTH
 *@return
 ****************************************************************************/
void MDrv_VBI_RegisterCB(VBI_CB_FN pFN, MS_PHYADDR bufferAddr, MS_U32 length);

/****************************************************************************
 *@brief            : Reset TTX Ring Buffer
 *@param
 *@return
 ****************************************************************************/
void MDrv_VBI_RingBuffer_Reset(void);

/****************************************************************************
 *@brief            : Initialize TTX Slicer
 *@param bufferAddr : [IN] TTX buffer address
 *@param packetCount: [IN] TTX packet count
 *@return
 ****************************************************************************/
void MDrv_VBI_InitializeTTXSlicer(MS_PHYADDR bufferAddr, MS_U16 packetCount);

/****************************************************************************
 *@brief            : Enable TTX Slicer
 *@param bEnable    : [IN] enable or disable TTX slicer
 *@return
 ****************************************************************************/
void MDrv_VBI_EnableTTXSlicer(MS_BOOL bEnable);

/****************************************************************************
 *@brief            : VPS Is Ready or Not
 *@param
 *@return
 *  - TRUE : VPS is ready.
 *  - FALSE: VPS is not ready.
 ****************************************************************************/
MS_BOOL MDrv_VBI_IsVPS_Ready(void);

/****************************************************************************
 *@brief            : TTX Is Ready or Not
 *@param
 *@return
 *  - TRUE : TTX is ready.
 *  - FALSE: TTX is not ready.
 ****************************************************************************/
MS_BOOL MDrv_VBI_IsTTX_Ready(void);

/****************************************************************************
 *@brief            : WSS Is Ready or Not
 *@param
 *@return
 *  - TRUE : WSS is ready.
 *  - FALSE: WSS is not ready.
 ****************************************************************************/
MS_BOOL MDrv_VBI_IsWSS_Ready(void);

/****************************************************************************
 *@brief            : Get WSS Data
 *@param
 *@return           : return WSS data
 ****************************************************************************/
MS_U16 MDrv_VBI_GetWSS_Data(void);

/****************************************************************************
 *@brief            : Get VPS Data
 *@param lowerWord  : [OUT] VPS lower data
 *@param higherWord : [OUT] VPS higher data
 *@return
 ****************************************************************************/
void MDrv_VBI_GetVPS_Data(MS_U8 *lowerWord, MS_U8 *higherWord);

/****************************************************************************
 *@brief            : Set Video Standard
 *@param eStandard  : [IN] type (NTSC/PAL/SECAM)
 *@see VBI_VIDEO_STANDARD
 *@return
 ****************************************************************************/
void MDrv_VBI_SetVideoStandard(VBI_VIDEO_STANDARD eStandard);

/****************************************************************************
 *@brief            : Check TTX circuit ready
 *@param
 *@return
 *  - TRUE : TTX circuit is ready.
 *  - FALSE: TTX circuit is not ready.
 ****************************************************************************/
MS_BOOL MDrv_VBI_TTX_CheckCircuitReady(void);

/****************************************************************************
 *@brief            : Get TTX Packet Count
 *@param
 *@return           : TTX packet count
 ****************************************************************************/
MS_U16 MDrv_VBI_TTX_GetPacketCount(void);

/****************************************************************************
 *@brief            : Check if the TTX packet in VBI buffer is empty
 *@param
 *@return
 *  - TRUE : is empty
 *  - FALSE: not empty
 ****************************************************************************/
MS_BOOL MDrv_VBI_TTX_PacketBufferIsEmpty(void);

// Get all of the packets in the VBI buffer (if the input buffer is big enough)
/****************************************************************************
 *@brief            : Get TTX Packets
 *@param dataAddr   : [IN] data address
 *@param length     : [OUT] packet length
 *@return
 *  - TRUE : get TTX packets successfully.
 *  - FALSE: get TTX packets unsuccessfully.
 ****************************************************************************/
MS_BOOL MDrv_VBI_TTX_GetPackets(MS_PHYADDR dataAddr, MS_U32 *length);

// Get 1 of the packets in the VBI buffer
/****************************************************************************
 *@brief                : Get TTX Packet
 *@param packetAddress  : [OUT] packet address
 *@return
 *  - TRUE : get TTX packet successfully.
 *  - FALSE: get TTX packet unsuccessfully.
 ****************************************************************************/
MS_BOOL MDrv_VBI_TTX_GetPacket(MS_PHYADDR *packetAddress);

/***********************************************************************
 * FUNCTION: MDrv_VBI_TTX_PacketBufferIsOverflow
 *
 * DESCRIPTION:
 *   Check if there is a packet buffer overflow. If there is an overflow,
 *   the the packet buffer should be cleared from the reading task.
 *
 * RETURN:
 *   TRUE if there is packet buffer overflow,
 *   NULL otherwise.
 ***********************************************************************/
MS_BOOL MDrv_VBI_TTX_PacketBufferIsOverflow( void );

/***********************************************************************
 * FUNCTION: MDrv_VBI_TTX_PacketBufferGetNoOfOverflows
 *
 * DESCRIPTION:
 *   Resuren the nomber of packet buffer overflows since the last reset
 *   or creation.
 *
 * RETURN:
 *   The number of packet buffer overflows.
 ***********************************************************************/
MS_U16 MDrv_VBI_TTX_PacketBufferGetNoOfOverflows( void );

/****************************************************************************
 *@brief            : Set TTX Enable Line
 *@param StartLine  : [IN] TTX start line
 *@param EndLine    : [IN] TTX end line
 *@return
 ****************************************************************************/
void MDrv_VBI_TTX_EnableLine(MS_U16 StartLine, MS_U16 EndLine);

/*
 *  ClosedCaption
 */
void MDrv_VBI_CC_InitSlicer(MS_U32 u32RiuAddr, MS_PHYADDR bufferAddr, MS_U16 packetCount);
void MDrv_VBI_CC_InitYPbYr(MS_U8 cvbs_no);
void MDrv_VBI_CC_EnableSlicer(MS_BOOL bEnable);
MS_U8 MDrv_VBI_CC_SetDataRate(MS_U8 *ptable);
void MDrv_VBI_CC_SetFrameCnt(MS_U8 cnt);
MS_U32 MDrv_VBI_CC_GetInfo(MS_U32 selector);
void MDrv_VBI_CC_EnableLine(MS_U16 StartLine, MS_U16 EndLine, MS_U8 mode);
MS_BOOL MDrv_VBI_SyncMemory( MS_U32 u32Start, MS_U32 u32Size );

/*
 *  Others
 */
void MDrv_VBI_WSS_SetVpsByteNum(MS_U8 cnt);

#ifdef __cplusplus
}
#endif

#endif

