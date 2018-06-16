

#ifndef __BASELIB_PATHS_H
#define __BASELIB_PATHS_H

#include <stdbool.h>

#include "list.h"



char * paths_normalize(char * path);
char * paths_resolve(char * base, char * path);

char * paths_get_parent(char * path);
char * paths_get_relative_to(char * from, char * path);
char * paths_get_last_common_ancestor(char * path1, char * path2);

List * paths_to_list(char * path);

bool paths_ascends_hierarchy(char * path);
bool paths_equals(char * path1, char * path2);

bool paths_is_absolute(char * path);
bool paths_is_relative(char * path);

bool paths_is_ancestor_of(char * ancestor, char * path);
bool paths_is_parent_of(char * ancestor, char * path);


#endif


