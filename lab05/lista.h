#ifndef LISTA_H
#define LISTA_H

typedef struct Node
{
   int address;
   int length;
   struct Node *next;
   struct Node *prev;
} Node;

typedef Node * p_node;

/**
 * Initialize a heap with 'size' free memory
 */
p_node create_heap(int size);

/**
 * Allocates memory in the heap
 */
p_node alloc_memory(p_node heap, int mem_len);

/**
 * Returns the best node in the heap to allocate the memory
 */
p_node find_best_fit_node(p_node heap, int mem_len);

/**
 * Calculates how much memory will reamin in the segment if allocated in a given node
 */
int calculate_remaining_length(p_node node, int mem_len);

/**
 * Reallocates memory in the heap
 */
p_node realloc_memory(p_node heap, int mem_address, int mem_len, int new_mem_len);

/**
 * Deallocates memory in the heap
 */
p_node dealloc_memory(p_node heap, int mem_address, int mem_len);

/**
 * Updates the heap so it stays a valid heap
 */
p_node format_heap(p_node heap);

/**
 * Removes memory segments with length 0
 */
p_node remove_empty_nodes(p_node heap);

/**
 * Group nodes that can be grouped
 * Eg: Nodes 5-10 and 11-14 should be only one node 5-14
 */
p_node group_adjacent_segments(p_node heap);

/**
 * Removes the node of the heap
 */
p_node remove_node(p_node node);

/**
 * Prints the heap
 */
void print_heap(p_node heap);

/**
 * Prints the nodes
 */
void recursive_list_print(p_node node);

/**
 * Free the memory allocated
 */
void free_heap(p_node heap);

#endif
