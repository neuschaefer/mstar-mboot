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
#define  MSAPI_DEMUX_C

////////////////////////////////////////////////////////////////////////////////
///
/// @file msAPI_demux.c
/// @author MStar Semiconductor Inc.
/// @brief Demux API wrapper
///
////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <common.h>
#include <linux/string.h>
#include <asm/string.h>
#include <MsTypes.h>
#include <MsOS.h>

// API Layer
#include "msAPI_demux.h"
// MW Layer


/******************************************************************************/
/*                                   Define                                   */
/******************************************************************************/
extern MS_U32 u32OadbufMonitorAddr;
extern MS_U32 u32OadbufMonitorSize;
extern MS_U32 u32OadbufDownloadAddr;
extern MS_U32 u32OadbufDownloadSize;


/******************************************************************************/
/*                                   Macro                                    */
/******************************************************************************/
#if (ENABLE_NEW_DMX_INTERFACE)
#define DMX_DB(y)   //y
#endif


#if(CSA_ENABLE == 1)
#include "msAPI_MailBox.h"
typedef enum
{
    MB_CSA_FILTER_START,
    MB_CSA_FILTER_STOP,
    MB_CSA_FILTER_SET_EVEN_KEY,
    MB_CSA_FILTER_SET_ODD_KEY,
    MB_CSA_SEC_READ_ADDRESS,
    MB_CSA_SEC_WRITE_ADDRESS,
    MB_CSA_FILTER_STOP_FINISH,
    MB_CSA_FILTER_SUCCESS,
} MB_CSA_CLASS;
MS_U8 even_key[8] = {0x92, 0xFB, 0x05, 0x92, 0xEA, 0x32, 0xE7, 0x03};
MS_U8 odd_key[8] = {0x92, 0xFB, 0x05, 0x92, 0xEA, 0x32, 0xE7, 0x03};
#define E_MBX_CLASS_CSA E_MBX_CLASS_LZSS
#define CSA_MSA_QUEUE_SIZE 10
static MS_BOOL _bCSA_Filter_ON=FALSE;
static MS_BOOL _bCSA_ON=FALSE;
static MS_U8 _u8FilterGroup=0;
static MS_U32 _u32SecWriteAddress,_u32SecReadAddress,_u32SecStartAddress,_u32SecEndAddress;
static void _HandleCSAMSG(MBX_Msg *pMsg, MS_BOOL *pbAddToQueue);
#endif
/******************************************************************************/
/*                                   Enum                                     */
/******************************************************************************/


/******************************************************************************/
/*                                 Global Var                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 Local Var                                  */
/******************************************************************************/


/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/


//------------------------------------------------------------------------------
/// Demux EIT parsing function for parsing EIT P/F table of current service channel
/// @param  pu8Section \b IN received section data
/// @return None
//------------------------------------------------------------------------------

#if (ENABLE_NEW_DMX_INTERFACE)

extern MS_U32 u32Sec1KFilterBufferSize;
extern MS_U32 u32Sec4KFilterBufferSize;
typedef struct MApp_Dmx_Ts_Filter
{
    MS_U8 u8FltID;
    MS_U8 bUsed;
    MS_U16 u16TimeoutMilliSec;
    MS_U32 u32TimerEnd;
    void (*pfNotify)(MS_U8 u8FID, DMX_EVENT enEvent);
    MS_U32 u32SectionFltType;
} _MApp_Dmx_Ts_Filter;
static _MApp_Dmx_Ts_Filter _DmxTsFilter[MSAPI_DMX_MAX_FILTER_NUMBER];

static DMX_FILTER_STATUS _MApp_Dmx_HaveFreeFilter(void)
{
    MS_U8 i,u8UsedFilter=0;;
    for (i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        if (_DmxTsFilter[i].bUsed)
        {
            u8UsedFilter++;
        }
    }
    if(u8UsedFilter >= MSAPI_DMX_USABLE_FILTER_NUMBER)
    {
        //printf("no free filter max %d\n",MSAPI_DMX_USABLE_FILTER_NUMBER);
        return DMX_FILTER_STATUS_ERROR;
    }
    return DMX_FILTER_STATUS_OK;
}

