#include "MIUSEL_A3_2MIU.h"
#include "Board.h"

@-------------------------------------------------------------------------------------------------
@ MIU registers
@-------------------------------------------------------------------------------------------------
MIU0_BASE                   = (MS_BUS_RIU_ADDR+0x00202400)
MIU1_BASE                   = (MS_BUS_RIU_ADDR+0x00200C00)

MIU0_ATOP_BASE              = (MS_BUS_RIU_ADDR+0x00221A00)
MIU1_ATOP_BASE              = (MS_BUS_RIU_ADDR+0x00221B00)   @ alan : need to update

CLK_GEN0_BASE               = (MS_BUS_RIU_ADDR+0x00201600)
CLK_GEN1_BASE               = (MS_BUS_RIU_ADDR+0x00206600)

ADC_ATOP_BASE               = (MS_BUS_RIU_ADDR+0x00204A00)
ADC_DTOP_BASE               = (MS_BUS_RIU_ADDR+0x00204C00)
DVI_DTOP_BASE               = (MS_BUS_RIU_ADDR+0x00204424)
DVI_ATOP_BASE               = (MS_BUS_RIU_ADDR+0x00221200)

CHIP_TOP_BASE               = (MS_BUS_RIU_ADDR+0x00203C00)
ANA_MISC_BASE               = (MS_BUS_RIU_ADDR+0x00221800)

USB0_BASE                   = (MS_BUS_RIU_ADDR+0x00200E00)
USB1_BASE                   = (MS_BUS_RIU_ADDR+0x00200F00)

UTMI1_BASE                  = (MS_BUS_RIU_ADDR+0x00207400)
UTMI0_BASE                  = (MS_BUS_RIU_ADDR+0x00207500)

SC1_BASE                    = (MS_BUS_RIU_ADDR+0x00205E00)
SC3_BASE                    = (MS_BUS_RIU_ADDR+0x00206200)
SC4_BASE                    = (MS_BUS_RIU_ADDR+0x00206400)

AFEC_BASE                   = (MS_BUS_RIU_ADDR+0x00206A00)

@[*] BOOT_InitDRAM(FPGA) or BOOTROM_MIU_INIT(ASIC)
@-------------------------------------------------
@Macro: drv_miu_init
@-------------------------------------------------
.macro drv_miu_init

    WREG    0x1F201674, 0x0808
    @ MIU0 Software reset
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0000   @hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c00   @
    WREG    (MS_BUS_RIU_ADDR + (0x101202 <<1 )) , 0x0000   @disable all ddr bus out

    @ MIU0 Request mask
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x7FFE   @ mask group0
    WREG    (MS_BUS_RIU_ADDR + (0x101266 <<1 )) , 0xFFFF   @ mask group1
    WREG    (MS_BUS_RIU_ADDR + (0x101286 <<1 )) , 0xFFFF   @ mask group2
    WREG    (MS_BUS_RIU_ADDR + (0x1012A6 <<1 )) , 0xFFFF   @ mask group3

.if ( ENABLE_MIU1 == 1 )
    @ MIU1 Software reset
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0000   @hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c00   @
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0x0000   @

    @ MIU1 Request mask
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @ mask group0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0xFFFF   @ mask group1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0xFFFF   @ mask group2
    WREG    (MS_BUS_RIU_ADDR + (0x1006A6 <<1 )) , 0xFFFF   @ mask group3
