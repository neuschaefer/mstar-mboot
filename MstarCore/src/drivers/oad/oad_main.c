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
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <config.h>
#include <MsTypes.h>
#include <MsIRQ.h>
#include <MsOS.h>
#include <apiGOP.h>
#include <apiGFX.h>
#include <drvSEM.h>
#include <drvGPIO.h>
#include <apiDMX.h>
#include "msAPI_demux.h"
#include "msAPI_oad_process.h"
#include "msAPI_oad_parser.h"
#include "msAPI_Memory.h"
#include "msAPI_Tuner.h"
#include <linux/string.h>
#include <asm/string.h>
#include "uboot_mmap.h"

#if (CONFIG_OAD_IN_MBOOT)
#define ENABLE_OAD 1
#define ENABLE_BL_OAD_SCAN 1
#if (CONFIG_DISPLAY_OSD)
#define ENABLE_BL_UI 1
#define GWIN_WIDTH          720
#define GWIN_HEIGHT         576
#define GRAPHIC_WIDTH       600
#define GRAPHIC_HEIGHT      400
#define GRAPHIC_X           60
#define GRAPHIC_Y           88
#else
#define ENABLE_BL_UI 0
#endif
#define DBG_PRINT(x)    //x
#define TUNER_LOCK_TIME_OUT     5000//ms
#define MONITOR_DSI_TIME_OUT    60000//ms
#define MONITOR_DII_TIME_OUT    60000//ms
#define MONITOR_DDB_TIME_OUT    60000*1//ms
#define FE_NOT_LOCK     0
#define FE_LOCK         1
#define FE_AGC_NOT_LOCK 2
#define BUF_SIZE 4096

// OAD info
#define CUSTOMER_OUI            0x00169B    // MStar OUI
#define HW_MODEL                0x01        // HW Model
#define HW_VERSION              0x01        // HW Version
#define BL_SW_MODEL             0x01        // SW Model of Bootloader
#define BL_SW_VERSION           0x01        // SW Version of of Bootloader
#define AP_SW_MODEL             0x0001        // SW Model of Application
#define AP_SW_VERSION           0x0001        // SW Version of of Application

#define VERSION_CHECK 1
#define DATA_BC_ID_SSU          0x000A // DVB-SSU
#define DATA_BC_ID_UK_EC        0x0111 // UK Engineering Channel
#define MAX_DDB_MSGSIZE 4066
#define HW_MODEL_VER_CHECK      0

//buffer address
#define DOWNLOAD_BUFFER_LEN_OAD     0x0003200000
#define DOWNLOAD_BUFFER_ADR_OAD     UPGRADE_BUFFER_ADDR
#define OADSEC_BUFFER_ADR                                      DMX_SEC_BUFFER_ADR //Alignment 0x00010
#define OADSEC_BUFFER_LEN                                      0x0000014000

#define DMX_BUF_SIZE_MONITOR    0x4000
#define DMX_BUF_SIZE_DOWNLOAD   0x4000*4

#ifndef UNUSED
#define UNUSED(x) ((x)=(x))
#endif

static MS_U16 wOad_PID = 0;
static MS_U32 u32Frequency = 0;
static MS_U8  u8BandWidth = 0;
MS_U32  u32QAM = 0;
MS_U16  u16SymbolRate = 0;
#if(CONFIG_SDTT_OAD)
static MS_U8  u8IsSDTT_OAD = 0;
#endif
static MS_U32 tsVersion=0;
static MS_U32 MS_U32DOWNLOADSIZE=0;
static MS_U8   _u8OADMonitorFID=MSAPI_DMX_INVALID_FLT_ID;
static MS_U8   _u8OADDownloadFID=MSAPI_DMX_INVALID_FLT_ID;
MS_U8  au8MonitorSection[4096];
MS_U8  au8DownloadSection[4096];
static MS_U32 u32DownloadSize = 0x0;
static MS_U8  versionNum = 0xff ;
static MS_U32 u32ModuleAddr=0;
MS_U32 u32OadbufMonitorAddr = 0;
MS_U32 u32OadbufMonitorSize = 0;
MS_U32 u32OadbufDownloadAddr = 0;
MS_U32 u32OadbufDownloadSize = 0;


