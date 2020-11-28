/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _HAL_SPINAND_H_
#include "halSPINAND.h"
#include "drvSPICMD.h"
#include "cache.h"
#endif
#define udelay(TimerCount, WaitComplete)    hw_timer_delay(TimerCount)

static U32 hw_timer_delay(U32 u32usTick)
{
    U32 u32HWTimer = 0;
	volatile U16 u16TimerLow = 0;
	volatile U16 u16TimerHigh = 0;

	// reset HW timer
	REG_WRITE_UINT16(TIMER0_MAX_LOW, 0xFFFF);
	REG_WRITE_UINT16(TIMER0_MAX_HIGH, 0xFFFF);
	REG_WRITE_UINT16(TIMER0_ENABLE, 0);

	// start HW timer
	REG_SET_BITS_UINT16(TIMER0_ENABLE, 0x0001);

	while( u32HWTimer < 12*u32usTick ) // wait for u32usTick micro seconds
	{
		REG_READ_UINT16(TIMER0_CAP_LOW, u16TimerLow);
		REG_READ_UINT16(TIMER0_CAP_HIGH, u16TimerHigh);

		u32HWTimer = (u16TimerHigh<<16) | u16TimerLow;
	}

	REG_WRITE_UINT16(TIMER0_ENABLE, 0);

    return u32usTick+1;
}

static BOOL _HAL_WriteByte(U32 u32RegAddr, U8 u8Val)
{
    ((unsigned char  volatile *) CONFIG_RIU_BASE_ADDRESS + (FSP_BASE_ADDR << 1))[(u32RegAddr << 1) - (u32RegAddr & 1)] = u8Val;
    return TRUE;
}
static BOOL _HAL_Write2Byte(U32 u32RegAddr, U16 u16Val)
{
    RIU[FSP_BASE_ADDR + u32RegAddr] = u16Val;
    return TRUE;
}

#if 0
static BOOL _HAL_MBX_Write2Byte(U32 u32RegAddr, U16 u16Val)
{
    RIU[MBX_BASE_ADDR + u32RegAddr] = u16Val;
    return TRUE;
}

static U16 _HAL_MBX_WriteByte(U32 u32RegAddr, U8 u8Val)
{
    ((unsigned char  volatile *) CONFIG_RIU_BASE_ADDRESS + (MBX_BASE_ADDR << 1))[(u32RegAddr << 1) - (u32RegAddr & 1)] =  u8Val;
    return TRUE;
}
#endif
static U16 _HAL_Read2Byte(U32 u32RegAddr)
{
    return RIU[FSP_BASE_ADDR + (u32RegAddr)];
}

static U8 _HAL_ReadByte(U32 u32RegAddr)
{
    return((unsigned char  volatile *) CONFIG_RIU_BASE_ADDRESS + (FSP_BASE_ADDR << 1))[(u32RegAddr << 1) - (u32RegAddr & 1)];
}

static BOOL _HAL_BDMA_Write2Byte(U32 u32RegAddr, U16 u16Val)
{

     *(unsigned short  volatile *)(0xBF201200 + (u32RegAddr << 2)) = u16Val;
     return TRUE;
}
#if 0
static U16 _HAL_QSPI_Read2Byte(U32 u32RegAddr)
{
    return RIU[QSPI_BASE_ADDR + (u32RegAddr << 1)];
}
#endif
static U16 _HAL_QSPI_Write2Byte(U32 u32RegAddr, U16 u16Val)
{
    RIU[QSPI_BASE_ADDR + (u32RegAddr << 1)] = u16Val;
    return TRUE;
}

static U16 _HAL_CHIP_Read2Byte(U32 u32RegAddr)
{
    return RIU[CHIP_BASE_ADDR + (u32RegAddr << 1)];
}

static U16 _HAL_CHIP_Write2Byte(U32 u32RegAddr, U16 u16Val)
{
    RIU[CHIP_BASE_ADDR + (u32RegAddr << 1)] = u16Val;
    return TRUE;
}

