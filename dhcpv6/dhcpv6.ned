module DHCPv6Server
    connections:
endmodule
module DHCPv6Client
    submodules:
        cli: Cli;
            display: "p=264,176;i=block/blackboard_l";
        cli1: Cli;
            display: "p=120,168;b=40,28";
    connections:
        cli.out --> cli1.in;
endmodule
simple Cli
endsimple

