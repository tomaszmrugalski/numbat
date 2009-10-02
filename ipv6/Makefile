#
# OMNeT++/OMNEST Makefile for libipv6
#
# This file was generated with the command:
#  opp_makemake -f -lutil -L../util/out/gcc-debug/ -I../util -a
#

# Name of target to be created (-o option)
TARGET = libipv6$(A_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = -I../util -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/dhcpv6.o \
    $O/Internet.o \
    $O/ipv6disp.o \
    $O/ipv6node.o \
    $O/mip6.o \
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
	$(AR) $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS)

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
	-rm -f ipv6 ipv6.exe libipv6.so libipv6.a libipv6.dll libipv6.dylib
	-rm -f ./*_m.cc ./*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Internet.o: Internet.cc \
  ../util/Portable.h \
  ../util/logger.h \
  ./ipv6msg_m.h \
  ./Internet.h \
  ../util/ipv6.h
$O/dhcpv6.o: dhcpv6.cc \
  ../util/Portable.h \
  ../util/hoinfo.h \
  ./ipv6msg_m.h \
  ../util/ipv6.h \
  ../util/mih_m.h \
  ./dhcpv6.h \
  ../util/logger.h \
  ../util/ssinfo.h \
  ../util/fsm.h
$O/ipv6disp.o: ipv6disp.cc \
  ../util/Portable.h \
  ./ipv6msg_m.h \
  ../util/hoinfo.h \
  ../util/ipv6.h \
  ../util/mih_m.h \
  ../util/logger.h \
  ./ipv6disp.h \
  ../util/ssinfo.h
$O/ipv6node.o: ipv6node.cc \
  ../util/Portable.h \
  ../util/logger.h \
  ./ipv6node.h
$O/mip6.o: mip6.cc \
  ../util/Portable.h \
  ./mip6.h \
  ../util/hoinfo.h \
  ./ipv6msg_m.h \
  ../util/ipv6.h \
  ../util/mih_m.h \
  ../util/logger.h \
  ../util/ssinfo.h \
  ../util/fsm.h
$O/ra.o: ra.cc \
  ../util/Portable.h \
  ../util/hoinfo.h \
  ./ipv6msg_m.h \
  ../util/ipv6.h \
  ../util/mih_m.h \
  ../util/logger.h \
  ../util/ssinfo.h \
  ./ra.h \
  ../util/fsm.h
