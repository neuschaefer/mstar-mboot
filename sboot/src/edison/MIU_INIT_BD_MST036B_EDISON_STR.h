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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MIU_INIT_BD_MST036B_EDISON_STR_H__
#define __MIU_INIT_BD_MST036B_EDISON_STR_H__

#if (ENABLE_MSTAR_BD_MST036B_EDISON)

const MS_REG_INIT MIU0_DDR_Init_STR[] =
{
    _RV32_2( 0x101202, 0xf3a7  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
	_RV32_2( 0x101204, 0x000b  ),  //if I64Mode =0x8b else =0x0b

	#if(ENABLE_MEM1866MHz)
	_RV32_2( 0x101206, 0x0538  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
	_RV32_2( 0x101208, 0x20dd  ),  //reg_tRCD
	_RV32_2( 0x10120a, 0x2e76  ),  //reg_tRRD
	_RV32_2( 0x10120c, 0xc7e9  ),  //reg_tWL
	_RV32_2( 0x10120e, 0x4096  ),  //tRFC
	_RV32_2( 0x101210, 0x1e14  ),  //MR0
	_RV32_2( 0x101212, 0x4040  ),  //MR1
	_RV32_2( 0x101214, 0x8020  ),  //MR2
	_RV32_2( 0x101216, 0xC000  ),  //MR3
	#elif(ENABLE_MEM1600MHz)
	_RV32_2( 0x101206, 0x1460  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
	_RV32_2( 0x101208, 0x1cbb  ),  //reg_tRCD
	_RV32_2( 0x10120a, 0x2766  ),  //reg_tRRD
	_RV32_2( 0x10120c, 0x96c8  ),  //reg_tWL
	_RV32_2( 0x10120e, 0x40f0  ),  //tRFC
	_RV32_2( 0x101210, 0x1c70  ),  //MR0
	_RV32_2( 0x101212, 0x4040  ),  //MR1
	_RV32_2( 0x101214, 0x8018  ),  //MR2
	_RV32_2( 0x101216, 0xC000  ),  //MR3
	#else
	#error "Unsupport DDR freq!!!"
	#endif

    _RV32_2( 0x101226, 0x0000  ),
    _RV32_2( 0x101228, 0x4090  ),
	_RV32_2( 0x10122c, 0x0000  ),
		    #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
				_RV32_2( 0x10122a, 0x0000 ),
		    #endif

	_RV32_2( 0x10125a, 0x6000  ),  // reduce 2t latency en
	_RV32_2( 0x10125a, 0x4000  ),  // reduce 2t latency en

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d00, 0x3e09 ),
	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d00, 0x3e0A ),
	#endif

	_RV32_2( 0x110d04, 0x0080  ),
	_RV32_2( 0x110d10, 0x0c00  ),

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d30, 0x2e8b  ),
	_RV32_2( 0x110d32, 0x001a  ),
	_RV32_2( 0x110d36, 0x4001  ),
	_RV32_2( 0x110d38, 0x2266  ),
	_RV32_2( 0x110d38, 0x2266  ),
	_RV32_2( 0x110d48, 0x2266  ),
	_RV32_2( 0x110d3a, 0x5050  ),
	_RV32_2( 0x110d4a, 0x0000  ),
	_RV32_2( 0x110d02, 0x0000  ),
	_RV32_2( 0x110d3c, 0x0066  ),
	_RV32_2( 0x110d4c, 0x0077  ),

		#if(ENABLE_MEM1866MHz)
		_RV32_2( 0x110d30, 0x8a04  ),
		_RV32_2( 0x110d32, 0x0016  ),
		_RV32_2( 0x110d3a, 0x8080  ),
 		_RV32_2( 0x110d3c, 0x0222  ),
		_RV32_2( 0x110d4c, 0x0233  ),
		#endif

	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d38, 0x0043  ),
	_RV32_2( 0x110d48, 0x0044  ),
	_RV32_2( 0x110d3a, 0x2022  ),
	_RV32_2( 0x110d4a, 0x2022  ),
	_RV32_2( 0x110d02, 0x0000  ),
    _RV32_2( 0x110d3c, 0x0100  ),
    _RV32_2( 0x110d4c, 0x0100  ),
        #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
        _RV32_2( 0x110d38, 0x0044  ),
        _RV32_2( 0x110d48, 0x0054  ),
        _RV32_2( 0x110d3a, 0x6090  ),
        _RV32_2( 0x110d4a, 0x8092  ),
        _RV32_2( 0x110d3c, 0x0133  ),
        _RV32_2( 0x110d4c, 0x0133  ),
        #endif
	#endif

    _RV32_2( 0x110d5a, 0x2222  ),
    _RV32_2( 0x110d5c, 0x2222  ),
    _RV32_2( 0x110d5e, 0x2222  ),
		    #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
				_RV32_2( 0x110d5a, 0x2222  ),
		    _RV32_2( 0x110d5c, 0x2222  ),
		    _RV32_2( 0x110d5e, 0x2222  ),
		    #endif

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d3e, 0x0000  ),
	_RV32_2( 0x110d0e, 0x00e5  ),
	_RV32_2( 0x110d0e, 0x00a5  ),
	_RV32_2( 0x110d0e, 0x00e5  ),
	_RV32_2( 0x110d0e, 0x00a5  ),
	_RV32_2( 0x110d6e, 0x6767  ),

		#if(ENABLE_MEM1866MHz)
		_RV32_2( 0x110d0e, 0x00a9  ),
		_RV32_2( 0x110d3e, 0x0022  ),
		#endif

	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d3e, 0x1010  ),
	_RV32_2( 0x110d0e, 0x00e9  ),
	_RV32_2( 0x110d0e, 0x00a9  ),
	_RV32_2( 0x110d0e, 0x00e9  ),
	_RV32_2( 0x110d0e, 0x00a9  ),
	_RV32_2( 0x110d6e, 0x7768  ),
        #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
        _RV32_2( 0x110d0e, 0x00a7  ),
        _RV32_2( 0x110d28, 0x800D  ),
        _RV32_2( 0x110d2a, 0x0535  ),
        #endif
	#endif

	_RV32_2( 0x110d6a, 0x0020  ),
	_RV32_2( 0x110d68, 0x0020  ),

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d72, 0x0003  ),
	_RV32_2( 0x110d74, 0x6666  ),
	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d72, 0x0005  ),
	    #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
	    _RV32_2( 0x110d74, 0x6666  ),
	    #endif
	#endif

    //DLL calibration
    _RV32_2( 0x110d60, 0x000c  ),
    _RV32_2( 0x110d60, 0x0008  ),
    _RV32_2( 0x110d62, 0x007f  ),
    _RV32_2( 0x110d64, 0xf200  ),
    _RV32_2( 0x110d60, 0x2370  ),

	// patch
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d6C, 0xbbbb  ),
	_RV32_2( 0x110d6E, 0xbbbb  ),
	#endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d6C, 0x7777  ),
	_RV32_2( 0x110d6E, 0x7777  ),
	#endif
    #if (DDR_SAMSUNG_K4B2G1646E_BCK0 == 1)
    _RV32_2( 0x110d2D, 0x1111  ),
    _RV32_2( 0x110d2E, 0x1111  ),
    _RV32_2( 0x110d2F, 0x1111  ),
    _RV32_2( 0x110d1B, 0x4001  ),
    _RV32_2( 0x110d25, 0x8091  ),
    #endif
    _END_OF_TBL32_,
    MIU_VER
};

