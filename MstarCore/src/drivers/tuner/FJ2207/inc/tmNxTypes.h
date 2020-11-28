/*==========================================================================*/
/*     (Copyright (C) 2003 Koninklijke Philips Electronics N.V.             */
/*     All rights reserved.                                                 */
/*     This source code and any compilation or derivative thereof is the    */
/*     proprietary information of Koninklijke Philips Electronics N.V.      */
/*     and is confidential in nature.                                       */
/*     Under no circumstances is this software to be exposed to or placed   */
/*     under an Open Source License of any type without the expressed       */
/*     written permission of Koninklijke Philips Electronics N.V.           */
/*==========================================================================*/
/*
* Copyright (C) 2000,2001
*               Koninklijke Philips Electronics N.V.
*               All Rights Reserved.
*
* Copyright (C) 2000,2001 TriMedia Technologies, Inc.
*               All Rights Reserved.
*
*############################################################
*
* Module name  : tmNxTypes.h  %version: 4 %
*
* Last Update  : %date_modified: Tue Jul  8 18:08:00 2003 %
*
* Description: TriMedia/MIPS global type definitions.
*
* Document Ref: DVP Software Coding Guidelines Specification
* DVP/MoReUse Naming Conventions specification
* DVP Software Versioning Specification
* DVP Device Library Architecture Specification
* DVP Board Support Library Architecture Specification
* DVP Hardware API Architecture Specification
*
*
*############################################################
*/

#ifndef TMNXTYPES_H
#define TMNXTYPES_H

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//
#include "tmFlags.h"                    // DVP common build control flags

