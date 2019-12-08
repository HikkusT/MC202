#ifndef ABB_H
#define ABB_H

#include "data.h"

typedef struct Tree
{
   Data data;
   struct Tree *l_child;
   struct Tree *r_child;
} Tree;

typedef Tree * p_tree;

/**
 * Create a node with a given data
 */
p_tree create_node(Data data);

/**
 * Insert a node to the binary search tree
 */
p_tree insert(p_tree root, Data data);

/**
 * Find a node with a given index. If not found, NULL is returned
 */
p_tree find(p_tree root, int index);

/**
 * Returns the data of a given node
 */
Data get_data(p_tree node);

/**
 * Destroy the tree
 */
void destroy_tree(p_tree root);

#endif
