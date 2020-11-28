////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#define _MEMMAP_nonPM_  _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_     _RVM1(0x0000, 0x00, 0xFF)

#define _END_OF_TBL2_       0xFF, 0xFF

const U8 padInitTbl[] =
{
    0x39, 0xB6, 0x5B, 0x53,     // magic code for ISP_Tool

    // programable device number
    // spi flash count
    1 + (PIN_SPI_CZ1 != 0) + (PIN_SPI_CZ2 != 0) + (PIN_SPI_CZ3 != 0),
    0x00,                       // nor
    0x00,                       // nand
    0x00,                       // reserved
    0x00,                       // reserved
    0x00,                       // reserved

//---------------------------------------------------------------------
// GPIO Configuartion
//---------------------------------------------------------------------
    _MEMMAP_PM_,

    // SPI BUS
    #define SPI_CZ_IS_GPIO  (PAD_PM_SPI_CZ_IS_GPIO ? BIT1:0)

    #define SPI_BUS_IS_GPIO ((PAD_PM_SPI_CK_IS_GPIO | \
                              PAD_PM_SPI_DI_IS_GPIO | \
                              PAD_PM_SPI_DO_IS_GPIO) ? BIT0 :0)

    #define SPI_BUS_OEN     ((PAD_PM_SPI_CZ_IS_GPIO == GPIO_IN ? (1UL << 4) : 0) | \
                             (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? (1UL << 5) : 0) | \
                             (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? (1UL << 6) : 0) | \
                             (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? (1UL << 7) : 0))



    #define SPI_BUS_OUT     ((PAD_PM_SPI_CZ_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 4) : 0) | \
                             (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 5) : 0) | \
                             (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 6) : 0) | \
                             (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 7) : 0))

#if((PAD_PM_SPI_CZ_IS_GPIO != GPIO_NONE) && \
        (PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE) && \
        (PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE) && \
        (PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE))


        _RVM1(0x0E3A, SPI_BUS_OUT, BITMASK(7:4)),
        _RVM1(0x0E3C, SPI_BUS_OEN, BITMASK(7:4)),

        _RVM1(0x0E6A, SPI_CZ_IS_GPIO, BIT1),
        _RVM1(0x0E6A, SPI_BUS_IS_GPIO, BIT0),
#endif

    // IRIN
    #define IRIN_IS_GPIO    (PAD_IRIN_IS_GPIO ? BIT4: 0)
    #define IRIN_OEN        (PAD_IRIN_IS_GPIO == GPIO_IN ? (1UL << 0) : 0)
    #define IRIN_OUT        (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 0) : 0)

    _RVM1(0x0E3A, IRIN_OUT, BIT0),
    _RVM1(0x0E3C, IRIN_OEN, BIT0),
    _RVM1(0x0E38, IRIN_IS_GPIO, BIT4),

    // CEC
    #define CEC_IS_GPIO     (PAD_CEC_IS_GPIO ? BIT6: 0)
    #define CEC_OEN         (PAD_CEC_IS_GPIO == GPIO_IN ? (1UL << 2) : 0)
    #define CEC_OUT         (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 2) : 0)

    _RVM1(0x0E3A, CEC_OUT, BIT2),
    _RVM1(0x0E3C, CEC_OEN, BIT2),
    _RVM1(0x0E38, CEC_IS_GPIO, BIT6),

    // GPIO_PM0~GPIO_PM12
    #if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
        _RVM2(0x0e24, 0xBABE, 0xFFFF),
    #endif

    #define GPIO_PM6_IS_GPIO    (PAD_GPIO_PM6_IS_GPIO ? BIT2: 0)

    #if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
        _RVM1(0x0E6A, GPIO_PM6_IS_GPIO, BIT2),
    #endif


    #define GPIO_PM_OEN     ((PAD_GPIO_PM0_IS_GPIO == GPIO_IN ? (1UL <<  0) : 0) | \
                             (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? (1UL <<  1) : 0) | \
                             (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? (1UL <<  2) : 0) | \
                             (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? (1UL <<  3) : 0) | \
                             (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? (1UL <<  4) : 0) | \
                             (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? (1UL <<  5) : 0) | \
                             (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? (1UL <<  6) : 0) | \
                             (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? (1UL <<  7) : 0) | \
                             (PAD_GPIO_PM8_IS_GPIO == GPIO_IN ? (1UL <<  8) : 0) | \
                             (PAD_GPIO_PM9_IS_GPIO == GPIO_IN ? (1UL <<  9) : 0))

    #define GPIO_PM_OUT     ((PAD_GPIO_PM0_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  0) : 0) | \
                             (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  1) : 0) | \
                             (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  2) : 0) | \
                             (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  3) : 0) | \
                             (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  4) : 0) | \
                             (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  5) : 0) | \
                             (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  6) : 0) | \
                             (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  7) : 0) | \
                             (PAD_GPIO_PM8_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  8) : 0) | \
                             (PAD_GPIO_PM9_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  9) : 0))

    _RVM2(0x0E20, GPIO_PM_OUT, 0x03FF),
    _RVM2(0x0E1E, GPIO_PM_OEN, 0x03FF),



        // SAR
        // SAR
        #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT0),
        #endif
        #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT1),
        #endif
        #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT2),
        #endif
        #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT3),
        #endif

        #define SAR_OEN         ((PAD_SAR0_IS_GPIO == GPIO_IN ? (1UL <<  0) : 0) | \
                                 (PAD_SAR1_IS_GPIO == GPIO_IN ? (1UL <<  1) : 0) | \
                                 (PAD_SAR2_IS_GPIO == GPIO_IN ? (1UL <<  2) : 0) | \
                                 (PAD_SAR3_IS_GPIO == GPIO_IN ? (1UL <<  3) : 0))

        #define SAR_OUT         ((PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  0) : 0) | \
                                 (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  1) : 0) | \
                                 (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  2) : 0) | \
                                 (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  3) : 0))

        _RVM1(0x1424, SAR_OUT, BITMASK(3:0)),
        _RVM1(0x1423, SAR_OEN, BITMASK(3:0)),


    _MEMMAP_nonPM_,

