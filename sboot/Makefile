VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
NAME = Unnamed
CUSTOMER = MSTAR
PROJECT="TM14"
TOOL_PATH="/tools/script/ck"
PROJDIR=`pwd`
BLOCK_SIZE=2097152
# *DOCUMENTATION*
# To see a list of typical targets execute "make help"
# More info can be located in ./README
# Comments in this file are targeted only to the developer, do not
# expect to learn how to build the kernel reading this file.

# Do not print "Entering directory ..."
MAKEFLAGS += --no-print-directory

# We are using a recursive build, so we need to do a little thinking
# to get the ordering right.
#
# Most importantly: sub-Makefiles should only ever modify files in
# their own directory. If in some directory we have a dependency on
# a file in another dir (which doesn't happen often, but it's often
# unavoidable when linking the built-in.o targets which finally
# turn into sboot), we will call a sub make in that other dir, and
# after that we are sure that everything which is in that other dir
# is now up to date.
#
# The only cases where we need to modify files which have global
# effects are thus separated out and done before the recursive
# descending is started. They are now explicitly listed as the
# prepare rule.

# To put more focus on warnings, be less verbose as default
# Use 'make V=1' to see the full commands

ifdef V
  ifeq ("$(origin V)", "command line")
    KBUILD_VERBOSE = $(V)
  endif
endif
ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 0
endif

# Call sparse as part of compilation of C files
# Use 'make C=1' to enable sparse checking

ifdef C
  ifeq ("$(origin C)", "command line")
    KBUILD_CHECKSRC = $(C)
  endif
endif
ifndef KBUILD_CHECKSRC
  KBUILD_CHECKSRC = 0
endif

# Use make M=dir to specify directory of external module to build
# Old syntax make ... SUBDIRS=$PWD is still supported
# Setting the environment variable KBUILD_EXTMOD take precedence
ifdef SUBDIRS
  KBUILD_EXTMOD ?= $(SUBDIRS)
endif
ifdef M
  ifeq ("$(origin M)", "command line")
    KBUILD_EXTMOD := $(M)
  endif
endif


# kbuild supports saving output files in a separate directory.
# To locate output files in a separate directory two syntaxes are supported.
# In both cases the working directory must be the root of the kernel src.
# 1) O=
# Use "make O=dir/to/store/output/files/"
#
# 2) Set KBUILD_OUTPUT
# Set the environment variable KBUILD_OUTPUT to point to the directory
# where the output files shall be placed.
# export KBUILD_OUTPUT=dir/to/store/output/files/
# make
#
# The O= assignment takes precedence over the KBUILD_OUTPUT environment
# variable.


# KBUILD_SRC is set on invocation of make in OBJ directory
# KBUILD_SRC is not intended to be used by the regular user (for now)
ifeq ($(KBUILD_SRC),)

# OK, Make called in directory where kernel src resides
# Do we want to locate output files in a separate directory?
ifdef O
  ifeq ("$(origin O)", "command line")
    KBUILD_OUTPUT := $(O)
  endif
endif

ifeq (../.binary_release, $(wildcard ../.binary_release))
	BINARY_RELEASE_FLAG := y
else
	BINARY_RELEASE_FLAG := n
endif

# That's our default target when none is given on the command line
PHONY := _all
_all:

ifneq ($(KBUILD_OUTPUT),)
# Invoke a second make in the output directory, passing relevant variables
# check that the output directory actually exists
saved-output := $(KBUILD_OUTPUT)
KBUILD_OUTPUT := $(shell cd $(KBUILD_OUTPUT) && /bin/pwd)
$(if $(KBUILD_OUTPUT),, \
     $(error output directory "$(saved-output)" does not exist))

PHONY += $(MAKECMDGOALS)

$(filter-out _all,$(MAKECMDGOALS)) _all:
	$(if $(KBUILD_VERBOSE:1=),@)$(MAKE) -C $(KBUILD_OUTPUT) \
	KBUILD_SRC=$(CURDIR) \
	KBUILD_EXTMOD="$(KBUILD_EXTMOD)" -f $(CURDIR)/Makefile $@

# Leave processing to above invocation of make
skip-makefile := 1
endif # ifneq ($(KBUILD_OUTPUT),)
endif # ifeq ($(KBUILD_SRC),)

# We process the rest of the Makefile if this is the final invocation of make
ifeq ($(skip-makefile),)

# If building an external module we do not care about the all: rule
# but instead _all depend on modules
PHONY += all
ifeq ($(KBUILD_EXTMOD),)
_all: all
else
_all: modules
endif

srctree		:= $(if $(KBUILD_SRC),$(KBUILD_SRC),$(CURDIR))
TOPDIR		:= $(srctree)
# FIXME - TOPDIR is obsolete, use srctree/objtree
objtree		:= $(CURDIR)
src		:= $(srctree)
obj		:= $(objtree)

VPATH		:= $(srctree)$(if $(KBUILD_EXTMOD),:$(KBUILD_EXTMOD))

export srctree objtree VPATH TOPDIR

# Cross compiling and selecting different set of gcc/bin-utils
# ---------------------------------------------------------------------------
#
# When performing cross compilation for other architectures ARCH shall be set
# to the target architecture. (See arch/* for the possibilities).
# ARCH can be set during invocation of make:
# make ARCH=ia64
# Another way is to have ARCH set in the environment.
# The default ARCH is the host where make is executed.

# CROSS_COMPILE specify the prefix used for all executables used
# during compilation. Only gcc and related bin-utils executables
# are prefixed with $(CROSS_COMPILE).
# CROSS_COMPILE can be set on the command line
# make CROSS_COMPILE=ia64-linux-
# Alternatively CROSS_COMPILE can be set in the environment.
# Default value for CROSS_COMPILE is not to prefix executables
# Note: Some architectures assign CROSS_COMPILE in their arch/*/Makefile

CROSS_COMPILE ?=
# bbox: we may have CONFIG_CROSS_COMPILER_PREFIX in .config,
# and it has not been included yet... thus using an awkward syntax.
ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE := $(shell grep ^CONFIG_CROSS_COMPILER_PREFIX .config 2>/dev/null)
CROSS_COMPILE := $(subst CONFIG_CROSS_COMPILER_PREFIX=,,$(CROSS_COMPILE))
CROSS_COMPILE := $(subst ",,$(CROSS_COMPILE))
#")
endif

# SUBARCH tells the usermode build what the underlying arch is.  That is set
# first, and if a usermode build is happening, the "ARCH=um" on the command
# line overrides the setting of ARCH below.  If a native build is happening,
# then ARCH is assigned, getting whatever value it gets normally, and
# SUBARCH is subsequently ignored.

ifneq ($(CROSS_COMPILE),)
SUBARCH := $(shell echo $(CROSS_COMPILE) | cut -d- -f1)
else
SUBARCH := $(shell uname -m)
endif
SUBARCH := $(shell echo $(SUBARCH) | sed -e s/i.86/i386/ -e s/sun4u/sparc64/ \
					 -e s/arm.*/arm/ -e s/sa110/arm/ \
					 -e s/s390x/s390/ -e s/parisc64/parisc/ \
					 -e s/ppc.*/powerpc/ -e s/mips.*/mips/ )

ARCH ?= $(SUBARCH)

# Architecture as present in compile.h
UTS_MACHINE := $(ARCH)

# SHELL used by kbuild
CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	  else if [ -x /bin/bash ]; then echo /bin/bash; \
	  else echo sh; fi ; fi)

# 	Decide whether to build built-in, modular, or both.
#	Normally, just do built-in.

KBUILD_MODULES :=
KBUILD_BUILTIN := 1

#	If we have only "make modules", don't compile built-in objects.
#	When we're building modules with modversions, we need to consider
#	the built-in objects during the descend as well, in order to
#	make sure the checksums are uptodate before we record them.

ifeq ($(MAKECMDGOALS),modules)
  KBUILD_BUILTIN := $(if $(CONFIG_MODVERSIONS),1)
endif

#	If we have "make <whatever> modules", compile modules
#	in addition to whatever we do anyway.
#	Just "make" or "make all" shall build modules as well

ifneq ($(filter all _all modules,$(MAKECMDGOALS)),)
  KBUILD_MODULES := 1
endif

ifeq ($(MAKECMDGOALS),)
  KBUILD_MODULES := 1
endif

export KBUILD_MODULES KBUILD_BUILTIN
export KBUILD_CHECKSRC KBUILD_SRC KBUILD_EXTMOD

# Beautify output
# ---------------------------------------------------------------------------
#
# Normally, we echo the whole command before executing it. By making
# that echo $($(quiet)$(cmd)), we now have the possibility to set
# $(quiet) to choose other forms of output instead, e.g.
#
#         quiet_cmd_cc_o_c = Compiling $(RELDIR)/$@
#         cmd_cc_o_c       = $(CC) $(c_flags) -c -o $@ $<
#
# If $(quiet) is empty, the whole command will be printed.
# If it is set to "quiet_", only the short version will be printed.
# If it is set to "silent_", nothing wil be printed at all, since
# the variable $(silent_cmd_cc_o_c) doesn't exist.
#
# A simple variant is to prefix commands with $(Q) - that's useful
# for commands that shall be hidden in non-verbose mode.
#
#	$(Q)ln $@ :<
#
# If KBUILD_VERBOSE equals 0 then the above command will be hidden.
# If KBUILD_VERBOSE equals 1 then the above command is displayed.

ifeq ($(KBUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(findstring s,$(MAKEFLAGS)),)
  quiet=silent_
endif

export quiet Q KBUILD_VERBOSE


# Look for make include files relative to root of kernel src
MAKEFLAGS += --include-dir=$(srctree)

HOSTCC  	= gcc
HOSTCXX  	= g++
HOSTCFLAGS	:=
HOSTCXXFLAGS	:=
# We need some generic definitions
include $(srctree)/scripts/Kbuild.include

HOSTCFLAGS	+= $(call hostcc-option,-Wall -Wstrict-prototypes -O2 -fomit-frame-pointer,)
HOSTCXXFLAGS	+= -O2

# For maximum performance (+ possibly random breakage, uncomment
# the following)

MAKEFLAGS += -rR

# Add flag for specific compiler version
ifeq ($(CPU),mips)
SBOOT_TOOLCHAIN_VERSION = -V 4.3.2
else
SBOOT_TOOLCHAIN_VERSION =
endif


# Make variables (CC, etc...)

AS		= $(CROSS_COMPILE)as
ifeq ($(PARA),1)
CC		= cpptestscan --cpptestscanProjectName=MBoot $(CROSS_COMPILE)gcc $(SBOOT_TOOLCHAIN_VERSION)
else
CC		= $(CROSS_COMPILE)gcc $(SBOOT_TOOLCHAIN_VERSION)
endif
LD		= $(CC) -nostdlib
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
AWK		= awk
GENKSYMS	= scripts/genksyms/genksyms
DEPMOD		= /sbin/depmod
KALLSYMS	= scripts/kallsyms
PERL		= perl
CHECK		= sparse
CAT 		=cat
GREP		=grep
CHECKFLAGS     := -D__linux__ -Dlinux -D__STDC__ -Dunix -D__unix__ -Wbitwise $(CF)
MODFLAGS	= -DMODULE
CFLAGS_MODULE   = $(MODFLAGS)
AFLAGS_MODULE   = $(MODFLAGS)
LDFLAGS_MODULE  = -r
CFLAGS_KERNEL	=
AFLAGS_KERNEL	=
ifeq ($(CPU),aeonR2)
LDFLAGS +=-maeonR2_elfl -EBinst
endif

# Use LINUXINCLUDE when you must reference the include/ directory.
# Needed to be compatible with the O= option
CFLAGS		:= $(CFLAGS)
# Added only to final link stage of sboot binary
CFLAGS_sboot	:= $(CFLAGS_sboot)
CPPFLAGS	:= $(CPPFLAGS)
AFLAGS		:= $(AFLAGS)
LDFLAGS		:= $(LDFLAGS)
LDLIBS		:=

# Read KERNELRELEASE from .kernelrelease (if it exists)
KERNELRELEASE = $(shell cat .kernelrelease 2> /dev/null)
KERNELVERSION = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)$(EXTRAVERSION)

export	VERSION PATCHLEVEL SUBLEVEL KERNELRELEASE KERNELVERSION \
	ARCH CONFIG_SHELL HOSTCC HOSTCFLAGS CROSS_COMPILE AS LD CC \
	CPP AR NM STRIP OBJCOPY OBJDUMP MAKE AWK GENKSYMS PERL UTS_MACHINE \
	HOSTCXX HOSTCXXFLAGS LDFLAGS_MODULE CHECK CHECKFLAGS

export CPPFLAGS NOSTDINC_FLAGS LINUXINCLUDE OBJCOPYFLAGS LDFLAGS
export CFLAGS CFLAGS_KERNEL CFLAGS_MODULE
export AFLAGS AFLAGS_KERNEL AFLAGS_MODULE
export FLTFLAGS

# When compiling out-of-tree modules, put MODVERDIR in the module
# tree rather than in the kernel tree. The kernel tree might
# even be read-only.
export MODVERDIR := $(if $(KBUILD_EXTMOD),$(firstword $(KBUILD_EXTMOD))/).tmp_versions

# Files to ignore in find ... statements

RCS_FIND_IGNORE := \( -name SCCS -o -name BitKeeper -o -name .svn -o -name CVS -o -name .pc -o -name .hg -o -name .git \) -prune -o
export RCS_TAR_IGNORE := --exclude SCCS --exclude BitKeeper --exclude .svn --exclude CVS --exclude .pc --exclude .hg --exclude .git

# ===========================================================================
# Rules shared between *config targets and build targets

# Basic helpers built in scripts/

-include .config
PHONY += scripts_basic
scripts_basic:
ifneq ($(BINARY_RELEASE_FLAG),y)
	$(Q)$(MAKE) $(build)=scripts/basic
endif

PROJ=sboot
_PROJ=u-boot-2011.06

ifeq ($(CONFIG_SBOOT_TO_KERNEL), y)
all: out/sboot2knl.bin doc
endif

# To avoid any implicit rule to kick in, define an empty command.
scripts/basic/%: scripts_basic ;

PHONY += outputmakefile
# outputmakefile generates a Makefile in the output directory, if using a
# separate output directory. This allows convenient use of make in the
# output directory.
outputmakefile:
ifneq ($(KBUILD_SRC),)
	$(Q)$(CONFIG_SHELL) $(srctree)/scripts/mkmakefile \
	    $(srctree) $(objtree) $(VERSION) $(PATCHLEVEL)
endif

# To make sure we do not include .config for any of the *config targets
# catch them early, and hand them over to scripts/kconfig/Makefile
# It is allowed to specify more targets when calling make, including
# mixing *config targets and build targets.
# For example 'make oldconfig all'.
# Detect when mixed targets is specified, and make a second invocation
# of make so .config is not included in this case either (for *config).

no-dot-config-targets := clean mrproper distclean \
			 cscope TAGS tags help %docs
#bbox# check% is removed from above

config-targets := 0
mixed-targets  := 0
dot-config     := 1

ifneq ($(filter $(no-dot-config-targets), $(MAKECMDGOALS)),)
	ifeq ($(filter-out $(no-dot-config-targets), $(MAKECMDGOALS)),)
		dot-config := 0
	endif
endif

ifeq ($(KBUILD_EXTMOD),)
        ifneq ($(filter config %config,$(MAKECMDGOALS)),)
                config-targets := 1
                ifneq ($(filter-out config %config,$(MAKECMDGOALS)),)
                        mixed-targets := 1
                endif
        endif
endif

ifeq ($(mixed-targets),1)
# ===========================================================================
# We're called with mixed targets (*config and build targets).
# Handle them one by one.

%:: FORCE
	$(Q)$(MAKE) -C $(srctree) KBUILD_SRC= $@

else
ifeq ($(config-targets),1)
# ===========================================================================
# *config targets only - make sure prerequisites are updated, and descend
# in scripts/kconfig to make the *config target

# Read arch specific Makefile to set KBUILD_DEFCONFIG as needed.
# KBUILD_DEFCONFIG may point out an alternative default configuration
# used for 'make defconfig'
-include $(srctree)/arch/$(ARCH)/Makefile
export KBUILD_DEFCONFIG

config: scripts_basic outputmakefile FORCE
	$(Q)mkdir -p include
	$(Q)$(MAKE) $(build)=scripts/kconfig $@
	$(Q)$(MAKE) -C $(srctree) KBUILD_SRC= .kernelrelease

%config: scripts_basic outputmakefile FORCE
	$(Q)mkdir -p include
	$(Q)$(MAKE) $(build)=scripts/kconfig $@
	$(Q)$(MAKE) -C $(srctree) KBUILD_SRC= .kernelrelease

else
# ===========================================================================
# Build targets only - this includes sboot, arch specific targets, clean
# targets and others. In general all targets except *config targets.

ifeq ($(KBUILD_EXTMOD),)
# Additional helpers built in scripts/
# Carefully list dependencies so we do not try to build scripts twice
# in parrallel
PHONY += scripts
scripts: scripts_basic include/config/MARKER
	$(Q)$(MAKE) $(build)=$(@)

scripts_basic: include/autoconf.h

# Objects we will link into sboot / subdirs we need to visit
core-y		:= \

