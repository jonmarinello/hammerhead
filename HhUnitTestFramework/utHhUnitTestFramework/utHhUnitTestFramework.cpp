/*
 * Copyright (c) 2003-2005, Jon Marinello
 *
 */

#include <HhUnitTestFramework/UnitTest.h>

class UtHhUnitTest : public HH_UnitTest
{
public:
    UtHhUnitTest( bool& variableDataGeneration, bool interactive )
        : HH_UnitTest( variableDataGeneration, interactive ),
          m_stringValue( "defaultStringValue" ),
		  m_boolValue( true )
    {}

protected:
    virtual void TestCommands();
    virtual void HelpForTestCommands();

private:
    bool        m_boolValue;
    std::string m_stringValue;
};


void UtHhUnitTest::HelpForTestCommands()
{
    std::cout << "SetBool <bool> - saves away a bool in a member variable." << std::endl << std::endl;
    std::cout << "GetBool - displays the bool member variable." << std::endl << std::endl;
    std::cout << "SetStringValue <string> - saves away stringValue as a member variable." << std::endl << std::endl;
    std::cout << "GetStringValue - displays the _stringValue member variable." << std::endl << std::endl;
    std::cout << "TestMultipleParams \"<multiple token string>\" <string> <intNumber> <doubleNumber> - tests use of multiple test arguments." << std::endl << std::endl;
}


void UtHhUnitTest::TestCommands()
{
    HH_TESTCMD( "SetBool" )
    {
        HH_TESTCMD_PARAM( bool, boolValue );
        m_boolValue = boolValue;
    }
    HH_TESTCMD( "GetBool" )
    {
        std::cout << m_boolValue << std::endl;
    }
    HH_TESTCMD( "SetStringValue" )
    {
        HH_TESTCMD_PARAM( std::string, stringValue );
        m_stringValue = stringValue;
    }
    HH_TESTCMD( "GetStringValue" )
    {
        std::cout << m_stringValue << std::endl;
    }
    HH_TESTCMD( "TestMultipleParams" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, multiTokenString );
        HH_TESTCMD_PARAM( std::string, string );
        HH_TESTCMD_PARAM( bool, boolValue );
        HH_TESTCMD_PARAM( int, intNumber );
        HH_TESTCMD_PARAM( double, doubleNumber );

        std::cout << "multiTokenString = " << multiTokenString << std::endl;
        std::cout << "string = \"" << string << "\"" << std::endl;
        std::cout << "boolValue = " << boolValue << std::endl;
        std::cout << "intNumber = " << intNumber << std::endl;
        std::cout << "doubleNumber = " << doubleNumber << std::endl;
    }
    HH_TESTCMD( "Test2MultiTokenStrings" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, multiTokenString1 );
        HH_TESTCMD_PARAM( HH_MultiTokenString, multiTokenString2 );
        std::cout << "multiTokenString1 = " << multiTokenString1 << std::endl;
        std::cout << "multiTokenString2 = " << multiTokenString2 << std::endl;
    }
}


void main( int argc, char*[] )
{
    bool variableDataGeneration = false;
    UtHhUnitTest utHhUnitTest( variableDataGeneration, argc == 1 );
    utHhUnitTest.Run();
}
