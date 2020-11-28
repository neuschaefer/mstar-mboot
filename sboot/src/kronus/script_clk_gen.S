//swch 4

//<<CLKGEN_PM>>
WREG (REG_ADDR_BASE + (0x000e40 <<1 )) , 0x1008   // clk_mcu = 172M (step 1/2)
                          // clk_spi = 54M (step_1/2)
// WREG (REG_ADDR_BASE + (0x000e40 <<1 )) , 0x5088   // clk_mcu = 172M (step 2/2)
                          // clk_spi = 54M (step_2/2)


//<<CLKGEN0>>
WREG (REG_ADDR_BASE + (0x100b02 <<1 )) , 0x0007   // SRAM bist test clk 7:xtal, 6:62M, 5:86M 4:108M 3:123M 2:144M 1:172M 0:216M

//MCU
WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0400   // clk_mcu = 172M (step 1/2)
WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0401   // clk_mcu = 172M (step 2/2)

WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x0000   // clk_ocp on
                          // clk_mips = 500M (step 1/2) (MIPSPLL_VCO)
WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x8000   // clk_mips = 500M (step 2/2) (MIPSPLL_VCO)


WREG (REG_ADDR_BASE + (0x100b28 <<1 )) , 0x0000   // clk_uart1 = 172M (step_1/2)
                          // clk_uart2 = 172M (step_1/2)
WREG (REG_ADDR_BASE + (0x100b26 <<1 )) , 0x0c06   // clk_uart0 = 123M
                          // clk_uart1 = 172M (step_2/2)
                          // clk_uart2 = 172M (step_2/2)

WREG (REG_ADDR_BASE + (0x100b2c <<1 )) , 0x0010   // clk_spi = 54M (step_1/2)
WREG (REG_ADDR_BASE + (0x100b2c <<1 )) , 0x0030   // clk_spi = 54M (step_2/2)

WREG (REG_ADDR_BASE + (0x100b2e <<1 )) , 0x0100   // clk_fuart = 54M
                          // uart synthesizer enable

//PCM & TCK
WREG (REG_ADDR_BASE + (0x101e08 <<1 )) , 0x0020   // CLK_TCK_IN from PAD_TS1_SYNC
WREG (REG_ADDR_BASE + (0x100b34 <<1 )) , 0x0000   // clk_pcm = 27M
                          // clk_tck = CLK_TCK_IN

//MIU
.if (ENABLE_MEM1066MHz == 1)
WREG (REG_ADDR_BASE + (0x100b3c <<1 )) , 0x0102   // clk_mpll_syn = 432M (for VEPLL  0: 216M, 1:432M)
                                             //reg_ckg_mempll => select mempll0_clk05x
WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0000   // clk_miu = MEMPLL out, DDR2 1/4 mode -> 1066/4 = 266
.else
WREG (REG_ADDR_BASE + (0x100b3c <<1 )) , 0x0100   // clk_mpll_syn = 432M (for VEPLL  0: 216M, 1:432M)
WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0010   // clk_miu = 240M
.endif
WREG (REG_ADDR_BASE + (0x100bfc <<1 )) , 0x0001   // clk_ddr_syn = 432M (for MEMPLL  0: 216M, 1:432M)

//VE
WREG (REG_ADDR_BASE + (0x100b48 <<1 )) , 0x0800   // clk_ve = 27M
                          // clk_vedac = 108M
WREG (REG_ADDR_BASE + (0x100b4a <<1 )) , 0x001c   // clk_ve_in = 27M (clk_odclk)

//TSP
WREG (REG_ADDR_BASE + (0x101e04 <<1 )) , 0x0001   // CLK_TS0_IN from PAD_TS0_CLK
WREG (REG_ADDR_BASE + (0x100b50 <<1 )) , 0x0000   // clk_ts0 = CLK_TS0_IN
                          // clk_ts1 = CLK_TS0_IN
WREG (REG_ADDR_BASE + (0x100b54 <<1 )) , 0x0000   // clk_tsp = 144M
                          // clk_stc0 = 27M (STC0_SYNTH_OUT)

//VD_MHEG5
WREG (REG_ADDR_BASE + (0x100b60 <<1 )) , 0x0000   // ckg_vd_mheg5 = 160M

//HVD
WREG (REG_ADDR_BASE + (0x100b62 <<1 )) , 0x0004   // ckg_HVD = 160M

//JPD
WREG (REG_ADDR_BASE + (0x100b6a <<1 )) , 0x0008   // ckg_jpg = 144M (0:72m 4:108m 8:144m c:192m)

