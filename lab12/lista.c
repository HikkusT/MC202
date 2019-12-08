#include <stdlib.h>
#include <stdio.h>

#include "lista.h"


// Check if get_element_weight cant find the element
int has_element(p_node list, int v)
{
   return get_element_weight(list, v) != -1;
}

// Recursively goes through the list looking for v
// Returns -1 if no element v is found
int get_element_weight(p_node list, int v)
{
   if (list != NULL)
   {
      if (list->v == v)
         return list->weight;
      else
         return get_element_weight(list->next, v);
   }

   return -1;
}

p_node insert_at_start(p_node list, int v, int weight)
{
   p_node node = malloc(sizeof(Node));
   if (node == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   node->v = v;
   node->weight = weight;
   node->next = list;

   return node;
}

// Recursively remove the elements
p_node remove_bigger_elements(p_node list, int threshold)
{
   if (list == NULL)
      return NULL;
   
   // Remove further elements that violates the threshold
   list->next = remove_bigger_elements(list->next, threshold);

   // If the current node goes over the threshold, remove it
   p_node ret = list;
   if (list->weight > threshold)
   {
      ret = list->next;
      free(list);
   }

   return ret;
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