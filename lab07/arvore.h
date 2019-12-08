#ifndef ARVORE_H
#define ARVORE_H

#define INF -9999999     // Used as a empty i_value field

typedef struct Tree
{
   int  i_value;         // Hold a int value in case it is a number
   char c_value;         // Hold a char value in case it is a "variable" or an operator
   struct Tree *l_child;
   struct Tree *r_child;
} Tree;

typedef Tree * p_tree;

/**
 * Create a tree with NULL childs
 */
p_tree create_tree();

/**
 * Check if a node is a leaf (has no childs)
 */
int is_leaf(p_tree tree);

/**
 * Check if a node is empty(i.e. does not hold any data)
 */
int is_empty(p_tree tree);

/**
 * Check if a node holds a number(not a operation or a variable)
 */
int is_number(p_tree tree);

/**
 * Add nodes to the tree, shaping it
 */
int expand_tree(p_tree tree);

/**
 * Insert an int value in the tree
 */
int add_ivalue(p_tree tree, int value);

/**
 * Insert a char value in the tree
 */
int add_cvalue(p_tree tree, char value);

/**
 * Insert an operator in the thee
 */
int add_operator(p_tree tree, char operator);

/**
 * Check if the tree is completely filled
 */
int is_filled(p_tree tree);

/**
 * Calculates a expression given by a tree
 */
int calculate_expression(int lc, int rc, char operation);

/**
 * Simplify a tree
 */
void simplify_tree(p_tree tree);

/**
 * Print a leaf node
 */
void print_leaf(p_tree tree);

/**
 * Print a tree
 */
void print_tree(p_tree tree);

/**
 * Destroy a tree
 */
void destroy_tree(p_tree tree);

#endif