//MVD
WREG (REG_ADDR_BASE + (0x100b70 <<1 )) , 0x0000   // mvd_syn off

WREG (REG_ADDR_BASE + (0x100b72 <<1 )) , 0x0400   // clk_mvd = 144M
                          // clk_mvd2 = 144M

WREG (REG_ADDR_BASE + (0x100b74 <<1 )) , 0x0000   // clk_mvd_chroma on
                          // clk_mvd_luma_a on
WREG (REG_ADDR_BASE + (0x100b76 <<1 )) , 0x0000   // clk_mvd_luma_b on
                          // clk_mvd_luma_c on
WREG (REG_ADDR_BASE + (0x100b78 <<1 )) , 0x0000   // clk_mvd_rmem on
                          // clk_mvd_rmem1 on

//GOP
WREG (REG_ADDR_BASE + (0x100b80 <<1 )) , 0x0000   // clk_gopg0 = 27M (clk_odclk)
                          // clk_gopg1 = 27M (clk_odclk)
WREG (REG_ADDR_BASE + (0x100b82 <<1 )) , 0x0018   // clk_gopmix = 27M (clk_ve)
                          // clk_gopd = 27M (clk_odclk)
WREG (REG_ADDR_BASE + (0x100b84 <<1 )) , 0x0004   // clk_gopg2 = 192M (clk_idclk)
                          // clk_gopg3 = 27M (clk_odclk)

WREG (REG_ADDR_BASE + (0x100b86 <<1 )) , 0x0000   // clk_psram0 on

//GE
WREG (REG_ADDR_BASE + (0x100b90 <<1 )) , 0x0000   // clk_ge = 170M

//STB_DC
WREG (REG_ADDR_BASE + (0x100b98 <<1 )) , 0x0018   // clk_dc0 = 192M

//SC
WREG (REG_ADDR_BASE + (0x100ba2 <<1 )) , 0x0400   // clk_ficlk = 192M (clk_fclk)
WREG (REG_ADDR_BASE + (0x100ba4 <<1 )) , 0x1000   // clk_flck = 192M
WREG (REG_ADDR_BASE + (0x100ba6 <<1 )) , 0x000c   // clk_odclk = 27M (CLK_OUT_DAC/8) (output pixel clock)
WREG (REG_ADDR_BASE + (0x100baa <<1 )) , 0x000c   // clk_idclk = 192M (clk_dc0)
WREG (REG_ADDR_BASE + (0x100bb0 <<1 )) , 0x0c00   // clk_hdgen = 27M (clk_odlck)
                          // clk_hdgen_fir = 27M (CLK_OUT_DAC/8)
WREG (REG_ADDR_BASE + (0x100bb2 <<1 )) , 0x000c   // clk_dac1 = 108M (clk_vedac) (SD)
                          // clk_dac2 = 27M (clk_hdgen_fir) (HD)
WREG (REG_ADDR_BASE + (0x100bb4 <<1 )) , 0x000c   // clk_dcs = 27M (CLK_OUT_DAC/8)
                          // clk_dcs27 = 27M

//EMAC
WREG (REG_ADDR_BASE + (0x100bc0 <<1 )) , 0x0000   // clk_emac_ahb = 123M
                          // clk_emac_rx = CLK_EMAC_RX_IN
WREG (REG_ADDR_BASE + (0x100bc2 <<1 )) , 0x0000   // clk_emac_tx = CLK_EMAC_TX_IN
                          // clk_emac_rx_ref = CLK_EMAC_RX_IN
WREG (REG_ADDR_BASE + (0x100bc4 <<1 )) , 0x0000   // clk_emac_tx_ref = CLK_EMAC_TX_IN

//NAND
WREG (REG_ADDR_BASE + (0x100bc8 <<1 )) , 0x0024   // clk_fice = 54M

//MPIF
WREG (REG_ADDR_BASE + (0x100bd0 <<1 )) , 0x0000   // clk_mpif = 123M

//CA
WREG (REG_ADDR_BASE + (0x103348 <<1 )) , 0x0000   // clk_nsk = 123M
                          // clk_sm_ca = 27M, clk_sm_ca2 = 27M

//HDMITX
WREG (REG_ADDR_BASE + (0x103350 <<1 )) , 0x0000   // clk_hdmitx = 27M (clk_odclk)

//MIIC
WREG (REG_ADDR_BASE + (0x103360 <<1 )) , 0x0000   // clk_miic = 24M


