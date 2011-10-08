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

//
// IPv6 router Configured to operate as a Home Agent in a network supporting MIPv6.
//

package inet.nodes.xmipv6;

import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv6.RoutingTable6;
import inet.networklayer.xmipv6.BindingCache;


module HomeAgent6
{
    parameters:
        @node();
    gates:
           //in: in[];
           //out: out[];
        input ethIn[];
        output ethOut[];
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,60;i=block/control");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=150,60;i=block/table");
        }
        bindingCache: BindingCache {
            parameters:
                @display("p=55,124;i=old/harddisk");
        }
        routingTable6: RoutingTable6 {
            parameters:
                isRouter = true;
                @display("p=240,60;i=block/table2");
        }
        networkLayer: MobileIPLayer6 {
            parameters:
                isMN = false; //is Mobile Node
                isHA = true; //is Home Agent
                @display("p=200,141;i=block/fork;q=queue");
            gates:
                ifIn[sizeof(out)+sizeof(ethOut)];
                ifOut[sizeof(out)+sizeof(ethOut)];
        }
        eth[sizeof(ethOut)]: EthernetInterface {
            parameters:
                @display("p=145,257,row,110;q=l2queue;i=block/ifcard");
        }
    connections allowunconnected:
        for i=0..sizeof(ethOut)-1 {
            ethIn[i] --> eth[i].phys$i;
            ethOut[i] <-- eth[i].phys$o;
            eth[i].netwOut --> networkLayer.ifIn[sizeof(out)+i];
            eth[i].netwIn <-- networkLayer.ifOut[sizeof(out)+i];
        }
}

