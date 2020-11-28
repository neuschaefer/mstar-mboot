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
#ifndef _MSAPI_OAD_PARSER_C_
#define _MSAPI_OAD_PARSER_C_


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define HIGHBYTE(u16)               ((MS_U8)((u16) >> 8))
#define LOWBYTE(u16)                ((MS_U8)(u16))

/*------------------------------------------------------------------------------
*   include files
*-----------------------------------------------------------------------------*/
#include "msAPI_oad_parser.h"
#include "msAPI_oad_process.h"
#include <linux/string.h>
#include <asm/string.h>
#include <MsTypes.h>

extern MS_U8 g_OAD_OUI[3];
static  void    msAPI_OAD_RestartSectionFilter(MS_U8  u08OadFID);

/******************************************************************************/
// The following functions is used by AP code.
/******************************************************************************/
MS_U8 *msAPI_OAD_PollingSectionFilter(MS_U8  u08OadFID,MS_U8  *sectionBuffer)
{
    MS_U32 u32ActualSize,u32RmnSize;
    MS_U8 *pu8SecBuf = NULL;
    DMX_FILTER_STATUS procRet ;
    DMX_EVENT eEvent = 0 ;//DMX_EVENT_DATA_READY;

    if( u08OadFID == MSAPI_DMX_INVALID_FLT_ID ) return pu8SecBuf;
    OAD_DEBUG(printf("u08OadFID = %d \n",(MS_U8)u08OadFID)) ;  
   
    procRet = MApi_DMX_Proc(u08OadFID,&eEvent) ;


    OAD_DEBUG(printf("eEvent = %d \n",(MS_U8)eEvent)) ;

    OAD_DEBUG(printf("procRet = %d \n",(MS_U8)procRet));

    if (procRet==DMX_FILTER_STATUS_OK)
    {
        if (eEvent == DMX_EVENT_DATA_READY)
        {
            OAD_DEBUG(memset(sectionBuffer, 0xBB, MSAPI_DMX_SECTION_4K));
            OAD_DEBUG(printf("section Addr: 0x%08LX\n", (sectionBuffer)));

            //Patch for section data error.
            //MsOS_DelayTask(5);
            if( MApi_DMX_CopyData(u08OadFID, sectionBuffer, MSAPI_DMX_SECTION_4K,(MS_U32*)&u32ActualSize,(MS_U32*)&u32RmnSize,NULL) == DMX_FILTER_STATUS_OK )
            {
                if(msAPI_DMX_CheckCRC32(sectionBuffer)== FALSE)
                {
                    OAD_ASSERT(printf("crc error %s %d \n",__FUNCTION__,__LINE__));
                    //msAPI_OAD_RestartSectionFilter(u08OadFID); 
                    pu8SecBuf = NULL ;
                }
                else
                {
                    pu8SecBuf = sectionBuffer;
                }
            }
            else
            {
                if ( 0 != u32RmnSize)
                {
                    OAD_ASSERT( printf("Error> msAPI_OAD_PollingSectionFilter : MApi_DMX_CopyData Error.\n") );
                    msAPI_OAD_RestartSectionFilter(u08OadFID);
                }
            }
        }
        else
        {
            if (DMX_EVENT_BUF_OVERFLOW == eEvent)
            {
                OAD_ASSERT( printf("Polling OVERFLOW = %u\n", (MS_U8)u08OadFID); );
                msAPI_OAD_RestartSectionFilter(u08OadFID);
            }
        }
    }
    return pu8SecBuf;
}

MS_BOOL msAPI_OAD_CreateSectionFilter( MS_U32 u32Type,MS_U8 u08TableId,MS_U16 u16MsgId, MS_U16 u16Pid,MS_U8  *u08OadFID)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;

    memset(stSectionMonitor.au8MaskByte,     0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

    stSectionMonitor.u32SectionFltType   = u32Type;
    stSectionMonitor.au8MatchByte[0]    = u08TableId;              // table id
    stSectionMonitor.au8MaskByte[0]     = 0xFF;
    if (u08TableId!=OAD_UNT_SECTION_TYPE)
    {
       stSectionMonitor.au8MatchByte[8] = 0x11;//protocolDiscriminator
       stSectionMonitor.au8MaskByte[8] = 0xFF;
       stSectionMonitor.au8MatchByte[9] = 0x03;//dsmccType
       stSectionMonitor.au8MaskByte[9] = 0xFF;
       stSectionMonitor.au8MatchByte[10] = HIGHBYTE(u16MsgId);//HIGHBYTE(OAD_DSMCC_MSGID_DDB);//messageId[1]
       stSectionMonitor.au8MatchByte[11] = LOWBYTE(u16MsgId) ;//LOWBYTE(OAD_DSMCC_MSGID_DDB); //messageId[0]
       stSectionMonitor.au8MaskByte[10] = 0xFF;
       stSectionMonitor.au8MaskByte[11] = 0xFF;
       stSectionMonitor.pfNotify           = NULL;
       stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
       stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;
    }
    else
    {
       stSectionMonitor.au8MatchByte[8] = (GET_3BYTE(g_OAD_OUI)&0xff0000)>>16 ;
       stSectionMonitor.au8MaskByte[8] = 0xFF;
       stSectionMonitor.au8MatchByte[9] = (GET_3BYTE(g_OAD_OUI)&0x00ff00)>>8 ;
       stSectionMonitor.au8MaskByte[9] = 0xFF;
       stSectionMonitor.au8MatchByte[10] = (GET_3BYTE(g_OAD_OUI)&0x0000ff) ;
       stSectionMonitor.au8MaskByte[10] = 0xFF;
       stSectionMonitor.pfNotify           = NULL;
       stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
       stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;
    }
    stSectionMonitor.u16PID             = u16Pid;
    stSectionMonitor.pu8FID             = u08OadFID;

    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
    {
        return TRUE ;
    }
    else
    {
        return FALSE ;
    }

}

void msAPI_OAD_DeleteSectionFilter(MS_U8  *u08OadFID)
{
    if( *u08OadFID == MSAPI_DMX_INVALID_FLT_ID ) return;

    msAPI_DMX_Stop(*u08OadFID);
    msAPI_DMX_Close(*u08OadFID);

    *u08OadFID = MSAPI_DMX_INVALID_FLT_ID;
}

static void msAPI_OAD_RestartSectionFilter(MS_U8  u08OadFID)
{
    if( u08OadFID == MSAPI_DMX_INVALID_FLT_ID ) return;

    msAPI_DMX_Stop(u08OadFID);
    msAPI_DMX_Reset(u08OadFID);
    msAPI_DMX_Start(u08OadFID);
}

#undef _MSAPI_OAD_PARSER_C_
#endif //_MSAPI_OAD_PARSER_C_

