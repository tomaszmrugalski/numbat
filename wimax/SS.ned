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
        initialBS: numeric,
        NetworkEntryTime: numeric,
        HandoverTime: numeric,
        ipSkipDad: numeric,
        dhcpSkipInitialDelay: numeric,
        dhcpPref255: numeric,
        dhcpRapidCommit: numeric,
        SStrace_centerx: numeric,
        SStrace_centery: numeric,
        SStrace_radius: numeric,
        SStrace_step: numeric;
    gates:
        out: out;
        in: in;
    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=232,240;q=SendQueue";
        ssMac: ssMAC;
            display: "i=block/control,#ce1821;p=232,152";
        ssIPv6: IPv6Client;
            display: "i=block/app,#ce1821;p=232,64;tx=Tx,rx";
        //         ssIPv6_1: IPv6Node;
        //             parameters:
        //                 BurstInterval = 0.026, // TBD
        //                 BurstSize = 1, // TBD
        //                 BurstPacketSize = 100; // TBD
        //             display: "i=block/app,#ce1821;p=248,80";
        ssInfo: ssInfo;
            display: "p=88,112;i=block/blackboard,#ce1821";
    connections nocheck:
        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        ssMac.ipOut --> ssIPv6.ipIn;
        ssIPv6.ipOut --> ssMac.ipIn;

        ssPhy.rfOut --> out;
        in --> ssPhy.rfIn;
    display: "b=352,296";
endmodule