.endif

    #if(ENABLE_MEM1600MHz)
    WREG    (MS_BUS_RIU_ADDR + (0x110d36 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    WREG    (MS_BUS_RIU_ADDR + (0x110d34 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110d30 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110d32 <<1 )) , 0x0019
    #endif

    #if(ENABLE_MEM1300MHz)
    WREG    (MS_BUS_RIU_ADDR + (0x110d36 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    WREG    (MS_BUS_RIU_ADDR + (0x110d34 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110d30 <<1 )) , 0x6b0e   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110d32 <<1 )) , 0x001f
    #endif
    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x1000

.if ( ENABLE_MIU1 == 1 )
    #if(ENABLE_MEM1600MHz)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    WREG    (MS_BUS_RIU_ADDR + (0x110db4 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110db0 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110db2 <<1 )) , 0x0019
    #endif

    #if(ENABLE_MEM1300MHz)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    WREG    (MS_BUS_RIU_ADDR + (0x110db4 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110db0 <<1 )) , 0x6b0e   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110db2 <<1 )) , 0x001f
    #endif
    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x1000
.endif

    DELAYUS 5000    @ delay 5ms

    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x0000
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x0000
.endif

    ldr r0, =MIU0_DDR_Init
    bl MDrv_WriteRegTbl32

    WREG    (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x8400

    @MIU0 pack enable
    RREG    r0,(MS_BUS_RIU_ADDR + (0x101228 <<1 ))
    orr     r0, r0, #0x4000
    ldr     r1, =0x1F202450
    str     r0, [r1]

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c08

    #if(ENABLE_MEM1600MHz)
    #if(ENABLE_MSTAR_TITANIA_BD_MST029B_10AFVA_A3 || ENABLE_MSTAR_TITANIA_BD_CUS28_6A801 || ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3_ATSC || ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3 ||ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_BOX_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e01   @reg_pkg_sel      1   : [0]
    #else
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1a01   @reg_pkg_sel      1   : [0]
    #endif
    #endif

    #if(ENABLE_MEM1300MHz)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1a01   @reg_pkg_sel      1   : [0]
    #endif
    WREG    (MS_BUS_RIU_ADDR + (0x110d02 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]

.if ( ENABLE_MIU1 == 1 )
    ldr r0, =MIU1_DDR_Init
    bl MDrv_WriteRegTbl32

    WREG    (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x8400

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c08

    #if(ENABLE_MEM1600MHz)
    #if(ENABLE_MSTAR_TITANIA_BD_MST029B_10AFVA_A3 || ENABLE_MSTAR_TITANIA_BD_CUS28_6A801 || ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3 ||ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3_ATSC ||ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3 ||ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3 || ENABLE_MSTAR_TITANIA_BD_MST029B_BOX_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e01   @reg_pkg_sel      1   : [0]
    #else
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1a01   @reg_pkg_sel      1   : [0]
    #endif
    #endif

    #if(ENABLE_MEM1300MHz)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1a01   @reg_pkg_sel      1   : [0]
    #endif
    WREG    (MS_BUS_RIU_ADDR + (0x110d82 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
.endif

    DELAYUS  100  @ delay 100us

#if(ENABLE_MSTAR_TITANIA_BD_MST129F_D01A1_S)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x403f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST145A_D01A1_S)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST145B_D01A_S)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST142A_D01A_S_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MST028B_10AFX_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MST029B_10AFVA_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3_ATSC)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

#if(ENABLE_MSTAR_TITANIA_BD_CUS28_6A801)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
#endif

.if ( ENABLE_MIU1 == 1 )
#if(ENABLE_MSTAR_TITANIA_BD_MST129F_D01A1_S)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x403f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST145A_D01A1_S)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST145B_D01A_S)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST142A_D01A_S_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST028B_10AFX_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST029B_10AFVA_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MS801_MAA2XG_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS37_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS18_A3_ATSC)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_MST029B_CUS36_A3)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
#if(ENABLE_MSTAR_TITANIA_BD_CUS28_6A801)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
#endif
.endif

    @ MIU0 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
    DBGREG  0x0025

CheckMiu0Init:
    RREG    r0,(MS_BUS_RIU_ADDR + (0x101200 <<1 ))
    lsr     r0, r0, #15
    cmp     r0, #1
    bne     CheckMiu0Init

.if ( ENABLE_MIU1 == 1 )
    @ MIU1 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG    r0,(MS_BUS_RIU_ADDR + (0x100600 <<1 ))
    lsr     r0, r0, #15
    cmp     r0, #1
    bne     CheckMiu1Init
.endif

    DELAYUS 200   @ delay 200us

    drv_miu_init_priority

@ disable auto phase for chip bring up
NONTEST_SELF_REFRESH_3:
.if(CONFIG_MSTAR_STR_ENABLE == 1)
    is_slept
    beq END_OF_BIST
.endif
#if 1
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    .if(EMMC_BOOT == 0)
    drv_miu0_autophase
    .endif
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    .if(EMMC_BOOT == 0)
    drv_miu1_autophase
    .endif
    nop
.endif
#endif


    @ BIST test
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    drv_miu0_bisttest
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    drv_miu1_bisttest
.endif
    WREG    (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )) , 0x0000   @ stop bist test
END_OF_BIST:

    @ open all MIU0 request mask (All IP can access MIU resource)
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x0000   @Mask MIU0_group_0
    WREG    (MS_BUS_RIU_ADDR + (0x101266 <<1 )) , 0x0000   @Mask MIU0_group_1
    WREG    (MS_BUS_RIU_ADDR + (0x101286 <<1 )) , 0x0000   @Mask MIU0_group_2
    WREG    (MS_BUS_RIU_ADDR + (0x1012a6 <<1 )) , 0x0000   @Mask MIU0_group_3

.if ( ENABLE_MIU1 == 1 )
    @ open all MIU1 request mask (All IP can access MIU resource)
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x0000   @Mask MIU0_group_0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0x0000   @Mask MIU0_group_1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0x0000   @Mask MIU0_group_2
    WREG    (MS_BUS_RIU_ADDR + (0x1006a6 <<1 )) , 0x0000   @Mask MIU0_group_3

    @ all MIU1 IP select MIU0 in bringup
    WREG    (MS_BUS_RIU_ADDR + (0x1006f0 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f2 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f4 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f6 <<1 )), 0x0000
.endif

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )), 0x1808   @ SW initial done and turn on arbitor
@// WREG    (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x8400
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )), 0x1808   @ SW initial done and turn on arbitor
@// WREG    (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x8400
.endif

    @default BW table
    WREG    (MS_BUS_RIU_ADDR + (0x101242 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x101244 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x101262 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x101264 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x101282 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x101284 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x1012A2 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x1012A4 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x101240 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x101260 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x101280 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x1012A0 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x101226 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1012FA <<1 )), 0x0010
    WREG    (MS_BUS_RIU_ADDR + (0x1012F8 <<1 )), 0x0403
    WREG    (MS_BUS_RIU_ADDR + (0x101228 <<1 )), 0x6490
    WREG    (MS_BUS_RIU_ADDR + (0x10122A <<1 )), 0x2225
    WREG    (MS_BUS_RIU_ADDR + (0x101228 <<1 )), 0x649E
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100642 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x100644 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x100662 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x100664 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x100682 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x100684 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x1006A2 <<1 )), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x1006A4 <<1 )), 0x0200
    WREG    (MS_BUS_RIU_ADDR + (0x100640 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x100660 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x100680 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x1006A0 <<1 )), 0x8015
    WREG    (MS_BUS_RIU_ADDR + (0x100626 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x100628 <<1 )), 0x2490
    WREG    (MS_BUS_RIU_ADDR + (0x10062A <<1 )), 0x2225
    WREG    (MS_BUS_RIU_ADDR + (0x100628 <<1 )), 0x249E