DMX_FILTER_STATUS msAPI_DMX_Close(MS_U8 u8FltID)
{
    MS_U8 i;
    for (i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        if (_DmxTsFilter[i].bUsed && _DmxTsFilter[i].u8FltID == u8FltID)
        {
            _DmxTsFilter[i].bUsed=FALSE;
            _DmxTsFilter[i].pfNotify=NULL;
#if(CSA_ENABLE == 1)
            if(u8FltID == CSA_FILTER_ID)
            {
                MBX_Result mbxResult;
                MBX_Msg mbxMsg;
                MBX_MSGQ_Status MsgQueueStatus;
                MS_U32 u32CurrentMsgNumber = 0;
                MS_U8 wait=0;
                mbxMsg.eMsgType=E_MBX_MSG_TYPE_NORMAL;
                mbxMsg.u8MsgClass=E_MBX_CLASS_CSA;
                mbxMsg.u8Index=MB_CSA_FILTER_STOP;
                mbxMsg.u8ParameterCount=0;
                mbxResult = MApi_MBX_SendMsg(&mbxMsg);
                if(mbxResult != E_MBX_SUCCESS)
                {
                    printf("%s...%d error\n",__FUNCTION__,__LINE__);
                }
                while(wait++ < 100)
                {
                    msAPI_Timer_Delayms(1);
                    mbxResult = MApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_CSA, &MsgQueueStatus);
                    if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_INSTANT_MSG)
                        u32CurrentMsgNumber = MsgQueueStatus.u32InstantMsgCount;
                    else if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_NORMAL_MSG)
                        u32CurrentMsgNumber = MsgQueueStatus.u32NormalMsgCount;
                    if(u32CurrentMsgNumber>0)
                    {
                        if(MApi_MBX_RecvMsg(E_MBX_CLASS_CSA, &mbxMsg, 0, MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
                        {
                            if(((MS_U8)mbxMsg.u8Index) == MB_CSA_FILTER_STOP_FINISH)
                            {
                                printf("close CSA success--\n");
                                break;
                            }
                        }
                    }
                }
                if(wait>=100)printf("%s ..%d close CSA filter failed\n",__FUNCTION__,__LINE__);
                MApi_MBX_UnRegisterMSG(E_MBX_CLASS_CSA);
                _bCSA_Filter_ON=FALSE;
                return DMX_FILTER_STATUS_OK;
            }
#endif
            MApi_DMX_Close(u8FltID);
            //printf("msAPI_DMX_Close %d\n",u8FltID);
            return DMX_FILTER_STATUS_OK;
        }
    }
    return DMX_FILTER_STATUS_ERROR;
}


DMX_FILTER_STATUS msAPI_DMX_Stop(MS_U8 u8FltID)
{
    MS_U8 i;

#if(CSA_ENABLE == 1)
    if(u8FltID == CSA_FILTER_ID)
    {
        return DMX_FILTER_STATUS_OK;
    }
#endif
    for (i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        if (_DmxTsFilter[i].bUsed && _DmxTsFilter[i].u8FltID == u8FltID)
        {
            MApi_DMX_Stop(u8FltID);
            //printf("MApi_DMX_Stop %d\n",u8FltID);
            #if ENABLE_CI && ENABLE_CI_PLUS
            msAPI_CI_CC_SetFID(u8FltID, FALSE);
            #endif

            return DMX_FILTER_STATUS_OK;
        }
    }
    return DMX_FILTER_STATUS_ERROR;
}

