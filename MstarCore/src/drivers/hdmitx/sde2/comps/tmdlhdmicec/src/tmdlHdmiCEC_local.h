//=============================================================================
// Copyright (C) 2007 NXP N.V., All Rights Reserved.
// This source code and any compilation or derivative thereof is the proprietary
// information of NXP N.V. and is confidential in nature. Under no circumstances
// is this software to be  exposed to or placed under an Open Source License of
// any type without the expressed written permission of NXP N.V.
//=============================================================================
/*!
    \file    tmdlHdmiCEC_local.h

	\version 1.0

	\date    24/07/2007

 	\brief   devlib driver component API for the CEC messages.

    \section refs  Reference Documents
             TDA998X Driver - tmdlHdmiTx - SCS.doc
    \note    None.
 
    HISTORY :
    \verbatim
     Date          Modified by CRPRNr  TASKNr  Maintenance description
     -------------|-----------|-------|-------|-----------------------------------
     24/07/2007   |  F.G      |       |       | Creation.
     -------------|-----------|-------|-------|-----------------------------------
    \endverbatim
*/
//==========================================================================

#ifndef TMDLHDMICEC_LOCAL_H
#define TMDLHDMICEC_LOCAL_H

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/
//#include "tmdlHdmiCEC_IW.h"
#include "hdmitx/sde2/comps/tmdlhdmicec/cfg/tmdlHdmiCEC_cfg.h"


#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
/*                       MACRO DEFINITIONS                                    */
/*============================================================================*/

/* Version of the SW driver */
#define VERSION_COMPATIBILITY 0
#define VERSION_MAJOR         1
#define VERSION_MINOR         4

/**
 * A macro to check a condition and if true return a result
 */
#define RETIF(cond, rslt)       if ((cond)){HDMI_TRACE("RERIF") return (rslt);}

/**
 * A macro to check a condition and if true return 
 * TMBSL_ERR_HDMI_BAD_PARAMETER.
 * To save code space, it can be compiled out by defining NO_RETIF_BADPARAM on
 * the compiler command line.
 */
#ifdef NO_RETIF_BADPARAM
#define RETIF_BADPARAM(cond)
#else
#define RETIF_BADPARAM(cond)  if ((cond)){ HDMI_TRACE("RETIF_BADPARAM")return TMBSL_ERR_HDMI_BAD_PARAMETER;}
#endif

/**
 * A macro to check the result of a register API and if not TM_OK to return it.
 * To save code space, it can be compiled out by defining NO_RETIF_REG_FAIL on
 * the compiler command line.
 */
#ifdef NO_RETIF_REG_FAIL
#define RETIF_REG_FAIL(result)
#else
#define RETIF_REG_FAIL(result)  if ((result) != TM_OK){HDMI_TRACE("RETIF_REG_FAIL")return (result);}
#endif

#define TDA9950_RESET_DELAY_MS 250

/*============================================================================*/
/*                       ENUM OR TYPE DEFINITIONS                             */
/*============================================================================*/

#ifdef TMFL_TDA9989

#define E_REG_ENAMODS	0xFF
#define E_REG_CEC_CLK	0xF6
#define E_REG_CEC_INT	0xEE
#define E_REG_COMBI_INT	0xEC
#define DEFAULT_ENAMODS 0x81
#define CEC_CLK_SEL	0xE6
#define CEC_INT_MASK	0x01

#define E_REG_CEC_CAL_XOSC_CTRL1 0xF2
#define E_REG_CEC_DES_FREQ2      0xF5


#define CEC_AUTOMATIC_CALIBRATION_MSK    0x7F
#define CEC_SELECT_FRO_CLOCK_SOURCE      0x11
#define CEC_ENABLE_CEC_CLK_MSK           0x80
#define CEC_ENABLE_FRO_MSK               0xBF
#define CEC_ENABLE_CALIBRATION           0x01
#define CEC_DISABLE_CALIBRATION          0x00


#endif  /* TMFL_TDA9989 */

/*!
   \enum  CEC Stack Processor Regsiters 
   \brief The CSP is controlled via a series of registers
*/

