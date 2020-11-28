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
////////////////////////////////////////////////////////////////////////////////

// This file is generated by script, please do not edit it directly
#ifndef _MSD7C19_H_
#define _MSD7C19_H_

#define PAD_NC 9999
#define PAD_GND 0

#define PIN_7 PAD_SPDIF_OUT
#define PAD_SPDIF_OUT 107
#define GPIO_PAD_107 GPIO106
#ifndef PIN_7_IS_GPIO
#define PIN_7_IS_GPIO 0
#endif
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO PIN_7_IS_GPIO
#endif

#define PIN_10 PAD_SM0_GPIO0
#define PAD_SM0_GPIO0 26
#define GPIO_PAD_26 GPIO25
#ifndef PIN_10_IS_GPIO
#define PIN_10_IS_GPIO 0
#endif
#ifndef PAD_SM0_GPIO0_IS_GPIO
#define PAD_SM0_GPIO0_IS_GPIO PIN_10_IS_GPIO
#endif

#define PIN_11 PAD_SM0_GPIO1
#define PAD_SM0_GPIO1 27
#define GPIO_PAD_27 GPIO26
#ifndef PIN_11_IS_GPIO
#define PIN_11_IS_GPIO 0
#endif
#ifndef PAD_SM0_GPIO1_IS_GPIO
#define PAD_SM0_GPIO1_IS_GPIO PIN_11_IS_GPIO
#endif

#define PIN_12 PAD_SM1_IO
#define PAD_SM1_IO 28
#define GPIO_PAD_28 GPIO27
#ifndef PIN_12_IS_GPIO
#define PIN_12_IS_GPIO 0
#endif
#ifndef PAD_SM1_IO_IS_GPIO
#define PAD_SM1_IO_IS_GPIO PIN_12_IS_GPIO
#endif

#define PIN_13 PAD_SM0_CD
#define PAD_SM0_CD 24
#define GPIO_PAD_24 GPIO23
#ifndef PIN_13_IS_GPIO
#define PIN_13_IS_GPIO 0
#endif
#ifndef PAD_SM0_CD_IS_GPIO
#define PAD_SM0_CD_IS_GPIO PIN_13_IS_GPIO
#endif

#define PIN_14 PAD_SM0_RST
#define PAD_SM0_RST 23
#define GPIO_PAD_23 GPIO22
#ifndef PIN_14_IS_GPIO
#define PIN_14_IS_GPIO 0
#endif
#ifndef PAD_SM0_RST_IS_GPIO
#define PAD_SM0_RST_IS_GPIO PIN_14_IS_GPIO
#endif

#define PIN_15 PAD_SM0_VCC
#define PAD_SM0_VCC 25
#define GPIO_PAD_25 GPIO24
#ifndef PIN_15_IS_GPIO
#define PIN_15_IS_GPIO 0
#endif
#ifndef PAD_SM0_VCC_IS_GPIO
#define PAD_SM0_VCC_IS_GPIO PIN_15_IS_GPIO
#endif

#define PIN_16 PAD_SM0_IO
#define PAD_SM0_IO 21
#define GPIO_PAD_21 GPIO20
#ifndef PIN_16_IS_GPIO
#define PIN_16_IS_GPIO 0
#endif
#ifndef PAD_SM0_IO_IS_GPIO
#define PAD_SM0_IO_IS_GPIO PIN_16_IS_GPIO
#endif

#define PIN_17 PAD_SM0_CLK
#define PAD_SM0_CLK 22
#define GPIO_PAD_22 GPIO21
#ifndef PIN_17_IS_GPIO
#define PIN_17_IS_GPIO 0
#endif
#ifndef PAD_SM0_CLK_IS_GPIO
#define PAD_SM0_CLK_IS_GPIO PIN_17_IS_GPIO
#endif

#define PIN_18 PAD_S_GPIO0
#define PAD_S_GPIO0 111
#define GPIO_PAD_111 GPIO110
#ifndef PIN_18_IS_GPIO
#define PIN_18_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO0_IS_GPIO
#define PAD_S_GPIO0_IS_GPIO PIN_18_IS_GPIO
#endif

#define PIN_80 PAD_S_GPIO1
#define PAD_S_GPIO1 112
#define GPIO_PAD_112 GPIO111
#ifndef PIN_80_IS_GPIO
#define PIN_80_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO1_IS_GPIO
#define PAD_S_GPIO1_IS_GPIO PIN_80_IS_GPIO
#endif

#define PIN_81 PAD_S_GPIO2
#define PAD_S_GPIO2 113
#define GPIO_PAD_113 GPIO112
#ifndef PIN_81_IS_GPIO
#define PIN_81_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO2_IS_GPIO
#define PAD_S_GPIO2_IS_GPIO PIN_81_IS_GPIO
#endif

#define PIN_82 PAD_CI_A14
#define PAD_CI_A14 54
#define GPIO_PAD_54 GPIO53
#ifndef PIN_82_IS_GPIO
#define PIN_82_IS_GPIO 0
#endif
#ifndef PAD_CI_A14_IS_GPIO
#define PAD_CI_A14_IS_GPIO PIN_82_IS_GPIO
#endif

