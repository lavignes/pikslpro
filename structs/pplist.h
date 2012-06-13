/**
 * @file pplist.h
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

#ifndef PP_LIST_H
#define PP_LIST_H

/**
 * @struct ppList
 * @typedef ppList 
 * 
 * @brief Handle for list instances.
 */
typedef struct ppList ppList;

/**
 * @fn ppList* pp_list_new()
 * @brief Generate a new list.
 * @return a list instance.
 */
ppList* pp_list_new();

/**
 * @fn void pp_list_free(ppList* list)
 * @brief Free a list instance.
 * @param list a list to be freed.
 */
void pp_list_free(ppList* list);

/**
 * @fn void pp_list_pushfront(ppList* list, void* value)
 * @brief Add an item to the front of a list.
 * @param list a list handle.
 * @param value the item to add to the list.
 */
void pp_list_pushfront(ppList* list, void* value);

/**
 * @fn void pp_list_pushback(ppList* list, void* value)
 * @brief Add an item to the back of a list.
 * @param list a list handle.
 * @param value a pointer to an object.
 */
void pp_list_pushback(ppList* list, void* value);

/**
 * @fn void* pp_list_popfront(ppList* list)
 * @brief Remove an item from the front of a list.
 * @param list a list handle.
 * @return the data object or NULL if the list was empty.
 */
void* pp_list_popfront(ppList* list);

/**
 * @fn void* pp_list_popback(ppList* list)
 * @brief Remove an item from the back of a list.
 * @param list a list handle.
 * @return the data object or NULL if the list was empty.
 */
void* pp_list_popback(ppList* list);

/**
 * @fn void* pp_list_peekfront(ppList* list)
 * @brief Get the object at the front of a list.
 * @param list a list handle.
 * @return the data object or NULL if the list was empty.
 */
void* pp_list_peekfront(ppList* list);

/**
 * @fn void* pp_list_peekback(ppList* list)
 * @brief Get the object at the back of a list.
 * @param list a list handle.
 * @return the data object or NULL if the list was empty.
 */
void* pp_list_peekback(ppList* list);

/**
 * @fn void pp_list_insertbefore(ppList* list, void* pos, void* value)
 * @brief Insert an object before another. If the latter cannot be found
 *        the state of the list does not change.
 * @param list a list handle.
 * @param pos the object to insert before.
 * @param value a pointer to an object to insert.
 */
void pp_list_insertbefore(ppList* list, void* pos, void* value);

/**
 * @fn void pp_list_insertafter(ppList* list, void* pos, void* value)
 * @brief Insert an object after another. If the latter cannot be found
 *        the state of the list does not change.
 * @param list a list handle.
 * @param pos the object to insert after.
 * @param value a pointer to an object to insert.
 */
void pp_list_insertafter(ppList* list, void* pos, void* value);

/**
 * @fn void pp_list_remove(ppList* list, void* value)
 * @brief Remove an item from a list.
 * @param list a list handle.
 * @param value the item to remove from the list.
 */
void pp_list_remove(ppList* list, void* value);

/**
 * @fn void pp_list_empty(ppList* list)
 * @brief Remove all items from a list.
 * @param list a list handle.
 */
void pp_list_empty(ppList* list);

/**
 * @fn size_t pp_list_size(ppList* list)
 * @brief Count the number of items in a list
 * @param list a list handle.
 * @return the number of items in the list.
 */
size_t pp_list_size(ppList* list);

#endif /* PP_LIST_H */
