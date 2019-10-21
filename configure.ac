dnl
dnl sadplay - AdLib music player with graphics.
dnl 
dnl configure.ac - Autoconf configuration file
dnl 
dnl Copyright (C) 2019 Marco Confalonieri <marco at marcoconfalonieri.it>
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl 
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <https://www.gnu.org/licenses/>.
dnl

AC_INIT([sadplay],
        m4_esyscmd_s([
          if [ "x$AZURE_BUILD_VERSION" != "x" ]; then
            echo $AZURE_BUILD_VERSION
          else
            echo 1.0.0-SNAPSHOT
          fi
        ]), [marco@marcoconfalonieri.it])
AM_INIT_AUTOMAKE([foreign parallel-tests color-tests])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG(C++)
AC_PROG_CXX

AX_CODE_COVERAGE

dnl Check for SDL
SDL_VERSION=2.0
AM_PATH_SDL2($SDL_VERSION,
        :,
        AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AX_FFTW3()

# Nothing works without these libraries...
AC_CHECK_LIB(stdc++,main,,AC_MSG_ERROR([libstdc++ not installed]))
PKG_CHECK_MODULES([adplug], [adplug >= 2.0],,[
AC_MSG_WARN([You seem to be using a version of AdPlug prior to 2.0. \
I will try to do the old-style library search for which i cannot check \
versions. Please bear in mind that i am requiring at least version 1.4.])
AC_CHECK_LIB(adplug,main,,AC_MSG_ERROR([*** AdPlug not installed ***]))])

# Check if getopt header is installed on this system
AC_CHECK_HEADERS([getopt.h], ,
	AC_SUBST(GETOPT_SOURCES, [getopt.c getopt1.c getopt.h]))

# Save compiler flags and set up for compiling test programs
oldlibs="$LIBS"
oldcppflags="$CPPFLAGS"
LIBS="$LDFLAGS $adplug_LIBS"
CPPFLAGS="$CPPFLAGS $adplug_CFLAGS"

# Check if AdPlug is installed and linked correctly
AC_MSG_CHECKING([whether AdPlug is linked correctly])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <adplug/player.h>

class Testplayer: public CPlayer
{
  public:
    Testplayer(): CPlayer(NULL) {}
    bool load(const std::string &f, const CFileProvider &fp) { return false; }
    bool update() { return false; }
    float getrefresh() { return 0; }
    std::string gettype() { return std::string(); }
    void rewind(int s) {}
};

Testplayer p;], [p.getrefresh();])],
  AC_MSG_RESULT([yes]), AC_MSG_RESULT([no]); AC_MSG_ERROR([Unable to compile a program using AdPlug. Please check to ensure AdPlug is installed correctly.]) )

# Check if AdPlug supports the new getsubsong() method
AC_MSG_CHECKING([whether AdPlug supports the getsubsong() method])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <adplug/player.h>

class Testplayer: public CPlayer
{
  public:
    Testplayer(): CPlayer(NULL) {}
    bool load(const std::string &f, const CFileProvider &fp) { return false; }
    bool update() { return false; }
    float getrefresh() { return 0; }
    std::string gettype() { return std::string(); }
    void rewind(int s) {}
};

Testplayer p;], [p.getsubsong();])],
   AC_DEFINE(HAVE_ADPLUG_GETSUBSONG,, [Defined if AdPlug supports the getsubsong() method])
AC_MSG_RESULT([yes]), AC_MSG_RESULT([no]))

# Check if AdPlug supports the new surround/harmonic synth
AC_MSG_CHECKING([whether AdPlug supports the surround/harmonic synth])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <adplug/surroundopl.h>], [CSurroundopl *dummy;])],
   AC_DEFINE(HAVE_ADPLUG_SURROUND,, [Defined if AdPlug supports the surround/harmonic synth])
AC_MSG_RESULT([yes]), AC_MSG_RESULT([no - AdPlug >= 2.2 required]))

# Check if AdPlug supports NukedOPL
AC_MSG_CHECKING([whether AdPlug supports the NukedOPL synth])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <adplug/nemuopl.h>], [CNemuopl *dummy;])],
   AC_DEFINE(HAVE_ADPLUG_NUKEDOPL,, [Defined if AdPlug supports the NukedOPL synth])
AC_MSG_RESULT([yes]), AC_MSG_RESULT([no - AdPlug >= 2.3 required]))

# Restore flags after compiling test programs
LIBS="$oldlibs"
CPPFLAGS="$oldcppflags"

AC_SUBST(CXXFLAGS, "$CXXFLAGS $SDL_CFLAGS $FFTW3_CFLAGS $adplug_CFLAGS -I./include")
AC_SUBST(LIBS, "$LIBS $SDL_LIBS $FFTW3_LIBS $adplug_LIBS")
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