extern MS_BOOL msAPI_Tuner_CheckLock(MS_BOOL *CheckLockResult,MS_BOOL fScan);

#if (ENABLE_BL_UI)
void MApp_BL_DisplaySystem(MS_U8  u8Percent);
void MApp_BL_DisplaySystem_clear(void);
void MApp_BL_DisplaySystem_setStatus(S8 *status);

void MApp_BL_DisplaySystem(MS_U8  u8Percent)
{
    char* buffer=NULL;
    int ret=0;

    buffer=(char *)malloc(BUF_SIZE);
    if(buffer != NULL)
    {
        memset(buffer, 0 , 256);
        sprintf(buffer, "draw_rect %d %d %d %d 000000ff", GRAPHIC_X, GRAPHIC_Y+300, GRAPHIC_WIDTH, GRAPHIC_HEIGHT-300);
        ret=run_command(buffer, 0);

        memset(buffer, 0 , 256);
        sprintf(buffer, "draw_progress %d %d ffffffff %u", GRAPHIC_X+60, GRAPHIC_Y+300, u8Percent);
        ret=run_command(buffer, 0);
        sprintf(buffer, "osd_flush");
        run_command(buffer, 0);
        free(buffer);
    }
    else
    {
        printf("%s: malloc() failed, at %d\n", __func__, __LINE__);
    }
}

void MApp_BL_DisplaySystem_clear(void)
{
    char* buffer=NULL;
    int ret=0;

    buffer=(char *)malloc(BUF_SIZE);
    if(buffer != NULL)
    {
        memset(buffer, 0 , 256);
        sprintf(buffer, "draw_rect %d %d %d %d 000000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
        ret=run_command(buffer, 0);

        memset(buffer, 0 , 256);
        sprintf(buffer, "draw_string %d %d ffffffff 1 '%s'", GRAPHIC_X, GRAPHIC_Y+100, "PLEASE_DO_NOT_POWER_OFF");
        ret=run_command(buffer, 0);
        sprintf(buffer, "osd_flush");
        run_command(buffer, 0);
        free(buffer);
    }
    else
    {
        printf("%s: malloc() failed, at %d\n", __func__, __LINE__);
    }
}

void MApp_BL_DisplaySystem_setStatus(S8 *status)
{
    char* buffer=NULL;
    int ret=0;

    buffer=(char *)malloc(BUF_SIZE);
    if(buffer != NULL)
    {
        memset(buffer, 0 , 256);
        sprintf(buffer, "draw_string %d %d ffffffff 1 '%s'", GRAPHIC_X, GRAPHIC_Y+200, status);
        ret=run_command(buffer, 0);
        sprintf(buffer, "osd_flush");
        run_command(buffer, 0);
        free(buffer);
    }
    else
    {
        printf("%s: malloc() failed, at %d\n", __func__, __LINE__);
    }
}
#else //(ENABLE_BL_UI)
void MApp_BL_DisplaySystem(MS_U8  u8Percent){UNUSED(u8Percent);}
void MApp_BL_DisplaySystem_clear(void){}
void MApp_BL_DisplaySystem_setStatus(S8 *status){UNUSED(status);}
#endif //(ENABLE_BL_UI)

int oad_check(void);
int oad_check()
{
    MS_U8  *pu8Buf = NULL;
    OAD_STATUS_REPORT_TYPE ddbStatus ;
    MS_U16 blockID=0,msgLen=0,msgType=0 ;
    MS_U32 msgAddr = 0 ;
    MS_BOOL Check_FE_Result;
    MS_U32 u32DsmccTimer=0;
    DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );

    u32DsmccTimer = MsOS_GetSystemTime();
    while(1)
    {
        if( msAPI_Tuner_CheckLock( &Check_FE_Result,FALSE) == FALSE )
        {
            printf("FE Fail!\n");
        }
        else
        {
            if(Check_FE_Result==FE_LOCK)
            {
                printf("FE Locked.\n");
                break;
            }
            else
            {
                printf("FE Not Locked. Check_FE_Result = %d\n", Check_FE_Result);
            }
        }
        if (MsOS_Timer_DiffTimeFromNow(u32DsmccTimer) > TUNER_LOCK_TIME_OUT)
        {
            OAD_DEBUG( printf("Error> Exit DSI\n") );
            return 1; //return to do USB download
        }
		DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );
        MsOS_DelayTask(500);
    }

