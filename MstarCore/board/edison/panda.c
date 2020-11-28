/*
 * (C) Copyright 2010
 * Texas Instruments Incorporated, <www.ti.com>
 * Steve Sakoman  <steve@sakoman.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "panda.h"


#if 0//(CONFIG_R2_BRINGUP)
#include "drvSERFLASH.h" //for flash copy fw from flash to dram
#include "drvBDMA.h" //for bdma copy fw from flash to dram

static MS_U32 _gMIO_MapBase = 0x1F000000;

#define UART_DBG_FRCR2  0x00 //A5
#define UART_DBG_UART0  0x04
#define UART_DBG_SECR2  0x0D
#define UART_DBG_OTHER  UART_DBG_UART0 

#define UART_DBG_SRC    UART_DBG_SECR2
#define REG_R2_BASE			0x122A00

#define BIT11			(1 << 11)
#define BIT12			(1 << 12)
#define BIT13			(1 << 13)

MS_U8 _ReadByte(MS_U32 u32RegAddr)
{
    return ((volatile MS_U8*)(_gMIO_MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)];
}

MS_U16 _Read2Byte(MS_U32 u32RegAddr)
{
    return ((volatile MS_U16*)(_gMIO_MapBase))[u32RegAddr];
}

MS_U32 _Read4Byte(MS_U32 u32RegAddr)
{
    return (_Read2Byte(u32RegAddr) | _Read2Byte(u32RegAddr+2) << 16);
}

MS_BOOL _WriteByte(MS_U32 u32RegAddr, MS_U8 u8Val)
{
    if (!u32RegAddr)
    {
        return FALSE;
    }
    ((volatile MS_U8*)(_gMIO_MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)] = u8Val;
    return TRUE;
}

MS_BOOL _Write2Byte(MS_U32 u32RegAddr, MS_U16 u16Val)
{
    if (!u32RegAddr)
    {
        return FALSE;
    }

    ((volatile MS_U16*)(_gMIO_MapBase))[u32RegAddr] = u16Val;
    return TRUE;
}

MS_BOOL _Write4Byte(MS_U32 u32RegAddr, MS_U32 u32Val)
{
    if (!u32RegAddr)
    {
        return FALSE;
    }

    _Write2Byte(u32RegAddr, u32Val & 0x0000FFFF);
    _Write2Byte(u32RegAddr+2, u32Val >> 16);
    return TRUE;
}

MS_BOOL _WriteRegBit(MS_U32 u32RegAddr, MS_U8 u8Mask, MS_BOOL bEnable)
{
    MS_U8 u8Val = _ReadByte(u32RegAddr);
    if (!u32RegAddr)
    {
        return FALSE;
    }

    u8Val = _ReadByte(u32RegAddr);
    u8Val = (bEnable) ? (u8Val | u8Mask) : (u8Val & ~u8Mask);
    _WriteByte(u32RegAddr, u8Val);
    return TRUE;
}


void MApi_R2_FwCopy(MS_U32 u32FlashAddr, MS_U32 u32DramAddr, MS_U32 u32Len)
{
	printf("Copy R2 Fw from Flash 0x%08x to Ram 0x%08x, len = 0x%08x ... ",
		(unsigned int)u32FlashAddr, (unsigned int)u32DramAddr, (unsigned int)u32Len);

	MDrv_BDMA_SetDbgLevel(E_BDMA_DBGLV_ALL);

	MDrv_BDMA_Init(0x20000000);

	MDrv_BDMA_FlashCopy2Dram((MS_PHYADDR)u32FlashAddr, (MS_PHYADDR)u32DramAddr, u32Len);

	printf("Done!\n");
}

void MApi_R2_StartFrDRAM(MS_U32 addr)
{
	MS_U32 AeonBufAdr=addr;
	MS_U16 value;

	printf("R2 Boot from 0x%08x\n", (unsigned int)AeonBufAdr);

	// select UART source
	_WriteByte(0x101EA6, UART_DBG_SRC);

	//switch UART to dig_mux (instead of MCU51)
	value = _Read2Byte(0x0E12);
#if 1 //HK message
	value &= (~BIT12); //0: dig_mux (reg_uart_sel0)
	value |= BIT11; //1: enable uart rx via  PAD_DDCA for dig_mux (reg_uart_sel0)
#else //PM message
	value |= (BIT12); //1: HK MCU51 uart0
	value |= BIT11; //1: enable uart rx via  PAD_DDCA for dig_mux (reg_uart_sel0)
#endif
	_Write2Byte(0x0E12,value);


	//(1) Disable R2 -> Stop
	_WriteByte(REG_R2_BASE+0x40*2, 0x00); //disable R2

	//(2) Set R2 clock
	// [1:0] = 2'b00
	// [3:2] = 2'b00: 240MHz,  2'b01: 192HMz, 2'b10: 172MHz, 2'b11: 144MHz
	// Set to 240 MHz
	_WriteByte(0x10337A, 0x00);

	// check MIU memory mapping
#if 0
	//(3) Set CPU SDR base
	_Write2Byte(REG_R2_BASE+0x41*2, (AeonBufAdr&0x0000FFFF)); //I Fetch Offset - Low
	_Write2Byte(REG_R2_BASE+0x42*2, (AeonBufAdr>>16)); //I Fetch Offset - High
	_Write2Byte(REG_R2_BASE+0x43*2, (AeonBufAdr&0x0000FFFF)); //D Fetch Offset - Low
	_Write2Byte(REG_R2_BASE+0x44*2, (AeonBufAdr>>16)); //D Fetch Offset - High
#else
	//(3) Set CPU reset base(vector)
	_Write2Byte(REG_R2_BASE+0x5A*2, (AeonBufAdr>>16)); //CPU reset base (vector)  // reset vector address 0x0(64K alignment)
#endif

	//(4) Set UART base
	_Write2Byte(REG_R2_BASE+0x55*2, 0x9000); // UART base address

	//(5) Set IO space enable (UART, RIU) with QMEM space disabled
	_Write2Byte(REG_R2_BASE+0x58*2, 0x0003); // io_space_en[3:0]: UART,RIU, qmem_space_en[4] : disable

	//(6) CPU SW reset R2
	_Write2Byte(0x2E52, _Read2Byte(0x2E52) &(~BIT13));
	_Write2Byte(0x2E52, _Read2Byte(0x2E52) |(BIT13));

	//(7) Without QMEM 
#if 0
	_Write2Byte(REG_R2_BASE+0x4E*2, 0xB000); // QMEM base address = 0x80000000
	_Write2Byte(REG_R2_BASE+0x50*2, 0xF000); // QMEM less, set DCU Decoding..
#endif

	//(8) Enable R2 -> Start
	_WriteByte(REG_R2_BASE+0x40*2, 0x24); // miu_sw_rst and sdram_boot = 1
	_WriteByte(REG_R2_BASE+0x40*2, 0x27); // sdram_boot and (miu/r2/r2_rst) =1
}

#endif	// CONFIG_R2_BRINGUP



DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
	"Board:"
};

/**
 * @brief board_init
 *
 * @return 0
 */
