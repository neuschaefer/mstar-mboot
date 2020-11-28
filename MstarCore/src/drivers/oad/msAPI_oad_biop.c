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
#define _MSAPI_OAD_BIOP_C_

/******************************************************************************/
/*                       Header Files                                         */
/******************************************************************************/

// C Library
#include <common.h>
#include <MsTypes.h>
#include <asm/string.h>
#include <linux/string.h>
#define xdata
#include "msAPI_Memory.h"

extern int strcmp(const char *,const char *);

#include "msAPI_oad_process.h"
#include "msAPI_oad_biop.h"

//To add ASSERT statements
#ifndef __ASSERT
#define __ASSERT(expr) (void)((expr) || printf("%s %d\n", __FILE__, __LINE__));
#endif

#define OBJECT_KEY_MAX_LENGTH   10

static BIOP_USERINFO_MIS        MIS_Info;
static struct biop_iop_ior      sg_ior;
static MS_U32                      DSI_OC_Transaction_id;
static MS_U8                       u8ObjKeyLength = 0;
static MS_U8                       u8ObjKey[OBJECT_KEY_MAX_LENGTH] = {0};
static BIOP_FILE_INFO           FileInfo;
//static MS_U8 code                  ZipArea[3800];

extern MS_U8 g_OAD_OUI[3];
extern MS_U8 OAD_OUI_ASCII[7];
extern BIOP_BODY_PROFILE_IOR_INFO  OAD_OUI_DIR_IOR;
extern BIOP_BODY_PROFILE_IOR_INFO  OAD_FILE_IOR;

/******************************************************************************/
MS_U32 process_service_domain( MS_U32 Addr, MS_U8 DataType );
MS_U32 process_iop_ior( MS_U8 byte_order, MS_U32 Addr, struct biop_iop_ior *ior, MS_U8 DataType );
MS_U32 process_service_context_list( MS_U32 Addr, MS_U8 DataType );
void process_biop_dir( MS_U8 byte_order, MS_U32 Addr, MS_U8 DataType) ;


/******************************************************************************/
MS_U8 biop_uint08( MS_U32 Addr, MS_U8 DataType )
{
    MS_U8  *p;
    MS_U8  Buf[1];
    MS_U32 dstaddr= 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(1), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)1) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)1) ;
    }

    p = (MS_U8 xdata *)dstaddr;

    return *p;
}

/*
 * convert to the correct byte order
 */
MS_U16 biop_uint16( MS_U8 byte_order, MS_U32 Addr, MS_U8 DataType )
{
    MS_U8  *p;
    MS_U16 val;
    MS_U8  Buf[2];
    MS_U32 dstaddr= 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(2), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)2) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)2) ;
    }

    p = (MS_U8 xdata *)(dstaddr);

    if(byte_order == BIOP_BIGENDIAN)
        val = (p[0] << 8) + p[1];
    else
        val = (p[1] << 8) + p[0];

    return val;
}


MS_U32 biop_uint32( MS_U8 byte_order, MS_U32 Addr, MS_U8 DataType )
{
    MS_U8  *p;
    MS_U32 val;
    MS_U8  Buf[4];
    MS_U32 dstaddr= 0, temp1= 0, temp2= 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(4), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)4) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)4) ;
    }

    p = (MS_U8 xdata *)(dstaddr);
    val = 0;

    if ( byte_order == BIOP_BIGENDIAN )
    {
        temp1 = (p[2] << 8) + p[3];
        temp2 = (p[0] << 8) + p[1];
        val = ((MS_U32)temp2 <<16) + ((MS_U32)temp1);
    }
    else
    {
        temp1 = (p[1] << 8) + p[0];
        temp2 = (p[3] << 8) + p[2];
        val = ((MS_U32)temp2 <<16) + ((MS_U32)temp1);
    }

    return val;
}

/*
 * returns the number of bytes including the size field
 */
MS_U32 biop_sequence255( MS_U32 Addr, struct biop_sequence *out, MS_U8 DataType )
{
    MS_U8  *p;
    MS_U8  Buf[1];
    MS_U32 dstaddr = 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(1), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)1) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)1) ;
    }

    p = (MS_U8 xdata *)dstaddr;

    out->size       = (MS_U32)(*p);
    out->data_p     = (MS_U32)(Addr + 1);

    return 1 + out->size;
}

/*
 * returns the number of bytes including the size field
 */

MS_U32 biop_sequence65535( MS_U8 byte_order, MS_U32 Addr, struct biop_sequence *out, MS_U8 DataType )
{
    MS_U8  Buf[2];
    MS_U32 dstaddr= 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(2), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)2) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)2) ;
    }

    out->size       = (MS_U32)biop_uint16( byte_order, dstaddr, DataType );
    out->data_p     = (MS_U32)(Addr + 2);

    return 2 + out->size;
}

/*
 * returns the number of bytes including the size field
 */

MS_U32 biop_sequence( MS_U8 byte_order, MS_U32 Addr, struct biop_sequence *out, MS_U8 DataType )
{
    MS_U8  Buf[4];
    MS_U32 dstaddr = 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(4), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)4) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)4) ;
    }

    out->size       = (MS_U32)biop_uint32(byte_order, dstaddr, DataType);
    out->data_p     = (MS_U32)(Addr + 4);

    return 4 + out->size;
}