#if(CONFIG_SDTT_OAD)
	if(!u8IsSDTT_OAD)
	{
#endif
	    if(msAPI_OAD_CreateSectionFilter( MSAPI_DMX_FILTER_TYPE_OAD_MONITOR, OAD_CONTROL_SECTION_TYPE, OAD_DSMCC_MSGID_DSI,
	            wOad_PID, &_u8OADMonitorFID ) == TRUE)
	    {
	        DBG_PRINT( printf("Create filter: OK, pid: 0x%x.\n", wOad_PID) );
	    }

	    DBG_PRINT( printf("Line: %d\n", __LINE__) );

	    u32DsmccTimer = MsOS_GetSystemTime();
	    while(1)
	    {
	        pu8Buf = msAPI_OAD_PollingSectionFilter(_u8OADMonitorFID, au8MonitorSection);

	        if(pu8Buf)
	        {
	            DBG_PRINT( printf("DSI Poll filter: OK.\n") );

	            if (OAD_SUCCEED==msAPI_OAD_ProcessDSI(pu8Buf))
	            {
	                u32DsmccTimer = MsOS_GetSystemTime();
	                versionNum = msAPI_OAD_GetDsiVersionNum() ;

	                if (versionNum!=msAPI_OAD_GetDsiVersionNum())
	                {
	                    printf("versionNum error !!!\n");
	                }
	                msAPI_OAD_DeleteSectionFilter(&_u8OADMonitorFID);
	                break;
	            }
	            else
	            {
	                printf("process DSI error !!!\n");
	            }
	        }
	        else
	        {
	            printf("No DSI Data!\n");
	        }

	        if (MsOS_Timer_DiffTimeFromNow(u32DsmccTimer) > MONITOR_DSI_TIME_OUT)
	        {
	            OAD_DEBUG( printf("Error> Exit DSI\n") );
	            return 1;
	        }
	        MsOS_DelayTask(100);
	    }
#if(CONFIG_SDTT_OAD)
	}
	else
	{
	    printf("===== [%s][%d] =====\n",__FUNCTION__,__LINE__);
	    DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );
	    msAPI_OAD_SetOADMode(OAD_MODE_DATACAR);
	    msAPI_Set_SDTT_OAD(TRUE);
	}