// Script Generated GPIO

    #if(PAD_SM0_IO_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_IO_OEN (PAD_SM0_IO_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_IO_OUT (PAD_SM0_IO_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2500, PAD_SM0_IO_OUT, BIT4),
    _RVM1(0x2500, PAD_SM0_IO_OEN, BIT5),
    #endif

    #if(PAD_SM0_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_CLK_OEN (PAD_SM0_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_CLK_OUT (PAD_SM0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2502, PAD_SM0_CLK_OUT, BIT4),
    _RVM1(0x2502, PAD_SM0_CLK_OEN, BIT5),
    #endif

    #if(PAD_SM0_RST_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_RST_OEN (PAD_SM0_RST_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_RST_OUT (PAD_SM0_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2504, PAD_SM0_RST_OUT, BIT4),
    _RVM1(0x2504, PAD_SM0_RST_OEN, BIT5),
    #endif

    #if(PAD_SM0_CD_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_CD_OEN (PAD_SM0_CD_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_CD_OUT (PAD_SM0_CD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2506, PAD_SM0_CD_OUT, BIT4),
    _RVM1(0x2506, PAD_SM0_CD_OEN, BIT5),
    #endif

    #if(PAD_SM0_VCC_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_VCC_OEN (PAD_SM0_VCC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_VCC_OUT (PAD_SM0_VCC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2508, PAD_SM0_VCC_OUT, BIT4),
    _RVM1(0x2508, PAD_SM0_VCC_OEN, BIT5),
    #endif

    #if(PAD_SM0_GPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_GPIO0_OEN (PAD_SM0_GPIO0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_GPIO0_OUT (PAD_SM0_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x250a, PAD_SM0_GPIO0_OUT, BIT4),
    _RVM1(0x250a, PAD_SM0_GPIO0_OEN, BIT5),
    #endif

    #if(PAD_SM0_GPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_GPIO1_OEN (PAD_SM0_GPIO1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_GPIO1_OUT (PAD_SM0_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x250c, PAD_SM0_GPIO1_OUT, BIT4),
    _RVM1(0x250c, PAD_SM0_GPIO1_OEN, BIT5),
    #endif

    #if(PAD_SM1_IO_IS_GPIO != GPIO_NONE)
    #define PAD_SM1_IO_OEN (PAD_SM1_IO_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM1_IO_OUT (PAD_SM1_IO_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x250e, PAD_SM1_IO_OUT, BIT4),
    _RVM1(0x250e, PAD_SM1_IO_OEN, BIT5),
    #endif

    #if(PAD_I2CM0_SDA_IS_GPIO != GPIO_NONE)
    #define PAD_I2CM0_SDA_OEN (PAD_I2CM0_SDA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2CM0_SDA_OUT (PAD_I2CM0_SDA_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x251c, PAD_I2CM0_SDA_OUT, BIT4),
    _RVM1(0x251c, PAD_I2CM0_SDA_OEN, BIT5),
    #endif

    #if(PAD_I2CM0_SCL_IS_GPIO != GPIO_NONE)
    #define PAD_I2CM0_SCL_OEN (PAD_I2CM0_SCL_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2CM0_SCL_OUT (PAD_I2CM0_SCL_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x251e, PAD_I2CM0_SCL_OUT, BIT4),
    _RVM1(0x251e, PAD_I2CM0_SCL_OEN, BIT5),
    #endif

    #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2524, PAD_TS0_CLK_OUT, BIT4),
    _RVM1(0x2524, PAD_TS0_CLK_OEN, BIT5),
    #endif

    #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2526, PAD_TS0_VLD_OUT, BIT4),
    _RVM1(0x2526, PAD_TS0_VLD_OEN, BIT5),
    #endif

    #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2528, PAD_TS0_SYNC_OUT, BIT4),
    _RVM1(0x2528, PAD_TS0_SYNC_OEN, BIT5),
    #endif

    #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x252a, PAD_TS0_D7_OUT, BIT4),
    _RVM1(0x252a, PAD_TS0_D7_OEN, BIT5),
    #endif

    #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x252c, PAD_TS0_D6_OUT, BIT4),
    _RVM1(0x252c, PAD_TS0_D6_OEN, BIT5),
    #endif

    #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x252e, PAD_TS0_D5_OUT, BIT4),
    _RVM1(0x252e, PAD_TS0_D5_OEN, BIT5),
    #endif

    #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2530, PAD_TS0_D4_OUT, BIT4),
    _RVM1(0x2530, PAD_TS0_D4_OEN, BIT5),
    #endif

    #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2532, PAD_TS0_D3_OUT, BIT4),
    _RVM1(0x2532, PAD_TS0_D3_OEN, BIT5),
    #endif

    #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2534, PAD_TS0_D2_OUT, BIT4),
    _RVM1(0x2534, PAD_TS0_D2_OEN, BIT5),
    #endif

    #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2536, PAD_TS0_D1_OUT, BIT4),
    _RVM1(0x2536, PAD_TS0_D1_OEN, BIT5),
    #endif

    #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2538, PAD_TS0_D0_OUT, BIT4),
    _RVM1(0x2538, PAD_TS0_D0_OEN, BIT5),
    #endif

    #if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x253a, PAD_TS1_CLK_OUT, BIT4),
    _RVM1(0x253a, PAD_TS1_CLK_OEN, BIT5),
    #endif

    #if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x253c, PAD_TS1_SYNC_OUT, BIT4),
    _RVM1(0x253c, PAD_TS1_SYNC_OEN, BIT5),
    #endif

    #if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x253e, PAD_TS1_VLD_OUT, BIT4),
    _RVM1(0x253e, PAD_TS1_VLD_OEN, BIT5),
    #endif

    #if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2540, PAD_TS1_D7_OUT, BIT4),
    _RVM1(0x2540, PAD_TS1_D7_OEN, BIT5),
    #endif

    #if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2542, PAD_TS1_D6_OUT, BIT4),
    _RVM1(0x2542, PAD_TS1_D6_OEN, BIT5),
    #endif

    #if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2544, PAD_TS1_D5_OUT, BIT4),
    _RVM1(0x2544, PAD_TS1_D5_OEN, BIT5),
    #endif

    #if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2546, PAD_TS1_D4_OUT, BIT4),
    _RVM1(0x2546, PAD_TS1_D4_OEN, BIT5),
    #endif

    #if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2548, PAD_TS1_D3_OUT, BIT4),
    _RVM1(0x2548, PAD_TS1_D3_OEN, BIT5),
    #endif

    #if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x254a, PAD_TS1_D2_OUT, BIT4),
    _RVM1(0x254a, PAD_TS1_D2_OEN, BIT5),
    #endif

    #if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x254c, PAD_TS1_D1_OUT, BIT4),
    _RVM1(0x254c, PAD_TS1_D1_OEN, BIT5),
    #endif

    #if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x254e, PAD_TS1_D0_OUT, BIT4),
    _RVM1(0x254e, PAD_TS1_D0_OEN, BIT5),
    #endif

    #if(PAD_NF_CEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NF_CEZ_OEN (PAD_NF_CEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_NF_CEZ_OUT (PAD_NF_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2558, PAD_NF_CEZ_OUT, BIT4),
    _RVM1(0x2558, PAD_NF_CEZ_OEN, BIT5),
    #endif

    #if(PAD_CI_A14_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A14_OEN (PAD_CI_A14_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A14_OUT (PAD_CI_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x255a, PAD_CI_A14_OUT, BIT4),
    _RVM1(0x255a, PAD_CI_A14_OEN, BIT5),
    #endif

    #if(PAD_CI_A13_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A13_OEN (PAD_CI_A13_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A13_OUT (PAD_CI_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x255c, PAD_CI_A13_OUT, BIT4),
    _RVM1(0x255c, PAD_CI_A13_OEN, BIT5),
    #endif

    #if(PAD_CI_A12_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A12_OEN (PAD_CI_A12_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A12_OUT (PAD_CI_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x255e, PAD_CI_A12_OUT, BIT4),
    _RVM1(0x255e, PAD_CI_A12_OEN, BIT5),
    #endif

    #if(PAD_CI_A11_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A11_OEN (PAD_CI_A11_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A11_OUT (PAD_CI_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2560, PAD_CI_A11_OUT, BIT4),
    _RVM1(0x2560, PAD_CI_A11_OEN, BIT5),
    #endif

    #if(PAD_CI_A10_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A10_OEN (PAD_CI_A10_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A10_OUT (PAD_CI_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2562, PAD_CI_A10_OUT, BIT4),
    _RVM1(0x2562, PAD_CI_A10_OEN, BIT5),
    #endif

    #if(PAD_CI_A9_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A9_OEN (PAD_CI_A9_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A9_OUT (PAD_CI_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2564, PAD_CI_A9_OUT, BIT4),
    _RVM1(0x2564, PAD_CI_A9_OEN, BIT5),
    #endif

    #if(PAD_CI_A8_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A8_OEN (PAD_CI_A8_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A8_OUT (PAD_CI_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2566, PAD_CI_A8_OUT, BIT4),
    _RVM1(0x2566, PAD_CI_A8_OEN, BIT5),
    #endif

    #if(PAD_CI_A7_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A7_OEN (PAD_CI_A7_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A7_OUT (PAD_CI_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2568, PAD_CI_A7_OUT, BIT4),
    _RVM1(0x2568, PAD_CI_A7_OEN, BIT5),
    #endif

    #if(PAD_CI_A6_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A6_OEN (PAD_CI_A6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A6_OUT (PAD_CI_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x256a, PAD_CI_A6_OUT, BIT4),
    _RVM1(0x256a, PAD_CI_A6_OEN, BIT5),
    #endif

    #if(PAD_CI_A5_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A5_OEN (PAD_CI_A5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A5_OUT (PAD_CI_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x256c, PAD_CI_A5_OUT, BIT4),
    _RVM1(0x256c, PAD_CI_A5_OEN, BIT5),
    #endif

    #if(PAD_CI_A4_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A4_OEN (PAD_CI_A4_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A4_OUT (PAD_CI_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x256e, PAD_CI_A4_OUT, BIT4),
    _RVM1(0x256e, PAD_CI_A4_OEN, BIT5),
    #endif

    #if(PAD_CI_A3_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A3_OEN (PAD_CI_A3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A3_OUT (PAD_CI_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2570, PAD_CI_A3_OUT, BIT4),
    _RVM1(0x2570, PAD_CI_A3_OEN, BIT5),
    #endif

    #if(PAD_CI_A2_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A2_OEN (PAD_CI_A2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A2_OUT (PAD_CI_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2572, PAD_CI_A2_OUT, BIT4),
    _RVM1(0x2572, PAD_CI_A2_OEN, BIT5),
    #endif

    #if(PAD_CI_A1_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A1_OEN (PAD_CI_A1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A1_OUT (PAD_CI_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2574, PAD_CI_A1_OUT, BIT4),
    _RVM1(0x2574, PAD_CI_A1_OEN, BIT5),
    #endif

    #if(PAD_CI_A0_IS_GPIO != GPIO_NONE)
    #define PAD_CI_A0_OEN (PAD_CI_A0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_A0_OUT (PAD_CI_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2576, PAD_CI_A0_OUT, BIT4),
    _RVM1(0x2576, PAD_CI_A0_OEN, BIT5),
    #endif

    #if(PAD_CI_D7_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D7_OEN (PAD_CI_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D7_OUT (PAD_CI_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2578, PAD_CI_D7_OUT, BIT4),
    _RVM1(0x2578, PAD_CI_D7_OEN, BIT5),
    #endif

    #if(PAD_CI_D6_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D6_OEN (PAD_CI_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D6_OUT (PAD_CI_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x257a, PAD_CI_D6_OUT, BIT4),
    _RVM1(0x257a, PAD_CI_D6_OEN, BIT5),
    #endif

    #if(PAD_CI_D5_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D5_OEN (PAD_CI_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D5_OUT (PAD_CI_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x257c, PAD_CI_D5_OUT, BIT4),
    _RVM1(0x257c, PAD_CI_D5_OEN, BIT5),
    #endif

    #if(PAD_CI_D4_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D4_OEN (PAD_CI_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D4_OUT (PAD_CI_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x257e, PAD_CI_D4_OUT, BIT4),
    _RVM1(0x257e, PAD_CI_D4_OEN, BIT5),
    #endif

    #if(PAD_CI_D3_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D3_OEN (PAD_CI_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D3_OUT (PAD_CI_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2580, PAD_CI_D3_OUT, BIT4),
    _RVM1(0x2580, PAD_CI_D3_OEN, BIT5),
    #endif

    #if(PAD_CI_D2_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D2_OEN (PAD_CI_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D2_OUT (PAD_CI_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2582, PAD_CI_D2_OUT, BIT4),
    _RVM1(0x2582, PAD_CI_D2_OEN, BIT5),
    #endif

    #if(PAD_CI_D1_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D1_OEN (PAD_CI_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D1_OUT (PAD_CI_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2584, PAD_CI_D1_OUT, BIT4),
    _RVM1(0x2584, PAD_CI_D1_OEN, BIT5),
    #endif

    #if(PAD_CI_D0_IS_GPIO != GPIO_NONE)
    #define PAD_CI_D0_OEN (PAD_CI_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_D0_OUT (PAD_CI_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2586, PAD_CI_D0_OUT, BIT4),
    _RVM1(0x2586, PAD_CI_D0_OEN, BIT5),
    #endif

    #if(PAD_CI_IORDZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_IORDZ_OEN (PAD_CI_IORDZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_IORDZ_OUT (PAD_CI_IORDZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2588, PAD_CI_IORDZ_OUT, BIT4),
    _RVM1(0x2588, PAD_CI_IORDZ_OEN, BIT5),
    #endif

    #if(PAD_CI_IOWRZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_IOWRZ_OEN (PAD_CI_IOWRZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_IOWRZ_OUT (PAD_CI_IOWRZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x258a, PAD_CI_IOWRZ_OUT, BIT4),
    _RVM1(0x258a, PAD_CI_IOWRZ_OEN, BIT5),
    #endif

    #if(PAD_CI_OEZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_OEZ_OEN (PAD_CI_OEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_OEZ_OUT (PAD_CI_OEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x258c, PAD_CI_OEZ_OUT, BIT4),
    _RVM1(0x258c, PAD_CI_OEZ_OEN, BIT5),
    #endif

    #if(PAD_CI_WEZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_WEZ_OEN (PAD_CI_WEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_WEZ_OUT (PAD_CI_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x258e, PAD_CI_WEZ_OUT, BIT4),
    _RVM1(0x258e, PAD_CI_WEZ_OEN, BIT5),
    #endif

    #if(PAD_CI_REGZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_REGZ_OEN (PAD_CI_REGZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_REGZ_OUT (PAD_CI_REGZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2590, PAD_CI_REGZ_OUT, BIT4),
    _RVM1(0x2590, PAD_CI_REGZ_OEN, BIT5),
    #endif

    #if(PAD_CI_CEZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_CEZ_OEN (PAD_CI_CEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_CEZ_OUT (PAD_CI_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2592, PAD_CI_CEZ_OUT, BIT4),
    _RVM1(0x2592, PAD_CI_CEZ_OEN, BIT5),
    #endif

    #if(PAD_CI_IRQAZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_IRQAZ_OEN (PAD_CI_IRQAZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_IRQAZ_OUT (PAD_CI_IRQAZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2594, PAD_CI_IRQAZ_OUT, BIT4),
    _RVM1(0x2594, PAD_CI_IRQAZ_OEN, BIT5),
    #endif

    #if(PAD_CI_WAITZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_WAITZ_OEN (PAD_CI_WAITZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_WAITZ_OUT (PAD_CI_WAITZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2596, PAD_CI_WAITZ_OUT, BIT4),
    _RVM1(0x2596, PAD_CI_WAITZ_OEN, BIT5),
    #endif

    #if(PAD_CI_RST_IS_GPIO != GPIO_NONE)
    #define PAD_CI_RST_OEN (PAD_CI_RST_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_RST_OUT (PAD_CI_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2598, PAD_CI_RST_OUT, BIT4),
    _RVM1(0x2598, PAD_CI_RST_OEN, BIT5),
    #endif

    #if(PAD_CI_CDZ_IS_GPIO != GPIO_NONE)
    #define PAD_CI_CDZ_OEN (PAD_CI_CDZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_CI_CDZ_OUT (PAD_CI_CDZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x259a, PAD_CI_CDZ_OUT, BIT4),
    _RVM1(0x259a, PAD_CI_CDZ_OEN, BIT5),
    #endif

    #if(PAD_AGC_UP_IS_GPIO != GPIO_NONE)
    #define PAD_AGC_UP_OEN (PAD_AGC_UP_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_AGC_UP_OUT (PAD_AGC_UP_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2600, PAD_AGC_UP_OUT, BIT4),
    _RVM1(0x2600, PAD_AGC_UP_OEN, BIT5),
    #endif

    #if(PAD_AGC_DOWN_IS_GPIO != GPIO_NONE)
    #define PAD_AGC_DOWN_OEN (PAD_AGC_DOWN_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_AGC_DOWN_OUT (PAD_AGC_DOWN_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2602, PAD_AGC_DOWN_OUT, BIT4),
    _RVM1(0x2602, PAD_AGC_DOWN_OEN, BIT5),
    #endif

    #if(PAD_ET_CRS_IS_GPIO != GPIO_NONE)
    #define PAD_ET_CRS_OEN (PAD_ET_CRS_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_CRS_OUT (PAD_ET_CRS_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2604, PAD_ET_CRS_OUT, BIT4),
    _RVM1(0x2604, PAD_ET_CRS_OEN, BIT5),
    #endif

    #if(PAD_ET_COL_IS_GPIO != GPIO_NONE)
    #define PAD_ET_COL_OEN (PAD_ET_COL_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_COL_OUT (PAD_ET_COL_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2606, PAD_ET_COL_OUT, BIT4),
    _RVM1(0x2606, PAD_ET_COL_OEN, BIT5),
    #endif

    #if(PAD_ET_TXD3_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXD3_OEN (PAD_ET_TXD3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXD3_OUT (PAD_ET_TXD3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2608, PAD_ET_TXD3_OUT, BIT4),
    _RVM1(0x2608, PAD_ET_TXD3_OEN, BIT5),
    #endif

    #if(PAD_ET_TXD2_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXD2_OEN (PAD_ET_TXD2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXD2_OUT (PAD_ET_TXD2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x260a, PAD_ET_TXD2_OUT, BIT4),
    _RVM1(0x260a, PAD_ET_TXD2_OEN, BIT5),
    #endif

    #if(PAD_ET_TXD1_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXD1_OEN (PAD_ET_TXD1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXD1_OUT (PAD_ET_TXD1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x260c, PAD_ET_TXD1_OUT, BIT4),
    _RVM1(0x260c, PAD_ET_TXD1_OEN, BIT5),
    #endif

    #if(PAD_ET_TXD0_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXD0_OEN (PAD_ET_TXD0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXD0_OUT (PAD_ET_TXD0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x260e, PAD_ET_TXD0_OUT, BIT4),
    _RVM1(0x260e, PAD_ET_TXD0_OEN, BIT5),
    #endif

    #if(PAD_ET_TX_EN_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TX_EN_OEN (PAD_ET_TX_EN_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TX_EN_OUT (PAD_ET_TX_EN_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2610, PAD_ET_TX_EN_OUT, BIT4),
    _RVM1(0x2610, PAD_ET_TX_EN_OEN, BIT5),
    #endif

    #if(PAD_ET_TX_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TX_CLK_OEN (PAD_ET_TX_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TX_CLK_OUT (PAD_ET_TX_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2612, PAD_ET_TX_CLK_OUT, BIT4),
    _RVM1(0x2612, PAD_ET_TX_CLK_OEN, BIT5),
    #endif

    #if(PAD_ET_TXER_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXER_OEN (PAD_ET_TXER_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXER_OUT (PAD_ET_TXER_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2614, PAD_ET_TXER_OUT, BIT4),
    _RVM1(0x2614, PAD_ET_TXER_OEN, BIT5),
    #endif

    #if(PAD_ET_RXER_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXER_OEN (PAD_ET_RXER_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXER_OUT (PAD_ET_RXER_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2616, PAD_ET_RXER_OUT, BIT4),
    _RVM1(0x2616, PAD_ET_RXER_OEN, BIT5),
    #endif

    #if(PAD_ET_RX_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RX_CLK_OEN (PAD_ET_RX_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RX_CLK_OUT (PAD_ET_RX_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2618, PAD_ET_RX_CLK_OUT, BIT4),
    _RVM1(0x2618, PAD_ET_RX_CLK_OEN, BIT5),
    #endif

    #if(PAD_ET_RX_DV_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RX_DV_OEN (PAD_ET_RX_DV_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RX_DV_OUT (PAD_ET_RX_DV_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x261a, PAD_ET_RX_DV_OUT, BIT4),
    _RVM1(0x261a, PAD_ET_RX_DV_OEN, BIT5),
    #endif

    #if(PAD_ET_RXD0_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXD0_OEN (PAD_ET_RXD0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXD0_OUT (PAD_ET_RXD0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x261c, PAD_ET_RXD0_OUT, BIT4),
    _RVM1(0x261c, PAD_ET_RXD0_OEN, BIT5),
    #endif

    #if(PAD_ET_RXD1_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXD1_OEN (PAD_ET_RXD1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXD1_OUT (PAD_ET_RXD1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x261e, PAD_ET_RXD1_OUT, BIT4),
    _RVM1(0x261e, PAD_ET_RXD1_OEN, BIT5),
    #endif

    #if(PAD_ET_RXD2_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXD2_OEN (PAD_ET_RXD2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXD2_OUT (PAD_ET_RXD2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2620, PAD_ET_RXD2_OUT, BIT4),
    _RVM1(0x2620, PAD_ET_RXD2_OEN, BIT5),
    #endif

    #if(PAD_ET_RXD3_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXD3_OEN (PAD_ET_RXD3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXD3_OUT (PAD_ET_RXD3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2622, PAD_ET_RXD3_OUT, BIT4),
    _RVM1(0x2622, PAD_ET_RXD3_OEN, BIT5),
    #endif

    #if(PAD_ET_MDC_IS_GPIO != GPIO_NONE)
    #define PAD_ET_MDC_OEN (PAD_ET_MDC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_MDC_OUT (PAD_ET_MDC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2624, PAD_ET_MDC_OUT, BIT4),
    _RVM1(0x2624, PAD_ET_MDC_OEN, BIT5),
    #endif

    #if(PAD_ET_MDIO_IS_GPIO != GPIO_NONE)
    #define PAD_ET_MDIO_OEN (PAD_ET_MDIO_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_MDIO_OUT (PAD_ET_MDIO_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2626, PAD_ET_MDIO_OUT, BIT4),
    _RVM1(0x2626, PAD_ET_MDIO_OEN, BIT5),
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x262c, PAD_SPDIF_OUT_OUT, BIT4),
    _RVM1(0x262d, PAD_SPDIF_OUT_OEN, BIT0),
    #endif

    #if(PAD_SPDIF_OUT2_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_OUT2_OEN (PAD_SPDIF_OUT2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SPDIF_OUT2_OUT (PAD_SPDIF_OUT2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x262c, PAD_SPDIF_OUT2_OUT, BIT5),
    _RVM1(0x262d, PAD_SPDIF_OUT2_OEN, BIT1),
    #endif

    #if(PAD_HSYNC_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_HSYNC_OUT_OEN (PAD_HSYNC_OUT_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_HSYNC_OUT_OUT (PAD_HSYNC_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x263c, PAD_HSYNC_OUT_OUT, BIT4),
    _RVM1(0x263c, PAD_HSYNC_OUT_OEN, BIT5),
    #endif

    #if(PAD_VSYNC_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_VSYNC_OUT_OEN (PAD_VSYNC_OUT_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_VSYNC_OUT_OUT (PAD_VSYNC_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x263e, PAD_VSYNC_OUT_OUT, BIT4),
    _RVM1(0x263e, PAD_VSYNC_OUT_OEN, BIT5),
    #endif

    #if(PAD_S_GPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_S_GPIO0_OEN (PAD_S_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_S_GPIO0_OUT (PAD_S_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e40, PAD_S_GPIO0_OUT, BIT0),
    _RVM1(0x1e41, PAD_S_GPIO0_OEN, BIT0),
    #endif

    #if(PAD_S_GPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_S_GPIO1_OEN (PAD_S_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_S_GPIO1_OUT (PAD_S_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e40, PAD_S_GPIO1_OUT, BIT1),
    _RVM1(0x1e41, PAD_S_GPIO1_OEN, BIT1),
    #endif

    #if(PAD_S_GPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_S_GPIO2_OEN (PAD_S_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_S_GPIO2_OUT (PAD_S_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e40, PAD_S_GPIO2_OUT, BIT2),
    _RVM1(0x1e41, PAD_S_GPIO2_OEN, BIT2),
    #endif

    #if(PAD_S_GPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_S_GPIO3_OEN (PAD_S_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_S_GPIO3_OUT (PAD_S_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e40, PAD_S_GPIO3_OUT, BIT3),
    _RVM1(0x1e41, PAD_S_GPIO3_OEN, BIT3),
    #endif

    #if(PAD_S_GPIO4_IS_GPIO != GPIO_NONE)
    #define PAD_S_GPIO4_OEN (PAD_S_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_S_GPIO4_OUT (PAD_S_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e40, PAD_S_GPIO4_OUT, BIT4),
    _RVM1(0x1e41, PAD_S_GPIO4_OEN, BIT4),
    #endif

    #if(PAD_S_GPIO5_IS_GPIO != GPIO_NONE)
    #define PAD_S_GPIO5_OEN (PAD_S_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_S_GPIO5_OUT (PAD_S_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e40, PAD_S_GPIO5_OUT, BIT5),
    _RVM1(0x1e41, PAD_S_GPIO5_OEN, BIT5),
    #endif