static BOOL _HAL_FSP_ChkWaitDone(void)
{
//consider as it spend very long time to check if FSP done, so it may implment timeout method to improve
    U16 u16Try = 0;
    U8 u8DoneFlag = 0;

    while (u16Try < CHK_NUM_WAITDONE)
    {
        u8DoneFlag = _HAL_Read2Byte(REG_FSP_DONE);
        if((u8DoneFlag & DONE_FSP) == DONE_FSP)
        {
            return TRUE;
        }
        u16Try++;
    }
    return FALSE;
}

static void _HAL_FSP_GetRData(U8 *pu8Data, U8 u8DataSize)
{
    U8 u8Index = 0;

    for (u8Index = 0; u8Index < u8DataSize; u8Index++)
    {
        pu8Data[u8Index] = _HAL_ReadByte((REG_FSP_READ_BUFF + u8Index));
    }
}


static U8 HAL_FSP_CHECK_SPINAND_DONE(void)
{
    U8 pu8Data = 1;
    U16 u16Try = 0;
    while((pu8Data & 1) && (u16Try < CHK_NUM_WAITDONE))
    {
        //FSP init config
        udelay(10,1);
        _HAL_Write2Byte(REG_FSP_CTRL, (ENABLE_FSP|RESET_FSP|INT_FSP));
        _HAL_Write2Byte(REG_FSP_CTRL2, 0);
        _HAL_Write2Byte(REG_FSP_CTRL4, 0);
        _HAL_WriteByte(REG_FSP_WRITE_BUFF, SPI_NAND_CMD_GF);
        _HAL_WriteByte(REG_FSP_WRITE_BUFF + 1, SPI_NAND_REG_STAT);
        _HAL_Write2Byte(REG_FSP_WRITE_SIZE, 0x2);
        _HAL_Write2Byte(REG_FSP_READ_SIZE, 0x1);
        //Trigger FSP
        _HAL_Write2Byte(REG_FSP_TRIGGER, TRIGGER_FSP);

        //Check FSP done flag
        if (_HAL_FSP_ChkWaitDone() == FALSE)
        {
            return FALSE;
        }

        //Clear FSP done flag
        _HAL_Write2Byte(REG_FSP_CLEAR_DONE, CLEAR_DONE_FSP);
        u16Try++;
        _HAL_FSP_GetRData(&pu8Data, 1);
    }
    return pu8Data;
}

static BOOL _HAL_SPINAND_RIU_READ(U16 u16Addr, U32 u32DataSize, U8 *u8pData)
{
    U32 u32Index = 0;
    U8  u8Addr = 0;
    U32 u32RealLength = 0;
    U8  u8WbufIndex = 0;
    S8  s8Index = 0;

    //FSP init config
    _HAL_Write2Byte(REG_FSP_CTRL, (ENABLE_FSP|RESET_FSP|INT_FSP));
    _HAL_Write2Byte(REG_FSP_CTRL2, 0);
    _HAL_Write2Byte(REG_FSP_CTRL4, 0);

    //Set FSP Read Command
    _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex), SPI_NAND_CMD_RFC);
    u8WbufIndex++;

    //Set Write & Read Length
    _HAL_Write2Byte(REG_FSP_WRITE_SIZE, 4); //add 4 because it is included of command and Address setting length
    if(u32DataSize > MAX_READ_BUF_CNT)
        _HAL_Write2Byte(REG_FSP_READ_SIZE, MAX_READ_BUF_CNT);
    else
        _HAL_Write2Byte(REG_FSP_READ_SIZE, u32DataSize);

    for(u32Index = 0; u32Index < u32DataSize; u32Index +=MAX_READ_BUF_CNT)
    {
        for(s8Index = (SPI_NAND_PAGE_ADDR_LEN - 1); s8Index >= 0 ; s8Index--)
        {
            u8Addr = (u16Addr >> (8 * s8Index) )& 0xFF;
            _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex),u8Addr);
            u8WbufIndex++;


        }
        // set dummy byte
        _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex),0x00);
        //Trigger FSP
        _HAL_WriteByte(REG_FSP_TRIGGER, TRIGGER_FSP);

        //Check FSP done flag
        if (_HAL_FSP_ChkWaitDone() == FALSE){
            return FALSE;
        }
        //Get Read Data
        u32RealLength = u32DataSize - u32Index;
        if(u32RealLength >= MAX_READ_BUF_CNT)
            u32RealLength = MAX_READ_BUF_CNT;
        _HAL_FSP_GetRData((u8pData + u32Index), u32RealLength);

        //Clear FSP done flag
        _HAL_WriteByte(REG_FSP_CLEAR_DONE, CLEAR_DONE_FSP);
        // update Read Start Address
        u16Addr += u32RealLength;
        u8WbufIndex -= SPI_NAND_PAGE_ADDR_LEN;

    }
    return TRUE;

}

