/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Add to readline cmdline-editing by
 * (C) Copyright 2005
 * JinHua Luo, GuangDong Linux Center, <luo.jinhua@gd-linux.com>
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

/* #define	DEBUG	*/

#include <common.h>
#include <watchdog.h>
#include <command.h>
#ifdef CONFIG_MODEM_SUPPORT
#include <malloc.h>		/* for free() prototype */
#endif
//Mstar Start
#include <MsStart.h>
//Mstar End
#ifdef CONFIG_SYS_HUSH_PARSER
#include <hush.h>
#endif

#include <post.h>
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
#include <MsSysUtility.h>
#endif

#if (CONFIG_VESTEL_MB100 == 1)
#include <MsUboot.h>
#endif

#if defined(CONFIG_SILENT_CONSOLE) || defined(CONFIG_POST) || defined(CONFIG_CMDLINE_EDITING)
DECLARE_GLOBAL_DATA_PTR;
#endif

#if defined(MBOOT_VERSION)
static const char *const mboot_version = MBOOT_VERSION;
#else
#warning "MBOOT_VERSION not defined!"
static const char *const mboot_version = NULL;
#endif
#include "drvUART.h"

#if (CONFIG_WDT)
#define WDT_UPGRADE_TIMEOUT 999
#endif

/*
 * Board-specific Platform code can reimplement show_boot_progress () if needed
 */
void inline __show_boot_progress (int val) {}
void show_boot_progress (int val) __attribute__((weak, alias("__show_boot_progress")));

#if defined(CONFIG_UPDATE_TFTP)
void update_tftp (void);
#endif /* CONFIG_UPDATE_TFTP */

#define MAX_DELAY_STOP_STR 32

#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
static int abortboot(int);
#endif

#undef DEBUG_PARSER

char        console_buffer[CONFIG_SYS_CBSIZE + 1];	/* console I/O buffer	*/

static char * delete_char (char *buffer, char *p, int *colp, int *np, int plen);
static const char erase_seq[] = "\b \b";		/* erase sequence	*/
static const char   tab_seq[] = "        ";		/* used to expand TABs	*/

#ifdef CONFIG_BOOT_RETRY_TIME
static uint64_t endtime = 0;  /* must be set, default is instant timeout */
static int      retry_time = -1; /* -1 so can call readline before main_loop */
#endif

#define	endtick(seconds) (get_ticks() + (uint64_t)(seconds) * get_tbclk())

#ifndef CONFIG_BOOT_RETRY_MIN
#define CONFIG_BOOT_RETRY_MIN CONFIG_BOOT_RETRY_TIME
#endif
#if (CONFIG_VESTEL_MB100 == 1)
#define WAIT_MFC_ENTER_MAIN_LOOP 400
#endif
#ifdef CONFIG_MODEM_SUPPORT
int do_mdm_init = 0;
extern void mdm_init(void); /* defined in board.c */
#endif
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
int uartEn=1;
#if ( CONFIG_VESTEL_MB97 == 1 )
MS_BOOL gb_EnvUpdate = FALSE;
#endif
//***************************************************************************
//=====================
//this enum should be synced with MBOOT and PM code
typedef enum
{
    eIR_RC5=0,
    eIR_JVC,
    eIR_NEC,
    eIR_PANASONIC,
    eIR_RC5X,
    eIR_RC6,
    eIR_SHARP,
    eIR_MAX,
    eIR_UNKNOW =0xFF,
}IRID;

typedef enum
{
    E_IR_CUS22T_HW = 0x01,
    E_IR_RC5 = 0x02,
    E_IR_PANASONIC = 0x03,
    E_IR_CUS03 = 0xFF,
} E_PM_MULTI_IR;

//#define RIU_DUMMY0_REG                0x0E68
#define RIU_DUMMY0_REG_H            0x1042
//#define RIU_DUMMY1_REG                0x0E6F
#define RIU_DUMMY2_REG                0x1044//0x0E5E
#define RIU_DUMMY2_REG_H            0x0E5F
#define RIU_DUMMY3_REG                0x1046
//#define RIU_DUMMY3_REG_H            0x0E73

#define NORML_1000MS				10	//unit: 100ms
#define FWUPGRADE_FINISH_600MS	6
#define FWUPGRADE_300MS			3


#define BLINKING_STATE        0x30
#define BLINK_ON            0x30
#define BLINK_OFF            0x00


void Enable_PM_LedBlinking(int time)
{
	if (time==FWUPGRADE_300MS)
	{
		WriteByte(RIU_DUMMY0_REG_H, (ReadByte(RIU_DUMMY0_REG_H)&(~BLINK_ON)));
		WriteByte(RIU_DUMMY3_REG, FWUPGRADE_300MS);
		WriteByte(RIU_DUMMY0_REG_H, (ReadByte(RIU_DUMMY0_REG_H)|BLINK_ON));
	}
	else
	{
		WriteByte(RIU_DUMMY0_REG_H, (ReadByte(RIU_DUMMY0_REG_H)&(~BLINK_ON)));
        WriteByte(RIU_DUMMY3_REG, NORML_1000MS);
	    WriteByte(RIU_DUMMY0_REG_H, (ReadByte(RIU_DUMMY0_REG_H)|BLINK_ON));
    }
}

#endif
/***************************************************************************
 * Watch for 'delay' seconds for autoboot stop or autoboot delay string.
 * returns: 0 -  no key string, allow autoboot
 *          1 - got key string, abort
 */
#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
# if defined(CONFIG_AUTOBOOT_KEYED)
static __inline__ int abortboot(int bootdelay)
{
	int abort = 0;
	uint64_t etime = endtick(bootdelay);
	struct {
		char* str;
		u_int len;
		int retry;
	}
	delaykey [] = {
		{ str: getenv ("bootdelaykey"),  retry: 1 },
		{ str: getenv ("bootdelaykey2"), retry: 1 },
		{ str: getenv ("bootstopkey"),   retry: 0 },
		{ str: getenv ("bootstopkey2"),  retry: 0 },
	};

	char presskey [MAX_DELAY_STOP_STR];
	u_int presskey_len = 0;
	u_int presskey_max = 0;
	u_int i;

#  ifdef CONFIG_AUTOBOOT_PROMPT
	printf(CONFIG_AUTOBOOT_PROMPT);
#  endif

#  ifdef CONFIG_AUTOBOOT_DELAY_STR
	if (delaykey[0].str == NULL)
		delaykey[0].str = CONFIG_AUTOBOOT_DELAY_STR;
#  endif
#  ifdef CONFIG_AUTOBOOT_DELAY_STR2
	if (delaykey[1].str == NULL)
		delaykey[1].str = CONFIG_AUTOBOOT_DELAY_STR2;
#  endif
#  ifdef CONFIG_AUTOBOOT_STOP_STR
	if (delaykey[2].str == NULL)
		delaykey[2].str = CONFIG_AUTOBOOT_STOP_STR;
#  endif
#  ifdef CONFIG_AUTOBOOT_STOP_STR2
	if (delaykey[3].str == NULL)
		delaykey[3].str = CONFIG_AUTOBOOT_STOP_STR2;
#  endif

	for (i = 0; i < sizeof(delaykey) / sizeof(delaykey[0]); i ++) {
		delaykey[i].len = delaykey[i].str == NULL ?
				    0 : strlen (delaykey[i].str);
		delaykey[i].len = delaykey[i].len > MAX_DELAY_STOP_STR ?
				    MAX_DELAY_STOP_STR : delaykey[i].len;

		presskey_max = presskey_max > delaykey[i].len ?
				    presskey_max : delaykey[i].len;

#  if DEBUG_BOOTKEYS
		printf("%s key:<%s>\n",
		       delaykey[i].retry ? "delay" : "stop",
		       delaykey[i].str ? delaykey[i].str : "NULL");
#  endif
	}

	/* In order to keep up with incoming data, check timeout only
	 * when catch up.
	 */
	do {
		if (tstc()) {
			if (presskey_len < presskey_max) {
				presskey [presskey_len ++] = getc();
			}
			else {
				for (i = 0; i < presskey_max - 1; i ++)
					presskey [i] = presskey [i + 1];

				presskey [i] = getc();
			}
		}

		for (i = 0; i < sizeof(delaykey) / sizeof(delaykey[0]); i ++) {
			if (delaykey[i].len > 0 &&
			    presskey_len >= delaykey[i].len &&
			    memcmp (presskey + presskey_len - delaykey[i].len,
				    delaykey[i].str,
				    delaykey[i].len) == 0) {
#  if DEBUG_BOOTKEYS
				printf("got %skey\n",
				       delaykey[i].retry ? "delay" : "stop");
#  endif

#  ifdef CONFIG_BOOT_RETRY_TIME
				/* don't retry auto boot */
				if (! delaykey[i].retry)
					retry_time = -1;
#  endif
				abort = 1;
			}
		}
	} while (!abort && get_ticks() <= etime);

#  if DEBUG_BOOTKEYS
	if (!abort)
		puts("key timeout\n");
#  endif

#ifdef CONFIG_SILENT_CONSOLE
	if (abort)
		gd->flags &= ~GD_FLG_SILENT;
#endif

	return abort;
}

