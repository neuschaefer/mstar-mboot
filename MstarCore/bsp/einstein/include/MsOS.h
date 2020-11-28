//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
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
/// @file   MsOS.h
/// @brief  MStar OS Wrapper
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _MS_OS_H_
#define _MS_OS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "MsIRQ.h"
//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define MSIF_MSOS_LIB_CODE              {'M','S','O','S'}    //Lib code
#define MSIF_MSOS_LIBVER                {'0','1'}            //LIB version
#define MSIF_MSOS_BUILDNUM              {'0','1'}            //Build Number
#define MSIF_MSOS_CHANGELIST            {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define MSOS_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_MSOS_LIB_CODE,                  /* IP__                                             */  \
    MSIF_MSOS_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_MSOS_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_MSOS_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

#define MSOS_TASK_MAX           (32+120)
#define MSOS_MEMPOOL_MAX        (8+64)
#define MSOS_FIXSIZE_MEMPOOL_MAX  (8)
#define MSOS_SEMAPHORE_MAX      (32+150)
#define MSOS_MUTEX_MAX          (64+240)
#define MSOS_EVENTGROUP_MAX     (64)
#define MSOS_TIMER_MAX          (32)
#define MSOS_QUEUE_MAX          (16+60)
#define MSOS_CONDITION_MAX      (64+240)

#define MSOS_OS_MALLOC          (0x7654FFFF)
#define MSOS_MALLOC_ID          (0x0000FFFF)

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
//time and clock macros
#define TICK_PER_ONE_MS     (1) //Note: confirm Kernel fisrt
#define MSOS_WAIT_FOREVER   (0xffffff00/TICK_PER_ONE_MS)

#ifdef  MSOS_PERF_DEBUG
#define MSOS_PERF_PROFILE_DECL()  MS_U32 u32time1=0, u32time2=0
#define MSOS_PERF_PROFILE_ON()    u32time1 = MsOS_GetSystemTime()
#define MSOS_PERF_PROFILE_OFF()   u32time2 = MsOS_GetSystemTime(); \
                                  printf("[MSOS_DBG]%s:%d takes %6dms\n",__FILE__, __LINE__, u32time2-u32time1)
#else
#define MSOS_PERF_PROFILE_DECL()
#define MSOS_PERF_PROFILE_ON()
#define MSOS_PERF_PROFILE_OFF()
#endif

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
#if defined (MSOS_TYPE_ECOS) || defined (MSOS_TYPE_LINUX) || defined (MSOS_TYPE_NOS) || defined (MSOS_TYPE_UCOS) || defined (MSOS_TYPE_NUTTX)

//compatible with Nucleus's task_entry
typedef void ( *TaskEntry ) (MS_U32 argc, void *argv); ///< Task entry function  argc: pass additional data to task entry; argv: not used by eCos
typedef void ( *InterruptCb ) (InterruptNum eIntNum);               ///< Interrupt callback function
typedef void ( *SignalCb ) (MS_U32 u32Signals);        ///< Signal callback function
typedef void ( *TimerCb ) (MS_U32 u32StTimer, MS_U32 u32TimerID);  ///< Timer callback function  u32StTimer: not used; u32TimerID: Timer ID

typedef struct {
    volatile MS_S32 s32Value;
} MsOS_Atomic;


#ifdef MSOS_TYPE_UCOS
/// Task priority
typedef enum
{
    E_TASK_PRI_SYS      = 0,    ///< System priority task   ( interrupt level driver, e.g. TSP, SMART )
    E_TASK_PRI_HIGHEST  = 16,   ///< Highest priority task  ( background monitor driver, e.g. DVBC, HDMI )
    E_TASK_PRI_HIGH     = 32,   ///< High priority task     ( service task )
    E_TASK_PRI_MEDIUM   = 48,   ///< Medium priority task   ( application task )
    E_TASK_PRI_LOW      = 64,   ///< Low priority task      ( nonbusy application task )
    E_TASK_PRI_LOWEST   = 96,   ///< Lowest priority task   ( idle application task )
} TaskPriority;
#elif defined(MSOS_TYPE_NUTTX)
/// Task priority
typedef enum
{
	E_TASK_PRI_SYS      = 255,
	E_TASK_PRI_HIGHEST  = 255,
	E_TASK_PRI_HIGH     = 178,
	E_TASK_PRI_MEDIUM   = 100,
	E_TASK_PRI_LOW      = 50,
	E_TASK_PRI_LOWEST   = 1,
} TaskPriority;
#else
/// Task priority
typedef enum
{
    E_TASK_PRI_SYS      = 0,    ///< System priority task   ( interrupt level driver, e.g. TSP, SMART )
    E_TASK_PRI_HIGHEST  = 4,    ///< Highest priority task  ( background monitor driver, e.g. DVBC, HDMI )
    E_TASK_PRI_HIGH     = 8,    ///< High priority task     ( service task )
    E_TASK_PRI_MEDIUM   = 12,   ///< Medium priority task   ( application task )
    E_TASK_PRI_LOW      = 16,   ///< Low priority task      ( nonbusy application task )
    E_TASK_PRI_LOWEST   = 24,   ///< Lowest priority task   ( idle application task )
} TaskPriority;
#endif


