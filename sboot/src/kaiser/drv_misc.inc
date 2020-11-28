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

#[*] Enable reg_vps_sram_act for 2D peaking line-buffer sram active of PEAKING_BK19
# in order to resolve screen flicker when boot logo show.
# Add by Grand.Zhu 2013-7-24
@-------------------------------------------------
@Macro: drv_misc_vps_sram_active
@-------------------------------------------------
.macro drv_misc_vps_sram_active
    WREG_B    0x1F205E00, 0x00      @ Control register of bank selection for scaler
    WREG_B    0x1F205E00, 0x19      @ Select bank 0x19
	RREG      r0, 0x1F205E40        @ Read BK19_20[15:0]
    orr       r0, r0, #0x0080       @ Set BK19_20[7] = 1
	LDR       r1, =0x1F205E40
	STR       r0, [r1]
.endm


