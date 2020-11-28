/*
  Copyright (C) 2006-2009 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmddNT220x.c
 *
 *                3
 *
 * \date          %modify_time%
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                NT220x_Driver_User_Guide.pdf
 *
 * Detailed description may be added here.
 *
 * \section info Change Information
 *
*/

/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#include "../../inc/tmNxTypes.h"
#include "../../inc/tmCompId.h"
#include "../../inc/tmFrontEnd.h"
#include "../../inc/tmbslFrontEndTypes.h"
#include "../../inc/tmUnitParams.h"

/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#include "../inc/tmddNT220x.h"
#include "tmddNT220xlocal.h"

#include "tmddNT220xInstance.h"

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

typedef struct _tmNT220x_CAL_Map_t {
    UInt8   Cal_number;
    UInt32  Cal_Freq[4];
    Int8    CprogOffset_Val[4];
} tmNT220x_CAL_Map_t, *ptmNT220x_CAL_Map_t;

typedef struct _tmNT220x_Freq_ROM_Map_t {
    UInt32  uRF_Max;
    UInt8   uCprog;
    UInt8   uGainTapper;
    UInt8   uRFBand;
} tmNT220x_Freq_ROM_Map_t, *ptmNT220x_Freq_ROM_Map_t;


#define NT220x_FREQ_ROM_MAP_ROW (565)

/* cal number / freq for index = 0 / freq for index = 1 / freq for index = 2 / freq for index = 3 / cprog_delta / cprog_offset / cprog_offset_0 / cprog_offset_1 / cprog_offset_2 / cprog_offset_3 */
static tmNT220x_CAL_Map_t NT220x_Cal_Map[NT220x_RFCAL_PROG_ROW] =
{
    { 0, { 52224000, 56320000, 44032000, 48128000 }, { 15, 0, 10, 17 } },
    { 1, { 93184000, 97280000, 84992000, 89088000 }, { 1, 0, -2, 3 } },
    { 2, { 115712000, 123904000, 106496000, 111616000 }, { 0, -1, 1, 2 } },
    { 3, { 169984000, 174080000, 161792000, 165888000 }, { 3, 0, 1, 2 } },
    { 4, { 232448000, 235520000, 224256000, 228352000 }, { 3, 0, 1, 2 } },
    { 5, { 322560000, 335872000, 301056000, 312320000 }, { 0, -1, 1, 2 } },
    { 6, { 397312000, 401408000, 389120000, 393216000 }, { -2, 0, -1, 1 } },
    { 7, { 465920000, 471040000, 455680000, 460800000 }, { 0, -2, -3, 1 } },
    { 8, { 570368000, 577536000, 555008000, 563200000 }, { -1, 0, -3, -2 } },
    { 9, { 658432000, 662528000, 647168000, 652288000 }, { -6, -3, 0, -5 } },
    { 10, { 762880000, 770048000, 748544000, 755712000 }, { -6, -3, 0, -5 } },
    { 11, { 809984000, 818176000, 792576000, 801792000 }, { -5, -2, 0, -4 } }
};

