///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiXC_mhl.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
    1. Check whether MHL cable is plugged or not in Rx side
    2. Disable R-term and output Vbus
    3. Check whether Cbus is connected(discovery pulse completed)
    4. Sink -> Source: "SET_HPD"
    5. Sink -> Source: Write_Stat - "DCAP_RDY" and Write_INT - "DCAP_CHG"
    6. Sink -> Source: Write_Stat - "PATH_EN"
*/


#ifndef _MAPI_MHL_H_
#define _MAPI_MHL_H_

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_MHL_POWER_ON,
    E_MHL_POWER_STANDBY,
    E_MHL_POWER_DOWN
} E_MHL_POWERCTRL_Mode;

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------

void MApi_XC_MHL_Init(void);
void MApi_XC_MHL_Handler(void);
void MApi_XC_MHL_SetHPD(MS_BOOL bflag);
void MApi_XC_MHL_PowerCtrl(E_MHL_POWERCTRL_Mode pctrl);
MS_BOOL MApi_XC_MHL_WakeupDetect_Handler(void);

#endif //_MAPI_MHL_H_


