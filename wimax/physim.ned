import
    "SS";
import
    "BS";
module Physim
    submodules:
        BS: BS;
            display: "p=49,72;i=device/antennatower_l";
        SS: SS;
            display: "p=239,232;i=device/pc_s";
    connections:

        BS.out --> SS.in;
        SS.out --> BS.in;


endmodule

network physim : Physim

endnetwork

