# Copyright (c) 2008-2009 MStar Semiconductor, Inc.
# All rights reserved.
#
# AWK script to automatically generate uboot config file for panel type options


$2 == "ENABLE_PNL_FULLHD_SEC_LE32A" {print "#define ENABLE_PNL_FULLHD_SEC_LE32A " $3}
$2 == "ENABLE_PNL_SXGA_AU17_EN05" {print "#define ENABLE_PNL_SXGA_AU17_EN05 " $3}
$2 == "ENABLE_PNL_WXGA_AU20_T200XW02" {print "#define ENABLE_PNL_WXGA_AU20_T200XW02 " $3}
$2 == "ENABLE_PNL_WXGA_PLUS_CMO190_M190A1" {print "#define ENABLE_PNL_WXGA_PLUS_CMO190_M190A1 " $3}
$2 == "ENABLE_PNL_WSXGA_AU22_M201EW01" {print "#define ENABLE_PNL_WSXGA_AU22_M201EW01 " $3}
$2 == "ENABLE_PNL_FULLHD_CMO216_H1L01" {print "#define ENABLE_PNL_FULLHD_CMO216_H1L01 " $3}
$2 == "ENABLE_PANEL_RES_FULL_HD" {print "#define ENABLE_PANEL_RES_FULL_HD " $3}
$2 == "ENABLE_PNL_WUXGA_CMO260_J2" {print "#define ENABLE_PNL_WUXGA_CMO260_J2 " $3}
$2 == "ENABLE_MFC120_FULLHD_CMO216_H1L01" {print "#define ENABLE_MFC120_FULLHD_CMO216_H1L01 " $3}
$2 == "ENABLE_MFC60_FULLHD_CMO216_H1L01" {print "#define ENABLE_MFC60_FULLHD_CMO216_H1L01 " $3}
$2 == "ENABLE_PNL_FULLHD_TCON" {print "#define ENABLE_PNL_FULLHD_TCON " $3}