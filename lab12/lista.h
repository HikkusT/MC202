#ifndef LISTA_H
#define LISTA_H

typedef struct Node
{
   int v;
   int weight;
   struct Node * next;
} Node;

typedef Node * p_node;

/**
 * Checks wether the list has the element v
 */
int has_element(p_node list, int v);

/**
 * Gets the weight of an element v
 */
int get_element_weight(p_node list, int v);

/**
 * Insert an element n at the start of the list and returns the new start of the list
 */
p_node insert_at_start(p_node list, int v, int weight);

/**
 * Remove every element of the list bigger than the threshold
 */
p_node remove_bigger_elements(p_node list, int threshold);

/**
 * Destroy the list
 */
void destroy_list(p_node list);

#endif // LISTA_H
