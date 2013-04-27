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

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <errno.h>

#include "twinint.h"
#include "twin_linux_touch.h"

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)	((array[LONG(bit)] >> OFF(bit)) & 1)

#if 0
#define DEBUG(fmt...)	printf(fmt)
#else
#define DEBUG(fmt...)
#endif

static int scale_touch_range(int val, int min, int max, int scale_range)
{
	twin_fixed_t ret;

	max -= min;
	val -= min;
	ret = twin_fixed_div(twin_int_to_fixed(val), twin_int_to_fixed(max));
	ret = twin_fixed_mul(ret, twin_int_to_fixed(scale_range));

	return twin_fixed_to_int(ret);
}

static twin_bool_t twin_linux_touch_events(int maybe_unused file,
					   twin_file_op_t maybe_unused ops,
					   void *closure)
{
	twin_linux_touch_t *touch = closure;
	twin_event_t tev;
	struct input_event event;
	int rc;

	rc = read(touch->fd, &event, sizeof(event));
	if (rc < 0 && errno != EAGAIN) {
		perror("error reading input event");
		return TWIN_FALSE;
	} else if (rc != sizeof(event)) {
		/* EAGAIN or rc < sizeof(event)
		 * Linux guarantees reads of at least one event, so ignore */
		return TWIN_TRUE;
	}

	switch (event.type) {
	case EV_ABS:
		switch (event.code) {
		case ABS_X:
			touch->x = scale_touch_range(event.value,
						     touch->min_x, touch->max_x,
						     touch->screen->width);
			break;
		case ABS_Y:
			touch->y = scale_touch_range(event.value,
						     touch->min_y, touch->max_y,
						     touch->screen->height);
			break;
		}
		break;
	case EV_KEY:
		switch (event.code) {
		case BTN_TOUCH:
			touch->btn_state = event.value;
			touch->btn_pending = 1;
			break;
		}
		break;
	case EV_SYN:
		tev.u.pointer.screen_x = touch->x;
		tev.u.pointer.screen_y = touch->y;
		tev.u.pointer.button = touch->btn_state;
		if (touch->btn_pending) {
			tev.kind = touch->btn_state ?
				TwinEventButtonDown : TwinEventButtonUp;
			touch->btn_pending = 0;
		} else {
			tev.kind = TwinEventMotion;
		}
		twin_screen_dispatch(touch->screen, &tev);
		break;
	}

	return TWIN_TRUE;
}

static int get_abs_range(twin_linux_touch_t *touch)
{
	struct input_absinfo absinfo;
	int rc;

	rc = ioctl(touch->fd, EVIOCGABS(ABS_X), &absinfo);
	if (rc < 0) {
		perror("EVIOCGABS X");
		return rc;
	}
	DEBUG("x min %d, max %d\n", absinfo.minimum, absinfo.maximum);

	rc = ioctl(touch->fd, EVIOCGABS(ABS_Y), &absinfo);
	if (rc < 0) {
		perror("EVIOCGABS Y");
		return rc;
	}
	DEBUG("y min %d, max %d\n", absinfo.minimum, absinfo.maximum);

	return 0;
}

static twin_linux_touch_t *twin_linux_touch_probe(twin_screen_t *screen)
{
	twin_linux_touch_t *touch = NULL;
	struct dirent *dirent;
	DIR *dir;

	dir = opendir("/dev/input");
	if (dir == NULL) {
		perror("opendir(/dev/input)");
		return NULL;
	}

	while ((dirent = readdir(dir))) {
		char dev_name[sizeof(dirent->d_name) + sizeof("/dev/input")];

		if (strncmp(dirent->d_name, "event", 5))
			continue;
		snprintf(dev_name, sizeof(dev_name),
			 "/dev/input/%s", dirent->d_name);

		touch = twin_linux_touch_create(dev_name, screen);
		if (touch)
			break;
	}
	closedir(dir);

	return touch;
}

twin_linux_touch_t *twin_linux_touch_create(const char *file, twin_screen_t *screen)
{
	twin_linux_touch_t *touch = NULL;
	unsigned long bits[NBITS(KEY_MAX)];
	int dev_fd;
	int rc;

	/* If file is unspecified, probe all event devices */
	if (!file)
		return twin_linux_touch_probe(screen);

	dev_fd = open(file, O_RDONLY | O_NONBLOCK);
	if (dev_fd < 0) {
		perror("open");
		return NULL;
	}
	DEBUG("Probing event device %s\n", file);
	rc = ioctl(dev_fd, EVIOCGBIT(EV_KEY, KEY_MAX), &bits);
	if (rc < 0) {
		perror("key ioctl");
		goto err_close;
	}
	if (!test_bit(BTN_TOUCH, bits))
		goto err_close;

	rc = ioctl(dev_fd, EVIOCGBIT(EV_ABS, KEY_MAX), &bits);
	if (rc < 0) {
		perror("EVIOCGBIT");
		goto err_close;
	}
	if (!test_bit(ABS_X, bits) || !test_bit(ABS_Y, bits))
		goto err_close;

	touch = calloc(1, sizeof(twin_linux_touch_t));
	if (!touch) {
		rc = -ENOMEM;
		goto err_close;
	}
	touch->fd = dev_fd;
	touch->screen = screen;

	if (get_abs_range(touch))
		goto err_free;
	touch->file = twin_set_file(twin_linux_touch_events, dev_fd, TWIN_READ, touch);
	DEBUG("%s attached as touchscreen\n", file);
	return touch;
err_free:
	free(touch);
err_close:
	close(dev_fd);
	return NULL;
}

void twin_linux_touch_destroy(twin_linux_touch_t *touch)
{
	twin_clear_file(touch->file);
	close(touch->fd);
	free(touch);
}
