#
# OMNeT++/OMNEST Makefile for numbat
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -Xdoc -Xobsolete -Xresults -Xscripts -XxMIPv6/obsolete -XxMIPv6/tests
#

# Name of target to be created (-o option)
TARGET = numbat$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iport-win32 \
    -Iutil \
    -Iwimax \
    -IxMIPv6 \
    -IxMIPv6/3rdparty \
    -IxMIPv6/_scripts \
    -IxMIPv6/_scripts/xmlschema \
    -IxMIPv6/_scripts/xsd2html \
    -IxMIPv6/doc \
    -IxMIPv6/doc/src \
    -IxMIPv6/doc/src/tcp \
    -IxMIPv6/doc/tutorial \
    -IxMIPv6/doc/walkthrough \
    -IxMIPv6/doc/walkthrough/images \
    -IxMIPv6/doc/walkthrough/thumbs \
    -IxMIPv6/etc \
    -IxMIPv6/etc/plugins \
    -IxMIPv6/examples \
    -IxMIPv6/examples/adhoc \
    -IxMIPv6/examples/adhoc/ieee80211 \
    -IxMIPv6/examples/adhoc/mf80211 \
    -IxMIPv6/examples/adhoc/mobility \
    -IxMIPv6/examples/emulation \
    -IxMIPv6/examples/emulation/extclient \
    -IxMIPv6/examples/emulation/extserver \
    -IxMIPv6/examples/emulation/traceroute \
    -IxMIPv6/examples/ethernet \
    -IxMIPv6/examples/ethernet/arptest \
    -IxMIPv6/examples/ethernet/arptest2 \
    -IxMIPv6/examples/ethernet/lans \
    -IxMIPv6/examples/inet \
    -IxMIPv6/examples/inet/ber \
    -IxMIPv6/examples/inet/bulktransfer \
    -IxMIPv6/examples/inet/flatnet \
    -IxMIPv6/examples/inet/kidsnw1 \
    -IxMIPv6/examples/inet/multicast \
    -IxMIPv6/examples/inet/nclients \
    -IxMIPv6/examples/inet/redtest \
    -IxMIPv6/examples/inet/routerperf \
    -IxMIPv6/examples/inet/tcpclientserver \
    -IxMIPv6/examples/inet/tcpsack \
    -IxMIPv6/examples/ipv6 \
    -IxMIPv6/examples/ipv6/demonetworketh \
    -IxMIPv6/examples/ipv6/ipv6bulk \
    -IxMIPv6/examples/ipv6/ipv6nclients \
    -IxMIPv6/examples/ipv6/mobileipv6 \
    -IxMIPv6/examples/ipv6/nclients \
    -IxMIPv6/examples/mpls \
    -IxMIPv6/examples/mpls/ldp \
    -IxMIPv6/examples/mpls/net37 \
    -IxMIPv6/examples/mpls/testte_failure \
    -IxMIPv6/examples/mpls/testte_failure2 \
    -IxMIPv6/examples/mpls/testte_reroute \
    -IxMIPv6/examples/mpls/testte_routing \
    -IxMIPv6/examples/mpls/testte_tunnel \
    -IxMIPv6/examples/ospfv2 \
    -IxMIPv6/examples/ospfv2/areas \
    -IxMIPv6/examples/ospfv2/backbone \
    -IxMIPv6/examples/ospfv2/fulltest \
    -IxMIPv6/examples/ospfv2/simpletest \
    -IxMIPv6/examples/rtp \
    -IxMIPv6/examples/rtp/data \
    -IxMIPv6/examples/rtp/multicast1 \
    -IxMIPv6/examples/rtp/multicast2 \
    -IxMIPv6/examples/rtp/unicast \
    -IxMIPv6/examples/sctp \
    -IxMIPv6/examples/sctp/multihomed \
    -IxMIPv6/examples/sctp/nclients \
    -IxMIPv6/examples/wireless \
    -IxMIPv6/examples/wireless/handover \
    -IxMIPv6/examples/wireless/hosttohost \
    -IxMIPv6/examples/wireless/lan80211 \
    -IxMIPv6/examples/wireless/throughput \
    -IxMIPv6/migrate \
    -IxMIPv6/src \
    -IxMIPv6/src/applications \
    -IxMIPv6/src/applications/ethernet \
    -IxMIPv6/src/applications/generic \
    -IxMIPv6/src/applications/pingapp \
    -IxMIPv6/src/applications/rtpapp \
    -IxMIPv6/src/applications/sctpapp \
    -IxMIPv6/src/applications/tcpapp \
    -IxMIPv6/src/applications/udpapp \
    -IxMIPv6/src/base \
    -IxMIPv6/src/linklayer \
    -IxMIPv6/src/linklayer/contract \
    -IxMIPv6/src/linklayer/ethernet \
    -IxMIPv6/src/linklayer/etherswitch \
    -IxMIPv6/src/linklayer/ext \
    -IxMIPv6/src/linklayer/ieee80211 \
    -IxMIPv6/src/linklayer/ieee80211/mac \
    -IxMIPv6/src/linklayer/ieee80211/mgmt \
    -IxMIPv6/src/linklayer/mf80211 \
    -IxMIPv6/src/linklayer/mf80211/macLayer \
    -IxMIPv6/src/linklayer/mf80211/phyLayer \
    -IxMIPv6/src/linklayer/mf80211/phyLayer/decider \
    -IxMIPv6/src/linklayer/mf80211/phyLayer/snrEval \
    -IxMIPv6/src/linklayer/mfcore \
    -IxMIPv6/src/linklayer/ppp \
    -IxMIPv6/src/linklayer/radio \
    -IxMIPv6/src/mobility \
    -IxMIPv6/src/networklayer \
    -IxMIPv6/src/networklayer/arp \
    -IxMIPv6/src/networklayer/autorouting \
    -IxMIPv6/src/networklayer/common \
    -IxMIPv6/src/networklayer/contract \
    -IxMIPv6/src/networklayer/extras \
    -IxMIPv6/src/networklayer/icmpv6 \
    -IxMIPv6/src/networklayer/ipv4 \
    -IxMIPv6/src/networklayer/ipv6 \
    -IxMIPv6/src/networklayer/ldp \
    -IxMIPv6/src/networklayer/mpls \
    -IxMIPv6/src/networklayer/ospfv2 \
    -IxMIPv6/src/networklayer/ospfv2/interface \
    -IxMIPv6/src/networklayer/ospfv2/messagehandler \
    -IxMIPv6/src/networklayer/ospfv2/neighbor \
    -IxMIPv6/src/networklayer/ospfv2/router \
    -IxMIPv6/src/networklayer/queue \
    -IxMIPv6/src/networklayer/rsvp_te \
    -IxMIPv6/src/networklayer/ted \
    -IxMIPv6/src/networklayer/xmipv6 \
    -IxMIPv6/src/nodes \
    -IxMIPv6/src/nodes/adhoc \
    -IxMIPv6/src/nodes/ethernet \
    -IxMIPv6/src/nodes/inet \
    -IxMIPv6/src/nodes/ipv6 \
    -IxMIPv6/src/nodes/mpls \
    -IxMIPv6/src/nodes/wireless \
    -IxMIPv6/src/nodes/xmipv6 \
    -IxMIPv6/src/transport \
    -IxMIPv6/src/transport/contract \
    -IxMIPv6/src/transport/rtp \
    -IxMIPv6/src/transport/rtp/profiles \
    -IxMIPv6/src/transport/rtp/profiles/avprofile \
    -IxMIPv6/src/transport/sctp \
    -IxMIPv6/src/transport/tcp \
    -IxMIPv6/src/transport/tcp/flavours \
    -IxMIPv6/src/transport/tcp/queues \
    -IxMIPv6/src/transport/tcp_nsc \
    -IxMIPv6/src/transport/tcp_nsc/queues \
    -IxMIPv6/src/transport/tcp_old \
    -IxMIPv6/src/transport/tcp_old/flavours \
    -IxMIPv6/src/transport/tcp_old/queues \
    -IxMIPv6/src/transport/udp \
    -IxMIPv6/src/util \
    -IxMIPv6/src/util/headerserializers \
    -IxMIPv6/src/util/headerserializers/headers \
    -IxMIPv6/src/world

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
    $O/xMIPv6/src/applications/ethernet/EtherAppCli.o \
    $O/xMIPv6/src/applications/ethernet/EtherAppSrv.o \
    $O/xMIPv6/src/applications/generic/IPTrafGen.o \
    $O/xMIPv6/src/applications/pingapp/PingApp.o \
    $O/xMIPv6/src/applications/rtpapp/RTPApplication.o \
    $O/xMIPv6/src/applications/sctpapp/SCTPClient.o \
    $O/xMIPv6/src/applications/sctpapp/SCTPPeer.o \
    $O/xMIPv6/src/applications/sctpapp/SCTPServer.o \
    $O/xMIPv6/src/applications/tcpapp/TCPBasicClientApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPEchoApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.o \
    $O/xMIPv6/src/applications/tcpapp/TCPGenericSrvApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPGenericSrvThread.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSessionApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSinkApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSpoof.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSrvHostApp.o \
    $O/xMIPv6/src/applications/tcpapp/TelnetApp.o \
    $O/xMIPv6/src/applications/udpapp/UDPAppBase.o \
    $O/xMIPv6/src/applications/udpapp/UDPBasicApp.o \
    $O/xMIPv6/src/applications/udpapp/UDPEchoApp.o \
    $O/xMIPv6/src/applications/udpapp/UDPSink.o \
    $O/xMIPv6/src/applications/udpapp/UDPVideoStreamCli.o \
    $O/xMIPv6/src/applications/udpapp/UDPVideoStreamSvr.o \
    $O/xMIPv6/src/base/AbstractQueue.o \
    $O/xMIPv6/src/base/BasicModule.o \
    $O/xMIPv6/src/base/Blackboard.o \
    $O/xMIPv6/src/base/ByteArrayMessage.o \
    $O/xMIPv6/src/base/Join.o \
    $O/xMIPv6/src/base/ModuleAccess.o \
    $O/xMIPv6/src/base/NotificationBoard.o \
    $O/xMIPv6/src/base/NotifierConsts.o \
    $O/xMIPv6/src/base/PassiveQueueBase.o \
    $O/xMIPv6/src/base/ProtocolMap.o \
    $O/xMIPv6/src/base/QueueBase.o \
    $O/xMIPv6/src/base/QueueWithQoS.o \
    $O/xMIPv6/src/base/ReassemblyBuffer.o \
    $O/xMIPv6/src/base/Sink.o \
    $O/xMIPv6/src/linklayer/contract/MACAddress.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherBus.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherEncap.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherHub.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherLLC.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherMAC.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherMAC2.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherMACBase.o \
    $O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.o \
    $O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitNP.o \
    $O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitPP.o \
    $O/xMIPv6/src/linklayer/ext/cSocketRTScheduler.o \
    $O/xMIPv6/src/linklayer/ext/ExtInterface.o \
    $O/xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Mac.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/CSMAMacLayer.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/Mac80211.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/Decider80211.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/SnrDecider.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.o \
    $O/xMIPv6/src/linklayer/mfcore/BasicDecider.o \
    $O/xMIPv6/src/linklayer/mfcore/BasicSnrEval.o \
    $O/xMIPv6/src/linklayer/mfcore/WirelessMacBase.o \
    $O/xMIPv6/src/linklayer/ppp/DropsGenerator.o \
    $O/xMIPv6/src/linklayer/ppp/DuplicatesGenerator.o \
    $O/xMIPv6/src/linklayer/ppp/PPP.o \
    $O/xMIPv6/src/linklayer/ppp/ThruputMeter.o \
    $O/xMIPv6/src/linklayer/radio/AbstractRadio.o \
    $O/xMIPv6/src/linklayer/radio/GenericRadio.o \
    $O/xMIPv6/src/linklayer/radio/GenericRadioModel.o \
    $O/xMIPv6/src/linklayer/radio/Ieee80211Radio.o \
    $O/xMIPv6/src/linklayer/radio/Ieee80211RadioModel.o \
    $O/xMIPv6/src/linklayer/radio/Modulation.o \
    $O/xMIPv6/src/linklayer/radio/PathLossReceptionModel.o \
    $O/xMIPv6/src/mobility/ANSimMobility.o \
    $O/xMIPv6/src/mobility/BasicMobility.o \
    $O/xMIPv6/src/mobility/BonnMotionFileCache.o \
    $O/xMIPv6/src/mobility/BonnMotionMobility.o \
    $O/xMIPv6/src/mobility/CircleMobility.o \
    $O/xMIPv6/src/mobility/ConstSpeedMobility.o \
    $O/xMIPv6/src/mobility/LinearMobility.o \
    $O/xMIPv6/src/mobility/LineSegmentsMobilityBase.o \
    $O/xMIPv6/src/mobility/MassMobility.o \
    $O/xMIPv6/src/mobility/NullMobility.o \
    $O/xMIPv6/src/mobility/RandomWPMobility.o \
    $O/xMIPv6/src/mobility/RectangleMobility.o \
    $O/xMIPv6/src/mobility/TurtleMobility.o \
    $O/xMIPv6/src/networklayer/arp/ARP.o \
    $O/xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator.o \
    $O/xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator6.o \
    $O/xMIPv6/src/networklayer/autorouting/NetworkConfigurator.o \
    $O/xMIPv6/src/networklayer/common/InterfaceEntry.o \
    $O/xMIPv6/src/networklayer/common/InterfaceTable.o \
    $O/xMIPv6/src/networklayer/contract/IPAddress.o \
    $O/xMIPv6/src/networklayer/contract/IPAddressResolver.o \
    $O/xMIPv6/src/networklayer/contract/IPControlInfo.o \
    $O/xMIPv6/src/networklayer/contract/IPv6Address.o \
    $O/xMIPv6/src/networklayer/contract/IPv6ControlInfo.o \
    $O/xMIPv6/src/networklayer/contract/IPvXAddress.o \
    $O/xMIPv6/src/networklayer/extras/Dummy.o \
    $O/xMIPv6/src/networklayer/extras/FailureManager.o \
    $O/xMIPv6/src/networklayer/extras/NetworkInfo.o \
    $O/xMIPv6/src/networklayer/icmpv6/ICMPv6.o \
    $O/xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.o \
    $O/xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.o \
    $O/xMIPv6/src/networklayer/ipv4/ErrorHandling.o \
    $O/xMIPv6/src/networklayer/ipv4/ICMP.o \
    $O/xMIPv6/src/networklayer/ipv4/IP.o \
    $O/xMIPv6/src/networklayer/ipv4/IPFragBuf.o \
    $O/xMIPv6/src/networklayer/ipv4/IPRoute.o \
    $O/xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.o \
    $O/xMIPv6/src/networklayer/ipv4/RoutingTable.o \
    $O/xMIPv6/src/networklayer/ipv4/RoutingTableParser.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6Datagram.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6ErrorHandling.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6FragBuf.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6Tunneling.o \
    $O/xMIPv6/src/networklayer/ipv6/RoutingTable6.o \
    $O/xMIPv6/src/networklayer/ldp/LDP.o \
    $O/xMIPv6/src/networklayer/mpls/LIBTable.o \
    $O/xMIPv6/src/networklayer/mpls/MPLS.o \
    $O/xMIPv6/src/networklayer/mpls/MPLSPacket.o \
    $O/xMIPv6/src/networklayer/ospfv2/OSPFRouting.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/ASExternalLSA.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/NetworkLSA.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/OSPFArea.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/RouterLSA.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/SummaryLSA.o \
    $O/xMIPv6/src/networklayer/queue/BasicDSCPClassifier.o \
    $O/xMIPv6/src/networklayer/queue/DropTailQoSQueue.o \
    $O/xMIPv6/src/networklayer/queue/DropTailQueue.o \
    $O/xMIPv6/src/networklayer/queue/REDQueue.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVP.o \
    $O/xMIPv6/src/networklayer/rsvp_te/SimpleClassifier.o \
    $O/xMIPv6/src/networklayer/rsvp_te/Utils.o \
    $O/xMIPv6/src/networklayer/ted/LinkStateRouting.o \
    $O/xMIPv6/src/networklayer/ted/TED.o \
    $O/xMIPv6/src/networklayer/xmipv6/BindingCache.o \
    $O/xMIPv6/src/networklayer/xmipv6/BindingUpdateList.o \
    $O/xMIPv6/src/networklayer/xmipv6/MobilityHeader.o \
    $O/xMIPv6/src/networklayer/xmipv6/xMIPv6.o \
    $O/xMIPv6/src/transport/contract/SCTPSocket.o \
    $O/xMIPv6/src/transport/contract/TCPSocket.o \
    $O/xMIPv6/src/transport/contract/TCPSocketMap.o \
    $O/xMIPv6/src/transport/contract/UDPSocket.o \
    $O/xMIPv6/src/transport/rtp/reports.o \
    $O/xMIPv6/src/transport/rtp/RTCP.o \
    $O/xMIPv6/src/transport/rtp/RTCPPacket.o \
    $O/xMIPv6/src/transport/rtp/RTP.o \
    $O/xMIPv6/src/transport/rtp/RTPInnerPacket.o \
    $O/xMIPv6/src/transport/rtp/RTPInterfacePacket.o \
    $O/xMIPv6/src/transport/rtp/RTPPacket.o \
    $O/xMIPv6/src/transport/rtp/RTPParticipantInfo.o \
    $O/xMIPv6/src/transport/rtp/RTPPayloadReceiver.o \
    $O/xMIPv6/src/transport/rtp/RTPPayloadSender.o \
    $O/xMIPv6/src/transport/rtp/RTPProfile.o \
    $O/xMIPv6/src/transport/rtp/RTPReceiverInfo.o \
    $O/xMIPv6/src/transport/rtp/RTPSenderInfo.o \
    $O/xMIPv6/src/transport/rtp/sdes.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfile.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.o \
    $O/xMIPv6/src/transport/sctp/SCTP.o \
    $O/xMIPv6/src/transport/sctp/SCTPAlg.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationBase.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationEventProc.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationRcvMessage.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationUtil.o \
    $O/xMIPv6/src/transport/sctp/SCTPCCFunctions.o \
    $O/xMIPv6/src/transport/sctp/SCTPMessage.o \
    $O/xMIPv6/src/transport/sctp/SCTPQueue.o \
    $O/xMIPv6/src/transport/sctp/SCTPReceiveStream.o \
    $O/xMIPv6/src/transport/sctp/SCTPSendStream.o \
    $O/xMIPv6/src/transport/sctp/SCTPSSFunctions.o \
    $O/xMIPv6/src/transport/tcp/TCP.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionBase.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionEventProc.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionRcvSegment.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionUtil.o \
    $O/xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.o \
    $O/xMIPv6/src/transport/tcp/TCPSegment.o \
    $O/xMIPv6/src/transport/tcp/flavours/DumbTCP.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPNewReno.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPNoCongestionControl.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPReno.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPTahoe.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPMsgBasedRcvQueue.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPMsgBasedSendQueue.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPVirtualDataRcvQueue.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPVirtualDataSendQueue.o \
    $O/xMIPv6/src/transport/tcp_nsc/TCP_NSC.o \
    $O/xMIPv6/src/transport/tcp_nsc/TCP_NSC_Connection.o \
    $O/xMIPv6/src/transport/tcp_nsc/queues/TCP_NSC_VirtualDataQueues.o \
    $O/xMIPv6/src/transport/tcp_old/TCP.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionBase.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionEventProc.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionRcvSegment.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionUtil.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/DumbTCP.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPNoCongestionControl.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPReno.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPTahoe.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedRcvQueue.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedSendQueue.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataRcvQueue.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataSendQueue.o \
    $O/xMIPv6/src/transport/udp/UDP.o \
    $O/xMIPv6/src/util/common.o \
    $O/xMIPv6/src/util/NAMTraceWriter.o \
    $O/xMIPv6/src/util/opp_utils.o \
    $O/xMIPv6/src/util/TCPDump.o \
    $O/xMIPv6/src/util/ThruputMeteringChannel.o \
    $O/xMIPv6/src/util/XMLUtils.o \
    $O/xMIPv6/src/util/headerserializers/ICMPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/IPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/SCTPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/TCPIPchecksum.o \
    $O/xMIPv6/src/util/headerserializers/TCPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/UDPSerializer.o \
    $O/xMIPv6/src/world/ChannelAccess.o \
    $O/xMIPv6/src/world/ChannelControl.o \
    $O/xMIPv6/src/world/ChannelInstaller.o \
    $O/xMIPv6/src/world/NAMTrace.o \
    $O/xMIPv6/src/world/ScenarioManager.o \
    $O/util/mih_m.o \
    $O/wimax/wmaxmsg_m.o \
    $O/xMIPv6/src/applications/ethernet/EtherApp_m.o \
    $O/xMIPv6/src/applications/pingapp/PingPayload_m.o \
    $O/xMIPv6/src/applications/tcpapp/GenericAppMsg_m.o \
    $O/xMIPv6/src/applications/udpapp/UDPEchoAppMsg_m.o \
    $O/xMIPv6/src/base/ByteArrayMessage_m.o \
    $O/xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.o \
    $O/xMIPv6/src/linklayer/contract/PhyControlInfo_m.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherFrame_m.o \
    $O/xMIPv6/src/linklayer/ext/ExtFrame_m.o \
    $O/xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt_m.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.o \
    $O/xMIPv6/src/linklayer/mfcore/AirFrame_m.o \
    $O/xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.o \
    $O/xMIPv6/src/linklayer/mfcore/TransmComplete_m.o \
    $O/xMIPv6/src/linklayer/ppp/PPPFrame_m.o \
    $O/xMIPv6/src/networklayer/arp/ARPPacket_m.o \
    $O/xMIPv6/src/networklayer/contract/IPControlInfo_m.o \
    $O/xMIPv6/src/networklayer/contract/IPProtocolId_m.o \
    $O/xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.o \
    $O/xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.o \
    $O/xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.o \
    $O/xMIPv6/src/networklayer/ipv4/ControlManetRouting_m.o \
    $O/xMIPv6/src/networklayer/ipv4/ICMPMessage_m.o \
    $O/xMIPv6/src/networklayer/ipv4/IPDatagram_m.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.o \
    $O/xMIPv6/src/networklayer/ldp/LDPPacket_m.o \
    $O/xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.o \
    $O/xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/IntServ_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.o \
    $O/xMIPv6/src/networklayer/ted/LinkStatePacket_m.o \
    $O/xMIPv6/src/networklayer/ted/TED_m.o \
    $O/xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.o \
    $O/xMIPv6/src/transport/contract/SCTPCommand_m.o \
    $O/xMIPv6/src/transport/contract/TCPCommand_m.o \
    $O/xMIPv6/src/transport/contract/UDPControlInfo_m.o \
    $O/xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.o \
    $O/xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.o \
    $O/xMIPv6/src/transport/sctp/SCTPMessage_m.o \
    $O/xMIPv6/src/transport/tcp/TCPSegment_m.o \
    $O/xMIPv6/src/transport/udp/UDPPacket_m.o

