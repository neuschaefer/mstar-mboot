
# turn on MainPLL, MIPSLL and UPLL
#swch 4

# MainPLL : DMPLL
WREG (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x112002 <<1 )) , 0x0070
WREG (REG_ADDR_BASE + (0x112840 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x112818 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x112878 <<1 )) , 0x1000
WREG (REG_ADDR_BASE + (0x112860 <<1 )) , 0x4801
WREG (REG_ADDR_BASE + (0x112866 <<1 )) , 0x2400
WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x0604

# MIPSPLL
WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0065    #clr bit4, disable power down
WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0045    #clr Bit5, disable reset
WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0005    #clr bit6, disable power reset

# CPU frequency = (24*loop_div_first*loop_div_second)/2
.if (CPU_CLOCK == 600)
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00D1    #loop_div_first [2:3]=0 for default 1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0032    #loop_div_second [7:0]=0x32 for default 50
.elseif (CPU_CLOCK == 696)
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00D1    #loop_div_first [2:3]=0 for default 1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x003a    #loop_div_second [7:0]=0x3A for default 58
.elseif (CPU_CLOCK == 792)
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00D1    #loop_div_first [2:3]=0 for default 1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0042    #loop_div_second [7:0]=0x42 for default 66
.elseif (CPU_CLOCK == 840)
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x00D1    #loop_div_first [2:3]=0 for default 1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0046    #loop_div_second [7:0]=0x42 for default 66
.else
.err
.endif


# TXPLL (216Mhz for 480p)
WREG (REG_ADDR_BASE + (0x103350 <<1 )) , 0x0000      # enable clk_hdmi_tx_p
WREG (REG_ADDR_BASE + (0x11303c <<1 )) , 0xffff      # clkgen enable
WREG (REG_ADDR_BASE + (0x11308a <<1 )) , 0x0000      # power on synth pll
WREG (REG_ADDR_BASE + (0x113066 <<1 )) , 0x0000      # power on tx pll
WREG (REG_ADDR_BASE + (0x113054 <<1 )) , 0x0000      # power on tm atop
WREG (REG_ADDR_BASE + (0x11305c <<1 )) , 0x000f      # enable tm atop

WREG (REG_ADDR_BASE + (0x113056 <<1 )) , 0x0000      # power on tm atop on tm_reg
WREG (REG_ADDR_BASE + (0x113058 <<1 )) , 0x0000      # power on tm atop on tm_reg

WREG (REG_ADDR_BASE + (0x113000 <<1 )) , 0x0080      # software reset synthesizer
WREG (REG_ADDR_BASE + (0x113000 <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x113100 <<1 )) , 0x0804      # [12]: BYPASS_DC_FIFO, [11]: REG_HPLL_LOCK_CHK, [10]: REG_DC_FIFO_RST, [9:8]: START_DE_PH
                          # [7:6]: REG_DC_MODE, [5]: REG_EN_CLAMP, [4]: PKT_MANUAL_MODE, [3]: REG_USER_ENABLE, [2]: REG_EN_PKT, [1]: REG_PHYMODE, [0]: REG_DVIMODE


# VEPLL
WREG (REG_ADDR_BASE + (0x103100 <<1 )) , 0x0000      #disable power reset
WREG (REG_ADDR_BASE + (0x103106 <<1 )) , 0x0001      #disable reset & power down

//Patch
WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0001
WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0019
DELAYUS 1000                  # delay 1ms

# UPLL (turn 480Mhz in USB)
# USBC0 <--> UTMI0
WREG_B (REG_ADDR_BASE + (0x100700   <<1 )) , 0x0a    # Disable MAC initial suspend, Reset UHC
WREG_B (REG_ADDR_BASE + (0x100700   <<1 )) , 0x28    # Release UHC reset, enable UHC and OTG XIU function

WREG_B (REG_ADDR_BASE + (0x103aa2   <<1 )) , 0xe0    # Set PLL_TEST[23:22] for enable 480MHz clock
WREG_B (REG_ADDR_BASE + (0x103aa0   <<1 )) , 0x03    # UTMI offset 0x20 bit1=1#Set PLL_TEST[1] for PLL multiplier 20X
WREG_B (REG_ADDR_BASE + (0x103a82   <<1 )) , 0x84    # Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x103a83   <<1 )-1) , 0x20    # Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x103a89   <<1 )-1) , 0x00    # #3=0 Disable force_pll_on
WREG_B (REG_ADDR_BASE + (0x103a88   <<1 )) , 0x00    # #7=0 Enable band-gap current
WREG_B (REG_ADDR_BASE + (0x103a81   <<1 )-1) , 0x6b    # Turn on reference voltage and regulator
WREG_B (REG_ADDR_BASE + (0x103a80   <<1 )) , 0xc3    # reg_pdn: bit<15>, bit <2> ref_pdn
DELAYUS 1000                  # delay 1ms

