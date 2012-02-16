#ifndef HH_UNIT_TEST_FRAMEWORK_EXCEPTIONS_HEADER
#define HH_UNIT_TEST_FRAMEWORK_EXCEPTIONS_HEADER

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <string>
#include <sstream>

/**
 *  Base class for all Hammerhead exceptions.
 */
class HH_Exception
{
public:
    /**
     *  Returns a string representation of this exception. Must be
     *  implemented by all derived classes.
     */
    virtual std::string AsString() const = 0;
};



/**
 *  Thrown when there isn't any data to parse and a quoted
 *  string was expected to feed a multi-token string.
 */
class HH_EmptyString : public HH_Exception
{
public:
    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        return "Can't find any tokens in multi-token string.";
    }
};



/**
 *  Thrown when there isn't a closing quote to feed a
 *  multi-token string.
 */
class HH_MissingEndQuote : public HH_Exception
{
public:
    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        return "Can't find closing quote in multi-token string.";
    }
};



/**
 *  Thrown when there isn't a character following the escape '\'
 *  charcter to feed a multi-token string.
 */
class HH_MissingEscapeCaracter : public HH_Exception
{
public:
    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        return "Can't find character to escape in multi-token string.";
    }
};



/**
 *  Thrown when the character following the escape '\'
 *  charcter isn't allowed to feed a multi-token string.
 *  Only '\' and '"' are allowed to be escaped.
 */
class HH_IllegalEscapeSequence : public HH_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param escapedCharacter - [in] the illegal escaped character encountered.
     */
    HH_IllegalEscapeSequence( char escapedCharacter )
        : m_escapedCharacter( escapedCharacter )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        char escapedCharacterAsString[2] = {0};

        escapedCharacterAsString[0] = m_escapedCharacter;
        std::string message = "Can't escape '" + std::string( escapedCharacterAsString ) +
            std::string ( "' in multi-token string." );
        return message;
    }

private:
    /**
     *  Name of the illegal escaped character encountered.
     */
    char m_escapedCharacter;
};



/**
 *  Thrown when the expected command paramter was found in the
 *  input stream.
 */
class HH_MissingCommandParameter : public HH_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param parameterType - [in] the type of the expected parameter name.
     *  @param parameterName - [in] the name of the expected parameter name.
     */
    HH_MissingCommandParameter( const std::string& parameterType, const std::string& parameterName )
        : m_parameterType( parameterType ),
          m_parameterName( parameterName )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        std::string message = "Missing parameter: "  + m_parameterType;
        message += " ";
        message += m_parameterName;
        return message;
    }

private:
    /**
     *  Type of the expected parameter.
     */
    std::string m_parameterType;

    /**
     *  Name of the expected parameter.
     */
    std::string m_parameterName;
};



/**
 *  Thrown when the pointer to the object passed to HH_RETURN_IF_NOT_CREATED()
 *  is NULL.
 */
class HH_ObjectNotYetCreated : public HH_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param objectName - [in] the name of the expected object.
     */
    HH_ObjectNotYetCreated( const std::string& objectName )
        : m_objectName( objectName )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        std::string message = m_objectName;
        message += " not yet created.";
        return message;
    }

private:
    /**
     *  Name of the expected object.
     */
    std::string m_objectName;
};



/**
 *  Thrown when a Win32 type function failed.
 */
class HH_Win32Error : public HH_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param message      - [in] the message (usually the name of the function).
     *  @param win32Error   - [in] the value of the last Win32 error (usually ::GetLastError()).
     */
    HH_Win32Error( const std::string& message, int win32Error )
        : m_message( message ),
          m_win32Error( win32Error )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    { 
        std::stringstream stream;
        stream << m_message << ", error (" << m_win32Error
                << ") " << ErrorNumberAsText( m_win32Error );
        return stream.str();
    }

    /**
     *  Returns the Win32 error associated with this exception.
     */
    int GetWin32Error() const { return m_win32Error; }

private:
    /**
     *  The message.
     */
    std::string m_message;

    /**
     *  The Win32 error number.
     */
    int         m_win32Error;

    /**
     *  Converts a Win32 error number into a string.
     */
    static std::string ErrorNumberAsText( int win32Error );
};



/**
 *  Thrown when a errno type function failed.
 */
class HH_ErrnoError : public HH_Exception
{
public:
    /**
     *  Constructor
     *
     *  @param message      - [in] the message (usually the name of the function).
     *  @param errorNumber  - [in] the value of the last error.
     */
    HH_ErrnoError( const std::string& message, int errorNumber = errno )
        : m_message( message ),
          m_errorNumber( errorNumber )
    {
    }

    /**
     *  Returns a string representation of this exception.
     */
    virtual std::string AsString() const
    {
        std::stringstream stream;
		char buffer[1024];
        stream << m_message << ", errno (" << m_errorNumber << ") " << strerror_s( buffer, sizeof buffer - 1, m_errorNumber );//_sys_errlist[ m_errorNumber ];
        return stream.str();
    }

    /**
     *  Returns the errno associated with this exception.
     */
    int GetErrno() const { return m_errorNumber; }

private:
    /**
     *  The message.
     */
    std::string m_message;

    /**
     *  The errno error number.
     */
    int         m_errorNumber;
};

#endif
