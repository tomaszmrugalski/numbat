#
# OMNeT++/OMNEST Makefile for wimax
#
# This file was generated with the command:
#  opp_makemake -f -lutil -lipv6 -L../util/out/gcc-debug -L../ipv6/out/gcc-debug -I../util -I../ipv6
#

# Name of target to be created (-o option)
TARGET = wimax$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -I../util -I../ipv6 -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../util/out/gcc-debug -L../ipv6/out/gcc-debug  -lutil -lipv6
LIBS += -Wl,-rpath,`abspath ../util/out/gcc-debug` -Wl,-rpath,`abspath ../ipv6/out/gcc-debug`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/wmaxctrl.o \
    $O/wmaxmac.o \
    $O/wmaxmaccs.o \
    $O/wmaxphy.o \
    $O/wmaxradio.o \
    $O/wmaxmsg_m.o

# Message files
MSGFILES = \
    wmaxmsg.msg

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
	-rm -f wimax wimax.exe libwimax.so libwimax.a libwimax.dll libwimax.dylib
	-rm -f ./*_m.cc ./*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/wmaxctrl.o: wmaxctrl.cc \
  ../util/Portable.h \
  ../util/hoinfo.h \
  ../util/ipv6.h \
  ../util/mih_m.h \
  ./wmaxmsg_m.h \
  ../util/logger.h \
  ./wmaxmsg.h \
  ./wmaxmac.h \
  ../util/ssinfo.h \
  ./wmaxradio.h \
  ./wmaxctrl.h \
  ../util/fsm.h
$O/wmaxmac.o: wmaxmac.cc \
  ../util/Portable.h \
  ../util/hoinfo.h \
  ../util/ipv6.h \
  ./wmaxmsg_m.h \
  ../util/logger.h \
  ./wmaxmsg.h \
  ../util/ssinfo.h \
  ./wmaxmac.h \
  ./wmaxctrl.h \
  ../util/fsm.h
$O/wmaxmaccs.o: wmaxmaccs.cc \
  ../util/Portable.h \
  ../util/hoinfo.h \
  ./wmaxmaccs.h \
  ../util/ipv6.h \
  ./wmaxmsg_m.h \
  ../util/logger.h \
  ./wmaxmsg.h \
  ../util/ssinfo.h \
  ./wmaxmac.h \
  ../ipv6/ipv6msg_m.h
$O/wmaxphy.o: wmaxphy.cc \
  ../util/Portable.h \
  ./wmaxphy.h \
  ../util/hoinfo.h \
  ../util/ipv6.h \
  ../util/mih_m.h \
  ./wmaxmsg_m.h \
  ../util/logger.h \
  ./wmaxmsg.h \
  ../util/ssinfo.h
$O/wmaxradio.o: wmaxradio.cc \
  ../util/logger.h \
  ./wmaxradio.h \
  ../util/fsm.h
