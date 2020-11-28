////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_MEMORY_H
#define MSAPI_MEMORY_H

#include <MsTypes.h>

/******************************************************************************/
/* Enum                                                                       */
/******************************************************************************/
// Please add your buffer ID when you need to allocate a buffer from buffer pool
/// buffer ID
typedef enum
{
    BUF_ID_ITC,                     ///< Buffer ID ITC
    BUF_ID_EVENT_INFO,              ///< Buffer ID Event Info
    BUF_ID_DESCRIPTOR,              ///< Buffer ID Descriptor
    BUF_ID_VCH,                     ///< Buffer ID VCH
    BUF_ID_PAT,                     ///< Buffer ID PAT
    BUF_ID_DTV_PG_INDEX,            ///< Buffer ID DTV PG Index
    BUF_ID_FLASH,                   ///< Buffer ID Flash
    BUF_ID_GLYPH_DISP_INFO,         ///< Buffer ID Glyph Display Info
    BUF_ID_DRAW_TEXT,               ///< Buffer ID Draw Text
    BUF_ID_SUBTITLE_SEC,            ///< Buffer ID Subtitle section buffer
    BUF_ID_MEM_REALLOC,             ///< Buffer ID Memory reallocate
    BUF_ID_AEON_MMAP,               ///< Buffer ID Aeon MMAP
    BUF_ID_FILEBROWER,              ///< Buffer ID Filebrowser
    BUF_ID_FILECNTL,                ///< Buffer ID File control
    BUF_ID_USB_DOWNLOAD,            ///< Buffer ID USB download
    BUF_ID_ZUI,                     ///< Buffer ID ZUI service
    BUF_ID_OAD_DOWNLOAD,            ///< Buffer ID OAD download
    BUF_ID_USB_HOST,                ///< Buffer ID USB Host
    BUF_ID_CC,                      ///< Buffer ID Closed-caption
    BUF_ID_ATSC,                    ///< Buffer ID ATSC
    BUF_ID_NIT_SCAN,                    ///< Buffer ID Netwok scan
    BUF_ID_NEW_MULTIPLEX,                   ///< Buffer ID new multiplex
    BUF_ID_MSB1210_DOWNLOAD,           ///< Buffer ID msb1210 download
} EN_BUFFER_ID;


/******************************************************************************/
/* Macro                                                                      */
/******************************************************************************/
#ifdef MSAPI_MEMORY_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/******************************************************************************/
// Function prototypes                                                        */
/******************************************************************************/
INTERFACE void msAPI_Memory_Init(void);
INTERFACE void *msAPI_Memory_Allocate(MS_U16 u16Number_of_bytes, EN_BUFFER_ID enBufID);
INTERFACE MS_U8 msAPI_Memory_Free(void *pFree, EN_BUFFER_ID enBufID);
INTERFACE void *msAPI_Memory_ReAllocate(void *pAlloc, MS_U16 newsize, EN_BUFFER_ID enBufID);

//INTERFACE void msAPI_Aeon_Disable(void);
//INTERFACE void msAPI_Aeon_ReInitial(U16 u16AeonBinID);

#define MSAPI_MEMORY_FREE(ptr,id)   \
{                                   \
    msAPI_Memory_Free(ptr, id);     \
    ptr = NULL;                     \
}
#undef INTERFACE

#endif

