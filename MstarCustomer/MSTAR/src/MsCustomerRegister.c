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

#include <MsCmdTable.h>
#include <config.h>
#include <mstarstr.h>

void Customer_Register_Process(void)
{
#if defined (CONFIG_URSA_6M40)
	if(!(is_str_resume()))
	{
		Add_Command_Table("ursa_lvds_off", 0, STAGE_PROCESS);
		Add_Command_Table("delay 50", 0, STAGE_PROCESS);
#if !defined(CONFIG_BOOTLOGO_4K2K)
		Add_Command_Table("ursa_2k_mode", 0, STAGE_PROCESS);
#endif
	}
#endif

    Add_Command_Table("load_environment_first_time", 0, STAGE_PROCESS);

     //Register customter Process
#if defined(CONFIG_LOAD_ENV_FROM_SN)
     if(is_str_resume()==0)
     {
        Add_Command_Table ("envload" , 0, STAGE_PROCESS);
     }
#endif

#if defined (CONFIG_MBOOT_VERSION)
     Add_Command_Table ("mbootver_set" , 0, STAGE_PROCESS);
#endif

#if 0 // "set_FRC" and "ursa_lvds_on" should not be before "panel_pre_init",and no need to call them.
#if defined(CONFIG_SET_4K2K_MODE) && !defined(CONFIG_ENABLE_4K2K_OP_DEFAULT)
    Add_Command_Table("set_FRC", 0, STAGE_PROCESS);
#endif

#if defined (CONFIG_URSA_6M40)
    if(strcmp(getenv("dc_poweroff"), "1") == 0)
    {
        Add_Command_Table("ursa_lvds_on", 0, STAGE_PROCESS);
    }
#endif
#endif

#if(ENABLE_URSA_8==1)
    if(is_str_resume())
    {
        Add_Command_Table ("InitUrsa8" , 0, STAGE_PROCESS);
    }
#endif

    if(is_str_resume())
    {
        Add_Command_Table ("panel_pre_init" , 0, STAGE_PROCESS);
        
        #if(ENABLE_OSDC_Init==1)
            Add_Command_Table ("xc_init" , 0, STAGE_TOKERNEL);
        #endif
        
        #if(ENABLE_CVBS_OUT==1)
            Add_Command_Table ("cvbs" , 0, STAGE_PROCESS);
        #endif

        #if(ENABLE_HDMI_TX == 1)
            Add_Command_Table ("hdmi init" , 0, STAGE_PROCESS);
        #endif
        
        #if(ENABLE_URSA_8==1)
            Add_Command_Table ("ursa8_lvds_on" , 0, STAGE_PROCESS);
        #endif
        
        #if defined (CONFIG_URSA_6M40)
            Add_Command_Table("ursa_lvds_on", 0, STAGE_PROCESS);
            Add_Command_Table("ursa_osd_unmute", 0, STAGE_PROCESS);
        #endif
    }

#if CONFIG_MSTAR_STR_ENABLE
    #if defined (CONFIG_SECURITY_BOOT)
    if(is_str_resume())
    {
        Add_Command_Table ("SecureInit" , 0, STAGE_PROCESS);
    }
    #endif
    
#if defined (CONFIG_TEE)
    if(is_str_resume()) 
    {
        //Add_Command_Table ("checkstr" , 0, STAGE_PROCESS);
        Add_Command_Table ("readNuttx" ,0, STAGE_PROCESS);
        Add_Command_Table ("bootNuttx" ,0, STAGE_PROCESS);
    }
    #endif
#endif

	if(is_str_resume())
	{
		Add_Command_Table ("panel_post_init" , 0, STAGE_PROCESS);
	}

#if CONFIG_MSTAR_STR_ENABLE
#if (CONFIG_ENABLE_RTPM)
     if(is_str_resume())
     {
        Add_Command_Table ("runtime_pm" , 0, STAGE_PROCESS);
     }
#endif
#endif

#if defined (CONFIG_URSA6_VB1)
    if(is_str_resume())
    {
        Add_Command_Table ("send_I2C_cmd_to_ursa6" , 0, STAGE_PROCESS); 
    }
#endif
	
#if CONFIG_MSTAR_STR_ENABLE //checkstr always lowermost.
    if(is_str_resume())
    {
        Add_Command_Table ("checkstr" , 0, STAGE_PROCESS);
    }
#endif

#if(ENABLE_MODULE_BOOT_IR==1)
	Add_Command_Table ("ir_delay" , 0, STAGE_PROCESS);//for IR detect delay
#endif

}


void Customer_Register_ToKernel(void)
{
    //Some flow must run after MBoot console entry to avoid MBoot halt.
    Add_Command_Table ("if_boot_to_pm" , 0, STAGE_TOKERNEL);

   /*bootcheck:check boot mode(usb/oad/net upgrade, recovery, normal).
     If it is normal mode, just go through this command.
     you can mark this to implement your customer boot flow. */
#if(ENABLE_URSA_8==1)
    Add_Command_Table ("InitUrsa8" , 0, STAGE_TOKERNEL);
#endif
    Add_Command_Table ("bootcheck" , 0, STAGE_TOKERNEL);



#if (ENABLE_MSTAR_RUNTIMEAEON==1)
    Add_Command_Table ("aeonrun", 0, STAGE_TOKERNEL);
#endif

#if (ENABLE_MSTAR_PUMABOOT)
    #if (CONFIG_PANEL_INIT)
    Add_Command_Table ("panel_pre_init" , 0, STAGE_TOKERNEL);
    #endif
    #if (ENABLE_HDMI_TX == 1)
    Add_Command_Table ("hdmi init" , 0, STAGE_TOKERNEL);
    #endif
    // Bring up R2
    Add_Command_Table ("r2pbrun" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbpnlinit" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbmmap" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbinput" , 0, STAGE_TOKERNEL);
    /*
    Add_Command_Table ("r2pbdbchan" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbdbuser" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbpnlinit" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbmmap" , 0, STAGE_TOKERNEL);
    Add_Command_Table ("r2pbinput" , 0, STAGE_TOKERNEL);
    */    
#endif
}

void Customer_Register_MsInit(void)
{
        //Register customter MsInit
}
