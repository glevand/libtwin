/*
 * Twin - A Tiny Window System
 * Copyright © 2004 Keith Packard <keithp@keithp.com>
 * All rights reserved.
 *
 * This Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with the Twin Library; see the file COPYING.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <twin_demo.h>

#define maybe_unused __attribute__((unused))
#define D(x) twin_double_to_fixed(x)

#if 0
static int styles[] = {
    TWIN_TEXT_ROMAN,
    TWIN_TEXT_OBLIQUE,
    TWIN_TEXT_BOLD,
    TWIN_TEXT_BOLD|TWIN_TEXT_OBLIQUE
};
#endif

#if 0
static void
twin_example_start (twin_screen_t *screen, int x, int y, int w, int h)
{
    twin_window_t   *window = twin_window_create (screen, TWIN_ARGB32,
						  TwinWindowApplication,
						  x, y, w, h);
    int		    wid = window->client.right - window->client.left;
    int		    hei = window->client.bottom - window->client.top;
    twin_pixmap_t   *pixmap = window->pixmap;
    twin_path_t	    *path = twin_path_create ();
    twin_path_t	    *pen = twin_path_create ();
    twin_pixmap_t   *alpha = twin_pixmap_create (TWIN_A8, w, h);
    twin_operand_t  source, mask;
    
    twin_fill (pixmap, 0xffffffff, TWIN_SOURCE, 0, 0, wid, hei);
    
    twin_window_set_name (window, "example");
    
    twin_path_circle (pen, D (1));
    
    /* graphics here in path */

    twin_fill_path (alpha, path, 0, 0);
    twin_path_destroy (path);
    twin_path_destroy (pen);
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xff000000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (pixmap, 0, 0,
		    &source, 0, 0, &mask, 0, 0, TWIN_OVER, w, h);
    twin_pixmap_destroy (alpha);
    twin_window_show (window);
}
#endif

static void
twin_line_start (twin_screen_t *screen, int x, int y, int w, int h)
{
    twin_window_t   *window = twin_window_create (screen, TWIN_ARGB32,
						  TwinWindowApplication,
						  x, y, w, h);
    twin_pixmap_t   *pixmap = window->pixmap;
    twin_path_t	    *stroke = twin_path_create ();
    twin_fixed_t    fy;
    
    twin_path_translate (stroke, D(200), D(200));
    twin_fill (pixmap, 0xffffffff, TWIN_SOURCE, 
	       0, 0, w, h);

    twin_window_set_name (window, "line");
    
    for (fy = 0; fy < 150; fy += 40)
    {
	twin_path_move (stroke, D(-150), -D(fy));
	twin_path_draw (stroke, D(150), D(fy));
    }
    twin_path_set_cap_style (stroke, TwinCapProjecting);
    twin_paint_stroke (pixmap, 0xff000000, stroke, D(10));
    twin_path_destroy (stroke);
    twin_window_show (window);
}

static void maybe_unused
twin_circletext_start (twin_screen_t *screen, int x, int y, int w, int h)
{
    twin_window_t   *window = twin_window_create (screen, TWIN_ARGB32,
						  TwinWindowApplication,
						  x, y, w, h);
    int		    wid = window->client.right - window->client.left;
    int		    hei = window->client.bottom - window->client.top;
    twin_pixmap_t   *pixmap = window->pixmap;
    twin_path_t	    *path = twin_path_create ();
    twin_path_t	    *pen = twin_path_create ();
    twin_pixmap_t   *alpha = twin_pixmap_create (TWIN_A8, wid, hei);
    int		    s;
    twin_operand_t  source, mask;
    
    twin_fill (pixmap, 0xffffffff, TWIN_SOURCE, 
	       0, 0, wid, hei);
    twin_window_set_name (window, "circletext");
    
    twin_path_set_font_style (path, TWIN_TEXT_UNHINTED);
    twin_path_circle (pen, 0, 0, D (1));
    
    twin_path_translate (path, D(200), D(200));
    twin_path_set_font_size (path, D(15));
    for (s = 0; s < 41; s++)
    {
	twin_state_t	state = twin_path_save (path);
	twin_path_rotate (path, twin_degrees_to_angle (9 * s));
	twin_path_move (path, D(100), D(0));
	twin_path_utf8 (path, "Hello, world!");
	twin_path_restore (path, &state);
    }
    twin_fill_path (alpha, path, 0, 0);
    twin_path_destroy (path);
    twin_path_destroy (pen);
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xff000000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (pixmap, 0, 0,
		    &source, 0, 0, &mask, 0, 0, TWIN_OVER, wid, hei);
    twin_pixmap_destroy (alpha);
    twin_window_show (window);
}

