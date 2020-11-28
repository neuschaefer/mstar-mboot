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
 * Class : mapi_demodulator_msb123x
 * File  : mapi_demodulator_msb123x.cpp
 **********************************************************************/
/*@ </FileComment ID=1246257763790> @*/
/*@ <Include> @*/


#ifndef _MSB123x_C_
#define _MSB123x_C_

#include <MsTypes.h>
#include <MsUboot.h>
#include <MsIRQ.h>
#include <MsOS.h>
#include <msAPI_Tuner.h>
#include <cofdm/MSB123x.h>

//#include <sys/prctl.h>
//#include "MsCommon.h"
//#include "debug.h"
//#include "drvGPIO.h"
////#include "apiSWI2C.h"
//#include "mapi_tuner.h"
//#include "mapi_demodulator.h"
//#include "mapi_i2c.h"
//#include "mapi_i2c_devTable.h"
//#include "mapi_gpio.h"
//#include "mapi_gpio_devTable.h"
//#include "mapi_interface.h"
//#include "device_demodulator.h"
//#include "device_demodulator_msb123x.h"
//#include "msb123x_dvbt.dat"
//#include "drvMMIO.h"
//#include "drvHWI2C.h"
/*@ </Include> @*/
/*@ <Definitions> @*/
#ifndef usleep
#define usleep MsOS_DelayTaskUs
#endif

#ifndef MAPI_BOOL
#define MAPI_BOOL BOOLEAN
#endif
#ifndef MAPI_U8
#define MAPI_U8 U8
#endif
#ifndef MAPI_U16
#define MAPI_U16 U16
#endif
#ifndef MAPI_U32
#define MAPI_U32 U32
#endif
#ifndef MAPI_TRUE
#define MAPI_TRUE TRUE
#endif
#ifndef MAPI_FALSE
#define MAPI_FALSE FALSE
#endif

#define LOADFW 1

#if (LOADFW == 1)
MAPI_U8 MSB123X_LIB[]={
#include <cofdm/msb123x_dvbt.dat>
};
#endif
#define MsOS_ObtainMutex(x,y)
#define MsOS_ReleaseMutex(x)

#define ERR_DOMOD_MSB(x)    x
#define DBG_DOMOD_MSB(x)    //x
#define DBG_DOMOD_FLOW(x)    //x
#define DBG_GET_SIGNAL(x)     //x
#define DBG_DEMOD_LOAD_I2C(x)     //x
#define DBG_DUMP_LOAD_DSP_TIME 0
#define MDrv_Timer_Delayms OS_DELAY_TASK
#define MDrv_Timer_GetTime0 OS_SYSTEM_TIME
//#define TS_CLK_INV 1
#if (LOADFW == 1)
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 1
#else
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 0
#endif
#define LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 1//1
#define SDRAM_DATA_CHECK                 0//1
#define LOAD_CODE_I2C_BLOCK_NUM          0x80
#define SDRAM_BASE                       0x5000


#define MSB123x_BOOT  0x01
#define MSB123x_DVBT2 0x02
#define MSB123x_DVBT  0x04
#define MSB123x_DVBC  0x08
#define MSB123x_ALL   0x0F

#define WIMBLEDON_BOOT_START_ADDR     0x00000
#define WIMBLEDON_BOOT_END_ADDR       0x00FFF
#define WIMBLEDON_DVBT2_P1_START_ADDR 0x01000
#define WIMBLEDON_DVBT2_P1_END_ADDR   0x08FFF
#define WIMBLEDON_DVBT2_P2_START_ADDR 0x09000
#define WIMBLEDON_DVBT2_P2_END_ADDR   0x0FFFF
#define WIMBLEDON_DVBT_START_ADDR     0x10000
#define WIMBLEDON_DVBT_END_ADDR       0x17FFF
#define WIMBLEDON_DVBC_START_ADDR     0x18000
#define WIMBLEDON_DVBC_END_ADDR       0x1FFFF

#define WIMBLEDON_WINDOWS_BASE                0x100
#define WIMBLEDON_BOOT_WINDOWS_OFFSET         WIMBLEDON_WINDOWS_BASE
#define WIMBLEDON_DVBT2_P2_WINDOWS_OFFSET    (WIMBLEDON_WINDOWS_BASE + 0x08)
#define WIMBLEDON_DVBT2_P1_WINDOWS_OFFSET    (WIMBLEDON_DVBT2_P2_WINDOWS_OFFSET + 0x08)
#define WIMBLEDON_DVBT_WINDOWS_OFFSET        (WIMBLEDON_DVBT2_P1_WINDOWS_OFFSET + 0x08)
#define WIMBLEDON_DVBC_WINDOWS_OFFSET        (WIMBLEDON_DVBT_WINDOWS_OFFSET + 0x08)

/*@ </Definitions> @*/
MAPI_U8 u8DeviceBusy = 0;
//MAPI_BOOL device_demodulator::m_bSerialOut = MAPI_FALSE;
//MAPI_U8 device_demodulator::gVifTop = VIF_TOP;
//MAPI_U8 device_demodulator::gVifSoundSystem = (MAPI_U8)VIF_SOUND_DK2;
//MAPI_U8 device_demodulator::gVifIfFreq = (MAPI_U8)IF_FREQ_3890;
U8 u8MsbData[6];
#if (LOADFW == 1)
MAPI_U8 gu8ChipRevId = 0;
#endif
//MAPI_U8 device_demodulator::gCalIdacCh0 = 0;
//MAPI_U8 device_demodulator::gCalIdacCh1 = 0;
//S_CMDPKTREG device_demodulator::gsCmdPacket;
//MAPI_U8 device_demodulator::gu8DemoDynamicI2cAddress = DEMOD_DYNAMIC_SLAVE_ID_1; //0x32;//Default
MAPI_BOOL FECLock = MAPI_FALSE;
//MAPI_BOOL device_demodulator::gbTVAutoScanEn = MAPI_FALSE; //init value=MAPI_FALSE, follow with auto/manual scan
EN_DEVICE_DEMOD_TYPE m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_NULL;
//pthread_t msb123x_pthread_id;

static MAPI_U32 u32ChkScanTimeStart = 0;
static MAPI_BOOL bPower_init_en = MAPI_FALSE;
//static MAPI_U32 g_u32Frequency = 0;

static MAPI_BOOL bDoReset = FALSE;
//MAPI_U32 u32StartTime = 0;
//MAPI_U8 gQamVal;

#define resetDemodTime 100
#define waitFlashTime 1500
//static MS_S32 _s32_Demod_DVBT2_Mutex=-1;
//static MS_S32 _s32_Demod_DVBT2_RW_Mutex=-1;
//static MS_S32 _s32_Demod_DVBT2_RW2_Mutex=-1;

#if (LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
//static MS_U8 g_WO_SPI_FLASH = 1;
#else
//static MS_U8 g_WO_SPI_FLASH = 0;
#endif

#if (LOADFW == 1)
/////////////// CONSTANT /////////////////
#define PAGE_WRITE_SIZE         256
#define VERSION_CODE_ADDR       0xFC0
#define VERSION_CODE_SIZE       32

// ONLY wo flash procedure used.
static MS_U8 g_sdram_code = 0x0;
static MS_U8 g_sram_code  = 0x0;
#endif

