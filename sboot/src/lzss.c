//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
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
#ifdef __mips__
typedef unsigned char   U8;
typedef unsigned int   U16;
typedef unsigned long  U32;
#define NULL 0

#include "ms_decompress_priv.h"

#define RIU_MAP  0xBF000000
#define RIU      ((unsigned short volatile *) RIU_MAP)

#define BIT0        0x0001
#define BIT1        0x0002
#define BIT2        0x0004
#define BIT3        0x0008
#define BIT4        0x0010
#define BIT5        0x0020
#define BIT6        0x0040
#define BIT7        0x0080
#define BIT8        0x0100
#define BIT9        0x0200
#define BIT10       0x0400
#define BIT11       0x0800
#define BIT12       0x1000
#define BIT13       0x2000
#define BIT14       0x4000
#define BIT15       0x8000

#ifdef CONFIG_MSTAR_KAISER
#define AP_IN_FLASH_ADDR        0x94020000              //This address should be 4' alignment
#else
#define AP_IN_FLASH_ADDR    0xBFC20000        //This address should be 4' alignment
#endif

#define _ReadChar(A)\
{\
    A=(*pInStream << (8 - u32BitPos))|(*(pInStream+1)>>u32BitPos);\
    pInStream++;\
}

#define _ReadBit(A)\
{\
    u32BitPos--;\
    A = (*pInStream >> u32BitPos) & 0x01;\
    if(u32BitPos == 0)\
    {\
        u32BitPos = 8;\
        pInStream++;\
    }\
}