/// Suspend type
typedef enum
{
    E_MSOS_PRIORITY,            ///< Priority-order suspension
    E_MSOS_FIFO,                ///< FIFO-order suspension
} MsOSAttribute;

/// Message size type
typedef enum
{
    E_MSG_FIXED_SIZE,           ///< Fixed size message
    E_MSG_VAR_SIZE,             ///< Variable size message
} MessageType;

/// Event mode
typedef enum
{
    E_AND,                      ///< Specify all of the requested events are require.
    E_OR,                       ///< Specify any of the requested events are require.
    E_AND_CLEAR,                ///< Specify all of the requested events are require. If the request are successful, clear the event.
    E_OR_CLEAR,                 ///< Specify any of the requested events are require. If the request are successful, clear the event.
} EventWaitMode;

typedef enum
{
    E_IRQ_DISABLE = 0 << 0, // reserve for MsOS_DisableInterrupt
    E_IRQ_ENABLE = 1 << 0, // reserve for MsOS_EnableInterrupt
    E_IRQ_ACK = 1 << 1,
    E_IRQ_DEBUG_STATUS_FLOW = 1 << 2,
    E_IRQ_DEBUG_DISABLE = 1 << 31,
} IrqDebugOpt;

typedef struct
{
    MS_S32                          iId;
    MS_U32                          uPoolSize;
    MS_U32                          u32MinAllocation;
    MS_U32                          u32Addr;
    MsOSAttribute                   eAttribute;
    char                            szName[16];
} MemoryPool_Info, *PMemoryPool_Info;

typedef struct
{
    MS_S32                          iId;
    TaskPriority                    ePriority;
    void                            *pStack;
    MS_U32                          u32StackSize;
    char szName[16];
} Task_Info, *PTask_Info;

typedef struct
{
        unsigned int                LX_MEM_ADDR;
        unsigned int                LX_MEM_LENGTH;
        unsigned int                LX_MEM2_ADDR;
        unsigned int                LX_MEM2_LENGTH;
        unsigned int                EMAC_ADDR;
        unsigned int                EMAC_LENGTH;
        unsigned int                DRAM_ADDR;
        unsigned int                DRAM_LENGTH;
        unsigned int                BB_ADDR;
        unsigned int                BB_LENGTH;
        unsigned int                MPOOL_MEM_ADDR;
        unsigned int                MPOOL_MEM_LENGTH;
        unsigned int                G3D_MEM0_ADDR;
        unsigned int                G3D_MEM0_LENGTH;
        unsigned int                G3D_MEM1_ADDR;
        unsigned int                G3D_MEM1_LENGTH;
        unsigned int                G3D_CMDQ_ADDR;
        unsigned int                G3D_CMDQ_LENGTH;
}IO_Sys_Info_t;

#elif defined (MSOS_TYPE_LINUX_KERNEL)

#include <linux/kernel.h>
#include <linux/interrupt.h>

typedef void ( *TaskEntry ) (MS_U32 argc, void *argv); ///< Task entry function  argc: pass additional data to task entry; argv: not used by eCos
// typedef void ( *InterruptCb ) (InterruptNum eIntNum);               ///< Interrupt callback function
typedef irqreturn_t ( *InterruptCb ) (InterruptNum eIntNum, void* dev_id);
typedef void ( *SignalCb ) (MS_U32 u32Signals);        ///< Signal callback function
typedef void ( *TimerCb ) (MS_U32 u32StTimer, MS_U32 u32TimerID);  ///< Timer callback function  u32StTimer: not used; u32TimerID: Timer ID

/// Task priority
typedef enum
{
    E_TASK_PRI_SYS      = 0,    ///< System priority task   ( interrupt level driver, e.g. TSP, SMART )
    E_TASK_PRI_HIGHEST  = 4,    ///< Highest priority task  ( background monitor driver, e.g. DVBC, HDMI )
    E_TASK_PRI_HIGH     = 8,    ///< High priority task     ( service task )
    E_TASK_PRI_MEDIUM   = 12,   ///< Medium priority task   ( application task )
    E_TASK_PRI_LOW      = 16,   ///< Low priority task      ( nonbusy application task )
    E_TASK_PRI_LOWEST   = 24,   ///< Lowest priority task   ( idle application task )
} TaskPriority;