/*
 * returns the number of bytes needed to round size upto the next 4 byte boundary
 */
MS_U32 biop_align32( MS_U32 size )
{
    return (size % 4) != 0 ? (4 - (size % 4)) : 0;
}

void biop_MessageHeader(MS_U32 Addr, struct BIOPMessageHeader *header, MS_U8 DataType)
{
    MS_U8      *p;
    MS_U32     dstaddr= 0, size= 0;
    MS_U8      Buf[12];

    size = sizeof(struct BIOPMessageHeader);

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        dstaddr = (MS_U32)Buf;
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(dstaddr), (MS_U32)(size), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)size) ;
        memcpy((MS_U8*)dstaddr,(MS_U8*)Addr,(MS_U32)size) ;
    }

    p = (MS_U8 xdata *)(dstaddr);
    memcpy(header->magic, p, 4);

    dstaddr += 4;
    header->biop_version.u8major  = biop_uint08((MS_U32)(dstaddr), SDRAM_TYPE); dstaddr+=1;
    header->biop_version.u8minor  = biop_uint08((MS_U32)(dstaddr), SDRAM_TYPE); dstaddr+=1;
    header->byte_order          = biop_uint08((MS_U32)(dstaddr), SDRAM_TYPE); dstaddr+=1;
    header->message_type        = biop_uint08((MS_U32)(dstaddr), SDRAM_TYPE); dstaddr+=1;
    header->message_size        = biop_uint32(header->byte_order, (MS_U32)(dstaddr), SDRAM_TYPE); dstaddr+=4;

}

/*
* Copy Data from SDRAM or XDATA to XDATA
*/
void biop_rawdata( MS_U32 Addr, MS_U8 * Buf, MS_U8 len, MS_U8 DataType )
{
    MS_U32 dstaddr= 0;

    if ( DataType == XDATA_TYPE )
    {
        dstaddr = (MS_U16)(Addr);
        memcpy(Buf, (MS_U8 xdata *)dstaddr, (MS_U16)len);
    }
    else if ( DataType == SDRAM_TYPE )
    {
        //MApi_BDMA_Copy((MS_U32)(Addr), XD2PHY(Buf), (MS_U32)(len), MIU_SDRAM2SDRAM);
        //MDrv_BDMA_MemCopy((MS_MS_U32)Addr, (MS_MS_U32)dstaddr,(MS_MS_U32)len) ;
        memcpy((MS_U8*)Buf,(MS_U8*)Addr,(MS_U32)len) ;
    }
}

//=======================================================================================
//BIOP uses CORBA's Interoperable Object Reference. An object reference contains for each
//network location one Profile Body.
//(1)For an IOR that refers to an Object within the same broadcast Service Domain, the BIOP
//                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   Profile Body identifies the location of the BIOP message that conveys the Object data
//   and attributes. The BIOP Profile Body consists therefore of an ObjectLocation component
//                                                                  ~~~~~~~~~~~~~~
//   and a ConnBinder component.
//         ~~~~~~~~~~
//(2)For an IOR that refers to an object in another Service Domain the Lite Options Profile
//                                                                     ~~~~~~~~~~~~~~~~~~~~
//   Body is used. The Lite Options Profile Body uses a globally unique NSAP address to
//   ~~~~
//   identify the Service Domain which may be either Interactive or Broadcast.
//=======================================================================================

/*
 * process the DSM::Directory message body
 */

