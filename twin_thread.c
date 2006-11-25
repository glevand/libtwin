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

#include "twinint.h"

void
twin_mutex_init (twin_mutex_t *mutex)
{
#if HAVE_PTHREAD_H
    pthread_mutex_init (mutex, NULL);
#endif
}

void
twin_mutex_lock (twin_mutex_t *mutex)
{
#if HAVE_PTHREAD_H
    pthread_mutex_lock (mutex);
#endif
}

void
twin_mutex_unlock (twin_mutex_t *mutex)
{
#if HAVE_PTHREAD_H
    pthread_mutex_unlock (mutex);
#endif
}

void
twin_cond_init (twin_cond_t *cond)
{
#if HAVE_PTHREAD_H
    pthread_cond_init (cond, NULL);
#endif
}

void
twin_cond_broadcast (twin_cond_t *cond)
{
#if HAVE_PTHREAD_H
    pthread_cond_broadcast (cond);
#else
    OOPS - need some synchronization mechanism
#endif
}

void
twin_cond_wait (twin_cond_t *cond, twin_mutex_t *mutex)
{
#if HAVE_PTHREAD_H
    pthread_cond_wait (cond, mutex);
#else
    OOPS - need some synchronization mechanism
#endif
}

int
twin_thread_create (twin_thread_t *thread, twin_thread_func_t func, void *arg)
{
    return pthread_create (thread, NULL, func, arg);
}