WREG_B (REG_ADDR_BASE + (0x103a81   <<1 )-1) , 0x69    # Turn on UPLL, reg_pdn: bit<9>
DELAYUS 2000                  # delay 2ms

WREG_B (REG_ADDR_BASE + (0x103a80   <<1 )) , 0x01    # Turn all (including hs_current) use override mode
WREG_B (REG_ADDR_BASE + (0x103a81   <<1 )-1) , 0x00
WREG_B (REG_ADDR_BASE + (0x103a83   <<1 )-1) , 0x00    ##7=0

WREG_B (REG_ADDR_BASE + (0x103abc   <<1 )) , 0x01    # set CA_START as 1
WREG_B (REG_ADDR_BASE + (0x103abc   <<1 )) , 0x00    # release CA_START

# USBC1 <--> UTMI1
WREG_B (REG_ADDR_BASE + (0x100780   <<1 )) , 0x0a    # Disable MAC initial suspend, Reset UHC
WREG_B (REG_ADDR_BASE + (0x100780   <<1 )) , 0x28    # Release UHC reset, enable UHC and OTG XIU function

WREG_B (REG_ADDR_BASE + (0x103a22   <<1 )) , 0xe0    # Set PLL_TEST[23:21] for enable 480MHz clock
WREG_B (REG_ADDR_BASE + (0x103a20   <<1 )) , 0x03    # Set PLL_TEST[1] for PLL multiplier 20X
WREG_B (REG_ADDR_BASE + (0x103a02   <<1 )) , 0x84    # Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x103a03   <<1 )-1) , 0x20
WREG_B (REG_ADDR_BASE + (0x103a09   <<1 )-1) , 0x00    # Disable force_pll_on
WREG_B (REG_ADDR_BASE + (0x103a08   <<1 )) , 0x00    # Enable band-gap current
WREG_B (REG_ADDR_BASE + (0x103a01   <<1 )-1) , 0x6b    # Turn on reference voltage and regulator
WREG_B (REG_ADDR_BASE + (0x103a00   <<1 )) , 0xc3    # reg_pdn: bit<15>, bit <2> ref_pdn
DELAYUS 1000                  # delay 1ms

WREG_B (REG_ADDR_BASE + (0x103a01   <<1 )-1) , 0x69    # Turn on UPLL, reg_pdn: bit<9>
DELAYUS 2000                  # delay 2ms

WREG_B (REG_ADDR_BASE + (0x103a00   <<1 )) , 0x01    # Turn all (including hs_current) use override mode
WREG_B (REG_ADDR_BASE + (0x103a01   <<1 )-1) , 0x00
WREG_B (REG_ADDR_BASE + (0x103a03   <<1 )-1) , 0x00    # #7=0

WREG_B (REG_ADDR_BASE + (0x103a3c   <<1 )) , 0x01    # set CA_START as 1
WREG_B (REG_ADDR_BASE + (0x103a3c   <<1 )) , 0x00    # release CA_START

# USBC2 <--> UTMI2
WREG_B (REG_ADDR_BASE + (0x110200   <<1 )) , 0x0a    # Disable MAC initial suspend, Reset UHC
WREG_B (REG_ADDR_BASE + (0x110200   <<1 )) , 0x68    # Release UHC reset, enable UHC and OTG XIU function

WREG_B (REG_ADDR_BASE + (0x102a22   <<1 )) , 0xe0    # Set PLL_TEST[23:21] for enable 480MHz clock
WREG_B (REG_ADDR_BASE + (0x102a20   <<1 )) , 0x03    # Set PLL_TEST[1] for PLL multiplier 20X
WREG_B (REG_ADDR_BASE + (0x102a02   <<1 )) , 0x84    # Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x102a03   <<1 )-1) , 0x20
WREG_B (REG_ADDR_BASE + (0x102a09   <<1 )-1) , 0x00    # Disable force_pll_on
WREG_B (REG_ADDR_BASE + (0x102a08   <<1 )) , 0x00    # Enable band-gap current
WREG_B (REG_ADDR_BASE + (0x102a01   <<1 )-1) , 0x6b    # Turn on reference voltage and regulator
WREG_B (REG_ADDR_BASE + (0x102a00   <<1 )) , 0xc3    # reg_pdn: bit<15>, bit <2> ref_pdn
DELAYUS 1000                  # delay 1ms

