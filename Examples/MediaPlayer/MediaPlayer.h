#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

#include <string>
#include <SoundCard/SoundCard.h>

// The MP_MediaPlayer Class
class MP_MediaPlayer
{
public:
	/**
	 * Constructs a sound card.
	 */
    MP_MediaPlayer();

	/**
	 * Destroys a sound card.
	 */
    ~MP_MediaPlayer();

	/**
	 * @param fileName - the file to play
	 * 
	 * Plays the media file.
     *
     * @exception SC_DeviceError, SC_InvalidMedia, SC_FileNotFound
	 */
    void Play( const std::string& fileName );

    /**
	 * Stops the current play or record in progress. If the media player
	 * isn't busy, calling this method has no effect. 
     *
     * @exception SC_DeviceError
	 */
    void Stop();

	/**
	 * Records sounds using the sound card hardware.
     *
     * @exception SC_DeviceError
	 */
    void Record();

	/**
	 * Returns the number of sound cards installed..
	 */
    static int GetNumHardwareDevices();

protected:
	/**
	 * @param fileName - the file to play
	 * 
	 * Plays the standard invalid media message.
     *
     * @exception SC_DeviceError, SC_InvalidMedia, SC_FileNotFound
	 */
    void PlayInvalidMediaMessage();

	/**
	 * @param fileName - the file to play
	 * 
	 * Plays the standard file not found message.
     *
     * @exception SC_DeviceError, SC_InvalidMedia, SC_FileNotFound
	 */
    void PlayFileNotFoundMessage();

    SC_SoundCard  soundCard;
    
private:
    MP_MediaPlayer( const MP_MediaPlayer& );            // not allowed
    MP_MediaPlayer& operator=( const MP_MediaPlayer& ); // not allowed
};

#endif
