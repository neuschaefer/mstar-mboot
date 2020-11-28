#ifndef _MMAP_SPI_H_
#define _MMAP_SPI_H_
//------------------------------------------- 
// Copy SPI map from mapi_flash.h
//
//
//-------------------------------------------

#define SPI_SIZE 0x200000 //for frmo board

#define SPI_BLOCK_SIZE                          0x10000

//Start of SPI MAP-----------------------------------------------------------------------------------
//-----------------------------------------
//  >>>  1M SPI MAP  <<<
//  Block Size = 0x10000
//  Total Size = 0x100000 (16 blocks)
//
//
//  PM               1  block
//  BootLogo     0  block
//  Reserved     3  block
//   -3. OAD
//   -2. MAP
//   -1. HOTEL_MODE
//
//  Total       16  block
//----------------------------------------------------------------

#define MBOOT_V259                              259
#define V259_BootLogo_Block_Position            16
#define V259_BootLogo_Block_Size                13
#define V259_OAD_Block_Reverse_Count_Position   1       //Reverse count

#define u8OAD_Block_Reverse_Count_Position          3   //Reverse count
#define u8PM51_Block_Position                             1  //PM51 resides at block1
#define u8PM51_Block_Size                             1 //PM51 occupies 1 block

#define SPI_PM51_ADDR                               (SPI_BLOCK_SIZE * u8PM51_Block_Position)
#define SPI_PM51_SIZE                               (SPI_BLOCK_SIZE * u8PM51_Block_Size)


//-----------------------------------------
// Reserved 3 / 3 block, OAD
//-----------------------------------------
#define SPI_OAD_BASE_ADDR                       (SPI_SIZE-(SPI_BLOCK_SIZE * u8OAD_Block_Reverse_Count_Position))
#define SPI_OAD_BOOT_FLAG_ADDR                  0
#define SPI_OAD_BOOT_FLAG_SIZE                  0x1000
#define SPI_OAD_APP_CRC_ADDR                    (SPI_OAD_BOOT_FLAG_ADDR+SPI_OAD_BOOT_FLAG_SIZE)
#define SPI_OAD_APP_CRC_SIZE                    0x1000
#define SPI_OAD_FACTORY_DL_CODE_ADDR            (SPI_OAD_APP_CRC_ADDR+SPI_OAD_APP_CRC_SIZE)
#define SPI_OAD_FACTORY_DL_CODE_SIZE            0x1000

#if 0
//-----------------------------------------
// Reserved 3 / 4 block, Env
//-----------------------------------------
#define SPI_MAP_MINUS1BLOCK_BASE_ADDR           (SPI_SIZE-(SPI_BLOCK_SIZE*3)) 
#define SPI_MAP_ENV_ADDR                        0x00
#define SPI_MAP_ENV_SIZE                        SPI_BLOCK_SIZE
#endif

//-----------------------------------------
// Reserved 2 / 3 block, MAP
//-----------------------------------------
#define SPI_MAP_BASE_ADDR                       (SPI_SIZE-(SPI_BLOCK_SIZE*2))
#define SPI_MAP_DDR_ADDR                        0x00
#define SPI_MAP_DDR_SIZE                        128
#define SPI_MAP_CIP_ADDR                        (SPI_MAP_DDR_ADDR+SPI_MAP_DDR_SIZE)
#define SPI_MAP_CIP_SIZE                        5120
#define SPI_MAP_HDCP_ADDR                       (SPI_MAP_CIP_ADDR+SPI_MAP_CIP_SIZE)
#define SPI_MAP_HDCP_SIZE                       512
#define SPI_MAP_EDID_ADDR                       (SPI_MAP_HDCP_ADDR+SPI_MAP_HDCP_SIZE)
#define SPI_MAP_EDID_SIZE                       512
#define SPI_MAP_MAC_ADDR                        (SPI_MAP_EDID_ADDR+SPI_MAP_EDID_SIZE)
#define SPI_MAP_MAC_SIZE                        32
#define SPI_MAP_RC_ADDR                         (SPI_MAP_MAC_ADDR+SPI_MAP_MAC_SIZE)
#define SPI_MAP_RC_SIZE                         1
#define SPI_MAP_MBOOT_NAME_ADDR                 (SPI_MAP_RC_ADDR + SPI_MAP_RC_SIZE)
#define SPI_MAP_MBOOT_NAME_SIZE                 100
#define SPI_MAP_CUSTOMER_SERVICE_ADDR           (SPI_MAP_MBOOT_NAME_ADDR + SPI_MAP_MBOOT_NAME_SIZE)
#define SPI_MAP_CUSTOMER_SERVICE_SIZE           64
#define SPI_MAP_MEM_MAP_MODE_ADDR               (SPI_MAP_CUSTOMER_SERVICE_ADDR + SPI_MAP_CUSTOMER_SERVICE_SIZE)
#define SPI_MAP_MEM_MAP_MODE_SIZE               1

