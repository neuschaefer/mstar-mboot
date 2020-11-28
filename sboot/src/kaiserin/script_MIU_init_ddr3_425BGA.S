#if (ENABLE_MEM1300MHz)
#elif (ENABLE_MEM1600MHz)
#else
#error "Invalid MIU Memory Frequency Selection"
#endif
 #
 #swch 4
 #
 #//MIU0 Software reset
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0000  #wriu -w   0x10121e  0x0000
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01  #wriu -w   0x10121e  0x0c01
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0e00  #wriu -w   0x10121e  0x0e00
WREG (REG_ADDR_BASE + (0x101202 <<1 )) , 0x0000  #wriu -w   0x101202  0x0000
 #
 #//MIU0 Request mask
WREG (REG_ADDR_BASE + (0x1012f8 <<1 )) , 0x8000  #wriu -w   0x1012f8  0x8000
WREG (REG_ADDR_BASE + (0x101246 <<1 )) , 0xFFFE  #wriu -w   0x101246  0xFFFE
WREG (REG_ADDR_BASE + (0x101266 <<1 )) , 0xFFFF  #wriu -w   0x101266  0xFFFF
WREG (REG_ADDR_BASE + (0x101286 <<1 )) , 0xFFFF  #wriu -w   0x101286  0xFFFF
WREG (REG_ADDR_BASE + (0x1012A6 <<1 )) , 0xFFFF  #wriu -w   0x1012A6  0xFFFF
 #
 #//MIU1 Software reset
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0000  #wriu -w   0x10061e  0x0000
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01  #wriu -w   0x10061e  0x0c01
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0e00  #wriu -w   0x10061e  0x0e00
WREG (REG_ADDR_BASE + (0x100602 <<1 )) , 0x0000  #wriu -w   0x100602  0x0000
 #
 #//MIU1 Request mask
WREG (REG_ADDR_BASE + (0x1006f8 <<1 )) , 0x8000  #wriu -w   0x1006f8  0x8000
WREG (REG_ADDR_BASE + (0x100646 <<1 )) , 0xFFFE  #wriu -w   0x100646  0xFFFE
WREG (REG_ADDR_BASE + (0x100666 <<1 )) , 0xFFFF  #wriu -w   0x100666  0xFFFF
WREG (REG_ADDR_BASE + (0x100686 <<1 )) , 0xFFFF  #wriu -w   0x100686  0xFFFF
WREG (REG_ADDR_BASE + (0x1006A6 <<1 )) , 0xFFFF  #wriu -w   0x1006A6  0xFFFF
 #
 #//=================================================================================================
 #// MIU0: 128MB DDR3-1600
 #
WREG (REG_ADDR_BASE + (0x110d3a <<1 )) , 0x0000  #wriu -w   0x110d3a  0x0000      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
 #
