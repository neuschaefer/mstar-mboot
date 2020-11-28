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
//
// "Contains BIGDIGITS multiple-precision arithmetic code originally
// written by David Ireland, copyright (c) 2001-6 by D.I. Management
// Services Pty Limited <www.di-mgt.com.au>, and is used with
// permission."
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _RSA_H_
#define _RSA_H_

#ifdef CRYPTO_RSA_C
#define EXTERN 
#else
#define EXTERN extern
#endif

//-------------------------------------------------------------------------------------------------
// Type definition
//-------------------------------------------------------------------------------------------------
typedef unsigned int                DIGIT_T;
#define DIGIT_S                     sizeof(DIGIT_T)

#define RSA_KEY_DIGI_LEN            (256)                                // DIGIT_T count

#define REG_OTPKEY_RSA_N_LEN        (64*DIGIT_S)                        // 2048
#define REG_OTPKEY_RSA_E_LEN        (1 *DIGIT_S)                        // 32

typedef struct _Integer2048
{
    unsigned char                   Byte[256];
} Integer2048;

typedef struct _Integer128
{
    unsigned char                   Byte[16];
} Integer128;

typedef struct _Integer32
{
    unsigned char                   Byte[4];
} Integer32;

//-------------------------------------------------------------------------------------------------
// Extern prototype
//-------------------------------------------------------------------------------------------------

EXTERN int _mpConvFromOctets(DIGIT_T a[], int ndigits, const unsigned char *c, int nbytes);
EXTERN int _mpModExp(DIGIT_T yout[], const DIGIT_T x[], const DIGIT_T e[], const DIGIT_T m[], int ndigits);
EXTERN int _mpEqual(const DIGIT_T a[], const DIGIT_T b[], int ndigits);
EXTERN int _mpSquare(DIGIT_T w[], const DIGIT_T x[], int ndigits);
EXTERN int _mpMultiply(DIGIT_T w[], const DIGIT_T u[], const DIGIT_T v[], int ndigits);
EXTERN int _mpDivide(DIGIT_T q[], DIGIT_T r[], const DIGIT_T u[], int udigits, DIGIT_T v[], int vdigits);
EXTERN DIGIT_T _mpShortDiv(DIGIT_T q[], const DIGIT_T u[], DIGIT_T v, int ndigits);
EXTERN DIGIT_T _mpShiftLeft(DIGIT_T a[], const DIGIT_T *b, int shift, int ndigits);
EXTERN DIGIT_T _mpShiftRight(DIGIT_T a[], const DIGIT_T b[], int shift, int ndigits);
EXTERN int _spMultiply(DIGIT_T p[2], DIGIT_T x, DIGIT_T y);
EXTERN DIGIT_T _spDivide(DIGIT_T *q, DIGIT_T *r, const DIGIT_T u[2], DIGIT_T v);
EXTERN int rsa_main(unsigned char *Signature, unsigned char *PublicKey_N, unsigned char *PublicKey_E, unsigned char *Sim_SignOut);

#undef EXTERN

#endif // _RSA_H_

