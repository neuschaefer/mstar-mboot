#if (ENABLE_MEM1066MHz)
#elif (ENABLE_MEM1300MHz)
#elif (ENABLE_MEM1600MHz)
#else
#error "Invalid MIU Memory Frequency Selection"
#endif

#
#swch 4
#
#//MIU0 Software reset
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0e00
WREG (REG_ADDR_BASE + (0x101202 <<1 )) , 0x0000
#//MIU0 Request mask
WREG (REG_ADDR_BASE + (0x1012f8 <<1 )) , 0x8000
WREG (REG_ADDR_BASE + (0x101246 <<1 )) , 0xFFFE
WREG (REG_ADDR_BASE + (0x101266 <<1 )) , 0xFFFF
WREG (REG_ADDR_BASE + (0x101286 <<1 )) , 0xFFFF
WREG (REG_ADDR_BASE + (0x1012A6 <<1 )) , 0xFFFF

#//MIU1 Software reset
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0e00
WREG (REG_ADDR_BASE + (0x100602 <<1 )) , 0x0000
#//MIU1 Request mask
WREG (REG_ADDR_BASE + (0x1006f8 <<1 )) , 0x8000
WREG (REG_ADDR_BASE + (0x100646 <<1 )) , 0xFFFE
WREG (REG_ADDR_BASE + (0x100666 <<1 )) , 0xFFFF
WREG (REG_ADDR_BASE + (0x100686 <<1 )) , 0xFFFF
WREG (REG_ADDR_BASE + (0x1006A6 <<1 )) , 0xFFFF

#//=================================================================================================
#// MIU0: 128MB DDR3-1600
#
WREG (REG_ADDR_BASE + (0x110d3a <<1 )) , 0x0000  #// mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select

