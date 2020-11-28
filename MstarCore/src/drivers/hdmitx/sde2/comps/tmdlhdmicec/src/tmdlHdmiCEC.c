//=============================================================================
// Copyright (C) 2007 NXP N.V., All Rights Reserved.
// This source code and any compilation or derivative thereof is the proprietary
// information of NXP N.V. and is confidential in nature. Under no circumstances
// is this software to be  exposed to or placed under an Open Source License of
// any type without the expressed written permission of NXP N.V.
//=============================================================================
/*!
    \file    tmdlHdmiCEC.c

    \version 1.0

    \date    24/07/2007

    \brief   devlib driver component API for the CEC features.

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

/*============================================================================*/
/*                   FILE CONFIGURATION                                       */
/*============================================================================*/


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
#include <stdio.h>
#endif
#include "hdmitx/sde2/comps/tmdlhdmicec/cfg/tmdlHdmiCEC_IW.h"
#include "hdmitx/sde2/comps/tmdlhdmicec/cfg/tmdlHdmiCEC_cfg.h"
#include "hdmitx/sde2/comps/tmdlhdmicec/inc/tmdlHdmiCEC.h"
#include "hdmitx/sde2/comps/tmdlhdmicec/src/tmdlHdmiCEC_local.h"

/*============================================================================*/
/*                   MACRO DEFINITIONS                                        */
/*============================================================================*/
#ifdef TMFL_LINUX_OS_KERNEL_DRIVER
#define DV_DBG_PRINT printk
#else
#define DV_DBG_PRINT printf
#endif

/*============================================================================*/
/*                   TYPE DEFINITIONS                                         */
/*============================================================================*/


/*============================================================================*/
/*                   PUBLIC VARIABLE DEFINITIONS                              */
/*============================================================================*/
tmdlHdmiCecUnitConfig_t UnitTable[MAX_UNITS] = {
    {0,CEC_LOGICAL_ADDRESS_UNREGISTRED_BROADCAST,False, TMDL_HDMICEC_DEVICE_TDA9950, CEC_STATE_NOT_INITIALIZED, 0}
};

tmdlHdmiCecDriverConfigTable_t gtmdlHdmiCecDriverConfigTable[MAX_UNITS];

tmdlHdmiCecSaveMessage_t gtmdlHdmiCecDriverSaveMessage;


/*============================================================================*/
/*                   STATIC CONSTANT DECLARATIONS                             */
/*============================================================================*/


/*============================================================================*/
/*                   STATIC VARIABLE DECLARATIONS                             */
/*============================================================================*/


/*============================================================================*/
/*                   STATIC FUNCTION DECLARATIONS                             */
/*============================================================================*/


