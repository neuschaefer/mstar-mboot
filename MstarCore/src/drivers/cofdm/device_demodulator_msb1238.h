#if(FRONTEND_DEMOD_TYPE ==DEMOD_MSB1238)
#ifndef _MSB1238_H_
#define _MSB1238_H_

/* ------------------------------------
    Header Files
   ------------------------------------ */

#include "Board.h"
//#include "datatype.h"
#include "MsTypes.h"
#include "drvIIC.h"

/* ------------------------------------
    Macro Definitions
   ------------------------------------ */

#ifdef _MSB1238_C_
#define INTERFACE
#else
#define INTERFACE  extern
#endif

//typedef enum
//{
//  Samsung_ERR_NO = 0,
//  Samsung_ERR_I2C = 1,
//  Samsung_ERR_INIT = 2,
//  Samsung_ERR_UNLOCK = 4,
//  Samsung_ERR_PARAM = 8,
//  /* Invalid parameter check              */
//  Samsung_ERR_CHECK_FUNC = 16,
//  /* Error returned from LgdtCheck...()   */
//  Samsung_ERR_ALTER_FUNC = 32,
//  /* Error returned from LgdtAlter...()   */
//  Samsung_ERR_SPECTRUM = 64,
//  /* Spectrum status symptom shows when QAM mode  */
//  Samsung_ERR_OTHER = 128,
//  Samsung_ERR_TUNER = 256,
//  /* Reserved for a tuner manufacturer    */
//  Samsung_ERR_SCAN = 512
//}SamsungReturn_t;
//
typedef enum
{
    MSB1238_SIGNAL_NO                   = 0,    /* little or no input power detected    */
    MSB1238_SIGNAL_WEAK                 = 1,    /* some power detected.                 */
    MSB1238_SIGNAL_MODERATE             = 2,    /*  */
    MSB1238_SIGNAL_STRONG               = 4,    /*  */
    MSB1238_SIGNAL_VERY_STRONG        = 8       /*  */
}MSB1238SignalCondition_t;
/*------------------------------------------------------//
// TYPE Definition of MPEG Mode
//------------------------------------------------------*/
//typedef enum
//{
//  Samsung_PARAL = 0x00,
//  /* Samsung_PARAL Mode                   */
//  Samsung_SERIAL = 0x01               /* Samsung_SERIAL Mode                      */
//}SamsungMpegMode_t;
//typedef struct
//{
//  MS_U8 Reg;
//  MS_U16 Value;
//} SamsungChipInit_t;

#define VSB_1238 0x04
#define QAM256_1238  0x02
#define VSB 1
#define QAM64 2
#define QAM256 4
#define VSB_SIGNAL_DISTANCE 5
#define QAM_SIGNAL_DISTANCE 5

INTERFACE MS_BOOL MSB1238_Init(void);
INTERFACE MS_BOOL MSB1238_Download(MS_U8* MSB1238_Download_Address, MS_U16 MSB1238_Download_Size, MS_U8* MSB1238_Download_Table);
INTERFACE MS_BOOL MSB1238_ReadReg(MS_U16 u16Addr, MS_U8* u8Data);
INTERFACE MS_BOOL MSB1238_WriteReg(MS_U16 u16Addr, MS_U8 u8Data);
INTERFACE MS_BOOL MSB1238_RepeaterEnable(void);
INTERFACE MS_BOOL MSB1238_RepeaterDisable(void);
INTERFACE MS_BOOL MSB1238_SoftReset(void);
INTERFACE MS_BOOL MSB1238_VsbMode(void);
INTERFACE MS_BOOL MSB1238_64QamMode(void);
INTERFACE MS_BOOL MSB1238_256QamMode(void);
INTERFACE MS_BOOL MSB1238_Vsb_PreLock(void);
INTERFACE MS_BOOL MSB1238_Vsb_QAM_AGCLock(void);
INTERFACE MS_BOOL MSB1238_QAM_PreLock(void);
INTERFACE MS_BOOL MSB1238_QAM_Main_Lock(void);
INTERFACE MS_BOOL MSB1238_Vsb_CE_Lock(void);
INTERFACE MS_BOOL MSB1238_Vsb_FEC_Lock(void);
INTERFACE void MSB1238_CheckSignalCondition(MSB1238SignalCondition_t* pstatus);
INTERFACE MS_BOOL MSB1238_QAMCheckLock(void);
INTERFACE MS_U8  MSB1238_Check8VSB64_256QAM(void);
INTERFACE MS_U8 MSB1238_ReadSNRPercentage(void);
INTERFACE MS_S16 MSB1238_ReadFrequencyOffset(void);
INTERFACE void MSB1238_FWVERSION(void);
INTERFACE MS_BOOL MSB1238_VSBCheckLock(void);
void MDrv_Demod_1238_SetMode(MS_U8 u8demod_type);
MS_U8 MDrv_Demod_1238_GetMode(void);
//INTERFACE void MSB1238_FWVERSION(void);
#undef INTERFACE
#endif
#endif

