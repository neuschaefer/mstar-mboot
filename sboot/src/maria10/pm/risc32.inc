################################################################################
##
## Copyright (c) 2006-2009 MStar Semiconductor, Inc.
## All rights reserved.
##
## Unless otherwise stipulated in writing, any and all information contained
## herein regardless in any format shall remain the sole proprietary of
## MStar Semiconductor Inc. and be kept in strict confidence
## ("MStar Confidential Information") by the recipient.
## Any unauthorized act including without limitation unauthorized disclosure,
## copying, use, reproduction, sale, distribution, modification, disassembling,
## reverse engineering and compiling of the contents of MStar Confidential
## Information is unlawful and strictly prohibited. MStar hereby reserves the
## rights to any and all damages, losses, costs and expenses resulting therefrom.
##
#################################################################################

## Register Aliases for ABI

#define sp r1
#define lr r9
#define fp r10

#define p0 r3
#define p1 r4
#define p2 r5
#define p3 r6
#define p4 r7
#define p5 r8

#define __TEXT_ALIGN      .align 4

#define ENTRY(name)                 \
        __TEXT_ALIGN;               \
        .globl _##name;             \
        .type _##name,@function;    \
_##name:

# Size of GPR regs - 4 bytes for risc32
#define RISC32_GPRSIZE    4

# Size of all other registers
#define RISC32_REGSIZE    4

# Utility macro: Load a 32-bit constant into a register
.macro  load32i reg const
    l.movhi \reg,hi(\const)
    l.ori   \reg,\reg,lo(\const)
.endm

#define RISC32REGS_GPRS   0
#ifdef __AEONR2__
#define RISC32REG_MACHI2  (RISC32REGS_GPRS + RISC32_GPRSIZE * 32)
#define RISC32REG_MACHI   (RISC32REG_MACHI2 + RISC32_GPRSIZE)
#else
#define RISC32REG_MACHI   (RISC32REGS_GPRS + RISC32_GPRSIZE * 32)
#endif
#define RISC32REG_MACLO   (RISC32REG_MACHI + RISC32_REGSIZE)
#define RISC32REG_VECTOR  (RISC32REG_MACLO + RISC32_REGSIZE)
#define RISC32REG_SR      (RISC32REG_VECTOR+ RISC32_REGSIZE)
#define RISC32REG_PC      (RISC32REG_SR    + RISC32_REGSIZE)
#define RISC32REG_EEAR    (RISC32REG_PC    + RISC32_REGSIZE)

#define LEAF_FUNC_SIZE 128
#define SIZEOF_RISC32REGS (RISC32REG_EEAR  + RISC32_REGSIZE + LEAF_FUNC_SIZE)