//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
    _MEMMAP_PM_,

    #define IRIN_USE_PM5 ((PADS_PM5_IS_IRIN==1)? BIT0 : 0) //reg_qfp156_mode

    _RVM1(0x0E50, IRIN_USE_PM5, BIT0),

    _MEMMAP_nonPM_,

    #define SM0_OPEN ((PADS_SM0_OPEN == PAD_SM0_CLK) ? (BIT0) : \
                      (PADS_SM0_OPEN == PAD_SM0_RST ) ? (BIT0) : 0)

    _RVM1(0x1E18, SM0_OPEN, BIT0),

    #define SM0_C48 ((PADS_SM0_C48 == PAD_SM0_GPIO0) ? (BIT4) : \
                     (PADS_SM0_C48 == PAD_SM0_GPIO1) ? (BIT4) : 0)

    _RVM1(0x1E18, SM0_C48, BIT4),

    #define SM0_EN  ((PADS_SM0_EN == PAD_SM0_IO) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_CLK) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_RST) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_CD) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_VCC) ? (BIT0) : 0)

    _RVM1(0x1E19, SM0_EN, BIT0),

/*
    #define SM1_OPEN ((PADS_SM1_OPEN == PAD_SM1_RST ) ? (BIT0) : \
                      (PADS_SM1_OPEN == PAD_SM1_CLK) ? (BIT0) : \
                      (PADS_SM1_OPEN == PAD_TS1_CLK) ? (BIT1) : \
                      (PADS_SM1_OPEN == PAD_TS1_D6) ? (BIT1) : 0)

    _RVM1(0x1E1A, SM1_OPEN, BIT1|BIT0),

     #define SM1_C48 ((PADS_SM1_C48 == PAD_SM1_GPIO0 ) ? (BIT4) : \
                      (PADS_SM1_C48 == PAD_SM1_GPIO1) ? (BIT4) : \
                      (PADS_SM1_C48 == PAD_TS1_D7) ? (BIT5) : \
                      (PADS_SM1_C48 == PAD_TS1_D6) ? (BIT5) : 0)

    _RVM1(0x1E1A, SM1_C48, BIT5|BIT4),

    #define SM1_EN  ((PADS_SM1_EN == PAD_SM1_RST  ) ? (BIT0) : \
                      (PADS_SM1_EN == PAD_SM1_CD) ? (BIT0) : \
                      (PADS_SM1_EN == PAD_SM1_VCC) ? (BIT0) : \
                      (PADS_SM1_EN == PAD_SM1_GPIO0) ? (BIT1) : \
                      (PADS_SM1_EN == PAD_SM1_GPIO1) ? (BIT1) : \
                      (PADS_SM1_EN == PAD_TS1_CLK) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_SYNC) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_VLD) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_D7) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_D6) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E1B, SM1_EN, BIT1|BIT0),
*/

    #define I2CM0_MODE ((PADS_I2CM0_MODE == PAD_I2CM0_SDA  ) ? (BIT0) : \
                      (PADS_I2CM0_MODE == PAD_I2CM0_SCL) ? (BIT0) : \
                      (PADS_I2CM0_MODE == PAD_SM0_IO) ? (BIT1) : \
                      (PADS_I2CM0_MODE == PAD_SM0_CLK) ? (BIT1) : \
                      (PADS_I2CM0_MODE == PAD_CI_CEZ) ? (BIT1|BIT0) : \
                      (PADS_I2CM0_MODE == PAD_CI_IRQAZ) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E12, I2CM0_MODE, BIT1|BIT0),
