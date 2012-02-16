#ifndef HH_RUNTIME_EXCEPTIONS_HEADER
#define HH_RUNTIME_EXCEPTIONS_HEADER

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <string>
#include <sstream>

#include <HhUnitTestFramework/Exceptions.h>


class HH_CantOpenConfigFile : public HH_Exception
{
public:
    HH_CantOpenConfigFile( const std::string& configFileName )
        : m_configFileName( configFileName )
    {
    }

    virtual std::string AsString() const
    { 
        return "Can't open hammerhead config file \"" + m_configFileName + "\"";
    }

private:
    std::string m_configFileName;
};



class HH_CantOpenInputFile : public HH_Exception
{
public:
    HH_CantOpenInputFile( const std::string& inputFileName )
        : m_inputFileName( inputFileName )
    {
    }

    virtual std::string AsString() const
    { 
        return "Can't open hammerhead unit test input file \"" + m_inputFileName + "\"";
    }

private:
    std::string m_inputFileName;
};



class HH_CantOpenKnownGoodFile : public HH_Exception
{
public:
    HH_CantOpenKnownGoodFile( const std::string& knownGoodFileName )
        : m_knownGoodFileName( knownGoodFileName )
    {
    }

    virtual std::string AsString() const
    { 
        return "Can't open hammerhead unit test known good file \"" + m_knownGoodFileName + "\"";
    }

private:
    std::string m_knownGoodFileName;
};



class HH_MissingNameInConfigFile : public HH_Exception
{
public:
    HH_MissingNameInConfigFile( const std::string& configFileName )
        : m_configFileName( configFileName )
    {
    }

    virtual std::string AsString() const
    { 
        return "Can't find unit test name in hammerhead config file \"" + m_configFileName + "\"";
    }

private:
    std::string m_configFileName;
};



class HH_MissingExePathInConfigFile : public HH_Exception
{
public:
    HH_MissingExePathInConfigFile( const std::string& configFileName )
        : m_configFileName( configFileName )
    {
    }

    virtual std::string AsString() const
    { 
        return "Can't find unit test executable path in hammerhead config file \"" + m_configFileName + "\"";
    }

private:
    std::string m_configFileName;
};


class HH_CantFindUnitTestExecutable : public HH_Exception
{
public:
    HH_CantFindUnitTestExecutable( const std::string& fileName )
        : m_fileName( fileName )
    {
    }

    virtual std::string AsString() const
    { 
        return "Can't find unit test executable \"" + m_fileName + "\"";
    }

private:
    std::string m_fileName;
};

#endif
