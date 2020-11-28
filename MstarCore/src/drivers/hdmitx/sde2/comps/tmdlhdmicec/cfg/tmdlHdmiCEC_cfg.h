/**
 * Copyright (C) 2006 NXP N.V., All Rights Reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of NXP N.V. and is confidential in nature. Under no circumstances
 * is this software to be  exposed to or placed under an Open Source License of
 * any type without the expressed written permission of NXP N.V.
 *
 * \file          tmdlHdmiCEC_cfg.h
 *
 * \version       $Revision: 1 $
 *
 * \date          $Date:  $
 *
 * \brief         devlib driver component API for the CEC messages
 *
 * \section refs  Reference Documents
 *
 * \section info  Change Information
 *
 * \verbatim
 *
   $History:  tmdlHdmiCEC_cfg.h
 *
 *
   \endverbatim
 *
*/
/******************************************************************************
******************************************************************************
*                THIS FILE MUST NOT BE MODIFIED BY CUSTOMER                  *
******************************************************************************
*****************************************************************************/

#ifndef TMDLHDMICEC_CFG_H
#define TMDLHDMICEC_CFG_H

#include "hdmitx/sde2/inc/tmNxTypes.h"
#include "hdmitx/sde2/comps/tmdlhdmicec/inc/tmdlHdmiCEC_Types.h"
#include "hdmitx/sde2/comps/tmdlhdmicec/inc/tmdlHdmiCEC_Functions.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Number of HW units supported by SW driver */
#define MAX_UNITS 1


#ifndef TMFL_CEC_AVAILABLE
typedef struct _tmbslHdmiTxSysArgs_t
{
    UInt8 slaveAddr;
    UInt8 firstRegister;
    UInt8 lenData;
    UInt8 *pData;
} tmbslHdmiTxSysArgs_t;
#endif



/*============================================================================*/
/*                          TYPES DECLARATIONS                                */
/*============================================================================*/
typedef struct
{
    UInt8                         commandTaskPriority;
    UInt8                         commandTaskStackSize;
    UInt8                         commandTaskQueueSize;
    UInt8                         i2cAddress;
    ptmdlHdmiCecSysFunc_t         i2cReadFunction;
    ptmdlHdmiCecSysFunc_t         i2cWriteFunction;
    tmdlHdmiCecCapabilities_t     *pCapabilitiesList;
} tmdlHdmiCecDriverConfigTable_t;

/*============================================================================*/
/*                       FUNCTIONS DECLARATIONS                               */
/*============================================================================*/

/**
    \brief This function allows to the main driver to retrieve its
           configuration parameters.

    \param pConfig Pointer to the config structure

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent

******************************************************************************/
tmErrorCode_t tmdlHdmiCecCfgGetConfig
(
    tmUnitSelect_t                 unit,
    tmdlHdmiCecDriverConfigTable_t *pConfig
);


#ifdef __cplusplus
}
#endif

#endif /* TMDLHDMICEC_CFG_H */

/*============================================================================*/
/*                               END OF FILE                                  */
/*============================================================================*/
