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
        MinDelayRng: numeric,
        MaxDelayRng: numeric,
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

//Simulates transmission between 1 BS and 0..n SSes.
simple WMaxRadio
    gates:
        in: phyIn;
        out: phyOut;
        out: radioOut[];
        in: radioIn[];
endsimple
module BS
    parameters:

    gates:
        out: out[];
        in: in[];
    submodules:
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=104,368;q=SendQueue";
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=104,264;q=SendQueue";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=104,64;tx=Tx,rx";
        //         bsIPv6_1: IPv6Node;
        //             parameters:
        //                 BurstInterval = 0.027, // TBD
        //                 BurstSize = 1, // TBD
        //                 BurstPacketSize = 400; // TBD
        //             display: "i=block/app,#40e221;p=232,80";
        WMaxCtrlBS: WMaxCtrlBS;
            display: "i=block/cogwheel,#40e221;p=216,160";
        bsCS: WMaxMacCS;
            display: "p=104,160;i=block/classifier,#40e221";
        radio: WMaxRadio;
            gatesizes:
                radioIn[sizeof(in)],
                radioOut[sizeof(in)]; // use in, for consistency

            display: "p=104,480;i=device/receiverdish,#40e221,30";
    connections nocheck:

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

        radio.phyOut --> bsPhy.rfIn;
        bsPhy.rfOut --> radio.phyIn; //
                                     //

    display: "b=272,544";
endmodule



