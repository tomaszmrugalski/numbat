//package numbat.ipv6;

//A single switch, actually
simple Internet
{
    parameters:
        volatile double MinDelay;
        volatile double MaxDelay;
    gates:
        input ipIn[];
        output ipOut[];
}


simple IPv6Node
{
    parameters:
        volatile double BurstInterval;
        volatile double BurstSize;
        volatile double BurstPacketSize;
        volatile double InitialDelay;
        volatile double TrafficType;
    gates:
        output ipOut;
        input ipIn;
        input eventIn;
}

simple DHCPv6Srv
{
    parameters:
        volatile double MinDelayAdvertise;
        volatile double MaxDelayAdvertise;
        volatile double MinDelayReply;
        volatile double MaxDelayReply;
        volatile double preference;
        volatile double MinDelayRelay;
        volatile double MaxDelayRelay;
        string prefix;
    gates:
        output dhcpOut;
        input dhcpIn;
}
simple DHCPv6Cli
{
    parameters:
        //IP address that is going to be used in the next location after handover (if remote autoconf is enabled)
        string nextIP;
    gates:
        output dhcpOut;
        input dhcpIn;
        input eventIn;
}
//Mobile IPv6 Mobile Node
simple MobIPv6mn
{
    parameters:
        string myIP;
        string corrIP;
        string prefix;
    gates:
        output upperOut;
        input upperIn;
        output lowerOut;
        input lowerIn;
        input eventIn;
}
//Mobile IPv6 Home Agent
simple MobIPv6ha
{
    parameters:
        string prefix;
    gates:
        output mipOut;
        input mipIn;
        output networkOut;
        input networkIn;
}
//Module used to dispatch incoming IPv6 packets to appropriate module.
simple IPv6Dispatch
{
    gates:
        input ipIn;
        output ipOut;
        input dhcpIn;
        output dhcpOut;
        input raIn;
        output raOut;
        input genIn;
        output genOut;
        input eventIn;
}
simple RaGen
{
    parameters:
        volatile double RaInterval;
    gates:
        output raOut;
}
//Router Advertisement Receiver
simple RaRcv
{
    gates:
        input raIn;
        input eventIn;
}

module IPv6Server
{
    parameters:
        @display("bgb=323,225");
    gates:
        input ipIn;
        output ipOut;
        input eventIn;
        input networkIn;
        output networkOut;
    submodules:
        DispatchBS: IPv6Dispatch {
            parameters:
                @display("i=abstract/dispatcher;p=168,164");
        }
        raGen: RaGen {
            parameters:
                @display("i=block/source;p=272,72");
        }
        mobIPv6ha: MobIPv6ha {
            parameters:
                @display("i=misc/house;p=168,72");
        }
        DHCPv6Srv: DHCPv6Srv {
            parameters:
                @display("i=device/mainframe;p=72,72");
        }
    connections allowunconnected:
        eventIn --> DispatchBS.eventIn;
        DispatchBS.ipOut --> ipOut;
        ipIn --> DispatchBS.ipIn;
        raGen.raOut --> DispatchBS.raIn;

        DHCPv6Srv.dhcpOut --> DispatchBS.dhcpIn;
        DispatchBS.dhcpOut --> DHCPv6Srv.dhcpIn;


        mobIPv6ha.mipOut --> DispatchBS.genIn;
        DispatchBS.genOut --> mobIPv6ha.mipIn;

        mobIPv6ha.networkOut --> networkOut;
        networkIn --> mobIPv6ha.networkIn;
}
module IPv6Client
{
    parameters:
        @display("bgb=309,321");
    gates:
        input ipIn;
        output ipOut;
    submodules:
        MNode: IPv6Node {
            parameters:
                @display("i=block/rxtx;p=168,56");
        }
        DispatchSS: IPv6Dispatch {
            parameters:
                @display("i=abstract/dispatcher;p=168,256");
        }
        DHCPv6Cli: DHCPv6Cli {
            parameters:
                @display("i=device/laptop;p=72,128");
        }
        mobIPv6mn: MobIPv6mn {
            parameters:
                @display("i=block/user;p=264,128");
        }
        raRcv: RaRcv {
            parameters:
                @display("i=block/sink;p=168,128");
        }
    connections allowunconnected:
                         //         IPv6Node.ipOut --> IPv6Dispatch.genIn;
                         //         IPv6Dispatch.genOut --> IPv6Node.ipIn;

        //         mobIPv6mn.lowerOut --> IPv6Dispatch.mipIn;
        //         IPv6Dispatch.mipOut --> mobIPv6mn.lowerIn;
        MNode.ipOut --> mobIPv6mn.upperIn;
        mobIPv6mn.upperOut --> MNode.ipIn;
        DispatchSS.genOut --> mobIPv6mn.lowerIn;
        mobIPv6mn.lowerOut --> DispatchSS.genIn;

        DispatchSS.raOut --> raRcv.raIn;
        DHCPv6Cli.dhcpOut --> DispatchSS.dhcpIn;
        DispatchSS.dhcpOut --> DHCPv6Cli.dhcpIn;
        DispatchSS.ipOut --> ipOut;
        ipIn --> DispatchSS.ipIn;
}
simple MobIPv6cn
{
    parameters:
        string myIP;
        string corrIP;
        string prefix;
    gates:
        input lowerIn;
        output lowerOut;
        input upperIn;
        output upperOut;
}
module CorrNode
{
    parameters:
        @display("bgb=244,162");
    gates:
        input ipIn;
        output ipOut;
    submodules:
        CNode: IPv6Node {
            parameters:
                @display("i=block/rxtx;p=176,88");
        }
        mobIPv6cn: MobIPv6cn {
            parameters:
                @display("i=block/user;p=80,88");
        }
    connections allowunconnected:
        CNode.ipOut --> mobIPv6cn.upperIn;
        mobIPv6cn.upperOut --> CNode.ipIn;
        mobIPv6cn.lowerOut --> ipOut;
        ipIn --> mobIPv6cn.lowerIn;
}

