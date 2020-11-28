////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Tuner.h
/// MStar Application Interface for Tuner
/// @brief API for tuner settings
/// @author MStar Semiconductor, Inc.
//
// Tuner settings differ from front end suppliers. Please check front end type define
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_TUNER_C

/******************************************************************************/
/*                    Header Files                                            */
/******************************************************************************/
#include <common.h>
#include <command.h>
#include <MsTypes.h>
#include <cofdm/COFDM_Demodulator.h>
#include <msAPI_Tuner.h>
#if ((MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225)|| \
       (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225) )
#include <drvSYS.h>
#endif

#if 1//((CONFIG_COMMANDS&(CFG_CMD_TUNER | CFG_CMD_DEMOD)) == (CFG_CMD_TUNER | CFG_CMD_DEMOD))

#ifndef UNUSED
#define UNUSED(x) ((x)=(x))
#endif

#if ENABLE_SCAN_ONELINE_MSG
#define TUNER_API_DBG_ONELINE(y)       y
#else
#define TUNER_API_DBG_ONELINE(y)
#endif


#define TUNER_API_DBG(y)        //y
#define NEW_SCAN_API_DBG(y)     //y

#define SCAN_DEBUG_CH       0x01
#define SCAN_DEBUG_PAL      0x02
#define SCAN_DEBUG_DVB      0x04

#define SCAN_DEBUG          0x00
#define SCAN_DBG(flag,s)    if (SCAN_DEBUG & flag) { s; }


static EN_DVB_TYPE _bDvbType=EN_DVB_T_TYPE;
/******************************************************************************/
/*                     Local                                                  */
/******************************************************************************/
static MS_TP_SETTING stCurrentTPSetting;    // current setting of front end
static EN_VSB_CHECK_LOCK_STATE enVSBCheckLockState = STATE_VSB_CHECK_INIT;
static EN_VSB_CHECK_STABLE_STATE enVSBCheckStableState = STATE_VSB_STABLE_INIT;
static BOOLEAN _bTSParallelMode=FALSE;
static BOOLEAN _bTSByPassMode=FALSE;
//static U32 u32CheckLock_Timer;              // ms

/******************************************************************************/
/*                   Functions                                                */
/******************************************************************************/
//extern void msAPI_Timer_Delayms(unsigned long u32DelayTime); //unit = ms

/******************************************************************************/
/// API for lnitialize current TP setting::
/******************************************************************************/
void msAPI_Tuner_InintCurrentTPSetting(void)
{
    memset(&stCurrentTPSetting, 0, sizeof(stCurrentTPSetting));
}

/******************************************************************************/
/// API for lnitialize tuner::
/******************************************************************************/
void msAPI_Tuner_Initialization(BOOLEAN bSrcChg)
{
    msAPI_Tuner_InintCurrentTPSetting();
#if ((MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225)|| \
      (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225) )
    MDrv_SYS_Init();
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_PARALLEL_IN);
#endif
    if(bSrcChg)
    {
#if 0 //DVB_C_ENABLE
    #if ENABLE_T_C_COMBO
        if(!IsCATVInUse())
        {
        #if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
            DTV_SECOND_TS_ON();
            DTV_IF_AGC_SEL_T();
            msAPI_Tuner_SetAntenna(0);
        #endif
            devCOFDM_Init();
        }
        else
    #endif
        {
        #if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
            DTV_SECOND_TS_OFF();
            DTV_IF_AGC_SEL_C();
            msAPI_Tuner_SetAntenna(1);
        #endif
            devQAM_Init();
        }
#else
        devCOFDM_Init();
#endif
    }

}

/******************************************************************************/
/// API for lnitialize tuner::
/******************************************************************************/
void msAPI_Tuner_InitExternDemod(void)
{
#if ( (FRONTEND_DEMOD_TYPE != EMBEDDED_DVBT_DEMOD) && (FRONTEND_DEMOD_TYPE != EMBEDDED_DVBC_DEMOD) )
    devCOFDM_Init();
#endif
}

/******************************************************************************/
/// API for Set RF channel::
/// Set RF channel related parameters, such as RF frequency, modulation type
/// @param pstTPSetting \b IN pointer to RF channel information structure
/******************************************************************************/
void msAPI_Tuner_Tune2RfCh(MS_TP_SETTING *pstTPSetting)
{
#if TS_FROM_PLAYCARD
    return;
#endif

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD)
msAPI_Tuner_Serial_Control(TRUE);
devCOFDM_SetDemodType(devCOFDM_GetDemodType());
#endif

