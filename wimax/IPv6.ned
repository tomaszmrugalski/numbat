simple IPv6Node
    parameters:
        BurstInterval: numeric,
        BurstSize: numeric,
        BurstPacketSize: numeric;
    gates:
        out: ipOut;
        in: ipIn;
endsimple

simple DHCPv6Srv
endsimple
simple DHCPv6Cli
endsimple
//Mobile IPv6 Mobile Node
simple MobIPv6mn
endsimple
//Mobile IPv6 Home Agent
simple MobIPv6ha
endsimple
module IPv6Server
    connections:
endmodule
module IPv6Client
    gates:
        in: ipIn;
        out: ipOut;
    submodules:
        IPv6Node: IPv6Node;
            parameters:
                BurstInterval = 1, // TBD
                BurstSize = 1, // TBD
                BurstPacketSize = 1; // TBD
            display: "p=240,176;b=40,28";
    connections:
        IPv6Node.ipOut --> ipOut;
        ipIn --> IPv6Node.ipIn;
    display: "b=477,273";
endmodule

