/**
 * Copyright (C) 2009 NXP N.V., All Rights Reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of NXP N.V. and is confidential in nature. Under no circumstances
 * is this software to be  exposed to or placed under an Open Source License of
 * any type without the expressed written permission of NXP N.V.
 *
 * \file          tmbslTDA9989_HDCP.c
 *
 * \version       $Revision: 2 $
 *
 * \date          $Date: 05-Jun-2009 $
 *
 * \brief         TDA9989x low level software driver
 *
*/

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

#include "hdmitx/sde2/comps/tmbslhdmitx/inc/tmbslHdmiTx_types.h"
#include "hdmitx/sde2/comps/tmbsltda9989/inc/tmbslTDA9989_Functions.h"
#include "tmbslTDA9989_local.h"
#include "tmbslTDA9989_State_l.h"
#include "tmbslTDA9989_InOut_l.h"

/*============================================================================*/
/*                     TYPES DECLARATIONS                                     */
/*============================================================================*/

/*============================================================================*/
/*                       CONSTANTS DECLARATIONS EXPORTED                      */
/*============================================================================*/

#define TDA19989_TIMER_H_DEFAULT 0x41
#define TDA19989_TIMER_M_DEFAULT 0xC2
#define TDA19989_TIMER_L_DEFAULT 0x40


/**
 * Table of registers to switch HDMI HDCP mode off for DVI
 */

RAM_DAT tmHdmiTxRegMaskVal_t kVoutHdcpOff[] =
{
    {E_REG_P00_TBG_CNTRL_1_W,   E_MASKREG_P00_TBG_CNTRL_1_dwin_dis, 1},
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_hdmi,       0},
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_eess,       0},
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_ctl_sel,    0},
    {0,0,0}
};

/**
 * Table of registers to switch HDMI HDCP mode on for HDMI
 */
RAM_DAT tmHdmiTxRegMaskVal_t kVoutHdcpOn[] =
{
    {E_REG_P00_TBG_CNTRL_1_W,   E_MASKREG_P00_TBG_CNTRL_1_dwin_dis, 0},
    {E_REG_P11_ENC_CNTRL_RW,    E_MASKREG_P11_ENC_CNTRL_ctl_code,   1},
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_hdmi,       1},
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_eess,       1},
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_ctl_sel,    1},
    {0,0,0}
};

/*============================================================================*/
/*                       CONSTANTS DECLARATIONS                               */
/*============================================================================*/

#ifdef TMFL_HDCP_SUPPORT

/**
 * Table of registers to declare that BKSV is secure
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kBksvSecure[] =
{
    /* BKSV is secure */
    {E_REG_P12_CTRL_W,     E_MASKREG_P12_CTRL_hdcp_ena,   1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_nok,    0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_ok,     1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_ok,     0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_nok,    0},

    /* Commented for HDCP-ATC B-1_03 WA:TDA19989 */
    /* Disable BCAPS interrupt: must not handle it while awaiting BSTATUS */
    {E_REG_P00_INT_FLAGS_0_RW,  E_MASKREG_P00_INT_FLAGS_0_bcaps,    0},

    {0,0,0}
};

/**
 * Table of registers to declare that BKSV is not secure
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kBksvNotSecure[] =
{
    /* BKSV is not secure */
    {E_REG_P12_CTRL_W,     E_MASKREG_P12_CTRL_hdcp_ena,   1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_ok,     0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_nok,    1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_ok,     0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_nok,    0},
    /* Re-enable BCAPS interrupt */
    {E_REG_P00_INT_FLAGS_0_RW,  E_MASKREG_P00_INT_FLAGS_0_bcaps,    1},
    {0,0,0}
};

/**
 * Table of registers to declare that KSV list is secure
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kKsvLSecure[] =
{
    /* KSV list is secure */
    {E_REG_P12_CTRL_W,     E_MASKREG_P12_CTRL_hdcp_ena,   1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_nok,    0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_ok,     0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_ok,     1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_nok,    0},
    {0,0,0}
};

/**
 * Table of registers to declare that BKSV is not secure
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kKsvLNotSecure[] =
{
    /* BKSV is not secure */
    {E_REG_P12_CTRL_W,     E_MASKREG_P12_CTRL_hdcp_ena,   1},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_ok,     0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_bksv_nok,    0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_ok,     0},
    {E_REG_P12_TX1_RW,     E_MASKREG_P12_TX1_ksvl_nok,    1},
    {0,0,0}
};


/**
 * Table of registers to recover from HDCP T0 interrupt
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kT0Recovery[] =
{
    /* Stop HDCP */
    {E_REG_P12_TX0_RW,     E_MASKREG_P12_TX0_sr_hdcp,     1},
    /* TX advance cipher not supported */
    {E_REG_P12_BCAPS_W,    E_MASKREG_P12_BCAPS_1_1,       0},
    /* Init BKSV no specific action */
    {E_REG_P12_TX1_RW,     E_MASKREG_ALL,                      0},
    /* Wait for BCAPS check */
    {E_REG_P12_TX0_RW,     E_MASKREG_P12_TX0_ainfo_rdy,   0},
    /* Disable XOR encryption */
    {E_REG_P12_CTRL_W,     E_MASKREG_P12_CTRL_hdcp_ena,   0},
    {0,0,0}
};

/**
 * Table of registers to initialise HDCP (part 1)
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kHdcpInit1[] =
{
    /* Added since GS HDCP 2.0 */
    {E_REG_P12_TX33_RW,    E_MASKREG_P12_TX33_sys_req,    1},
    /* Must be set before HDCP */
    {E_REG_P12_TX0_RW,     E_MASKREG_P12_TX0_sr_hdcp,     1},
    /* Enable DDC master */
    {E_REG_P12_TX0_RW,     E_MASKREG_P12_TX0_mst_en,      1},
    /* stop HDCP state machine automatic restart */
    {E_REG_P12_TX0_RW,     E_MASKREG_P12_TX0_hook_sm,     1},

    {E_REG_P12_BACK_COMP_RW, E_MASKREG_P12_BACK_COMP_RiCheck, 0},
    {E_REG_P12_BACK_COMP_RW, E_MASKREG_P12_BACK_COMP_AnGen,   1},
    {E_REG_P12_BACK_COMP_RW, E_MASKREG_P12_BACK_COMP_Bcaps,   0},
    {E_REG_P12_BACK_COMP_RW, E_MASKREG_P12_BACK_COMP_3rdPhase,0},
    {E_REG_P12_BACK_COMP_RW, E_MASKREG_P12_BACK_COMP_2ndPhase,0},
    {E_REG_P12_BACK_COMP_RW, E_MASKREG_P12_BACK_COMP_1stPhase,1},

    {E_REG_P00_BCAPS_POLL_RW,E_MASKREG_ALL,20}, /* BCAPS polling freq of 100ms */

    {0,0,0}
};

