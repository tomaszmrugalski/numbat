//
// Copyright (C) 2007 Faqir Zarrar Yousaf
// Communication Networks Institute,
// University of Dortmund, Germany
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



package inet.nodes.xmipv6;

import inet.networklayer.icmpv6.ICMPv6;
import inet.networklayer.icmpv6.IPv6NeighbourDiscovery;
import inet.networklayer.ipv6.IPv6;
import inet.networklayer.ipv6.IPv6ErrorHandling;
import inet.networklayer.ipv6.IPv6Tunneling;
import inet.networklayer.xmipv6.xMIPv6;


//SAME AS NetworkLayer6.ned EXCEPT THE INCLUSION OF xMIPv6.ned SIMPLE MODULE
// Represents an IPv6 network layer (L3) with L3 mobility support (MIPv6, HMIPv6, FMIPv6, NEMO etc).
//!!!!The mobility protocols are under development !!!!!
//
// The module has ports to connect to a higher layer (TCP,UDP) and
// several network interfaces.
//
module MobileIPLayer6
{
    parameters:
        bool isMN; //is Mobile Node
        bool isHA; //is Home Agent
    gates:
        input ifIn[];
        output ifOut[];
        input tcpIn;
        output TCPOut;
        input udpIn;
        output udpOut;
        input rsvpIn;
        output rsvpOut;
        input ospfIn;
        output ospfOut;
        input pingIn;
        output pingOut;
        output errorOut;
    submodules:
        ipv6: IPv6 {
            parameters:
                protocolMapping = "6:0,17:1,46:2,89:3";
                @display("i=block/network2;p=84,129");
            gates:
                transportIn[4];
                transportOut[4];
                queueIn[sizeof(ifIn)];
                queueOut[sizeof(ifIn)];
        }
        icmpv6: ICMPv6 {
            parameters:
                @display("i=block/control;p=208,71");
        }
        ipv6ErrorHandling: IPv6ErrorHandling {
            parameters:
                @display("p=304,79;i=block/process_s");
        }
        neighbourDiscovery: IPv6NeighbourDiscovery {
            parameters:
                @display("p=264,211;i=block/network");
        }
        iptunneling: IPv6Tunneling {
            parameters:
                @display("p=152,246;i=block/tunnel");
        }
        xMobileIPv6: xMIPv6 {
            parameters:
                isHomeAgent = isHA;
                isMobileNode = isMN;
                @display("p=312,131;i=block/classifier2");
        }
    connections allowunconnected: // FIXME remove 'nocheck'!
        // IPv6 to transport Layer
        ipv6.transportOut[0] --> { @display("m=n"); } --> TCPOut;
        ipv6.transportIn[0] <-- { @display("m=n"); } <-- tcpIn;

        ipv6.transportOut[1] --> { @display("m=n"); } --> udpOut;
        ipv6.transportIn[1] <-- { @display("m=n"); } <-- udpIn;

        ipv6.transportOut[2] --> { @display("m=n"); } --> rsvpOut;
        ipv6.transportIn[2] <-- { @display("m=n"); } <-- rsvpIn;

        ipv6.transportOut[3] --> { @display("m=n"); } --> ospfOut;
        ipv6.transportIn[3] <-- { @display("m=n"); } <-- ospfIn;

        // IPv6 to ICMPv6
        ipv6.icmpOut --> icmpv6.ipv6In;
        ipv6.icmpIn <-- icmpv6.ipv6Out;

        // ICMPv6 to IPv6ErrorHandling
        icmpv6.errorOut --> ipv6ErrorHandling.in;

        // ICMPv6 to ping I/O
        icmpv6.pingOut --> pingOut;
        icmpv6.pingIn <-- pingIn;

        // IPv6 to Neighbour Discovery
        ipv6.ndOut --> neighbourDiscovery.ipv6In;
        ipv6.ndIn <-- neighbourDiscovery.ipv6Out;

        // IPv6 to IPv6 Tunneling
        iptunneling.upperLayerIn <-- ipv6.upperTunnelingOut;
        iptunneling.upperLayerOut --> ipv6.upperTunnelingIn;
        iptunneling.linkLayerIn <-- ipv6.lowerTunnelingOut;
        iptunneling.linkLayerOut --> ipv6.lowerTunnelingIn;

        //IPv6 to Mobile IPv6
        ipv6.xMIPv6Out --> xMobileIPv6.fromIPv6;
        ipv6.xMIPv6In <-- xMobileIPv6.toIPv6;

        // IPv6 to L2
        for i=0..sizeof(ifOut)-1 {
            ifIn[i] --> { @display("m=s"); } --> ipv6.queueIn[i];
            ifOut[i] <-- { @display("m=s"); } <-- ipv6.queueOut[i];
        }
}