libs-y		:= \
		$(sort $(dir $(wildcard src/*))) \

endif # KBUILD_EXTMOD

ifeq ($(dot-config),1)
# In this section, we need .config

# Read in dependencies to all Kconfig* files, make sure to run
# oldconfig if changes are detected.
-include .kconfig.d

-include .config

# If .config needs to be updated, it will be done via the dependency
# that autoconf has on .config.
# To avoid any implicit rule to kick in, define an empty command
.config .kconfig.d: ;

# Now we can define CFLAGS etc according to .config
include $(srctree)/Makefile.flags

# If .config is newer than include/autoconf.h, someone tinkered
# with it and forgot to run make oldconfig.
# If kconfig.d is missing then we are probarly in a cleaned tree so
# we execute the config step to be sure to catch updated Kconfig files
include/autoconf.h: .kconfig.d .config
ifneq ($(BINARY_RELEASE_FLAG),y)
	$(Q)$(MAKE) -f $(srctree)/Makefile silentoldconfig
endif

else
# Dummy target needed, because used as prerequisite
include $(srctree)/Makefile.flags
include/autoconf.h: ;
endif

# The all: target is the default when no target is given on the
# command line.
# This allow a user to issue only 'make' to build a kernel including modules
# Defaults sboot but it is usually overridden in the arch makefile


all: PROTECT_FLAG_CONFLICT_CHECK MBOOT_SIZE_CHECK LINT_RESULT doc

	$(Q)rm -f ../$(_PROJ)/u-boot.bin
	$(Q)rm -f ../$(_PROJ)/u-boot.map

-include $(srctree)/arch/$(ARCH)/Makefile

# arch Makefile may override CC so keep this after arch Makefile is included
#bbox# NOSTDINC_FLAGS += -nostdinc -isystem $(shell $(CC) -print-file-name=include)
CHECKFLAGS += $(NOSTDINC_FLAGS)

# Default kernel image to build when no specific target is given.
# KBUILD_IMAGE may be overruled on the commandline or
# set in the environment
# Also any assignments in arch/$(ARCH)/Makefile take precedence over
# this default value
export KBUILD_IMAGE ?= sboot

#
# INSTALL_PATH specifies where to place the updated kernel and system map
# images. Default is /boot, but you can set it to other values
export	INSTALL_PATH ?= /boot

#
# INSTALL_MOD_PATH specifies a prefix to MODLIB for module directory
# relocations required by build roots.  This is not defined in the
# makefile but the arguement can be passed to make if needed.
#

MODLIB	= $(INSTALL_MOD_PATH)/lib/modules/$(KERNELRELEASE)
export MODLIB

libs-y +=  $(sort $(dir $(wildcard src/$(CHIP_FOLDER)/))) \

ifeq ($(KBUILD_EXTMOD),)
sboot-dirs	:= $(patsubst %/,%,$(filter %/, $(core-y) $(core-m) $(libs-y) $(libs-m)))

sboot-alldirs	:= $(sort $(sboot-dirs) $(patsubst %/,%,$(filter %/, \
		     $(core-n) $(core-) $(libs-n) $(libs-) \
		)))

ifeq ($(CONFIG_MSTAR_MACAW12_PM),y)
UTOPIA_LIB = ./src/$(CHIP_FOLDER)/utopia/lib/libapiCEC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiSWI2C.lib     \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvCPU.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvDDC2BI.lib    \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvGPIO.lib      \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIR.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPM.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPWM.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvRTC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSAR.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSERFLASH.lib  \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSYS.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWDT.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiXC.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libnos.lib

#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvHWI2C.lib     \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvVE.lib        \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWBLE.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvBDMA.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIRQ.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMMIO.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSEM.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvUART.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMBX.lib      \

core-y		:= $(patsubst %/, %/built-in.o, $(core-y))
libs-y1		:= $(patsubst %/, %/lib.a, $(libs-y))
libs-y2		:= $(patsubst %/, %/built-in.o, $(libs-y))
libs-y		:= ./src/$(CHIP_FOLDER)/lib.a $(libs-y2) $(UTOPIA_LIB)
else ifeq ($(CONFIG_MSTAR_EDEN_PM),y)
UTOPIA_LIB = ./src/$(CHIP_FOLDER)/utopia/lib/libapiCEC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiSWI2C.lib     \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvCPU.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvDDC2BI.lib    \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvGPIO.lib      \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIR.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPM.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPWM.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvRTC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSAR.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSERFLASH.lib  \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSYS.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWDT.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiXC.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libnos.lib

#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvHWI2C.lib     \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvVE.lib        \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWBLE.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvBDMA.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIRQ.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMMIO.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSEM.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvUART.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMBX.lib      \

core-y		:= $(patsubst %/, %/built-in.o, $(core-y))
libs-y1		:= $(patsubst %/, %/lib.a, $(libs-y))
libs-y2		:= $(patsubst %/, %/built-in.o, $(libs-y))
libs-y		:= ./src/$(CHIP_FOLDER)/lib.a $(libs-y2) $(UTOPIA_LIB)
else ifeq ($(CONFIG_MSTAR_EULER_PM),y)
UTOPIA_LIB = ./src/$(CHIP_FOLDER)/utopia/lib/libapiCEC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiSWI2C.lib     \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvCPU.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvDDC2BI.lib    \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvGPIO.lib      \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIR.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPM.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPWM.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvRTC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSAR.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSERFLASH.lib  \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSYS.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWDT.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiXC.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libnos.lib

#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvHWI2C.lib     \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvVE.lib        \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWBLE.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvBDMA.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIRQ.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMMIO.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSEM.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvUART.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMBX.lib      \

core-y		:= $(patsubst %/, %/built-in.o, $(core-y))
libs-y1		:= $(patsubst %/, %/lib.a, $(libs-y))
libs-y2		:= $(patsubst %/, %/built-in.o, $(libs-y))
libs-y		:= ./src/$(CHIP_FOLDER)/lib.a $(libs-y2) $(UTOPIA_LIB)
else ifeq ($(CONFIG_MSTAR_NASA_PM),y)
UTOPIA_LIB = ./src/$(CHIP_FOLDER)/utopia/lib/libapiCEC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiSWI2C.lib     \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvCPU.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvDDC2BI.lib    \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvGPIO.lib      \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIR.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPM.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvPWM.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvRTC.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSAR.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSERFLASH.lib  \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSYS.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWDT.lib       \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libapiXC.lib        \
						 ./src/$(CHIP_FOLDER)/utopia/lib/libnos.lib

#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvHWI2C.lib     \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvVE.lib        \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvWBLE.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvBDMA.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvIRQ.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMMIO.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvSEM.lib       \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvUART.lib      \
#						 ./src/$(CHIP_FOLDER)/utopia/lib/libdrvMBX.lib      \

core-y		:= $(patsubst %/, %/built-in.o, $(core-y))
libs-y1		:= $(patsubst %/, %/lib.a, $(libs-y))
libs-y2		:= $(patsubst %/, %/built-in.o, $(libs-y))
libs-y		:= ./src/$(CHIP_FOLDER)/lib.a $(libs-y2) $(UTOPIA_LIB)
else
core-y		:= $(patsubst %/, %/built-in.o, $(core-y))
libs-y1		:= $(patsubst %/, %/lib.a, $(libs-y))
libs-y2		:= $(patsubst %/, %/built-in.o, $(libs-y))
libs-y		:= $(libs-y1) $(libs-y2)
endif

# Build sboot
# ---------------------------------------------------------------------------
# sboot is build from the objects selected by $(sboot-init) and
# $(sboot-main). Most are built-in.o files from top-level directories
# in the kernel tree, others are specified in arch/$(ARCH)Makefile.
# Ordering when linking is important, and $(sboot-init) must be first.
#
# sboot
#   ^
#   |
#   +-< $(sboot-init)
#   |   +--< init/version.o + more
#   |
#   +--< $(sboot-main)
#   |    +--< driver/built-in.o mm/built-in.o + more
#   |
#   +-< kallsyms.o (see description in CONFIG_KALLSYMS section)
#
# sboot version (uname -v) cannot be updated during normal
# descending-into-subdirs phase since we do not yet know if we need to
# update sboot.
# Therefore this step is delayed until just before final link of sboot -
# except in the kallsyms case where it is done just before adding the
# symbols to the kernel.
#
# System.map is generated to document addresses of all kernel symbols

BOOT_OUTPUT_PATH= out

BOOT1_INC       = $(BOOT_OUTPUT_PATH)/boot1.inc
SBOOT_BIN       = $(BOOT_OUTPUT_PATH)/sboot.bin
UBOOT_BIN	    = $(BOOT_OUTPUT_PATH)/u-boot.bin
UBOOT_MAP	    = $(BOOT_OUTPUT_PATH)/u-boot.map
CHUNK_HEADER    = $(BOOT_OUTPUT_PATH)/chunk_header.bin
SECURITY_BIN    = $(BOOT_OUTPUT_PATH)/secure_info.bin
SECURITY_INC    = $(BOOT_OUTPUT_PATH)/security.inc
MCONFIG_BIN     = $(BOOT_OUTPUT_PATH)/mboot_config.bin
MCONFIG_ALIGN_BIN = $(BOOT_OUTPUT_PATH)/mboot_config_dummy.bin

CLEANBOOT_BIN   = bin/cleanboot/$(CHIP_FOLDER)/cleanboot.bin
PUMABOOT_BIN   = bin/pumaboot/$(CHIP_FOLDER)/pumaboot.bin
RT_AEON_BIN 	= bin/runtimeAEON/$(CHIP_FOLDER)/runtimeAEON.bin
HASH0_BIN       = secure/hash/$(CHIP_FOLDER)/hash0.bin
HASH0_BIN_SZ    = secure/hash/$(CHIP_FOLDER)/SZ/hash0.bin
AUT_BIN         = secure/AUT_info.bin

HASH1_BIN       = $(BOOT_OUTPUT_PATH)/hash1.bin
HASH2_BIN       = $(BOOT_OUTPUT_PATH)/hash2.bin
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
HASH3_BIN       = $(BOOT_OUTPUT_PATH)/hash3.bin
endif
HASH1_MIU_BIN   = $(BOOT_OUTPUT_PATH)/hash1_miu.bin
HASH1_STR_BIN   = $(BOOT_OUTPUT_PATH)/hash1_str.bin
HASH1_DESKEW_BIN= $(BOOT_OUTPUT_PATH)/hash1_deskew.bin
EMMC_BOOT_BIN   = $(BOOT_OUTPUT_PATH)/rom_emmc_boot.bin

HASH1_SIG       = $(BOOT_OUTPUT_PATH)/hash1.bin.sig.bin
HASH2_SIG       = $(BOOT_OUTPUT_PATH)/hash2.bin.sig.bin
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
HASH3_SIG       = $(BOOT_OUTPUT_PATH)/hash3.bin.sig.bin
endif
HASH1_STR_SIG   = $(BOOT_OUTPUT_PATH)/hash1_str.bin.sig.bin
HASH1_MIU_SIG   = $(BOOT_OUTPUT_PATH)/hash1_miu.bin.sig.bin
HASH1_DESKEW_SIG= $(BOOT_OUTPUT_PATH)/hash1_deskew.bin.sig.bin

ifeq ($(CONFIG_MSTAR_NIKE),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_MADISON),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_CLIPPERS),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x0E00
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1200
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3900

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3A00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x0E00
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1200
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4B00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_MIAMI),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_MONET),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x3800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x3400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x3800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x3700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x3800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x5300

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x5400
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x6F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_MONACO),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x3800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x3600
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x3800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x3700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x3800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x5300

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x5400
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x6F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x1000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x1400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0x9300

CONFIG_BOOT_HASH3_OFFSET_ADDRESS    = 0x9400
CONFIG_BOOT_HASH3_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH3_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH3_SIG_ADDRESS       = 0xB700
else
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300
endif

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_MUJI),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x3800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x3600
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x3800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x3700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x3800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x5300

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x5400
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x6F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_CELTICS),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x3800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x3600
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x3800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x3700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x3800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x5300

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x5400
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1800
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1C00
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x6F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_NADAL),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_EDISON),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1200
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1200
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_EIFFEL),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
endif

ifeq ($(CONFIG_MSTAR_EINSTEIN),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700
CONFIG_BOOT_HASH1_AUT_ADDRESS       = 0x2600

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
CONFIG_BOOT_AUT_IMAGE_SIZE          = 0x0008
endif

ifeq ($(CONFIG_MSTAR_EINSTEIN3),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700
CONFIG_BOOT_HASH1_AUT_ADDRESS       = 0x2600

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
CONFIG_BOOT_AUT_IMAGE_SIZE          = 0x0008
endif

ifeq ($(CONFIG_MSTAR_NAPOLI),y)
CONFIG_BOOT_HASH0_IMAGE_SIZE        = 0x2800

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x2400
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x2800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x2700
CONFIG_BOOT_HASH1_AUT_ADDRESS       = 0x2600

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x2800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x3B00

CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS= 0x3C00
CONFIG_BOOT_HASH1_STR_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_STR_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_STR_SIG_ADDRESS   = 0x4F00

CONFIG_BOOT_HASH1_DESKEW_OFFSET_ADDRESS= 0x5000
CONFIG_BOOT_HASH1_DESKEW_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_DESKEW_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_DESKEW_SIG_ADDRESS   = 0x6300

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x1000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x1400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0x9300

CONFIG_BOOT_HASH3_OFFSET_ADDRESS    = 0x9400
CONFIG_BOOT_HASH3_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH3_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH3_SIG_ADDRESS       = 0xB700
else
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300
endif

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
CONFIG_BOOT_AUT_IMAGE_SIZE          = 0x0008
endif

ifeq ($(CONFIG_MSTAR_NUGGET),y)

CONFIG_BOOT_HASH1_OFFSET_ADDRESS    = 0x0000
CONFIG_BOOT_HASH1_IMAGE_SIZE        = 0x3000
CONFIG_BOOT_HASH1_AREA_SIZE         = 0x3800
CONFIG_BOOT_HASH1_SIG_ADDRESS       = 0x3000
CONFIG_BOOT_HASH1_AUT_ADDRESS       = 0x3100

CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS= 0x3800
CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE    = 0x1000
CONFIG_BOOT_HASH1_MIU_AREA_SIZE     = 0x1400
CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS   = 0x4B00

CONFIG_BOOT_HASH2_OFFSET_ADDRESS    = 0x8000
CONFIG_BOOT_HASH2_IMAGE_SIZE        = 0x2000
CONFIG_BOOT_HASH2_AREA_SIZE         = 0x2400
CONFIG_BOOT_HASH2_SIG_ADDRESS       = 0xA300

CONFIG_BOOT_SIG_IMAGE_SIZE          = 0x0100
CONFIG_BOOT_AUT_IMAGE_SIZE          = 0x0008
endif

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	CONFIG_ROM_BOOTING_ENABLE = yes
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH), y)
	CONFIG_ROM_BOOTING_ENABLE = yes
else
	CONFIG_ROM_BOOTING_ENABLE = no
endif

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
HASH1_CODE_SIZE = 0x2400
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
HASH2_CODE_SIZE = 0x1000
HASH3_CODE_SIZE = 0x2000
HASH3_SIZE = 0x2200
else
HASH2_CODE_SIZE = 0x8000
endif
endif

STATIC_SBOOT_PATH=../MstarCustomer/$(CUSTOMER)/sboot/bin/sboot
PM_SBOOT_PATH=../MstarCustomer/$(CUSTOMER)/sboot/bin/pm

ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU), y)
	ifeq ($(CONFIG_MSTAR_STR_ENABLE), y)
		PM_BIN	   	= $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_cpu/STR_PM.bin
	else
		PM_BIN	    = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_cpu/PM.bin
	endif
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH), y)
	ifeq ($(CONFIG_MSTAR_STR_ENABLE), y)
	    PM_BIN      = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/rom_with_cpu/STR_PM.bin
	else
	    PM_BIN      = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/rom_with_cpu/PM.bin
	endif
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	ifeq ($(CONFIG_MSTAR_STR_ENABLE), y)
	    PM_BIN      = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/rom_with_cpu/STR_PM.bin
	else
	    PM_BIN      = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/rom_with_cpu/PM.bin
	endif
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_FOR_BUILD_PM_BIN), y)
	ifeq ($(CONFIG_MSTAR_STR_ENABLE), y)
	    PM_BIN      = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/rom_with_cpu/STR_PM.bin
	else
	    PM_BIN      = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/rom_with_cpu/PM.bin
	endif
else ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51), y)
		PM_BIN		= $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_51/$(BOARD_NAME)/PM.bin
else ifeq ($(CONFIG_BOOTING_FROM_OTP_WITH_PM51), y)
		PM_BIN		= $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/otp_with_51/PM.bin
else
		error "Unknown Booting mode!!"
endif
ifeq ($(CONFIG_MSTAR_RT_PM_IN_SPI),y)
    RT_PM_BIN           = $(PM_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_cpu/RT_PM.bin
endif
AUTOCONF_H  = include/autoconf.h
UBOOT_MODULE_CONFIG_H = ../$(_PROJ)/include/configs/uboot_module_config.h
UBOOT_BOARD_CONFIG_H = ../$(_PROJ)/include/configs/uboot_board_config.h
UBOOT_PANEL_CONFIG_H = ../$(_PROJ)/include/configs/uboot_panel_config.h

LOGO_BIN = out/boot0.jpg
ifdef CONFIG_BOOT_SPI_ECOS
LOGO_SRC = bin/boot_hummingbird.jpg
else 
LOGO_SRC = ../MstarCustomer/$(CUSTOMER)/sboot/bin/logo/boot0.jpg
endif

TOOLDIR=./util
SBOOT_LDS=./src/$(CHIP_FOLDER)/sboot.lds.S
SBOOT_MAP=./out/sboot.elf.map
SECUREDIR = ./secure
SIGNATURE_PM=./secure_info_pm.bin
SIGNATURE_SBOOT=./secure_info_sboot.bin
SIGNATURE_UBOOT=./secure_info_uboot.bin

SIGNATURE_CUSTOMER_KEY_BANK=$(SECUREDIR)/secure_info_customer_key_bank.bin
RSA_BOOT_PRIVATE_KEY=$(SECUREDIR)/RSAboot_priv.txt
RSA_BOOT_PUBLIC_KEY=$(SECUREDIR)/RSAboot_pub.txt
RSA_BOOT_PUBLIC_KEY_BIN=$(SECUREDIR)/RSAboot_pub.bin
RSA_UPGRADE_PUBLIC_KEY=$(SECUREDIR)/RSAupgrade_pub.txt
RSA_UPGRADE_PUBLIC_KEY_BIN=$(SECUREDIR)/RSAupgrade_pub.bin
RSA_IMAGE_PUBLIC_KEY=$(SECUREDIR)/RSAimage_pub.txt
RSA_IMAGE_PUBLIC_KEY_BIN=$(SECUREDIR)/RSAimage_pub.bin
ifeq ($(CONFIG_VESTEL_MB97), y)
AES_BOOT_KEY=$(SECUREDIR)/MB97_AES/AESboot.bin
else ifeq ($(CONFIG_VESTEL_MB100), y)
AES_BOOT_KEY=$(SECUREDIR)/MB100_AES/AESboot.bin
else
AES_BOOT_KEY=$(SECUREDIR)/AESboot.bin
endif
AES_UPGRADE_KEY=$(SECUREDIR)/AESupgrade.bin
MAGIC_ID=$(SECUREDIR)/MagicID.bin
DDR_BACKUP_BIN=ddrBackup.bin

ifdef CONFIG_STATIC_SBOOT
static-sboot:
		$(Q) echo "== STATIC SBOOT =="
ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU), y)
	$(Q)cp $(STATIC_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_cpu/$(BOARD_NAME)/sboot.* ./out
else ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51),y)
	$(Q)cp $(STATIC_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_51/$(BOARD_NAME)/sboot.* ./out
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH),y)
	$(Q)cp $(STATIC_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_51/$(BOARD_NAME)/rom_emmc_boot.bin ./out	
	$(Q)cp $(STATIC_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_51/$(BOARD_NAME)/rom_emmc_boot.bin ./out	
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH),y)
	$(Q)cp $(STATIC_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_51/$(BOARD_NAME)/rom_emmc_boot.bin ./out	
	$(Q)cp $(STATIC_SBOOT_PATH)/$(CHIP_FOLDER)/ext_spi_with_51/$(BOARD_NAME)/rom_emmc_boot.bin ./out	
else
        $(Q)echo "wait to implement!!"
endif
endif

sboot-all  := $(core-y) $(libs-y)

# Rule to link sboot - also used during CONFIG_KALLSYMS
# May be overridden by arch/$(ARCH)/Makefile
quiet_cmd_sboot__ ?= LINK    $@
	cmd_sboot__ ?= $(srctree)/scripts/trylink \
	"$@" \
	"$(CC)" \
	"$(CFLAGS) $(CFLAGS_sboot)" \
	"$(LDFLAGS) $(EXTRA_LDFLAGS)" \
	"$(core-y)" \
	"$(libs-y)" \
	"$(LDLIBS)"

out:
	$(Q)[ -d @ ] || mkdir -p $@
ifeq ($(CONFIG_BINARY_RELEASE),y)
	$(Q)[ -f mboot_config.bin ] && cp -f mboot_config.bin $@
endif

../$(_PROJ)/u-boot.bin:
	$(Q)$(CC) -v 2>/dev/null
	$(Q)echo "  GEN     uboot_module_config.h"
	$(Q)echo "/* Automatically generated module config: don't edit */" > $(UBOOT_MODULE_CONFIG_H)
	$(Q)$(AWK) -f scripts/uboot-module-config.awk $(AUTOCONF_H) >> $(UBOOT_MODULE_CONFIG_H)
	$(Q)echo "  GEN     uboot_board_config.h"
	$(Q)echo "/* Automatically generated board config: don't edit */" > $(UBOOT_BOARD_CONFIG_H)
	$(Q)$(AWK) -f scripts/uboot-board-config.awk $(AUTOCONF_H) >> $(UBOOT_BOARD_CONFIG_H)
ifneq ($(CONFIG_MSTAR_MANUAL), y)
ifeq ($(CONFIG_CPU_216MHZ), y)
	$(Q)echo "#define CPU_CLOCK 216000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_240MHZ), y)
	$(Q)echo "#define CPU_CLOCK 240000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_264MHZ), y)
	$(Q)echo "#define CPU_CLOCK 264000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_288MHZ), y)
	$(Q)echo "#define CPU_CLOCK 288000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_312MHZ), y)
	$(Q)echo "#define CPU_CLOCK 312000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_336MHZ), y)
	$(Q)echo "#define CPU_CLOCK 336000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_360MHZ), y)
	$(Q)echo "#define CPU_CLOCK 360000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_384MHZ), y)
	$(Q)echo "#define CPU_CLOCK 384000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_408MHZ), y)
	$(Q)echo "#define CPU_CLOCK 408000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_432MHZ), y)
	$(Q)echo "#define CPU_CLOCK 432000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_456MHZ), y)
	$(Q)echo "#define CPU_CLOCK 456000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_480MHZ), y)
	$(Q)echo "#define CPU_CLOCK 480000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_504MHZ), y)
	$(Q)echo "#define CPU_CLOCK 504000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_528MHZ), y)
	$(Q)echo "#define CPU_CLOCK 528000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_552MHZ), y)
	$(Q)echo "#define CPU_CLOCK 552000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_576MHZ), y)
	$(Q)echo "#define CPU_CLOCK 576000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_600MHZ), y)
	$(Q)echo "#define CPU_CLOCK 600000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_624MHZ), y)
	$(Q)echo "#define CPU_CLOCK 624000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_672MHZ), y)
	$(Q)echo "#define CPU_CLOCK 672000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_684MHZ), y)
	$(Q)echo "#define CPU_CLOCK 684000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_696MHZ), y)
	$(Q)echo "#define CPU_CLOCK 696000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_708MHZ), y)
	$(Q)echo "#define CPU_CLOCK 708000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_720MHZ), y)
	$(Q)echo "#define CPU_CLOCK 720000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_756MHZ), y)
	$(Q)echo "#define CPU_CLOCK 756000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_780MHZ), y)
	$(Q)echo "#define CPU_CLOCK 780000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_792MHZ), y)
	$(Q)echo "#define CPU_CLOCK 792000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_804MHZ), y)
	$(Q)echo "#define CPU_CLOCK 804000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_816MHZ), y)
	$(Q)echo "#define CPU_CLOCK 816000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_828MHZ), y)
	$(Q)echo "#define CPU_CLOCK 828000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_840MHZ), y)
	$(Q)echo "#define CPU_CLOCK 840000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_852MHZ), y)
	$(Q)echo "#define CPU_CLOCK 852000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_864MHZ), y)
	$(Q)echo "#define CPU_CLOCK 864000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_876MHZ), y)
	$(Q)echo "#define CPU_CLOCK 876000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_888MHZ), y)
	$(Q)echo "#define CPU_CLOCK 888000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_900MHZ), y)
	$(Q)echo "#define CPU_CLOCK 900000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_936MHZ), y)
	$(Q)echo "#define CPU_CLOCK 936000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_948MHZ), y)
	$(Q)echo "#define CPU_CLOCK 948000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_984MHZ), y)
	$(Q)echo "#define CPU_CLOCK 984000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1008MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1008000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1044MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1044000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1100MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1100000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1152MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1152000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1400MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1400000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1450MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1450000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
ifeq ($(CONFIG_CPU_1700MHZ), y)
	$(Q)echo "#define CPU_CLOCK 1700000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif
else
	$(Q)echo "#define CPU_CLOCK $(CONFIG_MSTAR_OTHERS)000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif

ifeq ($(CONFIG_MSTAR_GPU_MANUAL), y)
	$(Q)echo "#define GPU_CLOCK $(CONFIG_MSTAR_GPU_OTHERS)000000UL" >> $(UBOOT_BOARD_CONFIG_H)
endif

ifeq ($(CONFIG_EARLY_DISABLE_UART), y)
	$(Q)echo "#define EARLY_DISABLE_UART 1" >> $(UBOOT_BOARD_CONFIG_H)
else
	$(Q)echo "#define EARLY_DISABLE_UART 0" >> $(UBOOT_BOARD_CONFIG_H)
endif
	$(Q)echo "  GEN     uboot_panel_config.h"
	$(Q)echo "/* Automatically generated panel type config: don't edit */" > $(UBOOT_PANEL_CONFIG_H)
	$(Q)$(AWK) -f scripts/uboot-panel-config.awk $(AUTOCONF_H) >> $(UBOOT_PANEL_CONFIG_H)
	$(Q)$(AWK) -f scripts/uboot-chip-config.awk $(AUTOCONF_H)

$(UBOOT_BIN): ../$(_PROJ)/u-boot.bin
	$(Q)echo "  COPY    $@"
	$(Q)cp $< $@
ifeq ($(CONFIG_COMPRESSED_UBOOT), y)
	$(Q)echo "  COMPRESS U-BOOT    "
	$(Q)mv $@ $@.nocompress
	$(Q)$(TOOLDIR)/mscompress -c -u 0 $< > $@
endif

$(UBOOT_MAP): ../$(_PROJ)/u-boot.map
	$(Q)echo "  COPY    $@"
	$(Q)cp $< $@

#	Customer Key Bank  struct{
#		SUB_SECURE_INFO customerKeyBank;
#  		U8 u8RSABootPublicKey[260];
#  		U8 u8RSAUpgradePublicKey[260];
#  		U8 u8RSAImagePublicKey[260];
#  		U8 u8AESBootKey[16];
#  		U8 u8AESUpgradeKey[16];
#  		U8 u8MagicID[16];
#  		U8 checkSum[4];
#   }
$(SECURITY_BIN):
	$(Q)cat $(RSA_BOOT_PUBLIC_KEY_BIN) > tempKeyBank;
ifeq ($(CONFIG_REAL_KEY),y)
	$(Q)echo "make keybank with real key"
	$(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/keybank.sh $(PROJDIR)/tempKeyBank $(PROJECT)
	$(Q)cat $(MAGIC_ID) >> tempKeyBank;
	$(Q)$(SECUREDIR)/crc -a tempKeyBank;
	$(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/SubSecureInfoGen_boot.sh $(PROJDIR)/tempKeyBank.signature.bin $(PROJDIR)/tempKeyBank 1 $(PROJECT) $(PROJDIR)/secure 0 8 0 $(BLOCK_SIZE) 0;
else
	$(Q)cat $(RSA_UPGRADE_PUBLIC_KEY_BIN) >> tempKeyBank;
	$(Q)cat $(RSA_IMAGE_PUBLIC_KEY_BIN) >> tempKeyBank;
	$(Q)cat $(AES_BOOT_KEY) >> tempKeyBank;
	$(Q)cat $(AES_UPGRADE_KEY) >> tempKeyBank;
	$(Q)cat $(MAGIC_ID) >> tempKeyBank;
	$(Q)$(SECUREDIR)/crc -a tempKeyBank;
	$(Q)$(SECUREDIR)/SubSecureInfoGen.exe tempKeyBank.signature.bin tempKeyBank $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0  8 0 $(BLOCK_SIZE) 0 $(SECUREDIR);
endif
	$(Q)cat tempKeyBank >> tempKeyBank.signature.bin;
# generate bakcup for CustomerKeyBank
	$(TOOLDIR)/align tempKeyBank.signature.bin $(CUS_KEYBANK_LEN);
	$(Q)cp tempKeyBank.signature.bin _tempKeyBank.signature.bin;
	$(Q)cat tempKeyBank.signature.bin >>_tempKeyBank.signature.bin;
	$(TOOLDIR)/align _tempKeyBank.signature.bin $(MBOOT_ALIGNMENT_SIZE);
	$(Q)cat _tempKeyBank.signature.bin >> $@;
	$(Q)rm _tempKeyBank.signature.bin;


$(LOGO_BIN): $(LOGO_SRC)
ifeq ($(CONFIG_LOGO_STORE_IN_MBOOT),y)
	$(Q)echo "  COPY    $< $@"
	$(Q)cp $< $@
endif

ifeq ($(CONFIG_NON_OS), y)
$(BOOT1_INC):
	$(Q)echo "  GEN     $@"
	$(Q)echo "#This file is auto created. Do not modify!" > $(BOOT1_INC)
ifneq ($(CONFIG_MSTAR_MANUAL), y)
ifeq ($(CONFIG_CPU_216MHZ), y)
	$(Q)echo "CPU_CLOCK = 216" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_240MHZ), y)
	$(Q)echo "CPU_CLOCK = 240" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_264MHZ), y)
	$(Q)echo "CPU_CLOCK = 264" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_288MHZ), y)
	$(Q)echo "CPU_CLOCK = 288" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_312MHZ), y)
	$(Q)echo "CPU_CLOCK = 312" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_336MHZ), y)
	$(Q)echo "CPU_CLOCK = 336" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_360MHZ), y)
	$(Q)echo "CPU_CLOCK = 360" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_384MHZ), y)
	$(Q)echo "CPU_CLOCK = 384" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_408MHZ), y)
	$(Q)echo "CPU_CLOCK = 408" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_432MHZ), y)
	$(Q)echo "CPU_CLOCK = 432" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_456MHZ), y)
	$(Q)echo "CPU_CLOCK = 456" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_480MHZ), y)
	$(Q)echo "CPU_CLOCK = 480" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_504MHZ), y)
	$(Q)echo "CPU_CLOCK = 504" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_528MHZ), y)
	$(Q)echo "CPU_CLOCK = 528" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_552MHZ), y)
	$(Q)echo "CPU_CLOCK = 552" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_576MHZ), y)
	$(Q)echo "CPU_CLOCK = 576" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_600MHZ), y)
	$(Q)echo "CPU_CLOCK = 600" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_624MHZ), y)
	$(Q)echo "CPU_CLOCK = 624" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_672MHZ), y)
	$(Q)echo "CPU_CLOCK = 672" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_684MHZ), y)
	$(Q)echo "CPU_CLOCK = 684" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_696MHZ), y)
	$(Q)echo "CPU_CLOCK = 696" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_708MHZ), y)
	$(Q)echo "CPU_CLOCK = 708" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_720MHZ), y)
	$(Q)echo "CPU_CLOCK = 720" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_756MHZ), y)
	$(Q)echo "CPU_CLOCK = 756" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_780MHZ), y)
	$(Q)echo "CPU_CLOCK = 780" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_792MHZ), y)
	$(Q)echo "CPU_CLOCK = 792" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_804MHZ), y)
	$(Q)echo "CPU_CLOCK = 804" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_816MHZ), y)
	$(Q)echo "CPU_CLOCK = 816" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_828MHZ), y)
	$(Q)echo "CPU_CLOCK = 828" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_840MHZ), y)
	$(Q)echo "CPU_CLOCK = 840" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_852MHZ), y)
	$(Q)echo "CPU_CLOCK = 852" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_864MHZ), y)
	$(Q)echo "CPU_CLOCK = 864" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_876MHZ), y)
	$(Q)echo "CPU_CLOCK = 876" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_888MHZ), y)
	$(Q)echo "CPU_CLOCK = 888" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_900MHZ), y)
	$(Q)echo "CPU_CLOCK = 900" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_936MHZ), y)
	$(Q)echo "CPU_CLOCK = 936" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_948MHZ), y)
	$(Q)echo "CPU_CLOCK = 948" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_984MHZ), y)
	$(Q)echo "CPU_CLOCK = 984" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1008MHZ), y)
	$(Q)echo "CPU_CLOCK = 1008" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1044MHZ), y)
	$(Q)echo "CPU_CLOCK = 1044" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1100MHZ), y)
	$(Q)echo "CPU_CLOCK = 1100" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1152MHZ), y)
	$(Q)echo "CPU_CLOCK = 1152" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1400MHZ), y)
	$(Q)echo "CPU_CLOCK = 1400" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1450MHZ), y)
	$(Q)echo "CPU_CLOCK = 1450" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1700MHZ), y)
	$(Q)echo "CPU_CLOCK = 1700" >> $(BOOT1_INC)
