///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mapi_mhl.h
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

#include "MsTypes.h"
#include "mdrv_mhl_st.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
void mapi_mhl_SetHPD(MS_BOOL bflag);
void mapi_mhl_SetARC(MS_BOOL bEable);
MS_BOOL mapi_mhl_HDMI_5V_Detect(void);
MS_BOOL mapi_mhl_CableDetect(void);
MS_BOOL mapi_mhl_CbusStatus(void);
void mapi_mhl_CbusConnectionCheck(void);
void mapi_mhl_init(void);
void mapi_mhl_init_EDID(MS_U8 *edid);
MS_BOOL mapi_mhl_CbusRcpReply (MS_U8 statusCode, MS_U8 keyCode);
MS_BOOL mapi_mhl_CbusRapReply (MS_U8 statusCode);
MS_BOOL mapi_mhl_Cbus_SetHPDState(MS_BOOL bflag);
void mapi_mhl_Cbus_SetPathEn(MS_BOOL bflag);
void mapi_mhl_Cbus_SetDCapRdy(MS_BOOL bflag);
void mapi_mhl_Cbus_SetDCapChg(MS_BOOL bflag);
void mapi_mhl_SetCbusReqState(CbusReqState_T cbusState);
void mapi_mhl_CbusIntCB(void);
void mapi_mhl_CbusIntHandler(void);
MS_U8 mapi_mhl_CBusNextCmdQueue(void);
MS_U8 mapi_mhl_CBusGetQueueSize(void);
MS_BOOL mapi_mhl_CbusSendMsg (CbusReq_S *pReq);
MS_BOOL mapi_mhl_CBusProcessMSCSubCmd (MS_U8 cmd);
void mapi_mhl_RegisterCallBackFunctions(link_cbus_event_handle_func rcp, link_cbus_event_handle_func rap);
void mapi_mhl_CbusRxHandler (void);
MS_U8 mapi_mhl_CbusTxHandler (void);
MS_BOOL msapi_mhl_SendRCPCmd(MS_U8 databuf);
MS_BOOL msapi_mhl_SendRAPCmd(MS_U8 databuf);
MS_BOOL msapi_mhl_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease);
void mapi_mhl_SetDevCapTbl(MS_U8* pu8Tbl);
MS_BOOL mapi_mhl_Cbus_SetHPDState(MS_BOOL bflag);
void mapi_mhl_CbusProcessMSCSubCmd (MS_U8 subcmd, MS_U8 subdata);

#ifdef __cplusplus
}
#endif

#endif //_MAPI_MHL_H_


