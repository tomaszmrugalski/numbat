import
    "common";
import
    "IPv6";
import
    "MAC";

//ssPhy
simple WMaxPhyBS
    gates:
        in: rfIn;
        out: rfOut;
        in: phyIn;
        out: phyOut;
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
        x: numeric,
        y: numeric;
    gates:
        out: out[];
        in: in[];
    submodules:
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=104,280;q=SendQueue";
        bsMac: bsMAC;
            display: "i=block/control,#40e221;p=104,168;q=SendQueue";
        bsIPv6: IPv6Node;
            display: "i=block/app,#40e221;p=104,64;tx=Tx,rx";
        radio: WMaxRadio;
            gatesizes:
                radioIn[sizeof(in)],
                radioOut[sizeof(in)]; // use in, for consistency

            display: "p=216,280;i=device/receiverdish,#40e221,30";
    connections nocheck:

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        bsMac.ipOut --> bsIPv6.ipIn;
        bsIPv6.ipOut --> bsMac.ipIn;

        radio.phyOut --> bsPhy.rfIn;
        bsPhy.rfOut --> radio.phyIn; //
                                     //
    display: "b=264,328";
endmodule



