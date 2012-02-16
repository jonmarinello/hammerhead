// SC_SoundCard Stub

#include <stdafx.h>
#include <iostream>

#include <SoundCard/SoundCard.h>

// This is a stub of the SC_SoundCard Class

int numHarwareDevices = 0;
std::string exceptionToThrow = "";

static void ThrowExceptionIfNeeded( const std::string& fileName )
{
    if ( exceptionToThrow == "" )
    {
        // do nothing
    }
    else if ( exceptionToThrow == "SC_DeviceError" )
    {
        exceptionToThrow = "";
        throw SC_DeviceError();
    }
    else if ( exceptionToThrow == "SC_InvalidMedia" && fileName.length() > 0 )
    {
        exceptionToThrow = "";
        throw SC_InvalidMedia( fileName );
    }
    else if ( exceptionToThrow == "SC_FileNotFound" && fileName.length() > 0 )
    {
        exceptionToThrow = "";
        throw SC_FileNotFound( fileName );
    }
    else
    {
        std::cout << "Invalid exception " << exceptionToThrow << " encountered in unit test input." << std::endl;
        exceptionToThrow = "";
    }
}


SC_SoundCard::SC_SoundCard()
{
    // Stream out that this was called
    std::cout << "SC_SoundCard::SC_SoundCard() called." << std::endl;
}



SC_SoundCard::~SC_SoundCard()
{
    // Stream out that this was called
    std::cout << "~SC_SoundCard() called." << std::endl;
}



void SC_SoundCard::Play( const std::string& fileName )
{
    // Stream out that this was called and all the parameters
    std::cout   << "SC_SoundCard::Play() called with \"" << fileName << "\"."
                << std::endl;

    ThrowExceptionIfNeeded( fileName );
}



void SC_SoundCard::Stop()
{
    std::cout << "SC_SoundCard::Stop() called." << std::endl;

    ThrowExceptionIfNeeded( "" );
}



void SC_SoundCard::Record()
{
    std::cout << "SC_SoundCard::Record() called." << std::endl;

    ThrowExceptionIfNeeded( "" );
}



int SC_SoundCard::GetNumHardwareDevices()
{
    return numHarwareDevices;
}