#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4001  #// mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0300  #// loop_div/input_div
WREG (REG_ADDR_BASE + (0x110d30 <<1 )) , 0x1b87  #// ddfset
WREG (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x0028	 #// ddrpll_reset/ddrpll_porst/ddrpl_pd
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
#elif (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4002  #// mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0300  #// loop_div/input_div
WREG (REG_ADDR_BASE + (0x110d30 <<1 )) , 0x2e8b  #// ddfset
WREG (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x001f  #// ddrpll_reset/ddrpll_porst/ddrpl_pd
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4002  #// mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0300  #// loop_div/input_div
WREG (REG_ADDR_BASE + (0x110d30 <<1 )) , 0x2e8b  #// ddfset
WREG (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x001a  #// ddrpll_reset/ddrpll_porst/ddrpl_pd
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
#endif

#
DELAYUS 4000 #wait  4                         // delay 4ms
#

WREG (REG_ADDR_BASE + (0x101202 <<1 )) , 0x03a3  #//ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
WREG (REG_ADDR_BASE + (0x101204 <<1 )) , 0x000B  #//if I64Mode =0x8b else =0x0b
WREG (REG_ADDR_BASE + (0x101206 <<1 )) , 0x8450  #//refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450

#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x27b6  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x95c8  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x405a  #//tRFC
#elif (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1899  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2165  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96BA  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x406B  #//tRFC
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x4080  #//tRFC
#endif

WREG (REG_ADDR_BASE + (0x101210 <<1 )) , 0x1c70  #//MR0
WREG (REG_ADDR_BASE + (0x101204 <<1 )) , 0x000B  #//if I64Mode =0x8b else =0x0b

#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x101206 <<1 )) , 0x0430
#else
WREG (REG_ADDR_BASE + (0x101206 <<1 )) , 0x8434
#endif

#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x405a  #//tRFC
#elif (ENABLE_MEM1300MHz)
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0xb6ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x40c0  #//tRFC
#else
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1899  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2165  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ba  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x406b  #//tRFC
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x4080  #//tRFC
#endif

WREG (REG_ADDR_BASE + (0x101210 <<1 )) , 0x1c70  #//MR0
WREG (REG_ADDR_BASE + (0x101212 <<1 )) , 0x4004  #//MR1
WREG (REG_ADDR_BASE + (0x101214 <<1 )) , 0x8018  #//MR2
WREG (REG_ADDR_BASE + (0x101216 <<1 )) , 0xC000  #//MR3
WREG (REG_ADDR_BASE + (0x101228 <<1 )) , 0xb270  #//pack_en enable
WREG (REG_ADDR_BASE + (0x10122c <<1 )) , 0x71C1  #// Address Balance Mode
WREG (REG_ADDR_BASE + (0x101230 <<1 )) , 0x0000

WREG (REG_ADDR_BASE + (0x110d54 <<1 )) , 0x0000  #//miu_0_atop  start
WREG (REG_ADDR_BASE + (0x110d00 <<1 )) , 0x0411
WREG (REG_ADDR_BASE + (0x110d02 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d04 <<1 )) , 0x0080
WREG (REG_ADDR_BASE + (0x110d06 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d08 <<1 )) , 0x003F
WREG (REG_ADDR_BASE + (0x110d0a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d0c <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d0e <<1 )) , 0x00e5
WREG (REG_ADDR_BASE + (0x110d0e <<1 )) , 0x00a5
WREG (REG_ADDR_BASE + (0x110d10 <<1 )) , 0x0600
WREG (REG_ADDR_BASE + (0x110d12 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d14 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d16 <<1 )) , 0x0200
WREG (REG_ADDR_BASE + (0x110d18 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d1a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d1c <<1 )) , 0x0000

#//wriu -w   0x110d1e  0xffff
WREG (REG_ADDR_BASE + (0x110d20 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110d22 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d26 <<1 )) , 0x0000

#if (ENABLE_MEM1600MHz)
#//#if(ENABLE_MSTAR_MMAP_256MB)
WREG (REG_ADDR_BASE + (0x110d28 <<1 )) , 0x000D  #//set MIU0 ssc
WREG (REG_ADDR_BASE + (0x110d2a <<1 )) , 0x0535  #//set MIU0 ssc
#//#else
#//error "only for 256MB"
#WREG (REG_ADDR_BASE + (0x110d28 <<1 )) , 0x0012  #//set MIU0 ssc
#WREG (REG_ADDR_BASE + (0x110d2a <<1 )) , 0x0458  #//set MIU0 ssc
#//#endif
#else
WREG (REG_ADDR_BASE + (0x110d28 <<1 )) , 0x0012  #//set MIU0 ssc
WREG (REG_ADDR_BASE + (0x110d2a <<1 )) , 0x0458  #//set MIU0 ssc
#endif

WREG (REG_ADDR_BASE + (0x110d2c <<1 )) , 0x0014
WREG (REG_ADDR_BASE + (0x110d2e <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d38 <<1 )) , 0x0045
WREG (REG_ADDR_BASE + (0x110d3a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d3c <<1 )) , 0x0077
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110d38 <<1 )) , 0x0044
#else
WREG (REG_ADDR_BASE + (0x110d38 <<1 )) , 0x1055
#endif
WREG (REG_ADDR_BASE + (0x110d3a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d3c <<1 )) , 0x0077
WREG (REG_ADDR_BASE + (0x110d3e <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d40 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d42 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d44 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d46 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d48 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d4a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d4c <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d4e <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d50 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d52 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d54 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d56 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d58 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d5a <<1 )) , 0x0000
#if (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x110d5c <<1 )) , 0x4444
WREG (REG_ADDR_BASE + (0x110d5e <<1 )) , 0x4444
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110d5c <<1 )) , 0x4444
WREG (REG_ADDR_BASE + (0x110d5e <<1 )) , 0x4444
#endif

WREG (REG_ADDR_BASE + (0x110d60 <<1 )) , 0x2370
WREG (REG_ADDR_BASE + (0x110d62 <<1 )) , 0x0032
WREG (REG_ADDR_BASE + (0x110d64 <<1 )) , 0xf200
WREG (REG_ADDR_BASE + (0x110d66 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d68 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110d6a <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110d6c <<1 )) , 0x0000
#if(ENABLE_MEM1600MHz)
#//#if(ENABLE_MSTAR_MMAP_256MB)
#WREG (REG_ADDR_BASE + (0x110d6e <<1 )) , 0x0089
#//#else
#//error "only for 256MB"
WREG (REG_ADDR_BASE + (0x110d6e <<1 )) , 0x0088
#//#endif
#else
WREG (REG_ADDR_BASE + (0x110d6e <<1 )) , 0x0088
#endif
#if (ENABLE_MEM1300MHz)
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8803
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8803
#else
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8805
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8805
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8803
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8803
#endif
WREG (REG_ADDR_BASE + (0x110d0e <<1 )) , 0x00a5  #// 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c00

