/**
 * @file pptree.c
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

#include <string.h>
#include <stdlib.h>

#include <jemalloc/jemalloc.h>

#include "pptree.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct ppTreeNode {

  char* key;
  void* value;
  struct ppTreeNode *left, *right;
  int isred; 

} ppTreeNode;

struct ppTree {

  struct ppTreeNode* root;
};

static ppTreeNode* pp_treenode_new(char* key, void* value) {

  ppTreeNode* node = malloc(sizeof(ppTreeNode));

  // Duplicate the string to store in the node
  node->key = malloc(strlen(key) + 1);
  strcpy(node->key, key);

  node->value = value;

  node->left = node->right = NULL;

  node->isred = TRUE;

  return node;
}

static void pp_treenode_free(ppTreeNode* node) {

  if (node != NULL) {
  
    if (node->left != NULL)
      pp_treenode_free(node->left);

    if (node->right != NULL)
      pp_treenode_free(node->right);

    free(node->key);
    free(node);
  }
}

static void pp_treenode_colorflip(ppTreeNode* node) {

  node->isred = !node->isred;

  if (node->left != NULL)
    node->left->isred = !node->left->isred;

  if (node->right != NULL)
    node->right->isred = !node->right->isred;
}

static int pp_treenode_isred(ppTreeNode* node) {

	return ((node != NULL) && node->isred);
}

static ppTreeNode* pp_treenode_rotleft(ppTreeNode* node) {

  ppTreeNode* x = node->right;
  node->right = x->left;
  x->left = node;
  x->isred = node->isred;
  node->isred = TRUE;
  return x;
}

static ppTreeNode* pp_treenode_rotright(ppTreeNode* node) {

  ppTreeNode* x = node->left;
  node->left = x->right;
  x->right = node;
  x->isred = node->isred;
  node->isred = TRUE;
  return x;
}

static ppTreeNode* pp_treenode_redleft(ppTreeNode* node) {

  pp_treenode_colorflip(node);

  if (node->right != NULL && pp_treenode_isred(node->right->left)) {

    node->right = pp_treenode_rotright(node->right);
    node = pp_treenode_rotleft(node);
    pp_treenode_colorflip(node);
  }

  return node;
}

static ppTreeNode* pp_treenode_redright(ppTreeNode* node) {

  pp_treenode_colorflip(node);

  if (node->left != NULL && pp_treenode_isred(node->left->left)) {

    node = pp_treenode_rotright(node);
    pp_treenode_colorflip(node);
  }

  return node;
}

static ppTreeNode*
pp_treenode_insert(ppTreeNode* node, char* key, void* value) {

  if (node == NULL)
    return pp_treenode_new(key, value);

  if (pp_treenode_isred(node->left) && pp_treenode_isred(node->right))
    pp_treenode_colorflip(node);

  int cmp = strcmp(key, node->key);
  if (cmp == 0)     node->value = value;
  else if (cmp < 0) node->left = pp_treenode_insert(node->left, key, value);
  else              node->right = pp_treenode_insert(node->right, key, value);

  if (pp_treenode_isred(node->right) && !pp_treenode_isred(node->left))
    node = pp_treenode_rotleft(node);

  if (pp_treenode_isred(node->left) && pp_treenode_isred(node->left->left))
    node = pp_treenode_rotright(node);

  return node;
}

static ppTreeNode* pp_treenode_fixup(ppTreeNode* node) {

  if (pp_treenode_isred(node->right))
    node = pp_treenode_rotleft(node);

  if (pp_treenode_isred(node->left) && pp_treenode_isred(node->left->left))
    node = pp_treenode_rotright(node);

  if (pp_treenode_isred(node->left) && pp_treenode_isred(node->left))
    pp_treenode_colorflip(node);
  
  return node;
}

static ppTreeNode* pp_treenode_removemin(ppTreeNode* node) {

  if (node->left == NULL) {

    pp_treenode_free(node);    
    return NULL;
  }
 
  if (!pp_treenode_isred(node->left) && !pp_treenode_isred(node->left->left))
    node = pp_treenode_redleft(node);

  node->left = pp_treenode_removemin(node->left);

  return pp_treenode_fixup(node);
}

static ppTreeNode* pp_treenode_findmin(ppTreeNode* node) {

  while (node->left != NULL)
    node = node->left;

  return node;
}

static ppTreeNode* pp_treenode_remove(ppTreeNode* node, char* key) {

  if (strcmp(key, node->key) < 0) {

    if (node->left != NULL) {

      if (!pp_treenode_isred(node->left) && pp_treenode_isred(node->left->left))
        node = pp_treenode_redleft(node);

      node->left = pp_treenode_remove(node->left, key);
    }
  
  } else {

    if (pp_treenode_isred(node->left))
      node = pp_treenode_rotright(node);

    if (strcmp(key, node->key) == 0 && (node->right == NULL)) {

      pp_treenode_free(node);
      return NULL;
    }

    if (node->right != NULL) {

      if (!pp_treenode_isred(node->right) && !pp_treenode_isred(node->right->left))
        node = pp_treenode_redright(node);

      if (strcmp(key, node->key) == 0) {

        node->value = pp_treenode_findmin(node->right)->value;
        node->right = pp_treenode_removemin(node->right);
      
      } else {

        node->right = pp_treenode_remove(node->right, key);
      }
    }
  }

  return pp_treenode_fixup(node);
}

ppTree* pp_tree_new() {

  ppTree* tree = malloc(sizeof(ppTree));

  tree->root = NULL;

  return tree;
}

void pp_tree_free(ppTree* tree) {

  pp_tree_clear(tree);
  free(tree);
}

void* pp_tree_search(ppTree* tree, char* key) {

  ppTreeNode* x = tree->root;

  while (x != NULL) {

    // Compare the two strings
    int cmp = strcmp(key, x->key);

    if (cmp == 0)     return x->value; // Strings match
    else if (cmp < 0) x = x->left;
    else              x = x->right;
  }

  return NULL;
}

void pp_tree_insert(ppTree* tree, char* key, void* value) {

  tree->root = pp_treenode_insert(tree->root, key, value);
  tree->root->isred = FALSE;
}

void pp_tree_remove(ppTree* tree, char* key) {

  if (tree->root != NULL) {
    tree->root = pp_treenode_remove(tree->root, key);

    if (tree->root != NULL)
      tree->root->isred = FALSE;
  }
}

void pp_tree_clear(ppTree* tree) {

  pp_treenode_free(tree->root);
  tree->root = NULL;
}

static void pp_treenode_traverse(ppTreeNode* node,
  void(*fn)(char*, void*, void*), void* data) {

  if (node->left != NULL)
    pp_treenode_traverse(node->left, fn, data);

  fn(node->key, node->value, data);

  if (node->right != NULL)
    pp_treenode_traverse(node->right, fn, data);
}

void pp_tree_traverse(ppTree* tree,
  void(*fn)(char*, void*, void*), void* data) {

  if (tree->root != NULL)
    pp_treenode_traverse(tree->root, fn, data);
}
