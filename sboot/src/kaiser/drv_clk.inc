#[*] BOOTROM_MPLL_INIT
@-------------------------------------------------
@Macro: drv_clk_mpll_init
@-------------------------------------------------
.macro drv_clk_mpll_init
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)

    WREG 0x1F206700 0x0010

    //<< RFDAC >>
    WREG   0x1F247484 0x0000    @ Disable RFDAC

    //<< RIU MASK>>
    WREG   0x1F200248 0x6000	@ mask miic0/miic1 xiu ready

    WREG_B 0x1F001C25 0x00	@ dmatop ref_pd=0

    WREG 0x1F206700 0x0011

    @Module: MPLL (0x101E)
    WREG    0x1F203C70, 0x0000      @MPLL 3.3V XTAL Power on, [8] reg_dmdtop_dmd_sel

    WREG 0x1F206700 0x0012

    @Module: DMDANA MPLL (0x1128)
    WREG_B  0x1F224005, 0x00      @[13]reg_dmd_ana_misc_rst    = 0

@-------------------------------------------------
@[2:0]       reg_dmldo_vsel
@[8:4]       reg_dmldo_tst
@[12]        reg_dmldo_pd    = 0
@-------------------------------------------------
    WREG    0x1F2250F0, 0x0000      @mpll
    WREG 0x1F206700 0x0013
