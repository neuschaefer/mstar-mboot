#ifndef __UBOOT_MMAP_H__
#define __UBOOT_MMAP_H__

#include <config.h>

#if defined(CONFIG_MSTAR_NAPOLI) || defined(CONFIG_MSTAR_MONACO) || defined(CONFIG_MSTAR_MADISON)|| defined(CONFIG_MSTAR_CLIPPERS)
#define R2_CACHE_ADDR 0x00000000
#else
#define R2_CACHE_ADDR 0x40000000
#endif
#define UPGRADE_ADDR_STR        "UPGRADE_MEM_ADDR"
#if (ENABLE_MODULE_ANDROID_BOOT == 1 )
#define BOOT_MODE_TMP_BUF_ADDR  (CONFIG_SYS_MIU0_CACHE|0x5000000)
#else
#if defined(CONFIG_VESTEL_MB97) 
#define BOOT_MODE_TMP_BUF_ADDR  (CONFIG_SYS_MIU0_CACHE|0x3ffffc0)
#else
#define BOOT_MODE_TMP_BUF_ADDR  (CONFIG_SYS_MIU0_CACHE|0x400000)
#endif
#endif
#if (ENABLE_KENYA) || (ENABLE_KERES) || (ENABLE_KRITI) || (ENABLE_KRIS)
#define UPGRADE_BUFFER_ADDR     (CONFIG_SYS_MIU0_CACHE)
#else
#define UPGRADE_BUFFER_ADDR     (CONFIG_SYS_MIU0_CACHE|0x200000)//(CACHE_ADDR|0x00000000)
#endif
/*************************************
* Runtime PM *
**************************************/

#define RUNTIME_PM_START_ADDR 0
#define RUNTIME_PM_START_SIZE 0x10000


/*************************************
***  Secure booting memory setting ***
**************************************/
//#define SHA256_OUTPUT_BUFFER                              0x200000 //AESDMA sha256 output buffer address
#define UPGRADE_SECUREINFO_BUFFER_ADDR        (CONFIG_SYS_MIU0_CACHE|0x500000)
#define AES_DECRYPTED_ADDR                    (CONFIG_SYS_MIU0_CACHE|0x4000000)
#define AES_DECRYPTED_LEN                      0x500000 // Len can't smallier than SEGMENT_SIZE
#define RSA_AUTHENTICATION_ADDR               (CONFIG_SYS_MIU0_CACHE|0x4500000)
#define RSA_AUTHENTICATION_LEN                 0x500000// Len can't smallier than SEGMENT_SIZE
#define FILESYSTEM_AUTHENTICATION_BUFFER_ADDR (CONFIG_SYS_MIU0_CACHE|0x5000000)
#define SECURITY_COMMON_BUFFER_ADDR (CONFIG_SYS_MIU0_CACHE|0xA00000)//0x80A00000


/*************************************
*****   panel memory setting   *******
**************************************/
#if (CONFIG_BINARY_RELEASE == 1)
#define VE_BUFFER_ADDR 			mboot_config.ve_buffer_address		// IS_MBootBinaryRelease Test
#else
#if defined(CONFIG_A3_STB)
#define VE_BUFFER_ADDR          0x15EC0000//0x06C00000
#elif (defined(CONFIG_MSTAR_KERES)||defined(CONFIG_MSTAR_KRIS)) && (ENABLE_BOOT_SPI_ECOS)
#define VE_BUFFER_ADDR          0x05800000
#else
#define VE_BUFFER_ADDR          0x06C00000
#endif
#endif


#if defined(CONFIG_MSTAR_MADISON) || defined(CONFIG_MSTAR_NUGGET)
#define CANVAS_BUFFER_ADDR      0x0AE00000
#elif (defined(CONFIG_MSTAR_KERES)||defined(CONFIG_MSTAR_KRIS)) && (ENABLE_BOOT_SPI_ECOS)
#define CANVAS_BUFFER_ADDR      0x04800000
#else
#define CANVAS_BUFFER_ADDR      0x14000000
#endif
#define DMX_SEC_BUFFER_ADR      0x073FC000

#if (defined(CONFIG_MSTAR_KERES)||defined(CONFIG_MSTAR_KRIS)) && (ENABLE_BOOT_SPI_ECOS)
#define GOP_BUFFER_ADDR         0x01200000
#endif

/*************************************
*****   audio memory setting   *******
**************************************/
#if (CONFIG_AUDIO_CUSTOM_CONFIG)
#define AUDIO_R2_MEM_INFO_ADR       CONFIG_AUDIO_R2_MEM_INFO_ADR
#define AUDIO_S_MEM_INFO_ADR        CONFIG_AUDIO_S_MEM_INFO_ADR
#define AUDIO_D_MEM_INFO_ADR        CONFIG_AUDIO_D_MEM_INFO_ADR
#else
#define AUDIO_R2_MEM_INFO_ADR       0x000A200000 //E_MMAP_ID_MAD_R2_ADR
#define AUDIO_S_MEM_INFO_ADR        0x000A340000 //E_MMAP_ID_MAD_SE_ADR
#define AUDIO_D_MEM_INFO_ADR        0x000A440000 //E_MMAP_ID_MAD_DEC_ADR
#endif
#define AUDIO_ES1_ADR               AUDIO_D_MEM_INFO_ADR


