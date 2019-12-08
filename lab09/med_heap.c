#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "med_heap.h"

// Compare function for the maxheap
int cmp_maxheap(const char *a, const char *b)
{
   return strcmp(a, b) > 0;
}

// Compare function for the minheap
int cmp_minheap(const char *a, const char *b)
{
   return strcmp(a, b) < 0;
}

p_medheap create_medheap(int size)
{
   p_medheap medheap = malloc(sizeof(MedHeap));
   if (medheap == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }
   medheap->maxheap = create_heap(size, &cmp_maxheap);
   medheap->minheap = create_heap(size, &cmp_minheap);

   return medheap;
}

// Total number of elements = elements in maxheap + elements in minheap
int get_num_elements(p_medheap medheap)
{
   return get_count(medheap->maxheap) + get_count(medheap->minheap);
}

void insert(p_medheap medheap, const char *id)
{
   // If its empty, add it to the maxheap
   if (get_num_elements(medheap) == 0)
      push_heap(medheap->maxheap, id);
   else
   {
      // If the element is bigger than the median, insert it to the minheap. Else insert it in the maxheap
      if (strcmp(id, get_median(medheap)) > 0)
         push_heap(medheap->minheap, id);
      else
         push_heap(medheap->maxheap, id);
   }

   // Fix the heap if the insertion broke it somehow
   balance_heaps(medheap);
}

// By its definition, the two heaps cant have a count difference of more than 2. If it got past it
// Then we should send one element of the more populous heap to the other
void balance_heaps(p_medheap medheap)
{
   char extra_elem[CHAR_ID_SIZE];
   if (get_count(medheap->maxheap) - get_count(medheap->minheap) > 1)
   {
      pop_heap(medheap->maxheap, extra_elem);
      push_heap(medheap->minheap, extra_elem);
   }
   else if (get_count(medheap->minheap) - get_count(medheap->maxheap) > 1)
   {
      pop_heap(medheap->minheap, extra_elem);
      push_heap(medheap->maxheap, extra_elem);
   }
}

// If one heap has more elements than the other, we have a odd number, so the median is just the top of the more populous heap
// In the case the number of elements is even, return the bigger of the two medians
const char* get_median(p_medheap medheap)
{
   if (get_count(medheap->maxheap) > get_count(medheap->minheap))
      return peek(medheap->maxheap);
   else
      return peek(medheap->minheap);
}

// Print the two medians in the case the number of elements is even
void print_median(p_medheap medheap)
{
   if (get_count(medheap->maxheap) > get_count(medheap->minheap))
      printf("%s\n", peek(medheap->maxheap));
   else if (get_count(medheap->minheap) > get_count(medheap->maxheap))
      printf("%s\n", peek(medheap->minheap));
   else
      printf("%s %s\n", peek(medheap->maxheap), peek(medheap->minheap));
}

// Free each heap before freeing itself
void free_medheap(p_medheap medheap)
{
   free_heap(medheap->maxheap);
   free_heap(medheap->minheap);
   free(medheap);
}