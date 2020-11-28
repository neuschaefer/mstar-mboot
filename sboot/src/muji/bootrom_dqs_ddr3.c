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

    if(u8MiuDev == 0)
    {
        u16RegMiuArb = MIU0_RIU_ARB;
        u16RegMiuAtop = MIU0_RIU_ATOP;
    }
    else if(u8MiuDev == 1)
    {
        u16RegMiuArb = MIU1_RIU_ARB;
        u16RegMiuAtop = MIU1_RIU_ATOP;
    }
    else if(u8MiuDev == 2)
    {
        u16RegMiuArb = MIU2_RIU_ARB;
        u16RegMiuAtop = MIU2_RIU_ATOP;
    }
    else
    {
        return;
    }

    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xfe, 0x00e4);
    MHal_MIU_WritReg16(MIU1_RIU_DTOP, 0xf8, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe0, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe2, 0x0000);

    /* Set test length */
    MHal_MIU_WritReg16(MIU1_RIU_DTOP, 0xe6, 0x0000);

    /* Enable SI mode */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xd4, 0x11c1);
    
    /*Enable miu_test limit mask*/
    MHal_MIU_WritReg16(u16RegMiuArb, 0x1c, 0x8000);

    /* DPAT engine pre-setting */
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0004);
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x72, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0833);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x7c, 0x8000);

    /* STEP 1: Set RX DQS Phase = 1/2* Kcode + offset */
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x90, 0xf0f1);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0800);

    /* STEP 2 : Enable TX DQ deskew scan (by DPAT engine) */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe4, 0x0090);
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

    /* STEP 4 : Enable RX DQ/DQS deskew (by DPAT engine) */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe4, 0x2400);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_ARB, 0x78, 0x0000);
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
    
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0001);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa4, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa6, u16RegVal0);

    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0002);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xa8, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xaa, u16RegVal0);

    MHal_MIU_WritReg16(u16RegMiuAtop, 0xc0, 0x0003);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc2);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xac, u16RegVal0);
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuAtop, 0xc4);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0xae, u16RegVal0);
    
    /* STEP 6 : Disable DPAT engine & Set DQS Phase = 1/2* Kcode+offset (ratio mode) */
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x90, 0xf001);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x78, 0x0000);
    MHal_MIU_WritReg16(u16RegMiuArb, 0x74, 0x0830);
    MHal_MIU_WritReg16(u16RegMiuAtop, 0x70, 0x0800);
    
    MHal_MIU_WritReg16(u16RegMiuArb, 0x1c, 0x0000);

    /* Disable SI mode */
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xfe, 0x08e4);
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