#define SPI_MAP_LX_MEM_ADDR_INFO_ADDR           (SPI_MAP_MEM_MAP_MODE_ADDR + SPI_MAP_MEM_MAP_MODE_SIZE)
#define SPI_MAP_LX_MEM_ADDR_INFO_SIZE           8
#define SPI_MAP_LX_MEM_SIZE_INFO_ADDR           (SPI_MAP_LX_MEM_ADDR_INFO_ADDR + SPI_MAP_LX_MEM_ADDR_INFO_SIZE)
#define SPI_MAP_LX_MEM_SIZE_INFO_SIZE           8
#define SPI_MAP_LX2_MEM_ADDR_INFO_ADDR          (SPI_MAP_LX_MEM_SIZE_INFO_ADDR + SPI_MAP_LX_MEM_SIZE_INFO_SIZE)
#define SPI_MAP_LX2_MEM_ADDR_INFO_SIZE          8
#define SPI_MAP_LX2_MEM_SIZE_INFO_ADDR          (SPI_MAP_LX2_MEM_ADDR_INFO_ADDR + SPI_MAP_LX2_MEM_ADDR_INFO_SIZE)
#define SPI_MAP_LX2_MEM_SIZE_INFO_SIZE          8

#define SPI_MAP_LX_MEM_ADDR_INFO_SUM_ADDR       (SPI_MAP_LX2_MEM_SIZE_INFO_ADDR + SPI_MAP_LX2_MEM_SIZE_INFO_SIZE)
#define SPI_MAP_LX_MEM_ADDR_INFO_SUM_SIZE       2
#define SPI_MAP_LX_MEM_SIZE_INFO_SUM_ADDR       (SPI_MAP_LX_MEM_ADDR_INFO_SUM_ADDR + SPI_MAP_LX_MEM_ADDR_INFO_SUM_SIZE)
#define SPI_MAP_LX_MEM_SIZE_INFO_SUM_SIZE       2
#define SPI_MAP_LX2_MEM_ADDR_INFO_SUM_ADDR      (SPI_MAP_LX_MEM_SIZE_INFO_SUM_ADDR + SPI_MAP_LX_MEM_SIZE_INFO_SUM_SIZE)
#define SPI_MAP_LX2_MEM_ADDR_INFO_SUM_SIZE      2
#define SPI_MAP_LX2_MEM_SIZE_INFO_SUM_ADDR      (SPI_MAP_LX2_MEM_ADDR_INFO_SUM_ADDR + SPI_MAP_LX2_MEM_ADDR_INFO_SUM_SIZE)
#define SPI_MAP_LX2_MEM_SIZE_INFO_SUM_SIZE      2

#define SPI_MAP_PANEL_SETTING_VALID_ADDR        (SPI_MAP_LX2_MEM_SIZE_INFO_SUM_ADDR+SPI_MAP_LX2_MEM_SIZE_INFO_SUM_SIZE)
#define SPI_MAP_PANEL_SETTING_VALID_SIZE        1
#define SPI_MAP_PANEL_SETTING_ADDR              (SPI_MAP_PANEL_SETTING_VALID_ADDR+SPI_MAP_PANEL_SETTING_VALID_SIZE)
#define SPI_MAP_PANEL_SETTING_SIZE              92
#define SPI_MAP_BOOT_LOGO_VALID_ADDR            (SPI_MAP_PANEL_SETTING_ADDR+SPI_MAP_PANEL_SETTING_SIZE)
#define SPI_MAP_BOOT_LOGO_VALID_SIZE            1
#define SPI_MAP_BOOT_LOGO_INFO_ADDR             (SPI_MAP_BOOT_LOGO_VALID_ADDR+SPI_MAP_BOOT_LOGO_VALID_SIZE)
#define SPI_MAP_BOOT_LOGO_INFO_SIZE             4
#define SPI_MAP_MFC_SETTING_VALID_ADDR          (SPI_MAP_BOOT_LOGO_INFO_ADDR+SPI_MAP_BOOT_LOGO_INFO_SIZE)
#define SPI_MAP_MFC_SETTING_VALID_SIZE          1
#define SPI_MAP_MFC_SETTING_ADDR                (SPI_MAP_MFC_SETTING_VALID_ADDR+SPI_MAP_MFC_SETTING_VALID_SIZE)
#define SPI_MAP_MFC_SETTING_SIZE                (39*2)
#define SPI_MAP_ENABLE_PANEL_FLIP_ADDR          (SPI_MAP_MFC_SETTING_ADDR+SPI_MAP_MFC_SETTING_SIZE)
#define SPI_MAP_ENABLE_PANEL_FLIP_SIZE          1

