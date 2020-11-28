/**
 * Copyright (C) 2006 Koninklijke Philips Electronics N.V., All Rights Reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of Koninklijke Philips Electronics N.V. and is confidential in
 * nature. Under no circumstances is this software to be  exposed to or placed
 * under an Open Source License of any type without the expressed written
 * permission of Koninklijke Philips Electronics N.V.
 *
 * \file          tmdlHdmiCEC_local.c
 *
 * \version       $Revision:  $
 *
 * \date          $Date: $
 *
 * \brief         dev lib driver component for the CEC messages
 *
 * \section refs  Reference Documents
 * \section info  Change Information
 *
 * \verbatim
   $History: tmdlHdmiCEC_local.c $
 * 
   \endverbatim
 *
*/

/*============================================================================*/
/*                   FILE CONFIGURATION                                       */
/*============================================================================*/

/* Defining this symbol on the compiler command line excludes some API checks */
/* #define NO_RETIF_BADPARAM */

/*============================================================================*/
/*                   STANDARD INCLUDE FILES                                   */
/*============================================================================*/


/*============================================================================*/
/*                   PROJECT INCLUDE FILES                                    */
/*============================================================================*/
#ifdef TMFL_LINUX_OS_KERNEL_DRIVER
#include <linux/kernel.h>
#else
//#include <string.h>
#endif
#include "hdmitx/sde2/comps/tmdlhdmicec/inc/tmdlHdmiCEC.h"
#include "tmdlHdmiCEC_local.h"
#include "hdmitx/sde2/inc/M_supply_type.h"
/*============================================================================*/
/*                   MACRO DEFINITIONS                                        */
/*============================================================================*/

/*============================================================================*/
/*                   TYPE DEFINITIONS                                         */
/*============================================================================*/

/*============================================================================*/
/*                   PUBLIC VARIABLE DEFINITIONS                              */
/*============================================================================*/

/*============================================================================*/
/*                   STATIC VARIABLE DECLARATIONS                             */
/*============================================================================*/

/**
 * Lookup table to map an 8-bit mask to a number of left shifts
 * needed to shift a value starting at bit 0 onto the mask.
 * Indexed by mask 0-255. For example, mask 0x00 and 0x01 need
 * no shift, mask 0x02 needs one shift, mask 0x03 needs no shift,
 * mask 0x04 needs 2 shifts, etc.
 * Rows were formatted by "HDMI Driver - Register List.xls" and pasted here
 */
static CONST_DAT UInt8 kMaskToShift[256] =
{/* Mask index: */
 /*x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC xD xE xF        */
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 1x */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 2x */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 3x */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 4x */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 5x */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 6x */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 7x */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 8x */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 9x */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* Ax */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* Bx */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* Cx */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* Dx */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* Ex */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0  /* Fx */
};

/*============================================================================*/
/*                   STATIC FUNCTION DECLARATIONS                             */
/*============================================================================*/

/*============================================================================*/
/*                   PUBLIC FUNCTION DEFINITIONS                              */
/*============================================================================*/

/*============================================================================*/
/* getCecHwRegisters                                                             */
/*============================================================================*/
tmErrorCode_t
getCecHwRegisters
(
    tmdlHdmiCecDriverConfigTable_t *pDis, 
    UInt8  regAddr,
    UInt8  *pData, 
    UInt16 lenData
    )
{
    tmErrorCode_t        err;     /* Error code */
    tmdlHdmiCecSysArgs_t sysArgs; /* Arguments passed to system function   */

    /* Get I2C register range - all non-OK results are errors */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = (UInt8)lenData;
    sysArgs.pData           = pData;
    err = pDis->i2cReadFunction(&sysArgs);
    return (err == TM_OK) ? TM_OK : TMDL_ERR_DLHDMICEC_I2C_READ;
}

/*============================================================================*/
/* getCecHwRegister                                                              */
/*============================================================================*/
tmErrorCode_t
getCecHwRegister
(
    tmdlHdmiCecDriverConfigTable_t *pDis, 
    UInt8 regAddr, 
    UInt8 *pRegValue
)
{
    tmErrorCode_t        err;     /* Error code */
    tmdlHdmiCecSysArgs_t sysArgs; /* Arguments passed to system function   */

    /* Get I2C register - all non-OK results are errors */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = 1;
    sysArgs.pData           = pRegValue;
    err = pDis->i2cReadFunction(&sysArgs);
    return (err == TM_OK) ? TM_OK : TMDL_ERR_DLHDMICEC_I2C_READ;

}

