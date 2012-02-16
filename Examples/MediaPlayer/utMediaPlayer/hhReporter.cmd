@echo off

set batchBuildId=%1
set name=%2
set externalResult=%3
set result=%4

@echo **** Parameters passed ****
@echo batch build id = "%batchBuildId%"
@echo unit test name = "%name%"
@echo external result = "%externalResult"
@echo test result = "%result%"
@echo **** Important Note ****
@echo This is the batch file you can implement to connect to any external program to
@echo record the outcome of this unit test run. To execute this command file you must
@echo run hh.exe with the -b flag and specify a single token for the externalResult
@echo variable in the hh.cfg file. With this information you can do almost anything.
@echo For example you can record this information in a database or produce additional
@echo diff output to email your developers. You have the unit test name, the external
@echo result defined in the hh.cfg file (this could be the number or name of the unit
@echo test as elsewhere in your organization) and the test result which is either
@echo PASSED or FAILED.

@echo.
@echo hhReporter is recording unit test %result%

if "%result%"=="PASSED" del "%name%".diff 2>NUL
if "%result%"=="PASSED" del "%name%".fail 2>NUL
if "%result%"=="PASSED" @echo %externalResult% 1 > "%name%".pass
if "%result%"=="PASSED" goto :endok

if "%result%"=="FAILED" del "%name%".pass 2>NUL
if "%result%"=="FAILED" @echo %externalResult% 0 > "%name%".fail
if "%result%"=="FAILED" diff "%name%".out "%name%".good > "%name%".diff
if "%result%"=="FAILED" goto :endok


:endok

