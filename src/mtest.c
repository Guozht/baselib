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

#include <assert.h>
#include <stdlib.h>
#include <semaphore.h>


#include "mtest.h"


static int _mtest_allocations;
static sem_t _mtest_mutex;


static void mtest_aug_allocations(int value)
{

  sem_wait(&_mtest_mutex);

  _mtest_allocations += value;
  assert(_mtest_allocations >= 0);

  sem_post(&_mtest_mutex);

}


void mtest_init()
{
  _mtest_allocations = 0;
  sem_init(&_mtest_mutex, 0, 1);
}

void mtest_deinit()
{
  sem_destroy(&_mtest_mutex);
}


void * mtest_malloc(size_t allocation_size)
{
  mtest_aug_allocations(1);
  return malloc(allocation_size);
}

void * mtest_calloc(size_t size, size_t count)
{
  mtest_aug_allocations(1);
  return calloc(size, count);
}


void * mtest_realloc(void * pointer, size_t reallocation_size)
{
  return realloc(pointer, reallocation_size);
}


void mtest_free(void * pointer)
{
  mtest_aug_allocations(-1);
  free(pointer);
}




int mtest_allocations()
{
  int ret;

  sem_wait(&_mtest_mutex);
  ret = _mtest_allocations;
  sem_post(&_mtest_mutex);

  return ret;
}
