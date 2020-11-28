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

#define MIU0_RIU_ATOP                      0x110d
#define MIU1_RIU_ATOP                      0x1616
#define MIU0_RIU_DTOP                      0x1012
#define MIU1_RIU_DTOP                      0x1006

#define REG_ATOP_REGION                    0x2F
//#define DEBUG

typedef unsigned char   u8;
typedef unsigned int   u16;
typedef unsigned long  u32;

//-------------------------------------------------------------------------------------------------
//  Prototypes
//-------------------------------------------------------------------------------------------------
void BootRom_MiuTxDqs( void );
void putn( u8 n );
void putk( char c );
u8 MHal_MIU_ReadReg8( u32 u32bank, u32 u32reg );
void MHal_MIU_WritReg8( u32 u32bank, u32 u32reg, u8 u8val );
u16 MHal_MIU_ReadReg16( u32 u32bank, u32 u32reg );
void MHal_MIU_WritReg16( u32 u32bank, u32 u32reg, u16 u16val );
void MHal_MIU_Mask_Request( u8 u8Miu );
void MHal_MIU_Unmask_Request( u8 u8Miu );
u16 MHal_MIU_Bist( u8 u8Miu, u8 u8Region );
void MHal_MIU_Set_TxDqs( u8 u8Miu, u8 u8Region, u16 u16TxDqs );
void MHal_MIU_Set_Region( u8 u8Miu, u8 u8Region, u8 u8Val );
void MHal_MIU_Trans_DqsTbl( u8 u8Phase, u16 u16Val, u16 *u16DqsTbl );
void MHal_MIU_Get_MedianTbl( u16 *u16MedianTbl, u16* u16DqsTbl );
u8 MHal_MIU_Get_RegionTbl( u16 *u16RegionTbl, u16 *u16MedianTbl );
void MHal_MIU_Get_FinalDqsTbl( u16 *u16DqsTbl, u16* u16MedianTbl, u8 u8MinRegionVal );
void MHal_MIU_Set_Region_Dqs( u8 u8Miu, u8 u8Region, u16* u16DqsTbl, u8 u8MinRegionVal );
void BootRom_MiuTxAutoDqs( u8 u8Miu );

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

/*8-bit RIU address*/
u8 MHal_MIU_ReadReg8( u32 u32bank, u32 u32reg )
{
    u8 val;
    u32 address = MIU_RIU_REG_BASE + u32bank*0x100*2;
    address = address + (u32reg << 1) - (u32reg & 1);

    val = *( ( volatile u8* ) address );
    return val;
}

void MHal_MIU_WritReg8( u32 u32bank, u32 u32reg, u8 u8val )
{
    u32 address = MIU_RIU_REG_BASE + u32bank*0x100*2;
    address = address + (u32reg << 1) - (u32reg & 1);

    *( ( volatile u8* ) address ) = u8val;
}

u16 MHal_MIU_ReadReg16( u32 u32bank, u32 u32reg )
{
    u16 val;
    u32 address = MIU_RIU_REG_BASE + u32bank*0x100*2;
    address = address + (u32reg << 1);

    val = *( ( volatile u16* ) address );
    return val;
}

void MHal_MIU_WritReg16( u32 u32bank, u32 u32reg, u16 u16val )
{
    u32 address = MIU_RIU_REG_BASE + u32bank*0x100*2;
    address = address + (u32reg << 1);

    *( ( volatile u16* ) address ) = u16val;
}

void MHal_MIU_Mask_Request( u8 u8Miu )
{
    u16 u16Bank;

    if(u8Miu == 0)
        u16Bank = MIU0_RIU_DTOP;
    else
        u16Bank = MIU1_RIU_DTOP;

    MHal_MIU_WritReg16(u16Bank, 0x46, 0x7ffe);
    MHal_MIU_WritReg16(u16Bank, 0x66, 0xffff);
    MHal_MIU_WritReg16(u16Bank, 0x86, 0xffff);
    MHal_MIU_WritReg16(u16Bank, 0xa6, 0xffff);
}

void MHal_MIU_Unmask_Request( u8 u8Miu )
{
    u16 u16Bank;

    if(u8Miu == 0)
        u16Bank = MIU0_RIU_DTOP;
    else
        u16Bank = MIU1_RIU_DTOP;

    MHal_MIU_WritReg16(u16Bank, 0x46, 0x0000);
    MHal_MIU_WritReg16(u16Bank, 0x66, 0x0000);
    MHal_MIU_WritReg16(u16Bank, 0x86, 0x0000);
    MHal_MIU_WritReg16(u16Bank, 0xa6, 0x0000);
}

