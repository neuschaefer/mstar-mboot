/*******************************************************************************
 *
 * FILE NAME          : MxL608_TunerSpurTable.cpp
 * 
 * AUTHOR             : Dong Liu                 
 *
 * DATE CREATED       : 12/21/2012
 *
 * DESCRIPTION        : This file contains spur shift table that used in channel 
 *                      tune procedure 
 *                             
 *******************************************************************************
 *                Copyright (c) 2012, MaxLinear, Inc.
 ******************************************************************************/

#include "MxL608_TunerSpurTable.h"
#include "MxL608_TunerCfg.h"
#include "Board.h"

#if (FRONTEND_TUNER_TYPE == TUNER_MXL608)

MXL608_CHAN_DEPENDENT_SPUR_REGISTER_T MxL608_SPUR_REGISTER = 
{ 2, {DFE_REFLUT_BYP_REG, DFE_REFSX_INT_MOD_REG} };

// Below lookup table of frequencies in different applications mode
// on which optimized channel tunning settings will be configured

// Table : For DVB-C and J.83B 
MXL608_CHAN_DEPENDENT_FREQ_TABLE_T MXL608_DIG_CABLE_FREQ_LUT[] = 
{ 
  {1        , 0x00, 0xD8},
  {695000000, 0x20, 0xD7},
  {0, 0, 0},
};


// Table : For Digital Terrestrial 
MXL608_CHAN_DEPENDENT_FREQ_TABLE_T MXL608_DIG_TERR_FREQ_LUT[] = 
{ 
  {1, 0x00, 0xD8},
  {0, 0, 0},
};
#endif //(FRONTEND_TUNER_TYPE == TUNER_MXL608)