#define PIN_83 PAD_CI_A13
#define PAD_CI_A13 55
#define GPIO_PAD_55 GPIO54
#ifndef PIN_83_IS_GPIO
#define PIN_83_IS_GPIO 0
#endif
#ifndef PAD_CI_A13_IS_GPIO
#define PAD_CI_A13_IS_GPIO PIN_83_IS_GPIO
#endif

#define PIN_84 PAD_CI_A12
#define PAD_CI_A12 56
#define GPIO_PAD_56 GPIO55
#ifndef PIN_84_IS_GPIO
#define PIN_84_IS_GPIO 0
#endif
#ifndef PAD_CI_A12_IS_GPIO
#define PAD_CI_A12_IS_GPIO PIN_84_IS_GPIO
#endif

#define PIN_85 PAD_CI_A11
#define PAD_CI_A11 57
#define GPIO_PAD_57 GPIO56
#ifndef PIN_85_IS_GPIO
#define PIN_85_IS_GPIO 0
#endif
#ifndef PAD_CI_A11_IS_GPIO
#define PAD_CI_A11_IS_GPIO PIN_85_IS_GPIO
#endif

#define PIN_86 PAD_CI_A10
#define PAD_CI_A10 58
#define GPIO_PAD_58 GPIO57
#ifndef PIN_86_IS_GPIO
#define PIN_86_IS_GPIO 0
#endif
#ifndef PAD_CI_A10_IS_GPIO
#define PAD_CI_A10_IS_GPIO PIN_86_IS_GPIO
#endif

#define PIN_87 PAD_CI_A9
#define PAD_CI_A9 59
#define GPIO_PAD_59 GPIO58
#ifndef PIN_87_IS_GPIO
#define PIN_87_IS_GPIO 0
#endif
#ifndef PAD_CI_A9_IS_GPIO
#define PAD_CI_A9_IS_GPIO PIN_87_IS_GPIO
#endif

#define PIN_88 PAD_CI_A8
#define PAD_CI_A8 60
#define GPIO_PAD_60 GPIO59
#ifndef PIN_88_IS_GPIO
#define PIN_88_IS_GPIO 0
#endif
#ifndef PAD_CI_A8_IS_GPIO
#define PAD_CI_A8_IS_GPIO PIN_88_IS_GPIO
#endif

#define PIN_90 PAD_CI_A7
#define PAD_CI_A7 61
#define GPIO_PAD_61 GPIO60
#ifndef PIN_90_IS_GPIO
#define PIN_90_IS_GPIO 0
#endif
#ifndef PAD_CI_A7_IS_GPIO
#define PAD_CI_A7_IS_GPIO PIN_90_IS_GPIO
#endif

#define PIN_91 PAD_CI_A6
#define PAD_CI_A6 62
#define GPIO_PAD_62 GPIO61
#ifndef PIN_91_IS_GPIO
#define PIN_91_IS_GPIO 0
#endif
#ifndef PAD_CI_A6_IS_GPIO
#define PAD_CI_A6_IS_GPIO PIN_91_IS_GPIO
#endif

#define PIN_92 PAD_CI_A5
#define PAD_CI_A5 63
#define GPIO_PAD_63 GPIO62
#ifndef PIN_92_IS_GPIO
#define PIN_92_IS_GPIO 0
#endif
#ifndef PAD_CI_A5_IS_GPIO
#define PAD_CI_A5_IS_GPIO PIN_92_IS_GPIO
#endif

#define PIN_93 PAD_CI_A2
#define PAD_CI_A2 66
#define GPIO_PAD_66 GPIO65
#ifndef PIN_93_IS_GPIO
#define PIN_93_IS_GPIO 0
#endif
#ifndef PAD_CI_A2_IS_GPIO
#define PAD_CI_A2_IS_GPIO PIN_93_IS_GPIO
#endif

#define PIN_94 PAD_NF_CEZ
#define PAD_NF_CEZ 53
#define GPIO_PAD_53 GPIO52
#ifndef PIN_94_IS_GPIO
#define PIN_94_IS_GPIO 0
#endif
#ifndef PAD_NF_CEZ_IS_GPIO
#define PAD_NF_CEZ_IS_GPIO PIN_94_IS_GPIO
#endif

#define PIN_95 PAD_CI_A3
#define PAD_CI_A3 65
#define GPIO_PAD_65 GPIO64
#ifndef PIN_95_IS_GPIO
#define PIN_95_IS_GPIO 0
#endif
#ifndef PAD_CI_A3_IS_GPIO
#define PAD_CI_A3_IS_GPIO PIN_95_IS_GPIO
#endif

#define PIN_96 PAD_CI_A0
#define PAD_CI_A0 68
#define GPIO_PAD_68 GPIO67
#ifndef PIN_96_IS_GPIO
#define PIN_96_IS_GPIO 0
#endif
#ifndef PAD_CI_A0_IS_GPIO
#define PAD_CI_A0_IS_GPIO PIN_96_IS_GPIO
#endif

#define PIN_97 PAD_CI_A1
#define PAD_CI_A1 67
#define GPIO_PAD_67 GPIO66
#ifndef PIN_97_IS_GPIO
#define PIN_97_IS_GPIO 0
#endif
#ifndef PAD_CI_A1_IS_GPIO
#define PAD_CI_A1_IS_GPIO PIN_97_IS_GPIO
#endif

