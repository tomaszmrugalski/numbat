import
    "SS";
import
    "BS";

simple AirDummy
    gates:
        in: in[];
endsimple

module Physim
    parameters:
        LogLevel: numeric,
        numBS: numeric,
        numSS: numeric;

    submodules:
        BS: BS[numBS];
            gatesizes:
                in[numSS],
                out[numSS];
            display: "i=device/antennatower_l";
        SS: SS[numSS];
            display: "p=127,144;i=device/pc_s";
        CN: MobIPv6cn[numSS];
            display: "p=158,336;b=40,24";
        internet: Internet;
            display: "p=160,280;i=misc/cloud";
    connections nocheck:

    display: "b=330,369";
endmodule

network physim : Physim

endnetwork

