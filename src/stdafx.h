/* 
Copyright (C) 2011-2016 Robert DeSantis
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


// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define NOMINMAX

#include "targetver.h"

#include <afxwin.h>
#include <stdio.h>
#include <tchar.h>
#include <stdint.h>
#include <iostream>
#include <conio.h>
#include <atlstr.h>
#include <shlobj.h> 
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <iterator>
#include <exception>
#include <memory>
#include <limits>
#include <afxmt.h>
#include <Mmdeviceapi.h>
#include <Audioclient.h>
#include <EndpointVolume.h> 
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

#define COLOR_SUPPORT

#include "StudioTypes.h"
#include "ColorStrobe.h"
#include "BPMRating.h"
#include "StudioException.h"
#include "Event.h"
#include "EventBus.h"
#include "EventBusListener.h"
