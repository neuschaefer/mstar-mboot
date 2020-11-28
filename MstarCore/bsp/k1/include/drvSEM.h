#ifndef __DRV_SEM_H__
#define __DRV_SEM_H__

#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define SEM_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    {'S','E','M','_'},                  /* IP__                                             */  \
    {'0','1'},                          /* 0.0 ~ Z.Z                                        */  \
    {'0','1'},                          /* 00 ~ 99                                          */  \
    {'0','0','2','6','4','8','8','5'},  /* CL#                                              */  \
    MSIF_OS

MS_BOOL MDrv_SEM_Init(void);
MS_BOOL MDrv_SEM_Get_Resource(MS_U8 u8SemID, MS_U16 u16ResId);
MS_BOOL MDrv_SEM_Free_Resource(MS_U8 u8SemID, MS_U16 u16ResId);
MS_BOOL MDrv_SEM_Reset_Resource(MS_U8 u8SemID);
MS_BOOL MDrv_SEM_Get_ResourceID(MS_U8 u8SemID, MS_U16* pu16ResId);
MS_U32 MDrv_SEM_Get_Num(void);
MS_BOOL MDrv_SEM_GetLibVer(const MSIF_Version **ppVersion);

//==============================================================================
// Semaphore Usage in Utopia
// #1 - GE
// #2 - GE
// #3 -
// #4 - 
// #5 -
// #6 - PM
// #7 - BDMA (optional by "BDMA_USE_HW_SEM" definitioin
//==============================================================================

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif // #ifndef __DRV_SEM_H__