WREG_B (REG_ADDR_BASE + (0x102a01   <<1 )-1) , 0x69    # Turn on UPLL, reg_pdn: bit<9>
DELAYUS 2000                  # delay 2ms

WREG_B (REG_ADDR_BASE + (0x102a00   <<1 )) , 0x01    # Turn all (including hs_current) use override mode
WREG_B (REG_ADDR_BASE + (0x102a01   <<1 )-1) , 0x00
WREG_B (REG_ADDR_BASE + (0x102a03   <<1 )-1) , 0x00    # #7=0

WREG_B (REG_ADDR_BASE + (0x102a3c   <<1 )) , 0x01    # set CA_START as 1
WREG_B (REG_ADDR_BASE + (0x102a3c   <<1 )) , 0x00    # release CA_START

# USBC3 <--> UTMI3
WREG_B (REG_ADDR_BASE + (0x120800   <<1 )) , 0x0a    # Disable MAC initial suspend, Reset UHC
WREG_B (REG_ADDR_BASE + (0x120800   <<1 )) , 0x68    # Release UHC reset, enable UHC and OTG XIU function

WREG_B (REG_ADDR_BASE + (0x120a22   <<1 )) , 0xe0    # Set PLL_TEST[23:21] for enable 480MHz clock
WREG_B (REG_ADDR_BASE + (0x120a20   <<1 )) , 0x03    # Set PLL_TEST[1] for PLL multiplier 20X
WREG_B (REG_ADDR_BASE + (0x120a02   <<1 )) , 0x84    # Enable CLK12_SEL bit <2> for select low voltage crystal clock
WREG_B (REG_ADDR_BASE + (0x120a03   <<1 )-1) , 0x20
WREG_B (REG_ADDR_BASE + (0x120a09   <<1 )-1) , 0x00    # Disable force_pll_on
WREG_B (REG_ADDR_BASE + (0x120a08   <<1 )) , 0x00    # Enable band-gap current
WREG_B (REG_ADDR_BASE + (0x120a01   <<1 )-1) , 0x6b    # Turn on reference voltage and regulator
WREG_B (REG_ADDR_BASE + (0x120a00   <<1 )) , 0xc3    # reg_pdn: bit<15>, bit <2> ref_pdn
DELAYUS 1000                  # delay 1ms

WREG_B (REG_ADDR_BASE + (0x120a01   <<1 )-1) , 0x69    # Turn on UPLL, reg_pdn: bit<9>
DELAYUS 2000                  # delay 2ms

WREG_B (REG_ADDR_BASE + (0x120a00   <<1 )) , 0x01    # Turn all (including hs_current) use override mode
WREG_B (REG_ADDR_BASE + (0x120a01   <<1 )-1) , 0x00
WREG_B (REG_ADDR_BASE + (0x120a03   <<1 )-1) , 0x00    # #7=0

WREG_B (REG_ADDR_BASE + (0x120a3c   <<1 )) , 0x01    # set CA_START as 1
WREG_B (REG_ADDR_BASE + (0x120a3c   <<1 )) , 0x00    # release CA_START

.if (ENABLE_GREENWICH == 1)
WREG  (REG_ADDR_BASE + (0x112810 <<1 )) , 0x0200    # bit 9 enable Greenwich clock
WREG  (REG_ADDR_BASE + (0x112818 <<1 )) , 0x0005    # Power off AVDD33_ADC
.endif

