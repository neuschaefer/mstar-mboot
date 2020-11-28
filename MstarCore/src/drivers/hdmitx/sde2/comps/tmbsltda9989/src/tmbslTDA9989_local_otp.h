/**
 * Copyright (C) 2009 NXP N.V., All Rights Reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of NXP N.V. and is confidential in nature. Under no circumstances
 * is this software to be  exposed to or placed under an Open Source License of
 * any type without the expressed written permission of NXP N.V.
 *
 * \file          tmbslTDA9989_local_otp.h
 *
 * \version       %version: 2 %
 *
*/

#ifndef TMBSLTDA9989_LOCAL_OTP_H
#define TMBSLTDA9989_LOCAL_OTP_H


/*============================================================================*/
/*                       ENUM OR TYPE DEFINITIONS                             */
/*============================================================================*/

#define BINARY(d7,d6,d5,d4,d3,d2,d1,d0) \
    (((d7)<<7)|((d6)<<6)|((d5)<<5)|((d4)<<4)|((d3)<<3)|((d2)<<2)|((d1)<<1)|(d0))

enum _eRegOtp {
    E_REG_P12_OTP_ADDRESS_W          = SPA(E_SNONE            , E_PAGE_12, 0x30),
    E_REG_P12_OTP_DATA_MSB_RW        = SPA(E_SNONE            , E_PAGE_12, 0x31),
    E_REG_P12_OTP_DATA_ISB_RW        = SPA(E_SNONE            , E_PAGE_12, 0x32),
    E_REG_P12_OTP_DATA_LSB_RW        = SPA(E_SNONE            , E_PAGE_12, 0x33),
    E_REG_P12_OTP_CNTRL_W            = SPA(E_SNONE            , E_PAGE_12, 0x34),
    E_REG_P12_OTP_STATUS_R           = SPA(E_SNONE            , E_PAGE_12, 0x35),
    E_REG_P12_VPP_TIMER_W            = SPA(E_SNONE            , E_PAGE_12, 0x36),
    E_REG_P12_WRITE_TIMER_W          = SPA(E_SNONE            , E_PAGE_12, 0x37),
    E_REG_P12_DISCHARGE_TIMER_W      = SPA(E_SNONE            , E_PAGE_12, 0x38),
    E_REG_P12_READ_TIMER_W           = SPA(E_SNONE            , E_PAGE_12, 0x39),
#ifdef TMFL_HDCP_SUPPORT
    E_REG_P12_CTRL_W                 = SPA(E_SP12_CTRL        , E_PAGE_12, 0x40),
#endif /* TMFL_HDCP_SUPPORT */
    E_REG_P12_KDS_HI_W          = SPA(E_SNONE            , E_PAGE_12, 0x42),
    E_REG_P12_KDS_LO_W          = SPA(E_SNONE            , E_PAGE_12, 0x43),
#ifdef TMFL_HDCP_SUPPORT
    E_REG_P12_BCAPS_W                = SPA(E_SP12_BCAPS       , E_PAGE_12, 0x49),
#endif /* TMFL_HDCP_SUPPORT */
    E_REG_P12_AKSV4_W           = SPA(E_SNONE            , E_PAGE_12, 0x4B),
    E_REG_P12_AKSV3_W           = SPA(E_SNONE            , E_PAGE_12, 0x4C),
    E_REG_P12_AKSV2_W           = SPA(E_SNONE            , E_PAGE_12, 0x4D),
    E_REG_P12_AKSV1_W           = SPA(E_SNONE            , E_PAGE_12, 0x4E),
    E_REG_P12_AKSV0_W           = SPA(E_SNONE            , E_PAGE_12, 0x4F),
    E_REG_P12_KIDX_W            = SPA(E_SNONE            , E_PAGE_12, 0x50),
    E_REG_P12_KEY6_W            = SPA(E_SNONE            , E_PAGE_12, 0x51),
    E_REG_P12_KEY5_W            = SPA(E_SNONE            , E_PAGE_12, 0x52),
    E_REG_P12_KEY4_W            = SPA(E_SNONE            , E_PAGE_12, 0x53),
    E_REG_P12_KEY3_W            = SPA(E_SNONE            , E_PAGE_12, 0x54),
    E_REG_P12_KEY2_W            = SPA(E_SNONE            , E_PAGE_12, 0x55),
    E_REG_P12_KEY1_W            = SPA(E_SNONE            , E_PAGE_12, 0x56),
    E_REG_P12_KEY0_W            = SPA(E_SNONE            , E_PAGE_12, 0x57),
    E_REG_P12_RI1_R             = SPA(E_SNONE            , E_PAGE_12, 0x60),
    E_REG_P12_RI0_R             = SPA(E_SNONE            , E_PAGE_12, 0x61),
    E_REG_P12_FSM_STATE_R       = SPA(E_SNONE            , E_PAGE_12, 0x62),
    E_REG_P12_BKSV4_R           = SPA(E_SNONE            , E_PAGE_12, 0x63),
    E_REG_P12_BKSV3_R           = SPA(E_SNONE            , E_PAGE_12, 0x64),
    E_REG_P12_BKSV2_R           = SPA(E_SNONE            , E_PAGE_12, 0x65),
    E_REG_P12_BKSV1_R           = SPA(E_SNONE            , E_PAGE_12, 0x66),
    E_REG_P12_BKSV0_R           = SPA(E_SNONE            , E_PAGE_12, 0x67),
    E_REG_P12_AN7_R             = SPA(E_SNONE            , E_PAGE_12, 0x68),
    E_REG_P12_AN6_R             = SPA(E_SNONE            , E_PAGE_12, 0x69),
    E_REG_P12_AN5_R             = SPA(E_SNONE            , E_PAGE_12, 0x6A),
    E_REG_P12_AN4_R             = SPA(E_SNONE            , E_PAGE_12, 0x6B),
    E_REG_P12_AN3_R             = SPA(E_SNONE            , E_PAGE_12, 0x6C),
    E_REG_P12_AN2_R             = SPA(E_SNONE            , E_PAGE_12, 0x6D),
    E_REG_P12_AN1_R             = SPA(E_SNONE            , E_PAGE_12, 0x6E),
    E_REG_P12_AN0_R             = SPA(E_SNONE            , E_PAGE_12, 0x6F),
    E_REG_P12_PJ_R              = SPA(E_SNONE            , E_PAGE_12, 0x70),
    E_REG_P12_AINFO_R           = SPA(E_SNONE            , E_PAGE_12, 0x71),
    E_REG_P12_KSVPTR_LSB_W      = SPA(E_SNONE            , E_PAGE_12, 0x90),
    E_REG_P12_KSVPTR_MSB_W      = SPA(E_SNONE            , E_PAGE_12, 0x91),
    E_REG_P12_KSV0_R            = SPA(E_SNONE            , E_PAGE_12, 0x92),
    E_REG_P12_KSV1_R            = SPA(E_SNONE            , E_PAGE_12, 0x93),
    E_REG_P12_KSV2_R            = SPA(E_SNONE            , E_PAGE_12, 0x94),
    E_REG_P12_KSV3_R            = SPA(E_SNONE            , E_PAGE_12, 0x95),
    E_REG_P12_KSV4_R            = SPA(E_SNONE            , E_PAGE_12, 0x96),
    E_REG_P12_TX0_RW            = SPA(E_SNONE            , E_PAGE_12, 0x97),
    E_REG_P12_TX1_RW            = SPA(E_SNONE            , E_PAGE_12, 0x98),
    E_REG_P12_TX2_RW            = SPA(E_SNONE            , E_PAGE_12, 0x99),
    E_REG_P12_TX3_RW            = SPA(E_SNONE            , E_PAGE_12, 0x9A),
#ifdef TMFL_HDCP_OPTIMIZED_POWER
    E_REG_P12_TX4_RW            = SPA(E_SNONE            , E_PAGE_12, 0x9B),
#endif
    E_REG_P12_KSV_check_R       = SPA(E_SNONE            , E_PAGE_12, 0xA0),
    E_REG_P12_BSTATUS_1_R       = SPA(E_SNONE            , E_PAGE_12, 0xA1),
    E_REG_P12_BSTATUS_0_R       = SPA(E_SNONE            , E_PAGE_12, 0xA2),
    E_REG_P12_BCAPS_RX_R        = SPA(E_SNONE            , E_PAGE_12, 0xA3),
    E_REG_P12_V0_0_R            = SPA(E_SNONE            , E_PAGE_12, 0xA4),
    E_REG_P12_V0_1_R            = SPA(E_SNONE            , E_PAGE_12, 0xA5),
    E_REG_P12_V0_2_R            = SPA(E_SNONE            , E_PAGE_12, 0xA6),
    E_REG_P12_V0_3_R            = SPA(E_SNONE            , E_PAGE_12, 0xA7),
    E_REG_P12_V1_0_R            = SPA(E_SNONE            , E_PAGE_12, 0xA8),
    E_REG_P12_V1_1_R            = SPA(E_SNONE            , E_PAGE_12, 0xA9),
    E_REG_P12_V1_2_R            = SPA(E_SNONE            , E_PAGE_12, 0xAA),
    E_REG_P12_V1_3_R            = SPA(E_SNONE            , E_PAGE_12, 0xAB),
    E_REG_P12_V2_0_R            = SPA(E_SNONE            , E_PAGE_12, 0xAC),
    E_REG_P12_V2_1_R            = SPA(E_SNONE            , E_PAGE_12, 0xAD),
    E_REG_P12_V2_2_R            = SPA(E_SNONE            , E_PAGE_12, 0xAE),
    E_REG_P12_V2_3_R            = SPA(E_SNONE            , E_PAGE_12, 0xAF),
    E_REG_P12_V3_0_R            = SPA(E_SNONE            , E_PAGE_12, 0xB0),
    E_REG_P12_V3_1_R            = SPA(E_SNONE            , E_PAGE_12, 0xB1),
    E_REG_P12_V3_2_R            = SPA(E_SNONE            , E_PAGE_12, 0xB2),
    E_REG_P12_V3_3_R            = SPA(E_SNONE            , E_PAGE_12, 0xB3),
    E_REG_P12_V4_0_R            = SPA(E_SNONE            , E_PAGE_12, 0xB4),
    E_REG_P12_V4_1_R            = SPA(E_SNONE            , E_PAGE_12, 0xB5),
    E_REG_P12_V4_2_R            = SPA(E_SNONE            , E_PAGE_12, 0xB6),
    E_REG_P12_V4_3_R            = SPA(E_SNONE            , E_PAGE_12, 0xB7),
    E_REG_P12_TX33_RW           = SPA(E_SNONE            , E_PAGE_12, 0xB8),
    E_REG_P12_FAILSTATE_R       = SPA(E_SNONE            , E_PAGE_12, 0xB9),

#ifdef TMFL_TDA19989
    E_REG_P12_BACK_COMP_RW      = SPA(E_SNONE            , E_PAGE_12, 0xBC),
#endif /* TMFL_TDA19989 */

};