#endif

    if(msAPI_OAD_CreateSectionFilter( MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD,OAD_CONTROL_SECTION_TYPE,OAD_DSMCC_MSGID_DII,wOad_PID, &_u8OADDownloadFID) == TRUE)
    {
        DBG_PRINT( printf("\n") );
        DBG_PRINT( printf("DII Create filter: OK.\n") );
        DBG_PRINT( printf("DII _u8OADDownloadFID = %d\n", _u8OADDownloadFID) );
        u32DsmccTimer = MsOS_GetSystemTime();
    }
    else
    {
        printf("Error> msAPI_OAD_CreateSectionFilter(OAD_CONTROL_SECTION_TYPE) : Invalid FID=%x\n",_u8OADDownloadFID);
        return 1;
    }

    while(1)
    {
        pu8Buf = msAPI_OAD_PollingSectionFilter(_u8OADDownloadFID, au8DownloadSection);

        if(pu8Buf)
        {
            if(OAD_SUCCEED==msAPI_OAD_ProcessDII(pu8Buf))
            {
                msAPI_OAD_DeleteSectionFilter(&_u8OADDownloadFID) ;
                DBG_PRINT( printf("process DII ok\n") );
                break;
            }

            if (MsOS_Timer_DiffTimeFromNow(u32DsmccTimer) > MONITOR_DII_TIME_OUT)
            {
                printf("Error> Timeout to receive DII\n");
                return 1;
            }
        }
    }

    if(msAPI_OAD_CreateSectionFilter( MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD,OAD_DATA_SECTION_TYPE ,OAD_DSMCC_MSGID_DDB,
                wOad_PID,&_u8OADDownloadFID) == TRUE)
    {
        DBG_PRINT( printf("\n") );
        DBG_PRINT( printf("DDB Create filter: OK.\n") );
        u32DsmccTimer = MsOS_GetSystemTime();
    }
    else
    {
        printf("Error> msAPI_OAD_CreateSectionFilter(OAD_DATA_SECTION_TYPE) : Invalid FID\n");
    }

    MApp_BL_DisplaySystem_clear(); //clear screen
    MApp_BL_DisplaySystem_setStatus((S8*)"DOWNLOAD");
    MApp_BL_DisplaySystem(0);

    while(1)
    {
//        msAPI_Timer_ResetWDT();
        pu8Buf = msAPI_OAD_PollingSectionFilter(_u8OADDownloadFID, au8DownloadSection);

        if(pu8Buf)
        {
            ddbStatus = msAPI_OAD_ProcessDDB(pu8Buf, &blockID, &msgLen, &msgAddr, &msgType) ;

            if (ddbStatus != OAD_FAIL)
            {
                u32DsmccTimer = MsOS_GetSystemTime();
                if(msgLen>0)
                {
                    if (msgType==OAD_MODE_OBJCAR)
                    {
                        if (blockID==0)
                        {
                        #if defined(CONFIG_URANUS4) || defined(CONFIG_KRONUS) || defined(CONFIG_KAISERIN) || defined(CONFIG_KENYA)
                            memcpy((MS_U8 *)(DOWNLOAD_BUFFER_ADR_OAD),(MS_U8 *)msgAddr,(MS_U32)msgLen) ;
                        #else
                            memcpy((MS_U8 *)MS_PA2KSEG1(MS_VA2PA(DOWNLOAD_BUFFER_ADR_OAD)),(MS_U8 *)msgAddr,(MS_U32)msgLen) ;
                        #endif

                        }
                        else
                        {
                        #if defined(CONFIG_URANUS4) || defined(CONFIG_KRONUS) || defined(CONFIG_KAISERIN) || defined(CONFIG_KENYA)
                            memcpy((MS_U8 *)(DOWNLOAD_BUFFER_ADR_OAD+(blockID*MAX_DDB_MSGSIZE)-BIOP_HEADER_LEN),(MS_U8 *)msgAddr,(MS_U32)msgLen) ;
                        #else
                            memcpy((MS_U8 *)MS_PA2KSEG1(MS_VA2PA(DOWNLOAD_BUFFER_ADR_OAD+(blockID*MAX_DDB_MSGSIZE)-BIOP_HEADER_LEN)),(MS_U8 *)msgAddr,(MS_U32)msgLen) ;
                        #endif
                        }
                    }
                    else if (msgType==OAD_MODE_DATACAR)
                    {
                        MS_U32 u32BlockSize = msAPI_OAD_GetBlockSize();
                    #if defined(CONFIG_URANUS4) || defined(CONFIG_KRONUS) || defined(CONFIG_KAISERIN) || defined(CONFIG_KENYA)
					    DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );
                        memcpy((MS_U8 *)(DOWNLOAD_BUFFER_ADR_OAD+(blockID*u32BlockSize)),(MS_U8 *)msgAddr,(MS_U32)msgLen) ;
                    #else
                        memcpy((MS_U8 *)MS_PA2KSEG1(MS_VA2PA(DOWNLOAD_BUFFER_ADR_OAD+(blockID*u32BlockSize))),(MS_U8 *)msgAddr,(MS_U32)msgLen) ;
                    #endif

                    }
                    //u32DownloadSize += msgLen ;
                }
            }
            if (ddbStatus == OAD_COMPLETE)
            {
                //MS_U32 CRC_result=0;
                //MS_U32 CRC_value=0;
                DBG_PRINT( printf("DDB complete.\n") );
                //Check CRC32
                //CRC_value=*((MS_U32*)(DOWNLOAD_BUFFER_ADR_OAD+u32DownloadSize-4));
                //CRC_result=crc32( 0x00, (MS_U8 *)DOWNLOAD_BUFFER_ADR_OAD, u32DownloadSize-4 );
                //DBG_PRINT( printf("CRC_result 0x%x, CRC_value 0x%x\n", CRC_result, CRC_value) );
                msAPI_OAD_DeleteSectionFilter(&_u8OADDownloadFID) ;
                break;
            }
        }
        {
            static MS_U8  u8PrevPersentage=0;
            MS_U8  u8Percentage = msAPI_OAD_GetProgress();
            if (u8Percentage > 100)
                u8Percentage = 100;
            if(u8PrevPersentage != u8Percentage)
            {
                u8PrevPersentage = u8Percentage;
                MApp_BL_DisplaySystem(u8Percentage);
                DBG_PRINT( printf("u8Percentage: %u, at %d\n", u8Percentage, __LINE__) );
            }
        }
        if (MsOS_Timer_DiffTimeFromNow(u32DsmccTimer) > MONITOR_DDB_TIME_OUT)
        {
            msAPI_OAD_ClearData();
            OAD_DEBUG( printf("Error> Exit DDB\n") );
            printf("DDB timeout!\n");
            return 1;
        }
    }

    MApp_BL_DisplaySystem(100);
    DBG_PRINT( printf("\nOAD Finished\n") );

    msAPI_OAD_GetModuleInfo( &u32ModuleAddr, &u32DownloadSize );
    printf("u32ModuleAddr 0x%x, u32DownloadSize 0x%x\n",(unsigned int)u32ModuleAddr,(unsigned int) u32DownloadSize);
    printf("DOWNLOAD_BUFFER_ADR_OAD 0x%X, DOWNLOAD_BUFFER_LEN_OAD 0x%X\n",(unsigned int) DOWNLOAD_BUFFER_ADR_OAD,(unsigned int) DOWNLOAD_BUFFER_LEN_OAD);
    MS_U32DOWNLOADSIZE = u32DownloadSize;

    MApp_BL_DisplaySystem_clear();
    MApp_BL_DisplaySystem_setStatus((S8*)"Software Update(OAD)");
    MApp_BL_DisplaySystem(0);
    return 0;
}

