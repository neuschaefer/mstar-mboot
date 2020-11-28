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


//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <command.h>
#include <common.h>
#include <MsDebug.h>
#include <ShareType.h>
#include <CusUrsa8Init.h>
#include "MsCommon.h"
#include <MsSystem.h>
#include <MsVfs.h>
#if(ENABLE_URSA_8==1)
#include <drvMSPI.h>

//#include <drvBDMA.h>



//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define TFTP_TIMEOUT "100000"
//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#define WRITE_REG(_reg, _val)            WRITE_WORD(0x1f000000+(_reg*2),_val)
#define READ_REG(_reg)                   READ_WORD(0x1f000000+(_reg*2))
#define WRITE_BIT(_reg, _val, _bit)      WRITE_WORD(0x1f000000+(_reg*2),(((READ_REG(_reg))&~(BIT(_bit)))|(_val<<_bit)))

#define PIU_DelayUs //
MS_BOOL MDrv_SS_RIU_Write8(MS_U16 u16Addr, MS_U8 data)
{
    BOOLEAN bRet = true;
    MS_U8 Wdata[4];

    Wdata[0] = RIU_W1_CMD;
    Wdata[1] = u16Addr & 0xFF;
    Wdata[2] = (u16Addr >> 8) & 0xFF;
    Wdata[3] = data;
    //intf("MDrv_SS_RIU_Write8\n");

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);

    // send write address & data
    MDrv_MSPI_Write(Wdata,4);

    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;
}

MS_BOOL MDrv_SS_RIU_Write16(MS_U16 u16Addr, MS_U16 data)
{
    BOOLEAN bRet = true;
    MS_U8 Wdata[4];

    Wdata[0] = RIU_W1_CMD;
    Wdata[1] = u16Addr & 0xFF;
    Wdata[2] = (u16Addr >> 8) & 0xFF;
    Wdata[3] = data& 0xFF;
    //intf("MDrv_SS_RIU_Write16\n");

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);

    // send write address & data
    MDrv_MSPI_Write(Wdata,4);

    MDrv_MSPI_SlaveEnable(FALSE);

    Wdata[1] = (u16Addr & 0xFF) + 1;
    Wdata[2] = (u16Addr >> 8) & 0xFF;
    Wdata[3] = (data >> 8)& 0xFF;

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);

    // send write address & data
    MDrv_MSPI_Write(Wdata,4);

    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;
}


MS_BOOL MDrv_SS_RIU_Write8_Mask(MS_U16 u16Addr, MS_U8 data, MS_U8 mask)
{
    BOOLEAN bRet = true;
    MS_U8 Wdata[4], Rdata = 0;
    MDrv_SS_RIU_Read8(u16Addr, &Rdata);
    data=(Rdata & ~(mask)) | ((data) & (mask));

    Wdata[0] = RIU_W1_CMD;
    Wdata[1] = u16Addr & 0xFF;
    Wdata[2] = (u16Addr >> 8) & 0xFF;
    Wdata[3] = data;
    //intf("MDrv_SS_RIU_Write8_Mask\n");

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);

    // send write address & data
    MDrv_MSPI_Write(Wdata,4);

    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;
}


MS_BOOL MDrv_SS_RIU_Read8(MS_U16 u16Addr, MS_U8 *pdata)
{
    MS_BOOL bRet = true;
    MS_U8 Rdata[5];

    Rdata[0] = RIU_R1T_CMD;
    Rdata[1] = u16Addr & 0xFF;
    Rdata[2] = (u16Addr >> 8) & 0xFF;
    Rdata[3] = 0x00;
    //intf("MDrv_SS_RIU_Read8\n");

    MDrv_MSPI_SlaveEnable(TRUE);
    // send read command to read data
    MDrv_MSPI_Write(Rdata,4);
    // read operation
    //printf("Read Operation\n");
    MDrv_MSPI_Read(pdata, 1);
    MDrv_MSPI_SlaveEnable(FALSE);
    return bRet;
}
MS_BOOL MDrv_SS_RIU_Read16(MS_U16 u16Addr, MS_U8 *pdata)
{
    MS_BOOL bRet = true;
    MS_U8 Rdata[5];
    Rdata[0] = 0x11;
    Rdata[1] = u16Addr & 0xFF;
    Rdata[2] = (u16Addr >> 8) & 0xFF;
    Rdata[3] = 0x00;
    MDrv_MSPI_SlaveEnable(TRUE);
    MDrv_MSPI_Write(Rdata,4);
    MDrv_MSPI_Read(pdata, 2);
    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;

}
/*
MS_BOOL MDrv_SS_MIU_Writes(MS_U32 u32Addr, MS_U8 *pdata, MS_U16 u16Size)
{
    MS_BOOL bRet = true;
    MS_U8 Wdata[5];

    Wdata[0] = MIU_W_CMD;
    Wdata[1] = u32Addr & 0xFF;
    Wdata[2] = (u32Addr >> 8) & 0xFF;
    Wdata[3] = (u32Addr >> 16)& 0xFF;
    Wdata[4] = (u32Addr >> 24);
    printf("MDrv_SS_MIU_Writes\n");
    printf("u32Addr=0x%x,pdata=0x%x,u16Size=0x%x",(unsigned int)u32Addr,(unsigned int)pdata,(unsigned int)u16Size );
    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);
    // send write address
    MDrv_MSPI_Write(Wdata,sizeof(Wdata));
    // send data
    MDrv_MSPI_Write(pdata,u16Size);
    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;

}
*/
MS_BOOL MDrv_SS_MIU_Writes(MS_U32 u32Addr, MS_U8 *pdata, MS_U32 u32Size)
{
    MS_BOOL bRet = true;
    MS_U8 Wdata[5];

    Wdata[0] = MIU_W_CMD;
    Wdata[1] = u32Addr & 0xFF;
    Wdata[2] = (u32Addr >> 8) & 0xFF;
    Wdata[3] = (u32Addr >> 16)& 0xFF;
    Wdata[4] = (u32Addr >> 24);
    printf("MDrv_SS_MIU_Writes\n");

    // Write operation

    while(u32Size > 0xffff)
    {
        //printf("u32Addr=0x%x,pdata=0x%x,u16Size=0x%x\n",(unsigned int)u32Addr,(unsigned int)pdata,(unsigned int)u32Size );
        MDrv_MSPI_SlaveEnable(TRUE);
        MDrv_MSPI_Write(Wdata,sizeof(Wdata));
        // send data
        MDrv_MSPI_Write(pdata,0xffff);
        MDrv_MSPI_SlaveEnable(FALSE);
        u32Size = u32Size - 0xffff;
        u32Addr = u32Addr + 0xffff;
        Wdata[1] = u32Addr & 0xFF;
        Wdata[2] = (u32Addr >> 8) & 0xFF;
        Wdata[3] = (u32Addr >> 16)& 0xFF;
        Wdata[4] = (u32Addr >> 24);
        pdata = pdata + 0xffff;
    }
    MDrv_MSPI_SlaveEnable(TRUE);
    // send write address
    MDrv_MSPI_Write(Wdata,sizeof(Wdata));
    // send data
    MDrv_MSPI_Write(pdata,u32Size);
    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;

}


