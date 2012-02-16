/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <Windows.h>
#include <HhUnitTestFramework/Exceptions.h>

/*
 * private HH_SafeLocalMemory class
 */
class HH_SafeLocalMemory
{
public:
    HH_SafeLocalMemory()
        : _pLocalMemory( 0 )
    {
    }

    ~HH_SafeLocalMemory()
    {
        if ( _pLocalMemory != 0 )
        {
            ::LocalFree( ( HLOCAL )_pLocalMemory );
        }
    }

    char* Get()
    {
        return ( char * )_pLocalMemory;
    }

private:
    HH_SafeLocalMemory( const HH_SafeLocalMemory& );
    HH_SafeLocalMemory& operator=( const HH_SafeLocalMemory& );

    void* _pLocalMemory;
};



/*
 * ErrorNumberAsText
 *
 *  Returns a formatted string representing the Win32 error passed in.
 */
std::string HH_Win32Error::ErrorNumberAsText( int win32Error )
{
    // Set up a safe local memory instance
    HH_SafeLocalMemory HH_SafeLocalMemory;

    // Format the message
    ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, win32Error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &HH_SafeLocalMemory, 0, NULL );

    // Get the message from the safe local memory instance
    char* pMessage = HH_SafeLocalMemory.Get();
    if ( pMessage == NULL )
    {
        return "";
    }

    // Get pointer to last null character in the message
    char* pEnd = strrchr( pMessage, '\0' );
    
    // While we haven't reached the beginning, attempt to
    // strip any trailing carraige returns and newline characters
    while ( pEnd-- != pMessage )
    {
        switch( *pEnd )
        {
        case '\r':
        case '\n':
            *pEnd = '\0';
            break;

        default:
            pEnd = pMessage;
            break;
        }
    }

    return pMessage;
}
