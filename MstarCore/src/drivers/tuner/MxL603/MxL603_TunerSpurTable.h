/*******************************************************************************
 *
 * FILE NAME          : MxL603_TunerSpurTable.h
 * 
 * AUTHOR             : Dong Liu
 *  
 * DATE CREATED       : 10/27/2012
 *
 * DESCRIPTION        : This file contains spur table definition for MxL603.
 *
 *******************************************************************************
 *                Copyright (c) 2012, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL603_TUNER_SPUR_TABLE_H__
#define __MXL603_TUNER_SPUR_TABLE_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/
#include "MaxLinearDataTypes.h"

/******************************************************************************
    Macros
******************************************************************************/
#define   MXL603_MAX_SPUR_REG_NUM    2 
/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/
typedef struct
{
  UINT8 SpurRegNum;  
  UINT8 SpurRegAddr[MXL603_MAX_SPUR_REG_NUM];
} MXL603_CHAN_DEPENDENT_SPUR_REGISTER_T, *PMXL603_CHAN_DEPENDENT_SPUR_REGISTER_T;

typedef struct
{
  UINT32 centerFreqHz;
  UINT8  reg_0xEA;
  UINT8  reg_0xEB;
} MXL603_CHAN_DEPENDENT_FREQ_TABLE_T, *PMXL603_CHAN_DEPENDENT_FREQ_TABLE_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/
extern MXL603_CHAN_DEPENDENT_SPUR_REGISTER_T MxL603_SPUR_REGISTER;

extern MXL603_CHAN_DEPENDENT_FREQ_TABLE_T MXL603_DIG_CABLE_FREQ_LUT[];
extern MXL603_CHAN_DEPENDENT_FREQ_TABLE_T MXL603_DIG_TERR_FREQ_LUT[];

/******************************************************************************
    Prototypes
******************************************************************************/

#endif /* __MXL603_TUNER_SPUR_TABLE_H__*/