MS_BOOL MDrv_SS_MIU_Reads(MS_U32 u32Addr, MS_U8 *pdata, MS_U16 u16Size)
{
    MS_BOOL bRet = true;
    MS_U8 Rdata[SPI_DEVICE_BUFFER_SIZE];
    MS_U16 dataLen, i, j=0;

    do
    {
        dataLen = (u16Size>16?16:u16Size);//(len>24?24:len);

        Rdata[0] = MIU_R_CMD;
        Rdata[1] = u32Addr & 0xFF;
        Rdata[2] = (u32Addr >> 8) & 0xFF;
        Rdata[3] = (u32Addr >> 16)& 0xFF;
        Rdata[4] = (u32Addr >> 24);
        Rdata[5] = dataLen+1;
        //printf("MDrv_SS_MIU_Reads, addr=0x%lx, dataLen=%d\n", u32Addr, dataLen);

        // send read command to read data
        MDrv_MSPI_SlaveEnable(TRUE);
        MDrv_MSPI_Write(Rdata,6);
        MDrv_MSPI_SlaveEnable(FALSE);

        // read operation
        Rdata[0] = MIU_ST_CMD;
        MDrv_MSPI_SlaveEnable(TRUE);
        MDrv_MSPI_Write(Rdata,1);
        printf("Read Operation\n");
        MDrv_MSPI_Read(Rdata, dataLen+1);
        MDrv_MSPI_SlaveEnable(FALSE);

        if(Rdata[0] != 0x0A)
        {
            printf("MDrv_SS_MIU_Reads fail, status=0x%x\n", Rdata[0] );
            return false;
        }

        for (i=1; i<dataLen+1; i++, j++)
        {
            pdata[j] = Rdata[i];
            printf("%x, ", pdata[j]);
            if(i%16 == 0)
                printf("\n");
        }

        u16Size -= dataLen;
        u32Addr += dataLen;
        printf("u16Size=%d,  u32Addr=0x%lx\n", u16Size, u32Addr);
    }while(u16Size);

    return bRet;
}