.endif

#if defined(CONFIG_MSTAR_TITANIA_MMAP_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_32MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB_DEFAULT)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_1024MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0xa000
#else
    #error "Incorrect MMAP setting!!"
#endif

.if ( ENABLE_MIU1 == 1 )
#if defined(CONFIG_MSTAR_TITANIA_MMAP_32MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB_DEFAULT)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_1024MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#else
    #error "Incorrect MMAP setting!!"
#endif
.endif

.endm

@-------------------------------------------------
@Macro: drv_miu_init_fpga
@-------------------------------------------------
.macro drv_miu_init_fpga

    @ XD2MIU init setting
    WREG    0x1F005788, 0x0004

    WREG    0x1F00578C, 0x3c11
    WREG    0x1F005790, 0x0010
    WREG    0x1F005794, 0x403c
    WREG    0x1F005798, 0x0101

    @ disable MIU random model
    WREG    0x1F202454, 0xC000
    WREG    0x1F2025FC, 0xFF00

    @T4 trigger MIU init
    WREG    0x1F202404, 0x0000
    WREG    0x1F202404, 0x0858
    WREG    0x1F202408, 0x0185
    WREG    0x1F20240C, 0x0120
    WREG    0x1F202410, 0x0833
    WREG    0x1F202414, 0x0c33
    WREG    0x1F202418, 0x7111
    WREG    0x1F20241C, 0x100e
    WREG    0x1F202420, 0x0031

    WREG    0x1F20243C, 0x0C01
    WREG    0x1F20243C, 0x0C00
    WREG    0x1F202400, 0x0008
    WREG    0x1F202400, 0x000c

    DELAYUS 100

    WREG    0x1F202400, 0x000e
    DELAYUS 0x100

    WREG    0x1F202400, 0x001f
    DELAYUS 100

    WREG    0x1F20243C, 0x0C08

.endm

@-------------------------------------------------
@Macro: drv_miu_init_priority
@-------------------------------------------------
.macro drv_miu_init_priority

    @ MIU0: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F202480
    and     r0, r0, #1
    cmp     r0, #1
    beq     miu0_rq0_skip

    RREG    r0, 0x1F202480
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

    RREG    r0, 0x1F202480
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

miu0_rq0_skip:

    RREG    r0, 0x1F2024C0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq1_skip

    RREG    r0, 0x1F2024C0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

    RREG    r0, 0x1F2024C0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