/*============================================================================*/
/* setCecHwRegisters                                                             */
/*============================================================================*/
tmErrorCode_t
setCecHwRegisters
(
    tmdlHdmiCecDriverConfigTable_t *pDis, 
    UInt8  regAddr,
    UInt8  *pData, 
    UInt16 lenData
    )
{
    tmErrorCode_t        err;     /* Error code */
    tmdlHdmiCecSysArgs_t sysArgs; /* Arguments passed to system function   */
    
    /* Write to I2C register range - all non-OK results are errors */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = (UInt8)lenData;
    sysArgs.pData           = pData;
    err = pDis->i2cWriteFunction(&sysArgs);
    return (err == TM_OK) ? TM_OK : TMDL_ERR_DLHDMICEC_I2C_WRITE;
}

/*============================================================================*/
/* setCecHwRegisterMsbLsb                                                        */
/*============================================================================*/
tmErrorCode_t
setCecHwRegisterMsbLsb
(
    tmdlHdmiCecDriverConfigTable_t *pDis, 
    UInt8  regAddr, 
    UInt16 regWord
)
{
    tmErrorCode_t        err;        /* Error code */
    UInt8                msbLsb[2];  /* The bytes from regWord                  */
    tmdlHdmiCecSysArgs_t sysArgs; /* Arguments passed to system function   */

    /* Unpack regWord bytes, MSB first */
    msbLsb[0] = (UInt8)(regWord >> 8);
    msbLsb[1] = (UInt8)(regWord & 0xFF);

    /* Write to I2C - all non-OK results are errors */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = 2;
    sysArgs.pData           = &msbLsb[0];
    err = pDis->i2cWriteFunction(&sysArgs);
    return (err == TM_OK) ? TM_OK : TMDL_ERR_DLHDMICEC_I2C_WRITE;
}

/*============================================================================*/
/* setCecHwRegister                                                              */
/*============================================================================*/
tmErrorCode_t
setCecHwRegister
(
    tmdlHdmiCecDriverConfigTable_t *pDis, 
    UInt8 regAddr, 
    UInt8 regValue
)
{
    tmErrorCode_t        err;     /* Error code */
    tmdlHdmiCecSysArgs_t sysArgs; /* Arguments passed to system function   */

    /* Write to I2C - all non-OK results are errors */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = 1;
    sysArgs.pData           = &regValue;
    err = pDis->i2cWriteFunction(&sysArgs);
    return (err == TM_OK) ? TM_OK : TMDL_ERR_DLHDMICEC_I2C_WRITE;
}

/*============================================================================*/
/*  setCecHwRegisterField                                                        */
/*============================================================================*/
tmErrorCode_t
setCecHwRegisterField
(
    tmdlHdmiCecDriverConfigTable_t *pDis, 
    UInt8 regAddr, 
    UInt8 fieldMask, 
    UInt8 fieldValue
)
{
    tmErrorCode_t        err;        /* Error code */
    UInt8                regValue;   /* The register's current value            */
    tmdlHdmiCecSysArgs_t sysArgs; /* Arguments passed to system function   */

    /* Read I2C register value.
     * All bitfield registers are either shadowed or can be read.
     */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = 1;
    sysArgs.pData           = &regValue;
    err = pDis->i2cReadFunction(&sysArgs);
    RETIF(err != TM_OK, TMDL_ERR_DLHDMICEC_I2C_READ)

    /* Reset register bits that are set in the mask */
    regValue = regValue & (UInt8)(~fieldMask);

    /* Shift the field value left to align its bits with the mask */
    fieldValue <<= kMaskToShift[fieldMask];

    /* Reset shifted field bits that are not set in the mask */
    fieldValue &= fieldMask;

    /* Set the shifted bitfield */
    regValue |= fieldValue;

    /* Write to I2C - all non-OK results are errors */
    sysArgs.slaveAddr       = pDis->i2cAddress;
    sysArgs.firstRegister   = regAddr;
    sysArgs.lenData         = 1;
    sysArgs.pData           = &regValue;
    err = pDis->i2cWriteFunction(&sysArgs);
    return (err == TM_OK) ? TM_OK : TMDL_ERR_DLHDMICEC_I2C_WRITE;
}


/*============================================================================*/
/*                   STATIC FUNCTION DEFINTIONS                               */
/*============================================================================*/

/*============================================================================*/
/*                     END OF FILE                                            */
/*============================================================================*/
