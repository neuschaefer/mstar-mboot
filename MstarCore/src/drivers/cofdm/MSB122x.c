/*@ <FileComment ID=1246257763790> @*/
/**********************************************************************
Copyright (c) 2006-2009 MStar Semiconductor, Inc.
All rights reserved.
Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
MStar Semiconductor Inc. and be kept in strict confidence
(MStar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of MStar Confidential
Information is unlawful and strictly prohibited. MStar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
 * Class : mapi_demodulator_msb122x
 * File  : mapi_demodulator_msb122x.cpp
 **********************************************************************/
/*@ </FileComment ID=1246257763790> @*/
/*@ <Include> @*/
#include <sys/common/MsTypes.h>
#include <sys/common/MsIRQ.h>
#include <sys/common/MsOS.h>
#include <msAPI_Tuner.h>
#include <device/MSB122x.h>

#define LOADFW 1
#if (LOADFW == 1)
#include <device/msb122x_dvbt.dat>
#endif



/*@ </Include> @*/
/*@ <Definitions> @*/
#define ERR_DOMOD_MSB(x)    x
#define DBG_DOMOD_MSB(x)      x
#define DBG_GET_SIGNAL(x)    x
#define DBG_DUMP_LOAD_DSP_TIME 0
#define MDrv_Timer_Delayms OS_DELAY_TASK
#define MDrv_Timer_GetTime0 OS_SYSTEM_TIME
//#define TS_CLK_INV 1


/*@ </Definitions> @*/
MAPI_U8 u8DeviceBusy = 0;
MAPI_U8 u8MsbData[6];
MAPI_U8  gu8ChipRevId;
S_CMDPKTREG gsCmdPacket;
MAPI_BOOL FECLock;
EN_DEVICE_DEMOD_TYPE m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_DVB_T;
static MAPI_U32 u32ChkScanTimeStart = 0;
static MAPI_BOOL bPower_init_en = MAPI_FALSE;

MAPI_BOOL Cmd_Packet_Send(S_CMDPKTREG *pCmdPacket, MAPI_U8 param_cnt);
MAPI_BOOL LoadDSPCode(void);
MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data);
MAPI_BOOL DTV_Config(RF_CHANNEL_BANDWIDTH BW, MAPI_BOOL bSerialTS, MAPI_BOOL bPalBG);

