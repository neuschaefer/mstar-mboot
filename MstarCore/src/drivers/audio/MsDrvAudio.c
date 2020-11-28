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
#include <command.h>
#include <config.h>
#include <MsTypes.h>
#include <bootlogo/MsPoolDB.h>
#include <MsOS.h>
#include <MsMmap.h>
#include <MsDebug.h>
#include <MsSystem.h>

#if (ENABLE_MSTAR_KAISER==1)
#include <drvSOUND.h>
#endif

#if ENABLE_POWER_MUSIC 
#define debug(fmt,args...)

#define AUDIO_DELAY1MS(x)    mdelay(x)

#define DEFAULT_VOL  30
unsigned int  MELODY_VOLUME = DEFAULT_VOL;

#include <audio/Audio_amplifier.h>
#include <apiAUDIO.h>
#include <drvAUDIO_if.h>
#include <drvAUDIO.h>
#include <drvGPIO.h>
#include <MsApiPM.h>

#define MUSIC_VOL_MAP_NUM 11
/*
     change user power on music vol (range from 0~100) to Abs audio vol(range from 0x7F00 ~ 0x0D01) 
*/
const MS_U16 music_vol_map[MUSIC_VOL_MAP_NUM] =             // UI:  Mute
//           Volume  Table     (High Byte : Integer part  ; Low Byte : Fraction part)
{
    //   1       2       3       4       5       6       7       8       9       10
    0x7F00, //  00
    0x4200, //  10
    0x3000, //  20
    0x2500, //  30
    0x1D00, //  40
    0x1800, //  50
    0x1402, //  60
    0x1106, //  70
    0x0F05, //  80
    0x0E03, //  90
    0x0D01, //  100
};

MS_U16 GetNonlinearAbsVol(MS_U8 u8vol)
{
    MS_U16 ret = 0;
    MS_U8  step = u8vol/10;
    
    if(u8vol>100)
    {
        u8vol = DEFAULT_VOL;
        step = u8vol/10;
        ret = music_vol_map[step] - (double)(u8vol%10)/10*(music_vol_map[step] - music_vol_map[step+1]);
    }
    else if(!(u8vol%10))
        ret =  music_vol_map[step];
    else
        ret = music_vol_map[step] - (double)(u8vol%10)/10*(music_vol_map[step] - music_vol_map[step+1]);

    return (MS_U16)ret;
}
void Mboot_Set_Melody_Play(void)
{
    MS_U8 u8Volume = DEFAULT_VOL;
    MS_U8 u8VolHi,u8VolLo;

    #if (!CONFIG_SIM_Amplifier)
    //    mdrv_gpio_init();
    drvAudio_AMP_Init();
    #endif
	
    char * p_vol = NULL;
    if((p_vol =getenv ("music_vol"))!=NULL)
    {
        MELODY_VOLUME = (int)simple_strtol(p_vol, NULL, 10);
    }
    
    if(MELODY_VOLUME == 0)
    {
        u8Volume = 0;
    }
    else
    {
        u8Volume = MELODY_VOLUME;
    }

    u8VolHi = (MS_U8)(GetNonlinearAbsVol(u8Volume)>>8);
    u8VolLo = (MS_U8)(GetNonlinearAbsVol(u8Volume)&0xFF);
    UBOOT_DEBUG("music u8VolHi=%u,u8VolLo=%u",u8VolHi,u8VolLo);//need this for Delay

  #if(ENABLE_MSTAR_NIKON)
    MDrv_AUDIO_SetInputPath(AUDIO_DSP1_DVB_INPUT, AUDIO_PATH_MAIN);      //Set Path
    MDrv_AUDIO_SetInputPath(AUDIO_DSP1_DVB_INPUT, AUDIO_PATH_0);      //Set Path
    MDrv_AUDIO_SetInputPath(AUDIO_DSP1_DVB_INPUT, AUDIO_PATH_1);      //Set Path
    MDrv_AUDIO_SetInputPath(AUDIO_DSP1_DVB_INPUT, AUDIO_PATH_3);      //Set Path

    MApi_AUDIO_SetAbsoluteVolume( AUDIO_PATH_MAIN, u8VolHi, u8VolLo );
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_PATH_0, 0x0C, 0x00 );   //Set volume
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_PATH_1, u8VolHi, u8VolLo );   //Set volume
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_PATH_3, u8VolHi, u8VolLo );   //Set volume

    MApi_AUDIO_SetMute(AUDIO_PATH_MAIN, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_PATH_0, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_PATH_1, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_PATH_3, 0);                     //Un Mute
  #else     
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_T3_PATH_I2S, u8VolHi, u8VolLo );
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_T3_PATH_AUOUT0, u8VolHi, u8VolLo );   //Set volume
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_T3_PATH_AUOUT1, u8VolHi, u8VolLo );   //Set volume
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_T3_PATH_AUOUT2, u8VolHi, u8VolLo );   //Set volume
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_T3_PATH_AUOUT3, u8VolHi, u8VolLo );   //Set volume
    MApi_AUDIO_SetAbsoluteVolume( AUDIO_T3_PATH_SPDIF, u8VolHi, u8VolLo );   //Set volume//AUDIO_T3_PATH_I2S
    MDrv_AUDIO_SetInputPath(AUDIO_DSP1_DVB_INPUT, AUDIO_PATH_MAIN);      //Set Path
	#if ((ENABLE_MSTAR_KAISER==1)||(ENABLE_MSTAR_KERES==1)||(ENABLE_MSTAR_KRITI==1)||(ENABLE_MSTAR_CLIPPERS==1))
	MDrv_SOUND_AbsoluteVolume( AUDIO_T3_PATH_HDMI, u8VolHi, u8VolLo );	  //Set  HDMI volume 
	#endif

