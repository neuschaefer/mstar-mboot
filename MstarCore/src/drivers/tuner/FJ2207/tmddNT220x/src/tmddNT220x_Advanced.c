/*-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2008 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of Philips Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of Philips
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than Philips Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmddNT220x_Alt.c
//
// DESCRIPTION:  NT220x standard APIs
//
// NOTES:        
//-----------------------------------------------------------------------------
*/

#include "../../inc/tmNxTypes.h"
#include "../../inc/tmCompId.h"
#include "../../inc/tmFrontEnd.h"
#include "../../inc/tmbslFrontEndTypes.h"

#include "../inc/tmddNT220x.h"
#include "tmddNT220xlocal.h"

#include "tmddNT220xInstance.h"

/*-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
*/

/*-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
*/

/*-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetTM_D:
//
// DESCRIPTION: Get the TM_D bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetTM_D
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // switch thermometer on
        pObj->I2CMap.uBx04.bF.TM_ON = 1;

        // write byte 0x04
        err = ddNT220xWrite(pObj, 0x04, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // read byte 0x03
            err = ddNT220xRead(pObj, 0x03, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx03.bF.TM_D;

            // switch thermometer off
            pObj->I2CMap.uBx04.bF.TM_ON = 0;

            // write byte 0x04
            err = ddNT220xWrite(pObj, 0x04, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetTM_ON:
//
// DESCRIPTION: Set the TM_ON bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetTM_ON
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx04.bF.TM_ON = uValue;

        // write byte 0x04
        err = ddNT220xWrite(pObj, 0x04, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetTM_ON:
//
// DESCRIPTION: Get the TM_ON bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetTM_ON
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x04
        err = ddNT220xRead(pObj, 0x04, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx04.bF.TM_ON;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPOR:
//
// DESCRIPTION: Get the POR bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPOR
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x05
        err = ddNT220xRead(pObj, 0x05, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx05.bF.POR ;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RSSI_End:
//
// DESCRIPTION: Get the MSM_RSSI_End bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RSSI_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue   //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x08
        err = ddNT220xRead(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_RSSI_End;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_LOCalc_End:
//
// DESCRIPTION: Get the MSM_LOCalc_End bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_LOCalc_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x08
        err = ddNT220xRead(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_LOCalc_End;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RFCal_End:
//
// DESCRIPTION: Get the MSM_RFCal_End bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RFCal_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x08
        err = ddNT220xRead(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_RFCal_End;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_IRCAL_End:
//
// DESCRIPTION: Get the MSM_IRCAL_End bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_IRCAL_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x08
        err = ddNT220xRead(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_IRCAL_End;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RCCal_End:
//
// DESCRIPTION: Get the MSM_RCCal_End bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RCCal_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x08
        err = ddNT220xRead(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_RCCal_End;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIRQ_Enable:
//
// DESCRIPTION: Set the IRQ_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIRQ_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.IRQ_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIRQ_Enable:
//
// DESCRIPTION: Get the IRQ_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIRQ_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.IRQ_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetXtalCal_Enable:
//
// DESCRIPTION: Set the XtalCal_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetXtalCal_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.XtalCal_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetXtalCal_Enable:
//
// DESCRIPTION: Get the XtalCal_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetXtalCal_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.XtalCal_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RSSI_Enable:
//
// DESCRIPTION: Set the MSM_RSSI_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RSSI_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.MSM_RSSI_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RSSI_Enable:
//
// DESCRIPTION: Get the MSM_RSSI_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RSSI_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_RSSI_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_LOCalc_Enable:
//
// DESCRIPTION: Set the MSM_LOCalc_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_LOCalc_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.MSM_LOCalc_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_LOCalc_Enable:
//
// DESCRIPTION: Get the MSM_LOCalc_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_LOCalc_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_LOCalc_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RFCAL_Enable:
//
// DESCRIPTION: Set the MSM_RFCAL_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RFCAL_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.MSM_RFCAL_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RFCAL_Enable:
//
// DESCRIPTION: Get the MSM_RFCAL_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RFCAL_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_RFCAL_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_IRCAL_Enable:
//
// DESCRIPTION: Set the MSM_IRCAL_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_IRCAL_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.MSM_IRCAL_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_IRCAL_Enable:
//
// DESCRIPTION: Get the MSM_IRCAL_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_IRCAL_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_IRCAL_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RCCal_Enable:
//
// DESCRIPTION: Set the MSM_RCCal_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RCCal_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx09.bF.MSM_RCCal_Enable = uValue;

        // write byte 0x09
        err = ddNT220xWrite(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RCCal_Enable:
//
// DESCRIPTION: Get the MSM_RCCal_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RCCal_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x09
        err = ddNT220xRead(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_RCCal_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetXtalCal_Clear:
//
// DESCRIPTION: Set the XtalCal_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetXtalCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0A.bF.XtalCal_Clear = uValue;

        // write byte 0x0A
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetXtalCal_Clear:
//
// DESCRIPTION: Get the XtalCal_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetXtalCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0A
        err = ddNT220xRead(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.XtalCal_Clear;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RSSI_Clear:
//
// DESCRIPTION: Set the MSM_RSSI_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RSSI_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0A.bF.MSM_RSSI_Clear = uValue;

        // write byte 0x0A
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RSSI_Clear:
//
// DESCRIPTION: Get the MSM_RSSI_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RSSI_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0A
        err = ddNT220xRead(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_RSSI_Clear;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_LOCalc_Clear:
//
// DESCRIPTION: Set the MSM_LOCalc_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_LOCalc_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0A.bF.MSM_LOCalc_Clear = uValue;

        // write byte 0x0A
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_LOCalc_Clear:
//
// DESCRIPTION: Get the MSM_LOCalc_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_LOCalc_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0A
        err = ddNT220xRead(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_LOCalc_Clear;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RFCal_Clear:
//
// DESCRIPTION: Set the MSM_RFCal_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RFCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0A.bF.MSM_RFCal_Clear = uValue;

        // write byte 0x0A
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RFCal_Clear:
//
// DESCRIPTION: Get the MSM_RFCal_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RFCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0A
        err = ddNT220xRead(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_RFCal_Clear;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_IRCAL_Clear:
//
// DESCRIPTION: Set the MSM_IRCAL_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_IRCAL_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0A.bF.MSM_IRCAL_Clear = uValue;

        // write byte 0x0A
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_IRCAL_Clear:
//
// DESCRIPTION: Get the MSM_IRCAL_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_IRCAL_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0A
        err = ddNT220xRead(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_IRCAL_Clear;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RCCal_Clear:
//
// DESCRIPTION: Set the MSM_RCCal_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RCCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0A.bF.MSM_RCCal_Clear = uValue;

        // write byte 0x0A
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RCCal_Clear:
//
// DESCRIPTION: Get the MSM_RCCal_Clear bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RCCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0A
        err = ddNT220xRead(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_RCCal_Clear;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIRQ_Set:
//
// DESCRIPTION: Set the IRQ_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIRQ_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.IRQ_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIRQ_Set:
//
// DESCRIPTION: Get the IRQ_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIRQ_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.IRQ_Set;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetXtalCal_Set:
//
// DESCRIPTION: Set the XtalCal_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetXtalCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.XtalCal_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetXtalCal_Set:
//
// DESCRIPTION: Get the XtalCal_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetXtalCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.XtalCal_Set;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RSSI_Set:
//
// DESCRIPTION: Set the MSM_RSSI_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RSSI_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.MSM_RSSI_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RSSI_Set:
//
// DESCRIPTION: Get the MSM_RSSI_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RSSI_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_RSSI_Set;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_LOCalc_Set:
//
// DESCRIPTION: Set the MSM_LOCalc_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_LOCalc_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.MSM_LOCalc_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_LOCalc_Set:
//
// DESCRIPTION: Get the MSM_LOCalc_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_LOCalc_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        // get value
        *puValue = pObj->I2CMap.uBx0B.bF.MSM_LOCalc_Set;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RFCal_Set:
//
// DESCRIPTION: Set the MSM_RFCal_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RFCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.MSM_RFCal_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RFCal_Set:
//
// DESCRIPTION: Get the MSM_RFCal_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RFCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_RFCal_Set;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_IRCAL_Set:
//
// DESCRIPTION: Set the MSM_IRCAL_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_IRCAL_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.MSM_IRCAL_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_IRCAL_Set:
//
// DESCRIPTION: Get the MSM_IRCAL_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_IRCAL_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_IRCAL_Set;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetMSM_RCCal_Set:
//
// DESCRIPTION: Set the MSM_RCCal_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetMSM_RCCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8            uValue //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0B.bF.MSM_RCCal_Set = uValue;

        // write byte 0x0B
        err = ddNT220xWrite(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetMSM_RCCal_Set:
//
// DESCRIPTION: Get the MSM_RCCal_Set bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetMSM_RCCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0B
        err = ddNT220xRead(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_RCCal_Set;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetLT_Enable:
//
// DESCRIPTION: Set the LT_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetLT_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0C.bF.LT_Enable = uValue;

        // write byte 0x0C
        err = ddNT220xWrite(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetLT_Enable:
//
// DESCRIPTION: Get the LT_Enable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetLT_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0C
        err = ddNT220xRead(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0C.bF.LT_Enable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC1_6_15dB:
//
// DESCRIPTION: Set the AGC1_6_15dB bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC1_6_15dB
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0C.bF.AGC1_6_15dB = uValue;

        // write byte 0x0C
        err = ddNT220xWrite(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC1_6_15dB:
//
// DESCRIPTION: Get the AGC1_6_15dB bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC1_6_15dB
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0C
        err = ddNT220xRead(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0C.bF.AGC1_6_15dB;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGCs_Up_Step_assym:
//
// DESCRIPTION: Set the AGCs_Up_Step_assym bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGCs_Up_Step_assym
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0E.bF.AGCs_Up_Step_assym = uValue;

        // write byte 0x0E
        err = ddNT220xWrite(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGCs_Up_Step_assym:
//
// DESCRIPTION: Get the AGCs_Up_Step_assym bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGCs_Up_Step_assym
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0E
        err = ddNT220xRead(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0E.bF.AGCs_Up_Step_assym;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPulse_Shaper_Disable:
//
// DESCRIPTION: Set the Pulse_Shaper_Disable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPulse_Shaper_Disable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0E.bF.Pulse_Shaper_Disable = uValue;

        // write byte 0x0E
        err = ddNT220xWrite(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPulse_Shaper_Disable:
//
// DESCRIPTION: Get the Pulse_Shaper_Disable bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPulse_Shaper_Disable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0E
        err = ddNT220xRead(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0E.bF.Pulse_Shaper_Disable;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFAGC_Low_BW:
//
// DESCRIPTION: Set the RFAGC_Low_BW bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFAGC_Low_BW
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx0F.bF.RFAGC_Low_BW = uValue;

        // write byte 0x0F
        err = ddNT220xWrite(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFAGC_Low_BW:
//
// DESCRIPTION: Get the RFAGC_Low_BW bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFAGC_Low_BW
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x0F
        err = ddNT220xRead(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0F.bF.RFAGC_Low_BW;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGCs_Do_Step_assym:
//
// DESCRIPTION: Set the AGCs_Do_Step_assym bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGCs_Do_Step_assym
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx11.bF.AGCs_Do_Step_assym = uValue;

        // write byte 0x11
        err = ddNT220xWrite(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGCs_Do_Step_assym:
//
// DESCRIPTION: Get the AGCs_Do_Step_assym bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGCs_Do_Step_assym
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x11
        err = ddNT220xRead(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx11.bF.AGCs_Do_Step_assym;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetI2C_Clock_Mode:
//
// DESCRIPTION: Set the I2C_Clock_Mode bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetI2C_Clock_Mode
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx14.bF.I2C_Clock_Mode = uValue;

        // write byte 0x14
        err = ddNT220xWrite(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetI2C_Clock_Mode:
//
// DESCRIPTION: Get the I2C_Clock_Mode bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetI2C_Clock_Mode
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x14
        err = ddNT220xRead(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx14.bF.I2C_Clock_Mode;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetXtalOsc_AnaReg_En:
//
// DESCRIPTION: Set the XtalOsc_AnaReg_En bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetXtalOsc_AnaReg_En
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx14.bF.XtalOsc_AnaReg_En = uValue;

        // write byte 0x14
        err = ddNT220xWrite(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetXtalOsc_AnaReg_En:
//
// DESCRIPTION: Get the XtalOsc_AnaReg_En bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetXtalOsc_AnaReg_En
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x14
        err = ddNT220xRead(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx14.bF.XtalOsc_AnaReg_En;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetXTout:
//
// DESCRIPTION: Set the XTout bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetXTout
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx14.bF.XTout = uValue;

        // write byte 0x14
        err = ddNT220xWrite(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetXTout:
//
// DESCRIPTION: Get the XTout bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetXTout
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x14
        err = ddNT220xRead(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx14.bF.XTout;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRSSI_Meas:
//
// DESCRIPTION: Set the RSSI_Meas bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRSSI_Meas
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.RSSI_Meas = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRSSI_Meas:
//
// DESCRIPTION: Get the RSSI_Meas bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRSSI_Meas
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.RSSI_Meas;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRF_CAL_AV:
//
// DESCRIPTION: Set the RF_CAL_AV bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRF_CAL_AV
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.RF_CAL_AV = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRF_CAL_AV:
//
// DESCRIPTION: Get the RF_CAL_AV bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRF_CAL_AV
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.RF_CAL_AV;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRF_CAL:
//
// DESCRIPTION: Set the RF_CAL bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRF_CAL
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.RF_CAL = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRF_CAL:
//
// DESCRIPTION: Get the RF_CAL bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRF_CAL
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue      //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.RF_CAL;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_CAL_Loop:
//
// DESCRIPTION: Set the IR_CAL_Loop bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_CAL_Loop
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.IR_CAL_Loop = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_CAL_Loop:
//
// DESCRIPTION: Get the IR_CAL_Loop bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_CAL_Loop
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;
    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.IR_CAL_Loop;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_Cal_Image:
//
// DESCRIPTION: Set the IR_Cal_Image bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_Cal_Image
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.IR_Cal_Image = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_Cal_Image:
//
// DESCRIPTION: Get the IR_Cal_Image bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_Cal_Image
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.IR_Cal_Image;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_CAL_Wanted:
//
// DESCRIPTION: Set the IR_CAL_Wanted bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_CAL_Wanted
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.IR_CAL_Wanted = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_CAL_Wanted:
//
// DESCRIPTION: Get the IR_CAL_Wanted bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_CAL_Wanted
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.IR_CAL_Wanted;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRC_Cal:
//
// DESCRIPTION: Set the RC_Cal bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRC_Cal
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.RC_Cal = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRC_Cal:
//
// DESCRIPTION: Get the RC_Cal bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRC_Cal
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.RC_Cal;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetCalc_PLL:
//
// DESCRIPTION: Set the Calc_PLL bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetCalc_PLL
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx19.bF.Calc_PLL = uValue;

        // read byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetCalc_PLL:
//
// DESCRIPTION: Get the Calc_PLL bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetCalc_PLL
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x19
        err = ddNT220xRead(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx19.bF.Calc_PLL;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPSM_AGC1:
//
// DESCRIPTION: Set the PSM_AGC1 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPSM_AGC1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1B.bF.PSM_AGC1 = uValue;

        // read byte 0x1B
        err = ddNT220xWrite(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPSM_AGC1:
//
// DESCRIPTION: Get the PSM_AGC1 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPSM_AGC1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1B
        err = ddNT220xRead(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.PSM_AGC1;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPSMRFpoly:
//
// DESCRIPTION: Set the PSMRFpoly bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPSMRFpoly
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1B.bF.PSMRFpoly = uValue;

        // read byte 0x1B
        err = ddNT220xWrite(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPSMRFpoly:
//
// DESCRIPTION: Get the PSMRFpoly bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPSMRFpoly
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1B
        err = ddNT220xRead(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        // get value
        *puValue = pObj->I2CMap.uBx1B.bF.PSMRFpoly;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPSM_Mixer:
//
// DESCRIPTION: Set the PSM_Mixer bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPSM_Mixer
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1B.bF.PSM_Mixer = uValue;

        // read byte 0x1B
        err = ddNT220xWrite(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPSM_Mixer:
//
// DESCRIPTION: Get the PSM_Mixer bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPSM_Mixer
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1B
        err = ddNT220xRead(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.PSM_Mixer;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPSM_Ifpoly:
//
// DESCRIPTION: Set the PSM_Ifpoly bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPSM_Ifpoly
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1B.bF.PSM_Ifpoly = uValue;

        // read byte 0x1B
        err = ddNT220xWrite(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPSM_Ifpoly:
//
// DESCRIPTION: Get the PSM_Ifpoly bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPSM_Ifpoly
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1B
        err = ddNT220xRead(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.PSM_Ifpoly;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPSM_Lodriver:
//
// DESCRIPTION: Set the PSM_Lodriver bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPSM_Lodriver
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1B.bF.PSM_Lodriver = uValue;

        // read byte 0x1B
        err = ddNT220xWrite(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPSM_Lodriver:
//
// DESCRIPTION: Get the PSM_Lodriver bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPSM_Lodriver
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1B
        err = ddNT220xRead(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.PSM_Lodriver;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetDCC_Bypass:
//
// DESCRIPTION: Set the DCC_Bypass bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetDCC_Bypass
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1C.bF.DCC_Bypass = uValue;

        // read byte 0x1C
        err = ddNT220xWrite(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDCC_Bypass:
//
// DESCRIPTION: Get the DCC_Bypass bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDCC_Bypass
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1C
        err = ddNT220xRead(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1C.bF.DCC_Bypass;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetDCC_Slow:
//
// DESCRIPTION: Set the DCC_Slow bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetDCC_Slow
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1C.bF.DCC_Slow = uValue;

        // read byte 0x1C
        err = ddNT220xWrite(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDCC_Slow:
//
// DESCRIPTION: Get the DCC_Slow bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDCC_Slow
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1C
        err = ddNT220xRead(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1C.bF.DCC_Slow;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetDCC_psm:
//
// DESCRIPTION: Set the DCC_psm bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetDCC_psm
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1C.bF.DCC_psm = uValue;

        // read byte 0x1C
        err = ddNT220xWrite(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDCC_psm:
//
// DESCRIPTION: Get the DCC_psm bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDCC_psm
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1C
        err = ddNT220xRead(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1C.bF.DCC_psm;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetFmax_Lo:
//
// DESCRIPTION: Set the Fmax_Lo bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetFmax_Lo
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1D.bF.Fmax_Lo = uValue;

        // read byte 0x1D
        err = ddNT220xWrite(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetFmax_Lo:
//
// DESCRIPTION: Get the Fmax_Lo bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetFmax_Lo
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1D
        err = ddNT220xRead(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1D.bF.Fmax_Lo;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_GStep:
//
// DESCRIPTION: Set the IR_GStep bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_GStep
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1E.bF.IR_GStep = uValue - 40;

        // read byte 0x1E
        err = ddNT220xWrite(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_GStep:
//
// DESCRIPTION: Get the IR_GStep bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_GStep
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1E
        err = ddNT220xRead(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1E.bF.IR_GStep + 40;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_FreqLow_Sel:
//
// DESCRIPTION: Set the IR_FreqLow_Sel bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_FreqLow_Sel
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1F.bF.IR_FreqLow_Sel = uValue;

        // read byte 0x1F
        err = ddNT220xWrite(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_FreqLow_Sel:
//
// DESCRIPTION: Get the IR_FreqLow_Sel bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_FreqLow_Sel
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1F
        err = ddNT220xRead(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1F.bF.IR_FreqLow_Sel;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_FreqLow:
//
// DESCRIPTION: Set the IR_FreqLow bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_FreqLow
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1F.bF.IR_FreqLow = uValue;

        // read byte 0x1F
        err = ddNT220xWrite(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_FreqLow:
//
// DESCRIPTION: Get the IR_FreqLow bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_FreqLow
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1F
        err = ddNT220xRead(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1F.bF.IR_FreqLow;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_FreqMid:
//
// DESCRIPTION: Set the IR_FreqMid bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_FreqMid
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx20.bF.IR_FreqMid = uValue;

        // read byte 0x20
        err = ddNT220xWrite(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_FreqMid:
//
// DESCRIPTION: Get the IR_FreqMid bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_FreqMid
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x20
        err = ddNT220xRead(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx20.bF.IR_FreqMid;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetCoarse_IR_FreqHigh:
//
// DESCRIPTION: Set the Coarse_IR_FreqHigh bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetCoarse_IR_FreqHigh
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx21.bF.Coarse_IR_FreqHigh = uValue;

        // write byte 0x21
        err = ddNT220xWrite(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetCoarse_IR_FreqHigh:
//
// DESCRIPTION: Get the Coarse_IR_FreqHigh bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetCoarse_IR_FreqHigh
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x21
        err = ddNT220xRead(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx21.bF.Coarse_IR_FreqHigh;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_FreqHigh:
//
// DESCRIPTION: Set the IR_FreqHigh bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_FreqHigh
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx21.bF.IR_FreqHigh = uValue;

        // read byte 0x21
        err = ddNT220xWrite(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_FreqHigh:
//
// DESCRIPTION: Get the IR_FreqHigh bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_FreqHigh
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x21
        err = ddNT220xRead(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx21.bF.IR_FreqHigh;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPD_Vsync_Mgt:
//
// DESCRIPTION: Set the PD_Vsync_Mgt bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPD_Vsync_Mgt
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx22.bF.PD_Vsync_Mgt = uValue;

        // write byte 0x22
        err = ddNT220xWrite(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPD_Vsync_Mgt:
//
// DESCRIPTION: Get the PD_Vsync_Mgt bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPD_Vsync_Mgt
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x22
        err = ddNT220xRead(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx22.bF.PD_Vsync_Mgt;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetPD_Ovld:
//
// DESCRIPTION: Set the PD_Ovld bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetPD_Ovld
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx22.bF.PD_Ovld = uValue;

        // write byte 0x22
        err = ddNT220xWrite(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetPD_Ovld:
//
// DESCRIPTION: Get the PD_Ovld bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetPD_Ovld
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x22
        err = ddNT220xRead(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx22.bF.PD_Ovld;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC_Ovld_Timer:
//
// DESCRIPTION: Set the AGC_Ovld_Timer bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC_Ovld_Timer
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx22.bF.AGC_Ovld_Timer = uValue;

        // write byte 0x22
        err = ddNT220xWrite(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC_Ovld_Timer:
//
// DESCRIPTION: Get the AGC_Ovld_Timer bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC_Ovld_Timer
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x22
        err = ddNT220xRead(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx22.bF.AGC_Ovld_Timer;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_Mixer_loop_off:
//
// DESCRIPTION: Set the IR_Mixer_loop_off bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_Mixer_loop_off
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx23.bF.IR_Mixer_loop_off = uValue;

        // read byte 0x23
        err = ddNT220xWrite(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_Mixer_loop_off:
//
// DESCRIPTION: Get the IR_Mixer_loop_off bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_Mixer_loop_off
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x23
        err = ddNT220xRead(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx23.bF.IR_Mixer_loop_off;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIR_Mixer_Do_step:
//
// DESCRIPTION: Set the IR_Mixer_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIR_Mixer_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx23.bF.IR_Mixer_Do_step = uValue;

        // read byte 0x23
        err = ddNT220xWrite(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIR_Mixer_Do_step:
//
// DESCRIPTION: Get the IR_Mixer_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIR_Mixer_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x23
        err = ddNT220xRead(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx23.bF.IR_Mixer_Do_step;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC1_loop_off:
//
// DESCRIPTION: Set the AGC1_loop_off bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC1_loop_off
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx24.bF.AGC1_loop_off = uValue;

        // read byte 0x24
        err = ddNT220xWrite(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC1_loop_off:
//
// DESCRIPTION: Get the AGC1_loop_off bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC1_loop_off
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x24
        err = ddNT220xRead(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.AGC1_loop_off;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC1_Do_step:
//
// DESCRIPTION: Set the AGC1_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC1_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx24.bF.AGC1_Do_step = uValue;

        // read byte 0x24
        err = ddNT220xWrite(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC1_Do_step:
//
// DESCRIPTION: Get the AGC1_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC1_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x24
        err = ddNT220xRead(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.AGC1_Do_step;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetForce_AGC1_gain:
//
// DESCRIPTION: Set the Force_AGC1_gain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetForce_AGC1_gain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx24.bF.Force_AGC1_gain = uValue;

        // read byte 0x24
        err = ddNT220xWrite(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetForce_AGC1_gain:
//
// DESCRIPTION: Get the Force_AGC1_gain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetForce_AGC1_gain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x24
        err = ddNT220xRead(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.Force_AGC1_gain;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC1_Gain:
//
// DESCRIPTION: Set the AGC1_Gain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC1_Gain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx24.bF.AGC1_Gain = uValue;

        // read byte 0x24
        err = ddNT220xWrite(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC1_Gain:
//
// DESCRIPTION: Get the AGC1_Gain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC1_Gain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x24
        err = ddNT220xRead(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.AGC1_Gain;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq0:
//
// DESCRIPTION: Set the RFCAL_Freq0 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq0
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx26.bF.RFCAL_Freq0 = uValue;

        // read byte 0x26
        err = ddNT220xWrite(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq0:
//
// DESCRIPTION: Get the RFCAL_Freq0 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq0
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x26
        err = ddNT220xRead(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx26.bF.RFCAL_Freq0;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq1:
//
// DESCRIPTION: Set the RFCAL_Freq1 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx26.bF.RFCAL_Freq1 = uValue;

        // read byte 0x26
        err = ddNT220xWrite(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq1:
//
// DESCRIPTION: Get the RFCAL_Freq1 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x26
        err = ddNT220xRead(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx26.bF.RFCAL_Freq1;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq2:
//
// DESCRIPTION: Set the RFCAL_Freq2 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx27.bF.RFCAL_Freq2 = uValue;

        // read byte 0x27
        err = ddNT220xWrite(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq2:
//
// DESCRIPTION: Get the RFCAL_Freq2 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x27
        err = ddNT220xRead(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Freq2;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq3:
//
// DESCRIPTION: Set the RFCAL_Freq3 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq3
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx27.bF.RFCAL_Freq3 = uValue;

        // read byte 0x27
        err = ddNT220xWrite(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq3:
//
// DESCRIPTION: Get the RFCAL_Freq3 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq3
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x27
        err = ddNT220xRead(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Freq3;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq4:
//
// DESCRIPTION: Set the RFCAL_Freq4 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx28.bF.RFCAL_Freq4 = uValue;

        // read byte 0x28
        err = ddNT220xWrite(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq4:
//
// DESCRIPTION: Get the RFCAL_Freq4 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x28
        err = ddNT220xRead(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Freq4;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq5:
//
// DESCRIPTION: Set the RFCAL_Freq5 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue   //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx28.bF.RFCAL_Freq5 = uValue;

        // read byte 0x28
        err = ddNT220xWrite(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq5:
//
// DESCRIPTION: Get the RFCAL_Freq5 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x28
        err = ddNT220xRead(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Freq5;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq6:
//
// DESCRIPTION: Set the RFCAL_Freq6 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq6
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx29.bF.RFCAL_Freq6 = uValue;

        // read byte 0x29
        err = ddNT220xWrite(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq6:
//
// DESCRIPTION: Get the RFCAL_Freq6 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq6
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x29
        err = ddNT220xRead(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Freq6;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq7:
//
// DESCRIPTION: Set the RFCAL_Freq7 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq7
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx29.bF.RFCAL_Freq7 = uValue;

        // read byte 0x29
        err = ddNT220xWrite(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq7:
//
// DESCRIPTION: Get the RFCAL_Freq7 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq7
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x29
        err = ddNT220xRead(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Freq7;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq8:
//
// DESCRIPTION: Set the RFCAL_Freq8 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq8
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2A.bF.RFCAL_Freq8 = uValue;

        // read byte 0x2A
        err = ddNT220xWrite(pObj, 0x2A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq8:
//
// DESCRIPTION: Get the RFCAL_Freq8 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq8
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2A
        err = ddNT220xRead(pObj, 0x2A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2A.bF.RFCAL_Freq8;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq9:
//
// DESCRIPTION: Set the RFCAL_Freq9 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq9
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2A.bF.RFCAL_Freq9 = uValue;

        // read byte 0x2A
        err = ddNT220xWrite(pObj, 0x2A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq9:
//
// DESCRIPTION: Get the RFCAL_Freq9 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq9
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2A
        err = ddNT220xRead(pObj, 0x2A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2A.bF.RFCAL_Freq9;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq10:
//
// DESCRIPTION: Set the RFCAL_Freq10 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq10
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2B.bF.RFCAL_Freq10 = uValue;

        // read byte 0x2B
        err = ddNT220xWrite(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq10:
//
// DESCRIPTION: Get the ? bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq10
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2B
        err = ddNT220xRead(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2B.bF.RFCAL_Freq10;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Freq11:
//
// DESCRIPTION: Set the RFCAL_Freq11 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Freq11
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2B.bF.RFCAL_Freq11 = uValue;

        // read byte 0x2B
        err = ddNT220xWrite(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Freq11:
//
// DESCRIPTION: Get the RFCAL_Freq11 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Freq11
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2B
        err = ddNT220xRead(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2B.bF.RFCAL_Freq11;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset0:
//
// DESCRIPTION: Set the RFCAL_Offset0 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset0
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[0].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx26.bF.RFCAL_Offset_Cprog0 = uValue;

            // read byte 0x26
            err = ddNT220xWrite(pObj, 0x26, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset0:
//
// DESCRIPTION: Get the RFCAL_Offset0 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset0
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[0].CprogOffset;
        }
        else
        {
            // read byte 0x26
            err = ddNT220xRead(pObj, 0x26, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx26.bF.RFCAL_Offset_Cprog0;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset1:
//
// DESCRIPTION: Set the RFCAL_Offset1 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[1].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx26.bF.RFCAL_Offset_Cprog1 = uValue;

            // read byte 0x26
            err = ddNT220xWrite(pObj, 0x26, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset1:
//
// DESCRIPTION: Get the RFCAL_Offset1 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[1].CprogOffset;
        }
        else
        {
            // read byte 0x26
            err = ddNT220xRead(pObj, 0x26, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx26.bF.RFCAL_Offset_Cprog1;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset2:
//
// DESCRIPTION: Set the RFCAL_Offset2 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[2].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog2 = uValue;

            // read byte 0x27
            err = ddNT220xWrite(pObj, 0x27, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset2:
//
// DESCRIPTION: Get the RFCAL_Offset2 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[2].CprogOffset;
        }
        else
        {
            // read byte 0x27
            err = ddNT220xRead(pObj, 0x27, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog2;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset3:
//
// DESCRIPTION: Set the RFCAL_Offset3 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset3
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[3].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog3 = uValue;

            // read byte 0x27
            err = ddNT220xWrite(pObj, 0x27, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset3:
//
// DESCRIPTION: Get the RFCAL_Offset3 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset3
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[3].CprogOffset;
        }
        else
        {
            // read byte 0x27
            err = ddNT220xRead(pObj, 0x27, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog3;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset4:
//
// DESCRIPTION: Set the RFCAL_Offset4 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[4].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog4 = uValue;

            // read byte 0x28
            err = ddNT220xWrite(pObj, 0x28, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset4:
//
// DESCRIPTION: Get the RFCAL_Offset4 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[4].CprogOffset;
        }
        else
        {
            // read byte 0x28
            err = ddNT220xRead(pObj, 0x28, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog4;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset5:
//
// DESCRIPTION: Set the RFCAL_Offset5 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue   //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[5].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog5 = uValue;

            // read byte 0x28
            err = ddNT220xWrite(pObj, 0x28, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset5:
//
// DESCRIPTION: Get the RFCAL_Offset5 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[5].CprogOffset;
        }
        else
        {
            // read byte 0x28
            err = ddNT220xRead(pObj, 0x28, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog5;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset6:
//
// DESCRIPTION: Set the RFCAL_Offset6 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset6
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[6].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog6 = uValue;

            // read byte 0x29
            err = ddNT220xWrite(pObj, 0x29, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset6:
//
// DESCRIPTION: Get the RFCAL_Offset6 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset6
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[6].CprogOffset;
        }
        else
        {
            // read byte 0x29
            err = ddNT220xRead(pObj, 0x29, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog6;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset7:
//
// DESCRIPTION: Set the RFCAL_Offset7 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset7
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[7].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog7 = uValue;

            // read byte 0x29
            err = ddNT220xWrite(pObj, 0x29, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset7:
//
// DESCRIPTION: Get the RFCAL_Offset7 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset7
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[7].CprogOffset;
        }
        else
        {
            // read byte 0x29
            err = ddNT220xRead(pObj, 0x29, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog7;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset8:
//
// DESCRIPTION: Set the RFCAL_Offset8 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset8
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[8].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx2A.bF.RFCAL_Offset_Cprog8 = uValue;

            // read byte 0x2A
            err = ddNT220xWrite(pObj, 0x2A, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset8:
//
// DESCRIPTION: Get the RFCAL_Offset8 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset8
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[8].CprogOffset;
        }
        else
        {
            // read byte 0x2A
            err = ddNT220xRead(pObj, 0x2A, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx2A.bF.RFCAL_Offset_Cprog8;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset9:
//
// DESCRIPTION: Set the RFCAL_Offset9 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset9
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[9].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx2A.bF.RFCAL_Offset_Cprog9 = uValue;

            // read byte 0x2A
            err = ddNT220xWrite(pObj, 0x2A, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset9:
//
// DESCRIPTION: Get the RFCAL_Offset9 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset9
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[9].CprogOffset;
        }
        else
        {
            // read byte 0x2A
            err = ddNT220xRead(pObj, 0x2A, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx2A.bF.RFCAL_Offset_Cprog9;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset10:
//
// DESCRIPTION: Set the RFCAL_Offset10 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset10
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[10].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx2B.bF.RFCAL_Offset_Cprog10 = uValue;

            // read byte 0x2B
            err = ddNT220xWrite(pObj, 0x2B, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset10:
//
// DESCRIPTION: Get the ? bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset10
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[10].CprogOffset;
        }
        else
        {
            // read byte 0x2B
            err = ddNT220xRead(pObj, 0x2B, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx2B.bF.RFCAL_Offset_Cprog10;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_Offset11:
//
// DESCRIPTION: Set the RFCAL_Offset11 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_Offset11
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            pObj->RFCAL_Prog[11].CprogOffset = uValue;
        }
        else
        {
            // set value
            pObj->I2CMap.uBx2B.bF.RFCAL_Offset_Cprog11 = uValue;

            // read byte 0x2B
            err = ddNT220xWrite(pObj, 0x2B, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_Offset11:
//
// DESCRIPTION: Get the RFCAL_Offset11 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_Offset11
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bRFCAL_SW_Algo_Enable)
        {
            *puValue = pObj->RFCAL_Prog[11].CprogOffset;
        }
        else
        {
            // read byte 0x2B
            err = ddNT220xRead(pObj, 0x2B, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                // get value
                *puValue = pObj->I2CMap.uBx2B.bF.RFCAL_Offset_Cprog11;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_SW_Algo_Enable:
//
// DESCRIPTION: Set the status of RFCAL Algo
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_SW_Algo_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->bRFCAL_SW_Algo_Enable = uValue;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_SW_Algo_Enable:
//
// DESCRIPTION: Get the status of RFCAL Algo
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_SW_Algo_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *puValue = (UInt8)pObj->bRFCAL_SW_Algo_Enable;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC2_loop_off:
//
// DESCRIPTION: Set the AGC2_loop_off bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC2_loop_off
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2C.bF.AGC2_loop_off = uValue;

        // read byte 0x2C
        err = ddNT220xWrite(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC2_loop_off:
//
// DESCRIPTION: Get the AGC2_loop_off bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC2_loop_off
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2C
        err = ddNT220xRead(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2C.bF.AGC2_loop_off;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetForce_AGC2_gain:
//
// DESCRIPTION: Set the Force_AGC2_gain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetForce_AGC2_gain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2C.bF.Force_AGC2_gain = uValue;

        // write byte 0x2C
        err = ddNT220xWrite(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetForce_AGC2_gain:
//
// DESCRIPTION: Get the Force_AGC2_gain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetForce_AGC2_gain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2C
        err = ddNT220xRead(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2C.bF.Force_AGC2_gain;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRF_Filter_Gv:
//
// DESCRIPTION: Set the RF_Filter_Gv bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRF_Filter_Gv
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2C.bF.RF_Filter_Gv = uValue;

        // read byte 0x2C
        err = ddNT220xWrite(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRF_Filter_Gv:
//
// DESCRIPTION: Get the RF_Filter_Gv bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRF_Filter_Gv
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2C
        err = ddNT220xRead(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2C.bF.RF_Filter_Gv;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetAGC2_Do_step:
//
// DESCRIPTION: Set the AGC2_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetAGC2_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2E.bF.AGC2_Do_step = uValue;

        // read byte 0x2E
        err = ddNT220xWrite(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC2_Do_step:
//
// DESCRIPTION: Get the AGC2_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC2_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2E
        err = ddNT220xRead(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2E.bF.AGC2_Do_step;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRF_BPF_Bypass:
//
// DESCRIPTION: Set the RF_BPF_Bypass bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRF_BPF_Bypass
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2F.bF.RF_BPF_Bypass = uValue;

        // read byte 0x2F
        err = ddNT220xWrite(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRF_BPF_Bypass:
//
// DESCRIPTION: Get the RF_BPF_Bypass bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRF_BPF_Bypass
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2F
        err = ddNT220xRead(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2F.bF.RF_BPF_Bypass;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRF_BPF:
//
// DESCRIPTION: Set the RF_BPF bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRF_BPF
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2F.bF.RF_BPF = uValue;

        // read byte 0x2F
        err = ddNT220xWrite(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRF_BPF:
//
// DESCRIPTION: Get the RF_BPF bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRF_BPF
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2F
        err = ddNT220xRead(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2F.bF.RF_BPF;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetUp_AGC5:
//
// DESCRIPTION: Get the Up_AGC5 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetUp_AGC5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Up_AGC5;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDo_AGC5:
//
// DESCRIPTION: Get the Do_AGC5 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDo_AGC5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Do_AGC5;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetUp_AGC4:
//
// DESCRIPTION: Get the Up_AGC4 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetUp_AGC4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Up_AGC4;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDo_AGC4:
//
// DESCRIPTION: Get the Do_AGC4 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDo_AGC4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Do_AGC4;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetUp_AGC2:
//
// DESCRIPTION: Get the Up_AGC2 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetUp_AGC2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Up_AGC2;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDo_AGC2:
//
// DESCRIPTION: Get the Do_AGC2 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDo_AGC2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Do_AGC2;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetUp_AGC1:
//
// DESCRIPTION: Get the Up_AGC1 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetUp_AGC1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Up_AGC1;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDo_AGC1:
//
// DESCRIPTION: Get the Do_AGC1 bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDo_AGC1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x31
        err = ddNT220xRead(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.Do_AGC1;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC2_Gain_Read:
//
// DESCRIPTION: Get the AGC2_Gain_Read bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC2_Gain_Read
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x32
        err = ddNT220xRead(pObj, 0x32, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx32.bF.AGC2_Gain_Read;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC1_Gain_Read:
//
// DESCRIPTION: Get the AGC1_Gain_Read bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC1_Gain_Read
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x32
        err = ddNT220xRead(pObj, 0x32, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx32.bF.AGC1_Gain_Read;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetTOP_AGC3_Read:
//
// DESCRIPTION: Get the TOP_AGC3_Read bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetTOP_AGC3_Read
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x33
        err = ddNT220xRead(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx33.bF.TOP_AGC3_Read;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC5_Gain_Read:
//
// DESCRIPTION: Get the AGC5_Gain_Read bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC5_Gain_Read
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x34
        err = ddNT220xRead(pObj, 0x34, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx34.bF.AGC5_Gain_Read;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetAGC4_Gain_Read:
//
// DESCRIPTION: Get the AGC4_Gain_Read bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetAGC4_Gain_Read
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x34
        err = ddNT220xRead(pObj, 0x34, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx34.bF.AGC4_Gain_Read;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRSSI:
//
// DESCRIPTION: Set the RSSI bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRSSI
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx35.RSSI = uValue;

        // write byte 0x35
        err = ddNT220xWrite(pObj, 0x35, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRSSI:
//
// DESCRIPTION: Get the RSSI bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRSSI
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x35
        err = ddNT220xRead(pObj, 0x35, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx35.RSSI;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRSSI_AV:
//
// DESCRIPTION: Set the RSSI_AV bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRSSI_AV
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx36.bF.RSSI_AV = uValue;

        // write byte 0x36
        err = ddNT220xWrite(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRSSI_AV:
//
// DESCRIPTION: Get the RSSI_AV bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRSSI_AV
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x36
        err = ddNT220xRead(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx36.bF.RSSI_AV;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRSSI_Cap_Reset_En:
//
// DESCRIPTION: Set the RSSI_Cap_Reset_En bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRSSI_Cap_Reset_En
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx36.bF.RSSI_Cap_Reset_En = uValue;

        // write byte 0x36
        err = ddNT220xWrite(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRSSI_Cap_Reset_En:
//
// DESCRIPTION: Get the RSSI_Cap_Reset_En bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRSSI_Cap_Reset_En
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x36
        err = ddNT220xRead(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx36.bF.RSSI_Cap_Reset_En;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRSSI_Cap_Val:
//
// DESCRIPTION: Set the RSSI_Cap_Val bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRSSI_Cap_Val
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx36.bF.RSSI_Cap_Val = uValue;

        // write byte 0x36
        err = ddNT220xWrite(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRSSI_Cap_Val:
//
// DESCRIPTION: Get the RSSI_Cap_Val bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRSSI_Cap_Val
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x36
        err = ddNT220xRead(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx36.bF.RSSI_Cap_Val;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRSSI_Dicho_not:
//
// DESCRIPTION: Set the RSSI_Dicho_not bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRSSI_Dicho_not
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx36.bF.RSSI_Dicho_not = uValue;

        // write byte 0x36
        err = ddNT220xWrite(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRSSI_Dicho_not:
//
// DESCRIPTION: Get the RSSI_Dicho_not bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRSSI_Dicho_not
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x36
        err = ddNT220xRead(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx36.bF.RSSI_Dicho_not;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetDDS_Polarity:
//
// DESCRIPTION: Set the DDS_Polarity bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetDDS_Polarity
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx37.bF.DDS_Polarity = uValue;

        // write byte 0x37
        err = ddNT220xWrite(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetDDS_Polarity:
//
// DESCRIPTION: Get the DDS_Polarity bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetDDS_Polarity
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x37
        err = ddNT220xRead(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.DDS_Polarity;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetRFCAL_DeltaGain:
//
// DESCRIPTION: Set the RFCAL_DeltaGain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetRFCAL_DeltaGain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx37.bF.RFCAL_DeltaGain = uValue;

        // read byte 0x37
        err = ddNT220xWrite(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetRFCAL_DeltaGain:
//
// DESCRIPTION: Get the RFCAL_DeltaGain bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetRFCAL_DeltaGain
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x37
        err = ddNT220xRead(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.RFCAL_DeltaGain;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetIRQ_Polarity:
//
// DESCRIPTION: Set the IRQ_Polarity bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetIRQ_Polarity
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx37.bF.IRQ_Polarity = uValue;

        // read byte 0x37
        err = ddNT220xWrite(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetIRQ_Polarity:
//
// DESCRIPTION: Get the IRQ_Polarity bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetIRQ_Polarity
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x37
        err = ddNT220xRead(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.IRQ_Polarity;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_0
//
// DESCRIPTION: Get the rfcal_log_0 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_0
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x38
        err = ddNT220xRead(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx38.bF.rfcal_log_0;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_1
//
// DESCRIPTION: Get the rfcal_log_1 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x39
        err = ddNT220xRead(pObj, 0x39, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx39.bF.rfcal_log_1;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_2
//
// DESCRIPTION: Get the rfcal_log_2 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x3A
        err = ddNT220xRead(pObj, 0x3A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3A.bF.rfcal_log_2;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_3
//
// DESCRIPTION: Get the rfcal_log_3 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_3
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x3B
        err = ddNT220xRead(pObj, 0x3B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3B.bF.rfcal_log_3;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_4
//
// DESCRIPTION: Get the rfcal_log_4 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x3C
        err = ddNT220xRead(pObj, 0x3C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3C.bF.rfcal_log_4;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_5
//
// DESCRIPTION: Get the rfcal_log_5 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x3D
        err = ddNT220xRead(pObj, 0x3D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3D.bF.rfcal_log_5;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_6
//
// DESCRIPTION: Get the rfcal_log_6 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_6
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x3E
        err = ddNT220xRead(pObj, 0x3E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3E.bF.rfcal_log_6;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_7
//
// DESCRIPTION: Get the rfcal_log_7 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_7
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x3F
        err = ddNT220xRead(pObj, 0x3F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3F.bF.rfcal_log_7;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_8
//
// DESCRIPTION: Get the rfcal_log_8 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_8
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x40
        err = ddNT220xRead(pObj, 0x40, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx40.bF.rfcal_log_8;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_9
//
// DESCRIPTION: Get the rfcal_log_9 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_9
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x41
        err = ddNT220xRead(pObj, 0x41, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx41.bF.rfcal_log_9;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_10
//
// DESCRIPTION: Get the rfcal_log_10 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_10
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x42
        err = ddNT220xRead(pObj, 0x42, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx42.bF.rfcal_log_10;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetrfcal_log_11
//
// DESCRIPTION: Get the rfcal_log_11 bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetrfcal_log_11
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_UNIT_NUMBER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x43
        err = ddNT220xRead(pObj, 0x43, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx43.bF.rfcal_log_11;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xLaunchRF_CAL
//
// DESCRIPTION: Launch the RF_CAL bit(s) status
//
// RETURN:      ddNT220x_ERR_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_UNIT_NUMBER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xLaunchRF_CAL
(
 tmUnitSelect_t  tUnit   //  I: Unit number
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set Calc_PLL & RF_CAL
        pObj->I2CMap.uBx19.MSM_byte_1 = 0x21;

        // write byte 0x19
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // trigger MSM_Launch
            pObj->I2CMap.uBx1A.bF.MSM_Launch = 1;

            // write byte 0x1A
            err = ddNT220xWrite(pObj, 0x1A, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

            // reset MSM_Launch (buffer only, no write)
            pObj->I2CMap.uBx1A.bF.MSM_Launch = 0;

            if(pObj->bIRQWait)
            {
                if(err == TM_OK)
                {
                    err = ddNT220xWaitIRQ(pObj, 1700, 50, 0x0C);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitIRQ(0x%08X) failed.", tUnit));
                }
                /* PATCH ES2 in case of WAIT IRQ Timeout */
                if(err == ddNT220x_ERR_NOT_READY && pObj->I2CMap.uBx02.bF.Major_rev == 1 && pObj->I2CMap.uBx02.bF.Minor_rev == 0)
                {
                        pObj->bSoftReset = True;
                }
            }            
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