MAPI_BOOL LoadDSPCode(void);
MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data);
MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
MAPI_BOOL WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data);
MAPI_BOOL WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size);
void Reset(void);
MAPI_BOOL WriteDspReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
MAPI_BOOL ReadDspReg(MAPI_U16 u16Addr, MAPI_U8* pData);
void Driving_Control(MAPI_BOOL bEnable);
MAPI_BOOL Active(MAPI_BOOL bEnable);
MAPI_BOOL MSB123x_MEM_switch(MAPI_U8 mem_type);
MAPI_BOOL I2C_CH_Reset(MAPI_U8 ch_num);
MAPI_BOOL Power_On_Initialization(void);
#if (LOADFW == 1)
MAPI_BOOL Connect(EN_DEVICE_DEMOD_TYPE enDemodType);
MAPI_BOOL DTV_DVBT2_DSPReg_Init(void);
MAPI_BOOL DTV_DVBT_DSPReg_Init(void);
MAPI_BOOL DTV_DVBC_DSPReg_Init(void);
#endif

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
//###############################  Public:Common Function Implementation ###################################
//##########################################################################################################
//##########################################################################################################
#if (LOADFW == 1)
// 144 ms roughly
MAPI_BOOL MSB123x_HW_init(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8 u8_tmp = 0;
    MAPI_U8 u8_timeout = 0;

    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]MSB123x_HW_init\n"));

    // mask miu access of mcu
    bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
    bRet &= WriteReg(0x1200+(0x23)*2,0xfe);

    // 10us delay
    usleep(10);

    // Reset MCU
    bRet &= WriteReg2bytes(0x0b00+(0x19)*2, 0x0003);

    bRet &= WriteReg2bytes(0x1200, 0x0000);

    // miu software reset for pwr down tolerance
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);

    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);

    // -------------------------------------------------------------------
    // Initialize DMD_ANA_MISC
    // -------------------------------------------------------------------

    // [1:0]    reg_mpll_loop_div_first
    // [15:8]   reg_mpll_loop_div_second
    bRet &= WriteReg2bytes(0x0A00+(0x33)*2, 0x0902);

    // [2:0]    reg_mpll_ictrl
    // [3]  reg_mpll_in_sel
    // [4]  reg_mpll_xtal2adc_sel
    // [5]  reg_mpll_xtal2next_pll_sel
    // [6]  reg_mpll_vco_offset
    // [7]  reg_mpll_pd
    // [8]  reg_xtal_en
    // [10:9]   reg_xtal_sel
    // [11]     reg_mpll_porst
    // [12]     reg_mpll_reset
    // [13]     reg_pd_dmpll_clk
    // [14]     reg_pd_3p3_1
    // [15]     reg_pd_3p3_2

    bRet &= WriteReg2bytes(0x0A00+(0x35)*2, 0x1804);
    bRet &= WriteReg2bytes(0x0A00+(0x35)*2, 0x0004);

    // [0]  reg_mpll_clk_dp_pd  dummy
    // [1]  reg_adc_clk_pd      ADC output clock power down
    // [2]  reg_mpll_div2_pd    MPLL_DIV2 power down
    // [3]  reg_mpll_div3_pd    MPLL_DIV3 power down
    // [4]  reg_mpll_div4_pd    MPLL_DIV4 power down
    // [5]  reg_mpll_div8_pd    MPLL_DIV8 power down
    // [6]  reg_mpll_div10_pd   MPLL_DIV10 power down
    // [13:8]  reg_mpll_adc_div_sel select the ADC clock divide ratio,ADC clk=XTAL_IN * (LOOP_DIV_FIRST*LOOP_DIV_SECOND)/div_ratio

    bRet &= WriteReg2bytes(0x0A00+(0x30)*2, 0x1200);

    // -------------------------------------------------------------------
    // Begin Initialize Initialize ADC I/Q
    // -------------------------------------------------------------------
    // [0]  Q channel ADC power down
    // [1]  I channel ADC power down
    // [2]  Q channel clamp enable. 0:enable, 1:disable
    // [3]  I channel clamp enable. 0:enable, 1:disable
    // [6:4]    I channel input mux control;
    //      3'b000=I channel ADC calibration mode input
    //          3'b001=VIF signal from VIFPGA
    //          3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //          all the other combination are only for test mode, don't use without understanding.
    // [10:8]   Q channel input mux control;
    //      3'b000=Q channel ADC calibration mode input
    //          3'b001=VIF signal from VIFPGA 3'b010 = SSIF signal from PAD_SIFP(M)
    //          3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //          all the other combination are only for test mode, don't use without understanding.
    // [12] ADC I,Q swap enable; 1: swap
    // [13] ADC clock out select; 1: ADC_CLKQ
    // [14] ADC linear calibration bypass enable; 1:enable
    // [15] ADC internal 1.2v regulator control always 0 in T3
    bRet &= WriteReg2bytes(0x0A00+(0x01)*2, 0x0440);


    // [0]  Channel I ADC power down: 1=power dwon
    // [1]  Channel Q ADC power down: 1=power dwon
    // [2]  power down clamp buffer for test mode
    // [3]  change ADC reference voltage for SSIF
    // [6:4]    ADC source bias current control
    // [9:8]    XTAL receiver amp gain
    bRet &= WriteReg2bytes(0x0A00+(0x0c)*2, 0x0002);

    // [3:0]    clamp voltage control
    //          3'b000 = 0.7v
    //          3'b001 = 0.75v
    //          3'b010 = 0.5v
    //          3'b011 = 0.4v
    //          3'b100 = 0.8v
    //          3'b101 = 0.9v
    //          3'b110 = 0.65v
    //          3'b111 = 0.60v
    // [4]  REFERENCE power down
    bRet &= WriteReg2bytes(0x0A00+(0x20)*2, 0x0000);

    // Set ADC gain is 1
    bRet &= WriteReg2bytes(0x0A00+(0x0b)*2, 0x0909);

    // Disable ADC Sign bit
    bRet &= WriteReg2bytes(0x0A00+(0x2e)*2, 0x0200);

    // ADC I channel offset
    bRet &= WriteReg2bytes(0x0A00+(0x2a)*2, 0x0c00);

    // ADC Q channel offset
    bRet &= WriteReg2bytes(0x0A00+(0x2b)*2, 0x0c00);
    // -------------------------------------------------------------------
    // End Initialize Initialize ADC I/Q
    // -------------------------------------------------------------------


    // [15:0]   reg_mpll_test
    // [4]  mpll lock detector enable
    bRet &= WriteReg2bytes(0x0A00+(0x34)*2, 0x0010);


    // @0x0919
    // [5:0]    reg_ckg_spif
    // [15:8]   reg_ckg_miu
    bRet &= WriteReg2bytes(0x0900+(0x19)*2, 0x3c0c);


    // @0x091b
    // [2:0]    reg_ckg_dvbt2_outer1x
    // [6:4]    reg_ckg_dvbt2_outer2x
    // [10:8]   reg_ckg_syn_miu
    // [14:12]  reg_ckg_syn_ts
    bRet &= WriteReg2bytes(0x0900+(0x1b)*2, 0x0000);


    /*Beg initialize MIU*/

    // dummy register setting
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);

    // dummy register setting
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);

    // dummy register setting
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);

    // miu software reset
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);


    // APLL PORST
    bRet &= WriteReg2bytes(0x1200+(0x11)*2, 0x60cc);

    bRet &= WriteReg2bytes(0x1200+(0x11)*2, 0x00cc);

    // set frequence 180MHz
    bRet &= WriteReg2bytes(0x1200+(0x11)*2, 0x0000);



    bRet &= WriteReg2bytes(0x1200+(0x10)*2, 0x4200);  //0x4200 //0x4220 NG //0x4a20 for IQ.TS debugg
    // bRet &= WriteReg2bytes(0x1200+(0x10)*2, 0x3a20);  // miu b/w issue djb fail, michael huang


    // 0x4220 -> 0x5220 for hi/low temp test.

    bRet &= WriteReg2bytes(0x1200+(0x12)*2, 0x4000);

    bRet &= WriteReg2bytes(0x1200+(0x13)*2, 0x0500);

    bRet &= WriteReg2bytes(0x1200+(0x16)*2, 0x0030);

    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0x8100);
    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0xe100);
    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0x8100);

    // in_phase
    bRet &= WriteReg2bytes(0x1200+(0x02)*2, 0x0371);

    // tREFRESH                      : [7:0] * 16
    bRet &= WriteReg2bytes(0x1200+(0x03)*2, 0x0040);

    // reg_tRAS                      : [3:0]         // 48.00 / 6.0ns = 8
    // reg_tRC                       : [7:4]         // 90.00 / 7.5ns = 12
    // reg_tRCD                      : [11:8]        // (min  12.50 ns) / 2.5ns = 5   // 5
    // reg_tRCD                      : [11:8]   // 22.50 / 7.5ns = 3
    // reg_tRP                       : [15:12]       // 22.50 / 7.5ns = 3
    bRet &= WriteReg2bytes(0x1200+(0x04)*2, 0x44c8);


    // reg_tRRD                      : [3:0]         3
    // tWR                           : [7:4]         2
    // reg_tMRD                      : [11:8]        2
    // reg_tRTP                      : [15:12]  0
    // reg_tRAS                      : [3:0]         // 48.00 / 6.0ns = 8
    bRet &= WriteReg2bytes(0x1200+(0x05)*2, 0x0233);


    // reg_w2r_dly(tWTR)             : [3:0]         3
    // reg_w2r_oen_dly               : [7:4]         6
    // reg_r2w_dly                   : [11:8]        6
    // reg_r2w_oen_dly               : [15:12]       8
    bRet &= WriteReg2bytes(0x1200+(0x06)*2, 0x5634);

    // tRFC                          : [5:0]         e
    // reg_tRAS[4]                   : [6]           0
    // reg_tRC[4]                    : [7]           0
    // reg_write_latency             : [10:8]        1
    // reg_tCCD                      : [15:14]       1
    bRet &= WriteReg2bytes(0x1200+(0x07)*2, 0x410e);

    bRet &= WriteReg2bytes(0x1200+(0x0e)*2, 0x1800);

    bRet &= WriteReg2bytes(0x1200+(0x1b)*2, 0x0161);   // 0x0167);

    bRet &= WriteReg2bytes(0x1200+(0x1c)*2, 0x00b0);

    /*Beg SIM SPIF initialize*/

    // mask other request
    bRet &= WriteReg2bytes(0x1200+(0x23)*2, 0x0000);

    // reg_rq0_round_robin : [0]
    bRet &= WriteReg2bytes(0x1200+(0x20)*2, 0xc001);

    // miu software reset
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);


    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);

    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0x010d);

    /*Beg Initial DRAM start here!!!*/

    bRet &= WriteReg2bytes(0x1200+(0x00)*2, 0x0001);

    // wait init_done

    bRet &= ReadReg(0x1201, &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb123x]MIU wait init done, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));
    while( u8_tmp != 0x80)
    {
        if(u8_timeout++>200)
        {
            ERR_DOMOD_MSB(printf("[msb123x][err]MIU init failure...\n"));
            return MAPI_FALSE;
        }
        // 10us delay
        usleep(10);
        bRet &= ReadReg(0x1201, &u8_tmp);
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x]MIU init done, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));
    /*Beg set MIU self test parameter*/

    bRet &= WriteReg2bytes(0x1200+(0x71)*2, 0x0000);

    // length
    bRet &= WriteReg2bytes(0x1200+(0x72)*2, 0x0010);

    // test data
    bRet &= WriteReg2bytes(0x1200+(0x74)*2, 0x5aa5);

    // reg_test_en                   : [0]
    // reg_test_mode                 : [2:1] 00 : address,
    //                                       01 : test data
    //                                       10 : shift data
    // reg_inv_data                  : [3]
    // reg_test_loop                 : [4]
    // reg_force_out                 : [5]
    // reg_force_in                  : [6]
    // reg_read_only                 : [8]
    // reg_write_only                : [9]
    bRet &= WriteReg2bytes(0x1200+(0x70)*2, 0x0001);

    // wait for test done

    bRet &= ReadReg((0x1200+(0x70)*2 + 1), &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb123x]MIU wait test done, u8_tmp=0x%x,bRet=0x%x\n",u8_tmp,bRet));
    while( u8_tmp != 0x80)
    {
        bRet &= ReadReg((0x1200+(0x70)*2 + 1), &u8_tmp);
    }
    // test done.

    // test result check

    bRet &= ReadReg((0x1200+(0x70)*2 + 1),&u8_tmp);

    if( u8_tmp == 0x40 )
    {
        ERR_DOMOD_MSB(printf("@msb123x, error, MIU self test fail !!!!\n"));
        bRet = false;
    }
    else
    {
        DBG_DEMOD_LOAD_I2C(printf("@msb123x, MIU self test successful.\n"));
    }

    bRet &= WriteReg2bytes(0x1200+(0x70)*2, 0x0000);

    /*End initialize MIU*/

    /* Beg Turn on pads */
    // ------Turn off all pad in
    // [0] reg_set_pad_low
    // [1] reg_set_pad_high
    // [2] reg_set_i2cs_pad_low
    // [3] reg_set_i2cs_pad_high
    // [8] reg_turn_off_pad
    bRet &= WriteReg2bytes(0x0900+(0x28)*2, 0x0000);


    // ------IF AGC PWM pad on
    // [0]      reg_rf_agc_pad_oen
    // [1]      reg_if_agc_pad_oen
    // [9:8]    reg_rf_agc_sel[1:0]
    // [11:10]  reg_if_agc_sel[1:0]
    // [13:12]  reg_rf_agc_ctrl_sel[1:0] 1:PWN on 2:UP GPIO on
    // [15:14]  reg_if_agc_ctrl_sel[1:0] 1:PWN on 2:DOWN GPIO on
    bRet &= WriteReg2bytes(0x0900+(0x2a)*2, 0x8001);

    // ------I2CM pad on
    // [1:0]    reg_iicm_pad_sel[1:0]   1:iicm enable 2:UART enable
    // [4]      reg_i2c_sbpm_en     1: enable I2CS bypass to I2CM function
    // [12:8]   reg_i2c_sbpm_idle_num[4:0]  a: default
    bRet &= WriteReg2bytes(0x0900+(0x08)*2, 0x0a01);

    // ------Transport Stream pad on (except TS ERR pad)
    // [15:0]   reg_en_ts_pad[15:0] 0x00ff:normal TS location 0xff00:reverse TS location
    bRet &= WriteReg2bytes(0x0900+(0x2d)*2, 0x00ff);

    // ------Transport Stream pad on (TS ERR pad)
    // [0]      reg_en_ts_err_pad   1: enable
    // [4]      reg_ts_err_pol  1: inverse 0:normal
    bRet &= WriteReg2bytes(0x0900+(0x2e)*2, 0x0001);


    // Initialize special registers

    bRet &= WriteReg(0x0C0E, 0x00);
    bRet &= WriteReg(0x0C0F, 0x00);
    bRet &= WriteReg(0x0C10, 0x00);
    bRet &= WriteReg(0x0C11, 0x00);

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]MSB123x_HW_init, bRet=0x%x\n",bRet));

    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return bRet;

}

// i2c 150Kb/s, average rate 110Kb/s, 32KB, 2436ms.
MAPI_BOOL Load2Sdram(MAPI_U8 *u8_ptr, MAPI_U16 data_length, MAPI_U16 sdram_win_offset_base)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  sdram_win_offset = sdram_win_offset_base;
    MAPI_U16  x_data_offset = 0;
    MAPI_U16  y_cir_addr = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]Load2Sdram, len=0x%x, win_offset=0x%x\n",data_length,sdram_win_offset_base));

    if (I2C_CH_Reset(0) == MAPI_FALSE)
    {
        ERR_DOMOD_MSB(printf(">>>MSB123x CH0 Reset:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {
        // set xData map upper and low bound for 64k DRAM window
        bRet &= WriteReg2bytes(0x2B00+(0x63)*2, 0x3F24);

        // set xData map offset for 64k DRAM window, 64kbytes alignment
        bRet &= WriteReg2bytes(0x2B00+(0x64)*2, 0x0000);

        // set xData map upper and low bound for 4k DRAM window
        bRet &= WriteReg2bytes(0x2B00+(0x65)*2, 0x2014);

        // set xData map offset for 4k DRAM window, 4kbytes alignment
        bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);

        // enable xData map for DRAM
        bRet &= WriteReg2bytes(0x2B00+(0x62)*2, 0x0007);

        for(x_data_offset = 0, y_cir_addr = SDRAM_BASE; x_data_offset < data_length;)
        {
            if (y_cir_addr == 0x6000)
            {
                //set xData map offset for 4k DRAM window, 4kbytes alignment
                // 0x1000, 4096 bytes
                bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);
                y_cir_addr = SDRAM_BASE;
            }

            // max 0x200, error above.....

            if((data_length - x_data_offset) >= LOAD_CODE_I2C_BLOCK_NUM)
            {
                bRet &= WriteRegs(y_cir_addr, (u8_ptr + x_data_offset),LOAD_CODE_I2C_BLOCK_NUM);
                y_cir_addr += LOAD_CODE_I2C_BLOCK_NUM;
                x_data_offset += LOAD_CODE_I2C_BLOCK_NUM;
            }
            else
            {
                bRet &= WriteRegs(y_cir_addr, (u8_ptr + x_data_offset),data_length - x_data_offset);
                y_cir_addr += (data_length - x_data_offset);
                x_data_offset += (data_length - x_data_offset);
            }
        }
        DBG_DEMOD_LOAD_I2C(printf("[msb123x]x_data_offset=%d,y_cir_addr=%d,z_block_num=%d\n",x_data_offset,y_cir_addr,sdram_win_offset));
#if (SDRAM_DATA_CHECK == 1)
        // beg data check.
        DBG_DEMOD_LOAD_I2C(printf("[msb123x]SDRAM data check...\n"));

        sdram_win_offset = sdram_win_offset_base;

        // set xData map offset for 4k DRAM window, 4kbytes alignment
        bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);

        for(x_data_offset = 0, y_cir_addr = SDRAM_BASE; x_data_offset < data_length;)
        {
            MAPI_U8 u8_tmp;
            if (y_cir_addr == 0x6000)
            {
                //set xData map offset for 4k DRAM window, 4kbytes alignment
                // 0x1000, 4096 bytes
                bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);
                y_cir_addr = SDRAM_BASE;
            }

            bRet &= ReadReg(y_cir_addr++, &u8_tmp);
            if(u8_tmp != *(u8_ptr + x_data_offset++))
            {
                ERR_DOMOD_MSB(printf("[msb123x]error, idx=0x%x, y=0x%x, x=0x%x\n",y_cir_addr-1, u8_tmp, *(u8_ptr + x_data_offset-1)));
            }
        }

        DBG_DEMOD_LOAD_I2C(printf("[msb123x]SDRAM data check...Done\n"));

        // end data check
#endif
        //  Release xData map for SDRAM
        bRet &= WriteReg2bytes(0x2B00+(0x62)*2, 0x0000);

        // Channel changed from CH 0x00 to CH 0x03
        if (I2C_CH_Reset(3) == MAPI_FALSE)
        {
            ERR_DOMOD_MSB(printf(">>>MSB123x CH3 Reset:Fail\n"));
            return MAPI_FALSE;
        }
    }

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]Load2Sdram, len=0x%x, win_offset=0x%x\n",data_length,sdram_win_offset_base));
    return bRet;
}

