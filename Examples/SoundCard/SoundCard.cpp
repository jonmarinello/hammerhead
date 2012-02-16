// SC_SoundCard Implementation

#include <stdafx.h>
#include "SoundCard.h"

SC_SoundCard::SC_SoundCard()
{
}


SC_SoundCard::~SC_SoundCard()
{
}



bool SC_SoundCard::IsBusy() const
{
    return false;// Since this isn't real
}



void SC_SoundCard::Play( const std::string& /* fileName */ )
{
    return;     // Since this isn't real
}


int SC_SoundCard::TimeLeftAsMS() const
{
    return 0;   // Since this isn't real
}


void SC_SoundCard::Stop()
{
    return;     // Since this isn't real
}


void SC_SoundCard::Record()
{
    return;     // Since this isn't real
}


int SC_SoundCard::GetNumHardwareDevices()
{
    return 0;   // Since this isn't real
}