DMX_FILTER_STATUS msAPI_DMX_Reset(MS_U8 u8FltID)
{
    MS_U8 i;
    for (i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        if (_DmxTsFilter[i].bUsed && _DmxTsFilter[i].u8FltID == u8FltID)
        {
            MApi_DMX_SectReset(u8FltID);
            return DMX_FILTER_STATUS_OK;
        }
    }
    return DMX_FILTER_STATUS_ERROR;
}
DMX_FILTER_STATUS msAPI_DMX_Start(MS_U8 u8FltID)
{
    MS_U8 i;
    for (i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        if (_DmxTsFilter[i].bUsed && _DmxTsFilter[i].u8FltID == u8FltID)
        {
            MApi_DMX_Start(u8FltID);
            if(_DmxTsFilter[i].u16TimeoutMilliSec != MSAPI_DMX_TIMEOUT_INFINITE)
            {
                _DmxTsFilter[i].u32TimerEnd=MsOS_GetSystemTime()+_DmxTsFilter[i].u16TimeoutMilliSec;
                //printf("msAPI_DMX_Start fid %d %d %d\n",u8FltID,MsOS_GetSystemTime(),_DmxTsFilter[i].u32TimerEnd);
            }
            //printf("msAPI_DMX_Start fid %d %d %d\n",u8FltID,MsOS_GetSystemTime(),_DmxTsFilter[i].u32TimerEnd);
            return DMX_FILTER_STATUS_OK;
        }
    }
    return DMX_FILTER_STATUS_ERROR;
}
DMX_FILTER_STATUS msAPI_DMX_Pid(MS_U8 u8FltID, MS_U16* pu16Pid, MS_BOOL bSet)
{
    MS_U8 i;
    for (i = 0; i < MSAPI_DMX_MAX_FILTER_NUMBER; i++)
    {
        if (_DmxTsFilter[i].bUsed && _DmxTsFilter[i].u8FltID == u8FltID)
        {
            MApi_DMX_Pid(u8FltID,pu16Pid,bSet);
            //printf("msAPI_DMX_Pid fid %d %d\n",u8FltID,*pu16Pid);
            return DMX_FILTER_STATUS_OK;
        }
    }
    return DMX_FILTER_STATUS_ERROR;
}
DMX_FILTER_STATUS msAPI_DMX_Proc(MS_U8 u8DmxId)
{
    MS_U8 i,u8Index;
    DMX_FILTER_STATUS eResult=DMX_FILTER_STATUS_ERROR;
    DMX_EVENT eEvent = DMX_EVENT_DATA_READY;
    static MS_U8 u8StartFltIndex = 0;
    if(MSAPI_DMX_INVALID_FLT_ID != u8DmxId)
    {
        eResult=MApi_DMX_Proc(u8DmxId, &eEvent);
    }
    else
    {
        for(i=u8StartFltIndex;i<MSAPI_DMX_MAX_FILTER_NUMBER+u8StartFltIndex;i++)
        {
            if (i < MSAPI_DMX_MAX_FILTER_NUMBER)
            {
                u8Index = i;
            }
            else
            {
                u8Index = i - MSAPI_DMX_MAX_FILTER_NUMBER;
            }
            if(_DmxTsFilter[u8Index].bUsed &&_DmxTsFilter[u8Index].pfNotify &&
               _DmxTsFilter[u8Index].u32SectionFltType!= MSAPI_DMX_FILTER_TYPE_OAD_MONITOR &&
               _DmxTsFilter[u8Index].u32SectionFltType!= MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD )
            {
                u8DmxId = _DmxTsFilter[u8Index].u8FltID;
#if(CSA_ENABLE == 1)
                if(u8DmxId == CSA_FILTER_ID)
                {
                    if(_u32SecWriteAddress != _u32SecReadAddress)
                    {
                        //printf("read %x write %x\n",_u32SecReadAddress,_u32SecWriteAddress);
                        eResult=DMX_FILTER_STATUS_OK;
                        eEvent=DMX_EVENT_DATA_READY;
                    }
                }
                else
#endif
                {
                    eResult=MApi_DMX_Proc(u8DmxId, &eEvent);
                }
                //printf("msAPI_DMX_Pid %d (%d) result %d\n",u8Index,u8DmxId,eResult);
                if(eResult == DMX_FILTER_STATUS_OK)
                {
                    u8StartFltIndex=u8Index+1;
                    break;
                }
            }
        }
    }
    if(eResult == DMX_FILTER_STATUS_OK)
    {
        for(i=0;i<MSAPI_DMX_MAX_FILTER_NUMBER;i++)
        {
            if(_DmxTsFilter[i].bUsed && (_DmxTsFilter[i].u8FltID == u8DmxId))
            {
                if(_DmxTsFilter[i].u16TimeoutMilliSec != MSAPI_DMX_TIMEOUT_INFINITE)
                {
                    _DmxTsFilter[i].u32TimerEnd=MsOS_GetSystemTime()+_DmxTsFilter[i].u16TimeoutMilliSec;
                }
                if(_DmxTsFilter[i].pfNotify)
                {
                    _DmxTsFilter[i].pfNotify(_DmxTsFilter[i].u8FltID, eEvent);
                }
                break;
            }
        }
    }
    if(eResult != DMX_FILTER_STATUS_OK)
    {
        for(i=0;i<(MSAPI_DMX_SEC1K_FILTER_NUMBER+MSAPI_DMX_SEC4K_FILTER_NUMBER);i++)
        {
            if(_DmxTsFilter[i].bUsed && (_DmxTsFilter[i].u16TimeoutMilliSec != MSAPI_DMX_TIMEOUT_INFINITE))
            {
                if ((MsOS_GetSystemTime() > _DmxTsFilter[i].u32TimerEnd) &&
                    ((MsOS_GetSystemTime()- _DmxTsFilter[i].u32TimerEnd) < 0xF0000000))
                {
                    //U16 u16Pid;
                    //MApi_DMX_Pid(_DmxTsFilter[i].u8FltID,&u16Pid,FALSE);
                    //printf("time out fid %d pid %d %d\n",_DmxTsFilter[i].u8FltID,u16Pid,_DmxTsFilter[i].u32TimerEnd);
                    if(_DmxTsFilter[i].pfNotify)
                    {
                        _DmxTsFilter[i].pfNotify(_DmxTsFilter[i].u8FltID,(DMX_EVENT)MSAPI_DMX_FILTER_STATUS_TIMEOUT);
                    }
                    break;
                }
            }
        }
    }
    return eResult;
}