void process_biop_dir( MS_U8 byte_order, MS_U32 Addr, MS_U8 DataType )
{
    MS_U32 data_p, start;
    MS_U16 nbindings;
    MS_U16 i;
    MS_U8 nnames;
    MS_U8 j;
    struct biop_sequence name;
    struct biop_sequence kind;
    MS_U8 type;
    struct biop_iop_ior ior;
    struct biop_sequence info;
    MS_BOOL bFoundOUIDir = FALSE;
    MS_BOOL bFoundFile = FALSE;

    data_p = start = Addr;

    /*[01]get bindings_count ==========================================================*/
    nbindings = biop_uint16(byte_order, data_p, DataType);
    data_p += 2;
    OAD_BIOP_DBG(printf("binding_count: %u", nbindings));

    /*[02]process each binding ========================================================*/
    for(i=0; i<nbindings; i++)
    {
        /*[02-1]nameComponents_count ==================================================*/
        OAD_BIOP_DBG(printf(" binding %u", i));
        nnames = biop_uint08(data_p, DataType);
        data_p += 1;
        OAD_BIOP_DBG(printf(" nameComponents: %u", nnames));

        /* only expecting 1 name, so just use the last one */

        /*[02-2]nameComponent_id & nameComponent_kind =================================*/
        for(j=0; j<nnames; j++)
        {
            MS_U8 *pName, *pKind;

            data_p += biop_sequence255((MS_U32)data_p, &name, DataType);
            //OAD_BIOP_DBG(printf("  name %u: '%.*s'", j, name.size, name.data_p));
            data_p += biop_sequence255((MS_U32)data_p, &kind, DataType);
            //OAD_BIOP_DBG(printf("  kind %u: '%.*s'", j, kind.size, kind.data_p));

            pName = msAPI_Memory_Allocate(name.size+1, BUF_ID_OAD_DOWNLOAD);
            __ASSERT(pName);
            pKind = msAPI_Memory_Allocate(kind.size+1, BUF_ID_OAD_DOWNLOAD);
            __ASSERT(pKind);
            pName[name.size] = 0;
            pKind[kind.size] = 0;
            biop_rawdata(name.data_p, pName, name.size, DataType);

            biop_rawdata(kind.data_p, pKind, kind.size, DataType);

            #if 0
            //dump data for debugging
            {
                MS_U8 i;
                printf("pName:\n   ");
                for (i=0; i<name.size; i++)
                {
                    printf("0x%bx ", pName[i]);
                }
                printf("\n");
            }
            {
                MS_U8 i;
                printf("pKind:\n   ");
                for (i=0; i<kind.size; i++)
                {
                    printf("0x%bx ", pKind[i]);
                }
                printf("\n");
            }
            #endif

            if ( FALSE == OAD_OUI_DIR_IOR.b_valid )
            {
                // find OUI directory
                if ( (strcmp((const char *)pKind, (const char *)BIOP_DIR) == 0) && (strcmp((const char *)pName, (const char *)OAD_OUI_ASCII) == 0 ) )
                {
                    bFoundOUIDir = TRUE;
                }
            }
            else
            {
                // find File
                if ( (strcmp((char *)pKind, BIOP_FILE) == 0) )
                {
                    bFoundFile = TRUE;
                }
            }
            msAPI_Memory_Free(pName, BUF_ID_OAD_DOWNLOAD);
            msAPI_Memory_Free(pKind, BUF_ID_OAD_DOWNLOAD);
        }

        /*[02-3]bindingType ===========================================================*/
        type = biop_uint08(data_p, DataType);
        data_p += 1;
        OAD_BIOP_DBG(printf(" bindingType: %u", type));

        /*[02-4]IOP::IOR() (objectRef) ================================================*/
        OAD_BIOP_DBG(printf(" objectRef:"));
        data_p += process_iop_ior(byte_order, data_p, &ior, DataType);

        if ( (TRUE == bFoundOUIDir) || (TRUE == bFoundFile) )
        {
            u8ObjKeyLength = ior.key.size;

            if ( u8ObjKeyLength > OBJECT_KEY_MAX_LENGTH )
            {
                u8ObjKeyLength = OBJECT_KEY_MAX_LENGTH;
            }

            biop_rawdata(ior.key.data_p, u8ObjKey, u8ObjKeyLength, DataType);

            #if 0
            //dump data for debugging
            {
                MS_U8 i;
                printf("Key2:\n   ");
                for (i=0; i<u8ObjKeyLength; i++)
                {
                    printf("0x%bx ", u8ObjKey[i]);
                }
                printf("\n");
            }
            #endif

            if (TRUE == bFoundOUIDir)
            {
                OAD_BIOP_DBG(printf("bFoundOUIDir\n"));
                OAD_OUI_DIR_IOR.association_tag = ior.association_tag;
                OAD_OUI_DIR_IOR.carousel_id = ior.carousel_id;
                OAD_OUI_DIR_IOR.module_id = ior.module_id;
                OAD_OUI_DIR_IOR.b_valid = TRUE;
            }
            else if (TRUE == bFoundFile)
            {
                OAD_BIOP_DBG(printf("bFoundFile\n"));
                OAD_FILE_IOR.association_tag = ior.association_tag;
                OAD_FILE_IOR.carousel_id = ior.carousel_id;
                OAD_FILE_IOR.module_id = ior.module_id;
                OAD_FILE_IOR.b_valid = TRUE;
                msAPI_OAD_SetOADFileFound(TRUE);
            }
            break;
        }

        /*[02-5]check the object reference ============================================*/
        /* make sure we are downloading the PID with this file on */

        /*
         * is the PID on the MUX we are currently tuned to
         * some BBC apps have links to files on different MUXes
         * eg 'games' on BBC1
         */

        /*[02-6]make the object reference based on file system symbolic link ==========*/

        /*[02-7]objectInfo ============================================================*/
        data_p += biop_sequence65535(byte_order, data_p, &info, DataType);
        OAD_BIOP_DBG(printf(" objectInfo:"));
    }

    return;
}

