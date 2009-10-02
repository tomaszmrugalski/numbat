
import SS;
import BS;
import numbat.ipv6.IPv6; //MiM

simple AirDummy
{
    gates:
        input in[];
}

module Physim
{
    parameters:
	int LogLevel; //was volatile double (MiM)
        int numBS; //volatile double
        int numSS; //volatile double

        @display("bgb=0,0");
    submodules:
        BS[numBS]: BS {
            parameters:
                @display("p=100,200,r,200;i=device/antennatower_l");
            gates:
                in[numSS];
                out[numSS];
        }
        SS[numSS]: SS {
            parameters:
                @display("p=50,50,r,50;i=device/pc_s");
        }
        CN[numSS]: CorrNode {
            parameters:
                @display("i=device/pc2;p=50,355,r,50");
        }
        internet: Internet {
            parameters:
                @display("p=480,280;i=misc/cloud");
        }
    connections allowunconnected:

        for i=1..numSS {
            CN[i-1].ipOut --> internet.ipIn++;
            internet.ipOut++ --> CN[i-1].ipIn;
        }

        for i=0..numBS-1 {
            BS[i].networkOut --> internet.ipIn++;
            internet.ipOut++ --> BS[i].networkIn;
        }

}

network physim extends Physim

{
    parameters:
}

