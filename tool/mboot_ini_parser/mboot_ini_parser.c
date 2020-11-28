#include <stdio.h>
#include <string.h>

#include "iniparser.h"
#include "mboot_ini_parser.h"

#define INI_PARSER_DEBUG(x)		//x

// store config function
static void parse_mboot_config(dictionary *ini, st_mboot_config *config);
static int store_boottopm_config(dictionary *ini, st_mboot_config *config);
static int store_flashwp_config(dictionary *ini, st_mboot_config *config);
static int store_dbtable_config(dictionary *ini, st_mboot_config *config);
static int store_keypad_config(dictionary *ini, st_mboot_config *config);
static int store_bootcheck_config(dictionary *ini, st_mboot_config *config);
static int store_bootlogo_config(dictionary *ini, st_mboot_config *config);
static int store_bootmusic_config(dictionary *ini, st_mboot_config *config);
static int store_osd_config(dictionary *ini, st_mboot_config *config);
static int store_usbupgrade_config(dictionary *ini, st_mboot_config *config);
static int store_mmap_config(dictionary *ini, st_mboot_config *config);
static int store_ursa_config(dictionary *ini, st_mboot_config *config);
static int store_ethcheck_config(dictionary *ini, st_mboot_config *config);

// dump config function
static void dump_boottopm_config(const st_mboot_config *config);
static void dump_flashwp_config(const st_mboot_config *config);
static void dump_dbtable_config(const st_mboot_config *config);
static void dump_keypad_config(const st_mboot_config *config);
static void dump_bootcheck_config(const st_mboot_config *config);
static void dump_bootlogo_config(const st_mboot_config *config);
static void dump_bootmusic_config(const st_mboot_config *config);
static void dump_osd_config(const st_mboot_config *config);
static void dump_usbupgrade_config(const st_mboot_config *config);
static void dump_mmap_config(const st_mboot_config *config);
static void dump_ursa_config(const st_mboot_config *config);
static void dump_ethcheck_config(const st_mboot_config *config);

// static function implementation
static int store_boottopm_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;
	int i;

	options = iniparser_getseckeys(ini, "boottopm");
	if(NULL == options)
	{
		printf_red("Cannot parse BootToPM, please check it\n");
		return -1;
	}

	config->pm_wakeup_source = 0x00;
	for(i = 0; i < NUMBER_OF_PM_WAKEUP_SOURCE; i++)
	{
		config->pm_wakeup_source |= (U16)iniparser_getint(ini, options[i], notfound);
		config->pm_wakeup_source <<= 1;
	}
	config->pm_wakeup_source >>= 1;

	config->pm_wakeup_keycode1   =  (U8)iniparser_getint(ini, options[NUMBER_OF_PM_WAKEUP_SOURCE+0], notfound);
	config->pm_wakeup_keycode2   =  (U8)iniparser_getint(ini, options[NUMBER_OF_PM_WAKEUP_SOURCE+1], notfound);
	config->pm_ir_headcode0      =  (U8)iniparser_getint(ini, options[NUMBER_OF_PM_WAKEUP_SOURCE+2], notfound);
	config->pm_ir_headcode1      =  (U8)iniparser_getint(ini, options[NUMBER_OF_PM_WAKEUP_SOURCE+3], notfound);
	return 0;
}

static int store_flashwp_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;

	options = iniparser_getseckeys(ini, "flashwp");
	if(NULL == options)
	{
		printf_red("Cannot parse FlashWP, please check it\n");
		return -1;
	}	
	config->pin_flash_wp0 = (U8)iniparser_getint(ini, options[0], notfound);
	config->pin_flash_wp1 = (U8)iniparser_getint(ini, options[1], notfound);
	return 0;
}

static int store_dbtable_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	char *def;

	options = iniparser_getseckeys(ini, "dbtable");
	if(NULL == options)
	{
		printf_red("Cannot parse DBTable, please check it\n");
		return -1;
	}
	memcpy(config->ubipart            ,  iniparser_getstring(ini, options[0], def),  MAX_STRING_LENGTH);
	memcpy(config->config_partition   ,  iniparser_getstring(ini, options[1], def),  MAX_STRING_LENGTH);
	memcpy(config->customer_partition ,  iniparser_getstring(ini, options[2], def),  MAX_STRING_LENGTH);
	memcpy(config->config_path        ,  iniparser_getstring(ini, options[3], def),  MAX_STRING_LENGTH);
	memcpy(config->customer_path      ,  iniparser_getstring(ini, options[4], def),  MAX_STRING_LENGTH);
	return 0;
}

