//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include <common.h>
#include <command.h> 
#if defined(CONFIG_CMD_EEPROM) && (CONFIG_MSTARI2C == 1)
#include <exports.h>
#include <apiSWI2C.h>
#include <CusConfig.h>
#include <CusDevice.h>
#include <MsOS.h>
#include <MsDebug.h>
#include <ShareType.h>
#include <MsEeprom.h>


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define HIBYTE(value)     ((MS_U8)((value) >> 8))
#define LOBYTE(value)     ((MS_U8)(value))

typedef enum
{
    EEPROM_24C01,
    EEPROM_24C02,
    EEPROM_24C04,
    EEPROM_24C08,
    EEPROM_24C16,
    EEPROM_24C32,
    EEPROM_24C64,
    EEPROM_24C128,
    EEPROM_24C256,
    EEPROM_24C512,
    EEPROM_24C1024,    
} EEPROM_FAMILY;


typedef struct
{
    MS_U16 u16DeviceAddr;
    EEPROM_FAMILY type;        // 24c02~24c512, page size is used in burst write
} ST_EEPROM_ID;


typedef struct
{
    MS_U16 u16SlaveIDAddr;
    MS_U8  u8AddrCnt;
    MS_U8  pu8Offset[2];
    MS_U16 u8PageSize; // max 2 bytes for many years !!
} ST_EEPROM_PARA;


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
const char *const fmt = "\nEEPROM @0x%lX(%d) %s: addr %08lx  off %04lx  count %ld ... \n";
static MS_U8 EepromID = 0 ; // default is 0
ST_EEPROM_ID stEepromArray[EEPROM_REGISTER_NUM]=
{
    EEPROM_REGISTER_INFO
};

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
static char* getEepromName(EEPROM_FAMILY type);
static void showDevInfo(void);
static ST_EEPROM_PARA getEepeomParameter(ST_EEPROM_ID EepromType,MS_U16 offset);

//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------
static ST_EEPROM_PARA getEepeomParameter(ST_EEPROM_ID EepromType,MS_U16 offset)
{
    ST_EEPROM_PARA stEtype;
    u16 u16Tmp = 0;
   
    switch(EepromType.type)
    {
        case EEPROM_24C01:    
        case EEPROM_24C02:
            stEtype.u16SlaveIDAddr=EepromType.u16DeviceAddr;
            stEtype.u8AddrCnt=1;
            stEtype.pu8Offset[0]=LOBYTE(offset);
            stEtype.u8PageSize=8;
            break;
        case EEPROM_24C04:
            u16Tmp=((HIBYTE(offset)&0x1)<<1);          
            stEtype.u16SlaveIDAddr=(EepromType.u16DeviceAddr|u16Tmp);
            stEtype.u8AddrCnt=1;
            stEtype.pu8Offset[0]=LOBYTE(offset);
            stEtype.u8PageSize=16;            
            break;
        case EEPROM_24C08:
            u16Tmp=((HIBYTE(offset)&0x3)<<1);          
            stEtype.u16SlaveIDAddr=(EepromType.u16DeviceAddr|u16Tmp);
            stEtype.u8AddrCnt=1;
            stEtype.pu8Offset[0]=LOBYTE(offset);
            stEtype.u8PageSize=16;                        
            break;
        case EEPROM_24C16:
            u16Tmp=((HIBYTE(offset)&0x7)<<1);          
            stEtype.u16SlaveIDAddr=(EepromType.u16DeviceAddr|u16Tmp);
            stEtype.u8AddrCnt=1;
            stEtype.pu8Offset[0]=LOBYTE(offset);
            stEtype.u8PageSize=16;              
            break;            
        case EEPROM_24C32:            
        case EEPROM_24C64:            
            stEtype.u8PageSize=32;              
            stEtype.u16SlaveIDAddr=EepromType.u16DeviceAddr;
            stEtype.u8AddrCnt=2;
            stEtype.pu8Offset[0]=HIBYTE(offset);
            stEtype.pu8Offset[1]=LOBYTE(offset);            
            break;
        case EEPROM_24C128:
        case EEPROM_24C256:
            stEtype.u8PageSize=64;              
            stEtype.u16SlaveIDAddr=EepromType.u16DeviceAddr;
            stEtype.u8AddrCnt=2;
            stEtype.pu8Offset[0]=HIBYTE(offset);
            stEtype.pu8Offset[1]=LOBYTE(offset);                
            break;
        case EEPROM_24C512:
            stEtype.u8PageSize=128;              
            stEtype.u16SlaveIDAddr=EepromType.u16DeviceAddr;
            stEtype.u8AddrCnt=2;
            stEtype.pu8Offset[0]=HIBYTE(offset);
            stEtype.pu8Offset[1]=LOBYTE(offset);                
        case EEPROM_24C1024:            
            stEtype.u8PageSize=256;              
            stEtype.u16SlaveIDAddr=EepromType.u16DeviceAddr;
            stEtype.u8AddrCnt=2;
            stEtype.pu8Offset[0]=HIBYTE(offset);
            stEtype.pu8Offset[1]=LOBYTE(offset);                
            break;
        default:
            UBOOT_ERROR("Wrong Eeprom Type!!\n");
            break;
    }
    return stEtype;
}



