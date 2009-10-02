
//package numbat.wimax;

import numbat.wimax.common;
import numbat.ipv6.IPv6;
import numbat.wimax.MAC;

//ssPhy
simple WMaxPhyBS
{
    gates:
        input rfIn;
        output rfOut;
        input phyIn;
        output phyOut;
}

//Simulates transmission between 1 BS and 0..n SSes.
simple WMaxRadio
{
    gates:
        input phyIn;
        output phyOut;
        output radioOut[];
        input radioIn[];
}

module BS
{
    parameters:
        volatile double x;
        volatile double y;
        @display("bgb=360,128");
    gates:
        output out[];
        input in[];
        input networkIn;
        output networkOut;
    submodules:
        bsPhy: WMaxPhyBS {
            parameters:
                @display("i=abstract/accesspoint,#40e221;p=232,72;q=SendQueue");
        }
        bsMac: bsMAC {
            parameters:
                @display("i=block/control,#40e221;p=144,72;q=SendQueue");
        }
        radio: WMaxRadio {
            parameters:
                @display("p=312,72;i=device/receiverdish,#40e221,30");
            gates:
                radioIn[sizeof(in)];
                radioOut[sizeof(in)]; // use in, for consistency

        }
        bsIPv6: IPv6Server {
            parameters:
                @display("i=block/app,#40e221;p=64,72");
        }
    connections allowunconnected:

        bsMac.phyOut --> bsPhy.phyIn;
        bsPhy.phyOut --> bsMac.phyIn;

        bsMac.ipOut --> bsIPv6.ipIn;
        bsIPv6.ipOut --> bsMac.ipIn;

        radio.phyOut --> bsPhy.rfIn;
        bsPhy.rfOut --> radio.phyIn;

        bsIPv6.networkOut --> networkOut;
        networkIn --> bsIPv6.networkIn;
}