enum _eMaskRegOtp
{
    E_MASKREG_P12_OTP_CNTRL_start_rd        = BINARY(0,0,0,0, 1,0,0,0),
    E_MASKREG_P12_OTP_CNTRL_start_dl        = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_OTP_CNTRL_bch_act         = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_OTP_CNTRL_start_pc        = BINARY(0,0,0,0, 0,0,0,1),

    E_MASKREG_P12_OTP_STATUS_rd_d_status    = BINARY(1,1,0,0, 0,0,0,0),
    E_MASKREG_P12_OTP_STATUS_rd_c_status    = BINARY(0,0,1,1, 0,0,0,0),
    E_MASKREG_P12_OTP_STATUS_rd_b_status    = BINARY(0,0,0,0, 1,1,0,0),
    E_MASKREG_P12_OTP_STATUS_rd_a_status    = BINARY(0,0,0,0, 0,0,1,1),

#ifdef TMFL_HDCP_SUPPORT

    E_MASKREG_P12_CTRL_ri_rate         = BINARY(1,1,0,0, 0,0,0,0),
    E_MASKREG_P12_CTRL_keyd            = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_CTRL_hdcp_ena        = BINARY(0,0,0,0, 0,0,0,1),

    E_MASKREG_P12_BCAPS_repeater       = BINARY(0,1,0,0, 0,0,0,0),

