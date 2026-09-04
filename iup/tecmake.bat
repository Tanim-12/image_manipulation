@echo off

REM Cygwin configuration
set MAKE_MODE=UNIX

REM *********************************************
REM Tecmake Configuration

REM Change the following lines to match your system installation
REM Use always  "/" is paths, except for TECMAKE_PATH

REM Do NOT use long file names with spaces here.
REM Use the tool "shortpath" to display the
REM   short name version of the current folder
REM   or pass the folder as the first parameter.
REM OR create a link to the folder using a name without spaces.
REM OR create a copy of the folder using a name without spaces.
REM *********************************************


REM Used only in some scripts on Tecmake for Windows.
REM Not used inside the Makefile.
REM Must use Windows standard PATH separators "\".
REM set TECMAKE_PATH=c:\tecgraf\tecmake
set TECMAKE_PATH=t:\lib\tecmake

REM This is the only place where a cygdrive path is used.
REM set TECMAKE_HOME=/cygdrive/c/tecgraf/tecmake
set TECMAKE_HOME=/cygdrive/t/lib/tecmake

REM This must be the GNU make
set TECMAKE_MAKE=make

REM Change the paths you need to match your installation:
rem set VC6=c:/app/lng/vc6
rem set VC7=c:/progra~1/micros~1.net/vc7
rem set VC8=c:/progra~1/mid05a~1/vc
rem set VC9=c:/progra~2/micros~1.0/vc
rem set VC10=c:/progra~2/micros~1.0/vc
rem set VC11=c:/progra~2/micros~1.0/vc
rem set VC12=c:/progra~2/micros~1.0/vc
rem set VC14=c:/progra~2/micros~1.0/vc
rem set VC15=c:/progra~2/micros~1.0/vc
rem set VC16=c:/progra~2/micros~1.0/vc

REM If you have problems with Visual C++ make sure that 
REM "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\IDE"
REM is in your PATH.

REM Leave this commented out to use the SDK installed with the compiler.
rem set PLATSDK=c:/progra~1/mifd68~1

REM By default for vc9/vc10 we will use the SDK
REM  from the folder $(VC9)/WinSDK or $(VC10)/WinSDK
REM VC9/VC10 installs the Windows SDK in a separate directory,
REM   usually is similar to "C:\Program Files\Microsoft SDKs\Windows\v6.0A".
REM   VC11 is at "C:\Program Files (x86)\Windows Kits\8.0"
rem set VC9SDK=c:/progra~1/micros~3/windows/v6.0a
rem set VC10SDK=c:/progra~1/micros~3/windows/v7.1
rem set VC11SDK=c:/progra~1/micros~1/window~1/8.0
rem set VC12SDK=c:/progra~1/micros~1/window~1/8.1
rem set VC14SDK=c:/progra~1/micros~1/window~1/8.1
rem set VC15SDK=c:/progra~1/micros~1/window~1/10
rem set VC16SDK=c:/progra~1/micros~1/window~1/10
REM If PLATSDK is defined then VC*SDK are not used.

rem set OWC1=c:/app/lng/owc1
rem set BC55=c:/app/lng/bcc55
rem set BC56=c:/app/lng/CBuilderX
rem set MINGW3=c:/app/lng/mingw3
rem set MINGW4=c:/app/lng/mingw4
rem set MINGW4_64=c:/app/lng/mingw4_64
rem set GCC3=c:/cygwin15
rem set GCC4=c:/cygwin17

rem set GLUT=c:/app/lng/glut
rem set GTK=c:/app/lng/gtk
rem set GTK3=c:/app/lng/gtk3

REM Uncomment the variables you need
rem set TECTOOLS_HOME=c:/tecgraf
rem set CD=%TECTOOLS_HOME%/cd
rem set IM=%TECTOOLS_HOME%/im
rem set IUP=%TECTOOLS_HOME%/iup
rem set LUA=%TECTOOLS_HOME%/lua
rem set LUA5=%TECTOOLS_HOME%/lua5
rem set LUA50=%TECTOOLS_HOME%/lua50
rem set LUA51=%TECTOOLS_HOME%/lua5.1
rem set LUA52=%TECTOOLS_HOME%/lua52
rem set LUA53=%TECTOOLS_HOME%/lua53
rem set CDDIR=%CD%/etc
                   
REM Must edit or set this for your Windows system
rem set TEC_SYSVERSION=5
rem set TEC_SYSMINOR=1
rem set TEC_SYSRELEASE=%TEC_SYSVERSION%.%TEC_SYSMINOR%
REM TEC_SYSRELEASE will be defined as a variable when compiling code only for gcc