// 92~95ms roughly
MAPI_BOOL LoadSdram2Sram(MAPI_U8 CodeNum)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8   u8_tmp = 0;
    MAPI_U8   u8DoneFlag = 0;
    MAPI_U32  u32Timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadSdram2Sram, g_sram_code=0x%x, codeNum=0x%x\n",g_sram_code,CodeNum));

    if(CodeNum == g_sram_code)
    {
        DBG_DEMOD_LOAD_I2C(printf("[msb123x]LoadSdram2Sram, code is available.\n"));
        return bRet;
    }

    bRet &= MSB123x_MEM_switch(0);

    if(CodeNum == MSB123x_DVBT2)
        u8_tmp = 1|0x10;
    else if(CodeNum == MSB123x_DVBT)
        u8_tmp = 2|0x10;
    else if(CodeNum == MSB123x_DVBC)
        u8_tmp = 3|0x10;
    else
        u8_tmp = 0|0x10;

    // Assign f/w code type to load => 0x11: dvbt2, 0x12: dvbt, 0x13: dvbc
    bRet &= WriteReg(0x0900+(0x4f)*2, u8_tmp);

    // enable miu access of mcu gdma
    bRet &= WriteReg(0x1200+(0x23)*2,0xf0);

    // 10us delay
    usleep(10);

    // enable mcu
    bRet &= WriteReg(0x0b00+(0x19)*2, 0x00);

    do
    {
        bRet &= ReadReg(0x0900+(0x4f)*2, &u8DoneFlag);

        if (u32Timeout++ > 500)
        {
            printf("@msb123x, LoadSdram2Sram boot move code fail.!!!\n");
            return MAPI_FALSE;
        }
        usleep(1*1000);

    } while(u8DoneFlag != 0xaa);

    // mask miu access of mcu
    bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
    bRet &= WriteReg(0x1200+(0x23)*2,0xfe);

    // 10us delay
    usleep(10);

    // Reset MCU
    bRet &= WriteReg(0x0b00+(0x19)*2, 0x03);

    bRet &= MSB123x_MEM_switch(1);

    if(bRet == false)
    {
        g_sram_code = 0x00;
    }
    else
    {
        g_sram_code = CodeNum;
    }

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadSdram2Sram, codeNum=0x%x, g_sram_code=0x%x, bRet=0x%x\n",CodeNum,g_sram_code,bRet));

    return bRet;
}


MAPI_BOOL LoadDspCodeToSDRAM_Boot(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size = 0, win_offset = 0;
    MAPI_U8   *data_ptr = NULL;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_Boot\n"));

    if(!(g_sdram_code&MSB123x_BOOT))
    {
        if(sizeof(MSB123X_LIB) > WIMBLEDON_BOOT_START_ADDR)
        {
            // boot code
            data_ptr = MSB123X_LIB + WIMBLEDON_BOOT_START_ADDR;
            code_size = WIMBLEDON_BOOT_END_ADDR - WIMBLEDON_BOOT_START_ADDR + 1;
            win_offset = WIMBLEDON_BOOT_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if(bRet == true)
            {
                g_sdram_code |= MSB123x_BOOT;
            }
        }
        else
        {
            printf("@msb123x, boot code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_Boot\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbt2(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size = 0, win_offset = 0;
    MAPI_U8   *data_ptr = NULL;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_dvbt2\n"));

    if( !(g_sdram_code&MSB123x_DVBT2) )
    {
        if(sizeof(MSB123X_LIB) > WIMBLEDON_DVBT2_P1_START_ADDR)
        {
            // dvbt2_p2
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBT2_P2_START_ADDR;
            code_size = WIMBLEDON_DVBT2_P2_END_ADDR - WIMBLEDON_DVBT2_P2_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBT2_P2_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);

            // dvbt2_p1
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBT2_P1_START_ADDR;
            code_size = WIMBLEDON_DVBT2_P1_END_ADDR - WIMBLEDON_DVBT2_P1_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBT2_P1_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);

            if(bRet == true)
            {
                g_sdram_code |= MSB123x_DVBT2;
            }
        }
        else
        {
            ERR_DOMOD_MSB(printf("@msb123x, dvbt2 code is unavailable!!!\n"));
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_dvbt2\n"));

    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbt(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size = 0, win_offset = 0;
    MAPI_U8   *data_ptr = NULL;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_dvbt\n"));

    if(!(g_sdram_code&MSB123x_DVBT))
    {
        // dvbt code
        if(sizeof(MSB123X_LIB) > WIMBLEDON_DVBT_START_ADDR)
        {
         data_ptr = MSB123X_LIB + WIMBLEDON_DVBT_START_ADDR;
         code_size = WIMBLEDON_DVBT_END_ADDR - WIMBLEDON_DVBT_START_ADDR + 1;
         win_offset = WIMBLEDON_DVBT_WINDOWS_OFFSET;
         bRet &= Load2Sdram(data_ptr,code_size,win_offset);
         if(bRet == true)
         {
             g_sdram_code |= MSB123x_DVBT;
         }
        }
        else
        {
         printf("@msb123x, dvbt code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_dvbt\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbc(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size = 0, win_offset = 0;
    MAPI_U8   *data_ptr = NULL;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_dvbc\n"));
    if(!(g_sdram_code&MSB123x_DVBC))
    {
        // dvbc code
        if(sizeof(MSB123X_LIB) > WIMBLEDON_DVBC_START_ADDR)
        {
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBC_START_ADDR;
            code_size = WIMBLEDON_DVBC_END_ADDR - WIMBLEDON_DVBC_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBC_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if(bRet == true)
            {
               g_sdram_code |= MSB123x_DVBC;
            }
        }
        else
        {
            printf("@msb123x, dvbc code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_dvbc\n"));
    return bRet;
}


// [0] bootloader [1] dvbt2, [2] dvbt, [3] dvbc [4] all
MAPI_BOOL LoadDspCodeToSDRAM(MAPI_U8 code_n)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM, code_n=0x%x\n",code_n));

    switch(code_n)
    {
        case MSB123x_BOOT:
            {
                // boot code
                bRet &= LoadDspCodeToSDRAM_Boot();
            }
        break;
        case MSB123x_DVBT2:
            {
                // dvbt2 code
                bRet &= LoadDspCodeToSDRAM_dvbt2();
            }
            break;
        case MSB123x_DVBT:
            {
                // dvbt
                bRet &= LoadDspCodeToSDRAM_dvbt();
            }
            break;
        case MSB123x_DVBC:
            {
                // dvbtc
                bRet &= LoadDspCodeToSDRAM_dvbc();
            }
            break;
        case MSB123x_ALL:
        default:
            {
                // boot+dvbt2+dvbt+dvbc

                // boot code
                bRet &= LoadDspCodeToSDRAM_Boot();

                // dvbt2
                bRet &= LoadDspCodeToSDRAM_dvbt2();
                // dvbt
                usleep(20);
                bRet &= LoadDspCodeToSDRAM_dvbt();
                // dvbtc
              //  bRet &= LoadDspCodeToSDRAM_dvbc();
            }
            break;
    }

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM, code_n=0x%x, bRet=0x%x\n",code_n,bRet));
    return bRet;
}

// mem_type 0: dram, 1:dram+sram
// 28 ms roughly
MAPI_BOOL MSB123x_MEM_switch(MAPI_U8 mem_type)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8 u8_tmp = 0;
    MAPI_U16 timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]MSB123x_MEM_switch, mem_type=0x%x\n",mem_type));

    if(mem_type == 1)
    {

        bRet &= WriteReg(0x2B80,0x10);

        // SRAM_START_ADDR 0x0000
        bRet &= WriteReg2bytes(0x1000,0x0000);
        bRet &= WriteReg2bytes(0x1004,0x0000);

        // SRAM_END_ADDR 0x7FFF
        bRet &= WriteReg2bytes(0x1002,0x0000);
        bRet &= WriteReg2bytes(0x1006,0x7FFF);

        // DRAM_START_ADDR 0x8000
        bRet &= WriteReg2bytes(0x1008,0x0000);
        bRet &= WriteReg2bytes(0x100C,0x8000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= WriteReg2bytes(0x100A,0x0000);
        bRet &= WriteReg2bytes(0x100E,0xFFFF);

        // Enable SRAM&SDRAM memory map
        bRet &= WriteReg(0x1018,0x05);

        // Wait memory map to be enabled
        do{
            bRet &= ReadReg(0x1018,&u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb123x, D+S memory mapping failure.!!!\n");
                return MAPI_FALSE;
            }
        }while (u8_tmp != 0x05);
    }
    else if(mem_type == 0)
    {
        // Enable SRAM&SDRAM memory map

        bRet &= WriteReg(0x2B80,0x10);

        // DRAM_START_ADDR 0x8000
        bRet &= WriteReg2bytes(0x1008,0x0000);
        bRet &= WriteReg2bytes(0x100C,0x0000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= WriteReg2bytes(0x100A,0x0000);
        bRet &= WriteReg2bytes(0x100E,0x7FFF);

        // Enable SRAM&SDRAM memory map
        bRet &= WriteReg(0x1018,0x04);

        // Wait memory map to be enabled
        do{
            bRet &= ReadReg(0x1018,&u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb123x, D memory mapping failure.!!!\n");
                return MAPI_FALSE;
            }
        }while (u8_tmp != 0x04);
    }
    else
    {
       printf("@msb123x, invalid mem type mapping.\n");
       return MAPI_FALSE;
    }

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]MSB123x_MEM_switch, , mem_type=0x%x, bRet=0x%x\n",mem_type,bRet));

    return bRet;
}

MAPI_BOOL IspProcFlash(MAPI_U8* pLibArry, MAPI_U32 dwLibSize)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U32    dwLoop = 0, dwTimeOut = 0;
    MAPI_U32    dwStartAddr = 0, dwEndAddr = 0;
    //MAPI_U16    wLoop;
    MAPI_U8     bError = false;//, bWriteData[PAGE_WRITE_SIZE];

    MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
  //  mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_2);
  //  iptr->WriteBytes(0, NULL, 5, bWriteData);
  	MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,0, NULL, 5, bWriteData);

    dwStartAddr = (MAPI_U32) 0;
    dwEndAddr = dwLibSize;


    MAPI_U8     bAddr[1];
    MAPI_U8     bReadData=0;
    for(dwLoop=dwStartAddr; (dwLoop<=dwEndAddr); dwLoop+=PAGE_WRITE_SIZE)
    {

        dwTimeOut = 10000;

        while(dwTimeOut--)
        {
            bAddr[0] = 0x10;
            bWriteData[0] = 0x05;
            //iptr->WriteBytes(1, bAddr, 1, bWriteData);
			MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,1, bAddr, 1, bWriteData);

            bAddr[0] = 0x11;
            //iptr->ReadBytes(1, bAddr, 1, &bReadData);
           	MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,1, bAddr, 1, &bReadData);

            bWriteData[0] = 0x12;
           // iptr->WriteBytes(0, NULL, 1, bWriteData);
			MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,0, NULL, 1, bWriteData);

            if (!(bReadData & 0x01))
                break;

            if(dwTimeOut==1)
            {
                bError = 1;
                break;
            }
            usleep(0);
        }

        if(!bError)
        {

            MAPI_U8    bAddr[5], bWriteData[1];
            MAPI_BOOL bError = TRUE;

            //mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_2);

            bAddr[0] = 0x10;
            bWriteData[0] = 0x06;
         //   bError &= iptr->WriteBytes(1, bAddr, 1, bWriteData);
			MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,1, bAddr, 1, bWriteData);

            bWriteData[0] = 0x12;
           // bError &= iptr->WriteBytes(0, NULL, 1, bWriteData);
			MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,0, NULL, 1, bWriteData);

            // Page Program
            bAddr[0] = 0x10;
            bAddr[1] = 0x02;
            bAddr[2] = dwLoop >> 16;
            bAddr[3] = dwLoop >> 8;
            bAddr[4] = dwLoop;

          //  bError &= iptr->WriteBytes(5, bAddr, PAGE_WRITE_SIZE, (pLibArry+dwLoop));
			bError &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,5, bAddr, PAGE_WRITE_SIZE, (pLibArry+dwLoop));

            bWriteData[0] = 0x12;
          //  bError &=  iptr->WriteBytes(0, NULL, 1, bWriteData);
			bError &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,0, NULL, 1, bWriteData);

            bAddr[0] = 0x10;
            bWriteData[0] = 0x04;
           // bError &=  iptr->WriteBytes(1, bAddr, 1, bWriteData);
			bError &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,1, bAddr, 1, bWriteData);

            bWriteData[0] = 0x12;
            //    bError &=  iptr->WriteBytes(0, NULL, 1, bWriteData);
				bError &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,0, NULL, 1, bWriteData);

            if(bError == FALSE)
            {
                break;
            }
        }
    }

    bWriteData[0]=0x24 ;
  //  iptr->WriteBytes(0, NULL, 1, bWriteData);
	MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID_2,0, NULL, 1, bWriteData);

    if(bError==false)
        return MAPI_TRUE;
    else
        return MAPI_FALSE;

}
#endif
#if (LOADFW == 1)
void PreLoadDSPcode(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
 //   prctl(PR_SET_NAME, (unsigned long)"PreLoadDSPcode");

    ERR_DOMOD_MSB(printf("[msb123x][beg] PreLoadDSPcode beg...\n"));

    MAPI_BOOL bRet = true;
    MAPI_U8     status = TRUE;

    Connect(E_DEVICE_DEMOD_DVB_T);

    status &= I2C_CH_Reset(3);
    if(status == MAPI_FALSE)
    {
        ERR_DOMOD_MSB(printf("[msb123x][err] I2C_CH_Reset failure...\n"));
    }

    status &= MSB123x_HW_init();
    if(status == MAPI_FALSE)
    {
        ERR_DOMOD_MSB(printf("[msb123x][err] MSB123x_HW_init failure...\n"));
    }

    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);

    status &= LoadDspCodeToSDRAM(MSB123x_ALL);
    if(status == MAPI_FALSE)
    {
        ERR_DOMOD_MSB(printf("[msb123x][err] LoadDspCodeToSDRAM failure...\n"));
    }

    MAPI_U8 u8Data = 0;
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            u8Data=MSB123x_DVBT2;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            u8Data=MSB123x_DVBT;
            break;
        case E_DEVICE_DEMOD_DVB_C:
            u8Data=MSB123x_DVBC;
            break;
        default:
            u8Data=MSB123x_DVBT;
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
          //  goto ExitPreload;
            break;
    }
    // mask miu access for all and
    bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
    bRet &= WriteReg(0x1200+(0x23)*2,0xfe);

    // 10us delay
    usleep(10);

    status &= WriteReg(0x0b00+(0x19)*2, 0x03);

    status &= LoadSdram2Sram(u8Data);

    // enable miu access of mcu gdma
    bRet &= WriteReg(0x1200+(0x23)*2,0xf0);

    // 10us delay
    usleep(10);

    // Enable MCU
    status &= WriteReg(0x0b00+(0x19)*2, 0x00);

    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            DTV_DVBT2_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_T:
            DTV_DVBT_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_C://mick
            DTV_DVBC_DSPReg_Init();
            break;

        default:
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            //goto ExitPreload;
    }

    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);

    if(status == MAPI_FALSE)
    {
        ERR_DOMOD_MSB(printf(">>>>MSB123x:Fail\n"));
    }
    else
    {
        bPower_init_en = TRUE;
    }
  //  pthread_exit(NULL);
}
#endif