miu0_rq1_skip:

    RREG    r0, 0x1F202500
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq2_skip

    RREG    r0, 0x1F202500
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

    RREG    r0, 0x1F202500
    bic     r0, r0, #0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

miu0_rq2_skip:

    RREG    r0, 0x1F202540
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq3_skip

    RREG    r0, 0x1F202540
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

    RREG    r0, 0x1F202540
    bic     r0, r0, #0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

miu0_rq3_skip:

    @ MIU1: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F200C80
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq0_skip

    RREG    r0, 0x1F200C80
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

    RREG    r0, 0x1F200C80
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

miu1_rq0_skip:

    RREG    r0, 0x1F200CC0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq1_skip

    RREG    r0, 0x1F200CC0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200CC0
    str     r0, [r1]

    RREG    r0, 0x1F200CC0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200CC0
    str     r0, [r1]

miu1_rq1_skip:

    RREG    r0, 0x1F200D00
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq2_skip

    RREG    r0, 0x1F200D00
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

    RREG    r0, 0x1F200D00
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

miu1_rq2_skip:

    RREG    r0, 0x1F200D40
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq3_skip

    RREG    r0, 0x1F200D40
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

    RREG    r0, 0x1F200D40
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

miu1_rq3_skip:
.endm

@-------------------------------------------------
@Macro: drv_miu_set_group_priority
@-------------------------------------------------
.macro drv_miu_set_group_priority
    @set group priority in MIU_0
    RREG    r0, 0x1F2025FC
    bic     r0, r0, #(1<<8)
    ldr     r1, =0x1F2025FC
    str     r0, [r1]

    RREG    r0, 0x1F2025FC
    and     r0, r0, #0xFF00
    orr     r0, r0, #(MIU0_GROUP_PRIORITY & 0xFF)
    ldr     r1, =0x1F2025FC
    str     r0, [r1]

    RREG    r0, 0x1F2025FC
    orr     r0, r0, #0x0100           @ set group fix priority
    ldr     r1, =0x1F2025FC
    str     r0, [r1]

    @set group priority in MIU_1
    RREG    r0, 0x1F200DFC
    bic     r0, r0, #(1<<8)
    ldr     r1, =0x1F200DFC
    str     r0, [r1]

    RREG    r0, 0x1F200DFC
    and     r0, r0, #0xFF00
    orr     r0, r0, #(MIU1_GROUP_PRIORITY & 0xFF)
    ldr     r1, =0x1F200DFC
    str     r0, [r1]

    RREG    r0, 0x1F200DFC
    orr     r0, r0, #0x0100
    ldr     r1, =0x1F200DFC
    str     r0, [r1]
.endm

@-------------------------------------------------
@Macro: drv_miu0_bisttest
@-------------------------------------------------
.macro drv_miu0_bisttest
    @miu_0 bist test ---128Mbyte
    PUTK   '\n'
    PUTK   '\r'
    PUTK   'B'
    PUTK   'I'
    PUTK   'S'
    PUTK   'T'
    PUTK   '0'
    PUTK   '-'

    WREG    (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )) , 0x0000   @1012e0 //reset bist test
    WREG    0x1F2025E0 , 0x0000   @1012f0 bit_15=1 choice to MIU_0
    WREG    (MS_BUS_RIU_ADDR + (0x1012e2 <<1 )) , 0x0000   @1012e2 //start address base unit   :8k bytes
    WREG    (MS_BUS_RIU_ADDR + (0x1012e4 <<1 )) , BIST_LEN
    WREG    (MS_BUS_RIU_ADDR + (0x1012e8 <<1 )) , 0x5aa5   @1012e8 //bist test pattern

    WREG    (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )) , 0x0003   @bitst test mode:3

ChkBistMiu0:
    RREG   r0 , (MS_BUS_RIU_ADDR + (0x1012e0 <<1 ))
    and    r1, r0, #0x8000
    cmp    r1, #0
    beq    ChkBistMiu0

    and    r1, r0, #0x6000
    cmp    r1, #0
    beq    BistMiu0_OK

BistMiu0_FAIL:
    PUTK   'F'
    PUTK   'A'
    PUTK   'I'
    PUTK   'L'
    bl     BistRetMIU0

BistMiu0_OK:
    PUTK   'O'
    PUTK   'K'

BistRetMIU0:
    PUTK   '\n'
    PUTK   '\r'
.endm