void InitialSystemPowerUp( void )
{
    // MPLL: From Victo
    MDrv_SS_RIU_Write8( 0x1e80, 0x7b );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1e81, 0x00 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1ec0, 0x00 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1ec1, 0x02 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1ec2, 0x00 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1ec3, 0x00 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1e88, 0x85 );
    MDrv_SS_RIU_Write8( 0x1e89, 0x00 );
    MDrv_SS_RIU_Write8( 0x1e8a, 0x00 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1e8b, 0x00 );//enable mpll , power down active low
    MDrv_SS_RIU_Write8( 0x1e86, 0x02 );//set mpll
    MDrv_SS_RIU_Write8( 0x1e87, 0x1b );//set mpll

    //==========================//
    //            LPLL          //
    //==========================//
    MDrv_SS_RIU_Write8(0x2A1E,0xD8);
    MDrv_SS_RIU_Write8(0x2A1F,0x54);
    MDrv_SS_RIU_Write8(0x2A20,0x1A);
    MDrv_SS_RIU_Write8(0x2A21,0x00);
    MDrv_SS_RIU_Write8(0x2A2A,0x00);
    MDrv_SS_RIU_Write8(0x2A2B,0x00);
    MDrv_SS_RIU_Write8(0x2A02,0x03);
    MDrv_SS_RIU_Write8(0x2A03,0x02);
    MDrv_SS_RIU_Write8(0x2A04,0x00);
    MDrv_SS_RIU_Write8(0x2A05,0x07);
    MDrv_SS_RIU_Write8(0x2A06,0x0E);
    MDrv_SS_RIU_Write8(0x2A07,0x00);
    MDrv_SS_RIU_Write8(0x2A08,0x00);
    MDrv_SS_RIU_Write8(0x2A09,0x00);
    MDrv_SS_RIU_Write8(0x2A5C,0xB0);
    MDrv_SS_RIU_Write8(0x2A5D,0x07);
    MDrv_SS_RIU_Write8(0x2A60,0x00);
    MDrv_SS_RIU_Write8(0x2A61,0x00);
    MDrv_SS_RIU_Write8(0x2A62,0x00);
    MDrv_SS_RIU_Write8(0x2A63,0x00);
    MDrv_SS_RIU_Write8(0x2A64,0x00);
    MDrv_SS_RIU_Write8(0x2A65,0x00);
    MDrv_SS_RIU_Write8(0x2A66,0x29);
    MDrv_SS_RIU_Write8(0x2A67,0x00);
    MDrv_SS_RIU_Write8(0x2A68,0x00);
    MDrv_SS_RIU_Write8(0x2A69,0x00);
    MDrv_SS_RIU_Write8(0x2A6A,0x00);
    MDrv_SS_RIU_Write8(0x2A6B,0x1F);
    MDrv_SS_RIU_Write8(0x2A6C,0x00);
    MDrv_SS_RIU_Write8(0x2A6D,0x00);
    MDrv_SS_RIU_Write8(0x2A6E,0x00);
    MDrv_SS_RIU_Write8(0x2A6F,0x00);
    MDrv_SS_RIU_Write8(0x2A72,0x00);
    MDrv_SS_RIU_Write8(0x2A73,0x00);
    MDrv_SS_RIU_Write8(0x2A74,0x00);
    MDrv_SS_RIU_Write8(0x2A75,0x00);
    MDrv_SS_RIU_Write8(0x2AC0,0x30);
    MDrv_SS_RIU_Write8(0x2AC1,0x00);
    MDrv_SS_RIU_Write8(0x2AC2,0x00);
    MDrv_SS_RIU_Write8(0x2AC3,0x00);
    MDrv_SS_RIU_Write8(0x2AC4,0x00);
    MDrv_SS_RIU_Write8(0x2AC5,0x00);
    MDrv_SS_RIU_Write8(0x2AC6,0x00);
    MDrv_SS_RIU_Write8(0x2AC7,0x00);
    MDrv_SS_RIU_Write8(0x2AC8,0x00);
    MDrv_SS_RIU_Write8(0x2AC9,0x00);
    MDrv_SS_RIU_Write8(0x2ACA,0x00);
    MDrv_SS_RIU_Write8(0x2ACB,0x00);
    MDrv_SS_RIU_Write8(0x2ACC,0x00);
    MDrv_SS_RIU_Write8(0x2ACD,0x00);
    MDrv_SS_RIU_Write8(0x2AE2,0x00);
    MDrv_SS_RIU_Write8(0x2AE3,0x00);

    // all pad in
    //MDrv_Write2Byte(0x1E9A, 0x0000 ); //[0]reg_allpad_in
    MDrv_SS_RIU_Write8_Mask( 0x1E9A, 1, BIT0 );//[0]reg_allpad_in

    //
    //open all clock
    //wriu -w 0x1E0

    MDrv_SS_RIU_Write16(0x1E04, 0x000C); //[15:12]ckg_mod_sr_rclk_pre
                            //[11:8]ckg_pwm[10]=0:xtali, 1:xtali_div2
                            //[4:0]ckg_miu bit[4:2]=0:mempll, 1:173MHz, 2:272MHz, 3:216MHz, 4:300MHz


    MDrv_SS_RIU_Write16(0x1E06, 0x7020); //[14:12]ckg_bist
                            //
                            //
                            //
                            //[5]sw_mcu_clk
                            //[4:0]ckg_mcu bit[4:2]=0:216MHz, 3:108MHz, 4:54MHz, 5:173MHz, 7:xtali


    MDrv_SS_RIU_Write16(0x1E08, 0x0038 ); // Set r2 clk=288M
                            //[15:12]ckg_ficlk2, bit[3:2]=0:fclk, 1:iclk
                            //[11:8]ckg_ficlk, bit[3:2]=0:fclk, 1:iclk
                            //[5]sw_r2_clk
                            //[4:0]ckg_r2, bit[4:2]=0:216MHz, 1:0MHz, 2:0MHz, 3:108MHz, 4:54MHz, 5:173MHz, 6:300MHz, 7:xtali

    MDrv_SS_RIU_Write16( 0x1E0A, 0x1004 ); //[14]ckg_fclk_mlb
                            //[13:8]ckg_fclk, bit[4:2]=0:0MHz, 1:0MHz, 2:0MHz, 3:0MHz, 4:odclk_div2, 5:173Mhz, 6:216Mhz, 7:xtali
                            //[6:4]ckg_odclk_ld, bit[2]=0:odclk
                            //[3:0]

    MDrv_SS_RIU_Write16( 0x1E0C, 0x1022 ); //[12]ckg_mpll, 0:216MHz, 1:432MHz
                            //[11:8]ckg_vby1, bit[3:2]=0:0MHz, 1:vby1_fifo, 2:0Mhz, 3:0MHz
                            //[7:4]
                            //[3:0]

    MDrv_SS_RIU_Write16( 0x1E0E, 0x0000 ); //[15:12]
                            //[11:8]ckg_misc, bit[3:2]=0:lpll2misc, 1:0MHz, 2:idclk, 3:idclk2; bit[2]=0:lpll2misc=lpll_buf, 1:lpll2misc=lpll_buf_div2
                            //[7:6]ckg_op2_sram, bit[7]=0:odclk, 1:mclk
                            //[4:0]ckg_odclk, bit[3:2]=0:lpll2odclkMhz, 1:0MHz, 2:idclk, 3:idclk2; bit[4]=0:lpll2odclk=odclk, 1:lpll2odclk=odclk_div2

    MDrv_SS_RIU_Write16( 0x1E10, 0x0400 ); //[15:12]ckg_mod_sr_wclk, bit[3:2]=0:clk_misc_p, 1:mod_sr_wclk_buf
                            //[11:8]
                            //[5:0]debug_sel
    MDrv_SS_RIU_Write16( 0x1E12, 0x0000 ); //[15:12]ckg_hsc, bit[3:2]=0:86MHz, 1:43.2Mhz, 2:xtali, 3:0MHz
    MDrv_SS_RIU_Write16( 0x1E28, 0x0180 ); //[15:13]ckg_fclk_opm, bit[2]=0:clk_fclk, 1:clk_fclk_t3d
                            //[12:11]ckg_ire
                            //[10:5]ckg_fclk_t3d, bit[4:2]=0:0MHz, 1:0MHz, 2:mclk, 3:350MHz, 4:lpll_buf, 5:173Mhz, 6:216MHz, 7:xtali
                            //[4:0]
    MDrv_SS_RIU_Write16( 0x1E8E, 0x0000 ); //[13:8]ckg_sspi2, bit[4:2]=0:216MHz, 1:0MHz, 2:0MHz, 3:108MHz, 4:54MHz, 5:173MHz, 6:0MHz, 7:xtali
    MDrv_SS_RIU_Write16( 0x1E92, 0x0400 ); //[12:8]ckg_sys_in, bit[3:2]=0:ckgbl, 1:ckgblx2, 2:ckgbl_osd, 3:0MHz
    MDrv_SS_RIU_Write16( 0x1E94, 0x0100 ); //[11:8]ckg_100mhz_bist
                            //[7:4]ckg_40mhz_i2c
                            //[3:0]ckg_fix_10k
    MDrv_SS_RIU_Write16( 0x1E96, 0x0000 ); //[15:12]ckg_ck_pad
    MDrv_SS_RIU_Write16( 0x1E98, 0x3838 ); //[15:14]ckg_t3d_sram
                            //[13:8]ckg_spi_s, bit[5]=1, bit[4:2]=110:86MHz
                            //[5:0]ckg_spi_m, bit[5]=1, bit[4:2]=110:86MHz
    MDrv_SS_RIU_Write16( 0x1EA6, 0x0000 ); //[7:6]ckg_od_sram4
                            //[5:4]ckg_od_sram3
                            //[3:2]ckg_od_sram2
                            //[1:0]ckg_od_sram1
    MDrv_SS_RIU_Write16( 0x1EA8, 0x0000 ); //[3:0]ckg_mod_sr_rclk
    MDrv_SS_RIU_Write16( 0x1EAA, 0x0000 ); //[7:4]ckg_mod_sr_rclk_bypass
                            //[3:0]ckg_mod_sr_wclk_bypass


    MDrv_SS_RIU_Write16( 0x1EB2, 0x0000 ); //[7:4] reg_ckg_inport2;
                                       //[12:8] reg_ckg_sys_in2;
                                       //Ukulele[Todo] Transfer from script

}