#define PIN_98 PAD_CI_A4
#define PAD_CI_A4 64
#define GPIO_PAD_64 GPIO63
#ifndef PIN_98_IS_GPIO
#define PIN_98_IS_GPIO 0
#endif
#ifndef PAD_CI_A4_IS_GPIO
#define PAD_CI_A4_IS_GPIO PIN_98_IS_GPIO
#endif

#define PIN_99 PAD_CI_D0
#define PAD_CI_D0 76
#define GPIO_PAD_76 GPIO75
#ifndef PIN_99_IS_GPIO
#define PIN_99_IS_GPIO 0
#endif
#ifndef PAD_CI_D0_IS_GPIO
#define PAD_CI_D0_IS_GPIO PIN_99_IS_GPIO
#endif

#define PIN_100 PAD_CI_D1
#define PAD_CI_D1 75
#define GPIO_PAD_75 GPIO74
#ifndef PIN_100_IS_GPIO
#define PIN_100_IS_GPIO 0
#endif
#ifndef PAD_CI_D1_IS_GPIO
#define PAD_CI_D1_IS_GPIO PIN_100_IS_GPIO
#endif

#define PIN_101 PAD_CI_D2
#define PAD_CI_D2 74
#define GPIO_PAD_74 GPIO73
#ifndef PIN_101_IS_GPIO
#define PIN_101_IS_GPIO 0
#endif
#ifndef PAD_CI_D2_IS_GPIO
#define PAD_CI_D2_IS_GPIO PIN_101_IS_GPIO
#endif

#define PIN_103 PAD_CI_D3
#define PAD_CI_D3 73
#define GPIO_PAD_73 GPIO72
#ifndef PIN_103_IS_GPIO
#define PIN_103_IS_GPIO 0
#endif
#ifndef PAD_CI_D3_IS_GPIO
#define PAD_CI_D3_IS_GPIO PIN_103_IS_GPIO
#endif

#define PIN_104 PAD_CI_D4
#define PAD_CI_D4 72
#define GPIO_PAD_72 GPIO71
#ifndef PIN_104_IS_GPIO
#define PIN_104_IS_GPIO 0
#endif
#ifndef PAD_CI_D4_IS_GPIO
#define PAD_CI_D4_IS_GPIO PIN_104_IS_GPIO
#endif

#define PIN_105 PAD_CI_D5
#define PAD_CI_D5 71
#define GPIO_PAD_71 GPIO70
#ifndef PIN_105_IS_GPIO
#define PIN_105_IS_GPIO 0
#endif
#ifndef PAD_CI_D5_IS_GPIO
#define PAD_CI_D5_IS_GPIO PIN_105_IS_GPIO
#endif

#define PIN_106 PAD_CI_D6
#define PAD_CI_D6 70
#define GPIO_PAD_70 GPIO69
#ifndef PIN_106_IS_GPIO
#define PIN_106_IS_GPIO 0
#endif
#ifndef PAD_CI_D6_IS_GPIO
#define PAD_CI_D6_IS_GPIO PIN_106_IS_GPIO
#endif

#define PIN_107 PAD_CI_D7
#define PAD_CI_D7 69
#define GPIO_PAD_69 GPIO68
#ifndef PIN_107_IS_GPIO
#define PIN_107_IS_GPIO 0
#endif
#ifndef PAD_CI_D7_IS_GPIO
#define PAD_CI_D7_IS_GPIO PIN_107_IS_GPIO
#endif

#define PIN_108 PAD_CI_IORDZ
#define PAD_CI_IORDZ 77
#define GPIO_PAD_77 GPIO76
#ifndef PIN_108_IS_GPIO
#define PIN_108_IS_GPIO 0
#endif
#ifndef PAD_CI_IORDZ_IS_GPIO
#define PAD_CI_IORDZ_IS_GPIO PIN_108_IS_GPIO
#endif

#define PIN_109 PAD_CI_IOWRZ
#define PAD_CI_IOWRZ 78
#define GPIO_PAD_78 GPIO77
#ifndef PIN_109_IS_GPIO
#define PIN_109_IS_GPIO 0
#endif
#ifndef PAD_CI_IOWRZ_IS_GPIO
#define PAD_CI_IOWRZ_IS_GPIO PIN_109_IS_GPIO
#endif

#define PIN_110 PAD_CI_OEZ
#define PAD_CI_OEZ 79
#define GPIO_PAD_79 GPIO78
#ifndef PIN_110_IS_GPIO
#define PIN_110_IS_GPIO 0
#endif
#ifndef PAD_CI_OEZ_IS_GPIO
#define PAD_CI_OEZ_IS_GPIO PIN_110_IS_GPIO
#endif

#define PIN_111 PAD_CI_WEZ
#define PAD_CI_WEZ 80
#define GPIO_PAD_80 GPIO79
#ifndef PIN_111_IS_GPIO
#define PIN_111_IS_GPIO 0
#endif
#ifndef PAD_CI_WEZ_IS_GPIO
#define PAD_CI_WEZ_IS_GPIO PIN_111_IS_GPIO
#endif