/// Suspend type
typedef enum
{
    E_MSOS_PRIORITY,            ///< Priority-order suspension
    E_MSOS_FIFO,                ///< FIFO-order suspension
} MsOSAttribute;

/// Message size type
typedef enum
{
    E_MSG_FIXED_SIZE,           ///< Fixed size message
    E_MSG_VAR_SIZE,             ///< Variable size message
} MessageType;

/// Event mode
typedef enum
{
    E_AND,                      ///< Specify all of the requested events are require.
    E_OR,                       ///< Specify any of the requested events are require.
    E_AND_CLEAR,                ///< Specify all of the requested events are require. If the request are successful, clear the event.
    E_OR_CLEAR,                 ///< Specify any of the requested events are require. If the request are successful, clear the event.
} EventWaitMode;

typedef struct
{
    MS_S32                          iId;
    MS_U32                          uPoolSize;
    MS_U32                          u32MinAllocation;
    MS_U32                          u32Addr;
    MsOSAttribute                   eAttribute;
    char                            szName[16];
} MemoryPool_Info, *PMemoryPool_Info;

typedef struct
{
    MS_S32                          iId;
    TaskPriority                    ePriority;
    void                            *pStack;
    MS_U32                          u32StackSize;
    char szName[16];
} Task_Info, *PTask_Info;

typedef struct
{
        unsigned int                LX_MEM_ADDR;
        unsigned int                LX_MEM_LENGTH;
        unsigned int                LX_MEM2_ADDR;
        unsigned int                LX_MEM2_LENGTH;
        unsigned int                EMAC_ADDR;
        unsigned int                EMAC_LENGTH;
        unsigned int                DRAM_ADDR;
        unsigned int                DRAM_LENGTH;
        unsigned int                BB_ADDR;
        unsigned int                BB_LENGTH;
        unsigned int                MPOOL_MEM_ADDR;
        unsigned int                MPOOL_MEM_LENGTH;
        unsigned int                G3D_MEM0_ADDR;
        unsigned int                G3D_MEM0_LENGTH;
        unsigned int                G3D_MEM1_ADDR;
        unsigned int                G3D_MEM1_LENGTH;
        unsigned int                G3D_CMDQ_ADDR;
        unsigned int                G3D_CMDQ_LENGTH;
}IO_Sys_Info_t;

#elif defined (MSOS_TYPE_XXX)

#error "The OS is not supported now ..."

#endif

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
//
// Init
//
MS_BOOL MsOS_Init (void);


//
// Memory management
//
MS_S32 MsOS_CreateMemoryPool (MS_U32 u32PoolSize,
                              MS_U32 u32MinAllocation,
                              void * pPoolAddr,
                              MsOSAttribute eAttribute,
                              char *pPoolName);

MS_BOOL MsOS_DeleteMemoryPool (MS_S32 s32PoolId);

MS_BOOL MsOS_InfoMemoryPool (MS_S32 s32PoolId,
                             void **pPoolAddr,
                             MS_U32 *pu32PoolSize,
                             MS_U32 *pu32FreeSize,
                             MS_U32 *pu32LargestFreeBlockSize);

void * MsOS_AllocateMemory (MS_U32 u32Size, MS_S32 s32PoolId);

//void * MsOS_AllocateAlignedMemory (MS_U32 u32Size, MS_U32 u32AlignedByte, MS_S32 s32PoolId);

void * MsOS_ReallocateMemory (void *pOrgAddress, MS_U32 u32NewSize, MS_S32 s32PoolId);

MS_BOOL MsOS_FreeMemory (void *pAddress, MS_S32 s32PoolId);

MS_S32 MsOS_CreateFixSizeMemoryPool (MS_U32 u32PoolSize,
                                     MS_U32 u32BlockSize,
                                     void * pPoolAddr,
                                     MsOSAttribute eAttribute,
                                     char *pPoolName);

MS_BOOL MsOS_DeleteFixSizeMemoryPool (MS_S32 s32PoolId);

MS_BOOL MsOS_InfoFixSizeMemoryPool (MS_S32 s32PoolId,
                                    void **pPoolAddr,
                                    MS_U32 *pu32PoolSize,
                                    MS_U32 *pu32FreeSize,
                                    MS_U32 *pu32LargestFreeBlockSize);