static BOOL _HAL_SPINAND_BDMA_READ(U32 u32Addr, U32 u32DataSize, U8 *u8pData)
{
    U32 u32Addr1;
    BOOL bRet = FALSE;

    //Set source and destination path
    _HAL_BDMA_Write2Byte(0x00, 0x0000);
    _HAL_BDMA_Write2Byte(0x02, 0x4045);

    // Set source address
    *(unsigned short  volatile *)(0xBF201210) = (u32Addr & 0xFFFF);
    *(unsigned short  volatile *)(0xBF201214) = (u32Addr >> 16);
    #if defined(CONFIG_MCU_MIPS32)
    flush_cache((U32)u8pData, u32DataSize);
    u32Addr1 = ((U32)u8pData & 0x1fffffff);
    #else
    u32Addr1 = (U32)u8pData;
    #endif 
    // Set destination  address
    *(unsigned short  volatile *)(0xBF201218) = (U16)(u32Addr1 & 0x0000FFFF);
    *(unsigned short  volatile *)(0xBF20121C) = (U16)(u32Addr1 >> 16);
    // Set Size
    *(unsigned short  volatile *)(0xBF201220) = (U16)(u32DataSize & 0xFFFF);
    *(unsigned short  volatile *)(0xBF201224) = (U16)(u32DataSize >> 16);

    // Trigger
    *(unsigned short  volatile *)(0xBF201200) = 1;

    do
    {
        //check done
        if(*(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x100902 << 1)) & 0x08)
        {
            //clear done
            *(unsigned char volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x100902 << 1)) = 0x08;
            bRet = TRUE;
            break;
        }
    } while (1);

    return bRet;

}

BOOL HAL_SPINAND_Init(void)
{
    U16 u16Data;
    //set pad mux for spinand
    _HAL_CHIP_Write2Byte(0x04, 0x13);
    _HAL_QSPI_Write2Byte(0x7A, 0x01);

    u16Data = _HAL_CHIP_Read2Byte(0x27);
    u16Data &= 0xFFFE;
    _HAL_CHIP_Write2Byte(0x27, u16Data);

    // reset spinand
    //FSP init config
    _HAL_Write2Byte(REG_FSP_CTRL, (ENABLE_FSP|RESET_FSP|INT_FSP));
    _HAL_Write2Byte(REG_FSP_CTRL2, 0);
    _HAL_Write2Byte(REG_FSP_CTRL4, 0);

    //Set FSP Read Command
    _HAL_Write2Byte(REG_FSP_WRITE_BUFF, SPI_NAND_CMD_RESET);

    _HAL_Write2Byte(REG_FSP_WRITE_SIZE, 1);
    _HAL_Write2Byte(REG_FSP_READ_SIZE, 0);

    //Trigger FSP
    _HAL_Write2Byte(REG_FSP_TRIGGER, TRIGGER_FSP);

    //Check FSP done flag
    if (_HAL_FSP_ChkWaitDone() == FALSE)
    {
        return FALSE;
    }

    //Clear FSP done flag
    _HAL_QSPI_Write2Byte(REG_SPI_CS_SET, REG_SPI_CS_HIGH);
    _HAL_Write2Byte(REG_FSP_CLEAR_DONE, CLEAR_DONE_FSP);

    udelay(SPI_RESET_DELAY,1);
    _HAL_QSPI_Write2Byte(REG_SPI_CS_SET, REG_SPI_CS_LOW);
    return TRUE;
}

