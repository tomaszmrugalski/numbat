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

using namespace std;

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

typedef struct SSInfo_s {
    uint64_t macAddr;
    uint16_t basicCid;

    string getMac();
} SSInfo_t;

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class ssInfo : public cSimpleModule {
public:
    SSInfo_s info;
    void stringUpdate();

protected:
    virtual void initialize();

};

ostream & operator<<(ostream & strum, SSInfo_t &ss);

#endif