/*@ <Operation ID=I2b28dd03m121c8cf959bmm722c> @*/
MAPI_BOOL Connect(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    DBG_DOMOD_MSB(printf("device_demodulator_msb123x: Connect type=%d\n",(int)enDemodType));
    if (u8DeviceBusy == 1)
        return MAPI_FALSE;
    m_enCurrentDemodulator_Type = enDemodType;
    u8DeviceBusy = 1;
    return MAPI_TRUE;
}

/*@ <Operation ID=I2b28dd03m121c8cf959bmm7207> @*/
MAPI_BOOL Disconnect(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    DBG_DOMOD_MSB(printf("device_demodulator_msb123x: Disconnect\n"));
    u8DeviceBusy = 0;
    return MAPI_TRUE;
}

/*@ <Operation ID=I2b28dd03m121c8cf959bmm71bd> @*/
void Reset(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U8     u8Data = 0x00;
    MAPI_U32    u32Retry = 0x00;

    DBG_DOMOD_MSB(printf(">>>MSB123x: Reset()\n"));
    //DBG_DOMOD_MSB(printf("\t\t\tRESET TIME   %ld\n", u32StartTime));//to measure time
    bDoReset = TRUE;

    // mask miu access for all and mcu
    bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
    bRet &= WriteReg(0x1200+(0x23)*2,0xfe);

    // 10us delay
    usleep(10);

    // reset mcu
    WriteReg(0x0B00+(0x19)*2, 0x03);
    WriteReg(0x0C00, 0x00); //clear MB_CNTL
    if(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T2)
    {
        WriteReg(0x0B00+(0x10)*2, 0x03);
    }
    else if ((m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T) ||
             (m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_C))
    {
        WriteReg(0x0B00+(0x10)*2, 0x00);
    }
    usleep(5 *1000);

    // enable miu access of mcu gdma
    bRet &= WriteReg(0x1200+(0x23)*2,0xf0);

    // 10us delay
    usleep(10);

    // enable mcu
    WriteReg(0x0B00+(0x19)*2, 0x00);
    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        ReadReg(0x0C00, &u8Data);       //check MB_CNTL ready
        while(u8Data != 0xff)
        {
            usleep(50*1000);
            ReadReg(0x0C00, &u8Data);       //check MB_CNTL ready
             if (u32Retry++ > 200)
            {
                ERR_DOMOD_MSB(printf(">>>MSB123x: Reset Fail!\n"));
                break;
            }
        }
    }
    printf(">>>MSB123x: Reset ok!\n");

    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm71bd> @*/
MAPI_BOOL IIC_Bypass_Mode(MAPI_BOOL enable)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8 u8Retry=10;

    DBG_DOMOD_MSB(printf(">>>MSB123x: IIC_bypass() set %x\n", enable));

//FRA_T2_BRINGUP
    while(u8Retry--)
    {
        if (enable)
            WriteReg(0x0900+(0x08)*2, 0x10);// IIC by-pass mode on
        else
            WriteReg(0x0900+(0x08)*2, 0x00);// IIC by-pass mode off
    }
    return MAPI_TRUE;
}

/*@ <Operation ID=Im17018142m1221763cc7cmm46c6> @*/
MAPI_BOOL Power_On_Initialization(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
	PreLoadDSPcode();
#endif

    return MAPI_TRUE;
}

/*@ </Operation ID=Im17018142m1221763cc7cmm46c6> @*/
MAPI_BOOL Set_PowerOn(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    return TRUE;
}

MAPI_BOOL Set_PowerOff(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    return TRUE;
}
//--------------------------------------------------------------------- for DVB-T
//operation
#define RFAGC_EN        0x00
#define HUMDET_EN       0x00
#define DCR_EN          0x01
#define IIS_EN          0x01
#define CCI_EN          0x01
#define ACI_EN          0x01
#define IQB_EN          0x00
#define AUTO_IQ_SWAP    0x01
#define AUTO_RFMAX      0x00
#define AUTO_ACI        0x00
#define MODE_CP_FORCED  0x00
#define TPS_FORCED      0x00
#define AUTO_SCAN       0x00
#define RSV_0D          0x00
#define RSV_0E          0x00
#define RSV_0F          0x00

//configure
#define RSSI            0x00
#define ZIF             0x00
#define FREQ            0x00
#ifdef TUNER_TYPE_NXP_TDA18273HN
#define FC_L            0xA6 // 0xE0 IF=4MHz // Low IF// FC=Fs-IF, IF=4.57MHz
#define FC_H            0xA9 //0xAB IF=4MHz //0xA9 IF=4.57MHz
#else
#define FC_L            0xE0 // Normal IF  // FC=Fs-IF, IF=36MHz
#define FC_H            0x2E
#endif
#define FS_L            0x80
#define FS_H            0xBB
#define BW              0x03
#define MODE            0x01
#define CP              0x03
#define LP_SEL          0x00
#define CSTL            0x00
#define HIER            0x00
#define HPCR            0x00
#define LPCR            0x00
#define IQ_SWAP         0x00
#define RFMAX           0x01
#define ATV_SYSTEM      0x01
#define ICFO_RANGE      0x01
#define RFAGC_REF               0x64
#define IFAGC_REF_2K            0x4B
#define IFAGC_REF_8K            0x4B
#define IFAGC_REF_ACI           0x4B
#define IFAGC_REF_IIS_2K        0xA0
#define IFAGC_REF_IIS_8K        0xA0
#define IFAGC_ACI_DET_TH_L      0x9A
#define IFAGC_ACI_DET_TH_H      0x01
#define SERIAL_TS               0x00
#define TS_SERIAL_CLK           0x00
#define TS_OUT_INV              0x01
#define TS_DATA_SWAP            0x00
#define SFO_2K_H                0x00
#define SFO_2K_L                0xC8
#define SFO_8K_H                0x00
#define SFO_8K_L                0xC8
#define CHECK_CHANNEL           0x00
#define SNR_POS                 0x00
#define CCI_KP                  0x00
#define CCI_FSWEEP              0x00
#define TS_CLK_RATE_AUTO        0x00
#define DVBT_CRC                0x00


MAPI_U8 MSB1231_DVBT_DSPREG_TABLE[] = // andy 2009-12-15 ¿ÀÈÄ 3:55:03 TW model
{
    RFAGC_EN,     HUMDET_EN,    DCR_EN,     IIS_EN,         CCI_EN,      ACI_EN,
    IQB_EN,       AUTO_IQ_SWAP, AUTO_RFMAX, AUTO_ACI,       MODE_CP_FORCED, TPS_FORCED,
    AUTO_SCAN,    RSV_0D,       RSV_0E,     RSV_0F,
    RSSI,         ZIF,          FREQ,       FC_L,           FC_H,        FS_L,      FS_H,
    BW,           MODE,         CP,         LP_SEL,         CSTL,        HIER,      HPCR,
    LPCR,         IQ_SWAP,      RFMAX,      ATV_SYSTEM,     ICFO_RANGE,  RFAGC_REF,
    IFAGC_REF_2K, IFAGC_REF_8K, IFAGC_REF_ACI,  IFAGC_REF_IIS_2K,  IFAGC_REF_IIS_8K, IFAGC_ACI_DET_TH_L,
    IFAGC_ACI_DET_TH_H,         SERIAL_TS,  TS_SERIAL_CLK,  TS_OUT_INV,  TS_DATA_SWAP,
    SFO_2K_H,     SFO_2K_L,     SFO_8K_H,   SFO_8K_L,       CHECK_CHANNEL,          SNR_POS,
    CCI_KP,       CCI_FSWEEP    ,TS_CLK_RATE_AUTO, DVBT_CRC
};

MAPI_U8  DTV_DVBT_DSPReg_CRC(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_U8 crc = 0;
    MAPI_U8 idx = 0;

    for (idx = 0; idx<((MAPI_U8)DVBT_PARAM_LEN - (MAPI_U8)T_OPMODE_RFAGC_EN - 1); idx++)
    {
        crc ^= MSB1231_DVBT_DSPREG_TABLE[idx];
    }

    crc = ~crc;

    return crc;
}

void  DTV_DVBT_DSPReg_ReadBack(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_U8 ret = 0;
    MAPI_U8 idx = 0;

    for (idx = T_OPMODE_RFAGC_EN; idx< (MAPI_U8)DVBT_PARAM_LEN; idx++)
    {
        ReadDspReg(idx,&ret);
        printf("@msb123x, idx=0x%x, dsp=0x%x, sw=0x%x\n",idx,ret,MSB1231_DVBT_DSPREG_TABLE[idx-(MAPI_U8)T_OPMODE_RFAGC_EN]);
    }

    return;
}



MAPI_BOOL  DTV_DVBT_DSPReg_Init(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8    idx = 0;

    for (idx = 0; idx<((MAPI_U8)DVBT_PARAM_LEN - (MAPI_U8)T_OPMODE_RFAGC_EN - 1); idx++)
    {
        if( WriteDspReg(idx + (MAPI_U8)T_OPMODE_RFAGC_EN, MSB1231_DVBT_DSPREG_TABLE[idx])!=TRUE)
        {
            ERR_DOMOD_MSB(printf("dsp reg init NG\n"));
            return FALSE;
        }
    }

    MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_PARAM_CHECK_SUM-(MAPI_U8)T_OPMODE_RFAGC_EN] = DTV_DVBT_DSPReg_CRC();

    if( WriteDspReg((MAPI_U8)T_PARAM_CHECK_SUM, MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_PARAM_CHECK_SUM-(MAPI_U8)T_OPMODE_RFAGC_EN])!=TRUE)
    {
        ERR_DOMOD_MSB(printf("dsp reg write crc NG\n"));
        return FALSE;
    }

    printf("dsp reg init ok\n");

    return MAPI_TRUE;
}


//configure
//--------------------------------------------------------------------- for DVB-T2
// BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
#define T2_BW_VAL           0x04

// FC: FC = FS - IF = 48000 - 4500 = 0xA9EC     (4.50MHz IF)
// FC: FC = FS - IF = 48000 - 36000 = 0x2EE0   (36.0MHz IF)
// FC: FC = FS - IF = 48000 - 4570 = 0xA9A6     (4.57MHz IF)
#ifdef TUNER_TYPE_NXP_TDA18273HN
#define T2_FC_L_VAL            0xA6 //0xE0 IF=4MHz // IF=4MHz //0xA6 // Low IF, IF = 4.57MHz
#define T2_FC_H_VAL            0xA9 //0xAB IF=4MHz //0xA9 IF=4.57MHz// Normal IF
#else
#define T2_FC_L_VAL            0xE0
#define T2_FC_H_VAL            0x2E
#endif
#define T2_TS_SERIAL_VAL       0x00
#define T2_TS_CLK_RATE_VAL     0x06
#define T2_TS_OUT_INV_VAL      0x01
#define T2_TS_DATA_SWAP_VAL    0x00
#define T2_TS_ERR_POL_VAL      0x00

MAPI_U8 MSB1231_DVBT2_DSPREG_TABLE[] =
{
    T2_BW_VAL,     T2_FC_L_VAL,     T2_FC_H_VAL
};