# else	/* !defined(CONFIG_AUTOBOOT_KEYED) */

#ifdef CONFIG_MENUKEY
static int menukey = 0;
#endif

static __inline__ int abortboot(int bootdelay)
{
	int abort = 0;
#if 1 //MStar
	char input=0;
#endif

    if(uartEn==0)
       return 0;

#ifdef CONFIG_MENUPROMPT
	printf(CONFIG_MENUPROMPT);
#else
	printf("Hit any key to stop autoboot: %2d ", bootdelay);
#endif

#if defined CONFIG_ZERO_BOOTDELAY_CHECK
	/*
	 * Check if key already pressed
	 * Don't check if bootdelay < 0
	 */
	if (bootdelay >= 0) {
		if (tstc()) {	/* we got a key press	*/
#if 1 //MStar, block all key except enter key
			input = getc();  /* consume input	*/
			if((input == '\r') || (input == '\n'))
			{
				puts ("\b\b\b 0");
				abort = 1;	/* don't auto boot	*/
			}
#else
			(void) getc();  /* consume input	*/
			puts ("\b\b\b 0");
			abort = 1;	/* don't auto boot	*/
#endif
		}
	}
#endif

	while ((bootdelay > 0) && (!abort)) {
		int i;

		--bootdelay;
		/* delay 100 * 10ms */
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
        for (i=0; !abort && i<10; ++i) {
#else
		for (i=0; !abort && i<100; ++i) {
#endif
			if (tstc()) {	/* we got a key press	*/
				abort  = 1;	/* don't auto boot	*/
				bootdelay = 0;	/* no more delay	*/
# ifdef CONFIG_MENUKEY
				menukey = getc();
# else
				(void) getc();  /* consume input	*/
# endif
				break;
			}
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
			udelay(10);
#else
			udelay(10000);
#endif
		}

		printf("\b\b\b%2d ", bootdelay);
	}

	putc('\n');

#ifdef CONFIG_SILENT_CONSOLE
	if (abort)
		gd->flags &= ~GD_FLG_SILENT;
#endif

	return abort;
}
# endif	/* CONFIG_AUTOBOOT_KEYED */
#endif	/* CONFIG_BOOTDELAY >= 0  */

/****************************************************************************/
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
//MB100_BRINGUP
extern int usb_init(int port);
extern int usb_stor_scan(int mode);
extern void msIR_Initialize(U8 irclk_mhz);
extern BOOLEAN msIR_GetIRKeyCode(U8 *pkey, U8 *pu8flag);
extern void Enable_PM_LedBlinking(int time);
extern void MDrv_SERFLASH_Init(void);
extern int get_mac_address_from_SPI(void);
extern int get_IR_Type_from_SPI(void);

extern MS_BOOL MDrv_SERFLASH_Read(MS_U32 u32FlashAddr, MS_U32 u32FlashSize, MS_U8 *user_buffer);
int check_sw_upgrade(void)
{
    printf("check_sw_upgrade\n");
    #if defined (CONFIG_USB_STORAGE)
        int port_switch = -1;

        if (usb_init(0) >= 0)
        {
            port_switch = 0;
        }
#if (CONFIG_VESTEL_MB97 == 1)
        else if (usb_init(1) >= 0)
        {
            port_switch = 1;
        }
#endif        
        else if (usb_init(3) >= 0)
        {
            port_switch = 3;
        }
        else if (usb_init(4) >= 0)
        {
            port_switch = 4;
        }
        else
        {
            printf("#usb init fail on port 0,3,4 need check!\n");
        }

        if (port_switch != -1)
        {
            printf("port_switch is:%d\n",port_switch);

            if(usb_stor_scan(1)!=-1)
            {
                printf("#* FLASH programming: started\n");
                if(-1 == run_command("ustar",0))
                {
                    printf("#* FLASH programming: FAILED!\n");
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
                    Enable_PM_LedBlinking(NORML_1000MS);
                    return -1;
#endif
                }
                else
                {
                    printf("#* FLASH programming: completed\n");
                }

            }
            else
            { //could not find usb storage
                printf("could not find usb storage\n");
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
                Enable_PM_LedBlinking(NORML_1000MS);
                return -1;
#endif
            }
        }
        else
        { //usb init fail
            printf("could not find usb storage\n");
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
            Enable_PM_LedBlinking(NORML_1000MS);
            return -1;
#endif
        }

return 1;
    #endif
}
#endif


#if defined(ENABLE_ILLUMINATED_LOGO)
typedef enum
{
    E_ILOGO_LED_ON_FADING_ON=0,        // set duty circle to full and start fading
    E_ILOGO_LED_OFF_FADING_ON,          // set duty circle to zero and start fading
    E_ILOGO_LED_ON_FADING_OFF,              // set duty circle to full and stop fading
    E_ILOGO_LED_OFF_FADING_OFF            // set duty circle to full and stop fading
}ILOGO_CMD;

void mapi_pm_ForceLogoFadingOn(void)
{
    // cmd => [6]: ILogo Enable, [5:4]: ILogo mode, [3]: ILogo Polarity, [2]: ILogo Cmd_Send, [1:0]: ILogo Cmd
    MS_U8 u8cmd = ReadByte(RIU_DUMMY2_REG);
    u8cmd |= BIT6;
    WriteByte(RIU_DUMMY2_REG, u8cmd);
}

void mapi_pm_IlluminatedLogoFadingOn(void)
{
    // cmd => [6]: ILogo Enable, [5:4]: ILogo mode, [3]: ILogo Polarity, [2]: ILogo Cmd_Send, [1:0]: ILogo Cmd
    MS_U8 u8cmd = ReadByte(RIU_DUMMY2_REG);
    MS_U8 u8mode = (u8cmd&(BIT5|BIT4))>>4;

    if((u8cmd&BIT6) != BIT6)    // check if ILogo enable
        return;

    switch(u8mode)
    {
        case 0x00:  //ICE_illuminated_logo_on:
            u8cmd = (u8cmd&(BIT6|BIT5|BIT4|BIT3))|BIT2|E_ILOGO_LED_ON_FADING_ON;
            break;

        case 0x01:  //ICE_illuminated_logo_off:
            u8cmd = (u8cmd&(BIT6|BIT5|BIT4|BIT3))|BIT2|E_ILOGO_LED_OFF_FADING_OFF;
            break;

        case 0x02:  //ICE_illuminated_logo_standby_on:
            u8cmd = (u8cmd&(BIT6|BIT5|BIT4|BIT3))|BIT2|E_ILOGO_LED_ON_FADING_ON;
            break;

        case 0x03:  //ICE_illuminated_logo_standby_off:
            u8cmd = (u8cmd&(BIT6|BIT5|BIT4|BIT3))|BIT2|E_ILOGO_LED_OFF_FADING_ON;
            break;
    }
    //printf("### u8cmd[0x%x] \n",u8cmd);
    WriteByte(RIU_DUMMY2_REG, u8cmd);

}
#endif
#if ((CONFIG_VESTEL_MB100 == 1) || (CONFIG_VESTEL_MB97 == 1))
/****************************************************************************/
int get_oad_flag(void)
{
    MS_U8 boot_data;
    /* read from flash to dram */
    if (MDrv_SERFLASH_Read((SPI_OAD_BOOT_FLAG_ADDR + SPI_OAD_BASE_ADDR), 1, &boot_data))
    {
        if (boot_data == 0xFF)
        {
            return 0xFF;
        }
        else
        {
            printf("OAD update code \n");
            return 0x00;
        }
    }
    else
    {
        printf("ERROR: SPI DMA fail !!!\n");
        return 0xFF; //default 0xFF
    }
}

void set_oad_flag(int bActive)
{
    MS_U8 boot_data;
    MS_U8 *pData;

    if (bActive == 1)
    {
        boot_data = 0x00;
        printf("Set OAD Flag \n");
    }
    else
    {
        boot_data = 0xFF;
        printf("Clear OAD Flag \n");
    }

    pData = malloc(SPI_BLOCK_SIZE);
    MDrv_SERFLASH_Read(SPI_OAD_BASE_ADDR, SPI_BLOCK_SIZE, pData);
    memcpy(pData + SPI_OAD_BOOT_FLAG_ADDR, &boot_data, 1);
    MDrv_SERFLASH_WriteProtect(0);
    //MDrv_SERFLASH_BlockErase(SPI_OAD_BASE_ADDR, SPI_OAD_BASE_ADDR, TRUE);
    MDrv_SERFLASH_AddressErase(SPI_OAD_BASE_ADDR, SPI_BLOCK_SIZE, TRUE);
    MDrv_SERFLASH_Write(SPI_OAD_BASE_ADDR, SPI_BLOCK_SIZE, pData);
    MDrv_SERFLASH_WriteProtect(1);
    free(pData);
}

#if ((CONFIG_VESTEL_MB100 == 1))
//MB100 now use EMMC
#define BUF1_ADDR 0xA0100000 //0x20400000
#define BUF1_COMPRESS_ADDR 0x20400000 //0x32000000
#define KL_SIZE 0x800000
#define RFS_SIZE 0x2000000
#define VEN_SIZE 0x19000000
#define CON_SIZE  0x0  // 0x1000000  // conf don't update in OAD
#define KL_UBI  0x800000
#define RFS_UBI 0x2000000
#define VEN_UBI 0x10000000
#define CON_UBI 0x4000000  // conf don't update in OAD
#define DECRYPT_KEY_SIZE 0x10
#define OAD_BIN_FILE "aurora.upg"  // should match FLASHFILE in ice_callisto.c
#if defined(CONFIG_TEE)
#define TEE_UBI 0x600000
#define TEE_SIZE 0x600000
#define KERNEL_SIGN_SIZE 0x220
#define TEE_SIGN_SIZE 0x1000 // sign part = 0x1210 + 16
#define NUTTX_CONFIG_SIZE 0x1000 //NUTTX config
//#define OAD_FILE_SIZE (KL_SIZE+RFS_SIZE+VEN_SIZE+TEE_SIZE+TEE_SIGN_SIZE+KERNEL_SIGN_SIZE+NUTTX_CONFIG_SIZE+DECRYPT_KEY_SIZE)
#define OAD_FILE_SIZE 0x10000000//0x8000000
#else
//#define OAD_FILE_SIZE (KL_SIZE+RFS_SIZE+VEN_SIZE+DECRYPT_KEY_SIZE)
#define OAD_FILE_SIZE 0x10000000//0x8000000
#endif //#if defined(CONFIG_TEE)

#elif (CONFIG_VESTEL_MB97 == 1)

#define BUF1_ADDR 0x80400000
#define BUF1_COMPRESS_ADDR 0x88C00000
#define KL_SIZE 0x400000
#define RFS_SIZE 0x900000
#define VEN_SIZE 0x6A00000
#define TEE_SIZE 0x400000
#define TEE_SIGN_SIZE 0x220
#define KERNEL_SIGN_SIZE 0x1000
#define RFS_UBI 0x1000000
#define VEN_UBI 0x6E00000
#define DECRYPT_KEY_SIZE 0x10
#define OAD_BIN_FILE "aurora.upg"  // should match FLASHFILE in ice_callisto.c
#define OAD_FILE_SIZE 0x5000000 //Luke Force to 80 MB //(KL_SIZE+RFS_SIZE+VEN_SIZE+DECRYPT_KEY_SIZE)

#endif
#define BUF_SIZE 4096

#if (CONFIG_VESTEL_MB97 == 1)
int oad_auto_update(void)
{
    char* buffer=NULL;

    buffer=(char *)malloc(BUF_SIZE);

    if(buffer==NULL)
    {
        printf("no memory for command string!!\n");
        return -1;
    }
    memset(buffer, 0 , BUF_SIZE);

    sprintf(buffer, "ubi part UBIB");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "ubifsmount BUF");
    printf("OAD >> %s \n",buffer);
    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }

    sprintf(buffer, "ubifsload 0x%X /%s 0x%X", BUF1_COMPRESS_ADDR,OAD_BIN_FILE, OAD_FILE_SIZE);

    printf("OAD >> %s \n",buffer);
    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }

    sprintf(buffer, "aesdec 0x%X 0x%X", BUF1_COMPRESS_ADDR, OAD_FILE_SIZE);

    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }

    sprintf(buffer,"mscompress7 d 0 0x%X 0x%X 0x%X",(BUF1_COMPRESS_ADDR+DECRYPT_KEY_SIZE),OAD_FILE_SIZE,(BUF1_ADDR+DECRYPT_KEY_SIZE));

    printf("OAD >> %s \n",buffer);
    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }

    //implement start led 150ms on/ 150ms off
    Enable_PM_LedBlinking(FWUPGRADE_300MS);//todo:wait for hardware ready

    sprintf(buffer, "nand erase KL");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "nand write.e 0x%X KL 0x%X", (BUF1_ADDR+DECRYPT_KEY_SIZE), KL_SIZE);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "nand erase UBIA");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "ubi part UBIA");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "ubi create RFS 0x%X", RFS_UBI);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "ubi create VEN 0x%X", VEN_UBI);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "ubi write 0x%X RFS 0x%X", (BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE), RFS_SIZE);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "ubi write 0x%X VEN 0x%X", (BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE), VEN_SIZE);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "nand erase.part tee");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "nand write.e 0x%X tee 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE),TEE_SIZE);
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "store_secure_info kernelSign 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+TEE_SIZE+KERNEL_SIGN_SIZE));
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "store_secure_info teeSign  0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+TEE_SIZE+KERNEL_SIGN_SIZE+TEE_SIGN_SIZE));
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "setenv LOAD_NUTTX nand read.e 0x51100000 tee 0x%X\;",TEE_SIZE);
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "setenv BOOT_NUTTX bootNuttx 0xE900000\;");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "saveenv");
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "store_nuttx_config NuttxConfig 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+TEE_SIZE));
    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    free(buffer);

    return 0;
}
#endif

