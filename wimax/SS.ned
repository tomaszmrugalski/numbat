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


module SS //
          //
    parameters:
        wmaxHoOptim: numeric;
    gates:
        out: out;
        in: in; //
                //
                //
    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=160,296;q=SendQueue";
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=160,208;q=SendQueue";
        ssIPv6: IPv6Node;
            display: "i=block/app,#ce1821;p=80,56;tx=Tx,rx";
        //         ssIPv6_1: IPv6Node;
        //             parameters:
        //                 BurstInterval = 0.026, // TBD
        //                 BurstSize = 1, // TBD
        //                 BurstPacketSize = 100; // TBD
        //             display: "i=block/app,#ce1821;p=248,80";
        WMaxCtrlSS: WMaxCtrlSS;
            display: "i=block/cogwheel,#ce1821;p=280,160";
        ssCS: WMaxMacCS;
            display: "p=160,128;i=block/classifier,#ce1821";
    connections:
        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        ssCS.ipOut++ --> ssIPv6.ipIn;
        ssIPv6.ipOut --> ssCS.ipIn++;

                                      //         ssCS.ipOut++ --> ssIPv6_1.ipIn;
                                      //         ssIPv6_1.ipOut --> ssCS.ipIn++;

        ssMac.macOut++ --> ssCS.macIn;
        ssCS.macOut --> ssMac.macIn++;

        ssMac.macOut++ --> WMaxCtrlSS.macIn;
        WMaxCtrlSS.macOut --> ssMac.macIn++;

        ssPhy.rfOut --> out;
        in --> ssPhy.rfIn;
    display: "b=328,360";
endmodule