/*
    #define I2CM1_MODE ((PADS_I2CM0_MODE == PAD_I2CM1_SCL) ? (BIT4) : \
                        (PADS_I2CM0_MODE == PAD_I2CM1_SDA) ? (BIT4) : \
                        (PADS_I2CM0_MODE == PAD_ET_TXD1) ? (BIT5) : \
                        (PADS_I2CM0_MODE == PAD_ET_TXD0) ? (BIT5) : \
                        (PADS_I2CM0_MODE == PAD_TS0_D5) ? (BIT5|BIT4) : \
                        (PADS_I2CM0_MODE == PAD_TS0_D4) ? (BIT5|BIT4) : \
                        (PADS_I2CM0_MODE == PAD_TS1_D5) ? (BIT6) : \
                        (PADS_I2CM0_MODE == PAD_TS1_D4) ? (BIT6) : 0)

    _RVM1(0x1E12, I2CM1_MODE, BITMASK(6:4)),
*/
    #define TS0_MODE ((PADS_TS0_MODE == PAD_TS0_CLK) ? (BIT0) : \
                      (PADS_TS0_MODE == PAD_TS0_D7) ? (BIT1) : \
                      (PADS_TS0_MODE == PAD_TS0_D0) ? (BIT1|BIT0) : \
                      (PADS_TS0_MODE == PAD_CI_D3) ? (BIT2) : \
                      (PADS_TS0_MODE == PAD_CI_D2) ? (BIT2|BIT0) : \
                      (PADS_TS0_MODE == PAD_CI_A14) ? (BIT2|BIT1) : 0)

    _RVM1(0x1E04, TS0_MODE, BITMASK(2:0)),

    #define TS1_MODE ((PADS_TS1_MODE == PAD_TS1_CLK) ? (BIT4) : \
                      (PADS_TS1_MODE == PAD_TS1_D7) ? (BIT5) : \
                      (PADS_TS1_MODE == PAD_TS1_D0) ? (BIT5|BIT4) : \
                      (PADS_TS1_MODE == PAD_CI_A6) ? (BIT6) : \
                      (PADS_TS1_MODE == PAD_CI_A7) ? (BIT6|BIT4) : \
                      (PADS_TS1_MODE == PAD_CI_A12) ? (BIT6|BIT5) : \
                      (PADS_TS1_MODE == PAD_CI_A4) ? (BIT6|BIT5|BIT4) : 0)

    _RVM1(0x1E04, TS1_MODE, BITMASK(6:4)),