DMX_FILTER_STATUS msAPI_DMX_Open(MS_DMX_SECTIONMONITOR_PARA * pstSectionMonitor, MS_U32 *u32StartAddress, MS_U32 *u32Size)
{
    DMX_FILTER_TYPE FilterType=DMX_FILTER_TYPE_SECTION;
    MS_U32 u32BufferSize=MSAPI_DMX_SECTION_1K;
    MS_U8 i;
    DMX_FILTER_TYPE eFilterType=DMX_FILTER_SOURCE_TYPE_LIVE;
#ifdef DISABLE_DMX
    return DMX_FILTER_STATUS_ERROR;
#endif
    if (pstSectionMonitor->pu8FID == NULL)
    {
        return DMX_FILTER_STATUS_ERROR;
    }

    if (pstSectionMonitor->pfNotify == NULL)
    {
        //return MAPI_DMX_FILTER_STATUS_ERROR;
    }
    if((pstSectionMonitor->u32SectionFltType & MSAPI_DMX_FILTER_SOURCE_TYPE_MASK) == MSAPI_DMX_FILTER_SOURCE_TYPE_FILE)
    {
        eFilterType=DMX_FILTER_SOURCE_TYPE_FILE;
    }
    pstSectionMonitor->u32SectionFltType=(pstSectionMonitor->u32SectionFltType&~MSAPI_DMX_FILTER_SOURCE_TYPE_MASK);
#if 0//(CSA_ENABLE == 1)
    if( pstSectionMonitor->u32SectionFltType ==  MSAPI_DMX_FILTER_TYPE_CSA_PACKET)
    {
        MBX_Result mbxResult;
        MBX_Msg mbxMsg;
        MS_U8 wait=0;
        MBX_MSGQ_Status MsgQueueStatus;
        MS_U32 u32CurrentMsgNumber = 0;
        if(_bCSA_Filter_ON)
        {
            //printf("error %s...%d \n",__FUNCTION__,__LINE__);
            return DMX_FILTER_STATUS_ERROR;
        }
        *(pstSectionMonitor->pu8FID) = MSAPI_DMX_INVALID_FLT_ID;
        for(i=MSAPI_DMX_SEC1K_FILTER_NUMBER;i<(MSAPI_DMX_SEC1K_FILTER_NUMBER+MSAPI_DMX_SEC4K_FILTER_NUMBER);i++)
        {
            if(_DmxTsFilter[i].bUsed == FALSE)
            {
                _DmxTsFilter[i].bUsed=TRUE;
                _DmxTsFilter[i].u16TimeoutMilliSec=pstSectionMonitor->u16TimeoutMilliSec;
                _DmxTsFilter[i].pfNotify=pstSectionMonitor->pfNotify;
                _DmxTsFilter[i].u8FltID=CSA_FILTER_ID;
                _DmxTsFilter[i].u32SectionFltType = pstSectionMonitor->u32SectionFltType ;
                if(pstSectionMonitor->u16TimeoutMilliSec != MSAPI_DMX_TIMEOUT_INFINITE)
                {
                    _DmxTsFilter[i].u32TimerEnd=MsOS_GetSystemTime()+pstSectionMonitor->u16TimeoutMilliSec;
                }
                *u32StartAddress=((SECBUF_START_MEMORY_TYPE & MIU1) ? (SECBUF_START_ADR | MIU_INTERVAL) : (SECBUF_START_ADR))+MSAPI_DMX_SEC1K_FILTER_NUMBER*u32Sec1KFilterBufferSize+((i-MSAPI_DMX_SEC1K_FILTER_NUMBER)*u32Sec4KFilterBufferSize);
                *u32Size=u32Sec4KFilterBufferSize;
                break;
            }
        }
        if(i>=(MSAPI_DMX_SEC1K_FILTER_NUMBER+MSAPI_DMX_SEC4K_FILTER_NUMBER))
        {
            printf("!!!!!!no free filter for CSA\n");
            return DMX_FILTER_STATUS_ERROR;
        }
        mbxResult = MApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_CSA, CSA_MSA_QUEUE_SIZE, _HandleCSAMSG);
        if(E_MBX_SUCCESS != mbxResult)
        {
			_DmxTsFilter[i].bUsed=FALSE;
            printf("!!!!!!MBX register msg error\n");
            return DMX_FILTER_STATUS_ERROR;
        }

        mbxMsg.eMsgType=E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8MsgClass=E_MBX_CLASS_CSA;
        mbxMsg.u8Index=MB_CSA_FILTER_SET_EVEN_KEY;
        mbxMsg.u8ParameterCount=8;
        mbxMsg.u8Parameters[0]=even_key[0];
        mbxMsg.u8Parameters[1]=even_key[1];
        mbxMsg.u8Parameters[2]=even_key[2];
        mbxMsg.u8Parameters[3]=even_key[3];
        mbxMsg.u8Parameters[4]=even_key[4];
        mbxMsg.u8Parameters[5]=even_key[5];
        mbxMsg.u8Parameters[6]=even_key[6];
        mbxMsg.u8Parameters[7]=even_key[7];

	    mbxResult = MApi_MBX_SendMsg(&mbxMsg);

        mbxMsg.eMsgType=E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8MsgClass=E_MBX_CLASS_CSA;
        mbxMsg.u8Index=MB_CSA_FILTER_SET_ODD_KEY;
        mbxMsg.u8ParameterCount=8;
        mbxMsg.u8Parameters[0]=odd_key[0];
        mbxMsg.u8Parameters[1]=odd_key[1];
        mbxMsg.u8Parameters[2]=odd_key[2];
        mbxMsg.u8Parameters[3]=odd_key[3];
        mbxMsg.u8Parameters[4]=odd_key[4];
        mbxMsg.u8Parameters[5]=odd_key[5];
        mbxMsg.u8Parameters[6]=odd_key[6];
        mbxMsg.u8Parameters[7]=odd_key[7];

	    mbxResult = MApi_MBX_SendMsg(&mbxMsg);


        mbxMsg.eMsgType=E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8MsgClass=E_MBX_CLASS_CSA;
        mbxMsg.u8Index=MB_CSA_FILTER_START;
        mbxMsg.u8ParameterCount=9;
        mbxMsg.u8Parameters[0]=((pstSectionMonitor->u16PID)>>8)&0xFF;
        mbxMsg.u8Parameters[1]=(pstSectionMonitor->u16PID)&0xFF;
        mbxMsg.u8Parameters[2]=(*u32StartAddress)>>24;
        mbxMsg.u8Parameters[3]=(*u32StartAddress>>16)&0xFF;
        mbxMsg.u8Parameters[4]=(*u32StartAddress>>8)&0xFF;
        mbxMsg.u8Parameters[5]=(*u32StartAddress)&0xFF;
        mbxMsg.u8Parameters[6]=(*u32Size>>8)&0xFF;
        mbxMsg.u8Parameters[7]=(*u32Size)&0xFF;
        mbxMsg.u8Parameters[8]=_u8FilterGroup;

	    mbxResult = MApi_MBX_SendMsg(&mbxMsg);

        if(E_MBX_SUCCESS != mbxResult)
        {
            _DmxTsFilter[i].bUsed=FALSE;
            printf("!!!!!!MBX send msg error\n");
            return DMX_FILTER_STATUS_ERROR;
        }

        while(wait++ < 100)
        {
            msAPI_Timer_Delayms(1);
            mbxResult = MApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_CSA, &MsgQueueStatus);
            if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_INSTANT_MSG)
                u32CurrentMsgNumber = MsgQueueStatus.u32InstantMsgCount;
            else if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_NORMAL_MSG)
                u32CurrentMsgNumber = MsgQueueStatus.u32NormalMsgCount;
            if(u32CurrentMsgNumber>0)
            {
                if(MApi_MBX_RecvMsg(E_MBX_CLASS_CSA, &mbxMsg, 0, MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
                {
                    if(((MS_U8)mbxMsg.u8Index) == MB_CSA_FILTER_SUCCESS)
                    {
                        printf("open CSA success--\n");
                        break;
                    }
                }
            }
        }
        if(wait>=100)
        {
            _DmxTsFilter[i].bUsed=FALSE;
            printf("!!!!!!open CSA filter error\n");
            return DMX_FILTER_STATUS_ERROR;
        }
        _u32SecStartAddress=_u32SecWriteAddress=_u32SecReadAddress=*u32StartAddress;
        _u32SecEndAddress=_u32SecStartAddress+*u32Size;

        *(pstSectionMonitor->pu8FID)=CSA_FILTER_ID;
        _bCSA_Filter_ON=TRUE;
        return DMX_FILTER_STATUS_OK;
    }