static int store_keypad_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;
	int i_level;

	options = iniparser_getseckeys(ini, "keypadconfig");
	if(NULL == options)
	{
		printf_red("Cannot parse KeypadConfig, please check it\n");
		return -1;
	}
	config->adc_key_level_num = (U8)iniparser_getint(ini, options[0], notfound);
	for(i_level = 0; i_level < NUMBER_OF_KEYPAD_ADC_LEVEL; i_level++)
	{
		config->adc_key_level[i_level] = (U8)iniparser_getint(ini, options[i_level+1], notfound);
	}
	return 0;
}

static int store_bootcheck_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;

	options = iniparser_getseckeys(ini, "bootcheck");
	if(NULL == options)
	{
		printf_red("Cannot parse BootCheck, please check it\n");
		return -1;
	}
	config->ir_recovery_key          =  (U8)iniparser_getint(ini, options[0], notfound);
	config->ir_force_upgrade_key     =  (U8)iniparser_getint(ini, options[1], notfound);
	config->ir_uart_onoff_key        =  (U8)iniparser_getint(ini, options[2], notfound);
	config->keypad_recovery_key      =  (U8)iniparser_getint(ini, options[3], notfound);
	config->keypad_force_upgrade_key =  (U8)iniparser_getint(ini, options[4], notfound);
	config->keypad_uart_onoff_key    =  (U8)iniparser_getint(ini, options[5], notfound);
	return 0;
}

static int store_bootlogo_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	char *def;

	options = iniparser_getseckeys(ini, "bootlogo");
	if(NULL == options)
	{
		printf_red("Cannot parse BootLogo, please check it\n");
		return -1;
	}
	memcpy(config->boot_logo_partition ,  iniparser_getstring(ini, options[0], def),  MAX_STRING_LENGTH);
	memcpy(config->boot_logo_path      ,  iniparser_getstring(ini, options[1], def),  MAX_STRING_LENGTH);
	memcpy(config->boot_logo_file      ,  iniparser_getstring(ini, options[2], def),  MAX_STRING_LENGTH);
	return 0;
}

static int store_bootmusic_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	char *def;

	options = iniparser_getseckeys(ini, "bootmusic");
	if(NULL == options)
	{
		printf_red("Cannot parse BootMusic, please check it\n");
		return -1;
	}
	memcpy(config->boot_music_partition ,  iniparser_getstring(ini, options[0], def),  MAX_STRING_LENGTH);
	memcpy(config->boot_music_path      ,  iniparser_getstring(ini, options[1], def),  MAX_STRING_LENGTH);
	memcpy(config->boot_music_file      ,  iniparser_getstring(ini, options[2], def),  MAX_STRING_LENGTH);
	return 0;
}

static int store_osd_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;
	char *def;

	options = iniparser_getseckeys(ini, "osd");
	if(NULL == options)
	{
		printf_red("Cannot parse OSD, please check it\n");
		return -1;
	}
	config->default_osd_layer_width  =  (U32)iniparser_getint(ini, options[0], notfound);
	config->default_osd_layer_height =  (U32)iniparser_getint(ini, options[1], notfound);
	config->default_osd_attrib		 =  (U16)iniparser_getint(ini, options[2], notfound);
	config->default_osd_color		 =  (U8) iniparser_getint(ini, options[3], notfound);
	config->default_osd_string_x     =  (U8) iniparser_getint(ini, options[4], notfound);
	config->default_osd_string_y     =  (U8) iniparser_getint(ini, options[5], notfound);
	memcpy(config->default_osd_string_tips     ,  iniparser_getstring(ini, options[6], def),  MAX_STRING_LENGTH);
	memcpy(config->default_osd_background_path ,  iniparser_getstring(ini, options[7], def),  MAX_STRING_LENGTH);
	return 0;
}

static int store_usbupgrade_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	char *def;

	options = iniparser_getseckeys(ini, "usbupgrade");
	if(NULL == options)
	{
		printf_red("Cannot parse USBUpgrade, please check it\n");
		return -1;
	}
	memcpy(config->default_oad_bin_path   ,  iniparser_getstring(ini, options[0], def),  MAX_STRING_LENGTH);
	memcpy(config->default_net_bin_path   ,  iniparser_getstring(ini, options[1], def),  MAX_STRING_LENGTH);
	memcpy(config->default_ap_bin_path    ,  iniparser_getstring(ini, options[2], def),  MAX_STRING_LENGTH);
	memcpy(config->default_mboot_bin_path ,  iniparser_getstring(ini, options[3], def),  MAX_STRING_LENGTH);
	memcpy(config->defalut_sboot_bin_path ,  iniparser_getstring(ini, options[4], def),  MAX_STRING_LENGTH);
	memcpy(config->default_ursa_bin_path  ,  iniparser_getstring(ini, options[5], def),  MAX_STRING_LENGTH);
	memcpy(config->default_ota_zip_path   ,  iniparser_getstring(ini, options[6], def),  MAX_STRING_LENGTH);
	return 0;
}