@-------------------------------------------------
@[2:0]        reg_mpll_ictrl
@[3]  reg_mpll_in_sel                 1.8V or 3.3V reference clock domain select (1'b0=0==>3.3 V reference clock domain)
@[4]  reg_mpll_xtal2adc_sel           select the XTAL clock bypass to MPLL_ADC_CLK
@[5]  reg_mpll_xtal2next_pll_sel      crystal clock bypass to next PLL select
@[6]  reg_mpll_vco_offset             set VCO initial offset frequency
@[7]  reg_mpll_pd                     gated reference clock and power down PLL analog_3v: 1=power down
@[8]  reg_xtal_en                     XTAL enable register; 1:enable
@[10:9]reg_xtal_sel                   XTAL driven strength select.
@[11] reg_mpll_porst                  MPLL input  power on reset, connect to reg as MPLL_RESET
@[12] reg_mpll_reset                  PLL software reset; 1:reset
@[13] reg_pd_dmpll_clk                XTAL to MPLL clock reference power down
@[14] reg_pd_3p3_1                    XTAL to CLK_24M_3P3_1 power down
@[15] reg_pd_3p3_2                    XTAL to CLK_24M_3P3_2 power down
@-------------------------------------------------
    WREG    0x1F2250D4, 0x0000      @mpll

    WREG 0x1F206700 0x0014
@-------------------------------------------------
@0    0       reg_mpll_clk_dp_pd     dummy
@1    1       reg_adc_clk_pd         ADC output clock power down
@2    2       reg_mpll_div2_pd       MPLL_DIV2 power down
@3    3       reg_mpll_div3_pd       MPLL_DIV3 power down
@4    4       reg_mpll_div4_pd       MPLL_DIV4 power down
@5    5       reg_mpll_div8_pd       MPLL_DIV8 power down
@6    6       reg_mpll_div10_pd      MPLL_DIV10 power down
@7    7       reg_mpll_div5_pd       MPLL_DIV5 power down
@8    8       reg_mpll_div7_pd       MPLL_DIV7 power down
@9    9       reg_mpll_div14_pd      MPLL_DIV14 power down
@15   10      reg_mpll_adc_div_sel   select the ADC clock divide ratio,
@div_ratio=(2^5*b5+2^4*b4+2^3*b3+2^2*b2+2^1*b1+b0);                                                             @[b5:b0]=[000000], div_ratio=64 ADC clk=XTAL_IN * (LOOP_DIV_FIRST*LOOP_DIV_SECOND)/(INPUT_DIV_FIRST*INPUT_DIV_SECOND)/div_ratio
@-------------------------------------------------
    WREG    0x1F2250C0 0x4900   @ MPLL div clocks enable


    WREG    0x1F2250CC 0x1201  @ Loop divider ; VCO = 24*2^2*9 = 864
                              @1    0       reg_mpll_loop_div_first       feedback divider 00:div by 1 01:div by 2 10:div by 4 11:div by 8
                              @15   8       reg_mpll_loop_div_second      feedback divider, div by binary data number


    WREG_B  0x1F001C25 0x01    @ PWDN_REF_pm => reg_ext_xtali_pwdn_ref = 0!!!

    WREG 0x1F206700 0x0015
@=======================================================================================================
@ MIPSPLL
@=======================================================================================================
    WREG    0x1F221800 0x3700         @ Enable PLL
                                          @`RIU_W((`RIUBASE_ANA_MISC>>1)+7'h01, 2'b11, 16'h5300);       @ CPU clock = 12*0x53h = 996 MHz
    @WREG    0x1F221804 0x4b00         @ CPU clock = 12*0x4bh = 900 MHz
    @WREG    0x1F221804 0x4300         @ CPU clock = 12*0x43h = 804 MHz

    .if (CPU_CLOCK == 780)
    WREG    0x1F221804 0x4100        @MIPSPLL enable --> 780MHz for bring up
    .endif

    .if (CPU_CLOCK == 804)
    WREG    0x1F221804 0x4300        @MIPSPLL enable --> 804MHz for bring up
    .endif

    .if (CPU_CLOCK == 840)
    WREG    0x1F221804 0x4600        @MIPSPLL enable --> 840MHz for bring up
    .endif

    .if (CPU_CLOCK == 852)
    WREG    0x1F221804 0x4700        @MIPSPLL enable --> 852MHz for bring up
    .endif

    .if (CPU_CLOCK == 864)
    WREG    0x1F221804 0x4800        @MIPSPLL enable --> 864MHz for bring up
    .endif

    .if (CPU_CLOCK == 876)
    WREG    0x1F221804 0x4900        @MIPSPLL enable --> 876MHz for bring up
    .endif

    .if (CPU_CLOCK == 888)
    WREG    0x1F221804 0x4a00        @MIPSPLL enable --> 888MHz for bring up
    .endif

    .if (CPU_CLOCK == 900)
    WREG    0x1F221804 0x4b00        @MIPSPLL enable --> 900MHz for bring up
    .endif

    .if (CPU_CLOCK == 984)
    WREG    0x1F221804 0x5200        @MIPSPLL enable --> 984MHz for bring up
    .endif

    .if (CPU_CLOCK == 1008)
    WREG    0x1F221804 0x5400        @MIPSPLL enable --> 1008MHz for bring up
    .endif

    WREG 0x1F206700 0x0016
@=======================================================================================================
@ MIUPLL
@=======================================================================================================
    WREG    0x1F221880 0x0003	@ Enable PLL
                                @`RIU_W((`RIUBASE_ANA_MISC_MIU>>1)+7'h01, 2'b11, 16'h3200);
                                @ [15:8] loop_div_second(LDS), default 0x32 = 300 MHz
                                @ clock = 24*LDS/4
#if (ENABLE_MSTAR_MOBF_ENABLE)
     WREG    0x1F221884 0x2000	@ Clock = 24*32/4 = 192 MHz, dramObf and write cache only support MIU_CLK < CLK200MHz
#else
    @WREG    0x1F221884 0x2000	@ Clock = 24*32/4 = 192 MHz
    @WREG    0x1F221884 0x2200	@ Clock = 24*34/4 = 204 MHz
    @WREG    0x1F221884 0x2800	@ Clock = 24*40/4 = 240 MHz
    WREG    0x1F221884 0x3200	@ Clock = 24*50/4 = 300 MHz
    @WREG    0x1F221884 0x3000	@ Clock = 24*50/4 = 288 MHz