MS_BOOL process_biop( MS_U32 Addr, MS_U32 size, MS_U8 DataType )
{
    MS_U32     bytes_left, msgheaderSize;
    MS_U32     data_p, start, subhdr;
    struct  BIOPMessageHeader msgheader;
    struct  biop_sequence key;
    struct  biop_sequence kind;
    struct  biop_sequence info;
    struct  biop_sequence body;
    struct  biop_sequence file;
    signed char      TypeID[4];
    MS_U8      ObjectKey[OBJECT_KEY_MAX_LENGTH];
    MS_BOOL retValue = TRUE ;

    data_p = start = Addr;
    msgheaderSize = sizeof(struct BIOPMessageHeader);

    OAD_BIOP_DBG(printf("Whole BIOP, size=%u ", size));

    /*
     * we may get 0, 1 or more BIOP messages in a single block
     * (Channel 4 sends us modules that uncompress to 0 bytes)
     */
    bytes_left = size;
    while(bytes_left != 0)
    {
        /*[01]check BIOP Message Headers or SubHeaders ================================*/
        biop_MessageHeader(data_p, &msgheader, DataType);

        if ( (bytes_left < msgheaderSize)
        || (strncmp(msgheader.magic, BIOP_MAGIC_STR, BIOP_MAGIC_LEN) != 0)
        || (msgheader.biop_version.u8major != BIOP_VSN_MAJOR)
        || (msgheader.biop_version.u8minor != BIOP_VSN_MINOR)
        || (msgheader.message_type != BIOP_MSG_TYPE)
          )
        {
            OAD_BIOP_ASSERT(printf("Invalid BIOP header"));
            retValue = FALSE ;
            break;
        }

        size = msgheader.message_size;

        if (bytes_left < (msgheaderSize + size))
        {
            OAD_BIOP_ASSERT(printf("Not enough BIOP data"));
            retValue = FALSE ;
            break;
        }

        /*[02]get object content ======================================================*/
        subhdr = data_p + msgheaderSize;

        /*[02-1]object key & object kind ==============================================*/
        subhdr += biop_sequence255(subhdr, &key, DataType);
        //printf("\nobjectKey-> Size: 0x%08LX ; Addr: 0x%08LX", key.size, key.data_p);

        subhdr += biop_sequence(msgheader.byte_order, subhdr, &kind, DataType);
        //printf("\nobjectKind-> Size: 0x%08LX ; Addr: 0x%08LX", kind.size, kind.data_p);

        biop_rawdata(key.data_p, ObjectKey, sizeof(ObjectKey), DataType);
        biop_rawdata(kind.data_p, (MS_U8*)TypeID, sizeof(TypeID), DataType);

        // match key
        if ( memcmp(ObjectKey, u8ObjKey, u8ObjKeyLength) != 0 )
        {
            /*[04] not matched, move onto the next ======================================================*/
            data_p += (msgheaderSize + size);
            bytes_left -= (msgheaderSize + size);
            OAD_BIOP_ASSERT(printf("Invalid ObjectKey"));
            retValue = FALSE ;
            continue;
        }
        else retValue = TRUE ;

        #if 0
        //dump data for debugging
        {
            MS_U8 i;
            printf("ObjectKey:\n   ");
            for (i=0; i<u8ObjKeyLength; i++)
            {
                printf("0x%bx ", ObjectKey[i]);
            }
            printf("\n");
        }
        #endif

        /*[02-2]only file & directory & service contain object info immediately =======*/
        if ( (strcmp((char *)TypeID, BIOP_STREAM) != 0) && (strcmp((char *)TypeID, BIOP_STREAMEVENT) != 0) )
        {
            subhdr += biop_sequence65535(msgheader.byte_order, subhdr, &info, DataType);
            //printf("\nobjectInfo:");
            subhdr += process_service_context_list(subhdr, DataType);
            //printf("\nserviceContextList:");
            subhdr += biop_sequence(msgheader.byte_order, subhdr, &body, DataType);
            //printf("\nmessageBody: %u bytes \n", body.size);
        }

        /*[03]decode the message body, based on the objectKind field ==================*/
        /*[03-1]BIOP::DirectoryMessage ================================================*/
        if ( strcmp((char *)TypeID, BIOP_DIR) == 0 )
        {
            /* a directory */
            OAD_BIOP_DBG(printf("<<DSM::Directory>>"));
            process_biop_dir(msgheader.byte_order, body.data_p, DataType);
        }
        /*[03-2]BIOP::ServiceGateway (the same with directory) ========================*/
        else if ( strcmp((char *)TypeID, BIOP_SERVICEGATEWAY) == 0 )
        {
            /* the service gateway is the root directory */
            OAD_BIOP_DBG(printf("<<DSM::ServiceGateway>>"));
            process_biop_dir(msgheader.byte_order, body.data_p, DataType);
        }
        /*[03-3]BIOP::FileMessage =====================================================*/
        else if ( strcmp((char *)TypeID, BIOP_FILE) == 0 )
        {
            /* a file */
            OAD_BIOP_DBG(printf("<<DSM::File>>"));
            (void) biop_sequence(msgheader.byte_order, body.data_p, &file, DataType);

            FileInfo.FileBufferAddr    = file.data_p;
            FileInfo.FileBufferSize    = file.size;
        }
        /*[03-4]BIOP::StreamMessage ===================================================*/
        else if ( strcmp((char *)TypeID, BIOP_STREAM) == 0 )
        {
            /* a stream */
            OAD_BIOP_DBG(printf("<<DSM::Stream>>"));
        }
        /*[03-5]BIOP::StreamEventMessage ==============================================*/
        else if ( strcmp((char *)TypeID, BIOP_STREAMEVENT) == 0 )
        {
            /* a stream event */
            OAD_BIOP_DBG(printf("<<BIOP::StreamEvent>>"));
        }
        /*[03-6]Non supported =========================================================*/
        else
        {
            OAD_BIOP_DBG(printf("Unknown BIOP object: '%.*s'\n", kind.size, kind.data_p));
        }

        /*[04]move onto the next ======================================================*/
        data_p += (msgheaderSize + size);
        bytes_left -= (msgheaderSize + size);
    }

    return retValue ;
}

