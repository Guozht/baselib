/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                         *
 *  baselib: a library implementing several simple utilities for C         *
 *  Copyright (C) 2017  LeqxLeqx                                           *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __BASELIB_MTEST_H
#define __BASELIB_MTEST_H

#include <sys/types.h>


#ifdef MTEST_DEBUG

#define _malloc(s) mtest_malloc(s)
#define _calloc(s, c) mtest_calloc(s, c)
#define _realloc(p, s) mtest_realloc(p, s)
#define _free(p) mtest_free(p)

#else

#define _malloc(s) malloc(s)
#define _calloc(s, c) calloc(s, c)
#define _realloc(p, s) realloc(p, s)
#define _free(p) free(p)

#endif


void mtest_init();
void mtest_deinit();

void * mtest_malloc(size_t allocation_size);
void * mtest_calloc(size_t size, size_t count);
void * mtest_realloc(void * pointer, size_t reallocation_size);
void mtest_free(void * pointer);

int mtest_allocations();


#endif
