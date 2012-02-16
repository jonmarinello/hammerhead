// hh.cpp : Defines the entry point for the Hammerhead console application.
//

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include "stdafx.h"

#include <HhUnitTestFramework/UnitTest.h>
#include <hhruntime/version.h>
#include <hhruntime/runtime.h>
#include <hh/getopt.h>
#include <hh/exceptions.h>

#define RESULT_SUCCESS  (0)
#define RESULT_ERROR    (-1)

void DisplayCopyrightNotice();
void DisplayUsage( const char* const programName );
void DisplayElapsedTime( const CTimeSpan& startTimeSpan, bool verbose );
void DisplayParameters( const HH_Runtime& runtime, bool verbose );
std::string GetIniFile( bool verbose );

class HH_CommandLineNotifier : public HH_Notifier
{
public:
    HH_CommandLineNotifier( bool verbose )
        : m_verbose( verbose )
    {
    }

    virtual void ReportProgressMessage( const std::string& message )
    {
        if ( m_verbose )
        {
            std::cout << message << std::endl;
        }
    }

    virtual void ReportTestResult( bool testPassed )
    {
        std::cout << ( testPassed ? "TEST PASSED" : "TEST FAILED" ) << std::endl;
    }

    virtual bool OverwriteConfigFileCheck( const std::string& configFileName )
    {
        std::cout << "\"" << configFileName << "\"" << " already exists. Overwrite? [y/n] ";
        if ( tolower( ::getc( stdin ) ) != 'y' )
        {
            std::cout << std::endl;
            return true;
        }

        std::cout << std::endl;
        return false;
    }

private:
    bool    m_verbose;
};



int main( int argc, char* argv[] )
{
    DisplayCopyrightNotice();

    std::string configFile = "hh.cfg";
    std::string batchBuildId = "";

    CTimeSpan totalTimeSpan;

    enum RunOption
    {
        ApproveUnitTest,
        ExecuteUnitTests,
        ExecuteUnitTestsInBatchBuildMode,
        GenerateConfigFile,
        ViewUnitTestFailures,
        EditUnitTest
    };

    RunOption runOption = ExecuteUnitTests;
    bool verbose = false;

    try
    {
        for ( ;; )
        {
            int c = getopt( argc, argv, "ac:b:gefv?" );
            if (c == -1)
            {
                break;
            }
     
            switch ( c )
            {
                case 'a':
                    runOption = ApproveUnitTest;
                    break;

                case 'c':
                    configFile = optarg;
                    break;

                case 'b':
                    runOption = ExecuteUnitTestsInBatchBuildMode;
                    batchBuildId = optarg;
                    break;

                case 'g':
                    runOption = GenerateConfigFile;
                    break;

                case 'e':
                    runOption = EditUnitTest;
                    break;

                case 'f':
                    runOption = ViewUnitTestFailures;
                    break;

                case 'v':
                    verbose = true;
                    break;

                case '?':
                    DisplayUsage( argv[0] );
                    return RESULT_SUCCESS;
            }
        }
    }
    catch ( HH_CommandLineError& ex )
    {
        std::cout << ex.AsString() << std::endl;
        std::cout << std::endl;
        DisplayUsage( argv[0] );
        return RESULT_ERROR;
    }

    try
    {
        HH_CommandLineNotifier  commandLineNotifier( verbose );

        switch( runOption )
        {
        case ExecuteUnitTests:
            {
                HH_Runtime  runtime( GetIniFile( verbose ), configFile, commandLineNotifier );
                DisplayParameters( runtime, verbose );
                totalTimeSpan = runtime.ExecuteUnitTest( batchBuildId );
                DisplayElapsedTime( totalTimeSpan, verbose );
            }
            break;

        case ExecuteUnitTestsInBatchBuildMode:
            {
                HH_Runtime  runtime( GetIniFile( verbose ), configFile, commandLineNotifier );
                DisplayParameters( runtime, verbose );
                totalTimeSpan = runtime.ExecuteUnitTest( batchBuildId );
                DisplayElapsedTime( totalTimeSpan, verbose );
            }
            break;

        case ApproveUnitTest:
            {
                HH_Runtime  runtime( GetIniFile( verbose ), configFile, commandLineNotifier );
                DisplayParameters( runtime, verbose );
                runtime.ApproveUnitTest();
            }
            break;

        case GenerateConfigFile:
            HH_Runtime::GenerateConfigFile( commandLineNotifier );
            break;

        case ViewUnitTestFailures:
            {
                HH_Runtime  runtime( GetIniFile( verbose ), configFile, commandLineNotifier );
                DisplayParameters( runtime, verbose );
                runtime.ViewUnitTestFailures();
            }
            break;

        case EditUnitTest:
            {
                HH_Runtime  runtime( GetIniFile( verbose ), configFile, commandLineNotifier );
                DisplayParameters( runtime, verbose );
                runtime.EditDotInFile();
            }
            break;
        }
    }
    catch ( HH_Exception& ex )
    {
        HH_UnitTest::LogException( ex );
        DisplayElapsedTime( totalTimeSpan, verbose );
        return RESULT_ERROR;
    }

    return RESULT_SUCCESS;
}


void DisplayCopyrightNotice()
{
    std::cout << "Hammerhead C++ Unit Testing Framework" << std::endl;
    std::cout << "Release " << HH_VERSION_AS_STRING << " built on " << __DATE__ << std::endl;
    std::cout << "Copyright (c) 2003-2005, Jon Marinello" << std::endl;
    std::cout << std::endl;
}


void DisplayUsage( const char* const programName )
{
    std::cout << "usage: " << programName << " [-agfev] [-c <config file>] [-b <batch build id>]"<< std::endl << std::endl;
    std::cout << "    -a approve unit test" << std::endl;
    std::cout << "    -c <config file> default is hh.cfg" << std::endl;
    std::cout << "    -b <batch build id> execute in batch build mode (execute hhReporter if externalResult defined in config file)" << std::endl;
    std::cout << "    -g generate a default config file (hh.cfg)" << std::endl;
    std::cout << "    -f view unit test failures" << std::endl;
    std::cout << "    -e edit unit test .in file" << std::endl;
    std::cout << "    -v verbose mode" << std::endl;
    std::cout << std::endl;
}


void DisplayElapsedTime( const CTimeSpan& totalTimeSpan, bool verbose )
{
    if ( verbose )
    {
        std::string s = totalTimeSpan.Format( "Elapsed time: %D days, %H hours, %M minutes, %S seconds" );
        std::cout << s << std::endl;
    }
}


void DisplayParameters( const HH_Runtime& runtime, bool verbose )
{
    if ( verbose )
    {
        std::cout << "Config file: \"" + runtime.GetConfigFile() + "\"" << std::endl;
        std::cout << "Name: \"" + runtime.GetName() + "\"" << std::endl;
        std::cout << "ExePath: \"" + runtime.GetExePath() + "\"" << std::endl;
        std::cout << "External Result: \"" + runtime.GetExternalResult() + "\"" << std::endl;
    }
}


std::string GetIniFile( bool verbose )
{
    char modulePath[ _MAX_PATH ];

    if ( !::GetModuleFileName( ::GetModuleHandle( NULL ), modulePath, sizeof modulePath ) )
    {
        throw HH_Win32Error( "::GetModuleFileName() failed", ::GetLastError() );
    }
    *( strrchr( modulePath, '\\' ) + 1 ) = '\0';

    if ( verbose )
    {
        std::cout << "Loading program parameters from \"" << std::string( modulePath ) + "hh.ini\"" << std::endl;
    }

    return std::string( modulePath ) + "hh.ini";
}
