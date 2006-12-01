AM_CFLAGS = @WARN_CFLAGS@

EXTRA_PROGRAMS =

bin_PROGRAMS =
lib_LTLIBRARIES = libtwin.la
pkginclude_HEADERS = twin.h twin_def.h

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

if TWIN_X11
pkginclude_HEADERS += twin_x11.h
libtwin_la_SOURCES += twin_x11.c
endif

if TWIN_FB
pkginclude_HEADERS += twin_fbdev.h
libtwin_la_SOURCES += twin_fbdev.c
endif

if TWIN_MOUSE
pkginclude_HEADERS += twin_linux_mouse.h
libtwin_la_SOURCES += twin_linux_mouse.c
endif

# demo twin applications
EXTRA_PROGRAMS += twin_demos/xtwin twin_demos/ftwin
noinst_PROGRAMS =
noinst_LIBRARIES = twin_demos/libtwin_demos.a

if TWIN_X11
noinst_PROGRAMS += twin_demos/xtwin
endif

if TWIN_FB
noinst_PROGRAMS += twin_demos/ftwin
endif

twin_demos_xtwin_SOURCES = twin_demos/xtwin.c
twin_demos_xtwin_CFLAGS = @TWIN_DEP_CFLAGS@ -I$(top_srcdir)/twin_demos
twin_demos_xtwin_LDADD = twin_demos/libtwin_demos.a libtwin.la \
	@TWIN_DEP_LDFLAGS@

twin_demos_ftwin_SOURCES = twin_demos/ftwin.c
twin_demos_ftwin_CFLAGS = @TWIN_DEP_CFLAGS@ -I$(top_srcdir)/twin_demos
twin_demos_ftwin_LDADD = twin_demos/libtwin_demos.a libtwin.la \
	@TWIN_DEP_LDFLAGS@

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
EXTRA_PROGRAMS += twin_ttf/twin_ttf

if TWIN_TTF
bin_PROGRAMS += twin_ttf/twin_ttf
endif

twin_ttf_twin_ttf_SOURCES = \
	twin_ttf/twin_ttf.h \
	twin_ttf/twin_ttf.c

twin_ttf_twin_ttf_LDADD = @FREETYPE_LIBS@ -lm
twin_ttf_twin_ttf_CFLAGS = -g @WARN_CFLAGS@
twin_ttf_twin_ttf_CPPFLAGS = @FREETYPE_CFLAGS@ -I$(top_srcdir)/twin_ttf
