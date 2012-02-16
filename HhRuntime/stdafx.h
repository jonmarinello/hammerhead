// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <process.h>

#if _MSC_VER == 1200            // VC++ 6.0
#include <afx.h>
#define __time64_t time_t
#define _time64 time
#else
#include <atltime.h>
#endif

#include <Windows.h>

#include  <io.h>
#include <iostream>
#include <fstream>
#include <sstream>
