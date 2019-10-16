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

AC_INIT([sadplay], [1.0])
AM_INIT_AUTOMAKE([foreign parallel-tests color-tests])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX

AX_CODE_COVERAGE

dnl Check for SDL
SDL_VERSION=2.0
AM_PATH_SDL2($SDL_VERSION,
        :,
        AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AX_FFTW3()

AC_SUBST(CXXFLAGS, "$CXXFLAGS $SDL_CFLAGS $FFTW3_CFLAGS -I./include")
AC_SUBST(LIBS, "$LIBS $SDL_LIBS $FFTW3_LIBS")
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