@-------------------------------------------------
@Macro: drv_miu1_bisttest
@-------------------------------------------------
.macro drv_miu1_bisttest
    @miu_1 bist test ---128Mbyte
    WREG   0x1F2025c0 , 0x0000   @1012e0 //reset bist test
    WREG   0x1F2025E0 , 0x8000   @1012f0 bit_15=1 choice to MIU_1

    WREG   0x1F2025c4 , 0x0000   @1012e2 //start address base unit   :8k bytes
    WREG   0x1F2025c8 , BIST_LEN
    PUTK   'B'
    PUTK   'I'
    PUTK   'S'
    PUTK   'T'
    PUTK   '1'
    PUTK   '-'

    WREG    (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )) , 0x0003   @bitst test mode:3

ChkBistMiu1:
    RREG   r0 , (MS_BUS_RIU_ADDR + (0x1012e0 <<1 ))
    and    r1, r0, #0x8000
    cmp    r1, #0
    beq    ChkBistMiu1

    and    r1, r0, #0x6000
    cmp    r1, #0
    beq    BistMiu1_OK

BistMiu1_FAIL:
    PUTK   'F'
    PUTK   'A'
    PUTK   'I'
    PUTK   'L'
    bl     BistRetMIU1

BistMiu1_OK:
    PUTK   'O'
    PUTK   'K'

BistRetMIU1:
    PUTK   '\n'
    PUTK   '\r'
.endm

@-------------------------------------------------
@Macro: drv_miu0_autophase 'porting from J2'
@-------------------------------------------------
.macro drv_miu0_autophase
#define DUMMY_REG   r10         // $28 Dummy register to store miu 0 DQS phase result
#define DUMMY_VAL   r9          // $24 DQS phase result
#define DQS_VAL     r0          // $9
#define DQS_VAL_BK  r8          // $29
#define miu_phase_reg r7       // $11
#define miu0_dqs_mask_reg r6    // $10
#define REG_ADDR_BASE 0x1f000000

    PUTK   '\n'
    PUTK   '\r'

    WREG    0x1F2025E0 , 0x0000    @ 1012f0 bit_15=0 choice to MIU_0
    ldr     DUMMY_REG,=(REG_ADDR_BASE+(0x103390<<1))
    ldr     DUMMY_VAL,=0

    RREG    DQS_VAL, (REG_ADDR_BASE+(0x110D6E<<1))  @store the default phase setting to r19
    mov     DQS_VAL_BK, DQS_VAL

    ldr     miu_phase_reg, =(REG_ADDR_BASE+(0x110D6E<<1))  @ reg_0x110D6E  //miu_phase_reg

    AutoPhaseLoop
.endm

@-------------------------------------------------
@Macro: drv_miu1_autophase
@-------------------------------------------------
.macro drv_miu1_autophase
#define DUMMY_REG   r10         // $28 Dummy register to store miu 0 DQS phase result
#define DUMMY_VAL   r9          // $24 DQS phase result
#define DQS_VAL     r0          // $9
#define DQS_VAL_BK  r8          // $29
#define miu_phase_reg r7       // $11
#define miu0_dqs_mask_reg r6    // $10
#define REG_ADDR_BASE 0x1f000000

    WREG    0x1F2025E0 , 0x8000    @ 1012f0 bit_15=1 choice to MIU_1
    ldr     DUMMY_REG,=(REG_ADDR_BASE+(0x103394<<1))
    ldr     DUMMY_VAL,=0

    RREG    DQS_VAL, (REG_ADDR_BASE+(0x110DEE<<1))  @store the default phase setting to r19
    mov     DQS_VAL_BK, DQS_VAL

    ldr     miu_phase_reg, =(REG_ADDR_BASE+(0x110DEE<<1))  @ 0x110DEE  //miu_phase_reg

    AutoPhaseLoop
.endm

@-------------------------------------------------
@Macro: AutoPhaseLoop
@-------------------------------------------------
.macro AutoPhaseLoop
#define DUMMY_REG   r10         // $28 Dummy register to store miu 0 DQS phase result
#define DUMMY_VAL   r9          // $24 DQS phase result
#define DQS_VAL     r0          // $9
#define DQS_VAL_BK  r8          // $29
#define miu_phase_reg r7       // $11
#define miu0_dqs_mask_reg r6    // $10
#define tmp_var0    r1          // $13
#define good_phase_cnt r2       // $21
#define good_phase_sum r3       // $20
#define good_phase_bit r4       // $25
#define temp_val       r5       // $8
#define REG_ADDR_BASE 0x1f000000


    PUTK    '['
    WREG    (REG_ADDR_BASE+(0x1012e4<<1)), 0x0401   @ 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e6<<1)), 0x0000   @ 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e8<<1)), 0x00FF   @ 1012e4~1012e7 bist test pattern

    ldr     tmp_var0, =0
    ldr     good_phase_cnt, =0
    ldr     good_phase_sum, =0
    ldr     good_phase_bit, =1

