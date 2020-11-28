################################################################################
##
## Copyright (c) 2006-2009 MStar Semiconductor, Inc.
## All rights reserved.
##
## Unless otherwise stipulated in writing, any and all information contained
## herein regardless in any format shall remain the sole proprietary of
## MStar Semiconductor Inc. and be kept in strict confidence
## (!¡±MStar Confidential Information!¡L) by the recipient.
## Any unauthorized act including without limitation unauthorized disclosure,
## copying, use, reproduction, sale, distribution, modification, disassembling,
## reverse engineering and compiling of the contents of MStar Confidential
## Information is unlawful and strictly prohibited. MStar hereby reserves the
## rights to any and all damages, losses, costs and expenses resulting therefrom.
##
################################################################################
#if defined(__mips__)

#if defined(CONFIG_MSTAR_TITANIA2)
    #define RIUBASE_NONPM   0xBF800000
#else
    #define RIUBASE_PM              0xBF000000
    #define RIUBASE_NONPM           0xBF200000
    #define RIUBASE_NONPM_EXT12     0xBF240000  #//Support Bank 0x12XX
#endif

##
## void MDrv_WriteRegMaskTbl(unsigned char *pTable)
## {
##     U8  u8Length;
##     U16 u16Index; // register index
##
##     u32MapBase = _MapBase_nonPM_S7;
##     while (1)
##     {
##         u16Index = (pPadConfig[0] << 8) + (pPadConfig[1]);
##
##         if (u16Index == 0xFFFF) // check end of table
##             break;
##
##         pPadConfig += 2;
##
##         if(u16Index == 0x0000) // switch base address
##         {
##             if(pPadConfig[0]==0x00)
##             {
##                 u32MapBase = _MapBase_PM_S7;
##             }
##             else
##             {
##                 u32MapBase = _MapBase_nonPM_S7;
##             }
##             pPadConfig += 2;
##             continue;
##         }
##
##         u8Length = HIGHBYTE(u16Index) >> 6;
##         u16Index &= 0x3FFF;
##
##         while (1)
##         {
##             MDrv_PAD_WriteByteMask((U32)u16Index, pPadConfig[0], pPadConfig[1]);
##             pPadConfig += 2;
##
##             if (u8Length == 0)
##                 break;
##
##             u8Length--;
##             u16Index++;
##         }
##     }
## }
##
    .section    .text.MDrv_WriteRegMaskTbl,"ax",@progbits
    .align      2
    .globl      MDrv_WriteRegMaskTbl
    .ent        MDrv_WriteRegMaskTbl
    .type       MDrv_WriteRegMaskTbl, @function
MDrv_WriteRegMaskTbl:
    .set        nomips16
    .frame      $sp,0,$31                   # vars= 0, regs= 0/0, args= 0, gp= 0
    .mask       0x00000000,0
    .fmask      0x00000000,0
    .set        noreorder

#define GPR_TABLE           $4
#define GPR_END_MARK        $15
#define GPR_RIUBASE         $9
#define GPR_RIUBASE_PM      $13
#define GPR_RIUBASE_NONPM   $14
#define GPR_ENTRY_LEN       $11
#define GPR_REGADDR         $7
#define GPR_ENDADDR         $12

#if defined(RIUBASE_PM)

    li          GPR_RIUBASE_NONPM,RIUBASE_NONPM

#endif

    li          GPR_END_MARK,0xFFFF
    li          GPR_RIUBASE,RIUBASE_NONPM

$L_WHILE_LOOP:
    lbu         $2,0(GPR_TABLE)
    lbu         $3,1(GPR_TABLE)
    sll         $2,$2,8
    addu        $2,$2,$3

    beq         $2,GPR_END_MARK,$L_FINISH
    addiu       GPR_TABLE,GPR_TABLE,2

