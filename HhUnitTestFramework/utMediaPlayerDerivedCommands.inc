void UtMediaPlayer::TestCommands()
{
    try
    {
        HH_TESTCMD( "create" )
        {
            m_pMediaPlayer = ( std::auto_ptr< MP_MediaPlayer > )new MP_MediaPlayer();
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
