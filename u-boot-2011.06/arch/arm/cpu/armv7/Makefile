#
# (C) Copyright 2000-2003
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

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).o

START	:= start.o
ifdef CONFIG_MSTAR_STR_MINISIZE
START += start_str.o
endif
COBJS	:= cpu.o
COBJS  += syslib.o
SOBJS  := cache.o

SRCS	:= $(START:.o=.S) $(COBJS:.o=.c) $(SOBJS:.o=.S)
OBJS	:= $(addprefix $(obj),$(COBJS))
OBJS	+= $(addprefix $(obj),$(SOBJS))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend PREPARE_PRANA2 $(START) $(LIB)

PREPARE_PRANA2:
ifeq ($(CONFIG_MSTAR_EAGLE),y)
	cp $(TOPDIR)/lib/mstar/libprana_eagle.a $(TOPDIR)/lib/mstar/temp_libprana_eagle.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_eagle.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_eagle.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_eagle.a head.o
endif
ifeq ($(CONFIG_MSTAR_EIFFEL),y)
	cp $(TOPDIR)/lib/mstar/libprana_eiffel.a $(TOPDIR)/lib/mstar/temp_libprana_eiffel.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_eiffel.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_eiffel.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_eiffel.a head.o
endif
ifeq ($(CONFIG_MSTAR_NIKE),y)
	cp $(TOPDIR)/lib/mstar/libprana_nike.a $(TOPDIR)/lib/mstar/temp_libprana_nike.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_nike.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_nike.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_nike.a head.o
endif

ifeq ($(CONFIG_MSTAR_MADISON),y)
	cp $(TOPDIR)/lib/mstar/libprana_madison.a $(TOPDIR)/lib/mstar/temp_libprana_madison.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_madison.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_madison.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_madison.a head.o
endif

ifeq ($(CONFIG_MSTAR_CLIPPERS),y)
	cp $(TOPDIR)/lib/mstar/libprana_clippers.a $(TOPDIR)/lib/mstar/temp_libprana_clippers.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_clippers.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_clippers.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_clippers.a head.o
endif

ifeq ($(CONFIG_MSTAR_MIAMI),y)
	cp $(TOPDIR)/lib/mstar/libprana_miami.a $(TOPDIR)/lib/mstar/temp_libprana_miami.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_miami.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_miami.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_miami.a head.o
endif

ifeq ($(CONFIG_MSTAR_NADAL),y)
	cp $(TOPDIR)/lib/mstar/libprana_nadal.a $(TOPDIR)/lib/mstar/temp_libprana_nadal.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/temp_libprana_nadal.a vectors.o
	ar d $(TOPDIR)/lib/mstar/temp_libprana_nadal.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/temp_libprana_nadal.a head.o
endif

ifeq ($(CONFIG_MSTAR_AGATE),y)
	cp $(TOPDIR)/lib/mstar/libprana_agate.a $(TOPDIR)/lib/mstar/templibprana_agate.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_agate.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_agate.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_agate.a head.o
endif
ifeq ($(CONFIG_MSTAR_EINSTEIN),y)
	cp $(TOPDIR)/lib/mstar/libprana_einstein.a $(TOPDIR)/lib/mstar/templibprana_einstein.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_einstein.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_einstein.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_einstein.a head.o
endif
ifeq ($(CONFIG_MSTAR_AMBER3),y)
	cp $(TOPDIR)/lib/mstar/libprana_a3.a $(TOPDIR)/lib/mstar/templibprana_a3.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_a3.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_a3.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_a3.a head.o
endif
ifeq ($(CONFIG_MSTAR_EDISON),y)
	cp $(TOPDIR)/lib/mstar/libprana_edison.a $(TOPDIR)/lib/mstar/templibprana_edison.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_edison.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_edison.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_edison.a head.o
endif
ifeq ($(CONFIG_MSTAR_KAISER),y)
	cp $(TOPDIR)/lib/mstar/libprana_kaiser.a $(TOPDIR)/lib/mstar/templibprana_kaiser.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_kaiser.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_kaiser.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_kaiser.a head.o
endif
ifeq ($(CONFIG_MSTAR_EINSTEIN3),y)
	cp $(TOPDIR)/lib/mstar/libprana_einstein3.a $(TOPDIR)/lib/mstar/templibprana_einstein3.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_einstein3.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_einstein3.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_einstein3.a head.o
endif
ifeq ($(CONFIG_MSTAR_NAPOLI),y)
	cp $(TOPDIR)/lib/mstar/libprana_napoli.a $(TOPDIR)/lib/mstar/templibprana_napoli.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_napoli.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_napoli.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_napoli.a head.o
endif
ifeq ($(CONFIG_MSTAR_MONACO),y)
	cp $(TOPDIR)/lib/mstar/libprana_monaco.a $(TOPDIR)/lib/mstar/templibprana_monaco.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_monaco.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_monaco.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_monaco.a head.o
endif
ifeq ($(CONFIG_MSTAR_MUJI),y)
	cp $(TOPDIR)/lib/mstar/libprana_muji.a $(TOPDIR)/lib/mstar/templibprana_muji.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_muji.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_muji.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_muji.a head.o
endif
ifeq ($(CONFIG_MSTAR_CELTICS),y)
	cp $(TOPDIR)/lib/mstar/libprana_celtics.a $(TOPDIR)/lib/mstar/templibprana_celtics.a
	@echo "Extracting vectors.o..."
	ar x $(TOPDIR)/lib/mstar/templibprana_celtics.a vectors.o
	ar d $(TOPDIR)/lib/mstar/templibprana_celtics.a vectors.o
	@echo "Removing head.o..."
	ar d $(TOPDIR)/lib/mstar/templibprana_celtics.a head.o
endif
$(LIB):	$(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