#endif

@=======================================================================================================
@ DSPPLL
@=======================================================================================================
    WREG    0x1F221900 0x0003	@ Enable PLL, 360 MHz
                                @`RIU_W((`RIUBASE_ANA_MISC_DSP>>1)+7'h01, 2'b11, 16'h3c00);     @[15:8] loop_div_second(LDS), default 0x3c = 360 MHz
                                                                        @ clock = 24*LDS/4

    WREG    0x1F221904 0x3a00   @ clock = 24*58/4 = 348 MHz

 WREG 0x1F206700 0x0017
@=======================================================================================================
@ HDMIPLL (432 MHz)
@=======================================================================================================
    WREG    0x1F221940 0x001a  @ MPLL_PD=0 ; MPLL_CLK_ADC_VCO_DIV2_PD=0

@=======================================================================================================
@ HDMI TPLL
@=======================================================================================================
    WREG    0x1F004314 0x0001      @  power on synth pll
    WREG    0x1F0042CC 0x0080      @  power on tx pll
    WREG    0x1F0042A8 0x0000      @  power on tm atop
    WREG    0x1F0042B8 0x000f      @  enable tm atp

    WREG    0x1F0042AC 0x0000      @  power on tm atp on tm_reg
    WREG    0x1F0042B0 0x0000      @  power on tm atp on tm_reg

    WREG    0x1F004360 0x0002      @  Enable TM FIFO

    @ hdmitx synthesizer
    WREG_B  0x1F226079 0xff  @ enable_clk_432mhz_hdmitx_synth
                        @`RIU_W  ((`RIUBASE_HDMITX_MISC>>1)+7'h10, 2'b11, Nf_reg[15:0]);
                        @`RIU_W  ((`RIUBASE_HDMITX_MISC>>1)+7'h11, 2'b11, Nf_reg[31:16]);
    WREG    0x1F226040 0x0a21
    WREG    0x1F226044 0x2546

    @Delay 1000;
    DELAYUS     2000
    @ software reset synthesizer
    WREG    0x1F226000 0x0080
    WREG    0x1F226000 0x0000

    @ DR/DC/DAC divider
    @`RIU_W  ((`RIUBASE_HDMITX_PM>>1)+7'h38, 2'b11, {dac_div[2:0], dr_div[4:0], loop_div[3:0], tx_div[1:0], regsel[1:0]});
    WREG    0x1F0042E0 0x6060

    @`RIU_W  ((`RIUBASE_HDMITX_PM>>1)+7'h34, 2'b11, test[15:0]);    @  power on synth pll
    WREG    0x1F0042D0 0x0010    @  power on synth pll
    WREG    0x1F22A3E4 0x0000    @  power on synth pll
    WREG    0x1F0042CC 0x0030    @  power on tx pll

WREG 0x1F206700 0x0018
@=======================================================================================================
@ DACPLL (input*8)
@=======================================================================================================
    WREG_B  0x1F221840 0x04  @ MIPSPLL_OUTPUT_DIV_FIRST[1:0]=2'b01, [4]PD=0
         @`RIU_W( (`RIUBASE_ANA_MISC_DAC>>1) + 7'h01, 2'b11, 16'h4000);  @ clock = input*0x40/8

WREG 0x1F206700 0x0019
@=======================================================================================================
@ GMACPLL (250 MHz)
@=======================================================================================================

        @ Enable GMACPLL, output freuqency is 250MHz
    WREG    0x1F20178C 0x0000 @reg_gmac_gate = 0

    WREG    0x1F2218D0 0x8008 @[15] 1 ssc_en, [14] 0 ssc_mode, [13:12] 00 ddft, [9:0] step 10'h008
                                                                     @ 1000 0000 0000 1000
    WREG    0x1F2218D4 0x0683 @[13:0] span 14'h0683
    WREG    0x1F2218E0 0xbc6a @[15:0] ddfset 16'hbc6a
    WREG    0x1F2218E4 0x0014 @[23:16] ddfset 8'h14
    WREG    0x1F2218C0 0x0019 @
    WREG    0x1F2218CC 0x0007 @ turn on GMACPLL