void DoLZSSDecompression(void);
void DoLZSSDecompression(void)
{
    U8 IsCompressMagicNumber = 0;
    U32 CompressedFileLength = 0;
    U32 u32ROM_START = *((U32 *)(AP_IN_FLASH_ADDR + 0));    //This address should be 4' alignment
    U32 i;

    // Check if this bin file is compressed format, find compress format magic number
    //*((U32 *)(0xbf206704)) = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+3));
    //*((U32 *)(0xbf206708)) = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+2));
    //*((U32 *)(0xbf20670C)) = *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+1));

    if ( ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+3)) == 0xDE )
    && ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+2)) == 0xAD )
    && ( *((U8 *)((u32ROM_START+COMPRESSED_LENGTH_POS-4)+1)) == 0xBE ) )
        IsCompressMagicNumber = 1;
    else
        IsCompressMagicNumber = 0;

    if ( IsCompressMagicNumber )
    {
        U32 u32RAM_START, u32RAM_END;

        //Compressed Format
        u32RAM_START = *((U32 *)(AP_IN_FLASH_ADDR + 4));    //This address should be 4' alignment
        u32RAM_END = *((U32 *)(AP_IN_FLASH_ADDR + 8));

        //Copy uncompressed part first
        for(i=0;i<((UNCOMPRESSED_LENGTH + 7) & ~7UL);i+=4)
        {
            *((U32 *)(u32RAM_START+i)) = *((U32 *)((U32)(u32ROM_START+i)));
        }

        //Copy compressed part second
        for(i=0;i<(((u32RAM_END-u32RAM_START-UNCOMPRESSED_LENGTH) + 7) & ~7UL);i+=4)
        {
            *((U32 *)(DECOMPRESS_BUF + i)) = *((U32 *)(u32ROM_START + UNCOMPRESSED_LENGTH + i));
        }

        CompressedFileLength=*((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+3));
        CompressedFileLength<<=8;
        CompressedFileLength|=*((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+2));
        CompressedFileLength<<=8;
        CompressedFileLength|=*((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+1));
        CompressedFileLength<<=8;
        CompressedFileLength|=*((U8 *)(u32RAM_START+COMPRESSED_LENGTH_POS+0));
        CompressedFileLength -= 2;

        // Start to decompress
        //if ( IsCompressMagicNumber )
        {

    #if 0
            static       U32 _u32BitPos = 0;
            static       U32 u32NextChar = 0;
            static       U8 *pOutStream;
            static       U32 _u32Offset = 0;
            static       U8 *pSlidingWindow;

            register      U32 i ;
            register      U32 offset,length;
            register      U32 mask=0xFFF;
            register      U32 u32BitPos = 0;
            register      U8 *pStreamEnd = NULL;
            register      U32 tmp0,tmp1;
    #else
            U32 _u32BitPos = 0;
            U32 u32NextChar = 0;
            U8 *pOutStream;
            U32 _u32Offset = 0;
            U8 *pSlidingWindow;

            //U32 i ;
            U32 offset,length;
            U32 mask=0xFFF;
            U32 u32BitPos = 0;
            U8 *pStreamEnd = NULL;
            U32 tmp0,tmp1;
    #endif

            U8 *pInStream;
            U32 u32DataLen;
            pSlidingWindow = (U8 *)(DECOMPRESS_BUF-WINDOW_SIZE);

            for(i=0;i<WINDOW_SIZE;i++)
            {
                *(pSlidingWindow+i)=0;
            }

            _u32BitPos = 8;
            u32NextChar = 1;
            _u32Offset = 0;

            {
                //pInStream = (U8 *)(DECOMPRESS_BUF+UNCOMPRESSED_LENGTH);
                pInStream = (U8 *)(DECOMPRESS_BUF);
                pOutStream = (U8 *)(u32RAM_START + UNCOMPRESSED_LENGTH);
                u32DataLen = CompressedFileLength - UNCOMPRESSED_LENGTH;

                u32BitPos = _u32BitPos;
                pInStream = pInStream;
                pStreamEnd = pInStream + u32DataLen;

                pInStream += _u32Offset;

                while (pInStream <= pStreamEnd)
                {
                    _ReadBit(tmp0);
                    if (tmp0 != UNCODED)
                    {
                        _ReadChar(tmp0);
                        _ReadChar(tmp1);
                        offset = (tmp0 << 8) | tmp1;
                        length = (offset & 0x0F) + 2;
                        offset >>= 4;
                        if ((u32NextChar+length) < WINDOW_SIZE)
                        {
                            for (i = 0; i < length; i++)
                            {
                                *pOutStream = pSlidingWindow[(offset+i) & mask];
                                pSlidingWindow[(u32NextChar+i)] = *pOutStream++;
                            }
                        }
                        else
                        {
                            for (i = 0; i < length; i++)
                            {
                                *pOutStream = pSlidingWindow[(offset+i) & mask];
                                pSlidingWindow[(u32NextChar+i) & mask] = *pOutStream++;
                            }
                        }
                        u32NextChar+=length;
                    }
                    else
                    {
                        _ReadChar(tmp0);
                        *pOutStream = tmp0;
                        pSlidingWindow[u32NextChar] = *pOutStream++;
                        u32NextChar++;
                    }
                    u32NextChar = u32NextChar & mask;
                }
            }
            //We don't use these two variables any more, so don't care their values at this time
            //        _u32BitPos = u32BitPos;
            //        _u32Offset = pInStream - pStreamEnd;
            //DeCompressedLength = pOutStream - pOutHead - sizeof(U32);
            //return (pOutStream - pOutHead);
        }
    }
    else
    {
        // Uncompressed format
        asm volatile (
        // Load ROM_START, RAM_START, RAM_END, ROM_END from 0xBFC20000
        #if defined( CONFIG_MSTAR_KAISERIN ) || defined( CONFIG_MSTAR_KAISER )
            "li      $15, 0x94020000;"
        #else
            "li      $15, 0xbfc20000;"
        #endif
            "lw      $8, 0($15);"
            "lw      $9, 4($15);"
            "lw      $10, 8($15);"
            "lw      $11, 12($15);"

        "1:;"
            "ld      $12, 0($8);"      //#ld=lw lw to save time
            "ld      $14, 8($8);"
            "sd      $12, 0($9);"
            "sd      $14, 8($9);"
            "addu    $8, $8, 16;"
            "addu    $9, $9, 16;"
            "bltu    $9, $10, 1b;"
            "nop;"
            :::"$15", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "memory"
        );
    }
}
#endif
