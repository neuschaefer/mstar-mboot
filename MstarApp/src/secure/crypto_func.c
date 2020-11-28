////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
////////////////////////////////////////////////////////////////////////////////

#include <secure/crypto_rsa.h>
#include <secure/crypto_sha.h>
#include <secure/crypto_func.h>

// mpFunc Table
void _Null(void) { while (1) ;}

MpFuncTbl _mpFunc =
{
    _mpConvFromOctets,
    _mpModExp,
    _mpEqual,

    _mpSquare,
    _mpMultiply,
    _mpDivide,
    _mpShortDiv,
    _mpShiftLeft,
    _mpShiftRight,
    _spMultiply,
    _spDivide,

   { _Null, _Null, _Null, _Null, _Null, _Null, _Null, _Null,
    _Null, _Null, _Null, _Null, _Null},
};

MpFuncTbl *mpFunc = &_mpFunc;

