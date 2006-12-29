/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2006-12-29 01:50:38+0100
 * 
 * @brief  WMax MAC control layer
 * @licence GNU GPLv2
 * 
 */

#include <omnetpp.h>
#include <vector>
#include "wmaxmsg_m.h"

using namespace std;

#ifndef WMAXCTRL_H
#define WMAXCTRL_H

/**************************************************************/
/*** WIMAX CONSTANTS ******************************************/
/**************************************************************/

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class WMaxCtrl : public cSimpleModule
{
public:
    WMaxCtrl();
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

protected:

};

class WMaxCtrlSS : public WMaxCtrl
{
public:
    WMaxCtrlSS();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

class WMaxCtrlBS : public WMaxCtrl
{
public:
    WMaxCtrlBS();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