void * MsOS_AllocateFixSizeMemory (MS_S32 s32PoolId);

MS_BOOL MsOS_FreeFixSizeMemory (void *pAddress, MS_S32 s32PoolId);


//
// Task
//
MS_S32 MsOS_CreateTask (TaskEntry pTaskEntry,
                        MS_U32 u32TaskEntryData,
                        TaskPriority eTaskPriority,
                        MS_BOOL bAutoStart,
                        void * pStackEntry,
                        MS_U32 u32StackSize,
                        char *pTaskName);

MS_BOOL MsOS_DeleteTask (MS_S32 s32TaskId);

void MsOS_YieldTask (void);

void MsOS_DelayTask (MS_U32 u32Ms);

void MsOS_DelayTaskUs (MS_U32 u32Us);

void MsOS_DelayTaskUs_Poll(MS_U32 u32Us);

MS_BOOL MsOS_ResumeTask (MS_S32 s32TaskId);

MS_BOOL MsOS_SuspendTask (MS_S32 s32TaskId);

MS_S32 MsOS_InfoTaskID (void);
//-------------------------------------------------------------------------------------------------
/// Get thread ID of current thread/process in OS
/// @return : current thread ID
//-------------------------------------------------------------------------------------------------
MS_S32 MsOS_GetOSThreadID (void);

//
// Mutex
//
#define MSOS_PROCESS_PRIVATE    0x00000000
#define MSOS_PROCESS_SHARED     0x00000001
#define MAX_MUTEX_NAME_LENGTH   50
MS_S32 MsOS_CreateMutex ( MsOSAttribute eAttribute, char *pMutexName, MS_U32 u32Flag);

MS_BOOL MsOS_DeleteMutex (MS_S32 s32MutexId);

MS_BOOL MsOS_ObtainMutex (MS_S32 s32MutexId, MS_U32 u32WaitMs);

MS_BOOL MsOS_ReleaseMutex (MS_S32 s32MutexId);

MS_BOOL MsOS_InfoMutex (MS_S32 s32MutexId, MsOSAttribute *peAttribute, char *pMutexName);


//
// Semaphore
//
MS_S32 MsOS_CreateSemaphore (MS_U32 u32InitCnt,
                             MsOSAttribute eAttribute,
                             char *pName);

MS_BOOL MsOS_DeleteSemaphore (MS_S32 s32SemaphoreId);

MS_BOOL MsOS_ObtainSemaphore (MS_S32 s32SemaphoreId, MS_U32 u32WaitMs);

MS_BOOL MsOS_ReleaseSemaphore (MS_S32 s32SemaphoreId);

MS_BOOL MsOS_InfoSemaphore (MS_S32 s32SemaphoreId, MS_U32 *pu32Cnt, MsOSAttribute *peAttribute, char *pSemaphoreName);


//
// Event management
//
MS_S32 MsOS_CreateEventGroup (char *pName);

MS_BOOL MsOS_DeleteEventGroup (MS_S32 s32EventGroupId);

MS_BOOL MsOS_SetEvent (MS_S32 s32EventGroupId, MS_U32 u32EventFlag);

MS_BOOL MsOS_ClearEvent (MS_S32 s32EventGroupId, MS_U32 u32EventFlag);

MS_BOOL MsOS_WaitEvent (MS_S32  s32EventGroupId,
                        MS_U32  u32WaitEventFlag,
                        MS_U32  *pu32RetrievedEventFlag,
                        EventWaitMode eWaitMode,
                        MS_U32  u32WaitMs);

/*
//
// Signal management
//
MS_BOOL MsOS_CreateSignal (SignalCb pSignalCb);

MS_BOOL MsOS_ControlSignals (MS_U32 u32SignalMask);

MS_BOOL MsOS_SendSignals (MS_S32 s32TaskId, MS_U32 u32Signal);

MS_U32 MsOS_ReceiveSignals (void);
*/

//
// Timer management
//
MS_S32 MsOS_CreateTimer (TimerCb    pTimerCb,
                         MS_U32     u32FirstTimeMs,
                         MS_U32     u32PeriodTimeMs,
                         MS_BOOL    bStartTimer,
                         char       *pName);

MS_BOOL MsOS_DeleteTimer (MS_S32 s32TimerId);

MS_BOOL MsOS_StartTimer (MS_S32 s32TimerId);

MS_BOOL MsOS_StopTimer (MS_S32 s32TimerId);

MS_BOOL MsOS_ResetTimer (MS_S32     s32TimerId,
                         MS_U32     u32FirstTimeMs,
                         MS_U32     u32PeriodTimeMs,
                         MS_BOOL    bStartTimer);