#define PIN_112 PAD_CI_REGZ
#define PAD_CI_REGZ 81
#define GPIO_PAD_81 GPIO80
#ifndef PIN_112_IS_GPIO
#define PIN_112_IS_GPIO 0
#endif
#ifndef PAD_CI_REGZ_IS_GPIO
#define PAD_CI_REGZ_IS_GPIO PIN_112_IS_GPIO
#endif

#define PIN_113 PAD_CI_CEZ
#define PAD_CI_CEZ 82
#define GPIO_PAD_82 GPIO81
#ifndef PIN_113_IS_GPIO
#define PIN_113_IS_GPIO 0
#endif
#ifndef PAD_CI_CEZ_IS_GPIO
#define PAD_CI_CEZ_IS_GPIO PIN_113_IS_GPIO
#endif

#define PIN_114 PAD_CI_IRQAZ
#define PAD_CI_IRQAZ 83
#define GPIO_PAD_83 GPIO82
#ifndef PIN_114_IS_GPIO
#define PIN_114_IS_GPIO 0
#endif
#ifndef PAD_CI_IRQAZ_IS_GPIO
#define PAD_CI_IRQAZ_IS_GPIO PIN_114_IS_GPIO
#endif

#define PIN_115 PAD_CI_WAITZ
#define PAD_CI_WAITZ 84
#define GPIO_PAD_84 GPIO83
#ifndef PIN_115_IS_GPIO
#define PIN_115_IS_GPIO 0
#endif
#ifndef PAD_CI_WAITZ_IS_GPIO
#define PAD_CI_WAITZ_IS_GPIO PIN_115_IS_GPIO
#endif

#define PIN_116 PAD_CI_RST
#define PAD_CI_RST 85
#define GPIO_PAD_85 GPIO84
#ifndef PIN_116_IS_GPIO
#define PIN_116_IS_GPIO 0
#endif
#ifndef PAD_CI_RST_IS_GPIO
#define PAD_CI_RST_IS_GPIO PIN_116_IS_GPIO
#endif

#define PIN_117 PAD_CI_CDZ
#define PAD_CI_CDZ 86
#define GPIO_PAD_86 GPIO85
#ifndef PIN_117_IS_GPIO
#define PIN_117_IS_GPIO 0
#endif
#ifndef PAD_CI_CDZ_IS_GPIO
#define PAD_CI_CDZ_IS_GPIO PIN_117_IS_GPIO
#endif

#define PIN_118 PAD_TS1_CLK
#define PAD_TS1_CLK 42
#define GPIO_PAD_42 GPIO41
#ifndef PIN_118_IS_GPIO
#define PIN_118_IS_GPIO 0
#endif
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO PIN_118_IS_GPIO
#endif

#define PIN_119 PAD_TS1_D7
#define PAD_TS1_D7 45
#define GPIO_PAD_45 GPIO44
#ifndef PIN_119_IS_GPIO
#define PIN_119_IS_GPIO 0
#endif
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO PIN_119_IS_GPIO
#endif

#define PIN_120 PAD_TS1_D6
#define PAD_TS1_D6 46
#define GPIO_PAD_46 GPIO45
#ifndef PIN_120_IS_GPIO
#define PIN_120_IS_GPIO 0
#endif
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO PIN_120_IS_GPIO
#endif

#define PIN_121 PAD_TS1_D5
#define PAD_TS1_D5 47
#define GPIO_PAD_47 GPIO46
#ifndef PIN_121_IS_GPIO
#define PIN_121_IS_GPIO 0
#endif
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO PIN_121_IS_GPIO
#endif

#define PIN_122 PAD_TS1_D4
#define PAD_TS1_D4 48
#define GPIO_PAD_48 GPIO47
#ifndef PIN_122_IS_GPIO
#define PIN_122_IS_GPIO 0
#endif
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO PIN_122_IS_GPIO
#endif

#define PIN_123 PAD_TS1_D3
#define PAD_TS1_D3 49
#define GPIO_PAD_49 GPIO48
#ifndef PIN_123_IS_GPIO
#define PIN_123_IS_GPIO 0
#endif
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO PIN_123_IS_GPIO
#endif

#define PIN_124 PAD_TS1_D2
#define PAD_TS1_D2 50
#define GPIO_PAD_50 GPIO49
#ifndef PIN_124_IS_GPIO
#define PIN_124_IS_GPIO 0
#endif
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO PIN_124_IS_GPIO
#endif

#define PIN_125 PAD_TS1_D1
#define PAD_TS1_D1 51
#define GPIO_PAD_51 GPIO50
#ifndef PIN_125_IS_GPIO
#define PIN_125_IS_GPIO 0
#endif
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO PIN_125_IS_GPIO
#endif

#define PIN_126 PAD_TS1_D0
#define PAD_TS1_D0 52
#define GPIO_PAD_52 GPIO51
#ifndef PIN_126_IS_GPIO
#define PIN_126_IS_GPIO 0
#endif
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO PIN_126_IS_GPIO
#endif

#define PIN_127 PAD_TS1_VLD
#define PAD_TS1_VLD 44
#define GPIO_PAD_44 GPIO43
#ifndef PIN_127_IS_GPIO
#define PIN_127_IS_GPIO 0
#endif
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO PIN_127_IS_GPIO
#endif

#define PIN_128 PAD_TS1_SYNC
#define PAD_TS1_SYNC 43
#define GPIO_PAD_43 GPIO42
#ifndef PIN_128_IS_GPIO
#define PIN_128_IS_GPIO 0
#endif
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO PIN_128_IS_GPIO
#endif

