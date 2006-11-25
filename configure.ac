dnl
dnl Twin - A Tiny Window System
dnl Copyright © 2003 Keith Packard, Noah Levitt
dnl All rights reserved.
dnl
dnl This Library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Library General Public License as
dnl published by the Free Software Foundation; either version 2 of the
dnl License, or (at your option) any later version.
dnl
dnl This Library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Library General Public License for more details.
dnl
dnl You should have received a copy of the GNU Library General Public
dnl License along with the Gnome Library; see the file COPYING.LIB.  If not,
dnl write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
dnl Boston, MA 02111-1307, USA.
dnl
dnl
dnl Process this file with autoconf to create configure.

AC_PREREQ([2.57])

AC_INIT(libtwin, 0.0.0, [keithp@keithp.com], libtwin)
AM_INIT_AUTOMAKE()
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(twin_def.h)
AC_CONFIG_AUX_DIR(.)

# Check for progs
AC_PROG_CC
AC_PROG_LIBTOOL

WARN_CFLAGS=""

if test "x$GCC" = "xyes"; then
	WARN_CFLAGS="-Wall -Wpointer-arith -Wstrict-prototypes \
	-Wmissing-prototypes -Wmissing-declarations \
	-Wnested-externs -fno-strict-aliasing"
fi
AC_SUBST(WARN_CFLAGS)

# Check for X
PKG_CHECK_MODULES(X, x11, 
		  [x_found_with_pkgconfig=yes],
		  [x_found_with_pkgconfig=no])
AC_SUBST(X_CFLAGS)
AC_SUBST(X_LIBS)

#
#AC_ARG_WITH(freetype-config, [  --with-freetype-config=PROG   Use FreeType configuration program PROG], freetype_config=$withval, freetype_config=yes)
#
#if test "$freetype_config" = "yes"; then 
#	AC_PATH_PROG(ft_config,freetype-config,no)
#	if test "$ft_config" = "no"; then
#		AC_MSG_ERROR([You must have freetype installed; see http://www.freetype.org/])
#	fi
#else
#	ft_config="$freetype_config"
#fi
#
#FREETYPE_CFLAGS="`$ft_config --cflags`"
#FREETYPE_LIBS="`$ft_config --libs`"
#
#AC_SUBST(FREETYPE_LIBS)
#AC_SUBST(FREETYPE_CFLAGS)

AC_OUTPUT([Makefile
           twin.pc])
