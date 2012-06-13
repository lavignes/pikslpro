/**
 * @file pplist.c
 * @author  Scott LaVigne <scott.lavigne@linux.com>
 * @version 0.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * A quick-and-dirty list manager.
 *
 */

#include <stdlib.h>

#include <jemalloc/jemalloc.h>

#include "pplist.h"

typedef struct ppListNode {

  struct ppListNode *next, *prev;
  void* value;

} ppListNode;

struct ppList {

  ppListNode *head, *tail;
};

ppListNode* pp_listnode_new(void* value) {

  ppListNode* node = malloc(sizeof(ppList));
  
  node->next = NULL;
  node->prev = NULL;
  node->value = value;

  return node;
}

void pp_listnode_free(ppListNode* node) {

  if (node != NULL)
    free(node);
}

ppList* pp_list_new() {

  ppList* list = malloc(sizeof(ppList));
  
  list->head = NULL;
  list->tail = NULL;
  
  return list;
}

void pp_list_free(ppList* list) {

  if (list != NULL) {
  
    pp_list_empty(list);
    free(list);
  }
}

void pp_list_pushfront(ppList* list, void* value) {

  ppListNode* node = pp_listnode_new(value);

  // First check for empty list
  if (list->head == NULL) {
  
    list->head = node;
    list->tail = node;
  
  } else {
  
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
  } 
}

void pp_list_pushback(ppList* list, void* value) {

  ppListNode* node = pp_listnode_new(value);

  // First check for empty list
  if (list->head == NULL) {
  
    list->head = node;
    list->tail = node;
  
  } else {
  
    // If the list only has 1 node
    if (list->head->next == NULL) {
    
      list->head->next = node;
      list->tail = node;
      node->prev = list->head;
      
    } else {
    
      list->tail->next = node;
      node->prev = list->tail;
    }
  }
}

void* pp_list_popfront(ppList* list) {

  if (list->head == NULL)
    return NULL;
    
  void* value = list->head->value;
    
  // 1 item lists
  if (list->head->next == NULL) {
    
    pp_listnode_free(list->head);
    
    list->head = NULL;
    list->tail = NULL;
  
  } else {
  
    list->head = list->head->next;
    pp_listnode_free(list->head->prev);
    
    list->head->prev = NULL;
  }
  
  return value;
}

void* pp_list_popback(ppList* list) {
  
  // If we have an empty list
  if (list->head == NULL)
    return NULL;
    
  void* value = list->tail->value;
  
  // 1 item lists
  if (list->head->next == NULL) {
  
    pp_listnode_free(list->tail);
    
    list->head = NULL;
    list->tail = NULL;
  
  } else {
  
    list->tail = list->tail->prev;
    pp_listnode_free(list->tail->next);
    
    list->tail->next = NULL;
  }
  
  return value;
}

void* pp_list_peekfront(ppList* list) {

  if (list->head != NULL)
    return list->head->value;
    
  else return NULL;
}

void* pp_list_peekback(ppList* list) {

  if (list->tail != NULL)
    return list->tail->value;
    
  else return NULL;
}

static ppListNode* pp_list_locate(ppList* list, void* pos) {

  ppListNode* node = list->head;
  
  while (node != NULL) {
  
    if (node->value == pos) break;
    
    node = node->next;
  }
  
  return node;
}

void pp_list_insertbefore(ppList* list, void* pos, void* value) {

  ppListNode* x = pp_list_locate(list, pos);

  // If the item couldnt be found
  // of if we are inserting before the head
  if (x == NULL || x == list->head)
    pp_list_pushfront(list, value);
  
  else {
 
    ppListNode* node = pp_listnode_new(value);
    
    node->next = x;
    node->prev = x->prev;
    x->prev = node;
  }
}

void pp_list_insertafter(ppList* list, void* pos, void* value) {

  ppListNode* x = pp_list_locate(list, pos);
  
  // If the item couldnt be found
  // of if we are inserting after the tail
  if (x == NULL || x == list->tail)
    pp_list_pushback(list, value);
    
  else {
  
    ppListNode* node = pp_listnode_new(value);
    
    node->prev = x;
    node->next = x->next;
    x->next = node;
  }
}

void pp_list_remove(ppList* list, void* value) {

  ppListNode* x = pp_list_locate(list, value);
  
  if (x != NULL) {
  
    if (x == list->head)
      pp_listnode_free(pp_list_popfront(list));
      
    else if (x == list->tail)
      pp_listnode_free(pp_list_popback(list));
      
    else {
    
      // Unlink the node
      // prev <===> next
      //    ^       ^
      //     \     /
      //      \   /
      //      node
      x->prev->next = x->next;
      x->next->prev = x->prev;
      
      pp_listnode_free(x);
    }
  }
}

void pp_list_empty(ppList* list) {
  
  ppListNode* x = list->head;
  
  while (x != NULL) {
  
    list->head = x->next;
    pp_listnode_free(x);
    x = list->head;
  }
  
  list->head = NULL;
  list->tail = NULL;
}

size_t pp_list_size(ppList* list) {

  ppListNode* x = list->head;
  size_t size = 0;
  
  while (x != NULL) {
  
    ++size;
    x = x->next;
  }
  
  return size;
}

void pp_list_traverse(ppList* list, void(*fn)(void*, void*), void* data) {

  ppListNode* x = list->head;
  
  while (x != NULL) {
  
    fn(x->value, data);
    x = x->next;
  }
}