#if defined(RIUBASE_PM)

    bne         $2,$0,$L_NORMAL
    lbu         $3,0(GPR_TABLE)

    li          GPR_RIUBASE,RIUBASE_PM
    addiu       GPR_TABLE,GPR_TABLE,2

#if defined(CONFIG_MSTAR_AMETHYST) || \
    defined(CONFIG_MSTAR_EMERALD)  || \
    defined(CONFIG_MSTAR_NUGGET)

#//Add code to support Bank 0x12XX

    beqz        $3, $L_WHILE_LOOP
    nop

    beq         $3, 0x10, $L_WHILE_LOOP
    li          GPR_RIUBASE, RIUBASE_NONPM

#// beq         $3, 0x12, $L_WHILE_LOOP
#// li          GPR_RIUBASE, RIUBASE_NONPM_EXT12

    j           $L_WHILE_LOOP
    li          GPR_RIUBASE, RIUBASE_NONPM_EXT12

#else

    j           $L_WHILE_LOOP
    movn        GPR_RIUBASE,GPR_RIUBASE_NONPM,$3

#endif
#endif

$L_NORMAL:
    andi        GPR_REGADDR,$2,0x3fff
    srl         GPR_ENTRY_LEN,$2,14
    addu        GPR_ENDADDR,GPR_REGADDR,GPR_ENTRY_LEN

$L_WRITE_LOOP:

    # $10 = (GPR_REGADDR << 1)  - (GPR_REGADDR & 1)  + GPR_RIUBASE

    sll         $10,GPR_REGADDR,1
    andi        $2,GPR_REGADDR,0x1
    addu        $10,$10,GPR_RIUBASE
    subu        $10,$10,$2

    lbu         $3,1(GPR_TABLE)        # mask
    lbu         $6,0(GPR_TABLE)        # value
    lbu         $2,0($10)

    nor         $5,$0,$3        # $5 = ~mask
    and         $2,$2,$5        # $2 = read & ~mask

    and         $3,$3,$6        # $3 = value & mask
    or          $2,$2,$3        # $2 = (read & ~mask) | (value & mask)

    addiu       GPR_TABLE,GPR_TABLE,2

    beq         GPR_REGADDR,GPR_ENDADDR,$L_WHILE_LOOP
    sb          $2,0($10)

    j           $L_WRITE_LOOP
    addiu       GPR_REGADDR,GPR_REGADDR,1

$L_FINISH:
    j           $31
    nop

    .set    reorder
    .end    MDrv_WriteRegMaskTbl

##
## void MDrv_WriteRegTbl32Off(unsigned char *pTable, int iRegOffset)
## {
##     U8 u8Length;
##     U32 u32Index; // register index
##
##     while (1)
##     {
##         u32Index = (((U32)pRegTable[0] << 16) + ((U32)pRegTable[1] << 8) + pRegTable[2]);
##         if (u32Index == 0xFFFFFF) // check end of table
##             break;
##
##         u8Length = pRegTable[0] >> 5;
##         u32Index &= 0x1FFFFF;
##         u32Index += iRegOffset;
##
##         pRegTable += 3;
##         do
##         {
##             RIU8[ (u32Index << 1) - (u32Index & 1) ] = *pRegTable++;
##             u32Index++;
##         } while (u8Length-- > 0);
##     }
## }
##

    .section    .text.MDrv_WriteRegTbl32Off,"ax",@progbits
    .align      2
    .globl      MDrv_WriteRegTbl32Off
    .ent        MDrv_WriteRegTbl32Off
    .type       MDrv_WriteRegTbl32Off, @function
MDrv_WriteRegTbl32Off:
    .set        nomips16
    .frame      $sp,0,$31                   # vars= 0, regs= 0/0, args= 0, gp= 0
    .mask       0x00000000,0
    .fmask      0x00000000,0
    .set        noreorder

    li          $2,0xFF0000
    ori         $12,$2,0xFFFF               # $12 == 0xFFFFFF
    li          $2,0x1F0000
    move        $13,$4
    ori         $11,$2,0xFFFF               # $11 == 0x1FFFFF