@=======================================================================================================
@ Enable UTMI PLL clock
@=======================================================================================================

    @Module: usb0 (0x1007)
    WREG_B  0x1F200E00, 0x0a        @Disable MAC initial suspend, Reset UHC
    WREG_B  0x1F200E00, 0x28        @Release UHC reset, enable UHC and OTG XIU function

    @Module: utmi (0x103A)
    WREG    0x1F207544, 0x2088      @ PLL_TEST[30:28]: 3'b010 for IBIAS current select
                                    @ PLL_TEST[23] CLK480 to digital output source selection
    WREG    0x1F207540, 0x8051      @ PLL_TEST[15]: Bypass 480MHz clock divider
                                    @ PLL_TEST[7:4]: 5'b0101_0 for 1.0x
                                    @ PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG    0x1F207504, 0x2084      @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F207510, 0x0000      @ #7=0 Enable band-gap current  #3=0 Disable force_pll_on
    @ 0x0007 for Edison
    WREG    0x1F207510, 0x0007      @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F207500, 0x6bc3      @ reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG    0x1F207500, 0x69c3      @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG    0x1F207500, 0x0001      @ Turn all (including hs_current) use override mode

    @Module: usb1 (0x1007)
    WREG_B  0x1F200F00, 0x0a        @ Disable MAC initial suspend, Reset UHC
    WREG_B  0x1F200F00, 0x28        @ Release UHC reset, enable UHC and OTG XIU function

    @Module: utmi1 (0x103A)
    WREG    0x1F207444, 0x2088      @ PLL_TEST[30:28]: 3'b010 for IBIAS current select
                                    @ PLL_TEST[23] CLK480 to digital output source selection
    WREG    0x1F207440, 0x8051      @ PLL_TEST[15]: Bypass 480MHz clock divider
                                    @ PLL_TEST[7:4]: 5'b0101_0 for 1.0x
                                    @ PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG    0x1F207404, 0x2084      @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F207410, 0x0000      @ Enable band-gap current
    @ modify to 0x0007 for Edison
    WREG    0x1F207410, 0x0007      @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F207400, 0x6bc3      @ reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG    0x1F207400, 0x69c3      @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG    0x1F207400, 0x0001      @ Turn all (including hs_current) use override mode

    @USBC2 <--> UTMI2
    WREG_B  0x1F220400, 0x0a         @ Disable MAC initial suspend, Reset UHC
    WREG_B  0x1F220400, 0x28         @ Release UHC reset, enable UHC and OTG XIU function

    WREG    0x1F205444, 0x2088       @ Set PLL_TEST[23:21] for enable 480MHz clock
    WREG    0x1F205440, 0x8051
    WREG    0x1F205404, 0x2084       @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F205410, 0x0000       @ Enable band-gap current
    @ modify 0x0007 for Edison
    WREG    0x1F205410, 0x0007       @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F205400, 0x6bc3       @ reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS 1000

    WREG    0x1F205400, 0x69c3       @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS 2000

    WREG    0x1F205400, 0x0001       @ Turn all (including hs_current) use override mode


    @Module: USB30 UTMI
    WREG    0x1F245644, 0x2088       @ Set PLL_TEST[23:21] for enable 480MHz clock
    WREG    0x1F245640, 0x8051
    WREG    0x1F245604, 0x2084       @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F245610, 0x0000       @ Enable band-gap current
    WREG    0x1F245610, 0x0007       @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F245600, 0x6bc3       @ reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS 1000

    WREG    0x1F245600, 0x69c3       @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS 2000

    WREG    0x1F245600, 0x0001       @ Turn all (including hs_current) use override mode

    .endif

.endm