/*
    #define TS2_MODE ((PADS_TS2_MODE == PAD_TS2_CLK) ? (BIT0) : \
                      (PADS_TS2_MODE == PAD_I2S_OUT_SD0) ? (BIT1) : 0)

    _RVM1(0x1E05, TS2_MODE, BITMASK(1:0)),
*/
    #define NAND_MODE ((PADS_NAND_MODE == PAD_TS1_VLD) ? (BIT0) : \
                       (PADS_NAND_MODE == PAD_TS0_D7) ? (BIT1) : \
                       (PADS_NAND_MODE == PAD_S_GPIO4) ? (BIT1|BIT0) : \
                       (PADS_NAND_MODE == PAD_CI_A5) ? (BIT2|BIT0) : 0)
//                       (PADS_NAND_MODE == PAD_PF_A21) ? (BIT2) :

    _RVM1(0x1E0C, NAND_MODE, BITMASK(3:0)),

    #define CI_MODE ((PADS_CI_MODE == PAD_CI_A14) ? (BIT0) : 0)

    _RVM1(0x1E0E, CI_MODE, BIT0),

    #define CCIR_OUT_MODE ((PADS_CCIR_OUT_MODE == PAD_TS0_CLK) ? (BIT4) : 0)

    _RVM1(0x1E10, CCIR_OUT_MODE, BIT4),

    #define CCIR_IN_MODE ((PADS_CCIR_IN_MODE == PAD_TS0_CLK) ? (BIT0) : 0)

    _RVM1(0x1E10, CCIR_OUT_MODE, BIT0),

    #define PANEL_IF_MODE ((PADS_PANEL_IF_MODE == PAD_CI_A12) ? (BIT0) : 0)

    _RVM1(0x1E11, PANEL_IF_MODE, BIT0),

    #define SPDIF_OUT_MODE ((PADS_SPDIF_OUT_MODE == PAD_CI_A12) ? (BIT4) : \
                            (PADS_SPDIF_OUT_MODE == PAD_TS0_CLK) ? (BIT5) : \
                            (PADS_SPDIF_OUT_MODE == PAD_SPDIF_OUT) ? (BIT5|BIT4) : \
                            (PADS_SPDIF_OUT_MODE == PAD_TS1_D6) ? (BIT6) : \
                            (PADS_SPDIF_OUT_MODE == PAD_SM0_CD) ? (BIT6|BIT4) : 0)

    _RVM1(0x1E0A, SPDIF_OUT_MODE, BITMASK(6:4)),

    #define SPDIF_IN_MODE ((PADS_SPDIF_IN_MODE == PAD_CI_A12) ? (BIT0) : \
                            (PADS_SPDIF_IN_MODE == PAD_CI_A12) ? (BIT1) : \
                            (PADS_SPDIF_IN_MODE == PAD_SPDIF_OUT) ? (BIT1|BIT0) : \
                            (PADS_SPDIF_IN_MODE == PAD_TS1_D6) ? (BIT2) : \
                            (PADS_SPDIF_IN_MODE == PAD_SM0_CD) ? (BIT2|BIT0) : 0)

    _RVM1(0x1E0A, SPDIF_IN_MODE, BITMASK(2:0)),

