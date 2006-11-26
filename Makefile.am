INCLUDES= @X_CFLAGS@ @WARN_CFLAGS@

SUBDIRS=twin_ttf

#libtwin_la_SOURCES = \
#	twin.h \
#	twin_draw.c \
#	twin_pixmap.c \
#	twin_primitive.c \
#	twin_screen.c \
#	twin_x11.c \
#	twinint.h
#
#lib_LTLIBRARIES = libtwin.la

bin_PROGRAMS = xtwin ftwin

base_SOURCES = \
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
	twinint.h \
	twin_clock.c \
	twin_clock.h \
	twin_calc.c \
	twin_calc.h \
	twin_text.c \
	twin_text.h

xtwin_SOURCES = $(base_SOURCES) \
	twin_x11.c \
	twin_x11.h \
	twin_demo.c \
	twin_demo.h \
	twin_hello.c \
	twin_hello.h \
	twin_demoline.c \
	twin_demoline.h \
	twin_demospline.c \
	twin_demospline.h \
	xtwin.c

ftwin_SOURCES = $(base_SOURCES) \
	twin_fbdev.c \
	twin_fbdev.h \
	twin_linux_mouse.c \
	twin_linux_mouse.h \
	twin_demo.c \
	twin_demo.h \
	twin_hello.c \
	twin_hello.h \
	twin_demoline.c \
	twin_demoline.h \
	twin_demospline.c \
	twin_demospline.h \
	ftwin.c

xtwin_LDADD = @X_LIBS@ -lm

ftwin_LDADD = -lm
