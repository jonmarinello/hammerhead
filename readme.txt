1. Introduction
    The Hammerhead C++ Unit Test Framework is available for you to use free of charge.
    However, you may not redistribute it for profit to any person or organization.

    Copyright (c) 2003-2005, Jon Marinello



2. Installation
    1. Unzip Hh.zip into whatever place you find convenient usually the root of your C drive.
    2. Add "c:\hh\bin" to the front of your PATH environment variable. It must be at the front.



3. Include Files and Libraries
    You will find the include files in the "HhUnitTestFramework" folder. Release and debug
    libraries can be found in the "Lib" folder. Note, these libraries are compiled with
    code generation set to "Multithreaded" and "Multithreaded DLL" for the release libraries and
    "Debug Multithreaded" and "Debug Multithreaded DLL" for the debug libraries. If you need a
    version of these libraries compiled some other way (i.e., single threaded) contact me at
    jonmarinello@hotmail.com.

    

4. Example Unit Test

4.1 utMediaPlayer
    This C++ example demonstrates virtually all of the concepts described in this
    document in a small self-contained set of source files. You can find the example
    unit test in the folder named "examples" under "hh". Note that this particular
    unit test resides under the unit test component. This is unique to this test as
    it is an example of how to write unit tests. Your unit test should reside directly
    under the component being tested.

4.2 Folder Structure
    There are three folders in the example:

        * SoundCard - Contains the header and implementation files for the wrapper
          class of an imaginary piece of hardware and its drivers for playing sounds.
          This class is not tested in this example but is used to demonstrate stubbing.

        * MediaPlayer - Contains the header and implementation files for a higher level
          class that defines the business rules for playing media. This is the component
          that is being unit tested.

        * utMediaPlayer - Contains the unit test for the MediaPlayer component.

4.3 Files
    The SoundCard folder contains the following files:

        * SoundCard.cpp - An imaginary implementation of the wrapper. In a real-world example,
          this would be talking to the drivers of the actual sound card.

        * SoundCard.h - The sound card class interface definition.

    The MediaPlayer folder contains the following files:

        * MediaPlayer.cpp - The media player implementation.

        * MediaPlayer.sln - The project solution. This is important as it contains the required
          dependency the unit test has on the library being tested. In your components, put the
          workspace ".sln" file next to the project ".vcproj" file.

        * MediaPlayer.h - The media player class interface definition.

        * Hh.cfg - This file is used by Hammerhead to simplify running the unit test, viewing failures
          and approving your changes. It should reside in the unit test folder.

    The utMediaPlayer folder contains the following files (none of which are part of the code shipped
    to our customers):

        * SoundCardStub.cpp - The stub file that provides an alternate implementation of the sound
          card wrapper class that allows the unit test to completely control program execution
          through all the code paths.

        * utMediaPlayer.cpp - The media player unit test implementation. This file contains a class
          called utMediaPlayer that inherits from HH_UnitTest and provides the virtual
          TestCommands() implementation.

        * utMediaPlayer.good - The approved unit test output.

        * utMediaPlayer.in - The input test script.

4.4 Building And Running The Unit Test Example

    To build the example unit test open the media player project workspace, set utMediaPlayer as the
    active project and then build. To run the example unit test, open a command window, change
    directories to utMediaPlayer and enter hh followed by the enter key. After you run
    the example test, you should see something like this:

    Hammerhead C++ Unit Testing Framework
    Release 1.03.4 built on Sep 25 2005
    Copyright (c) 2003-2005, Jon Marinello

    TEST PASSED

    Now try making some changes to the stub file or the ".in" file. Rebuild and run as needed. When
    you see "TEST FAILED" try executing hh.exe again but include the -f argument. This will run
    WinDiff and visually show you the differences between the ".out" file and the ".good" file. If
    you want to approve the test, execute hh.exe again but this time include the -a flag, which
    approves the test (i.e., copies the ".out" file over the ".good" file).



5. Using the Hammerhead Unit Test Framework

5.1 Overview
    The Hammerhead Unit Test Framework provides a simple and easy-to-use set of extensible classes,
    helpful macros and runtime to facilitate writing and maintaining automated unit tests for your
    C++ components.

    The Hammerhead Unit Test Framework design is based around the concept of scripting. Scripting
    allows you to test your component by entering commands into the unit test that exercise classes
    and methods in a simple language syntax based on test commands and parameters that you define.
    For each method you want to test, you define a C++ test command that invokes the method and passes
    to it all the required parameters. Once defined, this scriptable test command can be used to call
    the method under test in any number of ways without recompiling your unit test C++ code. Once at
    least a few of your test commands have been defined in your C++ unit test, you can create a set of
    scripted test cases in an input file with the ".in" extension. This file is used by the Hammerhead
    Unit Test Framework to drive the unit test and to produce a corresponding output file with the
    ".out" extension. This output file is compared with a known good output file with the ".good"
    extension to determine if the unit test passed or failed. When there is a failure a visual comparison
    of the differences may be produced to help you quickly "zero in" on what's changed to determine
    if this is expected or not. If the difference is expected, then the test can be approved. If the
    difference is unexpected, you can make whatever changes are needed to your component under test
    or the unit test you wrote until the test passes or the new output is what you expect. Appendix A
    shows the general workflow of how to write and run unit tests.

    Contrary to what you might initially think, using this framework will actually speed up development
    and maintenance of your classes. It also provides a suite of automated regression tests that is run
    as part of every nightly and QA build. In addition to the framework provided, there are a small
    number of artifacts that you must provide to write a unit test. This section describes these classes,
    macros and batch files as well as how to use them. It also describes the artifacts that you need to
    produce as well as how to run the test, view the output and approve the results. For a good example
    of how to use these classes see the "Example Unit Test" section of this document.

