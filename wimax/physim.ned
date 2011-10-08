
import SS;
import BS;
//import numbat.ipv6.IPv6; //MiM
import inet.networklayer.ipv6.IPv6;
import inet.nodes.xmipv6.CorrespondentNode6;
import numbat.wimax.Internet;
import inet.nodes.ipv6.Router6;
import inet.networklayer.autorouting.FlatNetworkConfigurator6;
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

// module Internet extends Router6
// {
    // parameters:
        // volatile double MinDelay;
        // volatile double MaxDelay;
// }

module Physim
{
    parameters:
        int LogLevel; //was volatile double (MiM)
        int numBS; //volatile double
        int numSS; //volatile double

        @display("bgb=0,0");
    submodules:
        // channelcontrol: ChannelControl {
            // parameters:
                // numChannels = 5;
                // @display("p=753,123");
        // }    
        BS[numBS]: BS {
            parameters:
                @display("p=100,200,r,200;i=device/antennatower_l");
            gates:
                in[numSS];
                out[numSS];
        }    
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
                @display("p=50,50,r,50;i=device/pc_s");
        }        
        configurator: FlatNetworkConfigurator6 {
            parameters:
                @display("p=763,53");
        }
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