    E_MASKREG_P12_BCAPS_1_1            = BINARY(0,0,0,0, 0,0,1,0),

    E_MASKREG_P12_TX0_rpt_sr           = BINARY(0,0,1,0, 0,0,0,0),
    E_MASKREG_P12_TX0_hook_sm          = BINARY(0,0,0,1, 0,0,0,0),
    E_MASKREG_P12_TX0_mst_en           = BINARY(0,0,0,0, 1,0,0,0),
    E_MASKREG_P12_TX0_ainfo_1          = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_TX0_ainfo_rdy        = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_TX0_sr_hdcp          = BINARY(0,0,0,0, 0,0,0,1),

    E_MASKREG_P12_TX1_ksvl_nok         = BINARY(0,0,0,0, 1,0,0,0),
    E_MASKREG_P12_TX1_ksvl_ok          = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_TX1_bksv_nok         = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_TX1_bksv_ok          = BINARY(0,0,0,0, 0,0,0,1),

    E_MASKREG_P12_TX2_slvaddr          = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_TX2_selrptsrc        = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_TX2_rpt_force        = BINARY(0,0,0,0, 0,0,0,1),

    E_MASKREG_P12_BCAPS_RX_hdmi        = BINARY(1,0,0,0, 0,0,0,0),
    E_MASKREG_P12_BCAPS_RX_repeater    = BINARY(0,1,0,0, 0,0,0,0),
    E_MASKREG_P12_BCAPS_RX_ready       = BINARY(0,0,1,0, 0,0,0,0),
    E_MASKREG_P12_BCAPS_RX_fast        = BINARY(0,0,0,1, 0,0,0,0),
    E_MASKREG_P12_BCAPS_RX_bit3        = BINARY(0,0,0,0, 1,0,0,0),
    E_MASKREG_P12_BCAPS_RX_bit2        = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_BCAPS_RX_1_1         = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_BCAPS_RX_fast_ra     = BINARY(0,0,0,0, 0,0,0,1),
#endif /* TMFL_HDCP_SUPPORT */

#ifdef TMFL_HDCP_OPTIMIZED_POWER
    E_MASKREG_P12_TX4_pd_rg            = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_TX4_pd_ram           = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_TX4_pd_hdcp          = BINARY(0,0,0,0, 0,0,0,1),
    E_MASKREG_P12_TX4_pd_all           = BINARY(0,0,0,0, 0,1,1,1),
#endif

