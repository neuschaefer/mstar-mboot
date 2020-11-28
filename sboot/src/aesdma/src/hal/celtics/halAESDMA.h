/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (��MStar Confidential Information��) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _HAL_AESDMA_H_
#define _HAL_AESDMA_H_


#define CONFIG_RIU_BASE_ADDRESS     0x1F000000
#define CONFIG_XIU_BASE_ADDRESS     0x1F600000
#define CONFIG_EMMC_BASE_ADDRESS    0x1FC00000

#ifndef TRUE
#define TRUE                        1
#endif

#ifndef FALSE
#define FALSE                       0
#endif

#ifndef U32
#define U32  unsigned long
#endif
#ifndef U16
#define U16  unsigned short
#endif
#ifndef U8
#define U8   unsigned char
#endif
#ifndef S32
#define S32  signed long
#endif
#ifndef S16
#define S16  signed short
#endif
#ifndef S8
#define S8   signed char
#endif

#define REG(Reg_Addr)           (*(volatile unsigned short *)(Reg_Addr))
#define SECURE_DEBUG(reg_addr, val)      REG((reg_addr)) = (val)
#define SECURE_DEBUG_REG		(CONFIG_RIU_BASE_ADDRESS + (0x100518 << 1))
#define ROM_AUTHEN_REG          (CONFIG_RIU_BASE_ADDRESS + (0x0038E0 << 1))

#define ALIGN_8(_x_)                (((_x_) + 7) & ~7)
#define RIU     ((unsigned short volatile *) CONFIG_RIU_BASE_ADDRESS)
#define RIU8    ((unsigned char  volatile *) CONFIG_RIU_BASE_ADDRESS)
#define XIU     ((unsigned int   volatile *) CONFIG_XIU_BASE_ADDRESS)
#define XIU8    ((unsigned char  volatile *) CONFIG_XIU_BASE_ADDRESS)


#define AESDMA_BASE_ADDR     (0x123C00)
#define SHARNG_BASE_ADDR     (0x123C00)
#define RSA_BASE_ADDR        (0x123C00)
#define DMA_SECURE_BASE_ADDR (0x113D00)
#define MAILBOX_BASE_ADDR    (0x103380)
#define POR_STATUS_BASE_ADDR (0x100500)

#define RSA_SIGNATURE_LEN                    (256)
#define SHA256_DIGEST_SIZE                   (32)

#define RSA_A_BASE_ADDR                      (0x80)
#define RSA_E_BASE_ADDR                      (0x00)
#define RSA_N_BASE_ADDR                      (0x40)
#define RSA_Z_BASE_ADDR                      (0xC0)

#define SECURE_RSA_OUT_DRAM_ADDRESS          (0x20109000)
#define SECURE_SHA_OUT_DRAM_ADDRESS          (0x20109100)
#define SECURE_RSA_OUT_SRAM_ADDRESS          (0x1FC03600)
#define SECURE_SHA_OUT_SRAM_ADDRESS          (0x1FC03680)
#define SECURE_WB_FIFO_OUT_ADDRESS           (0x1FC01C00)

#define SHARNG_CTRL_SHA_SEL_SHA256          0x0200
#define SHARNG_CTRL_SHA_CLR                 0x0040
#define SHARNG_CTRL_SHA_MSG_BLOCK_NUM       0x0001
#define SHARNG_CTRL_SHA_FIRE_ONCE           0x0001
#define SHARNG_CTRL_SHA_READY               0x0001
#define SHARNG_CTRL_SHA_RST                 0x0080
#define SHARNG_CTRL_SHA_BUSY                0x0002

#define RSA_INT_CLR                         0x0002
#define RSA_CTRL_RSA_RST                    0x0001
#define RSA_IND32_START                     0x0001
#define RSA_IND32_CTRL_DIRECTION_WRITE      0x0002
#define RSA_IND32_CTRL_ADDR_AUTO_INC        0x0004
#define RSA_IND32_CTRL_ACCESS_AUTO_START    0x0008
#define RSA_EXP_START                       0x0001
#define RSA_STATUS_RSA_BUSY                 0x0001
#define RSA_SEL_HW_KEY                      0x0002
#define RSA_SEL_PUBLIC_KEY                  0x0004

#define DMA_SECURE_CTRL_AES_SECURE_PROTECT  0x0001
#define DMA_SECURE_CTRL_AES_SECRET_KEY1     0x0020
#define DMA_SECURE_CTRL_AES_SECRET_KEY2     0x0040
#define DMA_SECURE_CTRL_WB2DMA_R_EN         0x0200
#define DMA_SECURE_CTRL_WB2DMA_W_EN         0x0100

#define AESDMA_CTRL_XIU_SEL_CA9             0x1000
#define AESDMA_CTRL_MIU_SEL_12M             0x8000
#define AESDMA_CTRL_SHA_FROM_IN             0x0100
#define AESDMA_CTRL_SHA_FROM_OUT            0x0200
#define AESDMA_CTRL_DMA_DONE                0x0001

#define AESDMA_CTRL_FILE_ST                 0x0001
#define AESDMA_CTRL_FOUT_EN                 0x0100
#define AESDMA_CTRL_CBC_MODE                0x2000
#define AESDMA_CTRL_CIPHER_DECRYPT          0x0200
#define AESDMA_CTRL_AES_EN                  0x0100
#define AESDMA_CTRL_USE_SECRET_KEY          0x1000

#define XIU_STATUS_W_RDY                    0x0001
#define XIU_STATUS_W_ERR                    0x0008
#define XIU_STATUS_W_LEN                    0x00F0
#define XIU_STATUS_R_RDY                    0x0100
#define XIU_STATUS_R_ERR                    0x0800
#define XIU_STATUS_R_LEN                    0xF000


void HAL_AESDMA_DisableXIUSelectCA9(void);
void HAL_AESDMA_WB2DMADisable(void);
void HAL_AESDMA_ShaFromOutput(void);
void HAL_AESDMA_ShaFromInput(void);
void HAL_AESDMA_SetXIULength(U32 u32Size);
void HAL_AESDMA_UseHwKey(void);
void HAL_AESDMA_CipherDecrypt(void);
void HAL_AESDMA_Disable(void);
void HAL_AESDMA_FileOutEnable(U8 u8FileOutEnable);
void HAL_AESDMA_SetFileinAddr(U32 u32addr);
void HAL_AESDMA_Start(U8 u8AESDMAStart);
U16 HAL_AESDMA_GetStatus(void);
void HAL_RSA_ClearInt(void);
void HAL_RSA_Reset(void);
void HAL_RSA_Ind32Ctrl(U8 u8dirction);
void HAL_RSA_LoadSiganature(U32 *ptr_Sign);
void HAL_RSA_LoadKeyE(U32 *ptr_E);
void HAL_RSA_LoadKeyN(U32 *ptr_N);
void HAL_RSA_SetKeyLength(U16 u16keylen);
void HAL_RSA_SetKeyType(U8 u8hwkey, U8 u8pubkey);
void HAL_RSA_ExponetialStart(void);
U16 HAL_RSA_GetStatus(void);
void HAL_RSA_FileOutStart(void);
void HAL_RSA_SetFileOutAddr(U32 u32offset);
U32 HAL_RSA_FileOut(void);
void HAL_SHA_Reset(void);
void HAL_SHA_SetLength(U32 u32Size);
void HAL_SHA_SelMode(U8 u8sha256);
U16 HAL_SHA_GetStatus(void);
void HAL_SHA_Clear(void);
void HAL_SHA_Out(U32 u32Buf);


#endif
