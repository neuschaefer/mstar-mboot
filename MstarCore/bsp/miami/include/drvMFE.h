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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡uMStar Confidential Information¡v) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _DRV_MFE_H_
#define _DRV_MFE_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
BITS_INFO_UNKNOW=0,
BITS_INFO_FRAMEDONE,
BITS_INFO_BUFFULL,
BITS_INFO_IMG_BUFFULL,
} BITS_STATUS_INFO;

typedef enum
{
GETBITS_NOT_READY=0,
GETBITS_READY=1,
} MFE_HW_STATUS;

#define MAX_OUTBUFFER 10

typedef struct {
    unsigned long miuAddress;    //hardware physical
    unsigned long miuPointer;    //need to OR 0xA0000000
    unsigned long virtual_addr;
    long size;
    BITS_STATUS_INFO status;	// 1: frame_done. 2: buffer full,3: image buffer full.
    int is_more_bits; //1: there are more bitstream packet;  0: this is the last bitstream packet
    unsigned char  voptype;
    unsigned long IVOP_address;
} BITSFRAME_INFO;

typedef struct{
	// MFE-compliant
	int width;
	int height;
	unsigned long BitsBuffStart;
	unsigned long BitsBuffSize;
	MEMMAP_t BitsOutBuffer[MAX_OUTBUFFER];
	// MFE new settings
	int nCodecType; //nCodecType;	// 0/1/2/3: MPEG4/H263/H264/JPEG
	int nDispWidth, nDispHeight;	// Display resolution
	int nBufWidth, nBufHeight;		// Image buffer resolution (aligned to 16 or 32 byte, depends on nCodecType)
	unsigned char bInterlace; //is Interlace? 0/1
	// GOP
	int nPbetweenI;
	int nBbetweenP;
       int nP_is_infinite;
	// Rate control
	int FrameRatex100;
	int nBitrate;

	// Video length
	int nTotalFrames;	// -1 means infinite. 0 is not allowed.
	char file_name[50]; //verify only
	int test_case_format; //nCodecType;	// 0/1/2/3: MPEG4/H263/H264/JPEG
	int test_case_num;
	unsigned char CModel_pattern[20*8];//20 frames
}PVR_Info;

#define MFE_IOC_MAGIC 0

//init MFE.  ioctl(mfe_fd, MFE_IOC_INIT, (MFE_U32)(&appPVR_Info)); PVR_Info appPVR_Info; please reference MApi_MFE_Initialize.
#define MFE_IOC_INIT            ((MFE_IOC_MAGIC<<8)|0)

//Get display order. ioctl(mfe_fd, MFE_IOC_GET_DISPORDER, (MFE_U32)&nDispOrder); MFE_U32 nDispOrder
#define MFE_IOC_GET_DISPORDER	((MFE_IOC_MAGIC<<8)|2)

//Get bitstream after fire HW. ioctl(mfe_fd, MFE_IOC_GETBITS, (u32)(&bitsinfo)); BITSFRAME_INFO bitsinfo.
//there is a Semaphore(_MFE_wait_queue) in this function. wake up at MDrv_MFE_ISR.
//U can get framedone or buffull by status and is_more_bits.
#define MFE_IOC_GETBITS         ((MFE_IOC_MAGIC<<8)|3)

//Fire HW to encode one frame. ioctl(mfe_fd, MFE_IOC_ENC_ONEFRAME, input_frame.miuAddress);
#define MFE_IOC_ENC_ONEFRAME    ((MFE_IOC_MAGIC<<8)|4)

//Close MFE. ioctl(mfe_fd, MFE_IOC_FINISH, none);
#define MFE_IOC_FINISH          ((MFE_IOC_MAGIC<<8)|5)

//Clear bitstream buf. ioctl(mfe_fd, MFE_IOC_CLEAR_BITSBUF, 1); (arg is always 1 now.)
#define MFE_IOC_CLEAR_BITSBUF   ((MFE_IOC_MAGIC<<8)|6)

//Changed Bitrate Dynamically. This ioctl will reset RC-Ctl.
//appPVR_Info.nBitrate = bitRate;
//ioctl(mfe_fd, MFE_IOC_SETBITRATE, (MFE_U32)(&appPVR_Info));
#define MFE_IOC_RESET_BITRATE ((MFE_IOC_MAGIC<<8)|7)

//appPVR_Info.FrameRatex100 = FrameRatex100;
//ioctl(mfe_fd, MFE_IOC_RESET_FRAMERATE, (MFE_U32)(&appPVR_Info));
#define MFE_IOC_RESET_FRAMERATE ((MFE_IOC_MAGIC<<8)|8)

//Get VOL.  ioctl(mfe_fd, MFE_IOC_GET_VOL, (MFE_U32)Buf); ex: Buf[512].
#define MFE_IOC_GET_VOL        ((MFE_IOC_MAGIC<<8)|11)

//Set before init. no support changed bitrate dynamically.
//appPVR_Info.nBitrate = bitRate;
//ioctl(mfe_fd, MFE_IOC_SETBITRATE, (MFE_U32)(&appPVR_Info));
#define MFE_IOC_SETBITRATE ((MFE_IOC_MAGIC<<8)|15)

//must be called before others. ioctl(mfe_fd, MFE_IOC_SET_MIU_OFFSET,  miu_offset);
#define MFE_IOC_SET_MIU_OFFSET ((MFE_IOC_MAGIC<<8)|18)

//must be called before init.
//Set RIU base.(MS_MODULE_HW). ioctl(mfe_fd, MFE_IOC_SET_RIU_BASE,  u32RiuBaseAdd);
//It can be got from MDrv_MMIO_GetBASE( &u32RiuBaseAdd, &u32NonPMBankSize, MS_MODULE_HW).
#define MFE_IOC_SET_RIU_BASE ((MFE_IOC_MAGIC<<8)|19)

//call before getbits.
//ioctl(mfe_fd, MFE_IOC_CHECK_STATUS, (MFE_U32*) status);
#define MFE_IOC_CHECK_STATUS ((MFE_IOC_MAGIC<<8)|20)



//utopia
/// data type signed int, data length 4 byte
typedef MS_S32     MFE_S32;

int MDrv_MFE_Ioctl(MFE_S32 MFE_fd, unsigned int cmd, unsigned long  arg);

#ifdef __cplusplus
}
#endif

#endif //_DRV_MFE_H_