    E_MASKREG_P12_TX33_ac_not          = BINARY(0,0,1,0, 0,0,0,0),
    E_MASKREG_P12_TX33_ctl_sel         = BINARY(0,0,0,1, 0,0,0,0),
    E_MASKREG_P12_TX33_sys_req         = BINARY(0,0,0,0, 1,0,0,0),
    E_MASKREG_P12_TX33_eess            = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_TX33_hdmi            = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_TX33_avmute          = BINARY(0,0,0,0, 0,0,0,1),

#ifdef TMFL_TDA19989
    E_MASKREG_P12_BACK_COMP_RiCheck          = BINARY(0,0,1,0, 0,0,0,0),
    E_MASKREG_P12_BACK_COMP_AnGen            = BINARY(0,0,0,1, 0,0,0,0),
    E_MASKREG_P12_BACK_COMP_Bcaps            = BINARY(0,0,0,0, 1,0,0,0),
    E_MASKREG_P12_BACK_COMP_3rdPhase         = BINARY(0,0,0,0, 0,1,0,0),
    E_MASKREG_P12_BACK_COMP_2ndPhase         = BINARY(0,0,0,0, 0,0,1,0),
    E_MASKREG_P12_BACK_COMP_1stPhase         = BINARY(0,0,0,0, 0,0,0,1),
#endif /* TMFL_TDA19989 */
};

#endif /* TMBSLTDA9989_LOCAL_OTP_H */
