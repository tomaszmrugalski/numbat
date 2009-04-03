/**
 * @file   ssinfo.h
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-06-30 21:01:52+0200
 * 
 * @brief  SS parameters
 * @licence GNU GPLv2
 * 
 */

#ifndef SSINFO_H
#define SSINFO_H

#include <omnetpp.h>
#include <string>
#include "Portable.h"
#include "hoinfo.h"

using namespace std;

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/
typedef struct SSInfo_s {
    uint64_t macAddr;
    uint16_t basicCid;

    string getMac();

    // used on BS-side only
    struct {
      uint16_t cid;
    } sf[32];
    uint16_t sfCnt;

} SSInfo_t;

/**************************************************************/
/*** UTIL FUNTIONS ********************************************/
/**************************************************************/
string MacToString(uint64_t mac);

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class ssInfo : public cSimpleModule {
public:
    SSInfo_t info;
    HoInfo_t hoInfo;
    void stringUpdate();

    void addEventListener(cModule * module);
    void delEventListener(cModule * module);
    void sendEvent(cMessage * msg);

protected:
    virtual void initialize();

private:
    list<cModule*> EventListenersLst;
    string getMsgName(cMessage * msg);

    /* stats */
    void updateStats(cMessage * msg);
    simtime_t  hoPrep;
    simtime_t  hoReentry;
    simtime_t  hoReconf;
    simtime_t  hoLackOfComm;

    cOutVector hoPrepVector;    /* HO (preparation phase) time */
    cOutVector hoReentryVector; /* HO (reentry L2 phase) time */
    cOutVector hoReconfVector;  /* HO (L3 reconfiguration) time */
    cOutVector hoLackOfCommVector; /* HO (lack of communication caps) time */
};

ostream & operator<<(ostream & strum, SSInfo_t &ss);

#endif
