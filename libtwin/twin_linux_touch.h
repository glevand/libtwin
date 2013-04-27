/*
 * Linux touchscreen driver for Twin
 *
 * Copyright 2013 Tyler Hall <tylerwhall@gmail.com>
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
#ifndef _TWIN_LINUX_TOUCH_H_
#define _TWIN_LINUX_TOUCH_H_

#include <libtwin/twin.h>

typedef struct _twin_linux_touch {
	twin_screen_t *screen;
	twin_file_t *file;

	int fd;
	int x, y;
	int min_x, max_x;
	int min_y, max_y;
	int btn_state;
	int btn_pending;
} twin_linux_touch_t;

/**
 * twin_linux_touch_create - create the linux touchscreen driver
 * @file: device file to open. Pass NULL to use first available
 */
twin_linux_touch_t *twin_linux_touch_create(const char *file, twin_screen_t *screen);

/**
 * twin_linux_touch_destroy - destroy the linux touchscreen driver
 */
void twin_linux_touch_destroy(twin_linux_touch_t *touch);

#endif /* _TWIN_LINUX_TOUCH_H_ */