#if DVB_C_ENABLE
    #if ENABLE_T_C_COMBO
        if(!IsCATVInUse())
        {
            if ((pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency) ||
                (pstTPSetting->enBandWidth != stCurrentTPSetting.enBandWidth) ||
                (pstTPSetting->u8HpLp != stCurrentTPSetting.u8HpLp)||
                (pstTPSetting->u8PLPID!= stCurrentTPSetting.u8PLPID))
            {
                devCOFDM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->enBandWidth,
                    pstTPSetting->u8HpLp?E_RF_CH_LP:E_RF_CH_HP,pstTPSetting->u8PLPID);
                stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
                stCurrentTPSetting.enBandWidth = pstTPSetting->enBandWidth;
                stCurrentTPSetting.u8HpLp = pstTPSetting->u8HpLp;
                stCurrentTPSetting.u8PLPID = pstTPSetting->u8PLPID;

            }
        }
        else
    #endif
        {
            if ( (pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency ||
                pstTPSetting->u32Symbol_rate != stCurrentTPSetting.u32Symbol_rate ||
                pstTPSetting->u8Modulation != stCurrentTPSetting.u8Modulation))
            {
                devQAM_SetAutoMode((U8)pstTPSetting->bAutoSRFlag, (U8)pstTPSetting->bAutoQamFlag);
                devQAM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->u8Modulation,pstTPSetting->u32Symbol_rate,TRUE);
                stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
                stCurrentTPSetting.u32Symbol_rate = pstTPSetting->u32Symbol_rate;
                stCurrentTPSetting.u8Modulation = pstTPSetting->u8Modulation;
            }
        }
#else
    if ((pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency) ||
        (pstTPSetting->enBandWidth != stCurrentTPSetting.enBandWidth) ||
        (pstTPSetting->u8HpLp != stCurrentTPSetting.u8HpLp) ||
        (pstTPSetting->u8PLPID!= stCurrentTPSetting.u8PLPID))
    {
        devCOFDM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->enBandWidth,
                    pstTPSetting->u8HpLp?E_RF_CH_LP:E_RF_CH_HP,pstTPSetting->u8PLPID);
        stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
        stCurrentTPSetting.enBandWidth = pstTPSetting->enBandWidth;
        stCurrentTPSetting.u8HpLp = pstTPSetting->u8HpLp;
        stCurrentTPSetting.u8PLPID = pstTPSetting->u8PLPID;
    }
  #endif
}

