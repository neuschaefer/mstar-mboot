////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Define
//-------------------------------------------------------------------------------------------------
#define MIU_RIU_REG_BASE                   0x1F000000

#define MIU0_RIU_DTOP                      0x1012
#define MIU1_RIU_DTOP                      0x1006
#define MIU2_RIU_DTOP                      0x1620
#define MIU0_RIU_ARB                       0x1615
#define MIU1_RIU_ARB                       0x1622
#define MIU2_RIU_ARB                       0x1623
#define MIU0_RIU_ATOP                      0x110d
#define MIU1_RIU_ATOP                      0x1616
#define MIU2_RIU_ATOP                      0x1621

//#define DEBUG
#define MIU_ENABLE_AUTO_WRITE_PHASE
#define MIU_ENABLE_AUTO_READ_PHASE

typedef unsigned char   u8;
typedef unsigned int   u16;
typedef unsigned long  u32;

#define MHal_MIU_ReadReg16(u32bank, u32reg ) *( ( volatile u16* ) (MIU_RIU_REG_BASE + (u32bank)*0x100*2 + ((u32reg) << 1)) )
#define MHal_MIU_WritReg16(u32bank, u32reg, u16val ) *( ( volatile u16* ) (MIU_RIU_REG_BASE + (u32bank)*0x100*2 + ((u32reg) << 1))  ) = (u16val)

//-------------------------------------------------------------------------------------------------
//  Prototypes
//-------------------------------------------------------------------------------------------------
void putn( u8 n );
void putk( char c );
void delayus(u32 us);
void BootRom_MiuDdr3Dqs(u8 u8MiuDev);
void setPowerSaving(void);
void setMiuXPowerSaving(u16 u16RegMiuAtop);

//-------------------------------------------------------------------------------------------------
//  Local variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Functions
//-------------------------------------------------------------------------------------------------
void putn(u8 n)
{
    char c = '0' + n;
          
   *(volatile unsigned int*)(0x1F201300) = c;
}

void putk(char c)
{
   *(volatile unsigned int*)(0x1F201300) = c;
}

void delayus(u32 us)
{
    u16 u16RegVal0;

    u16RegVal0 = ((us* 12) & 0xffff);
    MHal_MIU_WritReg16(0x30, 0x24, u16RegVal0);
    
    u16RegVal0 = ((us* 12) >> 16);
    MHal_MIU_WritReg16(0x30, 0x26, u16RegVal0);
    
    u16RegVal0 = 0x0002;
    MHal_MIU_WritReg16(0x30, 0x20, u16RegVal0);
    
    do{
        u16RegVal0 = MHal_MIU_ReadReg16(0x30, 0x22);
    }while((u16RegVal0 & 0x0001) == 0);
}

void BootRom_MiuDdr3Dqs(u8 u8MiuDev)
{
    u16 u16RegVal0;
    u16 u16RegVal1;
    u16 u16RegMiuArb;
    u16 u16RegMiuAtop;
    u16 u16RegMiuDtop;
    u16 u16DQSMaxCenter[4];
    u16 u16KCode;
    u16 u16KCodeOffset[4];
    u8 i = 0;

    if(u8MiuDev == 0)
    {
        u16RegMiuArb = MIU0_RIU_ARB;
        u16RegMiuAtop = MIU0_RIU_ATOP;
        u16RegMiuDtop = MIU0_RIU_DTOP;;
    }
    else if(u8MiuDev == 1)
    {
        u16RegMiuArb = MIU1_RIU_ARB;
        u16RegMiuAtop = MIU1_RIU_ATOP;
        u16RegMiuDtop = MIU1_RIU_DTOP;;
    }
    else if(u8MiuDev == 2)
    {
        u16RegMiuArb = MIU2_RIU_ARB;
        u16RegMiuAtop = MIU2_RIU_ATOP;
        u16RegMiuDtop = MIU2_RIU_DTOP;;
    }
    else
    {
        return;
    }
    
    /* unmask MIU0_group_4 bit15 */
    MHal_MIU_WritReg16(u16RegMiuArb, 0x06, 0x7FFF);
    
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xfe, 0x00e4);
    MHal_MIU_WritReg16(MIU1_RIU_DTOP, 0xf8, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe0, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe2, 0x0000);

    /* Set test length */
    MHal_MIU_WritReg16(MIU1_RIU_DTOP, 0xe6, 0x0000);

    /* Enable SI mode */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c1);
    
    /*Enable miu_test limit mask*/
    //MHal_MIU_WritReg16(u16RegMiuArb, 0x1c, 0x8000);
    
    /*Enable group4 member limit (24)*/
    MHal_MIU_WritReg16(u16RegMiuArb, 0x02, 0x2006);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x00, 0x8015);


    /* DPAT engine pre-setting */
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0004);
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x72, 0x0000);
    //MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0833);
    //MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0b63);
	MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0d83);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x7c, 0x8000);

    /* STEP 1: Set RX DQS Phase = 1/2* Kcode + offset */
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x90, 0xf0f1);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0800);

