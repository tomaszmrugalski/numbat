//
// Copyright (C) 2005 Wei Yang, Ng
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

package inet.examples.ipv6.demonetwork_2;

import inet.networklayer.autorouting.FlatNetworkConfigurator6;
import inet.nodes.ipv6.Router6;
import inet.nodes.xmipv6.MobileHost6;


channel ethernetline extends ned.DatarateChannel
{
    parameters:
        delay = 0.1us;
}

module DemoNetworkEth
{
    parameters:
        double n;
    submodules:
        configurator: FlatNetworkConfigurator6 {
        }
        r1: MobileRouter {
            parameters:
                @display("i=abstract/router");
        }
        r2: MobileRouter {
            parameters:
                @display("i=abstract/router");
        }
        r3: MobileRouter {
            parameters:
                @display("i=abstract/router");
        }
        r4: MobileRouter {
            parameters:
                @display("i=abstract/router");
        }
        mr1: Router6 {
            parameters:
                @display("i=abstract/router");
        }
        //mr2: Router6;
        //    display: "i=abstract/router";
        mr3: Router6 {
            parameters:
                @display("i=abstract/router");
        }
        //mr4: Router6;
        //    display: "i=abstract/router";
        host[4]: MobileHost6 {
            parameters:
                @display("i=device/laptop");

        }
    connections allowunconnected:
        host[0].ethOut++ --> ethernetline --> mr1.ethIn++;
        host[0].ethIn++ <-- ethernetline <-- mr1.ethOut++;
        host[1].ethOut++ --> ethernetline --> r2.ethIn++;
        host[1].ethIn++ <-- ethernetline <-- r2.ethOut++;
        host[2].ethOut++ --> ethernetline --> mr3.ethIn++;
        host[2].ethIn++ <-- ethernetline <-- mr3.ethOut++;
        host[3].ethOut++ --> ethernetline --> r4.ethIn++;
        host[3].ethIn++ <-- ethernetline <-- r4.ethOut++;

        mr1.ethOut++ --> ethernetline --> r1.ethIn++;
        mr1.ethIn++ <-- ethernetline <-- r1.ethOut++;
        //mr2.ethOut++ --> ethernetline --> r2.ethIn++;
        //mr2.ethIn++ <-- ethernetline <-- r2.ethOut++;
        mr3.ethOut++ --> ethernetline --> r3.ethIn++;
        mr3.ethIn++ <-- ethernetline <-- r3.ethOut++;
		//mr4.ethOut++ --> ethernetline --> r4.ethIn++;
		//mr4.ethIn++ <-- ethernetline <-- r4.ethOut++;

        r1.ethOut++ --> ethernetline --> r2.ethIn++;
        r1.ethIn++ <-- ethernetline <-- r2.ethOut++;

        r1.ethOut++ --> ethernetline --> r4.ethIn++;
        r1.ethIn++ <-- ethernetline <-- r4.ethOut++;
        r4.ethOut++ --> ethernetline --> r3.ethIn++;
        r4.ethIn++ <-- ethernetline <-- r3.ethOut++;

        r2.ethOut++ --> ethernetline --> r3.ethIn++;
        r2.ethIn++ <-- ethernetline <-- r3.ethOut++;

}

network demoNetworkEth extends DemoNetworkEth
{
    parameters:
}