/**
 * Table of registers to initialise HDCP (part 2)
 * (Not N4)
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kHdcpInit2[] =
{
    /* Disable XOR encryption */
    {E_REG_P12_CTRL_W,     E_MASKREG_P12_CTRL_hdcp_ena,   0},
    /* DDC clock = cclk/3 = 10MHz */
    /* {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_im_clksel,    1}, */
    {0,0,0}
};

/**
 * Table of registers to initialise HDCP (part 3)
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kHdcpInit3[] =
{
    /* TX advance cipher not supported */
    {E_REG_P12_BCAPS_W,    E_MASKREG_P12_BCAPS_1_1,       0},
    /* Init BKSV no specific action */
    {E_REG_P12_TX1_RW,     E_MASKREG_ALL,                      0},
    /* Wait for BCAPS check */
    {E_REG_P12_TX0_RW,     E_MASKREG_P12_TX0_ainfo_rdy,   0},
    {0,0,0}
};



/**
 *  Lookup table for each pixel clock frequency index's nearest MHz value
 */
static CONST_DAT UInt8 kPixClkToMHz[E_PIXCLK_NUM] =
{
   25,     /* E_PIXCLK_25175 */
   25,     /* E_PIXCLK_25200 */
   27,     /* E_PIXCLK_27000 */
   27,     /* E_PIXCLK_27027 */
   54,     /* E_PIXCLK_54000 */
   54,     /* E_PIXCLK_54054 */
   59,     /* E_PIXCLK_59400 */
   74,     /* E_PIXCLK_74175 */
   74,     /* E_PIXCLK_74250 */
   148,    /* E_PIXCLK_148350*/
   148     /* E_PIXCLK_148500*/

#ifdef FORMAT_PC
  ,31, /* E_PIXCLK_31500 */
   36, /* E_PIXCLK_36000 */
   40, /* E_PIXCLK_40000 */
   49, /* E_PIXCLK_49500 */
   50, /* E_PIXCLK_50000 */
   56, /* E_PIXCLK_56250 */
   65, /* E_PIXCLK_65000 */
   75, /* E_PIXCLK_75000 */
   79, /* E_PIXCLK_78750 */
   79, /* E_PIXCLK_79500 */
   85, /* E_PIXCLK_85500 */
   108, /* E_PIXCLK_108000 */
   122, /* E_PIXCLK_121750 */
   162  /* E_PIXCLK_162000 */
#endif /* FORMAT_PC */

};


/**
 * Table of registers to set 5s watchdog timer
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kSet5secWatchdog[] =
{
   /* BCAPS timer = TIMER[17..0]/(FreqFRO/32)xTIMER_5SEC[7..0] */
   /* with FreqFRO < 13.35MHz for F(pmos)F(nmos)F(poly) matrix batch */
   /* and BCAPS Timer > 5s */
   /* see P:\partages\BTC_TV_FE\product_Development\project folders\TDA9984 */
   /* \15_Application_(S&A)\15_d_Application Notes\AN10746_1.3.doc */
    {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_wd_clksel,    1},
    {E_REG_P00_TIMER_5SEC_W,    E_MASKREG_ALL,                      0x64},
    {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_tim_h,        0x00},
    {E_REG_P00_TIMER_M_W,       E_MASKREG_ALL,                      0x58},
    {E_REG_P00_TIMER_L_W,       E_MASKREG_ALL,                      0x00},
    {0,0,0}
};

/**
 * Table of registers to set 120ms watchdog timer based on HDMI clock
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kSet120msWatchdog[] =
{
    /* Set HDMI clock as watchdog */
    {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_wd_clksel,    0},
    /* Set 120ms watchdog (registers set to 120,000us) */
    {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_tim_h,        0x01},
    {E_REG_P00_TIMER_M_W,       E_MASKREG_ALL,                      0xD4},
    {E_REG_P00_TIMER_L_W,       E_MASKREG_ALL,                      0xC0},
    {0,0,0}
};

/**
 * Table of registers to set 1s watchdog timer based on HDMI clock use for phase3
 */
static CONST_DAT tmHdmiTxRegMaskVal_t kSetRiWatchdog[] =
{
    {E_REG_P00_TIMER_2SEC_W,    E_MASKREG_ALL,                      0},
    /* PNF57 Set HDMI clock as watchdog */
    {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_wd_clksel,    0},
    /* Set 600ms watchdog for link check */
    {E_REG_P00_TIMER_H_W,       E_MASKREG_P00_TIMER_H_tim_h,        0x01},
    {E_REG_P00_TIMER_M_W,       E_MASKREG_ALL,                      0xD4},
    {E_REG_P00_TIMER_L_W,       E_MASKREG_ALL,                      0xC0},
    {0,0,0}
};

#endif /* TMFL_HDCP_SUPPORT */

/*============================================================================*/
/*                       FUNCTION PROTOTYPES                                  */
/*============================================================================*/

#ifdef TMFL_HDCP_SUPPORT
static tmErrorCode_t    unlockHDCPStateMachine(tmHdmiTxobject_t *pDis);
#endif /* TMFL_HDCP_SUPPORT */
extern UInt8 pix_clk(tmbslHdmiTxVidFmt_t fmt, tmbslHdmiTxVfreq_t freq, UInt8 *pclk);