#ifdef RIUBASE_PM
    li          $10,RIUBASE_PM
#else
    li          $10,RIUBASE_NONPM
#endif

1: /* LOOP */
    lbu         $6,0($13)
    lbu         $2,2($13)
    lbu         $3,1($13)
    sll         $4,$6,16
    addu        $2,$2,$4
    sll         $3,$3,8
    addu        $3,$2,$3
    beq         $3,$12,3f /* FINISH */
    srl         $2,$6,5

    addiu       $8,$13,3
    addiu       $7,$2,1
    and         $13,$3,$11
    move        $6,$8
    addu        $13,$13,$5
    addu        $9,$7,$13
2: /* WRITE_LOOP */
    sll         $2,$13,1
    andi        $3,$13,0x1
    lbu         $4,0($6)
    subu        $2,$2,$3                        # $2 = ($13 << 1) + ($13 & 1)
    addu        $2,$2,$10                       # $2 += RIUBASE
    addiu       $13,$13,1
    sb          $4,0($2)
    bne         $13,$9,2b /* WRITE_LOOP */
    addiu       $6,$6,1

    j           1b  /* LOOP */
    addu        $13,$8,$7

3: /* FINISH */
    j   $31
    nop

    .end    MDrv_WriteRegTbl32Off

    .section    .text.MDrv_WriteRegTbl32,"ax",@progbits
    .align      2
    .globl      MDrv_WriteRegTbl32
    .ent        MDrv_WriteRegTbl32
    .type       MDrv_WriteRegTbl32, @function
MDrv_WriteRegTbl32:
    .set        nomips16
    .frame      $sp,0,$31                   # vars= 0, regs= 0/0, args= 0, gp= 0
    .mask       0x00000000,0
    .fmask      0x00000000,0
    .set        noreorder

    b           MDrv_WriteRegTbl32Off
    move        $5, $0

    .end    MDrv_WriteRegTbl32

#endif

#if defined(__arm__)

#define RIUBASE_PM      0x1F000000
#define RIUBASE_NONPM   0x1F200000

    .section .text.drvRIU_WriteRegTb
    .global MDrv_WriteRegTbl32
    .global MDrv_WriteRegMaskTbl

##
## void MDrv_WriteRegTbl32Off(unsigned char *pTable, int iRegOffset)
## {
##     U8 u8Length;
##     U32 u32Index; // register index
##
##     while (1)
##     {
##         u32Index = (((U32)pRegTable[0] << 16) + ((U32)pRegTable[1] << 8) + pRegTable[2]);
##         if (u32Index == 0xFFFFFF) // check end of table
##             break;
##
##         u8Length = pRegTable[0] >> 5;
##         u32Index &= 0x1FFFFF;
##         u32Index += iRegOffset;
##
##         pRegTable += 3;
##         do
##         {
##             RIU8[ (u32Index << 1) - (u32Index & 1) ] = *pRegTable++;
##             u32Index++;
##         } while (u8Length-- > 0);
##     }
## }
##
##
##    _RV32_2( 0x110d04, 0x0080 ),
##    _RV32_2( 0x110d06, 0x0000 ),
##   31 0D 04 80 00
##   31 0D 06 00 00
##
##   _RV32_1(   0x101203, 0x03   ),
##   _RV32_1(   0x101204, 0x0a   ),
##   10 12 03 03
##   10 12 04 0a
##   FF FF FF --> end of table

MDrv_WriteRegTbl32:

#define GPR_TABLE_TBL32     r0
#define GPR_INDEX           r1
#define GPR_REGADDR_TBL32   r4
#define GPR_ENDADDR_TBL32   r12
#define GPR_ENDOFTBL        r11
#define GPR_ENTRY_LEN_TBL32 r10
#define GPR_RIUBASE_TBL32   r9

    mov         GPR_ENDADDR_TBL32, #0
    mov         GPR_REGADDR_TBL32, #0
    mov         GPR_ENTRY_LEN_TBL32, #0
    ldr         GPR_ENDOFTBL, =0xFFFFFF
    ldr         GPR_RIUBASE_TBL32,=RIUBASE_PM