#if (CONFIG_VESTEL_MB100 == 1)
int oad_auto_update(void)
{
    char* buffer=NULL;

    buffer=(char *)malloc(BUF_SIZE);

    if(buffer==NULL)
    {
        printf("no memory for command string!!\n");
        return -1;
    }
    memset(buffer, 0 , BUF_SIZE);

#if defined(CONFIG_TEE)
    //sprintf(buffer, "ext4load mmc 0:8 0x%X /%s 0x%X", BUF1_ADDR,OAD_BIN_FILE, OAD_FILE_SIZE);
    sprintf(buffer, "ext4load mmc 0:8 0x%X /%s 0x%X", BUF1_COMPRESS_ADDR,OAD_BIN_FILE, OAD_FILE_SIZE);
#else
    //sprintf(buffer, "ext4load mmc 0:7 0x%X /%s 0x%X", BUF1_ADDR,OAD_BIN_FILE, OAD_FILE_SIZE);
    sprintf(buffer, "ext4load mmc 0:7 0x%X /%s 0x%X", BUF1_COMPRESS_ADDR,OAD_BIN_FILE, OAD_FILE_SIZE);
#endif

    printf("OAD >> %s \n",buffer);
    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }

    //sprintf(buffer, "aesdec 0x%X 0x%X", BUF1_ADDR, OAD_FILE_SIZE);
    sprintf(buffer, "aesdec 0x%X 0x%X", BUF1_COMPRESS_ADDR, OAD_FILE_SIZE);

    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }

    // Sean test
    sprintf(buffer,"mscompress7 d 0 0x%X 0x%X 0x%X",BUF1_COMPRESS_ADDR,OAD_FILE_SIZE,BUF1_ADDR);

    printf("OAD >> %s \n",buffer);
    if (run_command(buffer, 0) == -1)
    {
        free(buffer);
        return -1;
    }
    // Sean test

    //implement start led 150ms on/ 150ms off
    Enable_PM_LedBlinking(FWUPGRADE_300MS);//todo:wait for hardware ready

    sprintf(buffer, "mmc write.p 0x%X KL 0x%X", (BUF1_ADDR+DECRYPT_KEY_SIZE), KL_SIZE);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "mmc write.p 0x%X RFS 0x%X", (BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE), RFS_SIZE);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "mmc write.p 0x%X VEN 0x%X", (BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE), VEN_SIZE);

    printf("OAD >> %s \n",buffer);
    run_command(buffer, 0);