static void maybe_unused
twin_quickbrown_start (twin_screen_t *screen, int x, int y, int w, int h)
{
    twin_window_t   *window = twin_window_create (screen, TWIN_ARGB32,
						  TwinWindowApplication,
						  x, y, w, h);
    int		    wid = window->client.right - window->client.left;
    int		    hei = window->client.bottom - window->client.top;
    twin_pixmap_t   *pixmap = window->pixmap;
    twin_path_t	    *path = twin_path_create ();
    twin_path_t	    *pen = twin_path_create ();
    twin_pixmap_t   *alpha = twin_pixmap_create (TWIN_A8, wid, hei);
    twin_operand_t  source, mask;
    twin_fixed_t    fx, fy;
    int		    s;
    
    twin_window_set_name (window, "Quick Brown");
    
    twin_fill (pixmap, 0xffffffff, TWIN_SOURCE, 
	       0, 0, wid, hei);
    
    twin_path_circle (pen, 0, 0, D (1));
    
    fx = D(3);
    fy = D(8);
    for (s = 6; s < 36; s++)
    {
	twin_path_move (path, fx, fy);
	twin_path_set_font_size (path, D(s));
	twin_path_utf8 (path,
			"the quick brown fox jumps over the lazy dog.");
	twin_path_utf8 (path,
			"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.");
	fy += D(s);
    }

    twin_fill_path (alpha, path, 0, 0);
    twin_path_destroy (path);
    twin_path_destroy (pen);
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xff000000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (pixmap, 0, 0,
		    &source, 0, 0, &mask, 0, 0, TWIN_OVER, wid, hei);
    twin_pixmap_destroy (alpha);
    twin_window_show (window);
}