//
// System time
//
//MS_U32 MsOS_GetSystemTick (void);

MS_U32 MsOS_GetSystemTime (void);


MS_U32 MsOS_Timer_DiffTimeFromNow(MS_U32 u32TaskTimer); ///[OBSOLETE]

MS_U32 MsOS_Timer_DiffTime(MS_U32 u32Timer, MS_U32 u32TaskTimer); ///[OBSOLETE]
//MS_BOOL MsOS_SetSystemTime (MS_U32 u32SystemTime);


//
// Queue
//
MS_S32 MsOS_CreateQueue (void           *pStartAddr,
                         MS_U32         u32QueueSize,
                         MessageType    eMessageType,
                         MS_U32         u32MessageSize,
                         MsOSAttribute  eAttribute,
                         char           *pQueueName);

MS_BOOL MsOS_DeleteQueue (MS_S32 s32QueueId);

MS_BOOL MsOS_SendToQueue (MS_S32 s32QueueId, MS_U8 *pu8Message, MS_U32 u32Size, MS_U32 u32WaitMs);

MS_BOOL MsOS_RecvFromQueue (MS_S32 s32QueueId, MS_U8 *pu8Message, MS_U32 u32IntendedSize, MS_U32 *pu32ActualSize, MS_U32 u32WaitMs);

MS_BOOL MsOS_PeekFromQueue (MS_S32 s32QueueId, MS_U8 *pu8Message, MS_U32 u32IntendedSize, MS_U32 *pu32ActualSize);

//
// Interrupt management
//
MS_BOOL MsOS_AttachInterrupt (InterruptNum eIntNum, InterruptCb pIntCb);

MS_BOOL MsOS_DetachInterrupt (InterruptNum eIntNum);

MS_BOOL MsOS_EnableInterrupt (InterruptNum eIntNum);

MS_BOOL MsOS_DebugInterrupt (InterruptNum eIntNum, IrqDebugOpt eIrqDebugOpt);

MS_BOOL MsOS_DisableInterrupt (InterruptNum eIntNum);

MS_BOOL MsOS_In_Interrupt (void);

MS_U32  MsOS_DisableAllInterrupts(void);

MS_BOOL MsOS_RestoreAllInterrupts(MS_U32 u32OldInterrupts);

MS_BOOL MsOS_EnableAllInterrupts(void);



#if defined(__aeon__)
typedef enum {
    E_EXCEPTION_BUS_ERROR = 2,
    E_EXCEPTION_DATA_PAGE_FAULT,
    E_EXCEPTION_INSTRUCTION_PAGE_FAULT,
    E_EXCEPTION_TICK_TIMER,             ///< tick timer, do not use directly
    E_EXCEPTION_UNALIGNED_ACCESS,
    E_EXCEPTION_ILLEGAL_INSTRUCTION,
    E_EXCEPTION_EXTERNAL_INTERRUPT,     ///< external interrupt, do not use directly
    E_EXCEPTION_DTLB_MISS,
    E_EXCEPTION_ITLB_MISS,
    E_EXCEPTION_RANGE,
    E_EXCEPTION_SYSCALL,                ///< caused by l.sys
    E_EXCEPTION_RESERVED,
    E_EXCEPTION_TRAP,                   ///< caused by l.trap
    E_EXCEPTION_MAX = E_EXCEPTION_TRAP,
} MHAL_EXCEPTION_TYPE;

typedef enum {
    E_INTERRUPT_TICK_TIMER, //< risc32 builtin tick timer
#if defined(MSOS_TYPE_NUTTX) 
	E_INTERRUPT_00 = 0, 
#else
    E_INTERRUPT_00 = 1,     //< PIC interrupt start from 1 for handler performance
#endif
	E_INTERRUPT_01,
    E_INTERRUPT_02,
    E_INTERRUPT_03,
    E_INTERRUPT_04,
    E_INTERRUPT_05,
    E_INTERRUPT_06,
    E_INTERRUPT_07,
    E_INTERRUPT_08,
    E_INTERRUPT_09,
    E_INTERRUPT_10,
    E_INTERRUPT_11,
    E_INTERRUPT_12,
    E_INTERRUPT_13,
    E_INTERRUPT_14,
    E_INTERRUPT_15,
    E_INTERRUPT_16,
    E_INTERRUPT_17,
    E_INTERRUPT_18,
    E_INTERRUPT_19,
    E_INTERRUPT_20,
    E_INTERRUPT_21,
    E_INTERRUPT_22,
    E_INTERRUPT_23,
    E_INTERRUPT_24,
    E_INTERRUPT_25,
    E_INTERRUPT_26,
    E_INTERRUPT_27,
    E_INTERRUPT_28,
    E_INTERRUPT_29,
    E_INTERRUPT_30,
    E_INTERRUPT_31,
} MHAL_INTERRUPT_TYPE;

