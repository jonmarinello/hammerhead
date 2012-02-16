#ifndef HH_EXCEPTIONS_HEADER
#define HH_EXCEPTIONS_HEADER

/*
 * Copyright (c) 2003, Jon Marinello
 *
 */

#include "../HHRuntime/exceptions.h"

class HH_CommandLineError : public HH_Exception
{
public:
    HH_CommandLineError( const std::string& programName, int option )
        : _programName( programName ),
          _option( option )
    {
    }

protected:
    std::string _programName;
    int _option;
};

class HH_IllegalCommandLineOption : public HH_CommandLineError
{
public:
    HH_IllegalCommandLineOption( const std::string& programName, int option )
        : HH_CommandLineError( programName, option )
    {
    }

    virtual std::string AsString() const
    { 
        std::stringstream stream;

        stream << "Illegal command line option '" << (char)_option << "'";
        return  stream.str();
    }
};


class HH_CommandLineOptionMissingArgument : public HH_CommandLineError
{
public:
    HH_CommandLineOptionMissingArgument( const std::string& programName, int option )
        : HH_CommandLineError( programName, option )
    {
    }

    virtual std::string AsString() const
    { 
        std::stringstream stream;

        stream << "Command line option '" << (char)_option << "' is missing required argument";
        return  stream.str();
    }
};

#endif
