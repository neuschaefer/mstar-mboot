#define _MSB1238_C_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include <stdio.h>
//#include <string.h>
//#include "MApp_GlobalVar.h"

#include "MsCommon.h"
#include "MsOS.h"
#include "Board.h"
#include "drvDMD_common.h"
#include "drvDMD_VD_MBX.h"

#include "drvIIC.h"
#include "drvGPIO.h"
#include "drvHWI2C.h"
//#include "drvTuner.h"
#include "drvDemod.h"
#include "HbCommon.h"

#if(FRONTEND_DEMOD_TYPE == MSTAR_MSB1238_DEMOD)//1238????
#include "drvDMD_DTMB.h" //drvDMD_DTMB.h
#include "device_demodulator_msb1238.h"//1238.h???

#define ERR_DEMOD_MSB(x)            //  x
#define DBG_DOMOD_MSB(x)            //   x
#define DBG_DEMOD_CHECK_LOCK(x)   // x
#define DBG_DEMOD_INFO(x)   // x
#define DBG_SSI(x)        //  x
#define DBG_SQI(x)        //  x
#define DBG_MSB(x)              x
#define COFDMDMD_MUTEX_TIMEOUT       (2000)

#define DTMB_PreLock_timeout   300
#define DTMB_PNMLock_timeout   1200
#define DTMB_FEC_timeout   5000


#define DTMB_CASHMERE_SLAVE_ID  0xD2  //0xF2

#if (FRONTEND_TUNER_TYPE == TUNER_MXL603)
#define DTMB_TUNER_IF           5000 //4000//5000
#else
#define DTMB_TUNER_IF           3250
#endif
#define usleep(x)                   MsOS_DelayTask(x/1000)

#if TS_PARALLEL_OUTPUT
#define DTMB_TS_SERIAL        0x00
#else
#define DTMB_TS_SERIAL        0x01
#endif
// Division number of TS clock rate
// Formula: TS Clk Rate= 216 MHz/reg_dtmb_ts_clk_divnum
// Ex: DTMB_TS_CLK_DIVNUM = 31 => TS Clk = 216/31= 6.967 MHz
#define DTMB_TS_CLK_DIVNUM_SERIAL_MODE   2//0 // 4
#define DTMB_TS_CLK_DIVNUM_PARALLEL_MODE  6//26//31

#if (DTMB_TS_SERIAL)
#define DTMB_TS_CLK_DIVNUM    DTMB_TS_CLK_DIVNUM_SERIAL_MODE
#else
#define DTMB_TS_CLK_DIVNUM    DTMB_TS_CLK_DIVNUM_PARALLEL_MODE
#endif

#define DTMB_TS_DATA_SWAP  0x00  // TS data inversion
#define DTMB_TS_CLK_INV    TS_CLK_INV  //TS_CLK_INV  // TS clock inverseion //this define will depend on hw main board
#define DTMB_IQ_SWAP   FRONTEND_DEMOD_IQ_SWAP          // IQ Swap  //this define will depend on tuner
#define DTMB_IFAGC_REF 0x500              //this define will depend on tuner
#define DTMB_TDI_START_ADDR (DMD_DTMB_ADR/16)   // System must allocate a 7MB memory space starting from this (128-bit)address
//static BOOL s_bI2C_FastMode = false;



//Local variables//
static MS_S32                       _s32TaskId  = -1;
static MS_S32                       _s32MutexId;
static MS_BOOL                      bInited     = FALSE;


MS_U32 Scan_Time_Start;
static DEMOD_EN_TER_BW_MODE Lastest_BW = DEMOD_BW_MODE_6MHZ;
/***********************************************************************************
************************************************************************************/