static tmNT220x_Freq_ROM_Map_t NT220x_Freq_ROM_Map[NT220x_FREQ_ROM_MAP_ROW] =
{
    { 39936000, 0xFF, 0x17, 0 },
    { 40960000, 0xFD, 0x17, 0 },
    { 41984000, 0xF1, 0x15, 0 },
    { 43008000, 0xE5, 0x13, 0 },
    { 44032000, 0xDB, 0x13, 0 },
    { 45056000, 0xD1, 0x12, 0 },
    { 46080000, 0xC7, 0x10, 0 },
    { 47104000, 0xBE, 0x0F, 0 },
    { 48128000, 0xB5, 0x0F, 0 },
    { 49152000, 0xAD, 0x0F, 0 },
    { 50176000, 0xA6, 0x0F, 0 },
    { 51200000, 0x9F, 0x0F, 0 },
    { 52224000, 0x98, 0x0F, 0 },
    { 53248000, 0x91, 0x0F, 0 },
    { 54272000, 0x8B, 0x0F, 0 },
    { 55296000, 0x86, 0x0F, 0 },
    { 56320000, 0x80, 0x0F, 0 },
    { 57344000, 0x7B, 0x0E, 0 },
    { 58368000, 0x76, 0x0E, 0 },
    { 59392000, 0x72, 0x0D, 0 },
    { 60416000, 0x6D, 0x0D, 0 },
    { 61440000, 0x69, 0x0C, 0 },
    { 62464000, 0x65, 0x0C, 0 },
    { 63488000, 0x61, 0x0B, 0 },
    { 64512000, 0x5E, 0x0B, 0 },
    { 64512000, 0x5A, 0x0B, 0 },
    { 65536000, 0x57, 0x0A, 0 },
    { 66560000, 0x54, 0x0A, 0 },
    { 67584000, 0x51, 0x09, 0 },
    { 68608000, 0x4E, 0x09, 0 },
    { 69632000, 0x4B, 0x09, 0 },
    { 70656000, 0x49, 0x08, 0 },
    { 71680000, 0x46, 0x08, 0 },
    { 72704000, 0x44, 0x08, 0 },
    { 73728000, 0x41, 0x07, 0 },
    { 74752000, 0x3F, 0x07, 0 },
    { 75776000, 0x3D, 0x07, 0 },
    { 76800000, 0x3B, 0x07, 0 },
    { 77824000, 0x39, 0x07, 0 },
    { 78848000, 0x37, 0x07, 0 },
    { 79872000, 0x35, 0x07, 0 },
    { 80896000, 0x33, 0x07, 0 },
    { 81920000, 0x32, 0x07, 0 },
    { 82944000, 0x30, 0x07, 0 },
    { 83968000, 0x2F, 0x07, 0 },
    { 84992000, 0x2D, 0x07, 0 },
    { 86016000, 0x2C, 0x07, 0 },
    { 87040000, 0x2A, 0x07, 0 },
    { 88064000, 0x29, 0x06, 0 },
    { 89088000, 0x27, 0x06, 0 },
    { 90112000, 0x26, 0x06, 0 },
    { 91136000, 0x25, 0x06, 0 },
    { 92160000, 0x24, 0x06, 0 },
    { 93184000, 0x22, 0x05, 0 },
    { 94208000, 0x21, 0x05, 0 },
    { 95232000, 0x20, 0x05, 0 },
    { 96256000, 0x1F, 0x05, 0 },
    { 97280000, 0x1E, 0x05, 0 },
    { 98304000, 0x1D, 0x05, 0 },
    { 99328000, 0x1C, 0x04, 0 },
    { 100352000, 0x1B, 0x04, 0 },
    { 101376000, 0x1A, 0x04, 0 },
    { 103424000, 0x19, 0x04, 0 },
    { 104448000, 0x18, 0x04, 0 },
    { 105472000, 0x17, 0x04, 0 },
    { 106496000, 0x16, 0x03, 0 },
    { 106496000, 0x15, 0x03, 0 },
    { 108544000, 0x14, 0x03, 0 },
    { 109568000, 0x13, 0x03, 0 },
    { 111616000, 0x12, 0x03, 0 },
    { 112640000, 0x11, 0x03, 0 },
    { 113664000, 0x11, 0x07, 0 },
    { 114688000, 0x10, 0x07, 0 },
    { 115712000, 0x0F, 0x07, 0 },
    { 117760000, 0x0E, 0x07, 0 },
    { 119808000, 0x0D, 0x06, 0 },
    { 121856000, 0x0C, 0x06, 0 },
    { 123904000, 0x0B, 0x06, 0 },
    { 125952000, 0x0A, 0x05, 0 },
    { 128000000, 0x09, 0x05, 0 },
    { 130048000, 0x08, 0x05, 0 },
    { 133120000, 0x07, 0x04, 0 },
    { 135168000, 0x06, 0x04, 0 },
    { 138240000, 0x05, 0x04, 0 },
    { 141312000, 0x04, 0x04, 0 },
    { 144384000, 0x03, 0x03, 0 },
    { 145408000, 0xE0, 0x3F, 1 },
    { 147456000, 0xDC, 0x37, 1 },
    { 148480000, 0xD9, 0x32, 1 },
    { 149504000, 0xD6, 0x2F, 1 },
    { 149504000, 0xD2, 0x2F, 1 },
    { 150528000, 0xCF, 0x2F, 1 },
    { 151552000, 0xCC, 0x2B, 1 },
    { 152576000, 0xC9, 0x27, 1 },
    { 153600000, 0xC5, 0x27, 1 },
    { 154624000, 0xC2, 0x25, 1 },
    { 155648000, 0xBF, 0x23, 1 },
    { 156672000, 0xBD, 0x20, 1 },
    { 157696000, 0xBA, 0x1F, 1 },
    { 158720000, 0xB7, 0x1F, 1 },
    { 159744000, 0xB4, 0x1F, 1 },
    { 160768000, 0xB1, 0x1F, 1 },
    { 161792000, 0xAF, 0x1F, 1 },
    { 162816000, 0xAC, 0x1F, 1 },
    { 163840000, 0xAA, 0x1F, 1 },
    { 164864000, 0xA7, 0x1F, 1 },
    { 165888000, 0xA5, 0x1F, 1 },
    { 166912000, 0xA2, 0x1F, 1 },
    { 167936000, 0xA0, 0x1F, 1 },
    { 168960000, 0x9D, 0x1F, 1 },
    { 169984000, 0x9B, 0x1F, 1 },
    { 171008000, 0x99, 0x1F, 1 },
    { 172032000, 0x97, 0x1E, 1 },
    { 173056000, 0x95, 0x1D, 1 },
    { 174080000, 0x92, 0x1C, 1 },
    { 175104000, 0x90, 0x1B, 1 },
    { 176128000, 0x8E, 0x1A, 1 },
    { 177152000, 0x8C, 0x19, 1 },
    { 178176000, 0x8A, 0x18, 1 },
    { 179200000, 0x88, 0x17, 1 },
    { 180224000, 0x86, 0x17, 1 },
    { 181248000, 0x84, 0x17, 1 },
    { 182272000, 0x82, 0x17, 1 },
    { 183296000, 0x81, 0x17, 1 },
    { 184320000, 0x7F, 0x17, 1 },
    { 185344000, 0x7D, 0x16, 1 },
    { 186368000, 0x7B, 0x15, 1 },
    { 187392000, 0x7A, 0x14, 1 },
    { 188416000, 0x78, 0x14, 1 },
    { 189440000, 0x76, 0x13, 1 },
    { 190464000, 0x75, 0x13, 1 },
    { 191488000, 0x73, 0x13, 1 },
    { 192512000, 0x71, 0x12, 1 },
    { 192512000, 0x70, 0x11, 1 },
    { 193536000, 0x6E, 0x11, 1 },
    { 194560000, 0x6D, 0x10, 1 },
    { 195584000, 0x6B, 0x10, 1 },
    { 196608000, 0x6A, 0x0F, 1 },
    { 197632000, 0x68, 0x0F, 1 },
    { 198656000, 0x67, 0x0F, 1 },
    { 199680000, 0x65, 0x0F, 1 },
    { 200704000, 0x64, 0x0F, 1 },
    { 201728000, 0x63, 0x0F, 1 },
    { 202752000, 0x61, 0x0F, 1 },
    { 203776000, 0x60, 0x0F, 1 },
    { 204800000, 0x5F, 0x0F, 1 },
    { 205824000, 0x5D, 0x0F, 1 },
    { 206848000, 0x5C, 0x0F, 1 },
    { 207872000, 0x5B, 0x0F, 1 },
    { 208896000, 0x5A, 0x0F, 1 },
    { 209920000, 0x58, 0x0F, 1 },
    { 210944000, 0x57, 0x0F, 1 },
    { 211968000, 0x56, 0x0F, 1 },
    { 212992000, 0x55, 0x0F, 1 },
    { 214016000, 0x54, 0x0F, 1 },
    { 215040000, 0x53, 0x0F, 1 },
    { 216064000, 0x52, 0x0F, 1 },
    { 217088000, 0x50, 0x0F, 1 },
    { 218112000, 0x4F, 0x0F, 1 },
    { 219136000, 0x4E, 0x0F, 1 },
    { 220160000, 0x4D, 0x0E, 1 },
    { 221184000, 0x4C, 0x0E, 1 },
    { 222208000, 0x4B, 0x0E, 1 },
    { 223232000, 0x4A, 0x0E, 1 },
    { 224256000, 0x49, 0x0D, 1 },
    { 225280000, 0x48, 0x0D, 1 },
    { 226304000, 0x47, 0x0D, 1 },
    { 227328000, 0x46, 0x0D, 1 },
    { 228352000, 0x45, 0x0C, 1 },
    { 229376000, 0x44, 0x0C, 1 },
    { 230400000, 0x43, 0x0C, 1 },
    { 231424000, 0x42, 0x0C, 1 },
    { 232448000, 0x42, 0x0B, 1 },
    { 233472000, 0x41, 0x0B, 1 },
    { 234496000, 0x40, 0x0B, 1 },
    { 234496000, 0x3F, 0x0B, 1 },
    { 235520000, 0x3E, 0x0B, 1 },
    { 236544000, 0x3D, 0x0B, 1 },
    { 237568000, 0x3C, 0x0B, 1 },
    { 239616000, 0x3B, 0x0A, 1 },
    { 240640000, 0x3A, 0x0A, 1 },
    { 241664000, 0x39, 0x0A, 1 },
    { 242688000, 0x38, 0x0A, 1 },
    { 244736000, 0x37, 0x09, 1 },
    { 245760000, 0x36, 0x09, 1 },
    { 246784000, 0x35, 0x09, 1 },
    { 248832000, 0x34, 0x09, 1 },
    { 249856000, 0x33, 0x09, 1 },
    { 250880000, 0x32, 0x08, 1 },
    { 252928000, 0x31, 0x08, 1 },
    { 253952000, 0x30, 0x08, 1 },
    { 256000000, 0x2F, 0x08, 1 },
    { 257024000, 0x2E, 0x08, 1 },
    { 259072000, 0x2D, 0x07, 1 },
    { 260096000, 0x2C, 0x07, 1 },
    { 262144000, 0x2B, 0x07, 1 },
    { 264192000, 0x2A, 0x07, 1 },
    { 265216000, 0x29, 0x07, 1 },
    { 267264000, 0x28, 0x07, 1 },
    { 269312000, 0x27, 0x07, 1 },
    { 270336000, 0x26, 0x07, 1 },
    { 272384000, 0x25, 0x07, 1 },
    { 274432000, 0x24, 0x07, 1 },
    { 276480000, 0x23, 0x07, 1 },
    { 277504000, 0x22, 0x07, 1 },
    { 279552000, 0x21, 0x07, 1 },
    { 281600000, 0x20, 0x07, 1 },
    { 283648000, 0x1F, 0x07, 1 },
    { 285696000, 0x1E, 0x0F, 1 },
    { 287744000, 0x1D, 0x0F, 1 },
    { 289792000, 0x1C, 0x0E, 1 },
    { 291840000, 0x1B, 0x0E, 1 },
    { 293888000, 0x1A, 0x0D, 1 },
    { 296960000, 0x19, 0x0D, 1 },
    { 299008000, 0x18, 0x0C, 1 },
    { 301056000, 0x17, 0x0C, 1 },
    { 304128000, 0x16, 0x0C, 1 },
    { 306176000, 0x15, 0x0B, 1 },
    { 309248000, 0x14, 0x0B, 1 },
    { 312320000, 0x13, 0x0B, 1 },
    { 314368000, 0x12, 0x0B, 1 },
    { 317440000, 0x11, 0x0A, 1 },
    { 320512000, 0x10, 0x0A, 1 },
    { 322560000, 0x0F, 0x0A, 1 },
    { 325632000, 0x0E, 0x09, 1 },
    { 328704000, 0x0D, 0x09, 1 },
    { 331776000, 0x0C, 0x08, 1 },
    { 335872000, 0x0B, 0x08, 1 },
    { 338944000, 0x0A, 0x08, 1 },
    { 343040000, 0x09, 0x07, 1 },
    { 346112000, 0x08, 0x07, 1 },
    { 350208000, 0x07, 0x07, 1 },
    { 354304000, 0x06, 0x07, 1 },
    { 358400000, 0x05, 0x07, 1 },
    { 362496000, 0x04, 0x07, 1 },
    { 365568000, 0x04, 0x07, 1 },
    { 367616000, 0xDA, 0x2A, 2 },
    { 367616000, 0xD9, 0x27, 2 },
    { 368640000, 0xD8, 0x27, 2 },
    { 369664000, 0xD6, 0x27, 2 },
    { 370688000, 0xD5, 0x27, 2 },
    { 371712000, 0xD3, 0x25, 2 },
    { 372736000, 0xD2, 0x23, 2 },
    { 373760000, 0xD0, 0x23, 2 },
    { 374784000, 0xCF, 0x21, 2 },
    { 375808000, 0xCD, 0x1F, 2 },
    { 376832000, 0xCC, 0x1F, 2 },
    { 377856000, 0xCA, 0x1F, 2 },
    { 378880000, 0xC9, 0x1F, 2 },
    { 379904000, 0xC7, 0x1F, 2 },
    { 380928000, 0xC6, 0x1F, 2 },
    { 381952000, 0xC4, 0x1F, 2 },
    { 382976000, 0xC3, 0x1F, 2 },
    { 384000000, 0xC1, 0x1F, 2 },
    { 385024000, 0xC0, 0x1F, 2 },
    { 386048000, 0xBF, 0x1F, 2 },
    { 387072000, 0xBD, 0x1F, 2 },
    { 388096000, 0xBC, 0x1F, 2 },
    { 389120000, 0xBB, 0x1F, 2 },
    { 390144000, 0xB9, 0x1F, 2 },
    { 391168000, 0xB8, 0x1F, 2 },
    { 392192000, 0xB7, 0x1F, 2 },
    { 393216000, 0xB5, 0x1F, 2 },
    { 394240000, 0xB4, 0x1F, 2 },
    { 395264000, 0xB3, 0x1F, 2 },
    { 396288000, 0xB1, 0x1F, 2 },
    { 397312000, 0xB0, 0x1F, 2 },
    { 398336000, 0xAF, 0x1F, 2 },
    { 399360000, 0xAD, 0x1F, 2 },
    { 400384000, 0xAC, 0x1F, 2 },
    { 401408000, 0xAB, 0x1F, 2 },
    { 402432000, 0xAA, 0x1F, 2 },
    { 403456000, 0xA8, 0x1E, 2 },
    { 404480000, 0xA7, 0x1D, 2 },
    { 405504000, 0xA6, 0x1D, 2 },
    { 405504000, 0xA5, 0x1C, 2 },
    { 406528000, 0xA3, 0x1C, 2 },
    { 407552000, 0xA2, 0x1B, 2 },
    { 408576000, 0xA1, 0x1B, 2 },
    { 409600000, 0xA0, 0x1B, 2 },
    { 410624000, 0x9F, 0x1A, 2 },
    { 411648000, 0x9D, 0x1A, 2 },
    { 412672000, 0x9C, 0x19, 2 },
    { 413696000, 0x9B, 0x18, 2 },
    { 414720000, 0x9A, 0x18, 2 },
    { 415744000, 0x99, 0x17, 2 },
    { 416768000, 0x98, 0x17, 2 },
    { 417792000, 0x97, 0x17, 2 },
    { 418816000, 0x95, 0x17, 2 },
    { 419840000, 0x94, 0x17, 2 },
    { 420864000, 0x93, 0x17, 2 },
    { 421888000, 0x92, 0x17, 2 },
    { 422912000, 0x91, 0x17, 2 },
    { 423936000, 0x90, 0x17, 2 },
    { 424960000, 0x8F, 0x17, 2 },
    { 425984000, 0x8E, 0x16, 2 },
    { 427008000, 0x8D, 0x16, 2 },
    { 428032000, 0x8C, 0x15, 2 },
    { 429056000, 0x8B, 0x15, 2 },
    { 430080000, 0x8A, 0x15, 2 },
    { 431104000, 0x88, 0x14, 2 },
    { 432128000, 0x87, 0x14, 2 },
    { 433152000, 0x86, 0x14, 2 },
    { 434176000, 0x85, 0x13, 2 },
    { 435200000, 0x84, 0x13, 2 },
    { 436224000, 0x83, 0x13, 2 },
    { 437248000, 0x82, 0x13, 2 },
    { 438272000, 0x81, 0x13, 2 },
    { 439296000, 0x80, 0x12, 2 },
    { 440320000, 0x7F, 0x12, 2 },
    { 441344000, 0x7E, 0x12, 2 },
    { 442368000, 0x7D, 0x11, 2 },
    { 444416000, 0x7C, 0x11, 2 },
    { 445440000, 0x7B, 0x10, 2 },
    { 446464000, 0x7A, 0x10, 2 },
    { 447488000, 0x79, 0x10, 2 },
    { 448512000, 0x78, 0x10, 2 },
    { 448512000, 0x77, 0x0F, 2 },
    { 449536000, 0x76, 0x0F, 2 },
    { 450560000, 0x75, 0x0F, 2 },
    { 451584000, 0x74, 0x0F, 2 },
    { 452608000, 0x73, 0x0F, 2 },
    { 453632000, 0x72, 0x0F, 2 },
    { 454656000, 0x71, 0x0F, 2 },
    { 455680000, 0x70, 0x0F, 2 },
    { 457728000, 0x6F, 0x0F, 2 },
    { 458752000, 0x6E, 0x0F, 2 },
    { 459776000, 0x6D, 0x0F, 2 },
    { 460800000, 0x6C, 0x0F, 2 },
    { 461824000, 0x6B, 0x0F, 2 },
    { 462848000, 0x6A, 0x0F, 2 },
    { 464896000, 0x69, 0x0F, 2 },
    { 465920000, 0x68, 0x0F, 2 },
    { 466944000, 0x67, 0x0F, 2 },
    { 467968000, 0x66, 0x0F, 2 },
    { 468992000, 0x65, 0x0F, 2 },
    { 471040000, 0x64, 0x0F, 2 },
    { 472064000, 0x63, 0x0F, 2 },
    { 473088000, 0x62, 0x0F, 2 },
    { 474112000, 0x61, 0x0F, 2 },
    { 476160000, 0x60, 0x0F, 2 },
    { 477184000, 0x5F, 0x0F, 2 },
    { 478208000, 0x5E, 0x0F, 2 },
    { 479232000, 0x5D, 0x0F, 2 },
    { 481280000, 0x5C, 0x0F, 2 },
    { 482304000, 0x5B, 0x0F, 2 },
    { 483328000, 0x5A, 0x0F, 2 },
    { 485376000, 0x59, 0x0F, 2 },
    { 486400000, 0x58, 0x0F, 2 },
    { 487424000, 0x57, 0x0F, 2 },
    { 489472000, 0x56, 0x0F, 2 },
    { 490496000, 0x55, 0x0F, 2 },
    { 490496000, 0x54, 0x0F, 2 },
    { 492544000, 0x53, 0x0E, 2 },
    { 493568000, 0x52, 0x0E, 2 },
    { 495616000, 0x51, 0x0E, 2 },
    { 496640000, 0x50, 0x0E, 2 },
    { 497664000, 0x4F, 0x0E, 2 },
    { 499712000, 0x4E, 0x0D, 2 },
    { 500736000, 0x4D, 0x0D, 2 },
    { 502784000, 0x4C, 0x0D, 2 },
    { 503808000, 0x4B, 0x0D, 2 },
    { 505856000, 0x4A, 0x0C, 2 },
    { 506880000, 0x49, 0x0C, 2 },
    { 508928000, 0x48, 0x0C, 2 },
    { 509952000, 0x47, 0x0C, 2 },
    { 512000000, 0x46, 0x0C, 2 },
    { 513024000, 0x45, 0x0B, 2 },
    { 515072000, 0x44, 0x0B, 2 },
    { 517120000, 0x43, 0x0B, 2 },
    { 518144000, 0x42, 0x0B, 2 },
    { 520192000, 0x41, 0x0B, 2 },
    { 521216000, 0x40, 0x0B, 2 },
    { 523264000, 0x3F, 0x0B, 2 },
    { 525312000, 0x3E, 0x0B, 2 },
    { 526336000, 0x3D, 0x0B, 2 },
    { 528384000, 0x3C, 0x0A, 2 },
    { 530432000, 0x3B, 0x0A, 2 },
    { 531456000, 0x3A, 0x0A, 2 },
    { 533504000, 0x39, 0x0A, 2 },
    { 534528000, 0x38, 0x0A, 2 },
    { 536576000, 0x37, 0x0A, 2 },
    { 537600000, 0x36, 0x09, 2 },
    { 539648000, 0x35, 0x09, 2 },
    { 541696000, 0x34, 0x09, 2 },
    { 543744000, 0x33, 0x09, 2 },
    { 544768000, 0x32, 0x09, 2 },
    { 546816000, 0x31, 0x09, 2 },
    { 548864000, 0x30, 0x08, 2 },
    { 550912000, 0x2F, 0x08, 2 },
    { 552960000, 0x2E, 0x08, 2 },
    { 555008000, 0x2D, 0x08, 2 },
    { 557056000, 0x2C, 0x08, 2 },
    { 559104000, 0x2B, 0x08, 2 },
    { 561152000, 0x2A, 0x07, 2 },
    { 563200000, 0x29, 0x07, 2 },
    { 565248000, 0x28, 0x07, 2 },
    { 567296000, 0x27, 0x07, 2 },
    { 569344000, 0x26, 0x07, 2 },
    { 570368000, 0x26, 0x07, 2 },
    { 571392000, 0x25, 0x07, 2 },
    { 573440000, 0x24, 0x07, 2 },
    { 575488000, 0x23, 0x07, 2 },
    { 577536000, 0x22, 0x0F, 2 },
    { 578560000, 0x21, 0x0F, 2 },
    { 580608000, 0x20, 0x0F, 2 },
    { 583680000, 0x1F, 0x0F, 2 },
    { 585728000, 0x1E, 0x0F, 2 },
    { 587776000, 0x1D, 0x0F, 2 },
    { 589824000, 0x1C, 0x0F, 2 },
    { 592896000, 0x1B, 0x0F, 2 },
    { 594944000, 0x1A, 0x0F, 2 },
    { 596992000, 0x19, 0x0F, 2 },
    { 600064000, 0x18, 0x0F, 2 },
    { 602112000, 0x17, 0x0F, 2 },
    { 604160000, 0x16, 0x0F, 2 },
    { 607232000, 0x15, 0x0F, 2 },
    { 609280000, 0x14, 0x0F, 2 },
    { 612352000, 0x13, 0x0F, 2 },
    { 615424000, 0x12, 0x0F, 2 },
    { 617472000, 0x11, 0x0F, 2 },
    { 619520000, 0x10, 0x0E, 2 },
    { 621568000, 0x0F, 0x0E, 2 },
    { 623616000, 0x0F, 0x0E, 2 },
    { 624640000, 0xA3, 0x1F, 3 },
    { 625664000, 0xA2, 0x1F, 3 },
    { 626688000, 0xA1, 0x1F, 3 },
    { 627712000, 0xA0, 0x1F, 3 },
    { 628736000, 0x9F, 0x1F, 3 },
    { 630784000, 0x9E, 0x1F, 3 },
    { 631808000, 0x9D, 0x1F, 3 },
    { 632832000, 0x9C, 0x1F, 3 },
    { 633856000, 0x9B, 0x1F, 3 },
    { 635904000, 0x9A, 0x1F, 3 },
    { 636928000, 0x99, 0x1F, 3 },
    { 637952000, 0x98, 0x1F, 3 },
    { 638976000, 0x97, 0x1F, 3 },
    { 641024000, 0x96, 0x1E, 3 },
    { 642048000, 0x95, 0x1E, 3 },
    { 643072000, 0x94, 0x1E, 3 },
    { 644096000, 0x93, 0x1D, 3 },
    { 646144000, 0x92, 0x1D, 3 },
    { 647168000, 0x91, 0x1C, 3 },
    { 648192000, 0x90, 0x1C, 3 },
    { 650240000, 0x8F, 0x1B, 3 },
    { 651264000, 0x8E, 0x1B, 3 },
    { 652288000, 0x8D, 0x1B, 3 },
    { 654336000, 0x8C, 0x1B, 3 },
    { 655360000, 0x8B, 0x1B, 3 },
    { 656384000, 0x8A, 0x1B, 3 },
    { 658432000, 0x89, 0x1A, 3 },
    { 659456000, 0x88, 0x1A, 3 },
    { 660480000, 0x87, 0x1A, 3 },
    { 661504000, 0x86, 0x19, 3 },
    { 662528000, 0x85, 0x19, 3 },
    { 664576000, 0x84, 0x18, 3 },
    { 665600000, 0x83, 0x18, 3 },
    { 666624000, 0x82, 0x18, 3 },
    { 668672000, 0x81, 0x18, 3 },
    { 669696000, 0x80, 0x17, 3 },
    { 671744000, 0x7F, 0x17, 3 },
    { 672768000, 0x7E, 0x17, 3 },
    { 674816000, 0x7D, 0x17, 3 },
    { 675840000, 0x7C, 0x17, 3 },
    { 676864000, 0x7B, 0x17, 3 },
    { 678912000, 0x7A, 0x17, 3 },
    { 679936000, 0x79, 0x17, 3 },
    { 681984000, 0x78, 0x17, 3 },
    { 683008000, 0x77, 0x17, 3 },
    { 685056000, 0x76, 0x17, 3 },
    { 686080000, 0x75, 0x17, 3 },
    { 688128000, 0x74, 0x17, 3 },
    { 689152000, 0x73, 0x17, 3 },
    { 691200000, 0x72, 0x16, 3 },
    { 693248000, 0x71, 0x16, 3 },
    { 694272000, 0x70, 0x16, 3 },
    { 696320000, 0x6F, 0x15, 3 },
    { 697344000, 0x6E, 0x15, 3 },
    { 699392000, 0x6D, 0x15, 3 },
    { 700416000, 0x6C, 0x15, 3 },
    { 702464000, 0x6B, 0x14, 3 },
    { 704512000, 0x6A, 0x14, 3 },
    { 704512000, 0x69, 0x14, 3 },
    { 706560000, 0x68, 0x14, 3 },
    { 707584000, 0x67, 0x13, 3 },
    { 709632000, 0x66, 0x13, 3 },
    { 711680000, 0x65, 0x13, 3 },
    { 712704000, 0x64, 0x13, 3 },
    { 714752000, 0x63, 0x13, 3 },
    { 716800000, 0x62, 0x13, 3 },
    { 717824000, 0x61, 0x13, 3 },
    { 719872000, 0x60, 0x13, 3 },
    { 721920000, 0x5F, 0x12, 3 },
    { 723968000, 0x5E, 0x12, 3 },
    { 724992000, 0x5D, 0x12, 3 },
    { 727040000, 0x5C, 0x12, 3 },
    { 729088000, 0x5B, 0x11, 3 },
    { 731136000, 0x5A, 0x11, 3 },
    { 732160000, 0x59, 0x11, 3 },
    { 734208000, 0x58, 0x11, 3 },
    { 736256000, 0x57, 0x10, 3 },
    { 738304000, 0x56, 0x10, 3 },
    { 740352000, 0x55, 0x10, 3 },
    { 741376000, 0x54, 0x10, 3 },
    { 743424000, 0x53, 0x10, 3 },
    { 745472000, 0x52, 0x0F, 3 },
    { 746496000, 0x51, 0x0F, 3 },
    { 748544000, 0x50, 0x0F, 3 },
    { 750592000, 0x4F, 0x0F, 3 },
    { 752640000, 0x4E, 0x0F, 3 },
    { 753664000, 0x4D, 0x0F, 3 },
    { 755712000, 0x4C, 0x0F, 3 },
    { 757760000, 0x4B, 0x0F, 3 },
    { 759808000, 0x4A, 0x0F, 3 },
    { 761856000, 0x49, 0x0F, 3 },
    { 762880000, 0x49, 0x0F, 3 },
    { 763904000, 0x48, 0x0F, 3 },
    { 765952000, 0x47, 0x0F, 3 },
    { 768000000, 0x46, 0x0F, 3 },
    { 770048000, 0x45, 0x0F, 3 },
    { 772096000, 0x44, 0x0F, 3 },
    { 774144000, 0x43, 0x0F, 3 },
    { 776192000, 0x42, 0x0F, 3 },
    { 778240000, 0x41, 0x0F, 3 },
    { 780288000, 0x40, 0x0F, 3 },
    { 783360000, 0x3F, 0x0F, 3 },
    { 785408000, 0x3E, 0x0F, 3 },
    { 787456000, 0x3D, 0x0F, 3 },
    { 789504000, 0x3C, 0x0F, 3 },
    { 790528000, 0x3B, 0x0F, 3 },
    { 792576000, 0x3A, 0x0F, 3 },
    { 794624000, 0x39, 0x0F, 3 },
    { 797696000, 0x38, 0x0F, 3 },
    { 799744000, 0x37, 0x0F, 3 },
    { 801792000, 0x36, 0x0F, 3 },
    { 803840000, 0x35, 0x0F, 3 },
    { 806912000, 0x34, 0x0F, 3 },
    { 808960000, 0x33, 0x0F, 3 },
    { 809984000, 0x33, 0x0F, 3 },
    { 811008000, 0x32, 0x0F, 3 },
    { 813056000, 0x31, 0x0F, 3 },
    { 816128000, 0x30, 0x0F, 3 },
    { 818176000, 0x2F, 0x0F, 3 },
    { 820224000, 0x2E, 0x0F, 3 },
    { 823296000, 0x2D, 0x0F, 3 },
    { 825344000, 0x2C, 0x0F, 3 },
    { 828416000, 0x2B, 0x0F, 3 },
    { 830464000, 0x2A, 0x0F, 3 },
    { 832512000, 0x29, 0x0F, 3 },
    { 834560000, 0x28, 0x0F, 3 },
    { 836608000, 0x27, 0x0F, 3 },
    { 839680000, 0x26, 0x0F, 3 },
    { 841728000, 0x25, 0x0F, 3 },
    { 844800000, 0x24, 0x0F, 3 },
    { 847872000, 0x23, 0x0F, 3 },
    { 849920000, 0x22, 0x0F, 3 },
    { 852992000, 0x21, 0x0E, 3 },
    { 855040000, 0x20, 0x0E, 3 },
    { 858112000, 0x1F, 0x0E, 3 },
    { 861184000, 0x1E, 0x0E, 3 },
    { 863232000, 0x1D, 0x0E, 3 },
    { 866304000, 0x1C, 0x0E, 3 },
    { 900096000, 0x10, 0x0C, 3 },
    { 929792000, 0x07, 0x0B, 3 },
    { 969728000, 0x00, 0x0A, 3 }
};

