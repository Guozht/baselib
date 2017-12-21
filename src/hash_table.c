
#include <assert.h>
#include <semaphore.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "dictionary.h"
#include "dictionary_struct.h"
#include "dictionary_type.h"
#include "linked_list.h"
#include "list.h"
#include "strings.h"

#include "hash_table.h"


#define HASH_TABLE_TABLE_SIZE 0xFF


struct HashTableNode
{
  struct HashTableNode * next;
  char * key;
  Any value;
};

struct HashTable
{
  Dictionary base;
  struct HashTableNode ** data;
};


/* internals */

static struct HashTableNode * hash_table_node_new(char * key, Any value)
{
  struct HashTableNode * ret = (struct HashTableNode *) malloc(sizeof(struct HashTableNode));
  assert(ret);

  ret->key = strings_clone(key);
  ret->value = value;
  ret->next = NULL;

  return ret;
}

static void hash_table_node_destroy(struct HashTableNode * node)
{
  if (node->key)
    free(node->key);
  free(node);
}

static struct HashTableNode ** hash_table_node_get(HashTable * table, char * key)
{
  uint32_t index;
  if (key)
    index = ((uint32_t) strings_hash(key)) % HASH_TABLE_TABLE_SIZE;
  else
    index = 0;

  return &table->data[index];
}

static bool hash_table_node_find(struct HashTableNode * node, char * key, Any ** any, struct HashTableNode ** last_node)
{
  while (node)
  {
    if (strings_equals(key, node->key))
    {
      *any = &node->value;
      return true;
    }

    node = node->next;
  }

  if (last_node)
    *last_node = node;
  return false;
}

static void hash_table_node_remove(LinkedList * keys, struct HashTableNode ** root, char * key, Any * value)
{
  struct HashTableNode ** last_next = root, * current = *root;
  while (current)
  {
    if (strings_equals(current->key, key))
    {
      *last_next = current->next;
      *value = current->value;
      hash_table_node_destroy(current);
      linked_list_remove_and_free(keys, str_to_any(key));
      return;
    }

    last_next = &current->next;
    current = current->next;
  }

}

static void hash_table_set_imp(HashTable * hash_table, char * key, Any value, void * callback, bool callback_for_pointer)
{
  sem_wait(&hash_table->base.mutex);

  struct HashTableNode ** node = hash_table_node_get(hash_table, key);
  if (*node)
  {
    Any * ptr;
    struct HashTableNode * last_node;
    if (hash_table_node_find(*node, key, &ptr, &last_node))
    {
      if (callback)
      {
        if (callback_for_pointer)
          ((void (*)(void *)) callback)(any_to_ptr(*ptr));
        else
          ((void (*)(Any)) callback)(*ptr);
      }
      *ptr = value;
    }
    else
    {
      last_node->next = hash_table_node_new(key, value);
      linked_list_add((LinkedList *) hash_table->base.keys, str_to_any(strings_clone(key)));
    }
  }
  else
  {
    *node = hash_table_node_new(key, value);
    linked_list_add((LinkedList *) hash_table->base.keys, str_to_any(strings_clone(key)));
  }

  sem_post(&hash_table->base.mutex);
}

static void hash_table_clear_tree(struct HashTableNode * node, void * callback, bool callback_for_pointer)
{
  if (callback)
  {
    if (callback_for_pointer)
      ((void (*)(void *)) callback)(any_to_ptr(node->value));
    else
      ((void (*)(Any)) callback)(node->value);

  }

  struct HashTableNode * next = node->next;
  hash_table_node_destroy(node);

  if (next)
    hash_table_clear_tree(next, callback, callback_for_pointer);
}

static void hash_table_clear_imp(HashTable * hash_table, void * callback, bool callback_for_pointer)
{
  struct HashTableNode * node;
  for (unsigned int k = 0; k < HASH_TABLE_TABLE_SIZE; k++)
  {
    node = hash_table->data[k];
    if (node)
    {
      hash_table_clear_tree(node, callback, callback_for_pointer);
    }
  }

  memset(hash_table->data, 0, sizeof(struct HashTableNode *) * HASH_TABLE_TABLE_SIZE);

  linked_list_clear_and_free((LinkedList *) hash_table->base.keys);
}

