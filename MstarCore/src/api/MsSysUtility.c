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

#include <command.h>
#include <common.h>
#include <ShareType.h>
#include <drvGPIO.h>
#include <drvSAR.h>
#include <MsDebug.h>
#include <MsUboot.h>
#include <MsTypes.h>
#include <MsSysUtility.h>

MS_U8 ReadByte(MS_U32 u32RegAddr)
{
    return ((volatile MS_U8*)(MS_RIU_MAP))[(u32RegAddr << 1) - (u32RegAddr & 1)];
}

MS_U16 Read2Byte(MS_U32 u32RegAddr)
{
    MS_U16 u16Value=0;
    MS_U16 u8Value=0;    
    u16Value = (MS_U16)((volatile MS_U8*)(MS_RIU_MAP))[(u32RegAddr << 1) - (u32RegAddr & 1)];
    u32RegAddr++;
    u8Value = ((volatile MS_U8*)(MS_RIU_MAP))[(u32RegAddr << 1) - (u32RegAddr & 1)];
    u16Value = u16Value | (u8Value << 8);
    return u16Value;
}


MS_BOOL WriteByte(MS_U32 u32RegAddr, MS_U8 u8Val)
{
    ((volatile MS_U8*)(MS_RIU_MAP))[(u32RegAddr << 1) - (u32RegAddr & 1)] = u8Val;
    return TRUE;
}

MS_BOOL Write2Byte(MS_U32 u32RegAddr, MS_U16 u16Val)
{
    WriteByte(u32RegAddr,(MS_U8)u16Val);
    WriteByte((u32RegAddr+1),(MS_U8)(u16Val>>8));    
    return TRUE;
}

MS_BOOL WriteRegBit(MS_U32 u32RegAddr, MS_U16 u16Bit, MS_BOOL bEnable)
{
    MS_U16 u16Val = 0;

    u16Val = Read2Byte(u32RegAddr);  
    u16Val = (bEnable) ? (u16Val | u16Bit) : (u16Val & ~u16Bit);
    Write2Byte(u32RegAddr,u16Val);
    return TRUE;
}

MS_BOOL WriteRegBitPos(MS_U32 u32RegAddr, MS_U8 u8Bit, MS_BOOL bEnable)
{
    MS_U16 u16Bit;
    
    if(u8Bit >15)
    {
        UBOOT_ERROR("Over the bank boundary!\n");
    }

    u16Bit= (1 << u8Bit);
    WriteRegBit( u32RegAddr,  u16Bit,  bEnable);

    return TRUE;
}

int do_riu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_U32 u32Target = 0;
    MS_U32 u32Value  = 0;
    MS_U8  u8Bit =0;
    
    if (argc < 3)
    {
        cmd_usage(cmdtp);
        return 0;
    }
     
    if(strncmp(argv[1], "wword", 2) == 0) 
    {    
        u32Target = simple_strtoul(argv[2],NULL,16);     
        u32Value = simple_strtoul(argv[3],NULL,16);       
        Write2Byte(u32Target,(MS_U16)u32Value);
        u32Target = simple_strtoul(argv[2],NULL,16);     
        UBOOT_INFO("[%x]:0x%x\n",(unsigned int)u32Target,(unsigned int)Read2Byte(u32Target));
        
    }    
    else if(strncmp(argv[1], "rword", 2) == 0) 
    {
        u32Target = simple_strtoul(argv[2],NULL,16);     
        UBOOT_INFO("[%x]:0x%x\n",(unsigned int)u32Target,(unsigned int)Read2Byte(u32Target));
    }
    else if(strncmp(argv[1], "wbyte", 2) == 0) 
    {
        u32Target = simple_strtoul(argv[2],NULL,16);     
        u32Value = simple_strtoul(argv[3],NULL,16);           
        WriteByte(u32Target,(MS_U8)u32Value);
        UBOOT_INFO("[%x]:0x%x\n",(unsigned int)u32Target,(unsigned int)ReadByte(u32Target));
    }    
    else if(strncmp(argv[1], "rbyte", 2) == 0) 
    {
        u32Target = simple_strtoul(argv[2],NULL,16);         
        UBOOT_INFO("[%x]:0x%x\n",(unsigned int)u32Target,(unsigned int)ReadByte(u32Target));
    }     
    else if(strncmp(argv[1], "bit", 2) == 0) 
    {
        u32Target = simple_strtoul(argv[2],NULL,16);         
        u8Bit = simple_strtoul(argv[3],NULL,10);        
        u32Value = simple_strtoul(argv[4],NULL,16);              
        WriteRegBitPos(u32Target,u8Bit,(MS_U8)u32Value);
        UBOOT_INFO("[%x]:0x%x\n",(unsigned int)u32Target,(unsigned int)ReadByte(u32Target));
    }             
    else
    {
      cmd_usage(cmdtp);
    }
    
    return 0;    
}

