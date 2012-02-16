#ifndef HH_FILE_HEADER
#define HH_FILE_HEADER

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include "stdafx.h"

class HH_File
{
public:
    HH_File( const std::string& fileName, const char* mode = "rb" );
    ~HH_File();

    FILE* GetFilePtr() const { return m_filePtr; }

    long GetSize() const;
    bool Compare( HH_File& file );

    std::string GetLine( bool& eof );
    void PutLine( std::string line );

protected:
    std::string m_fileName;
    FILE*       m_filePtr;

private:
    HH_File( const HH_File& );                // not allowed
    HH_File& operator=( const HH_File& );     // not allowed
};

#endif
