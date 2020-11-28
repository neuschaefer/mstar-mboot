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
/// @file   drvWDT.h
/// @brief  Piu Watch Dog Timer Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_WDT_H_
#define _DRV_WDT_H_



#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

////////////////////////////////////////////////////////////////////////////////
//  Type and Structure
////////////////////////////////////////////////////////////////////////////////
#define MSIF_WDT_LIB_CODE              {'W','D','T','_'}    //Lib code
#define MSIF_WDT_LIBVER                {'0','1'}            //LIB version
#define MSIF_WDT_BUILDNUM              {'0','4'}            //Build Number
#define MSIF_WDT_CHANGELIST            {'0','0','3','8','2','1','7','1'} //P4 ChangeList Number

#define WDT_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_WDT_LIB_CODE,                  /* IP__                                             */  \
    MSIF_WDT_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_WDT_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_WDT_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

#define MAX_TIMER_NUM			2

typedef enum _WDT_DbgLv
{
    E_WDT_DBGLV_NONE,			/* no debug message */
    E_WDT_DBGLV_ERR_ONLY,		/* show error only */
    E_WDT_DBGLV_INFO,			/* show error & informaiton */
    E_WDT_DBGLV_ALL			/* show error, information & funciton name */
}WDT_DbgLv;

typedef enum
{
    E_WDT_FAIL,
    E_WDT_OK,
} WDT_Result;

typedef enum _E_PIU_Timer
{
    E_TIMER_0,
    E_TIMER_1,
} E_PIU_Timer;

typedef struct _tmr_interrupt {
	MS_U32 		u32TmrInit;						/* Initial value of timer 						*/
 	MS_U32 		u32TmrMax;						/* Max value of timer 						*/
	void 		(*TmrFnct)(void *, void *, void *);	/* Function to execute when timer times out	*/
	void			*TmrFnctArg0;					/* Arguments supplied to user defined function 	*/
	void			*TmrFnctArg1;					/* Arguments supplied to user defined function 	*/
	void			*TmrFnctArg2;					/* Arguments supplied to user defined function 	*/
	MS_BOOL 	bTmrEn;							/* Flag indicating whether timer is enable 		*/
}tmr_interrupt;

////////////////////////////////////////////////////////////////////////////////
//  Function and Variable
////////////////////////////////////////////////////////////////////////////////
WDT_Result MDrv_WDT_GetLibVer(const MSIF_Version **ppVersion);
WDT_Result MDrv_WDT_Init(WDT_DbgLv eLevel);
WDT_Result MDrv_WDT_Stop(WDT_DbgLv eLevel);
WDT_Result MDrv_WDT_Clear(void);
WDT_Result MDrv_WDT_ClearRstFlag(void);
WDT_Result MDrv_WDT_IsReset(void);
WDT_Result MDrv_WDT_IsEnable(void);
WDT_Result MDrv_WDT_SetTimer(WDT_DbgLv eLevel, MS_U16 sec);
WDT_Result MDrv_WDT_SetTimer_ms(WDT_DbgLv eLevel, MS_U16 msec);
WDT_Result MDrv_WDT_SetTimer_us(WDT_DbgLv eLevel, MS_U16 usec);
WDT_Result MDrv_WDT_SetIntTimer(WDT_DbgLv eLevel, MS_U16 sec);

void MDrv_TIMER_Init(void);
void MDrv_TIMER_CfgFnct(E_PIU_Timer eTimer, void (*fnct)(void *, void *, void *), void *arg0, void *arg1, void *arg2 );
void MDrv_TIMER_Count(E_PIU_Timer eTimer, MS_BOOL bEnable);
void MDrv_TIMER_INT(E_PIU_Timer eTimer, MS_BOOL bEnable);
void MDrv_TIMER_Rst(E_PIU_Timer eTimer);
void MDrv_TIMER_SetMaxMatch(E_PIU_Timer eTimer, MS_U32 u32MaxTimer);
MS_BOOL MDrv_TIMER_HitMaxMatch(E_PIU_Timer eTimer);
MS_U32 MDrv_TIMER_GetMaxMatch(E_PIU_Timer eTimer);
MS_U32 MDrv_TIMER_GetCounter(E_PIU_Timer eTimer);
MS_U32 MDrv_TIMER_GetSecond(E_PIU_Timer eTimer);
MS_U32 MDrv_TIMER_GetMs(E_PIU_Timer eTimer);
MS_U32 MDrv_TIMER_GetUs(E_PIU_Timer eTimer);
void MDrv_TIMER_Delay(E_PIU_Timer eTimer, MS_U32 u32Second);
void MDrv_TIMER_DelayMs(E_PIU_Timer eTimer, MS_U32 u32MS);
void MDrv_TIMER_DelayUs(E_PIU_Timer eTimer, MS_U32 u32US);
void MDrv_TIMER_Exit(void);

#ifdef __cplusplus
}
#endif


#endif // _DRV_WDT_H_