/*============================================================================*/
/* tmbslTDA9989HdcpCheck                                                      */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpCheck
(
    tmUnitSelect_t          txUnit,
    UInt16                  uTimeSinceLastCallMs,
    tmbslHdmiTxHdcpCheck_t  *pResult
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    UInt8             regVal;   /* Byte value read from register */
    UInt16            regRi;    /* RI value read from registers */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* See if a function has been scheduled */
    if (pDis->HdcpFuncRemainingMs > 0)
    {
        /* Decrement scheduled period by the call interval */
        if (pDis->HdcpFuncRemainingMs > uTimeSinceLastCallMs)
        {
            /* Not yet time to schedule a function */
            pDis->HdcpFuncRemainingMs = pDis->HdcpFuncRemainingMs - uTimeSinceLastCallMs;
        }
        else
        {
            /* Time now to call the scheduled function - reset the
             * timer to ensure only one schedule call */
            pDis->HdcpFuncRemainingMs = 0;
            /* See if a scheduled function is defined */
            if (pDis->HdcpFuncScheduled != (ptmHdmiTxFunc_t)0)
            {
                /* Call the scheduled function */
                err = pDis->HdcpFuncScheduled(txUnit);
                RETIF(err != TM_OK, err)
            }
        }
    }

    /* See if there are HDCP checks to do */
    if (pDis->HdcpCheckNum == 0)
    {
        /* No checks because not started yet, or HDCP was stopped */
        *pResult = HDMITX_HDCP_CHECK_NOT_STARTED;
    }
    /* Decrement check period by the call interval */
    else if (pDis->HdcpCheckRemainingMs > uTimeSinceLastCallMs)
    {
        /* Not yet time to do a check */
        pDis->HdcpCheckRemainingMs = pDis->HdcpCheckRemainingMs - uTimeSinceLastCallMs;
    }
    else
    {
        /* Time to do a check - restart the timer for next check */
        pDis->HdcpCheckRemainingMs = pDis->HdcpCheckIntervalMs;

        /* Increment check number if not yet passed or failed */
        if (pDis->HdcpCheckNum < pDis->HdcpChecksToDo)
        {
            pDis->HdcpCheckNum++;
        }
        /* else no increment to prevent wrap to 0 and disabling the test */

        /* Test driver state at every check */
        if (pDis->state != ST_HDCP_AUTHENTICATED)
        {
            *pResult = HDMITX_HDCP_CHECK_FAIL_DRIVER_STATE;
        }
        /* Test for T0 interrupts at every check */
        else if (pDis->HdcpT0FailState != 0)
        {
            *pResult = HDMITX_HDCP_CHECK_FAIL_DEVICE_T0;
        }
        else
        {
            /* In progress until pass or fail */
            *pResult = HDMITX_HDCP_CHECK_IN_PROGRESS;

            /* Read RI LSB and MSB registers every check interval */
            err = getHwRegister(pDis, E_REG_P12_RI0_R, &regVal);
            RETIF_REG_FAIL(err)
            regRi = regVal;
            err = getHwRegister(pDis, E_REG_P12_RI1_R, &regVal);
            RETIF_REG_FAIL(err)
            regRi |= ((UInt16)regVal << 8);

            /* Read FSM State register every check interval */
            err = getHwRegister(pDis, E_REG_P12_FSM_STATE_R, &regVal);
            RETIF_REG_FAIL(err)

            /* Only do history and completion checks after first time */
            if (pDis->HdcpCheckNum > 1)
            {
                if (regRi == pDis->HdcpRi)
                {
                    *pResult = HDMITX_HDCP_CHECK_FAIL_DEVICE_RI;
                }
                else if ((regVal == 0x10) && (pDis->HdcpFsmState == 0x10))
                {
                    *pResult = HDMITX_HDCP_CHECK_FAIL_DEVICE_FSM;
                }
                else if (pDis->HdcpCheckNum >= pDis->HdcpChecksToDo)
                {
                    *pResult = HDMITX_HDCP_CHECK_PASS;
                }
            }

            /* Save register values for next time */
            pDis->HdcpRi = regRi;
            pDis->HdcpFsmState = regVal;
        }
    }

    return TM_OK;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpConfigure                                                   */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpConfigure
(
    tmUnitSelect_t           txUnit,
    UInt8                    slaveAddress,
    tmbslHdmiTxHdcpTxMode_t  txMode,
    tmbslHdmiTxHdcpOptions_t options,
    UInt16                   uCheckIntervalMs,
    UInt8                    uChecksToDo
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    UInt8             bitVal;   /* Register bit value */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Check other arguments */
    RETIF_BADPARAM(txMode > HDMITX_HDCP_TXMODE_MAX)
    RETIF_BADPARAM((options & HDMITX_HDCP_OPTION_MASK_BAD) > 0)
    if (slaveAddress == HDMITX_HDCP_SLAVE_PRIMARY)
    {
        bitVal = 0;
    }
    else if (slaveAddress == HDMITX_HDCP_SLAVE_SECONDARY)
    {
        bitVal = 1;
    }
    else
    {
       return TMBSL_ERR_HDMI_BAD_PARAMETER;
    }

    /* Set slave address flag */
    err = setHwRegisterField(pDis, E_REG_P12_TX2_RW,
                             E_MASKREG_P12_TX2_slvaddr, bitVal);

    /* Copy aruments to Device Instance Structure */
    pDis->HdcpSlaveAddress = slaveAddress;
    pDis->HdcpTxMode       = txMode;
    pDis->HdcpOptions      = options;
    pDis->HdcpCheckIntervalMs = uCheckIntervalMs;
    pDis->HdcpChecksToDo   = uChecksToDo;

    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpDownloadKeys                                                */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpDownloadKeys
(
    tmUnitSelect_t          txUnit,
    UInt16                  seed,
    tmbslHdmiTxDecrypt_t    keyDecryption
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    UInt8             otp[3];   /* Data read from OTP */
#ifdef TMFL_HDCP_OPTIMIZED_POWER
    UInt8             reg;
#endif

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED);

    /* Note: Supported for N4 or later (N3 needed AKSV download from OTP
     * public space and is not supported)
     */
       
    /* Check other arguments */
    RETIF_BADPARAM(keyDecryption > HDMITX_HDCP_DECRYPT_MAX);
    
#ifdef TMFL_HDCP_OPTIMIZED_POWER
    /* OTP power supply on */
    getCECHwRegister(pDis, E_REG_CEC_FRO_IM_CLK_CTRL_RW, &reg);
    reg |= E_MASKREG_CEC_FRO_IM_CLK_CTRL_ena_otp;
    setCECHwRegister(pDis, E_REG_CEC_FRO_IM_CLK_CTRL_RW, reg);
    setHwRegisterField(pDis, E_REG_FEAT_POWER_DOWN, E_MASKREG_FEAT_POWER_DOWN_otp, 0);

    /* RAM on */
    setHwRegisterField(pDis, E_REG_P12_TX4_RW, E_MASKREG_P12_TX4_pd_ram, 0);
#endif

    /* Must be set before download */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_sr_hdcp, 1);
    RETIF_REG_FAIL(err)

    /* Set key decryption */
    err = setHwRegisterField(pDis, E_REG_P12_CTRL_W,
                             E_MASKREG_P12_CTRL_keyd, 
                             (UInt8)keyDecryption);
    RETIF_REG_FAIL(err)

    /* Set seed value */
    err = setHwRegisterMsbLsb(pDis, E_REG_P12_KDS_HI_W, seed);
    RETIF_REG_FAIL(err)

    /* Reset the key index */
    err = setHwRegister(pDis, E_REG_P12_KIDX_W, 0);
    RETIF_REG_FAIL(err)

    /* Pulse high-low to start download */
    err = setHwRegisterField(pDis, E_REG_P12_OTP_CNTRL_W,
                             E_MASKREG_P12_OTP_CNTRL_start_dl, 1);
    RETIF_REG_FAIL(err)
    err = setHwRegisterField(pDis, E_REG_P12_OTP_CNTRL_W,
                             E_MASKREG_P12_OTP_CNTRL_start_dl, 0);
    RETIF_REG_FAIL(err)

    /* Reset control register */
    err = setHwRegister(pDis, E_REG_P12_CTRL_W, 0);
    RETIF_REG_FAIL(err);

#ifdef TMFL_HDCP_OPTIMIZED_POWER
    /* OTP power supply off */
    setHwRegisterField(pDis, E_REG_FEAT_POWER_DOWN, E_MASKREG_FEAT_POWER_DOWN_otp, 1);
    getCECHwRegister(pDis, E_REG_CEC_FRO_IM_CLK_CTRL_RW, &reg);
    reg &= ~E_MASKREG_CEC_FRO_IM_CLK_CTRL_ena_otp;
    setCECHwRegister(pDis, E_REG_CEC_FRO_IM_CLK_CTRL_RW, reg);
#endif

    /* Read HDCP_AKSV4,HDCP_AKSV3 using API */
    err = tmbslTDA9989HdcpGetOtp(txUnit, 0x7E, otp);
    RETIF(err != TM_OK, err)
    pDis->HdcpAksv[0] = otp[1]; /* OTP_DATA_ISB */
    pDis->HdcpAksv[1] = otp[2]; /* OTP_DATA_LSB */

    /* Read HDCP_AKSV2,HDCP_AKSV1,HDCP_AKSV0 using API */
    err = tmbslTDA9989HdcpGetOtp(txUnit, 0x7F, otp);
    pDis->HdcpAksv[2] = otp[0]; /* OTP_DATA_MSB */
    pDis->HdcpAksv[3] = otp[1]; /* OTP_DATA_ISB */
    pDis->HdcpAksv[4] = otp[2]; /* OTP_DATA_LSB */

    /* EDID workaround (PR778) : save seed */
    pDis->HdcpSeed = seed;

#ifdef TMFL_RGB_DDR_12BITS
    /* RAM off */
    setHwRegisterField(pDis, E_REG_P12_TX4_RW, E_MASKREG_P12_TX4_pd_ram, 1);
#endif

    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpEncryptionOn                                                */
/*============================================================================*/

tmErrorCode_t
tmbslTDA9989HdcpEncryptionOn
(
    tmUnitSelect_t  txUnit,
    Bool            bOn
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Check other arguments */
    RETIF_BADPARAM(bOn > 1)

    err = setHwRegisterField(pDis, E_REG_P12_TX33_RW,
                             E_MASKREG_P12_TX33_ac_not, (UInt8)bOn);

    err = setHwRegisterField(pDis, E_REG_P12_TX33_RW,
	                         E_MASKREG_P12_TX33_avmute, (UInt8)bOn);

    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}


/*============================================================================*/
/* tmbslTDA9989HdcpGetOtp                                                      */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpGetOtp
(
    tmUnitSelect_t          txUnit,
    UInt8                   otpAddress,
    UInt8                   *pOtpData
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Check other arguments */
    RETIF_BADPARAM(!pOtpData)

    /* Set OTP address */
    err = setHwRegister(pDis, E_REG_P12_OTP_ADDRESS_W, otpAddress);
    RETIF_REG_FAIL(err)

    /* Pulse high-low to start read */
    err = setHwRegisterField(pDis, E_REG_P12_OTP_CNTRL_W,
                             E_MASKREG_P12_OTP_CNTRL_start_rd, 1);
    RETIF_REG_FAIL(err)
    err = setHwRegisterField(pDis, E_REG_P12_OTP_CNTRL_W,
                             E_MASKREG_P12_OTP_CNTRL_start_rd, 0);
    RETIF_REG_FAIL(err)

    /* Read OTP data registers */
    err = getHwRegister(pDis, E_REG_P12_OTP_DATA_MSB_RW, &pOtpData[0]);
    RETIF_REG_FAIL(err)
    err = getHwRegister(pDis, E_REG_P12_OTP_DATA_ISB_RW, &pOtpData[1]);
    RETIF_REG_FAIL(err)
    err = getHwRegister(pDis, E_REG_P12_OTP_DATA_LSB_RW, &pOtpData[2]);
    RETIF_REG_FAIL(err)

    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpGetT0FailState                                              */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpGetT0FailState
(
    tmUnitSelect_t  txUnit,
    UInt8           *pFailState
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Return if pointer is null */
    RETIF_BADPARAM(!pFailState)

    /* Return the value */
    *pFailState = pDis->HdcpT0FailState;
    return TM_OK;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleBCAPS                                                 */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleBCAPS
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Read sink BCAPS from DDC */
    err = getHwRegister(pDis, E_REG_P12_BCAPS_RX_R, &pDis->HdcpBcaps);
    RETIF_REG_FAIL(err)

    /* HDCP receiver repeater options */
    if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_NO_REPEATER) > 0)
    {
        /* Forced as not a repeater */
        err = setHwRegisterField(pDis, E_REG_P12_TX2_RW,
                                 E_MASKREG_P12_TX2_selrptsrc |
                                 E_MASKREG_P12_TX2_rpt_force, 2);
        RETIF_REG_FAIL(err)

        /* BCAPS:repeater bit forced to 0 (N4 and above) */
        err = setHwRegisterField(pDis, E_REG_P12_BCAPS_W,
                                 E_MASKREG_P12_BCAPS_repeater, 0);
        RETIF_REG_FAIL(err)

    }
    else if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_REPEATER) > 0)
    {
        /* Forced as a repeater */
        err = setHwRegisterField(pDis, E_REG_P12_TX2_RW,
                                 E_MASKREG_P12_TX2_selrptsrc |
                                 E_MASKREG_P12_TX2_rpt_force, 3);
        RETIF_REG_FAIL(err)

        /* BCAPS:repeater bit follows BCAPS_RX (N4 and above) */
        err = setHwRegisterField(pDis, E_REG_P12_BCAPS_W,
                                 E_MASKREG_P12_BCAPS_repeater, 1);
        RETIF_REG_FAIL(err)

    }
    else
    {
        /* Obey BCAPS bit 6 */
        err = setHwRegisterField(pDis, E_REG_P12_TX2_RW,
                                 E_MASKREG_P12_TX2_selrptsrc |
                                 E_MASKREG_P12_TX2_rpt_force, 0);
        RETIF_REG_FAIL(err)

        /* BCAPS:repeater bit follows BCAPS_RX (N4 and above) */
        err = setHwRegisterField(pDis, E_REG_P12_BCAPS_W,
                                 E_MASKREG_P12_BCAPS_repeater,
                    (UInt8)(((pDis->HdcpBcaps &
                    E_MASKREG_P12_BCAPS_RX_repeater) > 0) ? 1 : 0));
        RETIF_REG_FAIL(err)

    }


    /* HDCP receiver does not support 1.1 enhanced encryption, or is forced */
    if (((pDis->HdcpBcaps & E_MASKREG_P12_BCAPS_RX_1_1) == 0)
     || ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_NO_1_1) > 0))
    {
        err = setHwRegisterField(pDis, E_REG_P12_BCAPS_W,
                                 E_MASKREG_P12_BCAPS_1_1, 0);
        RETIF_REG_FAIL(err)
        err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                                 E_MASKREG_P12_TX0_ainfo_1, 0);
        RETIF_REG_FAIL(err)
    }
    else
    {
        err = setHwRegisterField(pDis, E_REG_P12_BCAPS_W,
                                 E_MASKREG_P12_BCAPS_1_1, 1);
        RETIF_REG_FAIL(err)
        err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                                 E_MASKREG_P12_TX0_ainfo_1, 1);
        RETIF_REG_FAIL(err)
    }

    /** \todo Handle other BCAPS bits and HDMITX_HDCP_OPTION_FORCE_SLOW_DDC */

    /* Signal that BCAPS was read */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_ainfo_rdy, 1);
    RETIF_REG_FAIL(err)
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_ainfo_rdy, 0);

    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleBKSV                                                  */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleBKSV
