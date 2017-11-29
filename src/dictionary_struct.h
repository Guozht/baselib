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

#ifndef __BASELIB_DICTIONARY_STRUCT_H
#define __BASELIB_DICTIONARY_STRUCT_H

#include <semaphore.h>
#include <stdbool.h>

#include "any.h"
#include "dictionary_type.h"
#include "list.h"


struct Dictionary
{
  DictionaryType type;
  sem_t mutex;
  List * keys;

  void (*dictionary_destroy)(struct Dictionary *);
  void (*dictionary_destroy_and_free)(struct Dictionary *);
  void (*dictionary_destroy_and_user_free)(struct Dictionary *, void (*)(void *));
  void (*dictionary_destroy_and)(struct Dictionary *, void (*)(Any));

  void (*dictionary_clear)(struct Dictionary *);
  void (*dictionary_clear_and_free)(struct Dictionary *);
  void (*dictionary_clear_and_user_free)(struct Dictionary *, void (*)(void *));
  void (*dictionary_clear_and)(struct Dictionary *, void (*)(Any));
  
  bool (*dictionary_has)(struct Dictionary *, char *);
  Any (*dictionary_get)(struct Dictionary *, char *);
  bool (*dictionary_try_get)(struct Dictionary *, char *, Any *);

  void (*dictionary_put)(struct Dictionary *, char *, Any);
  bool (*dictionary_try_put)(struct Dictionary *, char *, Any);

  void (*dictionary_set)(struct Dictionary *, char *, Any);
  void (*dictionary_set_and_free)(struct Dictionary *, char *, Any);
  void (*dictionary_set_and_user_free)(struct Dictionary *, char *, Any, void (*)(void *));
  void (*dictionary_set_and)(struct Dictionary *, char *, Any, void (*)(Any));

  Any (*dictionary_remove)(struct Dictionary *, char *); 
};



#endif