int eeprom_PageRead(MS_U16 offset, MS_U8 *pBuf, MS_U16 u16BufLen)
{
     ST_EEPROM_PARA stEtype;
     MS_U16 u16writeSize=0;

     if(pBuf==NULL)
     {
        UBOOT_ERROR("input parameter 'pBuf' is a null pointer\n");
        return -1;
     }

     while(u16BufLen>0)
     {       
        stEtype = getEepeomParameter(stEepromArray[EepromID],offset);
        UBOOT_DEBUG(fmt, stEtype.u16SlaveIDAddr, stEtype.u8AddrCnt,"read", pBuf,stEtype.pu8Offset, u16BufLen);   
        if(u16BufLen >= stEtype.u8PageSize)
        {
            u16writeSize = stEtype.u8PageSize;
            u16BufLen = u16BufLen - stEtype.u8PageSize;
        }
        else
        {
            u16writeSize = u16BufLen;
            u16BufLen = 0;
        }        
        if(MApi_SWI2C_ReadBytes(stEtype.u16SlaveIDAddr, stEtype.u8AddrCnt,stEtype.pu8Offset,u16writeSize, (MS_U8*)(pBuf)) != TRUE)
        {
            UBOOT_ERROR("MApi_SWI2C_ReadBytes FAIL!!\n");
            return -1;
        }
        
        pBuf+=u16writeSize;
        offset+=u16writeSize; 
    }   
    return 0;
}

int eeprom_PageWrite(MS_U16 offset, MS_U8 *pBuf, MS_U16 u16BufLen)
{
    ST_EEPROM_PARA stEtype;
    MS_U16 u16writeSize=0;

    if(pBuf==NULL)
    {
       UBOOT_ERROR("input parameter 'pBuf' is a null pointer\n");
       return -1;
    }
    
    while(u16BufLen>0)
    {       
       stEtype = getEepeomParameter(stEepromArray[EepromID],offset);
       UBOOT_DEBUG(fmt, stEtype.u16SlaveIDAddr, stEtype.u8AddrCnt,"write", pBuf,stEtype.pu8Offset, u16BufLen);         
       if(u16BufLen >= stEtype.u8PageSize)
       {
           u16writeSize = stEtype.u8PageSize;
           u16BufLen = u16BufLen - stEtype.u8PageSize;
       }
       else
       {
           u16writeSize = u16BufLen;
           u16BufLen = 0;
       }  
       if(MApi_SWI2C_WriteBytes(stEtype.u16SlaveIDAddr, stEtype.u8AddrCnt,stEtype.pu8Offset,u16writeSize, (MS_U8*)(pBuf)) != TRUE)
       {
           UBOOT_ERROR("MApi_SWI2C_WriteBytes FAIL!!\n");
           return -1;
       }
       
       MsOS_DelayTask(10);
       pBuf+=u16writeSize;
       offset+=u16writeSize; 
   }   
    return 0;
}

MS_U8 eeprom_ReadByte(MS_U16 offset)
{
    MS_U8 u8Value = 0;
    eeprom_PageRead(offset,(MS_U8 *)&u8Value,1);
    return u8Value;
}

int eeprom_WriteByte(MS_U16 offset,MS_U8 u8Value)
{
    return eeprom_PageWrite(offset, (MS_U8 *)&u8Value, 1);
}

static char* getEepromName(EEPROM_FAMILY type)
{
    char *EepromName = NULL;
    switch(type)
    {
        case EEPROM_24C01:
            EepromName="AT24C01";
            break;
        case EEPROM_24C02:
            EepromName="AT24C02";            
            break;
        case EEPROM_24C04:
            EepromName="AT24C04";         
            break;
        case EEPROM_24C08:
            EepromName="AT24C08";                    
            break;
        case EEPROM_24C16:
            EepromName="AT24C16";
            break;            
        case EEPROM_24C32:            
            EepromName="AT24C32";           
            break;              
        case EEPROM_24C64:            
            EepromName="AT24C64";              
            break;
        case EEPROM_24C128:
            EepromName="AT24C128";
            break;            
        case EEPROM_24C256:
            EepromName="AT24C256";   
            break;
        case EEPROM_24C512:
            EepromName="AT24C512";   
        case EEPROM_24C1024:            
            EepromName="AT24C1024";
            break;
        default:
            EepromName="UnKnowName\n";
            break;
    }
    return EepromName;
}

