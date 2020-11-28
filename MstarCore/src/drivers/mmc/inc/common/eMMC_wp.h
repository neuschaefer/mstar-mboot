#ifndef eMMC_WP
#define eMMC_WP

#include "eMMC.h"

// test 
extern U32  eMMC_verify_BootPartition_WP(void);
#define CFG_PERM  1
#define CFG_PWR   2
extern U32  eMMC_verify_BootWP_Config(U8 u8_Flag);
extern U32  eMMC_verify_BootWP_WRC(U16 u16_Flag);
extern U32  eMMC_verify_UserWP_WRC(U32 u32_eMMCBlkAddr);


// APIs
#define USER_TEMP   1
#define USER_PWR    2
#define USER_PERM   3
extern  U32 eMMC_set_UserWP(U32 u32_eMMCBlkAddr, u16 u16_Flag);
extern  U32 eMMC_get_UserWPStatus(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf);
extern  U32 eMMC_get_WPGropuSize(void);

#define BOOT1_PWR   1
#define BOOT2_PWR   2
#define BOTH_PWR    3
#define BOOT1_PERM  4
#define BOOT2_PERM  5
#define BOTH_PERM   6
extern  U32 eMMC_set_BootWP(U16 u16_Flag); 
extern  U32 eMMC_get_BootWPStatus(void);

#endif // eMMC_WP

