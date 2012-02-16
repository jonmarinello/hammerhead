/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include "stdafx.h"
#include <HhRuntime/Runtime.h>
#include <HhRuntime/File.h>

HH_File::HH_File( const std::string& fileName, const char* mode )
    : m_filePtr( NULL )
{
	errno_t errorno;
    errorno = ::fopen_s( &m_filePtr, fileName.c_str(), mode );

    if ( errorno != NULL )
    {
        std::string message = "Can't open file '";
        message += fileName;
        message += "' with ::fopen()";
        throw HH_ErrnoError( message, errno );
    }
    m_fileName = fileName;
}



HH_File::~HH_File()
{
    if ( m_filePtr != NULL )
    {
        ::fclose( m_filePtr );
    }
}



long HH_File::GetSize() const
{
    long size = ::_filelength( ::_fileno( m_filePtr ) );

    if ( size == -1 )
    {
        std::string message = "Can't get size of file  '";
        message += m_fileName;
        message += "' with ::filelength()";
        throw HH_ErrnoError( message, errno );
    }

    return size;
}



bool HH_File::Compare( HH_File& file )
{
    if ( GetSize() != file.GetSize() )
    {
        return false;
    }
    for ( ;; )
    {
        int firstChar = ::fgetc( m_filePtr );
        int secondChar = ::fgetc( file.GetFilePtr() );

        if ( firstChar != secondChar )
        {
            return false;
        }
        if ( firstChar == EOF )
        {
            break;
        }
    }
    return true;
}



std::string HH_File::GetLine( bool& eof )
{
    char buffer[10240] = "";

    if ( ::fgets( buffer, sizeof buffer, m_filePtr ) == NULL )
    {
        if ( feof( m_filePtr ) )
        {
            eof = true;
        }
        else if ( ferror( m_filePtr ) )
        {
            std::string message = "Can't read from file  '";
            message += m_fileName;
            message += "'";
            throw HH_ErrnoError( message, errno );
        }
    }
    return buffer;
}



void HH_File::PutLine( std::string line )
{
    if ( ::fputs( line.c_str(), m_filePtr ) < 0 )
    {
        std::string message = "Can't write to file  '";
        message += m_fileName;
        message += "'";
        throw HH_ErrnoError( message, errno );
    }
}

