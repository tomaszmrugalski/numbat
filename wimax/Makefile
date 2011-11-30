#
# OMNeT++/OMNEST Makefile for libwimax
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -o wimax -O out -I../xMIPv6/src/transport/sctp -I../xMIPv6/src/networklayer/arp -I../util -I../xMIPv6/src/networklayer/ted -I../xMIPv6/src/networklayer/common -I../xMIPv6/src/networklayer/ipv4 -I../xMIPv6/src/networklayer/mpls -I../xMIPv6/src/transport/contract -I../xMIPv6/src/util -I../xMIPv6/src/util/headerserializers -I../xMIPv6/src/networklayer/rsvp_te -I../xMIPv6/src/linklayer/mfcore -I../xMIPv6/src/linklayer/contract -I../xMIPv6/src/applications/pingapp -I../xMIPv6/src/networklayer/contract -I../xMIPv6/src/networklayer/xmipv6 -I../xMIPv6/src/base -I../xMIPv6/src/networklayer/ipv6 -I../xMIPv6/src/transport/udp -I../xMIPv6/src/world -I../xMIPv6/src/transport/tcp -I../xMIPv6/src/networklayer/ldp -I../xMIPv6/src/networklayer/icmpv6 -L../out/$(CONFIGNAME)/util -L../out/$(CONFIGNAME)/ipv6
#

# Name of target to be created (-o option)
TARGET = libwimax$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../xMIPv6/src/transport/sctp \
    -I../xMIPv6/src/networklayer/arp \
    -I../util \
    -I../xMIPv6/src/networklayer/ted \
    -I../xMIPv6/src/networklayer/common \
    -I../xMIPv6/src/networklayer/ipv4 \
    -I../xMIPv6/src/networklayer/mpls \
    -I../xMIPv6/src/transport/contract \
    -I../xMIPv6/src/util \
    -I../xMIPv6/src/util/headerserializers \
    -I../xMIPv6/src/networklayer/rsvp_te \
    -I../xMIPv6/src/linklayer/mfcore \
    -I../xMIPv6/src/linklayer/contract \
    -I../xMIPv6/src/applications/pingapp \
    -I../xMIPv6/src/networklayer/contract \
    -I../xMIPv6/src/networklayer/xmipv6 \
    -I../xMIPv6/src/base \
    -I../xMIPv6/src/networklayer/ipv6 \
    -I../xMIPv6/src/transport/udp \
    -I../xMIPv6/src/world \
    -I../xMIPv6/src/transport/tcp \
    -I../xMIPv6/src/networklayer/ldp \
    -I../xMIPv6/src/networklayer/icmpv6 \
    -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../out/$(CONFIGNAME)/util -L../out/$(CONFIGNAME)/ipv6
