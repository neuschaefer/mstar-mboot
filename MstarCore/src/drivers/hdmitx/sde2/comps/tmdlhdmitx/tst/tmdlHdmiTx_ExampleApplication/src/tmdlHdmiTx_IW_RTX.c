/*
 * Copyright (C) 2007 NXP N.V., All Rights Reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of NXP N.V. and is confidential in nature. Under no circumstances
 * is this software to be  exposed to or placed under an Open Source License of
 * any type without the expressed written permission of NXP N.V.
 *
 * \file          tmdlHdmiRxCfg.c
 *
 * \version       $Revision: 1 $
 *
 * \date          $Date: 06/02/07 8:32 $
 *
 * \brief         devlib driver component API for the TDA997x HDMI Receivers
 *                  Configuration module
 * \section refs  Reference Documents
 * TDA997X Driver - FRS.doc,
 * TDA997X Driver - tmdlHdmiRx - SCS.doc
 *
 * \section info  Change Information
 *
 * \verbatim

   $History: tmdlHdmiRxCfg.c $
 *
 * *****************  Version 1  *****************
 * User: Latapie     Date: 06/02/07   Time: 8:32
 * Updated in $/Source/tmdlHdmiRx/inc
 * initial version
 *

   \endverbatim
 *
*/


/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

/* Include function declaration and types for RTX */
//#include <LPC214x.H>

#ifndef TMFL_NO_RTOS
//#include "RTL.h"
#endif /* TMFL_NO_RTOS */

#include "hdmitx/sde2/inc/tmNxTypes.h"
#include "hdmitx/sde2/inc/tmNxCompId.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/inc/tmdlHdmiTx_Types.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/cfg/tmdlHdmiTx_cfg.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/cfg/tmdlHdmiTx_IW.h"

