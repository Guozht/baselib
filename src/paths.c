
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "mtest.h"
#include "strings.h"
#include "string_builder.h"

#include "paths.h"

static List * paths_to_list_imp(char * path, bool * rooted_ptr)
{
  if (strings_equals(path, "/"))
  {
    if (rooted_ptr)
      *rooted_ptr = true;
    return list_new(LIST_TYPE_ARRAY_LIST);
  }

  bool
    starts_with_slash = strings_starts_with(path, "/"),
    ends_with_slash = strings_ends_with(path, "/");

  path = strings_substring(
      path,
      starts_with_slash ? 1 : 0,
      strings_length(path) - (ends_with_slash ? 1 : 0)
    );
  if (rooted_ptr)
    *rooted_ptr = starts_with_slash;

  List * list = strings_split(path, '/');
  _free(path);


  if (list_contains(list, str_to_any("")))
  {
    list_destroy_and_free(list);
    return NULL;
  }

  return list;
}

static void paths_normalize_imp(List * list)
{
  list_remove_and_free(list, str_to_any("."));
  char * current, * last;

  for (unsigned int k = 0; k < list_size(list); k++)
  {
    current = any_to_str(list_get(list, k));
    if (k != 0 && strings_equals(current, ".."))
    {
      last = any_to_string(list_get(list, k - 1));
      if (!strings_equals(last, ".."))
      {
        list_remove_at(list, k);
        list_remove_at(list, k - 1);
        _free(current);
        _free(last);
        k -= 2;
      }
    }
  }
}

static char * paths_list_to_string(List * list, bool base_rooted)
{
  StringBuilder * sb = string_builder_new();

  if (base_rooted)
    string_builder_append_char(sb, '/');

  if (list_size(list) == 0)
  {
    if (!base_rooted)
      string_builder_append_char(sb, '.');
    return string_builder_to_string_destroy(sb);
  }

  string_builder_append(sb, any_to_str(list_get(list, 0)));
  for (unsigned int k = 1; k < list_size(list); k++)
  {
    string_builder_append_char(sb, '/');
    string_builder_append(sb, any_to_str(list_get(list, k)));
  }

  return string_builder_to_string_destroy(sb);
}

static bool paths_ascends_hierarchy_imp(List * list)
{
  bool ret;

  if (list_size(list) == 0)
    ret = false;
  else
    ret = strings_equals(list_get_str(list, 0), "..");

  return ret;
}


List * paths_get_last_common_ancestor_imp(List * list1, List * list2)
{
  List * ret;
  char * entry;
  bool continue_loop;
  
  ret = list_new(LIST_TYPE_LINKED_LIST);

  continue_loop = true;
  for (unsigned int k = 0; continue_loop && k < list_size(list1) &&
                                            k < list_size(list2); k++)
  {
    entry = list_get_str(list1, k);
    continue_loop = strings_equals(entry, list_get_str(list2, k));
    if (continue_loop)
      list_add(ret, str_to_any(strings_clone(entry)));
  }

  return ret;
}

char * paths_resolve(char * base, char * path)
{
  List * base_list, * path_list;
  bool base_rooted;
  char * ret;

  assert(!strings_is_null_or_empty(base));
  assert(!strings_is_null_or_empty(path));

  base_list = paths_to_list_imp(base, &base_rooted);
  if (!base_list)
    return NULL;

  path_list = paths_to_list_imp(path, NULL);
  if (!path_list)
  {
    list_destroy_and_free(base_list);
    return NULL;
  }

  list_add_range(base_list, path_list);
  paths_normalize_imp(base_list);

  ret = paths_list_to_string(base_list, base_rooted);

  list_destroy_and_free(base_list);
  list_destroy(path_list); /* contents not freed as strings are added
                              to the other list */

  return ret;
}

char * paths_normalize(char * path)
{
  List * list;
  char * ret;
  bool path_rooted;

  assert(!strings_is_null_or_empty(path));

  list = paths_to_list_imp(path, &path_rooted);
  if (!list)
    return NULL;

  paths_normalize_imp(list);
  ret = paths_list_to_string(list, path_rooted);
  
  list_destroy_and_free(list);

  return ret;
}


char * paths_get_parent(char * path)
{
  List * list;
  char * ret;
  bool rooted;

  assert(!strings_is_null_or_empty(path));
  
  list = paths_to_list_imp(path, &rooted);
  if (!list)
    return NULL;

  assert(!rooted || list_size(list) != 0);

  if (list_size(list) == 0)
    ret = strings_clone("..");
  else
  {
    _free(any_to_str(list_remove_at(list, list_size(list) - 1)));
    ret = paths_list_to_string(list, rooted);
  }
  
  list_destroy_and_free(list);

  return ret;
}

char * paths_get_relative_to(char * from, char * path)
{
  List * from_list, * path_list, * common_ancestor, * ret_list;
  char * ret;
  unsigned int from_depth;
  bool rooted1, rooted2;

  assert(!paths_ascends_hierarchy(from));
  assert(!paths_ascends_hierarchy(path));

  from_list = paths_to_list_imp(from, &rooted1);
  if (!from_list)
    return NULL;
  path_list = paths_to_list_imp(path, &rooted2);
  if (!path_list)
  {
    list_destroy_and_free(from_list);
    return NULL;
  }

  paths_normalize_imp(from_list);
  paths_normalize_imp(path_list);

  assert(rooted1 == rooted2);
  /* id est, they must either both be realtive or both absolute */

  common_ancestor = paths_get_last_common_ancestor_imp(from_list, path_list);
  ret_list = list_new(LIST_TYPE_LINKED_LIST);

  from_depth = list_size(from_list) - list_size(common_ancestor);

  for (unsigned int k = 0; k < from_depth; k++)
  {
    list_add(ret_list, str_to_any(".."));
  }
  for (unsigned int k = list_size(common_ancestor);
       k < list_size(path_list);
       k++)
  {
    list_add(ret_list, str_to_any(list_get_str(path_list, k)));
  }
  
  ret = paths_list_to_string(ret_list, false);

  list_destroy_and_free(from_list);
  list_destroy_and_free(path_list);
  list_destroy_and_free(common_ancestor);
  list_destroy(ret_list);

  return ret;
}

