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

module PhySim
    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=112,256;q=SendQueue";
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=400,256;q=SendQueue";
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=112,160;q=SendQueue";
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=400,152;q=SendQueue";
        ssIPv6: IPv6Node;
            display: "i=block/app,#ce1821;p=112,64;tx=Tx,rx";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=400,56;tx=Tx,rx";
    connections:
        ssPhy.rfOut --> bsPhy.rfIn;
        bsPhy.rfOut --> ssPhy.rfIn;

        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        ssIPv6.ipOut --> ssMac.macIn++;
        ssMac.macOut++ --> ssIPv6.ipIn;

        bsIPv6.ipOut --> bsMac.macIn++;
        bsMac.macOut++ --> bsIPv6.ipIn;
endmodule

network physim : PhySim
endnetwork


