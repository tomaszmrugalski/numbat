//


package inet.nodes.xmipv6;

import inet.applications.pingapp.PingApp;
import inet.applications.tcpapp.TCPApp;
import inet.applications.udpapp.UDPApp;
import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ieee80211.Ieee80211NicSTA;
import inet.linklayer.ppp.PPPInterface;
import inet.mobility.BasicMobility;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv6.RoutingTable6;
import inet.transport.tcp.TCP;
import inet.transport.udp.UDP;


//
// \MIPv6 host with TCP, UDP layers and applications.
//
module MobileHost6
{
    parameters:
        @node();
        double numTcpApps;
        double numUdpApps;
        string tcpAppType;
        string udpAppType;
        string mobilityType;
    gates:
        input in[];
        output out[];
        input ethIn[];
        output ethOut[];
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
        routingTable6: RoutingTable6 {
            parameters:
                isRouter = false;
                @display("p=60,230;i=block/table");
        }
        tcpApp[numTcpApps]: <tcpAppType> like TCPApp {
            parameters:
                @display("p=163,67;i=block/app");
        }
        tcp: TCP {
            parameters:
                @display("p=163,154;i=block/wheelbarrow");
        }
        udpApp[numUdpApps]: <udpAppType> like UDPApp {
            parameters:
                @display("i=block/app;p=272,67");
        }
        udp: UDP {
            parameters:
                @display("p=272,154;i=block/transport");
        }
        pingApp: PingApp {
            parameters:
                @display("i=block/app;p=343,200");
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
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=205,350,row,90;q=txQueue;i=block/ifcard");
        }
        eth[sizeof(ethOut)]: EthernetInterface {
            parameters:
                @display("p=240,350,row,90;q=txQueue;i=block/ifcard");
        }
        wlan: Ieee80211NicSTA {
            parameters:
                @display("p=120,350;q=queue;i=block/ifcard");
        }
        mobility: <mobilityType> like BasicMobility {
            parameters:
                @display("p=58,301;i=block/cogwheel_s");

        }
    connections allowunconnected:
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.appIn++;
            tcpApp[i].tcpIn <-- tcp.appOut++;
        }

        tcp.ipv6Out --> networkLayer.tcpIn;
        tcp.ipv6In <-- networkLayer.TCPOut;

        for i=0..numUdpApps-1 {
            udpApp[i].udpOut --> udp.appIn++;
            udpApp[i].udpIn <-- udp.appOut++;
        }

        udp.ipv6Out --> networkLayer.udpIn;
        udp.ipv6In <-- networkLayer.udpOut;

        networkLayer.pingOut --> pingApp.pingv6In;
        networkLayer.pingIn <-- pingApp.pingv6Out;

        // connections to network outside
        for i=0..sizeof(out)-1 {
            in[i] --> ppp[i].phys$i;
            out[i] <-- ppp[i].phys$o;
            ppp[i].netwOut --> networkLayer.ifIn[i];
            ppp[i].netwIn <-- networkLayer.ifOut[i];
        }

        for i=0..sizeof(ethOut)-1 {
            ethIn[i] --> eth[i].phys$i;
            ethOut[i] <-- eth[i].phys$o;
            eth[i].netwOut --> networkLayer.ifIn[sizeof(out)+i];
            eth[i].netwIn <-- networkLayer.ifOut[sizeof(out)+i];
        }

        radioIn --> { @display("m=s"); } --> wlan.radioIn;
        wlan.uppergateIn <-- networkLayer.ifOut[sizeof(out)+sizeof(ethOut)];
        wlan.uppergateOut --> networkLayer.ifIn[sizeof(out)+sizeof(ethOut)];
}

