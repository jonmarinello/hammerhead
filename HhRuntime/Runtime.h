#ifndef HAMMERHEAD_RUNTIME_HEADER
#define HAMMERHEAD_RUNTIME_HEADER

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <HhRuntime/Version.h>
#include <HhRuntime/exceptions.h>
#include <HhRuntime/File.h>

class HH_Notifier
{
public:
    virtual void ReportProgressMessage( const std::string& message ) = 0;
    virtual void ReportTestResult( bool testPassed ) = 0;
    virtual bool OverwriteConfigFileCheck( const std::string& configFileName ) = 0;
};

/**
 *  HH_Runtime is the runtime data model used by the Hammerhead C++ Unit Test controller.
 *
 *  @author Jon Marinello
 */
class HH_Runtime
{
public:
    HH_Runtime( const std::string& iniFile, const std::string& configFile, HH_Notifier& notifier );

    virtual ~HH_Runtime()
    {
    }

    void ApproveUnitTest();

    CTimeSpan ExecuteUnitTest( const std::string& batchBuildId );

    static void GenerateConfigFile( HH_Notifier& notifier );

    void ViewUnitTestFailures();

    void EditDotInFile();

    std::string GetIniFile() const { return m_iniFile; }

    std::string GetConfigFile() const { return m_configFile; }

    std::string GetName() const { return m_name; }

    std::string GetExePath() const { return m_exePath; }

    std::string GetExternalResult() const { return m_externalResult; }

    std::string GetInputFileName() const { return m_dotInputFileName; }

    std::string GetPreprocessedFileName() const { return m_dotPreprocessedFileName; }

    std::string GetKnownGoodFileName() const { return m_dotKnownGoodFileName; }

    std::string GetOutputFileName() const { return m_dotOutputFileName; }

    void PreprocessInputFile( HH_File& inputFile, HH_File& processedFile );

private:
    void VerifyUnitTestResults( const std::string& batchBuildId );

    void LoadConfigFile( std::string configFile );

    void ReportResult( const std::string& result, const std::string& batchBuildId );

    std::string     m_iniFile;
    std::string     m_configFile;
    HH_Notifier&    m_notifier;

    std::string     m_dotInputFileName;
    std::string     m_dotPreprocessedFileName;
    std::string     m_dotKnownGoodFileName;
    std::string     m_dotOutputFileName;

    std::string     m_name;
    std::string     m_exePath;
    std::string     m_externalResult;

    HH_Runtime( const HH_Runtime& );                // not allowed
    HH_Runtime& operator=( const HH_Runtime& );     // not allowed
};

#endif