/*============================================================================*/
/*                              FUNCTIONS                                     */
/*============================================================================*/

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGetSWVersion( )
    \brief Get the software version of the driver.

    \param pSWVersion Pointer to the version structure

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetSWVersion
(
    tmSWVersion_t  *pSWVersion
)
{
    /* check that input pointer is not NULL */
    RETIF(pSWVersion == Null, TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS)

    /* copy SW version */
    pSWVersion->compatibilityNr = VERSION_COMPATIBILITY;
    pSWVersion->majorVersionNr  = VERSION_MAJOR;
    pSWVersion->minorVersionNr  = VERSION_MINOR;

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGetNumberOfUnits( )
    \brief Get the number of available CEC devices in the system.
           A unit directly represents a physical device.

    \param pUnitCount Pointer to the number of available units.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetNumberOfUnits
(
    UInt32  *pUnitCount
)
{
    /* check that input pointer is not NULL */
    RETIF(pUnitCount == Null, TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS)

    /* copy the maximum number of units */
    *pUnitCount = MAX_UNITS;

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGetInstanceSetup( )
    \brief Get instance setup parameters.

    \param instance   Instance identifier.
    \param pSetupInfo Pointer to the structure that will receive setup
                      parameters

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetInstanceSetup
(
    tmInstance_t                instance,
    ptmdlHdmiCecInstanceSetup_t pSetupInfo
)
{
    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check that input pointer is not NULL */
    RETIF(pSetupInfo == Null, TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

    pSetupInfo->DeviceLogicalAddress  = UnitTable[instance].DeviceLogicalAddress;
    

    return(TM_OK);
}

//=========================	=================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecHandleInterrupt( )
    \brief Make device library handle an incoming interrupt. This function is
           used by application to tell the device library that the hardware
           sent an interrupt. It can also be used to poll the interrupt status
           of the device if the interrupt line is not physically connected to
           the CPU.
           This function is synchronous.
           This function is ISR friendly.


    \param instance   Instance identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_HANDLE: the handle number is wrong
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_FULL: the queue is full
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecHandleInterrupt
(
    tmInstance_t    instance
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_ReadBuffer[19] ;   /* I2C Read data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCecUnitConfig_t        *pCecObject; /* Pointer to Cec Object */
  tmdlHdmiCecFrameFormat_t  ReadFrame;
  tmdlHdmiCecSaveMessage_t  LastSendMessage;
  int i;


  pDis = &gtmdlHdmiCecDriverConfigTable[instance];
  pCecObject = &UnitTable[instance];

#ifdef TMFL_TDA9989
  //Check if pending CEC interruption
  errCode = getCecHwRegisters(pDis, E_REG_CEC_INT, I2c_ReadBuffer,1);
  RETIF(errCode != TM_OK, errCode)

  if ((I2c_ReadBuffer[0] & CEC_INT_MASK) == 0x00)
  {
  		//No CEC interruption pending.
		return TM_OK;
  }  	
#endif

  errCode = getCecHwRegisters(pDis, E_REG_CDR0,I2c_ReadBuffer,19);
  RETIF(errCode != TM_OK, errCode)
     
  /*Fill Frame structure with read data*/

  /* Case of Receiving CECData.cnf*/
  /*Inform Success or reason of failure of CEC message sending*/
  if (I2c_ReadBuffer[1]== 0x01)
  {
    /* Get Infos of last message send */ 
    getCecLastMessage(&LastSendMessage);
	
    if (LastSendMessage.MessageTypePolling)
    {
     ReadFrame.FrameByteCount = I2c_ReadBuffer[0];
     ReadFrame.AddressByte = LastSendMessage.AddressByte;
     ReadFrame.DataBytes[0]= I2c_ReadBuffer[2];
    }
    else
    {
     ReadFrame.FrameByteCount = I2c_ReadBuffer[0]+1;
     ReadFrame.AddressByte = LastSendMessage.AddressByte;
     ReadFrame.DataBytes[0]= I2c_ReadBuffer[2];
     ReadFrame.DataBytes[1]= LastSendMessage.Opcode;
    }
    
    pCecObject->MessageCallback(TMDL_HDMICEC_CALLBACK_STATUS
                               , (UInt8 *) &ReadFrame, ReadFrame.FrameByteCount);
  }

  /* Case of Receiving CECData.ind*/
  /*Give receive data from CEC bus*/
  if (I2c_ReadBuffer[1]== 0x81)
  {
    ReadFrame.FrameByteCount = I2c_ReadBuffer[0];
    ReadFrame.AddressByte = I2c_ReadBuffer[2];
    for (i=0; i<15; i++)
    {
    ReadFrame.DataBytes[i] = I2c_ReadBuffer[i+3];
    }

    pCecObject->MessageCallback(TMDL_HDMICEC_CALLBACK_MESSAGE_AVAILABLE
                               , (UInt8 *) &ReadFrame, ReadFrame.FrameByteCount);
  }

  return(TM_OK);

}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecOpen( )
    \brief Open unit 0 of CEC and provides the instance number to
           the caller. Note that one unit of CEC represents one physical
           CEC device and that only one instance per unit can be opened.

    \param pInstance Pointer to the variable that will receive the instance
                     identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_OWNED: the resource is already in use
            - TMDL_ERR_DLHDMICEC_INIT_FAILED: the unit instance is already
              initialised or something wrong happened at lower level.
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_NO_RESOURCES: the resource is not available
            - TMDL_ERR_DLHDMICEC_INVALID_STATE: the state is invalid for
              the function
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecOpen
(
    tmInstance_t   *pInstance
)
{
    /* directly call OpenM function for unit 0 and return the result */
    return(tmdlHdmiCecOpenM(pInstance, (tmUnitSelect_t)0));
}


//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecOpenM( )
    \brief Open a specific unit of CEC driver and provides the instance
           number to the caller. Note that one unit of CEC represents one
           physical CEC device and that only one instance per unit can be
           opened. This function switches driver's state machine to
           "initialized" state.

    \param pInstance Pointer to the structure that will receive the instance
                     identifier.
    \param unit      Unit number to be opened.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_OWNED: the resource is already in use
            - TMDL_ERR_DLHDMICEC_INIT_FAILED: the unit instance is already
              initialised or something wrong happened at lower level.
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_NO_RESOURCES: the resource is not available
            - TMDL_ERR_DLHDMICEC_INVALID_STATE: the state is invalid for
              the function

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecOpenM
(
    tmInstance_t   *pInstance,
    tmUnitSelect_t  unit
)
{

    /* check if unit number is in range */
    RETIF((unit < 0) || (unit >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER)

    /* check if Instance pointer is Null */
    RETIF(pInstance == Null, TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS)

    /* check if unit is already instanciated */
    RETIF(UnitTable[unit].opened == True, TMDL_ERR_DLHDMICEC_RESOURCE_OWNED)

    /* Ckeck the state */
    RETIF(UnitTable[unit].state != CEC_STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

    /* instanciate unit and return corresponding instance number */
    /* Since HW unit are only instanciable once, instance = unit */
    UnitTable[unit].opened           = True;    
    UnitTable[unit].MessageCallback = Null;
    /* Give a logical Address to Device */
    UnitTable[unit].DeviceLogicalAddress = CEC_LOGICAL_ADDRESS_UNREGISTRED_BROADCAST;

    /* Recover the configuration of the device library */
    RETIF(tmdlHdmiCecCfgGetConfig(unit, &gtmdlHdmiCecDriverConfigTable[unit])!= TM_OK, TMDL_ERR_DLHDMICEC_INIT_FAILED)

    *pInstance = (tmInstance_t)unit;

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecClose( )
    \brief Close an instance of CEC driver.

    \param instance Instance identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClose
(
    tmInstance_t   instance
)
{
    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

    /* close instance */
    UnitTable[instance].opened = False;
    UnitTable[instance].state = CEC_STATE_NOT_INITIALIZED;

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecInstanceConfig( )
    \brief Set the configuration of instance attributes. This function is
           required by DVP architecture rules but actually does nothing in this
           driver

    \param instance    Instance identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecInstanceConfig
(
    tmInstance_t    instance
)
{
    if (instance);

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecInstanceSetup( )
    \brief Setup the instance with its configuration parameters. This function
           allows basic instance configuration for CEC Stack Processor.

    \param instance   Instance identifier.
    \param pSetupInfo Pointer to the structure containing all setup parameters

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecInstanceSetup
(
    tmInstance_t               instance,
    tmdlHdmiCecInstanceSetup_t *pSetupInfo
)
{
    tmErrorCode_t                  errCode;
    tmdlHdmiCecDriverConfigTable_t *pDis;     /* Pointer to Device Instance Structure */
#ifdef TMFL_TDA9989
    unsigned char               I2c_ReadBuffer[1];
#endif


    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check that input pointer is not NULL */
    RETIF(pSetupInfo == Null, TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

    /* Ckeck the state */
    RETIF(UnitTable[instance].state != CEC_STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];

    /* Wait for 250 ms */
    RETIF( (errCode = tmdlHdmiTxIWWait(500) ) != TM_OK, errCode)

#ifdef TMFL_TDA9989
    /* Enable CEC Stack Processor */
	errCode = getCecHwRegisters(pDis, E_REG_CDR0,I2c_ReadBuffer,1);	
	RETIF(errCode != TM_OK, errCode)

	errCode = getCecHwRegisters(pDis, E_REG_ENAMODS,I2c_ReadBuffer,1);	
	RETIF(errCode != TM_OK, errCode)

	I2c_ReadBuffer[0] |= DEFAULT_ENAMODS; 

    errCode = setCecHwRegister(pDis, E_REG_ENAMODS, I2c_ReadBuffer[0]);
    if (errCode != TM_OK)
    {   
		//TODO WA still needed?
		errCode = setCecHwRegister(pDis, E_REG_ENAMODS, I2c_ReadBuffer[0]);
        RETIF(errCode != TM_OK, errCode)
    }

    RETIF( (errCode = tmdlHdmiTxIWWait(TDA9950_RESET_DELAY_MS) ) != TM_OK, errCode)

	/* Select CEC clock source and divider value */

    if (pSetupInfo->cecClockSource == TMDL_HDMICEC_CLOCK_XTAL)
	{
	   errCode = getCecHwRegisters(pDis, E_REG_CEC_CLK,I2c_ReadBuffer,1);	
	   RETIF(errCode != TM_OK, errCode)

	   I2c_ReadBuffer[0] &= CEC_CLK_SEL; 
       errCode = setCecHwRegister(pDis, E_REG_CEC_CLK, I2c_ReadBuffer[0]);
    }

	RETIF( (errCode = tmdlHdmiTxIWWait(TDA9950_RESET_DELAY_MS) ) != TM_OK, errCode)

    //TODO WA to avoid spurious interrupts
	errCode = getCecHwRegisters(pDis, E_REG_CDR0,I2c_ReadBuffer,1);
    RETIF(errCode != TM_OK, errCode)
#endif


    /* Reset CEC Stack Processor */
    errCode = setCecHwRegister(pDis, E_REG_CCR, 0x80);
    RETIF(errCode != TM_OK, errCode)


    /* Wait for 250 ms */
    RETIF( (errCode = tmdlHdmiTxIWWait(TDA9950_RESET_DELAY_MS) ) != TM_OK, errCode)

    /* Configure Stack Processor (Retry = 5)*/
    errCode = setCecHwRegister(pDis, E_REG_CCONR, 0x05);
    RETIF(errCode != TM_OK, errCode)


    UnitTable[instance].DeviceLogicalAddress = pSetupInfo->DeviceLogicalAddress;


    /* CEC Control register */
    errCode = setCecHwRegisterMsbLsb(pDis, E_REG_ACKH, 0x1 << (UnitTable[instance].DeviceLogicalAddress));
    RETIF(errCode != TM_OK, errCode)


    /* CEC Stack Processor enable*/
    errCode = setCecHwRegister(pDis, E_REG_CCR, 0x40);
    RETIF(errCode != TM_OK, errCode)


    /* switch instance to its new state */
    UnitTable[instance].state = CEC_STATE_CONFIGURED;

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRegisterCallback( )
    \brief Register event callbacks. Three types of callbacks can be
           registered : input activity related callback, data related
           callback (infoframes, packets, etc.) and general information
           callback. A null pointer means that no callback are registered.

    \param instance                 Instance identifier.
    \param MessageCallback         Pointer to the callback function that will
                                    handle message related events.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_INVALID_STATE: the state is invalid for
              the function

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRegisterCallbacks
(
    tmInstance_t               instance,
    ptmdlHdmiCecCallbackFunc_t MessageCallback
)
{
    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

    /* check if instance state is correct */
    //RETIF(UnitTable[instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

    /* store callback pointers */
    UnitTable[instance].MessageCallback  = MessageCallback;

    return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetLogicalAddress( )
    \brief Set Device Logical Address

    \param instance      Instance identifier.
    \param LogicalAddress Logical address value.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetLogicalAddress
(
    tmInstance_t   instance,
	tmdlHdmiCECLogicalAddress_t   LogicalAddress
)
{
    tmErrorCode_t                  errCode;
    tmdlHdmiCecDriverConfigTable_t *pDis;     /* Pointer to Device Instance Structure */
	
    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

    /* Ckeck the state */
    RETIF(UnitTable[instance].state != CEC_STATE_CONFIGURED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];
    
    UnitTable[instance].DeviceLogicalAddress = LogicalAddress;
    
    errCode = setCecHwRegisterMsbLsb(pDis, E_REG_ACKH, 0x1 << (UnitTable[instance].DeviceLogicalAddress));
    RETIF(errCode != TM_OK, errCode)

    return(TM_OK);
}


//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetRetry( )
    \brief Change the number of retransmission

    \param instance Instance identifier.
    \param NbRetry Number of retry.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetRetry
(
    tmInstance_t   instance,
	UInt8   NbRetry
)
{
    tmErrorCode_t                  errCode;
	tmdlHdmiCecDriverConfigTable_t *pDis;     /* Pointer to Device Instance Structure */
	
	/* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

	/* Ckeck the state */
    RETIF(UnitTable[instance].state != CEC_STATE_CONFIGURED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

	pDis = &gtmdlHdmiCecDriverConfigTable[instance];

    /* Configure Retry register */
    errCode = setCecHwRegister(pDis, E_REG_CCONR, NbRetry);
    RETIF(errCode != TM_OK, errCode)

	return(TM_OK);
}


//==========================================================================
/*!
    \fn tmErrorCode_t getCecLastMessage( )
    \brief Return the Addresses and the Opcode of the last CEC
	       transmitted message

    \param pSaveMessage   Pointer to the CEC Save Message

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t getCecLastMessage
(
    tmdlHdmiCecSaveMessage_t  *pSaveMessage
)
{
    /* copy Last CEC message datas */
    pSaveMessage->AddressByte  = gtmdlHdmiCecDriverSaveMessage.AddressByte;
    pSaveMessage->MessageTypePolling = gtmdlHdmiCecDriverSaveMessage.MessageTypePolling;
    pSaveMessage->Opcode  = gtmdlHdmiCecDriverSaveMessage.Opcode;

    return(TM_OK);
}


//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecImageViewOn( )
    \brief This message sent by a source device to the TV whenever it enters
           the active state

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receivers. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecImageViewOn
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C Write data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  //RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Image View On command */
	
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_IMAGE_VIEW_ON ;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecInactiveSource( )
    \brief This message is used by the currently active source to inform the
           TV that it has no video to be presented to the user, or is going
           into standby as the result of a lcoal user command on the device.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress, \n
           Address of message receiver. \n

    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Physical Address of the device. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecInactiveSource
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */  	

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];
  //======To do : make a prepare message function with parameter
  /* Inactive source command */  
  I2c_Buffer[0] = 0x06;  

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_INACTIVE_SOURCE ;  /* Inactive Source*/
  I2c_Buffer[4] = (unsigned char)(PhysicalAddress >> 8);    /* MsByte of Physical Address */
  I2c_Buffer[5] = (unsigned char)PhysicalAddress;           /* LsByte of Physical Address */


  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecActiveSource()
    \brief This message is used by a new source to indicate that it has started
           to transmit a stream OR used in reponse to a <Request Active Source>

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt16 PhysicalAddress \n
           Physical address of the device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecActiveSource
(
   tmInstance_t   Instance,
   UInt16         PhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Active Source command */	
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_ACTIVE_SOURCE ;        /* Active source */
  I2c_Buffer[4] = (unsigned char)(PhysicalAddress >> 8);    /* MsByte of Physical Address */
  I2c_Buffer[5] = (unsigned char)PhysicalAddress;           /* LsByte of Physical Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecVersion()
    \brief This message is used to indicate the supported CEC version in response
           to a <Get CEC Version>

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress\n
           Address of message receiver. \n

    \param tmdlHdmiCECVersion_t CECVersion \n
           Supported CEC Version.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVersion
(
   tmInstance_t         Instance,
   UInt8                ReceiverLogicalAddress,
   tmdlHdmiCECVersion_t CECVersion
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* CEC Version command */
  I2c_Buffer[0] = 0x05;     /* Param number */  

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_CEC_VERSION ;  /* CECVersion*/
  I2c_Buffer[4] = CECVersion;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecClearAnalogueTimer( )
    \brief This message is used to clear an Analogue timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n

    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n

    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearAnalogueTimer
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   UInt8                               DayOfMonth,
   UInt8                               MonthOfYear,
   UInt16                              StartTime,
   tmdlHdmiCECDuration_t              *pDuration,
   UInt8                               RecordingSequence,
   tmdlHdmiCECAnalogueBroadcastType_t  AnalogueBroadcastType,
   UInt16                              AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t        BroadcastSystem
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[15] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Clear Analogue Timer command */
  I2c_Buffer[0] = 0x0f;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_CLEAR_ANALOGUE_TIMER ;
  I2c_Buffer[4] = DayOfMonth;                       /*Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                      /*Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);  /*Start Time*/
  I2c_Buffer[7] = (UInt8)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;               /*Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;              /*Duration minute*/
  I2c_Buffer[10] = RecordingSequence;               /*Recording Sequence*/
  I2c_Buffer[11] = AnalogueBroadcastType;           /*Analogue Broadcast Type*/
  I2c_Buffer[12] = (unsigned char)(AnalogueFrequency >> 8); /*Analogue Frequency*/
  I2c_Buffer[13] = (unsigned char)AnalogueFrequency;
  I2c_Buffer[14] = BroadcastSystem;                 /*BroadcastSystem*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,15); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecClearDigitalTimer( )
    \brief This message is used to clear a digital timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearDigitalTimer
(
   tmInstance_t                               Instance,
   UInt8                                      ReceiverLogicalAddress,
   UInt8                                      DayOfMonth,
   UInt8                                      MonthOfYear,
   UInt16                                     StartTime,
   tmdlHdmiCECDuration_t                     *pDuration,
   UInt8                                      RecordingSequence,
   tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[18] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCECAribData_t *pARIB_Pointer;
  tmdlHdmiCECAtscData_t *pATSC_Pointer;
  tmdlHdmiCECDvbData_t  *pDVB_Pointer;

  unsigned char Regval;                 /* Local variable*/


  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];


  //======To do : make a prepare message function with parameter
  /* Clear Digital Timer command */
  I2c_Buffer[0] = 0x12;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

	/*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_CLEAR_DIGITAL_TIMER ;
  I2c_Buffer[4] = DayOfMonth;                       /*Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                      /*Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);  /*Start Time*/
  I2c_Buffer[7] = (UInt8)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;               /*Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;              /*Durantion Minute*/
  I2c_Buffer[10] = RecordingSequence;               /*Recording Sequence*/

  /* Digital service Identification*/
  /*Merge Service Method and Digital Broadcast System in the same Byte*/
  Regval = (unsigned char)(pServiceIdentification->ServiceIdentificationMethod & 0x01); /*bit 7 is Service Method*/
  Regval = Regval << 7;
  Regval |= (unsigned char)(pServiceIdentification->DigitalBroadcastSystem & 0x7F);     /*bits 6 to 0 are Digital Broadcast*/
  I2c_Buffer[11] = Regval;


  /*Case of a ARIB Generic*/
  if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_GENERIC)
    {
        pARIB_Pointer =(tmdlHdmiCECAribData_t *)pServiceIdentification->pServiceIdentification;

		I2c_Buffer[12] = (unsigned char)(pARIB_Pointer->TransportStreamID >> 8);
		I2c_Buffer[13] = (unsigned char)pARIB_Pointer->TransportStreamID;
		I2c_Buffer[14] = (unsigned char)(pARIB_Pointer->ServiceID >> 8);
		I2c_Buffer[15] = (unsigned char)pARIB_Pointer->ServiceID;
		I2c_Buffer[16] = (unsigned char)(pARIB_Pointer->OriginalNetworkID >> 8);
		I2c_Buffer[17] = (unsigned char)pARIB_Pointer->OriginalNetworkID;

    }
    /*Case of a ATSC Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ATSC_GENERIC)
    {
        pATSC_Pointer = (tmdlHdmiCECAtscData_t*)pServiceIdentification->pServiceIdentification;

		I2c_Buffer[12] = (unsigned char)(pATSC_Pointer->TransportStreamID >> 8);
		I2c_Buffer[13] = (unsigned char)pATSC_Pointer->TransportStreamID;
		I2c_Buffer[14] = (unsigned char)(pATSC_Pointer->ProgramNumber >> 8);
		I2c_Buffer[15] = (unsigned char)pATSC_Pointer->ProgramNumber;
		I2c_Buffer[16] = (unsigned char)(pATSC_Pointer->Reserved >> 8);
		I2c_Buffer[17] = (unsigned char)pATSC_Pointer->Reserved;
    }
    /*Case of a DVB Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_DVB_GENERIC)
    {
        pDVB_Pointer = (tmdlHdmiCECDvbData_t*)pServiceIdentification->pServiceIdentification;

		I2c_Buffer[12] = (unsigned char)(pDVB_Pointer->TransportStreamID >> 8);
		I2c_Buffer[13] = (unsigned char)pDVB_Pointer->TransportStreamID;
		I2c_Buffer[14] = (unsigned char)(pDVB_Pointer->ServiceID >> 8);
		I2c_Buffer[15] = (unsigned char)pDVB_Pointer->ServiceID;
		I2c_Buffer[16] = (unsigned char)(pDVB_Pointer->OriginalNetworkID >> 8);
		I2c_Buffer[17] = (unsigned char)pDVB_Pointer->OriginalNetworkID;
    }
    /*other cases, Buffer are empty*/
  else
    {
		I2c_Buffer[12] = 0xFF;
		I2c_Buffer[13] = 0xFF;
		I2c_Buffer[14] = 0xFF;
		I2c_Buffer[15] = 0xFF;
		I2c_Buffer[16] = 0xFF;
		I2c_Buffer[17] = 0xFF;
    }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,18); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecClearExternalTimerWithExternalPlug( )
    \brief This message is used to clear a digital timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECExternalPlug_t  ExternalPlug \n
           indicates external plug number (1 to 255 )on the recording device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearExternalTimerWithExternalPlug
(
   tmInstance_t                Instance,
   UInt8                       ReceiverLogicalAddress,
   UInt8                       DayOfMonth,
   UInt8                       MonthOfYear,
   UInt16                      StartTime,
   tmdlHdmiCECDuration_t      *pDuration,
   UInt8                       RecordingSequence,
   tmdlHdmiCECExternalPlug_t   ExternalPlug
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[13] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  // RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Clear External Timer with External Plug Command*/
  I2c_Buffer[0] = 0x0D;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_CLEAR_EXTERNAL_TIMER ;
  I2c_Buffer[4] = DayOfMonth;                       /*Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                      /*Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);  /*Start Time*/
  I2c_Buffer[7] = (unsigned char)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;               /*Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;              /*Duration minute*/	
  I2c_Buffer[10] = RecordingSequence;               /*Recording Sequence*/
  I2c_Buffer[11] = CEC_EXTERNAL_PLUG;               /*External Source Specifier = External Plug */
  I2c_Buffer[12] = ExternalPlug;                    /*External Plug*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,13); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecClearExternalTimerWithPhysicalAddress( )
    \brief This message is used to clear a digital timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Defines the path between the TV an a device-thus giving it a physical
           address within the cluster.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearExternalTimerWithPhysicalAddress
(
   tmInstance_t                           Instance,
   UInt8                                  ReceiverLogicalAddress,
   UInt8                                  DayOfMonth,
   UInt8                                  MonthOfYear,
   UInt16                                 StartTime,
   tmdlHdmiCECDuration_t                 *pDuration,
   UInt8                                  RecordingSequence,
   tmdlHdmiCECExternalPhysicalAddress_t   ExternalPhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[14] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Clear External Timer with Physical Address Command */
  I2c_Buffer[0] = 0x0E;     /* Param number */  

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_CLEAR_EXTERNAL_TIMER ;             /*Clear External Timer*/
  I2c_Buffer[4] = DayOfMonth;                                   /*Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                                  /*Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);              /*Start Time*/
  I2c_Buffer[7] = (unsigned char)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;                           /*Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;                          /*Duration Minute*/
  I2c_Buffer[10] = RecordingSequence;                           /*Recording Sequence*/
  I2c_Buffer[11] = CEC_EXTERNAL_PHYSICAL_ADDRESS;               /*External Source Specifier = External Address*/
  I2c_Buffer[12] = (unsigned char)(ExternalPhysicalAddress >> 8);   /*External Address*/
  I2c_Buffer[13] = (unsigned char)ExternalPhysicalAddress;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,14); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTextViewOn( )
    \brief This message as <Image View On>, but should also remove any text,
           menus and PIP windows from the TV's display

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTextViewOn
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to Instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if Instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Text View On command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TEXT_VIEW_ON ;     /* Text View On */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTimerClearedStatus( )
    \brief This message is used to give the status of a <Cleared Analogue Timer>,
           <Clear Digital Timer> or <Clear External Timer> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECTimerClearedStatusData_t TimerClearedStatusData \n
           Indicates if the timer was cleared successfully. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTimerClearedStatus
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   tmdlHdmiCECTimerClearedStatusData_t TimerClearedStatusData
)
{

  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Timer Clear Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TIMER_CLEARED_STATUS;  /* System Audio Status*/
  I2c_Buffer[4] = TimerClearedStatusData;           /* Timer Cleared Status*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTimerStatus( )
    \brief This message is used to send timer status to the initiator of a
           <Set Timer> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECTimerStatusData_t *pTimerStatusData \n
           Pointer on the Timer status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTimerStatus
(
   tmInstance_t                 Instance,
   UInt8                        ReceiverLogicalAddress,
   tmdlHdmiCECTimerStatusData_t *pTimerStatusData
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[7] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCECTimerProgrammedInfo_t *pTimerProgInfo;
  unsigned char Regval;

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Timer Status command */
  I2c_Buffer[0] = 0x07;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TIMER_CLEARED_STATUS;  /* System Audio Status*/
  /* First Byte Building */
  Regval = ((unsigned char)(pTimerStatusData->TimerOverlapWarning)& 0x01) << 7 ; // bit 7 for Timer Overlap Warning
  Regval |= ((unsigned char)(pTimerStatusData->MediaInfo)& 0x03) << 5;           // bit 6 to 5 for Media Info

  pTimerProgInfo = &(pTimerStatusData->TimerProgrammedInfo);
  Regval |= ((unsigned char)(pTimerProgInfo->SelectProgramInfo)& 0x01)<< 4;      // bit 4 for Timer Programed Indicator
  Regval |= (unsigned char)(pTimerProgInfo->ProgramInfo)& 0x0F;                  // bit 3 to 0 for Program Information
  I2c_Buffer[4] = Regval;

  /* 2 Duration Available Bytes Building */
  /* Duration Available is only filled in the the both following conditions*/
  if((pTimerProgInfo->SelectProgramInfo == CEC_PROGRAM_INDICATOR_NOT_PROGRAMMED)&&(pTimerProgInfo->ProgramInfo == CEC_PROGRAM_ERROR_INFO_DUPLICATE_ALREADY_PROGRAMMED))
  {
  I2c_Buffer[5] = (unsigned char)(pTimerProgInfo->DurationAvailable >> 8);
  I2c_Buffer[6] = (unsigned char)pTimerProgInfo->DurationAvailable;
  }
  else if((pTimerProgInfo->SelectProgramInfo == CEC_PROGRAM_INDICATOR_PROGRAMMED)&&(pTimerProgInfo->ProgramInfo == CEC_PROGRAM_INFO_NOT_ENOUGHT_SPACE_AVAILABLE_FOR_RECORDING))
  {
  I2c_Buffer[5] = (unsigned char)(pTimerProgInfo->DurationAvailable >> 8);
  I2c_Buffer[6] = (unsigned char)pTimerProgInfo->DurationAvailable;
  }
  /*Else, 2 bytes of Duration Available are filled with 0xFF*/
  else
  {
  I2c_Buffer[5] = 0xFF;
  I2c_Buffer[6] = 0xFF;
  }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTunerDeviceStatusAnalogue( )
    \brief This message is used by a tuner device to provide its status to the
           initiator of the <Give Tuner Device Status> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECRecordingFlag_t RecordingFlag \n
           Indicates if the tuner is being used as a source of a recording. \n

    \param tmdlHdmiCECTunerDisplayInfo_t TunerDisplayInfo \n
           Indicates if the the device is currently deplaying its tuner or not. \n

    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n

    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n

    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerDeviceStatusAnalogue
(
   tmInstance_t                       Instance,
   UInt8                              ReceiverLogicalAddress,
   tmdlHdmiCECRecordingFlag_t         RecordingFlag,
   tmdlHdmiCECTunerDisplayInfo_t      TunerDisplayInfo,
   tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType,
   UInt16                             AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t       BroadcastSystem
   )
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[9] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  unsigned char Regval;                 /*Local Variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Select Aanalogue Service command */
  I2c_Buffer[0] = 0x09;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TUNER_DEVICE_STATUS ;          /* Tuner Device Status*/
  /* Build First Byte*/
  Regval = ((unsigned char)RecordingFlag & 0X01)<< 7;       /*bit 7 is Recording Flag */
  Regval |= (unsigned char)TunerDisplayInfo & 0X7F;         /*bit 6 to 0 are Tuner display Info*/
  I2c_Buffer[4] = Regval;

  I2c_Buffer[5] = AnalogueBroadcastType;                    /*Analogue Broadcast System type*/
  I2c_Buffer[6] = (unsigned char)(AnalogueFrequency >> 8);  /*Analogue Frequency*/
  I2c_Buffer[7] = (unsigned char)AnalogueFrequency;
  I2c_Buffer[8] = BroadcastSystem;                          /*Broadcast System*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,9); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTunerDeviceStatusDigital( )
    \brief This message is used by a tuner device to provide its status to the
           initiator of the <Give Tuner Device Status> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECRecordingFlag_t RecordingFlag \n
           Indicates if the tuner is being used as a source of a recording. \n

    \param tmdlHdmiCECTunerDisplayInfo_t TunerDisplayInfo \n
           Indicates if the the device is currently deplaying its tuner or not. \n

    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerDeviceStatusDigital
(
   tmInstance_t                               Instance,
   UInt8                                      ReceiverLogicalAddress,
   tmdlHdmiCECRecordingFlag_t                 RecordingFlag,
   tmdlHdmiCECTunerDisplayInfo_t              TunerDisplayInfo,
   ptmdlHdmiCECDigitalServiceIdentification_t pServiceIdentification
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[12] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCECAribData_t *pARIB_Pointer;
  tmdlHdmiCECAtscData_t *pATSC_Pointer;
  tmdlHdmiCECDvbData_t  *pDVB_Pointer;

  unsigned char Regval;                 /* Local variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record On Digital Service command */
  I2c_Buffer[0] = 0x0C;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TUNER_DEVICE_STATUS ;      /* Tuner Device Status*/

  /* Merge Recording Flag With Tuner Display Info*/
  Regval = ((unsigned char)RecordingFlag & 0X01)<< 7; /* bit 7 is Recording Flag*/
  Regval |= (unsigned char)TunerDisplayInfo & 0X7F;   /* bit 6 to 0 are Tuner display Info*/
  I2c_Buffer[4] = Regval;

  /* Digital service Identification*/
  /*Merge Service Method and Digital Broadcast System in the same Byte*/
  Regval = (unsigned char)(pServiceIdentification->ServiceIdentificationMethod & 0x01) << 7; /* bit 7 is Service Method*/
  Regval |= (unsigned char)(pServiceIdentification->DigitalBroadcastSystem & 0x7F);          /* bits 6 to 0 are Digital Broadcast*/
  I2c_Buffer[5] = Regval;

  /*Case of a ARIB Generic*/
  if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_GENERIC)
    {
        pARIB_Pointer = (tmdlHdmiCECAribData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[6] = (unsigned char)(pARIB_Pointer->TransportStreamID >> 8);
        I2c_Buffer[7] = (unsigned char)pARIB_Pointer->TransportStreamID;
        I2c_Buffer[8] = (unsigned char)(pARIB_Pointer->ServiceID >> 8);
        I2c_Buffer[9] = (unsigned char)pARIB_Pointer->ServiceID;
        I2c_Buffer[10] = (unsigned char)(pARIB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[11] = (unsigned char)pARIB_Pointer->OriginalNetworkID;
    }
    /*Case of a ATSC Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ATSC_GENERIC)
    {
        pATSC_Pointer = (tmdlHdmiCECAtscData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[6] = (unsigned char)(pATSC_Pointer->TransportStreamID >> 8);
        I2c_Buffer[7] = (unsigned char)pATSC_Pointer->TransportStreamID;
        I2c_Buffer[8] = (unsigned char)(pATSC_Pointer->ProgramNumber >> 8);
        I2c_Buffer[9] = (unsigned char)pATSC_Pointer->ProgramNumber;
        I2c_Buffer[10] = (unsigned char)(pATSC_Pointer->Reserved >> 8);
        I2c_Buffer[11] = (unsigned char)pATSC_Pointer->Reserved;
    }
    /*Case of a DVB Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_DVB_GENERIC)
    {
        pDVB_Pointer = (tmdlHdmiCECDvbData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[6] = (unsigned char)(pDVB_Pointer->TransportStreamID >> 8);
        I2c_Buffer[7] = (unsigned char)pDVB_Pointer->TransportStreamID;
        I2c_Buffer[8] = (unsigned char)(pDVB_Pointer->ServiceID >> 8);
        I2c_Buffer[9] = (unsigned char)pDVB_Pointer->ServiceID;
        I2c_Buffer[10] = (unsigned char)(pDVB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[11] = (unsigned char)pDVB_Pointer->OriginalNetworkID;
    }
    /*other cases, Buffer are empty*/
  else
    {
        I2c_Buffer[6] = 0xFF;
        I2c_Buffer[7] = 0xFF;
        I2c_Buffer[8] = 0xFF;
        I2c_Buffer[9] = 0xFF;
        I2c_Buffer[10] = 0xFF;
        I2c_Buffer[11] = 0xFF;
    }
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,12); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestActiveSource( )
    \brief This message is used by a new device to discover the status of
           the system.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_Instance: the Instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestActiveSource
(
   tmInstance_t  Instance
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* IRequest Active Source command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_REQUEST_ACTIVE_SOURCE ;        /* Request Active Source */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRoutingChange( )
    \brief This message is sent by a CEC switch when it is manually switched to
           inform all other devices on the network that the active route below
           the switch has changed.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt16 OriginalAddress \n
           Previous address that the switch was switched to. \n

    \param UInt16 NewAddress \n
           The new address it has been moved to. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRoutingChange
(
   tmInstance_t  Instance,
   UInt16        OriginalAddress,
   UInt16        NewAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[8] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Routing Change command */
  I2c_Buffer[0] = 0x08;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_ROUTING_CHANGE ;            /* Routing Change */
  I2c_Buffer[4] = (unsigned char)(OriginalAddress >> 8); /* MsByte of Original Address*/
  I2c_Buffer[5] = (unsigned char)OriginalAddress;        /* LsByte of Original Address */
  I2c_Buffer[6] = (unsigned char)(NewAddress >> 8);      /* MsByte of New Address */
  I2c_Buffer[7] = (unsigned char)NewAddress;             /* LsByte of New Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,8); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRoutingInformation( )
    \brief This message is sent by a CEC switch to indicate the active route
           below the switch.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt16 PhysicalAddress \n
           The current active route to the sink in the CEC switch. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRoutingInformation
(
   tmInstance_t  Instance,
   UInt16        PhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Routing Information command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_ROUTING_INFORMATION ;       /* Routing Information */
  I2c_Buffer[4] = (unsigned char)(PhysicalAddress >> 8); /* MsByte of Physical Address*/
  I2c_Buffer[5] = (unsigned char)PhysicalAddress;        /* LsByte of Physical Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSelectAnalogueService( )
    \brief This message select directly an analogue TV Service.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n

    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n

    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSelectAnalogueService
(
   tmInstance_t                       Instance,
   UInt8                              ReceiverLogicalAddress,
   tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType,
   UInt16                             AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t       BroadcastSystem
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[8] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Select Aanalogue Service command */
  I2c_Buffer[0] = 0x08;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_ANALOGUE_SERVICE ; /* Select Analogue Service*/
  I2c_Buffer[4] = AnalogueBroadcastType;
  I2c_Buffer[5] = (unsigned char)(AnalogueFrequency >> 8);
  I2c_Buffer[6] = (unsigned char)AnalogueFrequency;
  I2c_Buffer[7] = BroadcastSystem;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,8); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetStreamPath( )
    \brief This message is used by a TV to request a streaming path from
           the specified physical address.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt16 PhysicalAddress \n
           Physical address of the device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetStreamPath
(
   tmInstance_t  Instance,
   UInt16        PhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set Stream Path command */
  I2c_Buffer[0] = 0x06;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_SET_STREAM_PATH ;              /* Set Stream Path */
  I2c_Buffer[4] = (unsigned char)(PhysicalAddress >> 8);    /* MsByte of Physical Address*/
  I2c_Buffer[5] = (unsigned char)PhysicalAddress;           /* LsByte of Physical Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}
 //==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetSystemAudioMode( )
    \brief This message turn the system audio Mode ON or OFF.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus \n
           Specifies if the system audio mode is ON or OFF.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetSystemAudioMode
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set System Audio Mode Command */
  I2c_Buffer[0] = 0x05;    /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_SYSTEM_AUDIO_MODE ;    /* Set System Audio Mode*/
  I2c_Buffer[4] = SystemAudioStatus;                    /*System Audio Status*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetTimerProgramTitle( )
    \brief This message is used to set the name of a program associated
           with a timer block.Sent directly after sending a
           <Set analogue Timer> or <Set Digital Timer> message. The name
           is then associated with that timer block.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param const char *pProgramTitleString \n
           Pointer on the program title. \n

    \param UInt8    ProgramTitleLength \n
           Length of Program Title String. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetTimerProgramTitle
(
   tmInstance_t Instance,
   UInt8        ReceiverLogicalAddress,
   const char   *pProgramTitleString,
   UInt8        ProgramTitleLength
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[19] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char loci;                   /* Local increment variable*/
  unsigned char MessLength;             /* Local Message length*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Set Timer Program Title */
  MessLength = ProgramTitleLength+4;                         /* Calculate Message length*/

  I2c_Buffer[0] = (unsigned char)MessLength;

  I2c_Buffer[1] = 0x00;                                      /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_TIMER_PROGRAM_TITLE ;      /* Set Timer Program Title*/

  for(loci = 0; loci <= ProgramTitleLength ; loci++)
    {
        I2c_Buffer[(loci+4)] = pProgramTitleString[loci];     /* Fill Table with Program Title characters*/
    }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,(MessLength)); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecStandby( )
    \brief This message switches one or all devices into standby mode.Can be
           be used as a broadcast message o be addressed to a specific device.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecStandby
(
   tmInstance_t Instance,
   UInt8        ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Standby command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_STANDBY ;      /* Standby */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSystemAudioModeRequest( )
    \brief A device implementing System Audio Control and which has volume
           control RC button(eg TV or STB) request to use System Audio Mode
           to the amplifier.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt16 PhysicalAddress \n
           Physical address of the device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSystemAudioModeRequest
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt16        PhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* System Audio Mode Request command */
  I2c_Buffer[0] = 0x06;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST ;    /* System Audio Mode Request*/
  I2c_Buffer[4] = (unsigned char)(PhysicalAddress >> 8);    /* MsByte of Physical Address */
  I2c_Buffer[5] = (unsigned char)PhysicalAddress;           /* LsByte of Physical Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSystemAudioModeStatus( )
    \brief Reports the current status of the System Audio Mode.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus \n
           Current system audio mode.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSystemAudioModeStatus
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* System Audio Mode Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS ; /* System Audio Mode Status*/
  I2c_Buffer[4] = SystemAudioStatus;                    /* System Audio Status*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveTunerDeviceStatus( )
    \brief This message is used to request the status of a tuner device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECStatusRequest_t StatusRequest \n
           Allows the initiator to request the status once or on all future state
           change. Or to cancel a previous <Give Tuner Device Status > ["On"] request. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveTunerDeviceStatus
(
   tmInstance_t               Instance,
   UInt8                      ReceiverLogicalAddress,
   tmdlHdmiCECStatusRequest_t StatusRequest
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* System Audio Mode Request command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_TUNER_DEVICE_STATUS ; /* Give Tuner Device Status*/
  I2c_Buffer[4] = (unsigned char)StatusRequest; /* Status Request */

  errCode = setCecHwRegisters(pDis,E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordTvScreen( )
    \brief This message request by the recording device to record the presently
           displayed source.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordTvScreen
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
)
{ tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record TV Sreen command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_TV_SCREEN ;     /* Record TV screen */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportAudioStatus( )
    \brief This message report an amplifier's volume and mute.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECAudioStatus_t AudioStatus \n
           Volume and mute status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportAudioStatus
(
   tmInstance_t              Instance,
   UInt8                     ReceiverLogicalAddress,
   ptmdlHdmiCECAudioStatus_t pAudioStatus
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char Regval;                 /*Local Variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Report Audio Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_AUDIO_STATUS ;  /* Report Audio Statust*/
  Regval = (((unsigned char)pAudioStatus -> audioMuteStatus) & 0x01 )<< 7; /* bit 7 Mute Status*/
  Regval |= ((unsigned char)pAudioStatus -> audioVolumeStatus) & 0x7F; /* bit 6 to 0 Volum Status*/
  I2c_Buffer[4] = Regval;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportShortAudioDescriptor( )
    \brief This message Report Audio Capability.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt32 ShortAudioDecriptor \n
           Audio Descriptor. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportShortAudioDescriptor
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress,
   UInt32         ShortAudioDecriptor
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[7] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x07;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR ;  /* Report Audio Capability*/
  I2c_Buffer[4] = (unsigned char)(ShortAudioDecriptor >> 16);  /* MSByte of ShortAudioDecriptor*/
  I2c_Buffer[5] = (unsigned char)(ShortAudioDecriptor >> 8);
  I2c_Buffer[6] = (unsigned char)ShortAudioDecriptor;          /* LSByte of ShortAudioDecriptor*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestShortAudioDescriptor( )
    \brief This message Request Audio Capability.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8 AudioFormatID \n
	   
    \param UInt8 AudioFormatCode \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestShortAudioDescriptor
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress,
   UInt8          AudioFormatID,
   UInt8          AudioFormatCode
   
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char Regval;                 /*Local Variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR ;  /* Request Audio Capability*/
  Regval = (((unsigned char)AudioFormatCode) & 0x3F )<< 2; /* bit 3 to 7  AudioFormatCode*/
  Regval |= ((unsigned char)AudioFormatID) & 0x03; /* bit 1 to 0 AudioFormatID*/
  I2c_Buffer[4] = Regval;
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecIniateARC( )
    \brief This message Used by an ARC RX device to activate the
           ARC functionality in an ARC TX device

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecIniateARC
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_INITATE_ARC ; 
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportArcInitiated( )
    \brief This message Used by an ARC TX device to indicate that
           its ARC functionality has been activated

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportArcInitiated
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_ARC_INITIATED ; 
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportArcTerminated( )
    \brief This message Used by an ARC TX device to indicate that its ARC functionality
           has been deactivated.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportArcTerminated
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_ARC_TERMINATED ; 
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestArcInitiation( )
    \brief This message Used by an ARC TX device to request an ARC RX device to
           activate the ARC functionality in the ARC TX device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestArcInitiation
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_ARC_INITIATION ; 
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestArcTerminiation( )
    \brief Used by an ARC TX device to request an ARC RX device to deactivate 
           the ARC functionality in the ARC TX device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestArcTerminiation
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_ARC_TERMINATION ; 
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTerminateARC( )
    \brief Used by an ARC TX device to request an ARC RX device to deactivate 
           the ARC functionality in the ARC TX device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTerminateARC
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Report Short Audio Decriptor */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TERMINATE_ARC ; 
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGivePhysicalAddress( )
    \brief This message is a request to a device to return its physical Address

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGivePhysicalAddress
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give physical Address command */
  I2c_Buffer[0] = 0x04;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_PHYSICAL_ADDRESS ;        /* Give Physical Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveSystemAudioModeStatus( )
    \brief This message request the status of the system audio mode

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveSystemAudioModeStatus
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give System Audio Mode Status command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS ;    /* Give System Audio Mode Status*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGetMenuLanguage( )
    \brief This message is sent by a device capable of character generation
           (for OSD and Menus) to a TV in order to discover the currently selected
           Menu Language. Also used by a TV during installation to dicover the
           currently set menu language of other devices.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetMenuLanguage
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Get Menu Language command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GET_MENU_LANGUAGE ;        /* Get Menu Address */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}
//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveAudioStatus( )
    \brief This message is requests an amplifier to send its volume and mute status

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveAudioStatus
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give Audio Mode Status command */
  I2c_Buffer[0] = 0x04;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_AUDIO_STATUS ;    /* Message Abort*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecPollingMessage( )
    \brief This message is used by any device for device discovery - similar to
           ping in other protocols

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecPollingMessage
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[3] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Polling Message command */
  I2c_Buffer[0] = 0x03;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,3); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 1;
  gtmdlHdmiCecDriverSaveMessage.Opcode = 0;

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordStatus( )
    \brief This message is used by a recording device to inform the initiator
           of the message <Record On> about its status.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECRecordStatusInfo_t  RecordStatusInfo \n
           The recording status of the device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordStatus
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECRecordStatusInfo_t  RecordStatusInfo
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_STATUS ;    /* Record Status */
  I2c_Buffer[4] = RecordStatusInfo; /* Record Status */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordOff( )
    \brief This message request a device to stop a recording

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOff
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record Off command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_OFF ;   /* Record Off */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordOnAnalogueService( )
    \brief This message attempt to record analogue source

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n

    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n

    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnAnalogueService
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   tmdlHdmiCECAnalogueBroadcastType_t  AnalogueBroadcastType,
   UInt16                              AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t        BroadcastSystem
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[9] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Record On Analogue Device command */
  I2c_Buffer[0] = 0x09;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_ON ;                     /*Record On*/

  I2c_Buffer[4] = CEC_RECORD_SOURCE_ANALOGUE_SERVICE;        /*RecordSourceType = CEC_RECORD_SOURCE_ANALOGUE_SERVICE*/
  I2c_Buffer[5] = AnalogueBroadcastType;                     /*Analogue Brodcast Type*/
  I2c_Buffer[6] = (unsigned char)(AnalogueFrequency >> 8);   /*Analogue Frequency*/
  I2c_Buffer[7] = (unsigned char)AnalogueFrequency;
  I2c_Buffer[8] = BroadcastSystem;                           /*Brodcast System*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,9); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordOnDigitalService( )
    \brief This message attempt to record digital source

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnDigitalService
(
   tmInstance_t                              Instance,
   UInt8                                     ReceiverLogicalAddress,
   tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[12] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCECAribData_t *pARIB_Pointer;
  tmdlHdmiCECAtscData_t *pATSC_Pointer;
  tmdlHdmiCECDvbData_t  *pDVB_Pointer;

  unsigned char Regval;                 /* Local variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record On Digital Service command */
  I2c_Buffer[0] = 0x0C;     /* Param number = 10*/

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_ON ;                  /* Record On Digital Service*/

  I2c_Buffer[4] = CEC_RECORD_SOURCE_DIGITAL_SERVICE;     /* RecordSourceType = CEC_RECORD_SOURCE_DIGITAL_SERVICE */

  /* Digital Service Identification*/
  /*Merge Service Method and Digital Broadcast System in the same Byte*/
  Regval = (unsigned char)(pServiceIdentification->ServiceIdentificationMethod & 0x01); /*bit 7 is Service Method*/
  Regval = Regval << 7;
  Regval |= (unsigned char)(pServiceIdentification->DigitalBroadcastSystem & 0x7F);     /*bits 6 to 0 are Digital Broadcast*/
  I2c_Buffer[5] = Regval;

  /*Case of a ARIB Generic*/
  if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_GENERIC)
    {
        pARIB_Pointer = (tmdlHdmiCECAribData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[6] = (unsigned char)(pARIB_Pointer->TransportStreamID >> 8);
        I2c_Buffer[7] = (unsigned char)pARIB_Pointer->TransportStreamID;
        I2c_Buffer[8] = (unsigned char)(pARIB_Pointer->ServiceID >> 8);
        I2c_Buffer[9] = (unsigned char)pARIB_Pointer->ServiceID;
        I2c_Buffer[10] = (unsigned char)(pARIB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[11] = (unsigned char)pARIB_Pointer->OriginalNetworkID;
    }
    /*Case of a ATSC Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ATSC_GENERIC)
    {
        pATSC_Pointer = (tmdlHdmiCECAtscData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[6] = (unsigned char)(pATSC_Pointer->TransportStreamID >> 8);
        I2c_Buffer[7] = (unsigned char)pATSC_Pointer->TransportStreamID;
        I2c_Buffer[8] = (unsigned char)(pATSC_Pointer->ProgramNumber >> 8);
        I2c_Buffer[9] = (unsigned char)pATSC_Pointer->ProgramNumber;
        I2c_Buffer[10] = (unsigned char)(pATSC_Pointer->Reserved >> 8);
        I2c_Buffer[11] = (unsigned char)pATSC_Pointer->Reserved;
    }
    /*Case of a DVB Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_DVB_GENERIC)
    {
        pDVB_Pointer = (tmdlHdmiCECDvbData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[6] = (unsigned char)(pDVB_Pointer->TransportStreamID >> 8);
        I2c_Buffer[7] = (unsigned char)pDVB_Pointer->TransportStreamID;
        I2c_Buffer[8] = (unsigned char)(pDVB_Pointer->ServiceID >> 8);
        I2c_Buffer[9] = (unsigned char)pDVB_Pointer->ServiceID;
        I2c_Buffer[10] = (unsigned char)(pDVB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[11] = (unsigned char)pDVB_Pointer->OriginalNetworkID;
    }
    /*other cases, Buffer are empty*/
  else
    {
        I2c_Buffer[6] = 0xFF;
        I2c_Buffer[7] = 0xFF;
        I2c_Buffer[8] = 0xFF;
        I2c_Buffer[9] = 0xFF;
        I2c_Buffer[10] = 0xFF;
        I2c_Buffer[11] = 0xFF;
    }
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,12); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordOnExternalPhysicalAddress( )
    \brief This message attempt to record an external physical address source

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Defines the path between the TV an a device-thus giving it a physical
           address within the cluster.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnExternalPhysicalAddress
(
   tmInstance_t                         Instance,
   UInt8                                ReceiverLogicalAddress,
   tmdlHdmiCECExternalPhysicalAddress_t ExternalPhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[7] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record On External Physial Address command */
  I2c_Buffer[0] = 0x07;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_ON ;                          /*Record On*/
  I2c_Buffer[4] = CEC_RECORD_SOURCE_EXTERNAL_PHYSICAL_ADDRESS;    /*RecordSourceType = CEC_RECORD_SOURCE_EXTERNAL_PHYSICAL_ADDRESS*/
  I2c_Buffer[5] = (unsigned char)(ExternalPhysicalAddress >> 8);  /*External Physical Address*/
  I2c_Buffer[6] = (unsigned char)ExternalPhysicalAddress;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7);       /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordOnExternalPlug( )
    \brief This message attempt to record an external plug source

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECExternalPlug_t  ExternalPlug \n
           indicates external plug number (1 to 255 )on the recording device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnExternalPlug
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECExternalPlug_t      ExternalPlug
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record On External Plug command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_ON ;                   /* Record On*/

  I2c_Buffer[4] = CEC_RECORD_SOURCE_EXTERNAL_PLUG;         /* RecordSourceType = CEC_RECORD_SOURCE_EXTERNAL_PLUG*/
  I2c_Buffer[5] = ExternalPlug;                            /*External Plug*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRecordOnOwnSource( )
    \brief This message attempt to record an external plug source

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnOwnSource
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Record On Own Source command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_RECORD_ON ;                /* Record On*/

  I2c_Buffer[4] = CEC_RECORD_SOURCE_OWN_SOURCE;         /* RecordSourceType = CEC_RECORD_SOURCE_OWN_SOURCE*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}


//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportPhysicalAddress( )
    \brief This message is used to inform all other devices of the mapping
           between physical and logical address of the initiator.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt16 PhysicalAddress \n
           Device physical address within the cluster. \n

    \param tmdlHdmiCECDeviceType_t DeviceType \n
           Type of the device (TV, Playback, tuner,...). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportPhysicalAddress
(
   tmInstance_t             Instance,
   UInt16                   PhysicalAddress,
   tmdlHdmiCECDeviceType_t  DeviceType
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[7] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Report Physical Address command */
  I2c_Buffer[0] = 0x07;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_PHYSICAL_ADDRESS ;      /* Report Physical Address */
  I2c_Buffer[4] = (unsigned char)(PhysicalAddress >> 8);    /* MsByte of Physical Address*/
  I2c_Buffer[5] = (unsigned char)PhysicalAddress;           /* LsByte of Physical Address */

  I2c_Buffer[6] = DeviceType ;                              /* Device Type*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetMenuLanguage( )
    \brief This message is used by a TV or another device to indicate the menu
           Language.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param const char *pLanguage \n
           Pointer on the user's menu language choice. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetMenuLanguage
(
   tmInstance_t Instance,
   const char   *pLanguage
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[7] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
 // RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set Menu Language command */
  I2c_Buffer[0] = 0x07;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_SET_MENU_LANGUAGE ;        /* Set Menu Language*/
  I2c_Buffer[4] = pLanguage[0];     /* First Tocken*/
  I2c_Buffer[5] = pLanguage[1];
  I2c_Buffer[6] = pLanguage[2];     /* Last Tocken*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecDeckControl()
    \brief This message is used to conrol a device's media functions

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECDecControlMode_t DeckControlMode \n
           Used in message <Deck Control>\n

    \note  The "Skip Forward / Wind" and "Skip Reverse / Rewind" values are
           used for example in a DVD as next xhapter and previous chapter and
           in a VCR as wind and rewind. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDeckControl
(
   tmInstance_t                Instance,
   UInt8                       ReceiverLogicalAddress,
   tmdlHdmiCECDecControlMode_t DeckControlMode
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if Instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to Instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if Instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Deck Control command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_DESCK_CONTROL;     /* Deck Control Mode*/
  I2c_Buffer[4] = DeckControlMode;      /* Deck Control Value*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecDeckStatus()
    \brief This message is used to provide a deck's status to the initiator
           of the <Give Deck Status> message

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECDecInfo_t DeckInfo \n
           Information on the device's current status \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDeckStatus
(
   tmInstance_t         Instance,
   UInt8                ReceiverLogicalAddress,
   tmdlHdmiCECDecInfo_t DeckInfo
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Deck Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_DECK_STATUS;       /* Deck Status*/
  I2c_Buffer[4] = DeckInfo;     /* Deck Status Mode Information*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveDeckStatus( )
    \brief This message is used to request the status of a device regardless
           of whether or not it is the current active source.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECStatusRequest_t StatusRequest \n
           Allows the initiator to request the status once or on all future state
           change. Or to cancel a previous <Give Deck Status > ["On"] request. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveDeckStatus
(
   tmInstance_t               Instance,
   UInt8                      ReceiverLogicalAddress,
   tmdlHdmiCECStatusRequest_t StatusRequest
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if Instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give Deck Status command */
  I2c_Buffer[0] = 0x05;    /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_DECK_STATUS;      /* Give Deck Status*/
  I2c_Buffer[4] = StatusRequest;        /* Deck Status Request Information*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecPlay( )
    \brief This message is used to control the playback behaviour of a source
           device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECPlayMode_t  PlayMode \n
           In which mode to play media. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecPlay
(
   tmInstance_t           Instance,
   UInt8                  ReceiverLogicalAddress,
   tmdlHdmiCECPlayMode_t  PlayMode
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Play command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_PLAY;  /* Play*/
  I2c_Buffer[4] = (unsigned char)PlayMode;          /* Play Mode Information Information*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSelectDigitalService( )
    \brief This message select directly a digital TV, Radio or Data Broadcast
           Service.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSelectDigitalService
(
   tmInstance_t                                Instance,
   UInt8                                       ReceiverLogicalAddress,
   ptmdlHdmiCECDigitalServiceIdentification_t  pServiceIdentification
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[11] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCECAribData_t *pARIB_Pointer;
  tmdlHdmiCECAtscData_t *pATSC_Pointer;
  tmdlHdmiCECDvbData_t  *pDVB_Pointer;

  unsigned char Regval;                 /*Local Variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Select Digital Service command */
  I2c_Buffer[0] = 0x0B;     /* Param number = 10*/

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_DIGITAL_SERVICE ;      /* Select Digital Service*/

  /*Merge Service Method and Digital Broadcast System in the same Byte*/
  Regval = (unsigned char)(pServiceIdentification->ServiceIdentificationMethod & 0x01); /* Load the 1 bit of Service Method*/
  Regval = Regval << 7;
  Regval |= (unsigned char)(pServiceIdentification->DigitalBroadcastSystem & 0x7F);     /*Merge with the 7 bits of Digital Broadcast*/
  I2c_Buffer[4] = Regval;

  /*Case of a ARIB Generic*/
  if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_GENERIC)
    {
        pARIB_Pointer = (tmdlHdmiCECAribData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[5] = (unsigned char)(pARIB_Pointer->TransportStreamID >> 8);     /* Service Identification */
        I2c_Buffer[6] = (unsigned char)pARIB_Pointer->TransportStreamID;
        I2c_Buffer[7] = (unsigned char)(pARIB_Pointer->ServiceID >> 8);
        I2c_Buffer[8] = (unsigned char)pARIB_Pointer->ServiceID;
        I2c_Buffer[9] = (unsigned char)(pARIB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[10] = (unsigned char)pARIB_Pointer->OriginalNetworkID;
    }
    /*Case of a ATSC Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ATSC_GENERIC)
    {
        pATSC_Pointer = (tmdlHdmiCECAtscData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[5] = (unsigned char)(pATSC_Pointer->TransportStreamID >> 8);     /* Service Identification */
        I2c_Buffer[6] = (unsigned char)pATSC_Pointer->TransportStreamID;
        I2c_Buffer[7] = (unsigned char)(pATSC_Pointer->ProgramNumber >> 8);
        I2c_Buffer[8] = (unsigned char)pATSC_Pointer->ProgramNumber;
        I2c_Buffer[9] = (unsigned char)(pATSC_Pointer->Reserved >> 8);
        I2c_Buffer[10] = (unsigned char)pATSC_Pointer->Reserved;
    }
    /*Case of a DVB Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_DVB_GENERIC)
    {
        pDVB_Pointer = (tmdlHdmiCECDvbData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[5] = (unsigned char)(pDVB_Pointer->TransportStreamID >> 8);      /* Service Identification */
        I2c_Buffer[6] = (unsigned char)pDVB_Pointer->TransportStreamID;
        I2c_Buffer[7] = (unsigned char)(pDVB_Pointer->ServiceID >> 8);
        I2c_Buffer[8] = (unsigned char)pDVB_Pointer->ServiceID;
        I2c_Buffer[9] = (unsigned char)(pDVB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[10] = (unsigned char)pDVB_Pointer->OriginalNetworkID;
    }
    /*other cases, Buffer are empty*/
  else
    {
        I2c_Buffer[5] = 0xFF;       /* Service Identification */
        I2c_Buffer[6] = 0xFF;
        I2c_Buffer[7] = 0xFF;
        I2c_Buffer[8] = 0xFF;
        I2c_Buffer[9] = 0xFF;
        I2c_Buffer[10] = 0xFF;
    }
	errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,11); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetAnalogueTimer( )
    \brief This message is used to set asingle timer block on an analogue
           recording device.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n

    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n

    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetAnalogueTimer
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   UInt8                               DayOfMonth,
   UInt8                               MonthOfYear,
   UInt16                              StartTime,
   tmdlHdmiCECDuration_t              *pDuration,
   UInt8                               RecordingSequence,
   tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType,
   UInt16                              AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t       BroadcastSystem
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[15] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set Analogue Timer command */
  I2c_Buffer[0] = 0x0F;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_ANALOGUE_TIMER ;   /* Message Abort*/
  I2c_Buffer[4] = DayOfMonth;
  I2c_Buffer[5] = MonthOfYear;
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);
  I2c_Buffer[7] = (unsigned char)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;
  I2c_Buffer[9] = pDuration -> Minute;
  I2c_Buffer[10] = RecordingSequence;
  I2c_Buffer[11] = AnalogueBroadcastType;
  I2c_Buffer[12] = (unsigned char)(AnalogueFrequency >> 8);
  I2c_Buffer[13] = (unsigned char)AnalogueFrequency;
  I2c_Buffer[14] = BroadcastSystem;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,15); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetAudioRate( )
    \brief This message is used to control audio rate from Source device.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECAudioRate_t AudioRate \n
           The audio rate requested. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetAudioRate
(
   tmInstance_t           Instance,
   UInt8                  ReceiverLogicalAddress,
   tmdlHdmiCECAudioRate_t AudioRate
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set Audio Rate command */
  I2c_Buffer[0] = 0x05;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_AUDIO_RATE ;   /* Set Audio Rate */
  I2c_Buffer[4] = AudioRate;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetDigitalTimer( )
    \brief This message is used to set a digital timer block on a digital
           recording device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetDigitalTimer
(
   tmInstance_t                               Instance,
    UInt8                                     ReceiverLogicalAddress,
   UInt8                                      DayOfMonth,
   UInt8                                      MonthOfYear,
   UInt16                                     StartTime,
   tmdlHdmiCECDuration_t                     *pDuration,
   UInt8                                      RecordingSequence,
   tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[18] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  tmdlHdmiCECAribData_t *pARIB_Pointer;
  tmdlHdmiCECAtscData_t *pATSC_Pointer;
  tmdlHdmiCECDvbData_t  *pDVB_Pointer;

  unsigned char Regval;                 /* Local variable*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set Digital Timer command */
  I2c_Buffer[0] = 0x12;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_DIGITAL_TIMER ;        /* Set Digital Timer*/
  I2c_Buffer[4] = DayOfMonth;                           /* Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                          /* Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);      /* Start Time*/
  I2c_Buffer[7] = (unsigned char)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;                   /* Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;                  /* Duration Minute*/
  I2c_Buffer[10] = RecordingSequence;                   /*Recording Sequence*/

  /* Digital service Identification*/
  /*Merge Service Method and Digital Broadcast System in the same Byte*/
  Regval = (unsigned char)(pServiceIdentification->ServiceIdentificationMethod & 0x01); /*bit 7 is Service Method*/
  Regval = Regval << 7;
  Regval |= (unsigned char)(pServiceIdentification->DigitalBroadcastSystem & 0x7F);     /*bits 6 to 0 are Digital Broadcast*/
  I2c_Buffer[11] = Regval;

  /*Case of a ARIB Generic*/
  if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_GENERIC)
    {
        pARIB_Pointer = (tmdlHdmiCECAribData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[12] = (unsigned char)(pARIB_Pointer->TransportStreamID >> 8);
        I2c_Buffer[13] = (unsigned char)pARIB_Pointer->TransportStreamID;
        I2c_Buffer[14] = (unsigned char)(pARIB_Pointer->ServiceID >> 8);
        I2c_Buffer[15] = (unsigned char)pARIB_Pointer->ServiceID;
        I2c_Buffer[16] = (unsigned char)(pARIB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[17] = (unsigned char)pARIB_Pointer->OriginalNetworkID;
    }
    /*Case of a ATSC Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_ATSC_GENERIC)
    {
        pATSC_Pointer = (tmdlHdmiCECAtscData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[12] = (unsigned char)(pATSC_Pointer->TransportStreamID >> 8);
        I2c_Buffer[13] = (unsigned char)pATSC_Pointer->TransportStreamID;
        I2c_Buffer[14] = (unsigned char)(pATSC_Pointer->ProgramNumber >> 8);
        I2c_Buffer[15] = (unsigned char)pATSC_Pointer->ProgramNumber;
        I2c_Buffer[16] = (unsigned char)(pATSC_Pointer->Reserved >> 8);
        I2c_Buffer[17] = (unsigned char)pATSC_Pointer->Reserved;
    }
    /*Case of a DVB Generic*/
  else if(pServiceIdentification->DigitalBroadcastSystem == CEC_DIGITAL_BROADCAST_SYSTEM_DVB_GENERIC)
    {
        pDVB_Pointer = (tmdlHdmiCECDvbData_t*)pServiceIdentification->pServiceIdentification;

        I2c_Buffer[12] = (unsigned char)(pDVB_Pointer->TransportStreamID >> 8);
        I2c_Buffer[13] = (unsigned char)pDVB_Pointer->TransportStreamID;
        I2c_Buffer[14] = (unsigned char)(pDVB_Pointer->ServiceID >> 8);
        I2c_Buffer[15] = (unsigned char)pDVB_Pointer->ServiceID;
        I2c_Buffer[16] = (unsigned char)(pDVB_Pointer->OriginalNetworkID >> 8);
        I2c_Buffer[17] = (unsigned char)pDVB_Pointer->OriginalNetworkID;
    }
    /*other cases, Buffer are empty*/
  else
    {
        I2c_Buffer[12] = 0xFF;
        I2c_Buffer[13] = 0xFF;
        I2c_Buffer[14] = 0xFF;
        I2c_Buffer[15] = 0xFF;
        I2c_Buffer[16] = 0xFF;
        I2c_Buffer[17] = 0xFF;
    }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,18); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetExternalTimerWithExternalPlug( )
    \brief This message is used to set a single timer block to record from an
           external device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECExternalPlug_t  ExternalPlug \n
           indicates external plug number (1 to 255 )on the recording device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetExternalTimerWithExternalPlug
(
   tmInstance_t                Instance,
   UInt8                       ReceiverLogicalAddress,
   UInt8                       DayOfMonth,
   UInt8                       MonthOfYear,
   UInt16                      StartTime,
   tmdlHdmiCECDuration_t      *pDuration,
   UInt8                       RecordingSequence,
   tmdlHdmiCECExternalPlug_t  ExternalPlug
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[13] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set External Timer With External Plug command */
  I2c_Buffer[0] = 0x0D;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_EXTERNAL_TIMER ;   /*SetDigital Timer*/

  I2c_Buffer[4] = DayOfMonth;                       /*Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                      /*Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);  /*Start Time*/
  I2c_Buffer[7] = (unsigned char)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;               /*Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;              /*Duration Minute*/
  I2c_Buffer[10] = RecordingSequence;               /*Recording Sequence*/
  I2c_Buffer[11] = CEC_EXTERNAL_PLUG;               /*External Source Specifier = External Plug */
  I2c_Buffer[12] = ExternalPlug;                    /*External Plug*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,13); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetExternalTimerWithPhysicalAddress( )
    \brief This message is used to set a single timer block to record from an
           external device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8  DayOfMonth \n
           Day of the month.\n

    \param UInt8  MonthOfYear \n
           Month of the year.\n

    \param UInt16 StartTime \n
           Start time for a timer based recording.\n

    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n

    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n

    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Defines the path between the TV an a device-thus giving it a physical
           address within the cluster.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetExternalTimerWithPhysicalAddress
(
   tmInstance_t                           Instance,
   UInt8                                  ReceiverLogicalAddress,
   UInt8                                  DayOfMonth,
   UInt8                                  MonthOfYear,
   UInt16                                 StartTime,
   tmdlHdmiCECDuration_t                 *pDuration,
   UInt8                                  RecordingSequence,
   tmdlHdmiCECExternalPhysicalAddress_t  ExternalPhysicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[14] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set external Timer With External Physical Address command */
  I2c_Buffer[0] = 0x0E;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_EXTERNAL_TIMER ;   /* SetDigital Timer*/

  I2c_Buffer[4] = DayOfMonth;                       /* Day of Month*/
  I2c_Buffer[5] = MonthOfYear;                      /* Month of Year*/
  I2c_Buffer[6] = (unsigned char)(StartTime >> 8);  /* Start Time*/
  I2c_Buffer[7] = (unsigned char)StartTime;
  I2c_Buffer[8] = pDuration -> Hours;               /* Duration Hours*/
  I2c_Buffer[9] = pDuration -> Minute;              /* Duration Minute*/
  I2c_Buffer[10] = RecordingSequence;               /* Recording Sequence*/
  I2c_Buffer[11] = CEC_EXTERNAL_PHYSICAL_ADDRESS;   /*External Source Specifier = External Address*/
  I2c_Buffer[12] = (unsigned char)(ExternalPhysicalAddress >> 8);  /*External Address*/
  I2c_Buffer[13] = (unsigned char) ExternalPhysicalAddress;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,14); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTunerStepDecrement( )
    \brief This message is used to tune to next lowest service in a tuner's
           service list.Can be used for PIP.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerStepDecrement
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{

  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Tuner Step Decrement command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TUNER_STEP_DECREMENT ;         /* Tuner Step Decrement*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTunerStepIncrement( )
    \brief This message is used to tune to next highest service in a tuner's
           service list.Can be used for PIP.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerStepIncrement
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Tuner Step Increment command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_TUNER_STEP_INCREMENT ;     /* Tuner Step Increment*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecDeviceVendorID()
    \brief This message report the vendor ID of this device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt32 VendorID \n
           Indentifier for a specific Vendor \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDeviceVendorID
(
   tmInstance_t Instance,
   UInt32       VendorID
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[7] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Device Vendor ID command */
  I2c_Buffer[0] = 0x07;     /* Param number in case of Vendor ID is 32 Bytes*/

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= 0x0F;                                                            /* Broadcast*/

  I2c_Buffer[3] = CEC_OPCODE_DEVICE_VENDOR_ID ;     /* Device Vendor ID opcode = 0x87*/
  I2c_Buffer[4] = (unsigned char)(VendorID >> 16);  /* MSByte of Vendor ID*/
  I2c_Buffer[5] = (unsigned char)(VendorID >> 8);
  I2c_Buffer[6] = (unsigned char)VendorID;          /* LSByte of Vendor ID*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,7); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveDeviceVendorID( )
    \brief This message is request the vendor ID from a device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveDeviceVendorID
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give Device Vendor ID command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_DEVICE_VENDOR_ID ;        /* Give Device Vendor*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecVendorCommand( )
    \brief This message is allows vendor specific commands to be sent between
           two devices.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8  *pVendorSpecificData \n
           Pointer to the Vendor Specific datas

    \param UInt8    VendorSpecificDataLength \n
           Length of VendorSpecificData. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorCommand
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt8         *pVendorSpecificData,
   UInt8         VendorSpecificDataLength
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[19] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char loci;                   /* Local increment variable*/
  unsigned char MessLength;             /* Local Message length*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Vendor Command command */
  MessLength = VendorSpecificDataLength + 4;       /* Calculate Message length*/

  I2c_Buffer[0] = MessLength;                    /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_VENDOR_COMMAND ;       /* Vendor Command*/

  for(loci = 0; loci <= VendorSpecificDataLength ; loci++)
    {
        I2c_Buffer[(loci+7)] = pVendorSpecificData[loci];    /* Fill Table with vendorSpecific Data characters*/
    }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,MessLength); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecVendorCommandWithID( )
    \brief This message is allows vendor specific commands to be sent between
           two devices or broadcast.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt32 VendorID \n
           Indentifier for a specific Vendor \n

    \param UInt8  *pVendorSpecificData \n
           Pointer to the Vendor Specific datas

    \param UInt8    VendorSpecificDataLength \n
           Length of VendorSpecificData. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorCommandWithID
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt32        VendorID,
   UInt8         *pVendorSpecificData,
   UInt8         VendorSpecificDataLength
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[19] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char loci;                   /* Local increment variable*/
  unsigned char MessLength;             /* Local Message length*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Vendor Command With ID command */
   MessLength = VendorSpecificDataLength + 7;       /* Calculate Message length*/

  I2c_Buffer[0] = MessLength;                      /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_VENDOR_COMMAND_WITH_ID ;       /* Vendor Command*/
  I2c_Buffer[4] = (unsigned char)(VendorID >> 16);  /* MSByte of Vendor ID*/
  I2c_Buffer[5] = (unsigned char)(VendorID >> 8);
  I2c_Buffer[6] = (unsigned char)VendorID;          /* LSByte of Vendor ID*/

  for(loci = 0; loci <= VendorSpecificDataLength ; loci++)
  {
     I2c_Buffer[(loci+7)] = pVendorSpecificData[loci];    /* Fill Table with vendorSpecific Data characters*/
  }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,MessLength); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecVendorRemoteButtonDown( )
    \brief This message indicates that a remote control button has been depressed.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8  *pVendorSpecificRcCode \n
           Pointer to the Vendor Specific remote control code.
           its recommended t keep this to a minimum size.
           The maximum length shall not exceed 14 data blocks to avoid saturating bus

    \param UInt8    VendorSpecificRcCodeLength \n
           Length of VendorSpecificRcCode. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorRemoteButtonDown
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt8         *pVendorSpecificRcCode,
   UInt8         VendorSpecificRcCodeLength
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[19] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char loci;                   /* Local increment variable*/
  unsigned char MessLength;             /* Local Message length*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  /* Vendor Remote Button Down command */
  MessLength = VendorSpecificRcCodeLength + 4;         /* Calculate Message length*/

  I2c_Buffer[0] = MessLength;                       /* Message Length */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_VENDOR_REMOTE_BUTTON_DOWN ;    /* Vendor Remote Button Down Opcode*/
  /*Vendor Specific RC code Parameter*/
  for(loci = 0; loci <= VendorSpecificRcCodeLength ; loci++)
    {
        I2c_Buffer[(loci+4)] = pVendorSpecificRcCode[loci];   /* Fill Table with Vendor Specific RC Code data*/
    }
  /*Send message Via I2C*/
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,MessLength);
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecVendorRemoteButtonUp( )
    \brief This message indicates that a remote control button (the last button
           pressed indicated by the <Vendor remote button down > message) has
           been released.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorRemoteButtonUp
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Vendor Remote Button Up command */
  I2c_Buffer[0] = 0x05;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_VENDOR_REMOTE_BUTTON_UP ;      /* Vendor Remote Button Up*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetOsdString( )
    \brief This message is used to send a test message to output on a TV.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECDisplayControl_t DisplayControl \n
           Display timing. \n

    \param const char *pOsdString \n
           Pointer on the Text to display. \n

    \param UInt8    OsdStringLength \n
           Length of Osd String. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetOsdString
(
   tmInstance_t                 Instance,
   UInt8                        ReceiverLogicalAddress,
   tmdlHdmiCECDisplayControl_t  DisplayControl,
   const char                   *pOsdString,
   UInt8                        OsdStringLength
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[19] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char loci;                   /* Local increment variable*/
  unsigned char MessLength;             /* Local Message length*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set OSD String command */

  MessLength = OsdStringLength+5;                   /* Calculate Message length*/

  I2c_Buffer[0] = (unsigned char)MessLength;

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_OSD_STRING ;       /* Set Osd String*/
  I2c_Buffer[4] = DisplayControl;                   /*Display Control*/
   for(loci = 0; loci <= OsdStringLength ; loci++)
    {
        I2c_Buffer[(loci+5)] = pOsdString[loci];         /* Fill Table with OSD Name characters*/
    }
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,(MessLength)); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveOsdName( )
    \brief This message is used to request preferred OSD name of a device
           for use in menus associated with that device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveOsdName
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give OSD Name command */
  I2c_Buffer[0] = 0x04;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_OSD_NAME ;    /* Give OSD Name*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetOsdName( )
    \brief This message is used to set the preferred OSD name of a device
           for use in manus associated with that device.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param const char *pOsdName \n
           Pointer on the preferred name of the device. \n

    \param UInt8    OsdNameLength \n
           Length of Osd Name String. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetOsdName
(
   tmInstance_t Instance,
   UInt8        ReceiverLogicalAddress,
   const char   *pOsdName,
   UInt8        OsdNameLength
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[19] ;       /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */
  unsigned char loci;                   /* Local increment variable*/
  unsigned char MessLength;             /* Local Message length*/

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Set OSD Name command */

  MessLength = OsdNameLength+4;                         /* Calculate Message length*/

  I2c_Buffer[0] = (unsigned char)MessLength;
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_SET_OSD_NAME ;     /* Set Osd Name*/
    for(loci = 0; loci <= OsdNameLength ; loci++)
    {
        I2c_Buffer[(loci+4)] = pOsdName[loci];       /* Fill Table with OSD Name characters*/
    }

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,(MessLength)); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecMenuRequest( )
    \brief This message request from the TV for a device to show/remove a
           menu or to query if a device is currently showing a menu

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECMenuRequestType_t  MenuRequestType \n
           Indicates if the menu request is to activate or deactivate the
           devices menu or simply query the devices menu status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecMenuRequest
(
   tmInstance_t                  Instance,
   UInt8                         ReceiverLogicalAddress,
   tmdlHdmiCECMenuRequestType_t  MenuRequestType
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Menu Request command */
  I2c_Buffer[0] = 0x05;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_MENU_REQUEST ;     /* Menu Request*/
  I2c_Buffer[4] = MenuRequestType;              /*Menu Request Type */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecMenuStatus( )
    \brief This message is used to indicate to the TV that the device is
           showing/has removed a menu and requets the remote control keys to
           be passed though

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECMenuState_t  MenuState \n
           Indicates if the device is in the 'Device Menu Active' state or
           'Device Menu Inactive' state. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecMenuStatus
(
   tmInstance_t            Instance,
   UInt8                   ReceiverLogicalAddress,
   tmdlHdmiCECMenuState_t  MenuState
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Menu Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_MENU_STATUS;       /* Menu Status*/
  I2c_Buffer[4] = MenuState;                    /* Menu State*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlPressed( )
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECUserRemoteControlCommand_t UICommand \n
           Relevant UI command issued by user. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressed
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECUserRemoteControlCommand_t UICommand
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Pressed command */
  I2c_Buffer[0] = 0x05;     /* Param number */
  
  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_PRESSED;      /* User Control pressed*/
  I2c_Buffer[4] = UICommand;                            /* UI Command*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlPressedPlay( )
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECPlayMode_t PlayMode \n
           In which mode to play media. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedPlay
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECPlayMode_t                 PlayMode
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Presses Play command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_PRESSED;      /* User Control Pressed*/

  I2c_Buffer[4] = CEC_REMOTE_BUTTON_PLAY_FUNCTION;      /* UI Command = CEC_REMOTE_BUTTON_PLAY_FUNCTION */
  I2c_Buffer[5] = PlayMode;                             /* Play Mode*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlPressedSelectAudioInput( )
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 SelectAudioInput \n
           Number of the Audio Input (Audio input number between 1 and 255). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedSelectAudioInput
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   UInt8                                 SelectAudioInput
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Pressed Select Audio Input command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_PRESSED;                /* User Control Pressed*/

  I2c_Buffer[4] = CEC_REMOTE_BUTTON_SELECT_AUDIO_INPUT_FUNCTION;  /* UI Command = CEC_REMOTE_BUTTON_SELECT_AUDIO_INPUT_FUNCTION*/
  I2c_Buffer[5] = SelectAudioInput;                               /* UI Function Select Audio mode*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6);       /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlPressedSelectAVInput( )
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 SelectAVInput \n
           Number of the A/V Input (A/V input number between 1 and 255). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedSelectAVInput
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   UInt8                                 SelectAVInput
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Pressed Select AV Input command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_PRESSED;             /* User Control Pressed*/

  I2c_Buffer[4] = CEC_REMOTE_BUTTON_SELECT_AV_INPUT_FUNCTION;  /* UI Command = CEC_REMOTE_BUTTON_SELECT_AV_INPUT_FUNCTION */
  I2c_Buffer[5] = SelectAVInput;                               /* UI Function Select A/V Input*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlPressedSelectMedia( )
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 SelectMedia \n
           Number of Media (Media number between 1 and 255). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedSelectMedia
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   UInt8                                 SelectMedia
)
{ 
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Pressed Select Media command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_PRESSED;          /* User Control Pressed*/

  I2c_Buffer[4] = CEC_REMOTE_BUTTON_SELECT_MEDIA_FUNCTION;  /* UI Command = CEC_REMOTE_BUTTON_SELECT_MEDIA_FUNCTION*/
  I2c_Buffer[5] = SelectMedia;                              /* UI Function Media*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlPressedTune( )
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECChannelIdentifier_t  *pChannelIdentifier \n
           Pointer to the structure of Major and Minor Channel number

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedTune
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECChannelIdentifier_t        *pChannelIdentifier
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[10] ;       /* I2C data buffer */
  UInt16 Regval16 ;                      /* Local variable used for conversion*/
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Pressed Tune command */
  I2c_Buffer[0] = 0x0A;   /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_PRESSED;      /* User Control Pressed Opcode*/

  I2c_Buffer[4] = CEC_REMOTE_BUTTON_TUNE_FUNCTION;      /* UI Command = CEC_REMOTE_BUTTON_TUNE_FUNCTION*/

  /* Merge 6 bits of ChanNum with 10 bits of Major channel*/
  Regval16 = (UInt16)(pChannelIdentifier->ChanNumFormat & 0x003F); // Save the 6 lsbits
  Regval16 = Regval16 << 10;
  Regval16 |= (UInt16)(pChannelIdentifier->MajorChanNumber & 0x03FF);

  /* Load the 4 information bytes of Channel ID*/
  I2c_Buffer[5] = (unsigned char)(Regval16 >> 8);
  I2c_Buffer[6] = (unsigned char)Regval16;
  I2c_Buffer[7] = (unsigned char)(pChannelIdentifier->MinorChanNumber >> 8);
  I2c_Buffer[8] = (unsigned char)pChannelIdentifier->MinorChanNumber;

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,9); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}
//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecUserControlReleased( )
    \brief This message is used to indicate that the user released a remote button
           The last one indicated by the <User Control Pressed> Message.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlReleased
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* User Control Released command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_USER_CONTROL_RELEASED ;        /* User Control Released */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGiveDevicePowerStatus( )
    \brief This message is used to determine the current power status of a
           target device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveDevicePowerStatus
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Give Device power Status Power Status command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GIVE_DEVICE_POWER_STATUS ;     /* Give Device Power Status */

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportPowerStatus( )
    \brief This message is used to inform a requesting device of the current
           power status.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECPowerStatus_t PowerStatus \n
           Current power status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportPowerStatus
(
   tmInstance_t             Instance,
   UInt8                    ReceiverLogicalAddress,
   tmdlHdmiCECPowerStatus_t PowerStatus
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[5] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Report Power Status command */
  I2c_Buffer[0] = 0x05;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

 /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_REPORT_POWER_STATUS ;      /* Report Power Status*/
  I2c_Buffer[4] = PowerStatus;                          /* Power Status*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,5); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecFeatureAbort()
    \brief This message is used as a reponse to indicate that the device does
           not support the requested message type, or that it cannot execute it
           at the present time.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param tmdlHdmiCECFeatureOpcode_t FeatureOpcode \n
           Opcode of the aborted message. \n

    \param tmdlHdmiCECAbortReason_t   AbortReason \n
           The reason why message cannot respond. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecFeatureAbort
(
   tmInstance_t               Instance,
   UInt8                      ReceiverLogicalAddress,
   tmdlHdmiCECFeatureOpcode_t FeatureOpcode,
   tmdlHdmiCECAbortReason_t   AbortReason
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[6] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Feature Abort command */
  I2c_Buffer[0] = 0x06;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_FEATURE_ABORT ;    /* Feature Abort*/
  I2c_Buffer[4] = FeatureOpcode;    /* Feature Opcode*/
  I2c_Buffer[5] = AbortReason;      /* Abort Reason*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,6); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGetCecVersion( )
    \brief This message is used by a device to enquire which version of CEC
           the target supports

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetCecVersion
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* Get CEC Version command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_GET_CEC_VERSION ;  /* Get CEC Version*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecAbortMessage( )
    \brief This message is reserved for testing purposes

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \param UInt8 ReceiverLogicalAddress\n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecAbortMessage
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
)
{
  tmErrorCode_t  errCode;
  unsigned char  I2c_Buffer[4] ;        /* I2C data buffer */
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((Instance < 0) || (Instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[Instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

  /* check if instance state is correct */
  //RETIF(UnitTable[Instance].state != STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

  pDis = &gtmdlHdmiCecDriverConfigTable[Instance];

  //======To do : make a prepare message function with parameter
  /* CEC Abort Message command */
  I2c_Buffer[0] = 0x04;     /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[Instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= ReceiverLogicalAddress & 0x0F;                                   /* Receiver logical Address*/

  I2c_Buffer[3] = CEC_OPCODE_ABORT_MESSAGE ;    /* Message Abort*/

  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,4); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)

  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = I2c_Buffer[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = I2c_Buffer[3];

  return(TM_OK);
}

//Non Functional function used to provide easy way to access register 

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecGetRegister( )
    \brief Setup the instance with its configuration parameters. This function
           allows basic instance configuration for CEC Stack Processor.

    \param instance   Instance identifier.
    \param pSetupInfo Pointer to the structure containing all setup parameters

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
unsigned char tmdlHdmiCecGetRegister
(
    tmInstance_t               instance,
    UInt32                     offset
)
{
    tmErrorCode_t                  errCode;
	tmdlHdmiCecDriverConfigTable_t *pDis;     /* Pointer to Device Instance Structure */
    unsigned char               I2c_ReadBuffer[1];


    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), 0xFF)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, 0xFF)

    /* Ckeck the state */
    //RETIF(UnitTable[instance].state != CEC_STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];

    errCode = getCecHwRegisters(pDis, (UInt8) offset,I2c_ReadBuffer,1);
    RETIF(errCode != TM_OK, 0xff)

    return(I2c_ReadBuffer[0]);
}

//QB 10 Jan ==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetRegister( )
    \brief Setup the instance with its configuration parameters. This function
           allows basic instance configuration for CEC Stack Processor.

    \param instance   Instance identifier.
    \param pSetupInfo Pointer to the structure containing all setup parameters

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetRegister
(
    tmInstance_t                instance,
    UInt32                      offset,
    UInt32                      value
)
{
    tmErrorCode_t                  errCode;
    tmdlHdmiCecDriverConfigTable_t *pDis;     /* Pointer to Device Instance Structure */


    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    /* check if unit corresponding to instance is opened */
    RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)

    /* Ckeck the state */
    //RETIF(UnitTable[instance].state != CEC_STATE_NOT_INITIALIZED, TMDL_ERR_DLHDMICEC_INVALID_STATE)

        pDis = &gtmdlHdmiCecDriverConfigTable[instance];

    errCode = setCecHwRegister(pDis, (UInt8) offset,(UInt8)value);
    RETIF(errCode != TM_OK, errCode)

    return(TM_OK);
}



//==========================================================================
/*!
    \brief Set the power state of an instance of the CEC device. ON
           state corresponds to a fully supplied, up and running device. Other
           modes correspond to the powerdown state of the device.
           This function is synchronous.
           This function is not ISR friendly.


    \param instance   Instance identifier.
    \param powerState Power state to set.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetPowerState
(
    tmInstance_t   instance,
    tmPowerState_t powerState
)
{
    tmErrorCode_t errCode = TM_OK;

#ifdef TMFL_TDA9989
    unsigned char I2c_ReadBuffer[1];

    tmdlHdmiCecDriverConfigTable_t *pDis;

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];

    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    if (powerState == tmPowerOn) {
  
	errCode = getCecHwRegisters(pDis, E_REG_ENAMODS,I2c_ReadBuffer,1);
        RETIF(errCode != TM_OK, errCode)

	I2c_ReadBuffer[0] |= DEFAULT_ENAMODS;

        errCode = setCecHwRegister(pDis, E_REG_ENAMODS, I2c_ReadBuffer[0]);
	RETIF(errCode != TM_OK, errCode)


    }
    else if (powerState == tmPowerStandby) {

	errCode = getCecHwRegisters(pDis, E_REG_ENAMODS,I2c_ReadBuffer,1);
        RETIF(errCode != TM_OK, errCode)

        I2c_ReadBuffer[0] &=  ~(DEFAULT_ENAMODS);

        errCode = setCecHwRegister(pDis, E_REG_ENAMODS, I2c_ReadBuffer[0]);
	RETIF(errCode != TM_OK, errCode)

        UnitTable[instance].state = CEC_STATE_NOT_INITIALIZED;

    }
    else {
        return TMDL_ERR_DLHDMICEC_BAD_PARAMETER;
    }

#endif  /*  TMFL_TDA9989 */

    return errCode;
}


//==========================================================================
/*!
    \brief Get the power state of an instance of the CEC device. ON
           state corresponds to a fully supplied, up and running device. Other
           modes correspond to the powerdown state of the device.
           This function is synchronous.
           This function is not ISR friendly.

    \param instance    Instance identifier.
    \param pPowerState Pointer to the power state.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetPowerState
(
    tmInstance_t    instance,
    tmPowerState_t *pPowerState
)
{
   tmErrorCode_t errCode = TM_OK;

#ifdef TMFL_TDA9989

    unsigned char I2c_ReadBuffer[1];

    tmdlHdmiCecDriverConfigTable_t *pDis;

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];


    /* check if instance number is in range */
    RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

    if (pPowerState == NULL) return TMDL_ERR_DLHDMICEC_BAD_PARAMETER;


    errCode = getCecHwRegisters(pDis, E_REG_ENAMODS,I2c_ReadBuffer,1);
    RETIF(errCode != TM_OK, errCode)

    if ((I2c_ReadBuffer[0] & DEFAULT_ENAMODS) == DEFAULT_ENAMODS) {
        *pPowerState = tmPowerOn;
    }
    else {
        *pPowerState = tmPowerStandby;
    }


#endif  /*  TMFL_TDA9989 */

    return errCode;

}

//==========================================================================
/*!
    \brief This function allow to send a generic CEC message
           This function has to be used when CEC messages are construct in 
	   the middleware

    \param instance  Instance identifier.
    
    \param *pData    Pointer to the CEC data buffer 
    
    \param lenData   Lenght of I2C data buffer
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
	    - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSendMessage(

   tmInstance_t instance,
   UInt8        *pData,
   UInt16       lenData
)
{

  tmErrorCode_t  errCode = TM_OK;

#ifdef TMFL_TDA9989

  unsigned char  I2c_Buffer[19] ;        /* I2C data buffer */
  unsigned char  Loci;                   /* Local increment variable*/
  unsigned char  MessLength;             /* Local Message length*/
  
  tmdlHdmiCecDriverConfigTable_t *pDis; /* Pointer to Device Instance Structure */

  /* check if instance number is in range */
  RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

  /* check if unit corresponding to instance is opened */
  RETIF(UnitTable[instance].opened == False, TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED)
  
  /* check if CEC message is not too long */
  RETIF((lenData > 16), TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS)

  pDis = &gtmdlHdmiCecDriverConfigTable[instance];

  /* Calculate Internal Message length*/
  MessLength = (lenData-1)+3; /* real data is less ReceiverLogical address */
  
  I2c_Buffer[0] = MessLength;  /* Param number */

  I2c_Buffer[1] = 0x00;     /* Request CEC data */

  /*Build Initiator and Reciever Logical Address Byte*/
  I2c_Buffer[2] = (unsigned char)(UnitTable[instance].DeviceLogicalAddress) & 0x0F; /*Initiator logical Address*/
  I2c_Buffer[2] = I2c_Buffer[2] << 4;
  I2c_Buffer[2] |= pData[0] & 0x0F;

  for(Loci = 0; Loci <= lenData ; Loci++)
  {
     I2c_Buffer[(Loci+3)] = pData[(Loci+1)];     /* Fill Table with Data from middleware, Data begin at position 1*/
  }
  
  errCode = setCecHwRegisters(pDis, E_REG_CDR0, I2c_Buffer,MessLength); /* CEC Data register */
  RETIF(errCode != TM_OK, errCode)
  
  /* Save Datas of the CEC message send */
  gtmdlHdmiCecDriverSaveMessage.AddressByte = pData[2];
  gtmdlHdmiCecDriverSaveMessage.MessageTypePolling = 0;
  gtmdlHdmiCecDriverSaveMessage.Opcode = pData[3];

#endif  /*  TMFL_TDA9989 */

  return errCode;

}



//==========================================================================
//==========================================================================
tmErrorCode_t tmdlHdmiCecEnableCalibration(tmInstance_t instance,tmdlHdmiCecClockSource_t cecClockSource)
{
    tmErrorCode_t errCode = TM_OK;

#ifdef TMFL_TDA9989

    unsigned char                   I2c_ReadBuffer[1];
    tmdlHdmiCecDriverConfigTable_t *pDis;

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];

   /* check if instance number is in range */
   RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

   /* CLOCK SOURCE is FRO */
   if (cecClockSource == TMDL_HDMICEC_CLOCK_FRO) {



   	   /* cf PR1795 set desired frequency to 12 Mhz*/

	   tmdlHdmiCecSetRegister(instance, 0xF3, 0xC0);

	   RETIF(errCode != TM_OK, errCode)

	   tmdlHdmiCecSetRegister(instance, 0xF4, 0xD4);

	   RETIF(errCode != TM_OK, errCode)

       /* set calibration in automatic mode */
       errCode = getCecHwRegisters(pDis, E_REG_CEC_DES_FREQ2,I2c_ReadBuffer,1);
       RETIF(errCode != TM_OK, errCode)
       I2c_ReadBuffer[0] &= CEC_AUTOMATIC_CALIBRATION_MSK;
       errCode = setCecHwRegister(pDis, E_REG_CEC_DES_FREQ2, I2c_ReadBuffer[0]);
       RETIF(errCode != TM_OK, errCode)


       /* select FRO clock mode, osc_freq shall be also set to one */
       I2c_ReadBuffer[0] = CEC_SELECT_FRO_CLOCK_SOURCE;
       errCode = setCecHwRegister(pDis, E_REG_CEC_CLK, I2c_ReadBuffer[0]);
       RETIF(errCode != TM_OK, errCode)


       /* Enable cec_clk AND FRO */
       errCode = getCecHwRegisters(pDis, E_REG_ENAMODS,I2c_ReadBuffer,1);	
       RETIF(errCode != TM_OK, errCode)
       I2c_ReadBuffer[0] |= CEC_ENABLE_CEC_CLK_MSK;
       I2c_ReadBuffer[0] &= CEC_ENABLE_FRO_MSK;
       errCode = setCecHwRegister(pDis, E_REG_ENAMODS, I2c_ReadBuffer[0]);
       RETIF(errCode != TM_OK, errCode)

       /* Enable calibration */
       I2c_ReadBuffer[0] = CEC_ENABLE_CALIBRATION;
       errCode = setCecHwRegister(pDis, E_REG_CEC_CAL_XOSC_CTRL1, I2c_ReadBuffer[0]);
       RETIF(errCode != TM_OK, errCode)

   } /* CLOCK SOURCE is FRO */

#endif  /*  TMFL_TDA9989 */

    return errCode;
}


//==========================================================================
//==========================================================================
tmErrorCode_t tmdlHdmiCecDisableCalibration(tmInstance_t instance)
{
    tmErrorCode_t errCode = TM_OK;

#ifdef TMFL_TDA9989

    unsigned char                   I2c_ReadBuffer[1];
    tmdlHdmiCecDriverConfigTable_t *pDis;

    pDis = &gtmdlHdmiCecDriverConfigTable[instance];

   /* check if instance number is in range */
   RETIF((instance < 0) || (instance >= MAX_UNITS), TMDL_ERR_DLHDMICEC_BAD_INSTANCE)

   /* Disable calibration */
   I2c_ReadBuffer[0] = CEC_DISABLE_CALIBRATION;
   errCode = setCecHwRegister(pDis, E_REG_CEC_CAL_XOSC_CTRL1, I2c_ReadBuffer[0]);
   RETIF(errCode != TM_OK, errCode)

#endif  /*  TMFL_TDA9989 */

    return errCode;
}

/*============================================================================*/
/*                     END OF FILE                                            */
/*============================================================================*/