static void showDevInfo(void)
{
    int i=0;    
    UBOOT_INFO("Num\tDeviceID\tDeviceType\n");
    for(i=0;i<EEPROM_REGISTER_NUM;i++)
    {
        UBOOT_INFO(" %d\t 0x%.4x\t\t %s\n",(i+1),stEepromArray[i].u16DeviceAddr,getEepromName(stEepromArray[i].type));
    }
}

void eeprom_switch(int i)   // base 0
{
    EepromID = i;
    UBOOT_INFO("EepromNum : %d\n",EepromID+1);    
}


int do_eeprom ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    MS_U32 addr = 0;
    MS_U32 off = 0;
    MS_U16 cnt = 0;
    char * data = NULL;
    int ret = 0;
    char buffer[CMD_BUF]="\0";

    if (argc < 2) 
    {     
        return cmd_usage(cmdtp);
    }
    if (strncmp (argv[1], "wb", 2) == 0) 
    {
         off=simple_strtoul (argv[2], NULL, 16);
         addr=simple_strtoul (argv[3], NULL, 16);         
         ret = eeprom_WriteByte(off,addr); 

         addr=(MS_U32)eeprom_ReadByte(off);    
         UBOOT_INFO("0x%x\n",(unsigned int)addr);
         
    }
    else if (strncmp (argv[1], "rb", 2) == 0) 
    {
		off  = simple_strtoul (argv[2], NULL, 16);        
        addr=(MS_U32)eeprom_ReadByte(off);    
        UBOOT_INFO("0x%x\n",(unsigned int)addr);
    }
    else if (strncmp (argv[1], "ws", 2) == 0)
    {
		off = simple_strtoul (argv[2], NULL, 16);
		data = (char *)argv[3];       
        ret = eeprom_PageWrite(off,(MS_U8*)data,strlen(data));        
    }
	else if (strncmp (argv[1], "dump", 4) == 0) 
    {        
 		off  = simple_strtoul (argv[2], NULL, 16);
		cnt  = simple_strtoul (argv[3], NULL, 16);       
        data=(char *)malloc(cnt);
        if(data==NULL)
        {
            UBOOT_ERROR("memory allocate fail\n");
            return -1;
        }
        eeprom_PageRead(off,(MS_U8 *)data,cnt);
        snprintf(buffer,CMD_BUF,"md.b %x %x",data,cnt);
        run_command(buffer,0); 
    }    
	else if (strncmp (argv[1], "read", 4) == 0) 
    {        
		addr = simple_strtoul (argv[2], NULL, 16);
		off  = simple_strtoul (argv[3], NULL, 16);
		cnt  = simple_strtoul (argv[4], NULL, 16);
        ret = eeprom_PageRead(off,(MS_U8*)addr,cnt);
    }
    else if (strncmp (argv[1], "write", 5) == 0) 
    {        
		addr = simple_strtoul (argv[2], NULL, 16);
		off  = simple_strtoul (argv[3], NULL, 16);
		cnt  = simple_strtoul (argv[4], NULL, 16);
		ret = eeprom_PageWrite(off,(MS_U8*)addr,cnt);
	}
    else if (strncmp (argv[1], "erase", 5) == 0) 
    {
		cnt  = simple_strtoul (argv[2], NULL, 16);       
        data=(char *)malloc(cnt);
        memset((void *)data,0xFF,cnt);
        ret = eeprom_PageWrite(off,(MS_U8*)data,cnt);
        free(data);
    }    
    else if (strncmp (argv[1], "switch", 5) == 0) 
    {
        EepromID = simple_strtoul (argv[2], NULL, 16);
        EepromID--;        
        UBOOT_INFO("EepromNum : %d\n",EepromID+1);    

    }
    else if (strncmp (argv[1], "list", 4) == 0) 
    {
        UBOOT_INFO("------------------------------------\n");     
        UBOOT_INFO("    Current Eeprom Number : %d \n",(EepromID+1));    
        UBOOT_INFO("------------------------------------\n");    
        showDevInfo();
        UBOOT_INFO("------------------------------------\n");         
    }
    else
    {
        cmd_usage(cmdtp);
    }

	return ret;
}



#endif