int do_sar( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    U8 ch;
    U8 sarValue;
    U16 percent;

    if(argc<2)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    UBOOT_DEBUG("MS_RIU_MAP is 0x%x\n",(U32)MS_RIU_MAP);    

    ch=(U8)atoi(argv[1]);  
 
	sarValue=MDrv_SAR_Adc_GetValue(ch);
    percent=1.0*sarValue*1000/0x3ff;
    UBOOT_INFO("sar(8bit) = %x\n", sarValue);

    UBOOT_TRACE("OK\n");    
    return 0;
}



int do_gpio( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    MS_GPIO_NUM gpio_num;
    MS_GPIO_NUM gpio_num_p1;

    if(argc<3)
    {
        if(strcmp(argv[1],"list")==NULL && argc==2)
        {
        }
        else
        {
            cmd_usage(cmdtp);
            return -1;
        }
    }

    gpio_num=(MS_GPIO_NUM)atoi(argv[2]);  
    gpio_num_p1=gpio_num+1;

    if((strcmp(argv[1],"get")==NULL) ||(strncmp(argv[1],"inp",3)==NULL))
    {
        mdrv_gpio_set_input(gpio_num_p1);      
        UBOOT_INFO("IN  ");
        UBOOT_INFO("pin=%d\n", mdrv_gpio_get_level(gpio_num_p1));
    }
    else if(strncmp(argv[1],"output",3)==NULL)
    {
        if(argv[3][0]=='1') mdrv_gpio_set_high(gpio_num_p1);
        else if(argv[3][0]=='0') mdrv_gpio_set_low(gpio_num_p1);
        
        UBOOT_INFO("gpio[%d] is %d\n", gpio_num, mdrv_gpio_get_level(gpio_num_p1));
    }
    else if(strncmp(argv[1],"toggle",3)==NULL)
    {
        if(mdrv_gpio_get_level(gpio_num_p1)) 
        {
            mdrv_gpio_set_low(gpio_num_p1);        
        }
        else 
        {    
            mdrv_gpio_set_high(gpio_num_p1);
        }
        UBOOT_INFO("gpio[%d] is %d\n", gpio_num, mdrv_gpio_get_level(gpio_num_p1));
    }
    else if(strncmp(argv[1],"state",3)==NULL)
    {
        if(mdrv_gpio_get_inout(gpio_num_p1)) 
        {
            UBOOT_INFO("IN  ");
        }
        else
        {
            UBOOT_INFO("OUT ");
        }
        UBOOT_INFO("pin=%d\n", mdrv_gpio_get_level(gpio_num_p1));
    }
    else if(strncmp(argv[1],"list",3)==NULL)
    {
        U8 i;
        U8 size;


        if(argc==2)
        {
            size=200;
        }
        else
        {
            size=(MS_GPIO_NUM)atoi(argv[2]);  
        }
        
        for(i=1;i<size;i++) // END_GPIO_NUM 213 in eiffel
        {
            UBOOT_INFO("GPIO %3d ", i);
            gpio_num_p1=i+1;
        
            if(mdrv_gpio_get_inout(gpio_num_p1)) 
            {
                UBOOT_INFO("IN  ");
            }
            else
            {
                UBOOT_INFO("Out ");
            }
            UBOOT_INFO("pin=%d\n", mdrv_gpio_get_level(gpio_num_p1));

            if(i%10==0) UBOOT_INFO("\n");
        
        }

    }
    else
    {
        cmd_usage(cmdtp);
        return -1;

    }


    UBOOT_TRACE("OK\n");    
    return 0;
}





