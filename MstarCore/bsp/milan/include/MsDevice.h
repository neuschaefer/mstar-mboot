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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#ifndef __PRANA_DEVICE_H__
#define __PRANA_DEVICE_H__

#include "MsTypes.h"

#define DEVICE_NULL ((device_t)0)

typedef unsigned long device_t;

//
// device PM event
//
typedef enum
{
    E_EVT_SUSPEND   = 1,
    E_EVT_SHUTDOWN  = 2,
} eDEVEVT;

typedef enum
{
    E_POWER_SUSPEND     = 1,    // State is backup in DRAM, components power off.
    E_POWER_RESUME      = 2,    // Resume from Suspend or Hibernate mode
    E_POWER_MECHANICAL  = 3,    // Full power off mode. System return to working state only after full reboot 
    E_POWER_SOFT_OFF    = 4,    // The system appears to be off, but some components remain powered for trigging boot-up.
} EN_POWER_MODE;

//
// poll types
//

#ifndef POLLIN
#define POLLIN      0x01
#endif

#ifndef POLLOUT
#define POLLOUT     0x02
#endif

#ifndef POLLHUP
#define POLLHUP     0x04
#endif

//
// device I/O operations
//
struct devio
{
    int     (*open) (device_t dev, int mode);
    int     (*close)(device_t dev);
//    int     (*read) (device_t dev, char *buf, size_t len, int off);
    int     (*read) (device_t dev, char *buf, MS_U32 len, int off);
//    int     (*write)(device_t dev, const char *buf, size_t len, int off);
    int     (*write)(device_t dev, const char *buf, MS_U32 len, int off);
    int     (*poll) (device_t dev, int types);
    int     (*ioctl)(device_t dev, int request, unsigned long arg);
    int     (*event)(eDEVEVT evt);
};


#define DEVICE_MAGIC    (('D' << 24) | ('E' << 16) | ('V' << 8) | 'I')

//
// device structure
//
struct device
{
    int             magic;              // magic number
    int             refcnt;             // reference count
    int             flags;              // device characteristics
    struct devio    *devio;             // device i/o table
};

#define device_valid(dev) ((dev)->magic == DEVICE_MAGIC)
#endif /* __PRANA_DEVICE_H__ */

//MSTAR Module ID
/*******************************************************************************
!!!! WARNING NOT ALLOW MODIFY EXISTED VALUE !!!!
!!!! ONLY ALLOW ADD NEW VALUE AFTER END OF THIS LIST !!!!
*******************************************************************************/
#define MS_MODULE_HW                0x0000

#define MS_MODULE_CHIPTOP           0x0011
#define MS_MODULE_MIU               0x0012
#define MS_MODULE_WDT               0x003C
#define MS_MODULE_CFG               0x00F0                              // Chip hard configuration info
#define MS_MODULE_OTP               0x00F4
#define MS_MODULE_SPRAM             0x00F5

#define MS_MODULE_ACE               0x0101
#define MS_MODULE_AUDIO             0x0102
#define MS_MODULE_AVD               0x0103
#define MS_MODULE_BDMA              0x0104
#define MS_MODULE_DLC               0x0105
#define MS_MODULE_FLASH             0x0106
#define MS_MODULE_GE                0x0107
#define MS_MODULE_GOP               0x0108
#define MS_MODULE_HVD               0x0109
#define MS_MODULE_HWI2C             0x010a
#define MS_MODULE_IR                0x010b
#define MS_MODULE_IRQ               0x010c
#define MS_MODULE_JPD               0x010d
#define MS_MODULE_MBX               0x010e
#define MS_MODULE_MVD               0x010f
#define MS_MODULE_MVOP              0x0120
#define MS_MODULE_RVD               0x0122
#define MS_MODULE_SC                0x0123
#define MS_MODULE_TSP               0x0124
#define MS_MODULE_UART              0x0125
#define MS_MODULE_VPU               0x0126
#define MS_MODULE_XC                0x0127
#define MS_MODULE_PNL               0x0128
#define MS_MODULE_ISP               0x0129
#define MS_MODULE_PFSH              0x012a
#define MS_MODULE_GPIO              0x012b
#define MS_MODULE_PM                0x012c
#define MS_MODULE_VBI               0x012d
#define MS_MODULE_PCMCIA            0x012e
#define MS_MODULE_PIU               0x012f
#define MS_MODULE_MHEG5             0x0130
#define MS_MODULE_RTC_0             0x0131
#define MS_MODULE_RTC_2             0x0132
#define MS_MODULE_VIF               0x0133
#define MS_MODULE_MFE               0x0134
#define MS_MODULE_DIP               0x0135
#define MS_MODULE_RASP              0x0136
#define MS_MODULE_MMFILEIN          0x0137
#define MS_MODULE_MPIF              0x0138
#define MS_MODULE_GPD               0x0139
#define MS_MODULE_TSO               0x013a
#define MS_MODULE_CMDQ              0x013b
#define MS_MODULE_MSPI              0x013c

#define MS_MODULE_SEM               0x02f0

#define MS_MODULE_CA                0x0300                              // CA reserved
#define MS_MODULE_NDS               0x0310                              // NDS
#define MS_MODULE_NSK               0x0311
#define MS_MODULE_CAM               0x0312
#define MS_MODULE_NGA               0x0313

#define MS_MODULE_PWM               0x1032
#define MS_MODULE_DMD               0x1033
#define MS_MODULE_PWS               0x1034
#define MS_MODULE_EFUSE             0x1035

#define MS_MODULE_FRC               0x2000                              // A5 only


