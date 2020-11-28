#
# (C) Copyright 2000-2002
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

#CROSS_COMPILE ?= arm-linux-
CROSS_COMPILE ?=  arm-none-eabi-

ifndef CONFIG_STANDALONE_LOAD_ADDR
ifeq ($(SOC),omap3)
CONFIG_STANDALONE_LOAD_ADDR = 0x80300000
else
CONFIG_STANDALONE_LOAD_ADDR = 0xc100000
endif
endif

PLATFORM_CPPFLAGS += -DCONFIG_ARM -D__ARM__

# Explicitly specifiy 32-bit ARM ISA since toolchain default can be -mthumb:
PF_CPPFLAGS_ARM := $(call cc-option,-marm,)

# Try if EABI is supported, else fall back to old API,
# i. e. for example:
# - with ELDK 4.2 (EABI supported), use:
#	-mabi=aapcs-linux -mno-thumb-interwork
# - with ELDK 4.1 (gcc 4.x, no EABI), use:
#	-mabi=apcs-gnu -mno-thumb-interwork
# - with ELDK 3.1 (gcc 3.x), use:
#	-mapcs-32 -mno-thumb-interwork
PF_CPPFLAGS_ABI := $(call cc-option,\
			-mabi=aapcs-linux -mno-thumb-interwork,\
			$(call cc-option,\
				-mapcs-32,\
				$(call cc-option,\
					-mabi=apcs-gnu,\
				)\
			) $(call cc-option,-mno-thumb-interwork,)\
		)
PLATFORM_CPPFLAGS += $(PF_CPPFLAGS_ARM) $(PF_CPPFLAGS_ABI)

# For EABI, make sure to provide raise()
ifneq (,$(findstring -mabi=aapcs-linux,$(PLATFORM_CPPFLAGS)))
# This file is parsed several times; make sure to add only once.
ifeq (,$(findstring arch/arm/lib/eabi_compat.o,$(PLATFORM_LIBS)))
PLATFORM_LIBS += $(OBJTREE)/arch/arm/lib/eabi_compat.o
endif
endif

ifdef CONFIG_SYS_LDSCRIPT
# need to strip off double quotes
LDSCRIPT := $(subst ",,$(CONFIG_SYS_LDSCRIPT))
else
LDSCRIPT := $(SRCTREE)/$(CPUDIR)/u-boot.lds
endif

# needed for relocation
ifndef CONFIG_NAND_SPL
LDFLAGS_u-boot += -pie
ifdef CONFIG_MSTAR_STR_MINISIZE
LDFLAGS_u-boot-str += -pie
LDFLAGS_u-boot-chk += -pie
endif
endif