LIBS += -Wl,-rpath,`abspath ../out/$(CONFIGNAME)/util` -Wl,-rpath,`abspath ../out/$(CONFIGNAME)/ipv6`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = wimax
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/wmaxphy.o \
    $O/wmaxradio.o \
    $O/wmaxmaccs.o \
    $O/wmaxctrl.o \
    $O/wmaxmac.o \
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
	-rm -f wimax wimax.exe libwimax.so libwimax.a libwimax.dll libwimax.dylib
	-rm -f ./*_m.cc ./*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/wmaxradio.o: wmaxradio.cc \
	../util/fsm.h \
	wmaxradio.h \
	../util/logger.h
$O/wmaxphy.o: wmaxphy.cc \
	../util/Portable.h \
	wmaxmsg.h \
	../util/ssinfo.h \
	../util/mih_m.h \
	../util/hoinfo.h \
	../xMIPv6/src/base/INETDefs.h \
	wmaxmsg_m.h \
	../xMIPv6/src/networklayer/contract/IPv6Address.h \
	../util/logger.h \
	wmaxphy.h
$O/wmaxmaccs.o: wmaxmaccs.cc \
	../xMIPv6/src/base/NotificationBoard.h \
	../util/Portable.h \
	wmaxmsg.h \
	../xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	../xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	../xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	../util/logger.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	../xMIPv6/src/base/ModuleAccess.h \
	../xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	../xMIPv6/src/networklayer/common/InterfaceToken.h \
	../xMIPv6/src/linklayer/contract/MACAddress.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	wmaxmac.h \
	../xMIPv6/src/networklayer/common/InterfaceEntry.h \
	../xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	../xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	../xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	../util/hoinfo.h \
	../xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	../xMIPv6/src/networklayer/contract/IPv6Address.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	../xMIPv6/src/base/NotifierConsts.h \
	wmaxmaccs.h \
	wmaxmsg_m.h \
	../xMIPv6/src/base/INETDefs.h \
	../xMIPv6/src/networklayer/common/InterfaceTable.h \
	../xMIPv6/src/networklayer/common/IInterfaceTable.h \
	../xMIPv6/src/base/INotifiable.h \
	../util/ssinfoaccess.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	../util/ssinfo.h \
	../xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	../xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h
$O/wmaxmsg_m.o: wmaxmsg_m.cc \
	../util/Portable.h \
	wmaxmsg.h \
	../xMIPv6/src/base/INETDefs.h \
	wmaxmsg_m.h \
	../xMIPv6/src/networklayer/contract/IPv6Address.h
$O/wmaxctrl.o: wmaxctrl.cc \
	wmaxmsg.h \
	../xMIPv6/src/networklayer/contract/IPAddress.h \
	../xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	../xMIPv6/src/networklayer/xmipv6/xMIPv6.h \
	../xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	../util/logger.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	../xMIPv6/src/base/ModuleAccess.h \
	../xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	wmaxmac.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	../xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	../xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	../xMIPv6/src/base/NotifierConsts.h \
	../xMIPv6/src/networklayer/contract/IPvXAddress.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	../util/mih_m.h \
	../xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	../xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	../xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	wmaxradio.h \
	wmaxctrl.h \
	../xMIPv6/src/base/NotificationBoard.h \
	../util/Portable.h \
	../xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	../xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	../util/fsm.h \
	../xMIPv6/src/networklayer/common/InterfaceToken.h \
	../xMIPv6/src/linklayer/contract/MACAddress.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	../xMIPv6/src/networklayer/common/InterfaceEntry.h \
	../xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	../xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	../util/hoinfo.h \
	../xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	../xMIPv6/src/networklayer/contract/IPv6Address.h \
	../xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	../xMIPv6/src/base/INETDefs.h \
	wmaxmsg_m.h \
	../xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	../xMIPv6/src/networklayer/common/InterfaceTable.h \
	../xMIPv6/src/base/INotifiable.h \
	../xMIPv6/src/networklayer/common/IInterfaceTable.h \
	../util/ssinfoaccess.h \
	../util/ssinfo.h \
	../xMIPv6/src/networklayer/xmipv6/xMIPv6Access.h \
	../xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	../xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h
$O/wmaxmac.o: wmaxmac.cc \
	wmaxmsg.h \
	../xMIPv6/src/networklayer/contract/IPAddress.h \
	../xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	../xMIPv6/src/networklayer/xmipv6/xMIPv6.h \
	../xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	../util/logger.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	../xMIPv6/src/base/ModuleAccess.h \
	../xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	wmaxmac.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	../xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	../xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	../xMIPv6/src/base/NotifierConsts.h \
	../xMIPv6/src/networklayer/contract/IPvXAddress.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	../xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	../xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	../xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	../xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	wmaxctrl.h \
	../xMIPv6/src/base/NotificationBoard.h \
	../util/Portable.h \
	../xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	../xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	../util/fsm.h \
	../xMIPv6/src/linklayer/contract/MACAddress.h \
	../xMIPv6/src/networklayer/common/InterfaceToken.h \
	../xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	../xMIPv6/src/networklayer/common/InterfaceEntry.h \
	../xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	../xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	../util/hoinfo.h \
	../xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	../xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	../xMIPv6/src/networklayer/contract/IPv6Address.h \
	../xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	wmaxmsg_m.h \
	../xMIPv6/src/base/INETDefs.h \
	../xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	../xMIPv6/src/networklayer/common/InterfaceTable.h \
	../xMIPv6/src/base/INotifiable.h \
	../xMIPv6/src/networklayer/common/IInterfaceTable.h \
	../util/ssinfoaccess.h \
	../util/ssinfo.h \
	../xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	../xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h

