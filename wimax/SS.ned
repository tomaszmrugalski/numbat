import
    "common";

simple WMaxPhySS
    gates:
        out: rfOut;
        in: rfIn;
        in: phyIn;
        out: phyOut;
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


simple WMaxCtrlSS
    gates:
        out: macOut;
        in: macIn;
endsimple


module SS

    gates:
        out: out;
        in: in;


    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=232,296;q=SendQueue";
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=232,208;q=SendQueue";
        ssIPv6: IPv6Node;
            display: "i=block/app,#ce1821;p=112,160;tx=Tx,rx";
        ssIPv6_1: IPv6Node;
            parameters:
                BurstInterval = 0.026, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 100; // TBD
            display: "i=block/app,#ce1821;p=232,80";
        WMaxCtrlSS: WMaxCtrlSS;
            display: "i=block/cogwheel,#ce1821;p=352,160";
    connections:

        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;
        ssIPv6.ipOut --> ssMac.macIn++;
        ssMac.macOut++ --> ssIPv6.ipIn;
        ssMac.macOut++ --> ssIPv6_1.ipIn;
        ssIPv6_1.ipOut --> ssMac.macIn++;
        ssMac.macOut++ --> WMaxCtrlSS.macIn;
        WMaxCtrlSS.macOut --> ssMac.macIn++;
        ssPhy.rfOut --> out;
        in --> ssPhy.rfIn;
    display: "b=448,360";
endmodule

