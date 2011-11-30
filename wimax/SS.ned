import common;
//import IPv6;
import MAC;
//============= Adam 14-09-2011 =====================
import inet.nodes.xmipv6.MobileIPLayer6;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.xmipv6.BindingUpdateList;
import inet.networklayer.ipv6.RoutingTable6;
import inet.base.NotificationBoard;
import inet.applications.pingapp.PingApp;
//============= Adam, end  14-09-2011==================s

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
        @node();    //============= Adam 14-09-2011 =====================
        volatile int wmaxHoOptim; 
        volatile int wmaxIsMobile; // defines type of physical mobility: 0 (fixed station), 1 (handover executed after certain timeout (next BS)), 2 (simulated SS movement), 3 (handover executed after certain timeout (random BS))
        volatile int movementType;
        volatile double x;
        volatile double y;
        volatile int initialBS;
        volatile double NetworkEntryTime;
        volatile double HandoverTime;
        volatile bool dhcpRemoteAutoconf;
        volatile int connType;
        volatile int connMsr;
        volatile double SStrace_centerx;
        volatile double SStrace_centery;
        volatile double SStrace_radius;
        volatile double SStrace_step;
        @display("bgb=400,400");
        bool FMIP = default(false); // Defines if Fast Handovers should be used or not.
    gates:
        output out;
        input in;
    submodules:
    //============= Adam 14-09-2011 =====================
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
        networkLayer: MobileIPLayer6 {
            parameters:
                @display("i=block/app,#ce1821;p=160,144;tx=Tx,rx");
        }
        pingApp: PingApp {
            parameters:
                @display("i=block/app;p=343,248");
        }
    //============= Adam, end  14-09-2011==================
        ssInfo: ssInfo {
            parameters:
                @display("p=152,80;i=block/blackboard,#ce1821");
        }
        ssPhy: WMaxPhySS {
            parameters:
                @display("i=abstract/accesspoint,#ce1821;p=350,144;q=SendQueue");
        }
        ssMac: ssMAC {
            parameters:
                @display("i=block/control,#ce1821;p=270,144");
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