/*************************************
*****   logo memory setting   *******
**************************************/
#if 0 //get from supernove mmap.ini
#if (CONFIG_LOGO_CUSTOM_CONFIG)
#define JPD_READBUFF_ADR     CONFIG_JPD_READBUFF_ADR
#define JPD_READBUFF_LEN     CONFIG_JPD_READBUFF_LEN
#define JPD_INTERBUFF_ADR    CONFIG_JPD_INTERBUFF_ADR
#define JPD_INTERBUFF_LEN    CONFIG_JPD_INTERBUFF_LEN
#define JPD_OUT_ADR          CONFIG_JPD_OUT_ADR
#define JPD_OUT_LEN          CONFIG_JPD_OUT_LEN
#define LOGO_JPG_DRAM_ADDR   CONFIG_LOGO_JPG_DRAM_ADDR
#define GOP_BUFFER_ADDR      CONFIG_GOP_BUFFER_ADDR
#define GOP1_BUFFER_ADDR     CONFIG_GOP1_BUFFER_ADDR

#else
#define JPD_READBUFF_ADR        0x0E9C2000 		//E_DFB_JPD_READ_ADR
#define JPD_READBUFF_LEN        0x00100000 		//E_DFB_JPD_READ_LEN
#define JPD_INTERBUFF_ADR       0x0EAC2000 		//E_DFB_JPD_INTERNAL_ADR
#define JPD_INTERBUFF_LEN       0x00100000 		//E_DFB_JPD_INTERNAL_LEN
#define JPD_OUT_ADR             0x0EBC2000 		//E_DFB_JPD_WRITE_ADR
#define JPD_OUT_LEN             0x009CA000 		//E_DFB_JPD_WRITE_LEN

#define LOGO_JPG_DRAM_ADDR      0x05B2C000
    #if(ENABLE_EAGLE==1 || ENABLE_EDISON==1 || ENABLE_EIFFEL==1 || \
	ENABLE_NIKE==1 || ENABLE_MADISON==1  || ENABLE_CLIPPERS==1 || \
	ENABLE_MIAMI==1 || ENABLE_NADAL==1 || ENABLE_EINSTEIN==1 || \
	ENABLE_KAISERIN==1 ||ENABLE_KAISER==1 || ENABLE_EINSTEIN3==1 || \
	ENABLE_MONACO==1 || ENABLE_MUJI==1 || ENABLE_CELTICS==1)
    #define GOP_BUFFER_ADDR         0x0E600000	//E_MMAP_ID_GOP_FB_ADR E_DFB_FRAMEBUFFER_ADR
    #define GOP1_BUFFER_ADDR        0x17AD3000
    #else
    #define GOP_BUFFER_ADDR         (0x0E600000|MIU_INTERVAL)
    #endif
#endif
#endif
#if CONFIG_MINIUBOOT
// from SN_MMAP_AMETHYST_MST028B-10AFX_Lite.h
#define MMAP_E_DFB_FRAMEBUFFER_ADDR 0x0006BEC000

#define MMAP_E_MMAP_ID_JPD_READ_ADDR 0x0005CE8400
#define MMAP_E_MMAP_ID_JPD_READ_SIZE 0x0000050080
#define MMAP_E_MMAP_ID_JPD_WRITE_ADDR 0x0005D38480
#define MMAP_E_MMAP_ID_JPD_WRITE_SIZE 0x00003FC000
#define MMAP_E_MMAP_ID_PHOTO_INTER_ADDR 0x0006134480
#define MMAP_E_MMAP_ID_PHOTO_INTER_SIZE 0x0000630000
#elif ENABLE_BOOT_SPI_ECOS
#define MMAP_E_DFB_FRAMEBUFFER_ADDR            0x04D20000

#define MMAP_E_MMAP_ID_JPD_WRITE_ADDR           0x00730000  //Alignment 0x00008
#define MMAP_E_MMAP_ID_JPD_WRITE_SIZE            0x003FC000
#define MMAP_E_MMAP_ID_JPD_READ_ADDR             0x00000000  //Alignment 0x00010
#define MMAP_E_MMAP_ID_JPD_READ_SIZE              0x00100000
#define MMAP_E_MMAP_ID_PHOTO_INTER_ADDR       0x00100000   //Alignment 0x00200
#define MMAP_E_MMAP_ID_PHOTO_INTER_SIZE        0x00630000
#endif

#endif //__UBOOT_MMAP_H__
