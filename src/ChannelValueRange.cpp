/* 
Copyright (C) 2011,2012 Robert DeSantis
hopluvr at gmail dot com

This file is part of DMX Studio.
 
DMX Studio is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.
 
DMX Studio is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
License for more details.
 
You should have received a copy of the GNU General Public License
along with DMX Studio; see the file _COPYING.txt.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA.
*/


#include "ChannelValueRange.h"

// ----------------------------------------------------------------------------
//
ChannelValueRange::ChannelValueRange( BYTE start, BYTE end, const char *name, int extra ) :
    m_start( start ),
    m_end( end ),
    m_name( name ),
    m_extra( extra )
{
}

// ----------------------------------------------------------------------------
//
ChannelValueRange::~ChannelValueRange(void)
{
}