WREG (REG_ADDR_BASE + (0x110d7e <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d00 <<1 )) , 0x0401
WREG (REG_ADDR_BASE + (0x110d02 <<1 )) , 0xaaaa
#
#//=================================================================================================
#// MIU1: 128MB DDR3-1600
#
WREG (REG_ADDR_BASE + (0x110dba <<1 )) , 0x0000  #// mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
#
#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x110db6 <<1 )) , 0x4001  #// mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110db4 <<1 )) , 0x0300  #// loop_div/input_div
WREG (REG_ADDR_BASE + (0x110db0 <<1 )) , 0x1b87  #// ddfset
WREG (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x0028  #// ddrpll_reset/ddrpll_porst/ddrpl_pd
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000
#elif (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x110db6 <<1 )) , 0x4001  #// mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110db4 <<1 )) , 0x0300  #// loop_div/input_div
WREG (REG_ADDR_BASE + (0x110db0 <<1 )) , 0x2e8b  #// ddfset
WREG (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x001f  #// ddrpll_reset/ddrpll_porst/ddrpl_pd
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110db6 <<1 )) , 0x4001  #// mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110db4 <<1 )) , 0x0300  #// loop_div/input_div
WREG (REG_ADDR_BASE + (0x110db0 <<1 )) , 0x2e8b  #// ddfset
WREG (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x001a  #// ddrpll_reset/ddrpll_porst/ddrpl_pd
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000
#endif
#
DELAYUS 4000 #wait  4                         // delay 4ms
#
WREG (REG_ADDR_BASE + (0x100602 <<1 )) , 0x03a3  #//ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
WREG (REG_ADDR_BASE + (0x100604 <<1 )) , 0x000b  #//if I64Mode =0x8b else =0x0b
WREG (REG_ADDR_BASE + (0x100606 <<1 )) , 0x8420  #//refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420

#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x27b6  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x95c8  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x405a  #//tRFC
#elif (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1899  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2165  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ba  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x406b  #//tRFC
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x4080  #//tRFC
#endif
WREG (REG_ADDR_BASE + (0x100610 <<1 )) , 0x1c70  #//MR0
WREG (REG_ADDR_BASE + (0x100604 <<1 )) , 0x000b

#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x100606 <<1 )) , 0x0430  #//refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
#else
WREG (REG_ADDR_BASE + (0x100606 <<1 )) , 0x8434  #wriu -w   0x100606  0xb434      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
#endif


#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x405a  #//tRFC
#elif (ENABLE_MEM1300MHz)
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0xb6ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x40c0  #//tRFC
#else
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1899  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2165  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ba  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x406b  #//tRFC
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #//reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2766  #//reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ca  #//reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x4080  #//tRFC
#endif
WREG (REG_ADDR_BASE + (0x100610 <<1 )) , 0x1c70  #//MR0
WREG (REG_ADDR_BASE + (0x100612 <<1 )) , 0x4004  #//MR1
WREG (REG_ADDR_BASE + (0x100614 <<1 )) , 0x8018  #//MR2
WREG (REG_ADDR_BASE + (0x100616 <<1 )) , 0xC000  #//MR3
WREG (REG_ADDR_BASE + (0x100628 <<1 )) , 0xb270  #//pack_en enable
WREG (REG_ADDR_BASE + (0x10062c <<1 )) , 0x71c1  #// Address Balance Mode
WREG (REG_ADDR_BASE + (0x100630 <<1 )) , 0x0000

WREG (REG_ADDR_BASE + (0x110dd4 <<1 )) , 0x0000  #//miu_0_atop  start
WREG (REG_ADDR_BASE + (0x110d80 <<1 )) , 0x0411
WREG (REG_ADDR_BASE + (0x110d82 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d84 <<1 )) , 0x0080
WREG (REG_ADDR_BASE + (0x110d86 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d88 <<1 )) , 0x003F
WREG (REG_ADDR_BASE + (0x110d8a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d8c <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d8e <<1 )) , 0x00e5
WREG (REG_ADDR_BASE + (0x110d8e <<1 )) , 0x00a5
WREG (REG_ADDR_BASE + (0x110d90 <<1 )) , 0x0600
WREG (REG_ADDR_BASE + (0x110d92 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d94 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d96 <<1 )) , 0x0200
WREG (REG_ADDR_BASE + (0x110d98 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d9a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d9c <<1 )) , 0x0000
#//wriu -w   0x110d9e  0xffff
WREG (REG_ADDR_BASE + (0x110da0 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110da2 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110da6 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110da8 <<1 )) , 0x0012  #//set MIU1 ssc
WREG (REG_ADDR_BASE + (0x110daa <<1 )) , 0x0458  #//set MIU ssc
WREG (REG_ADDR_BASE + (0x110dac <<1 )) , 0x0014
WREG (REG_ADDR_BASE + (0x110dae <<1 )) , 0x0000

#if (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0054
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0043
#endif

WREG (REG_ADDR_BASE + (0x110dba <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dbc <<1 )) , 0x0077

#if (ENABLE_MEM1300MHz)
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0043
#else
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0155
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0043
#endif

WREG (REG_ADDR_BASE + (0x110dba <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dbc <<1 )) , 0x0077
WREG (REG_ADDR_BASE + (0x110dbe <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dc0 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dc2 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dc4 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dc6 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dc8 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dca <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dcc <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dce <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dd0 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dd2 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dd4 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dd6 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dd8 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110dda <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110ddc <<1 )) , 0x4444  #//set MIU1 Dringing
WREG (REG_ADDR_BASE + (0x110dde <<1 )) , 0x4444  #//set MIU1 Dringing
WREG (REG_ADDR_BASE + (0x110de0 <<1 )) , 0x2370
WREG (REG_ADDR_BASE + (0x110de2 <<1 )) , 0x0032
WREG (REG_ADDR_BASE + (0x110de4 <<1 )) , 0xf200
WREG (REG_ADDR_BASE + (0x110de6 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110de8 <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110dea <<1 )) , 0x0020
WREG (REG_ADDR_BASE + (0x110dec <<1 )) , 0x0000

#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110dee <<1 )) , 0x0088
#else
WREG (REG_ADDR_BASE + (0x110dee <<1 )) , 0x0089
#endif
#if (ENABLE_MEM1300MHz)
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8803
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8803
#else
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8805
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8805
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8803
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8803
#endif
WREG (REG_ADDR_BASE + (0x110d8e <<1 )) , 0x00a5  #// 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c00
#//wriu -w   0x1012fe  0x0000
WREG (REG_ADDR_BASE + (0x110dfe <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x110d80 <<1 )) , 0x0401
WREG (REG_ADDR_BASE + (0x110d82 <<1 )) , 0xaaaa
#
#//=================================================================================================
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x0008
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x000c

DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x000e
DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x001f
DELAYUS 50000 #wait 50                    // delay 50ms
#
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x0008
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x000c

DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x000e
DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x001f
DELAYUS 50000 #wait  50                   // delay 50ms

#//=================================================================================================
#//MIU_Init_Priority
#//MIU_Set_Group_Priority
#
WREG (REG_ADDR_BASE + (0x101246 <<1 )) , 0x0000  #//unmask group0
WREG (REG_ADDR_BASE + (0x101266 <<1 )) , 0x0000  #//unmask group1
WREG (REG_ADDR_BASE + (0x101286 <<1 )) , 0x0000  #//unmask group2
WREG (REG_ADDR_BASE + (0x1012A6 <<1 )) , 0x0000  #//mask group3 //jc_db: should u4 have group3
#
#//MIU1_GROUP_SELMIU
WREG (REG_ADDR_BASE + (0x100646 <<1 )) , 0x0000  #//unmask group0
WREG (REG_ADDR_BASE + (0x100666 <<1 )) , 0x0000  #//unmask group1
WREG (REG_ADDR_BASE + (0x100686 <<1 )) , 0x0000  #//unmask group2
WREG (REG_ADDR_BASE + (0x1006A6 <<1 )) , 0x0000  #//mask group3 //jc_db: should u4 have group3

#//=================================================================================================
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c08  #//SW initial done and turn on arbitor
#
#