static tmErrorCode_t
ddNT220xGetRFCalFreq(ptmddNT220xObject_t pObj, UInt32 idx, UInt32 *puRF0, UInt32 *puRF1)
{
    switch(idx)
    {
    case 0:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx26.bF.RFCAL_Freq0];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx26.bF.RFCAL_Freq1];
        break;

    case 1:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx26.bF.RFCAL_Freq1];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx27.bF.RFCAL_Freq2];
        break;

    case 2:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx27.bF.RFCAL_Freq2];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx27.bF.RFCAL_Freq3];
        break;

    case 3:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx27.bF.RFCAL_Freq3];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx28.bF.RFCAL_Freq4];
        break;

    case 4:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx28.bF.RFCAL_Freq4];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx28.bF.RFCAL_Freq5];
        break;

    case 5:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx28.bF.RFCAL_Freq5];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx29.bF.RFCAL_Freq6];
        break;

    case 6:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx29.bF.RFCAL_Freq6];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx29.bF.RFCAL_Freq7];
        break;

    case 7:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx29.bF.RFCAL_Freq7];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx2A.bF.RFCAL_Freq8];
        break;

    case 8:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx2A.bF.RFCAL_Freq8];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx2A.bF.RFCAL_Freq9];
        break;

    case 9:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx2A.bF.RFCAL_Freq9];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx2B.bF.RFCAL_Freq10];
        break;

    case 10:
        if(puRF0!=Null) *puRF0 = NT220x_Cal_Map[idx].Cal_Freq[pObj->I2CMap.uBx2B.bF.RFCAL_Freq10];
        if(puRF1!=Null) *puRF1 = NT220x_Cal_Map[idx+1].Cal_Freq[pObj->I2CMap.uBx2B.bF.RFCAL_Freq11];
        break;

    default:
        if(puRF0!=Null) *puRF0 = 0;
        if(puRF1!=Null) *puRF1 = 0;
        break;
    }

    return TM_OK;
}

/*============================================================================*/
/* Internal Prototypes:                                                       */
/*============================================================================*/

/*============================================================================*/
/* Exported functions:                                                        */
/*============================================================================*/


