//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


#ifndef _IPv6EXTENSIONHEADERS_H_
#define _IPv6EXTENSIONHEADERS_H_

#include <list>
#include "INETDefs.h"
#include "IPv6ExtensionHeaders_m.h"


/**
 * Represents an IPv6 Destination Options Header. More info in the IPv6ExtensionHeaders.msg
 * file (and the documentation generated from it).
 */
class INET_API IPv6DestinationOptionsHeader : public IPv6DestinationOptionsHeader_Base
{
  public:
	IPv6DestinationOptionsHeader() : IPv6DestinationOptionsHeader_Base() {};
	IPv6DestinationOptionsHeader(const IPv6DestinationOptionsHeader& other) : IPv6DestinationOptionsHeader_Base() {operator=(other);}
	//IPv6DestinationOptionsHeader& operator=(const IPv6DestinationOptionsHeader& other);
	IPv6DestinationOptionsHeader& operator=(const IPv6DestinationOptionsHeader& other) {IPv6DestinationOptionsHeader_Base::operator=(other); return *this;}

    virtual IPv6DestinationOptionsHeader *dup() const {return new IPv6DestinationOptionsHeader(*this);}
};


/**
 * Represents an IPv6 Routing Header. More info in the IPv6ExtensionHeaders.msg file
 * (and the documentation generated from it).
 */
class INET_API IPv6RoutingHeader : public IPv6RoutingHeader_Base
{
  public:
	  IPv6RoutingHeader() : IPv6RoutingHeader_Base() {};
	  IPv6RoutingHeader(const IPv6RoutingHeader& other) : IPv6RoutingHeader_Base() {operator=(other);}
	  //IPv6RoutingHeader& operator=(const IPv6RoutingHeader& other);
	  IPv6RoutingHeader& operator=(const IPv6RoutingHeader& other) {IPv6RoutingHeader_Base::operator=(other); return *this;}

	  virtual IPv6RoutingHeader *dup() const {return new IPv6RoutingHeader(*this);}
};

#endif