u16 MHal_MIU_Bist( u8 u8Miu, u8 u8Region )
{
    u16 val;

    if(u8Miu == 1)
        MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xf0, 0x8000);
    else
        MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xf0, 0x0000);

    if(u8Region == 0)
    {
        MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe6, 0xc000);
    }
    else
    {
        MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe6, 0x3000);
    }
    /*Set BIST length*/
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe4, 0x8001);

    /*Trigger BIST with mode 0x5*/
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe0, 0x0000);
    MHal_MIU_WritReg16(MIU0_RIU_DTOP, 0xe0, 0x0005);
    val = MHal_MIU_ReadReg16(MIU0_RIU_DTOP, 0xe0);

    /*Polling Bist done*/
    while(!(val & 0x8000))
    {
        val = MHal_MIU_ReadReg16(MIU0_RIU_DTOP, 0xe0);
    }
    
    val = MHal_MIU_ReadReg16(MIU0_RIU_DTOP, 0xee);

    return val;
}

void MHal_MIU_Set_TxDqs( u8 u8Miu, u8 u8Region, u16 u16TxDqs )
{
    u16 u16Bank;
    u16 u16Reg;

    if(u8Miu == 0)
        u16Bank = MIU0_RIU_ATOP;
    else
        u16Bank = MIU1_RIU_ATOP;

    if(u8Region == 0)
        u16Reg = 0x80;
    else
        u16Reg = 0x86;

    MHal_MIU_WritReg16(u16Bank, u16Reg, u16TxDqs);
    MHal_MIU_WritReg16(u16Bank, u16Reg+2, u16TxDqs);
    MHal_MIU_WritReg8(u16Bank, u16Reg+4, (u8)(u16TxDqs & 0x000F));
}

void MHal_MIU_Set_Region( u8 u8Miu, u8 u8Region, u8 u8Val )
{
    u16 u16Bank;
    u8  u8RegRegion;

    if(u8Miu == 0)
        u16Bank = MIU0_RIU_ATOP;
    else
        u16Bank = MIU1_RIU_ATOP;

    u8RegRegion = MHal_MIU_ReadReg8(u16Bank, 0x2F);
    
    if(u8Region == 0)
    {
        u8RegRegion = u8RegRegion & 0x0F;
        u8RegRegion = u8RegRegion | (u8Val << 4);
    }
    else
    {
        u8RegRegion = u8RegRegion & 0xF0;
        u8RegRegion = u8RegRegion | u8Val;
    }

    MHal_MIU_WritReg8(u16Bank, 0x2F, u8RegRegion);
}

void MHal_MIU_Trans_DqsTbl(u8 u8Phase, u16 u16Val, u16 *u16DqsTbl)
{
    u8  u8Dqs;
    
    for(u8Dqs = 0; u8Dqs < 16; u8Dqs++)
    {
        if(u16Val & (0x1 << u8Dqs))
        {
            u16DqsTbl[u8Dqs] = u16DqsTbl[u8Dqs] & ~(0x1 << u8Phase);
        }
        else
        {
            u16DqsTbl[u8Dqs] = u16DqsTbl[u8Dqs] | (0x1 << u8Phase);
        }
    }
}

void MHal_MIU_Get_MedianTbl(u16 *u16MedianTbl, u16* u16DqsTbl)
{
    u32 u32Sum;
    u32 u32Num;
    u8  u8Phase;
    u8  u8Dqs;
    u8  u8MinDqs;
    
    for(u8Dqs = 0; u8Dqs < 16; u8Dqs++)
    {
        u32Num = 0;
        u32Sum = 0;
        u8MinDqs = 0xFF;

        for(u8Phase = 0; u8Phase < 14; u8Phase++)
        {
            if(u16DqsTbl[u8Dqs] & (0x1 << u8Phase))
            {  
                u32Num ++ ;
                if(u8MinDqs > u8Phase)
                {
                    u8MinDqs = u8Phase;
                }
            }
        }
        u16MedianTbl[u8Dqs] = u8MinDqs + (u32Num / 2);
    }
}

