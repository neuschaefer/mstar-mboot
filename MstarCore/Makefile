#
# (C) Copyright 2004-2006
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk
include $(TOPDIR)/../sboot/.config
CONFIG_MSTAR_CHIP_NAME := $(subst ",,$(CONFIG_MSTAR_CHIP_NAME))

LIB	=  $(obj)libmscore.a

#AOBJS	=

COBJS	=
#MstarCore:src
COBJS += ./src/api/MsInit.o
COBJS += ./src/api/apiIR.o
COBJS += ./src/api/msAPI_Power.o
COBJS += ./src/api/MsTemplate.o
COBJS += ./src/api/MsSystem.o
COBJS += ./src/api/MsSysUtility.o
COBJS += ./src/api/MsCoreRegister.o

ifdef CONFIG_POINTS_HANDLER_ENABLE
COBJS += ./src/api/MsApiChkPoints.o
endif

ifeq ($(CONFIG_FRONT_END),y)
CPPFLAGS += -I./cofdm/
CFLAGS += -I./cofdm/
CPPFLAGS += -I./tuner/
CFLAGS += -I./tuner/
COBJS += ./src/api/msAPI_Tuner.o
endif
#ifeq ($(ENABLE_POWER_MUSIC),y)
COBJS += ./src/api/MsApiAudio.o
#endif
ifeq ($(CONFIG_CVBS_OUT),y)
COBJS += ./src/api/MsApiVE.o
COBJS += ./cmd/cmd_MsVE.o
endif
ifeq ($(CONFIG_XC_Init),y)
COBJS += ./src/api/MsApiXC.o
COBJS += ./cmd/cmd_MsXC.o
endif
COBJS += ./src/api/MsApiPanel.o
COBJS += ./src/api/MsApiGEGOP.o
COBJS += ./src/api/MsApiJpd.o
COBJS += ./src/api/MsApiPM.o
COBJS += ./src/api/MsApiSpi.o
COBJS += ./src/api/MsMemPerformance.o
ifdef CONFIG_CMD_MMC
COBJS += ./src/api/MsMmc.o
endif
ifdef CONFIG_MSTAR_MLC_FTL
COBJS += ./src/api/MsMLC.o
endif
ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
COBJS += ./src/api/MsSetupR2.o
else ifeq ($(CONFIG_MSTAR_PUMABOOT),y)
COBJS += ./src/api/MsSetupR2.o
endif
ifeq ($(CONFIG_MSTAR_RUNTIMEAEON),y)
COBJS += ./src/api/MsSetupAEON.o
endif
ifeq ($(CONFIG_HDMI_TX),y)
COBJS += ./src/api/MsApiHdmi.o
endif
ifeq ($(CONFIG_EEPROM),y)
COBJS += ./src/api/MsEeprom.o
endif
#MstarCore:cmd
ifeq ($(CONFIG_EMAC),y)
COBJS += ./cmd/cmd_emac.o
endif
ifeq ($(CONFIG_GMAC),y)
COBJS += ./cmd/cmd_emac.o
endif
COBJS += ./cmd/cmd_spi.o
COBJS += ./cmd/cmd_MsMemPerformance.o
COBJS += ./cmd/cmd_MsTemplate.o
COBJS += ./cmd/cmd_MsSystem.o
COBJS += ./cmd/cmd_MsSysUtility.o
COBJS += ./cmd/cmd_MsPanel.o

ifdef CONFIG_CMD_MMC
COBJS += ./cmd/cmd_MsMmc.o
endif
ifdef CONFIG_MSTAR_MLC_FTL
COBJS += ./cmd/cmd_MsMLC.o
endif
ifeq ($(CONFIG_FRONT_END),y)
COBJS += ./cmd/cmd_tuner.o
endif
ifeq ($(CONFIG_OAD_IN_MBOOT),y)
COBJS += ./cmd/cmd_dmx.o
endif
ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
COBJS += ./cmd/cmd_MsR2.o
else ifeq ($(CONFIG_MSTAR_PUMABOOT),y)
COBJS += ./cmd/cmd_MsR2.o
endif
ifeq ($(CONFIG_MSTAR_RUNTIMEAEON),y)
COBJS += ./cmd/cmd_MsAEON.o
endif
ifeq ($(CONFIG_HDMI_TX),y)
COBJS += ./cmd/cmd_MsHdmi.o
endif
ifeq ($(CONFIG_EEPROM),y)
COBJS += ./cmd/cmd_MsEeprom.o
endif
SRCS	:= $(AOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(AOBJS) $(COBJS))

#CPPFLAGS += -I..

all:	$(LIB)

$(LIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