#endif
    if ((pstSectionMonitor->u32SectionFltType != MSAPI_DMX_FILTER_TYPE_SECTION_1K     ) &&
        (pstSectionMonitor->u32SectionFltType != MSAPI_DMX_FILTER_TYPE_SECTION_4K            ) &&
        (pstSectionMonitor->u32SectionFltType != MSAPI_DMX_FILTER_TYPE_OAD_MONITOR) &&
        (pstSectionMonitor->u32SectionFltType != MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD) &&
        (pstSectionMonitor->u32SectionFltType != MSAPI_DMX_FILTER_TYPE_SUBTITLE       ))
    {
        return DMX_FILTER_STATUS_ERROR;
    }
    if(pstSectionMonitor->u32SectionFltType == MSAPI_DMX_FILTER_TYPE_SUBTITLE)
    {
        FilterType = DMX_FILTER_TYPE_PES;
    }
    /*[02]OPEN a filter ===============================================================*/
    if(DMX_FILTER_STATUS_OK != _MApp_Dmx_HaveFreeFilter())
    {
        return DMX_FILTER_STATUS_ERROR;
    }
    if(DMX_FILTER_STATUS_ERROR == MApi_DMX_Open(FilterType | eFilterType, pstSectionMonitor->pu8FID) )
    {
        *(pstSectionMonitor->pu8FID) = MSAPI_DMX_INVALID_FLT_ID;
        return DMX_FILTER_STATUS_ERROR;
    }
    //printf("MApi_DMX_Open %d\n",*(pstSectionMonitor->pu8FID));
    if(pstSectionMonitor->u32SectionFltType == MSAPI_DMX_FILTER_TYPE_SECTION_4K)
    {
        u32BufferSize=MSAPI_DMX_SECTION_4K;
    }
    //printf("MApi_DMX_Open %d\n",*(pstSectionMonitor->pu8FID));
    if(pstSectionMonitor->u32SectionFltType == MSAPI_DMX_FILTER_TYPE_OAD_MONITOR)
    {
        for(i=(MSAPI_DMX_SEC1K_FILTER_NUMBER+MSAPI_DMX_SEC4K_FILTER_NUMBER);i<MSAPI_DMX_MAX_FILTER_NUMBER;i++)
        {
            if(_DmxTsFilter[i].bUsed == FALSE)
            {
                _DmxTsFilter[i].bUsed=TRUE;
                _DmxTsFilter[i].u16TimeoutMilliSec=pstSectionMonitor->u16TimeoutMilliSec;
                _DmxTsFilter[i].pfNotify=pstSectionMonitor->pfNotify;
                _DmxTsFilter[i].u8FltID=*(pstSectionMonitor->pu8FID);
                _DmxTsFilter[i].u32SectionFltType = pstSectionMonitor->u32SectionFltType ;
                if(pstSectionMonitor->u16TimeoutMilliSec != MSAPI_DMX_TIMEOUT_INFINITE)
                {
                    _DmxTsFilter[i].u32TimerEnd=MsOS_GetSystemTime()+pstSectionMonitor->u16TimeoutMilliSec;
                }
                *u32StartAddress=u32OadbufMonitorAddr;
                *u32Size=u32OadbufMonitorSize;

                return DMX_FILTER_STATUS_OK;
            }
        }
    }
    if(pstSectionMonitor->u32SectionFltType == MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD)
    {
        for(i=(MSAPI_DMX_SEC1K_FILTER_NUMBER+MSAPI_DMX_SEC4K_FILTER_NUMBER);i<MSAPI_DMX_MAX_FILTER_NUMBER;i++)
        {
            if(_DmxTsFilter[i].bUsed == FALSE)
            {
                _DmxTsFilter[i].bUsed=TRUE;
                _DmxTsFilter[i].u16TimeoutMilliSec=pstSectionMonitor->u16TimeoutMilliSec;
                _DmxTsFilter[i].pfNotify=pstSectionMonitor->pfNotify;
                _DmxTsFilter[i].u8FltID=*(pstSectionMonitor->pu8FID);
                _DmxTsFilter[i].u32SectionFltType = pstSectionMonitor->u32SectionFltType ;
                if(pstSectionMonitor->u16TimeoutMilliSec != MSAPI_DMX_TIMEOUT_INFINITE)
                {
                    _DmxTsFilter[i].u32TimerEnd=MsOS_GetSystemTime()+pstSectionMonitor->u16TimeoutMilliSec;
                }
                *u32StartAddress=u32OadbufDownloadAddr;
                *u32Size=u32OadbufDownloadSize;

                return DMX_FILTER_STATUS_OK;
            }
        }
    }
    else
    {
    }
    MApi_DMX_Close(*(pstSectionMonitor->pu8FID));
    *(pstSectionMonitor->pu8FID) = MSAPI_DMX_INVALID_FLT_ID;
    return DMX_FILTER_STATUS_ERROR;
}


