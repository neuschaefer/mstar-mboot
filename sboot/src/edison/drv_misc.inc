#[*] Configure PAD top for MUX and GPIO (e.g. DDR power) MDrv_WriteRegMaskTbl(padInitTbl)
@-------------------------------------------------
@Macro: drv_misc_padInit
@-------------------------------------------------
.macro drv_misc_padInit
.endm


#[*] Enable MSTV_TOOL to access MIU
@-------------------------------------------------
@Macro: drv_misc_tvtool_access_miu
@-------------------------------------------------
.macro drv_misc_tvtool_access_miu
    WREG 0x1f005788, 0x0004
    WREG 0x1f00578C, 0x3c11
    WREG 0x1f005790, 0x0010
    WREG 0x1f005794, 0x403c
    WREG 0x1f005798, 0x0101
.endm

#[*] enable_riu32_bitmask
@-------------------------------------------------
@Macro: drv_misc_riu32_bitmask
@-------------------------------------------------
.macro drv_misc_riu32_bitmask
    LDR r12, =0x1f20025c
    LDR r11, =0x1f20025c
    orr r11, r11, #0x00000001
    STR r11, [r12]

    LDR r12, =0x1f203104
    LDR r11, =0x1f203104
    orr r11, r11, #0x00008000
    STR r11, [r12]

    LDR r12, =0x1f00025C
    LDR r11, =0x1f00025C
    orr r11, r11, #0x00000001
    STR r11, [r12]
.endm