#ifndef MIU_ENABLE_AUTO_WRITE_PHASE
    MHal_MIU_WritReg16(u16RegMiuArb, 0x76, 0x0002);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x78, 0x0013);

    do{
        u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuArb, 0x78);
    }while((u16RegVal0 & 0x8000) == 0);
#endif

#ifdef MIU_ENABLE_AUTO_WRITE_PHASE
    /* STEP 2 : Enable TX DQ deskew scan (by DPAT engine) */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe4, 0x0090);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c0);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c1);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc8, 0xffff);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xca, 0xffff);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xcc, 0x00ff);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x76, 0x0002);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x78, 0x0013);
    
    do{
        u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuArb, 0x78);
    }while((u16RegVal0 & 0x8000) == 0);
    
    /* STEP 3 : Read TX DQ deskew result & write to REGs */
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0004);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xd0, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xd2, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc6);
    u16RegVal1 = 0x0000 | (u16RegVal0 & 0x00ff);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xd8, u16RegVal1);
    u16RegVal1 = 0x0000 | (u16RegVal0 >> 8);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xe8, u16RegVal1);
    
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0005);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xd4, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xd6, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc6);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x2e, u16RegVal0);

    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0006);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xe0, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xe2, u16RegVal0);

    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0007);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xe4, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xe6, u16RegVal0);
#endif

#ifdef MIU_ENABLE_AUTO_READ_PHASE
    /* STEP 4 : Enable RX DQ/DQS deskew (by DPAT engine) */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe4, 0x2400);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c0);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c1);

    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x78, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0004);
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x90, 0x00f0);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x40, 0xffff);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x42, 0xffff);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x44, 0x000f);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0800);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x76, 0x0001);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x78, 0x0013);

    do{
        u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuArb, 0x78);
    }while((u16RegVal0 & 0x8000) == 0);

    /* STEP 5 : Read RX DQ deskew result & write to REGs */
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0000);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa0, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa2, u16RegVal0);
    u16DQSMaxCenter[0] = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc6);
    u16DQSMaxCenter[0] = u16DQSMaxCenter[0] & 0x007F;
    
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0001);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa4, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa6, u16RegVal0);
    u16DQSMaxCenter[1] = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc6);
    u16DQSMaxCenter[1] = u16DQSMaxCenter[1] & 0x007F;

    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0002);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa8, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xaa, u16RegVal0);
    u16DQSMaxCenter[2] = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc6);
    u16DQSMaxCenter[2] = u16DQSMaxCenter[2] & 0x007F;

    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0003);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xac, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xae, u16RegVal0);
    u16DQSMaxCenter[3] = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc6);
    u16DQSMaxCenter[3] = u16DQSMaxCenter[3] & 0x007F;
   
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x60, 0x33c8);
    u16KCode = MHal_MIU_ReadReg16(u16RegMiuAtop, 0x66);
    u16KCode = ((u16KCode & 0x007F) >> 1);
    
    for(i= 0; i < 4; i++)
    {
        if(u16DQSMaxCenter[i] > u16KCode)
        {
            u16KCodeOffset[i] = u16DQSMaxCenter[i] - u16KCode;
        }
        else
        {
            u16KCodeOffset[i] = u16KCode - u16DQSMaxCenter[i];
            u16KCodeOffset[i] = u16KCodeOffset[i] | 0x0010;
        }
    }
    u16RegVal0 = (u16KCodeOffset[1] << 8) | u16KCodeOffset[0];
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x94, u16RegVal0);
    u16RegVal0 = (u16KCodeOffset[3] << 8) | u16KCodeOffset[2];
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x96, u16RegVal0);
#endif

    /* STEP 6 : Disable DPAT engine & Set DQS Phase = 1/2* Kcode+offset (ratio mode) */
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x90, 0xf0f1);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x78, 0x0000);
    //MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0830);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0b60);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0800);
    
    MHal_MIU_WritReg16(u16RegMiuArb, 0x1c, 0x0000);

    /* Disable SI mode */
    //MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xfe, 0x08e4);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c0);

    putk('M');
    putk('I');
    putk('U');
    putn(u8MiuDev);
    putk('_');
    putk('D');
    putk('Q');
    putk('S');
    putk('-');
    putk('O');
    putk('K');
    putk('\n');
    putk('\r');
}

