#ifndef HH_UNIT_TEST_HEADER
#define HH_UNIT_TEST_HEADER

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <string>
#include <sstream>
#include <iostream>

#include <HhUnitTestFramework/Exceptions.h>
#include <HhUnitTestFramework/MultiTokenString.h>

/**
 *  HH_UnitTest is the abstract base class that all your unit tests
 *  should be derived from.
 *
 *  Here is the implementation of the class UtMediaPlayer in utMediaPlayer.cpp:
 *
 *  @include utMediaPlayerClass.inc
 *
 *  You must implement the TestCommands() method in your derived class
 *  and use the HH_TESTCMD() and HH_TESTCMD_PARAM() macros to define your test
 *  commands and thier respective parameters.
 *
 *  Here is the implementation of TestCommands() in utMediaPlayer.cpp:
 *
 *  @include utMediaPlayerDerivedCommands.inc
 *
 *  @author Copyright (c) 2003-2005, Jon Marinello
 */
class HH_UnitTest
{
public:
    /**
     *  Constructs an instance of this class.
     *
     *  @param [in,out] variableDataGeneration - used to control variable data suppression.
     *  @param [in] interactive - interactive mode enables command prompt and suppresses command echo.
     */
    HH_UnitTest( bool& variableDataGeneration, bool interactive );

    /**
     *  Destroys an instance of this class.
     */
    virtual ~HH_UnitTest();

    /**
     *  Kicks off the unit test.
     */
    void Run();

    /**
     *  Logs an exception as a string to stdout.
     *
     *  @param [in] ex - exception to log
     */
    static void LogException( const HH_Exception& ex );

    /**
     *  Creates a process.
     *
     *  @param [in] commandLine - The complete command line
     */
    static void CreateProcess( const std::string& commandLine );

protected:
    /**
     *  Implement your test commands in your derived class's implementation of this
     *  method. Use the HH_TESTCMD() and HH_TESTCMD_PARAM() macros for this.
     */
    virtual void TestCommands() = 0;

    /**
     *  Optionally implement help for your test commands in your derived class's
     *  implementation of this method.
     *
     *  Implement this method ONLY if you want to document your derived test commands.
     *  To display help for a command just stream the command name, parameter names and
     *  a brief description to std::cout.
     *
     *  If you don't implement this method in your derieved class, you will receive a message
     *  to this effect when help is invoked with '?' and '??'.
     */
    virtual void HelpForTestCommands();

    /**
     *  Implements the built-in commands:
     *
     *  -# System "command line" - shells out and executes "command line".
     *  -# Sleep milliseconds - sleeps for some number of milliseconds.
     *  -# SetVariableData - sets the current value of variable data output.
     *  -# GetVariableData - displays the current value of variable data output.
     *  -# Exit - exits the unit test.
     *  -# unlink "file name" - deletes the file "file name".
     *  -# mkdir "directory name" - creates the directory "directory name".
     *  -# rmdir "directory name" - removes the directory "directory name".
     *  -# ? - displays help for these built-in commands and also any documented derived commands.
     *  -# ?? - displays help for only documented derived commands.
     */
    void BuiltInTestCommands();

    /**
     *  Checks to see if the command parsed matches the current command using
     *  a case insensitive comparison.
     *
     *  @param [in] testCommand - The command to check
     *  @return true if the command matches; otherwise, false
     */
    bool TestCommandMatches( std::string testCommand );

    /**
     *  Holds the currently parsed test command arguments.
     */
    std::istringstream  m_testCommandParams;

private:
    /**
     *  Holds the currently parsed test command.
     */
    std::string         m_testCommand;

    /**
     *  If true a command match has been found.
     */
    bool                m_commandFound;

    /**
     *  If true the test is over and we can exit.
     */
    bool                m_runComplete;

    /**
     *  Internal reference to the consumer's variable data generation variable.
     */
    bool&               m_variableDataGeneration;

    /**
     *  Interactive mode.
     */
    bool                m_interactive;

    HH_UnitTest( const HH_UnitTest& );            // not allowed
    HH_UnitTest& operator=( const HH_UnitTest& ); // not allowed
};

/**
 *  Defines a test command.
 */
#define HH_TESTCMD( testCommand )                                               \
    if ( TestCommandMatches( testCommand ) )

/**
 *  Defines a test command parameter.
 */
#define HH_TESTCMD_PARAM( paramType, paramName )                                \
    paramType paramName;                                                        \
    try                                                                         \
    {                                                                           \
        m_testCommandParams >> paramName;                                       \
        if ( !m_testCommandParams )                                             \
        {                                                                       \
            throw HH_MissingCommandParameter( #paramType, #paramName );         \
        }                                                                       \
    }                                                                           \
    catch ( HH_EmptyString& )                                                   \
    {                                                                           \
        throw HH_MissingCommandParameter( #paramType, #paramName );             \
    }

/**
 *  Use to avoid crashes by ensuring any pointers you have to objects
 *  are not NULL.
 */
#define HH_OBJECT_MUST_EXIST( pObject, objectName )                             \
    if ( pObject == NULL )                                                      \
    {                                                                           \
        throw HH_ObjectNotYetCreated( #objectName );                            \
    }

#endif
