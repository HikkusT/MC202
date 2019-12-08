#include <stdlib.h>
#include <stdio.h>
#include "abb.h"

p_tree create_node(Data data)
{
   p_tree node = malloc(sizeof(Tree));
   if (node == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   node->data = data;
   node->l_child = NULL;
   node->r_child = NULL;

   return node;
}

// Binary search tree insert
p_tree insert(p_tree root, Data data)
{
   if (root == NULL)
      return create_node(data);
   
   if (data.index < root->data.index)
      root->l_child = insert(root->l_child, data);
   else
      root->r_child = insert(root->r_child, data);
   
   return root;
}

// Binary search tree find
p_tree find(p_tree root, int index)
{
   if (root == NULL || root->data.index == index)
      return root;
   
   if (index < root->data.index)
      return find(root->l_child, index);
   else
      return find(root->r_child, index);
}

Data get_data(p_tree node)
{
   return node->data;
}

// Recursively destroy
void destroy_tree(p_tree root)
{
   if (root != NULL)
   {
      destroy_tree(root->l_child);
      destroy_tree(root->r_child);
      free(root);
   }
}