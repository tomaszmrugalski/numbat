//A single switch, actually
simple Internet
    gates:
        in: ipIn[];
        out: ipOut[];
endsimple


simple IPv6Node
    parameters:
        BurstInterval: numeric,
        BurstSize: numeric,
        BurstPacketSize: numeric;
    gates:
        out: ipOut;
        in: ipIn;
        in: eventIn;
endsimple

simple DHCPv6Srv
    parameters:
        MinDelayAdvertise: numeric,
        MaxDelayAdvertise: numeric,
        MinDelayReply: numeric,
        MaxDelayReply: numeric,
        preference: numeric,
        MinDelayRelay: numeric,
        MaxDelayRelay: numeric,
        prefix: string;
    gates:
        out: dhcpOut;
        in: dhcpIn;
endsimple
simple DHCPv6Cli
    gates:
        out: dhcpOut;
        in: dhcpIn;
        in: eventIn;
endsimple
//Mobile IPv6 Mobile Node
simple MobIPv6mn
    parameters:
        myIP: string,
        corrIP: string,
        prefix: string;
    gates:
        out: upperOut;
        in: upperIn;
        out: lowerOut;
        in: lowerIn;
        in: eventIn;
endsimple
//Mobile IPv6 Home Agent
simple MobIPv6ha
    parameters:
        prefix: string;
    gates:
        out: mipOut;
        in: mipIn;
        out: networkOut;
        in: networkIn;
endsimple
//Module used to dispatch incoming IPv6 packets to appropriate module.
simple IPv6Dispatch
    gates:
        in: ipIn;
        out: ipOut;
        in: dhcpIn;
        out: dhcpOut;
        in: raIn;
        out: raOut;
        in: genIn;
        out: genOut;
        in: eventIn;
endsimple
simple RaGen
    parameters:
        RaInterval: numeric;
    gates:
        out: raOut;
endsimple
//Router Advertisement Receiver
simple RaRcv
    gates:
        in: raIn;
        in: eventIn;
endsimple

module IPv6Server
    gates:
        in: ipIn;
        out: ipOut;
        in: eventIn;
        in: networkIn;
        out: networkOut;
    submodules:
        IPv6Dispatch: IPv6Dispatch;
            display: "i=abstract/dispatcher;p=264,172";
        raGen: RaGen;
            display: "i=block/source;p=448,176";
        mobIPv6ha: MobIPv6ha;
            display: "i=misc/house;p=328,72";
        DHCPv6Srv: DHCPv6Srv;
            display: "i=device/mainframe;p=80,192";
    connections nocheck:
        eventIn --> IPv6Dispatch.eventIn;
        IPv6Dispatch.ipOut --> ipOut;
        ipIn --> IPv6Dispatch.ipIn;
        raGen.raOut --> IPv6Dispatch.raIn;

        DHCPv6Srv.dhcpOut --> IPv6Dispatch.dhcpIn;
        IPv6Dispatch.dhcpOut --> DHCPv6Srv.dhcpIn;


        mobIPv6ha.mipOut --> IPv6Dispatch.genIn;
        IPv6Dispatch.genOut --> mobIPv6ha.mipIn;

        mobIPv6ha.networkOut --> networkOut;
        networkIn --> mobIPv6ha.networkIn;
    display: "b=515,257";
endmodule
module IPv6Client
    gates:
        in: ipIn;
        out: ipOut;
    submodules:
        IPv6Node: IPv6Node;
            display: "i=block/rxtx;p=184,72";
        IPv6Dispatch: IPv6Dispatch;
            display: "i=abstract/dispatcher;p=256,192";
        DHCPv6Cli: DHCPv6Cli;
            display: "i=device/laptop;p=88,136";
        mobIPv6mn: MobIPv6mn;
            display: "i=block/user;p=344,72";
        raRcv: RaRcv;
            parameters:
            display: "i=block/sink;p=424,144";
    connections nocheck:
                         //         IPv6Node.ipOut --> IPv6Dispatch.genIn;
                         //         IPv6Dispatch.genOut --> IPv6Node.ipIn;

        //         mobIPv6mn.lowerOut --> IPv6Dispatch.mipIn;
        //         IPv6Dispatch.mipOut --> mobIPv6mn.lowerIn;
        IPv6Node.ipOut --> mobIPv6mn.upperIn;
        mobIPv6mn.upperOut --> IPv6Node.ipIn;
        IPv6Dispatch.genOut --> mobIPv6mn.lowerIn;
        mobIPv6mn.lowerOut --> IPv6Dispatch.genIn;

        IPv6Dispatch.raOut --> raRcv.raIn;
        DHCPv6Cli.dhcpOut --> IPv6Dispatch.dhcpIn;
        IPv6Dispatch.dhcpOut --> DHCPv6Cli.dhcpIn;
        IPv6Dispatch.ipOut --> ipOut;
        ipIn --> IPv6Dispatch.ipIn;
    display: "b=477,273";
endmodule
simple MobIPv6cn
    parameters:
        myIP: string,
        corrIP: string,
        prefix: string;
    gates:
        in: lowerIn;
        out: lowerOut;
        in: upperIn;
        out: upperOut;
endsimple
module CorrNode
    gates:
        in: ipIn;
        out: ipOut;
    submodules:
        IPv6Node: IPv6Node;
            display: "i=block/rxtx;p=240,320";
        mobIPv6cn: MobIPv6cn;
            display: "i=block/user;p=240,184";
    connections nocheck:
        IPv6Node.ipOut --> mobIPv6cn.upperIn;
        mobIPv6cn.upperOut --> IPv6Node.ipIn;
        mobIPv6cn.lowerOut --> ipOut;
        ipIn --> mobIPv6cn.lowerIn;
endmodule

