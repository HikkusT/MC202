#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heap.h"

// Aux function to swap two elements
void swap(char *a, char *b)
{
   char aux[CHAR_ID_SIZE];
   strcpy(aux, a);
   strcpy(a, b);
   strcpy(b, aux);
}

p_heap create_heap(int size, int (*custom_cmp)(const char *, const char *))
{
   p_heap heap = malloc(sizeof(Heap));
   if (heap == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   // Malloc each string
   heap->ids = malloc(size * sizeof(char *));
   if (heap->ids == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }
   for (int i = 0; i < size; i ++)
   {
      heap->ids[i] = malloc(CHAR_ID_SIZE * sizeof(char));
      if (heap->ids[i] == NULL)
      {
         printf("Not enough memory!\n");
         exit(1);
      }
   }
   heap->count = 0;
   heap->size = size;
   heap->cmp = custom_cmp;

   return heap;
}

int get_count(p_heap heap)
{
   return heap->count;
}

const char* peek(p_heap heap)
{
   return heap->ids[0];
}

// Insert the element at the last leaf and balance the heap
void push_heap(p_heap heap, const char *id)
{
   strcpy(heap->ids[heap->count], id);
   heap->count ++;
   heapify_up(heap, heap->count - 1);
}

// Return the element by assigning it to ret.
// Move last leaf to top and balance the heap
void pop_heap(p_heap heap, char *ret)
{
   strcpy(ret, peek(heap));

   swap(heap->ids[0], heap->ids[heap->count - 1]);
   heap->count --;
   heapify_down(heap, 0);
}

// While we can swap the element to the top, do it
void heapify_up(p_heap heap, int k)
{
   if (k > 0 && heap->cmp(heap->ids[k], heap->ids[PARENT(k)]))
   {
      swap(heap->ids[k], heap->ids[PARENT(k)]);
      heapify_up(heap, PARENT(k));
   }
}

// While we can swap the element to the botton, do it
void heapify_down(p_heap heap, int k)
{
   int child;
   if (L_CHILD(k) < heap->count)
   {
      child = L_CHILD(k);
      if (R_CHILD(k) < heap->count && heap->cmp(heap->ids[R_CHILD(k)], heap->ids[L_CHILD(k)]))
         child = R_CHILD(k);
      
      if (heap->cmp(heap->ids[child], heap->ids[k]))
      {
         swap(heap->ids[k], heap->ids[child]);
         heapify_down(heap, child);
      }
   }
}

// Free each string before freeing the array and itself
void free_heap(p_heap heap)
{
   for (int i = 0; i < heap->size; i ++)
      free(heap->ids[i]);
   free(heap->ids);
   free(heap);
}