MS_BOOL   MDrv_MSB1238_IIC_Write(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL   MDrv_MSB1238_IIC_Read(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);

#define GPIO_FE_RST 62
void MApi_Demod_HWReset(void)
{
    mdrv_gpio_set_high(GPIO_FE_RST);
    MsOS_DelayTask(100);
    mdrv_gpio_set_low(GPIO_FE_RST);
    MsOS_DelayTask(200);
    mdrv_gpio_set_high(GPIO_FE_RST);
    MsOS_DelayTask(100);
}

// Global function//
MS_BOOL MDrv_Demod_Init(void)
{
    DMD_DTMB_InitData sDMD_DTMB_InitData;
    static MS_U8 u8DMD_DTMB_InitExt[]={1};

    bInited = FALSE;
    DBG_MSB(printf("-----%s start-----\n", __FUNCTION__));

    if (_s32TaskId >= 0)
    {
        return TRUE;
    }

    _s32MutexId = MsOS_CreateMutex(E_MSOS_FIFO, "OfDmd_Mutex", MSOS_PROCESS_SHARED);

    if (_s32MutexId < 0)
    {
        GEN_EXCEP;
        return FALSE;
    }


   // void MApi_Demod_HWReset(void);
    MApi_Demod_HWReset();

    memset(&sDMD_DTMB_InitData,0,sizeof(sDMD_DTMB_InitData));
    sDMD_DTMB_InitData.u16IF_KHZ = 5000;//u16DtvIFFreqKHz;
    sDMD_DTMB_InitData.bIQSwap = DTMB_IQ_SWAP;//u8IqSwap;
    sDMD_DTMB_InitData.eSR_TYPE = SR_6M;
    sDMD_DTMB_InitData.u8IS_DUAL = FALSE;
    sDMD_DTMB_InitData.bIsUseSspiLoadCode = FALSE;
    sDMD_DTMB_InitData.u16VSBAGCLockCheckTime = 50;
    sDMD_DTMB_InitData.u16DTMBPreLockCheckTime = DTMB_PreLock_timeout;
    sDMD_DTMB_InitData.u16DTMBPNMLockCheckTime = DTMB_PNMLock_timeout;
    sDMD_DTMB_InitData.u16DTMBFECLockCheckTime = DTMB_FEC_timeout;

    sDMD_DTMB_InitData.u16QAMAGCLockCheckTime = 50;
    sDMD_DTMB_InitData.u16QAMPreLockCheckTime = 1000;
    sDMD_DTMB_InitData.u16QAMMainLockCheckTime = 3000;


    sDMD_DTMB_InitData.u8DMD_DTMB_InitExt = u8DMD_DTMB_InitExt;
    // sanghyun
    //sDMD_DTMB_InitData.u16AgcReferenceValue = DTMB_IFAGC_REF;

    //TS[begin]
    //Parallel mode
    sDMD_DTMB_InitData.u5TsConfigByte_DivNum = DTMB_TS_CLK_DIVNUM;
    sDMD_DTMB_InitData.u1TsConfigByte_ClockInv = DTMB_TS_CLK_INV;
    sDMD_DTMB_InitData.u1TsConfigByte_DataSwap = DTMB_TS_DATA_SWAP;
    sDMD_DTMB_InitData.u1TsConfigByte_SerialMode = DTMB_TS_SERIAL;
    //Serial mode
    //sDMD_ISDBT_InitData.u5TsConfigByte_DivNum = 4;
    //sDMD_ISDBT_InitData.u1TsConfigByte_ClockInv = 0;
    //sDMD_ISDBT_InitData.u1TsConfigByte_DataSwap = 0;
    //sDMD_ISDBT_InitData.u1TsConfigByte_SerialMode = 1;
    //TS[end]

    //I2C[begin]
    sDMD_DTMB_InitData.u8I2CSlaveAddr = DTMB_CASHMERE_SLAVE_ID;
    sDMD_DTMB_InitData.u8I2CSlaveBus = 0;
    //MAX
    sDMD_DTMB_InitData.bIsExtDemod = TRUE;
      //sDMD_DTMB_InitData.u16AgcReferenceValue = true;
    sDMD_DTMB_InitData.I2C_WriteBytes = MDrv_MSB1238_IIC_Write;

    sDMD_DTMB_InitData.I2C_ReadBytes = MDrv_MSB1238_IIC_Read;
    //I2C[end]

    MDrv_DMD_DTMB_Initial_Hal_Interface();

    MDrv_DMD_DTMB_Init(&sDMD_DTMB_InitData, sizeof(sDMD_DTMB_InitData));

    MDrv_DMD_DTMB_IIC_BYPASS_MODE(TRUE);

    //MDrv_DMD_DTMB_SetVsbMode();//MSB1238_VsbMode();
    MDrv_DMD_DTMB_SetDtmbMode();
	
    if (MDrv_Tuner_Init() == FALSE)
    {
        MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);
        return FALSE;
    }
    MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);

    bInited = TRUE;

    return TRUE;


}

MS_BOOL MDrv_Demod_Open(void)
{

    return TRUE;

}