// Aliases for interrupt number
#define E_INTERRUPT_FIQ         E_INTERRUPT_02
#define E_INTERRUPT_IRQ         E_INTERRUPT_03
#define E_INTERRUPT_UART        E_INTERRUPT_19
#define E_INTERRUPT_MAX         E_INTERRUPT_31

typedef struct
{
    unsigned long   r[32];          ///< GPR registers
#ifdef __AEONR2__
    unsigned long   machi2;         // Highest 32-bits of new 32x32=64 multiplier
#endif
    unsigned long   machi;          // High and low words of
    unsigned long   maclo;          //   multiply/accumulate reg

    // These are only saved for exceptions and interrupts
    int             vector;         ///< vector number
    int             sr;             ///< status register
    unsigned long   pc;             ///< program counter

    // Saved only for exceptions, and not restored when continued:
    // Effective address of instruction/data access that caused exception
    unsigned long   eear;           ///< exception effective address
} MHAL_SavedRegisters;
#else
typedef enum {
    E_EXCEPTION_DATA_TLBERROR_ACCESS = 1,    // TLB modification exception
    E_EXCEPTION_DATA_TLBMISS_ACCESS,         // TLB miss (Load or IFetch)
    E_EXCEPTION_DATA_TLBMISS_WRITE,          // TLB miss (Store)
    E_EXCEPTION_DATA_UNALIGNED_ACCESS,       // Address error (Load or Ifetch)
    E_EXCEPTION_DATA_UNALIGNED_WRITE,        // Address error (store)
    E_EXCEPTION_CODE_ACCESS,                 // Bus error (Ifetch)
    E_EXCEPTION_DATA_ACCESS,                 // Bus error (data load or store)
    E_EXCEPTION_SYSTEM_CALL,                 // System call
    E_EXCEPTION_INSTRUCTION_BP,              // Break point
    E_EXCEPTION_ILLEGAL_INSTRUCTION,         // Reserved instruction
    E_EXCEPTION_COPROCESSOR,                 // Coprocessor unusable
    E_EXCEPTION_OVERFLOW,                    // Arithmetic overflow
    E_EXCEPTION_RESERVED_13,                 // Reserved
    E_EXCEPTION_DIV_BY_ZERO,                 // Division-by-zero [reserved vector]
    E_EXCEPTION_FPU,                         // Floating point exception
    E_EXCEPTION_MAX = E_EXCEPTION_FPU,
} MHAL_EXCEPTION_TYPE;

typedef enum {
    E_INTERRUPT_02 = 0,
    E_INTERRUPT_03,
    E_INTERRUPT_04,
    E_INTERRUPT_05,
    E_INTERRUPT_06,
    E_INTERRUPT_07,
} MHAL_INTERRUPT_TYPE;

// Aliases for interrupt number
#define E_INTERRUPT_FIQ         E_INTERRUPT_03
#define E_INTERRUPT_IRQ         E_INTERRUPT_02
#define E_INTERRUPT_TICK_TIMER  E_INTERRUPT_07
#define E_INTERRUPT_MAX         E_INTERRUPT_07
#define E_EXCEPTION_TRAP        E_EXCEPTION_RESERVED_13

typedef struct
{
    // These are common to all saved states
    unsigned long    d[32];          /* Data regs                    */
    unsigned long    hi;             /* hi word of mpy/div reg       */
    unsigned long    lo;             /* lo word of mpy/div reg       */

    // The status register contains the interrupt-enable bit which needs
    // to be preserved across context switches.
    unsigned long    sr;             /* Status Reg                   */

    // These are only saved for exceptions and interrupts
    unsigned long    vector;         /* Vector number                */
    unsigned long    pc;             /* Program Counter              */

    // These are only saved for exceptions, and are not restored
    // when continued.
    unsigned long    cause;          /* Exception cause register     */
    unsigned long    badvr;          /* Bad virtual address reg      */

} MHAL_SavedRegisters;
#endif

#if defined (__arm__)
typedef void (*mhal_isr_t)(void);
#else
#if defined(MSOS_TYPE_NUTTX) 
typedef int (*mhal_isr_t)(int irq, void *context);
#else
typedef void (*mhal_isr_t)(MHAL_SavedRegisters *regs, MS_U32 vector);
#endif
#endif

MS_U32 MsOS_CPU_DisableInterrupt (void);

