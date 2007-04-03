/*
 * Libjpeg interface to twin
 *
 * Copyright 2007 Benjamin Herrenschmidt <benh@kernel.crashing.org>
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
#ifndef _TWIN_JPEG_H_
#define _TWIN_JPEG_H_

#include <libtwin/twin.h>

twin_pixmap_t *twin_jpeg_to_pixmap(const char *filepath, twin_format_t fmt);

#endif /* _TWIN_JPEG_H_ */
