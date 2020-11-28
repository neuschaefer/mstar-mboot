#ifndef M_supply_type_h
#define M_supply_type_h
#include <stdio.h>
#include "MsTypes.h"

#define TMFL_TDA19988  1
#define TMFL_NO_RTOS  1
#define TMFL_CEC_AVAILABLE  1
#define HDMI_TDA19989_ENABLE 1

#define dbg_switch 0
#define HDMI_TRACE(fmt,args...)  {printf("##HDMI##      "fmt"  [%s] [%d]\n",##args,__FUNCTION__,__LINE__);}							
#ifndef  FUNC_PTR
#define FUNC_PTR
#endif
#ifndef RAM_DAT
#define RAM_DAT
#endif
#ifndef CONST_DAT
#define CONST_DAT const
#endif

#define OS_R_OK 0
#define OS_R_TMO -2
#define OS_R_NOK -1

#ifndef TMFL_NO_RTOS
typedef sem_t  OS_SEM;
typedef pthread_t thread_H;
typedef int HANDLE;
#endif


#endif
