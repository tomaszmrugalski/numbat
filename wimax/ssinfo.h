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

#include <stdint.h>
#include <omnetpp.h>
#include <string>
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
};

ostream & operator<<(ostream & strum, SSInfo_t &ss);

#endif