WREG (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4002  #wriu -w   0x110d36  0x4002      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0300  #wriu -w   0x110d34  0x0300      // loop_div/input_div
WREG (REG_ADDR_BASE + (0x110d30 <<1 )) , 0x2e8b  #wriu -w   0x110d30  0x2e8b      // ddfset
#if (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x001f  #wriu -w   0x110d32  0x001f      // ddrpll_reset/ddrpll_porst/ddrpl_pd
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x001a  #wriu -w   0x110d32  0x001a      // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0020  #wriu -w   0x110d24  0x0020
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000  #wriu -w   0x110d24  0x0000
 #
DELAYUS 4000 #wait  4                         // delay 4ms
 #
WREG (REG_ADDR_BASE + (0x101202 <<1 )) , 0x03a3  #wriu -w   0x101202  0x03a3      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
WREG (REG_ADDR_BASE + (0x101204 <<1 )) , 0x000B  #wriu -w   0x101204  0x000B      //if I64Mode =0x8b else =0x0b

#if (ENABLE_MEM1300MHz) && (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x101206 <<1 )) , 0x0430  #wriu -w   0x101206  0x0430      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
#else
WREG (REG_ADDR_BASE + (0x101206 <<1 )) , 0x8434  #wriu -w   0x101206  0x0434      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
#endif

#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #wriu -w   0x101208  0x1cbb      //reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2766  #wriu -w   0x10120a  0x2766      //reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ca  #wriu -w   0x10120c  0x96ca      //reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x405a  #wriu -w   0x10120e  0x405a      //tRFC
#elif (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1899  #                                //reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2165  #                                //reg_tRRD
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
	WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0xb6ca  #                                //reg_tWL
	WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x40c0  #                                //tRFC
#else
	WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ba  #                                //reg_tWL
	WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x406b  #                                //tRFC
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb  #                                //reg_tRCD
WREG (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2766  #                                //reg_tRRD
WREG (REG_ADDR_BASE + (0x10120c <<1 )) , 0x96ca  #                                //reg_tWL
WREG (REG_ADDR_BASE + (0x10120e <<1 )) , 0x4080  #                                //tRFC
#endif
WREG (REG_ADDR_BASE + (0x101210 <<1 )) , 0x1c70  #wriu -w   0x101210  0x1c70      //MR0
WREG (REG_ADDR_BASE + (0x101212 <<1 )) , 0x4004  #wriu -w   0x101212  0x4004      //MR1
WREG (REG_ADDR_BASE + (0x101214 <<1 )) , 0x8018  #wriu -w   0x101214  0x8018      //MR2
WREG (REG_ADDR_BASE + (0x101216 <<1 )) , 0xC000  #wriu -w   0x101216  0xC000      //MR3

#if (ENABLE_MEM1300MHz) && (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x101228 <<1 )) , 0xb270  #wriu -w   0x101228  0xb270      //pack_en enable
#else
WREG (REG_ADDR_BASE + (0x101228 <<1 )) , 0xf270  #wriu -w   0x101228  0xF270      //pack_en enable
#endif

WREG (REG_ADDR_BASE + (0x10122c <<1 )) , 0x71C1  #wriu -w   0x10122c  0x71C1      // Address Balance Mode
WREG (REG_ADDR_BASE + (0x101230 <<1 )) , 0x0000  #wriu -w   0x101230  0x0000
WREG (REG_ADDR_BASE + (0x110d54 <<1 )) , 0x0000  #wriu -w   0x110d54  0x0000      //miu_0_atop  start
WREG (REG_ADDR_BASE + (0x110d00 <<1 )) , 0x0411  #wriu -w   0x110d00  0x0411
WREG (REG_ADDR_BASE + (0x110d02 <<1 )) , 0x0000  #wriu -w   0x110d02  0x0000
WREG (REG_ADDR_BASE + (0x110d04 <<1 )) , 0x0080  #wriu -w   0x110d04  0x0080
WREG (REG_ADDR_BASE + (0x110d06 <<1 )) , 0x0000  #wriu -w   0x110d06  0x0000
WREG (REG_ADDR_BASE + (0x110d08 <<1 )) , 0x003F  #wriu -w   0x110d08  0x003F
WREG (REG_ADDR_BASE + (0x110d0a <<1 )) , 0x0000  #wriu -w   0x110d0a  0x0000
WREG (REG_ADDR_BASE + (0x110d0c <<1 )) , 0x0000  #wriu -w   0x110d0c  0x0000
WREG (REG_ADDR_BASE + (0x110d0e <<1 )) , 0x00e5  #wriu -w   0x110d0e  0x00e5
WREG (REG_ADDR_BASE + (0x110d0e <<1 )) , 0x00a5  #wriu -w   0x110d0e  0x00a5
WREG (REG_ADDR_BASE + (0x110d10 <<1 )) , 0x0600  #wriu -w   0x110d10  0x0600
WREG (REG_ADDR_BASE + (0x110d12 <<1 )) , 0x0000  #wriu -w   0x110d12  0x0000
WREG (REG_ADDR_BASE + (0x110d14 <<1 )) , 0x0000  #wriu -w   0x110d14  0x0000
WREG (REG_ADDR_BASE + (0x110d16 <<1 )) , 0x0200  #wriu -w   0x110d16  0x0200
WREG (REG_ADDR_BASE + (0x110d18 <<1 )) , 0x0000  #wriu -w   0x110d18  0x0000
WREG (REG_ADDR_BASE + (0x110d1a <<1 )) , 0x0000  #wriu -w   0x110d1a  0x0000
WREG (REG_ADDR_BASE + (0x110d1c <<1 )) , 0x0000  #wriu -w   0x110d1c  0x0000
 #//wriu -w   0x110d1e  0xffff
WREG (REG_ADDR_BASE + (0x110d20 <<1 )) , 0x0020  #wriu -w   0x110d20  0x0020
WREG (REG_ADDR_BASE + (0x110d22 <<1 )) , 0x0000  #wriu -w   0x110d22  0x0000
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000  #wriu -w   0x110d24  0x0000
WREG (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000  #wriu -w   0x110d24  0x0000
WREG (REG_ADDR_BASE + (0x110d26 <<1 )) , 0x0000  #wriu -w   0x110d26  0x0000

#if (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110d28 <<1 )) , 0x000D  #wriu -w   0x110d28  0x000D
WREG (REG_ADDR_BASE + (0x110d2a <<1 )) , 0x0535  #wriu -w   0x110d2a  0x0535
#else
WREG (REG_ADDR_BASE + (0x110d28 <<1 )) , 0x0012  #wriu -w   0x110d28  0x0012
WREG (REG_ADDR_BASE + (0x110d2a <<1 )) , 0x0458  #wriu -w   0x110d2a  0x0458
#endif

WREG (REG_ADDR_BASE + (0x110d2c <<1 )) , 0x0014  #wriu -w   0x110d2c  0x0014
WREG (REG_ADDR_BASE + (0x110d2e <<1 )) , 0x0000  #wriu -w   0x110d2e  0x0000

#if (ENABLE_MEM1300MHz) && (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110d38 <<1 )) , 0x0045  #wriu -w   0x110d38  0x0045
#else
WREG (REG_ADDR_BASE + (0x110d38 <<1 )) , 0x0044  #wriu -w   0x110d38  0x0044
#endif

WREG (REG_ADDR_BASE + (0x110d3a <<1 )) , 0x0000  #wriu -w   0x110d3a  0x0000
WREG (REG_ADDR_BASE + (0x110d3c <<1 )) , 0x0077  #wriu -w   0x110d3c  0x0077
WREG (REG_ADDR_BASE + (0x110d3e <<1 )) , 0x0000  #wriu -w   0x110d3e  0x0000
WREG (REG_ADDR_BASE + (0x110d40 <<1 )) , 0x0000  #wriu -w   0x110d40  0x0000
WREG (REG_ADDR_BASE + (0x110d42 <<1 )) , 0x0000  #wriu -w   0x110d42  0x0000
WREG (REG_ADDR_BASE + (0x110d44 <<1 )) , 0x0000  #wriu -w   0x110d44  0x0000
WREG (REG_ADDR_BASE + (0x110d46 <<1 )) , 0x0000  #wriu -w   0x110d46  0x0000
WREG (REG_ADDR_BASE + (0x110d48 <<1 )) , 0x0000  #wriu -w   0x110d48  0x0000
WREG (REG_ADDR_BASE + (0x110d4a <<1 )) , 0x0000  #wriu -w   0x110d4a  0x0000
WREG (REG_ADDR_BASE + (0x110d4c <<1 )) , 0x0000  #wriu -w   0x110d4c  0x0000
WREG (REG_ADDR_BASE + (0x110d4e <<1 )) , 0x0000  #wriu -w   0x110d4e  0x0000
WREG (REG_ADDR_BASE + (0x110d50 <<1 )) , 0x0000  #wriu -w   0x110d50  0x0000
WREG (REG_ADDR_BASE + (0x110d52 <<1 )) , 0x0000  #wriu -w   0x110d52  0x0000
WREG (REG_ADDR_BASE + (0x110d54 <<1 )) , 0x0000  #wriu -w   0x110d54  0x0000
WREG (REG_ADDR_BASE + (0x110d56 <<1 )) , 0x0000  #wriu -w   0x110d56  0x0000
WREG (REG_ADDR_BASE + (0x110d58 <<1 )) , 0x0000  #wriu -w   0x110d58  0x0000
WREG (REG_ADDR_BASE + (0x110d5a <<1 )) , 0x0000  #wriu -w   0x110d5a  0x0000
WREG (REG_ADDR_BASE + (0x110d5c <<1 )) , 0x4444  #wriu -w   0x110d5c  0x4444
WREG (REG_ADDR_BASE + (0x110d5e <<1 )) , 0x4444  #wriu -w   0x110d5e  0x4444
WREG (REG_ADDR_BASE + (0x110d60 <<1 )) , 0x2370  #wriu -w   0x110d60  0x2370
WREG (REG_ADDR_BASE + (0x110d62 <<1 )) , 0x0032  #wriu -w   0x110d62  0x0032
WREG (REG_ADDR_BASE + (0x110d64 <<1 )) , 0xf200  #wriu -w   0x110d64  0xf200
WREG (REG_ADDR_BASE + (0x110d66 <<1 )) , 0x0000  #wriu -w   0x110d66  0x0000
WREG (REG_ADDR_BASE + (0x110d68 <<1 )) , 0x0020  #wriu -w   0x110d68  0x0020
WREG (REG_ADDR_BASE + (0x110d6a <<1 )) , 0x0020  #wriu -w   0x110d6a  0x0020
WREG (REG_ADDR_BASE + (0x110d6c <<1 )) , 0x0000  #wriu -w   0x110d6c  0x0000
WREG (REG_ADDR_BASE + (0x110d6e <<1 )) , 0x0088  #wriu -w   0x110d6e  0x0088
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8803  #wriu -w   0x110d72  0x8803
WREG (REG_ADDR_BASE + (0x110d72 <<1 )) , 0x8803  #wriu -w   0x110d72  0x8803
WREG (REG_ADDR_BASE + (0x110d0e <<1 )) , 0x00a5  #wriu -w   0x110d0e  0x00a5      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01  #wriu -w   0x10121e  0x0c01
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c00  #wriu -w   0x10121e  0x0c00
WREG (REG_ADDR_BASE + (0x110d7e <<1 )) , 0x0000  #wriu -w   0x110d7e  0x0000
WREG (REG_ADDR_BASE + (0x110d00 <<1 )) , 0x0401  #wriu -w   0x110d00  0x0401
WREG (REG_ADDR_BASE + (0x110d02 <<1 )) , 0xaaaa  #wriu -w   0x110d02  0xaaaa
 #
 #//=================================================================================================
 #// MIU1: 128MB DDR3-1600
 #
WREG (REG_ADDR_BASE + (0x110dba <<1 )) , 0x0000  #wriu -w   0x110dba  0x0000      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
 #
WREG (REG_ADDR_BASE + (0x110db6 <<1 )) , 0x4001  #wriu -w   0x110db6  0x4001      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
WREG (REG_ADDR_BASE + (0x110db4 <<1 )) , 0x0300  #wriu -w   0x110db4  0x0300      // loop_div/input_div
WREG (REG_ADDR_BASE + (0x110db0 <<1 )) , 0x2e8b  #wriu -w   0x110db0  0x2e8b      // ddfset
#if (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x001f  #wriu -w   0x110db2  0x001f      // ddrpll_reset/ddrpll_porst/ddrpl_pd
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x001a  #wriu -w   0x110db2  0x001a      // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0020  #wriu -w   0x110da4  0x0020
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000  #wriu -w   0x110da4  0x0000
 #
DELAYUS 4000 #wait  4                         // delay 4ms
 #
WREG (REG_ADDR_BASE + (0x100602 <<1 )) , 0x03a3  #wriu -w   0x100602  0x03a3      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
WREG (REG_ADDR_BASE + (0x100604 <<1 )) , 0x000b  #wriu -w   0x100604  0x000b
#if (ENABLE_MEM1300MHz) && (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x100606 <<1 )) , 0x0430  #wriu -w   0x100606  0x0430      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
#else
WREG (REG_ADDR_BASE + (0x100606 <<1 )) , 0x8434  #wriu -w   0x100606  0xb434      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
#endif
#if (ENABLE_MEM1066MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #wriu -w   0x100608  0x1cbb      //reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2766  #wriu -w   0x10060a  0x2766      //reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ca  #wriu -w   0x10060c  0x96ca      //reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x405a  #wriu -w   0x10060e  0x405a      //tRFC
#elif (ENABLE_MEM1300MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1899  #                                //reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2165  #                                //reg_tRRD
#if (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
	WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0xb6ca  #								//reg_tWL
	WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x40c0  #								//tRFC
#else
	WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ba  #                                //reg_tWL
	WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x406b  #                                //tRFC
#endif
#elif (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x100608 <<1 )) , 0x1cbb  #                                //reg_tRCD
WREG (REG_ADDR_BASE + (0x10060a <<1 )) , 0x2766  #                                //reg_tRRD
WREG (REG_ADDR_BASE + (0x10060c <<1 )) , 0x96ca  #                                //reg_tWL
WREG (REG_ADDR_BASE + (0x10060e <<1 )) , 0x4080  #                                //tRFC
#endif
WREG (REG_ADDR_BASE + (0x100610 <<1 )) , 0x1c70  #wriu -w   0x100610  0x1c70      //MR0
WREG (REG_ADDR_BASE + (0x100612 <<1 )) , 0x4004  #wriu -w   0x100612  0x4004      //MR1
WREG (REG_ADDR_BASE + (0x100614 <<1 )) , 0x8018  #wriu -w   0x100614  0x8018      //MR2
WREG (REG_ADDR_BASE + (0x100616 <<1 )) , 0xC000  #wriu -w   0x100616  0xC000      //MR3

#if (ENABLE_MEM1300MHz) && (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x100628 <<1 )) , 0xb270  #wriu -w   0x100628  0xb270      //pack_en enable
#else
WREG (REG_ADDR_BASE + (0x100628 <<1 )) , 0xf270  #wriu -w   0x100628  0xF270      //pack_en enable
#endif

WREG (REG_ADDR_BASE + (0x10062c <<1 )) , 0x71c1  #wriu -w   0x10062c  0x71c1      // Address Balance Mode
WREG (REG_ADDR_BASE + (0x100630 <<1 )) , 0x0000  #wriu -w   0x100630  0x0000
WREG (REG_ADDR_BASE + (0x110dd4 <<1 )) , 0x0000  #wriu -w   0x110dd4  0x0000      //miu_0_atop  start
WREG (REG_ADDR_BASE + (0x110d80 <<1 )) , 0x0411  #wriu -w   0x110d80  0x0411
WREG (REG_ADDR_BASE + (0x110d82 <<1 )) , 0x0000  #wriu -w   0x110d82  0x0000
WREG (REG_ADDR_BASE + (0x110d84 <<1 )) , 0x0080  #wriu -w   0x110d84  0x0080
WREG (REG_ADDR_BASE + (0x110d86 <<1 )) , 0x0000  #wriu -w   0x110d86  0x0000
WREG (REG_ADDR_BASE + (0x110d88 <<1 )) , 0x003F  #wriu -w   0x110d88  0x003F
WREG (REG_ADDR_BASE + (0x110d8a <<1 )) , 0x0000  #wriu -w   0x110d8a  0x0000
WREG (REG_ADDR_BASE + (0x110d8c <<1 )) , 0x0000  #wriu -w   0x110d8c  0x0000
WREG (REG_ADDR_BASE + (0x110d8e <<1 )) , 0x00e5  #wriu -w   0x110d8e  0x00e5
WREG (REG_ADDR_BASE + (0x110d8e <<1 )) , 0x00a5  #wriu -w   0x110d8e  0x00a5
WREG (REG_ADDR_BASE + (0x110d90 <<1 )) , 0x0600  #wriu -w   0x110d90  0x0600
WREG (REG_ADDR_BASE + (0x110d92 <<1 )) , 0x0000  #wriu -w   0x110d92  0x0000
WREG (REG_ADDR_BASE + (0x110d94 <<1 )) , 0x0000  #wriu -w   0x110d94  0x0000
WREG (REG_ADDR_BASE + (0x110d96 <<1 )) , 0x0200  #wriu -w   0x110d96  0x0200
WREG (REG_ADDR_BASE + (0x110d98 <<1 )) , 0x0000  #wriu -w   0x110d98  0x0000
WREG (REG_ADDR_BASE + (0x110d9a <<1 )) , 0x0000  #wriu -w   0x110d9a  0x0000
WREG (REG_ADDR_BASE + (0x110d9c <<1 )) , 0x0000  #wriu -w   0x110d9c  0x0000
#//wriu -w   0x110d9e  0xffff
WREG (REG_ADDR_BASE + (0x110da0 <<1 )) , 0x0020  #wriu -w   0x110da0  0x0020
WREG (REG_ADDR_BASE + (0x110da2 <<1 )) , 0x0000  #wriu -w   0x110da2  0x0000
WREG (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000  #wriu -w   0x110da4  0x0000
WREG (REG_ADDR_BASE + (0x110da6 <<1 )) , 0x0000  #wriu -w   0x110da6  0x0000

#if (ENABLE_MEM1600MHz)
WREG (REG_ADDR_BASE + (0x110da8 <<1 )) , 0x000D  #wriu -w   0x110da8  0x000D
WREG (REG_ADDR_BASE + (0x110daa <<1 )) , 0x0535  #wriu -w   0x110daa  0x0535
#else
WREG (REG_ADDR_BASE + (0x110da8 <<1 )) , 0x0012  #wriu -w   0x110da8  0x0012
WREG (REG_ADDR_BASE + (0x110daa <<1 )) , 0x0458  #wriu -w   0x110daa  0x0458
#endif

WREG (REG_ADDR_BASE + (0x110dac <<1 )) , 0x0014  #wriu -w   0x110dac  0x0014
WREG (REG_ADDR_BASE + (0x110dae <<1 )) , 0x0000  #wriu -w   0x110dae  0x0000

#if (ENABLE_MEM1300MHz) && (ENABLE_MSTAR_KAISERIN_MMAP_512MB_512MB)
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0053  #wriu -w   0x110db8  0x0043
#else
WREG (REG_ADDR_BASE + (0x110db8 <<1 )) , 0x0044  #wriu -w   0x110db8  0x0044
#endif

WREG (REG_ADDR_BASE + (0x110dba <<1 )) , 0x0000  #wriu -w   0x110dba  0x0000
WREG (REG_ADDR_BASE + (0x110dbc <<1 )) , 0x0077  #wriu -w   0x110dbc  0x0077
WREG (REG_ADDR_BASE + (0x110dbe <<1 )) , 0x0000  #wriu -w   0x110dbe  0x0000
WREG (REG_ADDR_BASE + (0x110dc0 <<1 )) , 0x0000  #wriu -w   0x110dc0  0x0000
WREG (REG_ADDR_BASE + (0x110dc2 <<1 )) , 0x0000  #wriu -w   0x110dc2  0x0000
WREG (REG_ADDR_BASE + (0x110dc4 <<1 )) , 0x0000  #wriu -w   0x110dc4  0x0000
WREG (REG_ADDR_BASE + (0x110dc6 <<1 )) , 0x0000  #wriu -w   0x110dc6  0x0000
WREG (REG_ADDR_BASE + (0x110dc8 <<1 )) , 0x0000  #wriu -w   0x110dc8  0x0000
WREG (REG_ADDR_BASE + (0x110dca <<1 )) , 0x0000  #wriu -w   0x110dca  0x0000
WREG (REG_ADDR_BASE + (0x110dcc <<1 )) , 0x0000  #wriu -w   0x110dcc  0x0000
WREG (REG_ADDR_BASE + (0x110dce <<1 )) , 0x0000  #wriu -w   0x110dce  0x0000
WREG (REG_ADDR_BASE + (0x110dd0 <<1 )) , 0x0000  #wriu -w   0x110dd0  0x0000
WREG (REG_ADDR_BASE + (0x110dd2 <<1 )) , 0x0000  #wriu -w   0x110dd2  0x0000
WREG (REG_ADDR_BASE + (0x110dd4 <<1 )) , 0x0000  #wriu -w   0x110dd4  0x0000
WREG (REG_ADDR_BASE + (0x110dd6 <<1 )) , 0x0000  #wriu -w   0x110dd6  0x0000
WREG (REG_ADDR_BASE + (0x110dd8 <<1 )) , 0x0000  #wriu -w   0x110dd8  0x0000
WREG (REG_ADDR_BASE + (0x110dda <<1 )) , 0x0000  #wriu -w   0x110dda  0x0000
WREG (REG_ADDR_BASE + (0x110ddc <<1 )) , 0x4444  #wriu -w   0x110ddc  0x4444
WREG (REG_ADDR_BASE + (0x110dde <<1 )) , 0x4444  #wriu -w   0x110dde  0x4444
WREG (REG_ADDR_BASE + (0x110de0 <<1 )) , 0x2370  #wriu -w   0x110de0  0x2370
WREG (REG_ADDR_BASE + (0x110de2 <<1 )) , 0x0032  #wriu -w   0x110de2  0x0032
WREG (REG_ADDR_BASE + (0x110de4 <<1 )) , 0xf200  #wriu -w   0x110de4  0xf200
WREG (REG_ADDR_BASE + (0x110de6 <<1 )) , 0x0000  #wriu -w   0x110de6  0x0000
WREG (REG_ADDR_BASE + (0x110de8 <<1 )) , 0x0020  #wriu -w   0x110de8  0x0020
WREG (REG_ADDR_BASE + (0x110dea <<1 )) , 0x0020  #wriu -w   0x110dea  0x0020
WREG (REG_ADDR_BASE + (0x110dec <<1 )) , 0x0000  #wriu -w   0x110dec  0x0000
WREG (REG_ADDR_BASE + (0x110dee <<1 )) , 0x0088  #wriu -w   0x110dee  0x0088
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8803  #wriu -w   0x110df2  0x8803
WREG (REG_ADDR_BASE + (0x110df2 <<1 )) , 0x8803  #wriu -w   0x110df2  0x8803
WREG (REG_ADDR_BASE + (0x110d8e <<1 )) , 0x00a5  #wriu -w   0x110d8e  0x00a5       // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01  #wriu -w   0x10061e  0x0c01
WREG (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c00  #wriu -w   0x10061e  0x0c00
 #//wriu -w   0x1012fe  0x0000
WREG (REG_ADDR_BASE + (0x110dfe <<1 )) , 0x0000  #wriu -w   0x110dfe  0x0000
WREG (REG_ADDR_BASE + (0x110d80 <<1 )) , 0x0401  #wriu -w   0x110d80  0x0401
WREG (REG_ADDR_BASE + (0x110d82 <<1 )) , 0xaaaa  #wriu -w   0x110d82  0xaaaa
 #
 #//=================================================================================================
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x0000  #wriu -w   0x101200  0x0000
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x0008  #wriu -w   0x101200  0x0008
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x000c  #wriu -w   0x101200  0x000c
DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x000e  #wriu -w   0x101200  0x000e
DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x101200 <<1 )) , 0x001f  #wriu -w   0x101200  0x001f
DELAYUS 100000 #wait 100                    // delay 100ms
 #
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x0000  #wriu -w   0x100600  0x0000
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x0008  #wriu -w   0x100600  0x0008
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x000c  #wriu -w   0x100600  0x000c
DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x000e  #wriu -w   0x100600  0x000e
DELAYUS 1000 #wait  1                     // delay 1ms
WREG (REG_ADDR_BASE + (0x100600 <<1 )) , 0x001f  #wriu -w   0x100600  0x001f
DELAYUS 100000 #wait  100                   // delay 100ms
 #
 #//=================================================================================================
 #//MIU_Init_Priority
 #//MIU_Set_Group_Priority
 #
WREG (REG_ADDR_BASE + (0x101246 <<1 )) , 0x0000  #wriu -w   0x101246  0x0000   //unmask group0
WREG (REG_ADDR_BASE + (0x101266 <<1 )) , 0x0000  #wriu -w   0x101266  0x0000   //unmask group1
WREG (REG_ADDR_BASE + (0x101286 <<1 )) , 0x0000  #wriu -w   0x101286  0x0000   //unmask group2
WREG (REG_ADDR_BASE + (0x1012A6 <<1 )) , 0x0000  #wriu -w   0x1012A6  0x0000   //mask group3 //jc_db: should u4 have group3
 #
WREG (REG_ADDR_BASE + (0x100646 <<1 )) , 0x0000  #wriu -w   0x100646  0x0000   //unmask group0
WREG (REG_ADDR_BASE + (0x100666 <<1 )) , 0x0000  #wriu -w   0x100666  0x0000   //unmask group1
WREG (REG_ADDR_BASE + (0x100686 <<1 )) , 0x0000  #wriu -w   0x100686  0x0000   //unmask group2
WREG (REG_ADDR_BASE + (0x1006A6 <<1 )) , 0x0000  #wriu -w   0x1006A6  0x0000   //mask group3 //jc_db: should u4 have group3
 # MIU1_GROUP_SELMIU
WREG (REG_ADDR_BASE + (0x1006f0 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x1006f2 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x1006f4 <<1 )) , 0x0400  #bdma
WREG (REG_ADDR_BASE + (0x1006f6 <<1 )) , 0x0000
 #//=================================================================================================
WREG (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c08  #wriu -w   0x10121e  0x0c08      //SW initial done and turn on arbitor
 #
 #