MS_U32 process_service_domain( MS_U32 Addr, MS_U8 DataType )
{
    MS_U32  data_p, start;
    MS_U8   count;

    data_p = start = Addr;
    count = biop_uint08(data_p, DataType);
    data_p++;

    //AFI
    data_p++;
    //Type
    data_p++;
    //carouselId
    data_p+=4;
    //specifierType
    data_p++;
    //specifierData{IEEE OUI}
    data_p+=3;
    //transport_stream_id
    data_p+=2;
    //original_network_id
    data_p+=2;
    //service_id
    data_p+=2;
    //reserved
    data_p+=4;

    return (data_p-start);
}

/*
 * process an IOP::IOR data structure
 * stores the results in ior
 * returns the size in bytes
 */
MS_U32 process_iop_ior( MS_U8 byte_order, MS_U32 Addr, struct biop_iop_ior *ior, MS_U8 DataType )
{
    MS_U32 start, data_p;
    struct biop_sequence type;
    MS_U32 nprofiles;
    MS_U32 i,j;
    MS_U32 tag;
    struct biop_sequence profile;
    MS_U8 profile_bo;
    MS_U8 taps_count;
    MS_U32 transaction_id;
    MS_U32 timeout;
    MS_U16 association_tag;
    MS_U8 N4, N6;
    MS_U8 ncomponents;
    MS_U32 nameComponents_count;
    MS_U32 id_length;
    MS_U32 kind_length;
    MS_U32 initialContextLength;
    MS_U8 vsn_major, vsn_minor;

    data_p = start = Addr;

    /*[01]type_id =====================================================================*/
    /* typeId - "dir\0", "fil\0", etc */
    data_p += biop_sequence(byte_order, (MS_U32)data_p, &type, DataType);

    /*[02]taggedProfiles_count ========================================================*/
    nprofiles = biop_uint32(byte_order, (MS_U32)data_p, DataType);
    data_p += 4;

    OAD_BIOP_D1(printf("\nProfile: %08LX", nprofiles));

    /*[03]for each profile ============================================================*/
    for(i=0; i<nprofiles; i++)
    {
        OAD_BIOP_DBG(printf("   IOP::taggedProfile %u", i));

        /*[03-1]###profile header### ==================================================*/
        /*[03-1a]profileId_tag ========================================================*/
        tag = biop_uint32(byte_order, (MS_U32)data_p, DataType);

        data_p += 4;

        /*[03-1b]profile_data =========================================================*/
        data_p += biop_sequence(byte_order, (MS_U32)data_p, &profile, DataType);
        if(tag == TAG_BIOP)
        {
            OAD_BIOP_DBG(printf("   BIOPProfileBody:"));

            /*[03-1c]profile_data_p_byte_order ========================================*/
            profile_bo = biop_uint08(profile.data_p, DataType);
            OAD_BIOP_D1(printf("\nByteOrder: 0x%02bx", profile_bo));
            profile.data_p += 1;

            /*[03-1d]liteComponents_count =============================================*/
            ncomponents = biop_uint08(profile.data_p, DataType);
            OAD_BIOP_D1(printf("\nComponents: 0x%02bx", ncomponents));
            profile.data_p += 1;

            /*[03-2]###object location### =============================================*/
            /*[03-2a]BIOP::ObjectLocation =============================================*/
            if (biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType) != TAG_ObjectLocation)
                OAD_BIOP_ASSERT(printf("Expecting BIOP::ObjectLocation"));
            profile.data_p += 4;

            /*[03-2b]component_data_length ============================================*/
            /* component_data_length = *(profile.data_p); */
            OAD_BIOP_D1(printf("\nComponent Data Length: 0x%02bx", biop_uint08((MS_U32)profile.data_p, DataType)));
            profile.data_p += 1;

            /*[03-2c]carouselId =======================================================*/   //(1)===>Look Up DownloadInfoIndication
            ior->carousel_id = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
            OAD_BIOP_D1(printf("\nCar_ID: 0x%08LX", ior->carousel_id));
            profile.data_p += 4;

            /*[03-2d]moduleId =========================================================*/   //(2)===>Look Up DownloadInfoIndication
            ior->module_id = biop_uint16(profile_bo, (MS_U32)profile.data_p, DataType);
            OAD_BIOP_D1(printf("\nModule_ID: 0x%04X", ior->module_id));
            profile.data_p += 2;

            /*[03-2e]BIOP version =====================================================*/
            vsn_major = biop_uint08(profile.data_p, DataType);
            vsn_minor = biop_uint08((profile.data_p+1), DataType);
            if ( (vsn_major != BIOP_VSN_MAJOR) || (vsn_minor != BIOP_VSN_MINOR) )
                OAD_BIOP_ASSERT(printf("Expecting BIOP version 1.0"));

            profile.data_p += 2;

            /*[03-2f]objectKey ========================================================*/   //(3)===>Look Up DownloadInfoIndication
            profile.data_p += biop_sequence255((MS_U32)profile.data_p, &ior->key, DataType);

            /*[03-3]###ConnBinder### ==================================================*/
            /*[03-3a]DSM::ConnBinder: componentId_tag =================================*/
            if (biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType) != TAG_ConnBinder)
                OAD_BIOP_ASSERT(printf("Expecting DSM::ConnBinder"));

            profile.data_p += 4;
            OAD_BIOP_DBG(printf("    DSM::ConnBinder"));

            /*[03-3b]component_data_length ============================================*/
            /* component_data_length = *profile.data_p */
            profile.data_p += 1;

            /*[03-4]###tap I### =======================================================*/
            /*[03-4a]taps_count =======================================================*/
            taps_count = biop_uint08(profile.data_p, DataType);
            profile.data_p += 1;

            if(taps_count > 0)
            {
                /*[03-4b]id ===========================================================*/
                /* id MS_U16 */
                profile.data_p += 2;

                /*[03-4c]use ==========================================================*/
                if (biop_uint16(profile_bo, (MS_U32)profile.data_p, DataType) != BIOP_DELIVERY_PARA_USE)
                    OAD_BIOP_ASSERT(printf("Expecting BIOP_DELIVERY_PARA_USE"));
                profile.data_p += 2;

                /*[03-4d]association_tag ==============================================*/   //(1)===>Look Up PMT
                ior->association_tag = biop_uint16(profile_bo, (MS_U32)profile.data_p, DataType);
                OAD_BIOP_D1(printf("\nAss_Tag: 0x%04X", ior->association_tag));
                profile.data_p += 2;

                /*[03-4e]selector_length ==============================================*/
                if (biop_uint08(profile.data_p, DataType) != SELECTOR_TYPE_MESSAGE_LEN)
                    OAD_BIOP_ASSERT(printf("Expecting selector_length %u", SELECTOR_TYPE_MESSAGE_LEN));
                profile.data_p += 1;

                /*[03-4f]selector_type ================================================*/
                if (biop_uint16(profile_bo, (MS_U32)profile.data_p, DataType) != SELECTOR_TYPE_MESSAGE)
                    OAD_BIOP_ASSERT(printf("Expecting selector_type MESSAGE"));
                profile.data_p += 2;

                /*[03-4g]transactionId ================================================*/
                transaction_id = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
                OAD_BIOP_D1(printf("\ntransaction_id: 0x%08LX", transaction_id));
                DSI_OC_Transaction_id = transaction_id;
                profile.data_p += 4;

                /*[03-4h]timeout ======================================================*/
                timeout = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
                OAD_BIOP_D1(printf("\ntimeout: 0x%08LX", timeout));
                profile.data_p += 4;

                taps_count--;
            }

            /*[03-5]###tap II### ======================================================*/
            while(taps_count > 0)
            {
                OAD_BIOP_D1(printf("\nOther Tap"));
                /*[03-5a]id ===========================================================*/
                /* id = biop_uint16(profile_bo, *((MS_U16 *) profile.data_p)) */
                profile.data_p += 2;

                /*[03-5b]use ==========================================================*/
                if (biop_uint16(profile_bo, (MS_U32)profile.data_p, DataType) != BIOP_DELIVERY_PARA_USE)
                    OAD_BIOP_ASSERT(printf("Expecting BIOP_DELIVERY_PARA_USE"));
                profile.data_p += 2;

                /*[03-5c]association_tag ==============================================*/   //(1)===>Look Up PMT
                association_tag = biop_uint16(profile_bo, (MS_U32)profile.data_p, DataType);
                profile.data_p += 2;

                /*[03-5d]selector_length ==============================================*/
                N4 = biop_uint08(profile.data_p, DataType);
                profile.data_p += 1;

                /*[03-5e]selector_data_byte ===========================================*/
                for (i=0; i<N4 ;i++)
                {
                    //printf("%02x ", biop_uint08(profile.data_p+i, DataType));
                }
                //printf("]\n");

                /*[03-5f]next tap =====================================================*/
                profile.data_p +=N4;

                taps_count--;
            }

            /*[03-6]###LiteComponent### ===============================================*/
            while((ncomponents-2)>0)
            {
                OAD_BIOP_D1(printf("\nLiteComponent"));

                /*[03-6a]componentId_tag ==============================================*/
                OAD_BIOP_DBG(printf("componentId_tag=0x%08x ", biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType)));
                profile.data_p += 4;

                /*[03-6b]component_data_length ========================================*/
                N6 = biop_uint08(profile.data_p, DataType);
                profile.data_p += 1;

                /*[03-6c]component_data_byte ==========================================*/
                for(i=0; i<N6 ;i++)
                {
                    //printf("%02x ", biop_uint08(profile.data_p+i, DataType));
                }
                //printf("]\n");

                /*[03-6d]next component ===============================================*/
                profile.data_p +=N6;

                ncomponents--;
            }
        }
        else if(tag == TAG_LITE_OPTIONS)
        {
            OAD_BIOP_DBG(printf("   LiteOptionsProfileBody:"));

            /*[03-1c]profile_data_p_byte_order ========================================*/
            profile_bo = biop_uint08(profile.data_p, DataType);
            profile.data_p += 1;

            /*[03-1d]component_count ==================================================*/
            ncomponents = biop_uint08(profile.data_p, DataType);
            profile.data_p += 1;

            /*[03-2]###service location### ============================================*/
            /*[03-2a]BIOP::ServiceLocation ============================================*/
            if (biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType) != TAG_ServiceLocation)
                OAD_BIOP_ASSERT(printf("Expecting BIOP::ServiceLocation"));
            profile.data_p += 4;

            /*[03-2b]component_data_length ============================================*/
            /* component_data_length = biop_uint32(profile_bo, *((MS_U32 *) profile.data_p)); */   //<<=== spec is incorrect
            /* component_data_length = *(profile.data_p); */                                    //<<=== DTG is like this
            profile.data_p += 1;

            /*[03-3]###service domain### ==============================================*/
            profile.data_p += process_service_domain(profile.data_p, DataType);

            /*[03-4]###path name### ===================================================*/
            /*[03-4a]nameComponents_count =============================================*/
            nameComponents_count = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
            profile.data_p += 4;

            for(i=0; i< nameComponents_count; i++)
            {
                /*[03-4b]id_length ====================================================*/
                id_length = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
                profile.data_p += 4;

                /*[03-4c]id_data_byte =================================================*/
                for(j=0; j<id_length; j++)
                {
                    //printf("%c ", biop_uint08(profile.data_p+j, DataType));
                }
                //printf("\n");
                profile.data_p += id_length;

                /*[03-4d]kind_length ==================================================*/
                kind_length = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
                profile.data_p += 4;

                /*[03-4e]kind_data_byte ===============================================*/
                for(j=0; j<kind_length; j++)
                {
                    //printf("%c ", biop_uint08(profile.data_p+j, DataType));
                }
                //printf("\n");
                profile.data_p += kind_length;
            }

            /*[03-5]###initialContext### ==============================================*/
            /*[03-5a]initialContextLength =============================================*/
            initialContextLength = biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType);
            profile.data_p += 4;

            /*[03-5b]initialContext_data_byte =========================================*/
            for(j=0; j<initialContextLength; j++)
            {
                //printf("%c ", biop_uint08(profile.data_p+j, DataType));
            }
            //printf("\n");
            profile.data_p += initialContextLength;

            /*[03-6]###LiteOptionComponent### =========================================*/
            while((ncomponents-1)>0)
            {
                /*[03-6a]componentId_tag ==============================================*/
                OAD_BIOP_DBG(printf("componentId_tag=0x%08x ", biop_uint32(profile_bo, (MS_U32)profile.data_p, DataType)));
                profile.data_p += 4;

                /*[03-6b]component_data_length ========================================*/
                N6 = biop_uint08(profile.data_p, DataType);
                profile.data_p += 1;

                /*[03-6c]component_data_byte ==========================================*/
                for(i=0; i<N6 ;i++)
                {
                    //printf("%02x ", biop_uint08(profile.data_p+i, DataType));
                }
                //printf("]\n");

                /*[03-6d]next component ===============================================*/
                profile.data_p +=N6;

                ncomponents--;
            }
        }
        else
        {
            OAD_BIOP_ASSERT(printf("\nUnknown IOP::IOR profileId_tag (0x%x)", (unsigned int)tag));
        }
    }

    return (data_p - start);
}

