/**
 * @file   ssinfo.cc
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-06-30 21:01:52+0200
 * 
 * @brief  SS parameters
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>
#include <string>
#include <math.h>
#include "logger.h"
#include "ssinfo.h"

using namespace std;

/********************************************************************************/
/*** ssInfo  ********************************************************************/
/********************************************************************************/

Define_Module(ssInfo);

void ssInfo::initialize() {
    info.macAddr = ((uint64_t)0x0018de << 24) + (rand()%(((uint64_t)1 << 24) - 1));

    Log(Notice) << "macAddr=" << hex << info.macAddr << dec << LogEnd;

    info.basicCid = 0;

    stringUpdate();

}

void ssInfo::stringUpdate() {
    if (ev.isGUI()) {
        stringstream displayIt;
        displayIt << "macAddr=" << hex << info.macAddr << endl;
        displayIt << "basicCID=" << dec << info.basicCid;

        displayString().setTagArg("t",0, (displayIt.str()).c_str());
    }
}