#define PIN_129 PAD_TS0_CLK
#define PAD_TS0_CLK 31
#define GPIO_PAD_31 GPIO30
#ifndef PIN_129_IS_GPIO
#define PIN_129_IS_GPIO 0
#endif
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO PIN_129_IS_GPIO
#endif

#define PIN_130 PAD_TS0_D7
#define PAD_TS0_D7 34
#define GPIO_PAD_34 GPIO33
#ifndef PIN_130_IS_GPIO
#define PIN_130_IS_GPIO 0
#endif
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO PIN_130_IS_GPIO
#endif

#define PIN_131 PAD_TS0_D6
#define PAD_TS0_D6 35
#define GPIO_PAD_35 GPIO34
#ifndef PIN_131_IS_GPIO
#define PIN_131_IS_GPIO 0
#endif
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO PIN_131_IS_GPIO
#endif

#define PIN_132 PAD_TS0_D5
#define PAD_TS0_D5 36
#define GPIO_PAD_36 GPIO35
#ifndef PIN_132_IS_GPIO
#define PIN_132_IS_GPIO 0
#endif
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO PIN_132_IS_GPIO
#endif

#define PIN_133 PAD_TS0_D4
#define PAD_TS0_D4 37
#define GPIO_PAD_37 GPIO36
#ifndef PIN_133_IS_GPIO
#define PIN_133_IS_GPIO 0
#endif
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO PIN_133_IS_GPIO
#endif

#define PIN_134 PAD_TS0_D3
#define PAD_TS0_D3 38
#define GPIO_PAD_38 GPIO37
#ifndef PIN_134_IS_GPIO
#define PIN_134_IS_GPIO 0
#endif
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO PIN_134_IS_GPIO
#endif

#define PIN_137 PAD_TS0_D2
#define PAD_TS0_D2 39
#define GPIO_PAD_39 GPIO38
#ifndef PIN_137_IS_GPIO
#define PIN_137_IS_GPIO 0
#endif
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO PIN_137_IS_GPIO
#endif

#define PIN_138 PAD_TS0_D1
#define PAD_TS0_D1 40
#define GPIO_PAD_40 GPIO39
#ifndef PIN_138_IS_GPIO
#define PIN_138_IS_GPIO 0
#endif
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO PIN_138_IS_GPIO
#endif

#define PIN_139 PAD_TS0_D0
#define PAD_TS0_D0 41
#define GPIO_PAD_41 GPIO40
#ifndef PIN_139_IS_GPIO
#define PIN_139_IS_GPIO 0
#endif
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO PIN_139_IS_GPIO
#endif

#define PIN_140 PAD_TS0_VLD
#define PAD_TS0_VLD 32
#define GPIO_PAD_32 GPIO31
#ifndef PIN_140_IS_GPIO
#define PIN_140_IS_GPIO 0
#endif
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO PIN_140_IS_GPIO
#endif

#define PIN_141 PAD_TS0_SYNC
#define PAD_TS0_SYNC 33
#define GPIO_PAD_33 GPIO32
#ifndef PIN_141_IS_GPIO
#define PIN_141_IS_GPIO 0
#endif
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO PIN_141_IS_GPIO
#endif

#define PIN_142 PAD_S_GPIO3
#define PAD_S_GPIO3 114
#define GPIO_PAD_114 GPIO113
#ifndef PIN_142_IS_GPIO
#define PIN_142_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO3_IS_GPIO
#define PAD_S_GPIO3_IS_GPIO PIN_142_IS_GPIO
#endif

#define PIN_143 PAD_S_GPIO4
#define PAD_S_GPIO4 115
#define GPIO_PAD_115 GPIO114
#ifndef PIN_143_IS_GPIO
#define PIN_143_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO4_IS_GPIO
#define PAD_S_GPIO4_IS_GPIO PIN_143_IS_GPIO
#endif

#define PIN_144 PAD_I2CM0_SDA
#define PAD_I2CM0_SDA 29
#define GPIO_PAD_29 GPIO28
#ifndef PIN_144_IS_GPIO
#define PIN_144_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SDA_IS_GPIO
#define PAD_I2CM0_SDA_IS_GPIO PIN_144_IS_GPIO
#endif

#define PIN_145 PAD_I2CM0_SCL
#define PAD_I2CM0_SCL 30
#define GPIO_PAD_30 GPIO29
#ifndef PIN_145_IS_GPIO
#define PIN_145_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SCL_IS_GPIO
#define PAD_I2CM0_SCL_IS_GPIO PIN_145_IS_GPIO
#endif

#define PIN_155 PAD_AGC_DOWN
#define PAD_AGC_DOWN 88
#define GPIO_PAD_88 GPIO87
#ifndef PIN_155_IS_GPIO
#define PIN_155_IS_GPIO 0
#endif
#ifndef PAD_AGC_DOWN_IS_GPIO
#define PAD_AGC_DOWN_IS_GPIO PIN_155_IS_GPIO
#endif

