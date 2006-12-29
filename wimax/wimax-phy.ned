//ssPhy
simple WMaxPhySS
    gates:
        out: rfOut;
        in: rfIn;
        in: phyIn;
        out: phyOut;
endsimple
simple WMaxPhyBS
    gates:
        in: rfIn;
        out: rfOut;
        in: phyIn;
        out: phyOut;
endsimple

simple MacDummy
    gates:
        out: phyOut;
        in: phyIn;
endsimple

simple WMaxMacBS
    parameters:
        FrameLength: numeric;
    gates:
        in: phyIn;
        out: phyOut;
        in: macIn[];
        out: macOut[];
endsimple

simple WMaxMacSS
    parameters:
        FrameLength: numeric;
    gates:
        in: phyIn;
        out: phyOut;
        in: macIn[];
        out: macOut[];
endsimple

simple IPv6Node
    parameters:
        BurstInterval: numeric,
        BurstSize: numeric,
        BurstPacketSize: numeric;
    gates:
        out: ipOut;
        in: ipIn;
endsimple

simple WMaxCtrlSS
    gates:
        out: macOut;
        in: macIn;
endsimple

simple WMaxCtrlBS
    gates:
        out: macOut;
        in: macIn;
endsimple

module PhySim
    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=120,336;q=SendQueue";
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=488,336;q=SendQueue";
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=120,184;q=SendQueue";
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=488,176;q=SendQueue";
        ssIPv6: IPv6Node;
            display: "i=block/app,#ce1821;p=72,96;tx=Tx,rx";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=536,56;tx=Tx,rx";
        ssIPv6_1: IPv6Node;
            parameters:
                BurstInterval = 0.026, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 500; // TBD
            display: "i=block/app,#ce1821;p=168,56";
        bsIPv6_1: IPv6Node;
            parameters:
                BurstInterval = 0.027, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 400; // TBD
            display: "i=block/app,#40e221;p=416,88";
        WMaxCtrlSS: WMaxCtrlSS;
            display: "i=block/cogwheel,#ce1821;p=216,144";
        WMaxCtrlBS: WMaxCtrlBS;
            display: "i=block/cogwheel,#40e221;p=376,200";
    connections:
        ssPhy.rfOut --> bsPhy.rfIn;
        bsPhy.rfOut --> ssPhy.rfIn;

        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        ssIPv6.ipOut --> ssMac.macIn++;
        ssMac.macOut++ --> ssIPv6.ipIn;

        ssMac.macOut++ --> ssIPv6_1.ipIn;
        ssIPv6_1.ipOut --> ssMac.macIn++;

        bsIPv6.ipOut --> bsMac.macIn++;
        bsMac.macOut++ --> bsIPv6.ipIn;

        bsIPv6_1.ipOut --> bsMac.macIn++;
        bsMac.macOut++ --> bsIPv6_1.ipIn;

        ssMac.macOut++ --> WMaxCtrlSS.macIn;
        WMaxCtrlSS.macOut --> ssMac.macIn++;

        bsMac.macOut++ --> WMaxCtrlBS.macIn;
        WMaxCtrlBS.macOut --> bsMac.macIn++;
    display: "b=600,400";
endmodule

network physim : PhySim
endnetwork

