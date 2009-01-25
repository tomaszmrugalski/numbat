//A single switch, actually
simple Internet
    parameters:
        MinDelay: numeric,
        MaxDelay: numeric;
    gates:
        in: ipIn[];
        out: ipOut[];
endsimple


simple IPv6Node
    parameters:
        BurstInterval: numeric,
        BurstSize: numeric,
        BurstPacketSize: numeric,
        InitialDelay: numeric;
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
    parameters:
        //IP address that is going to be used in the next location after handover (if remote autoconf is enabled)
        nextIP: string;
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
        DispatchBS: IPv6Dispatch;
            display: "i=abstract/dispatcher;p=168,164";
        raGen: RaGen;
            display: "i=block/source;p=272,72";
        mobIPv6ha: MobIPv6ha;
            display: "i=misc/house;p=168,72";
        DHCPv6Srv: DHCPv6Srv;
            display: "i=device/mainframe;p=72,72";
    connections nocheck:
        eventIn --> DispatchBS.eventIn;
        DispatchBS.ipOut --> ipOut;
        ipIn --> DispatchBS.ipIn;
        raGen.raOut --> DispatchBS.raIn;

        DHCPv6Srv.dhcpOut --> DispatchBS.dhcpIn;
        DispatchBS.dhcpOut --> DHCPv6Srv.dhcpIn;


        mobIPv6ha.mipOut --> DispatchBS.genIn;
        DispatchBS.genOut --> mobIPv6ha.mipIn;

        mobIPv6ha.networkOut --> networkOut;
        networkIn --> mobIPv6ha.networkIn;
    display: "b=323,225";
endmodule
module IPv6Client
    gates:
        in: ipIn;
        out: ipOut;
    submodules:
        IPv6Node: IPv6Node;
            display: "i=block/rxtx;p=168,56";
        DispatchSS: IPv6Dispatch;
            display: "i=abstract/dispatcher;p=168,256";
        DHCPv6Cli: DHCPv6Cli;
            display: "i=device/laptop;p=72,128";
        mobIPv6mn: MobIPv6mn;
            display: "i=block/user;p=264,128";
        raRcv: RaRcv;
            parameters:
            display: "i=block/sink;p=168,128";
    connections nocheck:
                         //         IPv6Node.ipOut --> IPv6Dispatch.genIn;
                         //         IPv6Dispatch.genOut --> IPv6Node.ipIn;

        //         mobIPv6mn.lowerOut --> IPv6Dispatch.mipIn;
        //         IPv6Dispatch.mipOut --> mobIPv6mn.lowerIn;
        IPv6Node.ipOut --> mobIPv6mn.upperIn;
        mobIPv6mn.upperOut --> IPv6Node.ipIn;
        DispatchSS.genOut --> mobIPv6mn.lowerIn;
        mobIPv6mn.lowerOut --> DispatchSS.genIn;

        DispatchSS.raOut --> raRcv.raIn;
        DHCPv6Cli.dhcpOut --> DispatchSS.dhcpIn;
        DispatchSS.dhcpOut --> DHCPv6Cli.dhcpIn;
        DispatchSS.ipOut --> ipOut;
        ipIn --> DispatchSS.ipIn;
    display: "b=309,321";
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
            display: "i=block/rxtx;p=176,88";
        mobIPv6cn: MobIPv6cn;
            display: "i=block/user;p=80,88";
    connections nocheck:
        IPv6Node.ipOut --> mobIPv6cn.upperIn;
        mobIPv6cn.upperOut --> IPv6Node.ipIn;
        mobIPv6cn.lowerOut --> ipOut;
        ipIn --> mobIPv6cn.lowerIn;
    display: "b=244,162";
endmodule