#if defined(CONFIG_TEE)

    sprintf(buffer, "mmc write.p 0x%X tee 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+CON_SIZE),TEE_SIZE);
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "store_secure_info kernelSign 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+CON_SIZE+TEE_SIZE+NUTTX_CONFIG_SIZE));
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "store_secure_info teeSign 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+CON_SIZE+TEE_SIZE+NUTTX_CONFIG_SIZE+KERNEL_SIGN_SIZE));
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "setenv LOAD_NUTTX mmc read.p 0x50000000 tee 0x%X\;",TEE_SIZE);
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "setenv BOOT_NUTTX bootNuttx 0x10000000\;");
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "saveenv");
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);

    sprintf(buffer, "store_nuttx_config NuttxConfig 0x%X",(BUF1_ADDR+DECRYPT_KEY_SIZE+KL_SIZE+RFS_SIZE+VEN_SIZE+CON_SIZE+TEE_SIZE));
    printf("OAD.TEE_Part >> %s \n",buffer);
    run_command(buffer, 0);
#endif //#if defined(CONFIG_TEE)

    free(buffer);

    return 0;
}
#endif


#endif
void main_loop (void)
{
#ifndef CONFIG_SYS_HUSH_PARSER
	static char lastcommand[CONFIG_SYS_CBSIZE] = { 0, };
	int len;
	int rc = 1;
	int flag;
#endif

#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
	char *s = NULL;
	int bootdelay;
#endif
#ifdef CONFIG_PREBOOT
	char *p = NULL;
#endif
#ifdef CONFIG_BOOTCOUNT_LIMIT
	unsigned long bootcount = 0;
	unsigned long bootlimit = 0;
	char *bcs = NULL;
	char bcs_set[16]={0};
#endif /* CONFIG_BOOTCOUNT_LIMIT */

#ifdef CONFIG_BOOTCOUNT_LIMIT
    bcs = getenv ("bootcount");//bootcount = bootcount_load();
    if(bcs == NULL){
        bcs = "0";
    }
    bootcount = bcs ? simple_strtoul (bcs, NULL, 10) : 0;
    bootcount++;
    //bootcount_store (bootcount);
    sprintf (bcs_set, "%lu", bootcount);
    setenv ("bootcount", bcs_set);
    bcs = getenv ("bootlimit");
    if(bcs == NULL){
        bcs = "5";
        bootlimit = bcs ? simple_strtoul (bcs, NULL, 10) : 0;
        sprintf (bcs_set, "%lu", bootlimit);
        setenv ("bootlimit", bcs_set);
    } else {
        bootlimit = bcs ? simple_strtoul (bcs, NULL, 10) : 0;
    }
    saveenv();
#endif /* CONFIG_BOOTCOUNT_LIMIT */

#ifdef CONFIG_MODEM_SUPPORT
	debug ("DEBUG: main_loop:   do_mdm_init=%d\n", do_mdm_init);
	if (do_mdm_init) {
		char *str = strdup(getenv("mdm_cmd"));
		setenv ("preboot", str);  /* set or delete definition */
		if (str != NULL)
			free (str);
		mdm_init(); /* wait for modem connection */
	}
#endif  /* CONFIG_MODEM_SUPPORT */

#ifdef CONFIG_VERSION_VARIABLE
	{
		extern char version_string[];

		setenv ("ver", version_string);  /* set version variable */
	}
#endif /* CONFIG_VERSION_VARIABLE */

#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))

    bootargs_init();

#endif
#ifdef CONFIG_SYS_HUSH_PARSER
	u_boot_hush_start ();
#endif

#if defined(CONFIG_HUSH_INIT_VAR)
	hush_init_var ();
#endif

#ifdef CONFIG_PREBOOT
	if ((p = getenv ("preboot")) != NULL) {
# ifdef CONFIG_AUTOBOOT_KEYED
		int prev = disable_ctrlc(1);	/* disable Control C checking */
# endif

# ifndef CONFIG_SYS_HUSH_PARSER
		run_command (p, 0);
# else
		parse_string_outer(p, FLAG_PARSE_SEMICOLON |
				    FLAG_EXIT_FROM_LOOP);
# endif

# ifdef CONFIG_AUTOBOOT_KEYED
		disable_ctrlc(prev);	/* restore Control C checking */
# endif
	}
#endif /* CONFIG_PREBOOT */

#if defined(CONFIG_UPDATE_TFTP)
	update_tftp ();
#endif /* CONFIG_UPDATE_TFTP */

#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
	s = getenv ("bootdelay");
	bootdelay = s ? (int)simple_strtol(s, NULL, 10) : CONFIG_BOOTDELAY;

	debug ("### main_loop entered: bootdelay=%d\n\n", bootdelay);

# ifdef CONFIG_BOOT_RETRY_TIME
	init_cmd_timeout ();
# endif	/* CONFIG_BOOT_RETRY_TIME */

#ifdef CONFIG_POST
	if (gd->flags & GD_FLG_POSTFAIL) {
		s = getenv("failbootcmd");
	}
	else
#endif /* CONFIG_POST */
#ifdef CONFIG_BOOTCOUNT_LIMIT
	if (bootlimit && (bootcount > bootlimit)) {
		printf ("Warning: Bootlimit (%u) exceeded. Using altbootcmd.\n",
		        (unsigned)bootlimit);
		run_command ("custar", 0);
		s = getenv ("altbootcmd");
	}
	else
#endif /* CONFIG_BOOTCOUNT_LIMIT */


    #if ENABLE_LOEWE_FADING_ON
        mapi_pm_ForceLogoFadingOn(); //for Loewe only
    #endif

    #if defined( ENABLE_ILLUMINATED_LOGO)
        mapi_pm_IlluminatedLogoFadingOn();
    #endif


    #if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
    #if (CONFIG_VESTEL_MB97 == 1)
    MDrv_SERFLASH_SetMode(FALSE);
    printf("MDrv_SERFLASH_SetMode");
    #endif
    #if defined(CONFIG_CMD_NET)
    #if(CONFIG_VESTEL_MB100 == 1)
    get_mac_address_from_SPI();
    #endif
    #endif
    #endif

		s = getenv ("bootcmd");

	debug ("### main_loop: bootcmd=\"%s\"\n", s ? s : "<UNDEFINED>");
//Mstar Start
    if(FALSE==MstarProcess())
    {
      printf("Error: MstarProcess() \n");
    }
//Mstar End
#if !defined(CONFIG_MSTAR_TOOL_CMDLINE)
	if (bootdelay >= 0 && s && !abortboot (bootdelay)) {
# ifdef CONFIG_AUTOBOOT_KEYED
		int prev = disable_ctrlc(1);	/* disable Control C checking */
# endif
//Mstar Start
    if(FALSE==MstarToKernel())
    {
      printf("Error: MstarToKernel() \n");
    }
     //please add sw upgrade flow here
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
#define IR_POLLING_MAGIC 0xA0
#define IR_POLLING_MAGIC_CLEAR 0xC0
#define IR_POLLING_OK 0x0B
#define REG_IS_OK_KEY 0x1043
#define IR_POLLING_DELAY 10
#define IR_POLLING_EN_MASK  0xF0
#define IR_POLLING_KEY_MASK 0x0F
         //MB100_BRINGUP
        {
            U8 keycode, u8irPolTimeout=0;

            while((ReadByte(REG_IS_OK_KEY)&IR_POLLING_EN_MASK)!=IR_POLLING_MAGIC)
            {
                u8irPolTimeout++;
                mdelay(IR_POLLING_DELAY);
                printf("\033[34m Wait ir magic \n\033[m");
                if(u8irPolTimeout >= 200)
                    break;
            }
            mdelay(IR_POLLING_DELAY);

            keycode = (ReadByte(REG_IS_OK_KEY)&IR_POLLING_KEY_MASK);
            printf("\033[34m IR keycode = 0x%x\n\033[m", keycode);

            if(keycode == IR_POLLING_OK)
            {
                keycode = IR_POLLING_MAGIC_CLEAR;
                WriteByte(REG_IS_OK_KEY , keycode);
                printf("\033[34m IR OK key Pressed\n\033[m");
                if(-1 == check_sw_upgrade())
                {
                    //FAILED
                }
            }
            else
            {
                keycode = IR_POLLING_MAGIC_CLEAR;
                WriteByte(REG_IS_OK_KEY , keycode);
            }
        }

        //CUS08VL spec, OAD update
        if(get_oad_flag()==0x00)
        {
#if (CONFIG_WDT)
    {
                printf("Set WDT TIME TO %d\n",WDT_UPGRADE_TIMEOUT);
        char cmd[CMD_BUF] = {};
        memset(cmd, 0, CMD_BUF);
        snprintf(cmd, CMD_BUF-1, "wdt_enable %d", WDT_UPGRADE_TIMEOUT);
        run_command(cmd, 0);
    }
#endif
			int ret = 0;

            printf("OAD >> Performing OAD update...\n");
            ret = oad_auto_update();
            set_oad_flag(0);
            if(-1 != ret) //if OAD succeeded, set sync_environment flag to 1 and reset
            {
                setenv("sync_environment", "1");
                saveenv();
                printf("OAD >> Resetting TV...\n");
                do_reset (NULL, 0, 0, NULL);
            }
        }
        else
        {
            printf("No OAD...\n");
        }
#if ( CONFIG_VESTEL_MB97 == 1 )
    if ( gb_EnvUpdate == TRUE )
    {
        gb_EnvUpdate = FALSE;
        saveenv_final();
    }
#endif
#endif
#if defined(PCB_WITH_MFC)
    extern void MDrv_Ursa_PNL_ON(void);
#if (CONFIG_VESTEL_MB100 == 1)
    mdelay(WAIT_MFC_ENTER_MAIN_LOOP);// To meet panel power sequence, must call MDrv_Ursa_PNL_ON() here
#endif
    MDrv_Ursa_PNL_ON();
#endif

#if (ENABLE_MODULE_TEE==1) // alway in bottom
        run_command ("SecureBootCmd", 0);
#endif
        s = getenv ("bootcmd");
//Mstar End

# ifndef CONFIG_SYS_HUSH_PARSER
		run_command (s, 0);
# else
		parse_string_outer(s, FLAG_PARSE_SEMICOLON |
				    FLAG_EXIT_FROM_LOOP);
# endif

# ifdef CONFIG_AUTOBOOT_KEYED
		disable_ctrlc(prev);	/* restore Control C checking */
# endif
	}
# endif

# ifdef CONFIG_MENUKEY
	if (menukey == CONFIG_MENUKEY) {
	    s = getenv("menucmd");
	    if (s) {
# ifndef CONFIG_SYS_HUSH_PARSER
		run_command (s, 0);
# else
		parse_string_outer(s, FLAG_PARSE_SEMICOLON |
				    FLAG_EXIT_FROM_LOOP);
# endif
	    }
	}
#endif /* CONFIG_MENUKEY */
#endif /* CONFIG_BOOTDELAY */

	/*
	 * Main Loop for Monitor Command Processing
	 */
#ifdef CONFIG_SYS_HUSH_PARSER
	parse_file_outer();
	/* This point is never reached */
	for (;;);
#else
	for (;;) {
#ifdef CONFIG_BOOT_RETRY_TIME
		if (rc >= 0) {
			/* Saw enough of a valid command to
			 * restart the timeout.
			 */
			reset_cmd_timeout();
		}
#endif
		len = readline (CONFIG_SYS_PROMPT);

		flag = 0;	/* assume no special flags for now */
		if (len > 0)
			strcpy (lastcommand, console_buffer);
		else if (len == 0)
			flag |= CMD_FLAG_REPEAT;
#ifdef CONFIG_BOOT_RETRY_TIME
		else if (len == -2) {
			/* -2 means timed out, retry autoboot
			 */
			puts ("\nTimed out waiting for command\n");
# ifdef CONFIG_RESET_TO_RETRY
			/* Reinit board to run initialization code again */
			do_reset (NULL, 0, 0, NULL);
# else
			return;		/* retry autoboot */
# endif
		}
#endif

		if (len == -1)
			puts ("<INTERRUPT>\n");
		else
			rc = run_command (lastcommand, flag);

		if (rc <= 0) {
			/* invalid command or not repeatable, forget it */
			lastcommand[0] = 0;
		}
	}
#endif /*CONFIG_SYS_HUSH_PARSER*/
}

