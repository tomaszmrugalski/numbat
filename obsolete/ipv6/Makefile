#
# OMNeT++/OMNEST Makefile for libipv6
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -o ipv6 -O out -I../util -L../out/$(CONFIGNAME)/util -L../out/$(CONFIGNAME)/wimax -lutil
#

# Name of target to be created (-o option)
TARGET = libipv6$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = -I../util -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../out/$(CONFIGNAME)/util -L../out/$(CONFIGNAME)/wimax  -lutil
LIBS += -Wl,-rpath,`abspath ../out/$(CONFIGNAME)/util` -Wl,-rpath,`abspath ../out/$(CONFIGNAME)/wimax`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = ipv6
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/mip6.o \
    $O/ipv6node.o \
    $O/dhcpv6.o \
    $O/Internet.o \
    $O/ipv6disp.o \
    $O/ra.o \
    $O/ipv6msg_m.o

# Message files
MSGFILES = \
    ipv6msg.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(LIBS) $(OMNETPP_LIBS) $(LDFLAGS)
	$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f ipv6 ipv6.exe libipv6.so libipv6.a libipv6.dll libipv6.dylib
	-rm -f ./*_m.cc ./*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/ra.o: ra.cc \
	../util/mih_m.h \
	ipv6msg_m.h \
	../util/ipv6.h \
	../util/ssinfo.h \
	../util/Portable.h \
	../util/hoinfo.h \
	../util/logger.h \
	../util/fsm.h \
	ra.h
$O/mip6.o: mip6.cc \
	../util/mih_m.h \
	ipv6msg_m.h \
	../util/ipv6.h \
	../util/ssinfo.h \
	../util/Portable.h \
	../util/hoinfo.h \
	../util/logger.h \
	../util/fsm.h \
	mip6.h
$O/ipv6node.o: ipv6node.cc \
	../util/Portable.h \
	ipv6node.h \
	../util/logger.h
$O/ipv6msg_m.o: ipv6msg_m.cc \
	ipv6msg_m.h \
	../util/ipv6.h \
	../util/Portable.h
$O/ipv6disp.o: ipv6disp.cc \
	../util/mih_m.h \
	ipv6msg_m.h \
	../util/ipv6.h \
	../util/ssinfo.h \
	ipv6disp.h \
	../util/Portable.h \
	../util/hoinfo.h \
	../util/logger.h
$O/dhcpv6.o: dhcpv6.cc \
	../util/mih_m.h \
	ipv6msg_m.h \
	../util/ipv6.h \
	../util/ssinfo.h \
	../util/Portable.h \
	dhcpv6.h \
	../util/hoinfo.h \
	../util/logger.h \
	../util/fsm.h
$O/Internet.o: Internet.cc \
	Internet.h \
	ipv6msg_m.h \
	../util/ipv6.h \
	../util/Portable.h \
	../util/logger.h

