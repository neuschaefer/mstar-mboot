//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include <common.h>
#include <apiSWI2C.h>
#if ((ENABLE_MSTAR_KENYA == 1)||(ENABLE_MSTAR_KERES == 1))
#include <drvIIC.h>
#endif

#ifndef UNUSED
#define UNUSED(x) ((x)=(x))
#endif

#if ((ENABLE_MSTAR_KAISERIN == 1) || (ENABLE_MSTAR_KENYA == 1))
#define E_I2C_BUS_NUM 8
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
    {
        //Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-0
        {PAD_I2CM0_SCL,PAD_I2CM0_SDA,400}, //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-1
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,400},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-2
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-3
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-4
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-5
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-6
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Bus-7
        {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
        // Others, add other bus here
    };
#elif (ENABLE_MSTAR_KERES == 1)
//empty
#elif (ENABLE_MSTAR_NAPOLI== 1) || (ENABLE_MSTAR_EINSTEIN== 1)
#define E_I2C_BUS_NUM 1
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
{
	//Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C	/SCL_PAD /SDA_PAD /Delay
	// Bus-0
	{PAD_DDCR_CK,PAD_DDCR_DA,400}, //IS_SW_I2C	/SCL_PAD /SDA_PAD /Delay
	// Bus-1
	//{PAD_TGPIO2, PAD_TGPIO3,400},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-2
	//{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-3
	//{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-4
	//{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-5
	//{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-6
	//{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-7
	//{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Others, add other bus here
};
#elif (MS_BOARD_TYPE_SEL == BD_MST029B_10AFVA_A3 || MS_BOARD_TYPE_SEL == BD_MST029B_BOX_A3)
#define E_I2C_BUS_NUM 8
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
{
	//Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C	/SCL_PAD /SDA_PAD /Delay
	// Bus-0
	{PAD_DDCR_CK,PAD_DDCR_DA,400}, //IS_SW_I2C	/SCL_PAD /SDA_PAD /Delay
	// Bus-1
	{PAD_TGPIO2, PAD_TGPIO3,400},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-2
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-3
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-4
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-5
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-6
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-7
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Others, add other bus here
};
#elif (ENABLE_MSTAR_KAISER == 1)
#define E_I2C_BUS_NUM 8
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
{
    //Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C    /SCL_PAD /SDA_PAD /Delay
    // Bus-0
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,400}, //IS_SW_I2C    /SCL_PAD /SDA_PAD /Delay
    // Bus-1
    {PAD_I2CM1_SCL, PAD_I2CM1_SDA,400},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-2
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-3
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-4
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-5
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-6
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-7
    {PAD_I2CM0_SCL, PAD_I2CM0_SDA,100},    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Others, add other bus here
};
#elif (MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225)
#define E_I2C_BUS_NUM 3
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
{
    //Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C  /SCL_PAD /SDA_PAD /Delay
    //Bus-0
    {PAD_DDCR_CK, PAD_DDCR_DA,60}, //EEPROM
    //Bus-1
    {PAD_TGPIO2, PAD_TGPIO3,60}, //TUNER
    //Bus-2
    {PAD_I2S_IN_BCK, PAD_I2S_IN_SD, 60}, //EDINBURGH
    //Bus-3
    //{PAD_DDCDB_CK, PAD_DDCDB_DA, 60}, //HDMI 1 DDC
    //Bus-4
    //{PAD_DDCDC_CK, PAD_DDCDC_DA, 60}, //HDMI 1 DDC
    //Bus-5
    //{PAD_DDCDD_CK, PAD_DDCDD_DA, 60}, //HDMI 1 DDC
};
#elif (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225)
#define E_I2C_BUS_NUM 3
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
{
    //Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C  /SCL_PAD /SDA_PAD /Delay
    //Bus-0
    {PAD_DDCR_CK, PAD_DDCR_DA,60}, //EEPROM
    //Bus-1
    {PAD_TGPIO2, PAD_TGPIO3,60}, //TUNER
    //Bus-2
    {PAD_I2S_IN_BCK, PAD_I2S_IN_SD, 60}, //EDINBURGH
    //Bus-3
    //{PAD_DDCDB_CK, PAD_DDCDB_DA, 60}, //HDMI 1 DDC
    //Bus-4
    //{PAD_DDCDC_CK, PAD_DDCDC_DA, 60}, //HDMI 1 DDC
    //Bus-5
    //{PAD_DDCDD_CK, PAD_DDCDD_DA, 60}, //HDMI 1 DDC
};
#else
#define E_I2C_BUS_NUM 8
static SWI2C_BusCfg I2CBusCfg[E_I2C_BUS_NUM]=
{
	//Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C	/SCL_PAD /SDA_PAD /Delay
	// Bus-0
	{PAD_DDCR_CK,PAD_DDCR_DA,400}, //IS_SW_I2C	/SCL_PAD /SDA_PAD /Delay
	// Bus-1
	{PAD_TGPIO2, PAD_TGPIO3,400},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-2
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-3
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-4
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-5
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-6
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Bus-7
	{PAD_TGPIO2, PAD_TGPIO3,100},	//IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
	// Others, add other bus here
};
#endif

int msI2C_init(void)
{
#if ((ENABLE_MSTAR_KENYA == 1)||(ENABLE_MSTAR_KERES==1))
#if (ENABLE_MSTAR_KERES != 1)
    UNUSED(I2CBusCfg[0]);
#endif
#if (CONFIG_OAD_IN_MBOOT == 1)
    HWI2C_PORT hwi2c_port;
    hwi2c_port = getI2CPort(0);
    printf("IIC port == %d\n", hwi2c_port);
    MDrv_IIC_Init(hwi2c_port);
#endif
#else
	MApi_SWI2C_Init(I2CBusCfg,E_I2C_BUS_NUM);
#endif
	return 0;
}

