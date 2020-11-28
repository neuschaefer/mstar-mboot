#ifndef __MBOOT_INI_PARSER_H__
#define __MBOOT_INI_PARSER_H__

// common types
typedef unsigned int   U32;
typedef unsigned short U16;
typedef unsigned char  U8;

// general arguments
#define NUMBER_OF_PM_WAKEUP_SOURCE		 13
#define NUMBER_OF_KEYPAD_ADC_LEVEL   	  8
#define MAX_NUMBER_OF_KEYPAD_ADC_LEVEL	 16
#define MAX_STRING_LENGTH				 32
#define MBOOT_CONFIG_BIN_NAME			 "mboot_config.bin"
#define MBOOT_INI_CONFIG_NAME			 "mboot_config.ini"
#define BAR                              "\n===============================================================================\n"
#define MBOOT_CONFIG_BIN_SIZE					4096	// byte
#define MBOOT_CONFIG_MAGIC_NUMBER		0xAABBCCDD

// debug function
#define printf_red(args...)         do{ printf("\033[1;31m"); printf(args); printf("\033[m"); } while(0)
#define printf_green(args...)       do{ printf("\033[1;32m"); printf(args); printf("\033[m"); } while(0)
#define printf_blue(args...)        do{ printf("\033[1;34m"); printf(args); printf("\033[m"); } while(0)

#pragma pack (1)					// force to be aligned by one byte
typedef struct 
{
	/* magic number */
	U32 magic_number;
	
	/* version control*/
	U32 version;					// it records mboot_config.ini's version
	
	/* pm_boot_config (6 bytes) */
	U16 pm_wakeup_source;			// every bit represents one source, 1:enable, 0:disable
	U8  pm_wakeup_keycode1;
	U8  pm_wakeup_keycode2;
	U8	pm_ir_headcode0;
	U8  pm_ir_headcode1;

	/* flash_wp_config (2 bytes) */
	U8 pin_flash_wp0;
	U8 pin_flash_wp1;	

	/* db_table_config (32*5=160 bytes) */
	U8 ubipart[MAX_STRING_LENGTH];
	U8 config_partition[MAX_STRING_LENGTH];
	U8 customer_partition[MAX_STRING_LENGTH];
	U8 config_path[MAX_STRING_LENGTH];
	U8 customer_path[MAX_STRING_LENGTH];

	/* keypad_config (17 bytes)*/
	U8 adc_key_level_num;
	U8 adc_key_level[MAX_NUMBER_OF_KEYPAD_ADC_LEVEL];	

	/* boot_check_config (6 bytes)*/
	U8 ir_recovery_key;
	U8 ir_force_upgrade_key;
	U8 ir_uart_onoff_key;
	U8 keypad_recovery_key;
	U8 keypad_force_upgrade_key;
	U8 keypad_uart_onoff_key;

	/* boot_logo_config (32*3=96 bytes)*/ 
	U8 boot_logo_partition[MAX_STRING_LENGTH];
	U8 boot_logo_path[MAX_STRING_LENGTH];
	U8 boot_logo_file[MAX_STRING_LENGTH];

	/* boot_music_config (32*3=96 bytes)*/ 
	U8 boot_music_partition[MAX_STRING_LENGTH];
	U8 boot_music_path[MAX_STRING_LENGTH];
	U8 boot_music_file[MAX_STRING_LENGTH];	

	/* osd_config (4*2+3+32*2+2=77 bytes)*/ 
	U32 default_osd_layer_width;
	U32 default_osd_layer_height;
	U16 default_osd_attrib;
	U8  default_osd_color;
	U8  default_osd_string_x;
	U8  default_osd_string_y;
	U8  default_osd_string_tips[MAX_STRING_LENGTH];
	U8  default_osd_background_path[MAX_STRING_LENGTH];

	/* usb_upgrade_config (32*7=224 bytes)*/
	U8 default_oad_bin_path[MAX_STRING_LENGTH];
	U8 default_net_bin_path[MAX_STRING_LENGTH];
	U8 default_ap_bin_path[MAX_STRING_LENGTH];
	U8 default_mboot_bin_path[MAX_STRING_LENGTH];
	U8 defalut_sboot_bin_path[MAX_STRING_LENGTH];
	U8 default_ursa_bin_path[MAX_STRING_LENGTH];
	U8 default_ota_zip_path[MAX_STRING_LENGTH];	

	/* mmap_config 4 bytes */
	U32 ve_buffer_address;

	/* ursa_config 1 byte*/
	U8 ursa_type;

	/* eth_check_config 6 bytes*/
	U8  ethaddr_stored_position;
	U8  ethaddr_i2c_slave_address;
	U32 ethaddr_in_bank_address;	
} st_mboot_config;

#endif