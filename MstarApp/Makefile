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

LIB	=  $(obj)libmsapp.a

#AOBJS	=

COBJS	=
#MstarApp:src
COBJS += ./src/MsStart.o
COBJS += ./src/MsCmdTable.o
COBJS += ./src/MsAppRegister.o
COBJS += ./src/bootlogo/MsBootLogo.o
COBJS += ./src/bootlogo/MsPoolDB.o
COBJS += ./src/bootlogo/iniparser.o
COBJS += ./src/MsUpgrade.o
COBJS += ./src/MsUpgradeUtility.o
COBJS += ./src/MsBoot.o
COBJS += ./src/MsTest.o
COBJS += ./src/MsUtility.o
COBJS += ./src/MsVfs.o
COBJS += ./src/MsEnvironment.o
COBJS += ./src/MsMath.o
COBJS += ./src/MsString.o
COBJS += ./src/MsOSD.o
COBJS += ./src/MsApiFat.o
COBJS += ./src/MsDebug.o
COBJS += ./src/MsRawIO.o
COBJS += ./src/MsMmap.o
COBJS += ./src/MsMBootConfig.o
COBJS += ./src/MsApiMiu.o
#MstarApp:cmd
COBJS += ./cmd/cmd_MsBootLogo.o
COBJS += ./cmd/cmd_MsUpgrade.o
COBJS += ./cmd/cmd_MsUpgradeUtility.o
COBJS += ./cmd/cmd_MsBoot.o
COBJS += ./cmd/cmd_MsTest.o
COBJS += ./cmd/cmd_MsUtility.o
COBJS += ./cmd/cmd_MsEnvironment.o
COBJS += ./cmd/cmd_MsOSD.o
COBJS += ./cmd/cmd_MsFat.o
COBJS += ./cmd/cmd_MsMiu.o
ifeq ($(CONFIG_SECURITY_BOOT),y)
COBJS += ./cmd/cmd_MsSecure.o
endif
COBJS += ./cmd/cmd_MsDebug.o
COBJS += ./cmd/cmd_MsRawIO.o
COBJS += ./cmd/cmd_MsMmap.o

ifeq ($(CONFIG_MSTAR_FASTBOOT_ENABLE),y)
COBJS += ./cmd/cmd_MsFastboot.o
endif
COBJS += ./cmd/cmd_MsMBootConfig.o
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