#ifdef CONFIG_BOOT_RETRY_TIME
/***************************************************************************
 * initialize command line timeout
 */
void init_cmd_timeout(void)
{
	char *s = getenv ("bootretry");

	if (s != NULL)
		retry_time = (int)simple_strtol(s, NULL, 10);
	else
		retry_time =  CONFIG_BOOT_RETRY_TIME;

	if (retry_time >= 0 && retry_time < CONFIG_BOOT_RETRY_MIN)
		retry_time = CONFIG_BOOT_RETRY_MIN;
}

/***************************************************************************
 * reset command line timeout to retry_time seconds
 */
void reset_cmd_timeout(void)
{
	endtime = endtick(retry_time);
}
#endif

#ifdef CONFIG_CMDLINE_EDITING

/*
 * cmdline-editing related codes from vivi.
 * Author: Janghoon Lyu <nandy@mizi.com>
 */

#define putnstr(str,n)	do {			\
		printf ("%.*s", (int)n, str);	\
	} while (0)

#define CTL_CH(c)		((c) - 'a' + 1)
#define CTL_BACKSPACE		('\b')
#define DEL			((char)255)
#define DEL7			((char)127)
#define CREAD_HIST_CHAR		('!')

#define getcmd_putch(ch)	putc(ch)
#define getcmd_getch()		getc()
#define getcmd_cbeep()		getcmd_putch('\a')

#define HIST_MAX		20
#define HIST_SIZE		CONFIG_SYS_CBSIZE

static int hist_max = 0;
static int hist_add_idx = 0;
static int hist_cur = -1;
unsigned hist_num = 0;

char* hist_list[HIST_MAX];
char hist_lines[HIST_MAX][HIST_SIZE + 1];	 /* Save room for NULL */

#define add_idx_minus_one() ((hist_add_idx == 0) ? hist_max : hist_add_idx-1)

static void hist_init(void)
{
	int i;

	hist_max = 0;
	hist_add_idx = 0;
	hist_cur = -1;
	hist_num = 0;

	for (i = 0; i < HIST_MAX; i++) {
		hist_list[i] = hist_lines[i];
		hist_list[i][0] = '\0';
	}
}

static void cread_add_to_hist(char *line)
{
	strcpy(hist_list[hist_add_idx], line);

	if (++hist_add_idx >= HIST_MAX)
		hist_add_idx = 0;

	if (hist_add_idx > hist_max)
		hist_max = hist_add_idx;

	hist_num++;
}

static char* hist_prev(void)
{
	char *ret;
	int old_cur;

	if (hist_cur < 0)
		return NULL;

	old_cur = hist_cur;
	if (--hist_cur < 0)
		hist_cur = hist_max;

	if (hist_cur == hist_add_idx) {
		hist_cur = old_cur;
		ret = NULL;
	} else
		ret = hist_list[hist_cur];

	return (ret);
}

static char* hist_next(void)
{
	char *ret;

	if (hist_cur < 0)
		return NULL;

	if (hist_cur == hist_add_idx)
		return NULL;

	if (++hist_cur > hist_max)
		hist_cur = 0;

	if (hist_cur == hist_add_idx) {
		ret = "";
	} else
		ret = hist_list[hist_cur];

	return (ret);
}

#ifndef CONFIG_CMDLINE_EDITING
static void cread_print_hist_list(void)
{
	int i;
	unsigned long n;

	n = hist_num - hist_max;

	i = hist_add_idx + 1;
	while (1) {
		if (i > hist_max)
			i = 0;
		if (i == hist_add_idx)
			break;
		printf("%s\n", hist_list[i]);
		n++;
		i++;
	}
}
#endif /* CONFIG_CMDLINE_EDITING */

#define BEGINNING_OF_LINE() {			\
	while (num) {				\
		getcmd_putch(CTL_BACKSPACE);	\
		num--;				\
	}					\
}

#define ERASE_TO_EOL() {				\
	if (num < eol_num) {				\
		printf("%*s", (int)(eol_num - num), ""); \
		do {					\
			getcmd_putch(CTL_BACKSPACE);	\
		} while (--eol_num > num);		\
	}						\
}