#define PIN_156 PAD_AGC_UP
#define PAD_AGC_UP 87
#define GPIO_PAD_87 GPIO86
#ifndef PIN_156_IS_GPIO
#define PIN_156_IS_GPIO 0
#endif
#ifndef PAD_AGC_UP_IS_GPIO
#define PAD_AGC_UP_IS_GPIO PIN_156_IS_GPIO
#endif

#define PIN_157 PAD_SAR0
#define PAD_SAR0 17
#define GPIO_PAD_17 GPIO16
#ifndef PIN_157_IS_GPIO
#define PIN_157_IS_GPIO 0
#endif
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO PIN_157_IS_GPIO
#endif

#define PIN_158 PAD_SAR1
#define PAD_SAR1 18
#define GPIO_PAD_18 GPIO17
#ifndef PIN_158_IS_GPIO
#define PIN_158_IS_GPIO 0
#endif
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO PIN_158_IS_GPIO
#endif

#define PIN_159 PAD_SAR2
#define PAD_SAR2 19
#define GPIO_PAD_19 GPIO18
#ifndef PIN_159_IS_GPIO
#define PIN_159_IS_GPIO 0
#endif
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO PIN_159_IS_GPIO
#endif

#define PIN_160 PAD_SAR3
#define PAD_SAR3 20
#define GPIO_PAD_20 GPIO19
#ifndef PIN_160_IS_GPIO
#define PIN_160_IS_GPIO 0
#endif
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO PIN_160_IS_GPIO
#endif

#define PAD_GPIO_PM9 16
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO 0
#endif

#define PIN_163 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef PIN_163_IS_GPIO
#define PIN_163_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO PIN_163_IS_GPIO
#endif

#define PIN_164 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef PIN_164_IS_GPIO
#define PIN_164_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO PIN_164_IS_GPIO
#endif

#define PIN_165 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef PIN_165_IS_GPIO
#define PIN_165_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO PIN_165_IS_GPIO
#endif

#define PIN_166 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef PIN_166_IS_GPIO
#define PIN_166_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO PIN_166_IS_GPIO
#endif

#define PIN_169 PAD_GPIO_PM0
#define PAD_GPIO_PM0 7
#define GPIO_PAD_7 GPIO6
#ifndef PIN_169_IS_GPIO
#define PIN_169_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO PIN_169_IS_GPIO
#endif

#define PIN_170 PAD_GPIO_PM1
#define PAD_GPIO_PM1 8
#define GPIO_PAD_8 GPIO7
#ifndef PIN_170_IS_GPIO
#define PIN_170_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO PIN_170_IS_GPIO
#endif

#define PIN_171 PAD_GPIO_PM4
#define PAD_GPIO_PM4 11
#define GPIO_PAD_11 GPIO10
#ifndef PIN_171_IS_GPIO
#define PIN_171_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO PIN_171_IS_GPIO
#endif

#define PIN_172 PAD_GPIO_PM2
#define PAD_GPIO_PM2 9
#define GPIO_PAD_9 GPIO8
#ifndef PIN_172_IS_GPIO
#define PIN_172_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO PIN_172_IS_GPIO
#endif

#define PIN_173 PAD_GPIO_PM5
#define PAD_GPIO_PM5 12
#define GPIO_PAD_12 GPIO11
#ifndef PIN_173_IS_GPIO
#define PIN_173_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO PIN_173_IS_GPIO
#endif

#define PIN_174 PAD_GPIO_PM3
#define PAD_GPIO_PM3 10
#define GPIO_PAD_10 GPIO9
#ifndef PIN_174_IS_GPIO
#define PIN_174_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO PIN_174_IS_GPIO
#endif

#define PIN_175 PAD_GPIO_PM6
#define PAD_GPIO_PM6 13
#define GPIO_PAD_13 GPIO12
#ifndef PIN_175_IS_GPIO
#define PIN_175_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO PIN_175_IS_GPIO
#endif

#define PIN_176 PAD_GPIO_PM7
#define PAD_GPIO_PM7 14
#define GPIO_PAD_14 GPIO13
#ifndef PIN_176_IS_GPIO
#define PIN_176_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO PIN_176_IS_GPIO
#endif

#define PIN_177 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef PIN_177_IS_GPIO
#define PIN_177_IS_GPIO 0
#endif
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO PIN_177_IS_GPIO
#endif

#define PIN_178 PAD_GPIO_PM8
#define PAD_GPIO_PM8 15
#define GPIO_PAD_15 GPIO14
#ifndef PIN_178_IS_GPIO
#define PIN_178_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO PIN_178_IS_GPIO
#endif

#define PIN_179 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef PIN_179_IS_GPIO
#define PIN_179_IS_GPIO 0
#endif
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO PIN_179_IS_GPIO
#endif

#define PIN_183 PAD_VSYNC_OUT
#define PAD_VSYNC_OUT 110
#define GPIO_PAD_110 GPIO109
#ifndef PIN_183_IS_GPIO
#define PIN_183_IS_GPIO 0
#endif
#ifndef PAD_VSYNC_OUT_IS_GPIO
#define PAD_VSYNC_OUT_IS_GPIO PIN_183_IS_GPIO
#endif

#define PIN_184 PAD_ET_MDIO
#define PAD_ET_MDIO 106
#define GPIO_PAD_106 GPIO105
#ifndef PIN_184_IS_GPIO
#define PIN_184_IS_GPIO 0
#endif
#ifndef PAD_ET_MDIO_IS_GPIO
#define PAD_ET_MDIO_IS_GPIO PIN_184_IS_GPIO
#endif

