#!/bin/csh

# ########################
# Tecmake Configuration
# ########################

setenv TECTOOLS_HOME /home/tecgraf
setenv TECMAKE_HOME /home/tecgraf/tecmake
setenv TECMAKE_MAKE make

# ########################
# System Identification
# ########################

# Base Definitions
setenv TEC_SYSNAME	`uname -s`
setenv TEC_SYSVERSION	`uname -r|cut -f1 -d.`
setenv TEC_SYSMINOR	`uname -r|cut -f2 -d.`
setenv TEC_SYSARCH	`uname -m`

# Fixes
switch ( $TEC_SYSNAME )
case SunOS:
	setenv TEC_SYSARCH	`uname -p`
	breaksw
case IRIX:
	setenv TEC_SYSARCH	`uname -p`
	breaksw
case FreeBSD:
	setenv TEC_SYSMINOR	`uname -r|cut -f2 -d.|cut -f1 -d-`
	breaksw
case GNU/kFreeBSD:
	setenv TEC_SYSNAME	kFreeBSD
	setenv TEC_SYSMINOR	`uname -r|cut -f2 -d.|cut -f1 -d-`
	breaksw
case AIX:
	setenv TEC_SYSVERSION	`uname -v`
	setenv TEC_SYSMINOR	`uname -r`
	setenv TEC_SYSARCH	'ppc'
	breaksw
case Darwin:
	setenv TEC_SYSNAME	'MacOS'
	setenv TEC_SYSVERSION	`sw_vers -productVersion|cut -f1 -d.`
	setenv TEC_SYSMINOR	`sw_vers -productVersion|cut -f2 -d.`
	setenv TEC_SYSARCH	`uname -p`
	breaksw
endsw

if ($TEC_SYSARCH == 'i686' || $TEC_SYSARCH == 'i386') then
	setenv TEC_SYSARCH	'x86'
endif
if ($TEC_SYSARCH == 'powerpc') then
	setenv TEC_SYSARCH	'ppc'
endif
if ($TEC_SYSARCH == 'x86_64' || $TEC_SYSARCH == 'amd64') then
	setenv TEC_SYSARCH	'x64'
endif

# Compose
setenv TEC_SYSRELEASE	$TEC_SYSVERSION.$TEC_SYSMINOR
setenv TEC_UNAME	$TEC_SYSNAME$TEC_SYSVERSION$TEC_SYSMINOR

# Linux 2.4 and GCC 3.x
if ($TEC_UNAME == 'Linux24') then
  set GCCVER=`gcc -dumpversion|cut -f1 -d.`
  if ($GCCVER == '3') then
	  setenv TEC_UNAME	$TEC_UNAME'g3'
  endif
  unset GCCVER
endif

# Linux 2.6 and GCC 4.x
if ($TEC_UNAME == 'Linux26') then
  set GCCVER=`gcc -dumpversion|cut -f1 -d.`
  if ($GCCVER == '4') then
	  setenv TEC_UNAME	$TEC_UNAME'g4'
  endif
  unset GCCVER
endif

if ($TEC_SYSNAME == 'Linux') then
  # Linux and PowerPC
  if ($TEC_SYSARCH == 'ppc') then
	  setenv TEC_UNAME	$TEC_UNAME'ppc'
  endif

  # 64-bits Linux
  if ($TEC_SYSARCH == 'x64') then
    setenv BUILD_64	Yes
    setenv TEC_UNAME	$TEC_UNAME'_64'
  endif

  # Itanium Linux
  if ($TEC_SYSARCH == 'ia64') then
    setenv BUILD_64	Yes
    setenv TEC_UNAME $TEC_UNAME'_ia64'
  endif
    
  # Linux Distribution
  setenv TEC_DISTNAME	`lsb_release -is`
  setenv TEC_DISTVERSION	`lsb_release -rs|cut -f1 -d.`
  setenv TEC_DIST	$TEC_DISTNAME$TEC_DISTVERSION
endif

# 64-bits FreeBSD
if ($TEC_SYSNAME == 'FreeBSD') then
  if ($TEC_SYSARCH == 'x64') then
    setenv BUILD_64	Yes
    setenv TEC_UNAME	$TEC_UNAME'_64'
  endif
endif

# Solaris and Intel
if ($TEC_SYSNAME == 'SunOS') then
  if ($TEC_SYSARCH == 'x86') then
	  setenv TEC_UNAME	$TEC_UNAME'x86'
  endif
endif

# MacOS and Intel
if ($TEC_SYSNAME == 'MacOS') then
  if ($TEC_SYSMINOR < 6) then
    if ($TEC_SYSARCH == 'x86') then
      setenv TEC_UNAME	$TEC_UNAME'x86'
    endif
  else
    setenv TEC_SYSARCH	'x64'
  endif
endif

# #####################
# Environment Variables
# #####################

foreach produto ( im cd iup lua52 lua53 )
	set PROD=`echo $produto|tr \[a-z\] \[A-Z\]`
	setenv $PROD $TECTOOLS_HOME/$produto
	unset PROD
end

setenv LUA51 $TECTOOLS_HOME/lua5.1
#If the Lua executables are not in the above folder tree
#setenv LUA_BIN /usr/local/bin

setenv CDDIR $CD/etc