char * paths_get_last_common_ancestor(char * path1, char * path2)
{
  List * list1, * list2, * ret_list;
  char * ret;
  bool rooted1, rooted2;

  assert(!paths_ascends_hierarchy(path1));
  assert(!paths_ascends_hierarchy(path2));

  list1 = paths_to_list_imp(path1, &rooted1);
  if (!list1)
    return NULL;
  list2 = paths_to_list_imp(path2, &rooted2);
  if (!list2)
  {
    list_destroy_and_free(list1);
    return NULL;
  }

  paths_normalize_imp(list1);
  paths_normalize_imp(list2);

  assert(rooted1 == rooted2);
  /* id est, they must either both be realtive or both absolute */

  ret_list = paths_get_last_common_ancestor_imp(list1, list2);
  ret = paths_list_to_string(ret_list, rooted1);

  list_destroy_and_free(ret_list);
  list_destroy_and_free(list1);
  list_destroy_and_free(list2);

  return ret;
}

List * paths_to_list(char * path)
{
  assert(!strings_is_null_or_empty(path));

  return paths_to_list_imp(path, NULL);
}

bool paths_ascends_hierarchy(char * path)
{
  List * list;
  bool ret;

  list = paths_to_list_imp(path, NULL);
  if (!list)
    return NULL;
  paths_normalize_imp(list);

  ret = paths_ascends_hierarchy_imp(list);
  list_destroy_and_free(list);

  return ret;
}
bool paths_equals(char * path1, char * path2)
{
  List * list1, * list2;
  bool rooted1, rooted2, ret;

  list1 = paths_to_list_imp(path1, &rooted1);
  if (!list1)
    return NULL;

  list2 = paths_to_list_imp(path2, &rooted2);
  if (!list2)
  {
    list_destroy_and_free(list1);
    return NULL;
  }



  if (rooted1 != rooted2)
    ret = false;
  else
  {
    paths_normalize_imp(list1);
    paths_normalize_imp(list2);

    if (list_size(list1) != list_size(list2))
      ret = false;
    else
    {
      ret = true;
      for (unsigned int k = 0; ret &&  k < list_size(list1); k++)
      {
        if (!strings_equals(
          list_get_str(list1, k),
          list_get_str(list2, k)
          ))
          ret = false;
      }
    }
  }

  list_destroy_and_free(list1);
  list_destroy_and_free(list2);

  return ret;
}

bool paths_is_absolute(char * path)
{
  assert(!strings_is_null_or_empty(path));

  return path[0] == '/';
}

bool paths_is_relative(char * path)
{
  return !paths_is_absolute(path);
}

bool paths_is_ancestor_of(char * ancestor, char * path)
{
  List * ancestor_list, * path_list;
  bool ancestor_rooted, path_rooted, ret;

  assert(!strings_is_null_or_empty(path));

  ancestor_list = paths_to_list_imp(ancestor, &ancestor_rooted);
  if (!ancestor_list)
    return NULL;
  path_list = paths_to_list_imp(path, &path_rooted);
  if (!path_list)
  {
    list_destroy_and_free(ancestor_list);
    return NULL;
  }

  paths_normalize_imp(ancestor_list);
  paths_normalize_imp(path_list);

  if (ancestor_rooted != path_rooted ||
      list_size(ancestor_list) > list_size(path_list))
    ret = false;
  else
  {
    ret = true;
    for (unsigned int k = 0; ret && k < list_size(ancestor_list); k++)
    {
      if (!strings_equals(
            list_get_str(ancestor_list, k),
            list_get_str(path_list, k)
            ))
        ret = false;
    }
  }

  list_destroy_and_free(ancestor_list);
  list_destroy_and_free(path_list);

  return ret;
}

bool paths_is_parent_of(char * ancestor, char * path)
{
  List * ancestor_list, * path_list;
  bool ancestor_rooted, path_rooted, ret;

  assert(!strings_is_null_or_empty(path));

  ancestor_list = paths_to_list_imp(ancestor, &ancestor_rooted);
  if (!ancestor_list)
    return false;
  path_list = paths_to_list_imp(path, &path_rooted);
  if (!path_list)
  {
    list_destroy_and_free(ancestor_list);
    return false;
  }

  paths_normalize_imp(ancestor_list);
  paths_normalize_imp(path_list);

  if (ancestor_rooted != path_rooted ||
      list_size(ancestor_list) != list_size(path_list) - 1)
    ret = false;
  else
  {
    ret = true;
    for (unsigned int k = 0; ret && k < list_size(ancestor_list); k++)
    {
      if (!strings_equals(
            list_get_str(ancestor_list, k),
            list_get_str(path_list, k)
            ))
        ret = false;
    }
  }

  list_destroy_and_free(ancestor_list);
  list_destroy_and_free(path_list);

  return ret;
}
