#ifndef _SOUNDCARD_H_
#define _SOUNDCARD_H_

/*
 * Copyright (c) 2003, Jon Marinello
 *
 */

#include <string>

#include <SoundCard/Exceptions.h>

/**
 *  SC_SoundCard wraps a sound card.
 *
 *  This implementation would normally talk to the real sound card but
 *  as this class isn't real we'll skip that. But if it was real it would
 *  provide a nice object oriented based wrapper around the real hardware.
 *
 *  In this example this class is not under test but will instead be stubbed
 *  to allow us to completely test the MediaPlayer class.
 *
 *  @author Copyright (c) 2003, Jon Marinello
 */
class SC_SoundCard
{
public:
	/**
	 * Constructs a sound card.
	 */
    SC_SoundCard();

	/**
	 * Destroys a sound card.
	 */
    ~SC_SoundCard();

	/**
	 * Reports if the sound card is busy.
     *
     * @exception SC_DeviceError
	 */
    bool IsBusy() const;

	/**
	 * @param fileName - the file to play
	 * 
	 * Plays the media file.
     *
     * @exception SC_DeviceError, SC_InvalidMedia, SC_FileNotFound
	 */
    void Play( const std::string& fileName );

	/**
	 * Returns the number of milliseconds left to play.
	 */
    int TimeLeftAsMS() const;

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
    
private:
    SC_SoundCard( const SC_SoundCard& );            // not allowed
    SC_SoundCard& operator=( const SC_SoundCard& ); // not allowed
};

#endif
