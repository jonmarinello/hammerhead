@echo off

set batchBuildId=%1
set name=%2
set externalResult=%3
set result=%4

@echo.
@echo hhReporter is recording unit test %result%

if "%result%"=="PASSED" del "%name%".diff 2>NUL
if "%result%"=="PASSED" del "%name%".fail 2>NUL
if "%result%"=="PASSED" @echo %externalResult% 1 > "%name%".pass
if "%result%"=="PASSED" goto :endok

if "%result%"=="FAILED" del "%name%".pass 2>NUL
if "%result%"=="FAILED" @echo %externalResult% 0 > "%name%".fail
if "%result%"=="FAILED" diff "%name%".out "%name%".good > "%name%".diff
if "%result%"=="FAILED" type "%name%".diff
if "%result%"=="FAILED" goto :endok

:endok