/******************************************************************************/
/// API for Check is same RF channel::
/// @param pstTPSetting \b IN pointer to RF channel information structure
/// @return same RF or not
/******************************************************************************/
BOOLEAN msAPI_Tuner_IsSameRfChannel(MS_TP_SETTING *pstTPSetting)
{
    if ( pstTPSetting->u32Frequency == stCurrentTPSetting.u32Frequency )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************/
/// API for power on off front end::
/// @param bPower \b IN power on or off
/******************************************************************************/
void msAPI_Tuner_PowerOnOff(BOOLEAN bPower)
{
#if ENABLE_T_C_COMBO
    if((msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE) )
    {
        devQAM_ControlPowerOnOff(bPower);
    }
    else
    {
        devCOFDM_ControlPowerOnOff(bPower);
    }
#elif DVB_C_ENABLE

    devQAM_ControlPowerOnOff(bPower);

#else

    devCOFDM_ControlPowerOnOff(bPower);

#endif
}

U8 msAPI_Tuner_GetSignalSNRValue(void)
{
#if ENABLE_T_C_COMBO
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? (U8)devQAM_GetSignalToNoiseRatio() : (U8)devCOFDM_GetSignalToNoiseRatio();
#elif DVB_C_ENABLE
    return (U8)devQAM_GetSignalToNoiseRatio();
#else
    return (U8)devCOFDM_GetSignalToNoiseRatio();
#endif
}

U8 msAPI_Tuner_GetSingalSNRPercentage(void)
{
    U16 temp;
#if ENABLE_T_C_COMBO
    temp = (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? devQAM_GetSignalToNoiseRatio() : devCOFDM_GetSignalToNoiseRatio();
#elif DVB_C_ENABLE
    temp = devQAM_GetSignalToNoiseRatio();
#else
    temp = devCOFDM_GetSignalToNoiseRatio();
#endif

    if ( temp >= 35 )
    {
        return 100;
    }
    else
    {
        return (U8)(temp*100/35);
    }
}

MS_U16 msAPI_Tuner_GetSignalQualityPercentage(void)
{
    MS_U16 wPercentage = 0;

#if TS_FROM_PLAYCARD
    wPercentage = 80;
    return wPercentage;
#endif

#if ENABLE_T_C_COMBO
    if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
    {
        devQAM_GetSignalQuality(&wPercentage);
    }
    else
    {
        devCOFDM_GetSignalQuality(&wPercentage);
    }
#elif DVB_C_ENABLE
    devQAM_GetSignalQuality(&wPercentage);
#else
    devCOFDM_GetSignalQuality(&wPercentage);
#endif
    return wPercentage;
}

BOOLEAN msAPI_Tuner_GetBER(float *ber)
{
#if ENABLE_T_C_COMBO
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? TRUE : devCOFDM_GetBER(ber);
#elif DVB_C_ENABLE
    UNUSED(ber);
    return TRUE;
#else
    return devCOFDM_GetBER(ber);
#endif
}

BOOLEAN msAPI_Tuner_Get_CELL_ID( MS_U16 * cell_id)
{
    BOOLEAN eResult;
#if ENABLE_T_C_COMBO
    *cell_id = 0;
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? TRUE : devCOFDM_Get_CELL_ID(cell_id);
#elif DVB_C_ENABLE
    * cell_id = 0;
    eResult = TRUE;
#else
    eResult = devCOFDM_Get_CELL_ID(cell_id);
#endif

    return eResult;
}

BOOLEAN msAPI_Tuner_Get_PLP_ID( U8  * pu8plp_id)
{
    *pu8plp_id=stCurrentTPSetting.u8PLPID;
    return TRUE;
}
U8 msAPI_Tuner_Get_HpLp( void)
{
    return stCurrentTPSetting.u8HpLp;
}


BOOLEAN msAPI_Tuner_Is_HierarchyOn(void)
{
#if ENABLE_T_C_COMBO
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? FALSE : devCOFDM_Is_Hierarchy_On();
#elif DVB_C_ENABLE
    return FALSE;
#else

    return devCOFDM_Is_Hierarchy_On();
#endif
}
BOOLEAN msAPI_Tuner_GetSignalModulMode(MS_U16 *wModul_Mode)
{
#if ENABLE_T_C_COMBO
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? TRUE : devCOFDM_Get_Modul_Mode(wModul_Mode);
#elif DVB_C_ENABLE
    *wModul_Mode = 0;
    return TRUE;
#else
    if (devCOFDM_Get_Modul_Mode(wModul_Mode))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#endif
}

/******************************************************************************/
/// API for exit Demod::
/******************************************************************************/
void msAPI_Demodulator_Exit(void)
{
#if ENABLE_CI
    if(msAPI_CI_CardDetect())
    {
        extern void msAPI_CI_ReInitial(void);
        msAPI_CI_ReInitial();
    }
#endif
#if ENABLE_T_C_COMBO
    if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
    {
#if (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
        //INTERN_DVBC_Exit();
#endif
    }
    else
    {
#if (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
        //INTERN_DVBT_Exit();
#endif
    }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    //INTERN_DVBT_Exit();
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    //INTERN_DVBC_Exit();
#endif
}

BOOLEAN msAPI_Demodulator_Reset(void)
{
    return TRUE;
}

void msAPI_Check_Lock_State_Init(void)
{
    enVSBCheckLockState = STATE_VSB_CHECK_INIT;
    enVSBCheckStableState = STATE_VSB_STABLE_INIT;
}

BOOLEAN msAPI_Tuner_CheckLock(BOOLEAN *CheckLockResult,BOOLEAN fScan)
{
#if TS_FROM_PLAYCARD
    // for play card
    UNUSED(fScan);
    *CheckLockResult = FE_LOCK;
    return TRUE;
#endif

    U16 count;
    U8 skip = FALSE;
    U16 timeout;
    //U8 bTPSLocked = FALSE;
  #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    U8 bTPSLocked = FALSE;
  #endif

    if ( fScan )
    {
      #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
        timeout = 32;            // 1600ms
      #elif (FRONTEND_DEMOD_TYPE == TOSHIBA_TC90512XBG_DEMOD ||\
             FRONTEND_DEMOD_TYPE == TOSHIBA_TC90517FG_DEMOD)
        timeout = 20;           // 1000ms
      #elif ((FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)||(FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD) )
            #if (!DVB_C_ENABLE && !ENABLE_T_C_COMBO)
             timeout = 200;
            #elif (ENABLE_T_C_COMBO)
                if(IsCATVInUse())
                {
                    if (devQAM_GetSymbolRateMode() == 1)
                    {
                        timeout = 200;            // 10sec  for SR auto mode

                    }
                    else
                    {
                        timeout = 80;           // 2 sec  for SR fixed mode
                    }
                }
                else
                {
                    timeout = 200;            // 10sec  for SR auto mode
                }
            #else
            if (devQAM_GetSymbolRateMode() == 1)
            {
                timeout = 200;            // 10sec  for DVBC SR auto mode
            }
            else
            {
                timeout = 80;           // 4 sec  for DVBC SR fixed mode
            }
            #endif
      #else
        timeout = 40;						 // 2 sec.
      #endif

        for ( count = 0; count < timeout; count++ )
        {
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
            //if (devCOFDM_GetLockStatus(COFDM_AGC_LOCK) == TRUE)
            //    timeout = 60;        // 3000ms

            if (devCOFDM_GetLockStatus(COFDM_DESCRAMBLER_LOCK) == TRUE)
            {
                timeout = 120;        // 6000ms
            }

            if ((devCOFDM_ReadReg(0x802E)&0x40) == 0x40)
            {
                timeout = 240;        // 12000ms
                //printf("Run Optimizer ... \n");
            }

            if (bTPSLocked == TRUE)
            {
                timeout = 120;        // 6000ms
            }
            else if (devCOFDM_GetLockStatus(COFDM_TPS_LOCK) == TRUE)
            {
                bTPSLocked = TRUE;
            }

            if (devCOFDM_GetLockStatus(COFDM_TPS_LOCK) == TRUE)
            {
                if (devCOFDM_GetLockStatus(COFDM_FEC_LOCK) == TRUE)
                {
                    break;
                }
            }
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
            if (devCOFDM_GetLockStatus(COFDM_FEC_LOCK) == TRUE)
            {
                *CheckLockResult = FE_LOCK;
                return TRUE;
            }

            if (bTPSLocked == FALSE)
            {
                if (devCOFDM_GetLockStatus(COFDM_TPS_LOCK) == TRUE)
                {    // channel exist, extend timeout to 3sec
                    TUNER_API_DBG(printf(">> TPS Lock!!!\n"));
                    bTPSLocked = TRUE;
                    timeout = 120;
                }
            }
#elif (FRONTEND_DEMOD_TYPE == TOSHIBA_TC90512XBG_DEMOD ||\
       FRONTEND_DEMOD_TYPE == TOSHIBA_TC90517FG_DEMOD)
            if (count > 10) // typical 10~15 => 500~750mSec
            {
                if ( TRUE == devCOFDM_GetLockStatus(COFDM_FEC_LOCK) )
                {
                    *CheckLockResult = FE_LOCK;
                    return TRUE;
                }
            }
#else
#if DVB_C_ENABLE
    #if ENABLE_T_C_COMBO
        if (!IsCATVInUse())
        {
            if ( TRUE == devCOFDM_GetLockStatus(COFDM_FEC_LOCK) )
            {
                TUNER_API_DBG_ONELINE(printf("FEC LOCK "));
                *CheckLockResult = FE_LOCK;
                return TRUE;
            }
            if ( FALSE == devCOFDM_GetLockStatus(COFDM_TPS_LOCK) )
            {
				if(count > 20) // 20*50ms = 1 sec.
				{
					TUNER_API_DBG_ONELINE(printf("No TPS "));
					TUNER_API_DBG(printf("No TPS info\n"));
					break;
				}
            }
        }
        else
    #endif
        {
            if ( TRUE == devQAM_GetLockStatus(QAM_FEC_LOCK) )
            {
                TUNER_API_DBG_ONELINE(printf("FEC LOCK "));
                *CheckLockResult = FE_LOCK;
                return TRUE;
            }

            if ((devQAM_GetSpeedUp() & 0x0504) > 0)
            {
                break;
            }
        }
#else
            if ( TRUE == devCOFDM_GetLockStatus(COFDM_FEC_LOCK) )
            {
              #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
                if (devCOFDM_GetLockStatus(COFDM_TPS_LOCK) == TRUE)
                {
                    *CheckLockResult = FE_LOCK;
                    return TRUE;
                }
              #else
                *CheckLockResult = FE_LOCK;
                return TRUE;
              #endif
            }
            if ( FALSE == devCOFDM_GetLockStatus(COFDM_TPS_LOCK) )
            {
                if(count > 20) // 20*50ms = 1 sec.
                {
                    TUNER_API_DBG_ONELINE(printf("No TPS "));
                    TUNER_API_DBG(printf("No TPS info\n"));
                    break;
                }
            }
#endif // #if DVB_C_ENABLE
#endif

            if ( skip == TRUE )
            {
                break;
            }

            //printf("Check FEC Lock in auto scan\n");

            #if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
            #endif
            MsOS_DelayTask(50);//jerry-cp
            //msAPI_Timer_Delayms(50); //50
        }
    }
#if ENABLE_T_C_COMBO
    if ( (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  && (TRUE == devQAM_GetLockStatus(QAM_FEC_LOCK)) )
    {
        *CheckLockResult = FE_LOCK;
    }
    else if ( (msAPI_Tuner_GetSourceType() == EN_DVB_T_TYPE)  && (TRUE == devCOFDM_GetLockStatus(COFDM_FEC_LOCK)) )
    {
        *CheckLockResult = FE_LOCK;
    }
    else
    {
        *CheckLockResult = FE_NOT_LOCK;
    }
#elif DVB_C_ENABLE
    if ( TRUE == devQAM_GetLockStatus(QAM_FEC_LOCK) )
    {
        *CheckLockResult = FE_LOCK;
    }
    else
    {
        *CheckLockResult = FE_NOT_LOCK;
    }
#else
    if ( TRUE == devCOFDM_GetLockStatus(COFDM_FEC_LOCK) )
    {
      #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
        if (devCOFDM_GetLockStatus(COFDM_TPS_LOCK) == TRUE)
        {
            *CheckLockResult = FE_LOCK;
        }
        else
        {
            *CheckLockResult = FE_NOT_LOCK;
        }
      #else
        *CheckLockResult = FE_LOCK;
      #endif
    }
    else
    {
        *CheckLockResult = FE_NOT_LOCK;
    }
#endif

    return TRUE;
}


void msAPI_Tuner_Serial_Control(BOOLEAN bParallelMode)
{
    BOOLEAN bEnable;
    //printf("\n\nmsAPI_Tuner_Serial_Control.........%X\n\n", bParallelMode);
#if ENABLE_CI
#if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    bParallelMode = TRUE;
#endif
#endif
    _bTSParallelMode = bParallelMode;

#if ENABLE_CI
    if (bParallelMode)
    {
        bEnable = FALSE;
    }
    else
    {
        bEnable = TRUE;

    }
#else
    UNUSED(bParallelMode);
    bEnable = (!TS_PARALLEL_OUTPUT);
#endif

#if TS_FROM_PLAYCARD
    MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    return;
#endif

    if (bEnable == TRUE)
    {
#if (U3_BRINGUP_ONLY)
    #if(MS_BOARD_TYPE_SEL == BD_MST072F_D01A_S)
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, TS_CLK_INV, TRUE, FALSE);
    #else
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, TS_CLK_INV, TRUE, FALSE);
    #endif
#else // if (U3_BRINGUP_ONLY)
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, FALSE);
#endif