int board_init(void)
{
#if 0//(CONFIG_R2_BRINGUP)
	MS_U32 u32R2FWAddr = 0x100000;
	MS_U32 u32R2BaseAddr = 0x200000;
	MS_U32 u32R2FWLen = 0x20000;

	MApi_R2_FwCopy(u32R2FWAddr, u32R2BaseAddr, u32R2FWLen);

	MApi_R2_StartFrDRAM(u32R2BaseAddr);
#endif	// CONFIG_R2_BRINGUP

#if 0 //MSTAR
	gpmc_init();
#endif
	gd->bd->bi_arch_number = MACH_TYPE_OMAP4_PANDA;
	gd->bd->bi_boot_params = (0x40400000 + 0x100); /* boot param addr */

	return 0;
}

int board_eth_init(bd_t *bis)
{
	return 0;
}

/**
 * @brief misc_init_r - Configure Panda board specific configurations
 * such as power configurations, ethernet initialization as phase2 of
 * boot sequence
 *
 * @return 0
 */
int misc_init_r(void)
{
	return 0;
}

void do_set_mux(u32 base, struct pad_conf_entry const *array, int size)
{
	int i;
	struct pad_conf_entry *pad = (struct pad_conf_entry *) array;

	for (i = 0; i < size; i++, pad++)
		writew(pad->val, base + pad->offset);
}

/**
 * @brief set_muxconf_regs Setting up the configuration Mux registers
 * specific to the board.
 */
void set_muxconf_regs(void)
{
#if 0
	do_set_mux(CONTROL_PADCONF_CORE, core_padconf_array,
		   sizeof(core_padconf_array) /
		   sizeof(struct pad_conf_entry));

	do_set_mux(CONTROL_PADCONF_WKUP, wkup_padconf_array,
		   sizeof(wkup_padconf_array) /
		   sizeof(struct pad_conf_entry));
#endif
}

#if 0
extern int fcie_mmc_init(bd_t *bis);

int board_mmc_init(bd_t *bis)
{
	fcie_mmc_init(bis);
	return 0;
}
#endif