void setMiuXPowerSaving(u16 u16RegMiuAtop)
{
    u16 u16RegVal;
    u16 u16Data;

    // low word, low byte
    u16Data = 0x3F;
    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xD0);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //d0[3:0] = DQ0
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //d0[7:4] = DQ1
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //d0[11:8] = DQ2
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //d0[15:12] = DQ3

    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xD2);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //d2[3:0] = DQ4
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //d2[7:4] = DQ5
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //d2[11:8] = DQ6
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //d2[15:12] = DQ7
    
    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xD8);    
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //d8[3:0] = DQM0
    
    u16RegVal = (MHal_MIU_ReadReg16(u16RegMiuAtop, 0xFE) & (~0x3F00))|(u16Data << 8);  //fe[13 : 8]
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xFE, u16RegVal);

    //low word, high byte
    u16Data = 0x3F;
    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xD4);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //d4[3:0] = DQ8
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //d4[7:4] = DQ9
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //d4[11:8] = DQ10
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //d4[15:12] = DQ11

    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xD6);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //d6[3:0] = DQ12
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //d6[7:4] = DQ13
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //d6[11:8] = DQ14
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //d6[15:12] = DQ15

    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xD8);    
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //d8[7:4] = DQM1
    
    u16RegVal = (MHal_MIU_ReadReg16(u16RegMiuAtop, 0xFE) & (~0x3F))|(u16Data);  //fe[5 : 0]
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xFE, u16RegVal);

    //high word, low byte
    u16Data = 0x3F;
    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xE0);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //e0[3:0] = DQ16
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //e0[7:4] = DQ17
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //e0[11:8] = DQ18
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //e0[15:12] = DQ19

    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xE2);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //e2[3:0] = DQ20
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //e2[7:4] = DQ21
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //e2[11:8] = DQ22
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //e2[15:12] = DQ23
    
    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xE8);    
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //e8[3:0] = DQM2
    
    u16RegVal = (MHal_MIU_ReadReg16(u16RegMiuAtop, 0xFC) & (~0x3F00))|(u16Data << 8);  //fc[13 : 8]
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xFC, u16RegVal);

    //high word, high byte
    u16Data = 0x3F;
    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xE4);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //e4[3:0] = DQ24
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //e4[7:4] = DQ25
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //e4[11:8] = DQ26
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //e4[15:12] = DQ27

    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xE6);
    u16Data &= ~(1<<((u16RegVal) & 0xF));           //e6[3:0] = DQ28
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //e6[7:4] = DQ29
    u16Data &= ~(1<<((u16RegVal >> 8) & 0xF));      //e6[11:8] = DQ30
    u16Data &= ~(1<<((u16RegVal >> 12) & 0xF));     //e6[15:12] = DQ31

    u16RegVal = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xE8);    
    u16Data &= ~(1<<((u16RegVal >> 4) & 0xF));      //e8[7:4] = DQM3
    
    u16RegVal = (MHal_MIU_ReadReg16(u16RegMiuAtop, 0xFC) & (~0x3F))|(u16Data);  //fc[5 : 0]
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xFC, u16RegVal);
}

void setPowerSaving(void)
{
    //
    // MIU0, 0x110D
    //
    setMiuXPowerSaving (MIU0_RIU_ATOP);

    //
    // MIU1, 0x1616
    //
    setMiuXPowerSaving (MIU1_RIU_ATOP);

    //
    // MIU2, 0x1621
    //
    setMiuXPowerSaving (MIU2_RIU_ATOP);
}