(
    tmUnitSelect_t  txUnit,
    UInt8           *pBksv,
    Bool            *pbCheckRequired  /* May be null, but only for testing */
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Return if pointer is not assigned; pbCheckRequired can be Null */
    RETIF_BADPARAM(pBksv == Null)

    /* Top level and repeater :
	 * Read BKSV, MSB first: bksv[0]=MSB, bksv[4]=LSB */
    err = getHwRegisters(pDis, E_REG_P12_BKSV4_R, pBksv,
                         HDMITX_KSV_BYTES_PER_DEVICE);

    /* Is this driver operating as part of a Repeater? */
    if (pDis->HdcpTxMode == HDMITX_HDCP_TXMODE_REPEATER)
    {
        /* Repeater: Set 5s watchdog timer - now suppressed (PNF57) */
        /*err = setHwRegisterFieldTable(pDis, &kSet5secWatchdog[0]);
        RETIF_REG_FAIL(err) */

        /* No revocation list check needed for a TX repeater */
    }
    /* Not Repeater: Is this driver part of a top level transmitter? */
    else if (pDis->HdcpTxMode == HDMITX_HDCP_TXMODE_TOP_LEVEL)
    {
        /* CALLER MUST NOW CHECK BKSV AGAINST REVOCATION LIST AND CALL
         * tmbslTDA9989HdcpHandleBKSVResult, which will set state from result */
        if (pbCheckRequired)
        {
            /* Always return True for an application; can skip for testing */
            *pbCheckRequired = True;
        }
        return err; /* State is set later by tmbslTDA9989HdcpHandleBKSVResult */
    }
    /* else No revocation list check needed for this TX */

    /* BKSV is secure, disable BCAPS interrupt */
    err = setHwRegisterFieldTable(pDis, &kBksvSecure[0]);
    RETIF_REG_FAIL(err)

    /* Check if receiver is a repeater */
    if ((pDis->HdcpBcaps & E_MASKREG_P12_BCAPS_RX_repeater) > 0)
    {
        /* Go to next part of authentication for a repeater */
        setState(pDis, EV_HDCP_BKSV_REPEAT);
    }
    else
    {
        /* A secure non-repeater has authenticated */
        setState(pDis, EV_HDCP_BKSV_NREPEAT);
    }
    
    /* User revocation test is not required, pBksv is not set */
    if (pbCheckRequired)
    {
        *pbCheckRequired = False;
    }
    return TM_OK;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleBKSVResult                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleBKSVResult
(
    tmUnitSelect_t  txUnit,
    Bool            bSecure
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check other parameters */
    RETIF_BADPARAM(bSecure > 1)

    if (bSecure)
    {
        /* PNF57 Set 1s watchdog based on HDMI clock */
        err = setHwRegisterField(pDis, E_REG_P12_CTRL_W,
                                 E_MASKREG_P12_CTRL_hdcp_ena, 1);
        RETIF_REG_FAIL(err) 
    }
    else
    {
        /* BKSV is not secure, re-enable BCAPS interrupt */
        err = setHwRegisterFieldTable(pDis, &kBksvNotSecure[0]);
        RETIF_REG_FAIL(err)

        /* Authentication has failed */
        setState(pDis, EV_HDCP_BKSV_NSECURE);
    }

    return TM_OK;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleBSTATUS                                               */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleBSTATUS
(
    tmUnitSelect_t  txUnit,
    UInt16          *pBstatus   /* May be null */
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    UInt8             bstatus[2];

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Read BSTATUS MSB & LSB into bstatus[0] and [1] */
    err = getHwRegisters(pDis, E_REG_P12_BSTATUS_1_R, bstatus, 2);

    /* Check result of read */
    if (err != TM_OK)
    {
        /* No T0 interrupt from device after a bad BSTATUS so do it ourselves */
        err = tmbslTDA9989HdcpHandleT0(txUnit);/* Does a T0 state change */
        pDis->HdcpBstatus = 0;
    }
    else
    {
        /* Save BSTATUS to Device Instance Structure */
        pDis->HdcpBstatus = ((UInt16)bstatus[0] << 8) | bstatus[1];

        /* Check bstatus topology error indicators */
        if (((pDis->HdcpBstatus & HDMITX_HDCP_BSTATUS_MAX_CASCADE_EXCEEDED) > 0)
        ||  ((pDis->HdcpBstatus & HDMITX_HDCP_BSTATUS_MAX_DEVS_EXCEEDED) > 0))
        {
            /* No T0 interrupt from device after a bad BSTATUS so do it here */
            err = tmbslTDA9989HdcpHandleT0(txUnit);/* ->T0 state change */
        }
        else
        {
            err = TM_OK;
            setState(pDis, EV_HDCP_BSTATUS_GOOD);
        }
    }

    /* Copy to optional output parameter */
    if (pBstatus)
    {
        *pBstatus = pDis->HdcpBstatus;
    }
    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleENCRYPT                                               */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleENCRYPT
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    
    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    if ((pDis->state == ST_HDCP_WAIT_RX)
        ||
        (pDis->state == ST_HDCP_WAIT_BSTATUS)
        ||
        (pDis->state == ST_HDCP_WAIT_SHA_1)
        ||
        (pDis->state == ST_HDCP_AUTHENTICATED)
       )
    {
        if (pDis->HDCPIgnoreEncrypt)
        {
            /* Ignore 1st encrypt after HdcpInit */
            pDis->HDCPIgnoreEncrypt = False;
            return TM_OK;
        }
        else
        {
            /* Reset HDCP */
            return tmbslTDA9989HdcpHandleT0(txUnit); /* Does T0 state change */
        }
    }

    return TM_OK;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandlePJ                                                    */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandlePJ
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    
    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_PJ_IGNORED) == 0)
    {
        return tmbslTDA9989HdcpHandleT0(txUnit); /* Does T0 state change */
    }
    return TM_OK;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleSHA_1                                                 */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleSHA_1
(
    tmUnitSelect_t  txUnit,
    UInt8           maxKsvDevices,
    UInt8           *pKsvList,          /* May be null if maxKsvDevices is 0 */
    UInt8           *pnKsvDevices,      /* May be null if maxKsvDevices is 0 */
    UInt8           *pDepth             /* Connection tree depth returned with KSV list */
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;             /* Pointer to Device Instance Struct. */
    tmErrorCode_t     err;              /* Error code */
    UInt8             v_equ_vbar;       /* Register value for V=V' */
    UInt8             bstatusDevices;   /* No. of devices defined in BSTATUS */
    UInt16            ksvIndex;         /* Byte index into KSV list */
    UInt16            i;                /* Loop counter */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Re-read the BCAPS register since the bit ready KSV may not be set when the BCAP interrupt occurs */   
    err = getHwRegister(pDis, E_REG_P12_BCAPS_RX_R, &pDis->HdcpBcaps);
    RETIF_REG_FAIL(err)


    /* Check other parameters */
    RETIF_BADPARAM(maxKsvDevices > HDMITX_KSV_LIST_MAX_DEVICES)
    if (maxKsvDevices > 0)
    {
        RETIF((pKsvList == Null) || (pnKsvDevices == Null),
              TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
    }

    RETIF(pDepth == Null, TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)

    /* Force V=V' or read it from transmitter */
    if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_V_EQU_VBAR) > 0)
    {
        v_equ_vbar = 1;
    }
    else
    {
        err = getHwRegister(pDis, E_REG_P12_KSV_check_R, &v_equ_vbar);
        if (err != TM_OK)
        {
            /* Force bad value if supposed to read it but can't */
            v_equ_vbar = 0;
        }
    }

    err = TM_OK;
    if (!v_equ_vbar)
    {
        /* V=V' could not be read or is not set: reset HDCP */
        err = tmbslTDA9989HdcpHandleT0(txUnit); /* Does T0 state change */
        /*V != V' error HDCP*/
        err = TMBSL_ERR_HDMI_INCONSISTENT_PARAMS;
        if (pnKsvDevices)
        {
            *pnKsvDevices = 0;
        }
    }
    else
    { 
        /* read connection tree depth */
        if (pDepth != Null)
        {
            *pDepth = (UInt8)((pDis->HdcpBstatus & HDMITX_HDCP_BSTATUS_CASCADE_DEPTH)>>8);
        }

        if (maxKsvDevices == 0)
        {
            /* No KSV check requested by caller */
            if (pnKsvDevices)
            {
                *pnKsvDevices = 0;
            }

            /* Treat KSV as secure */
            setState(pDis, EV_HDCP_KSV_SECURE);
        }
        else
        {
            /* The KsvList length is limited by the smaller of the list array
            * length and the number of devices returned in BSTATUS */
            bstatusDevices = 
                (UInt8)(pDis->HdcpBstatus & HDMITX_HDCP_BSTATUS_DEVICE_COUNT);

            if (maxKsvDevices < bstatusDevices)
            {
                *pnKsvDevices = maxKsvDevices;
            }
            else
            {
                *pnKsvDevices = bstatusDevices;
            }

            /* Read the KSV list if there are device KSVs to read */
            if (*pnKsvDevices > 0)
            {
                /* Read KSV list, 5 bytes per device, up to the array length or the
                * number of devices in BSTATUS whichever is smaller */
                for (i = 0; i < *pnKsvDevices; i++)
                {
                    /* Set KSV index */
                    ksvIndex = (UInt16)(i * HDMITX_KSV_BYTES_PER_DEVICE);
                    err = setHwRegister(pDis, E_REG_P12_KSVPTR_LSB_W,
                                    (UInt8)ksvIndex);
                    RETIF_REG_FAIL(err)
                    err = setHwRegister(pDis, E_REG_P12_KSVPTR_MSB_W,
                                    (UInt8)(ksvIndex >> 8));
                    RETIF_REG_FAIL(err)

                    /* Read one device's ksv bytes */
                    err = getHwRegisters(pDis, E_REG_P12_KSV0_R,
                                        pKsvList + ksvIndex,
                                    (UInt8)HDMITX_KSV_BYTES_PER_DEVICE);
                }
                /* CALLER MUST NOW CHECK KSV LIST AGAINST REVOCATION LIST
                * BASED ON *pnKsvDevices > 0; IF REVOCATION LIST CHECK FAILS, 
                * CALLER MUST CALL tmbslTDA9989HdcpHandleT0, WHICH WILL DO A T0
                * STATE CHANGE */
            }
            else
            {
                /* No device KSVs to read so treat KSV as secure */
                setState(pDis, EV_HDCP_KSV_SECURE);
            }
        }
    }
    return err;
#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */

}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleSHA_1Result                                           */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleSHA_1Result
(
    tmUnitSelect_t  txUnit,
    Bool            bSecure
)
{
#ifdef TMFL_HDCP_SUPPORT

    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    UInt8           pixClk;     /* Pixel clock index */
    UInt8           regVal;     /* Register value */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check other parameters */
    RETIF_BADPARAM(bSecure > 1)

    if (bSecure)
    {
        pix_clk(pDis->voutFmt, pDis->voutFreq, &pixClk);

        if (pixClk != E_PIXCLK_INVALID)
        {
            /* Set watchdog timer reference to nearest pixel clock MHz */
            regVal = kPixClkToMHz[pixClk];
            err = setHwRegister(pDis, E_REG_P00_NDIV_PF_W, regVal);
            RETIF_REG_FAIL(err)

            err = setHwRegisterFieldTable(pDis, &kSetRiWatchdog[0]);
            RETIF_REG_FAIL(err)
        }

        
        err = setHwRegisterFieldTable(pDis, &kKsvLSecure[0]);
        RETIF_REG_FAIL(err)

        setState(pDis, EV_HDCP_KSV_SECURE);
    }
    else
    {
        /* BKSV is not secure */
        err = setHwRegisterFieldTable(pDis, &kKsvLNotSecure[0]);
        RETIF_REG_FAIL(err)
    }
    return err;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */

}

