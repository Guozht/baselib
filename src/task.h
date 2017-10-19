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


#ifndef __BASELIB_TASK_H
#define __BASELIB_TASK_H

#include <stdbool.h>

#include "task_arguments.h"
#include "any.h"

struct Task;
typedef struct Task Task;

enum TaskState
{
  TASK_STATE_NEW = 0,
  TASK_STATE_RUNNING = 1,
  TASK_STATE_COMPLETE = 2,
  TASK_STATE_ABORTED = 6,
};
typedef enum TaskState TaskState;


Task * task_new(Any (*callback)(TaskArguments *));
void task_destroy(Task * task);

void task_start(Task * task, TaskArguments * arguments);

void task_wait_for(Task * task);
bool task_wait_for_millis(Task * task, unsigned long long millis);
bool task_wait_for_nanos(Task * task, unsigned long long nanos);
void task_abort(Task * task);

Any task_get_result(Task * task);
TaskState task_get_state(Task * task);
bool task_is_complete(Task * task);
bool task_is_running(Task * task);

/* calls wait for, returns result and destroys task */
Any task_await(Task * task);


#endif

