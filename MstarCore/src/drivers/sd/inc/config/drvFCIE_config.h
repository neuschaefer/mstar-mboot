////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef __DRVFCIE_CONFIG_H__
#define __DRVFCIE_CONFIG_H__

#define FALSE           0
#define TRUE            1

#ifdef CONFIG_AMBER5
#include "drvFCIE_a5_uboot.h"
#endif

#if (ENABLE_EAGLE)
#include "drvFCIE_eagle_uboot.h"
#elif (ENABLE_EIFFEL)
#include "drvFCIE_eiffel_uboot.h"
#elif (ENABLE_NIKE)
#include "drvFCIE_nike_uboot.h"
#elif (ENABLE_MADISON)
#include "drvFCIE_madison_uboot.h"
#elif (ENABLE_CLIPPERS)
#include "drvFCIE_clippers_uboot.h"
#elif (ENABLE_MIAMI)
#include "drvFCIE_miami_uboot.h"
#elif (ENABLE_NADAL)
#include "drvFCIE_nadal_uboot.h"
#elif (ENABLE_AMBER3)
#include "drvFCIE_a3_uboot.h"
#elif (ENABLE_AGATE)
#include "drvFCIE_agate_uboot.h"
#elif (ENABLE_EINSTEIN)
#include "drvFCIE_einstein_uboot.h"
#elif (ENABLE_NAPOLI)
#include "drvFCIE_napoli_uboot.h"
#elif (ENABLE_MONACO)
#include "drvFCIE_monaco_uboot.h"
#elif (ENABLE_MUJI)
#include "drvFCIE_muji_uboot.h"
#elif (ENABLE_CELTICS)
#include "drvFCIE_celtics_uboot.h"
#elif (ENABLE_KAISER)
#include "drvFCIE_kaiser_uboot.h"
#else
#error "Wrong chip setting!"
#endif

#define CARDDET_CDZ         BIT00
#define CARDDET_INSERT_LOW  BIT01
#define CARDDET_INSERT_HIGH BIT02


#define SDIO_MODE_GPIO_PAD_BPS			1
#define SDIO_MODE_GPIO_PAD_SDR			2
#define SDIO_MODE_8BITS_MACRO_SDR		3
#define SDIO_MODE_8BITS_MACRO_DDR		4
#define SDIO_MODE_32BITS_MACRO_DDR		5
#define SDIO_MODE_32BITS_MACRO_HS200	6
#define SDIO_MODE_UNKNOWN				7

void HalFcie_SwitchPad(unsigned char);
//E_IO_STS HalFcie_WaitMieEvent(U16 u16ReqVal, U32 u32WaitMs)


#endif