int chakra2_main_loop(void)
{

    DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );
    if(!oad_check())
    {
        return 0;
    }
    return 1;

}

MS_BOOL oad_VersonCheck(MS_U16 type,MS_U8  *pPrivateData)
{
    MS_U16  compatibilityLength,descriptorCount,model,version=0x0,i;
    MS_U8   descriptorType, descriptorLength, specifierType,subDescriptorCount;
    MS_U32 specifierData;
    MS_BOOL swPass=FALSE;
#if HW_MODEL_VER_CHECK
    MS_BOOL hwPass=FALSE;
#endif

    if (!VERSION_CHECK) return TRUE ;

    if (type==DATA_BC_ID_UK_EC) // MIS
    {
        MS_U16 model_hw, version_hw;
        model_hw = GET_2BYTE(&pPrivateData[0]);
        version_hw = GET_2BYTE(&pPrivateData[2]);
        model = GET_2BYTE(&pPrivateData[4]);
        version = GET_2BYTE(&pPrivateData[6]);
#if HW_MODEL_VER_CHECK
        if ((model_hw == HW_MODEL)&&(version_hw == HW_VERSION))
#endif //HW_MODEL_VER_CHECK
        {
            if (model == AP_SW_MODEL)
            {
                tsVersion = (MS_U32)version;
                return TRUE ;
            }
        }
        return FALSE ;
    }
    else if (type==DATA_BC_ID_SSU) // GroupCompatibility()
    {
        compatibilityLength = GET_2BYTE(pPrivateData);
        pPrivateData += 2;

        if ( compatibilityLength < 2 )
        {
            OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDSI : compatibilityLength = 0x%x\n", compatibilityLength) );
            return FALSE ;
        }

        descriptorCount = GET_2BYTE(pPrivateData); pPrivateData += 2;
        OAD_DEBUG( printf("descriptorCount = %u\n", descriptorCount) );

        for ( i = 0; i < descriptorCount; i ++ )
        {
            descriptorType  = *pPrivateData++;
            descriptorLength= *pPrivateData++;

            switch ( descriptorType )
            {
                case 0x02:
                {
                    specifierType = *pPrivateData++;
                    specifierData = GET_3BYTE( pPrivateData ); pPrivateData += 3;
                    model = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    version = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    subDescriptorCount = *pPrivateData++;
                    tsVersion = (MS_U32)version;
                    OAD_DEBUG( printf("TS=%x\n",tsVersion));
                    if ((specifierType==0x01)&&(model == AP_SW_MODEL)&&(specifierData==CUSTOMER_OUI)) //Do NOT check version
                    {
                        swPass = TRUE;
                    }
                    else
                    {
                        return FALSE ;
                    }
                    //pPrivateData += (descriptorLength-9) ;
                    //OAD_DEBUG( printf("[OTA] specifierType = 0x%02bx, specifierData = 0x%08lx\n", specifierType, specifierData) );
                    break;
                }
                case 0x01:
#if HW_MODEL_VER_CHECK
                    specifierType = *pPrivateData++;
                    specifierData = GET_3BYTE( pPrivateData ); pPrivateData += 3;
                    model = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    version = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    subDescriptorCount = *pPrivateData++;
                    if(1)
                    {
                        tsVersion = (MS_U32)version;
                    }
                    OAD_DEBUG( printf("TS=%x\n",tsVersion));
                    if ((specifierType==0x01)&&(model == HW_MODEL)&&(version == HW_VERSION)&&(specifierData==CUSTOMER_OUI))
                    {
                        hwPass = TRUE;
                    }
                    else
                    {
                        return FALSE ;
                    }
                    //pPrivateData += (descriptorLength-9) ;
                    //OAD_DEBUG( printf("[OTA] specifierType = 0x%02bx, specifierData = 0x%08lx\n", specifierType, specifierData) );
                    break;
#endif
                default:
                {
                    pPrivateData += descriptorLength;
                    OAD_DEBUG( printf("[OTA] descriptorType = 0x%02bx\n", descriptorType) );
                    break;
                }
            }
       }// End of for
    }
#if HW_MODEL_VER_CHECK
    if((swPass == TRUE) && (hwPass == TRUE))
#else //HW_MODEL_VER_CHECK
    if(swPass == TRUE)
#endif //HW_MODEL_VER_CHECK
    {
        return TRUE ;
    }
    return FALSE ;
}

