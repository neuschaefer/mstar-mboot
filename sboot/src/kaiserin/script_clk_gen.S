#swch 4

#<<CLKGEN0>>
WREG (REG_ADDR_BASE + (0x100b02 <<1 )) , 0x0007   # SRAM bist test clk 7:xtal, 6:54M, 5:62M 4:72M 3:86M 2:108M 1:123M 0:144M

#MCU
WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0400   # clk_mcu = 172M (step 1/2)
WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0401   # clk_mcu = 172M (step 2/2)

WREG (REG_ADDR_BASE + (0x101d1e <<1 )) , 0x0021   # clk_ocp ratio and change
WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x0000   # clk_ocp on 400M
                                                  # clk_mips = 800M (step 1/2) (MIPSPLL_VCO)
WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x8000   # clk_mips = 800M (step 2/2) (MIPSPLL_VCO)

WREG (REG_ADDR_BASE + (0x100b28 <<1 )) , 0x0000   # clk_uart1 = 172M (step_1/2)
                                                  # clk_uart2 = 172M (step_1/2)
WREG (REG_ADDR_BASE + (0x100b26 <<1 )) , 0x0c06   # clk_uart0 = 123M
                                                  # clk_uart1 = 172M (step_2/2)
                                                  # clk_uart2 = 172M (step_2/2)

WREG (REG_ADDR_BASE + (0x100b2c <<1 )) , 0x0010   # clk_spi = 54M (step_1/2)
WREG (REG_ADDR_BASE + (0x100b2c <<1 )) , 0x0030   # clk_spi = 54M (step_2/2)

WREG (REG_ADDR_BASE + (0x100b2e <<1 )) , 0x0100   # clk_fuart = 54M
                                                  # uart synthesizer enable

#PCM & TCK
WREG (REG_ADDR_BASE + (0x101e08 <<1 )) , 0x0020   # CLK_TCK_IN from PAD_TS1_SYNC
WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0000   # clk_pcm = 27M
                                                  # clk_tck = CLK_TCK_IN

#MIU
WREG (REG_ADDR_BASE + (0x100b3c <<1 )) , 0x0100   # clk_mpll_syn = 432M (for VEPLL  0: 216M, 1:432M)

WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0018   # clk_miu = 288M
                                                  # clk_miu_rec = 93K (clk_xtal/128)
WREG (REG_ADDR_BASE + (0x100bfc <<1 )) , 0x0001   # clk_ddr_syn = 432M (for MEMPLL  0: 216M, 1:432M)

#VE
WREG (REG_ADDR_BASE + (0x100ba6 <<1 )) , 0x000c   # clk_odclk
WREG (REG_ADDR_BASE + (0x100b48 <<1 )) , 0x0800   # clk_ve = 27M
                                                  # clk_vedac = 108M
WREG (REG_ADDR_BASE + (0x100b4a <<1 )) , 0x001c   # clk_ve_in = 27M (clk_odclk)

#TSP
WREG (REG_ADDR_BASE + (0x101e04 <<1 )) , 0x0001   # CLK_TS0_IN from PAD_TS0_CLK
WREG (REG_ADDR_BASE + (0x100b50 <<1 )) , 0x0000   # clk_ts0 = CLK_TS0_IN
                                                  # clk_ts1 = CLK_TS0_IN
WREG (REG_ADDR_BASE + (0x100b54 <<1 )) , 0x0000   # clk_tsp = 144M
                                                  # clk_stc0 = 27M (STC0_SYNTH_OUT)
WREG (REG_ADDR_BASE + (0x100b58 <<1 )) , 0x0101   # reg_ts1_clk_sample_en = 1
                                                  # reg_ts1_clk_sample_cnt = 1
                                                  # enable TS1 clock delay

#VD_MHEG5
WREG (REG_ADDR_BASE + (0x100b60 <<1 )) , 0x0000   # ckg_vd_mheg5 = 160M

#HVD
WREG (REG_ADDR_BASE + (0x100b62 <<1 )) , 0x0000   # ckg_HVD = 216M