/*============================================================================*/
/* tmbslTDA9989HdcpHandleT0                                                    */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpHandleT0
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT

    tmHdmiTxobject_t    *pDis;    /* Pointer to Device Instance Structure */
    UInt8               pixClk;   /* Pixel clock index */
    UInt8               regVal;   /* Register value */
    tmErrorCode_t       err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Get device HDCP failure state that caused this interrupt.
     * This is an N4 register, but will return 0 for earlier versions. */
    err = getHwRegister(pDis, E_REG_P12_FAILSTATE_R,
                        &pDis->HdcpT0FailState);
    RETIF_REG_FAIL(err);

    /* Use voutFmt and voutFreq to index into a lookup table to get
     * the current HDMI pixel clock value. */
     
    pix_clk(pDis->voutFmt, pDis->voutFreq, &pixClk);

    if (pixClk != E_PIXCLK_INVALID)
    {
        /* Set watchdog timer reference to nearest pixel clock MHz */
        regVal = kPixClkToMHz[pixClk];
        err = setHwRegister(pDis, E_REG_P00_NDIV_PF_W, regVal);
        RETIF_REG_FAIL(err)

       /* Set 120ms watchdog based on HDMI clock */
       err = setHwRegisterFieldTable(pDis, &kSet120msWatchdog[0]);
       RETIF_REG_FAIL(err)
    }
    
    /* Recover from HDCP T0 interrupt */
    err = setHwRegisterFieldTable(pDis, &kT0Recovery[0]);
    RETIF_REG_FAIL(err)

    /* Enable all HDCP interrupts */
    regVal =
        E_MASKREG_P00_INT_FLAGS_0_sha_1   |
        E_MASKREG_P00_INT_FLAGS_0_bstatus |
        E_MASKREG_P00_INT_FLAGS_0_bcaps   |
        E_MASKREG_P00_INT_FLAGS_0_t0      |
        E_MASKREG_P00_INT_FLAGS_0_r0      |
        E_MASKREG_P00_INT_FLAGS_0_encrypt;
    if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_PJ_IGNORED) == 0)
    {
        /* Include Pj */
        regVal |= E_MASKREG_P00_INT_FLAGS_0_pj;
    }
    err = setHwRegisterField(pDis, E_REG_P00_INT_FLAGS_0_RW, regVal, regVal);
    RETIF_REG_FAIL(err)

    /* Set the flag so 1st Encrypt interrupt is ignored after a T0 error*/
    pDis->HDCPIgnoreEncrypt = True;


    /* Relaunch HDCP algorithm after interrupts enabled, to avoid missing any */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_sr_hdcp, 0);
    RETIF_REG_FAIL(err)

    err = unlockHDCPStateMachine(pDis);
    RETIF(err != TM_OK, err)

    /* Disable any scheduled function, leave HDCP check timer running */
    pDis->HdcpFuncRemainingMs = 0;

    setState(pDis, EV_HDCP_T0);
    return TM_OK;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */

}

