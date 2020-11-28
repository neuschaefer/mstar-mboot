#ifndef M_supply_h
#define M_supply_h
#include "hdmitx/sde2/inc/M_supply_type.h"
//--------------------------NXP Driver head file-----------------------//
#include "hdmitx/sde2/comps/tmbslhdmitx/inc/tmbslHdmiTx_types.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/cfg/tmdlHdmiTx_IW.h"
//-----------------------------------------------------------------//

///-------------------------Functions  for NXP TD9989 HDMI TX ------------------------//
//--------------------------             declearation              --------------------------//
 int hdmi_test(void);
 tmErrorCode_t i2cWrite(int reg , tmbslHdmiTxSysArgs_t *pSysArgs); 
 tmErrorCode_t i2cRead(int reg , tmbslHdmiTxSysArgs_t *pSysArgs); 
 int msHdmitx_Init(void);
/* This function is used to poll regularly the HMI TX driver in order to get
   HDMI TX interrupt registers status */
 void  msHdmitx_Poll(void);
MS_BOOL M_HDMI_GetRestoreResolution(tmdlHdmiTxVideoInConfig_t* in,tmdlHdmiTxVideoOutConfig_t* out);


///------------------------------------------------------------------------------//



#endif
