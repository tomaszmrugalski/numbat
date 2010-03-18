#
# OMNeT++/OMNEST Makefile for omnet
#
# This file was generated with the command:
#  opp_makemake -f --deep -X results -X scripts -X doc -X out -O numbat
#

# Name of target to be created (-o option)
TARGET = omnet$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iipv6 \
    -Iipv6/out \
    -Iipv6/out/gcc-debug \
    -Iport-win32 \
    -Iport-win32/out \
    -Iport-win32/out/gcc-debug \
    -Iutil \
    -Iwimax \
    -Iwimax/out \
    -Iwimax/out/gcc-debug

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = numbat
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/ipv6/dhcpv6.o \
    $O/ipv6/Internet.o \
    $O/ipv6/ipv6disp.o \
    $O/ipv6/ipv6node.o \
    $O/ipv6/mip6.o \
    $O/ipv6/ra.o \
    $O/port-win32/addrpack.o \
    $O/util/fsm.o \
    $O/util/ipv6.o \
    $O/util/logger.o \
    $O/util/ssinfo.o \
    $O/wimax/wmaxctrl.o \
    $O/wimax/wmaxmac.o \
    $O/wimax/wmaxmaccs.o \
    $O/wimax/wmaxphy.o \
    $O/wimax/wmaxradio.o \
    $O/ipv6/ipv6msg_m.o \
    $O/util/mih_m.o \
    $O/wimax/wmaxmsg_m.o

# Message files
MSGFILES = \
    ipv6/ipv6msg.msg \
    util/mih.msg \
    wimax/wmaxmsg.msg

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
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

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
	ln -s -f $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@mkdir -p $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f omnet omnet.exe libomnet.so libomnet.a libomnet.dll libomnet.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f ipv6/*_m.cc ipv6/*_m.h
	-rm -f ipv6/out/*_m.cc ipv6/out/*_m.h
	-rm -f ipv6/out/gcc-debug/*_m.cc ipv6/out/gcc-debug/*_m.h
	-rm -f port-win32/*_m.cc port-win32/*_m.h
	-rm -f port-win32/out/*_m.cc port-win32/out/*_m.h
	-rm -f port-win32/out/gcc-debug/*_m.cc port-win32/out/gcc-debug/*_m.h
	-rm -f util/*_m.cc util/*_m.h
	-rm -f wimax/*_m.cc wimax/*_m.h
	-rm -f wimax/out/*_m.cc wimax/out/*_m.h
	-rm -f wimax/out/gcc-debug/*_m.cc wimax/out/gcc-debug/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc ipv6/*.cc ipv6/out/*.cc ipv6/out/gcc-debug/*.cc port-win32/*.cc port-win32/out/*.cc port-win32/out/gcc-debug/*.cc util/*.cc wimax/*.cc wimax/out/*.cc wimax/out/gcc-debug/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/ipv6/Internet.o: ipv6/Internet.cc \
  util/Portable.h \
  util/ipv6.h \
  ipv6/ipv6msg_m.h \
  util/logger.h \
  ipv6/Internet.h
$O/ipv6/dhcpv6.o: ipv6/dhcpv6.cc \
  util/Portable.h \
  ipv6/ipv6msg_m.h \
  ipv6/dhcpv6.h \
  util/hoinfo.h \
  util/mih_m.h \
  util/ssinfo.h \
  util/ipv6.h \
  util/fsm.h \
  util/logger.h
$O/ipv6/ipv6disp.o: ipv6/ipv6disp.cc \
  util/Portable.h \
  ipv6/ipv6msg_m.h \
  ipv6/ipv6disp.h \
  util/hoinfo.h \
  util/mih_m.h \
  util/ipv6.h \
  util/ssinfo.h \
  util/logger.h
$O/ipv6/ipv6msg_m.o: ipv6/ipv6msg_m.cc \
  util/Portable.h \
  ipv6/ipv6msg_m.h \
  util/ipv6.h
$O/ipv6/ipv6node.o: ipv6/ipv6node.cc \
  util/Portable.h \
  ipv6/ipv6node.h \
  util/logger.h
$O/ipv6/mip6.o: ipv6/mip6.cc \
  util/Portable.h \
  ipv6/mip6.h \
  ipv6/ipv6msg_m.h \
  util/hoinfo.h \
  util/mih_m.h \
  util/ssinfo.h \
  util/ipv6.h \
  util/fsm.h \
  util/logger.h
$O/ipv6/ra.o: ipv6/ra.cc \
  util/Portable.h \
  ipv6/ra.h \
  ipv6/ipv6msg_m.h \
  util/hoinfo.h \
  util/mih_m.h \
  util/ipv6.h \
  util/ssinfo.h \
  util/fsm.h \
  util/logger.h
$O/port-win32/addrpack.o: port-win32/addrpack.cc \
  util/Portable.h
$O/util/fsm.o: util/fsm.cc \
  util/logger.h \
  util/fsm.h
$O/util/ipv6.o: util/ipv6.cc \
  util/Portable.h \
  util/ipv6.h \
  util/logger.h
$O/util/logger.o: util/logger.cc \
  util/logger.h
$O/util/mih_m.o: util/mih_m.cc \
  util/Portable.h \
  util/mih_m.h \
  util/ipv6.h
$O/util/ssinfo.o: util/ssinfo.cc \
  util/Portable.h \
  util/hoinfo.h \
  util/mih_m.h \
  util/ipv6.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxctrl.o: wimax/wmaxctrl.cc \
  util/Portable.h \
  wimax/wmaxctrl.h \
  wimax/wmaxmac.h \
  wimax/wmaxmsg_m.h \
  util/hoinfo.h \
  util/mih_m.h \
  wimax/wmaxmsg.h \
  util/ipv6.h \
  util/ssinfo.h \
  wimax/wmaxradio.h \
  util/fsm.h \
  util/logger.h
$O/wimax/wmaxmac.o: wimax/wmaxmac.cc \
  util/Portable.h \
  wimax/wmaxctrl.h \
  wimax/wmaxmsg_m.h \
  wimax/wmaxmac.h \
  util/hoinfo.h \
  util/ssinfo.h \
  util/ipv6.h \
  wimax/wmaxmsg.h \
  util/fsm.h \
  util/logger.h
$O/wimax/wmaxmaccs.o: wimax/wmaxmaccs.cc \
  util/Portable.h \
  ipv6/ipv6msg_m.h \
  wimax/wmaxmsg_m.h \
  wimax/wmaxmac.h \
  util/hoinfo.h \
  wimax/wmaxmaccs.h \
  wimax/wmaxmsg.h \
  util/ssinfo.h \
  util/ipv6.h \
  util/logger.h
$O/wimax/wmaxmsg_m.o: wimax/wmaxmsg_m.cc \
  util/Portable.h \
  wimax/wmaxmsg_m.h \
  wimax/wmaxmsg.h \
  util/ipv6.h
$O/wimax/wmaxphy.o: wimax/wmaxphy.cc \
  util/Portable.h \
  wimax/wmaxphy.h \
  wimax/wmaxmsg_m.h \
  util/hoinfo.h \
  util/mih_m.h \
  util/ipv6.h \
  wimax/wmaxmsg.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxradio.o: wimax/wmaxradio.cc \
  wimax/wmaxradio.h \
  util/fsm.h \
  util/logger.h
