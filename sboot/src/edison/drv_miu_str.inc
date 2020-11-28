#include "MIUSEL_EDISON_2MIU.h"
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
@Macro: drv_miu_init_str
@-------------------------------------------------
.macro drv_miu_init_str

    WREG    0x1F201674, 0x0808  @ turn on miu clock

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x2018
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x2018
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d18 << 1)), 0x3F80
    WREG        (MS_BUS_RIU_ADDR + (0x110d98 << 1)), 0x3F80
    DELAYUS     200                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0008
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d18 << 1)), 0x1000
    WREG        (MS_BUS_RIU_ADDR + (0x110d98 << 1)), 0x1000
    DELAYUS     1000                                         @//delay 200us

    @ MIU0 Software reset
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0000   @hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c00   @
    WREG    (MS_BUS_RIU_ADDR + (0x101202 <<1 )) , 0xf000   @disable all ddr bus out

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
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0xf000   @

    @ MIU1 Request mask
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @ mask group0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0xFFFF   @ mask group1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0xFFFF   @ mask group2
    WREG    (MS_BUS_RIU_ADDR + (0x1006A6 <<1 )) , 0xFFFF   @ mask group3
.endif

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d36 <<1 )) , 0x4002   @ reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d36 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d34 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110d30 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110d32 <<1 )) , 0x0019

    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x1000

.if ( ENABLE_MIU1 == 1 )
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4001   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110db4 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110db0 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110db2 <<1 )) , 0x0019

    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x1000
.endif

    DELAYUS 5000    @ delay 5ms

    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x0000
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x0000
.endif

    ldr r0, =MIU0_DDR_Init_STR
    bl MDrv_WriteRegTbl32

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e09   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e0a   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d02 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d18 <<1 )) , 0x1000   @STR
    WREG    (MS_BUS_RIU_ADDR + (0x101202 <<1 )) , 0xf3a7
    WREG    (MS_BUS_RIU_ADDR + (0x110d54 <<1 )) , 0x0070

.if ( ENABLE_MIU1 == 1 )
    ldr r0, =MIU1_DDR_Init_STR
    bl MDrv_WriteRegTbl32

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e09   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e0a   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d82 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d98 <<1 )) , 0x1000   @STR
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0xf3a3
    WREG    (MS_BUS_RIU_ADDR + (0x110dd4 <<1 )) , 0x0070
.endif

    DELAYUS  100  @ delay 100us

    @ MIU0 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
    DBGREG  0x0025


.if ( ENABLE_MIU1 == 1 )
    @ MIU1 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
.endif

    Miu_auto_phase_str
    
    Enter_DDR_RefreshMode
 
    Miu_str_oenz_disable
 
    WREG        (MS_BUS_RIU_ADDR + (0x110D54 <<1 )), 0x0000 @//ATOP_PD off
.if ( ENABLE_MIU1 == 1 )
    WREG        (MS_BUS_RIU_ADDR + (0x110Dd4 <<1 )), 0x0000 @//ATOP_PD off
.endif

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x703f   @reg_rx_en
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
    #endif

.if ( ENABLE_MIU1 == 1 )
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x703f   @reg_rx_en
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
    #endif
.endif

    Exit_DDR_RefreshMode

    DELAYUS 200   @ delay 200us

    @ U04 last down Z switch
    RREG    r0, (MS_BUS_RIU_ADDR + (0x001e02 <<1 ))
    bic     r0, r0, #0x00FF
    lsr     r0, r0, #8
    cmp     r0, #3 
    blt     U03_chip_bypass_str
    nop
    RREG    r0, (MS_BUS_RIU_ADDR + (0x10125E <<1 ))
    orr     r0, r0, #0x0100
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x10125E <<1 ))
    str     r0, [r1]
    .if ( ENABLE_MIU1 == 1 )
    RREG    r0, (MS_BUS_RIU_ADDR + (0x10065E <<1 ))
    orr     r0, r0, #0x0100
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x10065E <<1 ))
    str     r0, [r1]
    .endif
