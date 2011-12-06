
//package numbat.wimax;

// import numbat.wimax.common;
//import numbat.ipv6.IPv6;
//import inet.networklayer.ipv6.IPv6;
import inet.nodes.xmipv6.MobileIPLayer6;
// import numbat.wimax.MAC;
//============= Adam 14-09-2011 =====================
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv6.RoutingTable6;
import inet.base.NotificationBoard;
import inet.networklayer.xmipv6.BindingCache;
import inet.linklayer.ethernet.EthernetInterface;
//============= Adam, end  14-09-2011==================s
//ssPhy
simple WMaxPhyBS
{
    gates:
        input rfIn;
        output rfOut;
        input phyIn;
        output phyOut;
}

//Simulates transmission between 1 BS and 0..n SSes.
simple WMaxRadio
{
    gates:
        input phyIn;
        output phyOut;
        output radioOut[];
        input radioIn[];
}

module BS
{
    parameters:
        @node();    // needed by FlatNetworkConfigurator6
        volatile double x;
        volatile double y;
        @display("bgb=360,360");
    gates:
        output out[];
        input in[];
//============= Adam 14-09-2011 =====================        
        input ethIn;
        output ethOut;
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,60");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=60,150");
        }
        routingTable6: RoutingTable6 {
            parameters:
                isRouter = true;
                @display("p=60,240");
        }
        bindingCache: BindingCache {
            parameters:
                @display("p=63,308;i=old/harddisk");
        }    
//============= Adam, end  14-09-2011==================s
        bsPhy: WMaxPhyBS {
            parameters:
                @display("i=abstract/accesspoint,#40e221;p=232,72;q=SendQueue");
        }
        bsMac: bsMAC {
            parameters:
                @display("i=block/control,#40e221;p=144,72;q=SendQueue");
        }
        radio: WMaxRadio {
            parameters:
                @display("p=312,72;i=device/receiverdish,#40e221,30");
            gates:
                radioIn[sizeof(in)];
                radioOut[sizeof(in)]; // use in, for consistency

        }
        bsIPv6: MobileIPLayer6 {
            parameters:
                @display("p=200,141;i=block/fork;q=queue");
            // gates:
                // ifIn[sizeof(ethIn)+1];
                // ifOut[sizeof(ethOut)+1];
        }
        eth_int: EthernetInterface {
            parameters:
                @display("p=145,257,row,110;q=l2queue;i=block/ifcard");
        }
        
    connections allowunconnected:

        // for i=0..sizeof(ethOut)-1 {
            ethIn --> eth_int.phys$i;
            ethOut <-- eth_int.phys$o;
            eth_int.netwOut --> bsIPv6.ifIn++;
            eth_int.netwIn <-- bsIPv6.ifOut++;
        // }

        radio.phyOut --> bsPhy.rfIn;
        bsPhy.rfOut --> radio.phyIn;

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        bsMac.ipOut --> bsIPv6.ifIn++;
        bsIPv6.ifOut++ --> bsMac.ipIn;

        // bsIPv6.ifOut++ --> networkOut;   // zmiana modulu, dodanie interface eth polaczonego z internet
        // networkIn --> bsIPv6.ifIn++;

}