MAPI_BOOL DTV_DVBT2_DSPReg_Init(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8    idx = 0;
    for (idx = 0; idx<sizeof( MSB1231_DVBT2_DSPREG_TABLE); idx++)
    {
        if( WriteDspReg(idx + 0x40, MSB1231_DVBT2_DSPREG_TABLE[idx])!=TRUE)
        {
            printf("T2 dsp reg init NG\n");
            return FALSE;
        }
    }

    if( WriteDspReg((MAPI_U8)T2_TS_SERIAL, T2_TS_SERIAL_VAL) != TRUE)
    {
      printf("T2 dsp reg init NG\n");
    }
    if( WriteDspReg((MAPI_U8)T2_TS_CLK_RATE, T2_TS_CLK_RATE_VAL) != TRUE)
    {
      printf("T2 dsp reg init NG\n");
    }
    if( WriteDspReg((MAPI_U8)T2_TS_OUT_INV, T2_TS_OUT_INV_VAL) != TRUE)
    {
      printf("T2 dsp reg init NG\n");
    }
    if( WriteDspReg((MAPI_U8)T2_TS_DATA_SWAP, T2_TS_DATA_SWAP_VAL) != TRUE)
    {
      printf("T2 dsp reg init NG\n");
    }
    if( WriteDspReg((MAPI_U8)T2_TS_ERR_POL, T2_TS_ERR_POL_VAL) != TRUE)
    {
      printf("T2 dsp reg init NG\n");
    }

    printf("T2 dsp reg init ok\n");

    return MAPI_TRUE;
}
//--------------------------------------------------------------------- for DVB-C
#define SR0_H_AUTO              0x0F
#define SR0_L_AUTO              0xA0
#define SR0_H                   0x1A
#define SR0_L                   0xDB
/*
#define REAGC_EN                0x00 //0x20
#define HUMDET_EN_C             0x00
#define DCR_EN                  0x01
#define IQB_EN                  0x00
#define AUTO_IQ                 0x01
#define AUTO_RFMAX              0x00
#define AUTO_ACI                0x01
*/
#define AUTO_SCAN               0x00
#define AUTO_SCAN_SYM_RATE      0x00 //0x28
#define AUTO_SCAN_QAM           0x00
#define ATV_DET_EN              0x01 //0x2A
/*
#define RSV_0B                  0x00
#define RSV_0C                  0x00
#define RSV_0D                  0x00
#define RSV_0E                  0x00
#define RSV_0F                  0x00
*/
#define RSSI                    0x00 //0x30
#define ZIF                     0x00
#define FREQ                    0x00
#ifdef TUNER_TYPE_NXP_TDA18273HN
#define FC_L_DVBC               0xA6 // Low IF, IF = 4.57MHz
#define FC_H_DVBC               0xA9
#else
#define FC_L_DVBC               0xE0 // Normal IF
#define FC_H_DVBC               0x2E
#endif
#define FS_L                    0x80
#define FS_H                    0xBB
#define BW_L                    0xDB
#define BW_H                    0x1A
#define BW1_L                   0xF4
#define BW1_H                   0x1A
#define BW2_L                   0xDB
#define BW2_H                   0x1A
#define BW3_L                   0xDB
#define BW3_H                   0x1A
//#define RSV_0x1F              0x00
//#define RFMAX                     0x00 //0x40
#define QAM                     0x02
#define IQ_SWAP_C               0x01
#define CCI                     0x00
#define SERIAL_TS               0x00 //0: parallel 1:serial
//#define TS_SERIAL_CLK           0x05
#define TS_OUT_INV              0x01 //
#define TS_DATA_SWAP            0x00

MAPI_U8 MSB1231_DVBC_DSPREG_TABLE[] =
{
    00,     00,     01,     00,     01,     00,     01,       AUTO_SCAN,
    AUTO_SCAN_SYM_RATE, AUTO_SCAN_QAM,  ATV_DET_EN,     00,     00,     00,     00,     00,
    00,     00,     00,     FC_L_DVBC,      FC_H_DVBC,           FS_L,           FS_H,
    BW_L,       BW_H,       BW1_L,      BW1_H,      BW2_L,      BW2_H,      BW3_L,      BW3_H,      00,
    00,     QAM,        IQ_SWAP_C,      CCI,        SERIAL_TS,      05,
    TS_OUT_INV,     TS_DATA_SWAP
};

MAPI_BOOL  DTV_DVBC_DSPReg_Init(void)
{
    /*DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8    idx = 0;

    for (idx = 0; idx<((MAPI_U8)DVBC_PARAM_LEN - (MAPI_U8)C_opmode_rfagc_en - 1); idx++)
    {
        if( WriteDspReg(idx + (MAPI_U8)C_opmode_rfagc_en, MSB1231_DVBC_DSPREG_TABLE[idx])!=TRUE)
        {
            ERR_DOMOD_MSB(printf("dsp reg init NG\n"));
            return FALSE;
        }
    }
    ERR_DOMOD_MSB(printf("DVBC dsp reg init ok\n"));
*/
    return MAPI_TRUE;
}

/*@ <Operation ID=Im17018142m1221763cc7cmm464e> @*/
MAPI_BOOL Active(MAPI_BOOL bEnable)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8  status = MAPI_TRUE;
    bEnable = bEnable;
    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
    //FRA_T2_BRINGUP
        return MAPI_TRUE;
    }
    else if ((m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T)
       || (m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_C))
    {
        printf(" @MSB1231_active\n");

        WriteReg(0x0C00+(0x0E)*2, 0x0001);  // FSM_EN

        if(status)
        {
            printf(" @MSB1231_Active OK\n");
            return  MAPI_TRUE;
        }
        else
        {
            printf(" @MSB1231_Active NG\n");
            return MAPI_FALSE;
        }
    }
    return MAPI_FALSE;
}

#if 1
MAPI_BOOL ExtendCmd(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8 u8Data = 0;
    MAPI_U8 u8Status = MAPI_TRUE;


    SubCmd=SubCmd;
    u32Param1=u32Param1;
    u32Param2=u32Param2;
    pvParam3=pvParam3;

    if (SubCmd ==3)
    {
        //Read register from dvbt demod
        return ReadReg((MAPI_U16)u32Param1,(MAPI_U8*)pvParam3);
    }
    if (SubCmd ==4)
    {
        //Write register from dvbt demod
        return WriteReg((MAPI_U32) u32Param1,(MAPI_U8) u32Param2);
    }

    if (SubCmd == 0x80) // temp solution, to turn on/off IF AGC
    {
        if (u32Param1 == 1)         // turn on
        {
            u8Status &= WriteReg2bytes(0x0900+(0x2a)*2, 0x8001);
            ReadReg(0x0900+(0x2a)*2+1, &u8Data);
            printf("MSB123x: Turn on IF AGC: %02x\n", u8Data);
        }
        else if (u32Param1 == 0)    // turn off
        {
            u8Status &= ReadReg(0x0900+(0x2a)*2+1, &u8Data);
            u8Status &= WriteReg(0x0900+(0x2a)*2+1, (u8Data&0x3F));
            u8Status &= ReadReg(0x0900+(0x2a)*2+1, &u8Data);
            printf("MSB123x: Turn off IF AGC: %02x\n", u8Data);;
            //UNUSED(u8Data);
            //UNUSED(u8Status);
        }
    }

    if(SubCmd == 0x81)
    {
        if(u32Param1 == 1)
        {
            WriteReg2bytes(0x0900+(0x2d)*2, 0x00ff);
        }
        else
        {
            WriteReg2bytes(0x0900+(0x2d)*2, 0x0000);
        }
    }


    if (SubCmd == 0xFF) // temp solution, only for internal use, can't be called by upper layer
    {
        MAPI_U32    u32Timeout = 0;
        MAPI_U32    u32LockTimeout = 2000;
        MAPI_U8     u8Data = 0;
        MAPI_U16    u16RegAddress = 0;
        MAPI_U8     u8LockState = 0;
        MAPI_U8     u8BitMask = 0;
        MAPI_BOOL   bCheckPass=FALSE;
        static MAPI_U32 u32LockTimeStartDVBT = 0;
        static MAPI_U32 u32LockTimeStartDVBC = 0;//mick
        static MAPI_U32 u32LockTimeStartDVBT2 = 0;
        MAPI_U32 u32NowTime=MsOS_GetSystemTime();

        switch(m_enCurrentDemodulator_Type)
        {
            case E_DEVICE_DEMOD_DVB_T2:
            {
                u32Timeout=8000;

                ReadDspReg(0x00f0, &u8Data);

                if((u8Data&BIT7) != 0x00)
                    bCheckPass=MAPI_TRUE;
                else
                {
                    u16RegAddress =  0x00f0; //P1 Lock History
                    u8BitMask = BIT5;
                    ReadDspReg(u16RegAddress, &u8Data);
                    if((u8Data&u8BitMask) == 0)
                    {
                        u32Timeout=1500;//2000;
                    }
                }

                //DBG_DOMOD_MSB(printf(">>>MSB123x: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                if (bCheckPass)
                {

                    u32LockTimeStartDVBT2=MsOS_GetSystemTime();

                    FECLock = MAPI_TRUE;
                    if(bDoReset == TRUE)
                    {
                        //printf("[msb123x]++++DVBT2 lock, freq=%ld\n",g_u32Frequency);
                        //DBG_DOMOD_MSB(printf("\t\t\tDTV_DVB_T_GetLockStatus(LOCK/T2) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBT2-u32StartTime, u32LockTimeStartDVBT2, u32StartTime));//to measure time
                    }
                    bDoReset = FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_LOCK;
                }
                else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                    ||(u32NowTime - u32LockTimeStartDVBT2 < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
                }
            }
            break;
            case E_DEVICE_DEMOD_DVB_T:
            {
                    u32Timeout=1500;
                    u16RegAddress=0x11E0;
                    u8LockState=0x0B;
                    ReadReg(u16RegAddress, &u8Data);
                    if(u8Data==u8LockState)
                        bCheckPass=MAPI_TRUE;
                    else if(u8Data == 0xBB)
                    {
                        // dsp_table_crc_error
                        ERR_DOMOD_MSB(printf("@msb123x Dsp table init param crc error !!!\n"));
                        DTV_DVBT_DSPReg_ReadBack();
                    }
                    else
                    {
                        u16RegAddress =  0x0990; //TPS his Lock,
                        u8BitMask = BIT3;
                        ReadReg(u16RegAddress, &u8Data);
                        if((u8Data&u8BitMask) > 0)
                           u32Timeout=6000;
                    }
    /*
                if(FECLock) //check fec
                {
                    u32Timeout=6000;
                    u16RegAddress=0x11E0;
                    u8LockState=0x0B;
                    ReadReg(u16RegAddress, &u8Data);
                    if(u8Data==u8LockState)
                        bCheckPass=MAPI_TRUE;
                }
               else
                {
                    u32Timeout=2000;
                    //u16RegAddress =  0x0f22; //TPS Lock,
                    //u8BitMask = BIT1;
                    u16RegAddress =  0x0990; //TPS his Lock,
                    u8BitMask = BIT3;
                    ReadReg(u16RegAddress, &u8Data);
                    if((u8Data&u8BitMask) > 0)
                        bCheckPass=MAPI_TRUE;
                }
    */
                //DBG_DOMOD_MSB(printf(">>>MSB123x: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                if (bCheckPass)
                {
                    u32LockTimeStartDVBT=MsOS_GetSystemTime();
                    FECLock = MAPI_TRUE;
                    if(bDoReset==TRUE)
                    {
                        //printf("[msb123x]++++DVBT lock, freq=%ld\n",g_u32Frequency);
                        //DBG_DOMOD_MSB(printf("\t\t\tDTV_DVB_T_GetLockStatus(LOCK/T) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBT-u32StartTime, u32LockTimeStartDVBT, u32StartTime));//to measure time
                    }
                    bDoReset = FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_LOCK;
                }
                else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                ||(u32NowTime - u32LockTimeStartDVBT < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
                }
            }
            break;
            case E_DEVICE_DEMOD_DVB_C://mick
            {
                    u32Timeout=1500;
                    u16RegAddress=0x11E0;
                    u8LockState=0x0C;
                    ReadReg(u16RegAddress, &u8Data);
                    //printf("[msb123x]+++++++++DVBC State---->%d\n",u8Data);//mick
                    if(u8Data==u8LockState)
                        bCheckPass=MAPI_TRUE;
                    else
                    {
                        u16RegAddress =  0x0990; //TPS his Lock,
                        u8BitMask = BIT3;
                        ReadReg(u16RegAddress, &u8Data);
                        if((u8Data&u8BitMask) > 0)
                           u32Timeout=6000;
                    }
                //DBG_DOMOD_MSB(printf(">>>MSB123x: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                if (bCheckPass)
                {
                    u32LockTimeStartDVBC=MsOS_GetSystemTime();
                    FECLock = MAPI_TRUE;
                    if(bDoReset==TRUE)
                    {
                        //printf("[msb123x]++++DVBC lock, freq=%ld\n",g_u32Frequency);
                        //DBG_DOMOD_MSB(printf("\t\t\tDTV_DVB_C_GetLockStatus(LOCK/C) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBC-u32StartTime, u32LockTimeStartDVBC, u32StartTime));//to measure time
                    }
                    bDoReset = FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_LOCK;
                }
                else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                ||(u32NowTime - u32LockTimeStartDVBC < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
                }
            }
            break;
            default:
                *((EN_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
        }
    }
    return MAPI_TRUE;
}
#endif

//##########################################################################################################
//##########################################################################################################
//########################################  Public:DTV Implementation ##################################
//##########################################################################################################
//##########################################################################################################
// DVBT2 95~101ms, DVBT 38~39ms
MAPI_BOOL DTV_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    //MAPI_BOOL b_pal_bg;
    //MAPI_BOOL bStatus = MAPI_FALSE;
    DBG_DOMOD_MSB(printf("DTV_SetFrequency %d ,%d \n", (int)u32Frequency, (int)eBandWidth));
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);
    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

    if(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T2)
    {
        MAPI_U8 bw = E_DEMOD_BW_8M;
        switch (eBandWidth)
        {
            case E_RF_CH_BAND_6MHz:
                bw = E_DEMOD_BW_6M;
                break;
            case E_RF_CH_BAND_7MHz:
                bw = E_DEMOD_BW_7M;
                break;
            case E_RF_CH_BAND_8MHz:
                bw = E_DEMOD_BW_8M;
                break;
            default:
                bw = E_DEMOD_BW_8M;
                break;
        }
        Reset();
        usleep(500);
        WriteDspReg((MAPI_U8)T2_BW, bw);      // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
        DTV_SetPlpGroupID(0,0);
        WriteReg(0x0C00+(0x0E)*2, 0x0001);  // FSM_EN
    }
    else if (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
    {
        Reset();
        usleep(500);

        WriteDspReg((MAPI_U8)T_CONFIG_BW, eBandWidth);      // BW: 1->6M, 2->7M, 3->8M

        MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_CONFIG_BW-(MAPI_U8)T_OPMODE_RFAGC_EN] = (MAPI_U8)eBandWidth;
        MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_PARAM_CHECK_SUM-(MAPI_U8)T_OPMODE_RFAGC_EN] = DTV_DVBT_DSPReg_CRC();

        WriteDspReg((MAPI_U8)T_PARAM_CHECK_SUM, MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_PARAM_CHECK_SUM-(MAPI_U8)T_OPMODE_RFAGC_EN]);      // BW: 1->6M, 2->7M, 3->8M

        Active(1);
    }

    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return MAPI_TRUE;
}

EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    return E_FE_SIGNAL_NO;
}

U16 DTV_GetSignalQuality(void)
{
    if(FECLock==FALSE)
    {
        return 0;
    }
    //FRA_T2_BRINGUP
    return 80;

#if 0
    MAPI_U8     status = true;
    MAPI_U8     reg= 0, reg_frz = 0;
    MAPI_U16    BitErrPeriod = 0;
    MAPI_U32    BitErr = 0;
    MAPI_U16    PktErr = 0;
    MAPI_U8     u8Data = 0;
    float       fber = 0;
    float       log_ber = 0;
    //For DVBC
/*
    float           ber_sqi;
    float           cn_rec = 0;
    float           cn_nordig_p1 = 0;
    float           cn_rel = 0;
    MAPI_U8         tps_cnstl = 0, tps_cr = 0, i = 0;
    MAPI_U16        signal_strength = 0;
*/
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);
    switch(device_demodulator::m_enCurrentDemodulator_Type)
    {
        case mapi_demodulator::E_DEVICE_DEMOD_DVB_T2:
        {
            /////////// Check lock status /////////////
            ReadDspReg(0x00f0, &reg);
            if ((reg&BIT7) == 0x00)
            {
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return 0;
            }

            /////////// Data BER /////////////
            // bank 38 0x02 [0] freeze
            // status &= WriteReg(0x2604, 0x01);    // avoid confliction

            // bank 38 0x12 Data BER Window[15:0]
            status &= ReadReg(0x2625, &reg);
            BitErrPeriod = reg;
            status &= ReadReg(0x2624, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;

            // bank 38 0x32 Data BER count[15:0]
            // bank 38 0x33 Data BER count[31:16]
            status &= ReadReg(0x2667, &reg);
            BitErr = reg;
            status &= ReadReg(0x2666, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= ReadReg(0x2665, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= ReadReg(0x2664, &reg);
            BitErr = (BitErr << 8) | reg;

            // bank 38 0x02 [0] freeze
            // status &= WriteReg(0x2604, 0x00);     // avoid confliction

            if (BitErrPeriod == 0)
            //protect 0
                BitErrPeriod = 1;

            status &= ReadReg(0x268e, &reg);    //FEC Type[8:7]

            if (reg&0x0180)
                fber = (float)BitErr/(BitErrPeriod*64800);
            else
                fber = (float)BitErr/(BitErrPeriod*16200);

            DBG_DOMOD_MSB(printf("MSB123x Data BER = %8.3e \n ", fber));

            if (status == FALSE)
            {
                DBG_DOMOD_MSB(printf("DTV_GetSignalQuality_DVBT2_GetPostViterbiBer Fail!\n"));
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return 0;
            }

            log_ber = ( - 1) *Log10Approx(1 / fber); // Log10Approx() provide 1~2^32 input range only
            //DBG_GET_SIGNAL(printf("Log(BER) = %f\n",log_ber));
            if (log_ber <= ( - 7.0))
            // PostVit BER < 1e-7
            {
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return 100;
            }
            else if (log_ber < ( - 3.7))
            // PostVit BER < 2e-4
            {
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return (80+((( - 3.7) - log_ber) / (( - 3.7) - ( - 7.0))*(100-80)));
            }
            else if (log_ber < ( - 1.7))
            // PostVit BER < 2e-2
            {
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return (40+((( - 1.7) - log_ber) / (( - 1.7) - ( - 3.7))*(80-40)));
            }
            else if (log_ber < ( - 0.7))
            // PostVit BER < 2e-1
            {
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return (10+((( - 0.7) - log_ber) / (( - 0.7) - ( - 1.7))*(40-10)));
            }
            else
            {
                //*quality = 5;
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return 5;
            }
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return 0;

            break;
        }

        case mapi_demodulator::E_DEVICE_DEMOD_DVB_T:
        case mapi_demodulator::E_DEVICE_DEMOD_DVB_C:
        default:
        {
            if (ReadReg(0x112C, &u8Data) == FALSE)
            {
                DBG_DOMOD_MSB(printf("DTV_DVBT_GetSignalQuality ReadReg fail!!! \n"));
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return 0;
            }
            if (u8Data &0x02 /*BIT1*/)
            {
                /////////// Post-Viterbi BER /////////////
                // bank 7 0x32 [7] reg_bit_err_num_freeze
                status &= ReadReg(0x1132, &reg_frz);
                status &= WriteReg(0x1132, reg_frz | 0x80);
                // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
                //             [15:8] reg_bit_err_sblprd_15_8
                status &= ReadReg(0x1131, &reg);
                BitErrPeriod = reg;
                status &= ReadReg(0x1130, &reg);
                BitErrPeriod = (BitErrPeriod << 8) | reg;
                // bank 7 0x3a [7:0] reg_bit_err_num_7_0
                //             [15:8] reg_bit_err_num_15_8
                // bank 7 0x3c [7:0] reg_bit_err_num_23_16
                //             [15:8] reg_bit_err_num_31_24
                status &= ReadReg(0x113D, &reg);
                BitErr = reg;
                status &= ReadReg(0x113C, &reg);
                BitErr = (BitErr << 8) | reg;
                status &= ReadReg(0x113B, &reg);
                BitErr = (BitErr << 8) | reg;
                status &= ReadReg(0x113A, &reg);
                BitErr = (BitErr << 8) | reg;
                // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
                //             [15:8] reg_uncrt_pkt_num_15_8
                status &= ReadReg(0x113F, &reg);
                PktErr = reg;
                status &= ReadReg(0x113E, &reg);
                PktErr = (PktErr << 8) | reg;
                // bank 7 0x32 [7] reg_bit_err_num_freeze
                status &= WriteReg(0x1132, reg_frz);
                if (BitErrPeriod == 0)
                //protect 0
                    BitErrPeriod = 1;
                if (BitErr <= 0)
                    fber = 0.5 / ((float)BitErrPeriod *128 * 188 * 8);
                else
                    fber = (float)BitErr / ((float)BitErrPeriod *128 * 188 * 8);
                DBG_DOMOD_MSB(printf("MSB123x PostVitBER = %8.3e \n ", fber));
                DBG_DOMOD_MSB(printf("MSB123x PktErr = %d \n ", (int)PktErr));

                if (status == FALSE)
                {
                    DBG_DOMOD_MSB(printf("DTV_GetSignalQuality GetPostViterbiBer Fail!\n"));
                    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                    return 0;
                }

                log_ber = ( - 1) *Log10Approx(1 / fber); // Log10Approx() provide 1~2^32 input range only
                //DBG_GET_SIGNAL(printf("Log(BER) = %f\n",log_ber));
                if (log_ber <= ( - 7.0))
                // PostVit BER < 1e-7
                {
                    //*quality = 100;
                    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                    return 100;
                }
                else if (log_ber < ( - 3.7))
                // PostVit BER < 2e-4
                {
                    //*quality = 60 + (((-3.7) - log_ber) / ((-3.7)-(-7.0)) * (100-60));
                    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                    return (60+((( - 3.7) - log_ber) / (( - 3.7) - ( - 7.0))*(100-60)));
                }
                else if (log_ber < ( - 2.7))
                // PostVit BER < 2e-3
                {
                    //*quality = 10 + (((-2.7) - log_ber) / ((-2.7)-(-3.7)) * (60-10));
                    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                    return (10+((( - 2.7) - log_ber) / (( - 2.7) - ( - 3.7))*(60-10)));
                }
                else
                {
                    //*quality = 10;
                    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                    return 10;
                }
            }
            else
            {
                //*quality = 0;
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return 0;
            }
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return 0;

            break;
        }
    }  // end of switch
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return 0;
#endif
}

MAPI_U16 DTV_GetSignalStrength(void)
{
    if(FECLock==FALSE)
    {
        return 0;
    }

    return 80;

#if 0
    MAPI_U8    status = true;
    MAPI_U8    reg_tmp = 0;
    MAPI_U8    rf_agc_val = 0;
    MAPI_U8    if_agc_val = 0;
//    MAPI_U8    if_agc_err = 0;
    MAPI_U8    i = 0;
    MAPI_U8    ssi_tbl_len = 0;
//    MAPI_U8    err_tbl_len = 0;
    MAPI_U8    tps_cnstl = 0;
    MAPI_U8    tps_cr = 0;
    MAPI_U8    ssi = 0;
    float    ch_power_db = 0;
    float    ch_power_rf = 0;
    float    ch_power_if = 0;
    float    ch_power_ref = 0;
    float    ch_power_rel = 0;

    mapi_demodulator::EN_LOCK_STATUS eLockStatus = mapi_demodulator::E_DEMOD_CHECKING;
    S_IFAGC_SSI     *ifagc_ssi;
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);
    switch(device_demodulator::m_enCurrentDemodulator_Type)
    {
        case mapi_demodulator::E_DEVICE_DEMOD_DVB_T2:
        {
            // debug select
            WriteReg(0x3e00+0x13*2, 0x03);
            WriteReg(0x3e00+0x02*2, 0x00);   //set freeze & dump [Write]
            WriteReg(0x3e00+0x02*2+1, 0x80);

            // agc gain2
            ReadReg(0x3e00+0x14*2+1, &reg_tmp);

            DBG_GET_SIGNAL(printf(">>> reg_tmp = %d <<<\n", (int)reg_tmp));
            if_agc_val = reg_tmp;
            DBG_GET_SIGNAL(printf(">>> if_agc_val = %d <<<\n", (int)if_agc_val));

            //if ( if_agc_val < 0xB4 )  // 0dbm ~ 59dbm - 100
            if ( if_agc_val < 0x2D )  // 0dbm ~ 59dbm - 100
            {
                ssi = 100;
            }
            //else if ( if_agc_val < 0xC1 )  // -60dbm~ -69dbm  90 ~ 99
            else if ( if_agc_val < 0x31 )  // -60dbm~ -69dbm  90 ~ 99
            {
                //ssi = 99 - ( ( if_agc_val - 0x50 ) / ((0x58-0x50)/10) );
                ssi = 99 - ( ( if_agc_val - 0x2D ) * 10  / (0x31-0x2D) );
            }
            //else if ( if_agc_val < 0xD2 )  // -70dbm~ -79dbm  60 ~ 89
            else if ( if_agc_val < 0x50 )  // -70dbm~ -79dbm  60 ~ 89
            {
                //ssi =  ( ( if_agc_val - 0xC1 ) / ((0xD2-0xC1)/30) );
                //ssi = 89 - ( ( if_agc_val - 0xC1 ) * 30 / (0xD2-0xC1) );
                ssi = 89 - ( ( if_agc_val - 0x31 ) * 30 / (0x50 -0x31) );
            }
            //else if ( if_agc_val < 0xD8 )  // -80dbm ~ 10 ~ 59
            else if ( if_agc_val < 0x72 )  // -80dbm ~ 10 ~ 59
            {
                //ssi = 59 - ( ( if_agc_val - 0xD2 ) / ((0xD8-0xD2)/50) );
                //ssi = 59 - ( ( if_agc_val - 0xD2 ) * 50  / (0xD8-0xD2) );
                ssi = 59 - ( ( if_agc_val - 0x50 ) * 50  / (0x72-0x50) );
            }
            else
            {
                ssi = 10;
            }

            DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)ssi));
        }
        break;

        case mapi_demodulator::E_DEVICE_DEMOD_DVB_T:
        case mapi_demodulator::E_DEVICE_DEMOD_DVB_C:
        {
            ///////// RF/IF-AGC Gain Out /////////////
            rf_agc_val = 0x3f;

            // ==== IFAGC_GAIN_OUT (GAIN2) ====

            // reg_agc_debug_sel[3:0]
            ReadReg(0x3e26, &reg_tmp);
            reg_tmp = (reg_tmp&0xf0)|0x03;    // select ifagc_gain
            WriteReg(0x3e26, reg_tmp);

            // reg_agc_gain2_out
            // use only high byte value
            ReadReg(0x3e29, &reg_tmp);
            if_agc_val = reg_tmp;

            DBG_GET_SIGNAL(printf("SSI_RFAGC (SAR) = 0x%x\n", (MAPI_U16)rf_agc_val));
            DBG_GET_SIGNAL(printf("SSI_IFAGC_H = 0x%x\n", (MAPI_U16) if_agc_val));

            for(i = 0; i < sizeof(FT2125_RFAGC_SSI)/sizeof(S_RFAGC_SSI); i++)
            {
                if (rf_agc_val <= FT2125_RFAGC_SSI[i].sar3_val)
                {
                    ch_power_rf = FT2125_RFAGC_SSI[i].power_db;
                    break;
                }
            }

            ifagc_ssi = FT2125_IFAGC_SSI;
            ssi_tbl_len = sizeof(FT2125_IFAGC_SSI)/sizeof(S_IFAGC_SSI);

            for(i = 0; i < ssi_tbl_len; i++)
            {
                if (if_agc_val <= FT2125_IFAGC_SSI[i].agc_val)
                {
                    ch_power_if = FT2125_IFAGC_SSI[i].power_db;
                    break;
                }
            }

            DBG_GET_SIGNAL(printf("ch_power_rf = %f\n", ch_power_rf));
            DBG_GET_SIGNAL(printf("ch_power_if = %f\n", ch_power_if));

            ch_power_db = (ch_power_rf > ch_power_if)? ch_power_rf : ch_power_if;

            ExtendCmd(0xFF, 0, 0, (void *)&eLockStatus);

           if( mapi_demodulator::E_DEMOD_LOCK == eLockStatus )
           {
            ///////// Get Constellation and Code Rate to determine Ref. Power //////////
            ///////// (refer to Teracom min. spec 2.0 4.1.1.6) /////

                status &= ReadReg(0x0f24, &reg_tmp);
                tps_cnstl = reg_tmp & 0x03;

                status &= ReadReg(0x0f24+1, &reg_tmp);
                tps_cr = (reg_tmp & 0x70) >> 4;

                for(i = 0; i < sizeof(SsiPref)/sizeof(S_SSI_PREF); i++)
                {
                    if ( (tps_cnstl == SsiPref[i].constel)
                        && (tps_cr == SsiPref[i].code_rate) )
                    {
                    ch_power_ref = SsiPref[i].p_ref;
                    break;
                    }
                }
            }
            else
            {
                ch_power_ref = SsiPref[8].p_ref;
            }
                 //printf("tps_cnstl=%d, tps_cr = %d\n", tps_cnstl, tps_cr);

            ch_power_rel = ch_power_db - ch_power_ref;

                //printf("ch_power_db = %f, ch_power_ref=%f, ch_power_rel=%f\n", ch_power_db, ch_power_ref, ch_power_rel);

            if (ch_power_rel < -15.0)
                ssi = 0.0;
            else if (ch_power_rel < 0.0)
                ssi = (ch_power_rel + 15.0)*(10.0/15.0);
            else if (ch_power_rel < 20.0)
                ssi = ch_power_rel*4.0 + 10.0;
            else if (ch_power_rel < 35.0)
                ssi = (ch_power_rel - 20.0)*(10.0/15.0) + 90.0;
            else
                ssi = 100.0;

            DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)ssi));

        }
        break;

        default:
            ssi = 0;
            DBG_GET_SIGNAL(printf("Undefined!!!\n"));
        break;
    }
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return ssi;
#endif
}