enum _eReg
{
  E_REG_APR   = 0x00, /*!< Address Pointer Regsiter (Write)           */
  E_REG_CSR   = 0x00, /*!< CSP Status Register (Read)                 */
  E_REG_CER   = 0x01, /*!< CSP Error Register  (Read)                 */
  E_REG_CVR   = 0x02, /*!< CSP Version Register(Read)                 */
  E_REG_CCR   = 0x03, /*!< CSP Control Register (Read/Write)          */
  E_REG_ACKH  = 0x04, /*!< CEC Address ACK High Register (Read/Write) */
  E_REG_ACKL  = 0x05, /*!< CEC Address ACK Low Register (Read/Write)  */
  E_REG_CCONR = 0x06, /*!< CEC Config Register (Read/Write)           */
  E_REG_CDR0  = 0x07, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR1  = 0x08, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR2  = 0x09, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR3  = 0x0A, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR4  = 0x0B, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR5  = 0x0C, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR6  = 0x0D, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR7  = 0x0E, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR8  = 0x0F, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR9  = 0x10, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR10 = 0x11, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR11 = 0x12, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR12 = 0x13, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR13 = 0x14, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR14 = 0x15, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR15 = 0x16, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR16 = 0x17, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR17 = 0x18, /*!< CEC Data Register (Read/Write)             */
  E_REG_CDR18 = 0x19 /*!< CEC Data Register (Read/Write)             */
};


/* possible states of the state driver */
typedef enum
{
    CEC_STATE_NOT_INITIALIZED, /**< Driver is not initialized */
    CEC_STATE_UNLOCKED ,       /**< Driver is not locked */
    CEC_STATE_LOCKED,          /**< Driver is locked */
    CEC_STATE_CONFIGURED       /**< Driver is configured */
} tmdlHdmiCecDriverState_t;

/**
 * \brief The structure of a CEC object, one per device unit
*/
typedef struct
{
    tmInstance_t                  instance;
    tmdlHdmiCECLogicalAddress_t   DeviceLogicalAddress;
	Bool                          opened;                   /**< is unit instanciated ? */
    tmdlHdmiCecDeviceVersion_t    deviceVersion;            /**< Version of the HW device */
    tmdlHdmiCecDriverState_t      state;                    /**< Current state of the driver */
    ptmdlHdmiCecCallbackFunc_t    MessageCallback;         /**< Message callback */
}tmdlHdmiCecUnitConfig_t;


/**
 * \brief States of CEC Status
*/
#define CEC_MSG_SUCCESS	    			0x00	/*Message transmisson Succeed*/
#define CEC_CSP_OFF_STATE   			0x80	/*CSP in Off State*/
#define CEC_BAD_REQ_SERVICE 			0x81	/*Bad .req service*/
#define CEC_MSG_FAIL_UNABLE_TO_ACCESS	0x82	/*Message transmisson failed: Unable to access CEC line*/
#define CEC_MSG_FAIL_ARBITRATION_ERROR	0x83	/*Message transmisson failed: Arbitration error*/
#define CEC_MSG_FAIL_BIT_TIMMING_ERROR	0x84	/*Message transmisson failed: Bit timming error*/
#define CEC_MSG_FAIL_DEST_NOT_ACK		0x85	/*Message transmisson failed: Destination Address not aknowledged*/
#define CEC_MSG_FAIL_DATA_NOT_ACK		0x86	/*Message transmisson failed: Databyte not acknowledged*/


/*============================================================================*/
/*                       EXTERN DATA DEFINITION                               */
/*============================================================================*/

extern tmdlHdmiCecDriverConfigTable_t gtmdlHdmiCecDriverConfigTable[MAX_UNITS];

/*============================================================================*/
/*                       EXTERN FUNCTION PROTOTYPES                           */
/*============================================================================*/

tmErrorCode_t    getCecHwRegisters (tmdlHdmiCecDriverConfigTable_t *pDis, 
                                 UInt8  regAddr,
                                 UInt8 *pData, UInt16 lenData);
tmErrorCode_t    getCecHwRegister (tmdlHdmiCecDriverConfigTable_t *pDis, 
                                UInt8  regAddr,
                                UInt8 *pRegValue);
tmErrorCode_t    setCecHwRegisters (tmdlHdmiCecDriverConfigTable_t *pDis, 
                                 UInt8  regAddr,
                                 UInt8 *pData, UInt16 lenData);
tmErrorCode_t    setCecHwRegisterMsbLsb (tmdlHdmiCecDriverConfigTable_t *pDis, 
                                      UInt8  regAddr, 
                                      UInt16 regWord);
tmErrorCode_t    setCecHwRegister (tmdlHdmiCecDriverConfigTable_t *pDis, 
                                UInt8  regAddr,
                                UInt8 regValue);
tmErrorCode_t    setCecHwRegisterField (tmdlHdmiCecDriverConfigTable_t *pDis,
                                     UInt8  regAddr,
                                     UInt8 fieldMask, UInt8 fieldValue);


#ifdef __cplusplus
}
#endif

#endif /* TMDLHDMI_CEC_LOCAL_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/
