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

#include "any.h"
#include "list.h"

#include "task_arguments.h"



struct TaskArguments
{
  Any * arguments;
  unsigned int length;
};


TaskArguments * task_arguments_new(List * list)
{
  assert(list);
  
  TaskArguments * ret = (TaskArguments *) malloc(sizeof(TaskArguments));
  assert(ret);

  ret->length = list_size(list);
  ret->arguments = list_to_array(list);
  
  return ret;
}

void task_arguments_destroy(TaskArguments * task_arguments)
{
  assert(task_arguments);
  
  free(task_arguments->arguments);
  free(task_arguments);
}


Any task_arguments_get(TaskArguments * task_arguments, unsigned int index)
{
  assert(task_arguments);
  assert(task_arguments->length > index);
  
  return task_arguments->arguments[index];
}

unsigned int task_arguments_length(TaskArguments * task_arguments)
{
  return task_arguments->length;  
}