//    #define I2S_IN_MODE ((PADS_I2S_IN_MODE == PAD_SM1_RST ) ? (BIT0) :
    #define I2S_IN_MODE ((PADS_I2S_IN_MODE == PAD_TS1_CLK) ? (BIT1|BIT0) : 0)


    _RVM1(0x1E0B, I2S_IN_MODE, BITMASK(1:0)),

//    #define I2S_OUT_MUTE_MODE ((PADS_I2S_OUT_MUTE_MODE == PAD_I2S_OUT_SD3 ) ? (BIT5) : 0)

//    _RVM1(0x1E11, I2S_OUT_MUTE_MODE, BIT5),

//    #define I2S_OUT_MODE ((PADS_I2S_OUT_MODE == PAD_TS1_CLK) ? (BIT6|BIT5) : 0)

//    _RVM1(0x1E0B, I2S_OUT_MODE, BITMASK(6:5)),

/*
    #define MPIF_MODE ((PADS_MPIF_MODE == PAD_TS1_CLK) ? (BIT4) : \
                       (PADS_MPIF_MODE == PAD_ET_TXD1) ? (BIT5) : 0)
                       (PADS_MPIF_MODE == PAD_PF_A5) ? (BIT6) :
                       (PADS_MPIF_MODE == PAD_PF_A14) ? (BIT6|BIT4) : 0)
*/

