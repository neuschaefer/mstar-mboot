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
#ifndef _MSAPI_OAD_PROCESS_C_
#define _MSAPI_OAD_PROCESS_C_

/*------------------------------------------------------------------------------
*   include files
*-----------------------------------------------------------------------------*/
// C Library
#include <common.h>
#include <exports.h>
#include <MsTypes.h>
#include <asm/string.h>
#include <linux/string.h>
#include "msAPI_Memory.h"
#include "msAPI_oad_process.h"
#include "msAPI_oad_biop.h"

typedef MS_U16      UINT16;
#define BCD2Dec(x)      ((((x) >> 4) * 10) + ((x) & 0x0F))

#if 1//ENABLE_OAD
#define SECTION_LENGTH( h ) ( ( ( *( h + 1 ) & 0x0F ) << 8 ) | ( * ( h + 2 ) ) )

#define _BITMASKREFPOS  ( 0x80000000 )
#define _ISRCVDBLOCK( blknum ) ( ( OAD_ModInfo.blkchkbits[ blknum / 32 ] ) & ( _BITMASKREFPOS >> ( blknum % 32 ) ) )
#define _SETNEWBLOCK( blknum ) ( ( OAD_ModInfo.blkchkbits[ blknum / 32 ] ) |= ( _BITMASKREFPOS >> ( blknum % 32 ) ) )

#define DATA_BC_ID_SSU          0x000A // DVB-SSU
#define DATA_BC_ID_UK_EC        0x0111 // UK Engineering Channel
#define UNT_TAG_SCHED           0x01    // scheduling_descriptor
#define UNT_TAG_UPDAP           0x02    // updated_descriptor
#define UNT_TAG_SSULA           0x03    // ssu_location_descriptor

#define SECONDS_PER_MIN         60L
#define SECONDS_PER_HOUR        3600L
#define SECONDS_PER_DAY         86400L
#define DEFAULT_YEAR            1980
#define DEFAULT_MJD             44239

/*------------------------------------------------------------------------------
*   type define of variable types
*-----------------------------------------------------------------------------*/
typedef struct
{
    MS_U32           moduleData;     // Pointer to raw module data

    MS_U32           groupId;        // Transaction Id of DII
    MS_U32           downloadId;
    MS_U16           blockSize;      // Max size of blocks in this Module

    MS_U16           moduleId;       // Id of this module
    MS_U32           moduleSz;       // Size of this module
    MS_U8            version;        // Version of this module

    MS_U16           chkarraycnt;    // Number of bytes in 'blkchkbits'
    MS_U32           *blkchkbits;    // Bit flag marking received blocks

    MS_U16           totBlocks;      // Total number of blocks in module
    MS_U16           rcvBlocks;      // Total received blocks in module
} __attribute__ ((packed)) OAD_MODULE;


/*------------------------------------------------------------------------------
*   Global variables.
*-----------------------------------------------------------------------------*/
static OAD_MODULE  OAD_ModInfo ;
static MS_U8          OAD_ModInfos_Size = 0;
static OAD_MODULE  *pOAD_ModInfos = NULL;
static MS_U32      OAD_BlkChkBuffer[80]={0};
static MS_U32      *pOAD_BlkChkBuffer=NULL, g_u32OAD_BlkChkBufferLen=0;
static MS_U8      OAD_Mode = OAD_MODE_INVALID;
#if(CONFIG_SDTT_OAD)
static MS_BOOL bIsSDTT_OAD = FALSE;
#endif

static MS_BOOL bIsOADFileFound = FALSE;
static MS_U8 (*msAPI_OAD_VersionCheck)(MS_U16,MS_U8*)=NULL ;
static MS_U8   versionNum = 0 ;
static MS_U32  g_OAD_DDBBufferAddr;
static MS_U32  g_OAD_DDBBufferSize;
static MS_U32  g_OAD_MISVersionId;
static BIOP_BODY_PROFILE_IOR_INFO  OAD_DSI_IOR = {0, 0, 0, FALSE};
BIOP_BODY_PROFILE_IOR_INFO  OAD_OUI_DIR_IOR = {0, 0, 0, FALSE};
BIOP_BODY_PROFILE_IOR_INFO  OAD_FILE_IOR = {0, 0, 0, FALSE};
static MS_U16 SolarDays[28] =
{
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 396, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 397
};
static MSIF_Version _mw_oad_version = {
       .MW = { MW_OAD_VER },
};

MS_U8 g_OAD_OUI[3]={'M', 'S', 'T'};
MS_U8 OAD_OUI_ASCII[7];

extern MS_U32 MsOS_MPool_PA2KSEG1(MS_U32 pAddrPhys);
/*------------------------------------------------------------------------------
| Functions
*-----------------------------------------------------------------------------*/
static MS_U8 hex_digit(MS_U8 val)
{
    /* assert */
    if (val > 0x0F)
    {
        return '0';
    }

    return (val < 10) ? '0' + val : 'a' + (val - 10);
}

