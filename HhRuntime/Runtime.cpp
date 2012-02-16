/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include "stdafx.h"

#include <HhRuntime/Runtime.h>
#include <HhUnitTestFramework/UnitTest.h>

const char* applicationName = "Hammerhead";


HH_Runtime::HH_Runtime( const std::string& iniFile, const std::string& configFile, HH_Notifier& notifier )
    : m_iniFile( iniFile ),
      m_configFile( configFile ),
      m_notifier( notifier )
{
    LoadConfigFile( configFile );

    m_dotInputFileName =  std::string( ".\\" ) + m_name + ".in";
    m_dotPreprocessedFileName = std::string( ".\\" ) + m_name + ".tmp";
    m_dotOutputFileName = std::string( ".\\" ) + m_name + ".out";
    m_dotKnownGoodFileName = std::string( ".\\" ) + m_name + ".good";

}


void HH_Runtime::ApproveUnitTest()
{
    if ( !::CopyFile( m_dotOutputFileName.c_str(), m_dotKnownGoodFileName.c_str(), FALSE ) )
    {
        std::stringstream message;
        message << "Can't copy \"" << m_dotOutputFileName << "\" to \"" << m_dotKnownGoodFileName << "\"";
        throw HH_Win32Error( message.str(), ::GetLastError() );
    }

    std::stringstream messageStream;
    messageStream << "\"" << m_dotOutputFileName << "\" copied to \""
        << m_dotKnownGoodFileName << "\"" << " -- unit test approved" << std::endl;
    m_notifier.ReportProgressMessage( messageStream.str() );
}



void HH_Runtime::PreprocessInputFile( HH_File& inputFile, HH_File& processedFile )
{
    bool eof = false;

    do
    {
        std::string stringRead = inputFile.GetLine( eof );

        char buffer[10240];
        const char *includeCommand = "@include ";

        strcpy_s( buffer, stringRead.c_str() );
        if ( strncmp( buffer, includeCommand, strlen( includeCommand ) ) == 0 )
        {
            char* pNewLine = strrchr( buffer, '\n' );

            if ( pNewLine != NULL )
            {
                *pNewLine = '\0';
            }

            char* p = &buffer[ strlen( includeCommand ) ];
            while ( p != NULL && *p == ' ' )
            {
                ++p;
            }

            std::string includeFileName = p;

            HH_File inputFile( includeFileName, "r" );

            processedFile.PutLine( std::string( "# " ) + includeCommand + "\"" + includeFileName + "\"\n" );

            PreprocessInputFile( inputFile, processedFile );
        }
        else
        {
            processedFile.PutLine( stringRead );
        }
    }
    while ( !eof );
}



CTimeSpan HH_Runtime::ExecuteUnitTest( const std::string& batchBuildId )
{
    // Save off the start time
    __time64_t startTime;
    _time64( &startTime );
    CTimeSpan startTimeSpan( startTime );

    m_notifier.ReportProgressMessage( "Executing unit test..." );

    if  ( _access( m_exePath.c_str(), 00 ) != 0 )
    {
        throw HH_CantFindUnitTestExecutable( m_exePath );
    }

    if  ( _access( m_dotInputFileName.c_str(), 00 ) != 0 )
    {
        throw HH_CantOpenInputFile( m_dotInputFileName );
    }

    {
        HH_File inputFile( m_dotInputFileName, "r" );
        HH_File processedFile( m_dotPreprocessedFileName, "w" );

        PreprocessInputFile( inputFile, processedFile );
    }

    std::ostringstream commandStream;

    commandStream << m_exePath << " -batch < " << m_dotPreprocessedFileName << " > " << m_dotOutputFileName;
    system( commandStream.str().c_str() );

    VerifyUnitTestResults( batchBuildId );

    if ( _unlink( m_dotPreprocessedFileName.c_str() ) == -1 )
    {
        std::string message = "Can't remove  '";
        message += m_dotPreprocessedFileName;
        message += "'";
        throw HH_ErrnoError( message, errno );
    }

    // Compute the total time for test execution
    __time64_t endTime;
    _time64( &endTime );
    CTimeSpan endTimeSpan( endTime );

    return endTimeSpan - startTimeSpan;
}



void HH_Runtime::VerifyUnitTestResults( const std::string& batchBuildId )
{
    m_notifier.ReportProgressMessage( "Verifing unit test results..." );

    if  ( _access( m_dotKnownGoodFileName.c_str(), 00 ) != 0 )
    {
        throw HH_CantOpenKnownGoodFile( m_dotKnownGoodFileName );
    }

    // Compare the .out and .good files
    HH_File   dotOutputFile( m_dotOutputFileName );
    HH_File   dotKnownGoodFile( m_dotKnownGoodFileName );

    if ( !dotOutputFile.Compare( dotKnownGoodFile ) )
    {
        m_notifier.ReportTestResult( false );
        if ( batchBuildId.length() > 0 && m_externalResult.length() > 0 )
        {
            // Report failure to external system
            ReportResult( "FAILED", batchBuildId );
        }
    }
    else
    {
        m_notifier.ReportTestResult( true );
        if ( batchBuildId.length() > 0 && m_externalResult.length() > 0 )
        {
            // Report success to external system
            ReportResult( "PASSED", batchBuildId );
        }
    }
}



