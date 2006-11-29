AM_CFLAGS=-g
INCLUDES= @WARN_CFLAGS@ @FREETYPE_CFLAGS@

EXTRA_PROGRAMS = twin_ttf
bin_PROGRAMS = 

if TWIN_TTF
bin_PROGRAMS += twin_ttf
endif

twin_ttf_SOURCES = \
	twin_ttf.h \
	twin_ttf.c

twin_ttf_LDADD = @FREETYPE_LIBS@ -lm
