
/**
 * @file   wmaxphy.cc
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Sat Nov 18 18:52:36 2006
 * 
 * @brief  WMaxPHY implementation
 * 
 * 
 */

#include <omnetpp.h>
#include "wmaxphy.h"
#include "wmaxmsg_m.h"

/********************************************************************************/
/*** WMax PHY BS ****************************************************************/
/********************************************************************************/

Define_Module(WMaxPhyBS);

WMaxPhyBS::WMaxPhyBS()
{

}

WMaxPhyBS::~WMaxPhyBS()
{

}

void WMaxPhyBS::initialize()
{
    SendQueue.clear();
    SendQueue.setName("SendQueue");

    this->UlMap = 0;
    this->DlMap = 0;
    this->FrameCnt = 0;
}

void WMaxPhyBS::handleMessage(cMessage *msg)
{   checkConnect();
    cGate * gate = msg->arrivalGate();
    // uplink message
    ev << fullName() << ":Message " << msg->fullName() << " received on gate: " << gate->fullName() << ", id=" << gate->id() << endl;
    if (!strcmp(gate->fullName(),"rfIn")) {
	// deliver message immediately
	
	send(msg, "phyOut");
	return;
    }

    // downlink message
    if ( dynamic_cast<WMaxMsgDlMap*>(msg) ) {
	this->DlMap = check_and_cast<WMaxMsgDlMap*>(msg);
	ev << "DL-MAP ready to send." << endl;
	return;
    }
    if (dynamic_cast<WMaxMsgUlMap*>(msg)) {
	this->UlMap = check_and_cast<WMaxMsgUlMap*>(msg);
	ev << "UL-MAP ready to send." << endl;
	return;
    }
    if (dynamic_cast<WMaxPhyDummyFrameStart*>(msg)) {
	beginFrame();
	delete msg;
	return;
    }

    // store message for sending
    SendQueue.insert(msg);
}

void WMaxPhyBS::beginFrame()
{
    FrameCnt++;
    ev << fullName() << ": Frame number: " << FrameCnt << ", " << SendQueue.length() << " message(s) to send. " << endl;

    if (this->DlMap) {
	send(DlMap, "rfOut");
	this->DlMap = 0;
    } else {
	ev << "DL-MAP not set. Send skipped" << endl;
    }
    if (this->UlMap) {
	send(UlMap, "rfOut");
	this->UlMap = 0;
    } else {
	ev << "UL-MAP not set. Send skipped" << endl;
    }

    while (!SendQueue.empty()) {
	cMessage * msg = (cMessage*)SendQueue.pop();
	send(msg, "rfOut");
    }
}

// checks if BS is connected to anything and connects to dummy if not
void WMaxPhyBS::checkConnect()
{ cModule *BS = parentModule();
  cGate *BSout = BS->gate("out");
  if(BSout->isConnected())
  {
                          }
  else
          { int gatenum=-1;
            int connected=1; 
            cModule *BS = parentModule();
            cModule *physim = parentModule()->parentModule();
            cModule *dummy = physim->submodule("Dummy");
    
    while( connected) {
        gatenum++;
    cGate *dumgate=dummy->gate("in",gatenum);
    connected=(dumgate->isConnected());
    
                                       }
    
    BS->gate("out")->connectTo(dummy->gate("in",gatenum)) ; 
                                                           
           }   
     
   }

/********************************************************************************/
/*** WMax PHY SS ****************************************************************/
/********************************************************************************/

Define_Module(WMaxPhySS);

WMaxPhySS::WMaxPhySS()
{

}

WMaxPhySS::~WMaxPhySS()
{

}

void WMaxPhySS::initialize()
{   
    SendQueue.clear();
    SendQueue.setName("SendQueue");
    
    cModule *SS = parentModule();
    cModule *physim = parentModule()->parentModule();
    cModule *BS = physim->submodule("BS",0);
    SS->gate("out")->connectTo(BS->gate("in")) ; 
    BS->gate("out")->connectTo(SS->gate("in")) ;
}

void WMaxPhySS::beginFrame()
{
    while (!SendQueue.empty()) {
	cMessage * msg = (cMessage*)SendQueue.pop();
	send(msg, "rfOut");
    }
    

}

void WMaxPhySS::handleMessage(cMessage *msg)
{   static int licz ; // test
    cGate * gate = msg->arrivalGate();
    // uplink message
    ev << fullName() << ":Message " << msg->fullName() << " received on gate: " << gate->fullName() << ", id=" << gate->id() << endl;
    if (!strcmp(gate->fullName(),"rfIn")) {
	// deliver message immediately
	send(msg, "phyOut");
    licz=licz+1 ; //test
	return;
    }

    if (dynamic_cast<WMaxPhyDummyFrameStart*>(msg)) {
	beginFrame();
	delete msg;
	return;
    }
   // downlink message
    SendQueue.insert(msg);

    

}