int oad_prepare(void)
{
    DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );
    u32OadbufMonitorAddr = (MS_U32)(OADSEC_BUFFER_ADR); //(_VA2PA((MS_U32)demuxBuf.monitor)) ;
    u32OadbufDownloadAddr = (MS_U32)(OADSEC_BUFFER_ADR + 0x4000);//(_VA2PA((MS_U32)demuxBuf.download)) ;
    u32OadbufMonitorSize = DMX_BUF_SIZE_MONITOR;
    u32OadbufDownloadSize = DMX_BUF_SIZE_DOWNLOAD;

    _u8OADMonitorFID = MSAPI_DMX_INVALID_FLT_ID;
    _u8OADDownloadFID = MSAPI_DMX_INVALID_FLT_ID;
    MS_U32DOWNLOADSIZE = 0;
    u32DownloadSize = 0;
    versionNum = 0;
    u32ModuleAddr = 0;
    tsVersion=0;
    memset(au8MonitorSection, 0, sizeof(au8MonitorSection));
    memset(au8DownloadSection, 0, sizeof(au8DownloadSection));

    msAPI_OAD_ClearData();
    msAPI_OAD_SetOui((MS_U8 )(CUSTOMER_OUI>>16), (MS_U8 )(CUSTOMER_OUI>>8), (MS_U8 )(CUSTOMER_OUI));
    msAPI_OAD_SetVersionCheck(oad_VersonCheck) ;

    {
        //front end init
        char* buffer=NULL;
        int ret=0;

        buffer=(char *)malloc(BUF_SIZE);
        if(buffer != NULL)
        {
        #if defined(CONFIG_URANUS4) || defined(CONFIG_KRONUS) || defined(CONFIG_KAISERIN) || defined(CONFIG_KENYA)
            memset(buffer, 0 , 256);
            sprintf(buffer, "tuner_demodtype 1"); // dvbt/dvbs/dvbc
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                free(buffer);
                return -1;
            }

            memset(buffer, 0 , 256);
            sprintf(buffer, "tuner_init");
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                free(buffer);
                return -1;
            }


            memset(buffer, 0 , 256);
            sprintf(buffer, "tuner_tune %lu %x", u32Frequency, u8BandWidth);
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                return -1;
            }
        #else
            memset(buffer, 0 , 256);
            sprintf(buffer, "tuner_init");
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                free(buffer);
                return -1;
            }

            memset(buffer, 0 , 256);
            sprintf(buffer, "tuner_demodtype 1"); //dvbt
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                free(buffer);
                return -1;
            }
            memset(buffer, 0 , 256);
            sprintf(buffer, "tuner_tune %lu %x", u32Frequency, u8BandWidth);
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                //try T2
                memset(buffer, 0 , 256);
                sprintf(buffer, "tuner_demodtype 2"); //dvbt2
                ret=run_command(buffer, 0);
                if(ret==-1)
                {
                    free(buffer);
                    return -1;
                }
                memset(buffer, 0 , 256);
                sprintf(buffer, "tuner_tune %lu %x", u32Frequency, u8BandWidth);
                ret=run_command(buffer, 0);
                if(ret==-1)
                {
                    free(buffer);
                    return -1;
                }
            }
        #endif

            memset(buffer, 0 , 256);
