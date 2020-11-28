
// turn on MainPLL, MIPSLL and UPLL
// swch 4

// MainPLL : DMPLL

WREG (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x0000   //reg_dmdtop_dmd_sel@0x1c[8]=0
WREG (REG_ADDR_BASE + (0x112002 <<1 )) , 0x0070   //reg_dmd_ana_misc_rst@0x01[13] reg_dmdtop =0
WREG (REG_ADDR_BASE + (0x112840 <<1 )) , 0x0000   //reg_pwdn_ref@0x20[4]=0
WREG (REG_ADDR_BASE + (0x112818 <<1 )) , 0x0000   //reg_pwdn_adci@0x0c[0]=0, reg_pwdn_adcq@0x0c[1]=0, reg_pwdn_clpbuf@0x0c[2]=0
WREG (REG_ADDR_BASE + (0x112878 <<1 )) , 0x1000   //reg_dmldo_en@0x3c[12]=1
WREG (REG_ADDR_BASE + (0x112860 <<1 )) , 0x2401   //reg_mpll_divX_pd@0x30[9:1]=0, reg_mpll_adc_div_sel@0x30[15:10]=6'h09=6'd09
WREG (REG_ADDR_BASE + (0x112866 <<1 )) , 0x2400   //reg_mpll_loop_div_second@0x33[15:8]=8'h24=8'd36
WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x0604   //reg_mpll_pd@0x35[7]=0

// MIPSPLL
WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0065   //clr bit4, disable power down
WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0045   //clr Bit5, disable reset
WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0005   //clr bit6, disable power reset

.if (CPU_CLOCK == 552)
// 552 MHz
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00C5   //{output_div1,loop_div1,input_div1} //input_div2
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0017   //loop_div2 //output_div2
.else
.if(CPU_CLOCK == 600)
// 600 MHz
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00C5   //{output_div1,loop_div1,input_div1} //input_div2
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0019   //loop_div2 //output_div2
.else
// 696 MHz
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00C5   //{output_div1,loop_div1,input_div1} //input_div2
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x001D   //loop_div2 //output_div2
.endif
.endif

// TXPLL (216Mhz for 480p)
WREG (REG_ADDR_BASE + (0x103350 <<1 )) , 0x0000   // enable clk_hdmi_tx_p
WREG (REG_ADDR_BASE + (0x11303c <<1 )) , 0xffff   // clkgen enable
WREG (REG_ADDR_BASE + (0x11308a <<1 )) , 0x0000   // power on synth pll
WREG (REG_ADDR_BASE + (0x113066 <<1 )) , 0x0000   // power on tx pll
WREG (REG_ADDR_BASE + (0x113054 <<1 )) , 0x0000   // power on tm atop
WREG (REG_ADDR_BASE + (0x11305c <<1 )) , 0x000f   // enable tm atop

WREG (REG_ADDR_BASE + (0x113056 <<1 )) , 0x0000   // power on tm atop on tm_reg
WREG (REG_ADDR_BASE + (0x113058 <<1 )) , 0x0000   // power on tm atop on tm_reg

WREG (REG_ADDR_BASE + (0x113000 <<1 )) , 0x0080   // software reset synthesizer
WREG (REG_ADDR_BASE + (0x113000 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x113100 <<1 )) , 0x0804   // [12]: BYPASS_DC_FIFO, [11]: REG_HPLL_LOCK_CHK, [10]: REG_DC_FIFO_RST, [9:8]: START_DE_PH
                          // [7:6]: REG_DC_MODE, [5]: REG_EN_CLAMP, [4]: PKT_MANUAL_MODE, [3]: REG_USER_ENABLE, [2]: REG_EN_PKT, [1]: REG_PHYMODE, [0]: REG_DVIMODE

// VEPLL
WREG (REG_ADDR_BASE + (0x103100 <<1 )) , 0x0000   //disable power reset
WREG (REG_ADDR_BASE + (0x103106 <<1 )) , 0x0001   //disable reset & power down

// UPLL (turn 480Mhz in USB)
// USBC0 <--> UTMI0
WREG_B (REG_ADDR_BASE + (0x100700 <<1 )) , 0x0a    // Disable MAC initial suspend, Reset UHC
WREG_B (REG_ADDR_BASE + (0x100700 <<1 )) , 0x28    // Release UHC reset, enable UHC and OTG XIU function

WREG_B (REG_ADDR_BASE + (0x103aa2 <<1 )) , 0xa0    // Set PLL_TEST[23:22] for enable 480MHz clock
WREG_B (REG_ADDR_BASE + (0x103aa0 <<1 )) , 0x03    // UTMI offset 0x20 bit1=1//Set PLL_TEST[1] for PLL multiplier 20X
WREG_B (REG_ADDR_BASE + (0x103a82 <<1 )) , 0x84    // Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x103a83 <<1 )-1) , 0x20    // Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x103a89 <<1 )-1) , 0x00    // #3=0 Disable force_pll_on
WREG_B (REG_ADDR_BASE + (0x103a88 <<1 )) , 0x00    // #7=0 Enable band-gap current
WREG_B (REG_ADDR_BASE + (0x103a81 <<1 )-1) , 0x6b    // Turn on reference voltage and regulator
WREG_B (REG_ADDR_BASE + (0x103a80 <<1 )) , 0xc3    // reg_pdn: bit<15>, bit <2> ref_pdn
DELAYUS 1000                  // delay 1ms

WREG_B (REG_ADDR_BASE + (0x103a81 <<1 )-1) , 0x69    // Turn on UPLL, reg_pdn: bit<9>
DELAYUS 2000                  // delay 2ms

WREG_B (REG_ADDR_BASE + (0x103a80 <<1 )) , 0x01    // Turn all (including hs_current) use override mode
WREG_B (REG_ADDR_BASE + (0x103a81 <<1 )-1) , 0x00
WREG_B (REG_ADDR_BASE + (0x103a83 <<1 )-1) , 0x00    //#7=0

WREG_B (REG_ADDR_BASE + (0x103abc <<1 )) , 0x01    // set CA_START as 1
WREG_B (REG_ADDR_BASE + (0x103abc <<1 )) , 0x00    // release CA_START

//WREG_B (REG_ADDR_BASE + (0x103aa1 <<1 )-1) , 0x80    // for port0

// USBC2 <--> UTMI2
WREG_B (REG_ADDR_BASE + (0x110200 <<1 )) , 0x0a    // Disable MAC initial suspend, Reset UHC
WREG_B (REG_ADDR_BASE + (0x110200 <<1 )) , 0x68    // Release UHC reset, enable UHC and OTG XIU function

WREG_B (REG_ADDR_BASE + (0x102a22 <<1 )) , 0xe0    // Set PLL_TEST[23:21] for enable 480MHz clock
WREG   (REG_ADDR_BASE + (0x102a20 <<1 )) , 0x8003  // Set PLL_TEST[1] for PLL multiplier 20X
WREG_B (REG_ADDR_BASE + (0x102a02 <<1 )) , 0x84    // Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x102a03 <<1 )-1) , 0x20
WREG_B (REG_ADDR_BASE + (0x102a09 <<1 )-1) , 0x00    // Disable force_pll_on
WREG_B (REG_ADDR_BASE + (0x102a08 <<1 )) , 0x00    // Enable band-gap current
WREG_B (REG_ADDR_BASE + (0x102a01 <<1 )-1) , 0x6b    // Turn on reference voltage and regulator
WREG_B (REG_ADDR_BASE + (0x102a00 <<1 )) , 0xc3    // reg_pdn: bit<15>, bit <2> ref_pdn
DELAYUS 1000                  // delay 1ms

WREG_B (REG_ADDR_BASE + (0x102a01 <<1 )-1) , 0x69    // Turn on UPLL, reg_pdn: bit<9>
DELAYUS 2000                  // delay 2ms

WREG_B (REG_ADDR_BASE + (0x102a00 <<1 )) , 0x01    // Turn all (including hs_current) use override mode
WREG_B (REG_ADDR_BASE + (0x102a01 <<1 )-1) , 0x00
WREG_B (REG_ADDR_BASE + (0x102a03 <<1 )-1) , 0x00    // #7=0

WREG_B (REG_ADDR_BASE + (0x102a3c <<1 )) , 0x01    // set CA_START as 1
WREG_B (REG_ADDR_BASE + (0x102a3c <<1 )) , 0x00    // release CA_START

//WREG_B (REG_ADDR_BASE + (0x102a21 <<1 )-1) , 0x80    // for port2



