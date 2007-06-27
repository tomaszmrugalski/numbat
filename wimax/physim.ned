import
    "SS";
import
    "BS";

simple AirDummy
    parameters:
        LogLevel: numeric;
    gates:
        in: in[];
endsimple

module Physim
    parameters:
        numBS: numeric,
        numSS: numeric;

    submodules:
        Dummy: AirDummy;
            gatesizes:
                in[10];
            display: "p=169,72;i=misc/cloud";
        BS: BS[numBS];
	    gatesizes:
		in[numSS],
		out[numSS];
            display: "i=device/antennatower_l";
        SS: SS[numSS];
            display: "i=device/pc_s";
    connections nocheck:


endmodule

network physim : Physim

endnetwork