DMX_FILTER_STATUS msAPI_DMX_SectionMonitor(MS_DMX_SECTIONMONITOR_PARA * pstSectionMonitor, MS_BOOL bFileIn)
{
    DMX_Flt_info FltInfo;
    DMX_FILTER_TYPE FilterType=DMX_FILTER_TYPE_SECTION;
#if(CSA_ENABLE == 1)
    MS_U32 u32FilterType=pstSectionMonitor->u32SectionFltType;
#endif
    if(bFileIn)
    {
        pstSectionMonitor->u32SectionFltType|=MSAPI_DMX_FILTER_SOURCE_TYPE_FILE;
    }
    if(DMX_FILTER_STATUS_ERROR == msAPI_DMX_Open(pstSectionMonitor,(MS_U32 *)&FltInfo.Info.SectInfo.SectBufAddr,(MS_U32 *)&FltInfo.Info.SectInfo.SectBufSize))
    {
        return DMX_FILTER_STATUS_ERROR;
    }
#if(CSA_ENABLE == 1)
    if(MSAPI_DMX_FILTER_TYPE_CSA_PACKET == u32FilterType)
    {
        if(*(pstSectionMonitor->pu8FID) == CSA_FILTER_ID)
        {
            return DMX_FILTER_STATUS_OK;
        }
        return DMX_FILTER_STATUS_ERROR;
    }
#endif
#if 0
    printf("msAPI_DMX_Open fid %d pid %d buff start %x size %x\n",*(pstSectionMonitor->pu8FID),pstSectionMonitor->u16PID,
    FltInfo.Info.SectInfo.SectBufAddr, FltInfo.Info.SectInfo.SectBufSize);
#endif
    FltInfo.Info.SectInfo.SectMode  = pstSectionMonitor->SectMode;
    FltInfo.Info.SectInfo.Event     = DMX_EVENT_DATA_READY | DMX_EVENT_BUF_OVERFLOW|DMX_EVENT_CB_POLL;
    FltInfo.Info.SectInfo.pNotify   = (DMX_NotifyCb)pstSectionMonitor->pfNotify;

    // printf("msAPI_DMX_SectionMonitor notify...%x\n",FltInfo.Info.SectInfo.pNotify);
    MApi_DMX_Info(*(pstSectionMonitor->pu8FID), &FltInfo, &FilterType, TRUE);
    MApi_DMX_Pid(*(pstSectionMonitor->pu8FID), &pstSectionMonitor->u16PID, TRUE);
    MApi_DMX_SectPatternSet(*(pstSectionMonitor->pu8FID), pstSectionMonitor->au8MatchByte, pstSectionMonitor->au8MaskByte, pstSectionMonitor->au8NotMatchByte, MSAPI_DMX_MATCH_PATTERN_LENGTH);

    /*[04]RESET the filter ============================================================*/
    MApi_DMX_SectReset(*(pstSectionMonitor->pu8FID));

    /*[05]START the filter ============================================================*/
    MApi_DMX_Start(*(pstSectionMonitor->pu8FID));

    return DMX_FILTER_STATUS_OK;
}