static MS_U8* convert_key(MS_U8 *key, MS_U8 *ascii_key, MS_U8 size)
{
    MS_U8 i;

    /* convert to a string of hex byte values */
    for (i=0; i<size; i++)
    {
        ascii_key[i * 2] = hex_digit((key[i] >> 4) & 0x0f);
        ascii_key[(i * 2) + 1] = hex_digit(key[i] & 0x0f);
    }
    ascii_key[size * 2] = '\0';

    return ascii_key;
}

void _msAPI_OAD_ClearDynamicData( void )
{
    if((pOAD_BlkChkBuffer != NULL) || (g_u32OAD_BlkChkBufferLen > 0 ))
    {
        if(g_u32OAD_BlkChkBufferLen > 0)
        {
            free((void*)pOAD_BlkChkBuffer);
        }
        pOAD_BlkChkBuffer = NULL;
        g_u32OAD_BlkChkBufferLen = 0;
    }
}

void msAPI_OAD_SetOui(MS_U8 byte1, MS_U8 byte2, MS_U8 byte3)
{
    g_OAD_OUI[0]=byte1;
    g_OAD_OUI[1]=byte2;
    g_OAD_OUI[2]=byte3;
    convert_key(g_OAD_OUI, OAD_OUI_ASCII, 3);
}

void msAPI_OAD_SetDDBBuffer(MS_U32 u32Addr, MS_U32 u32Size)
{
    g_OAD_DDBBufferAddr   =   u32Addr;
    g_OAD_DDBBufferSize   =   u32Size;
}

MS_U32 msAPI_OAD_GetDDBBufferAddr()
{
    return g_OAD_DDBBufferAddr;
}

MS_U32 msAPI_OAD_MemAlloc(MS_U32 u32MemSize)
{
    MS_U32 u32Addr;

    if (u32MemSize > g_OAD_DDBBufferSize)
        u32Addr = OAD_INVALID_ADDR;
    else
    {
        u32Addr = g_OAD_DDBBufferAddr;
        //msAPI_MIU_Clear(0, g_OAD_DDBBufferAddr, g_OAD_DDBBufferSize, 0x00);
    }

    return u32Addr;
}


void msAPI_OAD_SetVersionCheck(MS_U8 (*cb)(MS_U16,MS_U8 *))
{
    msAPI_OAD_VersionCheck=cb ;
}

MS_U8 msAPI_OAD_GetDsiVersionNum(void)
{
    return versionNum ;
}

static MS_U8 msAPI_OAD_GetLeap ( MS_U16 u16year )
{
    if ( u16year % 400 == 0 )
    {
        return 1;
    }
    else if ( u16year % 100 == 0 )
    {
        return 0;
    }
    else if ( u16year % 4 == 0 )
    {
        return 1;
    }

    return 0;
}

static MS_U16 msAPI_OAD_GetDaysOfThisYear ( MS_U16 u16Year )
{
    return msAPI_OAD_GetLeap( u16Year ) ? 366 : 365;
}

static MS_U32 msAPI_OAD_MJDUTC2Seconds(MS_U8 *pau8TDTData)
{
    MS_U8 YY,MM,K;
    MS_U16 u16MJD;
    MS_U32 u32TotalSeconds;
    ST_TIME_OAD _stDate;

    u32TotalSeconds = 0;
    u16MJD = pau8TDTData[0] << 8 | pau8TDTData[1];
    if(u16MJD > DEFAULT_MJD)
    {
        YY = (MS_U8) ((u16MJD - 15078.2) / 365.25);
        MM = (MS_U8) ((u16MJD - 14956.1 - (MS_U16)(YY * 365.25)) / 30.6001);
        K = ((MM == 14) || (MM == 15)) ? 1 : 0;

        _stDate.u16Year = (MS_U16) (1900 + YY + K);
        _stDate.u8Month = (MS_U8) (MM - 1 - (K * 12));
        _stDate.u8Day = (MS_U8) (u16MJD - 14956 - (MS_U16) (YY * 365.25) - (MS_U16) (MM * 30.6001));
        _stDate.u8Hour = BCD2Dec(pau8TDTData[2]);
        _stDate.u8Min = BCD2Dec(pau8TDTData[3]);
        _stDate.u8Sec = BCD2Dec(pau8TDTData[4]);

        /* sec */
        u32TotalSeconds += _stDate.u8Sec;

        /* min */
        u32TotalSeconds += _stDate.u8Min * SECONDS_PER_MIN;

        /* hour */
        u32TotalSeconds += _stDate.u8Hour * SECONDS_PER_HOUR;

        /* day */
        u32TotalSeconds += (_stDate.u8Day - 1) * SECONDS_PER_DAY;

        /* month */
        u32TotalSeconds += SolarDays[msAPI_OAD_GetLeap(_stDate.u16Year) * 14 + _stDate.u8Month - 1] * SECONDS_PER_DAY;

        /* year */
        while(_stDate.u16Year > DEFAULT_YEAR)
        {
            _stDate.u16Year--;
            u32TotalSeconds += msAPI_OAD_GetDaysOfThisYear(_stDate.u16Year) * SECONDS_PER_DAY;
        }
    }

    return u32TotalSeconds;
}

