@echo off

echo Building Distribution folder...
if not exist Distribution mkdir Distribution\Hh
if not exist Distribution\Hh\Documentation mkdir Distribution\Hh\Documentation
if not exist Distribution\Hh\HhUnitTestFramework mkdir Distribution\Hh\HhUnitTestFramework
if not exist Distribution\Hh\Lib mkdir Distribution\Hh\Lib
if not exist Distribution\Hh\Bin mkdir Distribution\Hh\Bin
if not exist Distribution\Hh\Examples mkdir Distribution\Hh\Examples
if not exist Distribution\Hh\Examples\SoundCard mkdir Distribution\Hh\Examples\SoundCard
if not exist Distribution\Hh\Examples\MediaPlayer mkdir Distribution\Hh\Examples\MediaPlayer
if not exist Distribution\Hh\Examples\MediaPlayer\utMediaPlayer mkdir Distribution\Hh\Examples\MediaPlayer\utMediaPlayer


echo Copying files...
copy HhUnitTestFramework\UnitTest.h Distribution\Hh\HhUnitTestFramework
copy HhUnitTestFramework\MultiTokenString.h Distribution\Hh\HhUnitTestFramework
copy HhUnitTestFramework\exceptions.h Distribution\Hh\HhUnitTestFramework

copy HhUnitTestFramework\Debug\HhUnitTestFrameworkMtDbg.lib Distribution\Hh\Lib
copy HhUnitTestFramework\Release\HhUnitTestFrameworkMt.lib Distribution\Hh\Lib
copy HhUnitTestFramework\DebugMtDll\HhUnitTestFrameworkMtDbgDll.lib Distribution\Hh\Lib
copy HhUnitTestFramework\ReleaseMtDll\HhUnitTestFrameworkMtDll.lib Distribution\Hh\Lib

copy Examples\SoundCard\*.h Distribution\Hh\Examples\SoundCard
copy Examples\SoundCard\*.cpp Distribution\Hh\Examples\SoundCard
copy Examples\SoundCard\*.vcproj Distribution\Hh\Examples\SoundCard
copy Examples\SoundCard\*.sln Distribution\Hh\Examples\SoundCard

copy Examples\MediaPlayer\*.h Distribution\Hh\Examples\MediaPlayer
copy Examples\MediaPlayer\*.cpp Distribution\Hh\Examples\MediaPlayer
copy Examples\MediaPlayer\*.vcproj Distribution\Hh\Examples\MediaPlayer
copy Examples\MediaPlayer\*.sln Distribution\Hh\Examples\MediaPlayer

copy Examples\MediaPlayer\utMediaPlayer\*.h Distribution\Hh\Examples\MediaPlayer\utMediaPlayer
copy Examples\MediaPlayer\utMediaPlayer\*.cpp Distribution\Hh\Examples\MediaPlayer\utMediaPlayer
copy Examples\MediaPlayer\utMediaPlayer\*.vcproj Distribution\Hh\Examples\MediaPlayer\utMediaPlayer
copy Examples\MediaPlayer\utMediaPlayer\*.cfg Distribution\Hh\Examples\MediaPlayer\utMediaPlayer
copy Examples\MediaPlayer\utMediaPlayer\*.in Distribution\Hh\Examples\MediaPlayer\utMediaPlayer
copy Examples\MediaPlayer\utMediaPlayer\*.good Distribution\Hh\Examples\MediaPlayer\utMediaPlayer
copy Examples\MediaPlayer\utMediaPlayer\*.cmd Distribution\Hh\Examples\MediaPlayer\utMediaPlayer

copy HhUnitTestFramework\docs\html\Hammerhead.chm Distribution\Hh\Documentation

copy HhRuntime\hhReporter.cmd Distribution\Hh\bin
copy HhGui\Release\HhGui.exe Distribution\Hh\Bin
copy Hh\Release\Hh.exe Distribution\Hh\Bin
copy 3rdPartyTools\* Distribution\Hh\Bin

copy readme.txt Distribution\Hh

pause