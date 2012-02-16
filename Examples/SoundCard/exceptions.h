#ifndef __SOUND_CARD_EXCEPTIONS__
#define __SOUND_CARD_EXCEPTIONS__

/*
 * Copyright (c) 2003, Jon Marinello
 *
 */

#include <string>
#include <sstream>

/**
 *  Base class for all Hammerhead exceptions.
 */
class SC_Exception
{
public:
    /**
     *  Returns a string representation of this exception. Must be
     *  implemented by all derived classes.
     */
    virtual std::string AsString() const = 0;
};



/**
 *  Thrown when the sound card has a general device error.
 */
class SC_DeviceError : public SC_Exception
{
public:
    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        return "Device error on sound card.";
    }
};



/**
 *  Thrown when the file provided is not in a recognized media format.
 */
class SC_InvalidMedia : public SC_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param objectName - the name of the expected object.
     */
    SC_InvalidMedia( const std::string& fileName )
        : m_fileName( fileName )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        std::string message = "'" + m_fileName;
        message += "' in not in a recognized media format.";
        return message;
    }

protected:
    /**
     *  Name of the invalid file.
     */
    std::string m_fileName;
};



/**
 *  Thrown when the file provied is not in a rcognized media format.
 */
class SC_FileNotFound : public SC_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param objectName - the name of the expected object.
     */
    SC_FileNotFound( const std::string& fileName )
        : m_fileName( fileName )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        std::string message = "Can't find '" + m_fileName;
        message += "'.";
        return message;
    }

protected:
    /**
     *  Name of the invalid file.
     */
    std::string m_fileName;
};

#endif