endif
else
	$(Q)echo "CPU_CLOCK = $(CONFIG_MSTAR_OTHERS)" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_SBOOT_TO_KERNEL), y)
	$(Q)$(AWK) -f scripts/find-kernel-entry.awk $(SYSTEM_MAP) >> $(BOOT1_INC)
	$(Q)echo "SBOOT_TO_KERNEL = 1" >> $(BOOT1_INC)
	$(Q)printf "SIZE_KERNEL = 0x%08X\n" `ls -Gl $(KERNEL_BIN) | $(AWK) '{ print $$4 }'` >> $(BOOT1_INC)
else
	$(Q)echo "SBOOT_TO_KERNEL = 0" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_MSTAR_TITANIA_BD_FPGA), y)
	$(Q)echo "FPGA_BOARD = 1" >> $(BOOT1_INC)
else
	$(Q)echo "FPGA_BOARD = 0" >> $(BOOT1_INC)
endif
else
ifeq ($(CONFIG_DISPLAY_LOGO), y)
$(BOOT1_INC): $(UBOOT_BIN) $(UBOOT_MAP) $(SECURITY_BIN) $(LOGO_BIN)
else
$(BOOT1_INC): $(UBOOT_BIN) $(UBOOT_MAP) $(SECURITY_BIN)
endif
	$(Q)echo "  GEN     $@"
	$(Q)echo "#This file is auto created. Do not modify!" > $(BOOT1_INC)
ifeq ($(CHIP_FOLDER), janus)
	$(Q)$(AWK) '$$2 == "_start" { print "UBOOT_ENTRY_ADDR = "$$1 }' $(UBOOT_MAP) >> $(BOOT1_INC)
endif
ifeq ($(CHIP_FOLDER), maria10)
	$(Q)$(AWK) '$$2 == "_start" { print "UBOOT_ENTRY_ADDR = "$$1 }' $(UBOOT_MAP) >> $(BOOT1_INC)
endif
ifeq ($(CHIP_FOLDER), macaw12)
	$(Q)$(AWK) '$$2 == "_start" { print "UBOOT_ENTRY_ADDR = "$$1 }' $(UBOOT_MAP) >> $(BOOT1_INC)