/*@ <Operation ID=I2b28dd03m121c8cf959bmm722c> @*/
MAPI_BOOL Connect(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    DBG_DOMOD_MSB(printf("device_demodulator_msb122x: Connect\n"));
    if (u8DeviceBusy == 1)
        return MAPI_FALSE;
    m_enCurrentDemodulator_Type = enDemodType;

    u8DeviceBusy = 1;
    return MAPI_TRUE;
}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm722c> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm7207> @*/
MAPI_BOOL Disconnect(void)
{
    DBG_DOMOD_MSB(printf("device_demodulator_msb122x: Disconnect\n"));
    u8DeviceBusy = 0;
    return MAPI_TRUE;
}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm7207> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm71bd> @*/
void Reset(void)
{
    WriteReg(0x8232, 0x01);
    WriteReg(0x8220, 0x01);
    usleep(5 *1000);
    WriteReg(0x8220, 0x00);
    WriteReg(0x8232, 0x00);

    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm71bd> @*/
MAPI_BOOL IIC_Bypass_Mode(MAPI_BOOL enable)
{
    MAPI_U8 u8Retry=10;
    while(u8Retry--)
    {
        if (enable)
            WriteReg(0x8010, 0x10);// IIC by-pass mode on
        else
            WriteReg(0x8010, 0x00);// IIC by-pass mode off
        //usleep(500*1000);
    }
    return MAPI_TRUE;
}


/*@ <Operation ID=Im17018142m1221763cc7cmm46c6> @*/
MAPI_BOOL Power_On_Initialization(void)
{
    MAPI_U8 status = true;
    FECLock = MAPI_FALSE;
    DBG_DOMOD_MSB(printf(">>>MSB122x: Enter Power_On_Initialization()\n"));
    //// Firmware download //////////
    DBG_DOMOD_MSB(printf(">>>MSB122x: Load DSP...\n"));
    //usleep(100 *1000);
    if (bPower_init_en == TRUE)//Stan FIXME.
        return MAPI_TRUE;
    else
        bPower_init_en = MAPI_TRUE;

    if (LoadDSPCode() == MAPI_FALSE)
    {

        DBG_DOMOD_MSB(printf(">>>MSB122x:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {
        DBG_DOMOD_MSB(printf(">>>MSB122x:OK\n"));
    }


    DBG_DOMOD_MSB(printf(">>>MSB122x:OK\n"));
    //// MCU Reset //////////
    //DBG_DOMOD_MSB(printf(">>>MSB122x: Reset...\n"));
    //MSB122x_Reset();
    ReadReg(0x8000, &gu8ChipRevId);
    DBG_DOMOD_MSB(printf(">>>MSB122x:Gemini RevID:%x\n", gu8ChipRevId));

    return status;
}

/*@ <Operation ID=Im17018142m1221763cc7cmm464e> @*/
MAPI_BOOL Active(MAPI_BOOL bEnable)
{
    MAPI_U8 status = true;
    DBG_DOMOD_MSB(printf(">>>MSB122x: @msb122x_active\n"));
    //// MSB122x Finite State Machine on/off //////////
    gsCmdPacket.cmd_code = CMD_FSM_CTRL;
    gsCmdPacket.param[0] = (MAPI_U8)bEnable;
    status &= Cmd_Packet_Send(&gsCmdPacket, 1);
    return status;
}

MAPI_BOOL DTV_Set_Demod_TYPE(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    m_enCurrentDemodulator_Type = enDemodType;
    return MAPI_TRUE;
}

EN_DEVICE_DEMOD_TYPE DTV_Get_Demod_TYPE(void)
{
    return m_enCurrentDemodulator_Type;
}

//##########################################################################################################
//##########################################################################################################
//########################################  Public:DTV Implementation ##################################
//##########################################################################################################
//##########################################################################################################
MAPI_BOOL DTV_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    MAPI_BOOL b_pal_bg;
    MAPI_BOOL bStatus = MAPI_FALSE;
    DBG_DOMOD_MSB(printf("DTV_SetFrequency %d ,%d \n", (int)u32Frequency, (int)eBandWidth));
    FECLock = MAPI_FALSE;
    b_pal_bg = false;
    bStatus = DTV_Config(eBandWidth, /*m_bSerialOut*/ 0, b_pal_bg);
    u32Frequency = u32Frequency;

    if (bStatus == MAPI_FALSE)
    {
      //  TRACE;
        printf("Demod_Config failed \n");
        return MAPI_FALSE;
    }
    //printf("Demod_Config OK \n");
    bStatus = Active(MAPI_TRUE);
    if (bStatus == MAPI_FALSE)
    {
       // TRACE;
        printf("Demod Active failed \n");
        return MAPI_FALSE;
    }
     u32ChkScanTimeStart = MsOS_GetSystemTime();
    return MAPI_TRUE;
}
EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void)
{
    return E_FE_SIGNAL_NO;
}

MAPI_U16 DTV_GetSignalQuality(void)
{
    return 80; //sttest
}

MAPI_U16 DTV_GetSignalStrength(void)
{
    MAPI_U16               u16Strength;

	u16Strength = 88;
	return u16Strength;
}

//##########################################################################################################
//##########################################################################################################
//########################################  Public:DTV-DVB-T Implementation ################################
//##########################################################################################################
//##########################################################################################################
BOOLEAN DTV_DVB_T_GetLockStatus(void)
{
    MAPI_U32 u32Timeout = 1500;
    MAPI_U8 u8Data;

    ReadReg(0x87E0, &u8Data);
    DBG_DOMOD_MSB(printf(">>>MSB122x: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
    if (u8Data == 0x0B)
    {
        FECLock = MAPI_TRUE;
        return MAPI_TRUE;
    }
    else
    {
        FECLock = MAPI_FALSE;
    }
    if (MsOS_GetSystemTime() - u32ChkScanTimeStart < u32Timeout)
    {
        return MAPI_FALSE;
    }
    else
    {
        return MAPI_FALSE;
    }
}




//##########################################################################################################
//##########################################################################################################
//########################################  Private Function Implementation ################################
//##########################################################################################################
//##########################################################################################################
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6ff4> @*/
MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) &0xff;
    u8MsbData[2] = u16Addr &0xff;
    u8MsbData[3] = u8Data;
   // mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(gu8DemoDynamicI2cAddress);

  //  return iptr->WriteBytes(0, NULL, 4, u8MsbData);
   return MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 4, u8MsbData);
}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm6ff4> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6fcf> @*/
MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) &0xff;
    u8MsbData[2] = u16Addr &0xff;
   // mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(gu8DemoDynamicI2cAddress);
   // if (iptr->WriteBytes( 0, NULL, 3, u8MsbData) == MAPI_FALSE)
    if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 3, u8MsbData)== MAPI_FALSE)
    {
        DBG_DOMOD_MSB(printf(">>>MSB122x:Read write fail\n"));
        return MAPI_FALSE;
    }
    u8MsbData[0] = DEMOD_READ_REG;

    //return iptr->ReadBytes( 1, u8MsbData, 1, pu8Data);
    return MDrv_IIC_ReadBytes(DEMOD_SLAVE_ID,1, u8MsbData, 1, pu8Data);

}
/*@ </Operation ID=I2b28dd03m121c8cf959bmm6fcf> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6faa> @*/
MAPI_BOOL Cmd_Packet_Send(S_CMDPKTREG *pCmdPacket, MAPI_U8 param_cnt)
{

    MAPI_U8 status = true, indx;
    //MAPI_U8             reg_val, timeout = 0;
    MAPI_U16 timeout = 0;
    MAPI_U8 reg_val = 0;
    // ==== Command Phase ===================
    DBG_DOMOD_MSB(printf(">>>MSB122x: (cmd=0x%x)(0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,) \n", pCmdPacket->cmd_code, pCmdPacket->param[0], pCmdPacket->param[1], pCmdPacket->param[2], pCmdPacket->param[3], pCmdPacket->param[4], pCmdPacket->param[5]));
    // wait _BIT_END clear
    do
    {
        status &= ReadReg(REG_CMD_CTRL, &reg_val);
         if((reg_val & _BIT_END) != _BIT_END)
            break;

        usleep(5 *1000);
        if (timeout++ > 200)
        {
            DBG_DOMOD_MSB(printf(">>>MSB122x: MSB122x_Cmd_Packet_Send fail on 'wait _BIT_END clear' \n"));
            return false;
        }
    }while (1);

    // set cmd_3:0 and _BIT_START
    status &= ReadReg(REG_CMD_CTRL, &reg_val);
    reg_val = (reg_val &0x0f) | (pCmdPacket->cmd_code << 4) | _BIT_START;
    status &= WriteReg(REG_CMD_CTRL, reg_val);

    // wait _BIT_START clear
    do
    {
        status &= ReadReg(REG_CMD_CTRL, &reg_val);
         if((reg_val & _BIT_START) != _BIT_START)
            break;
        usleep(5 *1000);
        if (timeout++ > 200)
        {
            DBG_DOMOD_MSB(printf(">>>MSB122x: MSB122x_Cmd_Packet_Send fail on 'wait _BIT_START clear' \n"));
            return false;
        }
    }while (1);

    // ==== Data Phase ======================
    status &= WriteReg(REG_CMD_ADDR, 0x00);
    for (indx = 0; indx < param_cnt; indx++)
    {
        status &= ReadReg(REG_CMD_ADDR, &reg_val);
        DBG_DOMOD_MSB(printf("demod_config: param[%d] = %x\n", reg_val, pCmdPacket->param[indx]));
        // set param[indx] and _BIT_DRQ
        status &= WriteReg(REG_CMD_DATA, pCmdPacket->param[indx]);
        status &= ReadReg(REG_DTA_CTRL, &reg_val);
        status &= WriteReg(REG_DTA_CTRL, reg_val | _BIT_DRQ);

        // wait _BIT_DRQ clear
        do
        {
            status &= ReadReg(REG_DTA_CTRL, &reg_val);
             if ((reg_val & _BIT_DRQ) != _BIT_DRQ)
                break;
            usleep(5 *1000);
            if (timeout++ > 200)
            {
                DBG_DOMOD_MSB(printf(">>>MSB122x: MSB122x_Cmd_Packet_Send fail on 'wait _BIT_DRQ clear' \n"));
                return false;
            }
        }while (1);
    }

    // ==== End Phase =======================
    // set _BIT_END to finish command
    status &= ReadReg(REG_CMD_CTRL, &reg_val);
    status &= WriteReg(REG_CMD_CTRL, reg_val | _BIT_END);

    return status;
}


