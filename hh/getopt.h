#ifndef _GETOPT_H_
#define _GETOPT_H_

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

extern int      getopt( int nargc, char* const* nargv, const char* ostr );
extern char     *optarg;
extern int      optind, opterr, optopt, optreset;

#endif