# Message files
MSGFILES = \
    util/mih.msg \
    wimax/wmaxmsg.msg \
    xMIPv6/src/applications/ethernet/EtherApp.msg \
    xMIPv6/src/applications/pingapp/PingPayload.msg \
    xMIPv6/src/applications/tcpapp/GenericAppMsg.msg \
    xMIPv6/src/applications/udpapp/UDPEchoAppMsg.msg \
    xMIPv6/src/base/ByteArrayMessage.msg \
    xMIPv6/src/linklayer/contract/Ieee802Ctrl.msg \
    xMIPv6/src/linklayer/contract/PhyControlInfo.msg \
    xMIPv6/src/linklayer/ethernet/EtherFrame.msg \
    xMIPv6/src/linklayer/ext/ExtFrame.msg \
    xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame.msg \
    xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames.msg \
    xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg \
    xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt.msg \
    xMIPv6/src/linklayer/mf80211/macLayer/MacPkt.msg \
    xMIPv6/src/linklayer/mfcore/AirFrame.msg \
    xMIPv6/src/linklayer/mfcore/SnrControlInfo.msg \
    xMIPv6/src/linklayer/mfcore/TransmComplete.msg \
    xMIPv6/src/linklayer/ppp/PPPFrame.msg \
    xMIPv6/src/networklayer/arp/ARPPacket.msg \
    xMIPv6/src/networklayer/contract/IPControlInfo.msg \
    xMIPv6/src/networklayer/contract/IPProtocolId.msg \
    xMIPv6/src/networklayer/contract/IPv6ControlInfo.msg \
    xMIPv6/src/networklayer/icmpv6/ICMPv6Message.msg \
    xMIPv6/src/networklayer/icmpv6/IPv6NDMessage.msg \
    xMIPv6/src/networklayer/ipv4/ControlManetRouting.msg \
    xMIPv6/src/networklayer/ipv4/ICMPMessage.msg \
    xMIPv6/src/networklayer/ipv4/IPDatagram.msg \
    xMIPv6/src/networklayer/ipv6/IPv6Datagram.msg \
    xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.msg \
    xMIPv6/src/networklayer/ldp/LDPPacket.msg \
    xMIPv6/src/networklayer/ospfv2/OSPFPacket.msg \
    xMIPv6/src/networklayer/ospfv2/OSPFTimer.msg \
    xMIPv6/src/networklayer/rsvp_te/IntServ.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPHello.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPPacket.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg.msg \
    xMIPv6/src/networklayer/rsvp_te/SignallingMsg.msg \
    xMIPv6/src/networklayer/ted/LinkStatePacket.msg \
    xMIPv6/src/networklayer/ted/TED.msg \
    xMIPv6/src/networklayer/xmipv6/MobilityHeader.msg \
    xMIPv6/src/transport/contract/SCTPCommand.msg \
    xMIPv6/src/transport/contract/TCPCommand.msg \
    xMIPv6/src/transport/contract/UDPControlInfo.msg \
    xMIPv6/src/transport/rtp/RTPSenderControlMessage.msg \
    xMIPv6/src/transport/rtp/RTPSenderStatusMessage.msg \
    xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket.msg \
    xMIPv6/src/transport/sctp/SCTPMessage.msg \
    xMIPv6/src/transport/tcp/TCPSegment.msg \
    xMIPv6/src/transport/udp/UDPPacket.msg

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
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

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
	echo >.tmp$$$$ $(OBJS) $(EXTRA_OBJS) && $(AR) .tmplib$$$$ @.tmp$$$$ && $(CXX) -o $O/$(TARGET) $(WHOLE_ARCHIVE_ON) .tmplib$$$$ $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS) && rm .tmp$$$$ && rm .tmplib$$$$

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f numbat numbat.exe libnumbat.so libnumbat.a libnumbat.dll libnumbat.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f port-win32/*_m.cc port-win32/*_m.h
	-rm -f util/*_m.cc util/*_m.h
	-rm -f wimax/*_m.cc wimax/*_m.h
	-rm -f xMIPv6/*_m.cc xMIPv6/*_m.h
	-rm -f xMIPv6/3rdparty/*_m.cc xMIPv6/3rdparty/*_m.h
	-rm -f xMIPv6/_scripts/*_m.cc xMIPv6/_scripts/*_m.h
	-rm -f xMIPv6/_scripts/xmlschema/*_m.cc xMIPv6/_scripts/xmlschema/*_m.h
	-rm -f xMIPv6/_scripts/xsd2html/*_m.cc xMIPv6/_scripts/xsd2html/*_m.h
	-rm -f xMIPv6/doc/*_m.cc xMIPv6/doc/*_m.h
	-rm -f xMIPv6/doc/src/*_m.cc xMIPv6/doc/src/*_m.h
	-rm -f xMIPv6/doc/src/tcp/*_m.cc xMIPv6/doc/src/tcp/*_m.h
	-rm -f xMIPv6/doc/tutorial/*_m.cc xMIPv6/doc/tutorial/*_m.h
	-rm -f xMIPv6/doc/walkthrough/*_m.cc xMIPv6/doc/walkthrough/*_m.h
	-rm -f xMIPv6/doc/walkthrough/images/*_m.cc xMIPv6/doc/walkthrough/images/*_m.h
	-rm -f xMIPv6/doc/walkthrough/thumbs/*_m.cc xMIPv6/doc/walkthrough/thumbs/*_m.h
	-rm -f xMIPv6/etc/*_m.cc xMIPv6/etc/*_m.h
	-rm -f xMIPv6/etc/plugins/*_m.cc xMIPv6/etc/plugins/*_m.h
	-rm -f xMIPv6/examples/*_m.cc xMIPv6/examples/*_m.h
	-rm -f xMIPv6/examples/adhoc/*_m.cc xMIPv6/examples/adhoc/*_m.h
	-rm -f xMIPv6/examples/adhoc/ieee80211/*_m.cc xMIPv6/examples/adhoc/ieee80211/*_m.h
	-rm -f xMIPv6/examples/adhoc/mf80211/*_m.cc xMIPv6/examples/adhoc/mf80211/*_m.h
	-rm -f xMIPv6/examples/adhoc/mobility/*_m.cc xMIPv6/examples/adhoc/mobility/*_m.h
	-rm -f xMIPv6/examples/emulation/*_m.cc xMIPv6/examples/emulation/*_m.h
	-rm -f xMIPv6/examples/emulation/extclient/*_m.cc xMIPv6/examples/emulation/extclient/*_m.h
	-rm -f xMIPv6/examples/emulation/extserver/*_m.cc xMIPv6/examples/emulation/extserver/*_m.h
	-rm -f xMIPv6/examples/emulation/traceroute/*_m.cc xMIPv6/examples/emulation/traceroute/*_m.h
	-rm -f xMIPv6/examples/ethernet/*_m.cc xMIPv6/examples/ethernet/*_m.h
	-rm -f xMIPv6/examples/ethernet/arptest/*_m.cc xMIPv6/examples/ethernet/arptest/*_m.h
	-rm -f xMIPv6/examples/ethernet/arptest2/*_m.cc xMIPv6/examples/ethernet/arptest2/*_m.h
	-rm -f xMIPv6/examples/ethernet/lans/*_m.cc xMIPv6/examples/ethernet/lans/*_m.h
	-rm -f xMIPv6/examples/inet/*_m.cc xMIPv6/examples/inet/*_m.h
	-rm -f xMIPv6/examples/inet/ber/*_m.cc xMIPv6/examples/inet/ber/*_m.h
	-rm -f xMIPv6/examples/inet/bulktransfer/*_m.cc xMIPv6/examples/inet/bulktransfer/*_m.h
	-rm -f xMIPv6/examples/inet/flatnet/*_m.cc xMIPv6/examples/inet/flatnet/*_m.h
	-rm -f xMIPv6/examples/inet/kidsnw1/*_m.cc xMIPv6/examples/inet/kidsnw1/*_m.h
	-rm -f xMIPv6/examples/inet/multicast/*_m.cc xMIPv6/examples/inet/multicast/*_m.h
	-rm -f xMIPv6/examples/inet/nclients/*_m.cc xMIPv6/examples/inet/nclients/*_m.h
	-rm -f xMIPv6/examples/inet/redtest/*_m.cc xMIPv6/examples/inet/redtest/*_m.h
	-rm -f xMIPv6/examples/inet/routerperf/*_m.cc xMIPv6/examples/inet/routerperf/*_m.h
	-rm -f xMIPv6/examples/inet/tcpclientserver/*_m.cc xMIPv6/examples/inet/tcpclientserver/*_m.h
	-rm -f xMIPv6/examples/inet/tcpsack/*_m.cc xMIPv6/examples/inet/tcpsack/*_m.h
	-rm -f xMIPv6/examples/ipv6/*_m.cc xMIPv6/examples/ipv6/*_m.h
	-rm -f xMIPv6/examples/ipv6/demonetworketh/*_m.cc xMIPv6/examples/ipv6/demonetworketh/*_m.h
	-rm -f xMIPv6/examples/ipv6/ipv6bulk/*_m.cc xMIPv6/examples/ipv6/ipv6bulk/*_m.h
	-rm -f xMIPv6/examples/ipv6/ipv6nclients/*_m.cc xMIPv6/examples/ipv6/ipv6nclients/*_m.h
	-rm -f xMIPv6/examples/ipv6/mobileipv6/*_m.cc xMIPv6/examples/ipv6/mobileipv6/*_m.h
	-rm -f xMIPv6/examples/ipv6/nclients/*_m.cc xMIPv6/examples/ipv6/nclients/*_m.h
	-rm -f xMIPv6/examples/mpls/*_m.cc xMIPv6/examples/mpls/*_m.h
	-rm -f xMIPv6/examples/mpls/ldp/*_m.cc xMIPv6/examples/mpls/ldp/*_m.h
	-rm -f xMIPv6/examples/mpls/net37/*_m.cc xMIPv6/examples/mpls/net37/*_m.h
	-rm -f xMIPv6/examples/mpls/testte_failure/*_m.cc xMIPv6/examples/mpls/testte_failure/*_m.h
	-rm -f xMIPv6/examples/mpls/testte_failure2/*_m.cc xMIPv6/examples/mpls/testte_failure2/*_m.h
	-rm -f xMIPv6/examples/mpls/testte_reroute/*_m.cc xMIPv6/examples/mpls/testte_reroute/*_m.h
	-rm -f xMIPv6/examples/mpls/testte_routing/*_m.cc xMIPv6/examples/mpls/testte_routing/*_m.h
	-rm -f xMIPv6/examples/mpls/testte_tunnel/*_m.cc xMIPv6/examples/mpls/testte_tunnel/*_m.h
	-rm -f xMIPv6/examples/ospfv2/*_m.cc xMIPv6/examples/ospfv2/*_m.h
	-rm -f xMIPv6/examples/ospfv2/areas/*_m.cc xMIPv6/examples/ospfv2/areas/*_m.h
	-rm -f xMIPv6/examples/ospfv2/backbone/*_m.cc xMIPv6/examples/ospfv2/backbone/*_m.h
	-rm -f xMIPv6/examples/ospfv2/fulltest/*_m.cc xMIPv6/examples/ospfv2/fulltest/*_m.h
	-rm -f xMIPv6/examples/ospfv2/simpletest/*_m.cc xMIPv6/examples/ospfv2/simpletest/*_m.h
	-rm -f xMIPv6/examples/rtp/*_m.cc xMIPv6/examples/rtp/*_m.h
	-rm -f xMIPv6/examples/rtp/data/*_m.cc xMIPv6/examples/rtp/data/*_m.h
	-rm -f xMIPv6/examples/rtp/multicast1/*_m.cc xMIPv6/examples/rtp/multicast1/*_m.h
	-rm -f xMIPv6/examples/rtp/multicast2/*_m.cc xMIPv6/examples/rtp/multicast2/*_m.h
	-rm -f xMIPv6/examples/rtp/unicast/*_m.cc xMIPv6/examples/rtp/unicast/*_m.h
	-rm -f xMIPv6/examples/sctp/*_m.cc xMIPv6/examples/sctp/*_m.h
	-rm -f xMIPv6/examples/sctp/multihomed/*_m.cc xMIPv6/examples/sctp/multihomed/*_m.h
	-rm -f xMIPv6/examples/sctp/nclients/*_m.cc xMIPv6/examples/sctp/nclients/*_m.h
	-rm -f xMIPv6/examples/wireless/*_m.cc xMIPv6/examples/wireless/*_m.h
	-rm -f xMIPv6/examples/wireless/handover/*_m.cc xMIPv6/examples/wireless/handover/*_m.h
	-rm -f xMIPv6/examples/wireless/hosttohost/*_m.cc xMIPv6/examples/wireless/hosttohost/*_m.h
	-rm -f xMIPv6/examples/wireless/lan80211/*_m.cc xMIPv6/examples/wireless/lan80211/*_m.h
	-rm -f xMIPv6/examples/wireless/throughput/*_m.cc xMIPv6/examples/wireless/throughput/*_m.h
	-rm -f xMIPv6/migrate/*_m.cc xMIPv6/migrate/*_m.h
	-rm -f xMIPv6/src/*_m.cc xMIPv6/src/*_m.h
	-rm -f xMIPv6/src/applications/*_m.cc xMIPv6/src/applications/*_m.h
	-rm -f xMIPv6/src/applications/ethernet/*_m.cc xMIPv6/src/applications/ethernet/*_m.h
	-rm -f xMIPv6/src/applications/generic/*_m.cc xMIPv6/src/applications/generic/*_m.h
	-rm -f xMIPv6/src/applications/pingapp/*_m.cc xMIPv6/src/applications/pingapp/*_m.h
	-rm -f xMIPv6/src/applications/rtpapp/*_m.cc xMIPv6/src/applications/rtpapp/*_m.h
	-rm -f xMIPv6/src/applications/sctpapp/*_m.cc xMIPv6/src/applications/sctpapp/*_m.h
	-rm -f xMIPv6/src/applications/tcpapp/*_m.cc xMIPv6/src/applications/tcpapp/*_m.h
	-rm -f xMIPv6/src/applications/udpapp/*_m.cc xMIPv6/src/applications/udpapp/*_m.h
	-rm -f xMIPv6/src/base/*_m.cc xMIPv6/src/base/*_m.h
	-rm -f xMIPv6/src/linklayer/*_m.cc xMIPv6/src/linklayer/*_m.h
	-rm -f xMIPv6/src/linklayer/contract/*_m.cc xMIPv6/src/linklayer/contract/*_m.h
	-rm -f xMIPv6/src/linklayer/ethernet/*_m.cc xMIPv6/src/linklayer/ethernet/*_m.h
	-rm -f xMIPv6/src/linklayer/etherswitch/*_m.cc xMIPv6/src/linklayer/etherswitch/*_m.h
	-rm -f xMIPv6/src/linklayer/ext/*_m.cc xMIPv6/src/linklayer/ext/*_m.h
	-rm -f xMIPv6/src/linklayer/ieee80211/*_m.cc xMIPv6/src/linklayer/ieee80211/*_m.h
	-rm -f xMIPv6/src/linklayer/ieee80211/mac/*_m.cc xMIPv6/src/linklayer/ieee80211/mac/*_m.h
	-rm -f xMIPv6/src/linklayer/ieee80211/mgmt/*_m.cc xMIPv6/src/linklayer/ieee80211/mgmt/*_m.h
	-rm -f xMIPv6/src/linklayer/mf80211/*_m.cc xMIPv6/src/linklayer/mf80211/*_m.h
	-rm -f xMIPv6/src/linklayer/mf80211/macLayer/*_m.cc xMIPv6/src/linklayer/mf80211/macLayer/*_m.h
	-rm -f xMIPv6/src/linklayer/mf80211/phyLayer/*_m.cc xMIPv6/src/linklayer/mf80211/phyLayer/*_m.h
	-rm -f xMIPv6/src/linklayer/mf80211/phyLayer/decider/*_m.cc xMIPv6/src/linklayer/mf80211/phyLayer/decider/*_m.h
	-rm -f xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/*_m.cc xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/*_m.h
	-rm -f xMIPv6/src/linklayer/mfcore/*_m.cc xMIPv6/src/linklayer/mfcore/*_m.h
	-rm -f xMIPv6/src/linklayer/ppp/*_m.cc xMIPv6/src/linklayer/ppp/*_m.h
	-rm -f xMIPv6/src/linklayer/radio/*_m.cc xMIPv6/src/linklayer/radio/*_m.h
	-rm -f xMIPv6/src/mobility/*_m.cc xMIPv6/src/mobility/*_m.h
	-rm -f xMIPv6/src/networklayer/*_m.cc xMIPv6/src/networklayer/*_m.h
	-rm -f xMIPv6/src/networklayer/arp/*_m.cc xMIPv6/src/networklayer/arp/*_m.h
	-rm -f xMIPv6/src/networklayer/autorouting/*_m.cc xMIPv6/src/networklayer/autorouting/*_m.h
	-rm -f xMIPv6/src/networklayer/common/*_m.cc xMIPv6/src/networklayer/common/*_m.h
	-rm -f xMIPv6/src/networklayer/contract/*_m.cc xMIPv6/src/networklayer/contract/*_m.h
	-rm -f xMIPv6/src/networklayer/extras/*_m.cc xMIPv6/src/networklayer/extras/*_m.h
	-rm -f xMIPv6/src/networklayer/icmpv6/*_m.cc xMIPv6/src/networklayer/icmpv6/*_m.h
	-rm -f xMIPv6/src/networklayer/ipv4/*_m.cc xMIPv6/src/networklayer/ipv4/*_m.h
	-rm -f xMIPv6/src/networklayer/ipv6/*_m.cc xMIPv6/src/networklayer/ipv6/*_m.h
	-rm -f xMIPv6/src/networklayer/ldp/*_m.cc xMIPv6/src/networklayer/ldp/*_m.h
	-rm -f xMIPv6/src/networklayer/mpls/*_m.cc xMIPv6/src/networklayer/mpls/*_m.h
	-rm -f xMIPv6/src/networklayer/ospfv2/*_m.cc xMIPv6/src/networklayer/ospfv2/*_m.h
	-rm -f xMIPv6/src/networklayer/ospfv2/interface/*_m.cc xMIPv6/src/networklayer/ospfv2/interface/*_m.h
	-rm -f xMIPv6/src/networklayer/ospfv2/messagehandler/*_m.cc xMIPv6/src/networklayer/ospfv2/messagehandler/*_m.h
	-rm -f xMIPv6/src/networklayer/ospfv2/neighbor/*_m.cc xMIPv6/src/networklayer/ospfv2/neighbor/*_m.h
	-rm -f xMIPv6/src/networklayer/ospfv2/router/*_m.cc xMIPv6/src/networklayer/ospfv2/router/*_m.h
	-rm -f xMIPv6/src/networklayer/queue/*_m.cc xMIPv6/src/networklayer/queue/*_m.h
	-rm -f xMIPv6/src/networklayer/rsvp_te/*_m.cc xMIPv6/src/networklayer/rsvp_te/*_m.h
	-rm -f xMIPv6/src/networklayer/ted/*_m.cc xMIPv6/src/networklayer/ted/*_m.h
	-rm -f xMIPv6/src/networklayer/xmipv6/*_m.cc xMIPv6/src/networklayer/xmipv6/*_m.h
	-rm -f xMIPv6/src/nodes/*_m.cc xMIPv6/src/nodes/*_m.h
	-rm -f xMIPv6/src/nodes/adhoc/*_m.cc xMIPv6/src/nodes/adhoc/*_m.h
	-rm -f xMIPv6/src/nodes/ethernet/*_m.cc xMIPv6/src/nodes/ethernet/*_m.h
	-rm -f xMIPv6/src/nodes/inet/*_m.cc xMIPv6/src/nodes/inet/*_m.h
	-rm -f xMIPv6/src/nodes/ipv6/*_m.cc xMIPv6/src/nodes/ipv6/*_m.h
	-rm -f xMIPv6/src/nodes/mpls/*_m.cc xMIPv6/src/nodes/mpls/*_m.h
	-rm -f xMIPv6/src/nodes/wireless/*_m.cc xMIPv6/src/nodes/wireless/*_m.h
	-rm -f xMIPv6/src/nodes/xmipv6/*_m.cc xMIPv6/src/nodes/xmipv6/*_m.h
	-rm -f xMIPv6/src/transport/*_m.cc xMIPv6/src/transport/*_m.h
	-rm -f xMIPv6/src/transport/contract/*_m.cc xMIPv6/src/transport/contract/*_m.h
	-rm -f xMIPv6/src/transport/rtp/*_m.cc xMIPv6/src/transport/rtp/*_m.h
	-rm -f xMIPv6/src/transport/rtp/profiles/*_m.cc xMIPv6/src/transport/rtp/profiles/*_m.h
	-rm -f xMIPv6/src/transport/rtp/profiles/avprofile/*_m.cc xMIPv6/src/transport/rtp/profiles/avprofile/*_m.h
	-rm -f xMIPv6/src/transport/sctp/*_m.cc xMIPv6/src/transport/sctp/*_m.h
	-rm -f xMIPv6/src/transport/tcp/*_m.cc xMIPv6/src/transport/tcp/*_m.h
	-rm -f xMIPv6/src/transport/tcp/flavours/*_m.cc xMIPv6/src/transport/tcp/flavours/*_m.h
	-rm -f xMIPv6/src/transport/tcp/queues/*_m.cc xMIPv6/src/transport/tcp/queues/*_m.h
	-rm -f xMIPv6/src/transport/tcp_nsc/*_m.cc xMIPv6/src/transport/tcp_nsc/*_m.h
	-rm -f xMIPv6/src/transport/tcp_nsc/queues/*_m.cc xMIPv6/src/transport/tcp_nsc/queues/*_m.h
	-rm -f xMIPv6/src/transport/tcp_old/*_m.cc xMIPv6/src/transport/tcp_old/*_m.h
	-rm -f xMIPv6/src/transport/tcp_old/flavours/*_m.cc xMIPv6/src/transport/tcp_old/flavours/*_m.h
	-rm -f xMIPv6/src/transport/tcp_old/queues/*_m.cc xMIPv6/src/transport/tcp_old/queues/*_m.h
	-rm -f xMIPv6/src/transport/udp/*_m.cc xMIPv6/src/transport/udp/*_m.h
	-rm -f xMIPv6/src/util/*_m.cc xMIPv6/src/util/*_m.h
	-rm -f xMIPv6/src/util/headerserializers/*_m.cc xMIPv6/src/util/headerserializers/*_m.h
	-rm -f xMIPv6/src/util/headerserializers/headers/*_m.cc xMIPv6/src/util/headerserializers/headers/*_m.h
	-rm -f xMIPv6/src/world/*_m.cc xMIPv6/src/world/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc port-win32/*.cc util/*.cc wimax/*.cc xMIPv6/*.cc xMIPv6/3rdparty/*.cc xMIPv6/_scripts/*.cc xMIPv6/_scripts/xmlschema/*.cc xMIPv6/_scripts/xsd2html/*.cc xMIPv6/doc/*.cc xMIPv6/doc/src/*.cc xMIPv6/doc/src/tcp/*.cc xMIPv6/doc/tutorial/*.cc xMIPv6/doc/walkthrough/*.cc xMIPv6/doc/walkthrough/images/*.cc xMIPv6/doc/walkthrough/thumbs/*.cc xMIPv6/etc/*.cc xMIPv6/etc/plugins/*.cc xMIPv6/examples/*.cc xMIPv6/examples/adhoc/*.cc xMIPv6/examples/adhoc/ieee80211/*.cc xMIPv6/examples/adhoc/mf80211/*.cc xMIPv6/examples/adhoc/mobility/*.cc xMIPv6/examples/emulation/*.cc xMIPv6/examples/emulation/extclient/*.cc xMIPv6/examples/emulation/extserver/*.cc xMIPv6/examples/emulation/traceroute/*.cc xMIPv6/examples/ethernet/*.cc xMIPv6/examples/ethernet/arptest/*.cc xMIPv6/examples/ethernet/arptest2/*.cc xMIPv6/examples/ethernet/lans/*.cc xMIPv6/examples/inet/*.cc xMIPv6/examples/inet/ber/*.cc xMIPv6/examples/inet/bulktransfer/*.cc xMIPv6/examples/inet/flatnet/*.cc xMIPv6/examples/inet/kidsnw1/*.cc xMIPv6/examples/inet/multicast/*.cc xMIPv6/examples/inet/nclients/*.cc xMIPv6/examples/inet/redtest/*.cc xMIPv6/examples/inet/routerperf/*.cc xMIPv6/examples/inet/tcpclientserver/*.cc xMIPv6/examples/inet/tcpsack/*.cc xMIPv6/examples/ipv6/*.cc xMIPv6/examples/ipv6/demonetworketh/*.cc xMIPv6/examples/ipv6/ipv6bulk/*.cc xMIPv6/examples/ipv6/ipv6nclients/*.cc xMIPv6/examples/ipv6/mobileipv6/*.cc xMIPv6/examples/ipv6/nclients/*.cc xMIPv6/examples/mpls/*.cc xMIPv6/examples/mpls/ldp/*.cc xMIPv6/examples/mpls/net37/*.cc xMIPv6/examples/mpls/testte_failure/*.cc xMIPv6/examples/mpls/testte_failure2/*.cc xMIPv6/examples/mpls/testte_reroute/*.cc xMIPv6/examples/mpls/testte_routing/*.cc xMIPv6/examples/mpls/testte_tunnel/*.cc xMIPv6/examples/ospfv2/*.cc xMIPv6/examples/ospfv2/areas/*.cc xMIPv6/examples/ospfv2/backbone/*.cc xMIPv6/examples/ospfv2/fulltest/*.cc xMIPv6/examples/ospfv2/simpletest/*.cc xMIPv6/examples/rtp/*.cc xMIPv6/examples/rtp/data/*.cc xMIPv6/examples/rtp/multicast1/*.cc xMIPv6/examples/rtp/multicast2/*.cc xMIPv6/examples/rtp/unicast/*.cc xMIPv6/examples/sctp/*.cc xMIPv6/examples/sctp/multihomed/*.cc xMIPv6/examples/sctp/nclients/*.cc xMIPv6/examples/wireless/*.cc xMIPv6/examples/wireless/handover/*.cc xMIPv6/examples/wireless/hosttohost/*.cc xMIPv6/examples/wireless/lan80211/*.cc xMIPv6/examples/wireless/throughput/*.cc xMIPv6/migrate/*.cc xMIPv6/src/*.cc xMIPv6/src/applications/*.cc xMIPv6/src/applications/ethernet/*.cc xMIPv6/src/applications/generic/*.cc xMIPv6/src/applications/pingapp/*.cc xMIPv6/src/applications/rtpapp/*.cc xMIPv6/src/applications/sctpapp/*.cc xMIPv6/src/applications/tcpapp/*.cc xMIPv6/src/applications/udpapp/*.cc xMIPv6/src/base/*.cc xMIPv6/src/linklayer/*.cc xMIPv6/src/linklayer/contract/*.cc xMIPv6/src/linklayer/ethernet/*.cc xMIPv6/src/linklayer/etherswitch/*.cc xMIPv6/src/linklayer/ext/*.cc xMIPv6/src/linklayer/ieee80211/*.cc xMIPv6/src/linklayer/ieee80211/mac/*.cc xMIPv6/src/linklayer/ieee80211/mgmt/*.cc xMIPv6/src/linklayer/mf80211/*.cc xMIPv6/src/linklayer/mf80211/macLayer/*.cc xMIPv6/src/linklayer/mf80211/phyLayer/*.cc xMIPv6/src/linklayer/mf80211/phyLayer/decider/*.cc xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/*.cc xMIPv6/src/linklayer/mfcore/*.cc xMIPv6/src/linklayer/ppp/*.cc xMIPv6/src/linklayer/radio/*.cc xMIPv6/src/mobility/*.cc xMIPv6/src/networklayer/*.cc xMIPv6/src/networklayer/arp/*.cc xMIPv6/src/networklayer/autorouting/*.cc xMIPv6/src/networklayer/common/*.cc xMIPv6/src/networklayer/contract/*.cc xMIPv6/src/networklayer/extras/*.cc xMIPv6/src/networklayer/icmpv6/*.cc xMIPv6/src/networklayer/ipv4/*.cc xMIPv6/src/networklayer/ipv6/*.cc xMIPv6/src/networklayer/ldp/*.cc xMIPv6/src/networklayer/mpls/*.cc xMIPv6/src/networklayer/ospfv2/*.cc xMIPv6/src/networklayer/ospfv2/interface/*.cc xMIPv6/src/networklayer/ospfv2/messagehandler/*.cc xMIPv6/src/networklayer/ospfv2/neighbor/*.cc xMIPv6/src/networklayer/ospfv2/router/*.cc xMIPv6/src/networklayer/queue/*.cc xMIPv6/src/networklayer/rsvp_te/*.cc xMIPv6/src/networklayer/ted/*.cc xMIPv6/src/networklayer/xmipv6/*.cc xMIPv6/src/nodes/*.cc xMIPv6/src/nodes/adhoc/*.cc xMIPv6/src/nodes/ethernet/*.cc xMIPv6/src/nodes/inet/*.cc xMIPv6/src/nodes/ipv6/*.cc xMIPv6/src/nodes/mpls/*.cc xMIPv6/src/nodes/wireless/*.cc xMIPv6/src/nodes/xmipv6/*.cc xMIPv6/src/transport/*.cc xMIPv6/src/transport/contract/*.cc xMIPv6/src/transport/rtp/*.cc xMIPv6/src/transport/rtp/profiles/*.cc xMIPv6/src/transport/rtp/profiles/avprofile/*.cc xMIPv6/src/transport/sctp/*.cc xMIPv6/src/transport/tcp/*.cc xMIPv6/src/transport/tcp/flavours/*.cc xMIPv6/src/transport/tcp/queues/*.cc xMIPv6/src/transport/tcp_nsc/*.cc xMIPv6/src/transport/tcp_nsc/queues/*.cc xMIPv6/src/transport/tcp_old/*.cc xMIPv6/src/transport/tcp_old/flavours/*.cc xMIPv6/src/transport/tcp_old/queues/*.cc xMIPv6/src/transport/udp/*.cc xMIPv6/src/util/*.cc xMIPv6/src/util/headerserializers/*.cc xMIPv6/src/util/headerserializers/headers/*.cc xMIPv6/src/world/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/port-win32/addrpack.o: port-win32/addrpack.cc \
	util/Portable.h
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
	util/mih_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/util/ssinfo.o: util/ssinfo.cc \
	util/Portable.h \
	util/hoinfo.h \
	util/logger.h \
	util/mih_m.h \
	util/ssinfo.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/wimax/wmaxctrl.o: wimax/wmaxctrl.cc \
	util/Portable.h \
	util/fsm.h \
	util/hoinfo.h \
	util/logger.h \
	util/mih_m.h \
	util/ssinfo.h \
	util/ssinfoaccess.h \
	wimax/wmaxctrl.h \
	wimax/wmaxmac.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	wimax/wmaxradio.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6Access.h
$O/wimax/wmaxmac.o: wimax/wmaxmac.cc \
	util/Portable.h \
	util/fsm.h \
	util/hoinfo.h \
	util/logger.h \
	util/ssinfo.h \
	util/ssinfoaccess.h \
	wimax/wmaxctrl.h \
	wimax/wmaxmac.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6.h
$O/wimax/wmaxmaccs.o: wimax/wmaxmaccs.cc \
	util/Portable.h \
	util/hoinfo.h \
	util/logger.h \
	util/ssinfo.h \
	util/ssinfoaccess.h \
	wimax/wmaxmac.h \
	wimax/wmaxmaccs.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/wimax/wmaxmsg_m.o: wimax/wmaxmsg_m.cc \
	util/Portable.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/wimax/wmaxphy.o: wimax/wmaxphy.cc \
	util/Portable.h \
	util/hoinfo.h \
	util/logger.h \
	util/mih_m.h \
	util/ssinfo.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	wimax/wmaxphy.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/wimax/wmaxradio.o: wimax/wmaxradio.cc \
	util/fsm.h \
	util/logger.h \
	wimax/wmaxradio.h
$O/xMIPv6/src/applications/ethernet/EtherAppCli.o: xMIPv6/src/applications/ethernet/EtherAppCli.cc \
	xMIPv6/src/applications/ethernet/EtherAppCli.h \
	xMIPv6/src/applications/ethernet/EtherApp_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h
$O/xMIPv6/src/applications/ethernet/EtherAppSrv.o: xMIPv6/src/applications/ethernet/EtherAppSrv.cc \
	xMIPv6/src/applications/ethernet/EtherAppSrv.h \
	xMIPv6/src/applications/ethernet/EtherApp_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h
$O/xMIPv6/src/applications/ethernet/EtherApp_m.o: xMIPv6/src/applications/ethernet/EtherApp_m.cc \
	xMIPv6/src/applications/ethernet/EtherApp_m.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/applications/generic/IPTrafGen.o: xMIPv6/src/applications/generic/IPTrafGen.cc \
	xMIPv6/src/applications/generic/IPTrafGen.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/applications/pingapp/PingApp.o: xMIPv6/src/applications/pingapp/PingApp.cc \
	xMIPv6/src/applications/pingapp/PingApp.h \
	xMIPv6/src/applications/pingapp/PingPayload_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/applications/pingapp/PingPayload_m.o: xMIPv6/src/applications/pingapp/PingPayload_m.cc \
	xMIPv6/src/applications/pingapp/PingPayload_m.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/applications/rtpapp/RTPApplication.o: xMIPv6/src/applications/rtpapp/RTPApplication.cc \
	xMIPv6/src/applications/rtpapp/RTPApplication.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInterfacePacket.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/applications/sctpapp/SCTPClient.o: xMIPv6/src/applications/sctpapp/SCTPClient.cc \
	xMIPv6/src/applications/sctpapp/SCTPClient.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/contract/SCTPSocket.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/applications/sctpapp/SCTPPeer.o: xMIPv6/src/applications/sctpapp/SCTPPeer.cc \
	xMIPv6/src/applications/sctpapp/SCTPPeer.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/contract/SCTPSocket.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/applications/sctpapp/SCTPServer.o: xMIPv6/src/applications/sctpapp/SCTPServer.cc \
	xMIPv6/src/applications/sctpapp/SCTPServer.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/contract/SCTPSocket.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/applications/tcpapp/GenericAppMsg_m.o: xMIPv6/src/applications/tcpapp/GenericAppMsg_m.cc \
	xMIPv6/src/applications/tcpapp/GenericAppMsg_m.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/applications/tcpapp/TCPBasicClientApp.o: xMIPv6/src/applications/tcpapp/TCPBasicClientApp.cc \
	xMIPv6/src/applications/tcpapp/TCPBasicClientApp.h \
	xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/tcpapp/TCPEchoApp.o: xMIPv6/src/applications/tcpapp/TCPEchoApp.cc \
	xMIPv6/src/applications/tcpapp/TCPEchoApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.o: xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.cc \
	xMIPv6/src/applications/tcpapp/GenericAppMsg_m.h \
	xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/tcpapp/TCPGenericSrvApp.o: xMIPv6/src/applications/tcpapp/TCPGenericSrvApp.cc \
	xMIPv6/src/applications/tcpapp/GenericAppMsg_m.h \
	xMIPv6/src/applications/tcpapp/TCPGenericSrvApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/tcpapp/TCPGenericSrvThread.o: xMIPv6/src/applications/tcpapp/TCPGenericSrvThread.cc \
	xMIPv6/src/applications/tcpapp/GenericAppMsg_m.h \
	xMIPv6/src/applications/tcpapp/TCPGenericSrvThread.h \
	xMIPv6/src/applications/tcpapp/TCPSrvHostApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h \
	xMIPv6/src/transport/contract/TCPSocketMap.h
$O/xMIPv6/src/applications/tcpapp/TCPSessionApp.o: xMIPv6/src/applications/tcpapp/TCPSessionApp.cc \
	xMIPv6/src/applications/tcpapp/TCPSessionApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/tcpapp/TCPSinkApp.o: xMIPv6/src/applications/tcpapp/TCPSinkApp.cc \
	xMIPv6/src/applications/tcpapp/TCPSinkApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/tcpapp/TCPSpoof.o: xMIPv6/src/applications/tcpapp/TCPSpoof.cc \
	xMIPv6/src/applications/tcpapp/TCPSpoof.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h
$O/xMIPv6/src/applications/tcpapp/TCPSrvHostApp.o: xMIPv6/src/applications/tcpapp/TCPSrvHostApp.cc \
	xMIPv6/src/applications/tcpapp/TCPSrvHostApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h \
	xMIPv6/src/transport/contract/TCPSocketMap.h
$O/xMIPv6/src/applications/tcpapp/TelnetApp.o: xMIPv6/src/applications/tcpapp/TelnetApp.cc \
	xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.h \
	xMIPv6/src/applications/tcpapp/TelnetApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/applications/udpapp/UDPAppBase.o: xMIPv6/src/applications/udpapp/UDPAppBase.cc \
	xMIPv6/src/applications/udpapp/UDPAppBase.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/contract/UDPSocket.h
$O/xMIPv6/src/applications/udpapp/UDPBasicApp.o: xMIPv6/src/applications/udpapp/UDPBasicApp.cc \
	xMIPv6/src/applications/udpapp/UDPAppBase.h \
	xMIPv6/src/applications/udpapp/UDPBasicApp.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h
$O/xMIPv6/src/applications/udpapp/UDPEchoApp.o: xMIPv6/src/applications/udpapp/UDPEchoApp.cc \
	xMIPv6/src/applications/udpapp/UDPAppBase.h \
	xMIPv6/src/applications/udpapp/UDPBasicApp.h \
	xMIPv6/src/applications/udpapp/UDPEchoApp.h \
	xMIPv6/src/applications/udpapp/UDPEchoAppMsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h
$O/xMIPv6/src/applications/udpapp/UDPEchoAppMsg_m.o: xMIPv6/src/applications/udpapp/UDPEchoAppMsg_m.cc \
	xMIPv6/src/applications/udpapp/UDPEchoAppMsg_m.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/applications/udpapp/UDPSink.o: xMIPv6/src/applications/udpapp/UDPSink.cc \
	xMIPv6/src/applications/udpapp/UDPAppBase.h \
	xMIPv6/src/applications/udpapp/UDPSink.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h
$O/xMIPv6/src/applications/udpapp/UDPVideoStreamCli.o: xMIPv6/src/applications/udpapp/UDPVideoStreamCli.cc \
	xMIPv6/src/applications/udpapp/UDPAppBase.h \
	xMIPv6/src/applications/udpapp/UDPVideoStreamCli.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h
$O/xMIPv6/src/applications/udpapp/UDPVideoStreamSvr.o: xMIPv6/src/applications/udpapp/UDPVideoStreamSvr.cc \
	xMIPv6/src/applications/udpapp/UDPAppBase.h \
	xMIPv6/src/applications/udpapp/UDPVideoStreamSvr.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h
$O/xMIPv6/src/base/AbstractQueue.o: xMIPv6/src/base/AbstractQueue.cc \
	xMIPv6/src/base/AbstractQueue.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/base/BasicModule.o: xMIPv6/src/base/BasicModule.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h
$O/xMIPv6/src/base/Blackboard.o: xMIPv6/src/base/Blackboard.cc \
	xMIPv6/src/base/Blackboard.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ModuleAccess.h
$O/xMIPv6/src/base/ByteArrayMessage.o: xMIPv6/src/base/ByteArrayMessage.cc \
	xMIPv6/src/base/ByteArrayMessage.h \
	xMIPv6/src/base/ByteArrayMessage_m.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/base/ByteArrayMessage_m.o: xMIPv6/src/base/ByteArrayMessage_m.cc \
	xMIPv6/src/base/ByteArrayMessage_m.h \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/base/Join.o: xMIPv6/src/base/Join.cc \
	xMIPv6/src/base/INETDefs.h
$O/xMIPv6/src/base/ModuleAccess.o: xMIPv6/src/base/ModuleAccess.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ModuleAccess.h
$O/xMIPv6/src/base/NotificationBoard.o: xMIPv6/src/base/NotificationBoard.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h
$O/xMIPv6/src/base/NotifierConsts.o: xMIPv6/src/base/NotifierConsts.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/NotifierConsts.h
$O/xMIPv6/src/base/PassiveQueueBase.o: xMIPv6/src/base/PassiveQueueBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/PassiveQueueBase.h
$O/xMIPv6/src/base/ProtocolMap.o: xMIPv6/src/base/ProtocolMap.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ProtocolMap.h
$O/xMIPv6/src/base/QueueBase.o: xMIPv6/src/base/QueueBase.cc \
	xMIPv6/src/base/AbstractQueue.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/QueueBase.h
$O/xMIPv6/src/base/QueueWithQoS.o: xMIPv6/src/base/QueueWithQoS.cc \
	xMIPv6/src/base/AbstractQueue.h \
	xMIPv6/src/base/EnqueueHook.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/QueueWithQoS.h
$O/xMIPv6/src/base/ReassemblyBuffer.o: xMIPv6/src/base/ReassemblyBuffer.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ReassemblyBuffer.h
$O/xMIPv6/src/base/Sink.o: xMIPv6/src/base/Sink.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/Sink.h
$O/xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.o: xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h
$O/xMIPv6/src/linklayer/contract/MACAddress.o: xMIPv6/src/linklayer/contract/MACAddress.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h
$O/xMIPv6/src/linklayer/contract/PhyControlInfo_m.o: xMIPv6/src/linklayer/contract/PhyControlInfo_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h
$O/xMIPv6/src/linklayer/ethernet/EtherBus.o: xMIPv6/src/linklayer/ethernet/EtherBus.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherBus.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h
$O/xMIPv6/src/linklayer/ethernet/EtherEncap.o: xMIPv6/src/linklayer/ethernet/EtherEncap.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/TxNotifDetails.h \
	xMIPv6/src/linklayer/ethernet/EtherEncap.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/EtherMAC.h \
	xMIPv6/src/linklayer/ethernet/EtherMACBase.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/linklayer/ethernet/EtherFrame_m.o: xMIPv6/src/linklayer/ethernet/EtherFrame_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h
$O/xMIPv6/src/linklayer/ethernet/EtherHub.o: xMIPv6/src/linklayer/ethernet/EtherHub.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/EtherHub.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h
$O/xMIPv6/src/linklayer/ethernet/EtherLLC.o: xMIPv6/src/linklayer/ethernet/EtherLLC.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/EtherLLC.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h
$O/xMIPv6/src/linklayer/ethernet/EtherMAC.o: xMIPv6/src/linklayer/ethernet/EtherMAC.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/TxNotifDetails.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/EtherMAC.h \
	xMIPv6/src/linklayer/ethernet/EtherMACBase.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h
$O/xMIPv6/src/linklayer/ethernet/EtherMAC2.o: xMIPv6/src/linklayer/ethernet/EtherMAC2.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/TxNotifDetails.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/EtherMAC2.h \
	xMIPv6/src/linklayer/ethernet/EtherMACBase.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h
$O/xMIPv6/src/linklayer/ethernet/EtherMACBase.o: xMIPv6/src/linklayer/ethernet/EtherMACBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/TxNotifDetails.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/EtherMACBase.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.o: xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.h
$O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitNP.o: xMIPv6/src/linklayer/etherswitch/MACRelayUnitNP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.h \
	xMIPv6/src/linklayer/etherswitch/MACRelayUnitNP.h
$O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitPP.o: xMIPv6/src/linklayer/etherswitch/MACRelayUnitPP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.h \
	xMIPv6/src/linklayer/etherswitch/MACRelayUnitPP.h
$O/xMIPv6/src/linklayer/ext/ExtFrame_m.o: xMIPv6/src/linklayer/ext/ExtFrame_m.cc \
	xMIPv6/src/linklayer/ext/ExtFrame_m.h
$O/xMIPv6/src/linklayer/ext/ExtInterface.o: xMIPv6/src/linklayer/ext/ExtInterface.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ext/ExtFrame_m.h \
	xMIPv6/src/linklayer/ext/ExtInterface.h \
	xMIPv6/src/linklayer/ext/cSocketRTScheduler.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/util/headerserializers/IPSerializer.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h
$O/xMIPv6/src/linklayer/ext/cSocketRTScheduler.o: xMIPv6/src/linklayer/ext/cSocketRTScheduler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/ext/ExtFrame_m.h \
	xMIPv6/src/linklayer/ext/cSocketRTScheduler.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h \
	xMIPv6/src/util/headerserializers/headers/ethernet.h
$O/xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.o: xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h
$O/xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Mac.o: xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Mac.cc \
	xMIPv6/src/base/FSMA.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Mac.h \
	xMIPv6/src/linklayer/mfcore/WirelessMacBase.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ethernet/EtherFrame_m.h \
	xMIPv6/src/linklayer/ethernet/Ethernet.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.cc \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.h
$O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.o: xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h
$O/xMIPv6/src/linklayer/mf80211/macLayer/CSMAMacLayer.o: xMIPv6/src/linklayer/mf80211/macLayer/CSMAMacLayer.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mf80211/macLayer/CSMAMacLayer.h \
	xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.h \
	xMIPv6/src/linklayer/mfcore/WirelessMacBase.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/linklayer/mf80211/macLayer/Mac80211.o: xMIPv6/src/linklayer/mf80211/macLayer/Mac80211.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mf80211/macLayer/Consts80211.h \
	xMIPv6/src/linklayer/mf80211/macLayer/Mac80211.h \
	xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt_m.h \
	xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.h \
	xMIPv6/src/linklayer/mfcore/WirelessMacBase.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt_m.o: xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt_m.h \
	xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.h
$O/xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.o: xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.h
$O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/Decider80211.o: xMIPv6/src/linklayer/mf80211/phyLayer/decider/Decider80211.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mf80211/macLayer/Consts80211.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/decider/Decider80211.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicDecider.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.o: xMIPv6/src/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/decider/SnrDecider.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicDecider.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/SnrDecider.o: xMIPv6/src/linklayer/mf80211/phyLayer/decider/SnrDecider.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/decider/SnrDecider.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicDecider.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.o: xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicSnrEval.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.o: xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicSnrEval.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.o: xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mf80211/macLayer/Consts80211.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.h \
	xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicSnrEval.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/mfcore/AirFrame_m.o: xMIPv6/src/linklayer/mfcore/AirFrame_m.cc \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/mfcore/BasicDecider.o: xMIPv6/src/linklayer/mfcore/BasicDecider.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicDecider.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/mfcore/BasicSnrEval.o: xMIPv6/src/linklayer/mfcore/BasicSnrEval.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/BasicSnrEval.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/linklayer/mfcore/TransmComplete_m.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.o: xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h
$O/xMIPv6/src/linklayer/mfcore/TransmComplete_m.o: xMIPv6/src/linklayer/mfcore/TransmComplete_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/mfcore/TransmComplete_m.h
$O/xMIPv6/src/linklayer/mfcore/WirelessMacBase.o: xMIPv6/src/linklayer/mfcore/WirelessMacBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/WirelessMacBase.h
$O/xMIPv6/src/linklayer/ppp/DropsGenerator.o: xMIPv6/src/linklayer/ppp/DropsGenerator.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/ppp/DropsGenerator.h
$O/xMIPv6/src/linklayer/ppp/DuplicatesGenerator.o: xMIPv6/src/linklayer/ppp/DuplicatesGenerator.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/ppp/DuplicatesGenerator.h
$O/xMIPv6/src/linklayer/ppp/PPP.o: xMIPv6/src/linklayer/ppp/PPP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/TxNotifDetails.h \
	xMIPv6/src/linklayer/ppp/PPP.h \
	xMIPv6/src/linklayer/ppp/PPPFrame_m.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/linklayer/ppp/PPPFrame_m.o: xMIPv6/src/linklayer/ppp/PPPFrame_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/ppp/PPPFrame_m.h
$O/xMIPv6/src/linklayer/ppp/ThruputMeter.o: xMIPv6/src/linklayer/ppp/ThruputMeter.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/ppp/ThruputMeter.h
$O/xMIPv6/src/linklayer/radio/AbstractRadio.o: xMIPv6/src/linklayer/radio/AbstractRadio.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/PhyControlInfo_m.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/linklayer/radio/AbstractRadio.h \
	xMIPv6/src/linklayer/radio/IRadioModel.h \
	xMIPv6/src/linklayer/radio/IReceptionModel.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/radio/GenericRadio.o: xMIPv6/src/linklayer/radio/GenericRadio.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/linklayer/radio/AbstractRadio.h \
	xMIPv6/src/linklayer/radio/GenericRadio.h \
	xMIPv6/src/linklayer/radio/IRadioModel.h \
	xMIPv6/src/linklayer/radio/IReceptionModel.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/radio/GenericRadioModel.o: xMIPv6/src/linklayer/radio/GenericRadioModel.cc \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/linklayer/radio/GenericRadioModel.h \
	xMIPv6/src/linklayer/radio/IModulation.h \
	xMIPv6/src/linklayer/radio/IRadioModel.h \
	xMIPv6/src/linklayer/radio/Modulation.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/radio/Ieee80211Radio.o: xMIPv6/src/linklayer/radio/Ieee80211Radio.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/RadioState.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/linklayer/radio/AbstractRadio.h \
	xMIPv6/src/linklayer/radio/IRadioModel.h \
	xMIPv6/src/linklayer/radio/IReceptionModel.h \
	xMIPv6/src/linklayer/radio/Ieee80211Radio.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/linklayer/radio/Ieee80211RadioModel.o: xMIPv6/src/linklayer/radio/Ieee80211RadioModel.cc \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/mfcore/SnrList.h \
	xMIPv6/src/linklayer/radio/IRadioModel.h \
	xMIPv6/src/linklayer/radio/Ieee80211RadioModel.h \
	xMIPv6/src/util/FWMath.h
$O/xMIPv6/src/linklayer/radio/Modulation.o: xMIPv6/src/linklayer/radio/Modulation.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/radio/IModulation.h \
	xMIPv6/src/linklayer/radio/Modulation.h
$O/xMIPv6/src/linklayer/radio/PathLossReceptionModel.o: xMIPv6/src/linklayer/radio/PathLossReceptionModel.cc \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/linklayer/radio/IReceptionModel.h \
	xMIPv6/src/linklayer/radio/PathLossReceptionModel.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/ANSimMobility.o: xMIPv6/src/mobility/ANSimMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/ANSimMobility.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/LineSegmentsMobilityBase.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/BasicMobility.o: xMIPv6/src/mobility/BasicMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/BonnMotionFileCache.o: xMIPv6/src/mobility/BonnMotionFileCache.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/BonnMotionFileCache.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/BonnMotionMobility.o: xMIPv6/src/mobility/BonnMotionMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/BonnMotionFileCache.h \
	xMIPv6/src/mobility/BonnMotionMobility.h \
	xMIPv6/src/mobility/LineSegmentsMobilityBase.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/CircleMobility.o: xMIPv6/src/mobility/CircleMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/CircleMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/ConstSpeedMobility.o: xMIPv6/src/mobility/ConstSpeedMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/ConstSpeedMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/LineSegmentsMobilityBase.o: xMIPv6/src/mobility/LineSegmentsMobilityBase.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/LineSegmentsMobilityBase.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/LinearMobility.o: xMIPv6/src/mobility/LinearMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/LinearMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/MassMobility.o: xMIPv6/src/mobility/MassMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/MassMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/NullMobility.o: xMIPv6/src/mobility/NullMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/NullMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/RandomWPMobility.o: xMIPv6/src/mobility/RandomWPMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/LineSegmentsMobilityBase.h \
	xMIPv6/src/mobility/RandomWPMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/RectangleMobility.o: xMIPv6/src/mobility/RectangleMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/RectangleMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/mobility/TurtleMobility.o: xMIPv6/src/mobility/TurtleMobility.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/mobility/BasicMobility.h \
	xMIPv6/src/mobility/LineSegmentsMobilityBase.h \
	xMIPv6/src/mobility/TurtleMobility.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/networklayer/arp/ARP.o: xMIPv6/src/networklayer/arp/ARP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/arp/ARP.h \
	xMIPv6/src/networklayer/arp/ARPPacket_m.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h
$O/xMIPv6/src/networklayer/arp/ARPPacket_m.o: xMIPv6/src/networklayer/arp/ARPPacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/arp/ARPPacket_m.h \
	xMIPv6/src/networklayer/contract/IPAddress.h
$O/xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator.o: xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h
$O/xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator6.o: xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator6.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator6.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/autorouting/NetworkConfigurator.o: xMIPv6/src/networklayer/autorouting/NetworkConfigurator.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/autorouting/NetworkConfigurator.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h
$O/xMIPv6/src/networklayer/common/InterfaceEntry.o: xMIPv6/src/networklayer/common/InterfaceEntry.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/common/InterfaceTable.o: xMIPv6/src/networklayer/common/InterfaceTable.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/networklayer/contract/IPAddress.o: xMIPv6/src/networklayer/contract/IPAddress.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h
$O/xMIPv6/src/networklayer/contract/IPAddressResolver.o: xMIPv6/src/networklayer/contract/IPAddressResolver.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/contract/IPControlInfo.o: xMIPv6/src/networklayer/contract/IPControlInfo.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h
$O/xMIPv6/src/networklayer/contract/IPControlInfo_m.o: xMIPv6/src/networklayer/contract/IPControlInfo_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h
$O/xMIPv6/src/networklayer/contract/IPProtocolId_m.o: xMIPv6/src/networklayer/contract/IPProtocolId_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h
$O/xMIPv6/src/networklayer/contract/IPv6Address.o: xMIPv6/src/networklayer/contract/IPv6Address.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h
$O/xMIPv6/src/networklayer/contract/IPv6ControlInfo.o: xMIPv6/src/networklayer/contract/IPv6ControlInfo.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.o: xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/networklayer/contract/IPvXAddress.o: xMIPv6/src/networklayer/contract/IPvXAddress.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h
$O/xMIPv6/src/networklayer/extras/Dummy.o: xMIPv6/src/networklayer/extras/Dummy.cc
$O/xMIPv6/src/networklayer/extras/FailureManager.o: xMIPv6/src/networklayer/extras/FailureManager.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IScriptable.h \
	xMIPv6/src/networklayer/extras/FailureManager.h
$O/xMIPv6/src/networklayer/extras/NetworkInfo.o: xMIPv6/src/networklayer/extras/NetworkInfo.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IScriptable.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/extras/NetworkInfo.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h
$O/xMIPv6/src/networklayer/icmpv6/ICMPv6.o: xMIPv6/src/networklayer/icmpv6/ICMPv6.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.o: xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h
$O/xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.o: xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h
$O/xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.o: xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h
$O/xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.o: xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.cc \
	util/Portable.h \
	util/fsm.h \
	util/hoinfo.h \
	util/ssinfo.h \
	wimax/wmaxctrl.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6Access.h
$O/xMIPv6/src/networklayer/ipv4/ControlManetRouting_m.o: xMIPv6/src/networklayer/ipv4/ControlManetRouting_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ipv4/ControlManetRouting_m.h
$O/xMIPv6/src/networklayer/ipv4/ErrorHandling.o: xMIPv6/src/networklayer/ipv4/ErrorHandling.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/ErrorHandling.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h
$O/xMIPv6/src/networklayer/ipv4/ICMP.o: xMIPv6/src/networklayer/ipv4/ICMP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/ICMP.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h
$O/xMIPv6/src/networklayer/ipv4/ICMPMessage_m.o: xMIPv6/src/networklayer/ipv4/ICMPMessage_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h
$O/xMIPv6/src/networklayer/ipv4/IP.o: xMIPv6/src/networklayer/ipv4/IP.cc \
	xMIPv6/src/base/AbstractQueue.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/ProtocolMap.h \
	xMIPv6/src/base/QueueBase.h \
	xMIPv6/src/base/ReassemblyBuffer.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/arp/ARPPacket_m.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/ICMP.h \
	xMIPv6/src/networklayer/ipv4/ICMPAccess.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IP.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPFragBuf.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h
$O/xMIPv6/src/networklayer/ipv4/IPDatagram_m.o: xMIPv6/src/networklayer/ipv4/IPDatagram_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h
$O/xMIPv6/src/networklayer/ipv4/IPFragBuf.o: xMIPv6/src/networklayer/ipv4/IPFragBuf.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/ReassemblyBuffer.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/ICMP.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPFragBuf.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h
$O/xMIPv6/src/networklayer/ipv4/IPRoute.o: xMIPv6/src/networklayer/ipv4/IPRoute.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h
$O/xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.o: xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h
$O/xMIPv6/src/networklayer/ipv4/RoutingTable.o: xMIPv6/src/networklayer/ipv4/RoutingTable.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableParser.h
$O/xMIPv6/src/networklayer/ipv4/RoutingTableParser.o: xMIPv6/src/networklayer/ipv4/RoutingTableParser.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableParser.h
$O/xMIPv6/src/networklayer/ipv6/IPv6.o: xMIPv6/src/networklayer/ipv6/IPv6.cc \
	util/Portable.h \
	util/fsm.h \
	util/hoinfo.h \
	util/ssinfo.h \
	wimax/wmaxctrl.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/AbstractQueue.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/ProtocolMap.h \
	xMIPv6/src/base/QueueBase.h \
	xMIPv6/src/base/ReassemblyBuffer.h \
	xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6FragBuf.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6.h
$O/xMIPv6/src/networklayer/ipv6/IPv6Datagram.o: xMIPv6/src/networklayer/ipv6/IPv6Datagram.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.o: xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6ErrorHandling.o: xMIPv6/src/networklayer/ipv6/IPv6ErrorHandling.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ErrorHandling.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.o: xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.o: xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6FragBuf.o: xMIPv6/src/networklayer/ipv6/IPv6FragBuf.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/base/ReassemblyBuffer.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6FragBuf.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.o: xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/ipv6/IPv6Tunneling.o: xMIPv6/src/networklayer/ipv6/IPv6Tunneling.cc \
	util/Portable.h \
	util/fsm.h \
	util/hoinfo.h \
	util/ssinfo.h \
	wimax/wmaxctrl.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6Access.h
$O/xMIPv6/src/networklayer/ipv6/RoutingTable6.o: xMIPv6/src/networklayer/ipv6/RoutingTable6.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/util/opp_utils.h
$O/xMIPv6/src/networklayer/ldp/LDP.o: xMIPv6/src/networklayer/ldp/LDP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ldp/LDP.h \
	xMIPv6/src/networklayer/ldp/LDPPacket_m.h \
	xMIPv6/src/networklayer/mpls/ConstType.h \
	xMIPv6/src/networklayer/mpls/IClassifier.h \
	xMIPv6/src/networklayer/mpls/LIBTable.h \
	xMIPv6/src/networklayer/mpls/LIBTableAccess.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/ted/TED.h \
	xMIPv6/src/networklayer/ted/TEDAccess.h \
	xMIPv6/src/networklayer/ted/TED_m.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h \
	xMIPv6/src/transport/contract/TCPSocketMap.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/contract/UDPSocket.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/udp/UDPPacket.h \
	xMIPv6/src/transport/udp/UDPPacket_m.h
$O/xMIPv6/src/networklayer/ldp/LDPPacket_m.o: xMIPv6/src/networklayer/ldp/LDPPacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ldp/LDPPacket_m.h
$O/xMIPv6/src/networklayer/mpls/LIBTable.o: xMIPv6/src/networklayer/mpls/LIBTable.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/mpls/ConstType.h \
	xMIPv6/src/networklayer/mpls/LIBTable.h \
	xMIPv6/src/util/XMLUtils.h
$O/xMIPv6/src/networklayer/mpls/MPLS.o: xMIPv6/src/networklayer/mpls/MPLS.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ldp/LDP.h \
	xMIPv6/src/networklayer/ldp/LDPPacket_m.h \
	xMIPv6/src/networklayer/mpls/ConstType.h \
	xMIPv6/src/networklayer/mpls/IClassifier.h \
	xMIPv6/src/networklayer/mpls/LIBTable.h \
	xMIPv6/src/networklayer/mpls/LIBTableAccess.h \
	xMIPv6/src/networklayer/mpls/MPLS.h \
	xMIPv6/src/networklayer/mpls/MPLSPacket.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/Utils.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h \
	xMIPv6/src/transport/contract/TCPSocketMap.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/contract/UDPSocket.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h
$O/xMIPv6/src/networklayer/mpls/MPLSPacket.o: xMIPv6/src/networklayer/mpls/MPLSPacket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/mpls/MPLSPacket.h
$O/xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.o: xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h
$O/xMIPv6/src/networklayer/ospfv2/OSPFRouting.o: xMIPv6/src/networklayer/ospfv2/OSPFRouting.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFRouting.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.o: xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.o: xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.o: xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.o: xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.o: xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.o: xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.o: xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.o: xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.o: xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/router/ASExternalLSA.o: xMIPv6/src/networklayer/ospfv2/router/ASExternalLSA.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/router/NetworkLSA.o: xMIPv6/src/networklayer/ospfv2/router/NetworkLSA.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/router/OSPFArea.o: xMIPv6/src/networklayer/ospfv2/router/OSPFArea.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.o: xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.h \
	xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/IMessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.h \
	xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFArea.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/router/RouterLSA.o: xMIPv6/src/networklayer/ospfv2/router/RouterLSA.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/ospfv2/router/SummaryLSA.o: xMIPv6/src/networklayer/ospfv2/router/SummaryLSA.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.h \
	xMIPv6/src/networklayer/ospfv2/router/LSA.h \
	xMIPv6/src/networklayer/ospfv2/router/OSPFcommon.h
$O/xMIPv6/src/networklayer/queue/BasicDSCPClassifier.o: xMIPv6/src/networklayer/queue/BasicDSCPClassifier.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/queue/BasicDSCPClassifier.h \
	xMIPv6/src/networklayer/queue/IQoSClassifier.h
$O/xMIPv6/src/networklayer/queue/DropTailQoSQueue.o: xMIPv6/src/networklayer/queue/DropTailQoSQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/networklayer/queue/DropTailQoSQueue.h \
	xMIPv6/src/networklayer/queue/IQoSClassifier.h
$O/xMIPv6/src/networklayer/queue/DropTailQueue.o: xMIPv6/src/networklayer/queue/DropTailQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/networklayer/queue/DropTailQueue.h
$O/xMIPv6/src/networklayer/queue/REDQueue.o: xMIPv6/src/networklayer/queue/REDQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IPassiveQueue.h \
	xMIPv6/src/base/PassiveQueueBase.h \
	xMIPv6/src/networklayer/queue/REDQueue.h
$O/xMIPv6/src/networklayer/rsvp_te/IntServ_m.o: xMIPv6/src/networklayer/rsvp_te/IntServ_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h
$O/xMIPv6/src/networklayer/rsvp_te/RSVP.o: xMIPv6/src/networklayer/rsvp_te/RSVP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IScriptable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/mpls/ConstType.h \
	xMIPv6/src/networklayer/mpls/IClassifier.h \
	xMIPv6/src/networklayer/mpls/LIBTable.h \
	xMIPv6/src/networklayer/mpls/LIBTableAccess.h \
	xMIPv6/src/networklayer/rsvp_te/IRSVPClassifier.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVP.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPHelloMsg.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.h \
	xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.h \
	xMIPv6/src/networklayer/rsvp_te/Utils.h \
	xMIPv6/src/networklayer/ted/TED.h \
	xMIPv6/src/networklayer/ted/TEDAccess.h \
	xMIPv6/src/networklayer/ted/TED_m.h \
	xMIPv6/src/util/XMLUtils.h \
	xMIPv6/src/util/common.h
$O/xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.o: xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.h
$O/xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.o: xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.h
$O/xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.o: xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.h
$O/xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.o: xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.h
$O/xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.o: xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.h
$O/xMIPv6/src/networklayer/rsvp_te/SimpleClassifier.o: xMIPv6/src/networklayer/rsvp_te/SimpleClassifier.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/IScriptable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/mpls/ConstType.h \
	xMIPv6/src/networklayer/mpls/IClassifier.h \
	xMIPv6/src/networklayer/mpls/LIBTable.h \
	xMIPv6/src/networklayer/mpls/LIBTableAccess.h \
	xMIPv6/src/networklayer/rsvp_te/IRSVPClassifier.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVP.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPAccess.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPHelloMsg.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg.h \
	xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.h \
	xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.h \
	xMIPv6/src/networklayer/rsvp_te/SimpleClassifier.h \
	xMIPv6/src/util/XMLUtils.h
$O/xMIPv6/src/networklayer/rsvp_te/Utils.o: xMIPv6/src/networklayer/rsvp_te/Utils.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/rsvp_te/Utils.h
$O/xMIPv6/src/networklayer/ted/LinkStatePacket_m.o: xMIPv6/src/networklayer/ted/LinkStatePacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ted/LinkStatePacket_m.h \
	xMIPv6/src/networklayer/ted/TED_m.h
$O/xMIPv6/src/networklayer/ted/LinkStateRouting.o: xMIPv6/src/networklayer/ted/LinkStateRouting.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/ted/LinkStatePacket_m.h \
	xMIPv6/src/networklayer/ted/LinkStateRouting.h \
	xMIPv6/src/networklayer/ted/TED.h \
	xMIPv6/src/networklayer/ted/TEDAccess.h \
	xMIPv6/src/networklayer/ted/TED_m.h
$O/xMIPv6/src/networklayer/ted/TED.o: xMIPv6/src/networklayer/ted/TED.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/networklayer/ted/TED.h \
	xMIPv6/src/networklayer/ted/TED_m.h
$O/xMIPv6/src/networklayer/ted/TED_m.o: xMIPv6/src/networklayer/ted/TED_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/ted/TED_m.h
$O/xMIPv6/src/networklayer/xmipv6/BindingCache.o: xMIPv6/src/networklayer/xmipv6/BindingCache.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/util/opp_utils.h
$O/xMIPv6/src/networklayer/xmipv6/BindingUpdateList.o: xMIPv6/src/networklayer/xmipv6/BindingUpdateList.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/util/opp_utils.h
$O/xMIPv6/src/networklayer/xmipv6/MobilityHeader.o: xMIPv6/src/networklayer/xmipv6/MobilityHeader.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.o: xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h
$O/xMIPv6/src/networklayer/xmipv6/xMIPv6.o: xMIPv6/src/networklayer/xmipv6/xMIPv6.cc \
	util/Portable.h \
	util/fsm.h \
	util/hoinfo.h \
	util/ssinfo.h \
	wimax/wmaxctrl.h \
	wimax/wmaxctrlaccess.h \
	wimax/wmaxmsg.h \
	wimax/wmaxmsg_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/IPv6Tunneling.h \
	xMIPv6/src/networklayer/ipv6/IPv6TunnelingAccess.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/BindingCache.h \
	xMIPv6/src/networklayer/xmipv6/BindingCacheAccess.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateList.h \
	xMIPv6/src/networklayer/xmipv6/BindingUpdateListAccess.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/networklayer/xmipv6/xMIPv6.h
$O/xMIPv6/src/transport/contract/SCTPCommand_m.o: xMIPv6/src/transport/contract/SCTPCommand_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/contract/SCTPSocket.o: xMIPv6/src/transport/contract/SCTPSocket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/contract/SCTPSocket.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/contract/TCPCommand_m.o: xMIPv6/src/transport/contract/TCPCommand_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h
$O/xMIPv6/src/transport/contract/TCPSocket.o: xMIPv6/src/transport/contract/TCPSocket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h
$O/xMIPv6/src/transport/contract/TCPSocketMap.o: xMIPv6/src/transport/contract/TCPSocketMap.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/contract/TCPSocket.h \
	xMIPv6/src/transport/contract/TCPSocketMap.h
$O/xMIPv6/src/transport/contract/UDPControlInfo_m.o: xMIPv6/src/transport/contract/UDPControlInfo_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h
$O/xMIPv6/src/transport/contract/UDPSocket.o: xMIPv6/src/transport/contract/UDPSocket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/contract/UDPSocket.h
$O/xMIPv6/src/transport/rtp/RTCP.o: xMIPv6/src/transport/rtp/RTCP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/contract/UDPSocket.h \
	xMIPv6/src/transport/rtp/RTCP.h \
	xMIPv6/src/transport/rtp/RTCPPacket.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPParticipantInfo.h \
	xMIPv6/src/transport/rtp/RTPReceiverInfo.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderInfo.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h \
	xMIPv6/src/transport/rtp/reports.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/RTCPPacket.o: xMIPv6/src/transport/rtp/RTCPPacket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTCPPacket.h \
	xMIPv6/src/transport/rtp/reports.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/RTP.o: xMIPv6/src/transport/rtp/RTP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/contract/UDPSocket.h \
	xMIPv6/src/transport/rtp/RTP.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPInterfacePacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPProfile.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/transport/rtp/RTPInnerPacket.o: xMIPv6/src/transport/rtp/RTPInnerPacket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/transport/rtp/RTPInterfacePacket.o: xMIPv6/src/transport/rtp/RTPInterfacePacket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInterfacePacket.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/transport/rtp/RTPPacket.o: xMIPv6/src/transport/rtp/RTPPacket.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/rtp/RTPPacket.h
$O/xMIPv6/src/transport/rtp/RTPParticipantInfo.o: xMIPv6/src/transport/rtp/RTPParticipantInfo.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTCPPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPParticipantInfo.h \
	xMIPv6/src/transport/rtp/reports.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/RTPPayloadReceiver.o: xMIPv6/src/transport/rtp/RTPPayloadReceiver.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPPayloadReceiver.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/transport/rtp/RTPPayloadSender.o: xMIPv6/src/transport/rtp/RTPPayloadSender.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPPayloadSender.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/transport/rtp/RTPProfile.o: xMIPv6/src/transport/rtp/RTPProfile.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTCPPacket.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPParticipantInfo.h \
	xMIPv6/src/transport/rtp/RTPPayloadReceiver.h \
	xMIPv6/src/transport/rtp/RTPPayloadSender.h \
	xMIPv6/src/transport/rtp/RTPProfile.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h \
	xMIPv6/src/transport/rtp/reports.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/RTPReceiverInfo.o: xMIPv6/src/transport/rtp/RTPReceiverInfo.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTCPPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPParticipantInfo.h \
	xMIPv6/src/transport/rtp/RTPReceiverInfo.h \
	xMIPv6/src/transport/rtp/reports.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.o: xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h
$O/xMIPv6/src/transport/rtp/RTPSenderInfo.o: xMIPv6/src/transport/rtp/RTPSenderInfo.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTCPPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPParticipantInfo.h \
	xMIPv6/src/transport/rtp/RTPSenderInfo.h \
	xMIPv6/src/transport/rtp/reports.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.o: xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h
$O/xMIPv6/src/transport/rtp/reports.o: xMIPv6/src/transport/rtp/reports.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/reports.h
$O/xMIPv6/src/transport/rtp/sdes.o: xMIPv6/src/transport/rtp/sdes.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/rtp/sdes.h
$O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfile.o: xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfile.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPProfile.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h \
	xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfile.h
$O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.o: xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPPayloadReceiver.h \
	xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.h \
	xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.h
$O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.o: xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/transport/rtp/RTPInnerPacket.h \
	xMIPv6/src/transport/rtp/RTPPacket.h \
	xMIPv6/src/transport/rtp/RTPPayloadSender.h \
	xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.h \
	xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.h \
	xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.h \
	xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.h
$O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.o: xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.h
$O/xMIPv6/src/transport/sctp/SCTP.o: xMIPv6/src/transport/sctp/SCTP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPAlg.o: xMIPv6/src/transport/sctp/SCTPAlg.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAlg.h \
	xMIPv6/src/transport/sctp/SCTPAlgorithm.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPAssociationBase.o: xMIPv6/src/transport/sctp/SCTPAssociationBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAlgorithm.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPAssociationEventProc.o: xMIPv6/src/transport/sctp/SCTPAssociationEventProc.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAlgorithm.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPAssociationRcvMessage.o: xMIPv6/src/transport/sctp/SCTPAssociationRcvMessage.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAlgorithm.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPAssociationUtil.o: xMIPv6/src/transport/sctp/SCTPAssociationUtil.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.h \
	xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/transport/contract/SCTPCommand.h \
	xMIPv6/src/transport/contract/SCTPCommand_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAlgorithm.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPCCFunctions.o: xMIPv6/src/transport/sctp/SCTPCCFunctions.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPMessage.o: xMIPv6/src/transport/sctp/SCTPMessage.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPMessage_m.o: xMIPv6/src/transport/sctp/SCTPMessage_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h
$O/xMIPv6/src/transport/sctp/SCTPQueue.o: xMIPv6/src/transport/sctp/SCTPQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPReceiveStream.o: xMIPv6/src/transport/sctp/SCTPReceiveStream.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPSSFunctions.o: xMIPv6/src/transport/sctp/SCTPSSFunctions.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/sctp/SCTPSendStream.o: xMIPv6/src/transport/sctp/SCTPSendStream.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h
$O/xMIPv6/src/transport/tcp/TCP.o: xMIPv6/src/transport/tcp/TCP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h
$O/xMIPv6/src/transport/tcp/TCPConnectionBase.o: xMIPv6/src/transport/tcp/TCPConnectionBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPReceiveQueue.h \
	xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/TCPSendQueue.h
$O/xMIPv6/src/transport/tcp/TCPConnectionEventProc.o: xMIPv6/src/transport/tcp/TCPConnectionEventProc.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPReceiveQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/TCPSendQueue.h
$O/xMIPv6/src/transport/tcp/TCPConnectionRcvSegment.o: xMIPv6/src/transport/tcp/TCPConnectionRcvSegment.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPReceiveQueue.h \
	xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/TCPSendQueue.h
$O/xMIPv6/src/transport/tcp/TCPConnectionUtil.o: xMIPv6/src/transport/tcp/TCPConnectionUtil.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPReceiveQueue.h \
	xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/TCPSendQueue.h
$O/xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.o: xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h
$O/xMIPv6/src/transport/tcp/TCPSegment.o: xMIPv6/src/transport/tcp/TCPSegment.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h
$O/xMIPv6/src/transport/tcp/TCPSegment_m.o: xMIPv6/src/transport/tcp/TCPSegment_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h
$O/xMIPv6/src/transport/tcp/flavours/DumbTCP.o: xMIPv6/src/transport/tcp/flavours/DumbTCP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/DumbTCP.h
$O/xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.o: xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.h
$O/xMIPv6/src/transport/tcp/flavours/TCPNewReno.o: xMIPv6/src/transport/tcp/flavours/TCPNewReno.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.h \
	xMIPv6/src/transport/tcp/flavours/TCPNewReno.h \
	xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.h
$O/xMIPv6/src/transport/tcp/flavours/TCPNoCongestionControl.o: xMIPv6/src/transport/tcp/flavours/TCPNoCongestionControl.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.h \
	xMIPv6/src/transport/tcp/flavours/TCPNoCongestionControl.h
$O/xMIPv6/src/transport/tcp/flavours/TCPReno.o: xMIPv6/src/transport/tcp/flavours/TCPReno.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.h \
	xMIPv6/src/transport/tcp/flavours/TCPReno.h \
	xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.h
$O/xMIPv6/src/transport/tcp/flavours/TCPTahoe.o: xMIPv6/src/transport/tcp/flavours/TCPTahoe.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.h \
	xMIPv6/src/transport/tcp/flavours/TCPTahoe.h \
	xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.h
$O/xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.o: xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPAlgorithm.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.h \
	xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.h
$O/xMIPv6/src/transport/tcp/queues/TCPMsgBasedRcvQueue.o: xMIPv6/src/transport/tcp/queues/TCPMsgBasedRcvQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPReceiveQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/queues/TCPMsgBasedRcvQueue.h \
	xMIPv6/src/transport/tcp/queues/TCPVirtualDataRcvQueue.h
$O/xMIPv6/src/transport/tcp/queues/TCPMsgBasedSendQueue.o: xMIPv6/src/transport/tcp/queues/TCPMsgBasedSendQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/TCPSendQueue.h \
	xMIPv6/src/transport/tcp/queues/TCPMsgBasedSendQueue.h
$O/xMIPv6/src/transport/tcp/queues/TCPVirtualDataRcvQueue.o: xMIPv6/src/transport/tcp/queues/TCPVirtualDataRcvQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPReceiveQueue.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/queues/TCPVirtualDataRcvQueue.h
$O/xMIPv6/src/transport/tcp/queues/TCPVirtualDataSendQueue.o: xMIPv6/src/transport/tcp/queues/TCPVirtualDataSendQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCP.h \
	xMIPv6/src/transport/tcp/TCPConnection.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp/TCPSendQueue.h \
	xMIPv6/src/transport/tcp/queues/TCPVirtualDataSendQueue.h
$O/xMIPv6/src/transport/tcp_nsc/TCP_NSC.o: xMIPv6/src/transport/tcp_nsc/TCP_NSC.cc
$O/xMIPv6/src/transport/tcp_nsc/TCP_NSC_Connection.o: xMIPv6/src/transport/tcp_nsc/TCP_NSC_Connection.cc
$O/xMIPv6/src/transport/tcp_nsc/queues/TCP_NSC_VirtualDataQueues.o: xMIPv6/src/transport/tcp_nsc/queues/TCP_NSC_VirtualDataQueues.cc
$O/xMIPv6/src/transport/tcp_old/TCP.o: xMIPv6/src/transport/tcp_old/TCP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h
$O/xMIPv6/src/transport/tcp_old/TCPConnectionBase.o: xMIPv6/src/transport/tcp_old/TCPConnectionBase.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPReceiveQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCPSendQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h
$O/xMIPv6/src/transport/tcp_old/TCPConnectionEventProc.o: xMIPv6/src/transport/tcp_old/TCPConnectionEventProc.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPReceiveQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCPSendQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h
$O/xMIPv6/src/transport/tcp_old/TCPConnectionRcvSegment.o: xMIPv6/src/transport/tcp_old/TCPConnectionRcvSegment.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPReceiveQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCPSendQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h
$O/xMIPv6/src/transport/tcp_old/TCPConnectionUtil.o: xMIPv6/src/transport/tcp_old/TCPConnectionUtil.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/transport/contract/TCPCommand_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPReceiveQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCPSendQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h
$O/xMIPv6/src/transport/tcp_old/flavours/DumbTCP.o: xMIPv6/src/transport/tcp_old/flavours/DumbTCP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/flavours/DumbTCP_old.h
$O/xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg.o: xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg_old.h
$O/xMIPv6/src/transport/tcp_old/flavours/TCPNoCongestionControl.o: xMIPv6/src/transport/tcp_old/flavours/TCPNoCongestionControl.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPNoCongestionControl_old.h
$O/xMIPv6/src/transport/tcp_old/flavours/TCPReno.o: xMIPv6/src/transport/tcp_old/flavours/TCPReno.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPReno_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily_old.h
$O/xMIPv6/src/transport/tcp_old/flavours/TCPTahoe.o: xMIPv6/src/transport/tcp_old/flavours/TCPTahoe.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPTahoe_old.h
$O/xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily.o: xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPAlgorithm_old.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg_old.h \
	xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily_old.h
$O/xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedRcvQueue.o: xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedRcvQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPReceiveQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedRcvQueue_old.h \
	xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataRcvQueue_old.h
$O/xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedSendQueue.o: xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedSendQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPSendQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedSendQueue_old.h
$O/xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataRcvQueue.o: xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataRcvQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPReceiveQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataRcvQueue_old.h
$O/xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataSendQueue.o: xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataSendQueue.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/tcp_old/TCPConnection_old.h \
	xMIPv6/src/transport/tcp_old/TCPSendQueue_old.h \
	xMIPv6/src/transport/tcp_old/TCP_old.h \
	xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataSendQueue_old.h
$O/xMIPv6/src/transport/udp/UDP.o: xMIPv6/src/transport/udp/UDP.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo.h \
	xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Access.h \
	xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.h \
	xMIPv6/src/networklayer/ipv4/ICMP.h \
	xMIPv6/src/networklayer/ipv4/ICMPAccess.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.h \
	xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6.h \
	xMIPv6/src/networklayer/ipv6/RoutingTable6Access.h \
	xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.h \
	xMIPv6/src/transport/contract/UDPControlInfo_m.h \
	xMIPv6/src/transport/udp/UDP.h \
	xMIPv6/src/transport/udp/UDPPacket.h \
	xMIPv6/src/transport/udp/UDPPacket_m.h
$O/xMIPv6/src/transport/udp/UDPPacket_m.o: xMIPv6/src/transport/udp/UDPPacket_m.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/transport/udp/UDPPacket_m.h
$O/xMIPv6/src/util/NAMTraceWriter.o: xMIPv6/src/util/NAMTraceWriter.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/linklayer/contract/TxNotifDetails.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/util/NAMTraceWriter.h \
	xMIPv6/src/world/NAMTrace.h
$O/xMIPv6/src/util/TCPDump.o: xMIPv6/src/util/TCPDump.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/udp/UDPPacket_m.h \
	xMIPv6/src/util/TCPDump.h \
	xMIPv6/src/util/headerserializers/IPSerializer.h
$O/xMIPv6/src/util/ThruputMeteringChannel.o: xMIPv6/src/util/ThruputMeteringChannel.cc
$O/xMIPv6/src/util/XMLUtils.o: xMIPv6/src/util/XMLUtils.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPAddressResolver.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/util/XMLUtils.h
$O/xMIPv6/src/util/common.o: xMIPv6/src/util/common.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ.h \
	xMIPv6/src/networklayer/rsvp_te/IntServ_m.h \
	xMIPv6/src/util/common.h
$O/xMIPv6/src/util/opp_utils.o: xMIPv6/src/util/opp_utils.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/util/opp_utils.h
$O/xMIPv6/src/util/headerserializers/ICMPSerializer.o: xMIPv6/src/util/headerserializers/ICMPSerializer.cc \
	xMIPv6/src/applications/pingapp/PingPayload_m.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/util/headerserializers/ICMPSerializer.h \
	xMIPv6/src/util/headerserializers/IPSerializer.h \
	xMIPv6/src/util/headerserializers/TCPIPchecksum.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h \
	xMIPv6/src/util/headerserializers/headers/defs.h \
	xMIPv6/src/util/headerserializers/headers/in.h \
	xMIPv6/src/util/headerserializers/headers/in_systm.h \
	xMIPv6/src/util/headerserializers/headers/ip.h \
	xMIPv6/src/util/headerserializers/headers/ip_icmp.h \
	xMIPv6/src/util/headerserializers/headers/tcp.h
$O/xMIPv6/src/util/headerserializers/IPSerializer.o: xMIPv6/src/util/headerserializers/IPSerializer.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/ICMPMessage_m.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram.h \
	xMIPv6/src/networklayer/ipv4/IPDatagram_m.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/udp/UDPPacket.h \
	xMIPv6/src/transport/udp/UDPPacket_m.h \
	xMIPv6/src/util/headerserializers/ICMPSerializer.h \
	xMIPv6/src/util/headerserializers/IPSerializer.h \
	xMIPv6/src/util/headerserializers/SCTPSerializer.h \
	xMIPv6/src/util/headerserializers/TCPSerializer.h \
	xMIPv6/src/util/headerserializers/UDPSerializer.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h \
	xMIPv6/src/util/headerserializers/headers/defs.h \
	xMIPv6/src/util/headerserializers/headers/in.h \
	xMIPv6/src/util/headerserializers/headers/in_systm.h \
	xMIPv6/src/util/headerserializers/headers/ip.h \
	xMIPv6/src/util/headerserializers/headers/tcp.h
$O/xMIPv6/src/util/headerserializers/SCTPSerializer.o: xMIPv6/src/util/headerserializers/SCTPSerializer.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/contract/MACAddress.h \
	xMIPv6/src/networklayer/common/IInterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceEntry.h \
	xMIPv6/src/networklayer/common/InterfaceTable.h \
	xMIPv6/src/networklayer/common/InterfaceTableAccess.h \
	xMIPv6/src/networklayer/common/InterfaceToken.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPControlInfo.h \
	xMIPv6/src/networklayer/contract/IPControlInfo_m.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/networklayer/ipv4/IPRoute.h \
	xMIPv6/src/networklayer/ipv4/IRoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTable.h \
	xMIPv6/src/networklayer/ipv4/RoutingTableAccess.h \
	xMIPv6/src/transport/sctp/SCTP.h \
	xMIPv6/src/transport/sctp/SCTPAssociation.h \
	xMIPv6/src/transport/sctp/SCTPMessage.h \
	xMIPv6/src/transport/sctp/SCTPMessage_m.h \
	xMIPv6/src/transport/sctp/SCTPQueue.h \
	xMIPv6/src/transport/sctp/SCTPReceiveStream.h \
	xMIPv6/src/transport/sctp/SCTPSendStream.h \
	xMIPv6/src/util/headerserializers/SCTPSerializer.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h \
	xMIPv6/src/util/headerserializers/headers/defs.h \
	xMIPv6/src/util/headerserializers/headers/in.h \
	xMIPv6/src/util/headerserializers/headers/in_systm.h \
	xMIPv6/src/util/headerserializers/headers/ip.h \
	xMIPv6/src/util/headerserializers/headers/sctp.h
$O/xMIPv6/src/util/headerserializers/TCPIPchecksum.o: xMIPv6/src/util/headerserializers/TCPIPchecksum.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/util/headerserializers/TCPIPchecksum.h \
	xMIPv6/src/util/headerserializers/headers/defs.h \
	xMIPv6/src/util/headerserializers/headers/tcp.h
$O/xMIPv6/src/util/headerserializers/TCPSerializer.o: xMIPv6/src/util/headerserializers/TCPSerializer.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPProtocolId_m.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/util/headerserializers/TCPIPchecksum.h \
	xMIPv6/src/util/headerserializers/TCPSerializer.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h \
	xMIPv6/src/util/headerserializers/headers/defs.h \
	xMIPv6/src/util/headerserializers/headers/in.h \
	xMIPv6/src/util/headerserializers/headers/in_systm.h \
	xMIPv6/src/util/headerserializers/headers/tcp.h
$O/xMIPv6/src/util/headerserializers/UDPSerializer.o: xMIPv6/src/util/headerserializers/UDPSerializer.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/networklayer/contract/IPAddress.h \
	xMIPv6/src/networklayer/contract/IPv6Address.h \
	xMIPv6/src/networklayer/contract/IPvXAddress.h \
	xMIPv6/src/transport/tcp/TCPSegment.h \
	xMIPv6/src/transport/tcp/TCPSegment_m.h \
	xMIPv6/src/transport/udp/UDPPacket.h \
	xMIPv6/src/transport/udp/UDPPacket_m.h \
	xMIPv6/src/util/headerserializers/TCPIPchecksum.h \
	xMIPv6/src/util/headerserializers/UDPSerializer.h \
	xMIPv6/src/util/headerserializers/headers/bsdint.h \
	xMIPv6/src/util/headerserializers/headers/defs.h \
	xMIPv6/src/util/headerserializers/headers/in.h \
	xMIPv6/src/util/headerserializers/headers/in_systm.h \
	xMIPv6/src/util/headerserializers/headers/tcp.h \
	xMIPv6/src/util/headerserializers/headers/udp.h
$O/xMIPv6/src/world/ChannelAccess.o: xMIPv6/src/world/ChannelAccess.cc \
	xMIPv6/src/base/BasicModule.h \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/INotifiable.h \
	xMIPv6/src/base/ModuleAccess.h \
	xMIPv6/src/base/NotificationBoard.h \
	xMIPv6/src/base/NotifierConsts.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelAccess.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/world/ChannelControl.o: xMIPv6/src/world/ChannelControl.cc \
	xMIPv6/src/base/Coord.h \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/linklayer/mfcore/AirFrame_m.h \
	xMIPv6/src/util/FWMath.h \
	xMIPv6/src/world/ChannelControl.h
$O/xMIPv6/src/world/ChannelInstaller.o: xMIPv6/src/world/ChannelInstaller.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/world/ChannelInstaller.h
$O/xMIPv6/src/world/NAMTrace.o: xMIPv6/src/world/NAMTrace.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/world/NAMTrace.h
$O/xMIPv6/src/world/ScenarioManager.o: xMIPv6/src/world/ScenarioManager.cc \
	xMIPv6/src/base/INETDefs.h \
	xMIPv6/src/base/IScriptable.h \
	xMIPv6/src/world/ScenarioManager.h