START_LOOP:
    ldrb        GPR_INDEX, [GPR_TABLE_TBL32,#0]
    lsl         GPR_INDEX, GPR_INDEX, #16
    ldrb        r2, [GPR_TABLE_TBL32,#1]
    lsl         r2, r2, #8
    ldrb        r3, [GPR_TABLE_TBL32,#2]
    add         GPR_INDEX, GPR_INDEX, r2
    add         GPR_INDEX, GPR_INDEX, r3
    cmp         GPR_INDEX, GPR_ENDOFTBL
    beq         L_END_TABLE

    bic         GPR_REGADDR_TBL32, GPR_INDEX, #0xE00000
    lsr         GPR_ENTRY_LEN_TBL32, GPR_INDEX, #21
    add         GPR_ENDADDR_TBL32, GPR_REGADDR_TBL32, GPR_ENTRY_LEN_TBL32

    add         GPR_TABLE_TBL32, GPR_TABLE_TBL32, #3

WRITE_LOOP:
    lsl         r5, GPR_REGADDR_TBL32,#1
    and         r6, GPR_REGADDR_TBL32,#1
    add         r5, r5, GPR_RIUBASE_TBL32
    sub         r5, r5, r6                  @riu addr

    ldrb        r7, [GPR_TABLE_TBL32, #0]
    add         GPR_TABLE_TBL32, GPR_TABLE_TBL32, #1
    strb        r7, [r5, #0]

    cmp         GPR_ENDADDR_TBL32, GPR_REGADDR_TBL32
    beq         START_LOOP
    add         GPR_REGADDR_TBL32, GPR_REGADDR_TBL32, #1
    b           WRITE_LOOP

L_END_TABLE:
    bx          lr

##
## void MDrv_WriteRegMaskTbl(unsigned char *pTable)
## {
##     U8  u8Length;
##     U16 u16Index; // register index
##
##     u32MapBase = _MapBase_nonPM_S7;
##     while (1)
##     {
##         u16Index = (pPadConfig[0] << 8) + (pPadConfig[1]);
##
##         if (u16Index == 0xFFFF) // check end of table
##             break;
##
##         pPadConfig += 2;
##
##         if(u16Index == 0x0000) // switch base address
##         {
##             if(pPadConfig[0]==0x00)
##             {
##                 u32MapBase = _MapBase_PM_S7;
##             }
##             else
##             {
##                 u32MapBase = _MapBase_nonPM_S7;
##             }
##             pPadConfig += 2;
##             continue;
##         }
##
##         u8Length = HIGHBYTE(u16Index) >> 6;
##         u16Index &= 0x3FFF;
##
##         while (1)
##         {
##             MDrv_PAD_WriteByteMask((U32)u16Index, pPadConfig[0], pPadConfig[1]);
##             pPadConfig += 2;
##
##             if (u8Length == 0)
##                 break;
##
##             u8Length--;
##             u16Index++;
##         }
##     }
## }
##
## example:
##  _RVM1(0x1234,BIT1,BIT1), --> 12 34 02 02
##  _RVM2(0xabcd,BIT2,BIT2), --> 6B CD 04 04 00 00
##  _RVM3(0x1234,BIT1,BIT1), --> 92 34 02 02 00 00 00 00
##  _RVM4(0xabce,BIT2,BIT2), --> EB CE 04 04 00 00 00 00 00 00
##

MDrv_WriteRegMaskTbl:

#define GPR_TABLE           r0
#define GPR_END_MARK        r8
#define GPR_RIUBASE         r9
#define GPR_ENTRY_LEN       r10
#define GPR_REGADDR         r11
#define GPR_ENDADDR         r12

    ldr GPR_END_MARK,=0xFFFF
    ldr GPR_RIUBASE,=RIUBASE_NONPM
    mov GPR_ENTRY_LEN, #0
    mov GPR_REGADDR, #0
    mov GPR_ENDADDR, #0

L_WHILE_LOOP:
    ldrb        r2, [GPR_TABLE,#0]
    ldrb        r3, [GPR_TABLE,#1]
    lsl         r2, r2, #8
    add         r2, r2, r3
    cmp         r2, GPR_END_MARK
    beq         L_FINISH
    add         GPR_TABLE, GPR_TABLE, #2

    cmp         r2, #0
    bne         L_NORMAL
    ldrb        r2, [GPR_TABLE,#0]
    cmp         r2, #0
    bne         SET_RIUBASE_NONPM
    mov         GPR_RIUBASE, #RIUBASE_PM
    add         GPR_TABLE, GPR_TABLE, #2
    b           L_WHILE_LOOP
SET_RIUBASE_NONPM:
    ldr         GPR_RIUBASE,=RIUBASE_NONPM
    add         GPR_TABLE, GPR_TABLE, #2
    b           L_WHILE_LOOP

L_NORMAL:
    @ldrb        r2, [GPR_TABLE,#0]
    bic         GPR_REGADDR, r2, #0xC000
    lsr         GPR_ENTRY_LEN, r2, #14
    add         GPR_ENDADDR, GPR_REGADDR, GPR_ENTRY_LEN

L_WRITE_LOOP:
    lsl         r4, GPR_REGADDR, #1
    and         r5, GPR_REGADDR, #0x1
    add         r4, r4, GPR_RIUBASE
    sub         r4, r4, r5          @riu_addr

    ldrb        r6, [GPR_TABLE,#1]  @mask
    ldrb        r7, [GPR_TABLE,#0]  @value
    ldrb        r1, [r4,#0]         @get reg_val

    bic         r1, r1, r6          @read & ~mask
    and         r6, r6, r7          @vale & mask
    orr         r1, r1, r6          @(read & ~mask) | (value & mask)
    strb        r1, [r4, #0]

    add         GPR_TABLE, GPR_TABLE, #2
    cmp         GPR_REGADDR, GPR_ENDADDR
    beq         L_WHILE_LOOP
    add         GPR_REGADDR, GPR_REGADDR, #1
    b           L_WRITE_LOOP

L_FINISH:

    bx          lr

#endif

#if defined(__arm64__)

//=================================================================================================
#define RIUBASE_PM              0x1F000000
#define RIUBASE_NONPM           0x1F200000

    .section    .text.drvRIU_WriteRegTb

//=================================================================================================
    .global     MDrv_WriteRegTbl32
MDrv_WriteRegTbl32:

#define GPR_TABLE_TBL32         x0
#define GPR_INDEX               w1
#define GPR_REGADDR_TBL32       w4
#define GPR_ENDADDR_TBL32       w12
#define GPR_ENDOFTBL            w11
#define GPR_ENTRY_LEN_TBL32     w10
#define GPR_RIUBASE_TBL32       w9

    mov         GPR_ENDADDR_TBL32, #0
    mov         GPR_REGADDR_TBL32, #0
    mov         GPR_ENTRY_LEN_TBL32, #0
    ldr         GPR_ENDOFTBL, =0xFFFFFF
    ldr         GPR_RIUBASE_TBL32, =RIUBASE_PM

START_LOOP:
    ldrb        GPR_INDEX, [GPR_TABLE_TBL32 ,#0]
    lsl         GPR_INDEX, GPR_INDEX, #16
    ldrb        w2, [GPR_TABLE_TBL32, #1]
    lsl         w2, w2, #8
    ldrb        w3, [GPR_TABLE_TBL32, #2]
    add         GPR_INDEX, GPR_INDEX, w2
    add         GPR_INDEX, GPR_INDEX, w3
    cmp         GPR_INDEX, GPR_ENDOFTBL
    b.eq        L_END_TABLE

    bic         GPR_REGADDR_TBL32, GPR_INDEX, #0xE00000
    lsr         GPR_ENTRY_LEN_TBL32, GPR_INDEX, #21
    add         GPR_ENDADDR_TBL32, GPR_REGADDR_TBL32, GPR_ENTRY_LEN_TBL32
    add         GPR_TABLE_TBL32, GPR_TABLE_TBL32, #3

WRITE_LOOP:
    lsl         w5, GPR_REGADDR_TBL32,#1
    and         w6, GPR_REGADDR_TBL32,#1
    add         w5, w5, GPR_RIUBASE_TBL32
    sub         w5, w5, w6
    ldrb        w7, [GPR_TABLE_TBL32, #0]
    add         GPR_TABLE_TBL32, GPR_TABLE_TBL32, #1
    strb        w7, [x5, #0]

    cmp         GPR_ENDADDR_TBL32, GPR_REGADDR_TBL32
    b.eq        START_LOOP

    add         GPR_REGADDR_TBL32, GPR_REGADDR_TBL32, #1
    b           WRITE_LOOP

L_END_TABLE:
    ret

//=================================================================================================
    .global     MDrv_WriteRegMaskTbl
MDrv_WriteRegMaskTbl:

#define GPR_TABLE               x0
#define GPR_END_MARK            w8
#define GPR_RIUBASE             w9
#define GPR_ENTRY_LEN           w10
#define GPR_REGADDR             w11
#define GPR_ENDADDR             w12

    ldr         GPR_END_MARK, =0xFFFF
    ldr         GPR_RIUBASE, =RIUBASE_NONPM
    mov         GPR_ENTRY_LEN, #0
    mov         GPR_REGADDR, #0
    mov         GPR_ENDADDR, #0

L_WHILE_LOOP:
    ldrb        w2, [GPR_TABLE, #0]
    ldrb        w3, [GPR_TABLE, #1]
    lsl         w2, w2, #8
    add         w2, w2, w3

    cmp         w2, GPR_END_MARK
    b.eq        L_FINISH

    add         GPR_TABLE, GPR_TABLE, #2
    cmp         w2, #0
    b.ne        L_NORMAL

    ldrb        w2, [GPR_TABLE, #0]
    cmp         w2, #0
    b.ne        SET_RIUBASE_NONPM

    mov         GPR_RIUBASE, #RIUBASE_PM
    add         GPR_TABLE, GPR_TABLE, #2
    b           L_WHILE_LOOP

SET_RIUBASE_NONPM:
    ldr         GPR_RIUBASE,=RIUBASE_NONPM
    add         GPR_TABLE, GPR_TABLE, #2
    b           L_WHILE_LOOP

L_NORMAL:
//  ldrb        w2, [GPR_TABLE,#0]
    bic         GPR_REGADDR, w2, #0xC000
    lsr         GPR_ENTRY_LEN, w2, #14
    add         GPR_ENDADDR, GPR_REGADDR, GPR_ENTRY_LEN

L_WRITE_LOOP:
    lsl         w4, GPR_REGADDR, #1
    and         w5, GPR_REGADDR, #0x1
    add         w4, w4, GPR_RIUBASE
    sub         w4, w4, w5

    ldrb        w6, [GPR_TABLE,#1]
    ldrb        w7, [GPR_TABLE,#0]
    ldrb        w1, [x4, #0]

    bic         w1, w1, w6
    and         w6, w6, w7
    orr         w1, w1, w6
    strb        w1, [x4, #0]

    add         GPR_TABLE, GPR_TABLE, #2
    cmp         GPR_REGADDR, GPR_ENDADDR
    b.eq        L_WHILE_LOOP
    add         GPR_REGADDR, GPR_REGADDR, #1
    b           L_WRITE_LOOP

L_FINISH:
    ret

#endif