static void msAPI_OAD_UntSchedule(MS_U8 *pSelector, UNT_DESCRIPTOR *untDescriptor)
{
	pSelector +=2;
    untDescriptor->untSchedule.u32StartTime      = msAPI_OAD_MJDUTC2Seconds( pSelector );    pSelector+=5;
    untDescriptor->untSchedule.u32EndTime        = msAPI_OAD_MJDUTC2Seconds( pSelector );    pSelector+=5;
    untDescriptor->untSchedule.u8FinalAvail      = (*pSelector & 0x80) >> 7;
    untDescriptor->untSchedule.u8PeriodFlag      = (*pSelector & 0x40) >> 6;
    untDescriptor->untSchedule.u8PeriodUnit      = (*pSelector & 0x30) >> 4;
    untDescriptor->untSchedule.u8DurationUnit    = (*pSelector & 0x0C) >> 2;
    untDescriptor->untSchedule.u8EstimateUnit    = (*pSelector & 0x03);   pSelector++;
    untDescriptor->untSchedule.u8Period          = *pSelector++;
    untDescriptor->untSchedule.u8Duration        = *pSelector++;
    untDescriptor->untSchedule.u8Estimate        = *pSelector++;

    OAD_DEBUG(printf("u32StartTime=%x\n",untDescriptor->untSchedule.u32StartTime)) ;
    OAD_DEBUG(printf("u32EndTime=%x\n",untDescriptor->untSchedule.u32EndTime)) ;
}

static void msAPI_OAD_UntLocation(MS_U8 *pSelector, UNT_DESCRIPTOR *untDescriptor)
{
    UINT16 data_broadcast_id;

    pSelector+=2;
    data_broadcast_id = GET_2BYTE( pSelector );     pSelector+=2;
    if (data_broadcast_id == DATA_BC_ID_SSU)
    {
        untDescriptor->untLocation.association_tag = GET_2BYTE( pSelector );   pSelector+=2;
        OAD_DEBUG(printf("association_tag=%x\n",untDescriptor->untLocation.association_tag)) ;
    }
}


OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessUNT( MS_U8 *section , UNT_DESCRIPTOR *untDescriptor)
{
    MS_U8 table_id, u8Tag;
    signed long section_length;
    MS_U16 common_desploop_length, compat_desplength, platform_length, target_desplength, operal_desplength;
    MS_U16 u16TotalParseLength, u16DescriptorLength;
    MS_U8 *pu8Descriptor;
	MS_U32  ouiData;
    MS_BOOL foundSchedule = 0 , foundLocation = 0 ;

    table_id = *section++;
    section_length = (signed long)((UINT16)GET_2BYTE( section ) & 0x0FFF);   section+=2;

    if (section_length < 9)
    {
        OAD_ASSERT( printf("UNT Header length\n") );
        return OAD_FAIL;
    }

	section += 5;   section_length -= 5;
	ouiData	= GET_3BYTE( section );
	if(ouiData != GET_3BYTE(g_OAD_OUI))
	{
        OAD_ASSERT( printf("OUI error\n") );
		return OAD_FAIL;
	}
	section += 4;	 section_length -= 4;

    // common_descriptor_loop()
    common_desploop_length = ((UINT16)GET_2BYTE( section ) & 0x0FFF);
    if (section_length < common_desploop_length + 2)
    {
        OAD_ASSERT( printf("UNT common length\n") );
        return OAD_FAIL;
    }
    section += common_desploop_length + 2;    section_length -= (common_desploop_length + 2);

    // compatibilityDescriptor()
    compat_desplength = GET_2BYTE( section );
    if (section_length < compat_desplength + 2)
    {
        OAD_ASSERT( printf("UNT compat length\n") );
        return OAD_FAIL;
    }
	if ((msAPI_OAD_VersionCheck!=NULL)&&!(*msAPI_OAD_VersionCheck)(DATA_BC_ID_SSU,section)) // check version
	{
		return OAD_FAIL;
	}
    section += compat_desplength + 2;    section_length -= (compat_desplength + 2);

    // Platform
    platform_length = GET_2BYTE( section );
    if (section_length < platform_length + 2)
    {
        OAD_ASSERT( printf("UNT platform length\n") );
        return OAD_FAIL;
    }
    section += 2;    section_length -= 2;

    // Target Descriptor
    target_desplength = ((UINT16)GET_2BYTE( section ) & 0x0FFF);
    if (section_length < target_desplength + 2)
    {
        OAD_ASSERT( printf("UNT platform length\n") );
        return OAD_FAIL;
    }
    section += target_desplength + 2;    section_length -= (target_desplength + 2);

    // Operational Descriptor
    operal_desplength = ((UINT16)GET_2BYTE( section ) & 0x0FFF);
    if (section_length < operal_desplength + 2)
    {
        OAD_ASSERT( printf("UNT platform length\n") );
        return OAD_FAIL;
    }
    section += 2;    section_length -= 2;

    u16TotalParseLength = 0;
    pu8Descriptor = section;
    while(u16TotalParseLength < operal_desplength)
    {
        u8Tag = pu8Descriptor[0];   //descripter Tag
        switch(u8Tag)
        {
            case UNT_TAG_SCHED:
            {
               msAPI_OAD_UntSchedule(pu8Descriptor,untDescriptor);
               foundSchedule = 1 ;
            }
            break;

            case UNT_TAG_SSULA:
            {
                msAPI_OAD_UntLocation(pu8Descriptor,untDescriptor);
                foundLocation = 1 ;
            }
            break;

            default:
            break;
        }

        /* move to next descriptor */
        u16DescriptorLength = pu8Descriptor[1] + 2;
        u16TotalParseLength += u16DescriptorLength;
        pu8Descriptor += u16DescriptorLength;
    }

    if (foundLocation&&foundSchedule) return OAD_SUCCEED ;
    else return OAD_FAIL ;

}

OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessDSI( MS_U8 *section )
{
    MS_U16  section_length;

    // DSM MSG header
    MS_U32  trans_id;
    MS_U8  adaptLength;
    MS_U16  messageLength;

    //MS_U16 descriptorCount,model, version,i;
    //MS_U8  descriptorType, descriptorLength, specifierType ,subDescriptorCount;
    //MS_U32 specifierData;
    MS_U16  numberOfGroups ,privateDataLength ,gCount, compatibilityLength;
    MS_U32  groupId, groupSize;
    MS_U16  groupInfoLength;
    OAD_STATUS_REPORT_TYPE retValue ;
    MS_U8  *ptr;
    MS_U16  messageId;

    ptr = section + SECTION_HEADER_SIZE + 2;
    messageId = GET_2BYTE(ptr);

    if (messageId!=OAD_DSMCC_MSGID_DSI)
    {
        OAD_ASSERT(printf("Not DSI => messageId=%x\n",messageId)) ;
        return OAD_FAIL;
    }

    section_length = SECTION_LENGTH( section );
    versionNum = (0x3e&section[5]) >> 1 ;
    section += SECTION_HEADER_SIZE;

    if ( section_length <= SECTION_HEADER_SIZE + DSMMSG_HEADER_SIZE + DSIMSG_HEADER_SIZE )
    {
        OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDSI : dsmcc_section_length = 0x%x\n", section_length) );
        return OAD_FAIL;
    }

    // DSM MSG Header
    section += 4;   // protocolDiscriminator, dsmccType, messageId pass

    trans_id = GET_4BYTE( section );

    section += 5;   // trans_id, reserved pass

    adaptLength = *section++;
    messageLength = GET_2BYTE( section ); section += 2;

    section += adaptLength;


    // DSI Payload
    section += 20;  //serverId pass

    compatibilityLength = GET_2BYTE( section ); section += 2;
    section += compatibilityLength;

    privateDataLength = GET_2BYTE( section ); section += 2;

    if ( privateDataLength < 2 )
    {
        OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDSI : privateDataLength = 0x%x\n", privateDataLength) );
        return OAD_FAIL;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Here is privateDataByte
    ////////////////////////////////////////////////////////////////////////////
    // ServiceGatewayInfo() - UK Spec
    if ( section[4] == 's' && section[5] == 'r' && section[6] == 'g' && section[7] == 0x00 )
    {
        BIOP_USERINFO_MIS misinfo;

        OAD_DEBUG(printf("msAPI_OAD_ProcessDSI>> OAD_MODE_OBJCAR\n"));

        OAD_Mode = OAD_MODE_OBJCAR;
        process_biop_service_gateway_info(section);
        process_userinfo_GetMISInfo(&misinfo);
        g_OAD_MISVersionId = misinfo.version_id;

        OAD_DEBUG(printf("manufacturer_id>> TS = %lX, TV = %lX\n", misinfo.manufacturer_id, (MS_U32)GET_3BYTE(g_OAD_OUI)));
        if ( misinfo.manufacturer_id == GET_3BYTE(g_OAD_OUI) )
        {
            process_serviceGateway_IOR_Get(&OAD_DSI_IOR);

            if ((msAPI_OAD_VersionCheck!=NULL)&&(*msAPI_OAD_VersionCheck)(DATA_BC_ID_UK_EC,misinfo.reserved)) // check version
            {
                OAD_ModInfo.groupId = process_profile_Body_GetTransID();
                return OAD_SUCCEED;
            }
            else
            {
                return OAD_FAIL;
            }
        }
        else return OAD_FAIL;
    }
    else
    {
        OAD_DEBUG(printf("msAPI_OAD_ProcessDSI>> OAD_MODE_DATACAR\n"));

        // GroupInfoIndication() - SSU Spec
        OAD_Mode = OAD_MODE_DATACAR;
        numberOfGroups = GET_2BYTE( section ); section += 2;

        for ( gCount = 0; gCount < numberOfGroups; gCount++ )
        {
            groupId     = GET_4BYTE( section ); section += 4;
            groupSize   = GET_4BYTE( section ); section += 4;

            // GroupCompatibility()
            compatibilityLength = GET_2BYTE( section );
            if ((msAPI_OAD_VersionCheck!=NULL)&&(*msAPI_OAD_VersionCheck)(DATA_BC_ID_SSU,section)) // check version
            {
               OAD_ModInfo.groupId = groupId;
               retValue = OAD_SUCCEED;
               break ;
            }
            else
            {
                retValue = OAD_FAIL;
            }

            section += (2+compatibilityLength) ;

            // GroupInfoLength
            groupInfoLength = GET_2BYTE( section ); section += 2;
            section += groupInfoLength;

            // privateDataLength
            privateDataLength = GET_2BYTE( section ); section += 2;
            section += privateDataLength;
        }
    }
    return retValue;
}


OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessDII( MS_U8 *section )
{
    MS_U16  section_length;

    // DSM MSG header
    MS_U32  trans_id;
    MS_U8  adaptLength;
    MS_U16  messageLength;

    // DII MSG header
    MS_U32  downloadId;
    MS_U16  blockSize;
    MS_U16  compatibilityLength;
    MS_U16  numberOfModules;

    // DII MSG body
    MS_U16  moduleId;
    MS_U32  moduleSz;
    MS_U8  moduleVer;
    MS_U8  moduleInfoLength;

    section_length = SECTION_LENGTH( section );
    section += SECTION_HEADER_SIZE;

    if ( section_length <= SECTION_HEADER_SIZE + DSMMSG_HEADER_SIZE + DIIMSG_HEADER_SIZE )
    {
        OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDII : dsmcc_section_length = 0x%x\n", section_length) );
        return OAD_FAIL;
    }

    // DSM MSG Header
    section += 4;   // protocolDiscriminator, dsmccType, messageId pass

    trans_id = GET_4BYTE( section);
    OAD_DEBUG(printf("DII Trans_ID: 0x%08LX; GroipID: 0x%08LX\n", trans_id, OAD_ModInfo.groupId));

    if ( trans_id != OAD_ModInfo.groupId )
    {
        OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDII : DII transactionId = 0x%lx, DSI groupId = 0x%lx\n", trans_id, OAD_ModInfo.groupId) );
#if(!CONFIG_SDTT_OAD)	
     return OAD_FAIL;
#endif
    }
		
    section += 5;   // trans_id, reserved pass

    adaptLength = *section++;
    messageLength = GET_2BYTE( section ); section += 2;

    section += adaptLength;


    // DII Payload
    downloadId = GET_4BYTE( section ); section += 4;
    blockSize = GET_2BYTE( section ); section += 2;
    OAD_DEBUG(printf("\nDII DownloadID: 0x%08LX ; BlockSize: 0x%04X", downloadId, blockSize));

    if ( ( !blockSize ) || ( blockSize > 4066 ) )
    {
        OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDII : invalid block size = %d\n", blockSize) );
        return OAD_FAIL;
    }

    if ( ( OAD_Mode == OAD_MODE_OBJCAR ) && ( downloadId != OAD_DSI_IOR.carousel_id ) )
    {
        OAD_ASSERT( printf("Error> Invalid downloadID: %x ; carousel_id: %x\n", (unsigned int)downloadId , (unsigned int)OAD_DSI_IOR.carousel_id) );
        return OAD_FAIL;
    }

    section += 10; // windowSize, ackPeriod, tCDownloadWindow, tCDownloadScenario pass

    compatibilityLength = GET_2BYTE( section ); section += 2;
    section += compatibilityLength;


    numberOfModules = GET_2BYTE( section ); section += 2;
    OAD_DEBUG(printf("Number of Mudule: 0x%04X\n", numberOfModules));

    if ( OAD_Mode == OAD_MODE_OBJCAR )
    {
        // Support Multiple ModuleID
        MS_U8 i;
        MS_BOOL bFoundModuleID;

        if ( pOAD_ModInfos == NULL )
        {
            pOAD_ModInfos = (OAD_MODULE *) msAPI_Memory_Allocate(numberOfModules * sizeof(OAD_MODULE), BUF_ID_OAD_DOWNLOAD);
            OAD_ModInfos_Size = numberOfModules;
        }

        bFoundModuleID = FALSE;
        for (i=0; i< numberOfModules; i++)
        {
            moduleId = GET_2BYTE( section ); section += 2;
            moduleSz = GET_4BYTE( section ); section += 4;
            moduleVer  = *section++;
            moduleInfoLength = *section++;
            section += moduleInfoLength;

            pOAD_ModInfos[i].totBlocks   = ( moduleSz + blockSize - 1 ) / blockSize;
            pOAD_ModInfos[i].rcvBlocks   = 0;

            pOAD_ModInfos[i].chkarraycnt = ( pOAD_ModInfos[i].totBlocks + 31 ) / 32;
            if((pOAD_BlkChkBuffer == NULL) || (g_u32OAD_BlkChkBufferLen < (pOAD_ModInfos[i].chkarraycnt * sizeof( MS_U32 ))))
            {
                if(g_u32OAD_BlkChkBufferLen > 0)
                    free((void*)pOAD_BlkChkBuffer);
                g_u32OAD_BlkChkBufferLen = pOAD_ModInfos[i].chkarraycnt * sizeof( MS_U32 );
                pOAD_BlkChkBuffer = (MS_U32*)malloc(g_u32OAD_BlkChkBufferLen);
                if(pOAD_BlkChkBuffer == NULL)
                {
                    pOAD_BlkChkBuffer = ( MS_U32 * ) OAD_BlkChkBuffer;
                    g_u32OAD_BlkChkBufferLen = 0;
                }
            }
            pOAD_ModInfos[i].blkchkbits  = ( MS_U32 * ) pOAD_BlkChkBuffer;
            memset(pOAD_ModInfos[i].blkchkbits, 0, pOAD_ModInfos[i].chkarraycnt * sizeof(MS_U32));

            pOAD_ModInfos[i].downloadId  = downloadId;
            pOAD_ModInfos[i].blockSize   = blockSize;

            pOAD_ModInfos[i].moduleId    = moduleId;
            pOAD_ModInfos[i].moduleSz    = moduleSz;
            pOAD_ModInfos[i].version     = moduleVer;

            pOAD_ModInfos[i].moduleData  = OAD_INVALID_ADDR;

            if ( moduleId == OAD_DSI_IOR.module_id )
            {
                bFoundModuleID = TRUE;
                OAD_ModInfo = pOAD_ModInfos[i];
                OAD_DEBUG(printf("Find the Match ModuleID: %u\n", moduleId));
            }
        }

        if (bFoundModuleID == FALSE)
        {
            if ( pOAD_ModInfos != NULL )
            {
                msAPI_Memory_Free(pOAD_ModInfos, BUF_ID_OAD_DOWNLOAD);
                pOAD_ModInfos = NULL;
                OAD_ModInfos_Size = 0;
            }
            return OAD_FAIL;
        }
        else return OAD_SUCCEED ;
    }
    else if ( OAD_Mode == OAD_MODE_DATACAR )
    {
        if ( numberOfModules > 1 )
        {
            OAD_ASSERT( printf("Warning> msAPI_OAD_ProcessDII : invalid numberOfModules = %d\n", numberOfModules) );
            return OAD_FAIL;
        }

        OAD_DEBUG( printf("DII has %d modules, with blockSize %d\n", numberOfModules, blockSize) );

        moduleId    = GET_2BYTE( section ); section += 2;
        moduleSz    = GET_4BYTE( section ); section += 4;
        moduleVer   = *section++;

        OAD_ModInfo.totBlocks   = ( moduleSz + blockSize - 1 ) / blockSize;
        OAD_ModInfo.rcvBlocks   = 0;

        OAD_ModInfo.chkarraycnt = ( OAD_ModInfo.totBlocks + 31 ) / 32;
        if((pOAD_BlkChkBuffer == NULL) || (g_u32OAD_BlkChkBufferLen < (OAD_ModInfo.chkarraycnt * sizeof( MS_U32 ))))
        {
            if(g_u32OAD_BlkChkBufferLen > 0)
                free((void*)pOAD_BlkChkBuffer);
            g_u32OAD_BlkChkBufferLen = OAD_ModInfo.chkarraycnt * sizeof( MS_U32 );
            pOAD_BlkChkBuffer = (MS_U32*)malloc(g_u32OAD_BlkChkBufferLen);
            if(pOAD_BlkChkBuffer == NULL)
            {
                pOAD_BlkChkBuffer = ( MS_U32 * ) OAD_BlkChkBuffer;
                g_u32OAD_BlkChkBufferLen = 0;
            }
        }
        OAD_ModInfo.blkchkbits  = ( MS_U32 * ) pOAD_BlkChkBuffer;
        memset( OAD_ModInfo.blkchkbits, 0, OAD_ModInfo.chkarraycnt * sizeof( MS_U32 ) );

        OAD_ModInfo.downloadId  = downloadId;
        OAD_ModInfo.blockSize   = blockSize;

        OAD_ModInfo.moduleId    = moduleId;
        OAD_ModInfo.moduleSz    = moduleSz;
        OAD_ModInfo.version     = moduleVer;
        OAD_ModInfo.moduleData  = OAD_INVALID_ADDR;
        return OAD_SUCCEED;
    }
    else
    {
        return OAD_FAIL;
    }

    OAD_DEBUG( printf("NEW_M: Did=0x%lx, Mid=0x%04x, Mver=0x%02bx, Msize=%ld, blksz=%d totblkcnt=%d\n",
        downloadId, moduleId, moduleVer, moduleSz, blockSize, OAD_ModInfo.totBlocks ) );
}

OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessDDB(MS_U8 *section,MS_U16 *blockID,MS_U16 *msgLen,MS_U32 *msgAddr,MS_U16 *msgType)
{
    MS_U16  section_length;

    // DSM MSG header
    MS_U32  downloadId;
    MS_U8  adaptLength;
    MS_U16  messageLength;

    // DDB MSG header
    MS_U16  moduleId;
    MS_U8  moduleVer;
    MS_U16  blockNumber;

    OAD_STATUS_REPORT_TYPE retValue = OAD_FAIL;

    section_length = SECTION_LENGTH( section );
    section += SECTION_HEADER_SIZE;

    if ( section_length <= SECTION_HEADER_SIZE + DSMMSG_HEADER_SIZE + DDBMSG_HEADER_SIZE )
    {
        OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDDB : dsmcc_section_length = 0x%x\n", section_length) );
        goto msAPI_OAD_ProcessDDB_Fail;
    }

    // DSM Download Data Header
    OAD_DEBUG(printf("protocolDiscriminator = 0x%02X\n", *(section+0)));
    OAD_DEBUG(printf("dsmccType = 0x%02X\n", *(section+1)));
    OAD_DEBUG(printf("messageId = 0x%04X\n", GET_2BYTE((section+2))));
    section += 4;   // protocolDiscriminator, dsmccType, messageId pass

    downloadId = GET_4BYTE( section );
    OAD_DEBUG(printf("DDB downloadId: 0x%08LX\n", downloadId));

    section += 5;   // downloadId, reserved pass

    adaptLength = *section++;
    messageLength = GET_2BYTE( section ); section += 2;

    section += adaptLength;

    // DDB Payload
    moduleId = GET_2BYTE( section ); section += 2;
    moduleVer = *section++;
    section++;      // reserved pass
    blockNumber = GET_2BYTE( section ); section += 2;

    if (( OAD_ModInfo.downloadId != downloadId ) ||
        ( OAD_ModInfo.moduleId != moduleId ) ||
        ( OAD_ModInfo.version != moduleVer ) ||
        ( OAD_ModInfo.totBlocks == OAD_ModInfo.rcvBlocks ) ||
        ( OAD_ModInfo.totBlocks <= blockNumber ) )
    {
        OAD_DEBUG(printf("Invalid DDB - Did=0x%lx(0x%lx), Mid=0x%x(0x%x), Mver=0x%02bx(0x%02bx), BlkNo=0x%x(0x%x/0x%x)\n",
                  OAD_ModInfo.downloadId, downloadId, OAD_ModInfo.moduleId, moduleId, OAD_ModInfo.version, moduleVer,
                  blockNumber, OAD_ModInfo.rcvBlocks, OAD_ModInfo.totBlocks) );
        return OAD_FAIL;
    }

    *blockID = 0 ;
    *msgLen = 0 ;

    if (!_ISRCVDBLOCK(blockNumber))
    {
        MS_U8  *pSrc;
        MS_U16  msgSize = messageLength - adaptLength - 6;

        _SETNEWBLOCK( blockNumber );

        pSrc = section;

        if ((OAD_Mode==OAD_MODE_OBJCAR))
        {
           if (OAD_ModInfo.moduleId==OAD_FILE_IOR.module_id)
           {
              if (blockNumber==0)
              {
                 pSrc += BIOP_HEADER_LEN ;
                 msgSize -= BIOP_HEADER_LEN ;
              }
              *msgLen = msgSize ;
           }
        }
        else if (OAD_Mode==OAD_MODE_DATACAR)
        {
           *msgLen = msgSize ;
        }

        *blockID = blockNumber ;
        *msgAddr = (MS_U32)pSrc ;
        *msgType = OAD_Mode ;

        //memcpy((MS_U8*)msAPI_OAD_GetDDBBufferAddr(),(MS_U8*)pSrc,msgSize) ;

        OAD_ModInfo.rcvBlocks++;

        OAD_INFO( printf("MID=0x%x, BNO=%u[%u/%u]\n", OAD_ModInfo.moduleId, blockNumber, OAD_ModInfo.rcvBlocks, OAD_ModInfo.totBlocks) );

        if ((OAD_ModInfo.totBlocks == OAD_ModInfo.rcvBlocks )&&(OAD_ModInfo.totBlocks != 0))
        {
            //OAD_DEBUG( printf("[OAD] MODULE Complete[0x%x] Size=%ld\n", OAD_ModInfo.moduleId, moduleSz) );

            if ( OAD_Mode == OAD_MODE_OBJCAR )
            {
                MS_U8 Buf[4];
                MS_U32 dstaddr;

                if (OAD_ModInfo.moduleId == OAD_DSI_IOR.module_id)
                {
                   dstaddr = (MS_U32)Buf;
                   memcpy((MS_U8*)(dstaddr),(MS_U8*)(*msgAddr),(MS_U32)(BIOP_MAGIC_LEN)) ;
                   if ( strncmp((const char *)(Buf), BIOP_MAGIC_STR, BIOP_MAGIC_LEN) != 0 )
                   {
                       goto msAPI_OAD_ProcessDDB_Fail;
                   }

                   if (process_biop(*msgAddr, (MS_U32)(OAD_ModInfo.moduleSz), SDRAM_TYPE))
                   {
                      MS_U8 i = 0;

                      for (i=0; i<OAD_ModInfos_Size; i++)
                      {
                          if ( pOAD_ModInfos[i].moduleId == OAD_FILE_IOR.module_id )
                          {
                              OAD_ModInfo = pOAD_ModInfos[i];
                              if((pOAD_BlkChkBuffer == NULL) || (g_u32OAD_BlkChkBufferLen < (OAD_ModInfo.chkarraycnt * sizeof( MS_U32 ))))
                              {
                                  if(g_u32OAD_BlkChkBufferLen > 0)
                                      free((void*)pOAD_BlkChkBuffer);
                                  g_u32OAD_BlkChkBufferLen = OAD_ModInfo.chkarraycnt * sizeof( MS_U32 );
                                  pOAD_BlkChkBuffer = (MS_U32*)malloc(g_u32OAD_BlkChkBufferLen);
                                  if(pOAD_BlkChkBuffer == NULL)
                                  {
                                      pOAD_BlkChkBuffer = ( MS_U32 * ) OAD_BlkChkBuffer;
                                      g_u32OAD_BlkChkBufferLen = 0;
                                  }
                              }
                              OAD_ModInfo.blkchkbits  = ( MS_U32 * ) pOAD_BlkChkBuffer;
                              memset(OAD_ModInfo.blkchkbits, 0, OAD_ModInfo.chkarraycnt * sizeof(MS_U32));
                              retValue = OAD_CONTINUE;
                              break;
                          }
                      }
                   }
                   else
                   {
                      goto msAPI_OAD_ProcessDDB_Fail;
                   }
                }
                else if (OAD_ModInfo.moduleId == OAD_FILE_IOR.module_id)
                {
                    retValue = OAD_COMPLETE;
                }
            }
            else if ( OAD_Mode == OAD_MODE_DATACAR )
            {
                retValue = OAD_COMPLETE;
            }
        }
        else
        {
           retValue = OAD_CONTINUE;
        }
    }
    else
    {
        retValue = OAD_CONTINUE;
        OAD_DEBUG( printf("OLD BLOCK: MID=0x%x, BNO=0x%x\n", moduleId, blockNumber) );
    }
    if(retValue == OAD_FAIL || retValue == OAD_COMPLETE)
    {
        _msAPI_OAD_ClearDynamicData();
    }
    return retValue ;
msAPI_OAD_ProcessDDB_Fail:
    return OAD_FAIL ;
}

MS_U8 msAPI_OAD_GetProgress( void )
{
    MS_U8  ret = 0;

    if ( OAD_ModInfo.totBlocks )
    {
        ret = 100 * (float)OAD_ModInfo.rcvBlocks / OAD_ModInfo.totBlocks;
    }

    OAD_DEBUG( printf("OAD Progress %d/%d (%d%%)\n", OAD_ModInfo.rcvBlocks, OAD_ModInfo.totBlocks, ret) );

    return ret;
}

void msAPI_OAD_GetModuleInfo( MS_U32 *startAddr, MS_U32 *moduleSize )
{
    *startAddr  = OAD_ModInfo.moduleData;
    *moduleSize = OAD_ModInfo.moduleSz;
}

MS_U32 msAPI_OAD_GetMISVersionId( void )
{
    OAD_DEBUG( printf("OAD g_OAD_MISVersionId 0x%08X\n", g_OAD_MISVersionId) );

    return g_OAD_MISVersionId;
}

void msAPI_OAD_ClearData( void )
{
    _msAPI_OAD_ClearDynamicData();
    memset( &OAD_OUI_DIR_IOR, 0, sizeof( OAD_OUI_DIR_IOR ) );
    memset( &OAD_FILE_IOR, 0, sizeof( OAD_FILE_IOR ) );
    memset( &OAD_ModInfo, 0, sizeof( OAD_MODULE ) );

    OAD_ModInfo.moduleData  = OAD_INVALID_ADDR;
    OAD_Mode                = OAD_MODE_INVALID;
    g_OAD_MISVersionId      = 0;
}

MS_U8 msAPI_OAD_GetOADMode(void)
{
    return OAD_Mode;
}

#if(CONFIG_SDTT_OAD)
void msAPI_OAD_SetOADMode(MS_U8 mode)
{
     OAD_Mode =  mode;
}

void msAPI_Set_SDTT_OAD(MS_BOOL value)
{
	bIsSDTT_OAD = value;
}
#endif

void msAPI_OAD_SetOADFileFound(MS_BOOL bFound)
{
    OAD_DEBUG(printf("msAPI_OAD_SetOADFileFound: %bu\n", bFound));
    bIsOADFileFound = bFound;
}

MS_BOOL msAPI_OAD_IsOADFileFound(void)
{
    OAD_DEBUG(printf("msAPI_OAD_IsOADFileFound: %bu\n", bIsOADFileFound));
    return bIsOADFileFound;
}

MS_BOOL msAPI_OAD_GetLibVer(const MSIF_Version **ppVersion)
{
    if (!ppVersion)
    {
        return false;
    }

    *ppVersion = &_mw_oad_version;

    return true ;
}
MS_U32 msAPI_OAD_GetBlockSize(void)
{
    return OAD_ModInfo.blockSize;
}

MS_U32 msAPI_OAD_GetDownloadId(void)
{
    return OAD_ModInfo.downloadId;
}

MS_U32 msAPI_OAD_GetGroupId(void)
{
    return OAD_ModInfo.groupId;
}

#else //(!ENABLE_OAD)
void msAPI_OAD_DummyPrint( void )
{
    //This dummy function is just used to pass compiler.
    printf("\n");
}
#endif //(!ENABLE_OAD)

#undef _MSAPI_OAD_PROCESS_C_
#endif //_MSAPI_OAD_PROCESS_C_

