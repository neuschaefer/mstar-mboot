//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2014 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///@file Datatype.h
///@brief Datatype defination
///@author MStarSemi Inc.
///
/// Define datatype in this file.
///
///////////////////////////////////////////////////////////////////////////////
#ifndef __DATATYPE_H
#define __DATATYPE_H

#include <stdio.h>

///////////////////////////////////////////////////////////////////
//     Char definition    : 2 bytes font talbe
///////////////////////////////////////////////////////////////////
#define CHAR_RETURNICON                 0x0019
#define CHAR_ENTERICON                  0x001A
#define CHAR_MOVEICON                   0x001B
#define CHAR_UP                         0x001C
#define CHAR_DOWN                       0x001D
#define CHAR_LEFT                       0x001E
#define CHAR_RIGHT                      0x001F
#define CHAR_SPACE                      0x0020
#define CHAR_PERCENT                    0x0025
#define CHAR_APOSTROPHE                 0x0027
#define CHAR_LEFT_QUOTE                 0x0028
#define CHAR_RIGHT_QUOTE                0x0029
#define CHAR_STAR                       0x002A
#define CHAR_PLUS                       0x002B
#define CHAR_COMMA                      0x002C
#define CHAR_MINUS                      0x002D
#define CHAR_DOT                        0x002E
#define CHAR_SLASH                      0x002F
#define CHAR_0                          0x0030
#define CHAR_1                          0x0031
#define CHAR_2                          0x0032
#define CHAR_3                          0x0033
#define CHAR_4                          0x0034
#define CHAR_5                          0x0035
#define CHAR_6                          0x0036
#define CHAR_7                          0x0037
#define CHAR_8                          0x0038
#define CHAR_9                          0x0039
#define CHAR_COLON                      0x003A
#define CHAR_GT                         0x003E
#define CHAR_QM                         0x003F
#define CHAR_AT                         0x0040
#define CHAR_A                          0x0041
#define CHAR_B                          0x0042
#define CHAR_C                          0x0043
#define CHAR_D                          0x0044
#define CHAR_E                          0x0045
#define CHAR_F                          0x0046
#define CHAR_G                          0x0047
#define CHAR_H                          0x0048
#define CHAR_I                          0x0049
#define CHAR_J                          0x004A
#define CHAR_K                          0x004B
#define CHAR_L                          0x004C
#define CHAR_M                          0x004D
#define CHAR_N                          0x004E
#define CHAR_O                          0x004F
#define CHAR_P                          0x0050
#define CHAR_Q                          0x0051
#define CHAR_R                          0x0052
#define CHAR_S                          0x0053
#define CHAR_T                          0x0054
#define CHAR_U                          0x0055
#define CHAR_V                          0x0056
#define CHAR_W                          0x0057
#define CHAR_X                          0x0058
#define CHAR_Y                          0x0059
#define CHAR_Z                          0x005A
#define CHAR_LEFT_BRACKET               0x005B
#define CHAR_RIGHT_BRACKET              0x005D
#define CHAR_US                         0x005f
#define CHAR_a                          0x0061
#define CHAR_b                          0x0062
#define CHAR_c                          0x0063
#define CHAR_d                          0x0064
#define CHAR_e                          0x0065
#define CHAR_f                          0x0066
#define CHAR_g                          0x0067
#define CHAR_h                          0x0068
#define CHAR_i                          0x0069
#define CHAR_j                          0x006A
#define CHAR_k                          0x006B
#define CHAR_l                          0x006C
#define CHAR_m                          0x006D
#define CHAR_n                          0x006E
#define CHAR_o                          0x006F
#define CHAR_p                          0x0070
#define CHAR_q                          0x0071
#define CHAR_r                          0x0072
#define CHAR_s                          0x0073
#define CHAR_t                          0x0074
#define CHAR_u                          0x0075
#define CHAR_v                          0x0076
#define CHAR_w                          0x0077
#define CHAR_x                          0x0078
#define CHAR_y                          0x0079
#define CHAR_z                          0x007A
#define CHAR_wave                       0x007E