u8 MHal_MIU_Get_RegionTbl(u16 *u16RegionTbl, u16 *u16MedianTbl)
{
    u8  u8Dqs;
    u8  u8MinRegionVal;
    
    for(u8Dqs = 0; u8Dqs < 16; u8Dqs++)
    {
        if(u16MedianTbl[u8Dqs] < 2)
        {
            u16RegionTbl[u8Dqs] = 0;
        }
        else
        {
            u16RegionTbl[u8Dqs] = (u16MedianTbl[u8Dqs] - 2) / 2;
        }
    }
    
    #ifdef DEBUG
    for(u8Dqs = 0; u8Dqs < 16; u8Dqs ++)
    {
        *(volatile unsigned int*)(0x1F200A00 + 4*u8Dqs) = u16RegionTbl[u8Dqs];
    }
    #endif
    
    u8MinRegionVal = 0xFF;

    for(u8Dqs = 0; u8Dqs < 16; u8Dqs ++)
    {
        if(u16RegionTbl[u8Dqs] < u8MinRegionVal)
        {
            u8MinRegionVal = u16RegionTbl[u8Dqs];
        }
    }

    return u8MinRegionVal;
}
    
void MHal_MIU_Get_FinalDqsTbl(u16 *u16DqsTbl, u16* u16MedianTbl, u8 u8MinRegionVal)
{
    u8  u8Dqs;
    u8  u16DqsVal;

    for(u8Dqs = 0; u8Dqs < 16; u8Dqs ++)
    {
        u16DqsVal =  u16MedianTbl[u8Dqs] - (u8MinRegionVal * 2);

        if(u16DqsVal > 3)
        {
            u16DqsTbl[u8Dqs] = 3;
        }
        else
        {
            u16DqsTbl[u8Dqs] = u16DqsVal;
        }
    }
    
    /*Set DQSM0 and DQSM1*/
    u16DqsTbl[16] = u16DqsTbl[7];
    u16DqsTbl[17] = u16DqsTbl[15];

    #ifdef DEBUG
    for(u8Dqs = 0; u8Dqs < 18; u8Dqs ++)
    {
        *(volatile unsigned int*)(0x1F206700 + 4*u8Dqs) = u16DqsTbl[u8Dqs];
    }
    #endif
}

void MHal_MIU_Set_Region_Dqs( u8 u8Miu, u8 u8Region, u16* u16DqsTbl, u8 u8MinRegionVal )
{
    u16 u16Bank;
    u16 u16RegDqs;
    u16 u16RegDqsVal;
    u8  u8RegRegion;

    if(u8Miu == 0)
    {
        u16Bank = MIU0_RIU_ATOP;
    }
    else
    {
        u16Bank = MIU1_RIU_ATOP;
    }
    
    u8RegRegion = MHal_MIU_ReadReg8(u16Bank, 0x2F);

    if(u8Region == 0)
    {
        u8RegRegion = u8RegRegion & 0x0F;
        u8RegRegion = u8RegRegion | (u8MinRegionVal << 4);
        u16RegDqs = 0x80;
    }
    else
    {
        u8RegRegion = u8RegRegion & 0xF0;
        u8RegRegion = u8RegRegion | u8MinRegionVal;
        u16RegDqs = 0x86;
    }
   
    /*Set Region Value*/
    MHal_MIU_WritReg8(u16Bank, 0x2F, u8RegRegion);
    
    /*Set reg_sel_mclk1x_skew_0_dq0 ~ reg_sel_mclk1x_skew_0_dq7*/
    u16RegDqsVal = 0;
    u16RegDqsVal = (u16RegDqsVal & 0xFFFC) | (u16DqsTbl[5]) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFFF3) | (u16DqsTbl[7] << 2) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFFCF) | (u16DqsTbl[1] << 4) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFF3F) | (u16DqsTbl[3] << 6) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFCFF) | (u16DqsTbl[16] << 8) ;
    u16RegDqsVal = (u16RegDqsVal & 0xF3FF) | (u16DqsTbl[10] << 10) ;
    u16RegDqsVal = (u16RegDqsVal & 0xCFFF) | (u16DqsTbl[14] << 12) ;
    u16RegDqsVal = (u16RegDqsVal & 0x3FFF) | (u16DqsTbl[8] << 14) ;
    MHal_MIU_WritReg16(u16Bank, u16RegDqs, u16RegDqsVal);
    
    /*Set reg_sel_mclk1x_skew_0_dq8 ~ reg_sel_mclk1x_skew_0_dq15*/
    u16RegDqsVal = 0;
    u16RegDqs = u16RegDqs + 2; 
    u16RegDqsVal = (u16RegDqsVal & 0xFFFC) | (u16DqsTbl[12]) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFFF3) | (u16DqsTbl[9] << 2) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFFCF) | (u16DqsTbl[15] << 4) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFF3F) | (u16DqsTbl[11] << 6) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFCFF) | (u16DqsTbl[13] << 8) ;
    u16RegDqsVal = (u16RegDqsVal & 0xF3FF) | (u16DqsTbl[17] << 10) ;
    u16RegDqsVal = (u16RegDqsVal & 0xCFFF) | (u16DqsTbl[0] << 12) ;
    u16RegDqsVal = (u16RegDqsVal & 0x3FFF) | (u16DqsTbl[2] << 14) ;
    MHal_MIU_WritReg16(u16Bank, u16RegDqs, u16RegDqsVal);
    
    /*Set reg_sel_mclk1x_skew_0_dq16 ~ reg_sel_mclk1x_skew_0_dq17*/
    u16RegDqsVal = 0;
    u16RegDqs = u16RegDqs + 2; 
    u16RegDqsVal = (u16RegDqsVal & 0xFFFC) | (u16DqsTbl[6]) ;
    u16RegDqsVal = (u16RegDqsVal & 0xFFF3) | (u16DqsTbl[4] << 2) ;
    MHal_MIU_WritReg8(u16Bank, u16RegDqs, u16RegDqsVal);
}