#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_S7J) || (CHIP_FAMILY_TYPE==CHIP_FAMILY_M10) \
	|| (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET))
    //printf ("*********************set S7J flow\n");
    MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, FALSE);
    #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD)
    if (msAPI_GetDemodType() ==  E_DEVICE_DEMOD_DVB_T)
    {
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, TRUE, TRUE, TRUE);
    }
    else
    {
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, TRUE, TRUE);
    }
    #else
    MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    #endif
#endif

#if ENABLE_T_C_COMBO
        if (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            devQAM_SwitchTransportSteamInferface(E_QAM_SERIAL_INTERFACE);
        }
        else
        {
            devCOFDM_SwitchTransportSteamInferface(E_SERIAL_INTERFACE);
        }
#elif DVB_C_ENABLE
        devQAM_SwitchTransportSteamInferface(E_QAM_SERIAL_INTERFACE);
#else
        #if (FRONTEND_DEMOD_TYPE == ZARLINK_CE6355_DEMOD)
        devCOFDM_SwitchTransportSteamInferface(E_SERIAL_INTERFACE,stCurrentTPSetting.enBandWidth);
        #else
        devCOFDM_SwitchTransportSteamInferface(E_SERIAL_INTERFACE);
        #endif
#endif
    }
    else
    {
#if (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    #ifdef HSS_TWO_DEMOD
        if (devCOFDM_GetDemodType()==E_DEMOD_8G42)
        {
            //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_INTERNAL);
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, FALSE, TRUE);
        }
        else
        {
            //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
        }
    #else
        //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_INTERNAL);
        #ifdef HISENSE_6I78
	  	MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, FALSE, TRUE);
        #else
            #if((MS_BOARD_TYPE_SEL == BD_MST072D_D01A_S)||(MS_BOARD_TYPE_SEL == BD_MST072D_SKYWORTH))
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
            #elif(MS_BOARD_TYPE_SEL == BD_MST087F_D01A_T)
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
            #else
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, FALSE, TRUE);
            #endif
        #endif
    #endif
