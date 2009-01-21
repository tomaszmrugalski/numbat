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
        in: networkIn;
        out: networkOut;
    submodules:
        bsPhy: WMaxPhyBS;
            display: "i=abstract/accesspoint,#40e221;p=232,72;q=SendQueue";
        bsMac: bsMAC;
            display: "i=block/control,#40e221;p=144,72;q=SendQueue";
        radio: WMaxRadio;
            gatesizes:
                radioIn[sizeof(in)],
                radioOut[sizeof(in)]; // use in, for consistency

            display: "p=312,72;i=device/receiverdish,#40e221,30";
        bsIPv6: IPv6Server;
            display: "i=block/app,#40e221;p=64,72";
    connections nocheck:

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        bsMac.ipOut --> bsIPv6.ipIn;
        bsIPv6.ipOut --> bsMac.ipIn;

        radio.phyOut --> bsPhy.rfIn;
        bsPhy.rfOut --> radio.phyIn;

        bsIPv6.networkOut --> networkOut;
        networkIn --> bsIPv6.networkIn;
    display: "b=360,128";
endmodule



