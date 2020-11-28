/**
  Copyright (C) 2006 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmsysOM3869Instance.h
 *                %version: 2 %
 *
 * \date          %date_modified%
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *
 * Detailed description may be added here.
 *
 * \section info Change Information
 *
 * \verbatim
   Date          Modified by CRPRNr  TASKNr  Maintenance description
   -------------|-----------|-------|-------|-----------------------------------
   26-Nov-2007  | V.VRIGNAUD|       |       | COMPATIBILITY WITH NXPFE
                | C.CAZETTES|       |       | 
   -------------|-----------|-------|-------|-----------------------------------
                |           |       |       |
   -------------|-----------|-------|-------|-----------------------------------
   \endverbatim
 *
*/
#ifndef _TMSYSOM3869_INSTANCE_H //-----------------
#define _TMSYSOM3869_INSTANCE_H

#ifdef __cplusplus
extern "C" {
#endif


tmErrorCode_t OM3869AllocInstance (tmUnitSelect_t tUnit, pptmOM3869Object_t ppDrvObject);
tmErrorCode_t OM3869DeAllocInstance (tmUnitSelect_t tUnit);
tmErrorCode_t OM3869GetInstance (tmUnitSelect_t tUnit, pptmOM3869Object_t ppDrvObject);


#ifdef __cplusplus
}
#endif

#endif // _TMSYSOM3869_INSTANCE_H //---------------
