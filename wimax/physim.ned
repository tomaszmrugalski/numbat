
import SS;
import BS;
//import numbat.ipv6.IPv6; //MiM
import numbat.wimax.Internet;
//============= Adam 14-09-2011 =====================
import inet.networklayer.ipv6.IPv6;
import inet.nodes.xmipv6.CorrespondentNode6;
import inet.nodes.ipv6.Router6;
import inet.networklayer.autorouting.FlatNetworkConfigurator6;
//============= Adam, end  14-09-2011==================
// import inet.world.ChannelControl;

simple AirDummy
{
    gates:
        input in[];
}

module CorrNode6 extends CorrespondentNode6
{
    parameters:
        string myIP;
        string corrIP;
        string prefix;
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
                @display("p=100,200,r,100;i=device/antennatower_l");
            gates:
                in[numSS];
                out[numSS];
        }    
//============= Adam 14-09-2011 =====================
        internet: Router6 {
            parameters:
                @display("p=150,280;i=misc/cloud");
        }
        CN[numSS]: CorrNode6 {
            parameters:
                @display("i=device/pc2;p=50,355,r,50");
        }
        SS[numSS]: SS {
            parameters:
                @display("p=50,50,r,100;i=device/pc_s");
        }        
        configurator: FlatNetworkConfigurator6 {
            parameters:
                @display("p=463,53");
        }
//============= Adam, end  14-09-2011==================s        
        connections allowunconnected:

        for i=1..numSS {
            CN[i-1].ethOut++ --> internet.ethg$i++;
            internet.ethg$o++ --> CN[i-1].ethIn++;
        }
		
        for i=0..numBS-1 {
            internet.ethg$o++ --> BS[i].ethIn;
            BS[i].ethOut --> internet.ethg$i++;
        }

}

network physim extends Physim

{
    parameters:
}

