#ifndef HEAP_H
#define HEAP_H

#define CHAR_ID_SIZE 5

typedef struct Heap
{
   char **ids;                               // Array of ids(strings)
   int count;                                // Number of ids stored in the heap
   int size;                                 // Max size of the heap
   int (*cmp)(const char *, const char *);   // Custom compare function
} Heap;

typedef Heap * p_heap;

// Macros for navigating the heap
#define PARENT(i) ((i - 1)/2)
#define L_CHILD(i) (2 * i + 1)
#define R_CHILD(i) (2 * i + 2)

/**
 * Create a heap with a given size and that will use a given function as comparator
 */
p_heap create_heap(int size, int (*custom_cmp)(const char *, const char *));

/**
 * Get current number of elements in the heap
 */
int get_count(p_heap heap);

/**
 * Check the element at the top of the heap
 */
const char* peek(p_heap heap);

/**
 * Insert an element to the heap
 */
void push_heap(p_heap heap, const char *id);

/**
 * Remove the top element of the heap
 */
void pop_heap(p_heap heap, char *ret);

/**
 * Balance the heap from bottom to top
 */
void heapify_up(p_heap heap, int k);

/**
 * Balance the heap from top to bottom
 */
void heapify_down(p_heap heap, int k);

/**
 * Free the heap
 */
void free_heap(p_heap heap);

#endif
