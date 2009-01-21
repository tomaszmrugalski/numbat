import
    "common";
import
    "IPv6";
import
    "MAC";

simple WMaxPhySS
    gates:
        out: rfOut;
        in: rfIn;
        in: phyIn;
        out: phyOut;
endsimple

simple ssInfo
endsimple


module SS //
          //
    parameters:
        wmaxHoOptim: numeric,
        wmaxIsMobile: numeric,
        movementType: numeric,
        x: numeric,
        y: numeric,
        initialBS: numeric,
        NetworkEntryTime: numeric,
        HandoverTime: numeric,
        dadType: numeric,
        dhcpSkipInitialDelay: numeric,
        dhcpPref255: numeric,
        dhcpRapidCommit: numeric,
        dhcpRemoteAutoconf: numeric,
        dhcpAddrParams: numeric,
        mipRemoteLocUpdate: numeric,
        connType: numeric,
        connMsr: numeric,
        SStrace_centerx: numeric,
        SStrace_centery: numeric,
        SStrace_radius: numeric,
        SStrace_step: numeric;
    gates:
        out: out;
        in: in;
    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=248,144;q=SendQueue";
        ssMac: ssMAC;
            display: "i=block/control,#ce1821;p=152,144";
        ssIPv6: IPv6Client;
            display: "i=block/app,#ce1821;p=56,144;tx=Tx,rx";
        ssInfo: ssInfo;
            display: "p=152,80;i=block/blackboard,#ce1821";
    connections nocheck:
        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        ssMac.ipOut --> ssIPv6.ipIn;
        ssIPv6.ipOut --> ssMac.ipIn;

        ssPhy.rfOut --> out;
        in --> ssPhy.rfIn;
    display: "b=300,193";
endmodule

