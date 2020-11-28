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

#include <common.h>
#include <usb.h>
#include "drvhostlib2.h"
//#include "drvUSB.h"
#include "drvusbmain2.h"

//extern Host20_Attach_Device_Structure   sAttachDevice  ;
//static USBCallback _DrvUSB_CBFun = NULL;
extern UINT8 bSpeedP1;
//int _s32UsbEventId;
int Usb_host_Init2(void);
void MDrv_UsbClose2(void);

#if defined(ENABLE_SECOND_EHC)
//extern UINT8 bForceSpeed;//0=>All Clear 1=>Full Speed 2=>High Speed
#if 0
//U8 buf1[512];
#define  TEST_SIZE      64*1024
MS_BOOL MDrv_UsbDiskWrite( MS_U32 u32BlockAddr, MS_U32 u32BlockNum,MS_U32 u8Buffer);
MS_BOOL MDrv_UsbDiskRead(MS_U32 u32BlockAddr, MS_U32 u32BlockNum,MS_U32 u8Buffer);

void UsbTest(void)
{
MS_U32 i,j,k=0;
MS_U32 idx=0,xxx;
//U8 maxlun,lunbyte;
U8  *buf1,*buf2;
    //
 //   maxlun=	MDrv_GET_MASS_MAX_LUN();
 //   lunbyte=MDrv_GET_MASS_VALID_LUN();
	printf("usb test\n");
//	printf("maxlun :%02bx lunbyte:%02bx\n",maxlun,lunbyte);

    buf1=(U8*)MsOS_AllocateMemory(TEST_SIZE, gs32NonCachedPoolID );
    buf2=(U8*)MsOS_AllocateMemory(TEST_SIZE, gs32NonCachedPoolID );
    //printf("buf1:%x, buf2:%x\n",(MS_U32)buf1,(MS_U32)buf2);
    for (i=0 ; i < TEST_SIZE ; i++)
        {
            buf1[i]= i & 0xff;
      }

while (1)
	{
	    idx++;
          printf("Loop:%x \n",idx);
		//	MDrv_MIU_Copy
	     xxx=idx % 10000;

        // for (k=0; k < 8 ; k++)
            {
            if (MDrv_UsbDiskWrite(50+xxx+k*128,TEST_SIZE/512,(MS_U32)buf1)==FALSE)
                {
                   printf("write failed\n");
                   return;
                }
            }
         //for (k=0; k < 8 ; k++)
            {
            if (MDrv_UsbDiskRead(50+xxx+k*128,TEST_SIZE/512,(MS_U32)buf2)==FALSE)
                {
                    printf("read failed\n");
                    return;
                }
            }

	 	//MsOS_Delay_Task(10);
            for (j=0 ; j < TEST_SIZE ; j++)
                 {
                  if (buf2[j]!= buf1[j]) printf("data err\n");
                 }
          //  	MsOS_Delay_Task(500);
        }
	//time1=MDrv_Timer_TimeDifference( MDrv_Timer_GetTime0(), time1 ) ;
	//printf("time1:%lx",time1);
	//printf("Performace:%lx kBytes/sec",  (512*400)/time1);
}
#endif

int ever_inited2 = 0;

//====================================================================
// * Function Name: main
// * Description:
// * Input:
// * OutPut:
//====================================================================
int Usb_host_Init2(void)
{
    ever_inited2 = 1;

    extern void mwHost20Bit_Set2(int bByte,int wBitNum);
    mwHost20Bit_Set2(0x81,BIT6); // Data length byte alignment issue
    if (flib_OTGH_Init2(0, USB_WAIT_TIME)==0)
    {
        printf("usb init failed\n");
        return -1;
    }
    return bSpeedP1;
}

int Usb_host_PreInit2(void)
{
    extern void mwHost20Bit_Set2(int bByte,int wBitNum);
    mwHost20Bit_Set2(0x81,BIT6); // Data length byte alignment issue
    return -1;
}

int Usb_host_PostInit2(void)
{
    ever_inited2 = 1;

    extern void mwHost20Bit_Set2(int bByte,int wBitNum);
    mwHost20Bit_Set2(0x81,BIT6); // Data length byte alignment issue
    if (flib_OTGH_Init2(0, 0)==0)
    {
        printf("usb init failed\n");
        return -1;
    }
    return bSpeedP1;
}

void MDrv_UsbClose2(void)
{
    if(ever_inited2 == 0)
        return;

    flib_Host20_StopRun_Setting2(HOST20_Disable);
    //flib_Host20_Close2(0);

    if (ever_inited2 == 2)
    {
        printf("[USB] Long time stable device. Waiting .5 second...\n");
        mdelay(500);
    }
}
#endif

