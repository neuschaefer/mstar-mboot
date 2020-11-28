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

LIB	=  $(obj)libmscustomer.a

#AOBJS	=

COBJS	=
#MstarCustomer:src
COBJS += ./src/MsCustomerRegister.o
COBJS += ./src/CusSystem.o
COBJS += ./src/CusUpgrade.o
COBJS += ./src/CusUpgradeUtility.o
COBJS += ./src/CusOsd.o
COBJS += ./src/CusPM.o
COBJS += ./src/CusLED.o
COBJS += ./src/CusCB.o
ifeq ($(CONFIG_URSA_8),y)
COBJS += ./src/CusUrsa8Init.o
endif
ifeq ($(CONFIG_MSTARI2C),y)
COBJS += ./src/CusI2C.o
endif


#MstarCustomer:cmd
COBJS += ./cmd/cmd_CusSystem.o
COBJS += ./cmd/cmd_CusUpgrade.o
COBJS += ./cmd/cmd_CusUpgradeUtility.o
COBJS += ./cmd/cmd_CusPM.o
COBJS += ./cmd/cmd_CusLED.o
COBJS += ./cmd/cmd_CusUrsa8Init.o

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