static void hash_table_destroy_imp(HashTable * hash_table, void * callback, bool callback_for_pointer)
{
  hash_table_clear_imp(hash_table, callback, callback_for_pointer);

  sem_destroy(&hash_table->base.mutex);

  linked_list_destroy_and_free((LinkedList *) hash_table->base.keys);
  free(hash_table->data);
  free(hash_table);
}




HashTable * hash_table_new()
{
  HashTable * ret = (HashTable *) malloc(sizeof(HashTable));
  assert(ret);

  ret->base.type = DICTIONARY_TYPE_HASH_TABLE;
  sem_init(&ret->base.mutex, 0, 1);
  ret->base.keys = (List *) linked_list_new();

  ret->base.dictionary_destroy = (void (*)(Dictionary *)) hash_table_destroy;
  ret->base.dictionary_destroy_and_free = (void (*)(Dictionary *)) hash_table_destroy_and_free;
  ret->base.dictionary_destroy_and_user_free = (void (*)(Dictionary *, void (*)(void *))) hash_table_destroy_and_user_free;
  ret->base.dictionary_destroy_and = (void (*)(Dictionary *, void (*)(Any))) hash_table_destroy_and;

  ret->base.dictionary_clear = (void (*)(Dictionary *)) hash_table_clear;
  ret->base.dictionary_clear_and_free = (void (*)(Dictionary *)) hash_table_clear_and_free;
  ret->base.dictionary_clear_and_user_free = (void (*)(Dictionary *, void (*)(void *))) hash_table_clear_and_user_free;
  ret->base.dictionary_clear_and = (void (*)(Dictionary *, void (*)(Any))) hash_table_clear_and;

  ret->base.dictionary_has = (bool (*)(Dictionary *, char *)) hash_table_has;
  ret->base.dictionary_get = (Any (*)(Dictionary *, char *)) hash_table_get;
  ret->base.dictionary_try_get = (bool (*)(Dictionary *, char *, Any *)) hash_table_try_get;

  ret->base.dictionary_put = (void (*)(Dictionary *, char * key, Any)) hash_table_put;
  ret->base.dictionary_try_put = (bool (*)(Dictionary *, char * key, Any)) hash_table_try_put;

  ret->base.dictionary_set = (void (*)(Dictionary *, char *, Any)) hash_table_set;
  ret->base.dictionary_set_and_free = (void (*)(Dictionary *, char *, Any)) hash_table_set_and_free;
  ret->base.dictionary_set_and_user_free = (void (*)(Dictionary *, char *, Any, void (*)(void *))) hash_table_set_and_user_free;
  ret->base.dictionary_set_and = (void (*)(Dictionary *, char *, Any, void (*)(Any))) hash_table_set_and;

  ret->base.dictionary_remove = (Any (*)(Dictionary *, char *)) hash_table_remove;

  ret->data = (struct HashTableNode **) calloc(sizeof(struct HashTableNode *), HASH_TABLE_TABLE_SIZE);
  assert(ret->data);

  return ret;
}


void hash_table_destroy(HashTable * hash_table)
{
  assert(hash_table);
  hash_table_destroy_imp(hash_table, NULL, false);
}

void hash_table_destroy_and_free(HashTable * hash_table)
{
  assert(hash_table);
  hash_table_destroy_imp(hash_table, free, true);

}
void hash_table_destroy_and_user_free(HashTable * hash_table, void (*callback)(void *))
{
  assert(hash_table);
  assert(callback);
  hash_table_destroy_imp(hash_table, callback, true);
}

void hash_table_destroy_and(HashTable * hash_table, void (*callback)(Any))
{
  assert(hash_table);
  assert(callback);
  hash_table_destroy_imp(hash_table, callback, false);
}


List * hash_table_get_keys(HashTable * hash_table)
{
  return dictionary_get_keys((Dictionary *) hash_table);
}


void hash_table_clear(HashTable * hash_table)
{
  assert(hash_table);
  hash_table_clear_imp(hash_table, NULL, false);
}

void hash_table_clear_and_free(HashTable * hash_table)
{
  assert(hash_table);
  hash_table_clear_imp(hash_table, (void *) free, true);
}

