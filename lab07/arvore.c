#include <stdlib.h>
#include <stdio.h>

#include "arvore.h"

// Cretaes a node and set the data to a default and its children to NULL
p_tree create_tree()
{
   p_tree tree = malloc(sizeof(Tree));
   if (tree == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   tree->i_value = INF;          // Default int value
   tree->c_value = ' ';          // Default char value
   tree->l_child = NULL;
   tree->r_child = NULL;

   return tree;
}

// Check if both children are NULL
int is_leaf(p_tree tree)
{
   return tree->l_child == NULL && tree->r_child == NULL;
}

// Check if both data values are equals to the default
int is_empty(p_tree tree)
{
   return tree->i_value == INF && tree->c_value == ' ';
}

// Check if the int value is different than the default value
int is_number(p_tree tree)
{
   return !(tree->i_value == INF);
}

// Find the first empty leaf node(DFS) and add two children to it
int expand_tree(p_tree tree)
{
   // Check for leaf nodes
   if (is_leaf(tree))
   {
      // Only expand if it is empty
      if (is_empty(tree))
      {
         tree->l_child = create_tree();
         tree->r_child = create_tree();
         return 1;
      }
      else
         return 0;
   }

   // Pass the result of the children to the parent
   if (expand_tree(tree->l_child))
      return 1;
   else
      return expand_tree(tree->r_child);
}

// Find the first empty leaf node and insert a value to the int data
int add_ivalue(p_tree tree, int value)
{
   // Check for leaf nodes
   if (is_leaf(tree))
   {
      // Only insert if its empty
      if (is_empty(tree))
      {
         tree->i_value = value;
         return 1;
      }
      else
         return 0;
   }

   // Pass the result upwards
   if (add_ivalue(tree->l_child, value))
      return 1;
   else
      return add_ivalue(tree->r_child, value);
}

// Find the first empty leaf node and insert a value to the char data
int add_cvalue(p_tree tree, char value)
{
   // Check for leaf nodes
   if (is_leaf(tree))
   {
      // Only insert if its empty
      if (is_empty(tree))
      {
         tree->c_value = value;
         return 1;
      }
      else
         return 0;
   }

   // Pass the result upwards
   if (add_cvalue(tree->l_child, value))
      return 1;
   else
      return add_cvalue(tree->r_child, value);
}

// DFS in-order to insert an operator
int add_operator(p_tree tree, char operator)
{
   // Operators cant be a leaf
   if (is_leaf(tree))
      return 0;
   
   if (add_operator(tree->l_child, operator))
      return 1;
   else if (is_empty(tree))
   {
      // Insert if a not leaf node is empty
      tree->c_value = operator;
      return 1;
   }
   else
      return(add_operator(tree->r_child, operator));
}

// Recursively checks if a tree is fully filled (DFS in-order)
int is_filled(p_tree tree)
{
   if (is_leaf(tree))
      return !is_empty(tree);
   
   return is_filled(tree->l_child) && !is_empty(tree) && is_filled(tree->r_child);
}

// Use an operator and two ints to calculate the result of the expression
int calculate_expression(int lc, int rc, char operation)
{
   if (operation == '*')
      return lc * rc;
   else if (operation == '/')
      return lc / rc;
   else if (operation == '+')
      return lc + rc;
   else
      return lc - rc;
}

void simplify_tree(p_tree tree)
{
   // If its a leaf then we cant simplify
   if (is_leaf(tree))
      return;
   
   //Simplify both children
   simplify_tree(tree->l_child);
   simplify_tree(tree->r_child);

   // Only simply the current node if both children are number
   if (is_number(tree->l_child) && is_number(tree->r_child))
   {
      // Calculate
      int value = calculate_expression(tree->l_child->i_value, tree->r_child->i_value, tree->c_value);
      
      //Assign
      tree->i_value = value;

      // Remove utilized nodes
      destroy_tree(tree->l_child);
      destroy_tree(tree->r_child);
      tree->l_child = NULL;
      tree->r_child = NULL;
   }
}

// Print as int if it holds a int or print as a char otherwise
void print_leaf(p_tree tree)
{
   if (is_number(tree))
      printf("%d", tree->i_value);
   else
      printf("%c", tree->c_value);
}

// Recursively print the tree (DFS in-order)
void print_tree(p_tree tree)
{
   if (is_leaf(tree))
      print_leaf(tree);
   else
   {
      printf("( ");
      print_tree(tree->l_child);
      printf(" %c ", tree->c_value);
      print_tree(tree->r_child);
      printf(" )");
   }
}

// Recursively destroy the tree (DFS post-order)
void destroy_tree(p_tree tree)
{
   if (!is_leaf(tree))
   {
      destroy_tree(tree->l_child);
      destroy_tree(tree->r_child);
   }
   free(tree);
}