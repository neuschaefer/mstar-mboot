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
#ifndef _DRV_DMX_TTX_H
#define _DRV_DMX_TTX_H

#ifdef __cplusplus
extern "C"
{
#endif

#define VBI_TTX_DATA_LENGTH 48

typedef MS_U32(*DMX_CB_FN)(MS_U8 SecFltNo);

void MDrv_DMX_TTX_RingBuffer_Reset(void);
MS_BOOL MDrv_DMX_TTX_Init(MS_PHYADDR bufferAddr, MS_U16 packetCount);
void MDrv_DMX_TTX_SetCB(DMX_CB_FN fn);
void MDrv_DMX_TTX_SetFilterID(MS_U8 fid);
MS_BOOL MDrv_DMX_TTX_PacketBufferIsEmpty(void);
MS_BOOL MDrv_DMX_TTX_GetPackets(MS_PHYADDR dataAddr, MS_U32 *length);
MS_BOOL MDrv_DMX_TTX_GetPacket(MS_PHYADDR *packetAddress);

/***********************************************************************
 * FUNCTION: MDrv_DMX_TTX_PacketBufferIsOverflow
 *
 * DESCRIPTION:
 *   Check if there is a packet buffer overflow. If there is an overflow, 
 *   the the packet buffer should be cleared from the reading task.
 *
 * RETURN:
 *   TRUE if there is packet buffer overflow,
 *   NULL otherwise.
 ***********************************************************************/
MS_BOOL MDrv_DMX_TTX_PacketBufferIsOverflow( void );

/***********************************************************************
 * FUNCTION: MDrv_DMX_TTX_PacketBufferGetNoOfOverflows
 *
 * DESCRIPTION:
 *   Resuren the nomber of packet buffer overflows since the last reset
 *   or creation.
 *
 * RETURN:
 *   The number of packet buffer overflows.
 ***********************************************************************/
MS_U16 MDrv_DMX_TTX_PacketBufferGetNoOfOverflows( void );

#undef INTERFACE

#ifdef __cplusplus
}
#endif

#endif