.if 0
# Power-Saving
# disable port0
WREG_B (REG_ADDR_BASE + (0x103a88   <<1 )) , 0x83
WREG_B (REG_ADDR_BASE + (0x103a82   <<1 )) , 0x80
WREG_B (REG_ADDR_BASE + (0x103a83   <<1 )-1) , 0x90
WREG_B (REG_ADDR_BASE + (0x103a80   <<1 )) , 0xc7
WREG_B (REG_ADDR_BASE + (0x103a81   <<1 )-1) , 0xff
WREG_B (REG_ADDR_BASE + (0x100700   <<1 )) , 0x00
WREG_B (REG_ADDR_BASE + (0x100702   <<1 )) , 0x00
# disable port1
WREG_B (REG_ADDR_BASE + (0x103a08   <<1 )) , 0x83
WREG_B (REG_ADDR_BASE + (0x103a02   <<1 )) , 0x80
WREG_B (REG_ADDR_BASE + (0x103a03   <<1 )-1) , 0x90
WREG_B (REG_ADDR_BASE + (0x103a00   <<1 )) , 0xc7
WREG_B (REG_ADDR_BASE + (0x103a01   <<1 )-1) , 0xff
WREG_B (REG_ADDR_BASE + (0x100780   <<1 )) , 0x00
WREG_B (REG_ADDR_BASE + (0x100782   <<1 )) , 0x00
# disable port3
WREG_B (REG_ADDR_BASE + (0x120a08   <<1 )) , 0x83
WREG_B (REG_ADDR_BASE + (0x120a02   <<1 )) , 0x80
WREG_B (REG_ADDR_BASE + (0x120a03   <<1 )-1) , 0x90
WREG_B (REG_ADDR_BASE + (0x120a00   <<1 )) , 0xc7
WREG_B (REG_ADDR_BASE + (0x120a01   <<1 )-1) , 0xff
WREG_B (REG_ADDR_BASE + (0x120800   <<1 )) , 0x00
WREG_B (REG_ADDR_BASE + (0x120802   <<1 )) , 0x00
.endif

 #swch 4

 #//=====================================
 #//Module: chiptop (0x101E)
