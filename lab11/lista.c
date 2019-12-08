#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

// Recursively goes through the list looking for n
int has_element(p_node list, int n)
{
   if (list != NULL)
   {
      if (list->n == n)
         return 1;
      else
         return has_element(list->next, n);
   }

   return 0;
}

p_node insert_at_start(p_node list, int n)
{
   p_node node = malloc(sizeof(Node));
   if (node == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   node->n = n;
   node->next = list;

   return node;
}

// Recursively destroy the list
void destroy_list(p_node list)
{
   if (list != NULL)
   {
      destroy_list(list->next);
      free(list);
   }
}