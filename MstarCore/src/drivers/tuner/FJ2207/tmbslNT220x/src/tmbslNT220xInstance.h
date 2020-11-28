//-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2001 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of NXP Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of NXP
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than NXP Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmbslNT220xInstance.h
//
// DESCRIPTION:  define the static Objects
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:        
//-----------------------------------------------------------------------------
//
#ifndef _TMBSLNT220x_INSTANCE_H //-----------------
#define _TMBSLNT220x_INSTANCE_H

tmErrorCode_t NT220xAllocInstance (tmUnitSelect_t tUnit, pptmNT220xObject_t ppDrvObject);
tmErrorCode_t NT220xDeAllocInstance (tmUnitSelect_t tUnit);
tmErrorCode_t NT220xGetInstance (tmUnitSelect_t tUnit, pptmNT220xObject_t ppDrvObject);


#endif // _TMBSLNT220x_INSTANCE_H //---------------
