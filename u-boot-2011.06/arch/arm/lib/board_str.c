/*
 * (C) Copyright 2002-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <timestamp.h>
#include <version.h>
#include <net.h>
#include <serial.h>
#include <nand.h>
#include <onenand_uboot.h>
#include <mmc.h>

#include <MsCmdTable.h>
#include <MsCoreRegister.h>
#include <MsCustomerRegister.h>

// MSTAR start
#include <MsInit.h>
#include <ShareType.h>
#include <drvGPIO.h>
#include <drvIRQ.h>
#include <MsOS.h>
#include <MsDevice.h>
#include <common.h>
#include <command.h>
#include <drvSERFLASH.h>
#include <drvBDMA.h>
#include <drvSYS.h>

#include <drvPM.h>
#include <mmc.h>
#include <MsDebug.h>
#if defined (CONFIG_USB_PREINIT)
#include <usb.h>
#endif
#if(ENABLE_URSA_8==1)
#include <drvMSPI.h>
#endif

#if (CONFIG_BINARY_RELEASE == 1)
#include <MsMBootConfig.h>
#endif
// MSTAR end

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

#ifdef CONFIG_DRIVER_SMC91111
#include "../drivers/net/smc91111.h"
#endif
#ifdef CONFIG_DRIVER_LAN91C96
#include "../drivers/net/lan91c96.h"
#endif







typedef int (init_fnc_t) (void);
extern gd_t *gd ;
extern init_fnc_t *init_sequence[];
#define ROUND_UP(x,y) ((x+y-1)&(~(y - 1)))

cmd_tbl_t  *u_boot_cmd_tbl_start,*u_boot_cmd_tbl_end;
extern void board_init_str_r (gd_t *id, ulong dest_addr);

void init_cmd_tbl_str(void)
{
    u_boot_cmd_tbl_start=&__u_boot_cmd_str_start;
    u_boot_cmd_tbl_end=&__u_boot_cmd_str_end;
}

void board_init_str_f (ulong bootflag)
{
    gd_t lgd;
    init_fnc_t **init_fnc_ptr;
    gd_t *id;
    bd_t *bd;
	ulong addr, addr_sp, relocaddr;
    extern void set_irq_sp(ulong);

    memset(&lgd,0,sizeof(gd_t));
    gd = &lgd;
    gd->mon_len = _bss_str_end_ofs;
    for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}
#if defined(CONFIG_SYS_MEM_TOP_HIDE)
	/*
	 * Subtract specified amount of memory to hide so that it won't
	 * get "touched" at all by U-Boot. By fixing up gd->ram_size
	 * the Linux kernel should now get passed the now "corrected"
	 * memory size and won't touch it either. This should work
	 * for arch/ppc and arch/powerpc. Only Linux board ports in
	 * arch/powerpc with bootwrapper support, that recalculate the
	 * memory size from the SDRAM controller setup will have to
	 * get fixed.
	 */
	gd->ram_size -= CONFIG_SYS_MEM_TOP_HIDE;
#endif

    addr = (ulong)(&__bss_str_end__);
#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
	debug ("Reserving %dk for kernel logbuffer at %08lx\n", LOGBUFF_LEN, addr);
    /* reserve kernel log buffer */
	addr += (LOGBUFF_RESERVE);
#endif
#endif

#ifdef CONFIG_PRAM
	/*
	 * reserve protected RAM
	 */
	i = getenv_r ("pram", (char *)tmp, sizeof (tmp));
	reg = (i > 0) ? simple_strtoul ((const char *)tmp, NULL, 10) : CONFIG_PRAM;
	debug ("Reserving %ldk for protected RAM at %08lx\n", reg, addr);
    addr += (reg << 10);		/* size is in kB */
#endif /* CONFIG_PRAM */

#if !(defined(CONFIG_SYS_NO_ICACHE) && defined(CONFIG_SYS_NO_DCACHE))
	/* reserve TLB table */
    /* round down to next 16 kB limit */
	addr =ROUND_UP(addr, 0x4000);
    gd->tlb_addr = addr;
	debug ("TLB table at: %08lx\n", addr);
	addr += (4096 * 4);
    relocaddr = _TEXT_BASE;
	/*Setup page table, and enable MMU*/
	enable_mmu(gd->tlb_addr, relocaddr);
#endif

	/* round down to next 4 kB limit */
	addr = ROUND_UP(addr, 4096);
	debug ("Top of RAM usable for U-Boot at: %08lx\n", addr);

#ifdef CONFIG_LCD
#ifdef CONFIG_FB_ADDR
	gd->fb_base = CONFIG_FB_ADDR;
#else
	/* reserve memory for LCD display (always full pages) */
	addr = lcd_setmem (addr);
	gd->fb_base = addr;
#endif /* CONFIG_FB_ADDR */
#endif /* CONFIG_LCD */