MS_BOOL MsOS_CPU_EnableInterrupt (void);

MS_BOOL MsOS_CPU_RestoreInterrupt (MS_U32 u32OldInterrupts);

MS_BOOL MsOS_CPU_MaskAllInterrupt (void);

MS_BOOL MsOS_CPU_MaskInterrupt (MHAL_INTERRUPT_TYPE intr_num);

MS_BOOL MsOS_CPU_UnMaskInterrupt (MHAL_INTERRUPT_TYPE intr_num);

MS_BOOL MsOS_CPU_LockInterrupt (void);

MS_BOOL MsOS_CPU_UnLockInterrupt (void);

MS_BOOL MsOS_CPU_AttachInterrupt (MHAL_INTERRUPT_TYPE intr_num, mhal_isr_t isr, MS_U32 dat);

MS_BOOL MsOS_CPU_DetachInterrupt (MHAL_INTERRUPT_TYPE intr_num);

MS_BOOL MsOS_CPU_AttachException (MHAL_EXCEPTION_TYPE expt_num, mhal_isr_t isr, MS_U32 dat);

MS_BOOL MsOS_CPU_DetachExceptiont (MHAL_EXCEPTION_TYPE expt_num);

MS_BOOL MsOS_CPU_SetEBASE (MS_U32 u32Addr);




//
// Cache Opertation
//
MS_BOOL MsOS_Dcache_Flush( MS_U32 u32Start , MS_U32 u32Size );

MS_BOOL MsOS_Dcache_Invalidate( MS_U32 u32Start , MS_U32 u32Size );

MS_BOOL MsOS_Dcache_Writeback( MS_U32 u32Start , MS_U32 u32Size );

#if defined(CHIP_T12) || defined(CHIP_T8) || defined(CHIP_J2) || defined(CHIP_A2) || defined(CHIP_A5) || defined(CHIP_A3) || defined(CHIP_Edison)
MS_BOOL MsOS_L2Cache_Flush(void);
MS_BOOL MsOS_L2Cache_Read(void);
#endif

//
// CPU relative Operation
//
void MsOS_Sync(void);

typedef enum //_MsOSMPool_DbgLevel
{
    E_MsOSMPool_DBG_Release = 0,
    E_MsOSMPool_DBG_L1, // display error msg
} MsOSMPool_DbgLevel;

// Kernel related information
MS_BOOL MDrv_SYS_Info(IO_Sys_Info_t* SysInfo);
// MPool Operation
void  MsOS_MPool_SetDbgLevel(MsOSMPool_DbgLevel DbgLevel);
MS_BOOL MsOS_MPool_Init(void);
MS_BOOL MsOS_MPool_Get(void** pAddrVirt, MS_U32* pu32AddrPhys, MS_U32* pu32Size, MS_BOOL bNonCache);
MS_BOOL MsOS_MPool_Close(void);
MS_U32 MsOS_MPool_VA2PA(MS_U32 pAddrVirt);
MS_U32 MsOS_MPool_PA2KSEG1(MS_U32 pAddrPhys);
MS_U32 MsOS_MPool_PA2KSEG0(MS_U32 pAddrPhys);
MS_BOOL MsOS_MPool_Dcache_Flush(MS_U32 pAddrVirt, MS_U32 u32Size); // the input address should be user mode cacheable address
MS_BOOL MsOS_MPool_Dcache_Flush_All(void);
MS_BOOL MsOS_MPool_Mapping(MS_U8 u8MiuSel, MS_U32 u32Offset, MS_U32 u32MapSize, MS_BOOL bNonCache);
MS_BOOL MsOS_MPool_Kernel_Detect(MS_U32 *lx_addr, MS_U32 *lx_size, MS_U32 *lx2_addr, MS_U32 *lx2_size);

#define MsOS_MPool_PA2VA MsOS_MPool_PA2KSEG1

MS_U32 MsOS_Mapping_SharedMem(MS_U32 u32ShmSize,MS_BOOL *bInit);

MS_S32 MsOS_CreateNamedMutex(MS_S8 *ps8MutexName);
MS_BOOL MsOS_LockMutex(MS_S32 u32Index,int flag);
MS_BOOL MsOS_UnlockMutex(MS_S32 u32Index,int flag);
MS_BOOL MsOS_DeleteNamedMutexbyIndex(MS_S32 u32Index);

// Share memory operation
#define MAX_CLIENT_NAME_LENGTH  50
#define MSOS_SHM_QUERY          0x00000000
#define MSOS_SHM_CREATE         0x00000001