void MDrv_Macaw12_MiuInitial(void)
{
    MS_U32  dwUrsaChipId = 0;
    MS_U32  dwUrsaRevisionId = 0;

    //-------------------------------------------------------------------
    // initialize MIU
    //-------------------------------------------------------------------
    MDrv_SS_RIU_Write16(0x00121e, 0x0c00);
    MDrv_SS_RIU_Write16(0x00121e, 0x0c00);
    MDrv_SS_RIU_Write16(0x00121e, 0x0c00);
    MDrv_SS_RIU_Write16(0x00121e, 0x0c01);
    MDrv_SS_RIU_Write16(0x00121e, 0x0c00);
    MDrv_SS_RIU_Write16(0x001202, 0x0000);
    MDrv_SS_RIU_Write16(0x001246, 0xfffe);
    MDrv_SS_RIU_Write16(0x001266, 0xffff);
    MDrv_SS_RIU_Write16(0x001286, 0xffff);
    MDrv_SS_RIU_Write16(0x0012a6, 0xffff);

    MDrv_SS_RIU_Write16(0x001336, 0x0000);
    MDrv_SS_RIU_Write16(0x001334, 0x0200);
    MDrv_SS_RIU_Write16(0x001330, 0xf5b9);
    MDrv_SS_RIU_Write16(0x001332, 0x0029);
    MDrv_SS_RIU_Write16(0x001324, 0x1000);
    MDrv_SS_RIU_Write16(0x0013a4, 0x1000);
    MDrv_SS_RIU_Write16(0x001324, 0x0000);
    MDrv_SS_RIU_Write16(0x0013a4, 0x0000);
    udelay(1000);   //wait 1    // delay 1ms

    MDrv_SS_RIU_Read16(0x001e3a, (MS_U8 *) &dwUrsaChipId);
    dwUrsaChipId &= 0xff;

    MDrv_SS_RIU_Read16(0x001e3c, (MS_U8 *) &dwUrsaRevisionId);
    dwUrsaRevisionId = ((dwUrsaRevisionId >> 8) & 0xff);

    if((dwUrsaChipId == 0x73) && (dwUrsaRevisionId == 0))
    {
        //MIU 4x Mode
        printf("[INFO] Load Ukulele 4x Mode DRAM Settings\n");

        MDrv_SS_RIU_Write16(0x001202, 0x0292);
        MDrv_SS_RIU_Write16(0x001204, 0x000d);  //rd_timing            b       : [4:0]
        MDrv_SS_RIU_Write16(0x001206, 0x2428);
        MDrv_SS_RIU_Write16(0x001208, 0x1faa);
        MDrv_SS_RIU_Write16(0x00120a, 0x2866);
        MDrv_SS_RIU_Write16(0x00120c, 0x8598);
        MDrv_SS_RIU_Write16(0x00120e, 0x2047);
        MDrv_SS_RIU_Write16(0x001210, 0x0002);
        MDrv_SS_RIU_Write16(0x001212, 0x4004);  //{[9], [6], [2]} = 010
        MDrv_SS_RIU_Write16(0x001214, 0x8000);
        MDrv_SS_RIU_Write16(0x001216, 0xc000);

        MDrv_SS_RIU_Write16(0x001354, 0x0000);
        MDrv_SS_RIU_Write16(0x001300, 0x041a);
        MDrv_SS_RIU_Write16(0x001304, 0x0000);  //reg_dqs_pre_state : [7:0]
        MDrv_SS_RIU_Write16(0x001338, 0x0055);  //reg_clkph_dq0         3       : [3:0]
                                                //reg_clkph_dq1         3       : [7:4]
                                                //reg_clkph_dqs0        0       : [11:8]
                                                //reg_clkph_dqs1        0       : [15:12]
        MDrv_SS_RIU_Write16(0x00133a, 0x0440);  //reg_clkph_cmd         0       : [3:0]
                                                //reg_clkph_dqsm0       0       : [7:4]
                                                //reg_clkph_clk_a       0       : [11:8]
                                                //reg_clkph_dqsm1       0       : [15:12]
        MDrv_SS_RIU_Write16(0x001302, 0x0000);  //reg_cko_state         00      : [7:0]
                                                //reg_dqs_state         00      : [15:8]
        MDrv_SS_RIU_Write16(0x00133c, 0x0022);  //reg_dqsm0_skew 0 [2:0]
                                                //reg_dqsm1_skew 0 [6:4]
                                                //reg_dqs_skew   2 [10:8]
                                                //reg_cmd1_skew  0 [14:12]
        MDrv_SS_RIU_Write16(0x00133e, 0x0000);  //[2:0] reg_oen_skew
                                                //[6:4]  reg_dq_skew
                                                //[10:8] reg_cmd_skew
                                                //[14:12]    reg_cko_skew
        MDrv_SS_RIU_Write16(0x00130e, 0x00ed);  //[3:1] reg_dqsm_dly
        MDrv_SS_RIU_Write16(0x00130e, 0x00ad);
        MDrv_SS_RIU_Write16(0x00136e, 0x0056);  //reg_dll0_ph   : [3:0]
                                                //reg_dll1_ph    : [7:4]

        MDrv_SS_RIU_Write16(0x00136a, 0x00c2);
        MDrv_SS_RIU_Write16(0x001368, 0x00c2);
        MDrv_SS_RIU_Write16(0x001354, 0x0000);  //reg_cmd_mode_sel    [15:14] 00:default mode 01:2cmd mode 10:2cmd mode 11:2cmd mode(cs)
        MDrv_SS_RIU_Write16(0x00121e, 0x0c01);  //miu software reset
        MDrv_SS_RIU_Write16(0x00121e, 0x0c00);

        MDrv_SS_RIU_Write16(0x00137c, 0x0280);  //reg_sel_vref       : [15:8]
        MDrv_SS_RIU_Write16(0x00137e, 0x0000);  //reg_sel_zq         : [15:0]
        MDrv_SS_RIU_Write16(0x001300, 0x041a);
        udelay(1000);//wait 1

        MDrv_SS_RIU_Write16(0x001300, 0x0412);
        MDrv_SS_RIU_Write16(0x001300, 0x0402);  //reg_odt0_en           0       : [10]
                                                //reg_odt1_en           1       : [11]

        MDrv_SS_RIU_Write16(0x001302, 0xaaaa);
        MDrv_SS_RIU_Write16(0x001308, 0x00ff);

        MDrv_SS_RIU_Write16(0x001374, 0x0022);  //trig lvl
        MDrv_SS_RIU_Write16(0x00135c, 0xaaaa);  //drvn
        MDrv_SS_RIU_Write16(0x00135e, 0xaaaa);  //drvp

        //$display($time," start to program DLL0 ");
        MDrv_SS_RIU_Write16(0x001360, 0x000c);
        MDrv_SS_RIU_Write16(0x001360, 0x0008);
        MDrv_SS_RIU_Write16(0x001362, 0x007f);
        MDrv_SS_RIU_Write16(0x001364, 0xf200);
        MDrv_SS_RIU_Write16(0x001360, 0x2738);

        //Pack setting
//      MDrv_SS_RIU_Write16(0x001228, 0x4000); //pack off

        //Reduce latency setting
        MDrv_SS_RIU_Write16(0x00122a, 0x0000);

        //test sync fifo stage
        MDrv_SS_RIU_Write16(0x0012fc, 0x4400);

        MDrv_SS_RIU_Write16(0x001200, 0x0000);
        MDrv_SS_RIU_Write16(0x001200, 0x0008);
        MDrv_SS_RIU_Write16(0x001200, 0x000c);
        udelay(1000);   //wait 1 //delay 1ms

        MDrv_SS_RIU_Write16(0x001200, 0x000e);
        udelay(1000);   //wait 1 //delay 1ms

        MDrv_SS_RIU_Write16(0x001200, 0x001f);  //turn off dram odt [4]
        udelay(10000);  //wait 10 //check reg_101200 #15 for wait initial done

        //analog de glitch
        MDrv_SS_RIU_Write16(0x001246, 0x7FFE);
        MDrv_SS_RIU_Write16(0x00121e, 0x0c08);
        MDrv_SS_RIU_Write16(0x0012e0, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e2, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e4, 0x0001);
        MDrv_SS_RIU_Write16(0x0012e6, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e8, 0x5aa5);
        MDrv_SS_RIU_Write16(0x00130e, 0x00ed); //1 bit6
        MDrv_SS_RIU_Write16(0x0012e0, 0x0200);
        MDrv_SS_RIU_Write16(0x0012e0, 0x0201);
        MDrv_SS_RIU_Write16(0x0012e8, 0xffff);
        MDrv_SS_RIU_Write16(0x0012e8, 0xffff);
        MDrv_SS_RIU_Write16(0x00130e, 0x00ad); //0 bit6
        udelay(1000);//wait 1
    }
    else
    {
        //MIU 8x Mode
        printf("[INFO] Load Ukulele 8x Mode DRAM Settings\n");

        MDrv_SS_RIU_Write16(0x001202, 0x0392);
        MDrv_SS_RIU_Write16(0x001204, 0x000a);  //rd_timing            b       : [4:0]
        MDrv_SS_RIU_Write16(0x001206, 0x2428);
        MDrv_SS_RIU_Write16(0x001208, 0x1faa);
        MDrv_SS_RIU_Write16(0x00120a, 0x2877);
        MDrv_SS_RIU_Write16(0x00120c, 0x85a8);
        MDrv_SS_RIU_Write16(0x00120e, 0x206a);
        MDrv_SS_RIU_Write16(0x001210, 0x0003);
        MDrv_SS_RIU_Write16(0x001212, 0x4004);  //{[9], [6], [2]} = 010
        MDrv_SS_RIU_Write16(0x001214, 0x8000);
        MDrv_SS_RIU_Write16(0x001216, 0xc000);
        MDrv_SS_RIU_Write16(0x001354, 0x0000);
        MDrv_SS_RIU_Write16(0x001300, 0x041a);
        MDrv_SS_RIU_Write16(0x001304, 0x0000);  //reg_dqs_pre_state : [7:0]
        MDrv_SS_RIU_Write16(0x001338, 0x0055);  //reg_clkph_dq0         3       : [3:0]
                                                //reg_clkph_dq1         3       : [7:4]
                                                //reg_clkph_dqs0        0       : [11:8]
                                                //reg_clkph_dqs1        0       : [15:12]
        MDrv_SS_RIU_Write16(0x00133a, 0x0221);  //reg_clkph_cmd         0       : [3:0]
                                                //reg_clkph_dqsm0       0       : [7:4]
                                                //reg_clkph_clk_a       0       : [11:8]
                                                //reg_clkph_dqsm1       0       : [15:12]
        MDrv_SS_RIU_Write16(0x001302, 0x0000);  //reg_cko_state         00      : [7:0]
                                                //reg_dqs_state         00      : [15:8]
        MDrv_SS_RIU_Write16(0x00133c, 0x0022);  //reg_dqsm0_skew 0 [2:0]
                                                //reg_dqsm1_skew 0 [6:4]
                                                //reg_dqs_skew   2 [10:8]
                                                //reg_cmd1_skew  0 [14:12]
        MDrv_SS_RIU_Write16(0x00133e, 0x0000);  //[2:0] reg_oen_skew
                                                //[6:4]  reg_dq_skew
                                                //[10:8] reg_cmd_skew
                                                //[14:12]    reg_cko_skew
        MDrv_SS_RIU_Write16(0x00130e, 0x00e5);  //[3:1] reg_dqsm_dly
        MDrv_SS_RIU_Write16(0x00130e, 0x00a5);
        MDrv_SS_RIU_Write16(0x00136e, 0x0056);  //reg_dll0_ph   : [3:0]
                                                //reg_dll1_ph    : [7:4]

        MDrv_SS_RIU_Write16(0x00136a, 0x00c2);
        MDrv_SS_RIU_Write16(0x001368, 0x00c2);
        MDrv_SS_RIU_Write16(0x001354, 0x0000);  //reg_cmd_mode_sel    [15:14] 00:default mode 01:2cmd mode 10:2cmd mode 11:2cmd mode(cs)
        MDrv_SS_RIU_Write16(0x00121e, 0x0c01);  //miu software reset
        MDrv_SS_RIU_Write16(0x00121e, 0x0c00);

        MDrv_SS_RIU_Write16(0x00137c, 0x0280);  //reg_sel_vref       : [15:8]
        MDrv_SS_RIU_Write16(0x00137e, 0x0000);  //reg_sel_zq         : [15:0]
        MDrv_SS_RIU_Write16(0x001300, 0x041a);
        udelay(1000);//wait 1

        MDrv_SS_RIU_Write16(0x001300, 0x0412);
        MDrv_SS_RIU_Write16(0x001300, 0x0402);  //reg_odt0_en           0       : [10]
                                                //reg_odt1_en           1       : [11]

        MDrv_SS_RIU_Write16(0x001302, 0xaaaa);
        MDrv_SS_RIU_Write16(0x001308, 0x00ff);

        MDrv_SS_RIU_Write16(0x001374, 0x0022);  //trig lvl
        MDrv_SS_RIU_Write16(0x00135c, 0xaaaa);  //drvn
        MDrv_SS_RIU_Write16(0x00135e, 0xaaaa);  //drvp

        //$display($time," start to program DLL0 ");
        MDrv_SS_RIU_Write16(0x001360, 0x000c);
        MDrv_SS_RIU_Write16(0x001360, 0x0008);
        MDrv_SS_RIU_Write16(0x001362, 0x007f);
        MDrv_SS_RIU_Write16(0x001364, 0xf200);
        MDrv_SS_RIU_Write16(0x001360, 0x2738);

        //Pack setting
//      MDrv_SS_RIU_Write16(0x001228, 0x4000); //pack off

        //Reduce latency setting
        MDrv_SS_RIU_Write16(0x00122a, 0x0000);

        //test sync fifo stage
        MDrv_SS_RIU_Write16(0x0012fc, 0x4400);

        MDrv_SS_RIU_Write16(0x001200, 0x0000);
        MDrv_SS_RIU_Write16(0x001200, 0x0008);
        MDrv_SS_RIU_Write16(0x001200, 0x000c);
        udelay(1000);   //wait 1 //delay 1ms

        MDrv_SS_RIU_Write16( 0x001200, 0x000e);
        udelay(1000);   //wait 1 //delay 1ms

        MDrv_SS_RIU_Write16( 0x001200, 0x001f); //turn off dram odt [4]
        udelay(10000);  //wait 10 //check reg_101200 #15 for wait initial done

        //analog de glitch
        MDrv_SS_RIU_Write16(0x001246, 0x7FFE);
        MDrv_SS_RIU_Write16(0x00121e, 0x0c08);
        MDrv_SS_RIU_Write16(0x0012e0, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e2, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e4, 0x0001);
        MDrv_SS_RIU_Write16(0x0012e6, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e8, 0x5aa5);
        MDrv_SS_RIU_Write16(0x00130e, 0x00e5);  //1 bit6
        MDrv_SS_RIU_Write16(0x0012e0, 0x0200);
        MDrv_SS_RIU_Write16(0x0012e0, 0x0201);
        MDrv_SS_RIU_Write16(0x0012e8, 0xffff);
        MDrv_SS_RIU_Write16(0x0012e8, 0xffff);
        MDrv_SS_RIU_Write16(0x00130e, 0x00a5);  //0 bit6
        udelay(1000);   //wait 1
    }

    //BW setting
    MDrv_SS_RIU_Write16(0x001240, 0x8001);
    MDrv_SS_RIU_Write16(0x001260, 0x8001);
    MDrv_SS_RIU_Write16(0x001280, 0x8001);
    MDrv_SS_RIU_Write16(0x0012a0, 0x8001);

    //unmask all
    MDrv_SS_RIU_Write16(0x00121a, 0x0001);  //turn on report counter
    MDrv_SS_RIU_Write16(0x001246, 0x0000);  //unmask group0
    if((dwUrsaChipId == 0x73) && (dwUrsaRevisionId > 0))
    {
        MDrv_SS_RIU_Write16(0x001266, 0x0000);  //unmask group1
        MDrv_SS_RIU_Write16(0x001286, 0x0000);  //unmask group2
        MDrv_SS_RIU_Write16(0x0012a6, 0x0000);  //unmask group3
    }

    MDrv_SS_RIU_Write16(0x00121e, 0x0c08);  //threshold, release ff mask(bit3) (enable sw init done)

#if 0
    // ===== miu self test =====
//  MDrv_SS_RIU_Write16(0x0012fe, 0x0200);  //reg_address_inverse   1 : [9]
    MDrv_SS_RIU_Write16(0x0012e0, 0x0000);  //reg_test_en           0 : [0]
    MDrv_SS_RIU_Write16(0x0012e2, 0x0000);  //base
    MDrv_SS_RIU_Write16(0x0012e4, 0x0021);  //length
    MDrv_SS_RIU_Write16(0x0012e6, 0x0000);  //length
    MDrv_SS_RIU_Write16(0x0012e8, 0x5aa5);  //test data
//  MDrv_SS_RIU_Write16(0x0012d8, 0x0000);  //reg_address_test_sel    : [2:0]   0:1 1:32 2:64 3:128 4:256 5:512 6:1024 7:2056
    MDrv_SS_RIU_Write16(0x0012e0, 0x0001);  //reg_test_en           1 : [0]
//  MDrv_SS_RIU_Write16(0x00125a, 0x0000);  //turn on adc reg_adc_test_en
#endif
}

