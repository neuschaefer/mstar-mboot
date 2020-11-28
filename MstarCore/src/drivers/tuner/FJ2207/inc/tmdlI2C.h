/**
  Copyright (C) 2008 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmdlI2C.h
 *                %version: 4 %
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
   9-JULY-2007  | A.TANT    |       |       | CREATION OF I2C ARCHITECTURE 2.0.0
   -------------|-----------|-------|-------|-----------------------------------
                |           |       |       |
   -------------|-----------|-------|-------|-----------------------------------
   \endverbatim
 *
*/


#ifndef TMDLI2C_H
#define TMDLI2C_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

/*============================================================================*/
/*                       MACRO DEFINITION                                     */
/*============================================================================*/

/* SW Error codes */
#define I2C_ERR_BASE               (CID_COMP_PARPORT | CID_LAYER_HWAPI)
#define I2C_ERR_COMP               (CID_COMP_PARPORT | CID_LAYER_HWAPI | TM_ERR_COMP_UNIQUE_START)

#define I2C_ERR_BAD_UNIT_NUMBER    (I2C_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define I2C_ERR_NOT_INITIALIZED    (I2C_ERR_BASE + TM_ERR_NOT_INITIALIZED)
//#define I2C_ERR_INIT_FAILED        (I2C_ERR_BASE + TM_ERR_INIT_FAILED)
#define I2C_ERR_BAD_PARAMETER      (I2C_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define I2C_ERR_NOT_SUPPORTED      (I2C_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define I2C_ERR_NOT_INSTALLED      (I2C_ERR_COMP + 0x0001)
#define I2C_ERR_FAILED             (I2C_ERR_COMP + 0x0002)
#define I2C_ERR_HW                 (I2C_ERR_COMP + 0x0003)
//#define I2C_ERR_NOT_READY          (I2C_ERR_COMP + 0x0002)
//#define I2C_ERR_BAD_CRC            (I2C_ERR_COMP + 0x0003)
//#define I2C_ERR_BAD_VERSION        (I2C_ERR_COMP + 0x0004)

    typedef enum _tmI2CInterfaceType_t {
        tmI2CInterfaceUnknown = 0,  /* No I2C Interface Defined */
        tmI2CInterfaceURTParallel,  /* URT Parallel I2C Interface */
        tmI2CInterfaceURTUSB,       /* URT USB I2C Interface */
        tmI2CInterfaceMMPParallel,  /* MMP Parallel I2C Interface */
        tmI2CInterfaceCypressUSB,   /* Cypress USB I2C Interface */
        tmI2CInterfaceCustomer,     /* Customer I2C Interface */
        tmI2CInterfaceSienaUSB,     /* Siena USB I2C Interface */
        tmI2CInterfaceMax
    } tmI2CInterfaceType_t, *ptmI2CInterfaceType_t;

    typedef enum _tmI2CPortType_t {
        tmI2CPortUnknown = 0,   /* No Port Type Defined */
        tmI2CPortLPT1,          /* LPT1 Port Type */
        tmI2CPortLPT2,          /* LPT2 Port Type */
        tmI2CPortLPT3,          /* LPT3 Port Type */
        tmI2CPortUSB,           /* USB Port Type */
        tmI2CPortMax
    } tmI2CPortType_t, *ptmI2CPortType_t;

    typedef enum _tmI2CAction_t
    {
        tmI2CActionUnknown,
        tmI2CActionWrite = 0,
        tmI2CActionRead,
        tmI2CActionMax
    }   tmI2CAction_t, *ptmI2CAction_t;

    typedef enum
    {
        tmI2CIdentModeUnknown = 0,
        tmI2CIdentModePosition,
        tmI2CIdentModeInstanceIndex,
        tmI2CIdentModeSerialNumber,
        tmI2CIdentModeMax
    } tmI2CIdentMode_t, *ptmI2CIdentMode_t;

    typedef struct _tmI2CLLDriverVersion
    {
        UInt32  major;
        UInt32  minor;
        UInt32  build;
        UInt32  revision;
    } tmI2CLLDriverVersion, *ptmI2CLLDriverVersion;

    // Serial Number
    typedef struct _tmI2CSerialNumber
    {
        Bool    biSerialNumberAvailable;
        UInt8   iSerialNumber[32];
        UInt32  dwInstanceIndex;
    } tmI2CSerialNumber, *ptmI2CSerialNumber;

    // Enumeration
    typedef struct _tmI2CEnumDevices
    {
        UInt32              dwInstanceCount;
        tmI2CSerialNumber   devices[8];
    } tmI2CEnumDevices, *ptmI2CEnumDevices;

    typedef struct _tmI2CInterfaceConfig_t
    {
        tmI2CInterfaceType_t    eInterfaceType;         /* Interface Type */
        tmI2CPortType_t         ePortType;              /* Port Type */
        tmI2CIdentMode_t        tIdentificationMode;
        union
        {
            UInt8               position;
            UInt32              dwInstanceIndex;
            UInt8               serialNumber[32];
        }Identification;
        UInt32                  dwAdditionalDataSize;   /* Additional Data Size */
        void*                   pAdditionalData;        /* Additional Data Pointer */
    } tmI2CInterfaceConfig_t, *ptmI2CInterfaceConfig_t;

    // Callback for I2C Log
    typedef tmErrorCode_t (*w_tmdlI2CCallBack) (tmUnitSelect_t tUnit, CUInt32 uHwAddress, CUInt32 addrSize, CUInt8* pAddr, CUInt32 dataSize, CUInt8* pData, tmErrorCode_t err, tmI2CAction_t i2cAction, Bool bHwAddrAsWriteAddr);

