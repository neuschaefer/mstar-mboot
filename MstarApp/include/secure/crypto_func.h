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

#ifndef _FUNC_H_
#define _FUNC_H_

typedef int (*FP_MP_MOD_EXP)(DIGIT_T yout[], const DIGIT_T x[], const DIGIT_T e[], const DIGIT_T m[], int ndigits);

typedef int (*FP_MP_CONV_FROM_OCTETS)(DIGIT_T a[], int ndigits, const unsigned char *c, int nbytes);

typedef int (*FP_MP_EQUAL)(const DIGIT_T a[], const DIGIT_T b[], int ndigits);

typedef void (*FP_MP_SETZERO)(const DIGIT_T a[], int ndigits);

typedef void (*FP_NULL)(void);

//int mpSquare(DIGIT_T w[], const DIGIT_T x[], int ndigits)
typedef int (*FP_MP_SQUARE)(DIGIT_T w[], const DIGIT_T x[], int ndigits);

//int mpMultiply(DIGIT_T w[], const DIGIT_T u[], const DIGIT_T v[], int ndigits)
typedef int (*FP_MP_MULTIPLY)(DIGIT_T w[], const DIGIT_T u[], const DIGIT_T v[], int ndigits);

//int mpDivide(DIGIT_T q[], DIGIT_T r[], const DIGIT_T u[], int udigits, DIGIT_T v[], int vdigits)
typedef int (*FP_MP_DIVIDE)(DIGIT_T q[], DIGIT_T r[], const DIGIT_T u[], int udigits, DIGIT_T v[], int vdigits);

//DIGIT_T mpShortDiv(DIGIT_T q[], const DIGIT_T u[], DIGIT_T v, int ndigits)
typedef DIGIT_T (*FP_MP_SHORT_DIV)(DIGIT_T q[], const DIGIT_T u[], DIGIT_T v, int ndigits);

//DIGIT_T mpShiftLeft(DIGIT_T a[], const DIGIT_T *b, int shift, int ndigits)
typedef DIGIT_T (*FP_MP_SHIFT_LEFT)(DIGIT_T a[], const DIGIT_T *b, int shift, int ndigits);

//DIGIT_T mpShiftRight(DIGIT_T a[], const DIGIT_T b[], int shift, int ndigits)
typedef DIGIT_T (*FP_MP_SHIFT_RIGHT)(DIGIT_T a[], const DIGIT_T b[], int shift, int ndigits);

//int spMultiply(DIGIT_T p[2], DIGIT_T x, DIGIT_T y)
typedef int (*FP_SP_MULTIPLY)(DIGIT_T p[2], DIGIT_T x, DIGIT_T y);

//DIGIT_T spDivide(DIGIT_T *q, DIGIT_T *r, const DIGIT_T u[2], DIGIT_T v)
typedef DIGIT_T (*FP_SP_DIVIDE)(DIGIT_T *q, DIGIT_T *r, const DIGIT_T u[2], DIGIT_T v);

typedef struct
{
    FP_MP_CONV_FROM_OCTETS ConvFromOctets;
    FP_MP_MOD_EXP       ModExp;
    FP_MP_EQUAL         Equal;

    FP_MP_SQUARE        Square;
    FP_MP_MULTIPLY      Multiply;
    FP_MP_DIVIDE        Divide;
    FP_MP_SHORT_DIV     ShortDiv;
    FP_MP_SHIFT_LEFT    ShiftLeft;
    FP_MP_SHIFT_RIGHT   ShiftRight;

    FP_SP_MULTIPLY      SpMultiply;
    FP_SP_DIVIDE        SpDivide;

    FP_NULL             reserve_1[13];
} MpFuncTbl;

extern MpFuncTbl        *mpFunc;
extern MpFuncTbl        _mpFunc;

#endif

