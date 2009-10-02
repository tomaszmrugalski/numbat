#
# OMNeT++/OMNEST Makefile for omnet
#
# This file was generated with the command:
#  opp_makemake -f --deep -X results -X scripts -X port-win32 -X doc -X out
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
    -Iutil \
    -Iutil/out \
    -Iwimax

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
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
	-rm -f util/*_m.cc util/*_m.h
	-rm -f util/out/*_m.cc util/out/*_m.h
	-rm -f wimax/*_m.cc wimax/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc ipv6/*.cc ipv6/out/*.cc util/*.cc util/out/*.cc wimax/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/ipv6/dhcpv6.o: ipv6/dhcpv6.cc \
  ipv6/ipv6msg_m.h \
  ipv6/dhcpv6.h \
  util/fsm.h \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  util/mih_m.h \
  util/ssinfo.h \
  util/logger.h
$O/ipv6/Internet.o: ipv6/Internet.cc \
  ipv6/ipv6msg_m.h \
  util/Portable.h \
  util/ipv6.h \
  ipv6/Internet.h \
  util/logger.h
$O/ipv6/ipv6disp.o: ipv6/ipv6disp.cc \
  ipv6/ipv6msg_m.h \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  ipv6/ipv6disp.h \
  util/mih_m.h \
  util/ssinfo.h \
  util/logger.h
$O/ipv6/ipv6msg_m.o: ipv6/ipv6msg_m.cc \
  ipv6/ipv6msg_m.h \
  util/Portable.h \
  util/ipv6.h
$O/ipv6/ipv6node.o: ipv6/ipv6node.cc \
  util/Portable.h \
  ipv6/ipv6node.h \
  util/logger.h
$O/ipv6/mip6.o: ipv6/mip6.cc \
  ipv6/ipv6msg_m.h \
  util/Portable.h \
  util/fsm.h \
  util/hoinfo.h \
  util/ipv6.h \
  util/mih_m.h \
  util/ssinfo.h \
  util/logger.h \
  ipv6/mip6.h
$O/ipv6/ra.o: ipv6/ra.cc \
  ipv6/ipv6msg_m.h \
  util/Portable.h \
  util/fsm.h \
  util/hoinfo.h \
  util/ipv6.h \
  util/mih_m.h \
  ipv6/ra.h \
  util/ssinfo.h \
  util/logger.h
$O/util/fsm.o: util/fsm.cc \
  util/fsm.h \
  util/logger.h
$O/util/ipv6.o: util/ipv6.cc \
  util/Portable.h \
  util/ipv6.h \
  util/logger.h
$O/util/logger.o: util/logger.cc \
  util/logger.h
$O/util/mih_m.o: util/mih_m.cc \
  util/Portable.h \
  util/ipv6.h \
  util/mih_m.h
$O/util/ssinfo.o: util/ssinfo.cc \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  util/mih_m.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxctrl.o: wimax/wmaxctrl.cc \
  wimax/wmaxmsg.h \
  util/fsm.h \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  util/mih_m.h \
  wimax/wmaxmac.h \
  wimax/wmaxmsg_m.h \
  wimax/wmaxradio.h \
  wimax/wmaxctrl.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxmac.o: wimax/wmaxmac.cc \
  wimax/wmaxmsg.h \
  util/fsm.h \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  wimax/wmaxmac.h \
  wimax/wmaxmsg_m.h \
  wimax/wmaxctrl.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxmaccs.o: wimax/wmaxmaccs.cc \
  wimax/wmaxmsg.h \
  ipv6/ipv6msg_m.h \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  wimax/wmaxmaccs.h \
  wimax/wmaxmac.h \
  wimax/wmaxmsg_m.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxphy.o: wimax/wmaxphy.cc \
  wimax/wmaxmsg.h \
  util/Portable.h \
  util/hoinfo.h \
  util/ipv6.h \
  util/mih_m.h \
  wimax/wmaxmsg_m.h \
  wimax/wmaxphy.h \
  util/ssinfo.h \
  util/logger.h
$O/wimax/wmaxradio.o: wimax/wmaxradio.cc \
  util/fsm.h \
  wimax/wmaxradio.h \
  util/logger.h
