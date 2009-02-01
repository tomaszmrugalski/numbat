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
            display: "p=100,200,r,200;i=device/antennatower_l";
        SS: SS[numSS];
            display: "p=50,50,r,50;i=device/pc_s";
        CN: CorrNode[numSS];
            display: "i=device/pc2;p=50,355,r,50";
        internet: Internet;
            display: "p=480,280;i=misc/cloud";
    connections nocheck:

        for i=1..numSS do
            CN[i-1].ipOut --> internet.ipIn++;
            internet.ipOut++ --> CN[i-1].ipIn;
        endfor;

        for i=0..numBS-1 do
            BS[i].networkOut --> internet.ipIn++;
            internet.ipOut++ --> BS[i].networkIn;
        endfor;

    display: "b=0,0";
endmodule

network physim : Physim

endnetwork