#define PAD_ET_CRS 9999
#ifndef PAD_ET_CRS_IS_GPIO
#define PAD_ET_CRS_IS_GPIO 0
#endif

#define PIN_185 PAD_ET_MDC
#define PAD_ET_MDC 105
#define GPIO_PAD_105 GPIO104
#ifndef PIN_185_IS_GPIO
#define PIN_185_IS_GPIO 0
#endif
#ifndef PAD_ET_MDC_IS_GPIO
#define PAD_ET_MDC_IS_GPIO PIN_185_IS_GPIO
#endif

#define PAD_ET_TXD3 9999
#ifndef PAD_ET_TXD3_IS_GPIO
#define PAD_ET_TXD3_IS_GPIO 0
#endif

#define PIN_186 PAD_ET_COL
#define PAD_ET_COL 90
#define GPIO_PAD_90 GPIO89
#ifndef PIN_186_IS_GPIO
#define PIN_186_IS_GPIO 0
#endif
#ifndef PAD_ET_COL_IS_GPIO
#define PAD_ET_COL_IS_GPIO PIN_186_IS_GPIO
#endif

#define PAD_ET_TXD2 9999
#ifndef PAD_ET_TXD2_IS_GPIO
#define PAD_ET_TXD2_IS_GPIO 0
#endif

#define PIN_187 PAD_ET_RXD0
#define PAD_ET_RXD0 101
#define GPIO_PAD_101 GPIO100
#ifndef PIN_187_IS_GPIO
#define PIN_187_IS_GPIO 0
#endif
#ifndef PAD_ET_RXD0_IS_GPIO
#define PAD_ET_RXD0_IS_GPIO PIN_187_IS_GPIO
#endif

#define PAD_ET_TXER 9999
#ifndef PAD_ET_TXER_IS_GPIO
#define PAD_ET_TXER_IS_GPIO 0
#endif

#define PIN_188 PAD_ET_RXD1
#define PAD_ET_RXD1 102
#define GPIO_PAD_102 GPIO101
#ifndef PIN_188_IS_GPIO
#define PIN_188_IS_GPIO 0
#endif
#ifndef PAD_ET_RXD1_IS_GPIO
#define PAD_ET_RXD1_IS_GPIO PIN_188_IS_GPIO
#endif

#define PAD_ET_RXER 9999
#ifndef PAD_ET_RXER_IS_GPIO
#define PAD_ET_RXER_IS_GPIO 0
#endif

#define PIN_189 PAD_ET_TX_CLK
#define PAD_ET_TX_CLK 96
#define GPIO_PAD_96 GPIO95
#ifndef PIN_189_IS_GPIO
#define PIN_189_IS_GPIO 0
#endif
#ifndef PAD_ET_TX_CLK_IS_GPIO
#define PAD_ET_TX_CLK_IS_GPIO PIN_189_IS_GPIO
#endif

#define PAD_ET_RX_CLK 9999
#ifndef PAD_ET_RX_CLK_IS_GPIO
#define PAD_ET_RX_CLK_IS_GPIO 0
#endif

#define PIN_190 PAD_ET_TXD0
#define PAD_ET_TXD0 94
#define GPIO_PAD_94 GPIO93
#ifndef PIN_190_IS_GPIO
#define PIN_190_IS_GPIO 0
#endif
#ifndef PAD_ET_TXD0_IS_GPIO
#define PAD_ET_TXD0_IS_GPIO PIN_190_IS_GPIO
#endif

#define PAD_ET_RX_DV 9999
#ifndef PAD_ET_RX_DV_IS_GPIO
#define PAD_ET_RX_DV_IS_GPIO 0
#endif

#define PIN_191 PAD_ET_TXD1
#define PAD_ET_TXD1 93
#define GPIO_PAD_93 GPIO92
#ifndef PIN_191_IS_GPIO
#define PIN_191_IS_GPIO 0
#endif
#ifndef PAD_ET_TXD1_IS_GPIO
#define PAD_ET_TXD1_IS_GPIO PIN_191_IS_GPIO
#endif

#define PAD_ET_RXD2 9999
#ifndef PAD_ET_RXD2_IS_GPIO
#define PAD_ET_RXD2_IS_GPIO 0
#endif

#define PIN_192 PAD_ET_TX_EN
#define PAD_ET_TX_EN 95
#define GPIO_PAD_95 GPIO94
#ifndef PIN_192_IS_GPIO
#define PIN_192_IS_GPIO 0
#endif
#ifndef PAD_ET_TX_EN_IS_GPIO
#define PAD_ET_TX_EN_IS_GPIO PIN_192_IS_GPIO
#endif

#define PAD_ET_RXD3 9999
#ifndef PAD_ET_RXD3_IS_GPIO
#define PAD_ET_RXD3_IS_GPIO 0
#endif

#define PAD_S_GPIO5 9999
#ifndef PAD_S_GPIO5_IS_GPIO
#define PAD_S_GPIO5_IS_GPIO 0
#endif