/*@ <Operation ID=I2b28dd03m121c8cf959bmm6f60> @*/
MAPI_BOOL LoadDSPCode(void)
{
#if (LOADFW == 1)
    //    MAPI_U32 i;
    MAPI_U32 u32TempCounter = 0;
    DBG_DOMOD_MSB(printf(">>>MSB122x: Enter LoadDSPCode()\n"));
    if (WriteReg(0x8232, 0x01) == MAPI_FALSE)
    // MCU SW reset
        return MAPI_FALSE;
    if (WriteReg(0x8230, 0x03) == MAPI_FALSE)
    // Enable read SRAM from I2CS
        return MAPI_FALSE;
    if (WriteReg(0x8210, 0x55) == MAPI_FALSE)
        return MAPI_FALSE;
    if (WriteReg(0x8211, 0xAA) == MAPI_FALSE)
        return MAPI_FALSE;
    u8MsbData[0] = DEMOD_RAM_CONTROL;
    u8MsbData[1] = 0x01;
    //pi_i2c *iptr = mapi_i2c::GetI2C_Dev(gu8DemoDynamicI2cAddress);

   // if (iptr->WriteBytes( 0, NULL, 2, u8MsbData) == MAPI_FALSE) // Enable SRAM write
   if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 2, u8MsbData) == MAPI_FALSE) // Enable SRAM write
        return MAPI_FALSE;

   // iptr->SetSpeed(E_HWI2C_HIGH);
    // load table
    u32TempCounter = sizeof(MSB122x_table);
    //iptr->WriteBytes( 0, NULL, u32TempCounter, &MSB122x_table[0]);
	MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, u32TempCounter, &MSB122x_table[0]);
   // iptr->SetSpeed(E_HWI2C_SLOW);

    u8MsbData[0] = DEMOD_RAM_CONTROL;
    u8MsbData[1] = 0x00;
    //@FIXME , need to define I2C bus/slaveid reference
    //if (iptr->WriteBytes( 0, NULL, 2, u8MsbData) == MAPI_FALSE)
	if (MDrv_IIC_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 2, u8MsbData) == MAPI_FALSE)

    // Disable Ram write
        return MAPI_FALSE;
    if (WriteReg(0x8230, 0x00) == MAPI_FALSE)
    // Disable download from I2CS
        return MAPI_FALSE;
    #if 0
        MAPI_U16 checknum = sizeof(MSB122x_table) - 3;
        MAPI_U8 *getValue = new MAPI_U8[checknum];
        if (getValue != NULL)
        {
            MAPI_BOOL bRet = MAPI_TRUE;
            int i = 0;
            usleep(100 *1000);
            if (WriteReg(0x8230, 0x02) == FALSE)// Enable read SRAM from I2CS
                bRet = FALSE;
            u8MsbData[0] = DEMOD_ADDR_H;
            u8MsbData[1] = 0;
            u8MsbData[2] = 0;
            if (iptr->WriteBytes(0, 0, 3, u8MsbData) == FALSE)
            {
                bRet = FALSE;
            }
            usleep(100 *1000);
            u8MsbData[0] = DEMOD_READ_REG;
            //while(1)
            {
                iptr->SetSpeed(E_HWI2C_HIGH);
                iptr->ReadBytes( 1, u8MsbData, checknum, getValue);
                //usleep(2000 *1000);
                iptr->SetSpeed(E_HWI2C_SLOW);
            }
            for (i = 0; i < checknum; i++)
            {
                if (MSB122x_table[i + 3] != getValue[i])
                {
                    printf("load msb dsp error : %d,%x,%x \n", i, MSB122x_table[i + 3], getValue[i]);
                    ASSERT(0);
                    bRet = FALSE;
                }
            }
            printf("check over %d \n\n", checknum);
            if (WriteReg(0x8230, 0x0) == FALSE) // Disable read SRAM from I2CS
                bRet = FALSE;
            delete [] getValue;
            if (bRet == FALSE)
                return FALSE;
        }
        else
        {
            printf("sttest no mem to verify dsp \n\n");
        }
    #endif
    if (WriteReg(0x8232, 0x00) == MAPI_FALSE) // MCU SW reset
        return MAPI_FALSE;
