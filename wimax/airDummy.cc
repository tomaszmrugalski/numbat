
#include <omnetpp.h>
#include "AirDummy.h"

//using namespace std;
 
Define_Module(AirDummy);
 
void AirDummy::initialize()
 {
      
      
  }
  
 void AirDummy::handleMessage(cMessage *msg)
 
 {
      delete msg;
      }