void hash_table_clear_and_user_free(HashTable * hash_table, void (*callback)(void *))
{
  assert(hash_table);
  assert(callback);

  hash_table_clear_imp(hash_table, (void *) callback, true);
}

void hash_table_clear_and(HashTable * hash_table, void (*callback)(Any))
{
  assert(hash_table);
  hash_table_clear_imp(hash_table, (void *) callback, false);
}


bool hash_table_has(HashTable * hash_table, char * key)
{
  assert(hash_table);

  bool ret;

  sem_wait(&hash_table->base.mutex);

  struct HashTableNode ** node = hash_table_node_get(hash_table, key);
  if (*node)
  {
    Any * value_ptr;
    ret = hash_table_node_find(*node, key, &value_ptr, NULL);
  }
  else
    ret = false;

  sem_post(&hash_table->base.mutex);

  return ret;
}

Any hash_table_get(HashTable * hash_table, char * key)
{
  assert(hash_table);

  Any * ret;
  bool find_ret;

  sem_wait(&hash_table->base.mutex);

  struct HashTableNode ** node = hash_table_node_get(hash_table, key);
  assert(*node);

  find_ret = hash_table_node_find(*node, key, &ret, NULL);
  assert(find_ret);

  sem_post(&hash_table->base.mutex);

  return *ret;
}

bool hash_table_try_get(HashTable * hash_table, char * key, Any * value)
{
  assert(hash_table);
  assert(value);

  bool ret;
  Any * temp_ptr;

  sem_wait(&hash_table->base.mutex);

  struct HashTableNode ** node = hash_table_node_get(hash_table, key);
  if (*node)
  {
    ret = hash_table_node_find(*node, key, &temp_ptr, NULL);
    if (ret)
      *value = *temp_ptr;
  }
  else
    ret = false;

  sem_post(&hash_table->base.mutex);

  return ret;
}

void hash_table_put(HashTable * hash_table, char * key, Any value)
{
  bool ret = hash_table_try_put(hash_table, key, value);
  assert(ret);
}

bool hash_table_try_put(HashTable * hash_table, char * key, Any value)
{
  assert(hash_table);

  sem_wait(&hash_table->base.mutex);

  struct HashTableNode ** node = hash_table_node_get(hash_table, key);
  if (*node)
  {
    struct HashTableNode * last = *node;
    if (strings_equals(last->key, key))
    {
      sem_post(&hash_table->base.mutex);
      return false;
    }

    while (last->next)
    {
      last = last->next;
      if (strings_equals(last->key, key))
      {
        sem_post(&hash_table->base.mutex);
        return false;
      }
    }

    last->next = hash_table_node_new(key, value);
  }
  else
  {
    *node = hash_table_node_new(key, value);
  }

  linked_list_add((LinkedList *) hash_table->base.keys, str_to_any(strings_clone(key)));

  sem_post(&hash_table->base.mutex);
  return true;
}


void hash_table_set(HashTable * hash_table, char * key, Any value)
{
  assert(hash_table);
  hash_table_set_imp(hash_table, key, value, NULL, false);
}


void hash_table_set_and_free(HashTable * hash_table, char * key, Any value)
{
  assert(hash_table);
  hash_table_set_imp(hash_table, key, value, (void *) free, true);
}

void hash_table_set_and_user_free(HashTable * hash_table, char * key, Any value, void (*callback)(void *))
{
  assert(hash_table);
  assert(callback);

  hash_table_set_imp(hash_table, key, value, (void *) callback, true);
}

void hash_table_set_and(HashTable * hash_table, char * key, Any value, void (*callback)(Any))
{
  assert(hash_table);
  assert(callback);

  hash_table_set_imp(hash_table, key, value, (void *) callback, false);
}

Any hash_table_remove(HashTable * hash_table, char * key)
{
  assert(hash_table);

  Any ret = ptr_to_any(NULL);

  sem_wait(&hash_table->base.mutex);

  struct HashTableNode ** node = hash_table_node_get(hash_table, key);
  if (*node)
  {
    hash_table_node_remove((LinkedList *) hash_table->base.keys, node, key, &ret);
  }

  sem_post(&hash_table->base.mutex);

  return ret;
}