#if (ENABLE_DEMUX_SW_CRC_CHECK)
#define CRC_TABLE_NUM 256
static unsigned long drv_crc32_table[CRC_TABLE_NUM];

int MApp_Crc_GetCrc32(unsigned char *buffer, unsigned long length)
{
    unsigned long ulCRC = 0xFFFFFFFF;

    while (length--)
    {
        ulCRC = (ulCRC << 8) ^ drv_crc32_table[((ulCRC >> 24) & 0xFF) ^ *buffer++];
    }

    return (ulCRC);
}
static void _msAPI_DMX_Init_CRC_Table(void)
{
    int i,j;
    //printf("crc32\n");
    //MApi_DMX_SetDbgLevel(DMX_DBG_ERR);
    for(i=0;i<CRC_TABLE_NUM;i++)
    {
        drv_crc32_table[i]=i<<24;
        for(j=0;j<8;j++)
        {
            if((drv_crc32_table[i]&0x80000000L) == 0)
                drv_crc32_table[i]=(drv_crc32_table[i]<<1);
            else
                drv_crc32_table[i]=(drv_crc32_table[i]<<1)^0x04C11DB7;
        }
        //printf("0x%08x,\n",drv_crc32_table[i]);
    }
    //printf("\n");
}
#endif

MS_BOOL msAPI_DMX_CheckCRC32(MS_U8* pu8Section)
{
#if (ENABLE_DEMUX_SW_CRC_CHECK)

    MS_U16 u16SecLenInByte;
    static MS_BOOL bfirst=0;
    if(bfirst==0)
    {
        bfirst=1;
        _msAPI_DMX_Init_CRC_Table();
    }
    /*[01]get section length from buffer ==============================================*/
    u16SecLenInByte  = ((*(pu8Section+1) & 0x0f) << 8);
    u16SecLenInByte |= ((*(pu8Section+2) & 0xff) << 0);
    if (u16SecLenInByte <= 4)
    {
        return FALSE;
    }
    u16SecLenInByte = u16SecLenInByte + 3; // plus before section length fields

    /*[02]use hardware crc engine to compare ==========================================*/
    if (!MApp_Crc_GetCrc32(pu8Section, u16SecLenInByte))    //<---return 0 means CRC correct
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#else
    pu8Section = pu8Section;
    return TRUE;
#endif
}
#endif

//****************************************************************************
/// close SI/PSI filter
/// @param u8FID \b IN: filter ID
/// @return none
//****************************************************************************
void msAPI_DMX_CloseFilter(MS_U8 u8FID)
{
    /* stop section filter */
    msAPI_DMX_Stop(u8FID);

    /* close section filter */
    msAPI_DMX_Close(u8FID);
}
//****************************************************************************
/// restart SI/PSI filter
/// @param u8FID \b IN: filter ID
/// @return none
//****************************************************************************
void msAPI_DMX_RestartFilter(MS_U8 u8FID)
{
#if(CSA_ENABLE == 1)
    if(u8FID == CSA_FILTER_ID)
    {
        return;
    }
#endif

    /* stop section filter */
    msAPI_DMX_Stop(u8FID);

    /* reset fifo */
    msAPI_DMX_Reset(u8FID);

    /* start section filter */
    msAPI_DMX_Start(u8FID);
}

