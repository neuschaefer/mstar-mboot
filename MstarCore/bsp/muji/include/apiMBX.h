#ifndef _API_MBX_H
#define _API_MBX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

MBX_Result  MApi_MBX_Init(MBX_CPU_ID eHKCPU, MBX_ROLE_ID eHostRole, MS_U32 u32TimeoutMillSecs);
MBX_Result  MApi_MBX_DeInit(MS_BOOL bForceDiscardPendingMsg);
MBX_Result  MApi_MBX_RegisterMSG(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize);
// MBX_Result  MApi_MBX_RegisterMSGWithCallBack(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize, MBX_QUEUE_STATUS_NOTIFY_FUNC notifier);
MBX_Result  MApi_MBX_RegisterMSGWithCallBack(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize, MBX_MAIL_ARRIVE_NOTIFY_FUNC notifier);
MBX_Result  MApi_MBX_UnRegisterMSG(MBX_Class eMsgClass, MS_BOOL bForceDiscardMsgQueue);
MBX_Result  MApi_MBX_ClearMSG(MBX_Class eMsgClass);
MBX_Result  MApi_MBX_SendMsg(MBX_Msg *pMsg);
MBX_Result  MApi_MBX_GetMsgQueueStatus(MBX_Class eTargetClass, MBX_MSGQ_Status *pMsgQueueStatus);
MBX_Result  MApi_MBX_RecvMsg(MBX_Class eTargetClass, MBX_Msg *pMsg, MS_U32 u32WaitMillSecs, MS_U32 u32Flag);
MBX_Result  MApi_MBX_CheckMsg(MBX_Class eTargetClass, MBX_Msg *pMsg, MS_U32 u32WaitMillSecs, MS_U32 u32Flag);
MBX_Result  MApi_MBX_SendMsgLoopback(MBX_Msg *pMsg, MBX_ROLE_ID eSrcRoleId);
MBX_Result  MApi_MBX_Enable(MS_BOOL bEnable);//Enable receiving regisited messages in kernel
MBX_Result  MApi_MBX_RemoveLatestMsg(void);
MBX_Result  MApi_MBX_QueryDynamicClass(MBX_ROLE_ID eRoleID, char *name, MS_U8 *pmbx_class);
MBX_Result  MApi_MBX_GenerateDynamicClass(MBX_ROLE_ID eRoleID, char *name, MS_U8 *pmbx_class);

#ifdef __cplusplus
}
#endif

#endif