#[*] BOOTROM_L2_CLK_RATIO
@-------------------------------------------------
@Macro: drv_clk_L2_clk_ratio
@0x05= 1:2
@0x07= 1:3
@0x09= 1:4
@-------------------------------------------------
.macro drv_clk_L2_clk_ratio
    WREG      0x1F203ADC, 0x0000
    @WREG_B    0x1F203ADC, 0x04	      @mcu:L2 = 2:1
    @WREG_B    0x1F203ADC, 0x05
    WREG_B    0x1F203ADC, 0x02	      @mcu:L2 = 3:2
    WREG_B    0x1F203ADC, 0x03
    WREG      0x16000000, 0x0020
    WREG      0x15000F80, 0x0001
    WFI
    WREG      0x1F201644, 0x8000    @switch to CPU CLK
.endm

@=================================================
@ 002_CLKGEN
@=================================================

#[*] BOOTROM_CLK_GEN0_DVBT_INIT
@-------------------------------------------------
@Macro: drv_clk_gen0_dvbt_init
@-------------------------------------------------
.macro drv_clk_gen0_dvbt_init

@<<CLKGEN_PM>>
    WREG 0x1F001C80 0x1008   @ clk_mcu = 172M (step 1/2)
                             @ clk_spi = 54M (step_1/2)
    WREG 0x1F001C80 0x5088   @ clk_mcu = 172M (step 2/2)
                             @ clk_spi = 54M (step_2/2)
@--------------------------
@<<CLKGEN0>>
@--------------------------
    WREG 0x1F201604 0x0007   @ SRAM bist test clk 7:xtal, 6:62M, 5:86M 4:108M 3:123M 2:144M 1:172M 0:216M

@MCU
    WREG 0x1F201640 0x0400   @ clk_mcu = 172M (step 1/2)
    WREG 0x1F201640 0x0401   @ clk_mcu = 172M (step 2/2)

    WREG 0x1F201644 0x0000   @ clk_ocp on
                            @ clk_mips = 500M (step 1/2) (MIPSPLL_VCO)
    WREG 0x1F201644 0x8000   @ clk_mips = 500M (step 2/2) (MIPSPLL_VCO)

@HK_R2
    WREG 0x1F201648 0x001c   @ clk_aeon_p1 = 240M (step 1/2)
    WREG 0x1F201648 0x009c   @ clk_aeon select clk_aeon_p1 (step 2/2), default clk_xtal


    WREG 0x1F201650 0x0000   @ clk_uart1 = 172M (step_1/2)
                            @ clk_uart2 = 172M (step_1/2)
    WREG 0x1F20164C 0x0c06   @ clk_uart0 = 123M
                            @ clk_uart1 = 172M (step_2/2)
                            @ clk_uart2 = 172M (step_2/2)

    WREG 0x1F201658 0x0010   @ clk_spi = 54M (step_1/2)
    WREG 0x1F201658 0x0030   @ clk_spi = 54M (step_2/2)

    WREG 0x1F20165c 0x0100   @ clk_fuart = 54M
                            @ uart synthesizer enable

@PCM & TCK
    WREG 0x1F203C10 0x0020   @ CLK_TCK_IN from PAD_TS1_SYNC
    WREG 0x1F201668 0x0000   @ clk_pcm = 27M
                            @ clk_tck = CLK_TCK_IN

@MIU
    WREG 0x1F201678 0x0100   @ clk_mpll_syn = 432M (for VEPLL  0: 216M, 1:432M)
    @WREG 0x1F20167C 0x0010   @ clk_miu = 240M (from UTMI)
                            @ clk_miu_rec = 93K (clk_xtal/128)
    @WREG 0x1F20166c 0x8000   @ ckg_miu_256b = 240M (from UTMI)

#if (ENABLE_MSTAR_MOBF_ENABLE)
    WREG 0x1F20167C 0x001C   @ clk_miu = MIU_PLL M (MIUPLL < 200MHz)
                            @ clk_miu_rec = 93K (clk_xtal/128)
    WREG 0x1F20166c 0x8000   @ ckg_miu_256b = 200M (from MEMPLL)