DMX_FILTER_STATUS msAPI_DMX_CopyData(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32ActualSize, MS_U32* pu32RmnSize, DMX_CheckCb pfCheckCB)
{
#if(CSA_ENABLE == 1)
    if(u8DmxId == CSA_FILTER_ID)
    {
        MS_U16 secLen;
        MS_U32 u32ReadAddress;
        MBX_Result mbxResult;
        MBX_Msg mbxMsg;
        if(_u32SecWriteAddress == _u32SecReadAddress)return DMX_FILTER_STATUS_ERROR;
        //printf("read %x write %x start %x end %x\n",_u32SecReadAddress,_u32SecWriteAddress,
        //    _u32SecStartAddress,_u32SecEndAddress);
        if((_u32SecReadAddress+3)>_u32SecEndAddress)
        {

            memcpy(pu8Buf,(void*)MsOS_PA2KSEG1(_u32SecReadAddress),_u32SecEndAddress-_u32SecReadAddress);
            memcpy(&pu8Buf[_u32SecEndAddress-_u32SecReadAddress],(void*)MsOS_PA2KSEG1(_u32SecStartAddress),3-(_u32SecEndAddress-_u32SecReadAddress));
            secLen=((pu8Buf[1]&0xf)<<8)+pu8Buf[2]+3;
            memcpy(&pu8Buf[_u32SecEndAddress-_u32SecReadAddress],(void*)MsOS_PA2KSEG1(_u32SecStartAddress),secLen-(_u32SecEndAddress-_u32SecReadAddress));
            u32ReadAddress=_u32SecStartAddress+secLen-(_u32SecEndAddress-_u32SecReadAddress);
        }
        else
        {
            memcpy(pu8Buf,(void*)MsOS_PA2KSEG1(_u32SecReadAddress),3);
            secLen=((pu8Buf[1]&0xf)<<8)+pu8Buf[2]+3;
            if((_u32SecReadAddress+secLen)>_u32SecEndAddress)
            {
                memcpy(pu8Buf,(void*)MsOS_PA2KSEG1(_u32SecReadAddress),_u32SecEndAddress-_u32SecReadAddress);
                memcpy(&pu8Buf[_u32SecEndAddress-_u32SecReadAddress],(void*)MsOS_PA2KSEG1(_u32SecStartAddress),secLen-(_u32SecEndAddress-_u32SecReadAddress));
                u32ReadAddress=_u32SecStartAddress+secLen-(_u32SecEndAddress-_u32SecReadAddress);
            }
            else
            {
                memcpy(pu8Buf,(void*)MsOS_PA2KSEG1(_u32SecReadAddress),secLen);
                u32ReadAddress=_u32SecReadAddress+secLen;
                if(u32ReadAddress == _u32SecEndAddress)u32ReadAddress=_u32SecStartAddress;
            }
        }
        _u32SecReadAddress=u32ReadAddress;
        printf("len %x  read %x write %x start %x end %x\n",secLen,_u32SecReadAddress,_u32SecWriteAddress,
            _u32SecStartAddress,_u32SecEndAddress);
        mbxMsg.eMsgType=E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8MsgClass=E_MBX_CLASS_CSA;
        mbxMsg.u8Index=MB_CSA_SEC_READ_ADDRESS;
        mbxMsg.u8ParameterCount=4;
        mbxMsg.u8Parameters[0]=u32ReadAddress>>24;
        mbxMsg.u8Parameters[1]=(u32ReadAddress>>16)&0xFF;
        mbxMsg.u8Parameters[2]=(u32ReadAddress>>8)&0xFF;
        mbxMsg.u8Parameters[3]=(u32ReadAddress)&0xFF;
	    mbxResult = MApi_MBX_SendMsg(&mbxMsg);
        if(E_MBX_SUCCESS != mbxResult)
        {
            printf("!!!!!!MBX send read address msg error\n");
        }
        return DMX_FILTER_STATUS_OK;
    }
#endif
    return MApi_DMX_CopyData(u8DmxId,pu8Buf,u32BufSize,pu32ActualSize,pu32RmnSize,pfCheckCB);
}
MS_BOOL msAPI_DMX_IsCSA_ON(void)
{
#if(CSA_ENABLE == 1)
    return _bCSA_ON;
#else
    return FALSE;
#endif
}
#if(CSA_ENABLE == 1)
static void _HandleCSAMSG(MBX_Msg *pMsg, MS_BOOL *pbAddToQueue)
{
    if(MB_CSA_SEC_WRITE_ADDRESS == pMsg->u8Index)
    {
        _u32SecWriteAddress=((pMsg->u8Parameters[0]<<24)|(pMsg->u8Parameters[1]<<16)|(pMsg->u8Parameters[2]<<8)|(pMsg->u8Parameters[3]));
        *pbAddToQueue = FALSE;
    }
    else
    {
        *pbAddToQueue = TRUE;
    }
}


void msAPI_DMX_CSA_Enable(BOOLEAN bEnable, MS_U8 u8FilterGroup)
{
    _bCSA_ON=bEnable;
    _u8FilterGroup=u8FilterGroup;
}
#endif