BOOL HAL_SPINAND_PLANE_HANDLER(U32 u32Addr)
{
    U8 u8i = 0;

    while(!((BLOCK_SIZE >> u8i)&1))
    {
        u8i++;
    }
    if(u32Addr & BLOCK_SIZE)
    {
        u32Addr = u32Addr & BLOCK_SIZE;
        u32Addr = u32Addr >> u8i;
        u32Addr = u32Addr << REG_SPI_WRAP_BIT_OFFSET;
       *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (QSPI_BASE_ADDR << 1) + (REG_SPI_WRAP_VAL << 2)) = u32Addr;
    }
    else
    {
       u32Addr =  *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (QSPI_BASE_ADDR << 1) + (REG_SPI_WRAP_VAL << 2));
       u32Addr &= ~(REG_SPI_WRAP_BIT_MASK << REG_SPI_WRAP_BIT_OFFSET);
       *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (QSPI_BASE_ADDR << 1) + (REG_SPI_WRAP_VAL << 2)) = u32Addr;
    }
    return TRUE;

}


U32 HAL_SPINAND_RFC(U32 u32Addr, U8 *pu8Data)
{
    U8  u8Addr = 0;
    U8  u8WbufIndex = 0;
    S8  s8Index;

    //FSP init config
    _HAL_Write2Byte(REG_FSP_CTRL, (ENABLE_FSP|RESET_FSP|INT_FSP|ENABLE_THR_CMD|ENABLE_SEC_CMD));
    _HAL_Write2Byte(REG_FSP_CTRL2, 0);
    _HAL_Write2Byte(REG_FSP_CTRL4, 0);

    //Set FSP Read Command
    // FIRSET COMMAND PRELOAD
    _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex), SPI_NAND_CMD_WREN);
    u8WbufIndex++;

    //SECOND COMMAND READ COMMAND + 3BYTE ADDRESS
    _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex), SPI_NAND_CMD_PGRD);
    u8WbufIndex++;
    //seet Read Start Address
    for(s8Index = (SPI_NAND_ADDR_LEN - 1); s8Index >= 0 ; s8Index--)
    {
        u8Addr = (u32Addr >> (8 * s8Index) )& 0xFF;
        _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex),u8Addr);
        u8WbufIndex++;
    }
    //THIRD COMMAND GET FATURE CHECK CAHCHE READY
    _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex), SPI_NAND_CMD_GF);
    u8WbufIndex++;
    _HAL_WriteByte((REG_FSP_WRITE_BUFF + u8WbufIndex), SPI_NAND_REG_STAT);
    u8WbufIndex++;

    _HAL_Write2Byte(REG_FSP_WRITE_SIZE, 0x241);

    _HAL_Write2Byte(REG_FSP_READ_SIZE,  0x100);

    //Trigger FSP
    _HAL_WriteByte(REG_FSP_TRIGGER, TRIGGER_FSP);

    //Check FSP done flag
    if (_HAL_FSP_ChkWaitDone() == FALSE)
    {
        return FALSE;
    }
    //Clear FSP done flag
    _HAL_WriteByte(REG_FSP_CLEAR_DONE, CLEAR_DONE_FSP);

    *pu8Data = HAL_FSP_CHECK_SPINAND_DONE();

    return TRUE;
}

U32 HAL_SPINAND_Read (U32 u32Addr, U32 u32DataSize, U8 *pu8Data)
{
    if(RIU_FLAG)
    {
       _HAL_SPINAND_RIU_READ(u32Addr, u32DataSize, pu8Data);
    }
    else
    {
        // config SPI waveform for BDMA
        *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (QSPI_BASE_ADDR << 1) + (REG_SPI_FUNC_SET << 2)) = (REG_SPI_ADDR2_EN|REG_SPI_DUMMY_EN|REG_SPI_WRAP_EN);
        //Set dummy cycle
        *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (QSPI_BASE_ADDR << 1) + (REG_SPI_CKG_SPI << 2)) = (REG_SPI_USER_DUMMY_EN|REG_SPI_DUMMY_CYC_SINGAL);

        _HAL_SPINAND_BDMA_READ(u32Addr, u32DataSize, pu8Data);

    }

    return 1;
}

