/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include "stdafx.h"

#include <hh/getopt.h>
#include <hh/exceptions.h>

#pragma warning( disable : 4706 ) // turn off this warning in this old code

int             opterr = 1,     /* if error message should be printed */
                optind = 1,     /* index into parent argv vector */
                optopt,         /* character checked for validity */
                optreset;       /* reset getopt */
char*           optarg;         /* argument associated with option */
char            EMSG[] = "";

#define BADCH   ( int )'?'
#define BADARG  ( int )':'

int getopt( int nargc, char* const* nargv, const char* ostr )
{
    static char    *place = EMSG;           /* option letter processing */
    char           *oli;                    /* option letter list index */

    if ( optreset || !*place )              /* update scanning pointer */
    {
        optreset = 0;
        if ( optind >= nargc || *( place = nargv[ optind ] ) != '-' )
        {
            place = EMSG;
            return -1;
        }
        if ( place[1] && *++place == '-' )  /* found "--" */
        {
            ++optind;
            place = EMSG;
            return -1;
        }
    }                                       /* option letter okay? */
    if ( ( optopt = ( int )*place++ ) == ( int )':' ||
        !( oli = const_cast<char *>( strchr( ostr, optopt ) ) ) )
    {
        /*
         * if the user didn't specify '-' as an option,
         * assume it means -1.
         */
        if ( optopt == ( int )'-' )
        {
            return -1;
        }
        if (!*place)
        {
            ++optind;
        }
        if ( opterr && *ostr != ':' )
        {
            throw HH_IllegalCommandLineOption( nargv[0], optopt );
        }
        return BADCH;
    }
    if ( *++oli != ':' )                    /* don't need argument */
    {
        optarg = NULL;
        if ( !*place )
        {
            ++optind;
        }
    }
    else                                    /* need an argument */
    {
        if ( *place )                       /* no white space */
        {
            optarg = place;
        }
        else if ( nargc <= ++optind )       /* no arg */
        {
            place = EMSG;
            if ( *ostr == ':')
            {
                return BADARG;
            }
            if ( opterr )
            {
                throw HH_CommandLineOptionMissingArgument( nargv[0], optopt );
            }
            return BADCH;
        }
        else                                /* white space */
        {
           optarg = nargv[ optind ];
        }
        place = EMSG;
        ++optind;
    }
    return optopt;                          /* dump back option letter */
}