#if (ENABLE_MSTAR_MONACO==1)
    MDrv_AUDIO_SetInternalPath(INTERNAL_CH8, AUDIO_I2S_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_CH8, AUDIO_AUOUT0_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_CH8, AUDIO_AUOUT1_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_CH8, AUDIO_AUOUT2_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_CH8, AUDIO_AUOUT3_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_CH8, AUDIO_SPDIF_OUTPUT);
#else
    MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_I2S_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_AUOUT0_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_AUOUT1_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_AUOUT2_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_AUOUT3_OUTPUT);
    MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_SPDIF_OUTPUT);
#endif

    
	#if ((ENABLE_MSTAR_KAISER==1)||(ENABLE_MSTAR_KERES==1)||(ENABLE_MSTAR_KRITI==1)||(ENABLE_MSTAR_CLIPPERS==1))
	MDrv_AUDIO_SetInternalPath(INTERNAL_PCM, AUDIO_HDMI_OUTPUT);
	#endif
    MApi_AUDIO_SetMute(AUDIO_T3_PATH_AUOUT0, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_T3_PATH_AUOUT1, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_T3_PATH_AUOUT2, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_T3_PATH_AUOUT3, 0);                     //Un Mute
    MApi_AUDIO_SetMute(AUDIO_T3_PATH_I2S, 0);
    MApi_AUDIO_SetMute(AUDIO_T3_PATH_SPDIF, 0);  //Un Mute
	#if ((ENABLE_MSTAR_KAISER==1)||(ENABLE_MSTAR_KERES==1)||(ENABLE_MSTAR_KRITI==1)||(ENABLE_MSTAR_CLIPPERS==1))
	  MDrv_SOUND_SetMute(AUDIO_T3_PATH_HDMI, 0 );  
	#endif 
 #endif
	
#if((ENABLE_MSTAR_MONACO)||(ENABLE_MSTAR_KERES)||(ENABLE_MSTAR_KRITI)||(ENABLE_MSTAR_CLIPPERS)) 
    MDrv_AUDIO_SetInputPath(AUDIO_DSP1_DVB_INPUT , AUDIO_PATH_MAIN);
    MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MP3);
    MApi_AUDIO_MM2_initAesInfo(AU_DEC_ID1);
    AUDIO_DELAY1MS(5);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYMM_FILE2);
    AUDIO_DELAY1MS(5);
    MApi_AUDIO_MM2_inputAesFinished(AU_DEC_ID1, 0x10000-0x20, 0, 0);