U8 HAL_SPINAND_ReadID(U32 u32DataSize, U8 *pu8Data)
{
    U16 u16Index =0;
    U32 u32RealLength = 0;

    //FSP init config
    _HAL_Write2Byte(REG_FSP_CTRL, (ENABLE_FSP|RESET_FSP|INT_FSP));
    _HAL_Write2Byte(REG_FSP_CTRL2, 0);
    _HAL_Write2Byte(REG_FSP_CTRL4, 0);

    //Set FSP Read Command
    _HAL_Write2Byte(REG_FSP_WRITE_BUFF, SPI_NAND_CMD_RDID);
    //Set read id index
    _HAL_Write2Byte(REG_FSP_WRITE_BUFF + 1, 0x00);
    _HAL_Write2Byte(REG_FSP_WRITE_SIZE, 2);

    //Set Write & Read Length
    for(u16Index = 0;u16Index < u32DataSize;u16Index += u32RealLength)
    {
        if(u32DataSize > (MAX_READ_BUF_CNT))
        {
            _HAL_Write2Byte(REG_FSP_READ_SIZE, MAX_READ_BUF_CNT);
            u32RealLength = MAX_READ_BUF_CNT;
        }
        else
        {
            _HAL_Write2Byte(REG_FSP_READ_SIZE, u32DataSize);
            u32RealLength = u32DataSize;
        }

        //Trigger FSP
        _HAL_Write2Byte(REG_FSP_TRIGGER, TRIGGER_FSP);

        //Check FSP done flag
        if (_HAL_FSP_ChkWaitDone() == FALSE)
        {
            return FALSE;
        }

        //Get Read Data
        _HAL_FSP_GetRData((pu8Data + u16Index), u32RealLength);
        //Clear FSP done flag
        _HAL_Write2Byte(REG_FSP_CLEAR_DONE, CLEAR_DONE_FSP);

    }
    u16Index |= ((*pu8Data << 8) | *(pu8Data + 1));

    return 1;

}

void HAL_SPINAND_SetReadMode(BOOL bRIUFlag)
{
    RIU_FLAG = bRIUFlag;
}

void HAL_SPINAND_CSCONFIG(void)
{
    U16 u16Data;
    u16Data = _HAL_CHIP_Read2Byte(0x1F);
    u16Data |= 0x0100;
    _HAL_CHIP_Write2Byte(0x1F, u16Data);
}

#if SPINAND_DEBUG
BOOL HAL_SPINAND_BDMA_CHECK(U32 u32Addr, U32 u32DataSize, U8 *u8pData)
{
    U32 u32Addr1;
    BOOL bRet;

    //Set source and destination path
    _HAL_BDMA_Write2Byte(0x00, 0x0000);
    _HAL_BDMA_Write2Byte(0x02, 0x4029);

    u32Addr =(u32Addr - TSP_SRAM_BASE_ADDRESS);
    // Set source address
    *(unsigned short  volatile *)(0xBF201210) = (u32Addr & 0xFFFF);
    *(unsigned short  volatile *)(0xBF201214) = (u32Addr >> 16);
    u32Addr1 = ((U32)u8pData - 0x80000000);
    // Set destination  address
    *(unsigned short  volatile *)(0xBF201218) = (U16)(u32Addr1 & 0x0000FFFF);
    *(unsigned short  volatile *)(0xBF20121C) = (U16)(u32Addr1 >> 16);
    // Set Size
    *(unsigned short  volatile *)(0xBF201220) = (U16)(u32DataSize & 0xFFFF);
    *(unsigned short  volatile *)(0xBF201224) = (U16)(u32DataSize >> 16);

    //switch sram control to BDMA
    /*
          bootsram_access_sel 0 spi_nand_boot_sel  0 : MIPS
          bootsram_access_sel 0 spi_nand_boot_sel  1 : BDMA
      */
    *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x101ce0 << 1)) &= 0xfffd;

    // bootsram_access_sel
    *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x11135e << 1)) &= 0xffef;

    // spi_nand_boot_sel
    *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x103c1a << 1)) |= 0x8000;

    // Trigger
    *(unsigned short  volatile *)(0xBF201200) = 1;

    do
    {
        //check done
        if(*(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x100902 << 1)) & 0x08)
        {
            //clear done
            *(unsigned char volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x100902 << 1)) = 0x08;
            bRet = TRUE;
            break;
        }
    } while (1);
    // spi_nand_boot_sel
    *(unsigned short  volatile *)(CONFIG_RIU_BASE_ADDRESS + (0x103c1a << 1)) &= 0x7fff;

    return bRet;

}
#endif