endif
ifneq ($(CONFIG_MSTAR_MANUAL), y)
ifeq ($(CONFIG_CPU_216MHZ), y)
	$(Q)echo "CPU_CLOCK = 216" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_240MHZ), y)
	$(Q)echo "CPU_CLOCK = 240" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_264MHZ), y)
	$(Q)echo "CPU_CLOCK = 264" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_288MHZ), y)
	$(Q)echo "CPU_CLOCK = 288" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_312MHZ), y)
	$(Q)echo "CPU_CLOCK = 312" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_336MHZ), y)
	$(Q)echo "CPU_CLOCK = 336" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_360MHZ), y)
	$(Q)echo "CPU_CLOCK = 360" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_384MHZ), y)
	$(Q)echo "CPU_CLOCK = 384" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_408MHZ), y)
	$(Q)echo "CPU_CLOCK = 408" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_432MHZ), y)
	$(Q)echo "CPU_CLOCK = 432" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_456MHZ), y)
	$(Q)echo "CPU_CLOCK = 456" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_480MHZ), y)
	$(Q)echo "CPU_CLOCK = 480" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_504MHZ), y)
	$(Q)echo "CPU_CLOCK = 504" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_528MHZ), y)
	$(Q)echo "CPU_CLOCK = 528" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_552MHZ), y)
	$(Q)echo "CPU_CLOCK = 552" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_576MHZ), y)
	$(Q)echo "CPU_CLOCK = 576" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_600MHZ), y)
	$(Q)echo "CPU_CLOCK = 600" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_624MHZ), y)
	$(Q)echo "CPU_CLOCK = 624" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_672MHZ), y)
	$(Q)echo "CPU_CLOCK = 672" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_684MHZ), y)
	$(Q)echo "CPU_CLOCK = 684" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_696MHZ), y)
	$(Q)echo "CPU_CLOCK = 696" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_708MHZ), y)
	$(Q)echo "CPU_CLOCK = 708" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_720MHZ), y)
	$(Q)echo "CPU_CLOCK = 720" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_756MHZ), y)
	$(Q)echo "CPU_CLOCK = 756" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_780MHZ), y)
	$(Q)echo "CPU_CLOCK = 780" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_792MHZ), y)
	$(Q)echo "CPU_CLOCK = 792" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_804MHZ), y)
	$(Q)echo "CPU_CLOCK = 804" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_816MHZ), y)
	$(Q)echo "CPU_CLOCK = 816" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_828MHZ), y)
	$(Q)echo "CPU_CLOCK = 828" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_840MHZ), y)
	$(Q)echo "CPU_CLOCK = 840" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_852MHZ), y)
	$(Q)echo "CPU_CLOCK = 852" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_864MHZ), y)
	$(Q)echo "CPU_CLOCK = 864" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_876MHZ), y)
	$(Q)echo "CPU_CLOCK = 876" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_888MHZ), y)
	$(Q)echo "CPU_CLOCK = 888" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_900MHZ), y)
	$(Q)echo "CPU_CLOCK = 900" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_936MHZ), y)
	$(Q)echo "CPU_CLOCK = 936" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_948MHZ), y)
	$(Q)echo "CPU_CLOCK = 948" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_984MHZ), y)
	$(Q)echo "CPU_CLOCK = 984" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1008MHZ), y)
	$(Q)echo "CPU_CLOCK = 1008" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1044MHZ), y)
	$(Q)echo "CPU_CLOCK = 1044" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1100MHZ), y)
	$(Q)echo "CPU_CLOCK = 1100" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1152MHZ), y)
	$(Q)echo "CPU_CLOCK = 1152" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1400MHZ), y)
	$(Q)echo "CPU_CLOCK = 1400" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1450MHZ), y)
	$(Q)echo "CPU_CLOCK = 1450" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_CPU_1700MHZ), y)
	$(Q)echo "CPU_CLOCK = 1700" >> $(BOOT1_INC)
endif
else
	$(Q)echo "CPU_CLOCK = $(CONFIG_MSTAR_OTHERS)" >> $(BOOT1_INC)
endif

ifeq ($(CONFIG_MSTAR_GPU_MANUAL), y)
	$(Q)echo "GPU_CLOCK = $(CONFIG_MSTAR_GPU_OTHERS)" >> $(BOOT1_INC)
endif


ifeq ($(CONFIG_EMMC_BOOT), y)
	$(Q)echo "EMMC_BOOT = 1" >> $(BOOT1_INC)
else
	$(Q)echo "EMMC_BOOT = 0" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_SBOOT_TO_KERNEL), y)
	$(Q)$(AWK) -f scripts/find-kernel-entry.awk $(SYSTEM_MAP) >> $(BOOT1_INC)
	$(Q)echo "SBOOT_TO_KERNEL = 1" >> $(BOOT1_INC)
	$(Q)printf "SIZE_KERNEL = 0x%08X\n" `ls -Gl $(KERNEL_BIN) | $(AWK) '{ print $$4 }'` >> $(BOOT1_INC)
else
	$(Q)echo "SBOOT_TO_KERNEL = 0" >> $(BOOT1_INC)
endif
ifeq ($(CONFIG_MSTAR_TITANIA_BD_FPGA), y)
	$(Q)echo "FPGA_BOARD = 1" >> $(BOOT1_INC)
else
	$(Q)echo "FPGA_BOARD = 0" >> $(BOOT1_INC)
endif

ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51), y)
	$(Q)echo "BOOTING_FROM_EXT_SPI_WITH_PM51 = 1" >> $(BOOT1_INC)
else
	$(Q)echo "BOOTING_FROM_EXT_SPI_WITH_PM51 = 0" >> $(BOOT1_INC)
endif
	$(Q)printf "SIZE_UBOOT = 0x%08X\n" `ls -Gl $(UBOOT_BIN) | $(AWK) '{ print $$4 }'` >> $(BOOT1_INC)
	$(Q)echo "  GEN     out/security.inc"
	$(Q)echo "#This file is auto created. Do not modify!" > $(SECURITY_INC)
	$(Q)$(AWK) '$$2 == "ENABLE_SECURITY_BOOT" { print "ENABLE_MODULE_SECURITY_BOOT = " $$3 }' $(AUTOCONF_H) >> $(SECURITY_INC)
endif

define ALIGN
$$((($(1)+$(2)-1)&(~($(2)-1))))
endef

#####################################################################
#######         CREATE CHUNK HEADER INFORMATION START          ######
#####################################################################
##   Chunk Header parameter initialize START ##
UBOOT_ROM_START = 0
UBOOT_RAM_START = 0
UBOOT_RAM_END = 0
UBOOT_ROM_END = 0
UBOOT_RAM_ENTRY = 0
Reserved1 = 0
Reserved2 = 0x00000301
BINARY_ID = 0x0000B007
LOGO_ROM_OFFSET = 0
LOGO_SIZE = 0
SBOOT_ROM_OFFSET = 0
SBOOT_SIZE = 0x10000
SBOOT_RAM_OFFSET = 0
PM_ROM_OFFSET = 0
PM_SIZE = 0x10000
PM_RAM_OFFSET = 0
SECURITY_INFO_LOADER_ROM_OFFSET = 4
SECURITY_INFO_LOADER_SIZE = 0
SECURITY_INFO_LOADER_RAM_OFFSET = 0
CUSTOMER_KEY_BANK_ROM_OFFSET = 0
CUSTOMER_KEY_BANK_SIZE = 0
CUSTOMER_KEY_BANK_RAM_OFFSET =0
## In PM code, "0xFFFFFFFF" is the default value of DDR_BACKUP_TABLE_ROM_OFFSET.
## If this flag is not 0xFFFFFFFF, it will triger the PM code to do something.
DDR_BACKUP_TABLE_ROM_OFFSET = 0xFFFFFFFF
POWER_SEQUENCE_TABLE_ROM_OFFSET = 0
SECURITY_INFO_AP_ROM_OFFSET = 0
SECURITY_INFO_AP_SIZE = 0
UBOOT_ENVIRONMENT_ROM_OFFSET = 2
UBOOT_ENVIRONMENT_SIZE = 0x10000
UBOOT_POOL_ROM_OFFSET = 0
UBOOT_POOL_SIZE = 0
COPROBOOT_ROM_OFFSET = 0
COPROBOOT_SIZE = 0
RT_AEON_ROM_OFFSET = 0
RT_AEON_SIZE = 0
NUTTX_CONFIG_OFFSET = 0
NUTTX_CONFIG_SIZE = 0
MBOOT_CONFIG_BINARY_OFFSET = 0
MBOOT_CONFIG_BINARY_SIZE = 0
RESCURE_ENVIRONMENT_ROM_OFFSET = 0
RESCURE_ENVIRONMENT_SIZE = 0x10000
RESCURE_STATUS_ROM_OFFSET = 0
RESCURE_STATUS_SIZE = 0
MAX_CONFIG_BINARY_SIZE = 0x1000
SECURITY_SIZE = 0
##   Chunk Header parameter initialize END  ##

UBOOT_SIZE = $(shell ls -Gl $(UBOOT_BIN) | $(AWK) '{ print $$4 }')

ifeq ($(CONFIG_SECURITY_BOOT), y)
SECURITY_SIZE  = $(shell ls -Gl $(SECURITY_BIN) | $(AWK) '{ print $$4 }')
endif

ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
COPROBOOT_SIZE = $(shell ls -Gl $(CLEANBOOT_BIN) | $(AWK) '{ print $$4 }')
else ifeq ($(CONFIG_MSTAR_PUMABOOT),y)
ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU), y)
COPROBOOT_SIZE = $(CONFIG_PUMABOOT_SIZE)
CHUNK_HEADER_START = $$((0x20000 + $(CONFIG_PUMABOOT_SIZE)))
endif
endif

ifeq ($(CONFIG_MSTAR_RUNTIMEAEON),y)
RT_AEON_SIZE = $(shell ls -Gl $(RT_AEON_BIN) | $(AWK) '{ print $$4 }')
endif

ifeq ($(CONFIG_BINARY_RELEASE),y)
MBOOT_CONFIG_BINARY_SIZE = $(shell [ -f $(MCONFIG_BIN) ] && ls -Gl $(MCONFIG_BIN) | $(AWK) '{ print $$4 }' || echo 0)
endif

ifeq ($(CONFIG_COMPRESSED_UBOOT), y)
ORI_UBOOT_SIZE = $(shell ls -Gl $(UBOOT_BIN).nocompress | $(AWK) '{ print $$4 }')
else
ORI_UBOOT_SIZE = $(UBOOT_SIZE)
endif

CHUNK_HEADER_SIZE = 1024
CUS_KEYBANK_LEN = 0x1000
ifeq ($(ARCH),aeon)
SPI_BASE=0x00000000
RAM_BASE=0x00000000
else ifeq ($(ARCH),mips)
ifeq ($(CONFIG_MSTAR_KAISERIN),y)
SPI_BASE=0x94000000
else
SPI_BASE=0xBFC00000
endif
RAM_BASE=0x20000000
else ifeq ($(ARCH),arm)
SPI_BASE=0x14000000
RAM_BASE=$(CONFIG_MIU0_BUSADDR)
endif

ifeq ($(CONFIG_MSTAR_RT_PM_IN_SPI),y)
PM_SIZE           		= 0x20000
endif

ifneq ($(CONFIG_PM_SIZE_KB_FORCED),0)
_SIZE_1K=0x400
PM_SIZE=$$(($(CONFIG_PM_SIZE_KB_FORCED)*$(_SIZE_1K)))
endif

ifeq ($(CONFIG_ENV_IN_MMC),y)
UBOOT_ENVIRONMENT_ROM_OFFSET = 256
endif

ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51),y)
CUSTOMER_KEY_BANK_SIZE              = 0x10000
endif

MBOOT_ALIGNMENT_SIZE = 0x10000
ifeq ($(CONFIG_MBOOT_IN_SPI_FLASH),y)
MBOOT_ALIGNMENT_SIZE = 0x10000
else ifeq ($(CONFIG_MBOOT_IN_NAND_FLASH),y)
MBOOT_ALIGNMENT_SIZE = 0x10000
else ifeq ($(CONFIG_MBOOT_IN_MMC_FLASH),y)
MBOOT_ALIGNMENT_SIZE = 0x200
endif

ifeq ($(CONFIG_SECURITY_BOOT), y)
ifeq ($(CONFIG_SECURITY_STORE_IN_SPI_FLASH),y)
	SECURITY_INFO_AP_ROM_OFFSET = 4
else ifeq ($(CONFIG_SECURITY_STORE_IN_NAND_FLASH),y)
	SECURITY_INFO_AP_ROM_OFFSET = 4
else ifeq ($(CONFIG_SECURITY_STORE_IN_EMMC_FLASH),y)
	SECURITY_INFO_AP_ROM_OFFSET = 352
endif
endif

ifeq ($(CONFIG_R2_BRINGUP),y)
ifeq ($(CONFIG_TEE),y)
ifeq ($(CONFIG_NCONFIG_STORE_IN_EMMC_FLASH),y)
	NUTTX_CONFIG_OFFSET = 608
	NUTTX_CONFIG_SIZE = 128
else ifeq ($(CONFIG_NCONFIG_STORE_IN_NAND_FLASH),y)
 	NUTTX_CONFIG_OFFSET = 6
	NUTTX_CONFIG_SIZE = 1
else ifeq ($(CONFIG_NCONFIG_STORE_IN_SPI_FLASH),y)
	NUTTX_CONFIG_OFFSET = 6
	NUTTX_CONFIG_SIZE = 1
endif
endif
endif

