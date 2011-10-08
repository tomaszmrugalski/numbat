import common;
//import IPv6;
import MAC;
import inet.nodes.xmipv6.MobileIPLayer6;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.xmipv6.BindingUpdateList;
import inet.networklayer.ipv6.RoutingTable6;
import inet.base.NotificationBoard;
import inet.applications.pingapp.PingApp;

simple WMaxPhySS
{
    gates:
        output rfOut;
        input rfIn;
        input phyIn;
        output phyOut;
}

simple ssInfo
{
}

simple WMaxFlowSS
{
//this is created by MiM
}

module SS //
          //some doubles should be integers or booleans... fixed (MiM)
{
    parameters:
        @node();    
        volatile int wmaxHoOptim;
        volatile int wmaxIsMobile;
        volatile int movementType;
        volatile double x;
        volatile double y;
        volatile int initialBS;
        volatile double NetworkEntryTime;
        volatile double HandoverTime;
        volatile int dadType;
        volatile bool dhcpSkipInitialDelay;
        volatile bool dhcpPref255;
        volatile bool dhcpRapidCommit;
        volatile bool dhcpRemoteAutoconf;
        volatile bool dhcpAddrParams;
        volatile bool mipRemoteLocUpdate;
        volatile int connType;
        volatile int connMsr;
        volatile double SStrace_centerx;
        volatile double SStrace_centery;
        volatile double SStrace_radius;
        volatile double SStrace_step;
        @display("bgb=400,400");
    gates:
        output out;
        input in;
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
                isRouter = false;
                @display("p=60,240");
        }
        buList: BindingUpdateList {
            parameters:
                @display("p=60,300;i=old/harddisk");
        }    
    
        ssPhy: WMaxPhySS {
            parameters:
                @display("i=abstract/accesspoint,#ce1821;p=350,144;q=SendQueue");
        }
        ssMac: ssMAC {
            parameters:
                @display("i=block/control,#ce1821;p=270,144");
        }
        networkLayer: MobileIPLayer6 {
            parameters:
                @display("i=block/app,#ce1821;p=160,144;tx=Tx,rx");
        }
        ssInfo: ssInfo {
            parameters:
                @display("p=152,80;i=block/blackboard,#ce1821");
        }
        pingApp: PingApp {
            parameters:
                @display("i=block/app;p=343,248");
        }
        
    connections allowunconnected:
        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        ssMac.ipOut --> networkLayer.ifIn++;	
        networkLayer.ifOut++ --> ssMac.ipIn;

        ssPhy.rfOut --> out;
        in --> ssPhy.rfIn;
        
        networkLayer.pingOut --> pingApp.pingv6In;
        networkLayer.pingIn <-- pingApp.pingv6Out;
        
}