StartChk_x3_\@:

BistPatternfill_\@:                      @write data into each region respect to bist mode 0x183,0x185,0x187

.if ( ENABLE_MIU1 == 1 )
    WREG        0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1000   @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0,0x0000
    ldr     DQS_VAL,=0x0083             @bist mode 0x83
    b       BistRWModeTest_\@
    nop

Check_bist85_\@:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1100   @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0,0x0000
    ldr     DQS_VAL,=0x0085             @bist mode 0x85
    b       BistRWModeTest_\@
    nop

Check_bist87_\@:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1200   @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0,0x0000
    ldr     DQS_VAL,=0x0087             @bist mode 0x87
    b       BistRWModeTest_\@
    nop

BistRWModeTest_\@:
    ModeChangeDelay

    ldr     temp_val,=0x1f2025c0
    str     DQS_VAL,[temp_val]           @bist test start

CheckRWBistDone_\@:
    RREG    DQS_VAL, 0x1F2025C0
    and     temp_val, DQS_VAL, #0x8000
    cmp     temp_val, #0
    beq     CheckRWBistDone_\@           @ check done
    nop

RWBistCheckPhaseOK_\@:
    and     temp_val, DQS_VAL, #0x00FF
    cmp     temp_val, #0x83
    beq     Check_bist85_\@       @x83->0x85->0x87
    nop
    cmp     temp_val, #0x85
    beq     Check_bist87_\@
    nop

check_x3_\@:
    ClockReset
    and     DQS_VAL, tmp_var0, #0x000F
    lsl     DQS_VAL, DQS_VAL, #12
    ldr     temp_val, =0x0FFF
    and     temp_val, DQS_VAL_BK, temp_val
    orr     DQS_VAL, DQS_VAL, temp_val
    str     DQS_VAL,[miu_phase_reg]

    ClockUnReset
    b       StartCheck_\@
    nop

StartChk_x2_\@:
    str     DUMMY_VAL, [DUMMY_REG]  @store phase 0 result
    add     DUMMY_REG, DUMMY_REG, #4
    ldr     good_phase_bit, =1
    b       check_x2_\@
    nop

check_x2_\@:
    ClockReset
    and     DQS_VAL, tmp_var0, #0x000F
    lsl     DQS_VAL, DQS_VAL, #8
    ldr     temp_val, =0xF0FF
    and     temp_val, DQS_VAL_BK, temp_val
    orr     DQS_VAL, DQS_VAL, temp_val
    str     DQS_VAL,[miu_phase_reg]

    ClockUnReset
    b       StartCheck_\@
    nop

StartChk_x1_\@:
    str     DUMMY_VAL, [DUMMY_REG]  @store phase 0 result
    add     DUMMY_REG, DUMMY_REG, #4
    ldr     good_phase_bit, =1
    b       check_x1_\@
    nop

check_x1_\@:
    ClockReset
    and     DQS_VAL, tmp_var0, #0x000F
    lsl     DQS_VAL, DQS_VAL, #4
    ldr     temp_val, =0xFF0F
    and     temp_val, DQS_VAL_BK, temp_val
    orr     DQS_VAL, DQS_VAL, temp_val
    str     DQS_VAL,[miu_phase_reg]

    ClockUnReset
    b       StartCheck_\@
    nop

StartChk_x0_\@:
    str     DUMMY_VAL, [DUMMY_REG]  @store phase 0 result
    add     DUMMY_REG, DUMMY_REG, #4
    ldr     good_phase_bit, =1
    b       check_x0_\@
    nop

check_x0_\@:
    ClockReset
    and     DQS_VAL, tmp_var0, #0x000F
    lsl     DQS_VAL, DQS_VAL, #0
    ldr     temp_val, =0xFFF0
    and     temp_val, DQS_VAL_BK, temp_val
    orr     DQS_VAL, DQS_VAL, temp_val
    str     DQS_VAL,[miu_phase_reg]

    ClockUnReset
    b       StartCheck_\@
    nop

StartCheck_\@:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    0x1f2025C0, 0x0000
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1000 @ 1012e2 bist test start address, (4K byte/unit)
    ldr     DQS_VAL, =0x0183             @ bist mode 0x183
    b       ROBitModeTest_\@
    nop

