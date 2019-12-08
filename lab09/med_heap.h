#ifndef MEDHEAP_H
#define MEDHEAP_H

#include "heap.h"

typedef struct MedHeap
{
   p_heap maxheap;   // A maxheap that stores every element smaller than the median
   p_heap minheap;   // A minheap that stores every element bigger than the median
} MedHeap;

typedef MedHeap * p_medheap;

/**
 * Create a median heap, which initializes a maxheap and a minheap to keep track of the median
 */
p_medheap create_medheap(int size);

/**
 * Get number of elements current stored
 */
int get_num_elements(p_medheap medheap);

/**
 * Insert an element in the median heap
 */
void insert(p_medheap medheap, const char *id);

/**
 * Balance the maxheap and the minheap so the median property is still valid
 */
void balance_heaps(p_medheap medheap);

/**
 * Get the median for comparative uses
 * (note: if its even it will NOT return the two middle elements, but the bigger one of those two)
 */
const char* get_median(p_medheap medheap);

/**
 * Print the median or medians, in case it has a even number of elements
 */
void print_median(p_medheap medheap);

/**
 * Free the median heap
 */
void free_medheap(p_medheap medheap);


#endif