5.2 Classes

5.2.1 HH_UnitTest
    This is the most important class to understand how to use and extend. It provides a simple command
    parser.  Unit tests are generated by deriving a class from this class and implementing the virtual
    TestCommands() method.

    The implementation of the derived class should look something like the following:

    class utMyComponent : public HH_UnitTest
    {
    public:
        utMyComponent( bool& variableDataGeneration )
            : HH_UnitTest( variableDataGeneration )
        {
        }

        ~utMyComponent()
        {
        }

        void TestCommands();

    private:
        // member variables you need to declare can go here.

        // member functions you need to declare can go here. 
    }

    The implementation of the TestCommands() function should look something like the following:

    void utMyComponent::TestCommands()
    {
        HH_TESTCMD( "commandName" )
        {
            HH_TESTCMD_PARAM( argumentType, argument );
            < Additional arguments can follow here >
            < The implementation of the command goes here.  The implementation can
              access any of the arguments, and any attributes of the derived unit test class. >
        }
        < Additional commands can follow here >
    }

5.2.2 HH_MultiTokenString

    This helpful class allows input of strings that contain spaces separating multiple tokens. Let's
    assume you have a test command that has an argument like this:

    HH_TESTCMD( "dispIniFileOpenError" )
    {
        HH_TESTCMD_PARAM( HH_MultiTokenString, fileName );
        ...
    }

    Use of the HH_MultiTokenString type allows you to enter strings that contain spaces by delimiting
    them with double quotes.

5.3 Macros

5.3.1 HH_TESTCMD
    This macro defines a test command. It takes a string argument for the name of the command. In general
    you should define one of these for each public method your class has.

5.3.2 HH_TESTCMD_PARAM
    This macro defines a test command parameter. It takes an argument type (int, HH_MultiTokenString,
    std::string, etc. that must support STL streaming) that defines the C++ type of the test command parameter
    and a C++ name for test command. In general you will need as many of these as there are parameters to the
    method under test.

5.4 Commands

5.4.1 Built-in Commands
    The Unit Test Framework has several built-in convenience commands:

    * System "command line" - shells out and executes "command line" synchronously using ::system().
    * CreateProcess "executable" - shells out and executes "executable" synchronously using ::CreateProcess().
    * Sleep <milliseconds> - sleeps for some number of milliseconds.
    * Exit - exits the unit test.
    * SetVariableData - sets the current value of variable data output.
    * GetVariableData - displays the current value of variable data output.
    * unlink "<file name>" - deletes the file <file name>.
    * mkdir "<directory name>" - creates the directory <directory name>.
    * rmdir "<directory name>" - removes the directory <directory name>.
    * ? - displays help for these built-in commands and also any documented derived commands.
    * ?? - displays help for only documented derived commands.

5.4.2 Preprocessor Commands
    The Unit Test Framework has one preprocessor command:

    * @include <.in file name> - allows you to include other .in files
    
    The @include command allows you to include other .in files. Any .in file may contain this command and before
    your unit test actually runs, your .in files are preprocessed and a final temporary .in file is generated and
    fed into your unit test. This command is extremely  useful if you have some input script commands that you want
    to execute multiple times often with a slightly different setup.
    
    Be careful not to create a circular dependency.
    
5.5 Artifacts

5.5.1 .cpp Files
    You will need to create a .cpp file that contains your derived class and TestCommands() implementation.
    You can also implement any additional utility methods your derived class requires here too. The last
    thing you will need is a main() entry point. If you need to stub, you will also need to create one or
    more stub .cpp files for the components you're stubbing. These files often reside in the unit test subfolder.

5.5.2 .in File
    Although you can run your test interactively, this will become very tedious over time as the number of
    test commands you create grows. You will need to implement a .in file that contains all tests you want
    to run by calling the test commands you implemented in your derived class's TestCommands() function.
    Note that you will probably want to call the same test command numerous times with different parameter values
    in order to completely test your method. This file should reside in the unit test subfolder.

5.5.3 hh.cfg File
    You will need to create a Hammerhead configuration file that contains instructions on how to run your tests
    in an automated fashion using the hh.exe program. This file should reside in the unti test folder. The
    implementation of the Hammerhead configuration file should look something like the following:

    [Hammerhead]
    # Hammerhead config file 1.03.4

    # This file describes the settings to be used by the unit test system

    #
    # All text after a hash (#) is considered a comment and will be ignored
    # The format is:
    #       TAG = value [value,...]
    #

    #---------------------------------------------------------------------------
    # General configuration options
    #---------------------------------------------------------------------------
    #
    # The "name" tag is a single word or a sequence of words that identifies the unit test.
    name=utMediaPlayer


    # The "exepath" tag defines the path to the unit test excutable.
    exepath=debug\utMediaPlayer.exe


    # The "externalResult" tag defines the external name to report the test result as.
    # If you define this tag (which can be any arbitrary single token), the framework will
    # attempt to report the unit test result to a program called hhReporter that must
    # accept three parameters; the unit test name, this external result tag and lastly
    # the token PASSED or FAILED. You must supply this program and you may use it to
    # report to external systems (like databases) that are used to keep track of unit test.
    # results.
    externalResult=

    This file should reside in the unit test subfolder.

5.5.4 .vcproj and .sln Files
    You will need to create a Visual C++ project (.vcproj) file for the unit test project that contains your
    .cpp file as well as your .in file. This file should reside in the unit test subfolder.

    You will also need to create a Visual C++ solution (.sln) file for the unit test project. Be sure to
    create a dependency from the unit test project to the component project so that you can build it all
    from the IDE by simply building the unit test project. This file should reside in the component folder.