void MDrv_MIU_SimpleBist(void)
{
    MS_U8   pRdata[2];
    MS_U32  dwBistRetryCounter = 0;

    printf("Ukulele MIU BIST: ");

    // ===== miu self test =====
//  MDrv_SS_RIU_Write16(0x0012fe, 0x0200);  //reg_address_inverse   1 : [9]
    MDrv_SS_RIU_Write16(0x0012e0, 0x0000);  //reg_test_en           0 : [0]
    MDrv_SS_RIU_Write16(0x0012e2, 0x0000);  //base
    MDrv_SS_RIU_Write16(0x0012e4, 0x0021);  //length
    MDrv_SS_RIU_Write16(0x0012e6, 0x0000);  //length
    MDrv_SS_RIU_Write16(0x0012e8, 0x5aa5);  //test data
//  MDrv_SS_RIU_Write16(0x0012d8, 0x0000);  //reg_address_test_sel    : [2:0]   0:1 1:32 2:64 3:128 4:256 5:512 6:1024 7:2056

    while(1)
    {
        //Trigger bist
        MDrv_SS_RIU_Write16(0x0012e0, 0x0000);
        MDrv_SS_RIU_Write16(0x0012e0, 0x0001);   //reg_test_en           1 : [0]

        //Wait done
        MDrv_SS_RIU_Read16(0x0012e0, pRdata);

        while(!(pRdata[1] & BIT7))
        {
            MDrv_SS_RIU_Read16(0x0012e0, pRdata);
        }

        if(pRdata[1] & BIT6)                // Failed
        {
            dwBistRetryCounter ++;
            if(dwBistRetryCounter >= 10)
            {
                printf("Fail\n");
                while(1);
            }
        }
        else
        {
            printf("OK\n");
            break;
        }

        udelay(10);    // delay 1ms
    }

    MDrv_SS_RIU_Write16(0x0012e0, 0x0000);
}