Check_bist185_\@:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1100    @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0, 0x0000
    ldr     DQS_VAL, =0x0185             @ bist mode 0x0185
    b       ROBitModeTest_\@
    nop

Check_bist187_\@:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif

    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1200
    WREG    0x1f2025C0, 0x0000
    ldr     DQS_VAL, =0x0187             @ bist mode 0x187

ROBitModeTest_\@:                      @ read only bist
    ModeChangeDelay

    ldr     temp_val,=0x1f2025c0
    str     DQS_VAL,[temp_val]

CheckROBistDone_\@:
    RREG    DQS_VAL, 0x1f2025C0
    and     temp_val, DQS_VAL, #0x8000
    cmp     temp_val, #0
    beq     CheckROBistDone_\@
    nop
    and     temp_val, DQS_VAL, #0x6000
    cmp     temp_val, #0
    bne     checkloopFail_\@         @ bist test fail if not zero
    nop

ROBistCheckPhaseOK_\@:
    @and     r6, r0, #0x1FF
    ldr     temp_val,=0x1f2025c0
    ldr     DQS_VAL,[temp_val]
    and     DQS_VAL, DQS_VAL, #0x00FF

    nop
    cmp     DQS_VAL, #0x083
    beq     Check_bist185_\@        @ 0x183->0x185->0x187
    nop
    cmp     DQS_VAL, #0x085
    beq     Check_bist187_\@
    nop

    and     DQS_VAL, tmp_var0, #0x0f  @ move $13(loop cnt) to $9 for putchar
    puthex
    nop

    add     good_phase_cnt, good_phase_cnt, #1              @ good_phase_cnt++
    and     r11, tmp_var0, #0x0f                          @ get good_phase
    add     good_phase_sum, good_phase_sum, r11              @ good_phase_sum += good phase
    orr     DUMMY_VAL, DUMMY_VAL, good_phase_bit

checkloopFail_\@:

checkloop_\@:
    lsl     good_phase_bit, good_phase_bit, #1
    add     tmp_var0, tmp_var0, #1                          @add loop cnt by 1
    cmp     tmp_var0, #16
    bne     CheckLoopDone_\@
    nop

    cmp     good_phase_cnt, #0
    beq     SetToDefault_P3_\@                              @ if good_phase cnt == 0
    nop

    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    div_op
    mov     DQS_VAL, r12
    lsl     DQS_VAL, DQS_VAL, #12
    b       StorePhase_P3_\@
    nop

SetToDefault_P3_\@:
    ClockReset

    mov     DQS_VAL, DQS_VAL_BK
    b       SetPhaseToDefault_p3_\@
    nop

StorePhase_P3_\@:
    ClockReset

    ldr     r11, =0x0FFF
    and     r11, DQS_VAL_BK, r11
    orr     DQS_VAL, DQS_VAL, r11

SetPhaseToDefault_p3_\@:
    str     DQS_VAL,[miu_phase_reg]
    mov     DQS_VAL_BK, DQS_VAL

    ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    PUTK    '['

    @start check DQS_phase_0
    b       StartChk_x2_\@
    nop

CheckLoopDone_\@:
    cmp     tmp_var0, #16
    blt     check_x3_\@
    nop
    cmp     tmp_var0, #32
    blt     check_x2_\@             @ AutoPhaseLoop1
    cmp     tmp_var0, #32
    beq     SetP2_\@
    nop
    cmp     tmp_var0, #48
    blt     check_x1_\@             @ AutoPhaseLoop1
    cmp     tmp_var0, #48
    beq     SetP1_\@
    nop
    cmp     tmp_var0, #64
    blt     check_x0_\@             @ AutoPhaseLoop1
    cmp     tmp_var0, #64
    beq     SetP0_\@

SetP2_\@:
    str     DUMMY_VAL,[DUMMY_REG]
    nop
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P2_\@      @ good_phase cnt == 0
    nop
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    div_op
    mov     DQS_VAL, r12
    lsl     DQS_VAL, DQS_VAL, #8
    b       StorePhase_P2_\@
    nop

SetToDefault_P2_\@:
    ClockReset

    mov     DQS_VAL, DQS_VAL_BK
    b       SetPhaseToDefault_P2\@
    nop

StorePhase_P2_\@:
    ClockReset
    ldr     r11, =0xF0FF
    and     r11, DQS_VAL_BK, r11
    orr     DQS_VAL, DQS_VAL, r11

