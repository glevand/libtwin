AM_CFLAGS = @WARN_CFLAGS@

EXTRA_PROGRAMS = xtwin ftwin twin_ttf

bin_PROGRAMS =
lib_LTLIBRARIES = libtwin.la
pkginclude_HEADERS = twin.h twin_def.h

if TWIN_X11
bin_PROGRAMS += xtwin
lib_LTLIBRARIES += libtwin-x11.la
pkginclude_HEADERS += twin_x11.h
endif

if TWIN_FB
bin_PROGRAMS += ftwin
lib_LTLIBRARIES += libtwin-fbdev.la
pkginclude_HEADERS += twin_fbdev.h
endif

if TWIN_MOUSE
lib_LTLIBRARIES += libtwin-mouse.la
pkginclude_HEADERS += twin_linux_mouse.h
endif

libtwin_la_LDFLAGS = -version-info @LIB_VERSION@
libtwin_la_SOURCES = \
	twin_box.c \
	twin_button.c \
	twin_convolve.c \
	twin_cursor.c \
	twin_dispatch.c \
	twin_draw.c \
	twin_hull.c \
	twin_icon.c \
	twin_file.c \
	twin_fixed.c \
	twin_font.c \
	twin_font_default.c \
	twin_geom.c \
	twin_label.c \
	twin_matrix.c \
	twin_path.c \
	twin_pattern.c \
	twin_pixmap.c \
	twin_poly.c \
	twin_primitive.c \
	twin_queue.c \
	twin_screen.c \
	twin_spline.c \
	twin_timeout.c \
	twin_toplevel.c \
	twin_trig.c \
	twin_widget.c \
	twin_window.c \
	twin_work.c \
	twinint.h

libtwin_mouse_la_LDFLAGS = -version-info @LIB_VERSION@
libtwin_mouse_la_SOURCES = twin_linux_mouse.c

libtwin_x11_la_CPPFLAGS = @X_CFLAGS@
libtwin_x11_la_LDFLAGS = -version-info @LIB_VERSION@
libtwin_x11_la_SOURCES = twin_x11.c

xtwin_SOURCES =	xtwin.c
xtwin_CPPFLAGS = @X_CFLAGS@ -I$(top_srcdir)/twin_demos
xtwin_LDADD = twin_demos/libtwin_demos.a \
	libtwin.la libtwin-x11.la @X_LIBS@ -lm

libtwin_fbdev_la_LDFLAGS = -version-info @LIB_VERSION@
libtwin_fbdev_la_SOURCES = twin_fbdev.c

ftwin_SOURCES = ftwin.c
ftwin_CPPFLAGS = -I$(top_srcdir)/twin_demos
ftwin_LDADD = twin_demos/libtwin_demos.a \
	libtwin.la libtwin-fbdev.la libtwin-mouse.la -lm

# demo twin applications
noinst_LIBRARIES = twin_demos/libtwin_demos.a

twin_demos_libtwin_demos_a_CFLAGS = @WARN_CFLAGS@ -I$(top_srcdir)/twin_demos
twin_demos_libtwin_demos_a_SOURCES = \
	twin_demos/twin_calc.c twin_demos/twin_calc.h \
	twin_demos/twin_clock.c twin_demos/twin_clock.h \
	twin_demos/twin_demo.c twin_demos/twin_demo.h \
	twin_demos/twin_demoline.c twin_demos/twin_demoline.h \
	twin_demos/twin_demospline.c twin_demos/twin_demospline.h \
	twin_demos/twin_hello.c twin_demos/twin_hello.h \
	twin_demos/twin_text.c twin_demos/twin_text.h

# twin_ttf
if TWIN_TTF
bin_PROGRAMS += twin_ttf/twin_ttf
endif

twin_ttf_twin_ttf_SOURCES = \
	twin_ttf/twin_ttf.h \
	twin_ttf/twin_ttf.c

twin_ttf_twin_ttf_LDADD = @FREETYPE_LIBS@ -lm
twin_ttf_twin_ttf_CFLAGS = -g @WARN_CFLAGS@
twin_ttf_twin_ttf_CPPFLAGS = @FREETYPE_CFLAGS@ -I$(top_srcdir)/twin_ttf