#endif
    return MAPI_TRUE;
}
/*@ </Operation ID=Im17018142m1221763cc7cmm45a6> @*/
/************************************************************************************************
Subject:    channel change config
Function:   MSB122x_Config
Parmeter:   BW: bandwidth
Return:     BOOLEAN :
Remark:
 *************************************************************************************************/
MAPI_BOOL DTV_Config(RF_CHANNEL_BANDWIDTH BW, MAPI_BOOL bSerialTS, MAPI_BOOL bPalBG)
{
    MAPI_U8 bandwidth;
    MAPI_U8 status = true;
    switch (BW)
    {
        case E_RF_CH_BAND_6MHz:
            bandwidth = 1;
            break;
        case E_RF_CH_BAND_7MHz:
            bandwidth = 2;
            break;
        case E_RF_CH_BAND_8MHz:
        default:
            bandwidth = 3;
            break;
    }
    Reset();
    //// MSB1228 system init: DVB-T //////////
    gsCmdPacket.cmd_code = CMD_SYSTEM_INIT;
    gsCmdPacket.param[0] = 0;  //E_SYS_DVBT;
    status &= Cmd_Packet_Send(&gsCmdPacket, 1);
    //// DVB-T configurate ///////////////////
    gsCmdPacket.cmd_code = CMD_DVBT_CONFIG;
    gsCmdPacket.param[p_opmode_rfagc_en] = 0;
    gsCmdPacket.param[p_opmode_humdet_en] = 0;
    gsCmdPacket.param[p_opmode_dcr_en] = 1;
    gsCmdPacket.param[p_opmode_iqb_en] = 0;
    gsCmdPacket.param[p_opmode_auto_iq_swap] = 1;
    gsCmdPacket.param[p_opmode_auto_fsa_left] = 1;
    gsCmdPacket.param[p_opmode_auto_rfmax] = 0;
    gsCmdPacket.param[p_opmode_mode_forced] = 0;
    gsCmdPacket.param[p_opmode_cp_forced] = 0;
    gsCmdPacket.param[pc_config_rssi] = 0;
    gsCmdPacket.param[pc_config_zif] = 0;
    #if 1 // (TUNER_TYPE_NT220X==0) // on 2011-2-18 10:49
    gsCmdPacket.param[pc_config_fc_l] = 0x5a;
    gsCmdPacket.param[pc_config_fc_h] = 0x24;
    gsCmdPacket.param[pc_config_fs_l] = 0xa1;
    gsCmdPacket.param[pc_config_fs_h] = 0xb1;
    #else
         //IF frequency = 4000
	// 45473 - 4000 = 41473  = 0xA201
	//45473 = 0xB1A1;
       switch (BW)
       {
           case E_RF_CH_BAND_6MHz:
                    gsCmdPacket.param[pc_config_fc_l] = 0xef;
                    gsCmdPacket.param[pc_config_fc_h] = 0xa4;
                    gsCmdPacket.param[pc_config_fs_l] = 0xa1;
                    gsCmdPacket.param[pc_config_fs_h] = 0xb1;
               break;
           case E_RF_CH_BAND_7MHz:
                    gsCmdPacket.param[pc_config_fc_l] = 0xf5;
                    gsCmdPacket.param[pc_config_fc_h] = 0xa3;
                    gsCmdPacket.param[pc_config_fs_l] = 0xa1;
                    gsCmdPacket.param[pc_config_fs_h] = 0xb1;
               break;
           case E_RF_CH_BAND_8MHz:
           default:
                    gsCmdPacket.param[pc_config_fc_l] = 0x01;
                    gsCmdPacket.param[pc_config_fc_h] = 0xa2;
                    gsCmdPacket.param[pc_config_fs_l] = 0xa1;
                    gsCmdPacket.param[pc_config_fs_h] = 0xb1;
               break;
       }

    #endif
    gsCmdPacket.param[pc_config_bw] = bandwidth;
    gsCmdPacket.param[pc_config_fsa_left] = 0;
    gsCmdPacket.param[pc_config_rfmax] = 1;
    gsCmdPacket.param[pc_config_lp_sel] = 0;
    gsCmdPacket.param[pc_config_cp] = 3;
    gsCmdPacket.param[pc_config_mode] = 1;
    gsCmdPacket.param[pc_config_iq_swap] = 0;
    gsCmdPacket.param[pc_config_atv_system] = bPalBG ? 0 : 1;
    gsCmdPacket.param[pc_config_serial_ts] =bSerialTS;
    #if 1 // (TS_CLK_INV == 1)
    gsCmdPacket.param[pc_config_ts_out_inv] = true;
    #else
     gsCmdPacket.param[pc_config_ts_out_inv]= false;
    #endif
    gsCmdPacket.param[pc_config_ts_data_swap] = 0;
    gsCmdPacket.param[pc_config_icfo_range] = 1; // HD-Forum frequency offset +3;
    // gsCmdPacket.param[pc_config_ts_serial_clk]   = TS_SERIAL_CLK_57p6M;
    status &= Cmd_Packet_Send(&gsCmdPacket, DVBT_PARAM_LEN);
    //// DVB-T AGC_REF_x, ripple_switch_th configure/////

    gsCmdPacket.cmd_code = CMD_TUNED_VALUE;
    // default value
    gsCmdPacket.param[agc_ref_small] = 168;
    gsCmdPacket.param[agc_ref_large] = 248;
    gsCmdPacket.param[agc_ref_aci] = 150;
    // 0x19A = 410
    gsCmdPacket.param[ripple_switch_th_l] = 0x9A;
    gsCmdPacket.param[ripple_switch_th_h] = 0x01;
    status &= Cmd_Packet_Send(&gsCmdPacket, TUNED_PARAM_MAX_NUM);
    return status;
}

MAPI_BOOL SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType)
{
	return MAPI_TRUE;
}