REM Define this if compiling for 64-bits in a 32bits environment
if %PROCESSOR_ARCHITECTURE%==x86 set USE_X86_CL64=Yes

REM *********************************************

if "%1"==""            goto default
if "%1"=="all"         goto all
if "%1"=="all-vc"      goto all-vc
if "%1"=="all-vc_dll"  goto all-vc_dll
if "%1"=="all-gcc"     goto all-gcc
if "%1"=="all-gcc_dll" goto all-gcc_dll
if "%1"=="all-cygw"    goto all-cygw
if "%1"=="all-mingw"   goto all-mingw
if "%1"=="all-other"   goto all-other
if "%1"=="all-beta"    goto all-beta
if "%1"=="all-beta_vc" goto all-beta_vc
if "%1"=="gcc3"        goto make
if "%1"=="gcc4"        goto make
if "%1"=="gcc4_64"     goto make
if "%1"=="mingw3"      goto make
if "%1"=="mingw4"      goto make
if "%1"=="mingw4_64"   goto make
if "%1"=="cygw15"      goto make
if "%1"=="cygw17"      goto make
if "%1"=="cygw17_64"   goto make
if "%1"=="vc7"         goto make
if "%1"=="vc6"         goto make
if "%1"=="vc8"         goto make
if "%1"=="vc8_64"      goto make
if "%1"=="vc9"         goto make
if "%1"=="vc9_64"      goto make
if "%1"=="vc10"        goto make
if "%1"=="vc10_64"     goto make
if "%1"=="vc11"        goto make
if "%1"=="vc11_64"     goto make
if "%1"=="vc12"        goto make
if "%1"=="vc12_64"     goto make
if "%1"=="vc14"        goto make
if "%1"=="vc14_64"     goto make
if "%1"=="vc15"        goto make
if "%1"=="vc15_64"     goto make
if "%1"=="vc16"        goto make
if "%1"=="vc16_64"     goto make
if "%1"=="owc1"        goto make
if "%1"=="bc55"        goto make
if "%1"=="bc56"        goto make
if "%1"=="bc6"         goto make
if "%1"=="dll"         goto make
if "%1"=="dll7"        goto make
if "%1"=="dll8"        goto make
if "%1"=="dll8_64"     goto make
if "%1"=="dll9"        goto make
if "%1"=="dll9_64"     goto make
if "%1"=="dll10"       goto make
if "%1"=="dll10_64"    goto make
if "%1"=="dll11"       goto make
if "%1"=="dll11_64"    goto make
if "%1"=="dll12"       goto make
if "%1"=="dll12_64"    goto make
if "%1"=="dll14"       goto make
if "%1"=="dll14_64"    goto make
if "%1"=="dll15"       goto make
if "%1"=="dll15_64"    goto make
if "%1"=="dll16"       goto make
if "%1"=="dll16_64"    goto make
if "%1"=="dllw4"       goto make
if "%1"=="dllg4"       goto make
if "%1"=="dllw4_64"    goto make
if "%1"=="dllg4_64"    goto make
goto error

:all
FOR %%u IN (vc10 vc11 vc12 vc14 vc15 vc16 vc10_64 vc11_64 vc12_64 vc14_64 vc15_64 vc16_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
FOR %%u IN (dll10 dll11 dll12 dll14 dll15 dll16 dll10_64 dll11_64 dll12_64 dll14_64 dll15_64 dll16_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
FOR %%u IN (mingw6 mingw6_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
FOR %%u IN (dllw6 dllw6_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-vc
FOR %%u IN (vc10 vc11 vc12 vc14 vc14 vc15 vc16 vc10_64 vc11_64 vc12_64 vc14_64 vc15_64 vc16_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-vc_dll
FOR %%u IN (dll10 dll11 dll12 dll14 dll15 dll16 dll10_64 dll11_64 dll12_64 dll14_64 dll15_64 dll16_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-gcc
FOR %%u IN (mingw6 mingw6_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-gcc_dll
FOR %%u IN (dllw6 dllw6_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-cygw
FOR %%u IN (cygw17) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-mingw
FOR %%u IN (mingw6 mingw6_64 dllw6 dllw6_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-other
FOR %%u IN (owc1 bc6) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-beta
FOR %%u IN (vc10 vc10_64 vc12 vc12_64 dll10 dll10_64 dll12 dll12_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:all-beta_vc
FOR %%u IN (vc10 vc10_64 vc12 vc12_64) DO call %TECMAKE_PATH%\tecmakewin.bat %%u %2 %3 %4 %5 %6 %7 %8 %9
goto end

:make
call %TECMAKE_PATH%\tecmakewin.bat %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:default
call %TECMAKE_PATH%\tecmakewin.bat vc10
goto end

:error
echo Invalid parameter.

:end