#include "hdmitx/sde2/inc/M_supply_type.h"
#ifndef TMFL_NO_RTOS
#include <deque>
#include <sys/sem.h>
#endif
#include "stdio.h"
#ifdef __cplusplus
extern "C" {
#endif

    /*============================================================================*/
    /*                       DEFINES                                              */
    /*============================================================================*/

    /* maximum number of tasks that can be handled by the wrapper */
#define MAX_TASKS  6
    /* maximum number of message queues that can be handled by the wrapper */
#define MAX_QUEUES 6
    /* maximum number of message queues that can be handled by the wrapper */
#define MAX_SEMA   8

    /* macro for quick error handling */
#define RETIF(cond, rslt)       if ((cond)){HDMI_TRACE("RERIF") return (rslt);}



    /*============================================================================*/
    /*                       FUNCTION PROTOTYPES                                  */
    /*============================================================================*/

    /*============================================================================*/
    /*                       VARIABLES                                            */
    /*============================================================================*/

#ifndef TMFL_NO_RTOS

    /* table storing all tasks descriptions */
    iwTcb_t taskTable[MAX_TASKS] =
    {
        {False, False, 0, 0, 0, Null},
        {False, False, 0, 0, 0, Null},
        {False, False, 0, 0, 0, Null},
        {False, False, 0, 0, 0, Null},
        {False, False, 0, 0, 0, Null},
        {False, False, 0, 0, 0, Null}
    };



    /* table storing all message queues descriptions */
    iwQueue_t queueTable[MAX_QUEUES] =
    {
        {False, 0, NULL},// mpool0},
        {False, 0, NULL},// mpool1},
        {False, 0, NULL},// mpool2},
        {False, 0, NULL},// mpool3},
        {False, 0, NULL},// mpool4}
    };


    /* table storing all message queues descriptions */
    iwSem_t semTable[MAX_SEMA] =
    {
        {False,},
        {False,},
        {False,},
        {False,},
        {False,},
        {False,},
        {False,},
        {False,}
    };

#endif /* TMFL_NO_RTOS */
    /*============================================================================*/
    /*                       FUNCTION                                                */
    /*============================================================================*/

    /**
        \brief This function creates a task and allocates all the necessary resources. Note that creating a task do not start it automatically, an explicit call to IWTaskStart must be made.
    Parameters:

        \param pSWVersion    Pointer to the version structure
        \param pFunc        Pointer to the function that will be executed in the task context.
        \param Priority        Priority of the task. The minimum priority is 0, the maximum is 255.
        \param StackSize    Size of the stack to allocate for this task.
        \param pHandle        Pointer to the handle buffer.

        \return The call result:
                - TM_OK        If call is successful.
                - TM_NOK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWTaskCreate(tmdlHdmiTxIWFuncPtr_t     pFunc,
                                         UInt8           Priority,
                                         UInt16          StackSize,
                                         tmdlHdmiTxIWTaskHandle_t *pHandle)
    {
#ifndef TMFL_NO_RTOS
        UInt32 i;

        /* search for available task slot */
        for(i = 0; i < MAX_TASKS; i++)
        {
            if (taskTable[i].created == False)
                break;

        }
        if(i >= MAX_TASKS) return(TM_ERR_NO_RESOURCES);

        /* store task parameters into the dedicated structure */
        taskTable[i].priority = Priority;
        taskTable[i].stackSize = StackSize;
        taskTable[i].associatedTask = pFunc;
        taskTable[i].created = True;

        *pHandle = (tmdlHdmiTxIWTaskHandle_t)i;

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief    This function destroys an existing task and frees resources used by it.

        \param Handle        Handle of the task to be destroyed, as returned by TxIWTaskCreate.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWTaskDestroy(tmdlHdmiTxIWTaskHandle_t Handle)
    {
#ifndef TMFL_NO_RTOS
        if (taskTable[Handle].started == True)
        {
            if (os_tsk_delete(taskTable+Handle) == OS_R_OK)
            {
                taskTable[Handle].started = False;
            }
            else
            {
                return ~TM_OK;
            }
        }
        taskTable[Handle].created = False;

#endif /* TMFL_NO_RTOS */
        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function start an existing task.

        \param Handle        Handle of the task to be started.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWTaskStart(tmdlHdmiTxIWTaskHandle_t Handle)
    {
#ifndef TMFL_NO_RTOS
        thread_H threadHandle;

        /* check if task is already started */
        if (taskTable[Handle].started == True)
            return(TM_ERR_ALREADY_STARTED);

        /* start thread associated to the task */
        threadHandle = os_tsk_create(taskTable+Handle);

        /* check return code for errors */
        if (threadHandle)
        {
            return(TM_ERR_NOT_STARTED);
        }

        /* update task status */
        taskTable[Handle].threadHandle = threadHandle;
        taskTable[Handle].started = True;

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function blocks the current task for the specified amount time. This is a passive wait.

        \param Duration    Duration of the task blocking in milliseconds.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWWait(UInt16 Duration)
    {
#ifndef TMFL_NO_RTOS
        //TODO perform conversion with Tick system in order to consider ms
        os_dly_wait(Duration);
#else
	extern void udelay(unsigned long usec);
	udelay(Duration*1000);
#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function creates a message queue.

        \param QueueSize    Maximum number of messages in the message queue.
        \param pHandle        Pointer to the handle buffer.
        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWQueueCreate(UInt8 QueueSize, tmdlHdmiTxIWQueueHandle_t *pHandle)
    {
#ifndef TMFL_NO_RTOS
        UInt8 i;

        if (QueueSize > Queue_default_Size) return TM_ERR_BAD_PARAMETER;


        /* search for available queue slot */
        for(i = 0; i < MAX_QUEUES; i++)
        {
            if (queueTable[i].created == False)
            {
                break;
            }
        }
        if(i >= MAX_QUEUES) return(TM_ERR_NO_RESOURCES);

        *pHandle = i;

        /* Initialisation of queue object */
        //TODO check if we can reuse deleted queue
        // _init_box (queueTable[i].mpool, sizeof(mpool0),sizeof(UInt8));
        //os_mbx_init(queueTable[i].mbox, QueueSize);
        queueTable[i].mbox = new deque<UInt8>(1);

        if(queueTable[i].mbox==NULL)
        {
            HDMI_TRACE("queue[%d] create fail",i);
            return TM_FAIL;
        }
        HDMI_TRACE("queue[%d] created size:%d",i,QueueSize);
        /* update status of the queue table */
        queueTable[i].created = True;
        queueTable[i].queueSize = QueueSize;

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function destroys an existing message queue.

        \param    Handle        Handle of the queue to be destroyed.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWQueueDestroy(tmdlHdmiTxIWQueueHandle_t Handle)
    {
#ifndef TMFL_NO_RTOS
        UInt8 msg=0;

        RETIF(Handle > MAX_QUEUES, TM_ERR_BAD_HANDLE);
        RETIF(queueTable[Handle].created == False, TM_ERR_BAD_HANDLE);

        queueTable[Handle].created = False;


        while(os_mbx_check(queueTable[Handle].mbox) != queueTable[Handle].queueSize)
        {
            RETIF(os_mbx_wait(queueTable[Handle].mbox,(void *)&msg, 10) == OS_R_TMO, TM_ERR_TIMEOUT);
        }

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function sends a message into the specified message queue.

        \param Handle    Handle of the queue that will receive the message.
                        Message    Message to be sent.
        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWQueueSend(tmdlHdmiTxIWQueueHandle_t Handle, UInt8 Message)
    {
#ifndef TMFL_NO_RTOS
        UInt8  msg;

        /* check that handle is correct */
        RETIF(Handle > MAX_QUEUES, TM_ERR_BAD_HANDLE);
        RETIF(queueTable[Handle].created != True, TM_ERR_BAD_HANDLE);

        //msg = _alloc_box (queueTable[Handle].mpool);

        msg = Message;

//        if(os_mbx_check(queueTable[Handle].mbox) != 0)
        //  {
        RETIF(os_mbx_send(queueTable[Handle].mbox, &msg, 0xffff) == OS_R_TMO, TM_ERR_TIMEOUT);
        //   }
        //   else
        //   {
        //       return TM_ERR_FULL;
        //   }

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }
    /*============================================================================*/

    /**
        \brief This function reads a message from the specified message queue.

        \param    Handle        Handle of the queue from which to read the message.
                pMessage    Pointer to the message buffer.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWQueueReceive(tmdlHdmiTxIWQueueHandle_t Handle, UInt8 *pMessage)
    {
#ifndef TMFL_NO_RTOS
        UInt8  msg=0;
        /* check that handle is correct */
        RETIF(Handle > MAX_QUEUES, TM_ERR_BAD_HANDLE);
        RETIF(queueTable[Handle].created != True, TM_ERR_BAD_HANDLE);

        /* if we reach this point, this means that we got a message */
        /* ask for exclusive access to this queue */
        RETIF(os_mbx_wait(queueTable[Handle].mbox , (void *)&msg, 0xffff) == OS_R_TMO, TM_ERR_TIMEOUT);

        if (pMessage)
        {
            *pMessage = msg;
        }

        //_free_box (queueTable[Handle].mpool, msg);

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function creates a semaphore.

        \param     pHandle    Pointer to the handle buffer.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.
    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWSemaphoreCreate(tmdlHdmiTxIWSemHandle_t *pHandle)
    {
#ifndef TMFL_NO_RTOS
        UInt8 i;

        /* search for available queue slot */
        for(i = 0; i < MAX_SEMA; i++)
        {
            if (semTable[i].created == False)
                break;

        }
        if(i >= MAX_SEMA) return(TM_ERR_NO_RESOURCES);



        os_sem_init(&semTable[i].handle, 1);

        *pHandle = (tmdlHdmiTxIWSemHandle_t) i;

        semTable[i].created = True;

#endif /* TMFL_NO_RTOS */
        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function destroys an existing semaphore.

        \param    Handle        Handle of the semaphore to be destroyed.

        \return The call result:
                - TM_OK     If call is successful.
                - ~TM_OK If call failed.
    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWSemaphoreDestroy(tmdlHdmiTxIWSemHandle_t Handle)
    {
#ifndef TMFL_NO_RTOS
        UInt8  i;

        for(i=0; i<MAX_SEMA; i++)
        {
            if(i ==  Handle)
            {
                break;
            }
        }
        if(i >= MAX_SEMA) return(TM_ERR_NO_RESOURCES);
        os_sem_destroy(&semTable[i].handle);
        semTable[i].created = False;

#endif /* TMFL_NO_RTOS */

        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function acquires the specified semaphore.

        \param Handle        Handle of the semaphore to be acquired.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWSemaphoreP(tmdlHdmiTxIWSemHandle_t Handle)
    {
#ifndef TMFL_NO_RTOS
        if (semTable[Handle].created==False) return TM_ERR_BAD_HANDLE;
        //block way?
        RETIF(os_sem_wait(&semTable[Handle].handle, 0xffff) == OS_R_TMO, TM_ERR_TIMEOUT);

#endif /* TMFL_NO_RTOS */
        return(TM_OK);
    }

    /*============================================================================*/

    /**
        \brief This function releases the specified semaphore.

        \param    Handle        Handle of the semaphore to be released.

        \return The call result:
                - TM_OK    If call is successful.
                - ~TM_OK    If call failed.

    ******************************************************************************/
    tmErrorCode_t tmdlHdmiTxIWSemaphoreV(tmdlHdmiTxIWSemHandle_t Handle)
    {
#ifndef TMFL_NO_RTOS
        if (semTable[Handle].created==False) return TM_ERR_BAD_HANDLE;

        RETIF(os_sem_send(&semTable[Handle].handle) == OS_R_NOK, TM_ERR_BAD_HANDLE);
#endif /* TMFL_NO_RTOS */
        return(TM_OK);
    }

    /******************************************************************************
        \brief  This function disables the interrupts for a specific device.

        \param

        \return The call result:
                - TM_OK: the call was successful

    ******************************************************************************/
    void tmdlHdmiTxIWDisableInterrupts(tmdlHdmiIWDeviceInterrupt_t device)
    {
    }

    /******************************************************************************
        \brief  This function enables the interrupts for a specific device.

        \param

        \return The call result:
                - TM_OK: the call was successful

    ******************************************************************************/
    void tmdlHdmiTxIWEnableInterrupts(tmdlHdmiIWDeviceInterrupt_t device)
    {
    }

#ifdef __cplusplus
}
#endif

/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/