#define REFRESH_TO_EOL() {			\
	if (num < eol_num) {			\
		wlen = eol_num - num;		\
		putnstr(buf + num, wlen);	\
		num = eol_num;			\
	}					\
}

static void cread_add_char(char ichar, int insert, unsigned long *num,
	       unsigned long *eol_num, char *buf, unsigned long len)
{
	unsigned long wlen;

	/* room ??? */
	if (insert || *num == *eol_num) {
		if (*eol_num > len - 1) {
			getcmd_cbeep();
			return;
		}
		(*eol_num)++;
	}

	if (insert) {
		wlen = *eol_num - *num;
		if (wlen > 1) {
			memmove(&buf[*num+1], &buf[*num], wlen-1);
		}

		buf[*num] = ichar;
		putnstr(buf + *num, wlen);
		(*num)++;
		while (--wlen) {
			getcmd_putch(CTL_BACKSPACE);
		}
	} else {
		/* echo the character */
		wlen = 1;
		buf[*num] = ichar;
		putnstr(buf + *num, wlen);
		(*num)++;
	}
}

static void cread_add_str(char *str, int strsize, int insert, unsigned long *num,
	      unsigned long *eol_num, char *buf, unsigned long len)
{
	while (strsize--) {
		cread_add_char(*str, insert, num, eol_num, buf, len);
		str++;
	}
}

static int cread_line(const char *const prompt, char *buf, unsigned int *len)
{
	unsigned long num = 0;
	unsigned long eol_num = 0;
	unsigned long wlen;
	char ichar;
	int insert = 1;
	int esc_len = 0;
	char esc_save[8];
	int init_len = strlen(buf);

	if (init_len)
		cread_add_str(buf, init_len, 1, &num, &eol_num, buf, *len);

	while (1) {
#ifdef CONFIG_BOOT_RETRY_TIME
		while (!tstc()) {	/* while no incoming data */
			if (retry_time >= 0 && get_ticks() > endtime)
				return (-2);	/* timed out */
			WATCHDOG_RESET();
		}
#endif

		ichar = getcmd_getch();

		if ((ichar == '\n') || (ichar == '\r')) {
			putc('\n');
			break;
		}

		/*
		 * handle standard linux xterm esc sequences for arrow key, etc.
		 */
		if (esc_len != 0) {
			if (esc_len == 1) {
				if (ichar == '[') {
					esc_save[esc_len] = ichar;
					esc_len = 2;
				} else {
					cread_add_str(esc_save, esc_len, insert,
						      &num, &eol_num, buf, *len);
					esc_len = 0;
				}
				continue;
			}

			switch (ichar) {

			case 'D':	/* <- key */
				ichar = CTL_CH('b');
				esc_len = 0;
				break;
			case 'C':	/* -> key */
				ichar = CTL_CH('f');
				esc_len = 0;
				break;	/* pass off to ^F handler */
			case 'H':	/* Home key */
				ichar = CTL_CH('a');
				esc_len = 0;
				break;	/* pass off to ^A handler */
			case 'A':	/* up arrow */
				ichar = CTL_CH('p');
				esc_len = 0;
				break;	/* pass off to ^P handler */
			case 'B':	/* down arrow */
				ichar = CTL_CH('n');
				esc_len = 0;
				break;	/* pass off to ^N handler */
			default:
				esc_save[esc_len++] = ichar;
				cread_add_str(esc_save, esc_len, insert,
					      &num, &eol_num, buf, *len);
				esc_len = 0;
				continue;
			}
		}

		switch (ichar) {
		case 0x1b:
			if (esc_len == 0) {
				esc_save[esc_len] = ichar;
				esc_len = 1;
			} else {
				puts("impossible condition #876\n");
				esc_len = 0;
			}
			break;

		case CTL_CH('a'):
			BEGINNING_OF_LINE();
			break;
		case CTL_CH('c'):	/* ^C - break */
			*buf = '\0';	/* discard input */
			return (-1);
		case CTL_CH('f'):
			if (num < eol_num) {
				getcmd_putch(buf[num]);
				num++;
			}
			break;
		case CTL_CH('b'):
			if (num) {
				getcmd_putch(CTL_BACKSPACE);
				num--;
			}
			break;
		case CTL_CH('d'):
			if (num < eol_num) {
				wlen = eol_num - num - 1;
				if (wlen) {
					memmove(&buf[num], &buf[num+1], wlen);
					putnstr(buf + num, wlen);
				}

				getcmd_putch(' ');
				do {
					getcmd_putch(CTL_BACKSPACE);
				} while (wlen--);
				eol_num--;
			}
			break;
		case CTL_CH('k'):
			ERASE_TO_EOL();
			break;
		case CTL_CH('e'):
			REFRESH_TO_EOL();
			break;
		case CTL_CH('o'):
			insert = !insert;
			break;
		case CTL_CH('x'):
		case CTL_CH('u'):
			BEGINNING_OF_LINE();
			ERASE_TO_EOL();
			break;
		case DEL:
		case DEL7:
		case 8:
			if (num) {
				wlen = eol_num - num;
				num--;
				memmove(&buf[num], &buf[num+1], wlen);
				getcmd_putch(CTL_BACKSPACE);
				putnstr(buf + num, wlen);
				getcmd_putch(' ');
				do {
					getcmd_putch(CTL_BACKSPACE);
				} while (wlen--);
				eol_num--;
			}
			break;
		case CTL_CH('p'):
		case CTL_CH('n'):
		{
			char * hline;

			esc_len = 0;

			if (ichar == CTL_CH('p'))
				hline = hist_prev();
			else
				hline = hist_next();

			if (!hline) {
				getcmd_cbeep();
				continue;
			}

			/* nuke the current line */
			/* first, go home */
			BEGINNING_OF_LINE();

			/* erase to end of line */
			ERASE_TO_EOL();

			/* copy new line into place and display */
			strcpy(buf, hline);
			eol_num = strlen(buf);
			REFRESH_TO_EOL();
			continue;
		}
#ifdef CONFIG_AUTO_COMPLETE
		case '\t': {
			int num2, col;

			/* do not autocomplete when in the middle */
			if (num < eol_num) {
				getcmd_cbeep();
				break;
			}

			buf[num] = '\0';
			col = strlen(prompt) + eol_num;
			num2 = num;
			if (cmd_auto_complete(prompt, buf, &num2, &col)) {
				col = num2 - num;
				num += col;
				eol_num += col;
			}
			break;
		}
#endif
		default:
			cread_add_char(ichar, insert, &num, &eol_num, buf, *len);
			break;
		}
	}
	*len = eol_num;
	buf[eol_num] = '\0';	/* lose the newline */

	if (buf[0] && buf[0] != CREAD_HIST_CHAR)
		cread_add_to_hist(buf);
	hist_cur = hist_add_idx;

	return 0;
}

#endif /* CONFIG_CMDLINE_EDITING */

/****************************************************************************/

/*
 * Prompt for input and read a line.
 * If  CONFIG_BOOT_RETRY_TIME is defined and retry_time >= 0,
 * time out when time goes past endtime (timebase time in ticks).
 * Return:	number of read characters
 *		-1 if break
 *		-2 if timed out
 */
int readline (const char *const prompt)
{
	/*
	 * If console_buffer isn't 0-length the user will be prompted to modify
	 * it instead of entering it from scratch as desired.
	 */
	console_buffer[0] = '\0';

	return readline_into_buffer(prompt, console_buffer);
}