static int store_mmap_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;

	options = iniparser_getseckeys(ini, "mmap");
	if(NULL == options)
	{
		printf_red("Cannot parse MMAP, please check it\n");
		return -1;
	}
	config->ve_buffer_address =  (U32)iniparser_getint(ini, options[0], notfound);
	return 0;
}

static int store_ursa_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;

	options = iniparser_getseckeys(ini, "ursa");
	if(NULL == options)
	{
		printf_red("Cannot parse URSA, please check it\n");
		return -1;
	}
	config->ursa_type =  (U8)iniparser_getint(ini, options[0], notfound);
	return 0;
}

static int store_ethcheck_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;

	options = iniparser_getseckeys(ini, "ethcheck");
	if(NULL == options)
	{
		printf_red("Cannot parse EthCheck, please check it\n");
		return -1;
	}	
	config->ethaddr_stored_position   =  (U8)iniparser_getint(ini, options[0], notfound);
	config->ethaddr_i2c_slave_address =  (U8)iniparser_getint(ini, options[1], notfound);
	config->ethaddr_in_bank_address   =  (U32)iniparser_getint(ini, options[2], notfound);
	return 0;
}

static int store_version_config(dictionary *ini, st_mboot_config *config)
{
	char **options;
	int notfound;

	options = iniparser_getseckeys(ini, "version");
	if(NULL == options)
	{
		printf_red("Cannot parse Verison, please check it\n");
		return -1;
	}	
	config->version = (U32)iniparser_getint(ini, options[0], notfound);
	return 0;
}

static void dump_boottopm_config(const st_mboot_config *config)
{
	/* pm_boot_config #0 */
	INI_PARSER_DEBUG(printf_green("\n[BootToPM]\n"));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableIR     = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-1)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableSAR    = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-2)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableGPIO0  = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-3)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableGPIO1  = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-4)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableUART1  = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-5)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableSYNC   = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-6)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableESYNC  = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-7)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableRTC0   = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-8)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableRTC1   = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-9)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableDVI0   = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-10)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableDVI2   = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-11)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableCEC    = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-12)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeEnableAVLINK = %d\n", (config->pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-13)) ? 1 : 0)));
	INI_PARSER_DEBUG(printf_blue("PmWakeIRKeyCode1   = 0x%X\n", config->pm_wakeup_keycode1));
	INI_PARSER_DEBUG(printf_blue("PmWakeIRKeyCode2   = 0x%X\n", config->pm_wakeup_keycode2));
	INI_PARSER_DEBUG(printf_blue("PmWakeIRKeyCode0   = 0x%X\n", config->pm_ir_headcode0));
	INI_PARSER_DEBUG(printf_blue("PmWakeIRKeyCode1   = 0x%X\n", config->pm_ir_headcode1));	
}

static void dump_flashwp_config(const st_mboot_config *config)
{
	/* flash_wp_config #1 */
	INI_PARSER_DEBUG(printf_green("\n[FlashWP]\n"));
	INI_PARSER_DEBUG(printf_blue("PIN_FLASH_WP0      = %d\n", config->pin_flash_wp0));
	INI_PARSER_DEBUG(printf_blue("PIN_FLASH_WP1      = %d\n", config->pin_flash_wp1));	
}

static void dump_dbtable_config(const st_mboot_config *config)
{
	/* db_table_config #2 */
	INI_PARSER_DEBUG(printf_green("\n[DBTable]\n"));
	INI_PARSER_DEBUG(printf_blue("UBIPART            = %s\n", config->ubipart));
	INI_PARSER_DEBUG(printf_blue("Config_Partition   = %s\n", config->config_partition));
	INI_PARSER_DEBUG(printf_blue("Customer_Partition = %s\n", config->customer_partition));
	INI_PARSER_DEBUG(printf_blue("Config_Path        = %s\n", config->config_path));
	INI_PARSER_DEBUG(printf_blue("Customer_path      = %s\n", config->customer_path));	
}