ifeq ($(CONFIG_RESCUE_ENV),y)
ifeq ($(CONFIG_TEE),y)
	ifeq ($(CONFIG_ENV_IN_SERIAL),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 8
		RESCURE_STATUS_ROM_OFFSET = 9
	else ifeq ($(CONFIG_ENV_IN_NAND),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 8
		RESCURE_STATUS_ROM_OFFSET = 9
	else ifeq ($(CONFIG_ENV_IN_MMC),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 1120
		RESCURE_STATUS_ROM_OFFSET = 1121
	endif
else ifeq ($(CONFIG_SECURITY_BOOT),y)
	ifeq ($(CONFIG_ENV_IN_SERIAL),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 6
		RESCURE_STATUS_ROM_OFFSET = 7
	else ifeq ($(CONFIG_ENV_IN_NAND),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 6
		RESCURE_STATUS_ROM_OFFSET = 7
	else ifeq ($(CONFIG_ENV_IN_MMC),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 864
		RESCURE_STATUS_ROM_OFFSET = 865
	endif
else
	ifeq ($(CONFIG_ENV_IN_SERIAL),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 4
		RESCURE_STATUS_ROM_OFFSET = 5
	else ifeq ($(CONFIG_ENV_IN_NAND),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 4
		RESCURE_STATUS_ROM_OFFSET = 5
	else ifeq ($(CONFIG_ENV_IN_MMC),y)
		RESCURE_ENVIRONMENT_ROM_OFFSET = 608
		RESCURE_STATUS_ROM_OFFSET = 609
	endif
endif
endif


ifeq ($(CHIP_FOLDER), janus)
_UBOOT_RAM_START            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
UBOOT_RAM_ENTRY            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
else  ifeq ($(CHIP_FOLDER), maria10)
_UBOOT_RAM_START            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
UBOOT_RAM_ENTRY            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
else ifeq ($(CHIP_FOLDER), macaw12)
_UBOOT_RAM_START            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
UBOOT_RAM_ENTRY            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
else ifeq ($(CONFIG_MCU_ARM),y)
UBOOT_RAM_ENTRY            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
_UBOOT_RAM_START            = $$(($(UBOOT_RAM_ENTRY)-$(RAM_BASE)))
else
_UBOOT_RAM_START            = $(shell $(AWK) '$$2 == "other_vector" { print $$1 }' $(UBOOT_MAP))
UBOOT_RAM_ENTRY            = $(shell $(AWK) '$$2 == "_start" { print $$1 }' $(UBOOT_MAP))
endif

	UBOOT_RAM_START=$$(($(_UBOOT_RAM_START)+$(RAM_BASE)))
	UBOOT_RAM_END=$$(($(_UBOOT_RAM_START)+$(ORI_UBOOT_SIZE)+$(RAM_BASE)))

ifeq ($(CONFIG_BOOTING_FROM_OTP_WITH_PM51),y)
	SECURITY_INFO_LOADER_SIZE = 816
	PM_ROM_OFFSET=$(SPI_BASE)
	PM_RAM_OFFSET=$(CONFIG_PM_DRAM_ADDRESS)
	SBOOT_ROM_OFFSET=$$(($(PM_ROM_OFFSET)+$(PM_SIZE)))
	SBOOT_RAM_OFFSET=$(shell $(AWK) '$$2 == "_ld_boot_start" { print $$1 }' $(SBOOT_MAP))
	CUSTOMER_KEY_BANK_ROM_OFFSET=$$(($(SBOOT_ROM_OFFSET)+$(SBOOT_SIZE)))
	CUSTOMER_KEY_BANK_RAM_OFFSET=$(CONFIG_CUSTOMER_KEY_BANK_DRAM_ADDRESS)
    ## Remember Chunk Header
	UBOOT_ROM_START=$$(($(CUSTOMER_KEY_BANK_ROM_OFFSET)+$(CUSTOMER_KEY_BANK_SIZE)+$(CHUNK_HEADER_SIZE)))
	UBOOT_ROM_END=$$(($(UBOOT_ROM_START)+$(UBOOT_SIZE)))
	SECURITY_INFO_LOADER_ROM_OFFSET=$(UBOOT_ROM_END)
	SECURITY_INFO_LOADER_RAM_OFFSET=$(CONFIG_SECURITY_INFO_DRAM_ADDRESS)
else ifeq (y, $(findstring y, $(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)\
  							  $(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)))
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
	UBOOT_ROM_START=$$(($(CHUNK_HEADER_SIZE)+$(HASH3_SIZE)))
else
	UBOOT_ROM_START=$(CHUNK_HEADER_SIZE)
endif
	UBOOT_ROM_END=$$(($(UBOOT_ROM_START)+$(UBOOT_SIZE)))
	ifeq ($(CONFIG_SECURITY_BOOT), y)
	SECURITY_INFO_LOADER_SIZE = 272
	SECURITY_INFO_LOADER_ROM_OFFSET=$(UBOOT_ROM_END)
	_CUSTOMER_KEY_BANK_ROM_OFFSET=$$(($(SECURITY_INFO_LOADER_ROM_OFFSET)+$(SECURITY_INFO_LOADER_SIZE)))
	CUSTOMER_KEY_BANK_ROM_OFFSET=$(call ALIGN,$(_CUSTOMER_KEY_BANK_ROM_OFFSET),$(MBOOT_ALIGNMENT_SIZE))
	endif
	ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
	ifeq ($(CONFIG_SECURITY_BOOT), y)
	COPROBOOT_ROM_OFFSET=$$(($(CUSTOMER_KEY_BANK_ROM_OFFSET)+$(SECURITY_SIZE)))
	else
	COPROBOOT_ROM_OFFSET=$(UBOOT_ROM_END)
	endif
	endif
	ifeq ($(CONFIG_MSTAR_RUNTIMEAEON),y)
	RT_AEON_ROM_OFFSET=$(UBOOT_ROM_END)
	ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
	RT_AEON_ROM_OFFSET=$$(($(COPROBOOT_ROM_OFFSET)+$(COPROBOOT_SIZE)))
	endif
	ifeq ($(CONFIG_SECURITY_BOOT), y)
	RT_AEON_ROM_OFFSET=$$(($(CUSTOMER_KEY_BANK_ROM_OFFSET)+$(SECURITY_SIZE)))
	endif
	endif
else
	SBOOT_ROM_OFFSET=$$(($(PM_ROM_OFFSET)+$(PM_SIZE)))
	CUSTOMER_KEY_BANK_ROM_OFFSET=$$(($(PM_ROM_OFFSET)+$(SBOOT_SIZE)+$(PM_SIZE)))
        ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
	UBOOT_ROM_START=$$(($(PM_SIZE)+$(SBOOT_SIZE)+$(COPROBOOT_SIZE)+$(CUSTOMER_KEY_BANK_SIZE)+$(CHUNK_HEADER_SIZE)+$(SPI_BASE)))
	else ifeq ($(CONFIG_MSTAR_PUMABOOT),y)
        ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU), y)
	UBOOT_ROM_START=$$(($(PM_SIZE)+$(SBOOT_SIZE)+$(COPROBOOT_SIZE)+$(CUSTOMER_KEY_BANK_SIZE)+$(CHUNK_HEADER_SIZE)+$(SPI_BASE)))
        endif
        else
	UBOOT_ROM_START=$$(($(PM_SIZE)+$(SBOOT_SIZE)+$(CUSTOMER_KEY_BANK_SIZE)+$(CHUNK_HEADER_SIZE)+$(SPI_BASE)))
        endif
	UBOOT_ROM_END=$$(($(UBOOT_ROM_START)+$(UBOOT_SIZE)))
    ifeq ($(CONFIG_LOGO_STORE_IN_SPI_FLASH),y)
	ifeq ($(CONFIG_BINARY_RELEASE),y)
	MBOOT_CONFIG_BINARY_OFFSET = $$(((($(UBOOT_ROM_END)+$(SECURITY_INFO_LOADER_SIZE)+0x10000)&(~0xFFFF))-$(SPI_BASE)))
	UBOOT_POOL_ROM_OFFSET = $$(($(MBOOT_CONFIG_BINARY_OFFSET)+$(MAX_CONFIG_BINARY_SIZE)))
	else
	UBOOT_POOL_ROM_OFFSET = $$(((($(UBOOT_ROM_END)+$(RT_AEON_SIZE)+$(COPROBOOT_SIZE)+$(SECURITY_INFO_LOADER_SIZE)+0x10000)&(~0xFFFF))-$(SPI_BASE)))
	endif
    endif
endif

ifeq ($(CONFIG_LOGO_STORE_IN_MBOOT),y)
	LOGO_SIZE=$(shell ls -Gl $(LOGO_SRC) | $(AWK) '{ print $$4 }')
    _LOGO_ROM_OFFSET=$$(($(UBOOT_ROM_END)+$(SECURITY_INFO_LOADER_SIZE)+$(SECURITY_SIZE)+$(COPROBOOT_SIZE)))
    ifeq ($(CONFIG_MBOOT_IN_SPI_FLASH),y)
	LOGO_ROM_OFFSET=$$(($(call ALIGN,$(_LOGO_ROM_OFFSET),$(MBOOT_ALIGNMENT_SIZE)) - $(SPI_BASE)))
    else
	LOGO_ROM_OFFSET=$$(($(call ALIGN,$(_LOGO_ROM_OFFSET),$(MBOOT_ALIGNMENT_SIZE))))
    endif
endif

ifeq ($(CONFIG_BACKUP_SENSITIVE_TABLE), y)
DDR_BACKUP_TABLE_ROM_OFFSET=$(CONFIG_SPI_OFFSET_OF_BACKUP_TABLE)
endif

$(CHUNK_HEADER):
	$(Q)echo "  GEN     $@"
	$(Q)printf "== CHUNK HEADER INFO ==\n"
	$(Q)printf "UBOOT_ROM_START=0x%x\n" $(UBOOT_ROM_START)
	$(Q)printf "UBOOT_RAM_START=0x%x\n" $(UBOOT_RAM_START)
	$(Q)printf "UBOOT_RAM_END=0x%x\n" $(UBOOT_RAM_END)
	$(Q)printf "UBOOT_ROM_END=0x%x\n" $(UBOOT_ROM_END)
	$(Q)printf "UBOOT_RAM_ENTRY=0x%x\n" $(UBOOT_RAM_ENTRY)
	$(Q)printf "Reserved1=0x%x\n" $(Reserved1)
	$(Q)printf "Reserved2=0x%x\n" $(Reserved2)
	$(Q)printf "BINARY_ID=0x%x\n" $(BINARY_ID)
	$(Q)printf "LOGO_ROM_OFFSET=0x%x\n" $(LOGO_ROM_OFFSET)
	$(Q)printf "LOGO_SIZE=0x%x\n" $(LOGO_SIZE)
	$(Q)printf "SBOOT_ROM_OFFSET=0x%x\n" $(SBOOT_ROM_OFFSET)
	$(Q)printf "SBOOT_SIZE=0x%x\n" $(SBOOT_SIZE)
	$(Q)printf "SBOOT_RAM_OFFSET=0x%x\n" $(SBOOT_RAM_OFFSET)
	$(Q)printf "PM_ROM_OFFSET=0x%x\n" $(PM_ROM_OFFSET)
	$(Q)printf "PM_SIZE=0x%x\n" $(PM_SIZE)
	$(Q)printf "PM_RAM_OFFSET=0x%x\n" $(PM_RAM_OFFSET)
	$(Q)printf "SECURITY_INFO_LOADER_ROM_OFFSET=0x%x\n" $(SECURITY_INFO_LOADER_ROM_OFFSET)
	$(Q)printf "SECURITY_INFO_LOADER_SIZE=0x%x\n" $(SECURITY_INFO_LOADER_SIZE)
	$(Q)printf "SECURITY_INFO_LOADER_RAM_OFFSET=0x%x\n" $(SECURITY_INFO_LOADER_RAM_OFFSET)
	$(Q)printf "CUSTOMER_KEY_BANK_ROM_OFFSET=0x%x\n" $(CUSTOMER_KEY_BANK_ROM_OFFSET)
	$(Q)printf "CUSTOMER_KEY_BANK_SIZE=0x%x\n" $(CUSTOMER_KEY_BANK_SIZE)
	$(Q)printf "CUSTOMER_KEY_BANK_RAM_OFFSET=0x%x\n" $(CUSTOMER_KEY_BANK_RAM_OFFSET)
	$(Q)printf "DDR_BACKUP_TABLE_ROM_OFFSET=0x%x\n" $(DDR_BACKUP_TABLE_ROM_OFFSET)
	$(Q)printf "POWER_SEQUENCE_TABLE_ROM_OFFSET=0x%x\n" $(POWER_SEQUENCE_TABLE_ROM_OFFSET)
	$(Q)printf "SECURITY_INFO_AP_ROM_OFFSET=0x%x\n" $(SECURITY_INFO_AP_ROM_OFFSET)
	$(Q)printf "SECURITY_INFO_AP_SIZE=0x%x\n" $(SECURITY_INFO_AP_SIZE)
	$(Q)printf "UBOOT_ENVIRONMENT_ROM_OFFSET=0x%x\n" $(UBOOT_ENVIRONMENT_ROM_OFFSET)
	$(Q)printf "UBOOT_ENVIRONMENT_SIZE=0x%x\n" $(UBOOT_ENVIRONMENT_SIZE)
	$(Q)printf "UBOOT_POOL_ROM_OFFSET=0x%x\n" $(UBOOT_POOL_ROM_OFFSET)
	$(Q)printf "UBOOT_POOL_SIZE=0x%x\n" $(UBOOT_POOL_SIZE)
	$(Q)printf "COPROBOOT_ROM_OFFSET=0x%x\n" $(COPROBOOT_ROM_OFFSET)
	$(Q)printf "COPROBOOT_SIZE=0x%x\n" $(COPROBOOT_SIZE)
	$(Q)printf "RUNTIMEAEON_ROM_OFFSET=0x%x\n" $(RT_AEON_ROM_OFFSET)
	$(Q)printf "RUNTIMEAEON_SIZE=0x%x\n" $(RT_AEON_SIZE)
	$(Q)printf "NUTTX_CONFIG_OFFSET=0x%x\n" $(NUTTX_CONFIG_OFFSET)
	$(Q)printf "NUTTX_CONFIG_SIZE=0x%x\n" $(NUTTX_CONFIG_SIZE)
	$(Q)printf "MBOOT_CONFIG_BINARY_OFFSET=0x%x\n" $(MBOOT_CONFIG_BINARY_OFFSET)
	$(Q)printf "MBOOT_CONFIG_BINARY_SIZE=0x%x\n" $(MBOOT_CONFIG_BINARY_SIZE)
	$(Q)printf "RESCURE_ENVIRONMENT_ROM_OFFSET=0x%x\n" $(RESCURE_ENVIRONMENT_ROM_OFFSET)
	$(Q)printf "RESCURE_ENVIRONMENT_SIZE=0x%x\n" $(RESCURE_ENVIRONMENT_SIZE)
	$(Q)printf "RESCURE_STATUS_ROM_OFFSET=0x%x\n" $(RESCURE_STATUS_ROM_OFFSET)
	$(Q)printf "RESCURE_STATUS_SIZE=0x%x\n" $(RESCURE_STATUS_SIZE)

	$(Q)$(TOOLDIR)/create_chunk_header.exe $@ $(CHUNK_HEADER_SIZE)\
               $(UBOOT_ROM_START) $(UBOOT_RAM_START) $(UBOOT_RAM_END) $(UBOOT_ROM_END) \
               $(UBOOT_RAM_ENTRY) $(Reserved1) $(Reserved2) $(BINARY_ID) \
			   $(LOGO_ROM_OFFSET) $(LOGO_SIZE) $(SBOOT_ROM_OFFSET) $(SBOOT_SIZE) \
			   $(SBOOT_RAM_OFFSET) $(PM_ROM_OFFSET) $(PM_SIZE)	$(PM_RAM_OFFSET) \
			   $(SECURITY_INFO_LOADER_ROM_OFFSET) $(SECURITY_INFO_LOADER_SIZE) $(SECURITY_INFO_LOADER_RAM_OFFSET) $(CUSTOMER_KEY_BANK_ROM_OFFSET)\
			   $(CUSTOMER_KEY_BANK_SIZE) $(CUSTOMER_KEY_BANK_RAM_OFFSET) $(SECURITY_INFO_AP_ROM_OFFSET) $(SECURITY_INFO_AP_SIZE)  \
			   $(UBOOT_ENVIRONMENT_ROM_OFFSET) $(UBOOT_ENVIRONMENT_SIZE) $(DDR_BACKUP_TABLE_ROM_OFFSET) $(POWER_SEQUENCE_TABLE_ROM_OFFSET) \
			   $(UBOOT_POOL_ROM_OFFSET) $(UBOOT_POOL_SIZE) $(COPROBOOT_ROM_OFFSET) $(COPROBOOT_SIZE) \
			   $(RT_AEON_ROM_OFFSET) $(RT_AEON_SIZE) $(NUTTX_CONFIG_OFFSET) $(NUTTX_CONFIG_SIZE) \
			   $(MBOOT_CONFIG_BINARY_OFFSET) $(MBOOT_CONFIG_BINARY_SIZE) $(RESCURE_ENVIRONMENT_ROM_OFFSET) $(RESCURE_ENVIRONMENT_SIZE) \
			   $(RESCURE_STATUS_ROM_OFFSET) $(RESCURE_STATUS_SIZE)

#######           CREATE  CHUNK HEADER INFORMATION END              ######

# Generate System.map
quiet_cmd_sysmap = SYSMAP
      cmd_sysmap = $(CONFIG_SHELL) $(srctree)/scripts/mksysmap

# Link of sboot
# If CONFIG_KALLSYMS is set .version is already updated
# Generate System.map and verify that the content is consistent
# Use + in front of the sboot_version rule to silent warning with make -j2
# First command is ':' to allow us to use + in front of the rule
define rule_sboot__
	:
	$(call cmd,sboot__)
	$(Q)echo 'cmd_$@ := $(cmd_sboot__)' > $(@D)/.$(@F).cmd
endef


ifdef CONFIG_KALLSYMS
# Generate section listing all symbols and add it into sboot $(kallsyms.o)
# It's a three stage process:
# o .tmp_sboot1 has all symbols and sections, but __kallsyms is
#   empty
#   Running kallsyms on that gives us .tmp_kallsyms1.o with
#   the right size - sboot version (uname -v) is updated during this step
# o .tmp_sboot2 now has a __kallsyms section of the right size,
#   but due to the added section, some addresses have shifted.
#   From here, we generate a correct .tmp_kallsyms2.o
# o The correct .tmp_kallsyms2.o is linked into the final sboot.
# o Verify that the System.map from sboot matches the map from
#   .tmp_sboot2, just in case we did not generate kallsyms correctly.
# o If CONFIG_KALLSYMS_EXTRA_PASS is set, do an extra pass using
#   .tmp_sboot3 and .tmp_kallsyms3.o.  This is only meant as a
#   temporary bypass to allow the kernel to be built while the
#   maintainers work out what went wrong with kallsyms.

ifdef CONFIG_KALLSYMS_EXTRA_PASS
last_kallsyms := 3
else
last_kallsyms := 2
endif

kallsyms.o := .tmp_kallsyms$(last_kallsyms).o

define verify_kallsyms
	$(Q)$(if $($(quiet)cmd_sysmap),                       \
	  echo '  $($(quiet)cmd_sysmap) .tmp_System.map' &&)  \
	  $(cmd_sysmap) .tmp_sboot$(last_kallsyms) .tmp_System.map
	$(Q)cmp -s System.map .tmp_System.map ||              \
		(echo Inconsistent kallsyms data;             \
		 echo Try setting CONFIG_KALLSYMS_EXTRA_PASS; \
		 rm .tmp_kallsyms* ; /bin/false )
endef

# Update sboot version before link
# Use + in front of this rule to silent warning about make -j1
# First command is ':' to allow us to use + in front of this rule
cmd_ksym_ld = $(cmd_sboot__)
define rule_ksym_ld
	:
	+$(call cmd,sboot_version)
	$(call cmd,sboot__)
	$(Q)echo 'cmd_$@ := $(cmd_sboot__)' > $(@D)/.$(@F).cmd
endef

# Generate .S file with all kernel symbols
quiet_cmd_kallsyms = KSYM    $@
      cmd_kallsyms = $(NM) -n $< | $(KALLSYMS) \
                     $(if $(CONFIG_KALLSYMS_ALL),--all-symbols) > $@

.tmp_kallsyms1.o .tmp_kallsyms2.o .tmp_kallsyms3.o: %.o: %.S scripts FORCE
	$(call if_changed_dep,as_o_S)

.tmp_kallsyms%.S: .tmp_sboot% $(KALLSYMS)
	$(call cmd,kallsyms)

# .tmp_sboot1 must be complete except kallsyms, so update sboot version
.tmp_sboot1: $(sboot-lds) $(sboot-all) FORCE
	$(call if_changed_rule,ksym_ld)

.tmp_sboot2: $(sboot-lds) $(sboot-all) .tmp_kallsyms1.o FORCE
	$(call if_changed,sboot__)

.tmp_sboot3: $(sboot-lds) $(sboot-all) .tmp_kallsyms2.o FORCE
	$(call if_changed,sboot__)

# Needs to visit scripts/ before $(KALLSYMS) can be used.
$(KALLSYMS): scripts ;

# Generate some data for debugging strange kallsyms problems
debug_kallsyms: .tmp_map$(last_kallsyms)

.tmp_map%: .tmp_sboot% FORCE
	($(OBJDUMP) -h $< | $(AWK) '/^ +[0-9]/{print $$4 " 0 " $$2}'; $(NM) $<) | sort > $@

.tmp_map3: .tmp_map2

.tmp_map2: .tmp_map1

endif # ifdef CONFIG_KALLSYMS

# sboot image - including updated kernel symbols
ifeq ($(CONFIG_NON_OS), y)
out/sboot.elf: out $(BOOT1_INC) $(sboot-all) FORCE
else
ifeq ($(CONFIG_BOOTING_FROM_OTP_WITH_PM51),y)
out/sboot.elf: out $(BOOT1_INC) $(sboot-all) FORCE
else
out/sboot.elf: out $(BOOT1_INC) $(CHUNK_HEADER) $(sboot-all) FORCE
endif
endif
	$(call if_changed_rule,sboot__)
	$(Q)rm -f .old_version
	$(Q)$(OBJDUMP) -S $@ > out/sboot.dis
	$(Q)size $@ > out/sboot.siz

ifndef CONFIG_STATIC_SBOOT
ifeq ($(CONFIG_MSTAR_MARIA10_PM),y)
out/PM.bin: out/sboot.elf
else ifeq ($(CONFIG_MSTAR_MACAW12_PM),y)
out/PM.bin: out/sboot.elf
else ifeq ($(CONFIG_MSTAR_EDEN_PM),y)
out/PM.bin: out/sboot.elf
else ifeq ($(CONFIG_MSTAR_EULER_PM),y)
out/PM.bin: out/sboot.elf
else ifeq ($(CONFIG_MSTAR_NASA_PM),y)
out/PM.bin: out/sboot.elf
else ifeq ($(CONFIG_BOOTING_FROM_OTP_WITH_PM51),y)
out/sboot.bin: out/sboot.elf lint $(CHUNK_HEADER)
else
out/sboot.bin: out/sboot.elf lint
endif

	$(Q)$(OBJCOPY) -O binary -I elf32-little $< $@
ifneq ($(BINARY_RELEASE_FLAG),y)
	$(Q)$(HOSTCC) -o ./scripts/pad_version ./scripts/pad_version.c
endif
	$(Q)./scripts/pad_version $@
else
out/sboot.bin: out $(BOOT1_INC) $(CHUNK_HEADER) static-sboot
endif

ifeq ($(CONFIG_ROM_BOOTING_ENABLE), yes)
ifeq ($(CONFIG_MSTAR_NUGGET),y)
ifeq ($(CONFIG_MSTAR_AUTHEN_ENABLE), y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(AUT_BIN) $(CONFIG_BOOT_AUT_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_AUT_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)
endif
endif

ifeq ($(CONFIG_MSTAR_NIKE),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_MADISON),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_CLIPPERS),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_MIAMI),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_MONET),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_MONACO),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH3_BIN) $(CONFIG_BOOT_HASH3_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH3_IMAGE_SIZE)
endif
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH3_BIN) $(RSA_BOOT_PRIVATE_KEY)
endif
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_MUJI),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_CELTICS),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_NADAL),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_EDISON),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN_SZ) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_EIFFEL),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
        ifeq ($(CONFIG_REAL_KEY),y)
	$(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/rsa_sign_boot.sh  $(PROJDIR)/$(HASH1_BIN)  $(PROJDIR)/out $(PROJECT) $(PROJDIR)/secure
	$(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/rsa_sign_boot.sh  $(PROJDIR)/$(HASH1_STR_BIN)  $(PROJDIR)/out $(PROJECT) $(PROJDIR)/secure
	$(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/rsa_sign_boot.sh  $(PROJDIR)/$(HASH1_MIU_BIN)  $(PROJDIR)/out $(PROJECT) $(PROJDIR)/secure
	$(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/rsa_sign_boot.sh  $(PROJDIR)/$(HASH2_BIN)  $(PROJDIR)/out $(PROJECT) $(PROJDIR)/secure
        else
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
        endif
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_EINSTEIN),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(AUT_BIN) $(CONFIG_BOOT_AUT_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_AUT_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_EINSTEIN3),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)scripts/append_signature.pl $(AUT_BIN) $(CONFIG_BOOT_AUT_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_AUT_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

ifeq ($(CONFIG_MSTAR_NAPOLI),y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_BIN) $(CONFIG_BOOT_HASH1_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_MIU_BIN) $(CONFIG_BOOT_HASH1_MIU_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_MIU_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_STR_BIN) $(CONFIG_BOOT_HASH1_STR_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_STR_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH1_DESKEW_BIN) $(CONFIG_BOOT_HASH1_DESKEW_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH1_DESKEW_IMAGE_SIZE)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH2_BIN) $(CONFIG_BOOT_HASH2_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH2_IMAGE_SIZE)
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
	$(Q)$(TOOLDIR)/SeparateBin.exe $(SBOOT_BIN) $(HASH3_BIN) $(CONFIG_BOOT_HASH3_OFFSET_ADDRESS) $(CONFIG_BOOT_HASH3_IMAGE_SIZE)
endif
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_STR_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_MIU_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH1_DESKEW_BIN) $(RSA_BOOT_PRIVATE_KEY)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH2_BIN) $(RSA_BOOT_PRIVATE_KEY)
ifeq ($(CONFIG_DOUBLE_MBOOT), y)
	$(Q)$(SECUREDIR)/rsa_sign $(HASH3_BIN) $(RSA_BOOT_PRIVATE_KEY)