#ifndef CONFIG_PRELOADER
	/*
	 * reserve memory for malloc() arena
	 */
	addr_sp = addr;
	debug ("Reserving %dk for malloc() at: %08lx\n",
			TOTAL_MALLOC_LEN_STR >> 10, addr_sp);
    addr_sp = addr + TOTAL_MALLOC_LEN_STR;
	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	bd = (bd_t *) addr_sp;
	gd->bd = bd;
	debug ("Reserving %zu Bytes for Board Info at: %08lx\n",
			sizeof (bd_t), addr_sp);
    addr_sp += sizeof (bd_t);
	id = (gd_t *) addr_sp;
	debug ("Reserving %zu Bytes for Global Data at: %08lx\n",
			sizeof (gd_t), addr_sp);
    addr_sp += sizeof (gd_t);

	/* setup stackpointer for exeptions */
#ifdef CONFIG_USE_IRQ
	debug ("Reserving %zu Bytes for IRQ stack at: %08lx\n",
		CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ, addr_sp);
    addr_sp += (CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ);
#endif
	/* leave 3 words for abort-stack    */
	addr_sp += 12;

	/* 8-byte alignment for ABI compliance */
	addr_sp = ROUND_UP(addr_sp, 8);
    gd->irq_sp = addr_sp;
	set_irq_sp(gd->irq_sp);
#else
	addr_sp += 128;	/* leave 32 words for abort-stack   */
	gd->irq_sp = addr_sp;
#endif

	debug ("New Stack Pointer is: %08lx\n", addr_sp);

#ifdef CONFIG_POST
	post_bootmode_init();
	post_run (NULL, POST_ROM | post_bootmode_get(0));
#endif

	gd->bd->bi_baudrate = gd->baudrate;
	gd->relocaddr = relocaddr;
	gd->start_addr_sp = addr_sp+UBOOT_STK_LEN;
	gd->reloc_off = relocaddr - _TEXT_BASE;
	memcpy (id, (void *)gd, sizeof (gd_t));
	relocate_code_str (gd->start_addr_sp, id, relocaddr, (ulong)board_init_str_r);

}
extern unsigned int u32UbootStart;
extern unsigned int u32UbootEnd;
extern int print_cpuinfo (void);
extern void MstarSysInit_str(void);