U03_chip_bypass_str:

    @ last_done_z select to last stage
    WREG    (MS_BUS_RIU_ADDR + (0x101252 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x101272 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x101292 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1012B2 <<1 )) , 0xFFFF
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100652 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x100672 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x100692 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1006B2 <<1 )) , 0xFFFF
.endif

    Push_Dram_STR
    drv_miu_init_priority_str

    RREG        r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))
    orr         r8, r8, #0x0001
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))

    RREG        r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))
    bic         r8, r8, #0x0001
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))

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
    WREG    (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x8400
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )), 0x1808   @ SW initial done and turn on arbitor
    WREG    (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x8400
.endif


#if (ENABLE_MSTAR_EDISON_MMAP_512MB_256MB == 1)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif (ENABLE_MSTAR_EDISON_MMAP_512MB_512MB == 1)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#else
    #error "Incorrect MMAP setting in Edison!!"
#endif

    RREG     r0, 0x1F202454    @Switch MIU0 client 0x0F from BIST to SC
    orr      r0, r0, #0x4000
    REG_C2M  r0, 0x1F202454

    RREG     r0, 0x1F200C54    @Switch MIU1 client 0x0F from BIST to SC
    orr      r0, r0, #0x4000
    REG_C2M  r0, 0x1F200C54

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
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
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
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#else
    #error "Incorrect MMAP setting!!"
#endif
.endif


    @ MFE set to 128bit MIU bus
    RREG    r0, (MS_BUS_RIU_ADDR + (0x101e44 <<1 ))
    bic     r0, r0, #0x0180
    bic     r0, r0, #0x8000
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x101e44 <<1 ))
    str     r0, [r1]


.endm


@-------------------------------------------------
@Macro: Miu_auto_phase_str
@-------------------------------------------------
.macro Miu_auto_phase_str

    @ // Re write MIU auto phase
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB2 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6C << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB6 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6E << 1))
.if ( ENABLE_MIU1 == 1 )
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB8 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110DEC << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DBA << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110DEE << 1))
.endif

.endm


@-------------------------------------------------
@Macro: Enter_DDR_RefreshMode
@-------------------------------------------------
.macro Enter_DDR_RefreshMode

    @// [DDR3][enter] <MIU0>
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101218 << 1)), 0x0400 @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x042F @//trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x052F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x022F @//trig refresh
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x1430 @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x202F

.if ( ENABLE_MIU1 == 1 )
   @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x1006e0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100618 << 1)), 0x0400 @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x042F @//trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x052F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F @//trig refresh
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x1430 @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x202F
.endif

.endm

@-------------------------------------------------
@Macro: Miu_str_oenz_disable
@-------------------------------------------------
.macro Miu_str_oenz_disable

    RREG        r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    bic    r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
.if ( ENABLE_MIU1 == 1 )
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    bic    r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
.endif

.endm

@-------------------------------------------------
@Macro: Exit_DDR_RefreshMode
@-------------------------------------------------
.macro Exit_DDR_RefreshMode

    @// [DDR3][exit] <MIU0>
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001F
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x342b @//trig refresh
@//    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off

.if ( ENABLE_MIU1 == 1 )
    @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001F
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x342b @//trig refresh
@//    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off
.endif

.endm

@-------------------------------------------------
@Macro: Push_Dram_STR
@-------------------------------------------------
.macro Push_Dram_STR

#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e5 @// reg_en_mask @//Table: MIU0_DDR_Init_STR
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a5
#elif(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a7
#endif

.if ( ENABLE_MIU1 == 1 )    
#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e5 @// reg_en_mask @//Table: MIU1_DDR_Init_STR
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a5
#elif(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a7
#endif
.endif

    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 <<1 )), 0x0004 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101

    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101
    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0000

.if ( ENABLE_MIU1 == 1 )
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 <<1 )), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 <<1 )), 0x0004 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101

    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101
    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 <<1 )), 0x0000
.endif

.endm

@-------------------------------------------------
@Macro: drv_miu_init_priority_str
@-------------------------------------------------
.macro drv_miu_init_priority_str

    @ MIU0: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F202480
    and     r0, r0, #1
    cmp     r0, #1
    beq     miu0_rq0_skip_str

    RREG    r0, 0x1F202480
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

    RREG    r0, 0x1F202480
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

miu0_rq0_skip_str:

    RREG    r0, 0x1F2024C0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq1_skip_str

    RREG    r0, 0x1F2024C0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

    RREG    r0, 0x1F2024C0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

miu0_rq1_skip_str:

    RREG    r0, 0x1F202500
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq2_skip_str

    RREG    r0, 0x1F202500
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

    RREG    r0, 0x1F202500
    bic     r0, r0, #0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

miu0_rq2_skip_str:

    RREG    r0, 0x1F202540
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq3_skip_str

    RREG    r0, 0x1F202540
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

    RREG    r0, 0x1F202540
    bic     r0, r0, #0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

miu0_rq3_skip_str:

    @ MIU1: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F200C80
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq0_skip_str

    RREG    r0, 0x1F200C80
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

    RREG    r0, 0x1F200C80
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

miu1_rq0_skip_str:

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

miu1_rq1_skip_str:

    RREG    r0, 0x1F200D00
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq2_skip_str

    RREG    r0, 0x1F200D00
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

    RREG    r0, 0x1F200D00
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

miu1_rq2_skip_str:

    RREG    r0, 0x1F200D40
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq3_skip_str

    RREG    r0, 0x1F200D40
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

    RREG    r0, 0x1F200D40
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

miu1_rq3_skip_str:
.endm

#if 0
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
#endif
