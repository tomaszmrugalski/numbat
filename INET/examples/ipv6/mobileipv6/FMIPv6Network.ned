// Copyright (C) 2007 Faqir Zarrar Yousaf
// Communication Networks Institute
// University of Dortmund, Germany
// faqir.yousaf@uni-dortmund.de
//
// Copyright (C) 2004 Andras Varga
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


package inet.examples.ipv6.mobileipv6;

import inet.linklayer.ethernet.EtherHub;
import inet.networklayer.autorouting.FlatNetworkConfigurator6;
import inet.nodes.wireless.WirelessAPWithEth;
import inet.nodes.xmipv6.CorrespondentNode6;
import inet.nodes.xmipv6.HomeAgent6;
import inet.nodes.xmipv6.WirelessHost6;
import inet.world.ChannelControl;


//channel fiberline extends ned.DatarateChannel
//{
//    parameters:
//        delay = 1us;
//        datarate = 512*1000000;
//}
//
//channel ethernetline extends ned.DatarateChannel
//{
//    parameters:
//        delay = 0.1us;
//}

module FMIPv6Network
{
    parameters:
        double total_mn;
        double total_cn;
        double playgroundSizeX;
        double playgroundSizeY;

        @display("bgb=799,698");
    submodules:
        configurator: FlatNetworkConfigurator6 {
            parameters:
                @display("p=667,645");
        }
        channelcontrol: ChannelControl {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                numChannels = 5;
                @display("p=753,651");
        }
        Home_Agent: HomeAgent6 {
            parameters:
                @display("p=209,181;i=abstract/router");
        }
        R_1: AccessRouter6 {
            parameters:
                @display("p=526,179;i=abstract/router");
        }
        MN[total_mn]: WirelessHost6 {
            parameters:
                @display("p=86,356");
        }
        CN[total_cn]: CorrespondentNode6 {
            parameters:
                @display("i=device/pc2");
        }
        AP_Home: WirelessAPWithEth {
            parameters:
                @display("p=163,124;i=device/accesspoint_s");
        }
        AP_1: WirelessAPWithEth {
            parameters:
                @display("p=571,124;i=device/accesspoint_s");
        }
        hub: EtherHub {
            parameters:
                @display("p=606,180;i=device/hub_s");
        }
    connections allowunconnected:

        Home_Agent.ethOut++ --> ethernetline --> R_1.ethIn++;
        Home_Agent.ethIn++ <-- ethernetline <-- R_1.ethOut++;

        for i=0..total_cn-1 {
            CN[i].ethOut++ --> ethernetline --> hub.ethg$i++;
            CN[i].ethIn++ <-- ethernetline <-- hub.ethg$o++;
        }

        hub.ethg$o++ --> ethernetline --> R_1.ethIn++;
        hub.ethg$i++ <-- ethernetline <-- R_1.ethOut++;

        AP_Home.ethg$o++ --> ethernetline --> Home_Agent.ethIn++;
        AP_Home.ethg$i++ <-- ethernetline <-- Home_Agent.ethOut++;

        AP_1.eth$o++ --> ethernetline --> R_1.ethIn++;
        AP_1.eth$i++ <-- ethernetline <-- R_1.ethOut++;


}

network fMIPv6Network extends FMIPv6Network
{
    parameters:
}