//    _RVM1(0x1E0E, MPIF_MODE, BITMASK(6:4)),

    #define SDIO_MODE ((PADS_SDIO_MODE == PAD_TS1_CLK) ? (BIT4) : \
                       (PADS_SDIO_MODE == PAD_ET_TXD1) ? (BIT5) : 0)
//                       (PADS_SDIO_MODE == PAD_PF_A5) ? (BIT6) :
//                       (PADS_SDIO_MODE == PAD_PF_A14) ? (BIT6|BIT4) : 0)


    _RVM1(0x1E0C, SDIO_MODE, BITMASK(6:4)),

    #define ET_MODE ((PADS_ET_MODE == PAD_ET_CRS) ? (BIT0) : \
                       (PADS_ET_MODE == PAD_ET_TXD1) ? (BIT1) : 0)
//                       (PADS_ET_MODE == PAD_PF_A14) ? (BIT1|BIT0) :
//                       (PADS_ET_MODE == PAD_PF_A3) ? (BIT2) : 0)

    _RVM1(0x1E0F, ET_MODE, BITMASK(2:0)),

//    #define RF_AGC_EN ((PADS_RF_AGC_EN == PAD_RF_AGC) ? (BIT1) : 0)

//    _RVM1(0x1E3A, RF_AGC_EN, BIT1),

//    #define IF_AGC_EN ((PADS_IF_AGC_EN == PAD_IF_AGC) ? (BIT0) : 0)

//    _RVM1(0x1E3A, IF_AGC_EN, BIT0),

    #define MODEM_MODE ((PADS_MODEM_MODE == PAD_TS0_D3) ? (BIT4) : \
                        (PADS_MODEM_MODE == PAD_TS1_CLK) ? (BIT5) : \
                        (PADS_MODEM_MODE == PAD_CI_A14) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E0F, MODEM_MODE, BITMASK(5:4)),

    #define PWM_MODE ((PADS_PWM_MODE == PAD_HSYNC_OUT) ? (BIT0) : \
                        (PADS_PWM_MODE == PAD_VSYNC_OUT) ? (BIT0) : 0)

    _RVM1(0x1E13, PWM_MODE, BIT0),

//    #define PF_CS1_EN ((PADS_PF_CS1_EN == PAD_PF_A25) ? (BIT0) : 0)

