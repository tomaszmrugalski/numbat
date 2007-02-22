import "common";

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
            display: "i=abstract/accesspoint,#40e221;p=128,256;q=SendQueue";
        bsMac: WMaxMacBS;
            display: "i=block/control,#40e221;p=128,144;q=SendQueue";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=144,48;tx=Tx,rx";
        bsIPv6_1: IPv6Node;
            parameters:
                BurstInterval = 0.027, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 400; // TBD
            display: "i=block/app,#40e221;p=48,48";
        WMaxCtrlBS: WMaxCtrlBS;
            display: "i=block/cogwheel,#40e221;p=216,136";
    connections:


        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        bsIPv6.ipOut --> bsMac.macIn++;
        bsMac.macOut++ --> bsIPv6.ipIn;

        bsIPv6_1.ipOut --> bsMac.macIn++;
        bsMac.macOut++ --> bsIPv6_1.ipIn;


        bsMac.macOut++ --> WMaxCtrlBS.macIn;
        WMaxCtrlBS.macOut --> bsMac.macIn++;
        in --> bsPhy.rfIn;
        bsPhy.rfOut --> out;
    display: "b=240,312";
endmodule



