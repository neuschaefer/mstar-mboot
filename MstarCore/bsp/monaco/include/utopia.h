#ifndef MSOS_TYPE_LINUX_KERNEL
#include "stdlib.h"
#endif
#include "MsTypes.h"
#include "utopia_driver_id.h"

#ifndef _UTOPIA_H_
#define _UTOPIA_H_

#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************
Status define rule:
0xMMRRRRSS  //M:Module, R:Reserve(please keep 0), S:Status code
MM = 0 for common status.
MM = 1 for Utopia Framwork and Utopia module

Will support GetErrorStr(Status, *str);
*******************************************************************************/
#define UTOPIA_STATUS_SUCCESS               0x00000000
#define UTOPIA_STATUS_FAIL                  0x00000001
#define UTOPIA_STATUS_NOT_SUPPORTED         0x00000002
#define UTOPIA_STATUS_PARAMETER_ERROR       0x00000003
#define UTOPIA_STATUS_DONT_CARE             0x00000004
#define UTOPIA_STATUS_ERR_SYS               0x00000005       ///< operating system call failure
#define UTOPIA_STATUS_ERR_INV               0x00000006       ///< invalid argument passed
#define UTOPIA_STATUS_ERR_TIMEDOUT          0x00000007       ///< timeout occured
#define UTOPIA_STATUS_ERR_DEFERRED          0x00000008       ///< action has been deferred
#define UTOPIA_STATUS_ERR_UNIMPLEM          0x00000009       ///< Unimplemented service
#define UTOPIA_STATUS_ERR_LOCKED            0x00000010       ///< object locked
#define UTOPIA_STATUS_ERR_DELETED           0x00000011       ///< Object has been deleted
#define UTOPIA_STATUS_ERR_HEAP              0x00000012       ///< Heap full
#define UTOPIA_STATUS_ERR_UNINIT            0x00000013       ///< module is not initialised
#define UTOPIA_STATUS_ERR_UNIQUE            0x00000014       ///< unique id needed
#define UTOPIA_STATUS_ERR_STATE             0x00000015       ///< invalid state to invoke function
#define UTOPIA_STATUS_ERR_DEV               0x00000016       ///< no valid device exists
#define UTOPIA_STATUS_ERR_NOT_FOUND         0x00000017       ///< Not found
#define UTOPIA_STATUS_ERR_EOL               0x00000018       ///< a list traversal has ended
#define UTOPIA_STATUS_ERR_TERM              0x00000019       ///< module has terminated
#define UTOPIA_STATUS_ERR_LIMIT             0x00000020       ///< System limit was reached.
#define UTOPIA_STATUS_ERR_RESOURCE          0x00000021       ///< insufficient resources for request
#define UTOPIA_STATUS_ERR_NOT_AVAIL         0x00000022       ///< resources not available
#define UTOPIA_STATUS_ERR_BAD_DATA          0x00000023       ///< Bad data in transport stream
#define UTOPIA_STATUS_ERR_INLINE_SUCCESS    0x00000024
#define UTOPIA_STATUS_ERR_DEFERRED_SUCCESS  0x00000025
#define UTOPIA_STATUS_ERR_IN_USE            0x00000026       ///< Object is in use.
#define UTOPIA_STATUS_ERR_INTERMEDIATE      0x00000027       ///< Intermediate return 0x0000000 successful but not complete
#define UTOPIA_STATUS_ERR_OVERRUN           0x00000028       ///< Buffer overrun occured (e.g. in filters).
#define UTOPIA_STATUS_ERR_ABORT             0x00000029       ///< Request not supported.
#define UTOPIA_STATUS_ERR_NOTIMPLEMENTED    0x00000030       ///< Request not implemented.
#define UTOPIA_STATUS_ERR_INVALID_HANDLE    0x00000031
#define UTOPIA_STATUS_ERR_NOMEM             0x00000032       ///< No Memory
#define UTOPIA_STATUS_SHM_EXIST             0x00000033       ///< target share memory already exists
#define UTOPIA_STATUS_RPOOL_ESTABLISHED     0x00000034       ///< target resource pool is already established
#define UTOPIA_STATUS_NO_RESOURCE           0x00000035       ///< try to obtain resource but fail
#define UTOPIA_STATUS_ERR_USER              0x00000099       ///< start of subsystem specific errors

#define MS_MODULE_NULL 0
//#define MS_MODULE_UTOPIA 0xFFFF0000
#define MS_UTOPIA_DB_LEVEL_TRACE 0x80000000

#define utopia_malloc malloc
#define utopia_free free

#if defined(MSOS_TYPE_LINUX_KERNEL)
#define free kfree
#define malloc(size) kmalloc((size), GFP_KERNEL)
#endif

#define KERNEL_MODE 0x80000000

#define UTOPIA_IOC_MAGIC  'U'
#define UTOPIA_IOCTL_SetMODULE   _IOWR(UTOPIA_IOC_MAGIC, 1, int)
#define UTOPIA_IOCTL_OpenMODULE  _IOWR(UTOPIA_IOC_MAGIC, 2, int)
#define UTOPIA_IOCTL_IoctlMODULE  _IOWR(UTOPIA_IOC_MAGIC, 3, int)
#define UTOPIA_IOCTL_CloseMODULE  _IOWR(UTOPIA_IOC_MAGIC, 4, int)

#define UTOPIA_IOCTL_MODULE_DYNAMIC_MAPPING  _IOWR(UTOPIA_IOC_MAGIC, 5,KDrvMPool_Info_t)


MS_U32 UtopiaInit(void);
#ifdef CONFIG_MBOOT
MS_U32 UtopiaInit_str(void);
#endif
MS_U32 UtopiaOpen(MS_U32 u32ModuleID, void** pInstant, MS_U32 u32ModuleVersion, const void* const pAttribte);
MS_U32 UtopiaIoctl(void* pInstant, MS_U32 u32Cmd, void* const pArgs);
MS_U32 UtopiaClose(void* pInstant);

#ifdef __cplusplus
}
#endif

#endif