MS_BOOL MsOS_SHM_Init(void);
MS_BOOL MsOS_SHM_GetId(MS_U8* pu8ClientName, MS_U32 u32BufSize, MS_U32* pu32ShmId, MS_U32* pu32Addr, MS_U32* pu32BufSize, MS_U32 u32Flag);
MS_BOOL MsOS_SHM_FreeId(MS_U8* pu8ClientName, MS_U32 u32ShmId);

//
// OS Dependent Macro
//

// Worldwide thread safe macro
// Usage:
//     MS_S32 os_X_MutexID;
//     os_X_MutexID = OS_CREATE_MUTEX(_M_);
//     if (os_X_MutexID < 0) {  return FALSE; }
//     if (OS_OBTAIN_MUTEX(os_X_MutexID, 1000) == FALSE) { return FALSE; }
//     ...
//     OS_RELEASE_MUTEX(os_X_MutexID);
//     return X;
//

#define OS_CREATE_MUTEX(_M_)        MsOS_CreateMutex(E_MSOS_FIFO, "OS_"#_M_"_Mutex", MSOS_PROCESS_SHARED)
#define OS_OBTAIN_MUTEX(_mx, _tm)   MsOS_ObtainMutex(_mx, _tm)
#define OS_RELEASE_MUTEX(_mx)       MsOS_ReleaseMutex(_mx)
#define OS_DELETE_MUTEX(_mx)        MsOS_DeleteMutex(_mx)
#define OS_DELAY_TASK(_msec)        MsOS_DelayTask(_msec)
#define OS_SYSTEM_TIME()            MsOS_GetSystemTime()
#define OS_ENTER_CRITICAL()         MsOS_DisableAllInterrupts();
#define OS_EXIT_CRITICAL()          MsOS_EnableAllInterrupts();

//-------------------------------------------------------------------------------------------------
// Virutal/Physial address operation
//-------------------------------------------------------------------------------------------------
MS_U32 MsOS_VA2PA(MS_U32 addr);
MS_U32 MsOS_PA2KSEG0(MS_U32 addr);
MS_U32 MsOS_PA2KSEG1(MS_U32 addr);
MS_U32 MsOS_PA2BA(MS_PHYADDR u32PhyAddr);
MS_PHYADDR MsOS_BA2PA(MS_U32 u32Addr);
void   MsOS_FlushMemory(void);
void   MsOS_ReadMemory(void);

#define MS_VA2PA(_addr_)                (MS_U32)MsOS_VA2PA((_addr_))
#define MS_PA2KSEG0(_addr_)             (MS_U32)MsOS_PA2KSEG0((_addr_))
#define MS_PA2KSEG1(_addr_)             (MS_U32)MsOS_PA2KSEG1((_addr_))

//-------------------------------------------------------------------------------------------------
// Debug message
//-------------------------------------------------------------------------------------------------
#define MS_CRITICAL_MSG(x)      x       // for dump critical message
#define MS_FATAL_MSG(fmt,...) printf( "[MS_FATAL]: %s: %d \n"  fmt, __FUNCTION__, __LINE__, ## __VA_ARGS__)


#if defined (MSOS_TYPE_LINUX_KERNEL)
  #define printf printk                 // utopia being a kernel driver should use printk
#endif

#if defined (MS_DEBUG)
  #define MS_DEBUG_MSG(x)       x
#elif defined (MS_OPTIMIZE)
  #define MS_DEBUG_MSG(x)               // retail version remove debug message
#endif

//-------------------------------------------------------------------------------------------------
// debug
//-------------------------------------------------------------------------------------------------
extern void MsOS_RegMyDbg(void);                                        ///< MsOS debug register itself debug

typedef MS_BOOL (*UartDbg_IP_CallBack) (int argc, char *argv[]);        ///< MsOS debug call back function prototype

///< define your own name, help, callback mapping here
typedef struct
{
    const char *Func_Name;
    const char *Func_Help;
    UartDbg_IP_CallBack pCallBack;
} MS_DBG_LINK;

///< for application to pass debug command into MsOS debug module
extern MS_BOOL MsOS_Dbg_ParseCmd(char *Cmd, MS_U32 u32CmdLen);

///< register your main menu here
extern MS_BOOL MsOS_Dbg_Regist(const char *Func_Name, const char *Func_Help, MS_DBG_LINK *pAryDbgLink);

///< for user to handle their own sub menu
extern MS_BOOL MsOS_Dbg_ExecuteSubCB(const char *Func_Name, int argc, char *argv[], MS_DBG_LINK *pAryDbgLink);

#ifdef __cplusplus
}
#endif

#endif // _MS_OS_H_