static void dump_keypad_config(const st_mboot_config *config)
{
	/* keypad_config #3 */
	INI_PARSER_DEBUG(printf_green("\n[KeypadConfig]\n"));
	INI_PARSER_DEBUG(printf_blue("ADC_KEY_LEVEL      = %d\n", config->adc_key_level_num));
	{
		int i_level;
		for(i_level = 0; i_level < NUMBER_OF_KEYPAD_ADC_LEVEL; i_level++)
		{
			INI_PARSER_DEBUG(printf_blue("ADC_KEY_L%d         = 0x%X\n", i_level, config->adc_key_level[i_level]));		
		}
	}	
}

static void dump_bootcheck_config(const st_mboot_config *config)
{
	/* boot_check_config #4 */
	INI_PARSER_DEBUG(printf_green("\n[BootCheck]\n"));
	INI_PARSER_DEBUG(printf_blue("IR_RECOVERY_KEY          = 0x%X\n", config->ir_recovery_key));
	INI_PARSER_DEBUG(printf_blue("IR_FORCEUGRADE_KEY       = 0x%X\n", config->ir_force_upgrade_key));
	INI_PARSER_DEBUG(printf_blue("IR_UART_ONOFF_KEY        = 0x%X\n", config->ir_uart_onoff_key));
	INI_PARSER_DEBUG(printf_blue("KEYPAD_RECOVERY_KEY      = 0x%X\n", config->keypad_recovery_key));
	INI_PARSER_DEBUG(printf_blue("KEYPAD_FORCEUGRADE_KEY   = 0x%X\n", config->keypad_force_upgrade_key));
	INI_PARSER_DEBUG(printf_blue("KEYPAD_UART_ONOFF_KEY    = 0x%X\n", config->keypad_uart_onoff_key));
}

static void dump_bootlogo_config(const st_mboot_config *config)
{
	/* boot_logo_config #5 */
	INI_PARSER_DEBUG(printf_green("\n[BootLogo]\n"));
	INI_PARSER_DEBUG(printf_blue("Logo_Partition           = %s\n", config->boot_logo_partition));
	INI_PARSER_DEBUG(printf_blue("Logo_Path                = %s\n", config->boot_logo_path));
	INI_PARSER_DEBUG(printf_blue("Logo_File                = %s\n", config->boot_logo_file));	
}

static void dump_bootmusic_config(const st_mboot_config *config)
{
	/* boot_music_config #6 */
	INI_PARSER_DEBUG(printf_green("\n[BootMusic]\n"));
	INI_PARSER_DEBUG(printf_blue("Music_Partition           = %s\n", config->boot_music_partition));
	INI_PARSER_DEBUG(printf_blue("Music_Path                = %s\n", config->boot_music_path));
	INI_PARSER_DEBUG(printf_blue("Music_File                = %s\n", config->boot_music_file));	
}

static void dump_osd_config(const st_mboot_config *config)
{
	/* osd_config #7 */
	INI_PARSER_DEBUG(printf_green("\n[OSD]\n"));
	INI_PARSER_DEBUG(printf_blue("OSD_Layer_Width           = %d\n", config->default_osd_layer_width));
	INI_PARSER_DEBUG(printf_blue("OSD_Layer_Height          = %d\n", config->default_osd_layer_height));
	INI_PARSER_DEBUG(printf_blue("OSD_ATTRIB                = %x\n", config->default_osd_attrib));
	INI_PARSER_DEBUG(printf_blue("OSD_COLOR                 = %x\n", config->default_osd_color));
	INI_PARSER_DEBUG(printf_blue("OSD_String_X              = %d\n", config->default_osd_string_x));
	INI_PARSER_DEBUG(printf_blue("OSD_String_Y              = %d\n", config->default_osd_string_y));
	INI_PARSER_DEBUG(printf_blue("OSD_String_Tips           = %s\n", config->default_osd_string_tips));
	INI_PARSER_DEBUG(printf_blue("OSD_Backgroud_Path        = %s\n", config->default_osd_background_path));	
}

static void dump_usbupgrade_config(const st_mboot_config *config)
{
	/* usb_upgrade_config #8 */
	INI_PARSER_DEBUG(printf_green("\n[USBUpgrade]\n"));
	INI_PARSER_DEBUG(printf_blue("OAD_BIN_PATH              = %s\n", config->default_oad_bin_path));
	INI_PARSER_DEBUG(printf_blue("NET_BIN_PATH              = %s\n", config->default_net_bin_path));
	INI_PARSER_DEBUG(printf_blue("AP_BIN_PATH               = %s\n", config->default_ap_bin_path));
	INI_PARSER_DEBUG(printf_blue("MBOOT_BIN_PATH            = %s\n", config->default_mboot_bin_path));
	INI_PARSER_DEBUG(printf_blue("SBOOT_BIN_PATH            = %s\n", config->defalut_sboot_bin_path));
	INI_PARSER_DEBUG(printf_blue("URSA_BIN_PATH             = %s\n", config->default_ursa_bin_path));	
	INI_PARSER_DEBUG(printf_blue("OTA_ZIP_PATH              = %s\n", config->default_ota_zip_path));
}

