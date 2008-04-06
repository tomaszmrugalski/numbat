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
        CN: CorrNode[numSS];
            display: "p=160-70*(numSS-1),336,r,70;b=40,24";
        internet: Internet;
            display: "p=160,280;i=misc/cloud";
    connections nocheck:

       for i=1..numSS do
          CN[i-1].ipOut --> internet.ipIn++;
          internet.ipOut++ --> CN[i-1].ipIn;
       endfor;

    display: "b=330,369";
endmodule

network physim : Physim

endnetwork

