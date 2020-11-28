////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MSAPI_OAD_PARSER_H_
#define _MSAPI_OAD_PARSER_H_

/*------------------------------------------------------------------------------
*   include files
*-----------------------------------------------------------------------------*/
#include "msAPI_demux.h"

/*------------------------------------------------------------------------------
*   Function prototypes.
*-----------------------------------------------------------------------------*/
MS_U8 *msAPI_OAD_PollingSectionFilter(MS_U8  u08OadFID,MS_U8  *sectionBuffer);
MS_BOOL msAPI_OAD_CreateSectionFilter( MS_U32 u32Type,MS_U8 u08TableId,MS_U16 u16MsgId,MS_U16 u16Pid,MS_U8  *u08OadFID);
void msAPI_OAD_DeleteSectionFilter(MS_U8  *u08OadFID);

#endif // _MSAPI_OAD_PARSER_H_