#define CHAR_CC                         0x010D
#define CHAR_SIGNAL                     0x0121
//extended ASCII
#define CHAR_EXT_C                      0x00C7
#define CHAR_EXT_c                      0x00E7
#define CHAR_EXT_e                      0x00E9
#define CHAR_EXT_e2                     0x00E8
#define CHAR_EXT_e3                     0x00EA
#define CHAR_EXT_e4                     0x00EB
#define CHAR_EXT_E2                     0x00C8
#define CHAR_EXT_E3                     0x00C9
#define CHAR_EXT_O                      0x00D3
#define CHAR_EXT_a                      0x00E1
#define CHAR_EXT_a1                     0x00E0
#define CHAR_EXT_a2                     0x00E2
#define CHAR_EXT_A                      0x00C1
#define CHAR_EXT_u                      0x00FA
#define CHAR_EXT_U                      0x00DA
#define CHAR_EXT_n                      0x00F1
#define CHAR_EXT_N                      0x00D1
#define CHAR_EXT_I                      0x00CD
#define CHAR_EXT_i                      0x00ED
#define CHAR_EXT_i2                     0x00EE
#define CHAR_EXT_o                      0x00F3
#define CHAR_DOWN_ARROW                 0x2193
//KOREA Font UNICODE
#define CHAR_KOREAN_AM1                 0xc624
#define CHAR_KOREAN_AM2                 0xc804
#define CHAR_KOREAN_PM1                 0xc624
#define CHAR_KOREAN_PM2                 0xd6c4

#define CHAR_KOREAN_YEAR                0xB144
#define CHAR_KOREAN_MONTH               0xC6D4
#define CHAR_KOREAN_DAY                 0xC77C

#undef NULL
#define NULL                            0

#if defined(__cplusplus)
    #define MST_BEGIN_DECL              extern "C" {
    #define MST_END_DECL                }
#else
    #define MST_BEGIN_DECL
    #define MST_END_DECL
#endif

#define MST_MACRO_START                 do {
#define MST_MACRO_END                   } while (0)

/********************************************************************************/
/* Primitive types                                                              */
/********************************************************************************/

#if defined(__aeon__) || defined(__mips__) || defined(__arm__)

    #define WORDS_LITTLEENDIAN

    extern unsigned long RIU_MAP;

    #define RIU                         ((unsigned short volatile *) RIU_MAP)
    #define RIU8                        ((unsigned char  volatile *) RIU_MAP)

    #define REG8(a)                     RIU8[((a) * 2) - ((a) & 1)]

    // C51 extension keyword
    #define xdata
    #define code
    #define bit  U8
    #define _AT_(x)

    #define DATA
    #define IDATA
    #define PDATA
    #define XDATA
    #define RDATA

    //typedef unsigned char  BIT;

    typedef unsigned char               U8;
    typedef unsigned short              U16;
    typedef unsigned long               U32;
    typedef signed char                 S8;
    typedef signed short                S16;
    typedef signed long                 S32;

    typedef U8                          UINT8;
    typedef U16                         UINT16;
    typedef U32                         UINT32;

    typedef U8                          U_INT8;
    typedef U16                         U_INT16;
    typedef U32                         U_INT32;

    typedef U16                         FAST_U8;
    typedef U16                         FAST_U16;
    typedef U32                         FAST_U32;
    typedef S16                         FAST_S8;
    typedef S16                         FAST_S16;
    typedef S32                         FAST_S32;

#else

    #error "primitive types are not defined"

#endif

/// Data type unsigned char
typedef unsigned char                   UCHAR;
/// Data type unsigned char
typedef unsigned char                   BYTE;
/// Data type unsigned int
typedef unsigned int                    UINT;
/// Data type unsigned int
typedef unsigned short                  WORD;    // 16bit
/// Data type unsigned long
typedef unsigned long                   ULONG;
/// Data type unsigned long
typedef unsigned long                   DWORD;