const MS_REG_INIT MIU1_DDR_Init_STR[] =
{
    _RV32_2( 0x100602, 0xf3a3  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
        #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
       // _RV32_2( 0x100602, 0xf00b  ),
        #endif
    _RV32_2( 0x100604, 0x000b  ),  //if I64Mode =0x8b else =0x0b

	#if(ENABLE_MEM1866MHz)
    _RV32_2( 0x100606, 0x0538  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2( 0x100608, 0x20dd  ),  //reg_tRCD
    _RV32_2( 0x10060a, 0x2e76  ),  //reg_tRRD
    _RV32_2( 0x10060c, 0xc7e9  ),  //reg_tWL
    _RV32_2( 0x10060e, 0x4096  ),  //tRFC
    _RV32_2( 0x100610, 0x1e14  ),  //MR0
    _RV32_2( 0x100612, 0x4040  ),  //MR1
    _RV32_2( 0x100614, 0x8020  ),  //MR2
    _RV32_2( 0x100616, 0xC000  ),  //MR3
	#elif(ENABLE_MEM1600MHz)
	_RV32_2( 0x100606, 0x1460  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
	_RV32_2( 0x100608, 0x1cbb  ),  //reg_tRCD
	_RV32_2( 0x10060a, 0x2766  ),  //reg_tRRD
	_RV32_2( 0x10060c, 0x96c8  ),  //reg_tWL
	_RV32_2( 0x10060e, 0x40f0  ),  //tRFC
	_RV32_2( 0x100610, 0x1c70  ),  //MR0
	_RV32_2( 0x100612, 0x4040  ),  //MR1
	_RV32_2( 0x100614, 0x8018  ),  //MR2
	_RV32_2( 0x100616, 0xC000  ),  //MR3
	#else
	#error "Unsupport DDR freq!!!"
	#endif

	_RV32_2( 0x100626, 0x0000  ),

    _RV32_2( 0x100628, 0x4090  ),
    _RV32_2( 0x10062c, 0x0000  ),

    _RV32_2( 0x10065a, 0x6000  ), //	reduce 2t latency en
    _RV32_2( 0x10065a, 0x4000  ), //reduce 2t latency en

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d80, 0x3e09 ),
	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d80, 0x3e0A ),
	#endif

	_RV32_2( 0x110d84, 0x0080  ),
	_RV32_2( 0x110d90, 0x0c00  ),

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110db0, 0x2e8b  ),
	_RV32_2( 0x110db2, 0x001a  ),
	_RV32_2( 0x110db6, 0x4002  ),
	_RV32_2( 0x110db8, 0x2266  ),
	_RV32_2( 0x110dc8, 0x2266  ),
	_RV32_2( 0x110dba, 0x6000  ),
	_RV32_2( 0x110dca, 0x0000  ),
	_RV32_2( 0x110d82, 0x0000  ),
	_RV32_2( 0x110dbc, 0x0067  ),
	_RV32_2( 0x110dcc, 0x0077  ),
	_RV32_2( 0x110dbe, 0x0000  ),

		#if(ENABLE_MEM1866MHz)
		_RV32_2( 0x110db0, 0x8a04  ),
		_RV32_2( 0x110db2, 0x0016  ),
		_RV32_2( 0x110db8, 0x2266  ),
		_RV32_2( 0x110dba, 0x8080  ),
		_RV32_2( 0x110dbc, 0x0222  ),
		_RV32_2( 0x110dbe, 0x0022  ),
		_RV32_2( 0x110dcc, 0x0233  ),
		_RV32_2( 0x110dc8, 0x2266  ),
		#endif

	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110db8, 0x0044  ),
	_RV32_2( 0x110dc8, 0x0044  ),
	_RV32_2( 0x110dba, 0x2022  ),
	_RV32_2( 0x110dca, 0x2022  ),
	_RV32_2( 0x110d82, 0x0000  ),
	_RV32_2( 0x110dbc, 0x0100  ),
	_RV32_2( 0x110dcc, 0x0100  ),
	_RV32_2( 0x110dbe, 0x1010  ),
        #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
        _RV32_2( 0x110dba, 0x9003  ),
        _RV32_2( 0x110dca, 0x7073  ),
        _RV32_2( 0x110dbc, 0x0134  ),
        #endif
	#endif

    _RV32_2( 0x110dda, 0x2222  ),
    _RV32_2( 0x110ddc, 0x2222  ),
    _RV32_2( 0x110dde, 0x2222  ),

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110d8e, 0x00e5  ),
	_RV32_2( 0x110d8e, 0x00a5  ),
	_RV32_2( 0x110d8e, 0x00e5  ),
	_RV32_2( 0x110d8e, 0x00a5  ),
	_RV32_2( 0x110dee, 0x6767  ),

		#if(ENABLE_MEM1866MHz)
		_RV32_2( 0x110d8e, 0x00a9  ),
		#endif

	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110d8e, 0x00e9  ),
	_RV32_2( 0x110d8e, 0x00a9  ),
	_RV32_2( 0x110d8e, 0x00e9  ),
	_RV32_2( 0x110d8e, 0x00a9  ),
	_RV32_2( 0x110dee, 0x0077  ),
	    #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
        _RV32_2( 0x110d8e, 0x00a7  ),
        _RV32_2( 0x110da8, 0x800D  ),
        _RV32_2( 0x110daa, 0x0535  ),
        #endif
	#endif

	_RV32_2( 0x110dea, 0x0020  ),
	_RV32_2( 0x110de8, 0x0020  ),

	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110df2, 0x0003  ),
	_RV32_2( 0x110df4, 0x6666  ),
	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110df2, 0x0005  ),
	    #if(MS_BOARD_TYPE_SEL == BD_MST036B_EDISON)
        _RV32_2( 0x110df4, 0x6666  ),
        #endif
	#endif

    //DLL calibration
    _RV32_2( 0x110de0, 0x000c  ),
    _RV32_2( 0x110de0, 0x0008  ),
    _RV32_2( 0x110de2, 0x007f  ),
    _RV32_2( 0x110de4, 0xf200  ),
    _RV32_2( 0x110de0, 0x2370  ),

	// patch
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
	_RV32_2( 0x110dEC, 0xbbbb  ),
	_RV32_2( 0x110dEE, 0xbbbb  ),
	#endif
	#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
	_RV32_2( 0x110dEC, 0x7777  ),
	_RV32_2( 0x110dEE, 0x7777  ),
	#endif
    #if (DDR_SAMSUNG_K4B2G1646E_BCK0 == 1)
    _RV32_2( 0x110d2D, 0x1111  ),
    _RV32_2( 0x110d2E, 0x1111  ),
    _RV32_2( 0x110d2F, 0x1111  ),
    _RV32_2( 0x110d1B, 0x4001  ),
    _RV32_2( 0x110d25, 0x8091  ),
    #endif

    _END_OF_TBL32_,
};

#endif /* ENABLE_MSTAR_BD_MST036B_EDISON */
#endif /* __MIU_INIT_BD_MST036B_EDISON_H__*/