WREG (REG_ADDR_BASE + (0x110c80 <<1 )) , 0x000b #wriu -w 0x110c80    0x000b
WREG (REG_ADDR_BASE + (0x110c30 <<1 )) , 0x0065 #wriu -w 0x110c30    0x0065
WREG (REG_ADDR_BASE + (0x110c30 <<1 )) , 0x0045 #wriu -w 0x110c30    0x0045
WREG (REG_ADDR_BASE + (0x110c30 <<1 )) , 0x0005 #wriu -w 0x110c30    0x0005
WREG_B (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x00 #wriu    0x101e38    0x00
WREG_B (REG_ADDR_BASE + (0x101e39 <<1 )-1) , 0x00 #wriu    0x101e39    0x00
WREG_B (REG_ADDR_BASE + (0x112003 <<1 )-1) , 0x00 #wriu    0x112003    0x00
WREG (REG_ADDR_BASE + (0x112878 <<1 )) , 0x1000 #wriu -w 0x112878    0x1000
WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x0004 #wriu -w 0x11286a    0x0004
#WREG (REG_ADDR_BASE + (0x112860 <<1 )) , 0x4800 #wriu -w 0x112860    0x4800
WREG (REG_ADDR_BASE + (0x112860 <<1 )) , 0x4803 #wriu -w 0x112860    0x4803
WREG (REG_ADDR_BASE + (0x112866 <<1 )) , 0x2400 #wriu -w 0x112866    0x2400
WREG (REG_ADDR_BASE + (0x112802 <<1 )) , 0x0446 #wriu -w 0x112802    0x0446
#WREG (REG_ADDR_BASE + (0x112818 <<1 )) , 0x0000 #wriu -w 0x112818    0x0000
WREG (REG_ADDR_BASE + (0x112818 <<1 )) , 0x0005 #wriu -w 0x112818    0x0005
WREG (REG_ADDR_BASE + (0x112840 <<1 )) , 0x0000 #wriu -w 0x112840    0x0000

 #swch 3
WREG_B (REG_ADDR_BASE + (0x000e13 <<1 )-1) , 0x01 #wriu    0x000e13    0x01

 #swch 4
WREG (REG_ADDR_BASE + (0x100b00 <<1 )) , 0x0004 #wriu -w 0x100b00    0x0004
WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0000 #wriu -w 0x100b3e    0x0000
 #//=====================================

// Albany
 #swch 3
WREG_B (REG_ADDR_BASE + (0x0032fc <<1 )) , 0x00 #wriu    0x0032fc    0x00    // Power-on LDO
WREG_B (REG_ADDR_BASE + (0x0032b7 <<1 )-1) , 0x07 #wriu    0x0032b7    0x07    // Power-on ADC
WREG_B (REG_ADDR_BASE + (0x0032cb <<1 )-1) , 0x11 #wriu    0x0032cb    0x11    // Power-on BGAP
WREG_B (REG_ADDR_BASE + (0x0032cc <<1 )) , 0x80 #wriu    0x0032cc    0x80    // Power-on ADCPL
WREG_B (REG_ADDR_BASE + (0x0032cd <<1 )-1) , 0xd1 #wriu    0x0032cd    0xd1    // Power-on ADCPL
WREG_B (REG_ADDR_BASE + (0x0032d4 <<1 )) , 0x00 #wriu    0x0032d4    0x00    // Power-on LPF_OP
WREG_B (REG_ADDR_BASE + (0x0032b9 <<1 )-1) , 0x40 #wriu    0x0032b9    0x40    // Power-on LPF
WREG_B (REG_ADDR_BASE + (0x0032bb <<1 )-1) , 0x05 #wriu    0x0032bb    0x05    // Power-on REF
WREG (REG_ADDR_BASE + (0x0032b0 <<1 )) , 0x6002 #wriu -w 0x0032b0    0x6002  // Power-on TX

 #// LED


 # swch 3
 #
 # // ltp
WREG_B (REG_ADDR_BASE + (0x00311e <<1 )) , 0x00 # wriu 0x00311e 0x00
WREG_B (REG_ADDR_BASE + (0x00311f <<1 )-1) , 0x98 # wriu 0x00311f 0x98
WREG_B (REG_ADDR_BASE + (0x003120 <<1 )) , 0x84 # wriu 0x003120 0x84
WREG_B (REG_ADDR_BASE + (0x003121 <<1 )-1) , 0x84 # wriu 0x003121 0x84
WREG_B (REG_ADDR_BASE + (0x003122 <<1 )) , 0x88 # wriu 0x003122 0x88
WREG_B (REG_ADDR_BASE + (0x003123 <<1 )-1) , 0x88 # wriu 0x003123 0x88
WREG_B (REG_ADDR_BASE + (0x003124 <<1 )) , 0x8c # wriu 0x003124 0x8c
WREG_B (REG_ADDR_BASE + (0x003125 <<1 )-1) , 0x8c # wriu 0x003125 0x8c
WREG_B (REG_ADDR_BASE + (0x003126 <<1 )) , 0x98 # wriu 0x003126 0x98
WREG_B (REG_ADDR_BASE + (0x003127 <<1 )-1) , 0xc8 # wriu 0x003127 0xc8
WREG_B (REG_ADDR_BASE + (0x003128 <<1 )) , 0x00 # wriu 0x003128 0x00
WREG_B (REG_ADDR_BASE + (0x003129 <<1 )-1) , 0x00 # wriu 0x003129 0x00
WREG_B (REG_ADDR_BASE + (0x00312a <<1 )) , 0x00 # wriu 0x00312a 0x00
WREG_B (REG_ADDR_BASE + (0x00312b <<1 )-1) , 0x10 # wriu 0x00312b 0x10
WREG_B (REG_ADDR_BASE + (0x00312c <<1 )) , 0x00 # wriu 0x00312c 0x00
 #
 # // tin
WREG_B (REG_ADDR_BASE + (0x003188 <<1 )) , 0x3c # wriu 0x003188 0x3c
WREG_B (REG_ADDR_BASE + (0x003189 <<1 )-1) , 0x3c # wriu 0x003189 0x3c
WREG_B (REG_ADDR_BASE + (0x00318a <<1 )) , 0x3c # wriu 0x00318a 0x3c
WREG_B (REG_ADDR_BASE + (0x00318b <<1 )-1) , 0x3c # wriu 0x00318b 0x3c
WREG_B (REG_ADDR_BASE + (0x00318c <<1 )) , 0x30 # wriu 0x00318c 0x30
WREG_B (REG_ADDR_BASE + (0x00318d <<1 )-1) , 0x3c # wriu 0x00318d 0x3c
WREG_B (REG_ADDR_BASE + (0x00318e <<1 )) , 0x7c # wriu 0x00318e 0x7c
WREG_B (REG_ADDR_BASE + (0x00318f <<1 )-1) , 0x68 # wriu 0x00318f 0x68
WREG_B (REG_ADDR_BASE + (0x003190 <<1 )) , 0x34 # wriu 0x003190 0x34
WREG_B (REG_ADDR_BASE + (0x003191 <<1 )-1) , 0x78 # wriu 0x003191 0x78
WREG_B (REG_ADDR_BASE + (0x003192 <<1 )) , 0x94 # wriu 0x003192 0x94
WREG_B (REG_ADDR_BASE + (0x003193 <<1 )-1) , 0xd4 # wriu 0x003193 0xd4
WREG_B (REG_ADDR_BASE + (0x003194 <<1 )) , 0xa0 # wriu 0x003194 0xa0
WREG_B (REG_ADDR_BASE + (0x003195 <<1 )-1) , 0x84 # wriu 0x003195 0x84
WREG_B (REG_ADDR_BASE + (0x003196 <<1 )) , 0xc8 # wriu 0x003196 0xc8
WREG_B (REG_ADDR_BASE + (0x003197 <<1 )-1) , 0xe4 # wriu 0x003197 0xe4
WREG_B (REG_ADDR_BASE + (0x003198 <<1 )) , 0xc8 # wriu 0x003198 0xc8
WREG_B (REG_ADDR_BASE + (0x003199 <<1 )-1) , 0xc8 # wriu 0x003199 0xc8
WREG_B (REG_ADDR_BASE + (0x00319a <<1 )) , 0xe8 # wriu 0x00319a 0xe8
WREG_B (REG_ADDR_BASE + (0x00319b <<1 )-1) , 0xc8 # wriu 0x00319b 0xc8
WREG_B (REG_ADDR_BASE + (0x00319c <<1 )) , 0x3c # wriu 0x00319c 0x3c
WREG_B (REG_ADDR_BASE + (0x00319d <<1 )-1) , 0x3c # wriu 0x00319d 0x3c
WREG_B (REG_ADDR_BASE + (0x00319e <<1 )) , 0x3c # wriu 0x00319e 0x3c
WREG_B (REG_ADDR_BASE + (0x00319f <<1 )-1) , 0x3c # wriu 0x00319f 0x3c
WREG_B (REG_ADDR_BASE + (0x0031a0 <<1 )) , 0x30 # wriu 0x0031a0 0x30
WREG_B (REG_ADDR_BASE + (0x0031a1 <<1 )-1) , 0x24 # wriu 0x0031a1 0x24
WREG_B (REG_ADDR_BASE + (0x0031a2 <<1 )) , 0x7c # wriu 0x0031a2 0x7c
WREG_B (REG_ADDR_BASE + (0x0031a3 <<1 )-1) , 0x70 # wriu 0x0031a3 0x70
WREG_B (REG_ADDR_BASE + (0x0031a4 <<1 )) , 0x20 # wriu 0x0031a4 0x20
WREG_B (REG_ADDR_BASE + (0x0031a5 <<1 )-1) , 0x64 # wriu 0x0031a5 0x64
WREG_B (REG_ADDR_BASE + (0x0031a6 <<1 )) , 0xa0 # wriu 0x0031a6 0xa0
WREG_B (REG_ADDR_BASE + (0x0031a7 <<1 )-1) , 0xd4 # wriu 0x0031a7 0xd4
WREG_B (REG_ADDR_BASE + (0x0031a8 <<1 )) , 0x98 # wriu 0x0031a8 0x98
WREG_B (REG_ADDR_BASE + (0x0031a9 <<1 )-1) , 0x84 # wriu 0x0031a9 0x84
WREG_B (REG_ADDR_BASE + (0x0031aa <<1 )) , 0xc8 # wriu 0x0031aa 0xc8
WREG_B (REG_ADDR_BASE + (0x0031ab <<1 )-1) , 0xd0 # wriu 0x0031ab 0xd0
WREG_B (REG_ADDR_BASE + (0x0031ac <<1 )) , 0xc8 # wriu 0x0031ac 0xc8
WREG_B (REG_ADDR_BASE + (0x0031ad <<1 )-1) , 0xc8 # wriu 0x0031ad 0xc8
WREG_B (REG_ADDR_BASE + (0x0031ae <<1 )) , 0xc8 # wriu 0x0031ae 0xc8
WREG_B (REG_ADDR_BASE + (0x0031af <<1 )-1) , 0xc8 # wriu 0x0031af 0xc8
 #