#ifndef NULL
#define NULL                            (void *)0
#endif

typedef U8                              BOOLEAN;   ///< BOOLEAN
#define BOOL                            BOOLEAN

#define HIBYTE(value)                   ((BYTE)((value) / 0x100))
#define LOBYTE(value)                   ((BYTE)(value))
#define MAKEWORD(value1, value2)        (((WORD)(value1)) * 0x100) + (value2)
#define HINIBBLE(value)                 ((value) >> 4)
#define LONIBBLE(value)                 ((value) & 0x0f)

typedef struct
{
    BYTE    bBOOL_0: 1;
    BYTE    bBOOL_1: 1;
    BYTE    bBOOL_2: 1;
    BYTE    bBOOL_3: 1;
    BYTE    bBOOL_4: 1;
    BYTE    bBOOL_5: 1;
    BYTE    bBOOL_6: 1;
    BYTE    bBOOL_7: 1;

} BOOLEANS;

/********************************************************************************/
/* Macro for endianess                                                          */
/********************************************************************************/

#define ReadU16BE(b)                    (((U16)((b)[0])<<8)|((b)[1]))
#define ReadU24BE(b)                    (((U32)((b)[0])<<16)|((U32)((b)[1])<<8)|((b)[2])))
#define ReadU32BE(b)                    (((U32)((b)[0])<<24)|((U32)((b)[1])<<16)|((U32)((b)[2])<<8)|((b)[3]))
#define ReadU16LE(b)                    (((b)[0])|((U16)((b)[1])<<8))
#define ReadU24LE(b)                    (((b)[0])|((U32)((b)[1])<<8)|((U32)((b)[2])<<16))
#define ReadU32LE(b)                    (((b)[0])|((U32)((b)[1])<<8)|((U32)((b)[2])<<16)|((U32)((b)[3])<<24))

//#define Swap16(x)                     MDrv_ByteSwapU16(x)
//#define Swap32(x)                     MDrv_ByteSwapU32(x)
#define Swap16(x)                       ((x << 8) | (x >> 8))
#define Swap32(x) \
    ((x >> 24) | ((x & 0x00FF0000) >>  8) | \
     ((x & 0x0000FF00) <<  8) | (x << 24))

