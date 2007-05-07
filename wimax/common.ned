simple MacDummy
    gates:
        out: phyOut;
        in: phyIn;
endsimple

simple IPv6Node
    parameters:
        BurstInterval: numeric,
        BurstSize: numeric,
        BurstPacketSize: numeric;
    gates:
        out: ipOut;
        in: ipIn;
endsimple

simple WMaxMacCS
    gates:
        in: macIn;
        out: macOut;
        in: ipIn[];
        out: ipOut[];
endsimple