endif
	$(Q)scripts/append_signature.pl $(AUT_BIN) $(CONFIG_BOOT_AUT_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_AUT_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_MIU_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_MIU_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_STR_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_STR_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH1_DESKEW_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH1_DESKEW_SIG_ADDRESS)
	$(Q)scripts/append_signature.pl $(HASH2_SIG) $(CONFIG_BOOT_SIG_IMAGE_SIZE) $(SBOOT_BIN) $(CONFIG_BOOT_HASH2_SIG_ADDRESS)

ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
    ifeq ($(CONFIG_FOXCONN_ENABLE),y)
	$(Q)cp $(HASH0_BIN_SZ) $(EMMC_BOOT_BIN);
    else 
	$(Q)cp $(HASH0_BIN) $(EMMC_BOOT_BIN);
    endif
	$(Q)$(TOOLDIR)/MergeBin.exe $(SBOOT_BIN) $(EMMC_BOOT_BIN) $(CONFIG_BOOT_HASH0_IMAGE_SIZE)
endif
endif

endif

#
## ROM Layout:
#   SBOOT_BIN (boot + bootrom + bootram (nandflash+drvNAND_SLC+uart16550))
#   CHUNK_HEADER
#	UBOOT_BIN
#   DUMMY_BIN (if needed)
#	CHUNK 1, 2, ... 16
#
ifeq ($(CONFIG_SBOOT_TO_KERNEL), y)
ifeq ($(CONFIG_KERNEL_3_0_20), y)
SYSTEM_MAP =  ../../../THEALE/RedLion/3.0.20/System.map
KERNEL_BIN      = ../../../THEALE/RedLion/3.0.20/arch/arm/boot/zImage
KERNEL_COMPRESSED_BIN      = ../../../THEALE/RedLion/3.0.20/arch/arm/boot/zImage.lzo
else
ifeq ($(CONFIG_KERNEL_2_6_35_11), y)
SYSTEM_MAP =  ../../../THEALE/RedLion/2.6.35.11/System.map
KERNEL_BIN      = ../../../THEALE/RedLion/2.6.35.11/arch/arm/boot/zImage
KERNEL_COMPRESSED_BIN      = ../../../THEALE/RedLion/2.6.35.11/arch/arm/boot/zImage.lzo
else
ifeq ($(CONFIG_KERNEL_2_6_28_9), y)
SYSTEM_MAP =  ../../../THEALE/RedLion/2.6.28.9/System.map
KERNEL_BIN      = ../../../THEALE/RedLion/2.6.28.9/arch/mips/boot/vmlinux.bin
KERNEL_COMPRESSED_BIN      = ../../../THEALE/RedLion/2.6.28.9/arch/mips/boot/uImage.lzo
else
ifeq ($(CONFIG_KERNEL_3_10_23), y)
SYSTEM_MAP =  ../../../THEALE/RedLion/3.10.23/System.map
KERNEL_BIN      = ../../../THEALE/RedLion/3.10.23/arch/arm/boot/zImage
KERNEL_COMPRESSED_BIN      = ../../../THEALE/RedLion/3.10.23/arch/arm/boot/zImage.lzo
else ifeq ($(CONFIG_KERNEL_3_1_10), y)
SYSTEM_MAP =  ../../../THEALE/RedLion/3.1.10/System.map

ifeq ($(ARCH),mips)
    KERNEL_BIN = ../../../THEALE/RedLion/3.1.10/arch/mips/boot/vmlinux.bin
    KERNEL_COMPRESSED_BIN = ../../../THEALE/RedLion/3.1.10/arch/mips/boot/uImage.lzo
else ifeq ($(ARCH),arm)
    KERNEL_BIN      = ../../../THEALE/RedLion/3.1.10/arch/arm/boot/zImage
    KERNEL_COMPRESSED_BIN      = ../../../THEALE/RedLion/3.1.10/arch/arm/boot/zImage.lzo
else
endif

else
SYSTEM_MAP = ../../../THEALE/RedLion/2.6.32.15/kernel/System.map
KERNEL_BIN      = ../../../THEALE/RedLion/2.6.32.15/kernel/arch/mips/boot/vmlinux.bin
KERNEL_COMPRESSED_BIN      = ../../../THEALE/RedLion/2.6.32.15/kernel/arch/mips/boot/uImage.lzo
endif
endif
endif
endif

out/sboot2knl.bin: out/sboot.bin
ifneq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU), y)
ifneq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH), y)
	cat $(PM_BIN) > $@
endif
endif
	cat $< > $@; \
	cat $(KERNEL_BIN) >> $@;
endif

ifeq ($(CONFIG_NON_OS), y)
ifeq ($(CONFIG_MSTAR_MARIA10_PM),y)
out/mboot.bin: out/PM.bin
else ifeq ($(CONFIG_MSTAR_MACAW12_PM),y)
out/mboot.bin: out/PM.bin
else ifeq ($(CONFIG_MSTAR_EDEN_PM),y)
out/mboot.bin: out/PM.bin
else ifeq ($(CONFIG_MSTAR_EULER_PM),y)
out/mboot.bin: out/PM.bin
else ifeq ($(CONFIG_MSTAR_NASA_PM),y)
out/mboot.bin: out/PM.bin
else
out/mboot.bin: out/sboot.bin
endif
else
out/mboot.bin: out/sboot.bin
	$(Q)echo "  MERGE   $@"
ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU),y)
	$(Q)cat $< > $@;
ifneq ($(CONFIG_PM_SIZE_KB_FORCED),0)
	$(Q)cp $(PM_BIN) ./_PM.bin
	$(Q)dd if=./_PM.bin of=./PM.bin bs=$(CONFIG_PM_SIZE_KB_FORCED)K count=1 1>/dev/null
	$(Q)cat ./PM.bin >> $@;
	$(Q)rm -f ./PM.bin
else
	$(Q)cat $(PM_BIN) >> $@;
endif
    ifeq ($(CONFIG_MSTAR_RT_PM_IN_SPI),y)
	$(Q)cat $(RT_PM_BIN) >> $@;
	$(Q)echo "   MERGE   RT_PM_BIN $(RT_PM_BIN)"
    endif
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH), y)
	$(Q)cat $< > $@;
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH), y)
	$(Q)[ '-f $@' ] && rm -rf $@
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_FOR_BUILD_PM_BIN), y)
	$(Q)cat $< > $@;
	$(Q)cat $(PM_BIN) >> $@;
else #boot from 51
	$(Q)echo "  PM_BIN: $(PM_BIN)"
	$(Q)cat $(PM_BIN) > $@;
	$(Q)cat $< >> $@;
	$(Q)cat $(SECURITY_BIN) >> $@;
endif

ifeq (y, $(findstring y, $(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)\
                         $(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)))


    ifeq ($(CONFIG_MSTAR_AUTHEN_ENABLE), y)
	$(Q)head -c 752 $(CHUNK_HEADER) > $(CHUNK_HEADER).tmp
	$(Q)mv $(CHUNK_HEADER).tmp $(CHUNK_HEADER)
        ifeq ($(CONFIG_REAL_KEY),y)
	    $(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/SubSecureInfoGen_boot.sh $(PROJDIR)/$(CHUNK_HEADER).signature.bin $(PROJDIR)/$(CHUNK_HEADER) 1 $(PROJECT) $(PROJDIR)/secure 0 8 0 $(BLOCK_SIZE) 0
        else
	    $(Q)$(SECUREDIR)/SubSecureInfoGen.exe $(CHUNK_HEADER).signature.bin $(CHUNK_HEADER) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 8 0 $(BLOCK_SIZE) 0 $(SECUREDIR)
        endif
	$(Q)cat $(CHUNK_HEADER).signature.bin >> $(CHUNK_HEADER)
    endif
	$(Q)cat $(CHUNK_HEADER)>> $@;
    ifeq ($(CONFIG_DOUBLE_MBOOT), y)
	$(TOOLDIR)/align $@ $(MBOOT_ALIGNMENT_SIZE);
	$(Q)cat $(HASH3_BIN)>> $@;
	$(Q)cat $(HASH3_SIG)>> $@;
	$(TOOLDIR)/align $@ $(MBOOT_ALIGNMENT_SIZE);
    endif
	$(Q)cat $(UBOOT_BIN) >> $@;
ifeq (y, $(findstring y, $(CONFIG_DOUBLE_MBOOT)\
                         $(CONFIG_SECURITY_BOOT)))
        ifeq ($(CONFIG_REAL_KEY),y)
	    $(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/SubSecureInfoGen_boot.sh $(PROJDIR)/$(UBOOT_BIN).signature.bin $(PROJDIR)/$(UBOOT_BIN) 1 $(PROJECT) $(PROJDIR)/secure 0 8 0 $(BLOCK_SIZE) 0
        else
	    $(Q)$(SECUREDIR)/SubSecureInfoGen.exe $(UBOOT_BIN).signature.bin $(UBOOT_BIN) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 8 0 $(BLOCK_SIZE) 0 $(SECUREDIR)
        endif
	$(Q)cat $(UBOOT_BIN).signature.bin >> $@
	$(TOOLDIR)/align $@ $(MBOOT_ALIGNMENT_SIZE);
    endif
    ifeq ($(CONFIG_SECURITY_BOOT), y)
	$(Q)cat $(SECURITY_BIN) >> $@
    endif
    ifeq ($(CONFIG_MSTAR_CLEANBOOT),y)
	$(Q)cat $(CLEANBOOT_BIN) >> $@
	$(Q)echo "   MERGE   CleanBoot $(CLEANBOOT_BIN)"
    ifeq ($(CONFIG_SECURITY_BOOT), y)
        ifeq ($(CONFIG_REAL_KEY),y)
	    $(Q)$(TOOL_PATH)/grid.sh $(TOOL_PATH)/SubSecureInfoGen_boot.sh $(PROJDIR)/$(CLEANBOOT_BIN).signature.bin $(PROJDIR)/$(CLEANBOOT_BIN) 1 $(PROJECT) $(PROJDIR)/secure 0 8 0 $(BLOCK_SIZE) 0
        else
	    $(Q)$(SECUREDIR)/SubSecureInfoGen.exe $(CLEANBOOT_BIN).signature.bin $(CLEANBOOT_BIN) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 8 0 $(BLOCK_SIZE 0 $(SECUREDIR)
        endif
	$(Q)cat $(CLEANBOOT_BIN).signature.bin >> $@
	$(Q)rm $(CLEANBOOT_BIN).signature.bin
    endif
    endif
    ifeq ($(CONFIG_MSTAR_RUNTIMEAEON), y)
	$(Q)cat $(RT_AEON_BIN) >> $@;
	$(Q)echo "   MERGE   Runtime AEON $(RT_AEON_BIN)"
    endif
else
    ifeq ($(CONFIG_MSTAR_PUMABOOT),y)
        ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU), y)
	$(Q)cat $(PUMABOOT_BIN) >> $@;
	$(Q)echo "   MERGE   PumaBoot $(PUMABOOT_BIN)";
	$(Q)$(TOOLDIR)/MergeBin.exe $(CHUNK_HEADER) $@ $(CHUNK_HEADER_START);
	$(Q)cat $(UBOOT_BIN) >> $@;
        endif
    else
	$(Q)cat $(CHUNK_HEADER)>> $@;
	$(Q)cat $(UBOOT_BIN) >> $@;
    endif

        ifeq ($(CONFIG_BINARY_RELEASE),y)
	    $(Q)if [ -f $(MCONFIG_BIN) ] && [ $(MBOOT_CONFIG_BINARY_SIZE) -ne 0 ] ; then \
	        $(TOOLDIR)/align $@ $(MBOOT_ALIGNMENT_SIZE);\
                cat $(MCONFIG_BIN) >> $@; \
	    fi
        endif
endif

	$(Q)if [ $(LOGO_SIZE) != 0 ] ; then \
		   $(TOOLDIR)/align $@ $(MBOOT_ALIGNMENT_SIZE);\
		   cat $(LOGO_BIN) >> $@;\
        fi

ifeq ($(CONFIG_BOOTING_FROM_OTP_WITH_PM51),y)
	$(Q)[ '-f $(SIGNATURE_PM)' ] && rm -rf $(SIGNATURE_PM)
	$(Q) $(SECUREDIR)/SubSecureInfoGen.exe $(SIGNATURE_PM) ./$(PM_BIN) $(PM_RAM_OFFSET) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 $(SECUREDIR)
	$(Q)[ '-f $(SIGNATURE_SBOOT)' ] && rm -rf $(SIGNATURE_SBOOT)
	$(Q) $(SECUREDIR)/SubSecureInfoGen.exe $(SIGNATURE_SBOOT) ./out/sboot.bin $(SBOOT_RAM_OFFSET) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 $(SECUREDIR)
	$(Q)[ '-f $(SIGNATURE_UBOOT)' ] && rm -rf $(SIGNATURE_UBOOT)
	$(Q) $(SECUREDIR)/SubSecureInfoGen.exe $(SIGNATURE_UBOOT) ./$(UBOOT_BIN) $(_UBOOT_RAM_START) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 $(SECUREDIR)
	$(Q)cat $(SIGNATURE_PM) >> $@
	$(Q)cat $(SIGNATURE_SBOOT) >> $@
	$(Q)cat $(SIGNATURE_UBOOT) >> $@
endif
ifneq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU),y)
	$(Q) split -d -a 4 -b "65536" $@ ./out/keybank.
	$(Q) cp ./out/keybank.0002 ./out/customer_key_bank.bin
	$(Q) rm ./out/keybank.*
endif
	$(Q)$(TOOLDIR)/SeparateBin.exe $(PM_BIN) ./out/$(DDR_BACKUP_BIN) 0xF200 0xE00
	$(Q)$(SECUREDIR)/crc -a ./out/$(DDR_BACKUP_BIN);

ifeq ($(PARA),1)
	@rm -f ./MBoot.bdf*
	@find ../ -name "*.bdf" -exec cat {} >> ./MBoot.bdf.tmp \;
	@mv ./MBoot.bdf.tmp ./MBoot.bdf
endif
endif

ifeq ($(CONFIG_NON_OS), y)
ifeq ($(CONFIG_MSTAR_MARIA10_PM),y)
out/mboot_rom.bin: out/PM.bin
else ifeq ($(CONFIG_MSTAR_MACAW12_PM),y)
out/mboot_rom.bin: out/PM.bin
else
out/mboot_rom.bin: out/sboot.bin out/sboot1.bin
endif
else
out/mboot_rom.bin: out/sboot.bin out/sboot1.bin
	$(Q)echo "  MERGE   $@"
ifeq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU),y)
	$(Q)cat $< > $@;
	$(Q)cat $(SBOOT1_BIN) >> $@;
	#$(Q)cat $(PM_BIN) >> $@;
else ifeq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH), y)
	$(Q)cat $< > $@;
	$(Q)cat $(SBOOT1_BIN) >> $@;
	#$(Q)cat $(PM_BIN) >> $@;
else
	$(Q)cat $(PM_BIN) > $@;
	$(Q)cat $< >> $@;
	$(Q)cat $(SECURITY_BIN) >> $@;
endif
	cat $(CHUNK_HEADER) >> $@; \
	cat $(UBOOT_BIN) >> $@; \
	if [ $(LOGO_SIZE) != 0 ] ; then \
            $(TOOLDIR)/align $@ $(MBOOT_ALIGNMENT_SIZE);\
            cat $(LOGO_BIN) >> $@; \
        fi

ifeq ($(CONFIG_BOOTING_FROM_OTP_WITH_PM51),y)
	$(Q)[ '-f $(SIGNATURE_PM)' ] && rm -rf $(SIGNATURE_PM)
	$(Q) $(SECUREDIR)/SubSecureInfoGen.exe $(SIGNATURE_PM) ./$(PM_BIN) $(PM_RAM_OFFSET) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 $(SECUREDIR)
	$(Q)[ '-f $(SIGNATURE_SBOOT)' ] && rm -rf $(SIGNATURE_SBOOT)
	$(Q) $(SECUREDIR)/SubSecureInfoGen.exe $(SIGNATURE_SBOOT) ./out/sboot.bin $(SBOOT_RAM_OFFSET) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 $(SECUREDIR)
	$(Q)[ '-f $(SIGNATURE_UBOOT)' ] && rm -rf $(SIGNATURE_UBOOT)
	$(Q) $(SECUREDIR)/SubSecureInfoGen.exe $(SIGNATURE_UBOOT) ./$(UBOOT_BIN) $(_UBOOT_RAM_START) $(RSA_BOOT_PRIVATE_KEY) $(RSA_BOOT_PUBLIC_KEY) 0 $(SECUREDIR)
	$(Q)cat $(SIGNATURE_PM) >> $@
	$(Q)cat $(SIGNATURE_SBOOT) >> $@
	$(Q)cat $(SIGNATURE_UBOOT) >> $@