#else
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);
    UBOOT_DEBUG("......Step1");//need this for Delay
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
    UBOOT_DEBUG("......Step2");//need this for Delay
    AUDIO_DELAY1MS(5);
    UBOOT_DEBUG(".....Step3");//need this for Delay
    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_MMFileSize, FILE_SIZE_64KB, 0);
    UBOOT_DEBUG("......Step4");//need this for Delay
    UBOOT_DEBUG(".....\n");//need this for Delay
    AUDIO_DELAY1MS(5);
    UBOOT_DEBUG("......Step5");//need this for Delay

	MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);
    UBOOT_DEBUG("......Step6");//need this for Delay
    AUDIO_DELAY1MS(10);
    UBOOT_DEBUG("......Step7");//need this for Delay
    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_DEC1_MMTag, 1, 0);
    UBOOT_DEBUG("......Step8");//need this for Delay
    AUDIO_DELAY1MS(10);
    MApi_AUDIO_SendIntrupt(DSP_DEC, 0xE0);
    UBOOT_DEBUG("\r\n====== Melody Finished !!!=======\r\n");//need this for Delay
    
#endif
    // Do Audio_Amplifier_ON after melody set play command
    if(FALSE == pm_check_back_ground_active())
    {
        Adj_Volume_On();
        Audio_Amplifier_ON();
    }
}

void MsDrv_PlayMelody(void)
{
    UBOOT_DEBUG("music debug %s %s %u\n",__FILE__,__FUNCTION__,__LINE__);

    Mboot_Set_Melody_Play();
    
    printf("[AT][MB][Play Melody][%lu]\n", MsSystemGetBootTime());
}

int MsDrv_AudioPreInit(void)
{
    U32 u32R2Addr =0 , u32SeAddr =0 , u32DecAddr =0 ;  
	
    UBOOT_DEBUG("music debug %s %s %u\n",__FILE__,__FUNCTION__,__LINE__);
    Audio_Amplifier_OFF();  // Do Audio_Amplifier_OFF before audio init

    MApi_AUDIO_WritePreInitTable();

    if(get_addr_from_mmap("E_MMAP_ID_MAD_R2", &u32R2Addr)!=0)
    {
	    UBOOT_ERROR("get E_MMAP_ID_MAD_R2 mmap fail\n");
		return -1;
    }
    if(get_addr_from_mmap("E_MMAP_ID_MAD_SE", &u32SeAddr)!=0)
    {
	    UBOOT_ERROR("get E_MMAP_ID_MAD_SE mmap fail\n");
		return -1;
    }
    if(get_addr_from_mmap("E_MMAP_ID_MAD_DEC", &u32DecAddr)!=0)
    {
	    UBOOT_ERROR("get E_MMAP_ID_MAD_DEC mmap fail\n");
		return -1;
    }
	if(u32R2Addr==0xFFFF || u32SeAddr==0xFFFF ||u32DecAddr==0xFFFF)
	{
		UBOOT_ERROR("Get Mmap for Audio Fail Skip Power Music !!! \n");
		return -1;
	}

    MDrv_AUDIO_SetDspBaseAddr(DSP_DEC, 0, u32DecAddr);
    MDrv_AUDIO_SetDspBaseAddr(DSP_SE, 0,  u32SeAddr);
    MDrv_AUDIO_SetDspBaseAddr(DSP_ADV, 0, u32R2Addr);

    MApi_AUDIO_Initialize(); 
	return 1;
}

MS_U32 MsDrv_GetEsStartAddr(void)
{
    U32 u32EsAddress = 0; 
    
#if((ENABLE_MSTAR_MONACO)||(ENABLE_MSTAR_KERES)||(ENABLE_MSTAR_KRITI)||(ENABLE_MSTAR_CLIPPERS))
    u32EsAddress = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_Get_UNI_ES_Base);
#else
    u32EsAddress = MDrv_AUDIO_GetDspMadBaseAddr(DSP_DEC)+ (U32)MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferAddr);
#endif

    return u32EsAddress;
}
#endif

