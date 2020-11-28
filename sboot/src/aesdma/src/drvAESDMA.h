/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _DRV_AESDMA_H_
#define _DRV_AESDMA_H_

#ifdef CONFIG_MSTAR_EDISON
#define AESDMA_HAL_EDISON       1
#endif

#ifdef CONFIG_MSTAR_EIFFEL
#define AESDMA_HAL_EIFFEL       1
#endif

#ifdef CONFIG_MSTAR_NIKE
#define AESDMA_HAL_NIKE         1
#endif

#ifdef CONFIG_MSTAR_MADISON
#define AESDMA_HAL_MADISON      1
#endif

#ifdef CONFIG_MSTAR_CLIPPERS
#define AESDMA_HAL_CLIPPERS     1
#endif

#ifdef CONFIG_MSTAR_MIAMI
#define AESDMA_HAL_MIAMI        1
#endif

#ifdef CONFIG_MSTAR_MONACO
#define AESDMA_HAL_MONACO       1
#endif

#ifdef CONFIG_MSTAR_MUJI
#define AESDMA_HAL_MUJI       1
#endif

#ifdef CONFIG_MSTAR_CELTICS
#define AESDMA_HAL_CELTICS       1
#endif

#ifdef CONFIG_MSTAR_NADAL
#define AESDMA_HAL_NADAL        1
#endif

#ifdef CONFIG_MSTAR_NUGGET
#define AESDMA_HAL_NUGGET       1
#endif

#ifdef CONFIG_MSTAR_EINSTEIN
#define AESDMA_HAL_EINSTEIN     1
#endif

#ifdef CONFIG_MSTAR_EINSTEIN3
#define AESDMA_HAL_EINSTEIN3    1
#endif

#ifdef CONFIG_MSTAR_NAPOLI
#define AESDMA_HAL_NAPOLI       1
#endif

//=====================================================
// do NOT edit the following content.
//=====================================================
#if defined(AESDMA_HAL_EDISON) && AESDMA_HAL_EDISON
  #include "hal/edison/halAESDMA.h"
#elif defined(AESDMA_HAL_EIFFEL) && AESDMA_HAL_EIFFEL
  #include "hal/eiffel/halAESDMA.h"
#elif defined(AESDMA_HAL_NIKE) && AESDMA_HAL_NIKE
  #include "hal/nike/halAESDMA.h"
#elif defined(AESDMA_HAL_MADISON) && AESDMA_HAL_MADISON
  #include "hal/madison/halAESDMA.h"
#elif defined(AESDMA_HAL_CLIPPERS) && AESDMA_HAL_CLIPPERS
  #include "hal/clippers/halAESDMA.h"
#elif defined(AESDMA_HAL_MIAMI) && AESDMA_HAL_MIAMI
  #include "hal/miami/halAESDMA.h"
#elif defined(AESDMA_HAL_MONACO) && AESDMA_HAL_MONACO
  #include "hal/monaco/halAESDMA.h"
#elif defined(AESDMA_HAL_MUJI) && AESDMA_HAL_MUJI
  #include "hal/muji/halAESDMA.h"
#elif defined(AESDMA_HAL_CELTICS) && AESDMA_HAL_CELTICS
  #include "hal/celtics/halAESDMA.h"
#elif defined(AESDMA_HAL_NADAL) && AESDMA_HAL_NADAL
    #include "hal/nadal/halAESDMA.h"
#elif defined(AESDMA_HAL_NUGGET) && AESDMA_HAL_NUGGET
  #include "hal/nugget/halAESDMA.h"
#elif defined(AESDMA_HAL_EINSTEIN) && AESDMA_HAL_EINSTEIN
  #include "hal/einstein/halAESDMA.h"
#elif defined(AESDMA_HAL_EINSTEIN3) && AESDMA_HAL_EINSTEIN3
  #include "hal/einstein3/halAESDMA.h"
#elif defined(AESDMA_HAL_NAPOLI) && AESDMA_HAL_NAPOLI
  #include "hal/napoli/halAESDMA.h"
#else
  #error "Error! no platform selected."
#endif



void MDrv_AESDMA_SecureAuthen(U32 u32SHAInBuf, U32 u32Size, U32 u32RSAInBuf, U32 u32SHAOutBuf, U32 u32RSAOutBuf, U32 u32SramSel);
U32 MDrv_AESDMA_SecureMain(U32 u32PlaintextAddr, U32 u32Size, U32 u32SignatureAddr, U32 u32SramSel);


#endif