#if((MS_BOARD_TYPE_SEL == BD_MST098E_D01B) || (MS_BOARD_TYPE_SEL == BD_MST138B_D01A) \
    ||(MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225) || (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225))
            sprintf(buffer, "dmx_init 3");  // DMX_FLOW_INPUT_EXT_INPUT1
#elif defined(CONFIG_KENYA)
#if(FRONTEND_DEMOD_TYPE == MSTAR_MSB1238_DEMOD)//1238????
						sprintf(buffer, "dmx_init 2");	// DMX_FLOW_INPUT_EXT_INPUT0
#else
						sprintf(buffer, "dmx_init 0");
#endif
#else
            sprintf(buffer, "dmx_init 2");  // DMX_FLOW_INPUT_EXT_INPUT0
#endif
            ret=run_command(buffer, 0);
            if(ret==-1)
            {
                free(buffer);
                return -1;
            }
            free(buffer);
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

void MApp_BL_Init(void)
{
#if (ENABLE_BL_UI)
    {
        char* buffer=NULL;
        int ret=0;

        buffer=(char *)malloc(BUF_SIZE);
        if(buffer != NULL)
        {
            memset(buffer, 0 , 256);
            sprintf(buffer, "osd_create %d %d", GWIN_WIDTH, GWIN_HEIGHT);
            ret=run_command(buffer, 0);
            free(buffer);
            if(ret==-1)
                return;
        }
        else
        {
            printf("%s: malloc() failed, at %d\n", __func__, __LINE__);
        }
    }
#endif //(ENABLE_BL_UI)

    /* initialize 8K bytes memory pool */
    msAPI_Memory_Init();
}

