/**
 * @file   airDummy.h
 * @author Andrzej Bojarski <andrzej_bojarski@wp.pl>
 * @date   Sat Nov 18 18:42:04 2006
 * 
 * @brief  IPv6 transmitter/receiver
 * 
 * Published under GNU GPLv2 or later 
 */
 
#ifndef AIRDUMMY_H
#define AIRDUMMY_H
#include <omnetpp.h>
 
 
 class AirDummy : public cSimpleModule
 
 {public:
         
         protected:
                virtual void initialize();
                virtual void handleMessage(cMessage *msg);
       
       };
#endif