MS_U32 process_service_context_list( MS_U32 Addr, MS_U8 DataType )
{
    MS_U32 data_p, start;
    MS_U8 count;
    MS_U16 byte;
    MS_U8 i;
    MS_U16 j;

    data_p = start = Addr;
    count = biop_uint08(data_p, DataType);
    data_p++;

    for(i=0; i<count; i++)
    {
        //printf("data_broadcast_id=0x%04x ", biop_uint16(BIOP_BIGENDIAN, data_p, DataType));
        data_p+=2;
        //printf("application_type_code=0x%04x ", biop_uint16(BIOP_BIGENDIAN, data_p, DataType));
        data_p+=2;
        byte = biop_uint16(BIOP_BIGENDIAN, data_p, DataType);
        data_p+=2;
        //printf("application_specific_data= ");
        for(j=0;j<byte;j++)
        {
            //printf("%02x ", biop_uint08(data_p+j, DataType));
        }
        data_p+=byte;
    }
    return (data_p-start);
}

/*
 BIOP::DownloadTaps in the ServiceGateWayInfo structure
*/
MS_U32 process_biop_SGWInfo_Taps_Skip(MS_U32 Addr, MS_U8 DataType)
{
    MS_U8  downloadTapsCount, selectorLength;      // variable of DSM::Tap()
    MS_U8  i;
    MS_U32 data_p, start;

    data_p = start = Addr;

    //printf("\nSGWInfo Addr: 0x%08LX", data_p);

    // DSM::Tap() Skip
    downloadTapsCount = biop_uint08(data_p, DataType); data_p++;

    for ( i = 0; i < downloadTapsCount; i++ )
    {
        data_p += 6;        // id, use, assocTag pass

        selectorLength = biop_uint08(data_p, DataType); data_p++;
        data_p += selectorLength;
    }

    //printf("\nSGWInfo Leng: 0x%08LX", (data_p - start));

    return (data_p - start);
}