int do_cusUrsa8Init( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_U32  dwUrsaChipId = 0;
    MS_U32  dwUrsaRevisionId = 0;

    char    *PathBuf;
    U32     ukuleleSize = 0;
    U32     APsize = 0;
    MS_U8   pBinFileStartAddr[3];
    U32 u32_BinGroup_Start_Address=0;

    WRITE_BIT(0x101eb4, 1, 2);  //ld_spi3_config
    WRITE_BIT(0x000ee8, 0, 2);  //Enable Ukulele XTAL Clock
    udelay(1000);
    WRITE_BIT(0x101e58, 0, 6);  //Release Reset of Ukulele

    //disable WDT
    MDrv_SS_RIU_Write16(0x003c60, 0xaa55);

    InitialSystemPowerUp();
    MDrv_Macaw12_MiuInitial();
    MDrv_MIU_SimpleBist();

    MDrv_SS_RIU_Write8(0x00123c, 0x40); //switch from adc to mspi


    vfs_mount(UINSIDE);

    PathBuf = getenv("ursa_bin_name");
    if(PathBuf == NULL)
    {
        printf("Can't find ursa bin\n");
        return -1;
    }

    ukuleleSize = vfs_getsize(PathBuf);
    if(vfs_read((void *)(PA2NVA(Dram_Addr)), PathBuf, 0, ukuleleSize) == -1)
    {
        printf("vfs_read fail\n");
        return -1;
    }

    memcpy(pBinFileStartAddr,(MS_U8*) UKULELE_BIN_FILE_ADDR_IN_NIKE_MIU, sizeof(MS_U8) * 3);
    APsize = (pBinFileStartAddr[2] << 16) + (pBinFileStartAddr[1] << 8) + pBinFileStartAddr[0];
    u32_BinGroup_Start_Address = *((U32 *)(UKULELE_BIN_GROUP_ADDR_IN_NIKE_MIU));
    if(u32_BinGroup_Start_Address==0)
    {
        u32_BinGroup_Start_Address=UKULELE_BIN_START_ADDR;
    }
    UBOOT_DEBUG("ursa_bin_group_addr set to [0x%x] \n",u32_BinGroup_Start_Address);

    if(ukuleleSize <= APsize)
    {
        MDrv_SS_MIU_Writes(UKULELE_AP_START_ADDR, (MS_U8 *) PA2NVA(Dram_Addr+HEADER_LEN), ukuleleSize - HEADER_LEN); //load AP file
    }
    else
    {
        MDrv_SS_MIU_Writes(UKULELE_AP_START_ADDR, (MS_U8 *) PA2NVA(Dram_Addr+HEADER_LEN), APsize - HEADER_LEN); //load AP file
        MDrv_SS_MIU_Writes(u32_BinGroup_Start_Address, (MS_U8 *) PA2NVA(Dram_Addr+APsize), ukuleleSize - APsize); //load bin file
    }

    MDrv_SS_RIU_Read16(0x001e3a, (MS_U8 *) &dwUrsaChipId);
    dwUrsaChipId &= 0xff;
    MDrv_SS_RIU_Read16(0x001e3c, (MS_U8 *) &dwUrsaRevisionId);
    dwUrsaRevisionId = ((dwUrsaRevisionId >> 8) & 0xff);

    if((dwUrsaChipId == 0x73) && (dwUrsaRevisionId == 0))
    {
        MDrv_SS_RIU_Write8(0x00125F, 0x10);     //data mask for miu group 4 wd // dev0 (sspi + hsc client)
        MDrv_SS_RIU_Write16(0x001246, 0x0000);  //unmask group0
        MDrv_SS_RIU_Write16(0x001266, 0x0000);  //unmask group1
        MDrv_SS_RIU_Write16(0x001286, 0x0000);  //unmask group2
        MDrv_SS_RIU_Write16(0x0012a6, 0x0000);  //unmask group3
    }

    MDrv_SS_RIU_Write8(0x000fb4, 0x01); //cpu_reset_base
    MDrv_SS_RIU_Write8(0x000f80, 0x24);
    MDrv_SS_RIU_Write8(0x000f80, 0x27);

    UBOOT_TRACE("OK\n");

    return 0;
}

#endif
