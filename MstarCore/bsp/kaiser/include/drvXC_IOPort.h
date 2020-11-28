////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file    drvXC_IOPort.h
/// @brief  IO ports API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _IOPORT_H_
#define _IOPORT_H_

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

///This Enum is interface for Hal and Application level.
typedef enum
{
    INPUT_PORT_NONE_PORT = 0,

    INPUT_PORT_ANALOG0 = 1,        // Data port
    INPUT_PORT_ANALOG1,
    INPUT_PORT_ANALOG2,
    INPUT_PORT_ANALOG3,
    INPUT_PORT_ANALOG4,

    // Reserved area

    INPUT_PORT_ANALOG0_SYNC = 10,  // Sync port
    INPUT_PORT_ANALOG1_SYNC,
    INPUT_PORT_ANALOG2_SYNC,
    INPUT_PORT_ANALOG3_SYNC,
    INPUT_PORT_ANALOG4_SYNC,

    // Reserved area

    INPUT_PORT_YMUX_CVBS0 = 30,
    INPUT_PORT_YMUX_CVBS1,
    INPUT_PORT_YMUX_CVBS2,
    INPUT_PORT_YMUX_CVBS3,
    INPUT_PORT_YMUX_CVBS4,
    INPUT_PORT_YMUX_CVBS5,
    INPUT_PORT_YMUX_CVBS6,
    INPUT_PORT_YMUX_CVBS7,
    INPUT_PORT_YMUX_G0,
    INPUT_PORT_YMUX_G1,
    INPUT_PORT_YMUX_G2,

    // Reserved area

    INPUT_PORT_CMUX_CVBS0 = 50,
    INPUT_PORT_CMUX_CVBS1,
    INPUT_PORT_CMUX_CVBS2,
    INPUT_PORT_CMUX_CVBS3,
    INPUT_PORT_CMUX_CVBS4,
    INPUT_PORT_CMUX_CVBS5,
    INPUT_PORT_CMUX_CVBS6,
    INPUT_PORT_CMUX_CVBS7,
    INPUT_PORT_CMUX_R0,
    INPUT_PORT_CMUX_R1,
    INPUT_PORT_CMUX_R2,

    // Reserved area

    INPUT_PORT_DVI0 = 80,
    INPUT_PORT_DVI1,
    INPUT_PORT_DVI2,
    INPUT_PORT_DVI3,

    // Reserved area

    INPUT_PORT_MVOP = 100,
    INPUT_PORT_MVOP2,

} E_MUX_INPUTPORT;

///This Enum is interface for Hal and Application level.
typedef enum
{
    OUTPUT_PORT_NONE_PORT = 0,

    OUTPUT_PORT_SCALER_MAIN_WINDOW = 1,

    // Reserved area

    OUTPUT_PORT_SCALER_SUB_WINDOW1 = 10,

    // Reserved area

    OUTPUT_PORT_CVBS1 = 20,
    OUTPUT_PORT_CVBS2,

    // Reserved area

    OUTPUT_PORT_YPBPR1 = 40,
    OUTPUT_PORT_YPBPR2,

    // Reserved area

    OUTPUT_PORT_HDMI1 = 60,
    OUTPUT_PORT_HDMI2,

    // Reserved area

    OUTPUT_PORT_OFFLINE_DETECT = 80,

    // Reserved area
    OUTPUT_PORT_DWIN = 100,
} E_MUX_OUTPUTPORT;

#define IsAnalogPort(x)         ( (x) >= INPUT_PORT_ANALOG0 && (x) <= INPUT_PORT_ANALOG4 )
#define IsDVIPort(x)            ( (x) >= INPUT_PORT_DVI0 && (x) <= INPUT_PORT_DVI3 )
#define IsYCVBSPort(x)          ( (x) >= INPUT_PORT_YMUX_CVBS0 && (x) <= INPUT_PORT_YMUX_CVBS7 )
#define IsCCVBSPort(x)          ( (x) >= INPUT_PORT_CMUX_CVBS0 && (x) <= INPUT_PORT_CMUX_CVBS7 )
#define IsCVBSPort(x)           ( IsYCVBSPort(x) || IsCCVBSPort(x) )

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

#endif // _IOPORT_H_
