#copyright (c) 2008-2009 MStar Semiconductor, Inc.
# All rights reserved.
#
# AWK script to automatically generate uboot config file for board options
$3 == "kernel_entry" { print "KERNEL_ENTRY_CACHE = 0x"$1 }
$3 == "_text" { print "ADDR_BIN_RAM_START_CACHE  = 0x"$1 }