void HH_Runtime::GenerateConfigFile( HH_Notifier& notifier )
{
    std::ofstream   configFileStream;

    const char* defaultConfigFile= "hh.cfg";

    if  ( _access( defaultConfigFile, 00 ) == 0 )
    {
        if ( !notifier.OverwriteConfigFileCheck( defaultConfigFile ) )
        {
            return;
        }
    }

    configFileStream.open( defaultConfigFile );
    if  ( !configFileStream.is_open() )
    {
        throw HH_CantOpenConfigFile( defaultConfigFile );
    }

    configFileStream << "[" << applicationName << "]" << std::endl;
    configFileStream << "# Hammerhead config file " << HH_VERSION_AS_STRING << std::endl;
    configFileStream << std::endl;
    configFileStream << "# This file describes the settings to be used by the unit test system" << std::endl;
    configFileStream << "#" << std::endl;
    configFileStream << "# All text after a hash (#) is considered a comment and will be ignored" << std::endl;
    configFileStream << "# The format is:" << std::endl;
    configFileStream << "#       TAG = value [value,...]" << std::endl;
    configFileStream << "#" << std::endl;
    configFileStream << std::endl;
    configFileStream << "#---------------------------------------------------------------------------" << std::endl;
    configFileStream << "# General configuration options" << std::endl;
    configFileStream << "#---------------------------------------------------------------------------" << std::endl;
    configFileStream << "#" << std::endl;

    configFileStream << "# The \"name\" tag is a single word or a sequence of words that identifies the unit test." << std::endl;
    configFileStream << "name=" << std::endl;
    configFileStream << std::endl;
    configFileStream << std::endl;

    configFileStream << "# The \"exepath\" tag defines the path to the unit test excutable." << std::endl;
    configFileStream << "exepath=" << std::endl;
    configFileStream << std::endl;
    configFileStream << std::endl;

    configFileStream << "# The \"externalResult\" tag defines the external name to report the test result as." << std::endl;
    configFileStream << "# If you define this tag (which can be any arbitrary single token), the framework will" << std::endl;
    configFileStream << "# attempt to report the unit test result to a program called hhReporter that must" << std::endl;
    configFileStream << "# accept three parameters; the unit test name, this external result tag and lastly" << std::endl;
    configFileStream << "# the token PASSED or FAILED. You must supply this program and you may use it to" << std::endl;
    configFileStream << "# report to external systems (like databases) that are used to keep track of unit test." << std::endl;
    configFileStream << "# results." << std::endl;
    configFileStream << "externalResult=" << std::endl;
    configFileStream << std::endl;
    configFileStream << std::endl;

    configFileStream.close();
}



void HH_Runtime::ViewUnitTestFailures()
{
    char diffViewer[1024]; // hack: should be big enough
    ::GetPrivateProfileString( applicationName, "diffviewer", "windiff", diffViewer, sizeof diffViewer, m_iniFile.c_str() );

    std::stringstream command;
    command << "\"" << diffViewer << "\" " << m_dotKnownGoodFileName << " " << m_dotOutputFileName;

    m_notifier.ReportProgressMessage( "Executing: " + command.str() );

    HH_UnitTest::CreateProcess( command.str() );
}



void HH_Runtime::EditDotInFile()
{
    char editor[1024]; // hack: should be big enough
    ::GetPrivateProfileString( applicationName, "editor", "notepad", editor, sizeof editor, m_iniFile.c_str() );

    std::stringstream command;
    command << "\"" << editor << "\" " << m_dotInputFileName;

    m_notifier.ReportProgressMessage( "Executing: " + command.str() );

    HH_UnitTest::CreateProcess( command.str() );
}



void HH_Runtime::LoadConfigFile( std::string configFile )
{
    // Because the profle functions insist on only looking in
    // the Windows directory unless a path is specified we must
    // prepend a "./" if only a file name is provided
    char directory[ _MAX_DIR ];
    ::ZeroMemory( directory, sizeof directory );
    :: _splitpath_s( configFile.c_str(), NULL, 0, directory, sizeof directory, NULL, 0, NULL, 0 );
    if ( *directory == '\0' )
    {
        configFile = std::string( ".\\" ) + configFile;
    }

    char stringBuffer[1024]; // hack: should be big enough

    *stringBuffer = '\0';
    ::GetPrivateProfileString( applicationName, "name", "", stringBuffer, sizeof stringBuffer, configFile.c_str() );
    m_name = stringBuffer;
    if ( m_name.length() == 0 )
    {
        throw HH_MissingNameInConfigFile( configFile );
    }

    *stringBuffer = '\0';
    ::GetPrivateProfileString( applicationName, "exepath", "", stringBuffer, sizeof stringBuffer, configFile.c_str() );
    m_exePath = stringBuffer;
    if ( m_exePath.length() == 0 )
    {
        throw HH_MissingExePathInConfigFile( configFile );
    }

    *stringBuffer = '\0';
    ::GetPrivateProfileString( applicationName, "externalResult", "", stringBuffer, sizeof stringBuffer, configFile.c_str() );
    m_externalResult = stringBuffer;
}



void HH_Runtime::ReportResult( const std::string& result, const std::string& batchBuildId )
{
    std::stringstream command;
    command << "hhReporter" << " " << batchBuildId << " " << m_name << " " << m_externalResult << " " << result;

    m_notifier.ReportProgressMessage( "Executing: " + command.str() );

    ::system( command.str().c_str() );
}