MS_U32 process_service_context_list_Skip(MS_U32 Addr, MS_U8 DataType)
{
    MS_U8      i;
    MS_U8      contextListCount;       // variable of serviceContextList
    MS_U32     contextId;
    MS_U16     contextDataLength;
    MS_U32     data_p, start;

    data_p = start = Addr;

    //printf("\nservice context Addr: 0x%08LX", data_p);

    // serviceContextList Skip
    contextListCount = biop_uint08(data_p, DataType); data_p++;

    for ( i = 0; i < contextListCount; i++ )
    {
        contextId           = biop_uint32(BIOP_BIGENDIAN, data_p, DataType); data_p += 4;
        contextDataLength   = biop_uint16(BIOP_BIGENDIAN, data_p, DataType); data_p += 2;
        data_p += contextDataLength;
    }

    //printf("\nservice context Leng: 0x%08LX", (data_p - start));

    return (data_p - start);
}

void process_userinfo_GetMISInfo(BIOP_USERINFO_MIS *mis_info)
{
    mis_info->manufacturer_id   = MIS_Info.manufacturer_id;
    mis_info->version_id        = MIS_Info.version_id;
    memcpy(mis_info->reserved, MIS_Info.reserved, MIS_SELBYTE_LEN);
}

MS_U32 process_profile_Body_GetTransID(void)
{
    return DSI_OC_Transaction_id;
}

