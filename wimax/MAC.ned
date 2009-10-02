//package numbat.wimax;

simple WMaxMacCS
{
    gates:
        input macIn;
        output macOut;
        input ipIn[];
        output ipOut[];
}

simple WMaxMacSS
{
    parameters:
        volatile double FrameLength;
    gates:
        input phyIn;
        output phyOut;
        input macIn[];
        output macOut[];
}

simple WMaxCtrlSS
{
    gates:
        output macOut;
        input macIn;
        input eventIn;
}

simple WMaxMacBS
{
    parameters:
        volatile double FrameLength;
    gates:
        input phyIn;
        output phyOut;
        input macIn[];
        output macOut[];
}

simple WMaxCtrlBS
{
    parameters:
        volatile double MinDelayCdma;
        volatile double MaxDelayCdma;
        volatile double MinDelayRng;
        volatile double MaxDelayRng;
        volatile double MinDelaySbc;
        volatile double MaxDelaySbc;
        volatile double MinDelayScn;
        volatile double MaxDelayScn;
        volatile double MinDelayReg;
        volatile double MaxDelayReg;
        volatile double MinDelayHoRsp;
        volatile double MaxDelayHoRsp;
        volatile double MinDelayDsxRvd;
        volatile double MaxDelayDsxRvd;
        volatile double MinDelayDsxRsp;
        volatile double MaxDelayDsxRsp;
        volatile double MinDelaySaTek;
        volatile double MaxDelaySaTek;
    gates:
        output macOut;
        input macIn;
}


module ssMAC
{
    parameters:
        @display("bgb=346,162");
    gates:
        output phyOut;
        output ipOut;
        input phyIn;
        input ipIn;
    submodules:
        ssMac: WMaxMacSS {
            parameters:
                @display("i=block/control,#ce1821;p=160,96;q=SendQueue");
        }
        WMaxCtrlSS: WMaxCtrlSS {
            parameters:
                @display("i=block/cogwheel,#ce1821;p=264,80");
        }
        ssCS: WMaxMacCS {
            parameters:
                @display("p=64,64;i=block/classifier,#ce1821");
        }
    connections allowunconnected:
        ssMac.phyOut --> phyOut;
        phyIn --> ssMac.phyIn;

        ssCS.ipOut++ --> ipOut;
        ipIn --> ssCS.ipIn++;

        ssMac.macOut++ --> ssCS.macIn;
        ssCS.macOut --> ssMac.macIn++;

        ssMac.macOut++ --> WMaxCtrlSS.macIn;
        WMaxCtrlSS.macOut --> ssMac.macIn++;

}


module bsMAC
{
    parameters:
        @display("bgb=306,162");
    gates:
        output phyOut;
        output ipOut;
        input phyIn;
        input ipIn;
    submodules:
        bsMac: WMaxMacBS {
            parameters:
                @display("i=block/control,#40e221;p=152,112;q=SendQueue");
        }
        WMaxCtrlBS: WMaxCtrlBS {
            parameters:
                @display("i=block/cogwheel,#40e221;p=240,72");
        }
        bsCS: WMaxMacCS {
            parameters:
                @display("i=block/classifier,#40e221;p=72,72");
        }
    connections allowunconnected:

        bsMac.phyOut --> phyOut;
        phyIn --> bsMac.phyIn;

        bsCS.ipOut++ --> ipOut;
        ipIn --> bsCS.ipIn++;

        bsMac.macOut++ --> bsCS.macIn;
        bsCS.macOut --> bsMac.macIn++;

        bsMac.macOut++ --> WMaxCtrlBS.macIn;
        WMaxCtrlBS.macOut --> bsMac.macIn++;

}