#JPD
WREG (REG_ADDR_BASE + (0x100b6a <<1 )) , 0x000c   # ckg_jpd = 192M (0:72m 4:108m 8:144m c:192m)

#MVD
WREG (REG_ADDR_BASE + (0x100b70 <<1 )) , 0x0000   # mvd_syn off

WREG (REG_ADDR_BASE + (0x100b72 <<1 )) , 0x0400   # clk_mvd = 144M
                                                  # clk_mvd2 = 175M

WREG (REG_ADDR_BASE + (0x100b74 <<1 )) , 0x0000   # clk_mvd_chroma on
                                                  # clk_mvd_luma_a on
WREG (REG_ADDR_BASE + (0x100b76 <<1 )) , 0x0000   # clk_mvd_luma_b on
                                                  # clk_mvd_luma_c on
WREG (REG_ADDR_BASE + (0x100b78 <<1 )) , 0x0000   # clk_mvd_rmem on
                                                  # clk_mvd_rmem1 on

#GOP
WREG (REG_ADDR_BASE + (0x100baa <<1 )) , 0x0010   # clk_idclk_f2
WREG (REG_ADDR_BASE + (0x100b80 <<1 )) , 0x0000   # clk_gopg0 = 27M (clk_odclk)
                                                  # clk_gopg1 = 27M (clk_odclk)
WREG (REG_ADDR_BASE + (0x100b82 <<1 )) , 0x0018   # clk_gopmix = 27M (clk_odclk)
                                                  # clk_gopd = 27M (clk_odclk)
WREG (REG_ADDR_BASE + (0x100b84 <<1 )) , 0x0004   # clk_gopg2 = 27M (clk_idclk)
                                                  # clk_gopg3 = 27M (clk_odclk)
WREG (REG_ADDR_BASE + (0x100b86 <<1 )) , 0x0000   # clk_psram0 on

#GE
WREG (REG_ADDR_BASE + (0x100b90 <<1 )) , 0x0000   # clk_ge = 216M

#STB_DC
WREG (REG_ADDR_BASE + (0x100b98 <<1 )) , 0x0018   # clk_dc0 = 192M

#SC
WREG (REG_ADDR_BASE + (0x100ba2 <<1 )) , 0x0400   # clk_ficlk = 192M (clk_fclk)
WREG (REG_ADDR_BASE + (0x100ba4 <<1 )) , 0x1000   # clk_flck = 192M
WREG (REG_ADDR_BASE + (0x100ba6 <<1 )) , 0x000c   # clk_odclk = 27M (CLK_OUT_DAC/8) (output pixel clock)
WREG (REG_ADDR_BASE + (0x100baa <<1 )) , 0x0010   # clk_idclk = 27M (odclk)
WREG (REG_ADDR_BASE + (0x100bb0 <<1 )) , 0x0c00   # clk_hdgen = 27M (clk_odlck)
                                                  # clk_hdgen_fir = 27M (CLK_OUT_DAC/8)
WREG (REG_ADDR_BASE + (0x100bb2 <<1 )) , 0x000c   # clk_dac1 = 108M (clk_vedac) (SD)
                                                  # clk_dac2 = 27M (clk_hdgen_fir) (HD)
WREG (REG_ADDR_BASE + (0x100bb4 <<1 )) , 0x000c   # clk_dcs27 = 27M

#EMAC
WREG (REG_ADDR_BASE + (0x100bc0 <<1 )) , 0x0000   # clk_emac_ahb = 123M
                                                  # clk_emac_rx = CLK_EMAC_RX_IN
WREG (REG_ADDR_BASE + (0x100bc2 <<1 )) , 0x0000   # clk_emac_tx = CLK_EMAC_TX_IN
                                                  # clk_emac_rx_ref = CLK_EMAC_RX_IN
WREG (REG_ADDR_BASE + (0x100bc4 <<1 )) , 0x0000   # clk_emac_tx_ref = CLK_EMAC_TX_IN

