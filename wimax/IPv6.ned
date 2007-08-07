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
    gates:
        out: dhcpOut;
        in: dhcpIn;
endsimple
simple DHCPv6Cli
    gates:
        out: dhcpOut;
        in: dhcpIn;
endsimple
//Mobile IPv6 Mobile Node
simple MobIPv6mn
    gates:
        out: mipOut;
        in: mipIn;
endsimple
//Mobile IPv6 Home Agent
simple MobIPv6ha
    gates:
        out: mipOut;
        in: mipIn;
endsimple
//Module used to dispatch incoming IPv6 packets to appropriate module.
simple IPv6Dispatch
    gates:
        in: ipIn;
        out: ipOut;
        in: dhcpIn;
        out: dhcpOut;
        in: mipIn;
        out: mipOut;
        in: raIn;
        out: raOut;
        in: genIn;
        out: genOut;
        in: eventIn;
endsimple
simple RaGen
    gates:
        out: RaOut;
endsimple
//Router Advertisement Receiver
simple RaRcv
    gates:
        in: raIn;
endsimple
module IPv6Server
    connections:
endmodule
module IPv6Client
    gates:
        in: ipIn;
        out: ipOut;
        in: eventIn;
    submodules:
        IPv6Node: IPv6Node;
            display: "i=block/rxtx;p=184,72";
        IPv6Dispatch: IPv6Dispatch;
            display: "i=abstract/dispatcher;p=256,192";
        DHCPv6Cli: DHCPv6Cli;
            display: "i=block/user;p=88,136";
        mobIPv6mn: MobIPv6mn;
            display: "i=block/user;p=344,72";
        raRcv: RaRcv;
            parameters:
            display: "i=block/sink;p=424,144";
    connections nocheck:
        eventIn --> IPv6Dispatch.eventIn;
        mobIPv6mn.mipOut --> IPv6Dispatch.mipIn;
        IPv6Dispatch.mipOut --> mobIPv6mn.mipIn;
        IPv6Dispatch.raOut --> raRcv.raIn;
        DHCPv6Cli.dhcpOut --> IPv6Dispatch.dhcpIn;
        IPv6Dispatch.dhcpOut --> DHCPv6Cli.dhcpIn;
        IPv6Node.ipOut --> IPv6Dispatch.genIn;
        IPv6Dispatch.genOut --> IPv6Node.ipIn;
        IPv6Dispatch.ipOut --> ipOut;
        ipIn --> IPv6Dispatch.ipIn;
    display: "b=477,273";
endmodule

