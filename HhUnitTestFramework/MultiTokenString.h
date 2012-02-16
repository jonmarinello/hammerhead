#ifndef HH_MULTI_TOKEN_STRING_HEADER
#define HH_MULTI_TOKEN_STRING_HEADER

/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <string>
#include <sstream>
#include <iostream>

/**
 *  HH_MultiTokenString is used to stream in string parameters with embedded
 *  spaces.
 *
 *  @author Copyright (c) 2003-2005, Jon Marinello
 */
class HH_MultiTokenString
{
public:
    /**
     *  Returns a std::string representation.
     *
     *  @return the std::string value.
     */
    std::string GetString() const { return m_string; }

    /**
     *  Appends a character to this string.
     *
     *  @param [in] character - the character to append.
     */
    void operator += ( char character ) { m_string += character; }

private:
    /**
     *  The internal string containg the tokens parsed from a quoted string.
     */
    std::string m_string;
};

std::istream& operator >> ( std::istream& inputStream, HH_MultiTokenString& multiTokenString );
std::ostream& operator << ( std::ostream& outputStream, const HH_MultiTokenString& multiTokenString );

#endif
