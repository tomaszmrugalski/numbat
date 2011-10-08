// Copyright (C) 2007 Faqir Zarrar Yousaf
// Communication Networks Institute, University of Dortmund
// faqir.yousaf@uni-dortmund.de
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


package inet.nodes.xmipv6;

import inet.applications.pingapp.PingApp;
import inet.applications.tcpapp.TCPApp;
import inet.applications.udpapp.UDPApp;
import inet.base.NotificationBoard;
import inet.linklayer.ieee80211.Ieee80211NicSTA;
import inet.mobility.BasicMobility;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv6.RoutingTable6;
import inet.networklayer.xmipv6.BindingUpdateList;
import inet.transport.tcp.TCP;
import inet.transport.udp.UDP;


//
//It is an IPv6 compatible node with MIPv6 support.
// Models a host with one wireless (802.11b) card in infrastructure mode, supports handovers and MIPv6 protocol.
// This module is basically a StandardHost with an Ieee80211NicSTA and MobileIPLayer6
// added. It should be used in conjunction with WirelessAPSimplified,
// or any other AP model which contains Ieee80211NicAPSimplified.
//
// @see WirelessAP, WirelessAPSimplified, WirelessAPWithEth, WirelessAPWithEthSimplified
// @see WirelessHost, WirelessHostSimplified
// @see MobileHost, MFMobileHost
//
module WirelessHost6
{
    parameters:
        @node();
        double numTcpApps;
        double numUdpApps;
        string tcpAppType;
        string udpAppType;
        //IPForward: bool,
        string routingFile;
        string mobilityType;
        @display("i=device/wifilaptop");
    gates:
           //in: in[];
           //out: out[];
           //in: ethIn[];
           //out: ethOut[];
        input radioIn;
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,70;i=block/control");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=60,150;i=block/table");
        }
        buList: BindingUpdateList {
            parameters:
                @display("p=63,292;i=old/harddisk");
        }
        routingTable6: RoutingTable6 {
            parameters:
                isRouter = false;
                @display("p=60,230;i=block/table2");
        }
        tcpApp[numTcpApps]: <tcpAppType> like TCPApp {
            parameters:
                @display("p=195,75;i=block/app");
        }
        tcp: TCP {
            parameters:
                @display("p=195,170;i=block/wheelbarrow");
        }
        udpApp[numUdpApps]: <udpAppType> like UDPApp {
            parameters:
                @display("i=block/app;p=312,75");
        }
        udp: UDP {
            parameters:
                @display("p=312,170;i=block/transport");
        }
        pingApp: PingApp {
            parameters:
                @display("i=block/app;p=343,248");
        }
        networkLayer: MobileIPLayer6 {
            parameters:
                isMN = true; //is Mobile Node
                isHA = false; //is Home Agent
                @display("p=248,247;i=block/fork;q=queue");
            gates:
                ifIn[(sizeof(out)+sizeof(ethOut))+1];
                ifOut[(sizeof(out)+sizeof(ethOut))+1];
        }
        wlan: Ieee80211NicSTA {
            parameters:
                @display("p=248,358;q=queue;i=block/ifcard");
        }
        mobility: <mobilityType> like BasicMobility {
            parameters:
                @display("p=66,357;i=block/cogwheel_s");
        }
    connections allowunconnected:
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.appIn++;
            tcpApp[i].tcpIn <-- tcp.appOut++;
        }

        tcp.ipOut --> networkLayer.tcpIn;
        tcp.ipIn <-- networkLayer.TCPOut;

        for i=0..numUdpApps-1 {
            udpApp[i].udpOut --> udp.appIn++;
            udpApp[i].udpIn <-- udp.appOut++;
        }

        udp.ipv6Out --> networkLayer.udpIn;
        udp.ipv6In <-- networkLayer.udpOut;

        networkLayer.pingOut --> pingApp.pingv6In;
        networkLayer.pingIn <-- pingApp.pingv6Out;

                                                   // connections to network outside
                                                   //for i=0..sizeof(out)-1 do
                                                   //  in[i] --> ppp[i].physIn;
                                                   //  out[i] <-- ppp[i].physOut;
                                                   //  ppp[i].netwOut --> networkLayer.ifIn[i];
                                                   //  ppp[i].netwIn <-- networkLayer.ifOut[i];
                                                   // endfor;

                                                   //      for i=0..sizeof(ethOut)-1 do
                                                   //          ethIn[i] --> eth[i].physIn;
                                                   //          ethOut[i] <-- eth[i].physOut;
                                                   //          eth[i].netwOut --> networkLayer.ifIn[sizeof(out)+i];
                                                   //          eth[i].netwIn <-- networkLayer.ifOut[sizeof(out)+i];
                                                   //      endfor;

        radioIn --> wlan.radioIn;
        wlan.uppergateOut --> networkLayer.ifIn[sizeof(out)+sizeof(ethOut)];
        wlan.uppergateIn <-- networkLayer.ifOut[sizeof(out)+sizeof(ethOut)];
}

