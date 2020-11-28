/*
  Copyright (C) 2012 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18275_Instance.h
 *
 * \date          %modify_time%
 *
 * \author        Michael VANNIER
 *                
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18275_Driver_User_Guide.pdf
 *
 *
 * \section info Change Information
 *
*/

#ifndef _TMBSL_TDA18275_INSTANCE_H
#define _TMBSL_TDA18275_INSTANCE_H

#ifdef __cplusplus
extern "C"
{
#endif


tmErrorCode_t
iTDA18275_AllocInstance(tmUnitSelect_t tUnit, ppTDA18275Object_t ppDrvObject);

tmErrorCode_t
iTDA18275_DeAllocInstance(pTDA18275Object_t pDrvObject);

tmErrorCode_t
iTDA18275_GetInstance(tmUnitSelect_t tUnit, ppTDA18275Object_t ppDrvObject);

tmErrorCode_t
iTDA18275_ResetInstance(pTDA18275Object_t pDrvObject);


#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18275_INSTANCE_H */

