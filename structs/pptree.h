/**
 * @file pptree.h
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
 * A simple RBTree implementation based off of the paper
 * "Left-leaning Red-Black Trees" by Robert Sedgewick
 */

#ifndef PP_TREE_H
#define PP_TREE_H

/**
 * @struct ppTree
 * @typedef ppTree 
 * 
 * @brief Handle for tree instances.
 */
typedef struct ppTree ppTree;

/**
 * @fn ppTree* pp_tree_new()
 * @brief Generate a new tree.
 * @return a tree instance.
 */
ppTree* pp_tree_new();

/**
 * @fn void pp_tree_free(ppTree* tree)
 * @brief Free a tree instance.
 * @param tree a tree handle to free.
 */
void pp_tree_free(ppTree* tree);

/**
 * @fn void* pp_tree_search(ppTree* tree, char* key)
 * @brief Locate value given a key.
 * @param tree a tree handle.
 * @param key the string key to search for.
 * @return the value stored under that key, or NULL if key is not found.
 */
void* pp_tree_search(ppTree* tree, char* key);

/**
 * @fn void pp_tree_insert(ppTree* tree, char* key, void* value)
 * @brief Insert a reference into the tree.
 * @param tree a tree handle.
 * @param key the key used to retrieve the value later.
 * @param value a pointer to the object the key will reference.
 */
void pp_tree_insert(ppTree* tree, char* key, void* value);

/**
 * @fn void pp_tree_remove(ppTree* tree, char* key)
 * @brief Remove a reference from the tree.
 * @param tree a tree handle.
 * @param key the string key to search for and remove.
 */
void pp_tree_remove(ppTree* tree, char* key);

/**
 * @fn void pp_tree_clear(ppTree* tree)
 * @brief Remove all items in the tree.
 * @param tree a tree handle.
 */
void pp_tree_clear(ppTree* tree);

/**
 * @fn void pp_tree_traverse(ppTree* tree, void(*fn)(char*, void*, void*))
 * @brief Apply a function to every (key, value) tuple in the tree.
 * @param tree a tree handle.
 * @param fn A function that takes a key and reference.
 *        A third pointer is given for user-data.
 * @param data the user-data passed to the function.
 */
void pp_tree_traverse(ppTree* tree, void(*fn)(char*, void*, void*), void* data);

#endif /* PP_TREE_H */
