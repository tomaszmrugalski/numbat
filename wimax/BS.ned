import
    "common";

//ssPhy
simple WMaxPhyBS
    gates:
        in: rfIn;
        out: rfOut;
        in: phyIn;
        out: phyOut;
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
        MinDelaySbc: numeric,
        MaxDelaySbc: numeric,
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

module BS
    gates:
        out: out;
        in: in;

    submodules:
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=152,280;q=SendQueue";
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=152,200;q=SendQueue";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=80,56;tx=Tx,rx";
        //         bsIPv6_1: IPv6Node;
        //             parameters:
        //                 BurstInterval = 0.027, // TBD
        //                 BurstSize = 1, // TBD
        //                 BurstPacketSize = 400; // TBD
        //             display: "i=block/app,#40e221;p=232,80";
        WMaxCtrlBS: WMaxCtrlBS;
            display: "i=block/cogwheel,#40e221;p=240,160";
        bsCS: WMaxMacCS;
            display: "p=152,120;i=block/classifier,#40e221";
    connections:

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        bsCS.ipOut++ --> bsIPv6.ipIn;
        bsIPv6.ipOut --> bsCS.ipIn++;

                                      //         bsCS.ipOut++ --> bsIPv6_1.ipIn;
                                      //         bsIPv6_1.ipOut --> bsCS.ipIn++;

        bsMac.macOut++ --> bsCS.macIn;
        bsCS.macOut --> bsMac.macIn++;

                                       //        bsMac.macOut++ --> bsIPv6.ipIn;
                                       //        bsIPv6.ipOut --> bsMac.macIn++;

        bsMac.macOut++ --> WMaxCtrlBS.macIn;
        WMaxCtrlBS.macOut --> bsMac.macIn++;

        in --> bsPhy.rfIn;
        bsPhy.rfOut --> out;

    display: "b=280,344";
endmodule