void BootRom_MiuTxAutoDqs( u8 u8Miu )
{
    u16 u16DqsTbl[18];
    u16 u16RegionTbl[16];
    u16 u16MedianTbl[16];
    u8  u8RegionVal;
    u8  u8Phase;
    u8  u8Dqs;
    u16 u16DqsVal;
    u16 u16Val;
    u8  u8MinRegionVal;
    u8  u8Region;
    
    /*Mask client request*/
    MHal_MIU_Mask_Request(u8Miu);

    for(u8Region = 0; u8Region < 2; u8Region++)
    {
        /*Reset u16BistRest here to prevent toolchain using memset*/
        for(u8Dqs = 0; u8Dqs < 16; u8Dqs++)
        {
            u16DqsTbl[u8Dqs] = 0;
        }
    
        for(u8Phase = 0; u8Phase < 14; u8Phase ++)
        {
            if(u8Phase < 2)
            {
                u8RegionVal = 0;
                u16DqsVal = ((u8Phase & 0x01) == 0)? 0x0000 : 0x5555;
            }
            else
            {
                u8RegionVal = (u8Phase - 2) / 2;
                u16DqsVal = ((u8Phase & 0x01) == 0)? 0xaaaa : 0xffff;
            }

            MHal_MIU_Set_Region(u8Miu, u8Region, u8RegionVal);
            MHal_MIU_Set_TxDqs(u8Miu, u8Region, u16DqsVal);
            u16Val = MHal_MIU_Bist(u8Miu, u8Region);
            #ifdef DEBUG
            *(volatile unsigned int*)(0x1F206700 + 4*u8Phase) = u16Val;
            #endif
            MHal_MIU_Trans_DqsTbl(u8Phase, u16Val, u16DqsTbl);
        }
        /*Get Median Dqs*/ 
        MHal_MIU_Get_MedianTbl(u16MedianTbl, u16DqsTbl);
        
        /*Get Minimun Region*/ 
        u8MinRegionVal = MHal_MIU_Get_RegionTbl(u16RegionTbl, u16MedianTbl);
        
        #ifdef DEBUG
        for(u8Phase = 0; u8Phase < 16; u8Phase ++)
        {
            *(volatile unsigned int*)(0x1F206740 + 4*u8Phase) = u16DqsTbl[u8Phase];
        }
        #endif
        
        #ifdef DEBUG
        for(u8Phase = 0; u8Phase < 16; u8Phase ++)
        {
            *(volatile unsigned int*)(0x1F206780 + 4*u8Phase) = u16MedianTbl[u8Phase];
        }
        #endif
        
 
        #ifdef DEBUG
        putk('M');
        putk('I');
        putk('U');
        putn(u8Miu);
        putk('_');
        putk('R');
        putk('e');
        putk('g');
        putk('i');
        putk('o');
        putk('n');
        putk(':');
        putn(u8MinRegionVal);
        putk('\n');
        putk('\r');
        #endif
       
        /*Get Final DQS value*/
        MHal_MIU_Get_FinalDqsTbl(u16DqsTbl, u16MedianTbl, u8MinRegionVal);
 
        /*Set Final DQS value and Region Value to RIU*/
        MHal_MIU_Set_Region_Dqs(u8Miu, u8Region, u16DqsTbl, u8MinRegionVal);
    } // end of for(u8Region = 0; u8Region < 2; u8Region++)
    
    /*Unmask client request*/
    MHal_MIU_Unmask_Request(u8Miu);
}