#define ByteSwap16(x)                   (((x) & 0x00ff) << 8 | ((x) & 0xff00) >> 8)
#define ByteSwap32(x) \
    ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) | \
     (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

#ifdef WORDS_BIGENDIAN
    #define BE2ME16(x)                  (x)
    #define BE2ME32(x)                  (x)
    #define LE2ME16(x)                  ByteSwap16(x)
    #define LE2ME32(x)                  ByteSwap32(x)
    #define ME2BE16(x)                  (x)
    #define ME2BE32(x)                  (x)
    #define ME2LE16(x)                  ByteSwap16(x)
    #define ME2LE32(x)                  ByteSwap32(x)
#else
    #define BE2ME16(x)                  ByteSwap16(x)
    #define BE2ME32(x)                  ByteSwap32(x)
    #define LE2ME16(x)                  (x)
    #define LE2ME32(x)                  (x)
    #define ME2BE16(x)                  ByteSwap16(x)
    #define ME2BE32(x)                  ByteSwap32(x)
    #define ME2LE16(x)                  (x)
    #define ME2LE32(x)                  (x)
#endif

/********************************************************************************/
/* Macro for TDA1236D                                                             */
/********************************************************************************/
#define Data8                           U8
#define Data16                          S16
#define Data32                          S32
#define bool                            BOOLEAN
#define Bool                            BOOLEAN
#ifndef true
#define true                            TRUE
#endif
#ifndef false
#define false                           FALSE
#endif

/******************************************************************************/
/* Macro for bitwise                                                          */
/******************************************************************************/
#define _BITMASK(loc_msb, loc_lsb)      ((1U << (loc_msb)) - (1U << (loc_lsb)) + (1U << (loc_msb)))
#define BITMASK(x)                      _BITMASK(1?x, 0?x)
#define BITFLAG(loc)                    (1U << (loc))

#ifdef BIT0
#undef BIT0
#endif
#ifdef BIT1
#undef BIT1
#endif
#ifdef BIT2
#undef BIT2
#endif
#ifdef BIT3
#undef BIT3
#endif
#ifdef BIT4
#undef BIT4
#endif
#ifdef BIT5
#undef BIT5
#endif
#ifdef BIT6
#undef BIT6
#endif
#ifdef BIT7
#undef BIT7
#endif
#ifdef BIT8
#undef BIT8
#endif
#ifdef BIT9
#undef BIT9
#endif
#ifdef BIT6
#undef BIT6
#endif
#ifdef BIT10
#undef BIT10
#endif
#ifdef BIT11
#undef BIT11
#endif
#ifdef BIT12
#undef BIT12
#endif
#ifdef BIT13
#undef BIT13
#endif
#ifdef BIT14
#undef BIT14
#endif
#ifdef BIT15
#undef BIT15
#endif
#ifdef BIT16
#undef BIT16
#endif
#ifdef BIT17
#undef BIT17
#endif
#ifdef BIT18
#undef BIT18
#endif
#ifdef BIT19
#undef BIT19
#endif
#ifdef BIT20
#undef BIT20
#endif
#ifdef BIT21
#undef BIT21
#endif
#ifdef BIT22
#undef BIT22
#endif
#ifdef BIT23
#undef BIT23
#endif
#ifdef BIT24
#undef BIT24
#endif
#ifdef BIT25
#undef BIT25
#endif
#ifdef BIT26
#undef BIT26
#endif
#ifdef BIT27
#undef BIT27
#endif
#ifdef BIT28
#undef BIT28
#endif
#ifdef BIT29
#undef BIT29
#endif
#ifdef BIT30
#undef BIT30
#endif
#ifdef BIT31
#undef BIT31
#endif

#define BIT0                            0x0001
#define BIT1                            0x0002
#define BIT2                            0x0004
#define BIT3                            0x0008
#define BIT4                            0x0010
#define BIT5                            0x0020
#define BIT6                            0x0040
#define BIT7                            0x0080
#define BIT8                            0x0100
#define BIT9                            0x0200
#define BIT10                           0x0400
#define BIT11                           0x0800
#define BIT12                           0x1000
#define BIT13                           0x2000
#define BIT14                           0x4000
#define BIT15                           0x8000
#define BIT16                           0x00010000
#define BIT17                           0x00020000
#define BIT18                           0x00040000
#define BIT19                           0x00080000
#define BIT20                           0x00100000
#define BIT21                           0x00200000
#define BIT22                           0x00400000
#define BIT23                           0x00800000
#define BIT24                           0x01000000
#define BIT25                           0x02000000
#define BIT26                           0x04000000
#define BIT27                           0x08000000
#define BIT28                           0x10000000
#define BIT29                           0x20000000
#define BIT30                           0x40000000
#define BIT31                           0x80000000

#define SETBIT(REG, BIT)                ((REG) |= (1UL << (BIT)))
#define CLRBIT(REG, BIT)                ((REG) &= ~(1UL << (BIT)))
#define GETBIT(REG, BIT)                (((REG) >> (BIT)) & 0x01UL)
#define COMPLEMENT(a)                   (~(a))

#define _bit0_(val)                     ((bit)(val & BIT0))
#define _bit1_(val)                     ((bit)(val & BIT1))
#define _bit2_(val)                     ((bit)(val & BIT2))
#define _bit3_(val)                     ((bit)(val & BIT3))
#define _bit4_(val)                     ((bit)(val & BIT4))
#define _bit5_(val)                     ((bit)(val & BIT5))
#define _bit6_(val)                     ((bit)(val & BIT6))
#define _bit7_(val)                     ((bit)(val & BIT7))
#define _bit8_(val)                     ((bit)(val & BIT8))
#define _bit9_(val)                     ((bit)(val & BIT9))
#define _bit10_(val)                    ((bit)(val & BIT10))
#define _bit11_(val)                    ((bit)(val & BIT11))
#define _bit12_(val)                    ((bit)(val & BIT12))
#define _bit13_(val)                    ((bit)(val & BIT13))
#define _bit14_(val)                    ((bit)(val & BIT14))
#define _bit15_(val)                    ((bit)(val & BIT15))

/********************************************************************************/
/********************************************************************************/
//S7 BDMA SRC/TGT device   //T3 fpga test
#define DRAM_MIU_0                      0x40
#define DRAM_MIU_1                      0x41
#define PATTERN_SEARCH                  0x02
#define CRC32                           0x03
#define PATTERN_FILL                    0x44
#define SPI_FLASH                       0x45
#define NA_RESERVED                     0x06
#define VDMCU                           0x07
#define DSP                             0x08
#define TSP_MCU                         0x09

/// define MSRET U8
typedef U8 MSRET;
/// MS Return Error
#define MSRET_ERROR                     0
/// MS Return OK
#define MSRET_OK                        1

/// defination for FALSE
#define FALSE                           0
/// defination for TRUE
#define TRUE                            1

#define DISABLE                         0
#define ENABLE                          1

/// 0: FAIL
#define FAIL                            0
/// 1: PASS
#define PASS                            1

/// 0: NO
#define NO                              0
/// 1: YES
#define YES                             1

/// 0: WRITE
#define WRITE                           0
/// 1: READ
#define READ                            1


#define FE_NOT_LOCK                     0
#define FE_LOCK                         1
#define FE_AGC_NOT_LOCK                 2


#define NONE_HIGHLIGHT                  0
#define HIGHLIGHT                       1

#define HIU16(u32)                      ((U16)((u32)>>16))
#define LOU16(u32)                      ((U16)(u32))


#define LOWBYTE(u16)                    ((U8)(u16))
#define HIGHBYTE(u16)                   ((U8)((u16) >> 8))
#define HIGHNIBBLE(u8)                  ((u8) >> 4)
#define LOWNIBBLE(u8)                   ((u8) & 0x0F)
#define BCD2Dec(x)                      ((((x) >> 4) * 10) + ((x) & 0x0F))
#define DEC2BCD(x)                      ((((x) / 10) * 16) + ((x) % 10))

/// Font handle, handle to font table in memory
typedef S8                              FONTHANDLE;
/// Bitmap handle, handle to bitmap buffer
typedef S16                             BMPHANDLE;
typedef S8                              DBHANDLE;

#define INVALID_FONTHANDLE              -1
#define INVALID_BMPHANDLE               -1
#define INVALID_DBHANDLE                -1

// NOTE. these have problem with long integer (32-bit) on C51
#ifndef MAX
#define MAX(a, b)                       (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a ,b)                       (((a) < (b)) ? (a) : (b))
#endif

#define _MAX( a, b )                    (((a) >= (b)) * (a) + ((b) > (a)) * (b))
#define _MIN( a, b )                    (((a) <= (b)) * (a) + ((b) < (a)) * (b))

#define _CONCAT( a, b )                 a##b
#define CONCAT( a, b )                  _CONCAT( a, b )

#define COUNTOF( array )                (sizeof(array) / sizeof((array)[0]))

#define UNUSED( var )                   ((void)(var))

//extern U32 MDrv_ByteSwapU32(U32 val);
//extern U16 MDrv_ByteSwapU16(U16 val);

#define _PA2VA(x)                       (MS_U32) MsOS_PA2KSEG1((x))
#define _VA2PA(x)                       (MS_U32) MsOS_VA2PA((x))

#endif /* __DATATYPE_H */
