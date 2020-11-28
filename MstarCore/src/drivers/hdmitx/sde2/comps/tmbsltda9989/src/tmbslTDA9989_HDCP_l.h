/**
 * Copyright (C) 2008 NXP N.V., All Rights Reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of NXP N.V. and is confidential in nature. Under no circumstances
 * is this software to be  exposed to or placed under an Open Source License of
 * any type without the expressed written permission of NXP N.V.
 *
 * \file          tmbslTDA9989_HDCP_l.h
 *
 * \version       %version: 1 %
 *
 * \date          %date_modified: %
 *
 * \brief         BSL driver component local definitions for the TDA998x
 *                HDMI Transmitter.
 *
 * \section info  Change Information
 *
 *
*/

#ifndef TMBSLTDA9989_HDCP_L_H
#define TMBSLTDA9989_HDCP_L_H

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TMFL_HDCP_SUPPORT

extern tmErrorCode_t tmbslTDA9989handleBKSVResultSecure(tmUnitSelect_t txUnit);

#define HDCP_F1 {                                                      \
      /* Enable EESS if HDCP 1.1 receiver and if 1.1 not disabled */   \
      if (((pDis->HdcpBcaps & E_MASKREG_P12_BCAPS_RX_1_1) > 0)     \
          && ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_NO_1_1) == 0)) \
         {regVal = 1;}                                                  \
      else                                                              \
         {regVal = 0;}                                                  \
   }
   
#define HDCP_F2 {                                                       \
   err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,                \
                            E_MASKREG_P12_TX0_rpt_sr, 1);          \
   RETIF_REG_FAIL(err);                                                 \
   err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,                \
                            E_MASKREG_P12_TX0_rpt_sr, 0);          \
   RETIF_REG_FAIL(err);                                                 \
}

#define HDCP_F3 {                                           \
      if (fInterruptStatus & (1 << HDMITX_CALLBACK_INT_R0))     \
         {                                                      \
            err = tmbslTDA9989handleBKSVResultSecure(txUnit);   \
            RETIF(err != TM_OK, err);                           \
         }                                                      \
   }

#else

#define HDCP_F1 {regVal = 0;}

#define HDCP_F2 {}

#define HDCP_F3 {}

#endif /*TMFL_HDCP_SUPPORT*/

#ifdef __cplusplus
}
#endif

#endif /* TMBSLTDA9989_HDCP_L_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/