/*============================================================================*/
/*                       ENUM OR TYPE DEFINITION                              */
/*============================================================================*/


/*============================================================================*/
/*                       EXTERN DATA DEFINITION                               */
/*============================================================================*/



/*============================================================================*/
/*                       EXTERN FUNCTION PROTOTYPES                           */
/*============================================================================*/


extern tmErrorCode_t
tmdlI2CGetSWVersion
(
    ptmSWVersion_t   pSWVersion  /*  O: Receives SW Version  */
);

extern tmErrorCode_t
tmdlI2CGetLowLevelSWVersion
(
    tmUnitSelect_t          tUnit,
    ptmSWVersion_t          pSWVersion,     /*  O: Receives SW Version  */
    ptmI2CLLDriverVersion   pLLSWVersion    /*  O: Receives LL SW Version  */
);

extern tmErrorCode_t
tmdlI2CGetLowLevelDevices
(
    tmUnitSelect_t      tUnit,
    ptmI2CEnumDevices   pDevices    /*  O: Receives LL Devices */
);

extern tmErrorCode_t
tmdlI2CInit
(
    tmUnitSelect_t  tUnit,   /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t* psSrvFunc
);

extern tmErrorCode_t
tmdlI2CDeInit
(
    tmUnitSelect_t  tUnit
);

extern tmErrorCode_t
tmdlI2CSetInterface
(
    tmUnitSelect_t  tUnit,
    ptmI2CInterfaceConfig_t psI2CInterface
);

extern tmErrorCode_t
tmdlI2CGetInterface
(
    tmUnitSelect_t  tUnit,
    ptmI2CInterfaceConfig_t psI2CInterface
);

extern tmErrorCode_t
tmdlI2CWrite
(
    tmUnitSelect_t  tUnit,
    UInt32          uHwAddress,
    UInt32          AddrSize,
    UInt8*          pAddr,
    UInt32          WriteLen,
    UInt8*          pData
);

extern tmErrorCode_t
tmdlI2CRead
(
    tmUnitSelect_t  tUnit,
    UInt32          uHwAddress,
    UInt32          AddrSize,
    UInt8*          pAddr,
    UInt32          ReadLen,
    UInt8*          pData
);

extern tmErrorCode_t
tmdlI2CSetErrorEnable
(
    tmUnitSelect_t  tUnit,
    Bool            bErrorEnable
);

extern tmErrorCode_t
tmdlI2CGetErrorEnable
(
    tmUnitSelect_t  tUnit,
    Bool*           pbErrorEnable
);

extern tmErrorCode_t
tmdlI2CSetPortType
(
    tmUnitSelect_t  tUnit,
    tmI2CPortType_t dwPortType
);

extern tmErrorCode_t
tmdlI2CGetPortType
(
    tmUnitSelect_t      tUnit,
    ptmI2CPortType_t    pdwPortType
);

extern tmErrorCode_t
tmdlI2CSetBitrate
(
    tmUnitSelect_t  tUnit,
    UInt32          dwBitrate
);

extern tmErrorCode_t
tmdlI2CGetBitrate
(
    tmUnitSelect_t  tUnit,
    UInt32*         pdwBitrate
);

extern tmErrorCode_t
tmdlI2CSetHwAddrAsWriteAddr
(
    tmUnitSelect_t  tUnit,
    Bool            bHwAddrAsWriteAddr
);

extern tmErrorCode_t
tmdlI2CGetHwAddrAsWriteAddr
(
    tmUnitSelect_t  tUnit,
    Bool*           pbHwAddrAsWriteAddr
);

#ifdef __cplusplus
}
#endif

#endif /* TMDLI2C_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

