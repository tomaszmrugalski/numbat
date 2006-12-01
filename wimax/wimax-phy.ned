//ssPhy
simple WMaxPhySS
    parameters:
        FrameLength: numeric;
    gates:
        out: rfOut;
        in: rfIn;
        in: phyIn;
        out: phyOut;
endsimple
simple WMaxPhyBS
    parameters:
        FrameLength: numeric;
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
    gates:
        in: phyIn;
        out: phyOut;
endsimple

simple WMaxMacSS
    gates:
        in: phyIn;
        out: phyOut;
endsimple

module PhySim
    submodules:
        ssPhy: WMaxPhySS;
            display: "p=112,120;b=40,28";
        bsPhy: WMaxPhyBS;
            display: "p=400,120;b=40,28";
        ssMac: WMaxMacSS;
            display: "p=112,40;b=40,28";
        bsMac: WMaxMacBS;
            display: "p=400,40;b=40,28";
    connections:
        ssPhy.rfOut --> bsPhy.rfIn;
        bsPhy.rfOut --> ssPhy.rfIn;

        ssMac.phyOut --> ssPhy.phyIn;
        ssPhy.phyOut --> ssMac.phyIn;

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

endmodule

network physim : PhySim
endnetwork

