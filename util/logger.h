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
#define SLog(OBJ,X) logger :: log##X ((float)OBJ->simTime(), OBJ->fullName(), &ev)
#define LogEnd logger :: endl

#define LOGMODE_DEFAULT LOGMODE_SIMTIME

namespace logger {
    const int Emerg=1;
    const int Alert=2;
    const int Crit=3;
    const int Error=4;
    const int Warning=5;
    const int Notice=6;
    const int Info=7;
    const int Debug=8;

    enum Elogmode {
	LOGMODE_FULL,
	LOGMODE_SHORT,
	LOGMODE_SYSLOG,
	LOGMODE_EVENTLOG, /* unix only */
	LOGMODE_PRECISE,
	LOGMODE_SIMTIME
    };

    using namespace std;
    ostream& logCont(float simtime, const char * name, cEnvir * ev);
    ostream& logEmerg(float simtime, const char * name, cEnvir * ev);
    ostream& logAlert(float simtime, const char * name, cEnvir * ev);
    ostream& logCrit(float simtime, const char * name, cEnvir * ev);
    ostream& logError(float simtime, const char * name, cEnvir * ev);
    ostream& logWarning(float simtime, const char * name, cEnvir * ev);
    ostream& logNotice(float simtime, const char * name, cEnvir * ev);
    ostream& logInfo(float simtime, const char * name, cEnvir * ev);
    ostream& logDebug(float simtime, const char * name, cEnvir * ev);

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
    bool willPrint(int x);
    
    ostream & endl (ostream & strum);

}

#endif
