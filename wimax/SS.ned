import "common";

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
            display: "i=abstract/accesspoint,#ce1821;p=120,256;q=SendQueue";
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=120,184;q=SendQueue";
        ssIPv6: IPv6Node;
            display: "i=block/app,#ce1821;p=48,144;tx=Tx,rx";
        ssIPv6_1: IPv6Node;
            parameters:
                BurstInterval = 0.026, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 500; // TBD
            display: "i=block/app,#ce1821;p=120,72";
        WMaxCtrlSS: WMaxCtrlSS;
            display: "i=block/cogwheel,#ce1821;p=184,128";
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
    display: "b=224,352";
endmodule