//    _RVM1(0x1E1E, PF_CS1_EN, BIT0),

    #define HSYNC_EN ((PADS_HSYNC_EN == PAD_HSYNC_OUT) ? (BIT0) : 0)

    _RVM1(0x1E16, HSYNC_EN, BIT0),

    #define VSYNC_EN ((PADS_VSYNC_EN == PAD_VSYNC_OUT) ? (BIT4) : 0)

    _RVM1(0x1E16, VSYNC_EN, BIT4),

    // UART MUX
    #define SECOND_UART_MODE ((PADS_SECOND_UART_MODE == PAD_HSYNC_OUT) ? (BIT0) : \
                        (PADS_SECOND_UART_MODE == PAD_VSYNC_OUT) ? (BIT0) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM0_SDA) ? (BIT1) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM0_SCL) ? (BIT1) : \
                        (PADS_SECOND_UART_MODE == PAD_TS1_CLK) ? (BIT2) : \
                        (PADS_SECOND_UART_MODE == PAD_TS1_SYNC) ? (BIT2) : 0)
//                        (PADS_SECOND_UART_MODE == PAD_I2CM1_SCL) ? (BIT1|BIT0) :
//                        (PADS_SECOND_UART_MODE == PAD_I2CM1_SDA) ? (BIT1|BIT0) :

    _RVM1(0x1E06, SECOND_UART_MODE, BITMASK(2:0)),

    #define THIRD_UART_MODE ((PADS_THIRD_UART_MODE == PAD_TS1_D7) ? (BIT4) : \
                           (PADS_THIRD_UART_MODE == PAD_TS1_D6) ? (BIT4) : 0)
//                           (PADS_THIRD_UART_MODE == PAD_PF_A4) ? (BIT5) :
//                           (PADS_THIRD_UART_MODE == PAD_PF_A3) ? (BIT5) : 0)
//                           (PADS_THIRD_UART_MODE == PAD_I2S_OUT_SD2) ? (BIT5|BIT4) :
//                           (PADS_THIRD_UART_MODE == PAD_I2S_OUT_SD3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E06, THIRD_UART_MODE, BITMASK(5:4)),

    #define FOURTH_UART_MODE ((PADS_FOURTH_UART_MODE == PAD_ET_RXD2) ? (BIT0) : \
                           (PADS_FOURTH_UART_MODE == PAD_ET_RXD3) ? (BIT0) : \
                           (PADS_FOURTH_UART_MODE == PAD_TS0_D1) ? (BIT1) : \
                           (PADS_FOURTH_UART_MODE == PAD_TS0_D0) ? (BIT1) : \
                           (PADS_FOURTH_UART_MODE == PAD_HSYNC_OUT) ? (BIT1|BIT0) : \
                           (PADS_FOURTH_UART_MODE == PAD_VSYNC_OUT) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E07, FOURTH_UART_MODE, BITMASK(1:0)),
//---------------------------------------------------------------------
// Kronus U02 to fix smart card problem in 216 pin package
//---------------------------------------------------------------------
#if (MS_BOARD_TYPE_SEL != BD_MST124E_D01A_S && MS_BOARD_TYPE_SEL != BD_MST124E_D01A_SZ)
    _RVM1(0x1E45, 0, BIT2), // reg_156_mode set to 0 if the package is not 156 pin for SMC
#endif
//---------------------------------------------------------------------
    // UART_SRC_SEL
    #define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                         (UART1_INV ? BIT1 : 0) | \
                         (UART2_INV ? BIT2 : 0) | \
                         (UART3_INV ? BIT3 : 0) | \
                         (UART4_INV ? BIT4 : 0))

    _RVM1(0x1EAB, UART_INV, BITMASK(4:0)),
    _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
    _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
    _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),

    _MEMMAP_PM_,

    _RVM1(0x0E13, BIT3, BIT3),   // RX0_ENABLE
    _RVM1(0x0E13, 0 , BIT4),   // UART0 -> reg_uart_sel0
#if 0
    #define SEL_CZ_ON   ((PIN_SPI_CZ1 ? BIT5 : 0) | \
                         (PIN_SPI_CZ2 ? BIT6 : 0) | \
                         (PIN_SPI_CZ3 ? BIT7 : 0))

    _RVM1(0x3C1D, ~(SEL_CZ_ON), BITMASK(7:5)),
#endif
    _MEMMAP_nonPM_,

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL2_,

//---------------------------------------------------------------------
// ISP_TOOL Write Protect (Need to check ????)
//---------------------------------------------------------------------
#if ((MS_BOARD_TYPE_SEL==BD_MST098E_D01A) || (MS_BOARD_TYPE_SEL==BD_MST098E_D01B) || (MS_BOARD_TYPE_SEL==BD_ZDT300_V01))
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
    #if (PIN_FLASH_WP0)
    _RVM1(0x0E6A, BIT2, BIT2), //configure spi_cz1/gpio_pm[6] as GPIO
    _RVM1(0x0E1E,    0, BIT6), //set dir as output
    _RVM1(0x0E20, BIT6, BIT6), //set output high
    #endif
    _END_OF_TBL2_,
#elif ((MS_BOARD_TYPE_SEL==BD_MST124A_D01A_S) || (MS_BOARD_TYPE_SEL==BD_MST124B_D01A_S) || (MS_BOARD_TYPE_SEL==BD_MST124A_D02A_S))
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
    #if (PIN_FLASH_WP0)
    _RVM1(0x0E20, BIT0, BIT0), //set gpio_pm[0] output high
    _RVM1(0x0E1E,    0, BIT0), //set gpio_pm[0] dir as output
    #endif
    _END_OF_TBL2_,

#else
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
    #if (PIN_FLASH_WP0)
    _RVM1(0x0E21, BIT0, BIT0),
    _RVM1(0x0E1F,    0, BIT0),
    #endif
    _END_OF_TBL2_,

    //external flash #2
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    #if (PIN_SPI_CZ1)
    _RVM1(0x0E6A, 0x00, BIT2), //reg_spicsz1_gpio set to 0 (enable spi_cz1)
    _RVM1(0x08F4, 0x01, 0xFF), //reg_chip_select set to 1 (select external flash #1)
    #if (PIN_FLASH_WP1)
    _RVM1(0x0E21, BIT0, BIT0),
    _RVM1(0x0E1F,    0, BIT0),
    #endif
    _END_OF_TBL2_,
    #endif
#endif
};

//-----------------------------------------------------------------
// Sanity check for PAD_TOP setting (TODO)
//-----------------------------------------------------------------

#if (UART0_SRC_SEL == UART1_SRC_SEL) || \
    (UART0_SRC_SEL == UART2_SRC_SEL) || \
    (UART1_SRC_SEL == UART2_SRC_SEL)
    #error "UART src selection conflict"
#endif



