#ifndef _MMAP_SPI_H_
#define _MMAP_SPI_H_
//------------------------------------------- 
// Copy SPI map from mapi_flash.h
//
//
//-------------------------------------------

#define SPI_SIZE 0x200000

#define SPI_BLOCK_SIZE                          0x10000

//Start of SPI MAP-----------------------------------------------------------------------------------
//-----------------------------------------
//  >>>  1M SPI MAP  <<<
//  Block Size = 0x10000
//  Total Size = 0x100000 (16 blocks)
//
//
//  MBOOT       13  block
//  BootLogo     0  block
//  Reserved     3  block
//   -3. Env
//   -2. MAP
//   -1. OAD
//
//  Total       16  block
//-----------------------------------------
//  >>>  2M SPI MAP OLD, MBOOT_VER 259 and Before <<<
//  Block Size = 0x10000
//  Total Size = 0x200000 (32 blocks)
//
//
//  MBOOT       16  block
//  BootLogo    13  block
//  Reserved     3  block
//   -3. Env
//   -2. MAP
//   -1. OAD
//
//  Total       32  block
//-----------------------------------------
//  >>>  2M SPI MAP NEW, MBOOT_VER 260 and After  <<<
//  Block Size = 0x10000
//  Total Size = 0x200000 (32 blocks)
//
//
//  MBOOT       18  block
//  BootLogo    10  block
//  Reserved     4  block
//   -4. OAD
//   -3. Env
//   -2. MAP
//   -1. HOTEL_MODE
//
//  Total       32  block
//-----------------------------------------


//---------------------------------------------------------------
// From MBoot_Ver 260
// 1. MBoot       area ( 0~15 block)  --> ( 0~17 block)
// 2. BootLogo    area (16~28 block)  --> (18~27 block)
// 3. OAD_Block   area (31th block)   --> (28th block)
// 4. Hotel_Block area (31th block)   New
//
//                          <-------259 ,   260------->
//u8BootLogo_Block_Position         16      18
//u8BootLogo_Block_Size             13      10
//u8OAD_Block_Position              1       4
//---------------------------------------------------------------
//#define MBOOT_V259                                  259
//#define V259_BootLogo_Block_Position                16
//#define V259_BootLogo_Block_Size                    13
//#define V259_OAD_Block_Reverse_Count_Position       1       //Reverse count

#if (! ENABLE_MSTAR_MONACO)
#define u8BootLogo_Block_Position                   18
#define u8BootLogo_Block_Size                       10

//-----------------------------------------
// BootLogo Area Ver260 and After
//-----------------------------------------
#define SPI_BOOT_LOGO_ADDR                      (SPI_BLOCK_SIZE * u8BootLogo_Block_Position)    // Boot Logo area start address
#define SPI_BOOT_LOGO_SIZE                      (SPI_BLOCK_SIZE * u8BootLogo_Block_Size)        // Boot Logo area reserved size

#endif

#define u8OAD_Block_Reverse_Count_Position          4   //Reverse count
#define u8PM51_Block_Position                             1  //PM51 resides at block1
#define u8PM51_Block_Size                             1 //PM51 occupies 1 block

#define SPI_PM51_ADDR                               (SPI_BLOCK_SIZE * u8PM51_Block_Position)
#define SPI_PM51_SIZE                               (SPI_BLOCK_SIZE * u8PM51_Block_Size)


//-----------------------------------------
// Reserved 4 / 4 block, OAD
//-----------------------------------------
#define SPI_OAD_BASE_ADDR                       (SPI_SIZE-(SPI_BLOCK_SIZE * u8OAD_Block_Reverse_Count_Position))
#define SPI_OAD_BOOT_FLAG_ADDR                  0
#define SPI_OAD_BOOT_FLAG_SIZE                  0x1000
#define SPI_OAD_APP_CRC_ADDR                    (SPI_OAD_BOOT_FLAG_ADDR+SPI_OAD_BOOT_FLAG_SIZE)
#define SPI_OAD_APP_CRC_SIZE                    0x1000
#define SPI_OAD_FACTORY_DL_CODE_ADDR            (SPI_OAD_APP_CRC_ADDR+SPI_OAD_APP_CRC_SIZE)
#define SPI_OAD_FACTORY_DL_CODE_SIZE            0x1000


//-----------------------------------------
// Reserved 3 / 4 block, Env
//-----------------------------------------
#define SPI_MAP_MINUS1BLOCK_BASE_ADDR           (SPI_SIZE-(SPI_BLOCK_SIZE*3)) 
#define SPI_MAP_ENV_ADDR                        0x00
#define SPI_MAP_ENV_SIZE                        SPI_BLOCK_SIZE