#else
    WREG 0x1F20167C 0x0018   @ clk_miu = 288M (from UTMI)
                            @ clk_miu_rec = 93K (clk_xtal/128)
    WREG 0x1F20166c 0x8000   @ ckg_miu_256b = ?M (from MEMPLL)
#endif

    WREG 0x1F2017F8 0x0001   @ clk_ddr_syn = 432M (for MEMPLL  0: 216M, 1:432M)

@VE
    WREG 0x1F201690 0x0800   @ clk_ve = 27M
                            @ clk_vedac = 108M
    WREG 0x1F201694 0x001c   @ clk_ve_in = 27M (clk_odclk)

@TSP
    WREG 0x1F203C08 0x0001   @ CLK_TS0_IN from PAD_TS0_CLK
    WREG 0x1F2016A0 0x0000   @ clk_ts0 = CLK_TS0_IN
                            @ clk_ts1 = CLK_TS0_IN
    WREG 0x1F2016A8 0x000c   @ clk_tsp = 172M
                            @ clk_stc0 = 27M (STC0_SYNTH_OUT)

@VD_R2
    WREG 0x1F2016C0 0x001c   @ ckg_vd_mheg5 = 240M

@HVD
    WREG 0x1F2016C4 0x0000   @ ckg_hvd = 216M

@MFE
    WREG 0x1F2016D0 0x0008   @ ckg_mfe = 144M (0:123m 4:108m 8:144m c:192m)

@JPD
    WREG 0x1F2016D4 0x0008   @ ckg_jpd = 144M (0:72m 4:108m 8:144m c:192m)

@GPD
    WREG 0x1F2016D8 0x0000   @ ckg_gpd = 216M

@MVD
    WREG 0x1F2016E0 0x0000   @ mvd_syn off

    WREG 0x1F2016E4 0x0000   @ clk_mvd = 144M
                            @ clk_parser = 172M

    WREG 0x1F2016E8 0x0000   @ clk_mvd_chroma on
                            @ clk_mvd_luma_a on
    WREG 0x1F2016EC 0x0000   @ clk_mvd_luma_b on
                            @ clk_mvd_luma_c on
    WREG 0x1F2016F0 0x0000   @ clk_mvd_rmem on
                            @ clk_mvd_rmem1 on

@GOP
    WREG 0x1F201700 0x0000   @ clk_gopg0 = 27M (clk_odclk)
                            @ clk_gopg1 = 27M (clk_odclk)
    WREG 0x1F201704 0x0018   @ clk_gopmix = 27M (clk_ve)
                            @ clk_gopd = 27M (clk_odclk)
    WREG 0x1F201708 0x0004   @ clk_gopg2 = 192M (clk_idclk)
                            @ clk_gopg3 = 27M (clk_odclk)

    WREG 0x1F20170C 0x0000   @ clk_psram0,1,2,3 on

    WREG 0x1F201710 0x1414   @ clk_gopg4 = (clk_sc1_odclk)
                            @ clk_gopg5 = (clk_sc1_odclk)

@GE
    @WREG 0x1F201720 0x000c   @ clk_ge = 240MHz
    @WREG 0x1F201720 0x0008   @ clk_ge = MIUPLL
    WREG 0x1F201720 0x0000    @ clk_ge = 288MHz

@MVOP
    WREG 0x1F201730 0x0018   @ clk_dc0 = 160M

@MVOP SUB
    WREG 0x1F201734 0x0018   @ clk_sub_dc0 = 160M