/*============================================================================*/
/* tmbslTDA9989HdcpInit                                                        */
/* RETIF_REG_FAIL NOT USED HERE AS ALL ERRORS SHOULD BE TRAPPED IN ALL BUILDS */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpInit
(
    tmUnitSelect_t      txUnit,
    tmbslHdmiTxVidFmt_t voutFmt,
    tmbslHdmiTxVfreq_t  voutFreq
)
{

#ifdef TMFL_HDCP_SUPPORT

    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */
    UInt8             pixClk;   /* Pixel clock index */
    UInt8             regVal;   /* Register value */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Check other arguments */
#ifdef FORMAT_PC
    RETIF_BADPARAM(voutFmt       < HDMITX_VFMT_TV_MIN)
    RETIF_BADPARAM((voutFmt > HDMITX_VFMT_TV_MAX) && (voutFmt < HDMITX_VFMT_PC_MIN))
    RETIF_BADPARAM(voutFmt       > HDMITX_VFMT_PC_MAX)
#else /* FORMAT_PC */
    /*FORMAT TV only*/
    RETIF_BADPARAM(voutFmt       < HDMITX_VFMT_TV_MIN)
    RETIF_BADPARAM(voutFmt       > HDMITX_VFMT_TV_MAX)
#endif /* FORMAT_PC */
    
    RETIF_BADPARAM(voutFreq >= HDMITX_VFREQ_INVALID)
    
#ifdef FORMAT_PC
    if ( voutFmt < HDMITX_VFMT_PC_MIN )
    {
#endif /* FORMAT_PC */
       if (voutFreq == HDMITX_VFREQ_50Hz)
          {
             RETIF(((voutFmt < HDMITX_VFMT_17_720x576p_50Hz)        \
                    || (voutFmt > HDMITX_VFMT_31_1920x1080p_50Hz)),
                   TMBSL_ERR_HDMI_INCONSISTENT_PARAMS);
          }
       else if (voutFreq == HDMITX_VFREQ_24Hz)
          {
             RETIF((voutFmt != HDMITX_VFMT_32_1920x1080p_24Hz)      \
                   && (voutFmt != HDMITX_VFMT_60_1280x720p_24Hz),
                   TMBSL_ERR_HDMI_INCONSISTENT_PARAMS);
          }
       else if (voutFreq == HDMITX_VFREQ_25Hz)
          {
             RETIF((voutFmt != HDMITX_VFMT_33_1920x1080p_25Hz)      \
                   && (voutFmt != HDMITX_VFMT_20_1920x1080i_50Hz)   \
                   && (voutFmt != HDMITX_VFMT_61_1280x720p_25Hz),
                   TMBSL_ERR_HDMI_INCONSISTENT_PARAMS);
          }
       else if (voutFreq == HDMITX_VFREQ_30Hz)
          {
             RETIF((voutFmt != HDMITX_VFMT_34_1920x1080p_30Hz)      \
                   && (voutFmt != HDMITX_VFMT_05_1920x1080i_60Hz)   \
                   && (voutFmt != HDMITX_VFMT_62_1280x720p_30Hz),
                   TMBSL_ERR_HDMI_INCONSISTENT_PARAMS);
          }
       else
          {
             RETIF(voutFmt >= HDMITX_VFMT_17_720x576p_50Hz,
                   TMBSL_ERR_HDMI_INCONSISTENT_PARAMS);
          }
#ifdef FORMAT_PC
    }
    else
    {
        if (voutFreq == HDMITX_VFREQ_60Hz)
        {
            RETIF(voutFmt > HDMITX_VFMT_PC_1600x1200p_60Hz,
                                       TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
        }
        else if (voutFreq == HDMITX_VFREQ_70Hz)
        {
            RETIF(voutFmt != HDMITX_VFMT_PC_1024x768p_70Hz,
                                       TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
        }
        else if (voutFreq == HDMITX_VFREQ_72Hz)
        {
            RETIF( ((voutFmt < HDMITX_VFMT_PC_640x480p_72Hz) ||
                    (voutFmt > HDMITX_VFMT_PC_800x600p_72Hz)),
                                       TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
        }
        else if (voutFreq == HDMITX_VFREQ_75Hz)
        {
            RETIF( ((voutFmt < HDMITX_VFMT_PC_640x480p_75Hz) ||
                    (voutFmt > HDMITX_VFMT_PC_1280x1024p_75Hz)),
                                       TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
        }
        else if (voutFreq == HDMITX_VFREQ_85Hz)
        {
            RETIF( ((voutFmt < HDMITX_VFMT_PC_640x350p_85Hz) ||
                    (voutFmt > HDMITX_VFMT_PC_1280x1024p_85Hz)),
                                       TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
        }
        else
        {
            RETIF(voutFmt != HDMITX_VFMT_PC_1024x768i_87Hz,
                                       TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)
        }
    }
#endif /* FORMAT_PC */

    /* Use voutFmt and voutFreq to index into a lookup table to get
     * the current pixel clock value. */
     
    pix_clk(voutFmt, voutFreq, &pixClk);

    RETIF(pixClk == E_PIXCLK_INVALID, TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)

    /* Save vertical output frequency for use later by HandleT0 */
    pDis->voutFreq = voutFreq;

    /* Initialise HDCP (part 1) */
    err = setHwRegisterFieldTable(pDis, &kHdcpInit1[0]);
    RETIF(err != TM_OK, err)

    /* Set watchdog timer reference to nearest pixel clock MHz */
    regVal = kPixClkToMHz[pixClk];
    err = setHwRegister(pDis, E_REG_P00_NDIV_PF_W, regVal);
    RETIF(err != TM_OK, err)

    /* Set 120ms watchdog based on HDMI clock */
    err = setHwRegisterFieldTable(pDis, &kSet120msWatchdog[0]);
    RETIF(err != TM_OK, err)

    /* Initialise HDCP (part 2) */
    err = setHwRegisterFieldTable(pDis, &kHdcpInit2[0]);
    RETIF(err != TM_OK, err)

    /* Set DDC speed */
/*     if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_VSLOW_DDC) > 0) */
/*     { */
/*         regVal = 100; */
/*     } */
/*     else */
/*     { */
/*         regVal = 50; */
/*     } */
/*     err = setHwRegister(pDis, E_REG_P12_TX3_RW, regVal); */
/*     RETIF(err != TM_OK, err) */

    /* Initialise HDCP (part 3) */
    err = setHwRegisterFieldTable(pDis, &kHdcpInit3[0]);
    RETIF(err != TM_OK, err)

    /* Obey sink type - done in tmbslTDA9989VideoOutSetConfig */

    /* Set flag so 1st Encrypt interrupt after HdcpInit is ignored */
    pDis->HDCPIgnoreEncrypt = True;

    /* Enable all HDCP interrupts */
    regVal =
        E_MASKREG_P00_INT_FLAGS_0_sha_1   |
        E_MASKREG_P00_INT_FLAGS_0_bstatus |
        E_MASKREG_P00_INT_FLAGS_0_bcaps   |
        E_MASKREG_P00_INT_FLAGS_0_t0      |
        E_MASKREG_P00_INT_FLAGS_0_r0      |
        E_MASKREG_P00_INT_FLAGS_0_encrypt;
    if ((pDis->HdcpOptions & HDMITX_HDCP_OPTION_FORCE_PJ_IGNORED) == 0)
    {
        /* Include Pj */
        regVal |= E_MASKREG_P00_INT_FLAGS_0_pj;
    }
    err = setHwRegisterField(pDis, E_REG_P00_INT_FLAGS_0_RW, regVal, regVal);
    return err;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */

}

/*============================================================================*/
/* tmbslTDA9989HdcpRun                                                         */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpRun
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT

    tmHdmiTxobject_t    *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t       err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Reset device HDCP data in DIS to ensure that new values are used */
    pDis->HdcpBcaps = 0;
    pDis->HdcpBstatus = 0;
    pDis->HdcpT0FailState = 0;
    pDis->HdcpFsmState = 0;
    pDis->HdcpRi = 0;


    /* Launch HDCP algorithm */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_sr_hdcp, 0);

    err = unlockHDCPStateMachine(pDis);
    RETIF(err != TM_OK, err)

    if (err == TM_OK)
    {
        /* Start the HDCP check timer if checking is configured */
        if (pDis->HdcpChecksToDo > 1)
        {
            pDis->HdcpCheckRemainingMs = pDis->HdcpCheckIntervalMs;
            pDis->HdcpCheckNum = 1;
        }

        setState(pDis, EV_HDCP_RUN);
    }
    return err;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpStop                                                        */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpStop
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t    *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t       err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* Check if this device supports HDCP */
    RETIF(pDis->uDeviceFeatures & E_MASKREG_P00_VERSION_not_h,
          TMBSL_ERR_HDMI_NOT_SUPPORTED)

    /* Disable all HDCP interrupts */
    (void)setHwRegister(pDis, E_REG_P00_INT_FLAGS_0_RW,0);

    /* Stop HDCP algorithm */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_sr_hdcp, 1);


    /*reset to timer default values */

    err = setHwRegister(pDis, E_REG_P00_TIMER_H_W, TDA19989_TIMER_H_DEFAULT);
    RETIF(err != TM_OK, err)

    err = setHwRegister(pDis, E_REG_P00_TIMER_M_W, TDA19989_TIMER_M_DEFAULT);
    RETIF(err != TM_OK, err)

    err = setHwRegister(pDis, E_REG_P00_TIMER_L_W, TDA19989_TIMER_L_DEFAULT);
    RETIF(err != TM_OK, err)

    /* Disable any scheduled function and HDCP check timer */
    pDis->HdcpFuncRemainingMs = 0;
    pDis->HdcpCheckNum = 0;

    setState(pDis, EV_HDCP_STOP);
    return err;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}

/*============================================================================*/
/* tmbslTDA9989HdcpGetSinkCategory                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989HdcpGetSinkCategory
(
    tmUnitSelect_t              txUnit,
    tmbslHdmiTxSinkCategory_t   *category
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t     err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    RETIF(category == Null, TMBSL_ERR_HDMI_INCONSISTENT_PARAMS)

        /* check if receiver is a repeater */
        if ((pDis->HdcpBcaps & E_MASKREG_P12_BCAPS_RX_repeater) > 0)
        {
            *category = HDMITX_SINK_CAT_REPEATER;
        }
        else
        {
            *category = HDMITX_SINK_CAT_NOT_REPEATER;
        }

    return err;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */
}




/*============================================================================*/
/* tmbslTDA9989handleBKSVResultSecure                                         */
/*============================================================================*/
tmErrorCode_t
tmbslTDA9989handleBKSVResultSecure
(
    tmUnitSelect_t  txUnit
)
{
#ifdef TMFL_HDCP_SUPPORT
    tmHdmiTxobject_t    *pDis;     /* Pointer to Device Instance Structure */
    tmErrorCode_t       err;      /* Error code */

    /* Check unit parameter and point to its object */
    err = checkUnitSetDis(txUnit, &pDis);
    RETIF(err != TM_OK, err)

    /* BKSV is secure: check if receiver is a repeater */
    if ((pDis->HdcpBcaps & E_MASKREG_P12_BCAPS_RX_repeater) > 0)
    {

        pDis->sysFuncTimer(200);//give delay before starting BCAP ready bit chekcing

        err = setHwRegisterFieldTable(pDis, &kSet5secWatchdog[0]);
        RETIF_REG_FAIL(err) 
        /* Go to next part of authentication for a repeater */
        setState(pDis, EV_HDCP_BKSV_REPEAT);
    }
    else
    {
        err = setHwRegisterFieldTable(pDis, &kSetRiWatchdog[0]);
        RETIF_REG_FAIL(err)
        /* A secure non-repeater has authenticated */
        setState(pDis, EV_HDCP_BKSV_NREPEAT);
    }


    /* BKSV is secure, disable BCAPS interrupt */
    err = setHwRegisterFieldTable(pDis, &kBksvSecure[0]);
    return err;

#else /* TMFL_HDCP_SUPPORT */
    return TMBSL_ERR_HDMI_NOT_SUPPORTED;
#endif /* TMFL_HDCP_SUPPORT */

}


/*============================================================================*/
/*                              STATIC FUNCTIONS                              */
/*============================================================================*/


/*============================================================================*/
/* unlockHDCPStateMachine                                                     */
/*============================================================================*/
#ifdef TMFL_HDCP_SUPPORT
static tmErrorCode_t    unlockHDCPStateMachine(tmHdmiTxobject_t *pDis)
{

    tmErrorCode_t err = TM_OK;  /* Error code */

    /* Add 60ms timer (~3 frames) to get rid of error in simplayHD test7-20 */
    pDis->sysFuncTimer(60); /* ms */

    /* Unlock HDCP state Machine */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_hook_sm, 0);

    RETIF_REG_FAIL(err)

    /* Lock HDCP state Machine */
    err = setHwRegisterField(pDis, E_REG_P12_TX0_RW,
                             E_MASKREG_P12_TX0_hook_sm, 1);

    RETIF_REG_FAIL(err)

    return err;

}
#endif /* TMFL_HDCP_SUPPORT */


/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/
