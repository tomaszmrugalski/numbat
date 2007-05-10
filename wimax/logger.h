/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 * changes: Micha³ Kowalczuk <michal@kowalczuk.eu>
 * changes: Micha³ Kowalczuk <michal@kowalczuk.eu>
 *
 * $Id: Logger.h,v 1.15 2006-11-30 03:21:51 thomson Exp $
 *
 * Released under GNU GPL v2 licence
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <omnetpp.h>
#include "cenvir.h"
#include <iostream>
#include <string>

#define Log(X) SLog(this,X)
#define SLog(OBJ,X) logger::setSimTime(OBJ->simTime()); logger::setLogName(OBJ->fullName()); logger::setEv(&ev); logger :: log##X ()
#define LogEnd logger :: endl

#define LOGMODE_DEFAULT LOGMODE_SIMTIME

namespace logger {

    enum Elogmode {
	LOGMODE_FULL,
	LOGMODE_SHORT,
	LOGMODE_SYSLOG,
	LOGMODE_EVENTLOG, /* unix only */
	LOGMODE_PRECISE,
	LOGMODE_SIMTIME
    };

    using namespace std;
    ostream& logCont();
    ostream& logEmerg();
    ostream& logAlert();
    ostream& logCrit();
    ostream& logError();
    ostream& logWarning();
    ostream& logNotice();
    ostream& logInfo();
    ostream& logDebug();

    void Initialize(const char * file);
    void Terminate();
    void setLogName(string x);
    void setLogLevel(int x);
    void setLogMode(string x);
    void setEv(cEnvir * ev);
    void EchoOff();
    void EchoOn();
    string getLogName();
    int getLogLevel();
    void setSimTime(float x);
    
    ostream & endl (ostream & strum);

}

#endif