MS_BOOL MDrv_Demod_Close(void)
{
    return TRUE;
}

MS_BOOL MDrv_Demod_Reset(void)
{
 
        if(!MDrv_DMD_DTMB_SetReset())//(!MSB1238_SoftReset())
        {
            DBG_MSB(HB_printf("%s: Soft reset failed.\n", __FUNCTION__));
            return FALSE;
        }

    return TRUE;

}

MS_BOOL MDrv_Demod_TsOut(MS_BOOL bEnable)
{

    return TRUE;
}

MS_BOOL MDrv_Demod_PowerOnOff(MS_BOOL bPowerOn)
{

    return TRUE;
}

MS_BOOL MDrv_Demod_SetBW(MS_U32 u32BW)
{

    return TRUE;

}

MS_BOOL MDrv_Demod_GetBW(MS_U32 *pu32BW)
{

    return TRUE;

}

MS_BOOL MDrv_Demod_GetLock(EN_LOCK_STATUS *peLockStatus)
{
    DMD_DTMB_LOCK_STATUS eLockStatus = DMD_DTMB_UNLOCK;
    *peLockStatus =E_DEMOD_CHECKING;


    if(FALSE == bInited)
    {
        HB_printf("[%s]MSB1238 have not inited !!!\n",__FUNCTION__);
        
        return FALSE;
    }


    eLockStatus= MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK);   //DMD_DTMB_LOCK

    switch (eLockStatus) // _UTOPIA
    {
    case DMD_DTMB_LOCK:
        *peLockStatus = E_DEMOD_LOCK;
        break;
    case DMD_DTMB_CHECKING:
        *peLockStatus = E_DEMOD_CHECKING;
        break;
    case DMD_DTMB_CHECKEND:
        *peLockStatus = E_DEMOD_CHECKEND;
        break;
    case DMD_DTMB_UNLOCK:
        *peLockStatus = E_DEMOD_UNLOCK;
        break;
    default:
        DBG_MSB(HB_printf("MDrv_DMD_DTMB_GetLock error\n"));
        break;
    }

    
    return TRUE;

}

MS_BOOL MDrv_Demod_GetSNR(MS_U32 *pu32SNR)
{
   // MS_U8 u8snr=0;

        //if (TRUE == MSB1238_GetLock())
        if( MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK)== DMD_DTMB_LOCK)
        {
           *pu32SNR  =   MDrv_DMD_DTMB_GetSignalQuality();
            //u8snr = MDrv_DMD_DTMB_GetSNRPercentage();
            //*pu32SNR= (MS_U32) u8snr;//*0.4;
            //*pu32SNR = MSB1238_ReadSNRdB();
        }

        else
        {
            *pu32SNR = 0;
        }
    

    return TRUE ;

}

MS_BOOL MDrv_Demod_GetBER(float *pfBER)
{
    MS_U32  dwError = 0;


        *pfBER = -1;

    return (dwError ) ? FALSE : TRUE;
}

MS_BOOL MDrv_Demod_GetPWR(MS_S32 *ps32Signal)
{
#define DEFAULT_PWR_MIN (-97)
#define DEFAULT_PWR_MAX (-5)

    MS_U32  dwError=0;
    MS_U8 u8snr;
 // MS_S32  wSignal;

   
        //if (TRUE == MSB1238_GetLock())
        if( MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK)== DMD_DTMB_LOCK)
        {
           //Signal = lgdt3305_SignalStatus(DEMOD_TYPE);
           //       wSignal = lgdt3305_IfAcc();
          //rintf("PWR = 0x%x \n",wSignal);

         u8snr = MDrv_DMD_DTMB_GetSNRPercentage();
         *ps32Signal = (MS_U32) u8snr;
            //*ps32Signal =  MSB1238_ReadSNRPercentage();
        }

        else
        {
            *ps32Signal = DEFAULT_PWR_MIN;
        }
    
    return (dwError ) ? FALSE : TRUE;
   // return TRUE;
}

MS_BOOL MDrv_Demod_Config(MS_U8 *pRegParam)
{

    return TRUE;

}

MS_BOOL MDrv_Demod_GetParam(DEMOD_MS_FE_CARRIER_PARAM* pParam)
{

    return TRUE;

}

MS_BOOL MDrv_Demod_I2C_ByPass(MS_BOOL bEnable);

