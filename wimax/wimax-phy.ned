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
        in: ipIn;
        out: ipOut;
endsimple

simple WMaxMacSS
    parameters:
        FrameLength: numeric;
    gates:
        in: phyIn;
        out: phyOut;
        in: ipIn;
        out: ipOut;
endsimple

simple IPv6Node
    gates:
        out: ipOut;
        in: ipIn;
endsimple

module PhySim
    submodules:
        ssPhy: WMaxPhySS;
            display: "i=abstract/accesspoint,#ce1821;p=112,256";
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=400,256";
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=112,160";
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=400,152";
        ssIPv6: IPv6Node;
            display: "i=block/app,#ce1821;p=112,64";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=400,56";
    connections:
        ssPhy.rfOut --> bsPhy.rfIn;
        bsPhy.rfOut --> ssPhy.rfIn;

        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        ssIPv6.ipOut --> ssMac.ipIn;
        ssMac.ipOut --> ssIPv6.ipIn;

        bsIPv6.ipOut --> bsMac.ipIn;
        bsMac.ipOut --> bsIPv6.ipIn;
endmodule

network physim : PhySim
endnetwork


