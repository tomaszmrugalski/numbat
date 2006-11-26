#include <omnetpp.h>

class MacDummy : public cSimpleModule
{

public:
    MacDummy();
    virtual ~MacDummy();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(MacDummy);

MacDummy::MacDummy() 
{

}

MacDummy::~MacDummy()
{

}

void MacDummy::initialize()
{

}

void MacDummy::handleMessage(cMessage *msg)
{
    
}