#ifdef __cplusplus
extern "C"
{
#endif

    //-----------------------------------------------------------------------------
    // Types and defines:
    //-----------------------------------------------------------------------------
    //

    /*Under the TCS, <tmlib/tmtypes.h> may have been included by our client. In
    order to avoid errors, we take account of this possibility, but in order to
    support environments where the TCS is not available, we do not include the
    file by name.*/

#ifndef _TMtypes_h
#define _TMtypes_h

#define False           0
#define True            1

#ifdef TMFL_NATIVE_C_FORCED
 #undef TMFL_DOT_NET_2_0_TYPES
#undef NXPFE
#endif

#ifndef TMFL_DOT_NET_2_0_TYPES
 #ifdef __cplusplus
  #define Null            0
 #else
  #define Null            ((Void *) 0)
 #endif
#else
 #define Null            nullptr
#endif

    //
    //      Standard Types
    //

    typedef signed   char   CInt8;   //  8 bit   signed integer
    typedef signed   short  CInt16;  // 16 bit   signed integer
    typedef signed   long   CInt32;  // 32 bit   signed integer
    typedef unsigned char   CUInt8;  //  8 bit unsigned integer
    typedef unsigned short  CUInt16; // 16 bit unsigned integer
    typedef unsigned long   CUInt32; // 32 bit unsigned integer
    typedef float           CFloat;  // 32 bit floating point
    typedef unsigned int    CBool;   // Boolean (True/False)
    typedef char            CChar;   // character, character array ptr
    typedef int             CInt;    // machine-natural integer
    typedef unsigned int    CUInt;   // machine-natural unsigned integer

#ifndef TMFL_DOT_NET_2_0_TYPES
    typedef CInt8           Int8;   //  8 bit   signed integer
    typedef CInt16          Int16;  // 16 bit   signed integer
    typedef CInt32          Int32;  // 32 bit   signed integer
    typedef CUInt8          UInt8;  //  8 bit unsigned integer
    typedef CUInt16         UInt16; // 16 bit unsigned integer
    typedef CUInt32         UInt32; // 32 bit unsigned integer
    typedef CFloat          Float;  // 32 bit floating point
    typedef CBool           Bool;   // Boolean (True/False)
    typedef CChar           Char;   // character, character array ptr
    typedef CInt            Int;    // machine-natural integer
    typedef CUInt           UInt;   // machine-natural unsigned integer
    typedef char           *String; // Null terminated 8 bit char str

    //-----------------------------------------------------------------------------
    // Legacy TM Types/Structures (Not necessarily DVP Coding Guideline compliant)
    // NOTE: For DVP Coding Gudeline compliant code, do not use these types.
    //
    typedef char          *Address;        // Ready for address-arithmetic
    typedef char const    *ConstAddress;
    typedef unsigned char  Byte;           // Raw byte
    typedef float          Float32;        // Single-precision float
    typedef double         Float64;        // Double-precision float
    typedef void          *Pointer;        // Pointer to anonymous object
    typedef void const    *ConstPointer;
    typedef char const    *ConstString;
#else
    using namespace System;    
    typedef int             Int;
    typedef SByte           Int8;
    typedef Byte            UInt8;
    typedef float           Float32;    
    typedef unsigned int    Bool;
#endif


    typedef Int             Endian;
#define BigEndian       0
#define LittleEndian    1

    typedef struct tmVersion
    {
        UInt8   majorVersion;
        UInt8   minorVersion;
        UInt16  buildVersion;
    }   tmVersion_t, *ptmVersion_t;
#endif /*ndef _TMtypes_h*/

    /*Define DVP types that are not TCS types.*/

#ifndef TMFL_DOT_NET_2_0_TYPES
    typedef Int8   *pInt8;            //  8 bit   signed integer
    typedef Int16  *pInt16;           // 16 bit   signed integer
    typedef Int32  *pInt32;           // 32 bit   signed integer
    typedef UInt8  *pUInt8;           //  8 bit unsigned integer
    typedef UInt16 *pUInt16;          // 16 bit unsigned integer
    typedef UInt32 *pUInt32;          // 32 bit unsigned integer
    typedef void    Void, *pVoid;     // Void (typeless)
    typedef Float  *pFloat;           // 32 bit floating point
    typedef double  Double, *pDouble; // 32/64 bit floating point
    typedef Bool   *pBool;            // Boolean (True/False)
    typedef Char   *pChar;            // character, character array ptr
    typedef Int    *pInt;             // machine-natural integer
    typedef UInt   *pUInt;            // machine-natural unsigned integer
    typedef String *pString;          // Null terminated 8 bit char str,
#else
    typedef Void *pVoid;     // Void (typeless)
#endif
    /*Assume that 64-bit integers are supported natively by C99 compilers and Visual
    C version 6.00 and higher. More discrimination in this area may be added
    here as necessary.*/
#ifndef TMFL_DOT_NET_2_0_TYPES
#if defined __STDC_VERSION__ && __STDC_VERSION__ > 199409L
    /*This can be enabled only when all explicit references to the hi and lo
    structure members are eliminated from client code.*/
#define TMFL_NATIVE_INT64 1
    typedef signed   long long int Int64,  *pInt64;  // 64-bit integer
    typedef unsigned long long int UInt64, *pUInt64; // 64-bit bitmask
    // #elif defined _MSC_VER && _MSC_VER >= 1200
    // /*This can be enabled only when all explicit references to the hi and lo
    //     structure members are eliminated from client code.*/
    // #define TMFL_NATIVE_INT64 1
    // typedef signed   __int64 Int64,  *pInt64;  // 64-bit integer
    // typedef unsigned __int64 UInt64, *pUInt64; // 64-bit bitmask
#else /*!(defined __STDC_VERSION__ && __STDC_VERSION__ > 199409L)*/
#define TMFL_NATIVE_INT64 0
    typedef
    struct
    {
        /*Get the correct endianness (this has no impact on any other part of
        the system, but may make memory dumps easier to understand).*/
#if TMFL_ENDIAN == TMFL_ENDIAN_BIG
        Int32 hi; UInt32 lo;
#else
        UInt32 lo; Int32 hi;
#endif
    }
    Int64, *pInt64; // 64-bit integer
    typedef
    struct
    {
#if TMFL_ENDIAN == TMFL_ENDIAN_BIG
        UInt32 hi; UInt32 lo;
#else
        UInt32 lo; UInt32 hi;
#endif
    }
    UInt64, *pUInt64; // 64-bit bitmask
#endif /*defined __STDC_VERSION__ && __STDC_VERSION__ > 199409L*/
#endif /*TMFL_DOT_NET_2_0_TYPES*/
    // Maximum length of device name in all BSP and capability structures
#define HAL_DEVICE_NAME_LENGTH 16

    typedef CUInt32 tmErrorCode_t;
    typedef CUInt32 tmProgressCode_t;

    /* timestamp definition */
#ifndef TMFL_DOT_NET_2_0_TYPES
    typedef UInt64 tmTimeStamp_t, *ptmTimeStamp_t;
#endif
    //for backwards compatibility with the older tmTimeStamp_t definition
#define ticks   lo
#define hiTicks hi

    typedef union tmColor3                 // 3 byte color structure
    {
        unsigned long u32;
#if (TMFL_ENDIAN == TMFL_ENDIAN_BIG)
        struct {
UInt32       : 8;
            UInt32 red   : 8;
            UInt32 green : 8;
            UInt32 blue  : 8;
        } rgb;
        struct {
UInt32   : 8;
            UInt32 y : 8;
            UInt32 u : 8;
            UInt32 v : 8;
        } yuv;
        struct {
UInt32   : 8;
            UInt32 u : 8;
            UInt32 m : 8;
            UInt32 l : 8;
        } uml;
#else
        struct {
            UInt32 blue  : 8;
            UInt32 green : 8;
            UInt32 red   : 8;
UInt32       : 8;
        } rgb;
        struct {
            UInt32 v : 8;
            UInt32 u : 8;
            UInt32 y : 8;
UInt32   : 8;
        } yuv;
        struct {
            UInt32 l : 8;
            UInt32 m : 8;
            UInt32 u : 8;
UInt32   : 8;
        } uml;
#endif
    }   tmColor3_t, *ptmColor3_t;

    typedef union tmColor4                 // 4 byte color structure
    {
        unsigned long u32;
#if (TMFL_ENDIAN == TMFL_ENDIAN_BIG)
        struct {
            UInt32 alpha    : 8;
            UInt32 red      : 8;
            UInt32 green    : 8;
            UInt32 blue     : 8;
        } argb;
        struct {
            UInt32 alpha    : 8;
            UInt32 y        : 8;
            UInt32 u        : 8;
            UInt32 v        : 8;
        } ayuv;
        struct {
            UInt32 alpha    : 8;
            UInt32 u        : 8;
            UInt32 m        : 8;
            UInt32 l        : 8;
        } auml;
#else
        struct {
            UInt32 blue     : 8;
            UInt32 green    : 8;
            UInt32 red      : 8;
            UInt32 alpha    : 8;
        } argb;
        struct {
            UInt32 v        : 8;
            UInt32 u        : 8;
            UInt32 y        : 8;
            UInt32 alpha    : 8;
        } ayuv;
        struct {
            UInt32 l        : 8;
            UInt32 m        : 8;
            UInt32 u        : 8;
            UInt32 alpha    : 8;
        } auml;
#endif
    }   tmColor4_t, *ptmColor4_t;

    //-----------------------------------------------------------------------------
    // Hardware device power states
    //
    typedef enum tmPowerState
    {
        tmPowerOn,                          // Device powered on      (D0 state)
        tmPowerStandby,                     // Device power standby   (D1 state)
        tmPowerSuspend,                     // Device power suspended (D2 state)
        tmPowerOff                          // Device powered off     (D3 state)

    }   tmPowerState_t, *ptmPowerState_t;

    //-----------------------------------------------------------------------------
    // Software Version Structure
    //
    typedef struct tmSWVersion
    {
        UInt32      compatibilityNr;        // Interface compatibility number
        UInt32      majorVersionNr;         // Interface major version number
        UInt32      minorVersionNr;         // Interface minor version number

    }   tmSWVersion_t, *ptmSWVersion_t;

    /*Under the TCS, <tm1/tmBoardDef.h> may have been included by our client. In
    order to avoid errors, we take account of this possibility, but in order to
    support environments where the TCS is not available, we do not include the
    file by name.*/
#ifndef _TMBOARDDEF_H_
#define _TMBOARDDEF_H_

    //-----------------------------------------------------------------------------
    // HW Unit Selection
    //
    typedef CInt tmUnitSelect_t, *ptmUnitSelect_t;

#define tmUnitNone (-1)
#define tmUnit0    0
#define tmUnit1    1
#define tmUnit2    2
#define tmUnit3    3
#define tmUnit4    4

    /*+compatibility*/
#define unitSelect_t       tmUnitSelect_t
#define unit0              tmUnit0
#define unit1              tmUnit1
#define unit2              tmUnit2
#define unit3              tmUnit3
#define unit4              tmUnit4
#define DEVICE_NAME_LENGTH HAL_DEVICE_NAME_LENGTH
    /*-compatibility*/

#endif /*ndef _TMBOARDDEF_H_ */

    //-----------------------------------------------------------------------------
    // Instance handle
    //
    typedef Int tmInstance_t, *ptmInstance_t;

#ifndef TMFL_DOT_NET_2_0_TYPES
    // Callback function declaration
    typedef Void (*ptmCallback_t) (UInt32 events, Void *pData, UInt32 userData);
#define tmCallback_t ptmCallback_t /*compatibility*/
#endif
    //-----------------------------------------------------------------------------
    // INLINE keyword for inline functions in all environments
    //
    // WinNT/WinCE: Use TMSHARED_DATA_BEGIN/TMSHARED_DATA_END for multiprocess
    //  shared data on a single CPU.  To define data variables that are shared
    //  across all processes for WinNT/WinCE, use the defined #pragma macros
    //  TMSHARED_DATA_BEGIN/TMSHARED_DATA_END and initialize the data variables
    //  as shown in the example below.  Data defined outside of the begin/end
    //  section or not initialized will not be shared across all processes for
    //  WinNT/WinCE; there will be a separate instance of the variable in each
    //  process.  Use WinNT Explorer "QuickView" on the target DLL or text edit
    //  the target DLL *.map file to verify the shared data section presence and
    //  size (shared/static variables will not be named in the MAP file but will
    //  be included in the shared section virtual size).
    // NOTE: All data variables in the multiprocess section _MUST_BE_INITIALIZED_
    //       to be shared across processes; if no explicit initialization is
    //       done, the data variables will not be shared across processes.  This
    //       shared data mechanism only applies to WinNT/WinCE multiprocess data
    //       on a single CPU (pSOS shares all data across tasks by default).  Use
    //       the TMML MP shared data region for shared data across multiple CPUs
    //       and multiple processes.  Example (note global variable naming):
    //
    //  #if     (TMFL_OS_IS_CE || TMFL_OS_IS_NT)
    //  #pragma TMSHARED_DATA_BEGIN         // Multiprocess shared data begin
    //  #endif
    //
    //  static g<Multiprocess shared data variable> = <Initialization value>;
    //         gtm<Multiprocess shared data variable> = <Initialization value>;
    //
    //  #if     (TMFL_OS_IS_CE || TMFL_OS_IS_NT)
    //  #pragma TMSHARED_DATA_END           // Multiprocess shared data end
    //  #endif
    //

#if        TMFL_OS_IS_CE || TMFL_OS_IS_NT
#define inline  __inline

    //
    // Places shared data in named DLL data segment for WinNT/WinCE builds.
    // NOTE: These pragma defines require DLLFLAGS += -section:.tmShare,RWS in the
    //       nt.mak and ce.mak target OS makefiles for this mechanism to work.
    //
#define TMSHARED_DATA_BEGIN     data_seg(".tmShare")
#define TMSHARED_DATA_END       data_seg()

#elif      TMFL_OS_IS_PSOS && TMFL_CPU_IS_MIPS

    // NOTE regarding the keyword INLINE:
    //
    // Inline is not an ANSI-C keyword, hence every compiler can implement inlining
    // the way it wants to. When using the dcc compiler this might possibly lead to
    // redeclaration warnings when linking. For example:
    //
    //      dld: warning: Redeclaration of tmmlGetMemHandle
    //      dld:    Defined in root.o
    //      dld:    and        tmmlApi.o(../../lib/pSOS-MIPS/libtmml.a)
    //
    // For the dcc compiler inlining is not on by default. When building a retail
    // version ( _TMTGTREL=ret), inlining is turned on explicitly in the dvp1 pSOS
    // makefiles by specifying -XO, which enables all standard optimizations plus
    // some others, including inlining (see the Language User's Manual, D-CC and
    // D-C++ Compiler Suites p46). When building a debug version ( _TMTGTREL=dbg),
    // the optimizations are not turned on (and even if they were they would have
    // been overruled by -g anyway).
    //
    // When a .h file with inline function declarations gets included in multiple
    // source files, redeclaration warnings are issued.
    //
    // When building a retail version those functions are inlined, but in addition
    // the function is also declared within the .o file, resulting in redeclaration
    // warnings as the same function is also defined by including that same header
    // file in other source files. Defining the functions as static inline rather
    // than inline solves the problem, as now the additional function declaration
    // is omitted (as now the compiler realizes that there is no point in keeping
    // that declaration as it can only be called from within this specific file,
    // but it isn't, because all calls are already inline).
    //
    // When building a debug version no inlining is done, but the functions are
    // still defined within the .o file, again resulting in redeclaration warnings.
    // Again, defining the functions to be static inline rather than inline solves
    // the problem.

    // Now if we would change the definition of the inline keyword for pSOS from
    // __inline__ to static __inline__, all inline function definitions throughout
    // the code would not issue redeclaration warnings anymore, but all static
    // inline definitions would.
    // If we don't change the definition of the inline keyword, all inline func-
    // tion definitions would return redeclaration warnings.
    //
    // As this is a pSOS linker bug, it was decided not to change the code but
    // rather to ignore the issued warnings.
    //

#define inline  __inline__

#elif      TMFL_OS_IS_PSOS && TMFL_CPU_IS_TM
    // TriMedia keyword is already inline

#elif      TMFL_OS_IS_ECOS && TMFL_CPU_IS_MIPS

#define inline  __inline__

#elif      (TMFL_OS_IS_HPUNIX || TMFL_OS_IS_NULLOS)
    //
    // TMFL_OS_IS_HPUNIX is the HP Unix workstation target OS environment for the
    // DVP SDE2 using the GNU gcc toolset.  It is the same as TMFL_OS_IS_NULLOS
    // (which is inaccurately named because it is the HP Unix CPU/OS target
    // environment).
    //
    /* LM; 02/07/2202; to be able to use Insure, I modify the definition of inline */
    /* #define inline  __inline__ */
#define inline  

#elif TMFL_OS_IS_ECOS && TMFL_CPU_IS_MIPS

#define inline

#else // TMFL_OS_IS_???

#error confusing value in TMFL_OS!

#endif // TMFL_OS_IS_XXX

    /*Assume that |restrict| is supported by tmcc and C99 compilers only. More
    discrimination in this area may be added here as necessary.*/
#if !(defined __TCS__ ||                                                       \
    (defined __STDC_VERSION__ && __STDC_VERSION__ > 199409L))
#define restrict /**/
#endif

#ifdef __cplusplus
}
#endif

#endif //ndef TMNXTYPES_H