/*============================================================================*/
/* FUNCTION:    tmddNT220xInit                                              */
/*                                                                            */
/* DESCRIPTION: Create an instance of a NT220x Tuner                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xInit
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /* I: setup parameters */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    if (psSrvFunc == Null)
    {
        err = ddNT220x_ERR_BAD_PARAMETER;
    }

    /* Get Instance Object */
    if(err == TM_OK)
    {
        err = ddNT220xGetInstance(tUnit, &pObj);
    }

	tmDBGPRINTEx(DEBUGLVL_VERBOSE, "tmddNT220xInit", tUnit);

    /* Check driver state */
    if (err == TM_OK || err == ddNT220x_ERR_NOT_INITIALIZED)
    {
        if (pObj != Null && pObj->init == True)
        {
            err = ddNT220x_ERR_NOT_INITIALIZED;
        }
        else
        {
            /* Allocate the Instance Object */
            if (pObj == Null)
            {
                err = ddNT220xAllocInstance(tUnit, &pObj);
                if (err != TM_OK || pObj == Null)
                {
                    err = ddNT220x_ERR_NOT_INITIALIZED;
                }
            }

            if(err == TM_OK)
            {
                /* initialize the Instance Object */
                pObj->sRWFunc = psSrvFunc->sIo;
                pObj->sTime = psSrvFunc->sTime;
                pObj->sDebug = psSrvFunc->sDebug;

                if(  psSrvFunc->sMutex.Init != Null
                    && psSrvFunc->sMutex.DeInit != Null
                    && psSrvFunc->sMutex.Acquire != Null
                    && psSrvFunc->sMutex.Release != Null)
                {
                    pObj->sMutex = psSrvFunc->sMutex;

                    err = pObj->sMutex.Init(&pObj->pMutex);
                }

                pObj->init = True;
                err = TM_OK;
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xDeInit                                            */
/*                                                                            */
/* DESCRIPTION: Destroy an instance of a NT220x Tuner                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xDeInit
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    tmErrorCode_t           err = TM_OK;
    ptmddNT220xObject_t   pObj = Null;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);

    tmDBGPRINTEx(DEBUGLVL_VERBOSE, "tmddNT220xDeInit", tUnit);

    if(err == TM_OK)
    {
        if(pObj->sMutex.DeInit != Null)
        {
            if(pObj->pMutex != Null)
            {
                err = pObj->sMutex.DeInit(pObj->pMutex);
            }

            pObj->sMutex.Init = Null;
            pObj->sMutex.DeInit = Null;
            pObj->sMutex.Acquire = Null;
            pObj->sMutex.Release = Null;

            pObj->pMutex = Null;
        }
    }

    err = ddNT220xDeAllocInstance(tUnit);

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetSWVersion                                      */
/*                                                                            */
/* DESCRIPTION: Return the version of this device                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:       Values defined in the tmddNT220xlocal.h file                */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetSWVersion
(
    ptmSWVersion_t  pSWVersion  /* I: Receives SW Version */
)
{
    pSWVersion->compatibilityNr = NT220x_DD_COMP_NUM;
    pSWVersion->majorVersionNr  = NT220x_DD_MAJOR_VER;
    pSWVersion->minorVersionNr  = NT220x_DD_MINOR_VER;

    return TM_OK;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xReset                                             */
/*                                                                            */
/* DESCRIPTION: Initialize NT220x Hardware                                  */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xReset
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err = TM_OK;
    UInt8                   uSubAddress = 0x00;
    UInt8                   uData = 0x00;


    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

	tmDBGPRINTEx(DEBUGLVL_VERBOSE, "tmddNT220xReset", tUnit);

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(pObj->bIRQWait)
        {
            err = ddNT220xWaitXtalCal_End(pObj, 100, 5);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitXtalCal_End(0x%08X) failed.", tUnit));

            if(err == ddNT220x_ERR_NOT_READY)
            {
                tmDBGPRINTEx(DEBUGLVL_TERSE, "Xtal Calibration failed. SoftReset schedduled!", tUnit);
                /* Update variables to catch Xtal calibration error and perfom a softReset */
                err = TM_OK;
                pObj->bSoftReset = True;
            }
        }

        /* ---------- ES2 PATCH BEGIN ---------- */
        if(err == TM_OK && pObj->bSoftReset)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "SoftReset Start", tUnit);
            /* Soft_Reset */
            uSubAddress = 0x60;
            uData = 0x2;
            err = POBJ_SRVFUNC_SIO.Write(pObj->tUnit, 1, &uSubAddress, 1, &uData);
            uData = 0x3;
            err = POBJ_SRVFUNC_SIO.Write(pObj->tUnit, 1, &uSubAddress, 1, &uData);

            err = ddNT220xWait(pObj, 100);

            uData = 0x00;
            err = POBJ_SRVFUNC_SIO.Write(pObj->tUnit, 1, &uSubAddress, 1, &uData);

            pObj->bSoftReset = False;
            tmDBGPRINTEx(DEBUGLVL_TERSE, "SoftReset End", tUnit);

            /* Launch Xtal Calibration after SoftReset */
            tmDBGPRINTEx(DEBUGLVL_TERSE, "Launch Xtal Calibration after SoftReset", tUnit);
            err = tmddNT220xSetXtalCal_Launch(tUnit);

            if(pObj->bIRQWait)
            {
                err = ddNT220xWaitXtalCal_End(pObj, 100, 5);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitXtalCal_End(0x%08X) failed.", tUnit));
            }
        }

        if(err == TM_OK)
        {
            /* read all bytes */
            err = ddNT220xRead(pObj, 0x00, NT220x_I2C_MAP_NB_BYTES);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));
        }
        /****** ES2 I2C map initialization : begin *********/
        if(err == TM_OK)
        {
            /* RSSI_Ck_Speed    31,25 kHz   0 */
            err = tmddNT220xSetRSSI_Ck_Speed(tUnit, 0);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetRSSI_Ck_Speed(0x%08X, 0) failed.", tUnit));
        }
        if(err == TM_OK)
        {
            /* AGC1_Do_step    8,176 ms   2 */
            err = tmddNT220xSetAGC1_Do_step(tUnit, 2);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC1_Do_step(0x%08X, 2) failed.", tUnit));
        }
        if(err == TM_OK)
        {
            /* AGC2_Do_step    8,176 ms   1 */
            err = tmddNT220xSetAGC2_Do_step(tUnit, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC2_Do_step(0x%08X, 1) failed.", tUnit));
        }
        if(err == TM_OK)
        {
            /* AGCs_Up_Step_assym       UP 12 Asym / 4 Asym  / 5 Asym   3 */
            err = tmddNT220xSetAGCs_Up_Step_assym(tUnit, 3);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGCs_Up_Step_assym(0x%08X, 3) failed.", tUnit));
        }
        if(err == TM_OK)
        {
            /* AGCs_Do_Step_assym       DO 12 Asym / 45 Sym   2 */
            err = tmddNT220xSetAGCs_Do_Step_assym(tUnit, 2);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGCs_Do_Step_assym(0x%08X, 2) failed.", tUnit));
        }

        if(err == TM_OK && pObj->I2CMap.uBx02.bF.Major_rev == 1 && pObj->I2CMap.uBx02.bF.Minor_rev == 0)
        {
            /* ---------- ES2 PATCH ---------- */
            if(err == TM_OK)
            {
                /* CP Div change  :   77  ( 0x4D)  */
                err = tmddNT220xSetN_CP_Current(tUnit, 0x4D);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetN_CP_Current(0x%08X, 0x4D) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* AGC5 DN time constant    1,022 ms    3 */
                err = tmddNT220xSetAGC5_Do_step(tUnit, 3);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC5_Do_step(0x%08X, 3) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* AGCs Up time constant    Fast : 262,131,65,65ms  1 */
                err = tmddNT220xSetAGCs_Up_Step(tUnit, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGCs_Up_Step(0x%08X, 1) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* AGC Overload TOP AGC1 TOP DN + 6 / 110 / 85  7 */
                err = tmddNT220xSetAGC_Ovld_TOP(tUnit, 7);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC_Ovld_TOP(0x%08X, 7) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* IR loop    7   7 */
                err = tmddNT220xSetIR_Loop(tUnit, 7);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIR_Loop(0x%08X, 7) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* IR target    67 dB   7 */
                err = tmddNT220xSetIR_Target(tUnit, 7);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIR_Target(0x%08X, 7) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* IR corr boost    0    0 */
                err = tmddNT220xSetIR_Corr_Boost(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIR_Corr_Boost(0x%08X, 0) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* IR output calc    calc    0 */
                err = tmddNT220xSetIR_mode_ram_store(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIR_mode_ram_store(0x%08X, 0) failed.", tUnit));
            }

            if(err == TM_OK) /* PD Underload not active */
            {
                err = tmddNT220xSetPD_Udld(tUnit, 0x1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetPD_Udld(0x%08X) failed.", tUnit));
            }

            if(err == TM_OK) /* force PHI2 to -0.25 instead of +0.25 */
            {
                err =  tmddNT220xSetRFCAL_Phi2(tUnit, (UInt8) 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetRFCAL_Phi2(0x%08X) failed.", tUnit));
            }

            if(err == TM_OK) /*Disable RF Filter Bypass */
            {
                err = tmddNT220xSetRF_Filter_Bypass(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetRF_Filter_Bypass(0x%08X) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* Move IF_Reg from 2.8V to 3V */
                uSubAddress = 0x58;
                uData = 0x65;
                err = POBJ_SRVFUNC_SIO.Write (pObj->tUnit, 1, &uSubAddress, 1, &uData);
            }

            /* Enable RFCAL SW Algorithm */
            pObj->bRFCAL_SW_Algo_Enable = True;
            /* ---------- ES2 PATCH END ---------- */
        }
        /****** I2C map initialization : end *********/


        /*****************************************/
        /* Launch tuner calibration */
        /* State reached after 1.5 s max */
        if(err == TM_OK)
        {
            /* set IRQ_clear */
            err = tmddNT220xSetIRQ_Clear(tUnit, 0x1F);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIRQ_clear(0x%08X, 0x1F) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* set power state on */
            err = tmddNT220xSetPowerState(tUnit, tmddNT220x_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetPowerState(0x%08X, PowerNormalMode) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* set & trigger MSM */
            pObj->I2CMap.uBx19.MSM_byte_1 = 0x3B;
            pObj->I2CMap.uBx1A.MSM_byte_2 = 0x01;

            /* write bytes 0x19 to 0x1A */
            err = ddNT220xWrite(pObj, 0x19, 2);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

            pObj->I2CMap.uBx1A.MSM_byte_2 = 0x00;

        }

        if(pObj->bIRQWait)
        {
            if(err == TM_OK)
            {
                err = ddNT220xWaitIRQ(pObj, 1500, 50, 0x1F);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitIRQ(0x%08X) failed.", tUnit));
            }
            /* PATCH ES2 in case of WAIT IRQ Timeout */
            if(err == ddNT220x_ERR_NOT_READY && pObj->I2CMap.uBx02.bF.Major_rev == 1 && pObj->I2CMap.uBx02.bF.Minor_rev == 0)
            {
                pObj->bSoftReset = True;
            }
            /* ---------- ES2 PATCH END ---------- */

            if(err == TM_OK && pObj->bRFCAL_SW_Algo_Enable)
            {
                err = tmddNT220xRFFilterCorrInit(tUnit);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xRFFilterCorrInit(0x%08X) failed.", tUnit));
            }
        }
        /*****************************************/

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xRFFilterCorrInit                                  */
/*                                                                            */
/* DESCRIPTION: RF Filter Correction to be done after hardware initialization */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xRFFilterCorrInit
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;
    UInt8                   uData = 0;
    UInt8*                  puData = Null;
    UInt32                  uCounter = 0;
    UInt8                   idx = 0;
    UInt32                  uRFCal0 = 0;
    UInt32                  uRFCal1 = 0;

    /* Int32 calIdx1 = 0; */
    /* Int32 calIdx0 = 0; */
    /* Int32 deltaRF = 0; */


    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* read byte 0x38-0x43 */
        err = ddNT220xRead(pObj, 0x38, 12);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            puData = &pObj->I2CMap.uBx38.rfcal_log_0;

            /* Store Cprog */
            for(uCounter = 0; uCounter<NT220x_RFCAL_PROG_ROW; uCounter++)
            {
                uData = ((*puData)&0x7F);
                pObj->RFCAL_Prog[uCounter].DeltaCprog = uData>63?uData-128:uData;
                puData++;
            }

            /* read byte 0x26-0x2B */
            err = ddNT220xRead(pObj, 0x26, 6);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));
        }

        for(uCounter = 0; uCounter<NT220x_RFCAL_COEFFS_ROW; uCounter++)
        {
            idx = pObj->RFCAL_Coeffs[uCounter].Cal_number;

            if(err == TM_OK)
            {
                err = ddNT220xGetRFCalFreq(pObj, idx, &uRFCal0, &uRFCal1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetRFCalFreq(0x%08X) failed.", tUnit));
            }
            else
            {
                break;
            }

            pObj->RFCAL_Coeffs[uCounter].RF_B1 = pObj->RFCAL_Prog[idx].DeltaCprog + NT220x_Cal_Map[idx].CprogOffset_Val[pObj->RFCAL_Prog[idx].CprogOffset];
            pObj->RFCAL_Coeffs[uCounter].RF_A1 = (((pObj->RFCAL_Prog[idx+1].DeltaCprog + NT220x_Cal_Map[idx+1].CprogOffset_Val[pObj->RFCAL_Prog[idx].CprogOffset]) - (pObj->RFCAL_Prog[idx].DeltaCprog + NT220x_Cal_Map[idx].CprogOffset_Val[pObj->RFCAL_Prog[idx].CprogOffset])) * 1000000)/((Int32)(uRFCal1 - uRFCal0)/1000);

            /* calIdx1 = (NT220x_Cal[idx+1].DeltaCprog + NT220x_Cal_Map[idx+1].CprogOffset_Val[NT220x_Cal_Map[idx].CprogOffset]); */
            /* calIdx0 = (NT220x_Cal[idx].DeltaCprog + NT220x_Cal_Map[idx].CprogOffset_Val[NT220x_Cal_Map[idx].CprogOffset]); */
            /* deltaRF = (uRFCal1 - uRFCal0)/1000; */

            /* NT220x_Coeff_Map[uCounter].RF_A1 = ((calIdx1 - calIdx0)*1000000)/deltaRF; */

        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xRFFilterCorrTune                                  */
/*                                                                            */
/* DESCRIPTION: RF Filter Correction to be done after tune                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xRFFilterCorrTune
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uRF     /* I: RF */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;
    UInt32                  uCounter = 0;
    UInt8                   idx = 0;
    UInt32                  uRFCal0 = 0;
    UInt32                  uRFCal1 = 0;
    UInt8                   uSubBand = 0;
    Int32                   cProg = 0;
    UInt8                   gainTapper = 0;
    UInt8                   RFBand = 0;
    Int32                   RF_A1 = 0;
    Int32                   RF_B1 = 0;


    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* read byte 0x26-0x2B */
        err = ddNT220xRead(pObj, 0x26, 6);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            err = ddNT220xGetRFCalFreq(pObj, 1, &uRFCal0, Null);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetRFCalFreq(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = ddNT220xGetRFCalFreq(pObj, 4, &uRFCal1, Null);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetRFCalFreq(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            if(uRF < uRFCal0)
                uSubBand = 0;
            else if(uRF < 145700000)
                uSubBand = 1;
            else if(uRF < uRFCal1)
                uSubBand = 2;
            else if(uRF < 367400000)
                uSubBand = 3;
            else
            {
                err = ddNT220xGetRFCalFreq(pObj, 7, &uRFCal0, Null);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetRFCalFreq(0x%08X) failed.", tUnit));

                if(err == TM_OK)
                {
                    err = ddNT220xGetRFCalFreq(pObj, 10, &uRFCal1, Null);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetRFCalFreq(0x%08X) failed.", tUnit));
                }

                if(err == TM_OK)
                {
                    if(uRF < uRFCal0)
                        uSubBand = 4;
                    else if(uRF < 625000000)
                        uSubBand = 5;
                    else if(uRF < uRFCal1)
                        uSubBand = 6;
                    else
                        uSubBand = 7;
                }
            }
        }

        if(err == TM_OK)
        {
            idx = pObj->RFCAL_Coeffs[uSubBand].Cal_number;
            err = ddNT220xGetRFCalFreq(pObj, idx, &uRFCal0, Null);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetRFCalFreq(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            RF_A1 = pObj->RFCAL_Coeffs[uSubBand].RF_A1;
            RF_B1 = pObj->RFCAL_Coeffs[uSubBand].RF_B1;

            uCounter = 0;
            do uCounter ++;
            while (uRF >= NT220x_Freq_ROM_Map[uCounter].uRF_Max && uCounter < NT220x_FREQ_ROM_MAP_ROW);

            cProg = NT220x_Freq_ROM_Map[uCounter - 1].uCprog;
            gainTapper = NT220x_Freq_ROM_Map[uCounter - 1].uGainTapper;
            RFBand = NT220x_Freq_ROM_Map[uCounter - 1].uRFBand;

            cProg = (Int32)(cProg + RF_B1 + (RF_A1*((Int32)(uRF - uRFCal0)/1000))/1000000);

            if(cProg>255)   cProg = 255;
            if(cProg<0)     cProg = 0;

            err = tmddNT220xSetRF_Filter_Bypass(tUnit, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetRF_Filter_Bypass(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddNT220xSetRF_Filter_Cap(tUnit, (UInt8)cProg);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetRF_Filter_Cap(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddNT220xSetGain_Taper(tUnit, gainTapper);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetGain_Taper(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddNT220xSetRF_Filter_Band(tUnit, RFBand);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetRF_Filter_Band(0x%08X) failed.", tUnit));
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetLPF_Gain_Mode                                  */
/*                                                                            */
/* DESCRIPTION: Free/Freeze LPF Gain                                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetLPF_Gain_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uMode   /* I: Unknown/Free/Frozen */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(uMode)
        {
        case tmddNT220x_LPF_Gain_Unknown:
        default:
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetLPF_Gain_Free(0x%08X, tmddNT220x_LPF_Gain_Unknown).", tUnit));
            break;

        case tmddNT220x_LPF_Gain_Free:
            err = tmddNT220xSetAGC5_loop_off(tUnit, False); /* Disable AGC5 loop off */
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC5_loop_off(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                err = tmddNT220xSetForce_AGC5_gain(tUnit, False); /* Do not force AGC5 gain */
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetForce_AGC5_gain(0x%08X) failed.", tUnit));
            }
            break;

        case tmddNT220x_LPF_Gain_Frozen:
            err = tmddNT220xSetAGC5_loop_off(tUnit, True); /* Enable AGC5 loop off */
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC5_loop_off(0x%08X) failed.", tUnit));

            if(err == TM_OK)
            {
                err = tmddNT220xSetForce_AGC5_gain(tUnit, True); /* Force AGC5 gain */
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetForce_AGC5_gain(0x%08X) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                err = tmddNT220xSetAGC5_Gain(tUnit, 0);  /* Force gain to 0dB */
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGC5_Gain(0x%08X) failed.", tUnit));
            }
            break;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetLPF_Gain_Mode                                  */
/*                                                                            */
/* DESCRIPTION: Free/Freeze LPF Gain                                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetLPF_Gain_Mode
(
 tmUnitSelect_t  tUnit,  /* I: Unit number */
 UInt8           *puMode /* I/O: Unknown/Free/Frozen */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;
    UInt8                   AGC5_loop_off = 0;
    UInt8                   Force_AGC5_gain = 0;
    UInt8                   AGC5_Gain = 0;

    /* Test the parameter */
    if (puMode == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *puMode = tmddNT220x_LPF_Gain_Unknown;

        err = tmddNT220xGetAGC5_loop_off(tUnit, &AGC5_loop_off);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xGetAGC5_loop_off(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            err = tmddNT220xGetForce_AGC5_gain(tUnit, &Force_AGC5_gain);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xGetForce_AGC5_gain(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddNT220xGetAGC5_Gain(tUnit, &AGC5_Gain);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xGetAGC5_Gain(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            if(AGC5_loop_off==False && Force_AGC5_gain==False)
            {
                *puMode = tmddNT220x_LPF_Gain_Free;
            }
            else if(AGC5_loop_off==True && Force_AGC5_gain==True && AGC5_Gain==0)
            {
                *puMode = tmddNT220x_LPF_Gain_Frozen;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xWrite                                             */
/*                                                                            */
/* DESCRIPTION: Write in NT220x hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xWrite
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          uIndex,     /* I: Start index to write */
    UInt32          uNbBytes,   /* I: Number of bytes to write */
    UInt8*          puBytes     /* I: Pointer on an array of bytes */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err = TM_OK;
    UInt32                  uCounter;
    UInt8*                  pI2CMap = Null;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* pI2CMap initialization */
        pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1) + uIndex;

        /* Save the values written in the Tuner */
        for (uCounter = 0; uCounter < uNbBytes; uCounter++)
        {
            *pI2CMap = puBytes[uCounter];
            pI2CMap ++;
        }

        /* Write in the Tuner */
        err = ddNT220xWrite(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xRead                                              */
/*                                                                            */
/* DESCRIPTION: Read in NT220x hardware                                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xRead
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          uIndex,     /* I: Start index to read */
    UInt32          uNbBytes,   /* I: Number of bytes to read */
    UInt8*          puBytes     /* I: Pointer on an array of bytes */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err = TM_OK;
    UInt32                  uCounter = 0;
    UInt8*                  pI2CMap = Null;

    /* Test the parameters */
    if (uNbBytes > NT220x_I2C_MAP_NB_BYTES)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* pI2CMap initialization */
        pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1) + uIndex;

        /* Read from the Tuner */
        err = ddNT220xRead(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Copy read values to puBytes */
            for (uCounter = 0; uCounter < uNbBytes; uCounter++)
            {
                *puBytes = (*pI2CMap);
                pI2CMap ++;
                puBytes ++;
            }
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetMS                                             */
/*                                                                            */
/* DESCRIPTION: Get the MS bit(s) status                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetMS
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x00 */
        err = ddNT220xRead(pObj, 0x00, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        /* Get value */
        *puValue = pObj->I2CMap.uBx00.bF.MS ;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIdentity                                       */
/*                                                                            */
/* DESCRIPTION: Get the Identity bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIdentity
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt16*         puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x00-0x01 */
        err = ddNT220xRead(pObj, 0x00, 2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx00.bF.Ident_1 << 8 |  pObj->I2CMap.uBx01.bF.Ident_2;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetMinorRevision                                  */
/*                                                                            */
/* DESCRIPTION: Get the Revision bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetMinorRevision
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x02 */
        err = ddNT220xRead(pObj, 0x02, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx02.bF.Minor_rev;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetMajorRevision                                  */
/*                                                                            */
/* DESCRIPTION: Get the Revision bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetMajorRevision
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x02 */
        err = ddNT220xRead(pObj, 0x02, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx02.bF.Major_rev;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetLO_Lock                                        */
/*                                                                            */
/* DESCRIPTION: Get the LO_Lock bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetLO_Lock
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x05 */
        err = ddNT220xRead(pObj, 0x05, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx05.bF.LO_Lock ;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetPowerState                                     */
/*                                                                            */
/* DESCRIPTION: Set the power state of the NT220x                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetPowerState
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    tmddNT220xPowerState_t    powerState  /* I: Power state of this device */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read bytes 0x06-0x14 */
        err = ddNT220xRead(pObj, 0x06, 15);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        /* Set digital clock mode*/
        if(err == TM_OK)
        {
            switch (powerState)
            {
            case tmddNT220x_PowerStandbyWithLNAOnAndWithXtalOnAndWithSyntheOn:
            case tmddNT220x_PowerStandbyWithLNAOnAndWithXtalOn:
            case tmddNT220x_PowerStandbyWithXtalOn:
            case tmddNT220x_PowerStandby:
                /* Set 16 Mhz Xtal clock */
                err = tmddNT220xSetDigital_Clock_Mode(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetDigital_Clock_Mode(0x%08X, 16 Mhz xtal clock) failed.", tUnit));

                /* ---------- ES2 PATCH BEGIN ---------- */
                if(err == TM_OK && pObj->I2CMap.uBx02.bF.Major_rev == 1 && pObj->I2CMap.uBx02.bF.Minor_rev == 0)
                {
                    err = tmddNT220xSetAGCK_Mode(tUnit, 0x2); /* RSSI disable for analog PR/CR 165 */
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetAGCK_Mode(0x%08X, RSSI disable) failed.", tUnit));
                }
                /* ---------- ES2 PATCH END ---------- */
                break;

            default:
                break;
            }
        }

        /* Set power state */
        if(err == TM_OK)
        {
            switch (powerState)
            {
            case tmddNT220x_PowerNormalMode:
                pObj->I2CMap.uBx06.bF.SM = 0x00;
                pObj->I2CMap.uBx06.bF.SM_Synthe = 0x00;
                pObj->I2CMap.uBx06.bF.SM_LT = 0x00;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x00;
                break;

            case tmddNT220x_PowerStandbyWithLNAOnAndWithXtalOnAndWithSyntheOn:
                pObj->I2CMap.uBx06.bF.SM = 0x01;
                pObj->I2CMap.uBx06.bF.SM_Synthe = 0x00;
                pObj->I2CMap.uBx06.bF.SM_LT = 0x00;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x00;
                break;

            case tmddNT220x_PowerStandbyWithLNAOnAndWithXtalOn:
                pObj->I2CMap.uBx06.bF.SM = 0x01;
                pObj->I2CMap.uBx06.bF.SM_Synthe = 0x01;
                pObj->I2CMap.uBx06.bF.SM_LT = 0x00;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x00;
                break;

            case tmddNT220x_PowerStandbyWithXtalOn:
                pObj->I2CMap.uBx06.bF.SM = 0x01;
                pObj->I2CMap.uBx06.bF.SM_Synthe = 0x01;
                pObj->I2CMap.uBx06.bF.SM_LT = 0x01;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x00;
                break;

            case tmddNT220x_PowerStandby:
                pObj->I2CMap.uBx06.bF.SM = 0x01;
                pObj->I2CMap.uBx06.bF.SM_Synthe = 0x01;
                pObj->I2CMap.uBx06.bF.SM_LT = 0x01;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x01;
                break;

            default:
                /* Power state not supported*/
                return ddNT220x_ERR_NOT_SUPPORTED;
            }

            /* Write byte 0x06 */
            err = ddNT220xWrite(pObj, 0x06, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        /* Set digital clock mode*/
        if(err == TM_OK)
        {
            switch (powerState)
            {
            case tmddNT220x_PowerNormalMode:
                /* Set sigma delta clock*/
                err = tmddNT220xSetDigital_Clock_Mode(tUnit, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetDigital_Clock_Mode(0x%08X, sigma delta clock) failed.", tUnit));
                break;

            default:
                break;
            }
        }

        if(err == TM_OK)
        {
            /* Store powerstate */
            pObj->curPowerState = powerState;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetPowerState                                     */
/*                                                                            */
/* DESCRIPTION: Get the power state of the NT220x                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetPowerState
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    ptmddNT220xPowerState_t   pPowerState /* O: Power state of this device */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get power state */
        if ((pObj->I2CMap.uBx06.bF.SM == 0x00) && (pObj->I2CMap.uBx06.bF.SM_Synthe == 0x00) && (pObj->I2CMap.uBx06.bF.SM_LT == 0x00) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x00))
        {
            *pPowerState = tmddNT220x_PowerNormalMode;
        }
        else if ((pObj->I2CMap.uBx06.bF.SM == 0x01) && (pObj->I2CMap.uBx06.bF.SM_Synthe == 0x00) && (pObj->I2CMap.uBx06.bF.SM_LT == 0x00) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x00))
        {
            *pPowerState = tmddNT220x_PowerStandbyWithLNAOnAndWithXtalOnAndWithSyntheOn;
        }
        else if ((pObj->I2CMap.uBx06.bF.SM == 0x01) && (pObj->I2CMap.uBx06.bF.SM_Synthe == 0x01) && (pObj->I2CMap.uBx06.bF.SM_LT == 0x00) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x00))
        {
            *pPowerState = tmddNT220x_PowerStandbyWithLNAOnAndWithXtalOn;
        }
        else if ((pObj->I2CMap.uBx06.bF.SM == 0x01) && (pObj->I2CMap.uBx06.bF.SM_Synthe == 0x01) && (pObj->I2CMap.uBx06.bF.SM_LT == 0x01) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x00))
        {
            *pPowerState = tmddNT220x_PowerStandbyWithXtalOn;
        }
        else if ((pObj->I2CMap.uBx06.bF.SM == 0x01) && (pObj->I2CMap.uBx06.bF.SM_Synthe == 0x01) && (pObj->I2CMap.uBx06.bF.SM_LT == 0x01) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x01))
        {
            *pPowerState = tmddNT220x_PowerStandby;
        }
        else
        {
            *pPowerState = tmddNT220x_PowerMax;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetPower_Level                                    */
/*                                                                            */
/* DESCRIPTION: Get the Power_Level bit(s) status                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetPower_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;
    UInt8                   uValue = 0;
    /* ---------- ES2 PATCH BEGIN ---------- */
    UInt8                   uValue_AGC1 = 0;
    /* ---------- ES2 PATCH END ---------- */

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }
    if(err == TM_OK)
    {
        /* Set IRQ_clear*/
        err = tmddNT220xSetIRQ_Clear(tUnit, 0x10);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIRQ_clear(0x%08X, 0x10) failed.", tUnit));
    }
    if(err == TM_OK)
    {
        /* Trigger RSSI_Meas */
        pObj->I2CMap.uBx19.MSM_byte_1 = 0x80;
        err = ddNT220xWrite(pObj, 0x19, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xWrite(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /*Trigger MSM_Launch */
            pObj->I2CMap.uBx1A.bF.MSM_Launch = 1;

            /* Write byte 0x1A */
            err = ddNT220xWrite(pObj, 0x1A, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

            pObj->I2CMap.uBx1A.bF.MSM_Launch = 0;
            if(pObj->bIRQWait)
            {
                if(err == TM_OK)
                {
                    err = ddNT220xWaitIRQ(pObj, 700, 1, 0x10);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitIRQ(0x%08X) failed.", tUnit));
                }
            }
        }

        if(err == TM_OK)
        {
            /* Read byte 0x07 */
            err = ddNT220xRead(pObj, 0x07, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Get value (limit range) */
            uValue = pObj->I2CMap.uBx07.bF.Power_Level;

            /* ---------- ES2 PATCH BEGIN ---------- */
            if(err == TM_OK && pObj->I2CMap.uBx02.bF.Major_rev == 1 && pObj->I2CMap.uBx02.bF.Minor_rev == 0)
            {
                /* Correct value according AGC1_Gain_Read */
                err = ddNT220xRead(pObj, 0x32, 1);
                if(err == TM_OK)
                {
                    uValue_AGC1 = pObj->I2CMap.uBx32.bF.AGC1_Gain_Read ;
                    if ( uValue_AGC1 <= 7)
                        uValue =  uValue + 6;
                    else  if ( uValue_AGC1 <= 8)
                        uValue = uValue - 6;
                    else
                        uValue = uValue - 9;
                }
            }
            if (uValue < NT220x_POWER_LEVEL_MIN)
            {
                *puValue = 0x00;
            }
            else if (uValue > NT220x_POWER_LEVEL_MAX)
            {
                *puValue = 0xFF;
            }
            else
            {
                *puValue = uValue;
            }
            /* ---------- ES2 PATCH END ---------- */
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIRQ_status                                     */
/*                                                                            */
/* DESCRIPTION: Get the IRQ_status bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIRQ_status
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x08 */
        err = ddNT220xGetIRQ_status(pObj, puValue);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetIRQ_status(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetMSM_XtalCal_End                                */
/*                                                                            */
/* DESCRIPTION: Get the MSM_XtalCal_End bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetMSM_XtalCal_End
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x08 */
        err = ddNT220xGetMSM_XtalCal_End(pObj, puValue);

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIRQ_Clear                                      */
/*                                                                            */
/* DESCRIPTION: Set the IRQ_Clear bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIRQ_Clear
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8           irqStatus   /* I: IRQs to clear */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set IRQ_Clear */
        /*pObj->I2CMap.uBx0A.bF.IRQ_Clear = 1; */
        pObj->I2CMap.uBx0A.IRQ_clear |= (0x80|(irqStatus&0x1F));

        /* Write byte 0x0A */
        err = ddNT220xWrite(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        /* Reset IRQ_Clear (buffer only, no write) */
        /*pObj->I2CMap.uBx0A.bF.IRQ_Clear = 0;*/
        pObj->I2CMap.uBx0A.IRQ_clear &= (~(0x80|(irqStatus&0x1F)));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC1_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC1_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC1_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0C.bF.AGC1_TOP = uValue;

        /* write byte 0x0C */
        err = ddNT220xWrite(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC1_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC1_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC1_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0C */
        err = ddNT220xRead(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0C.bF.AGC1_TOP;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC2_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC2_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC2_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* set value */
        pObj->I2CMap.uBx0D.bF.AGC2_TOP = uValue;

        /* Write byte 0x0D */
        err = ddNT220xWrite(pObj, 0x0D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC2_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC2_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC2_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0D */
        err = ddNT220xRead(pObj, 0x0D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0D.bF.AGC2_TOP;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGCs_Up_Step                                   */
/*                                                                            */
/* DESCRIPTION: Set the AGCs_Up_Step bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGCs_Up_Step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0E.bF.AGCs_Up_Step = uValue;

        /* Write byte 0x0E */
        err = ddNT220xWrite(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGCs_Up_Step                                   */
/*                                                                            */
/* DESCRIPTION: Get the AGCs_Up_Step bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGCs_Up_Step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0E */
        err = ddNT220xRead(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0E.bF.AGCs_Up_Step;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGCK_Step                                      */
/*                                                                            */
/* DESCRIPTION: Set the AGCK_Step bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGCK_Step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0E.bF.AGCK_Step = uValue;

        /* Write byte 0x0E */
        err = ddNT220xWrite(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGCK_Step                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGCK_Step bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGCK_Step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0E */
        err = ddNT220xRead(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0E.bF.AGCK_Step;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGCK_Mode                                      */
/*                                                                            */
/* DESCRIPTION: Set the AGCK_Mode bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGCK_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0E.bF.AGCK_Mode = uValue;

        /* Write byte 0x0E */
        err = ddNT220xWrite(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGCK_Mode                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGCK_Mode bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGCK_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0E */
        err = ddNT220xRead(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0E.bF.AGCK_Mode;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetPD_RFAGC_Adapt                                 */
/*                                                                            */
/* DESCRIPTION: Set the PD_RFAGC_Adapt bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetPD_RFAGC_Adapt
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0F.bF.PD_RFAGC_Adapt = uValue;

        /* Write byte 0x0F */
        err = ddNT220xWrite(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetPD_RFAGC_Adapt                                 */
/*                                                                            */
/* DESCRIPTION: Get the PD_RFAGC_Adapt bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetPD_RFAGC_Adapt
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0F */
        err = ddNT220xRead(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0F.bF.PD_RFAGC_Adapt;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRFAGC_Adapt_TOP                                */
/*                                                                            */
/* DESCRIPTION: Set the RFAGC_Adapt_TOP bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRFAGC_Adapt_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0F.bF.RFAGC_Adapt_TOP = uValue;

        /* Write byte 0x0F */
        err = ddNT220xWrite(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRFAGC_Adapt_TOP                                */
/*                                                                            */
/* DESCRIPTION: Get the RFAGC_Adapt_TOP bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRFAGC_Adapt_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0F */
        err = ddNT220xRead(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0F.bF.RFAGC_Adapt_TOP;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRF_Atten_3dB                                   */
/*                                                                            */
/* DESCRIPTION: Set the RF_Atten_3dB bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRF_Atten_3dB
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0F.bF.RF_Atten_3dB = uValue;

        /* Write byte 0x0F */
        err = ddNT220xWrite(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRF_Atten_3dB                                   */
/*                                                                            */
/* DESCRIPTION: Get the RF_Atten_3dB bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRF_Atten_3dB
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0F */
        err = ddNT220xRead(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0F.bF.RF_Atten_3dB;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRFAGC_Top                                      */
/*                                                                            */
/* DESCRIPTION: Set the RFAGC_Top bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRFAGC_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0F.bF.RFAGC_Top = uValue;

        /* Write byte 0x0F */
        err = ddNT220xWrite(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRFAGC_Top                                      */
/*                                                                            */
/* DESCRIPTION: Get the RFAGC_Top bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRFAGC_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0F */
        err = ddNT220xRead(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0F.bF.RFAGC_Top;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIR_Mixer_Top                                   */
/*                                                                            */
/* DESCRIPTION: Set the IR_Mixer_Top bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIR_Mixer_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx10.bF.IR_Mixer_Top = uValue;

        /* Write byte 0x10 */
        err = ddNT220xWrite(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIR_Mixer_Top                                   */
/*                                                                            */
/* DESCRIPTION: Get the IR_Mixer_Top bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIR_Mixer_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x10 */
        err = ddNT220xRead(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx10.bF.IR_Mixer_Top;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC5_Ana                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_Ana bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC5_Ana
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx11.bF.AGC5_Ana = uValue;

        /* Write byte 0x11 */
        err = ddNT220xWrite(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC5_Ana                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_Ana bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC5_Ana
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x11 */
        err = ddNT220xRead(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx11.bF.AGC5_Ana;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC5_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC5_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx11.bF.AGC5_TOP = uValue;

        /* Write byte 0x11 */
        err = ddNT220xWrite(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC5_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC5_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x11 */
        err = ddNT220xRead(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx11.bF.AGC5_TOP;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIF_Level                                       */
/*                                                                            */
/* DESCRIPTION: Set the IF_level bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIF_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx12.bF.IF_level = uValue;

        /* Write byte 0x12 */
        err = ddNT220xWrite(pObj, 0x12, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIF_Level                                       */
/*                                                                            */
/* DESCRIPTION: Get the IF_level bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIF_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x12 */
        err = ddNT220xRead(pObj, 0x12, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx12.bF.IF_level;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIF_HP_Fc                                       */
/*                                                                            */
/* DESCRIPTION: Set the IF_HP_Fc bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIF_HP_Fc
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx13.bF.IF_HP_Fc = uValue;

        /* Write byte 0x13 */
        err = ddNT220xWrite(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIF_HP_Fc                                       */
/*                                                                            */
/* DESCRIPTION: Get the IF_HP_Fc bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIF_HP_Fc
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x13 */
        err = ddNT220xRead(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx13.bF.IF_HP_Fc;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIF_ATSC_Notch                                  */
/*                                                                            */
/* DESCRIPTION: Set the IF_ATSC_Notch bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIF_ATSC_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx13.bF.IF_ATSC_Notch = uValue;

        /* Write byte 0x13 */
        err = ddNT220xWrite(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIF_ATSC_Notch                                  */
/*                                                                            */
/* DESCRIPTION: Get the IF_ATSC_Notch bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIF_ATSC_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x13 */
        err = ddNT220xRead(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx13.bF.IF_ATSC_Notch;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetLP_FC_Offset                                   */
/*                                                                            */
/* DESCRIPTION: Set the LP_FC_Offset bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetLP_FC_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx13.bF.LP_FC_Offset = uValue;

        /* Write byte 0x13 */
        err = ddNT220xWrite(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetLP_FC_Offset                                   */
/*                                                                            */
/* DESCRIPTION: Get the LP_FC_Offset bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetLP_FC_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x13 */
        err = ddNT220xRead(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx13.bF.LP_FC_Offset;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetLP_FC                                          */
/*                                                                            */
/* DESCRIPTION: Set the LP_Fc bit(s) status                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetLP_FC
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx13.bF.LP_Fc = uValue;

        /* Write byte 0x13 */
        err = ddNT220xWrite(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetLP_FC                                          */
/*                                                                            */
/* DESCRIPTION: Get the LP_Fc bit(s) status                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetLP_FC
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x13 */
        err = ddNT220xRead(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx13.bF.LP_Fc;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetDigital_Clock_Mode                             */
/*                                                                            */
/* DESCRIPTION: Set the Digital_Clock_Mode bit(s) status                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetDigital_Clock_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx14.bF.Digital_Clock_Mode = uValue;

        /* Write byte 0x14 */
        err = ddNT220xWrite(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetDigital_Clock_Mode                             */
/*                                                                            */
/* DESCRIPTION: Get the Digital_Clock_Mode bit(s) status                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetDigital_Clock_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x14 */
        err = ddNT220xRead(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx14.bF.Digital_Clock_Mode;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Set the IF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx15.bF.IF_Freq = (UInt8)(uValue / 50000);

        /* Write byte 0x15 */
        err = ddNT220xWrite(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Get the IF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x15 */
        err = ddNT220xRead(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx15.bF.IF_Freq * 50000;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Set the RF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;
    UInt32                  uRF = 0;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        //***************************************
        // Configures the settings that depends on the chosen received TV standard
        // (standard and demodulator dependent)

        //pObj->I2CMap.uBx0E.AGCK_byte_1 = 0x1F;
        //pObj->I2CMap.uBx0F.RF_AGC_byte = 0x15;
        //pObj->I2CMap.uBx10.IR_Mixer_byte_1 = 0x0A;
        //pObj->I2CMap.uBx11.AGC5_byte_1 = 0x0A;
        //pObj->I2CMap.uBx12.IF_AGC_byte = 0x00;
        //pObj->I2CMap.uBx13.IF_Byte_1 = 0xE0;
        //pObj->I2CMap.uBx14.Reference_Byte = 0x03;
        //pObj->I2CMap.uBx15.IF_Frequency_byte = 0x00;

        ///* Write bytes 0x0E to 0x15
        //err = ddNT220xWrite(pObj, 0x0E, 8);
        //tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        //***************************************

        /*****************************************/
        /* Tune the settings that depend on the RF input frequency, expressed in kHz.*/
        /* RF filters tuning, PLL locking*/
        /* State reached after 5ms*/

        if(err == TM_OK)
        {
            /* Set IRQ_clear */
            err = tmddNT220xSetIRQ_Clear(tUnit, 0x0C);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetIRQ_clear(0x%08X, 0x0C) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set power state ON */
            err = tmddNT220xSetPowerState(tUnit, tmddNT220x_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xSetPowerState(0x%08X, PowerNormalMode) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set RF frequency expressed in kHz */
            uRF = uValue / 1000;
			pObj->I2CMap.uBx16.bF.RF_Freq_1 = (UInt8)((uRF & 0x00FF0000) >> 16);
			pObj->I2CMap.uBx17.bF.RF_Freq_2 = (UInt8)((uRF & 0x0000FF00) >> 8);
			pObj->I2CMap.uBx18.bF.RF_Freq_3 = (UInt8)(uRF & 0x000000FF);
            /* write bytes 0x16 to 0x18*/
            err = ddNT220xWrite(pObj, 0x16, 3);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set & trigger MSM */
            pObj->I2CMap.uBx19.MSM_byte_1 = 0x41;
            pObj->I2CMap.uBx1A.MSM_byte_2 = 0x01;

            /* Write bytes 0x19 to 0x1A */
            err = ddNT220xWrite(pObj, 0x19, 2);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

            pObj->I2CMap.uBx1A.MSM_byte_2 = 0x00;
        }
        if(pObj->bIRQWait)
        {
            if(err == TM_OK)
            {
                err = ddNT220xWaitIRQ(pObj, 50, 5, 0x0C);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitIRQ(0x%08X) failed.", tUnit));
            }

            /* PATCH ES2 in case of WAIT IRQ Timeout */
            if(err == ddNT220x_ERR_NOT_READY && pObj->I2CMap.uBx02.bF.Major_rev == 1 && pObj->I2CMap.uBx02.bF.Minor_rev == 0)
            {
                pObj->bSoftReset = True;
            }
            /* ---------- ES2 PATCH END ---------- */

            if(err == TM_OK && pObj->bRFCAL_SW_Algo_Enable)
            {
                err = tmddNT220xRFFilterCorrTune(tUnit, uValue);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddNT220xRFFilterCorrTune(0x%08X) failed.", tUnit));
            }

        }
        /*****************************************/


        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Get the RF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read bytes 0x16 to 0x18 */
        err = ddNT220xRead(pObj, 0x16, 3);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = (pObj->I2CMap.uBx16.bF.RF_Freq_1 << 16) | (pObj->I2CMap.uBx17.bF.RF_Freq_2 << 8) | pObj->I2CMap.uBx18.bF.RF_Freq_3;
            *puValue = *puValue * 1000;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xSetXtalCal_Launch:
//
// DESCRIPTION: Set the XtalCal_Launch bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xSetXtalCal_Launch
(
 tmUnitSelect_t      tUnit    //  I: Unit number
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1A.bF.XtalCal_Launch = 1;

        // write byte 0x1A
        err = ddNT220xWrite(pObj, 0x1A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        // reset XtalCal_Launch (buffer only, no write)
        pObj->I2CMap.uBx1A.bF.XtalCal_Launch = 0;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddNT220xGetXtalCal_Launch:
//
// DESCRIPTION: Get the XtalCal_Launch bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddNT220x_ERR_BAD_PARAMETER
//         ddNT220x_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddNT220xGetXtalCal_Launch
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x1A
        err = ddNT220xRead(pObj, 0x1A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1A.bF.XtalCal_Launch;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetMSM_Launch                                     */
/*                                                                            */
/* DESCRIPTION: Set the MSM_Launch bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetMSM_Launch
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1A.bF.MSM_Launch = 1;

        /* Write byte 0x1A */
        err = ddNT220xWrite(pObj, 0x1A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        /* Reset MSM_Launch (buffer only, no write) */
        pObj->I2CMap.uBx1A.bF.MSM_Launch = 0x00;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetMSM_Launch                                     */
/*                                                                            */
/* DESCRIPTION: Get the MSM_Launch bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetMSM_Launch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1A */
        err = ddNT220xRead(pObj, 0x1A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1A.bF.MSM_Launch;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetPSM_StoB                                       */
/*                                                                            */
/* DESCRIPTION: Set the PSM_StoB bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetPSM_StoB
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1B.bF.PSM_StoB = uValue;

        /* Read byte 0x1B */
        err = ddNT220xWrite(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetPSM_StoB                                       */
/*                                                                            */
/* DESCRIPTION: Get the PSM_StoB bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetPSM_StoB
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1B */
        err = ddNT220xRead(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1B.bF.PSM_StoB;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIR_Loop                                        */
/*                                                                            */
/* DESCRIPTION: Set the IR_Loop bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIR_Loop
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1E.bF.IR_Loop = uValue - 4;

        /* Read byte 0x1E */
        err = ddNT220xWrite(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIR_Loop                                        */
/*                                                                            */
/* DESCRIPTION: Get the IR_Loop bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIR_Loop
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1E */
        err = ddNT220xRead(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1E.bF.IR_Loop + 4;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIR_Target                                      */
/*                                                                            */
/* DESCRIPTION: Set the IR_Target bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIR_Target
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1E.bF.IR_Target = uValue;

        /* Read byte 0x1E */
        err = ddNT220xWrite(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIR_Target                                      */
/*                                                                            */
/* DESCRIPTION: Get the IR_Target bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIR_Target
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1E */
        err = ddNT220xRead(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1E.bF.IR_Target;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIR_Corr_Boost                                  */
/*                                                                            */
/* DESCRIPTION: Set the IR_Corr_Boost bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIR_Corr_Boost
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1F.bF.IR_Corr_Boost = uValue;

        /* Read byte 0x1F */
        err = ddNT220xWrite(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIR_Corr_Boost                                  */
/*                                                                            */
/* DESCRIPTION: Get the IR_Corr_Boost bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIR_Corr_Boost
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1F */
        err = ddNT220xRead(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1F.bF.IR_Corr_Boost;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIR_mode_ram_store                              */
/*                                                                            */
/* DESCRIPTION: Set the IR_mode_ram_store bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIR_mode_ram_store
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1F.bF.IR_mode_ram_store = uValue;

        /* Write byte 0x1F */
        err = ddNT220xWrite(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIR_mode_ram_store                              */
/*                                                                            */
/* DESCRIPTION: Get the IR_mode_ram_store bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIR_mode_ram_store
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1F */
        err = ddNT220xRead(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1F.bF.IR_mode_ram_store;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetPD_Udld                                        */
/*                                                                            */
/* DESCRIPTION: Set the PD_Udld bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetPD_Udld
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx22.bF.PD_Udld = uValue;

        /* Write byte 0x22 */
        err = ddNT220xWrite(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetPD_Udld                                        */
/*                                                                            */
/* DESCRIPTION: Get the PD_Udld bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetPD_Udld
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x22 */
        err = ddNT220xRead(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx22.bF.PD_Udld;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC_Ovld_TOP                                   */
/*                                                                            */
/* DESCRIPTION: Set the AGC_Ovld_TOP bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC_Ovld_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx22.bF.AGC_Ovld_TOP = uValue;

        /* Write byte 0x22 */
        err = ddNT220xWrite(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC_Ovld_TOP                                   */
/*                                                                            */
/* DESCRIPTION: Get the AGC_Ovld_TOP bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC_Ovld_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x22 */
        err = ddNT220xRead(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx22.bF.AGC_Ovld_TOP;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetHi_Pass                                        */
/*                                                                            */
/* DESCRIPTION: Set the Hi_Pass bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetHi_Pass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx23.bF.Hi_Pass = uValue;

        /* Read byte 0x23 */
        err = ddNT220xWrite(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetHi_Pass                                        */
/*                                                                            */
/* DESCRIPTION: Get the Hi_Pass bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetHi_Pass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x23 */
        err = ddNT220xRead(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx23.bF.Hi_Pass;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIF_Notch                                       */
/*                                                                            */
/* DESCRIPTION: Set the IF_Notch bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIF_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx23.bF.IF_Notch = uValue;

        /* Read byte 0x23 */
        err = ddNT220xWrite(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIF_Notch                                       */
/*                                                                            */
/* DESCRIPTION: Get the IF_Notch bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIF_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x23 */
        err = ddNT220xRead(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx23.bF.IF_Notch;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC5_loop_off                                  */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_loop_off bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC5_loop_off
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx25.bF.AGC5_loop_off = uValue;

        /* Read byte 0x25 */
        err = ddNT220xWrite(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC5_loop_off                                  */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_loop_off bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC5_loop_off
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x25 */
        err = ddNT220xRead(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx25.bF.AGC5_loop_off;
        }

        (void)ddNT220xMutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC5_Do_step                                   */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_Do_step bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC5_Do_step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx25.bF.AGC5_Do_step = uValue;

        /* Read byte 0x25 */
        err = ddNT220xWrite(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC5_Do_step                                   */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_Do_step bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC5_Do_step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x25 */
        err = ddNT220xRead(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx25.bF.AGC5_Do_step;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetForce_AGC5_gain                                */
/*                                                                            */
/* DESCRIPTION: Set the Force_AGC5_gain bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetForce_AGC5_gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx25.bF.Force_AGC5_gain = uValue;

        /* Read byte 0x25 */
        err = ddNT220xWrite(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetForce_AGC5_gain                                */
/*                                                                            */
/* DESCRIPTION: Get the Force_AGC5_gain bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetForce_AGC5_gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x25 */
        err = ddNT220xRead(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx25.bF.Force_AGC5_gain;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetAGC5_Gain                                      */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_Gain bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetAGC5_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx25.bF.AGC5_Gain = uValue;

        /* Read byte 0x25 */
        err = ddNT220xWrite(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetAGC5_Gain                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_Gain bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetAGC5_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x25 */
        err = ddNT220xRead(pObj, 0x25, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx25.bF.AGC5_Gain;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRF_Filter_Bypass                               */
/*                                                                            */
/* DESCRIPTION: Set the RF_Filter_Bypass bit(s) status                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRF_Filter_Bypass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2C.bF.RF_Filter_Bypass = uValue;

        /* Read byte 0x2C */
        err = ddNT220xWrite(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRF_Filter_Bypass                               */
/*                                                                            */
/* DESCRIPTION: Get the RF_Filter_Bypass bit(s) status                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRF_Filter_Bypass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2C */
        err = ddNT220xRead(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2C.bF.RF_Filter_Bypass;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRF_Filter_Band                                 */
/*                                                                            */
/* DESCRIPTION: Set the RF_Filter_Band bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRF_Filter_Band
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2C.bF.RF_Filter_Band = uValue;

        /* Read byte 0x2C */
        err = ddNT220xWrite(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRF_Filter_Band                                 */
/*                                                                            */
/* DESCRIPTION: Get the RF_Filter_Band bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRF_Filter_Band
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2C */
        err = ddNT220xRead(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2C.bF.RF_Filter_Band;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRF_Filter_Cap                                  */
/*                                                                            */
/* DESCRIPTION: Set the RF_Filter_Cap bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRF_Filter_Cap
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2D.bF.RF_Filter_Cap = uValue;

        /* Read byte 0x2D */
        err = ddNT220xWrite(pObj, 0x2D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRF_Filter_Cap                                  */
/*                                                                            */
/* DESCRIPTION: Get the RF_Filter_Cap bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRF_Filter_Cap
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2D */
        err = ddNT220xRead(pObj, 0x2D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2D.bF.RF_Filter_Cap;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetGain_Taper                                     */
/*                                                                            */
/* DESCRIPTION: Set the Gain_Taper bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetGain_Taper
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2E.bF.Gain_Taper = uValue;

        /* Read byte 0x2E */
        err = ddNT220xWrite(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetGain_Taper                                     */
/*                                                                            */
/* DESCRIPTION: Get the Gain_Taper bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetGain_Taper
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2E */
        err = ddNT220xRead(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2E.bF.Gain_Taper;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetN_CP_Current                                   */
/*                                                                            */
/* DESCRIPTION: Set the N_CP_Current bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetN_CP_Current
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx30.bF.N_CP_Current = uValue;

        /* Read byte 0x30 */
        err = ddNT220xWrite(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetN_CP_Current                                   */
/*                                                                            */
/* DESCRIPTION: Get the N_CP_Current bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetN_CP_Current
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x30 */
        err = ddNT220xRead(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx30.bF.N_CP_Current;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRSSI_Ck_Speed                                  */
/*                                                                            */
/* DESCRIPTION: Set the RSSI_Ck_Speed bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRSSI_Ck_Speed
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx36.bF.RSSI_Ck_Speed = uValue;
        /* Write byte 0x36 */
        err = ddNT220xWrite(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRSSI_Ck_Speed                                  */
/*                                                                            */
/* DESCRIPTION: Get the RSSI_Ck_Speed bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRSSI_Ck_Speed
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x36 */
        err = ddNT220xRead(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx36.bF.RSSI_Ck_Speed;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetRFCAL_Phi2                                     */
/*                                                                            */
/* DESCRIPTION: Set the RFCAL_Phi2 bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetRFCAL_Phi2
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx37.bF.RFCAL_Phi2 = uValue;

        /* Write byte 0x37 */
        err = ddNT220xWrite(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWrite(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetRFCAL_Phi2                                     */
/*                                                                            */
/* DESCRIPTION: Get the RFCAL_Phi2 bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetRFCAL_Phi2
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x37 */
        err = ddNT220xRead(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx37.bF.RFCAL_Phi2;
        }

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xWaitIRQ                                           */
/*                                                                            */
/* DESCRIPTION: Wait the IRQ to trigger                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xWaitIRQ
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeout */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = ddNT220xWaitIRQ(pObj, timeOut, waitStep, irqStatus);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitIRQ(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xWaitXtalCal_End                                   */
/*                                                                            */
/* DESCRIPTION: Wait the MSM_XtalCal_End to trigger                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xWaitXtalCal_End
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeout */
    UInt32          waitStep    /* I: wait step */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = ddNT220xWaitXtalCal_End(pObj, timeOut, waitStep);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xWaitXtalCal_End(0x%08X) failed.", tUnit));

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetIRQWait                                        */
/*                                                                            */
/* DESCRIPTION: Set whether wait IRQ in driver or not                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetIRQWait
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        pObj->bIRQWait = bWait;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetIRQWait                                        */
/*                                                                            */
/* DESCRIPTION: Get whether wait IRQ in driver or not                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetIRQWait
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (pbWait == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pbWait = pObj->bIRQWait;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSoftReset                                         */
/*                                                                            */
/* DESCRIPTION: Soft Reset                                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSoftReset
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        pObj->bSoftReset = True;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xSetVersionForced                                  */
/*                                                                            */
/* DESCRIPTION: Get NT220x IC version forced                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xSetVersionForced
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddNT220xGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        pObj->versionForced = uValue;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddNT220xGetVersionForced                                  */
/*                                                                            */
/* DESCRIPTION: Get NT220x IC version forced                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddNT220xGetVersionForced
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddNT220xObject_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddNT220xGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xGetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddNT220xMutexAcquire(pObj, ddNT220x_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *puValue = pObj->versionForced;

        (void)ddNT220xMutexRelease(pObj);
    }

    return err;
}


/*============================================================================*/
/* FUNCTION:    ddNT220xGetIRQ_status                                       */
/*                                                                            */
/* DESCRIPTION: Get IRQ status                                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xGetIRQ_status
(
    ptmddNT220xObject_t   pObj,   /* I: Instance object */
    UInt8*                  puValue /* I: Address of the variable to output item value */
)
{
    tmErrorCode_t   err  = TM_OK;

    /* Read byte 0x08 */
    err = ddNT220xRead(pObj, 0x08, 1);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", pObj->tUnit));

    if(err == TM_OK)
    {
        /* Get value */
        *puValue = pObj->I2CMap.uBx08.bF.IRQ_status;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xGetMSM_XtalCal_End                                  */
/*                                                                            */
/* DESCRIPTION: Get MSM_XtalCal_End bit(s) status                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xGetMSM_XtalCal_End
(
    ptmddNT220xObject_t   pObj,   /* I: Instance object */
    UInt8*                  puValue /* I: Address of the variable to output item value */
)
{
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddNT220x_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Read byte 0x08 */
        err = ddNT220xRead(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddNT220xRead(0x%08X) failed.", pObj->tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx08.bF.MSM_XtalCal_End;
        }
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xWaitIRQ                                             */
/*                                                                            */
/* DESCRIPTION: Wait for IRQ to trigger                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xWaitIRQ
(
    ptmddNT220xObject_t   pObj,       /* I: Instance object */
    UInt32                  timeOut,    /* I: timeout */
    UInt32                  waitStep,   /* I: wait step */
    UInt8                   irqStatus   /* I: IRQs to wait */
)
{
    tmErrorCode_t   err  = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStep ms */
    UInt8           uIRQ = 0;
    UInt8           uIRQStatus = 0;
    Bool            bIRQTriggered = False;

    while(err == TM_OK && (--counter)>0)
    {
        err = ddNT220xGetIRQ_status(pObj, &uIRQ);

        if(err == TM_OK && uIRQ == 1)
        {
            bIRQTriggered = True;
        }

        if(bIRQTriggered)
        {
            /* IRQ triggered => Exit */
            break;
        }

        if(err == TM_OK && irqStatus != 0x00)
        {
            uIRQStatus = ((pObj->I2CMap.uBx08.IRQ_status)&0x1F);

            if(irqStatus == uIRQStatus)
            {
                bIRQTriggered = True;
            }
        }

        err = ddNT220xWait(pObj, waitStep);
    }

    if(counter == 0)
    {
        err = ddNT220x_ERR_NOT_READY;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xWaitXtalCal_End                                     */
/*                                                                            */
/* DESCRIPTION: Wait for MSM_XtalCal_End to trigger                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xWaitXtalCal_End
(
    ptmddNT220xObject_t   pObj,       /* I: Instance object */
    UInt32                  timeOut,    /* I: timeout */
    UInt32                  waitStep    /* I: wait step */
)
{
    tmErrorCode_t   err  = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStepms */
    UInt8           uMSM_XtalCal_End = 0;

    while(err == TM_OK && (--counter)>0)
    {
        err = ddNT220xGetMSM_XtalCal_End(pObj, &uMSM_XtalCal_End);

        if(uMSM_XtalCal_End == 1)
        {
            /* MSM_XtalCal_End triggered => Exit */
            break;
        }

        ddNT220xWait(pObj, waitStep);
    }

    if(counter == 0)
    {
        err = ddNT220x_ERR_NOT_READY;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xWrite                                               */
/*                                                                            */
/* DESCRIPTION: Write in NT220x hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xWrite
(
    ptmddNT220xObject_t   pObj,           /* I: Driver object */
    UInt8                   uSubAddress,    /* I: sub address */
    UInt8                   uNbData         /* I: nb of data */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8*          pI2CMap = Null;

    /* pI2CMap initialization */
    pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1);

    err = POBJ_SRVFUNC_SIO.Write (pObj->tUnitW, 1, &uSubAddress, uNbData, &(pI2CMap[uSubAddress]));

    /* return value */
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xRead                                                */
/*                                                                            */
/* DESCRIPTION: Read in NT220x hardware                                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xRead
(
    ptmddNT220xObject_t   pObj,           /* I: Driver object */
    UInt8                   uSubAddress,    /* I: sub address */
    UInt8                   uNbData         /* I: nb of data */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8*          pI2CMap = Null;

    /* pRegister initialization */
    pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1) + uSubAddress;

    /* Read data from the Tuner */
    err = POBJ_SRVFUNC_SIO.Read(pObj->tUnitW, 1, &uSubAddress, uNbData, pI2CMap);

    if(err == TM_OK)
    {
        switch(pObj->versionForced)
        {
        default:
        case tmddNT220x_Version_Not_Forced:
            break;

        case tmddNT220x_Version_Forced_ES2:
            pObj->I2CMap.uBx02.bF.Major_rev = 1;
            pObj->I2CMap.uBx02.bF.Minor_rev = 0;
            break;

        case tmddNT220x_Version_Forced_ES3:
            pObj->I2CMap.uBx02.bF.Major_rev = 1;
            pObj->I2CMap.uBx02.bF.Minor_rev = 1;
            break;
        }
    }

    /* return value */
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xWait                                                */
/*                                                                            */
/* DESCRIPTION: Wait for the requested time                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xWait
(
    ptmddNT220xObject_t   pObj,   /* I: Driver object */
    UInt32                  Time    /*  I: time to wait for */
)
{
    tmErrorCode_t   err  = TM_OK;

    /* wait Time ms */
    err = POBJ_SRVFUNC_STIME.Wait (pObj->tUnit, Time);

    /* Return value */
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xMutexAcquire                                        */
/*                                                                            */
/* DESCRIPTION: Acquire driver mutex                                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xMutexAcquire
(
    ptmddNT220xObject_t   pObj,
    UInt32                  timeOut
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Acquire != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Acquire(pObj->pMutex, timeOut);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddNT220xMutexRelease                                        */
/*                                                                            */
/* DESCRIPTION: Release driver mutex                                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddNT220xMutexRelease
(
    ptmddNT220xObject_t   pObj
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Release != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Release(pObj->pMutex);
    }

    return err;
}

