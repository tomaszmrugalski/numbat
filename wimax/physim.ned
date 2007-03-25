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
	numBS:numeric;
	

    submodules:
    Dummy: AirDummy
		gatesizes:
		in[10];
	    display: "i=misc/cloud";	
    BS: BS[numBS];
            display: "i=device/antennatower_l";
    SS: SS;
            display: "p=239,232;i=device/pc_s";
    connections nocheck:

     //  BS[1].out --> SS.in;
      //  SS.out --> BS[1].in;



endmodule

network physim : Physim

endnetwork

