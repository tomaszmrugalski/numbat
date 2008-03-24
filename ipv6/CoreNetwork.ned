import
    "IPv6";

//A single switch, actually
simple Internet
    gates:
        in: ipIn[];
        out: ipOut[];
endsimple

module coreNetwork
    parameters:
        LogLevel: numeric;
    submodules:
        internet: Internet;
            display: "p=272,224;b=40,28";
        mobIPv6mn0: MobIPv6mn;
            display: "p=112,128;b=40,28";
        mobIPv6mn1: MobIPv6mn;
            display: "p=272,128;b=40,28";
        mobIPv6mn2: MobIPv6mn;
            display: "p=408,128;b=40,28";
        mobIPv6cn0: MobIPv6cn;
            display: "p=112,320;b=40,28";
        mobIPv6cn1: MobIPv6cn;
            display: "p=272,320;b=40,28";
        mobIPv6cn2: MobIPv6cn;
            display: "p=408,312;b=40,28";
        IPv6Node0: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=112,48;b=40,28";
        IPv6Node1: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=272,48;b=40,28";
        IPv6Node2: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=408,48;b=40,28";
        IPv6Node3: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=112,400;b=40,28";
        IPv6Node4: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=272,400;b=40,28";
        IPv6Node5: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=408,400;b=40,28";
    connections nocheck:
        IPv6Node0.ipOut --> mobIPv6mn0.upperIn;
        mobIPv6mn0.upperOut --> IPv6Node0.ipIn;

        IPv6Node1.ipOut --> mobIPv6mn1.upperIn;
        mobIPv6mn1.upperOut --> IPv6Node1.ipIn;

        IPv6Node2.ipOut --> mobIPv6mn2.upperIn;
        mobIPv6mn2.upperOut --> IPv6Node2.ipIn;

        mobIPv6mn0.lowerOut --> internet.ipIn++;
        internet.ipOut++ --> mobIPv6mn0.lowerIn;

        mobIPv6mn1.lowerOut --> internet.ipIn++;
        internet.ipOut++ --> mobIPv6mn1.lowerIn;

        mobIPv6mn2.lowerOut --> internet.ipIn++;
        internet.ipOut++ --> mobIPv6mn2.lowerIn;



        mobIPv6cn0.lowerOut --> internet.ipIn++;
        internet.ipOut++ --> mobIPv6cn0.lowerIn;

        mobIPv6cn1.lowerOut --> internet.ipIn++;
        internet.ipOut++ --> mobIPv6cn1.lowerIn;

        mobIPv6cn2.lowerOut --> internet.ipIn++;
        internet.ipOut++ --> mobIPv6cn2.lowerIn;



        IPv6Node3.ipOut --> mobIPv6cn0.upperIn;
        mobIPv6cn0.upperOut --> IPv6Node3.ipIn;

        IPv6Node4.ipOut --> mobIPv6cn1.upperIn;
        mobIPv6cn1.upperOut --> IPv6Node4.ipIn;

        IPv6Node5.ipOut --> mobIPv6cn2.upperIn;
        mobIPv6cn2.upperOut --> IPv6Node5.ipIn;
endmodule

network CoreNetwork : coreNetwork

endnetwork