//-----------------------------------------
// Reserved 2 / 4 block, MAP
//-----------------------------------------
#define SPI_MAP_BASE_ADDR                       (SPI_SIZE-(SPI_BLOCK_SIZE*2))
#define SPI_MAP_DDR_ADDR                        0x00
#define SPI_MAP_DDR_SIZE                        128
#define SPI_MAP_CIP_ADDR                        (SPI_MAP_DDR_ADDR+SPI_MAP_DDR_SIZE)
#define SPI_MAP_CIP_SIZE                        5120
#define SPI_MAP_HDCP_ADDR                       (SPI_MAP_CIP_ADDR+SPI_MAP_CIP_SIZE)
#define SPI_MAP_HDCP_SIZE                       512
#define SPI_MAP_EDID_HDMI_14_ADDR      (SPI_MAP_HDCP_ADDR+SPI_MAP_HDCP_SIZE)
#define SPI_MAP_EDID_HDMI_14_SIZE        512
#define SPI_MAP_EDID_HDMI_20_ADDR      (SPI_MAP_EDID_HDMI_14_ADDR+SPI_MAP_EDID_HDMI_14_SIZE)
#define SPI_MAP_EDID_HDMI_20_SIZE        512
#define SPI_MAP_MAC_ADDR                        (SPI_MAP_EDID_HDMI_20_ADDR+SPI_MAP_EDID_HDMI_20_SIZE)
#define SPI_MAP_MAC_SIZE                        32
#define SPI_MAP_RC_ADDR                         (SPI_MAP_MAC_ADDR+SPI_MAP_MAC_SIZE)
#define SPI_MAP_RC_SIZE                         1
#define SPI_MAP_MBOOT_NAME_ADDR                 (SPI_MAP_RC_ADDR + SPI_MAP_RC_SIZE)
#define SPI_MAP_MBOOT_NAME_SIZE                 100
#define SPI_MAP_CUSTOMER_SERVICE_ADDR           (SPI_MAP_MBOOT_NAME_ADDR + SPI_MAP_MBOOT_NAME_SIZE)
#define SPI_MAP_CUSTOMER_SERVICE_SIZE           64

#define SPI_MAP_SPIHWPROTECT_ADDR               (SPI_MAP_CUSTOMER_SERVICE_ADDR+SPI_MAP_CUSTOMER_SERVICE_SIZE)
#define SPI_MAP_SPIHWPROTECT_SIZE               1

#define SPI_MAP_ENABLE_UART_RX_ADDR             (SPI_MAP_SPIHWPROTECT_ADDR+SPI_MAP_SPIHWPROTECT_SIZE)
#define SPI_MAP_ENABLE_UART_RX_SIZE             1

#define SPI_MAP_STANDBY_LED_MODE_ADDR           (SPI_MAP_ENABLE_UART_RX_ADDR+SPI_MAP_ENABLE_UART_RX_SIZE)
#define SPI_MAP_STANDBY_LED_MODE_SIZE           1

#define SPI_MAP_HDCP2_ADDR                      (SPI_MAP_STANDBY_LED_MODE_ADDR+SPI_MAP_STANDBY_LED_MODE_SIZE)
#define SPI_MAP_HDCP2_SIZE                      1024

#define SPI_MAP_NETFLIX_ENABLED_ADDR               (SPI_MAP_HDCP2_ADDR + SPI_MAP_HDCP2_SIZE)
#define SPI_MAP_NETFLIX_ENABLED_SIZE               1

#define SPI_MAP_EDID_VGA_ADDR               (SPI_MAP_NETFLIX_ENABLED_ADDR + SPI_MAP_NETFLIX_ENABLED_SIZE)
#define SPI_MAP_EDID_VGA_SIZE               128

#define SPI_MAP_ESNID_ADDR                  (SPI_MAP_EDID_VGA_ADDR+SPI_MAP_EDID_VGA_SIZE)
#define SPI_MAP_ESNID_SIZE                    43

#define SPI_MAP_KPEKPH_ADDR                  (SPI_MAP_ESNID_ADDR+SPI_MAP_ESNID_SIZE)
#define SPI_MAP_KPEKPH_SIZE                    212

// Important note:
// SPI_MAP_BOOT_DB locates at the final 128byte of SPI_MAP_BASE_ADDR
// SPI_MAP_BASE_ADDR+SPI_BLOCK_SIZE-SPI_MAP_BOOT_DB_SIZE = SPISIZE (SPISIZE is defined at \sboot\Makefile)
#define SPI_MAP_BOOT_DB_SIZE                    128
#define SPI_MAP_BOOT_DB_ADDR                    (SPI_BLOCK_SIZE - SPI_MAP_BOOT_DB_SIZE)

//-----------------------------------------
// Reserved 1 / 4 block
// For HOTEL mboot, this block is reserved for Hotel mode parameter  
// For SecureBoot, this block is reserved for Signature
//-----------------------------------------



//End of SPI MAP-----------------------------------------------------------------------------------
#endif
