AM_CFLAGS = @WARN_CFLAGS@
AM_LDFLAGS = -version-info @LIB_VERSION@

SUBDIRS=twin_ttf

EXTRA_PROGRAMS = xtwin ftwin

bin_PROGRAMS =
lib_LTLIBRARIES = libtwin.la

if TWIN_X11
bin_PROGRAMS += xtwin
lib_LTLIBRARIES += libtwin-x11.la
endif

if TWIN_FB
bin_PROGRAMS += ftwin
lib_LTLIBRARIES += libtwin-fbdev.la
endif

if TWIN_MOUSE
lib_LTLIBRARIES += libtwin-mouse.la
endif

libtwin_la_SOURCES = \
	twin.h \
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

libtwin_mouse_la_LDFLAGS = -version-info=@PACKAGE_VERSION@
libtwin_mouse_la_SOURCES = twin_linux_mouse.c \
	twin_linux_mouse.h

demo_sources = twin_demo.c \
	twin_demo.h \
	twin_hello.c \
	twin_hello.h \
	twin_demoline.c \
	twin_demoline.h \
	twin_demospline.c \
	twin_demospline.h \
	twin_clock.c \
	twin_clock.h \
	twin_calc.c \
	twin_calc.h \
	twin_text.c \
	twin_text.h

libtwin_x11_la_SOURCES = twin_x11.c twin_x11.h
libtwin_x11_la_CPPFLAGS = @X_CFLAGS@

xtwin_SOURCES =	xtwin.c $(demo_sources)
xtwin_CPPFLAGS = @X_CFLAGS@
xtwin_LDADD = libtwin.la libtwin-x11.la @X_LIBS@ -lm

libtwin_fbdev_la_SOURCES = twin_fbdev.c twin_fbdev.h

ftwin_SOURCES = ftwin.c $(demo_sources)
ftwin_LDADD = libtwin.la libtwin-fbdev.la libtwin-mouse.la -lm