endif
ifneq ($(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU),y)
ifneq ($(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH), y)
	$(Q) split -d -a 4 -b "65536" $@ ./out/keybank.
	$(Q) cp ./out/keybank.0002 ./out/customer_key_bank.bin
	$(Q) rm ./out/keybank.*
endif
endif
	$(Q)$(TOOLDIR)/SeparateBin.exe $(PM_BIN) ./out/$(DDR_BACKUP_BIN) 0xF200 0xE00
	$(Q)$(SECUREDIR)/crc -a ./out/$(DDR_BACKUP_BIN);

ifeq ($(PARA),1)
	@rm -f ./MBoot.bdf*
	@find ../ -name "*.bdf" -exec cat {} >> ./MBoot.bdf.tmp \;
	@mv ./MBoot.bdf.tmp ./MBoot.bdf
endif
endif

sboot: sboot_unstripped
ifeq ($(SKIP_STRIP),y)
	$(Q)cp $< $@
else
	$(Q)$(STRIP) -s --remove-section=.note --remove-section=.comment \
		sboot_unstripped -o $@
# strip is confused by PIE executable and does not set exec bits
	$(Q)chmod a+x $@
endif

# The actual objects are generated when descending,
# make sure no implicit rule kicks in
$(sort $(sboot-all)): $(sboot-dirs) ;

# Handle descending into subdirectories listed in $(sboot-dirs)
# Preset locale variables to speed up the build process. Limit locale
# tweaks to this spot to avoid wrong language settings when running
# make menuconfig etc.
# Error messages still appears in the original language

PHONY += $(sboot-dirs)
#ifeq ($(BINARY_RELEASE_FLAG),y)
#$(sboot-dirs): prepare scripts
#else
$(sboot-dirs): prepare scripts
	$(Q)$(MAKE) $(build)=$@
#endif

# Build the kernel release string
# The KERNELRELEASE is stored in a file named .kernelrelease
# to be used when executing for example make install or make modules_install
#
# Take the contents of any files called localversion* and the config
# variable CONFIG_LOCALVERSION and append them to KERNELRELEASE.
# LOCALVERSION from the command line override all of this

nullstring :=
space      := $(nullstring) # end of line

___localver = $(objtree)/localversion* $(srctree)/localversion*
__localver  = $(sort $(wildcard $(___localver)))
# skip backup files (containing '~')
_localver = $(foreach f, $(__localver), $(if $(findstring ~, $(f)),,$(f)))

localver = $(subst $(space),, \
	   $(shell cat /dev/null $(_localver)) \
	   $(patsubst "%",%,$(CONFIG_LOCALVERSION)))

# If CONFIG_LOCALVERSION_AUTO is set scripts/setlocalversion is called
# and if the SCM is know a tag from the SCM is appended.
# The appended tag is determinded by the SCM used.
#
# Currently, only git is supported.
# Other SCMs can edit scripts/setlocalversion and add the appropriate
# checks as needed.
ifdef _BB_DISABLED_CONFIG_LOCALVERSION_AUTO
	_localver-auto = $(shell $(CONFIG_SHELL) \
	                  $(srctree)/scripts/setlocalversion $(srctree))
	localver-auto  = $(LOCALVERSION)$(_localver-auto)
endif

localver-full = $(localver)$(localver-auto)

# Store (new) KERNELRELASE string in .kernelrelease
kernelrelease = $(KERNELVERSION)$(localver-full)
.kernelrelease: FORCE
	$(Q)rm -f $@
	$(Q)echo $(kernelrelease) > $@


# Things we need to do before we recursively start building the kernel
# or the modules are listed in "prepare".
# A multi level approach is used. prepareN is processed before prepareN-1.
# archprepare is used in arch Makefiles and when processed asm symlink,
# version.h and scripts_basic is processed / created.

# Listed in dependency order
PHONY += prepare archprepare prepare0 prepare1 prepare2 prepare3

# prepare-all is deprecated, use prepare as valid replacement
PHONY += prepare-all

# prepare3 is used to check if we are building in a separate output directory,
# and if so do:
# 1) Check that make has not been executed in the kernel src $(srctree)
# 2) Create the include2 directory, used for the second asm symlink
prepare3: .kernelrelease
ifneq ($(KBUILD_SRC),)
	@echo '  Using $(srctree) as source for sboot'
	$(Q)if [ -f $(srctree)/.config ]; then \
		echo "  $(srctree) is not clean, please run 'make mrproper'";\
		echo "  in the '$(srctree)' directory.";\
		/bin/false; \
	fi;
	$(Q)if [ ! -d include2 ]; then mkdir -p include2; fi;
	$(Q)ln -fsn $(srctree)/include/asm-$(ARCH) include2/asm
endif

# prepare2 creates a makefile if using a separate output directory
prepare2: prepare3 outputmakefile