MAPI_BOOL DTV_Serial_Control(MAPI_BOOL bEnable)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);
    if(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T2)
    {
    //FRA_T2_BRINGUP
    }
    else if ((m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
        || (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C))
    {
        // set serial/parallel mode
        if( WriteDspReg((MAPI_U8)T_CONFIG_TS_SERIAL, (MAPI_U8)bEnable)!= TRUE)//Driver update 2009/11/20
        {
            printf(" @MSB1231_Serial_Control seting NG\n");
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return MAPI_FALSE;
        }
        MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_CONFIG_TS_SERIAL-(MAPI_U8)T_OPMODE_RFAGC_EN] = (MAPI_U8)bEnable;
        // set clok inverse
        if( WriteDspReg((MAPI_U8)T_CONFIG_TS_OUT_INV, (MAPI_U8)bEnable)!= TRUE)//Driver update 2009/11/20
        {
            printf(" @MSB1231_Serial_Control seting NG\n");
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return MAPI_FALSE;
        }
        MSB1231_DVBT_DSPREG_TABLE[(MAPI_U8)T_CONFIG_TS_OUT_INV-(MAPI_U8)T_OPMODE_RFAGC_EN] = (MAPI_U8)bEnable;
    }
    Driving_Control(1);
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return MAPI_TRUE;
}

//##########################################################################################################
//##########################################################################################################
//########################################  Public:DTV-DVB-T Implementation ################################
//##########################################################################################################
//##########################################################################################################
BOOLEAN DTV_DVB_T_GetLockStatus(void)
{
    U32 u32Timeout;
    U32 u32LockTimeout=1000;
    U8 u8Data;
    U16 u16RegAddress;
    U8 u8LockState;
    U8 u8BitMask;
    BOOLEAN bCheckPass=FALSE;
    static U32 u32LockTimeStartDVBT = 0;
    static U32 u32LockTimeStartDVBT2 = 0;
    U32 u32NowTime=MsOS_GetSystemTime();;

    //static MAPI_U32 u32FecLockTime;
    //static MAPI_U8 m_u8Data;
    //printf("sttest get lock state \n");
    switch(m_enCurrentDemodulator_Type)
    {
         case E_DEVICE_DEMOD_DVB_T2:
            u32Timeout=4000;
            u16RegAddress=0x0900+(0x48)*2;
            u8LockState=0x09;
            ReadReg(u16RegAddress, &u8Data);
            DBG_DOMOD_MSB(printf(">>>MSB123x: [%s][%d] Lock Status = %d\n", __FUNCTION__, __LINE__, u8Data));
            if(u8Data == u8LockState)
            {
                bCheckPass=TRUE;
            }
            else
            {
                u16RegAddress =  0x00f0; //P1 Lock History
                u8BitMask = BIT5;
                ReadDspReg(u16RegAddress, &u8Data);
                if((u8Data&u8BitMask) == 0)
                {
                    u32Timeout=2000;
                }
            }

            DBG_DOMOD_MSB(printf(">>>MSB123x: [%s] Reg Status = %d\n", __FUNCTION__, u8Data));
            if (bCheckPass)
            {
                u32LockTimeStartDVBT2=MsOS_GetSystemTime();

                FECLock = TRUE;
                return TRUE;
            }
            else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                ||(u32NowTime - u32LockTimeStartDVBT2 < u32LockTimeout))
            {
                FECLock = FALSE;
                return FALSE;
            }
            else
            {
                FECLock = FALSE;
                return FALSE;
            }
            break;
         case E_DEVICE_DEMOD_DVB_T:
            //u16RegAddress=0x11E0;
            //u8LockState=0x0B;
            u32Timeout=2000;
            u16RegAddress=0x11E0;
            u8LockState=0x0B;
            ReadReg(u16RegAddress, &u8Data);
            if(u8Data==u8LockState)
            {
                bCheckPass=TRUE;
            }
            else
            {
                u16RegAddress =  0x0990; //TPS his Lock,
                u8BitMask = BIT3;
                ReadReg(u16RegAddress, &u8Data);
                if((u8Data&u8BitMask) > 0)
                    u32Timeout=6000;
            }

            #if 0
            if(FECLock) //check fec
            {
                u32Timeout=6000;
                u16RegAddress=0x11E0;
                u8LockState=0x0B;
                ReadReg(u16RegAddress, &u8Data);
                if(u8Data==u8LockState)
                    bCheckPass=TRUE;
            }
           else
            {
                u32Timeout=2000;
                //u16RegAddress =  0x0f22; //TPS Lock,
                //u8BitMask = BIT1;
                u16RegAddress =  0x0990; //TPS his Lock,
                u8BitMask = BIT3;
                ReadReg(u16RegAddress, &u8Data);
                if((u8Data&u8BitMask) > 0)
                    bCheckPass=TRUE;
            }
            #endif
            DBG_DOMOD_MSB(printf(">>>MSB123x: [%s][%d] Lock Status = %d\n", __FUNCTION__, __LINE__, u8Data));
            if (bCheckPass)
            {
                u32LockTimeStartDVBT=MsOS_GetSystemTime();
                FECLock = TRUE;
                return TRUE;
            }
            else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
            ||(u32NowTime - u32LockTimeStartDVBT < u32LockTimeout))
            {
                FECLock = FALSE;
                return FALSE;
            }
            else
            {

                FECLock = FALSE;
                return FALSE;
            }
            break;
         default:
            return FALSE;
    }

}

//##########################################################################################################
//##########################################################################################################
//########################################  Private Function Implementation ################################
//##########################################################################################################
//##########################################################################################################

MAPI_BOOL I2C_CH_Reset(MAPI_U8 ch_num)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    //MAPI_U8         addr[4] = {0x00, 0x00, 0x00, 0x00};
    MAPI_U8         data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]I2C_CH_Reset, CH=0x%x\n",ch_num));
    MsOS_ObtainMutex(_s32_Demod_DVBT2_RW_Mutex, MSOS_WAIT_FOREVER);
    //mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_1);

    // 8'hb2(SRID)->8,h53(PWD1)->8,h45(PWD2)->8,h52(PWD3)->8,h44(PWD4)->8,h42(PWD5)
    data[0] = 0x53;
    //iptr->WriteBytes(0, NULL, 5, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 5, data);

    // 8'hb2(SRID)->8,h71(CMD)	//TV.n_iic_
    data[0] = 0x71;
    //iptr->WriteBytes(0, NULL, 1, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, data);

    // 8'hb2(SRID)->8,h81(CMD)	//TV.n_iic_sel_b0
    data[0] = ((ch_num & 0x01) != 0)? 0x81 : 0x80;
    //iptr->WriteBytes(0, NULL, 1, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, data);

    // 8'hb2(SRID)->8,h83(CMD)	//TV.n_iic_sel_b1
    data[0] = ((ch_num & 0x02) != 0)? 0x83 : 0x82;
    //iptr->WriteBytes(0, NULL, 1, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, data);

    // 8'hb2(SRID)->8,h84(CMD)	//TV.n_iic_sel_b2
    data[0] = ((ch_num & 0x04) != 0)? 0x85 : 0x84;
    //iptr->WriteBytes(0, NULL, 1, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, data);

    // 8'hb2(SRID)->8,h53(CMD)	//TV.n_iic_ad_byte_en2, 32bit read/write
    data[0] = 0x53;
    //iptr->WriteBytes(0, NULL, 1, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, data);

    // 8'hb2(SRID)->8,h7f(CMD)	//TV.n_iic_sel_use_cfg
    data[0] = 0x7f;
    //iptr->WriteBytes(0, NULL, 1, data);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, data);

/*
    // 8'hb2(SRID)->8,h35(CMD)	//TV.n_iic_use
    data[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h71(CMD)	//TV.n_iic_Re-shape
    data[0] = 0x71;
    iptr->WriteBytes(0, NULL, 1, data);
*/
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW_Mutex);
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]I2C_CH_Reset, CH=0x%x\n",ch_num));
    return MAPI_TRUE;
}

/*@ <Operation ID=I2b28dd03m121c8cf959bmm6ff4> @*/
MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet;
    MsOS_ObtainMutex(_s32_Demod_DVBT2_RW_Mutex, MSOS_WAIT_FOREVER);
    //hmapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_1);

    //bRet &= iptr->SetSpeed(0);


    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;
    u8MsbData[5] = u8Data;

    u8MsbData[0] = 0x35;
    //iptr->WriteBytes(0, NULL, 1, u8MsbData);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    //iptr->WriteBytes(0, NULL, 6, u8MsbData);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 6, u8MsbData);

    u8MsbData[0] = 0x34;
    //return iptr->WriteBytes(0, NULL, 1, u8MsbData);
    bRet = MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, u8MsbData);
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW_Mutex);
    return bRet;

}