#NAND
WREG (REG_ADDR_BASE + (0x100bc8 <<1 )) , 0x0024   # clk_fice = 54M

#MPIF
WREG (REG_ADDR_BASE + (0x100bd0 <<1 )) , 0x0024   # clk_mpif = 160M


#<<CLK_GEN1>>
#DEMOD
#WREG (REG_ADDR_BASE + (0x103300 <<1 )) , 0x0511   # parallel mode: 0x0511 / serial mode 0x0400
                          # reg_ckg_dvbtmk_ts_out_mode@0x00

#WREG (REG_ADDR_BASE + (0x103308 <<1 )) , 0x0000   # reg_ckg_dvbtc_ts@0x04[11:8] : 8KHz

#WREG (REG_ADDR_BASE + (0x10330c <<1 )) , 0x0000   # reg_ckg_dvbtc_inner1x@0x06[0:0] : DMPLLDIV14/2=31MHz
                          # reg_ckg_dvbtc_inner2x@0x06[8:8] : DMPLLDIV14=62MHz

#WREG (REG_ADDR_BASE + (0x103314 <<1 )) , 0x0000   # reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK=28.8MHz
                          # reg_ckg_demod_dma@0x0a[11:8] : ADC_CLK

#WREG (REG_ADDR_BASE + (0x103316 <<1 )) , 0x0000   # reg_ckg_dvbtc_eq8x@0x0b[0:0] : DMPLLDIV6=144MHz
                          # reg_ckg_dvbtc_eq@0x0b[8:8] : DMPLLDIV6/8=18MHz

#CA
WREG (REG_ADDR_BASE + (0x103348 <<1 )) , 0x0000   # clk_nsk = 123M
                                                  # clk_sm_ca = 27M, clk_sm_ca2 = 27M
WREG (REG_ADDR_BASE + (0x10334a <<1 )) , 0x0000
WREG (REG_ADDR_BASE + (0x10334a <<1 )) , 0x1100

#HDMITX
WREG (REG_ADDR_BASE + (0x103350 <<1 )) , 0x0000   # clk_hdmitx = 27M (clk_odclk)

#MIIC
WREG (REG_ADDR_BASE + (0x103360 <<1 )) , 0x0000   # clk_miic = 24M