prepare1: prepare2 include/config/MARKER
ifneq ($(KBUILD_MODULES),)
	$(Q)mkdir -p $(MODVERDIR)
	$(Q)rm -f $(MODVERDIR)/*
endif

archprepare: prepare1 scripts_basic

prepare0: archprepare FORCE
	$(Q)$(MAKE) $(build)=.

# All the preparing..
prepare prepare-all: prepare0

#	Leave this as default for preprocessing sboot.lds.S, which is now
#	done in arch/$(ARCH)/kernel/Makefile

export CPPFLAGS_sboot.lds += -P -C -U$(ARCH)

# 	FIXME: The asm symlink changes when $(ARCH) changes. That's
#	hard to detect, but I suppose "make mrproper" is a good idea
#	before switching between archs anyway.

#bbox# include/asm:
#bbox# 	@echo '  SYMLINK $@ -> include/asm-$(ARCH)'
#bbox# 	$(Q)if [ ! -d include ]; then mkdir -p include; fi;
#bbox# 	@ln -fsn asm-$(ARCH) $@

# 	Split autoconf.h into include/linux/config/*
quiet_cmd_gen_bbconfigopts = GEN     include/bbconfigopts.h
      cmd_gen_bbconfigopts = $(srctree)/scripts/mkconfigs > include/bbconfigopts.h
quiet_cmd_split_autoconf   = SPLIT   include/autoconf.h -> include/config/*
      cmd_split_autoconf   = scripts/basic/split-include include/autoconf.h include/config
#bbox# piggybacked generation of few .h files
include/config/MARKER: scripts/basic/split-include include/autoconf.h
	$(call cmd,split_autoconf)
	$(call cmd,gen_bbconfigopts)
	@touch $@

# Generate some files
# ---------------------------------------------------------------------------

# KERNELRELEASE can change from a few different places, meaning version.h
# needs to be updated, so this check is forced on all builds

uts_len := 64

define filechk_version.h
	if [ `echo -n "$(KERNELRELEASE)" | wc -c ` -gt $(uts_len) ]; then \
	  echo '"$(KERNELRELEASE)" exceeds $(uts_len) characters' >&2; \
	  exit 1; \
	fi; \
	(echo \#define UTS_RELEASE \"$(KERNELRELEASE)\"; \
	  echo \#define LINUX_VERSION_CODE `expr $(VERSION) \\* 65536 + $(PATCHLEVEL) \\* 256 + $(SUBLEVEL)`; \
	 echo '#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))'; \
	)
endef

# ---------------------------------------------------------------------------

PHONY += depend dep
depend dep:
	@echo '*** Warning: make $@ is unnecessary now.'

# ---------------------------------------------------------------------------
# Modules

ifdef _BB_DISABLED_CONFIG_MODULES

# 	By default, build modules as well

all: modules

#	Build modules

PHONY += modules
modules: $(sboot-dirs) $(if $(KBUILD_BUILTIN),sboot)
	@echo '  Building modules, stage 2.';
	$(Q)$(MAKE) -rR -f $(srctree)/scripts/Makefile.modpost


# Target to prepare building external modules
PHONY += modules_prepare
modules_prepare: prepare scripts

# Target to install modules
PHONY += modules_install
modules_install: _modinst_ _modinst_post

PHONY += _modinst_
_modinst_:
	@if [ -z "`$(DEPMOD) -V 2>/dev/null | grep module-init-tools`" ]; then \
		echo "Warning: you may need to install module-init-tools"; \
		echo "See http://www.codemonkey.org.uk/docs/post-halloween-2.6.txt";\
		sleep 1; \
	fi
	@rm -rf $(MODLIB)/kernel
	@rm -f $(MODLIB)/source
	@mkdir -p $(MODLIB)/kernel
	@ln -s $(srctree) $(MODLIB)/source
	@if [ ! $(objtree) -ef  $(MODLIB)/build ]; then \
		rm -f $(MODLIB)/build ; \
		ln -s $(objtree) $(MODLIB)/build ; \
	fi
	$(Q)$(MAKE) -rR -f $(srctree)/scripts/Makefile.modinst

# If System.map exists, run depmod.  This deliberately does not have a
# dependency on System.map since that would run the dependency tree on
# sboot.  This depmod is only for convenience to give the initial
# boot a modules.dep even before / is mounted read-write.  However the
# boot script depmod is the master version.
ifeq "$(strip $(INSTALL_MOD_PATH))" ""
depmod_opts	:=
else
depmod_opts	:= -b $(INSTALL_MOD_PATH) -r
endif
PHONY += _modinst_post
_modinst_post: _modinst_
	if [ -r System.map -a -x $(DEPMOD) ]; then $(DEPMOD) -ae -F System.map $(depmod_opts) $(KERNELRELEASE); fi

else # CONFIG_MODULES

# Modules not configured
# ---------------------------------------------------------------------------

modules modules_install: FORCE
	@echo
	@echo "The present sboot configuration has modules disabled."
	@echo "Type 'make config' and enable loadable module support."
	@echo "Then build a kernel with module support enabled."
	@echo
	@exit 1

endif # CONFIG_MODULES

###
# Cleaning is done on three levels.
# make clean     Delete most generated files
#                Leave enough to build external modules
# make mrproper  Delete the current configuration, and all generated files
# make distclean Remove editor backup files, patch leftover files and the like

# Directories & files removed with 'make clean'
CLEAN_DIRS  += $(MODVERDIR) _install 0_lib out src/compat51
ifeq ($(BINARY_RELEASE_FLAG),y)
CLEAN_FILES +=	sboot out/sboot.elf* \
                .tmp_kallsyms* .tmp_version .tmp_sboot* .tmp_System.map
else
CLEAN_FILES +=	sboot out/sboot.elf* sboot.links \
                System.map .kernelrelease sboot_ldscript \
                .tmp_kallsyms* .tmp_version .tmp_sboot* .tmp_System.map
endif

# Directories & files removed with 'make mrproper'
MRPROPER_DIRS  += include/config include2
MRPROPER_FILES += .config .config.old include/asm .version .old_version \
		  include/autoconf.h \
		  include/bbconfigopts.h \
		  include/usage_compressed.h \
		  include/applet_tables.h \
		  applets/usage \
		  .kernelrelease Module.symvers tags TAGS cscope* \
		  sboot_old

# clean - Delete most, but leave enough to build external modules
#
clean: rm-dirs  := $(CLEAN_DIRS)
clean: rm-files := $(CLEAN_FILES)
clean-dirs      := $(addprefix _clean_,$(srctree) $(sboot-alldirs))

PHONY += $(clean-dirs) clean archclean
$(clean-dirs):
	$(Q)$(MAKE) $(clean)=$(patsubst _clean_%,%,$@)

clean: archclean $(clean-dirs)
ifneq ($(CONFIG_NON_OS), y)
	$(Q)make -C ../$(_PROJ)/ distclean
endif
	$(call cmd,rmdirs)
	$(call cmd,rmfiles)
ifneq ($(BINARY_RELEASE_FLAG),y)
	@find . $(RCS_FIND_IGNORE) \
		\( -name '*.[oas]' -o -name '*.ko' -o -name '.*.cmd' \
		-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \) \
		-type f -print | xargs rm -f
endif
ifeq ($(PARA),1)
	@find ../ -name "*.bdf" -exec rm -f {} \;
endif

PHONY += doc-clean
doc-clean: rm-files := docs/sboot.pod \
		  docs/sboot.html docs/sboot.1 docs/sboot.txt
doc-clean:
	$(call cmd,rmfiles)

# mrproper - Delete all generated files, including .config
#
mrproper: rm-dirs  := $(wildcard $(MRPROPER_DIRS))
mrproper: rm-files := $(wildcard $(MRPROPER_FILES))
mrproper-dirs      := $(addprefix _mrproper_,scripts)

PHONY += $(mrproper-dirs) mrproper archmrproper
$(mrproper-dirs):
	$(Q)$(MAKE) $(clean)=$(patsubst _mrproper_%,%,$@)

mrproper: clean archmrproper $(mrproper-dirs)
	$(call cmd,rmdirs)
	$(call cmd,rmfiles)

# distclean
#
PHONY += distclean

distclean: mrproper
ifneq ($(CONFIG_NON_OS), y)
	$(Q)make -C ../$(_PROJ)/ distclean
endif
ifneq ($(BINARY_RELEASE_FLAG),y)
	@find $(srctree) $(RCS_FIND_IGNORE) \
		\( -name '*.orig' -o -name '*.rej' -o -name '*~' \
		-o -name '*.bak' -o -name '#*#' -o -name '.*.orig' \
		-o -name '.*.rej' -o -name '*.tmp' -o -size 0 \
		-o -name '*%' -o -name '.*.cmd' -o -name 'core' \) \
		-type f -print | xargs rm -f
endif


# Packaging of the kernel to various formats
# ---------------------------------------------------------------------------
# rpm target kept for backward compatibility
package-dir	:= $(srctree)/scripts/package

%pkg: FORCE
	$(Q)$(MAKE) $(build)=$(package-dir) $@
rpm: FORCE
	$(Q)$(MAKE) $(build)=$(package-dir) $@


# Brief documentation of the typical targets used
# ---------------------------------------------------------------------------

boards := $(wildcard $(srctree)/arch/$(ARCH)/configs/*_defconfig)
boards := $(notdir $(boards))

-include $(srctree)/Makefile.help

# Documentation targets
# ---------------------------------------------------------------------------
%docs: scripts_basic FORCE
	$(Q)$(MAKE) $(build)=Documentation/DocBook $@

else # KBUILD_EXTMOD

###
# External module support.
# When building external modules the kernel used as basis is considered
# read-only, and no consistency checks are made and the make
# system is not used on the basis kernel. If updates are required
# in the basis kernel ordinary make commands (without M=...) must
# be used.
#
# The following are the only valid targets when building external
# modules.
# make M=dir clean     Delete all automatically generated files
# make M=dir modules   Make all modules in specified dir
# make M=dir	       Same as 'make M=dir modules'
# make M=dir modules_install
#                      Install the modules build in the module directory
#                      Assumes install directory is already created

# We are always building modules
KBUILD_MODULES := 1
PHONY += crmodverdir
crmodverdir:
	$(Q)mkdir -p $(MODVERDIR)
	$(Q)rm -f $(MODVERDIR)/*

PHONY += $(objtree)/Module.symvers
$(objtree)/Module.symvers:
	@test -e $(objtree)/Module.symvers || ( \
	echo; \
	echo "  WARNING: Symbol version dump $(objtree)/Module.symvers"; \
	echo "           is missing; modules will have no dependencies and modversions."; \
	echo )

module-dirs := $(addprefix _module_,$(KBUILD_EXTMOD))
PHONY += $(module-dirs) modules
$(module-dirs): crmodverdir $(objtree)/Module.symvers
	$(Q)$(MAKE) $(build)=$(patsubst _module_%,%,$@)

modules: $(module-dirs)
	@echo '  Building modules, stage 2.';
	$(Q)$(MAKE) -rR -f $(srctree)/scripts/Makefile.modpost

PHONY += modules_install
modules_install: _emodinst_ _emodinst_post

install-dir := $(if $(INSTALL_MOD_DIR),$(INSTALL_MOD_DIR),extra)
PHONY += _emodinst_
_emodinst_:
	$(Q)mkdir -p $(MODLIB)/$(install-dir)
	$(Q)$(MAKE) -rR -f $(srctree)/scripts/Makefile.modinst

# Run depmod only is we have System.map and depmod is executable
quiet_cmd_depmod = DEPMOD  $(KERNELRELEASE)
      cmd_depmod = if [ -r System.map -a -x $(DEPMOD) ]; then \
                      $(DEPMOD) -ae -F System.map             \
                      $(if $(strip $(INSTALL_MOD_PATH)),      \
		      -b $(INSTALL_MOD_PATH) -r)              \
		      $(KERNELRELEASE);                       \
                   fi

PHONY += _emodinst_post
_emodinst_post: _emodinst_
	$(call cmd,depmod)

clean-dirs := $(addprefix _clean_,$(KBUILD_EXTMOD))

PHONY += $(clean-dirs) clean
$(clean-dirs):
	$(Q)$(MAKE) $(clean)=$(patsubst _clean_%,%,$@)

clean:	rm-dirs := $(MODVERDIR)
clean: $(clean-dirs)
	$(call cmd,rmdirs)
	@find $(KBUILD_EXTMOD) $(RCS_FIND_IGNORE) \
		\( -name '*.[oas]' -o -name '*.ko' -o -name '.*.cmd' \
		-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \) \
		-type f -print | xargs rm -f

help:
	@echo  '  Building external modules.'
	@echo  '  Syntax: make -C path/to/kernel/src M=$$PWD target'
	@echo  ''
	@echo  '  modules         - default target, build the module(s)'
	@echo  '  modules_install - install the module'
	@echo  '  clean           - remove generated files in module directory only'
	@echo  ''

# Dummies...
PHONY += prepare scripts
prepare: ;
scripts: ;
endif # KBUILD_EXTMOD

# Generate tags for editors
# ---------------------------------------------------------------------------

#We want __srctree to totally vanish out when KBUILD_OUTPUT is not set
#(which is the most common case IMHO) to avoid unneeded clutter in the big tags file.
#Adding $(srctree) adds about 20M on i386 to the size of the output file!

ifeq ($(src),$(obj))
__srctree =
else
__srctree = $(srctree)/
endif

ifeq ($(ALLSOURCE_ARCHS),)
ifeq ($(ARCH),um)
ALLINCLUDE_ARCHS := $(ARCH) $(SUBARCH)
else
ALLINCLUDE_ARCHS := $(ARCH)
endif
else
#Allow user to specify only ALLSOURCE_PATHS on the command line, keeping existing behaviour.
ALLINCLUDE_ARCHS := $(ALLSOURCE_ARCHS)
endif

ALLSOURCE_ARCHS := $(ARCH)

define all-sources
	( find $(__srctree) $(RCS_FIND_IGNORE) \
	       \( -name include -o -name arch \) -prune -o \
	       -name '*.[chS]' -print; \
	  for ARCH in $(ALLSOURCE_ARCHS) ; do \
	       find $(__srctree)arch/$${ARCH} $(RCS_FIND_IGNORE) \
	            -name '*.[chS]' -print; \
	  done ; \
	  find $(__srctree)security/selinux/include $(RCS_FIND_IGNORE) \
	       -name '*.[chS]' -print; \
	  find $(__srctree)include $(RCS_FIND_IGNORE) \
	       \( -name config -o -name 'asm-*' \) -prune \
	       -o -name '*.[chS]' -print; \
	  for ARCH in $(ALLINCLUDE_ARCHS) ; do \
	       find $(__srctree)include/asm-$${ARCH} $(RCS_FIND_IGNORE) \
	            -name '*.[chS]' -print; \
	  done ; \
	  find $(__srctree)include/asm-generic $(RCS_FIND_IGNORE) \
	       -name '*.[chS]' -print )
endef

quiet_cmd_cscope-file = FILELST cscope.files
      cmd_cscope-file = (echo \-k; echo \-q; $(all-sources)) > cscope.files

quiet_cmd_cscope = MAKE    cscope.out
      cmd_cscope = cscope -b

cscope: FORCE
	$(call cmd,cscope-file)
	$(call cmd,cscope)

quiet_cmd_TAGS = MAKE   $@
define cmd_TAGS
	rm -f $@; \
	ETAGSF=`etags --version | grep -i exuberant >/dev/null &&     \
                echo "-I __initdata,__exitdata,__acquires,__releases  \
                      -I EXPORT_SYMBOL,EXPORT_SYMBOL_GPL              \
                      --extra=+f --c-kinds=+px"`;                     \
                $(all-sources) | xargs etags $$ETAGSF -a
endef

TAGS: FORCE
	$(call cmd,TAGS)


quiet_cmd_tags = MAKE   $@
define cmd_tags
	rm -f $@; \
	CTAGSF=`ctags --version | grep -i exuberant >/dev/null &&     \
                echo "-I __initdata,__exitdata,__acquires,__releases  \
                      -I EXPORT_SYMBOL,EXPORT_SYMBOL_GPL              \
                      --extra=+f --c-kinds=+px"`;                     \
                $(all-sources) | xargs ctags $$CTAGSF -a
endef

tags: FORCE
	$(call cmd,tags)


# Scripts to check various things for consistency
# ---------------------------------------------------------------------------

includecheck:
	find * $(RCS_FIND_IGNORE) \
		-name '*.[hcS]' -type f -print | sort \
		| xargs $(PERL) -w scripts/checkincludes.pl

versioncheck:
	find * $(RCS_FIND_IGNORE) \
		-name '*.[hcS]' -type f -print | sort \
		| xargs $(PERL) -w scripts/checkversion.pl

namespacecheck:
	$(PERL) $(srctree)/scripts/namespace.pl

endif #ifeq ($(config-targets),1)
endif #ifeq ($(mixed-targets),1)

PHONY += checkstack
checkstack:
	$(OBJDUMP) -d sboot $$(find . -name '*.ko') | \
	$(PERL) $(src)/scripts/checkstack.pl $(ARCH)

kernelrelease:
	$(if $(wildcard .kernelrelease), $(Q)echo $(KERNELRELEASE), \
	$(error kernelrelease not valid - run 'make *config' to update it))
kernelversion:
	@echo $(KERNELVERSION)

# Single targets
# ---------------------------------------------------------------------------
# Single targets are compatible with:
# - build whith mixed source and output
# - build with separate output dir 'make O=...'
# - external modules
#
#  target-dir => where to store outputfile
#  build-dir  => directory in kernel source tree to use

ifeq ($(KBUILD_EXTMOD),)
        build-dir  = $(patsubst %/,%,$(dir $@))
        target-dir = $(dir $@)
else
        zap-slash=$(filter-out .,$(patsubst %/,%,$(dir $@)))
        build-dir  = $(KBUILD_EXTMOD)$(if $(zap-slash),/$(zap-slash))
        target-dir = $(if $(KBUILD_EXTMOD),$(dir $<),$(dir $@))
endif

%.s: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.i: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.o: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.lst: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.s: %.S prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.o: %.S prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)

# Modules
/: prepare scripts FORCE
	$(Q)$(MAKE) KBUILD_MODULES=$(if $(CONFIG_MODULES),1) \
	$(build)=$(build-dir)
%/: prepare scripts FORCE
	$(Q)$(MAKE) KBUILD_MODULES=$(if $(CONFIG_MODULES),1) \
	$(build)=$(build-dir)
%.ko: prepare scripts FORCE
	$(Q)$(MAKE) KBUILD_MODULES=$(if $(CONFIG_MODULES),1)   \
	$(build)=$(build-dir) $(@:.ko=.o)
	$(Q)$(MAKE) -rR -f $(srctree)/scripts/Makefile.modpost

# FIXME Should go into a make.lib or something
# ===========================================================================

quiet_cmd_rmdirs = $(if $(wildcard $(rm-dirs)),CLEAN   $(wildcard $(rm-dirs)))
      cmd_rmdirs = rm -rf $(rm-dirs)

quiet_cmd_rmfiles = $(if $(wildcard $(rm-files)),CLEAN   $(wildcard $(rm-files)))
      cmd_rmfiles = rm -f $(rm-files)


a_flags = -Wp,-MD,$(depfile) $(AFLAGS) $(AFLAGS_KERNEL) \
	  $(NOSTDINC_FLAGS) $(CPPFLAGS) \
	  $(modkern_aflags) $(EXTRA_AFLAGS) $(AFLAGS_$(*F).o)

quiet_cmd_as_o_S = AS      $@
cmd_as_o_S       = $(CC) $(a_flags) -c -o $@ $<

# read all saved command lines

targets := $(wildcard $(sort $(targets)))
cmd_files := $(wildcard .*.cmd $(foreach f,$(targets),$(dir $(f)).$(notdir $(f)).cmd))

ifneq ($(cmd_files),)
  $(cmd_files): ;	# Do not try to update included dependency files
  include $(cmd_files)
endif

# Shorthand for $(Q)$(MAKE) -f scripts/Makefile.clean obj=dir
# Usage:
# $(Q)$(MAKE) $(clean)=dir
clean := -f $(if $(KBUILD_SRC),$(srctree)/)scripts/Makefile.clean obj

endif	# skip-makefile

PHONY += FORCE
FORCE:

-include $(srctree)/Makefile.custom

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable se we can use it in if_changed and friends.
.PHONY: $(PHONY)

#LINT_SRC_C +=  $(addprefix ../${PROJ}/src/, $(sort $(notdir $(wildcard src/*.c))))
#LINT_SRC_C +=  $(addprefix ../${PROJ}/src/, $(sort $(notdir $(wildcard src/*.s))))
#LINT_SRC_C +=  $(addprefix ../${PROJ}/src/$(CHIP_FOLDER)/, $(sort $(notdir $(wildcard src/$(CHIP_FOLDER)/*.c))))
#LINT_SRC_C +=  $(addprefix ../${PROJ}/src/$(CHIP_FOLDER)/, $(sort $(notdir $(wildcard src/$(CHIP_FOLDER)/*.s))))
#LINT_INC+= $(subst -I,,$(addprefix ../${PROJ}/, $(filter -I%, $(CPPFLAGS))))
LINT_SRC_C +=  $(addprefix ${CURDIR}/src/, $(sort $(notdir $(wildcard src/*.c))))
LINT_SRC_C +=  $(addprefix ${CURDIR}/src/, $(sort $(notdir $(wildcard src/*.s))))
LINT_SRC_C +=  $(addprefix ${CURDIR}/src/$(CHIP_FOLDER)/, $(sort $(notdir $(wildcard src/$(CHIP_FOLDER)/*.c))))
LINT_SRC_C +=  $(addprefix ${CURDIR}/src/$(CHIP_FOLDER)/, $(sort $(notdir $(wildcard src/$(CHIP_FOLDER)/*.s))))
LINT_INC+= $(subst -I,,$(addprefix ${CURDIR}/, $(filter -I%, $(CPPFLAGS))))
LINT_DEF+=$(subst -D,-d,$(filter -D%,$(CPPFLAGS)))
LINT_PATH=../lint
FLINT=$(LINT_PATH)/flint
lint:
ifeq ($(ENABLE_LINT),1)
	@echo "==sboot LINT===";
	@(\
	cat ../${PROJ}/include/autoconf.h |\
	grep 'ENABLE' |\
	sed -e 's/#define \([^ ]*\) "\(..*\)"/-d"\1=(\2)"/' | \
	sed -e 's/#define \([^ ]*\) \(..*\)/-d"\1=\2"/' | \
	sed -e 's/#define /-d/' |\
	sed -e /#undef/d |\
	sed -e /USE/d |\
	sed -e /__VA_ARGS__/d >../${PROJ}/include/_autoconf.h;\
	cat ../${PROJ}/include/_autoconf.h |\
	grep '=1' |\
	sed -e 's/ENABLE/CONFIG/' >../${PROJ}/include/_conf.h;\
	cat ../${PROJ}/include/_autoconf.h > ../lint/${PROJ}.lnt;\
	cat ../${PROJ}/include/_conf.h >> ../lint/${PROJ}.lnt;\
	echo |  $(CROSS_COMPILE)cpp -dM | \
	sed -e '/LONG_LONG/d' | \
	sed -e 's/#define \([^ ]*\) "\(..*\)"/-d"\1=(\2)"/' | \
	sed -e 's/#define \([^ ]*\) \(..*\)/-d"\1=\2"/' | \
	sed -e 's/#define /-d/'; \
	#echo $(CPPFLAGS); \
	for i in $(LINT_DEF); do \
		echo $$i; \
	done; \
	for i in $(LINT_INC); do \
		echo -i\"$$i\"; \
	done;\
	for i in $(LINT_SRC_C); do \
		echo $$i; \
	done; \
	) >> ../lint/${PROJ}.lnt
	@$(FLINT) -fff $(LINT_PATH)/$(PROJ).lnt > $(LINT_PATH)/$(PROJ)LINT.txt; true
	@rm ../${PROJ}/include/_conf.h;
	@rm ../${PROJ}/include/_autoconf.h;
endif
LINT_PATH=../lint
SPROJ=sboot
UPROJ=u-boot-1.1.6
LINT_RESULT:
ifeq ($(ENABLE_LINT),1)
	@echo "====MBoot lint result====";
	@echo `grep 'Error' $(LINT_PATH)/$(SPROJ)LINT.txt | wc -l` $(SPROJ) LINT Errors. Please check $(LINT_PATH)/$(SPROJ)LINT.txt
	@echo `grep 'Error' $(LINT_PATH)/$(UPROJ)LINT.txt | wc -l` $(UPROJ) LINT Errors. Please check $(LINT_PATH)/$(UPROJ)LINT.txt
endif

PROTECT_FLAG_CONFLICT_CHECK:
ifeq ($(CONFIG_SECURE_SPI_FULL_PROTECT),y)
ifeq ($(CONFIG_ENV_IN_SERIAL),y)
	@echo " ##### Error ##### " ;
	@echo " Config Conflict"
	@echo " CONFIG_ENV_IN_SERIAL and CONFIG_SECURE_SPI_PARTIAL_PROTECT : no"
	@echo " Please re-tune CONFIG_ENV or CONFIG_SECURE_SPI_PARTIAL_PROTECT and compile again"
	@exit 99;
endif
endif

MBOOT_SIZE_CHECK: out/mboot.bin
ifeq ($(CONFIG_SECURE_SPI_PARTIAL_PROTECT),y)
	@echo " "
	@echo " ======= Check whether or not MBoot size is over protection range  $< Start	======= "
	$(Q)if [ $(shell expr $(shell printf %lu "$(CONFIG_SECURE_SPI_PROTECT_SPACE)") \>= $(shell stat -c '%s' "$<")) == 0 ]; then \
		echo " ##### Error ##### " ; \
		echo " CONFIG_SECURE_SPI_PROTECT_SPACE < $< size " ; \
		echo " CONFIG_SECURE_SPI_PROTECT_SPACE : $(shell printf %lu "$(CONFIG_SECURE_SPI_PROTECT_SPACE)")" ; \
		echo " $< : $(shell stat -c '%s' "$<")" ; \
		echo " Please re-tune CONFIG_SECURE_SPI_PROTECT_SPACE and compile again" ; \
		rm -rf "$<"; \
		exit 99; \
	else\
		echo " ##### Success ##### " ; \
	fi;
	@echo " ======= Check done $< Finished	======= "
endif
ifeq ($(CONFIG_FORCE_TO_ASSIGN_ENV_OFFSET),y)
	@echo " "
	@echo " ======= Check whether or not MBoot size overlay env address $< Start	======= "
	$(Q)if [ $(shell expr $(shell printf %lu "$(CONFIG_ENV_VAR_OFFSET)") \>= $(shell stat -c '%s' "$<")) == 0 ]; then \
		echo " ##### Error ##### " ; \
		echo " CONFIG_ENV_VAR_OFFSET < $< size " ; \
		echo " CONFIG_ENV_VAR_OFFSET : $(shell printf %lu "$(CONFIG_ENV_VAR_OFFSET)")" ; \
		echo " $< : $(shell stat -c '%s' "$<")" ; \
		echo " Please re-tune CONFIG_ENV_VAR_OFFSET and compile again" ; \
		rm -rf "$<"; \
		exit 99; \
	else\
		echo " ##### Success ##### " ; \
	fi;
	@echo " ======= Check done $< Finished	======= "
endif

ifeq ($(CONFIG_BINARY_RELEASE), y)
#########################################################################
## Rules for Binary Release
## Created by Grand.Zhu
#########################################################################
.PHONY: brelease uboot-release sboot-release mstar-release tool-release mboot_config.bin $(RELEASE_PATH)
RELEASE_PATH := ../release

$(RELEASE_PATH):
	@echo "---release path: $(RELEASE_PATH)---"
	@[ -d $@ ] && rm -rf $@/* || mkdir -p $@

mstar-release:
	@cp -af ../MstarCore ../MstarApp ../MstarCustomer $(RELEASE_PATH)
	@find $(RELEASE_PATH)/MstarCore/board -path "*/$(CHIP_FOLDER)" -prune -o -type d -not -name "board" -print | xargs rm -rf
	@find $(RELEASE_PATH)/MstarCore/bsp -path "*/$(CHIP_FOLDER)" -prune -o -type d -not -name "bsp" -print | xargs rm -rf
	@find $(RELEASE_PATH)/MstarCore \( -name "*.S" -o -name "*.c" -o -name "*.o" -not -name "lib*.o" \) | xargs rm -f
	@find $(RELEASE_PATH)/MstarApp \( -name "*.S" -o -name "*.c" -o -name "*.o" \) | xargs rm -f
	@find $(RELEASE_PATH)/MstarCustomer \( -name "lib*.a" -o -name "*.o" \) | xargs rm -f
#	@find $(RELEASE_PATH)/MstarCustomer \( -name "*.S" -o -name "*.c" -o -name "*.o" \) | xargs rm -f

uboot-release:
	@cp -af ../$(_PROJ) $(RELEASE_PATH)
	@find $(RELEASE_PATH)/$(_PROJ) -type f \( -name "*.S" -o -name "*.c" -o -name "*.inc" \) | xargs rm -f
	@find $(RELEASE_PATH)/$(_PROJ) -type f \( -name u-boot -o -name u-boot.map -o -name u-boot.hex \) | xargs rm -f
	@find $(RELEASE_PATH)/$(_PROJ) -type f \( -name "*.srec" -o -name "*.bin" -o -name u-boot.img \) | xargs rm -f

sboot-release:
	@cp -af $(TOPDIR) $(RELEASE_PATH)
	@find $(RELEASE_PATH)/sboot \( -name "out" -type d \) | xargs rm -rf
	@find $(RELEASE_PATH)/sboot -path "*/src" -prune -o \( -name "*.S" -o -name "*.c" -o -name "*.inc" \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/inc -path "*/$(CHIP_FOLDER)" -prune -o -type d -not -name inc -print | xargs rm -rf
	@find $(RELEASE_PATH)/sboot/src \( -path "*/$(CHIP_FOLDER)" -o -path "*/aesdma" -o -path "*/mmc" -o -path "*/nand" \) -prune \
        -o -type d -not -name src -print | xargs rm -rf
	@find $(RELEASE_PATH)/sboot/src/aesdma \( -name "*.S" -o -name "*.c" -o -name "*.inc" \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src/mmc \( -name "*.S" -o -name "*.c" -o -name "*.inc" \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src/nand \( -name "*.S" -o -name "*.c" -o -name "*.inc" \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src/$(CHIP_FOLDER) \( -name "*.S" -o -name "*.inc" \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src/$(CHIP_FOLDER) -name "*.c" -not \( -name drvPadConf.c -o -name drv_miu_init.c \
        -o -name drv_miu_init_str.c -o -name drv_miu1_init.c \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src/$(CHIP_FOLDER) \( -name *drvPadConf.o* -o -name *drv_miu_init.o* \
        -o -name *drv_miu_init_str.o* -o -name *drv_miu1_init.o* \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src/$(CHIP_FOLDER) -name *lib.a* -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/src -maxdepth 1 \( -name "*.S" -o -name "*.c" -o -name "*.inc" \) -print | xargs rm -f
	@find $(RELEASE_PATH)/sboot/bin/pm -path "*/$(CHIP_FOLDER)" -prune -o -type d -not -name pm -print | xargs rm -rf

tool-release:
	@make -C ../tool/mboot_ini_parser
	@mkdir -p $(RELEASE_PATH)/tool
	@cp -f ../tool/mboot_ini_parser.exe $(RELEASE_PATH)/tool

mboot_config.bin:
	@if [ -f mboot_config.ini ] ; then \
        ../tool/mboot_ini_parser.exe mboot_config.ini; \
	else \
	    echo "---Not found mboot_config.ini---"; \
	fi;

brelease: tool-release mboot_config.bin all $(RELEASE_PATH) mstar-release uboot-release sboot-release
	@echo "---release binary for $(CHIP_FOLDER)---"
	@cp -af ../*.sh $(RELEASE_PATH)
	@touch $(RELEASE_PATH)/.binary_release

btest:
	@echo "==If binary release? ($(BINARY_RELEASE_FLAG))=="

endif