static void maybe_unused
twin_ascii_start (twin_screen_t *screen, int x, int y, int w, int h)
{
    twin_window_t   *window = twin_window_create (screen, TWIN_ARGB32,
						  TwinWindowApplication,
						  x, y, w, h);
    int		    wid = window->client.right - window->client.left;
    int		    hei = window->client.bottom - window->client.top;
    twin_pixmap_t   *pixmap = window->pixmap;
    twin_path_t	    *path = twin_path_create ();
    twin_path_t	    *pen = twin_path_create ();
    twin_pixmap_t   *alpha = twin_pixmap_create (TWIN_A8, wid, hei);
    twin_operand_t  source, mask;
    twin_fixed_t    fx, fy;
    int		    s;
    
    twin_window_set_name (window, "ASCII");
    
    twin_fill (pixmap, 0xffffffff, TWIN_SOURCE, 0, 0, wid, hei);
    twin_path_circle (pen, 0, 0, D (1));
    
    fx = D(3);
    fy = D(8);
    for (s = 6; s < 36; s += 6)
    {
	twin_path_set_font_size (path, D(s));
        fy += D(s+2);
	twin_path_move (path, fx, fy);
	twin_path_utf8 (path,
			  " !\"#$%&'()*+,-./0123456789:;<=>?");
        fy += D(s+2);
	twin_path_move (path, fx, fy);
	twin_path_utf8 (path,
			  "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
        fy += D(s+2);
	twin_path_move (path, fx, fy);
	twin_path_utf8 (path,
			  "`abcdefghijklmnopqrstuvwxyz{|}~");
	fy += D(s+2);
    }

    twin_fill_path (alpha, path, 0, 0);
    twin_path_destroy (path);
    twin_path_destroy (pen);
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xff000000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (pixmap, 0, 0, 
		    &source, 0, 0, &mask, 0, 0, TWIN_OVER, wid, hei);
    twin_pixmap_destroy (alpha);
    twin_window_show (window);
}

static void maybe_unused
twin_jelly_start (twin_screen_t *screen, int x, int y, int w, int h)
{
    twin_window_t   *window = twin_window_create (screen, TWIN_ARGB32,
						  TwinWindowApplication,
						  x, y, w, h);
    int		    wid = window->client.right - window->client.left;
    int		    hei = window->client.bottom - window->client.top;
    twin_pixmap_t   *pixmap = window->pixmap;
    twin_path_t	    *path = twin_path_create ();
    twin_fixed_t    fx, fy;
    int		    s;
    
    twin_window_set_name (window, "Jelly");
    
    twin_fill (pixmap, 0xffffffff, TWIN_SOURCE, 
	       0, 0, wid, hei);
    
    fx = D(3);
    fy = D(8);
    for (s = 6; s < 36; s += 2)
    {
	twin_path_set_font_size (path, D(s));
	fy += D(s + 2);
	twin_path_move (path, fx, fy);
#define TEXT	"jelly text"
/*	twin_path_set_font_style (path, TWIN_TEXT_UNHINTED); */
	twin_path_utf8 (path, TEXT);
	twin_paint_path (pixmap, 0xff000000, path);
	twin_path_empty (path);
	{
	    twin_text_metrics_t	m;
	    twin_path_t	*stroke = twin_path_create ();
	    twin_path_set_matrix (stroke, twin_path_current_matrix (path));
	    twin_text_metrics_utf8 (path, TEXT, &m);
	    twin_path_translate (stroke, TWIN_FIXED_HALF, TWIN_FIXED_HALF);
	    twin_path_move (stroke, fx, fy);
	    twin_path_draw (stroke, fx + m.width, fy);
	    twin_paint_stroke (pixmap, 0xffff0000, stroke, D(1));
	    twin_path_empty (stroke);
	    twin_path_move (stroke, 
			    fx + m.left_side_bearing, fy - m.ascent);
	    twin_path_draw (stroke,
			    fx + m.right_side_bearing, fy - m.ascent);
	    twin_path_draw (stroke,
			    fx + m.right_side_bearing, fy + m.descent);
	    twin_path_draw (stroke,
			    fx + m.left_side_bearing, fy + m.descent);
	    twin_path_draw (stroke, 
			    fx + m.left_side_bearing, fy - m.ascent);
	    twin_paint_stroke (pixmap, 0xff00ff00, stroke, D(1));
	    twin_path_destroy (stroke);
	}
    }
    twin_window_show (window);
}

void
twin_demo_start (twin_screen_t *screen, const char maybe_unused *name, int x, int y, int w, int h)
{
#if 0
    twin_circletext_start (screen, x, y, w, h);
#endif
    twin_line_start (screen, x += 20, y += 20, w, h);
#if 0
    twin_quickbrown_start (screen, x += 20, y += 20, w, h);
    twin_ascii_start (screen, x += 20, y += 20, w, h);
    twin_jelly_start (screen, x += 20, y += 20, w, h);
#endif
#if 0

#if 0
    path = twin_path_create ();

    twin_path_rotate (path, -TWIN_ANGLE_45);
    twin_path_translate (path, D(10), D(2));
    for (s = 0; s < 40; s++)
    {
	twin_path_rotate (path, TWIN_ANGLE_11_25 / 16);
	twin_path_scale (path, D(1.125), D(1.125));
	twin_path_move (path, D(0), D(0));
	twin_path_draw (path, D(1), D(0));
	twin_path_draw (path, D(1), D(1));
	twin_path_draw (path, D(0), D(1));
    }
    
    twin_fill (alpha, 0x00000000, TWIN_SOURCE, 0, 0, w, h);
    twin_fill_path (alpha, path);
    
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xffff0000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (red, 0, 0, &source, 0, 0, &mask, 0, 0, TWIN_OVER,
		    w, h);
#endif

#if 0
    path = twin_path_create ();
    stroke = twin_path_create ();

    twin_path_translate (stroke, D(62), D(62));
    twin_path_scale (stroke,D(60),D(60));
    for (s = 0; s < 60; s++)
    {
        twin_state_t    save = twin_path_save (stroke);
	twin_angle_t    a = s * TWIN_ANGLE_90 / 15;
	    
	twin_path_rotate (stroke, a);
        twin_path_move (stroke, D(1), 0);
	if (s % 5 == 0)
	    twin_path_draw (stroke, D(0.85), 0);
	else
	    twin_path_draw (stroke, D(.98), 0);
        twin_path_restore (stroke, &save);
    }
    twin_path_convolve (path, stroke, pen);
    twin_fill (alpha, 0x00000000, TWIN_SOURCE, 0, 0, w, h);
    twin_fill_path (alpha, path);
    
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xffff0000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (red, 0, 0, &source, 0, 0, &mask, 0, 0, TWIN_OVER,
		    w, h);
#endif

#if 0
    path = twin_path_create ();
    stroke = twin_path_create ();

    twin_path_translate (stroke, D(100), D(100));
    twin_path_scale (stroke, D(10), D(10));
    twin_path_move (stroke, D(0), D(0));
    twin_path_draw (stroke, D(10), D(0));
    twin_path_convolve (path, stroke, pen);
    
    twin_fill (alpha, 0x00000000, TWIN_SOURCE, 0, 0, w, h);
    twin_fill_path (alpha, path);
    
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xffff0000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (red, 0, 0, &source, 0, 0, &mask, 0, 0, TWIN_OVER,
		    w, h);
#endif
    
#if 1
    path = twin_path_create ();

    stroke = twin_path_create ();
    
    twin_path_move (stroke, D (10), D (40));
    twin_path_draw (stroke, D (40), D (40));
    twin_path_draw (stroke, D (10), D (10));
    twin_path_move (stroke, D (10), D (50));
    twin_path_draw (stroke, D (40), D (50));

    twin_path_convolve (path, stroke, pen);
    twin_path_destroy (stroke);

    twin_fill (alpha, 0x00000000, TWIN_SOURCE, 0, 0, w, h);
    twin_fill_path (alpha, path, 0, 0);
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xff00ff00;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (blue, 0, 0, &source, 0, 0, &mask, 0, 0, TWIN_OVER,
		    100, 100);
    
    twin_path_destroy (path);

    path = twin_path_create ();
    stroke = twin_path_create ();

    twin_path_move (stroke, D (50), D (50));
    twin_path_curve (stroke, D (70), D (70), D (80), D (70), D (100), D (50));

    twin_fill (alpha, 0x00000000, TWIN_SOURCE, 0, 0, w, h);
    twin_fill_path (alpha, stroke, 0, 0);
    
    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xffff0000;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (blue, 0, 0, &source, 0, 0, &mask, 0, 0, TWIN_OVER,
		    100, 100);
    
    twin_path_convolve (path, stroke, pen);
    
    twin_fill (alpha, 0x00000000, TWIN_SOURCE, 0, 0, w, h);
    twin_fill_path (alpha, path, 0, 0);

    source.source_kind = TWIN_SOLID;
    source.u.argb = 0xff0000ff;
    mask.source_kind = TWIN_PIXMAP;
    mask.u.pixmap = alpha;
    twin_composite (blue, 0, 0, &source, 0, 0, &mask, 0, 0, TWIN_OVER,
		    100, 100);
#endif

    twin_window_show (redw);
    twin_window_show (bluew);
#endif
}
