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


#define _GNU_SOURCE

#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#include "any.h"
#include "task_arguments.h"

#include "task.h"


struct Task
{
  TaskState state;
  sem_t mutex, join_mutex;
  pthread_t thread;
  Any (*callback)(TaskArguments * arguments);
  Any result;
  TaskArguments * arguments;
};


static void * task_thread_routine(void * task_ptr)
{
  Task * task = (Task *) task_ptr;

  Any result = task->callback(task->arguments);

  sem_wait(&task->mutex);
  task->result = result;
  task->state = TASK_STATE_COMPLETE;
  sem_post(&task->mutex);
  
  return NULL;
}

static void task_add_nanos_to_timespec(struct timespec * time, unsigned long long add)
{
  unsigned long long nanoseconds = time->tv_nsec;
  time_t seconds = time->tv_sec;
  
  nanoseconds += add;
  
  time->tv_sec = seconds + nanoseconds / 1000000000;
  time->tv_nsec = nanoseconds % 1000000000;
}




Task * task_new(Any (*callback)(TaskArguments *))
{
  assert(callback);
  
  Task * task = (Task *) malloc(sizeof(Task));
  assert(task);
  
  sem_init(&task->mutex, 0, 1);
  sem_init(&task->join_mutex, 0, 1);
  task->state = TASK_STATE_NEW;
  task->callback = callback;
  task->result = ptr_to_any(NULL);
  task->arguments = NULL;
  
  return task;
}

void task_destroy(Task * task)
{
  assert(task);
  
  sem_wait(&task->mutex);
  
  if (task->state == TASK_STATE_RUNNING)
    pthread_cancel(task->thread);
    
  if (task->arguments != NULL)
    task_arguments_destroy(task->arguments);

  sem_post(&task->mutex);
  sem_destroy(&task->mutex);
  sem_destroy(&task->join_mutex);
  free(task);
  
}

void task_start(Task * task, TaskArguments * arguments)
{
  assert(task);
  assert(arguments);
  
  sem_wait(&task->mutex);
  sem_wait(&task->join_mutex);
  assert(task->state == TASK_STATE_NEW);
  
  task->arguments = arguments;
  task->state = TASK_STATE_RUNNING;
  pthread_create(&task->thread, NULL, task_thread_routine, (void *) task);
  
  sem_post(&task->join_mutex);
  sem_post(&task->mutex);
  
}

void task_wait_for(Task * task)
{
  assert(task);
  
  sem_wait(&task->mutex);
  assert(task->state != TASK_STATE_NEW);
  
  if (task->state == TASK_STATE_RUNNING)
  {
    sem_post(&task->mutex);
    sem_wait(&task->join_mutex);

    pthread_join(task->thread, NULL);

    sem_post(&task->join_mutex);
  }
  else
    sem_post(&task->mutex);
}
bool task_wait_for_millis(Task * task, unsigned long long millis)
{
  return task_wait_for_nanos(task, millis * 1000000);
}
bool task_wait_for_nanos(Task * task, unsigned long long nanos)
{
  assert(task);
  
  sem_wait(&task->mutex);
  assert(task->state != TASK_STATE_NEW);
  
  if (task->state == TASK_STATE_RUNNING)
  {
    sem_post(&task->mutex);
    
    struct timespec terminate_join_time;
    clock_gettime(CLOCK_REALTIME, &terminate_join_time);
    task_add_nanos_to_timespec(&terminate_join_time, nanos);
    
    if (sem_timedwait(&task->join_mutex, &terminate_join_time))
      return false;
    
    pthread_timedjoin_np(task->thread, NULL, &terminate_join_time);
    
    sem_post(&task->join_mutex);
  }
  else
    sem_post(&task->mutex);
  
  return true;
}
void task_abort(Task * task)
{
  assert(task);
  
  sem_wait(&task->mutex);
  assert(task->state != TASK_STATE_NEW);
  
  if (task->state == TASK_STATE_RUNNING)
    pthread_cancel(task->thread);
  
  sem_post(&task->mutex);
}

Any task_get_result(Task * task)
{
  assert(task);
  Any res;
  
  sem_wait(&task->mutex);
  assert(task->state == TASK_STATE_COMPLETE);
  
  res = task->result;
  sem_post(&task->mutex);
  
  return res;
}
TaskState task_get_state(Task * task)
{
  assert(task);
  TaskState state;
  
  sem_wait(&task->mutex);
  state = task->state;
  sem_post(&task->mutex);
  
  return state;
}
bool task_is_complete(Task * task)
{
  TaskState state = task_get_state(task);
  return state == TASK_STATE_COMPLETE || state == TASK_STATE_ABORTED;
}
bool task_is_running(Task * task)
{
  return task_get_state(task) == TASK_STATE_RUNNING;
}

/* calls wait for, returns result and destroys task */
Any task_await(Task * task)
{
  assert(task);

  task_wait_for(task);
  Any any = task_get_result(task);
  task_destroy(task);
  
  return any;
}