int chakra2_main(void)
{
    DBG_PRINT( printf("%s: at %d\n", __func__, __LINE__) );
    MApp_BL_Init();

    DBG_PRINT( printf("prepare USB/OAD upgrade !!\n") );
    //MDrv_Sys_ClearWatchDog();
    //usb_prepare();
    if(oad_prepare())
        return -1;


    MApp_BL_DisplaySystem_clear(); //clear screen
    MApp_BL_DisplaySystem(0);
    if(!chakra2_main_loop())
    {
        return 0;
    }
    return -1;
}

int do_oad_get_size (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_U32* size;
    if (argc !=2) {
        printf("Usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    size=(MS_U32*)simple_strtoul(argv[1], NULL, 16);
    *size = MS_U32DOWNLOADSIZE;
    return 0;
}


int do_oad (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if(CONFIG_SDTT_OAD)
    if (argc !=5) {
#else
    if (argc !=4) {
#endif
        printf("Usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    u32Frequency = (MS_U32)simple_strtoul(argv[1], NULL, 10);
    u8BandWidth  = (MS_U8 )simple_strtoul(argv[2], NULL, 16);
    wOad_PID 	 = (MS_U16)simple_strtoul(argv[3], NULL, 16);
#if(CONFIG_SDTT_OAD)
	u8IsSDTT_OAD = (MS_U8 )simple_strtoul(argv[4], NULL, 10);
#endif
    return chakra2_main();
}

int do_oad_dvbc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#if(CONFIG_SDTT_OAD)
    if (argc !=6) {
#else
    if (argc !=5) {
#endif
        printf("Usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    u32Frequency = (MS_U32)simple_strtoul(argv[1], NULL, 10);
    u32QAM = (MS_U32)simple_strtoul(argv[2], NULL, 10);
    u16SymbolRate = (MS_U16)simple_strtoul(argv[3], NULL, 10);
    printf("u32QAM = %ld\n",u32QAM);
    printf("u16SymbolRate = %d\n",u16SymbolRate);
    wOad_PID 	 = (MS_U16)simple_strtoul(argv[4], NULL, 16);
#if(CONFIG_SDTT_OAD)
	u8IsSDTT_OAD = (MS_U8 )simple_strtoul(argv[5], NULL, 10);
#endif
    return chakra2_main();
}

U_BOOT_CMD(
    oad_get_size,    2,   1,  do_oad_get_size,
    "oad_get_size - Get the file size from OAD download \n",
    "Get download size\n"
    "    - Address: 32 bits (Hex) address to save download size\n"
);

U_BOOT_CMD(
#if(CONFIG_SDTT_OAD)
    oad,    5,   1,  do_oad,
#else
    oad,    4,   1,  do_oad,
#endif
    "oad - Software Upgrade(OAD) \n",
    "Over the Air Download\n"
    "    - Frequency: 32 bits (Decimal). e.g. 474000\n"
    "    - Bandwidth: 1:6MHz, 2:7MHz, 3: 8MHz\n"
    "    - Pid: 16 bits (Hex) pid, e.g. 0x150\n"
);

U_BOOT_CMD(
#if(CONFIG_SDTT_OAD)
    oaddvbc,    6,   1,  do_oad_dvbc,
#else
    oaddvbc,    5,   1,  do_oad_dvbc,
#endif
    "oad - Software Upgrade(OAD) \n",
    "Over the Air Download\n"
    "    - Frequency: 32 bits (Decimal). e.g. 474000\n"
    "    - Bandwidth: 1:6MHz, 2:7MHz, 3: 8MHz\n"
    "    - Pid: 16 bits (Hex) pid, e.g. 0x150\n"
);
#endif