SetPhaseToDefault_P2\@:
    str     DQS_VAL,[miu_phase_reg]
    mov     DQS_VAL_BK, DQS_VAL

    ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    PUTK    '['

    @start check DQS_phase_0
    b       StartChk_x1_\@
    nop

SetP1_\@:
    str     DUMMY_VAL,[DUMMY_REG]
    nop
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P1_\@      @ good_phase cnt == 0
    nop
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    div_op
    mov     DQS_VAL, r12
    lsl     DQS_VAL, DQS_VAL, #4
    b       StorePhase_P1_\@
    nop

SetToDefault_P1_\@:
    ClockReset

    mov     DQS_VAL, DQS_VAL_BK
    b       SetPhaseToDefault_P1\@
    nop

StorePhase_P1_\@:
    ClockReset
    ldr     r11, =0xFF0F
    and     r11, DQS_VAL_BK, r11
    orr     DQS_VAL, DQS_VAL, r11

SetPhaseToDefault_P1\@:
    str     DQS_VAL,[miu_phase_reg]
    mov     DQS_VAL_BK, DQS_VAL

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    PUTK    '['

    @start check DQS_phase_0
    b       StartChk_x0_\@
    nop

SetP0_\@:
    str     DUMMY_VAL,[DUMMY_REG]
    nop
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P0_\@      @ good_phase cnt == 0
    nop
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    div_op
    mov     DQS_VAL, r12
    lsl     DQS_VAL, DQS_VAL, #0
    b       StorePhase_P0_\@
    nop

SetToDefault_P0_\@:
    ClockReset

    mov     DQS_VAL, DQS_VAL_BK
    b       SetPhaseToDefault_P0\@
    nop

StorePhase_P0_\@:
    ClockReset
    ldr     r11, =0xFFF0
    and     r11, DQS_VAL_BK, r11
    orr     DQS_VAL, DQS_VAL, r11

SetPhaseToDefault_P0\@:
    str     DQS_VAL,[miu_phase_reg]
    mov     DQS_VAL_BK, DQS_VAL
    ClockUnReset

    PUTK    ']'
    PUTK    '-'

    and     DQS_VAL, DQS_VAL_BK, #0xF000
    lsr     DQS_VAL, DQS_VAL, #12
    puthex
    nop
    and     DQS_VAL, DQS_VAL_BK, #0x0F00
    lsr     DQS_VAL, DQS_VAL, #8
    puthex
    nop
    and     DQS_VAL, DQS_VAL_BK, #0x00F0
    lsr     DQS_VAL, DQS_VAL, #4
    puthex
    nop
    and     DQS_VAL, DQS_VAL_BK, #0x000F
    lsr     DQS_VAL, DQS_VAL, #0
    puthex
    nop

    PUTK    '\r'
    PUTK    '\n'
.endm

@-------------------------------------------------
@Macro: puthex
@-------------------------------------------------
.macro puthex
    cmp     r0, #10
    blt     putx0_9_\@
    nop
putxA_F_\@:
    add     r0, r0, #0x37
    b       putx_\@
    nop
putx0_9_\@:
    add     r0, r0, #0x30
putx_\@:
    ldr     r5, =0x1F201300
    str     r0,[r5]
    nop
.endm

@-------------------------------------------------
@Macro: div_op
@-------------------------------------------------
.macro div_op
    @ldr     r11, =128    @ divide r11
    @ldr     r5, =4      @ by r5
    ldr     r12,=0      @ init counter
subtract_\@:
    sub     r11, r11, r5
    add     r12,r12, #1
    cmp     r11,r5
    bhs     subtract_\@
.endm

@-------------------------------------------------
@Macro: ModeChangeDelay
@-------------------------------------------------
.macro ModeChangeDelay
#define temp_val       r5      // $8
    ldr     temp_val,=0
DelayLoop_\@:
    add     temp_val, temp_val, #1
    cmp     temp_val, #10
    bne     DelayLoop_\@
    nop
.endm

@-------------------------------------------------
@Macro: ClockRest
@-------------------------------------------------
.macro ClockReset
    ldr     r11, =(REG_ADDR_BASE+(0x110D0E<<1))
    ldr     r12, [r11]
    and     r12, r12, #0x9F
    orr     r12, r12, #0x60
    strb    r12, [r11]
.endm

@-------------------------------------------------
@Macro: ClockUnRest
@-------------------------------------------------
.Macro ClockUnReset
    ldr     r11, =(REG_ADDR_BASE+(0x110D0E<<1))
    ldr     r12, [r11]
    and     r12, r12, #0x9F
    orr     r12, r12, #0x20
    strb    r12, [r11]
.endm

