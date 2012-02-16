/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <string>
#include <direct.h>
#include <windows.h>

#include <HhUnitTestFramework/UnitTest.h>

HH_UnitTest::HH_UnitTest( bool& variableDataGeneration, bool interactive )
    : m_variableDataGeneration( variableDataGeneration ),
      m_interactive( interactive ),
      m_runComplete( false )
{
    std::boolalpha( std::cout );
    std::boolalpha( std::cin );
    std::boolalpha( m_testCommandParams );
}


HH_UnitTest::~HH_UnitTest()
{
}


void HH_UnitTest::BuiltInTestCommands()
{
    HH_TESTCMD( "System" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, commandLine );

        ::system( commandLine.GetString().c_str() );
    }
    HH_TESTCMD( "CreateProcess" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, executable );

        HH_UnitTest::CreateProcess( executable.GetString() );
    }
    HH_TESTCMD( "Sleep" )
    {
        HH_TESTCMD_PARAM( int, sleepInMS );

        ::Sleep( sleepInMS );
    }
    HH_TESTCMD( "SetVariableData" )
    {
        HH_TESTCMD_PARAM( bool, newValue );

        m_variableDataGeneration = newValue;
    }
    HH_TESTCMD( "GetVariableData" )
    {
        std::cout << m_variableDataGeneration << std::endl;
    }
    HH_TESTCMD( "Exit" )
    {
        m_runComplete = true;
    }
    HH_TESTCMD( "unlink" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, fileName );

        if ( ::_unlink( fileName.GetString().c_str() ) == -1 && errno != ENOENT )
        {
            throw HH_ErrnoError( "::unlink()" );
        }
    }
    HH_TESTCMD( "mkdir" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, directoryName );

        if ( ::_mkdir( directoryName.GetString().c_str() ) == -1 && errno != EEXIST )
        {
            throw HH_ErrnoError( "::mkdir()" );
        }
    }
    HH_TESTCMD( "rmdir" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, directoryName );

        if ( ::_rmdir( directoryName.GetString().c_str() ) == -1 && errno != ENOENT )
        {
            throw HH_ErrnoError( "::rmdir()" );
        }
    }
    HH_TESTCMD( "?" )
    {
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Hammerhead C++ Unit Test Framework Built-in Commands" << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << std::endl;
        std::cout << "System \"command line\" - shells out and executes \"command line\" synchronously using ::system()." << std::endl << std::endl;
        std::cout << "CreateProcess \"executable\" - shells out and executes \"executable\" synchronously using ::CreateProcess()." << std::endl << std::endl;
        std::cout << "Sleep milliseconds - sleeps for some number of milliseconds." << std::endl << std::endl;
        std::cout << "SetVariableData - enables or disables variable data output with \"true\" or \"false\"." << std::endl << std::endl;
        std::cout << "GetVariableData - gets the current value of variable data output." << std::endl << std::endl;
        std::cout << "Exit - exits the unit test." << std::endl << std::endl;
        std::cout << "unlink \"file name\" - deletes the file \"file name\"." << std::endl << std::endl;
        std::cout << "mkdir \"directory name\" - creates the directory \"directory name\"." << std::endl << std::endl;
        std::cout << "rmdir \"directory name\" - removes the directory \"directory name\"." << std::endl << std::endl;
        std::cout << "? - displays help for these built-in commands and also any documented derived commands." << std::endl << std::endl;
        std::cout << "?? - displays help for only documented derived commands." << std::endl << std::endl;

        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "            Documented Derived Commands" << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << std::endl;

        HelpForTestCommands();
    }
    HH_TESTCMD( "??" )
    {
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "            Documented Derived Commands" << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << std::endl;

        HelpForTestCommands();
    }
}


bool HH_UnitTest::TestCommandMatches( std::string testCommand )
{
    if ( _stricmp( testCommand.c_str(), m_testCommand.c_str() ) == 0 )
    {
        m_commandFound = true;
        return true;
    }
    return false;
}


void HH_UnitTest::Run()
{
    while ( std::cin && !m_runComplete )
    {
        try
        {
            if ( m_interactive )
            {
                std::cout << "> ";
            }

            char inputLine[10240];
            std::cin.getline( inputLine, sizeof inputLine, '\n' );

            if ( !m_interactive )
            {
                std::cout << "> " << inputLine;
            }

            if ( strlen( inputLine ) == 0 )
            {
                std::cout << std::endl;
                continue;
            }

            char *p = inputLine;
            while ( *p == ' ' )
            {
                ++p;
            }
            if ( *p == '\0' )
            {
                std::cout << std::endl;
                continue;
            }

            if ( *inputLine == '#' )
            {
                std::cout << std::endl;
                continue;
            }

            m_testCommandParams.clear();
            m_testCommandParams.str( inputLine );
    #if _MSC_VER == 1200            // VC++ 6.0
            m_testCommand.erase();
    #else
            m_testCommand.clear();
    #endif
            m_testCommandParams >> m_testCommand;

            m_commandFound = false;

            std::cout << std::endl;

            TestCommands();
            if ( !m_commandFound )
            {
                BuiltInTestCommands();
            }

            if ( !m_commandFound )
            {
                std::cout << "Command not found." << std::endl;
            }
        }
        catch ( HH_Exception& ex )
        {
            HH_UnitTest::LogException( ex );
        }
    }
}


void HH_UnitTest::LogException( const HH_Exception& ex )
{
    std::cout << ex.AsString() << std::endl << std::endl;
}



void HH_UnitTest::CreateProcess( const std::string& commandLine )
{

    STARTUPINFO startupInfo;
    ::ZeroMemory( &startupInfo, sizeof startupInfo );
    startupInfo.cb = sizeof startupInfo;

    PROCESS_INFORMATION processInformation;
    ::ZeroMemory( &processInformation, sizeof processInformation );

    if ( ::CreateProcess(
            NULL,                           // No module name (use command line)
            const_cast< char* >( commandLine.c_str() ),
            NULL,                           // Process handle not inheritable. 
            NULL,                           // Thread handle not inheritable. 
            FALSE,                          // Set handle inheritance to FALSE
            0,                              // No creation flags
            NULL,                           // Use parent's environment block
            NULL,                           // Use parent's starting directory
            &startupInfo,
            &processInformation ) == 0 )
    {
        throw HH_Win32Error( "::CreateProcess() failed", GetLastError() );
    }

    // Wait until child process exits.
    if ( ::WaitForSingleObject( processInformation.hProcess, INFINITE ) == WAIT_FAILED )
    {
        throw HH_Win32Error( "::WaitForSingleObject() failed", GetLastError() );
    }

    // Close process and thread handles. 
    if ( ::CloseHandle( processInformation.hProcess ) == 0 )
    {
        throw HH_Win32Error( "::CloseHandle() failed", GetLastError() );
    }
    if ( ::CloseHandle( processInformation.hThread ) == 0 )
    {
        throw HH_Win32Error( "::CloseHandle() failed", GetLastError() );
    }
}


void HH_UnitTest::HelpForTestCommands()
{
    std::cout << "No specific command help available for this unit test." << std::endl << std::endl;
}