void board_init_str_r (gd_t *id, ulong dest_addr)
{
	bd_t *bd;
	ulong malloc_start;
#if !defined(CONFIG_SYS_NO_FLASH)
	ulong flash_size;
#endif

    gd = id;
	bd = gd->bd;
	gd->flags |= GD_FLG_RELOC;	/* tell others: relocation done */
    init_cmd_tbl_str();
    //display_banner();		/* say that we are here */
    malloc_start = (ulong)bd - TOTAL_MALLOC_LEN_STR;
	mem_malloc_init (malloc_start, TOTAL_MALLOC_LEN_STR);

    /*MSTAR start*/
    MstarSysInit_str();
    u32UbootStart = id->relocaddr;
    u32UbootEnd = id->start_addr_sp;
    printf("\nuboot held at [%08x~%08x],size=%08x\n",
            u32UbootStart,
            u32UbootEnd,
            u32UbootEnd-u32UbootStart);
    /* MSTAR end*/

    //monitor_flash_len = _end_ofs;

#if defined(CONFIG_DISPLAY_CPUINFO)
	print_cpuinfo();		/* display cpu info (and speed) */
#endif

    /* Ram ist board specific, so move it to board code ... */
	dram_init_banksize();
	//display_dram_config();	/* and display it */
	//debug ("monitor flash len: %08lX\n", monitor_flash_len);
	board_init();	/* Setup chipselects */

#ifdef CONFIG_SERIAL_MULTI
	serial_initialize();
#endif

	printf ("Now running in RAM - U-Boot at: %08lx\n", dest_addr);

    #if !defined(CONFIG_SYS_NO_FLASH)
	puts ("Flash: ");

	if ((flash_size = flash_init ()) > 0) {
#ifdef CONFIG_SYS_FLASH_CHECKSUM
		print_size (flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		s = getenv ("flashchecksum");
		if (s && (*s == 'y')) {
			printf ("  CRC: %08X",
				crc32 (0, (const unsigned char *) CONFIG_SYS_FLASH_BASE, flash_size)
			);
		}
		putc ('\n');
#else	/* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size (flash_size, "\n");
#endif /* CONFIG_SYS_FLASH_CHECKSUM */
	} else {
		puts (failed);
		hang ();
	}
#endif

#if defined(CONFIG_CMD_NAND)
	puts ("NAND:  ");
	nand_init();		/* go init the NAND */
#endif

#if defined(CONFIG_CMD_ONENAND)
	onenand_init();
#endif

#ifdef CONFIG_HAS_DATAFLASH
	AT91F_DataflashInit();
	dataflash_print_info();
#endif

#if defined(CONFIG_GENERIC_MMC) && defined(CONFIG_ENV_IS_IN_MMC)
	//puts("MMC:	");
	mmc_initialize(bd);
#endif
	/* initialize environment */
	env_relocate ();
#if defined(CONFIG_GENERIC_MMC) && defined(CONFIG_ENV_IS_IN_SPI_FLASH)
	//puts("MMC:	");
	mmc_initialize(bd);
#endif
#if defined(CONFIG_CMD_PCI) || defined(CONFIG_PCI)
	arm_pci_init();
#endif

	/* IP Address */
	gd->bd->bi_ip_addr = getenv_IPaddr ("ipaddr");
	stdio_init ();	/* get the devices list going. */
	jumptable_init ();

#if defined(CONFIG_API)
	/* Initialize API */
	api_init ();
#endif
	console_init_r ();	/* fully init console as a device */
#if defined(CONFIG_ARCH_MISC_INIT)
	/* miscellaneous arch dependent initialisations */
	arch_misc_init ();
#endif
#if defined(CONFIG_MISC_INIT_R)
	/* miscellaneous platform dependent initialisations */
	misc_init_r ();
#endif
	/* set up exceptions */
	interrupt_init ();
	/* enable exceptions */
	enable_interrupts ();

#if !(CONFIG_LOGO_STORE_IN_MBOOT) && !(CONFIG_MINIUBOOT) && !(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN)
    run_command("dbtable_init", 0);
#endif
    run_command("initDbgLevel", 0);
    run_command("updatemiureg", 0);
#if(ENABLE_URSA_8==1)
    run_command ("InitUrsa8" , 0);
#endif
    run_command("panel_pre_init",0);
#if(ENABLE_URSA_8==1)
    run_command ("ursa8_lvds_on" , 0);
#endif
#if defined (CONFIG_URSA_6M40)
    run_command("ursa_lvds_on", 0);
    run_command("ursa_osd_unmute", 0);
#endif
#if defined (CONFIG_SECURITY_BOOT)
    run_command ("SecureInit" , 0);
#endif

#if defined (CONFIG_TEE)
    run_command ("readNuttx" ,0);
    run_command ("bootNuttx" ,0);
#endif

    run_command("panel_post_init",0);
#if (CONFIG_ENABLE_RTPM)
    run_command ("runtime_pm" , 0);
#endif
#if defined (CONFIG_URSA6_VB1)
    run_command("send_I2C_cmd_to_ursa6" , 0);
#endif
    run_command ("checkstr" , 0);
    printf("Wow, we shouldn't be here!\n");
    while(1);
}

extern unsigned long MS_RIU_MAP;
extern MS_BOOL MDrv_MMIO_GetBASE(MS_U32 *u32Baseaddr, MS_U32 *u32Basesize, MS_U32 u32Module);
extern MS_BOOL MDrv_MMIO_Init(void);
void MstarSysInit_str(void)
{
    uint u32Tmp;
    /*set up Mstar IRQ handler*/
    extern void mhal_fiq_merge(void);
    extern void MAsm_CPU_TimerStart(void);
    extern void dcache_init(void);
    extern void l2_cache_init(void);
    mhal_fiq_merge();
    MsOS_Init_str();
#ifdef CONFIG_SYS_DCACHE
    dcache_init();
#endif

#ifndef CONFIG_L2_OFF
    l2_cache_init();
#endif
#if defined(CONFIG_TIMER_TEST)
    MDrv_Timer_ISR_Register();
#endif
    MsOS_CPU_EnableInterrupt();
    MAsm_CPU_TimerStart();

    MDrv_MMIO_Init();
    MDrv_MMIO_GetBASE((MS_U32 *)&MS_RIU_MAP, (MS_U32 *)&u32Tmp, MS_MODULE_PM);
    MDrv_SYS_Init();
#if (ENABLE_MODULE_ENV_IN_SERIAL==1)
#if (ENABLE_MODULE_SPI == 1)
    puts ("SPI:  ");
    {
        extern int spi_init (void);
        spi_init();		/* go init the SPI */
    }

    #if (CONFIG_MSTAR_BD_MST028B_10AFX_EAGLE||CONFIG_MSTAR_BD_MST038B_10AHT_EAGLE ||CONFIG_MSTAR_BD_MST049B_10AQV_NIKE || CONFIG_MSTAR_BD_MST049B_10AQV_NIKE_U)
    MDrv_SERFLASH_SetWPInfo(TRUE);
    #else
    ms_Flash_SetHWWP_CB pCB = msFlash_ActiveFlash_Set_HW_WP;
    MDrv_SERFLASH_SetFlashWPCallBack(pCB);
    FlashSetHWWPCB = FlashSetHWWPCB;
    McuChipSelectCB = McuChipSelectCB;
    #endif
#endif
#else
    #if (ENABLE_MODULE_SPI==1)
        MDrv_SERFLASH_Init();
    #endif
#endif

#if(ENABLE_URSA_8==1)
    MDrv_MSPI_Init_Ext(0x0);
#endif
    mdrv_gpio_init();
    MDrv_BDMA_Init(CONFIG_SYS_MIU_INTERVAL);

#if defined (CONFIG_USB_PREINIT)
        init_usb();
#endif
    #ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN
    run_command("init_raw_io" , 0);
    run_command("config_raw_io" , 0);
    #endif
}

