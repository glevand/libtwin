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

AC_INIT(libtwin, 0.0.1, [keithp@keithp.com], libtwin)
AC_CONFIG_AUX_DIR(.)
AM_INIT_AUTOMAKE()
AM_MAINTAINER_MODE

# Library versioning info
LIB_VERSION_CURRENT=0
LIB_VERSION_REVISION=1
LIB_VERSION_AGE=0
LIB_VERSION="$LIB_VERSION_CURRENT:$LIB_VERSION_REVISION:$LIB_VERSION_AGE"
AC_SUBST(LIB_VERSION)

AM_CONFIG_HEADER(twin_def.h)

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
PKG_CHECK_MODULES(X, x11, twin_x11="yes", twin_x11="no")
AC_SUBST(X_CFLAGS)
AC_SUBST(X_LIBS)

# Check for linux framebuffer includes
AC_CHECK_HEADER(linux/fb.h, twin_fb="yes", twin_fb="no")

# linux mouse
AC_ARG_ENABLE(linux-mouse,
	AC_HELP_STRING([--disable-linux-mouse], [Disable linux mouse support]),
	twin_mouse="$enableval", twin_mouse="yes")

# Check for freetype
PKG_CHECK_MODULES(FREETYPE, freetype2, twin_ttf="yes", twin_ttf="no")
AC_SUBST(FREETYPE_LIBS)
AC_SUBST(FREETYPE_CFLAGS)

# TWIN_DEP_*FLAGS define all flags required by dependencies of libtwin
TWIN_DEP_LDFLAGS="$X_LIBS -lm"
TWIN_DEPCFLAGS="$X_CFLAGS"
AC_SUBST(TWIN_DEP_CFLAGS)
AC_SUBST(TWIN_DEP_LDFLAGS)

AM_CONDITIONAL(TWIN_X11, test x$twin_x11 = xyes)
AM_CONDITIONAL(TWIN_FB, test x$twin_fb = xyes)
AM_CONDITIONAL(TWIN_TTF, test x$twin_ttf = xyes)
AM_CONDITIONAL(TWIN_MOUSE, test x$twin_mouse = xyes)

AC_MSG_NOTICE([x11 support:    $twin_x11])
AC_MSG_NOTICE([fb support:     $twin_fb])
AC_MSG_NOTICE([twin_ttf tool:  $twin_ttf])
AC_MSG_NOTICE([linux mouse:    $twin_mouse])

AC_OUTPUT([Makefile
           twin.pc])