MS_BOOL MDrv_Demod_Restart(DEMOD_MS_FE_CARRIER_PARAM* pParam)
{
    MS_U32  NoError = 0;
    //MS_BOOL bret;
    DMD_DTMB_SR_TYPE SR_BW = 0;

        MDrv_Demod_I2C_ByPass(TRUE);
        NoError = MDrv_Tuner_SetTuner( pParam->u32Frequency, pParam->TerParam.eBandWidth);
        MDrv_Demod_I2C_ByPass(FALSE);
        //MsOS_DelayTask(250); //necessary for NMI120 get RSSI
        if(!MDrv_DMD_DTMB_SetReset())//(!MSB1238_SoftReset())
        {
          HB_printf("-----%s FAIL-----\n", __FUNCTION__);
          return FALSE;
        }
        MsOS_DelayTask(100); // ori = 10
        if(Lastest_BW !=pParam->TerParam.eBandWidth)
        {
            //set dtmb SRType
            switch (pParam->TerParam.eBandWidth)
            {
                case DEMOD_BW_MODE_6MHZ:
                    SR_BW = SR_6M;
                    break;
                case DEMOD_BW_MODE_8MHZ:
                    SR_BW = SR_8M;
                    break;
                default:
                    SR_BW = SR_8M;
                    break;

            }
            Lastest_BW = pParam->TerParam.eBandWidth;
            MDrv_DMD_DTMB_SetSRType(SR_BW);
            MDrv_DMD_DTMB_LoadFW(0);
            MsOS_DelayTask(100);
        }
        MDrv_DMD_DTMB_SetDtmbMode();
        printf("    MDrv_DMD_DTMB_SetReset OK ! \n");

    return (NoError) ? TRUE : FALSE;
}

MS_BOOL MDrv_Demod_SetMode(Demod_Mode* pMode)
{

    return TRUE;

}

MS_BOOL MDrv_Demod_SetOutoutPath(DEMOD_INTERFACE_MODE path)
{
    //Dummy function
    return TRUE;
}


MS_BOOL   MDrv_MSB1238_IIC_Write(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    MS_BOOL bResult = TRUE;
    //printf("Enter MDrv_MSB140X_IIC_Write\n");
    //printf("u16BusNumSlaveID=%x\n",u16BusNumSlaveID);
    bResult = MDrv_IIC_Write(u16BusNumSlaveID, pu8addr, u8addrcount, pu8data,  u16size);
   // printf("\n===talent_%s=%d=slaveid=%d\n",__func__,bResult,u16BusNumSlaveID);
    if(!bResult)
    {
        printf("1238C IIC Write Erro..");
    }
    return bResult;
}

MS_BOOL   MDrv_MSB1238_IIC_Read(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data)
{
    MS_BOOL bResult = TRUE;
    //printf("Enter MDrv_MSB140X_IIC_Read\n");

    bResult = MDrv_IIC_Read(u16BusNumSlaveID, paddr, u8AddrNum, pu8data,  u16size);
    if(!bResult)
    {
        printf("1238C IIC Read Erro..");
    }
    return bResult;
}




DEMOD_INTERFACE_MODE MDrv_Demod_GetOutoutPath(void)
{
    //Dummy function
    return DEMOD_INTERFACE_PARALLEL;
}

MS_BOOL MDrv_Demod_I2C_ByPass(MS_BOOL bEnable)
{
    if(bEnable)
        return MDrv_DMD_DTMB_IIC_BYPASS_MODE(TRUE);
        //MSB1238_RepeaterEnable();
    else
        return MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);
        //MSB1238_RepeaterDisable();
}

MS_U16 MDrv_Demod_ReadReg(MS_U16 RegAddr)
{
    MS_U8 RegData = 0;
    //MSB1238_ReadReg(RegAddr, &RegData);
    MDrv_DMD_DTMB_GetReg(RegAddr,&RegData);
    return (MS_U16) RegData;
}

MS_BOOL MDrv_Demod_WriteReg(MS_U16 RegAddr, MS_U16 RegData)
{
      MS_U8 u8RegData = 0;

      u8RegData= (MS_U8) RegData;
    return MDrv_DMD_DTMB_SetReg(RegAddr, u8RegData);
    //return MSB1238_WriteReg(RegAddr, RegData);
}


/***********************************************************************************
************************************************************************************/
#undef _MSB1238_C_

#endif
