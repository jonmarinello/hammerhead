// utMediaPlayer Implementation

#include <stdafx.h>

#include <HhUnitTestFramework/UnitTest.h>
#include <MediaPlayer/MediaPlayer.h>


// These globals allow control of the SoundCard stub
extern int numHarwareDevices;
extern std::string exceptionToThrow;


// This is the unit test for the Media Player - the class under test
class UtMediaPlayer : public HH_UnitTest
{
public:
    UtMediaPlayer( bool& variableDataGeneration, bool interactive )
        : HH_UnitTest( variableDataGeneration, interactive )
    {
    }

    ~UtMediaPlayer()
    {
    }

protected:
    void TestCommands();
    void HelpForTestCommands();

private:
    std::auto_ptr< MP_MediaPlayer >   m_pMediaPlayer;
};


void UtMediaPlayer::HelpForTestCommands()
{
    std::cout << "create - creates a new media player." << std::endl << std::endl;
    std::cout << "play - calls Play( \"<file name>\" )." << std::endl << std::endl;
    std::cout << "record - calls Record()." << std::endl << std::endl;
    std::cout << "stop - calls Stop()." << std::endl << std::endl;
    std::cout << "getNumHardwareDevices - calls GetNumHardwareDevices()." << std::endl << std::endl;
    std::cout << "setNumHardwareDevices <nextNumHarwareDevices> - controls the SoundCard::GetNumHardwareDevices() stub." << std::endl << std::endl;
    std::cout << "setExceptionToThrow <exception name> - controls throwing exceptions in the SoundCard stub." << std::endl;
    std::cout << "    where <exception name> must be:" << std::endl;
    std::cout << "        - \"\"" << std::endl;
    std::cout << "        - SC_DeviceError" << std::endl;
    std::cout << "        - SC_InvalidMedia" << std::endl;
    std::cout << "        - SC_FileNotFound" << std::endl;
}


void UtMediaPlayer::TestCommands()
{
    try
    {
        HH_TESTCMD( "create" )
        {
#pragma warning( push )
#pragma warning( disable : 4239 )
            m_pMediaPlayer = ( std::auto_ptr< MP_MediaPlayer > )new MP_MediaPlayer();
#pragma warning( pop )
        }
        HH_TESTCMD( "play" )
        {
            HH_TESTCMD_PARAM( HH_MultiTokenString, fileName );
            HH_OBJECT_MUST_EXIST( m_pMediaPlayer.get(), "MediaPlayer" );

            m_pMediaPlayer->Play( fileName.GetString().c_str() );
        }
        HH_TESTCMD( "record" )
        {
            HH_OBJECT_MUST_EXIST( m_pMediaPlayer.get(), "MediaPlayer" );

            m_pMediaPlayer->Record();
        }
        HH_TESTCMD( "stop" )
        {
            HH_OBJECT_MUST_EXIST( m_pMediaPlayer.get(), "MediaPlayer" );

            m_pMediaPlayer->Stop();
        }
        HH_TESTCMD( "getNumHardwareDevices" )
        {
            std::cout << "GetNumHardwareDevices() returned " << SC_SoundCard::GetNumHardwareDevices() << std::endl;
        }
        HH_TESTCMD( "setNumHardwareDevices" )
        {
            HH_TESTCMD_PARAM( int, nextNumHarwareDevices );

            numHarwareDevices = nextNumHarwareDevices;
        }
        HH_TESTCMD( "setExceptionToThrow" )
        {
            HH_TESTCMD_PARAM( std::string, nextExceptionToThrow );

            exceptionToThrow = nextExceptionToThrow;
        }
    }
    catch ( SC_Exception& ex )
    {
        std::cout << ex.AsString() << std::endl;
    }
}



void main( int argc, char*[] )
{
    bool variableDataGeneration = true;
    UtMediaPlayer utMediaPlayer( variableDataGeneration, argc == 1 );
    utMediaPlayer.Run();
}