int readline_into_buffer (const char *const prompt, char * buffer)
{
	char *p = buffer;
#ifdef CONFIG_CMDLINE_EDITING
	unsigned int len = CONFIG_SYS_CBSIZE;
	int rc;
	static int initted = 0;

	/*
	 * History uses a global array which is not
	 * writable until after relocation to RAM.
	 * Revert to non-history version if still
	 * running from flash.
	 */
	if (gd->flags & GD_FLG_RELOC) {
		if (!initted) {
			hist_init();
			initted = 1;
		}

		if (prompt)
			puts (prompt);

		rc = cread_line(prompt, p, &len);
		return rc < 0 ? rc : len;

	} else {
#endif	/* CONFIG_CMDLINE_EDITING */
	char * p_buf = p;
	int	n = 0;				/* buffer index		*/
	int	plen = 0;			/* prompt length	*/
	int	col;				/* output column cnt	*/
	char	c;

	/* print prompt */
	if (prompt) {
		plen = strlen (prompt);
		puts (prompt);
	}
	col = plen;

	for (;;) {
#ifdef CONFIG_BOOT_RETRY_TIME
		while (!tstc()) {	/* while no incoming data */
			if (retry_time >= 0 && get_ticks() > endtime)
				return (-2);	/* timed out */
			WATCHDOG_RESET();
		}
#endif
		WATCHDOG_RESET();		/* Trigger watchdog, if needed */

#ifdef CONFIG_SHOW_ACTIVITY
		while (!tstc()) {
			extern void show_activity(int arg);
			show_activity(0);
			WATCHDOG_RESET();
		}
#endif
		c = getc();

		/*
		 * Special character handling
		 */
		switch (c) {
		case '\r':				/* Enter		*/
		case '\n':
			*p = '\0';
			puts ("\r\n");
			return (p - p_buf);

		case '\0':				/* nul			*/
			continue;

		case 0x03:				/* ^C - break		*/
			p_buf[0] = '\0';	/* discard input */
			return (-1);

		case 0x15:				/* ^U - erase line	*/
			while (col > plen) {
				puts (erase_seq);
				--col;
			}
			p = p_buf;
			n = 0;
			continue;

		case 0x17:				/* ^W - erase word	*/
			p=delete_char(p_buf, p, &col, &n, plen);
			while ((n > 0) && (*p != ' ')) {
				p=delete_char(p_buf, p, &col, &n, plen);
			}
			continue;

		case 0x08:				/* ^H  - backspace	*/
		case 0x7F:				/* DEL - backspace	*/
			p=delete_char(p_buf, p, &col, &n, plen);
			continue;

		default:
			/*
			 * Must be a normal character then
			 */
			if (n < CONFIG_SYS_CBSIZE-2) {
				if (c == '\t') {	/* expand TABs		*/
#ifdef CONFIG_AUTO_COMPLETE
					/* if auto completion triggered just continue */
					*p = '\0';
					if (cmd_auto_complete(prompt, console_buffer, &n, &col)) {
						p = p_buf + n;	/* reset */
						continue;
					}
#endif
					puts (tab_seq+(col&07));
					col += 8 - (col&07);
				} else {
					++col;		/* echo input		*/
					putc (c);
				}
				*p++ = c;
				++n;
			} else {			/* Buffer full		*/
				putc ('\a');
			}
		}
	}
#ifdef CONFIG_CMDLINE_EDITING
	}
#endif
}

/****************************************************************************/

static char * delete_char (char *buffer, char *p, int *colp, int *np, int plen)
{
	char *s;

	if (*np == 0) {
		return (p);
	}

	if (*(--p) == '\t') {			/* will retype the whole line	*/
		while (*colp > plen) {
			puts (erase_seq);
			(*colp)--;
		}
		for (s=buffer; s<p; ++s) {
			if (*s == '\t') {
				puts (tab_seq+((*colp) & 07));
				*colp += 8 - ((*colp) & 07);
			} else {
				++(*colp);
				putc (*s);
			}
		}
	} else {
		puts (erase_seq);
		(*colp)--;
	}
	(*np)--;
	return (p);
}

/****************************************************************************/