static void dump_mmap_config(const st_mboot_config *config)
{
	/* mmap_config #9 */
	INI_PARSER_DEBUG(printf_green("\n[MMAP]\n"));
	INI_PARSER_DEBUG(printf_blue("VE_BUFFER_ADDR            = 0x%X\n", config->ve_buffer_address));	
}

static void dump_ursa_config(const st_mboot_config *config)
{
	/* ursa_config #10 */
	INI_PARSER_DEBUG(printf_green("\n[URSA]\n"));
	INI_PARSER_DEBUG(printf_blue("URSA_Type                 = %d\n", config->ursa_type));
}

static void dump_ethcheck_config(const st_mboot_config *config)
{
	/* ethcheck_config #11 */
	INI_PARSER_DEBUG(printf_green("\n[EthCheck]\n"));
	INI_PARSER_DEBUG(printf_blue("Store_Position            = %d\n", config->ethaddr_stored_position));	
	INI_PARSER_DEBUG(printf_blue("I2C_Slave_Address         = %d\n", config->ethaddr_i2c_slave_address));	
	INI_PARSER_DEBUG(printf_blue("Bank_Address              = 0x%X\n", config->ethaddr_in_bank_address));	
}

static void dump_version_config(const st_mboot_config *config)
{
	INI_PARSER_DEBUG(printf_green("\n[Version]\n"));
	INI_PARSER_DEBUG(printf_blue("Version              = %d\n", config->version));
}
static void parse_mboot_config(dictionary *ini, st_mboot_config *config)
{
	if(0 == store_version_config(ini, config))
	{
		dump_version_config(config);
	}

	if(0 == store_boottopm_config(ini, config))
	{
		dump_boottopm_config(config);
	}
	if(0 == store_flashwp_config(ini, config))
	{
		dump_flashwp_config(config);
	}	
	if(0 == store_dbtable_config(ini, config))
	{
		dump_dbtable_config(config);
	}
	if(0 == store_keypad_config(ini, config))
	{
		dump_keypad_config(config);
	}
	if(0 == store_bootcheck_config(ini, config))
	{
		dump_bootcheck_config(config);
	}
	if(0 == store_bootlogo_config(ini, config))
	{
		dump_bootlogo_config(config);
	}
	if(0 == store_bootmusic_config(ini, config))
	{
		dump_bootmusic_config(config);
	}
	if(0 == store_osd_config(ini, config))
	{
		dump_osd_config(config);
	}
	if(0 == store_usbupgrade_config(ini, config))
	{
		dump_usbupgrade_config(config);
	}
	if(0 == store_mmap_config(ini, config))
	{
		dump_mmap_config(config);
	}
	if(0 == store_ursa_config(ini, config))
	{
		dump_ursa_config(config);
	}
	if(0 == store_ethcheck_config(ini, config))
	{
		dump_ethcheck_config(config);
	}
}

int main(int argc, char *argv[])
{
	dictionary * ini;
    char       * ini_name;
    FILE *binary_file;
    st_mboot_config config;
	int size, count;
	
    if(argc < 2)
    {
    	ini_name = MBOOT_INI_CONFIG_NAME;
    } 
    else
    {
    	ini_name = argv[1];
    }

    binary_file = fopen(MBOOT_CONFIG_BIN_NAME, "wa+b");
    if (NULL == binary_file)
    {
		printf_red("opening %s failed\n", MBOOT_CONFIG_BIN_NAME);
        return -1;
    }
    memset(&config, 0, sizeof(config));
	config.magic_number = MBOOT_CONFIG_MAGIC_NUMBER;

    ini = iniparser_load(ini_name);
    parse_mboot_config(ini, &config);

    size = fwrite(&config, sizeof(U8), sizeof(config), binary_file);
    if(size > MBOOT_CONFIG_BIN_SIZE)
	{
		printf_red("mboot_config.bin is larger than 4KB, please check your mboot_config.ini\n");
		return -1;
	}
	else
	{
		for(count = 0; count < MBOOT_CONFIG_BIN_SIZE - size; count++)
		{
			fputc('\0', binary_file);
		}
	}

    iniparser_freedict(ini);
    
    if (binary_file)
    {
        fclose(binary_file);
    }
    
    return 0;
}