#elif(FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, FALSE, TRUE);

#elif(FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
        MS_DEBUG_MSG(printf("\r\nEMBEDDED_DVBT_DEMOD"));
    #if ENABLE_CI
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    #else
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
    #endif
#elif(FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    #if ENABLE_CI
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    #else
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
    #endif
#else
        //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
        #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD)
        if (msAPI_GetDemodType() ==  E_DEVICE_DEMOD_DVB_T)
        {
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, TRUE, TRUE, TRUE);
        }
        else
        {
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, TRUE, TRUE);
        }

        #else
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
        #endif
#endif

#if ENABLE_T_C_COMBO
        if (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            devQAM_SwitchTransportSteamInferface(E_QAM_PARALLEL_INTERFACE);
        }
        else
        {
            devCOFDM_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
        }
#elif DVB_C_ENABLE
        devQAM_SwitchTransportSteamInferface(E_QAM_PARALLEL_INTERFACE);
#else
        #if (FRONTEND_DEMOD_TYPE == ZARLINK_CE6355_DEMOD)
        devCOFDM_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE,stCurrentTPSetting.enBandWidth);
        #else
        devCOFDM_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
#endif
#endif
    }
#if ENABLE_CI
#if ((!TS_SERIAL_OUTPUT_IF_CI_REMOVED) && (!BLOADER))
    msAPI_Tuner_SetByPassMode(TRUE, FALSE);