int parse_line (char *line, char *argv[])
{
	int nargs = 0;

#ifdef DEBUG_PARSER
	printf ("parse_line: \"%s\"\n", line);
#endif
	while (nargs < CONFIG_SYS_MAXARGS) {

		/* skip any white space */
		while ((*line == ' ') || (*line == '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
		printf ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		argv[nargs++] = line;	/* begin of argument string	*/

		/* find end of string */
		while (*line && (*line != ' ') && (*line != '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
		printf ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		*line++ = '\0';		/* terminate current arg	 */
	}

	printf ("** Too many args (max. %d) **\n", CONFIG_SYS_MAXARGS);

#ifdef DEBUG_PARSER
	printf ("parse_line: nargs=%d\n", nargs);
#endif
	return (nargs);
}

/****************************************************************************/

static void process_macros (const char *input, char *output)
{
	char c, prev;
	const char *varname_start = NULL;
	int inputcnt = strlen (input);
	int outputcnt = CONFIG_SYS_CBSIZE;
	int state = 0;		/* 0 = waiting for '$'  */

	/* 1 = waiting for '(' or '{' */
	/* 2 = waiting for ')' or '}' */
	/* 3 = waiting for '''  */
#ifdef DEBUG_PARSER
	char *output_start = output;

	printf ("[PROCESS_MACROS] INPUT len %d: \"%s\"\n", strlen (input),
		input);
#endif

	prev = '\0';		/* previous character   */

	while (inputcnt && outputcnt) {
		c = *input++;
		inputcnt--;

		if (state != 3) {
			/* remove one level of escape characters */
			if ((c == '\\') && (prev != '\\')) {
				if (inputcnt-- == 0)
					break;
				prev = c;
				c = *input++;
			}
		}

		switch (state) {
		case 0:	/* Waiting for (unescaped) $    */
			if ((c == '\'') && (prev != '\\')) {
				state = 3;
				break;
			}
			if ((c == '$') && (prev != '\\')) {
				state++;
			} else {
				*(output++) = c;
				outputcnt--;
			}
			break;
		case 1:	/* Waiting for (        */
			if (c == '(' || c == '{') {
				state++;
				varname_start = input;
			} else {
				state = 0;
				*(output++) = '$';
				outputcnt--;

				if (outputcnt) {
					*(output++) = c;
					outputcnt--;
				}
			}
			break;
		case 2:	/* Waiting for )        */
			if (c == ')' || c == '}') {
				int i;
				char envname[CONFIG_SYS_CBSIZE], *envval;
				int envcnt = input - varname_start - 1;	/* Varname # of chars */

				/* Get the varname */
				for (i = 0; i < envcnt; i++) {
					envname[i] = varname_start[i];
				}
				envname[i] = 0;

				/* Get its value */
				envval = getenv (envname);

				/* Copy into the line if it exists */
				if (envval != NULL)
					while ((*envval) && outputcnt) {
						*(output++) = *(envval++);
						outputcnt--;
					}
				/* Look for another '$' */
				state = 0;
			}
			break;
		case 3:	/* Waiting for '        */
			if ((c == '\'') && (prev != '\\')) {
				state = 0;
			} else {
				*(output++) = c;
				outputcnt--;
			}
			break;
		}
		prev = c;
	}

	if (outputcnt)
		*output = 0;
	else
		*(output - 1) = 0;

#ifdef DEBUG_PARSER
	printf ("[PROCESS_MACROS] OUTPUT len %d: \"%s\"\n",
		strlen (output_start), output_start);
#endif
}

/****************************************************************************
 * returns:
 *	1  - command executed, repeatable
 *	0  - command executed but not repeatable, interrupted commands are
 *	     always considered not repeatable
 *	-1 - not executed (unrecognized, bootd recursion or too many args)
 *           (If cmd is NULL or "" or longer than CONFIG_SYS_CBSIZE-1 it is
 *           considered unrecognized)
 *
 * WARNING:
 *
 * We must create a temporary copy of the command since the command we get
 * may be the result from getenv(), which returns a pointer directly to
 * the environment data, which may change magicly when the command we run
 * creates or modifies environment variables (like "bootp" does).
 */

int run_command (const char *cmd, int flag)
{
	cmd_tbl_t *cmdtp;
	char cmdbuf[CONFIG_SYS_CBSIZE]={0};	/* working copy of cmd		*/
	char *token;			/* start of token in cmdbuf	*/
	char *sep;			/* end of token (separator) in cmdbuf */
	char finaltoken[CONFIG_SYS_CBSIZE]={0};
	char *str = cmdbuf;
	char *argv[CONFIG_SYS_MAXARGS + 1];	/* NULL terminated	*/
	int argc, inquotes;
	int repeatable = 1;
	int rc = 0;

#ifdef DEBUG_PARSER
	printf ("[RUN_COMMAND] cmd[%p]=\"", cmd);
	puts (cmd ? cmd : "NULL");	/* use puts - string may be loooong */
	puts ("\"\n");
#endif

	clear_ctrlc();		/* forget any previous Control C */

	if (!cmd || !*cmd) {
		return -1;	/* empty command */
	}

	if (strlen(cmd) >= CONFIG_SYS_CBSIZE) {
		puts ("## Command too long!\n");
		return -1;
	}

	strcpy (cmdbuf, cmd);

	/* Process separators and check for invalid
	 * repeatable commands
	 */

#ifdef DEBUG_PARSER
	printf ("[PROCESS_SEPARATORS] %s\n", cmd);
#endif
	while (*str) {

		/*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
		for (inquotes = 0, sep = str; *sep; sep++) {
			if ((*sep=='\'') &&
			    (*(sep-1) != '\\'))
				inquotes=!inquotes;

			if (!inquotes &&
			    (*sep == ';') &&	/* separator		*/
			    ( sep != str) &&	/* past string start	*/
			    (*(sep-1) != '\\'))	/* and NOT escaped	*/
				break;
		}

		/*
		 * Limit the token to data between separators
		 */
		token = str;
		if (*sep) {
			str = sep + 1;	/* start of command for next pass */
			*sep = '\0';
		}
		else
			str = sep;	/* no more commands for next pass */
#ifdef DEBUG_PARSER
		printf ("token: \"%s\"\n", token);
#endif

		/* find macros in this token and replace them */
		process_macros (token, finaltoken);

		/* Extract arguments */
		if ((argc = parse_line (finaltoken, argv)) == 0) {
			rc = -1;	/* no command at all */
			continue;
		}

		/* Look up command in command table */
		if ((cmdtp = find_cmd(argv[0])) == NULL) {
			printf ("Unknown command '%s' - try 'help'\n", argv[0]);
			rc = -1;	/* give up after bad command */
			continue;
		}

		/* found - check max args */
		if (argc > cmdtp->maxargs) {
			cmd_usage(cmdtp);
			rc = -1;
			continue;
		}

#if defined(CONFIG_CMD_BOOTD)
		/* avoid "bootd" recursion */
		if (cmdtp->cmd == do_bootd) {
#ifdef DEBUG_PARSER
			printf ("[%s]\n", finaltoken);
#endif
			if (flag & CMD_FLAG_BOOTD) {
				puts ("'bootd' recursion detected\n");
				rc = -1;
				continue;
			} else {
				flag |= CMD_FLAG_BOOTD;
			}
		}
#endif

		/* OK - call function to do the command */
		if ((cmdtp->cmd) (cmdtp, flag, argc, argv) != 0) {
			rc = -1;
		}

		repeatable &= cmdtp->repeatable;

		/* Did the user stop this? */
		if (had_ctrlc ())
			return -1;	/* if stopped then not repeatable */
	}

	return rc ? rc : 0;
}

/****************************************************************************/

#if defined(CONFIG_CMD_RUN)
int do_run (cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	int i;

	if (argc < 2)
		return cmd_usage(cmdtp);

	for (i=1; i<argc; ++i) {
		char *arg;

		if ((arg = getenv (argv[i])) == NULL) {
			printf ("## Error: \"%s\" not defined\n", argv[i]);
			return 1;
		}
#ifndef CONFIG_SYS_HUSH_PARSER
		if (run_command (arg, flag) == -1)
			return 1;
#else
		if (parse_string_outer(arg,
		    FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
			return 1;
#endif
	}
	return 0;
}
#endif
#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))
extern int eth_initialize(bd_t *bis);

int get_mac_address_from_SPI(void)
{
    char mac_address_buf[SPI_MAP_MAC_SIZE+1];
    const char *pEthaddr;

    MDrv_SERFLASH_Read((MS_U32)(SPI_MAP_BASE_ADDR+SPI_MAP_MAC_ADDR), (MS_U32)SPI_MAP_MAC_SIZE, (MS_U8 *)mac_address_buf);

    printf("MAC address= %lx \n",(SPI_MAP_BASE_ADDR+SPI_MAP_MAC_ADDR));

    pEthaddr = getenv("macaddr");

    if(pEthaddr!=NULL)
    {
        printf("Existing ethaddr=%s\n",pEthaddr);
        if(!strncmp(pEthaddr,mac_address_buf,18))
            return 0;// same MAC, do nothing
    }

    if(mac_address_buf[2]!=':')
    {
        printf("Wrong MAC in SPI\n");
        return 0;// Wrong MAC, do nothing
    }

    mac_address_buf[SPI_MAP_MAC_SIZE] = 0x00; // string ending protection
    setenv("macaddr", mac_address_buf);
    saveenv();
    pEthaddr = getenv("macaddr");
    printf("New macaddr=%s\n",pEthaddr);
    eth_initialize(gd->bd);
    return 0;
}

int get_IR_Type_from_SPI(void)
{
#define IR_SWITCH_PROTOCOL 0x1040

    char ir_buf[SPI_MAP_RC_SIZE+1];

    MDrv_SERFLASH_Read((MS_U32)(SPI_MAP_BASE_ADDR+SPI_MAP_RC_ADDR), (MS_U32)SPI_MAP_RC_SIZE, (MS_U8 *)ir_buf);

    printf("RC type offset = 0x%lx, type = 0x%x \n",(SPI_MAP_BASE_ADDR+SPI_MAP_RC_ADDR), ir_buf[0]);

    switch(ir_buf[0])
    {
        default:
        case eIR_RC5:
            WriteByte(IR_SWITCH_PROTOCOL, E_IR_RC5);
            break;
        case eIR_NEC:
            WriteByte(IR_SWITCH_PROTOCOL, E_IR_CUS22T_HW);
            break;
        case eIR_PANASONIC:
            WriteByte(IR_SWITCH_PROTOCOL, E_IR_PANASONIC);
            break;
    }
    return 0;

}

void main_set_uart_status()
{
    MS_U8 u8EnableUart[SPI_MAP_ENABLE_UART_RX_SIZE+1] = {0xFF};
    MS_U16 u16UartConfig;
    MDrv_SERFLASH_Read((MS_U32)(SPI_MAP_BASE_ADDR+SPI_MAP_ENABLE_UART_RX_ADDR), (MS_U32)SPI_MAP_ENABLE_UART_RX_SIZE, (MS_U8 *)u8EnableUart);
    printf("uart spi offset = 0x%lx, value = 0x%x\n", (SPI_MAP_BASE_ADDR+SPI_MAP_ENABLE_UART_RX_ADDR), u8EnableUart[0]);
    if(u8EnableUart[0] == 0x00)
    {
        printf("\033[34mUART Disabled\n\033[m");

        //Make DDC output Disable
        //WriteByte(0x0494, 0x80);

        //Disable UART Rx via PAD_DDCA for dig_mux
        u16UartConfig = Read2Byte(0x0E12);
        u16UartConfig &= ~0x1800;
        Write2Byte(0x0E12 , u16UartConfig);

        //un Select UART0 source to PIU UART0 
        u16UartConfig = Read2Byte(0x101EA6);
        u16UartConfig |= 0x000F; //u16UartConfig &= ~0x0004;
        Write2Byte(0x101EA6 , u16UartConfig);

        //clear TX/RX fifo 
        Write2Byte(0x100988, 0x0000); //0x0988
        Write2Byte(0x100988, 0x0007); //0x0988

        //abort console
        uartEn = 0;
    }else
    {
        //Make DDC output Disable
        //WriteByte(0x0494, 0xA2);
        uartEn = 1;
    }
}

int bootargs_init(void)
{
    const char *bootargs;
    bootargs = getenv("bootargs");
    if(bootargs)
    {
        char bootarg_concat[500];
        char* cVerChk;
        strcpy(bootarg_concat, bootargs);
        cVerChk = strstr(bootarg_concat , "MBOOT_VER=");
        if(cVerChk==0)
        {
            strcat(bootarg_concat, " ");
            strcat(bootarg_concat, mboot_version);
            setenv("bootargs", bootarg_concat);
            saveenv();
        }
        else
        {
            char* cVerNumChk;
            int i=0;
            memcpy(cVerNumChk ,(cVerChk+((sizeof(MBOOT_VERSION_HEADER)/sizeof(char))-1)),((sizeof(MBOOT_VERSION_NUMBER)/sizeof(char))-1));
#if (CONFIG_VESTEL_MB97 != 1)
            if (!(memcmp(cVerNumChk,MBOOT_VERSION_NUMBER,((sizeof(MBOOT_VERSION_NUMBER)/sizeof(char))-1))))
            {
                 printf("Romboot same version \n");
            }
            else
#endif
            {
                for(i=0;i<(((sizeof(MBOOT_VERSION_HEADER)+sizeof(MBOOT_VERSION_NUMBER))/sizeof(char))-2);i++)
                {
                    bootarg_concat[cVerChk-bootarg_concat+i]=*(mboot_version+i);
                }
                setenv("bootargs", bootarg_concat);
                saveenv();
            }

        }
    }
    }

#endif
