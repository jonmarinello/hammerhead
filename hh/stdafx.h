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

#include <stdio.h>
#include <time.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#if _MSC_VER == 1200            // VC++ 6.0
#include <afx.h>
#else
#include <atltime.h>
#endif