.if POWER_SAVING_EN
#Power saving
#DTV w/ external demod
WREG_B (REG_ADDR_BASE + (0x100b24 <<1 )) , 0x01    #clk_aeon
WREG (REG_ADDR_BASE + (0x100b28 <<1 )) , 0x0101  #clk_uart2, clk_uart1
WREG_B (REG_ADDR_BASE + (0x100b2e <<1 )) , 0x01    #clk_fuart
#enalbe PCM clock by default on 98B and 98D
#.if ENABLE_MSTAR_TITANIA_BD_MST128A_D01A
#WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0100  #clk_tck
#.else
#.if ENABLE_MSTAR_TITANIA_BD_MST098B_D01A
#WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0100  #clk_tck
#.else
#.if ENABLE_MSTAR_TITANIA_BD_MST098B_D01B
#WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0100  #clk_tck
#.else
#.if ENABLE_MSTAR_TITANIA_BD_MST098B_D01A_S
#WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0100  #clk_tck
#.else
#.if ENABLE_MSTAR_TITANIA_BD_MST098D_D01A_S
#WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0100  #clk_tck
#.else
WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0100  #clk_tck, clk_pcm
#.endif
#.endif
#.endif
#.endif
#.endif
WREG_B (REG_ADDR_BASE + (0x100b51 <<1 )-1) , 0x01    #clk_ts1
WREG_B (REG_ADDR_BASE + (0x100b52 <<1 )) , 0x01    #clk_ts2
WREG_B (REG_ADDR_BASE + (0x100b6a <<1 )) , 0x01    #clk_jpd
WREG_B (REG_ADDR_BASE + (0x100b73 <<1 )-1) , 0x01    #clk_mvd2
WREG (REG_ADDR_BASE + (0x100b74 <<1 )) , 0x0101  #clk_mvd_luma_a, clk_mvd_chroma
WREG (REG_ADDR_BASE + (0x100b76 <<1 )) , 0x0101  #clk_mvd_luma_c, clk_mvd_luma_b
WREG (REG_ADDR_BASE + (0x100b78 <<1 )) , 0x0101  #clk_mvd_rmem1, clk_mvd_rmem
#WREG_B (REG_ADDR_BASE + (0x100b81 <<1 )-1) , 0x01    #clk_gop1
WREG_B (REG_ADDR_BASE + (0x100b83 <<1 )-1) , 0x01    #clk_gopd
#WREG_B (REG_ADDR_BASE + (0x100b85 <<1 )-1) , 0x01    #clk_gop3
WREG (REG_ADDR_BASE + (0x100bb4 <<1 )) , 0x0101  #clk_dcs27, clk_dcs
WREG_B (REG_ADDR_BASE + (0x100bd0 <<1 )) , 0x01    #clk_mpif
WREG_B (REG_ADDR_BASE + (0x103309 <<1 )-1) , 0x01    #clk_dvbc_ts
WREG (REG_ADDR_BASE + (0x10330c <<1 )) , 0x0101  #clk_dvbtc_inner2x, clk_dvbtc_inner1x
WREG (REG_ADDR_BASE + (0x103314 <<1 )) , 0x0101  #clk_dvbtc_dma, clk_dvbtc_adc
WREG (REG_ADDR_BASE + (0x103316 <<1 )) , 0x0101  #clk_dvbtc_eq, clk_dvbtc_eq8x
WREG_B (REG_ADDR_BASE + (0x103348 <<1 )) , 0x01    #clk_nsk
WREG_B (REG_ADDR_BASE + (0x10334a <<1 )) , 0x11    #clk_sm_ca2, clk_sm_ca1
#WREG_B (REG_ADDR_BASE + (0x103360 <<1 )) , 0x01    #clk_miic

#close miu not used circute:
WREG_B (REG_ADDR_BASE + (0x110DB3 <<1 )-1) , 0xE0
WREG_B (REG_ADDR_BASE + (0x10123E <<1 )-1) , 0x11
WREG_B (REG_ADDR_BASE + (0x10063E <<1 )-1) , 0x11
WREG_B (REG_ADDR_BASE + (0x110DE0 <<1 )) , 0x3C
WREG_B (REG_ADDR_BASE + (0x110DF8 <<1 )) , 0x02
WREG_B (REG_ADDR_BASE + (0x110DF0 <<1 )) , 0x02

#To reduce PAD leakage, RPUPCI_ENZ of padds_pdas16pdg_ti should be 1 initially.
WREG_B (REG_ADDR_BASE + (0x101e46 <<1 )) , 0x3113
                           # [0] : reg_ts1_clk_rpu
                           # [1] : reg_ts1_d3_rpu
                           # [4] : reg_spdif_out_rpu
                           # [8] : reg_i2s_out_sd3_rpu
                           # [12]: reg_et_txd1_rpu
                           # [13]: reg_et_mdio_rpu

#PE of padds_pdas16pdg_ti, padds_pdas08pdg_wvio_fast, padds_pdas08pdg_wvio is pull-enable.
#PS of padds_pdas16pdg_ti, padds_pdas08pdg_wvio_fast, padds_pdas08pdg_wvio is pull-select. (0: pull-low, 1: pull-high)
#DRV of padds_pdas16pdg_ti, padds_pdas08pdg_wvio_fast, padds_pdas08pdg_wvio is driving strength.
WREG_B (REG_ADDR_BASE + (0x101e42 <<1 )) , 0x0000
                           # [2:0]  : {reg_ts1_ps, reg_ts1_pe, reg_ts1_drv}
                           # [6:4]  : {reg_spdif_ps, reg_spdif_pe, reg_spdif_drv}
                           # [10:8] : {reg_i2s_out_ps, reg_i2s_out_pe, reg_i2s_out_drv}
                           # [14:12]: {reg_et_ps, reg_et_pe, reg_et_drv}
.endif