#define SPI_MAP_BOOT_FROMPM51_ADDR              (SPI_MAP_ENABLE_PANEL_FLIP_ADDR+SPI_MAP_ENABLE_PANEL_FLIP_SIZE)
#define SPI_MAP_BOOT_FROMPM51_SIZE              1
#define SPI_MAP_ENHANCE_SECURE_BOOT_ADDR        (SPI_MAP_BOOT_FROMPM51_ADDR+SPI_MAP_BOOT_FROMPM51_SIZE)
#define SPI_MAP_ENHANCE_SECURE_BOOT_SIZE        1
#define SPI_MAP_SPIHWPROTECT_ADDR               (SPI_MAP_ENHANCE_SECURE_BOOT_ADDR+SPI_MAP_ENHANCE_SECURE_BOOT_SIZE)
#define SPI_MAP_SPIHWPROTECT_SIZE               1

#define SPI_MAP_ENABLE_UART_RX_ADDR             (SPI_MAP_SPIHWPROTECT_ADDR+SPI_MAP_SPIHWPROTECT_SIZE)
#define SPI_MAP_ENABLE_UART_RX_SIZE             1

#define SPI_MAP_STANDBY_LED_MODE_ADDR           (SPI_MAP_ENABLE_UART_RX_ADDR+SPI_MAP_ENABLE_UART_RX_SIZE)
#define SPI_MAP_STANDBY_LED_MODE_SIZE           1

#define SPI_MAP_HDCP2_ADDR                      (SPI_MAP_STANDBY_LED_MODE_ADDR+SPI_MAP_STANDBY_LED_MODE_SIZE)
#define SPI_MAP_HDCP2_SIZE                      1024

#define SPI_MAP_LVDS_SWING_ADDR                 (SPI_MAP_HDCP2_ADDR+SPI_MAP_HDCP2_SIZE)
#define SPI_MAP_LVDS_SWING_SIZE                 2

#define SPI_MAP_MFC_LVDS2_SETTING_ADDR          (SPI_MAP_LVDS_SWING_ADDR+SPI_MAP_LVDS_SWING_SIZE)
#define SPI_MAP_MFC_LVDS2_SETTING_SIZE          (8)

#define SPI_MAP_MFC_CTRLSWING_SETTING_ADDR      (SPI_MAP_MFC_LVDS2_SETTING_ADDR+SPI_MAP_MFC_LVDS2_SETTING_SIZE)
#define SPI_MAP_MFC_CTRLSWING_SETTING_SIZE      (2)

#define SPI_MAP_NETFLIX_ENABLED_ADDR            (SPI_MAP_MFC_CTRLSWING_SETTING_ADDR + SPI_MAP_MFC_CTRLSWING_SETTING_SIZE)
#define SPI_MAP_NETFLIX_ENABLED_SIZE            (1)

#define SPI_MAP_EDID_VGA_ADDR               (SPI_MAP_NETFLIX_ENABLED_ADDR + SPI_MAP_NETFLIX_ENABLED_SIZE)
#define SPI_MAP_EDID_VGA_SIZE               128

#define SPI_MAP_ESNID_ADDR                  (SPI_MAP_EDID_VGA_ADDR+SPI_MAP_EDID_VGA_SIZE)
#define SPI_MAP_ESNID_SIZE                    43

#define SPI_MAP_KPEKPH_ADDR                  (SPI_MAP_ESNID_ADDR+SPI_MAP_ESNID_SIZE)
#define SPI_MAP_KPEKPH_SIZE                    212

//ENHANCE_BOOTING_TIME
#define SPI_MAP_CMD_ADDR                  (SPI_MAP_KPEKPH_ADDR+SPI_MAP_KPEKPH_SIZE)
#define SPI_MAP_CMD_SIZE                    1

// Important note:
// SPI_MAP_BOOT_DB locates at the final 128byte of SPI_MAP_BASE_ADDR
// SPI_MAP_BASE_ADDR+SPI_BLOCK_SIZE-SPI_MAP_BOOT_DB_SIZE = SPISIZE (SPISIZE is defined at \sboot\Makefile)
#define SPI_MAP_BOOT_DB_SIZE                    128
#define SPI_MAP_BOOT_DB_ADDR                    (SPI_BLOCK_SIZE - SPI_MAP_BOOT_DB_SIZE)

//-----------------------------------------
// Reserved 1 / 3 block
// For HOTEL mboot, this block is reserved for Hotel mode parameter  
// For SecureBoot, this block is reserved for Signature
//-----------------------------------------



//End of SPI MAP-----------------------------------------------------------------------------------
#endif
