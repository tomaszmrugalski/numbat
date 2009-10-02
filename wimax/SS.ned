import common;
import IPv6;
import MAC;

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
        @display("bgb=300,193");
    gates:
        output out;
        input in;
    submodules:
        ssPhy: WMaxPhySS {
            parameters:
                @display("i=abstract/accesspoint,#ce1821;p=248,144;q=SendQueue");
        }
        ssMac: ssMAC {
            parameters:
                @display("i=block/control,#ce1821;p=152,144");
        }
        ssIPv6: IPv6Client {
            parameters:
                @display("i=block/app,#ce1821;p=56,144;tx=Tx,rx");
        }
        ssInfo: ssInfo {
            parameters:
                @display("p=152,80;i=block/blackboard,#ce1821");
        }
    connections allowunconnected:
        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        ssMac.ipOut --> ssIPv6.ipIn;
        ssIPv6.ipOut --> ssMac.ipIn;

        ssPhy.rfOut --> out;
        in --> ssPhy.rfIn;
}