#endif
#endif
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD)
    devCOFDM_DTV_Serial_Control(bEnable);
    MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_IN);
#endif
}

FUNCTION_RESULT msAPI_Tuner_CheckSignalStrength(MS_U16 *wStrength)
{
    MS_U16 wSignalStrength;

#if TS_FROM_PLAYCARD
    *wStrength = 80;
    return E_RESULT_SUCCESS;
#endif

#if ENABLE_T_C_COMBO
        if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            if(E_RESULT_SUCCESS != devQAM_GetSignalStrength(&wSignalStrength))
            {
                return E_RESULT_FAILURE;
            }
        }
        else
        {
            if(E_RESULT_SUCCESS != devCOFDM_GetSignalStrength(&wSignalStrength))
            {
                return E_RESULT_FAILURE;
            }
        }
#elif DVB_C_ENABLE
    if(E_RESULT_SUCCESS != devQAM_GetSignalStrength(&wSignalStrength))
    {
        return E_RESULT_FAILURE;
    }
#else
    if(E_RESULT_SUCCESS != devCOFDM_GetSignalStrength(&wSignalStrength))
    {
        return E_RESULT_FAILURE;
    }
#endif

    *wStrength = wSignalStrength;
    return E_RESULT_SUCCESS;
}

FUNCTION_RESULT msAPI_Tuner_GetCurTPSetting(MS_TP_SETTING *pstCurTPSetting)
{
    U8 bLockStatus;

    if ((msAPI_Tuner_CheckLock(&bLockStatus, FALSE)== TRUE) && (bLockStatus == FE_LOCK))
    {
        memcpy(pstCurTPSetting,&stCurrentTPSetting,sizeof(MS_TP_SETTING));
    }

    return E_RESULT_SUCCESS;
}