#define PIN_195 PAD_SPDIF_OUT2
#define PAD_SPDIF_OUT2 108
#define GPIO_PAD_108 GPIO107
#ifndef PIN_195_IS_GPIO
#define PIN_195_IS_GPIO 0
#endif
#ifndef PAD_SPDIF_OUT2_IS_GPIO
#define PAD_SPDIF_OUT2_IS_GPIO PIN_195_IS_GPIO
#endif

#define PIN_196 PAD_HSYNC_OUT
#define PAD_HSYNC_OUT 109
#define GPIO_PAD_109 GPIO108
#ifndef PIN_196_IS_GPIO
#define PIN_196_IS_GPIO 0
#endif
#ifndef PAD_HSYNC_OUT_IS_GPIO
#define PAD_HSYNC_OUT_IS_GPIO PIN_196_IS_GPIO
#endif


// PADS group name to index
#define PADS_DDCR           1223
#define PADS_DDCR2          1224
#define PADS_TS0            1225
#define PADS_TS1            1226
#define PADS_GPIO1_GPIO2    1227
#define PADS_LHSYNC2_LVSYNC2 1228
#define PADS_PCI_AD20_AD21  1229
#define PADS_PCI            1230
#define PADS_PCM            1231
#define PADS_SAR            1232
#define PADS_DOUT           1233
#define PADS_DIN            1234
#define PADS_I2S            1235
#define PADS_PF             1236
#define PADS_EMAC           1237
#define PADS_TCON           1238
#define PADS_UART1_MODE1    1239
#define PADS_UART1_MODE2    1240
#define PADS_UART1_MODE3    1241
#define PADS_UART2_MODE1    1242
#define PADS_UART2_MODE2    1243
#define PADS_UART2_MODE3    1244
#define PADS_ET_MODE0       1245
#define PADS_ET_MODE1       1246
#define PADS_ET_MODE2       1247
#define PADS_ET_MODE3       1248
#define PADS_MIIC           1249
#define PADS_PF_MODE1       1250
#define PADS_PF_MODE2       1251
#define PADS_PF_MODE3       1252
#define PADS_SPI_CZ1        1253
#define PADS_SPI_CZ2        1254
#define PADS_SPI_CZ3        1255
#define PADS_DDCR3          1256

// chip capbilities
#define CHIP_HAS_BT656_IN          0
#define CHIP_HAS_TS0               1
#define CHIP_HAS_TS1               0
#define CHIP_HAS_LVDS_10BIT_X2     1
#define CHIP_HAS_LVDS_8BIT_X2      1
#define CHIP_HAS_LVDS_8BIT_X1      1
#define CHIP_HAS_CIMAX             0
#define CHIP_HAS_USB_P0            1
#define CHIP_HAS_USB_P1            1
#define CHIP_HAS_USBVBUS0          0
#define CHIP_HAS_USBVBUS1          0
#define CHIP_HAS_UART1_MODE1       1
#define CHIP_HAS_UART1_MODE2       1
#define CHIP_HAS_UART1_MODE3       1
#define CHIP_HAS_PCMCIA1           0
#define CHIP_HAS_PCMCIA2           0
#define CHIP_HAS_PCMCIA            0
#define CHIP_HAS_UART2_MODE1       1
#define CHIP_HAS_UART2_MODE2       1
#define CHIP_HAS_UART2_MODE3       1
#define CHIP_HAS_RGB_A             1
#define CHIP_HAS_RGB_B             1
#define CHIP_HAS_RGB_C             1
#define CHIP_HAS_HDMI_A            1
#define CHIP_HAS_HDMI_B            1
#define CHIP_HAS_HDMI_C            1
#define CHIP_HAS_SPI_CZ1           1
#define CHIP_HAS_SPI_CZ2           0
#define CHIP_HAS_SPI_CZ3           0
#define CHIP_HAS_DDCR              1
#define CHIP_HAS_DDCR2             1
#define CHIP_HAS_TCON              1
#define CHIP_HAS_ET_MODE0_MII      1
#define CHIP_HAS_ET_MODE0_RMII     1
#define CHIP_HAS_ET_MODE1_MII      1
#define CHIP_HAS_ET_MODE1_RMII     1
#define CHIP_HAS_ET_MODE2_MII      1
#define CHIP_HAS_ET_MODE2_RMII     1
#define CHIP_HAS_I2S_IN            0
#define CHIP_HAS_I2S_OUT           0
#define CHIP_HAS_SPDIF_IN          0
#define CHIP_HAS_SPDIF_OUT         0
#define CHIP_HAS_DDR_A_CMD         1
#define CHIP_HAS_DDR_A_DATA        1
#define CHIP_HAS_DDR_B_CMD         1
#define CHIP_HAS_DDR_B_DATA        1
#define CHIP_USE_PCM_CDN_IN_PCM2   0
#define CHIP_USE_I2S_IN_IN_PCM     0
#define CHIP_USE_I2S_OUT_IN_PCM    0
#define CHIP_USE_SPDIF_IN_IN_PCM   0
#define CHIP_USE_SPDIF_OUT_IN_PCM  0
#define CHIP_USE_IIC_IN_DDCR2      0
#define CHIP_USE_PWM2_IN_GPIO14    0
#define CHIP_USE_PWM3_IN_GPIO15    0

// chip additional information
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_S7J

#endif /* _MSD7C19_H_*/