void process_fileinfo_Get(BIOP_FILE_INFO * FileInfoData)
{
    FileInfoData->FileBufferAddr    = FileInfo.FileBufferAddr;
    FileInfoData->FileBufferSize    = FileInfo.FileBufferSize;
}

void process_serviceGateway_IOR_Get(BIOP_BODY_PROFILE_IOR_INFO *ior_info)
{
    ior_info->carousel_id       = sg_ior.carousel_id;
    ior_info->module_id         = sg_ior.module_id;
    ior_info->association_tag   = sg_ior.association_tag;
    ior_info->b_valid           = TRUE;
}

MS_U32 process_userinfo_MIS(MS_U32 Addr, MS_U8 DataType)
{
    MS_U16     userInfoLength, manufacturer_data_length;     // variable of userInfo
    MS_U16   i, j;
    MS_U8      manufacturer_info_tag;
    MS_U32     manufacturer_id, version_id;
    MS_U32     data_p, start;

    memset(&MIS_Info, 0, sizeof(MIS_Info));

    data_p = start = Addr;

    //printf("\nUser Info Addr: 0x%08LX", data_p);

    userInfoLength = biop_uint16(BIOP_BIGENDIAN, (MS_U32)data_p, DataType); data_p += 2;

    manufacturer_info_tag = biop_uint08(data_p, DataType); data_p++;

    manufacturer_data_length = biop_uint16(BIOP_BIGENDIAN, data_p, DataType); data_p += 2;
    OAD_BIOP_DBG(printf("manufacturer_data_length=%x\n",manufacturer_data_length)) ;
    if (manufacturer_info_tag == 0xE0)
    {
        manufacturer_id = 0;
        manufacturer_id += ((MS_U32)biop_uint08(data_p, DataType) << 16);
        manufacturer_id += ((MS_U32)biop_uint08(data_p+1, DataType) << 8);
        manufacturer_id += (biop_uint08(data_p+2, DataType));
        OAD_BIOP_DBG(printf("manufacturer_id = %08lX\n", manufacturer_id));

        data_p +=3;

        version_id = biop_uint32(BIOP_BIGENDIAN, data_p, DataType); data_p += 4;
        OAD_BIOP_DBG(printf("version_id = %08lX\n", version_id));

        // save into MIS_info structure
        MIS_Info.manufacturer_id    = manufacturer_id;
        MIS_Info.version_id         = version_id;
        for (i=0, j=0; i< (manufacturer_data_length-7); i++, j++)
        {
            // manufacturer specific data byte
            if ( j < sizeof(MIS_Info.reserved) )
            {
                MIS_Info.reserved[j] = biop_uint08(data_p, DataType);
            }
            data_p++;
        }
    }
    else
    {
        OAD_BIOP_DBG(printf("ERROR>> manufacturer_info_tag != 0xE0\n"));

        data_p +=manufacturer_data_length;

        // save into MIS_info structure
        MIS_Info.manufacturer_id = INVALID_MANUFACTURER_ID;
        MIS_Info.version_id = INVALID_VERSION_ID;
    }

    return (data_p - start);
}


//=======================================================================================
//The data in the privateDataByte field of the DownloadServerInitiate() message shall
//contain the BIOP::ServiceGatewayInfo structure.
//=======================================================================================

/*
 * returns the elementary_pid that maps to the association_tag in the IOP::IOR
 */

void process_biop_service_gateway_info(unsigned char *section)
{
    OAD_BIOP_DBG(printf("\n<<BIOP::ServiceGatewayInfo>>"));

    //Initialize the Transaction ID
    DSI_OC_Transaction_id = INVALID_TRANSACTION_ID;

    section += (MS_U32)process_iop_ior(BIOP_BIGENDIAN, (MS_U32)section, &sg_ior, SDRAM_TYPE);
    section += (MS_U32)process_biop_SGWInfo_Taps_Skip((MS_U32)section, SDRAM_TYPE);
    section += (MS_U32)process_service_context_list_Skip((MS_U32)section, SDRAM_TYPE);
    section += (MS_U32)process_userinfo_MIS((MS_U32)section, SDRAM_TYPE);

    u8ObjKeyLength = sg_ior.key.size;

    if ( u8ObjKeyLength > OBJECT_KEY_MAX_LENGTH )
    {
        u8ObjKeyLength = OBJECT_KEY_MAX_LENGTH;
    }

    biop_rawdata(sg_ior.key.data_p, u8ObjKey, u8ObjKeyLength, SDRAM_TYPE);

    #if 0
    //dump data for debugging
    {
        MS_U8 i;
        printf("Key:\n   ");
        for (i=0; i<u8ObjKeyLength; i++)
        {
            printf("0x%bx ", u8ObjKey[i]);
        }
        printf("\n");
    }
    #endif
}

#undef _MSAPI_OAD_BIOP_C_

