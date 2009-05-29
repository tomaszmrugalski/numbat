//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#ifndef __IPv6CONTROLINFO_H
#define __IPv6CONTROLINFO_H

#include "IPv6ControlInfo_m.h"

class IPv6Datagram;

class INET_API IPv6ControlInfo : public IPv6ControlInfo_Base
{
  protected:
    IPv6Datagram *dgram;

    // 19.10.07 - CB
    typedef std::vector<IPv6ExtensionHeader*> ExtensionHeaders;
    ExtensionHeaders extensionHeaders;

  public:
    IPv6ControlInfo() : IPv6ControlInfo_Base() {dgram=NULL;}
    virtual ~IPv6ControlInfo();
    IPv6ControlInfo(const IPv6ControlInfo& other) : IPv6ControlInfo_Base() {dgram=NULL; operator=(other);}
    IPv6ControlInfo& operator=(const IPv6ControlInfo& other) {IPv6ControlInfo_Base::operator=(other); return *this;}

    virtual void setOrigDatagram(IPv6Datagram *d);
    virtual IPv6Datagram *removeOrigDatagram();
    
    // 19.10.07 - CB
    /**
     * Returns the number of extension headers in this datagram
     */
    virtual unsigned int extensionHeaderArraySize() const;

    /**
     * Returns the kth extension header in this datagram
     */
    virtual IPv6ExtensionHeader* extensionHeader(unsigned int k);

    /**
     * Adds an extension header to the datagram, at the given position.
     * The default (atPos==-1) is to add the header at the end.
     */
    virtual void addExtensionHeader(IPv6ExtensionHeader* eh, int atPos=-1);
    
    /**
     * From IPv6ControlInfo_Base: overloaded to disallow it's usage. 
     */
    //void setExtHeaders(unsigned int k, const IPv6ExtensionHeader& extHeaders_var);
};

#endif


