
simple WMaxMacCS
    gates:
        in: macIn;
        out: macOut;
        in: ipIn[];
        out: ipOut[];
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
        in: eventIn;
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

simple WMaxCtrlBS
    parameters:
        MinDelayCdma: numeric,
        MaxDelayCdma: numeric,
        MinDelayRng: numeric,
        MaxDelayRng: numeric,
        MinDelaySbc: numeric,
        MaxDelaySbc: numeric,
        MinDelayScn: numeric,
        MaxDelayScn: numeric,
        MinDelayReg: numeric,
        MaxDelayReg: numeric,
        MinDelayHoRsp: numeric,
        MaxDelayHoRsp: numeric,
        MinDelayDsxRvd: numeric,
        MaxDelayDsxRvd: numeric,
        MinDelayDsxRsp: numeric,
        MaxDelayDsxRsp: numeric,
        MinDelaySaTek: numeric,
        MaxDelaySaTek: numeric;
    gates:
        out: macOut;
        in: macIn;
endsimple


module ssMAC
    gates:
        out: phyOut;
        out: ipOut;
        in: phyIn;
        in: ipIn;
    submodules:
        ssMac: WMaxMacSS;
            display: "i=block/control,#ce1821;p=160,96;q=SendQueue";
        WMaxCtrlSS: WMaxCtrlSS;
            display: "i=block/cogwheel,#ce1821;p=264,80";
        ssCS: WMaxMacCS;
            display: "p=64,64;i=block/classifier,#ce1821";
    connections nocheck:
        ssMac.phyOut --> phyOut;
        phyIn --> ssMac.phyIn;

        ssCS.ipOut++ --> ipOut;
        ipIn --> ssCS.ipIn++;

        ssMac.macOut++ --> ssCS.macIn;
        ssCS.macOut --> ssMac.macIn++;

        ssMac.macOut++ --> WMaxCtrlSS.macIn;
        WMaxCtrlSS.macOut --> ssMac.macIn++;

    display: "b=346,162";
endmodule


module bsMAC
    gates:
        out: phyOut;
        out: ipOut;
        in: phyIn;
        in: ipIn;
    submodules:
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=152,112;q=SendQueue";
        WMaxCtrlBS: WMaxCtrlBS;
            display: "i=block/cogwheel,#40e221;p=240,72";
        bsCS: WMaxMacCS;
            display: "i=block/classifier,#40e221;p=72,72";
    connections nocheck:

        bsMac.phyOut --> phyOut;
        phyIn --> bsMac.phyIn;

        bsCS.ipOut++ --> ipOut;
        ipIn --> bsCS.ipIn++;

        bsMac.macOut++ --> bsCS.macIn;
        bsCS.macOut --> bsMac.macIn++;

        bsMac.macOut++ --> WMaxCtrlBS.macIn;
        WMaxCtrlBS.macOut --> bsMac.macIn++;

    display: "b=306,162";
endmodule