#if 1//(ENABLE_T_C_COMBO || DVB_T_C_DIFF_DB)//TODO need add DVB-C case
//*************************************************************************
//Function name:    msAPI_Tuner_SwitchSource
//Passing parameter:    EN_DVB_TYPE eType: Demod type
//Return parameter:     none
//Description:      change demod source
//*************************************************************************
void msAPI_Tuner_SwitchSource(EN_DVB_TYPE etype, BOOLEAN bInit)
{
    if(_bDvbType==etype)
    {
        return;
    }
    _bDvbType = etype;
    if(bInit == FALSE)
    {
        return;
    }
    msAPI_Tuner_InintCurrentTPSetting();
    msAPI_Tuner_Initialization(TRUE);
#if (ENABLE_CI)
    if (msAPI_Tuner_IsParallelMode())
    {
        msAPI_Tuner_Serial_Control(TRUE);
    }
    else
    {
        msAPI_Tuner_Serial_Control(FALSE);
    }
    // DMX int end
#else
    msAPI_Tuner_Serial_Control(FALSE);
#endif
}


//*************************************************************************
//Function name:    msAPI_Tuner_GetSourceType
//Passing parameter:    none
//Return parameter:     EN_DVB_TYPE
//Description:      get demod source type
//*************************************************************************
EN_DVB_TYPE msAPI_Tuner_GetSourceType(void)
{
    return _bDvbType;

}

//*************************************************************************
//Function name:    msAPI_Tuner_SetAntenna
//Passing parameter:    Antenna
//Return parameter:     none
//Description:      change tuner Antenna
//*************************************************************************
void msAPI_Tuner_SetAntenna(BOOLEAN bIsCATV)
{
#if(FRONTEND_TUNER_TYPE == ALPS_TDQG9_601A_TUNER || FRONTEND_TUNER_TYPE == TCL_DTC78WI_3E_TUNER)
    //devTunerSetAntenna(bIsCATV);
    //jerry-cp
#else
    UNUSED(bIsCATV);
#endif
}

U8 msAPI_Tuner_GetDspStatus(void)
{
#if (FRONTEND_DEMOD_TYPE==EMBEDDED_DVBT_DEMOD)
    return INTERN_DVBT_GetDspStatus();
#else
    return 0xFF;
#endif
}

#endif //#if (ENABLE_T_C_COMBO || DVB_T_C_DIFF_DB)


DMX_FILTER_STATUS msAPI_Tuner_SetByPassMode(BOOLEAN bByPass, BOOLEAN bPVRMode)
{
    DMX_FILTER_STATUS eResult = DMX_FILTER_STATUS_OK;
    //printf("\n\nmsAPI_Tuner_SetByPassMode.................%X | %X\n\n", bByPass, bPVRMode);
#if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    _bTSByPassMode = bByPass;
    eResult = MApi_DMX_FlowSet(bPVRMode?DMX_FLOW_PVR:DMX_FLOW_PLAYBACK, bByPass?DMX_FLOW_INPUT_DEMOD:DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
#else
    UNUSED(bByPass);
    UNUSED(bPVRMode);
#endif
    return eResult;
}

BOOLEAN msAPI_Tuner_IsByPassMode(void)
{
    return _bTSByPassMode;
}

BOOLEAN msAPI_Tuner_IsParallelMode(void)
{
    return _bTSParallelMode;
}

#if (DVB_C_ENABLE)
void msAPI_Tuner_UpdateTPSetting(void)
{
#if (ENABLE_T_C_COMBO)
    if (IsCATVInUse())
#endif
    {
        stCurrentTPSetting.u32Symbol_rate = devQAM_GetCurrentSymbolRate();
        stCurrentTPSetting.u8Modulation = devQAM_GetCurrentQAM();
    }
}
#endif

#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD) \
    || (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD))
void msAPI_GetPlpBitMap(U8* u8PlpBitMap)
{
    DTV_GetPlpBitMap(u8PlpBitMap);
}
BOOLEAN msAPI_GetPlpGroupID(U8 u8PlpID, U8* u8GroupID)
{
    return DTV_GetPlpGroupID(u8PlpID,u8GroupID);
}

BOOLEAN msAPI_SetPlpGroupID(U32 u32PlpID, U32 u32GroupID)
{
    return DTV_SetPlpGroupID(u32PlpID,u32GroupID);
}

BOOLEAN msAPI_SetDemodType(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    msAPI_Tuner_InintCurrentTPSetting();
    return devCOFDM_SetDemodType(enDemodType);
}
EN_DEVICE_DEMOD_TYPE msAPI_GetDemodType(void)
{
    return devCOFDM_GetDemodType();
}

#endif
#endif
#undef MSAPI_TUNER_C

