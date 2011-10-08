//
// Copyright (C) 2009 Thomas Reschka
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


#ifndef __INET_DUPLICATESGENERATOR_H
#define __INET_DUPLICATESGENERATOR_H

#include <omnetpp.h>
#include "INETDefs.h"
#include <vector>


/**
 * Duplicates generator.
 */
class INET_API DuplicatesGenerator : public cSimpleModule
{
  protected:
    unsigned int numPackets;
	unsigned int numDuplicated;
	bool generateFurtherDuplicates;
	std::vector<unsigned int> duplicatesVector;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void parseVector(const char *vector);
    virtual void finish();
};

#endif
