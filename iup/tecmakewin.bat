@echo off

if "%1"=="cygw15"  goto posix
if "%1"=="cygw17"  goto posix
if "%1"=="cygw17_64"  goto posix
goto win

:win
%TECMAKE_MAKE% -f%TECMAKE_PATH%\tecmakewin.mak TEC_UNAME=%*
goto end
    
:posix
%TECMAKE_MAKE% -f%TECMAKE_PATH%\tecmake.mak %2 %3 %4 %5 %6 %7 %8 %9
goto end
    
:end
call %TECMAKE_PATH%\tecmakepause.bat