@SC
    WREG 0x1F201744 0x0400   @ clk_ficlk = 192M (clk_fclk)
    WREG 0x1F201748 0x1000   @ clk_flck = 192M
    WREG 0x1F20174C 0x000c   @ clk_odclk = 27M (CLK_OUT_DAC/8) (output pixel clock)
    WREG 0x1F201754 0x000c   @ clk_idclk = 192M (clk_dc0)
    WREG 0x1F201760 0x0c0c   @ clk_hdgen = 27M (CLK_OUT_DAC/8)
                            @ clk_hdgen_fir = 27M (CLK_OUT_DAC/8)
    WREG 0x1F201764 0x000c   @ clk_dac1 = 108M (clk_vedac) (SD)
                            @ clk_dac2 = 27M (clk_hdgen_fir) (HD)
    WREG 0x1F201768 0x000c   @ clk_dcs = 27M (CLK_OUT_DAC/8)
                            @ clk_dcs27 = 27M

@SC1
    WREG 0x1F2017A8 0x0000   @ clk_sc1_idclk0, clk_sc1_idclk2 on
    WREG 0x1F2017AC 0x0000   @ clk_sc1_sidckl0, clk_sc1_sidclk2, clk_sc1_edclk, clk_sc1_fclk on
    WREG 0x1F2017B0 0x0000   @ clk_sc1_feclk_f2, clk_sc1_feclk2_f2, clk_sc1_odclk on

@EMAC
    WREG 0x1F201780 0x0000   @ clk_emac_ahb = 123M
                            @ clk_emac_rx = CLK_EMAC_RX_IN
    WREG 0x1F201784 0x0000   @ clk_emac_tx = CLK_EMAC_TX_IN
                            @ clk_emac_rx_ref = CLK_EMAC_RX_IN
    WREG 0x1F201788 0x0000   @ clk_emac_tx_ref = CLK_EMAC_TX_IN

@NAND
    WREG 0x1F201790 0x0024   @ clk_fice = 54M

@MPIF
    WREG 0x1F2017A0 0x0000   @ clk_mpif = 123M

@SDIO
    WREG 0x1F2017A4 0x0028   @ clk_sdio = 48M

@--------------------------
@<<CLKGEN1>>
@--------------------------

@CA
    WREG 0x1F206690 0x0000   @ clk_nsk = 123M, clk_cftop = 48M
                            @ clk_sm_ca = 27M, clk_sm_ca2 = 27M

@HDMITX
    WREG 0x1F2066A0 0x0000   @ clk_hdmitx = 27M (clk_odclk)

@MIIC
    WREG 0x1F2066C0 0x0000   @ clk_miic = 24M

@GPU
    @WREG 0x1F2066C4 0x0000   @ clk_gpu = 240M
    WREG 0x1F2066C4 0x000C   @ clk_gpu = MIUPLL

@ BT (disalbe)
    WREG 0x1F2066E8 0x0001   @ disable clk_bt_au_src

@ SATA_AHB
    WREG 0x1F2066EC 0x0004   @ clk_sata_ahb = 216M

@ CH34
    WREG 0x1F2066F0 0x0000   @ clk_rf_src = 432M

.endm

#[*] SPI_CLK
@-------------------------------------------------
@Macro: drv_clk_spi_clk
@-------------------------------------------------
.macro drv_clk_spi_clk

    WREG_B 0x1F0011C4 , 0xFF        @0x0f:cz_high/0x0f:cz_setup/0x0f:cz_hold time set up
    WREG_B 0x1F0011C5 , 0x0F
    WREG_B 0x1F0011C8 , 0x01        @Enable fast read mode, let isp run up to 86Mhz
.endm

#[*] change SPI_CLK
@-------------------------------------------------
@Macro: drv_clk_change_spi_clk
@-------------------------------------------------
.macro drv_clk_change_spi_clk

    WREG_B 0x1F001C81 , 0x04        @step 1/2:set SPI clkgen to 54M
    WREG_B 0x1F001C81 , 0x44        @step 2/2:release SPI_clk from XTAL to clock gen (above line)
    WREG_B 0x1F001C80 , 0x80	    @Set clock of MCU to 170MHz
.endm
