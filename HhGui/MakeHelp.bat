@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by HHGUI.HPJ. >"hlp\HhGui.hm"
echo. >>"hlp\HhGui.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\HhGui.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\HhGui.hm"
echo. >>"hlp\HhGui.hm"
echo // Prompts (IDP_*) >>"hlp\HhGui.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\HhGui.hm"
echo. >>"hlp\HhGui.hm"
echo // Resources (IDR_*) >>"hlp\HhGui.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\HhGui.hm"
echo. >>"hlp\HhGui.hm"
echo // Dialogs (IDD_*) >>"hlp\HhGui.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\HhGui.hm"
echo. >>"hlp\HhGui.hm"
echo // Frame Controls (IDW_*) >>"hlp\HhGui.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\HhGui.hm"
REM -- Make help for Project HHGUI


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\HhGui.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\HhGui.hlp" goto :Error
if not exist "hlp\HhGui.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\HhGui.hlp" Debug
if exist Debug\nul copy "hlp\HhGui.cnt" Debug
if exist Release\nul copy "hlp\HhGui.hlp" Release
if exist Release\nul copy "hlp\HhGui.cnt" Release
echo.
goto :done

:Error
echo hlp\HhGui.hpj(1) : error: Problem encountered creating help file

:done
echo.
