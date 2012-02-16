/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <string>
#include <windows.h>

#include <HhUnitTestFramework/UnitTest.h>


std::istream& operator >> ( std::istream& inputStream, HH_MultiTokenString& multiTokenString )
{
    enum ParsingState
    {
        SkippingLeadingSpaces,
        InToken,
        InQuotes,
        InBackslash,
        Finished
    };

    ParsingState parsingState = SkippingLeadingSpaces;

    for ( int intRead = inputStream.rdbuf()->sgetc();
        parsingState != Finished;
        intRead = inputStream.rdbuf()->snextc() )
    {
        bool endOfString = false;

        if ( intRead == std::char_traits<char>::eof() )
        {
            endOfString = true;
        }

        char charRead = std::char_traits<char>::to_char_type( intRead );

        enum CharacterType
        {
            Normal,
            Space,
            BackSlash,
            Quote,
        };

        CharacterType characterType = Normal;

        switch ( charRead )
        {
        case ' ':
            characterType = Space;
            break;

        case '\\':
            characterType = BackSlash;
            break;

        case '"':
            characterType = Quote;
            break;

        default:
            characterType = Normal;
        }

        switch ( parsingState )
        {
        case SkippingLeadingSpaces:
            if ( endOfString )
            {
                throw HH_EmptyString();
            }
            
            switch ( characterType )
            {
            case Space:
                // just skip past this leading space
                break;

            case Quote:
                parsingState = InQuotes;
                break;

            case Normal:
                multiTokenString += charRead;
                parsingState = InToken;
                break;
            }
            break;

        case InToken:
            if ( endOfString )
            {
                parsingState = Finished;
            }
            else
            {
                switch ( characterType )
                {
                case Quote:
                    parsingState = InQuotes;
                    break;

                case Space:
                    parsingState = Finished;
                    break;

                default:
                    multiTokenString += charRead;
                    break;
                }
            }
            break;

        case InQuotes:
            if ( endOfString )
            {
                throw HH_MissingEndQuote();
            }

            switch ( characterType )
            {
            case Quote:
                parsingState = Finished;
                break;

            case BackSlash:
                parsingState = InBackslash;
                break;

            default:
                multiTokenString += charRead;
                break;
            }
            break;

        case InBackslash:
            if ( endOfString )
            {
                throw HH_MissingEscapeCaracter();
            }

            switch ( characterType )
            {
            case Quote:
                multiTokenString += charRead;
                parsingState = InQuotes;
                break;

            case BackSlash:
                multiTokenString += charRead;
                parsingState = InQuotes;
                break;

            default:
                throw HH_IllegalEscapeSequence( charRead );
                break;
            }
            break;

        }
    }

    return inputStream;
}


std::ostream& operator << ( std::ostream& outputStream, const HH_MultiTokenString& multiTokenString )
{
    outputStream << "\"";
    for (  unsigned int i = 0; i < multiTokenString.GetString().length(); ++i )
    {
        const char character = multiTokenString.GetString()[i];

        if ( character == '\\' || character == '"' )
        {
            // prepend a backslash to match input string
            outputStream << '\\';
        }

        outputStream << character;
    }
    outputStream << "\"";

    return outputStream;
}
