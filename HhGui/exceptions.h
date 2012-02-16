#ifndef HH_GUI_EXCEPTIONS_HEADER
#define HH_GUI_EXCEPTIONS_HEADER

/*
 * Copyright (c) 2003, Jon Marinello
 *
 */

#include <string>
#include <sstream>

#include <HhUnitTestFramework/Exceptions.h>


class HH_ShellCallFailed : public HH_Exception
{
public:
    HH_ShellCallFailed( const std::string& function )
        : _function( function )
    {
    }

    virtual std::string AsString() const
    { 
        return "Shell function " + _function + " failed.";
    }

private:
    std::string _function;
};

#endif
