#ifndef LISTA_H
#define LISTA_H

typedef struct Node
{
   int n;
   struct Node * next;
} Node;

typedef Node * p_node;

/**
 * Checks wether the list has the element n
 */
int has_element(p_node list, int n);

/**
 * Insert an element n at the start of the list and returns the new start of the list
 */
p_node insert_at_start(p_node list, int n);

/**
 * Destroy the list
 */
void destroy_list(p_node list);

#endif // LISTA_H
