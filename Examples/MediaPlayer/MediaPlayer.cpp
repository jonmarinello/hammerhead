// MP_MediaPlayer Implementation

#include <stdafx.h>
#include <MediaPlayer/MediaPlayer.h>


MP_MediaPlayer::MP_MediaPlayer()
{
}



MP_MediaPlayer::~MP_MediaPlayer()
{
}



void MP_MediaPlayer::Play( const std::string& fileName )
{
    try
    {
        soundCard.Play( fileName );
    }
    catch ( SC_InvalidMedia& ex )
    {
        // The file to play wasn't in a valid format so log the error and play a canned message
        std::cout << ex.AsString() << std::endl;
        PlayInvalidMediaMessage();
    }
    catch ( SC_FileNotFound& ex )
    {
        // The file to play wasn't found so log the error and play a canned message
        std::cout << ex.AsString() << std::endl;
        PlayFileNotFoundMessage();
    }
}



void MP_MediaPlayer::Stop()
{
    soundCard.Stop();
}



void MP_MediaPlayer::Record()
{
    soundCard.Record();
}



void MP_MediaPlayer::PlayInvalidMediaMessage()
{
    soundCard.Play( "InvalidMediaMessage.wav" );
}



void MP_MediaPlayer::PlayFileNotFoundMessage()
{
    soundCard.Play( "FileNotFound.wav" );
}


int MP_MediaPlayer::GetNumHardwareDevices()
{
    return SC_SoundCard::GetNumHardwareDevices();
}