MAPI_BOOL WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U8   u8MsbDataValue[LOAD_CODE_I2C_BLOCK_NUM + 5];
    MAPI_U16   idx = 0;

    //bRet &= MsOS_ObtainMutex(_s32_Demod_DVBT2_RW_Mutex, MSOS_WAIT_FOREVER);
    //mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_1);

    // bRet &= iptr->SetSpeed(0);

    u8MsbDataValue[0] = 0x10;
    u8MsbDataValue[1] = 0x00;
    u8MsbDataValue[2] = 0x00;
    u8MsbDataValue[3] = (u16Addr >> 8) &0xff;
    u8MsbDataValue[4] = u16Addr &0xff;
    // u8MsbDataValue[5] = 0x00;

    for(idx = 0; idx < data_size ; idx++)
    {
        u8MsbDataValue[5+idx] = u8pData[idx];
    }

    u8MsbDataValue[0] = 0x35;
    //bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
    bRet &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, u8MsbDataValue);

    u8MsbDataValue[0] = 0x10;
    //bRet &= iptr->WriteBytes(0, NULL, 5 + data_size, u8MsbData);
    bRet &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 5 + data_size, u8MsbDataValue);

    u8MsbDataValue[0] = 0x34;
    //bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
    bRet &= MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, u8MsbDataValue);

    //bRet &= MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW_Mutex);

    return bRet;
}

MAPI_BOOL WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL ret = true;
    ret &= WriteReg(u16Addr, (MAPI_U8)u16Data&0x00ff);
    ret &= WriteReg(u16Addr + 0x0001, (MAPI_U8)(u16Data>>8)&0x00ff);
    return ret;
}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm6ff4> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6fcf> @*/
MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet;
    MsOS_ObtainMutex(_s32_Demod_DVBT2_RW_Mutex, MSOS_WAIT_FOREVER);
    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    //iptr->WriteBytes(0, NULL, 1, u8MsbData);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    //iptr->WriteBytes(0, NULL, 5, u8MsbData);
    MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 5, u8MsbData);
    //iptr->ReadBytes(0, NULL, 1, pu8Data);
    MApi_SWI2C_ReadBytes(DEMOD_SLAVE_ID, 0, 0, 1, pu8Data);

    u8MsbData[0] = 0x34;
    //return iptr->WriteBytes(0, NULL, 1, u8MsbData);
    bRet = MApi_SWI2C_WriteBytes(DEMOD_SLAVE_ID, 0, 0, 1, u8MsbData);
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW_Mutex);
    return bRet;

}
#define REG_MB_CNTL     0x0C00
#define REG_MB_ADDR_L   0x0C02
#define REG_MB_ADDR_H   0x0C03
#define REG_MB_DATA     0x0C04

MAPI_BOOL WriteDspReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    MsOS_ObtainMutex(_s32_Demod_DVBT2_RW2_Mutex, MSOS_WAIT_FOREVER);
    status &= WriteReg(REG_MB_DATA, u8Data);
    status &= WriteReg(REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= WriteReg(REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= WriteReg(REG_MB_CNTL, 0x04);

    do {
        status &= ReadReg(REG_MB_CNTL, &cntl);
        if (cntr++ > 0x7ff)
        {
            ERR_DOMOD_MSB(printf("MSB123X_MB_WRITE_FAILURE\n"));
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW2_Mutex);
            return false;
        }
    }while (cntl != 0xff);
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW2_Mutex);
    return status;
}

MAPI_BOOL ReadDspReg(MAPI_U16 u16Addr, MAPI_U8* pData)
{
    //DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    MsOS_ObtainMutex(_s32_Demod_DVBT2_RW2_Mutex, MSOS_WAIT_FOREVER);

    status &= WriteReg(REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= WriteReg(REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= WriteReg(REG_MB_CNTL, 0x03);

    do {
        status &= ReadReg(REG_MB_CNTL, &cntl);
        if (cntr++ > 0x7ff)
        {
            ERR_DOMOD_MSB(printf("MSB123X_MB_READ_FAILURE\n"));
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW2_Mutex);
            return false;
        }
    }while (cntl != 0xff);

    status &= ReadReg(REG_MB_DATA, pData);
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_RW2_Mutex);
    return status;
}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm6fcf> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6faa> @*/
MAPI_BOOL MSB123x_Cmd_Packet_Send(S_CMDPKTREG *pCmdPacket, MAPI_U8 param_cnt)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_U8 status = true, indx;
    //MAPI_U8             reg_val, timeout = 0;
    MAPI_U16 timeout = 0;
    MAPI_U8 reg_val = 0;
    // ==== Command Phase ===================
    DBG_DOMOD_MSB(printf(">>>MSB123x: (cmd=0x%x)(0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,) \n", pCmdPacket->cmd_code, pCmdPacket->param[0], pCmdPacket->param[1], pCmdPacket->param[2], pCmdPacket->param[3], pCmdPacket->param[4], pCmdPacket->param[5]));
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);
    // wait _BIT_END clear
    do
    {
        status &= ReadReg(REG_CMD_CTRL, &reg_val);
         if((reg_val & _BIT_END) != _BIT_END)
            break;
        //MDrv_Timer_Delayms(5);
        usleep(5 *1000);
        if (timeout++ > 200)
        {
            DBG_DOMOD_MSB(printf(">>>MSB123x: MSB123x_Cmd_Packet_Send fail on 'wait _BIT_END clear' \n"));
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
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
            DBG_DOMOD_MSB(printf(">>>MSB123x: MSB123x_Cmd_Packet_Send fail on 'wait _BIT_START clear' \n"));
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
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
                DBG_DOMOD_MSB(printf(">>>MSB123x: MSB123x_Cmd_Packet_Send fail on 'wait _BIT_DRQ clear' \n"));
                MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
                return false;
            }
        }while (1);
    }

    // ==== End Phase =======================
    // set _BIT_END to finish command
    status &= ReadReg(REG_CMD_CTRL, &reg_val);
    status &= WriteReg(REG_CMD_CTRL, reg_val | _BIT_END);
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return status;
}


/*@ <Operation ID=I2b28dd03m121c8cf959bmm6f60> @*/
MAPI_BOOL LoadDSPCode(void)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    ////MAPI_U32 u32Now = MsOS_GetSystemTime();
    //printf("\t\t\tLoadDSPCode TIME   %ld (=%ld-%ld)\n", u32Now-u32StartTime, u32Now, u32StartTime);
    ////DBG_DOMOD_MSB(printf("\t\t\tLoadDSPCode TIME   %ld (=%ld-%ld)\n", u32Now-u32StartTime, u32Now, u32StartTime));//to measure time
    //u32StartTime = u32Now;
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCode\n"));
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);

    //MAPI_U32        u32Timeout = 0;
    //MAPI_U8         u8DoneFlag = 0;
    MAPI_U8         u8Data = 0;
    MAPI_BOOL       bRet = true;

    DBG_DOMOD_MSB(printf(">>>MSB123x: Load DSP...\n"));
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            u8Data=1;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            u8Data=2;
            break;
        case E_DEVICE_DEMOD_DVB_C:
            u8Data=3;
            break;
        default:
            u8Data=2;
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return MAPI_FALSE;
    }
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            DTV_DVBT2_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_T:
            DTV_DVBT_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_C://mick
            DTV_DVBC_DSPReg_Init();
            break;
        default:
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return MAPI_FALSE;
    }
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCode\n"));
    return bRet;
}




/************************************************************************************************
Subject:    Set demodulator type
Function:   SetCurrentDemodulatorType
Parmeter:   enDemodType
Return:     BOOLEAN :
 *************************************************************************************************/
MAPI_BOOL SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    DBG_DOMOD_FLOW(printf("%s(),%d, enDemodType=%d\n",__func__,__LINE__, enDemodType));
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    if(enDemodType == m_enCurrentDemodulator_Type)
    {
        return MAPI_TRUE;
    }
#endif
    u32ChkScanTimeStart = MsOS_GetSystemTime();
    switch(enDemodType)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            m_enCurrentDemodulator_Type = enDemodType;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            m_enCurrentDemodulator_Type = enDemodType;
            break;
        default:
            return MAPI_FALSE;
    }
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    if (bPower_init_en != TRUE)
    {
        return MAPI_TRUE;
    }
#endif
    if (LoadDSPCode() == MAPI_FALSE)
    {

        ERR_DOMOD_MSB(printf(">>>>MSB123x:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {
        DBG_DOMOD_MSB(printf(">>>MSB123x:OK\n"));
    }


    return MAPI_TRUE;
}


/************************************************************************************************
Subject:    Get PLP-ID Bit Map
Function:   DTV_GetPlpBitMap
Parmeter:   u32PlpBitMap
Return:     BOOLEAN :
Remark:     32 byte of data to show PLP-ID existense
            |00000000|00000000|...|00000000|00011111|11111111|
             byte31   byte30   ... byte2    byte1    byte0   => 256 bit in total
 *************************************************************************************************/
MAPI_BOOL DTV_GetPlpBitMap(MAPI_U8* u8PlpBitMap)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL   status = MAPI_TRUE;
    MAPI_U8     u8Data = 0;
    MAPI_U8     indx = 0;

    status &= ReadDspReg(0x0120, &u8Data);     // check L1 ready
    if (u8Data != 0x30)
        return MAPI_FALSE;

    while(indx < 32)
    {
        status &= ReadDspReg(0x0100+indx, &u8Data);
        u8PlpBitMap[indx] = u8Data;
        indx++;
    }

    return status;
}

/************************************************************************************************
Subject:    Get GROUP_ID upon PLP_ID for MPLP mode
Function:   DTV_GetPlpGroupID
Parmeter:   u8PlpID, u8GroupID
Return:     BOOLEAN :
Remark:
 *************************************************************************************************/
MAPI_BOOL DTV_GetPlpGroupID(MAPI_U8 u8PlpID, MAPI_U8* u8GroupID)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL   status = MAPI_TRUE;
    MAPI_U8 u8Data = 0;
    status &= ReadDspReg(0x0120, &u8Data);         // check L1 ready
    if (u8Data != 0x30)
    {
    	ERR_DOMOD_MSB(printf("[msb123x]dvbt2 L1 not ready yet\n"));
        return MAPI_FALSE;
    }

    ReadDspReg(0x00f0, &u8Data);

    if ((u8Data&BIT7) == 0x00)
    {
        ERR_DOMOD_MSB(printf("[msb123x]dvbt2 is un-lock\n"));
        return MAPI_FALSE;
    }
    // assign PLP-ID value
    status &= WriteReg(0x2700+(0x78)*2, u8PlpID);
    status &= WriteReg(0x2700+(0x01)*2 + 1, 0x01);  // MEM_EN
    usleep(1000);
    status &= ReadReg(0x2700+(0x79)*2, u8GroupID);
    status &= WriteReg(0x2700+(0x01)*2 + 1, 0x00);  // ~MEM_EN

    return status;
}

/************************************************************************************************
Subject:    Select PLP_ID, GROUP_ID for MPLP mode
Function:   DTV_SetPlpGroupID
Parmeter:   u8PlpID, u8GroupID
Return:     BOOLEAN :
Remark:
 *************************************************************************************************/
MAPI_BOOL DTV_SetPlpGroupID(MAPI_U8 u8PlpID, MAPI_U8 u8GroupID)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL   status = MAPI_TRUE;
    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();


    // assign Group-ID and PLP-ID value (must be written in order)
    status &= WriteDspReg(0x0122, u8GroupID);
    status &= WriteDspReg(0x0121, u8PlpID);

    return status;
}

void Driving_Control(MAPI_BOOL bEnable)
{
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8 u8Temp;
    ReadReg(0x0958, &u8Temp);
    if (bEnable)
    {
        u8Temp = 0xFF;
    }
    else
    {
        u8Temp = 0x00;
    }
    WriteReg(0x0958, u8Temp);

    ReadReg(0x0959, &u8Temp);
    if (bEnable)
    {
        u8Temp = u8Temp | 0x0F;
    }
    else
    {
        u8Temp = u8Temp &(~0x0F);
    }
    WriteReg(0x0959, u8Temp);
}

MAPI_U16 DTV_GetCellID(void)
{
    return 0;
#if 0
    DBG_DOMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8 id=0;
    MAPI_U8 status = MAPI_TRUE;
    MAPI_U16  cell_id  = 0;
    MsOS_ObtainMutex(_s32_Demod_DVBT2_Mutex, MSOS_WAIT_FOREVER);
    if (device_demodulator::m_enCurrentDemodulator_Type == mapi_demodulator::E_DEVICE_DEMOD_DVB_T2)
    {
        MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
        return 0;
    }
    else if ((device_demodulator::m_enCurrentDemodulator_Type == mapi_demodulator::E_DEVICE_DEMOD_DVB_T)
            || (device_demodulator::m_enCurrentDemodulator_Type == mapi_demodulator::E_DEVICE_DEMOD_DVB_C))
    {
        status &= WriteReg(0x0ffe, 0x01);

        status &= ReadReg(0x0f2b, &id);
        cell_id = (MAPI_U16)id;

        status &= ReadReg(0x0f2a, &id);
        cell_id |= (MAPI_U16)id << 8;

        status &= WriteReg(0x0ffe, 0x00);

        if(status)
        {
            printf(" @MSB1231_GetCellId OK\n");
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return  MAPI_TRUE;
        }
        else
        {
            printf(" @MSB1231_GetCellId NG\n");
            MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
            return MAPI_FALSE;
        }
    }
    MsOS_ReleaseMutex(_s32_Demod_DVBT2_Mutex);
    return cell_id;
#endif
}

#endif  //#ifndef  _MSB123x_C_