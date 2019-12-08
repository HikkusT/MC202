#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

#define INF 9999999 // Infinity. Used as a big number.

p_node create_heap(int size)
{
   p_node node;

   node = malloc(sizeof(Node));
   if (node == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   // The heap starts with only one node which starts at 0 and has a length of it's total size
   node->address = 0;
   node->length = size;
   node->next = NULL;
   node->prev = NULL;

   return node;
}

p_node alloc_memory(p_node heap, int mem_len)
{
   p_node node = find_best_fit_node(heap, mem_len);   // Find which node will leave the minimum of free space

   // Allocate the memory at the beginning of the best node
   node->address += mem_len;
   node->length -= mem_len;

   // Update the heap so it continues a valid heap
   return format_heap(heap);
}

// Recursively finds which node is the best one to allocate the memory
p_node find_best_fit_node(p_node heap, int mem_len)
{
   // If the heap has less than 2 nodes, return itself
   if (heap->next == NULL || heap == NULL)
      return heap;
   
   // Get the best candidate of the following nodes
   p_node best_child_node = find_best_fit_node(heap->next, mem_len);

   // Calculate the remaining space for both the current node and the best candidate
   int minimum_space = calculate_remaining_length(best_child_node, mem_len);
   int curr_space    = calculate_remaining_length(heap, mem_len);

   // If the current node is better than the best candidate, return it. Else mantain the best candidate
   if (curr_space <= minimum_space)
      return heap;
   else
      return best_child_node;
}

int calculate_remaining_length(p_node node, int mem_len)
{
   // If it is a NULL node or the memory doesnt fit in the node, return a infinite weight.
   // Else calculate how much memory will remain in the node
   if (node == NULL || node->length - mem_len < 0)
      return INF;
   else
      return node->length - mem_len;
}

p_node realloc_memory(p_node heap, int mem_address, int mem_len, int new_mem_len)
{
   p_node target_node = NULL;
   p_node previous_node = NULL;
   int end_address = mem_address + mem_len - 1;
   int new_end_address = mem_address + new_mem_len - 1;

   // Find the node right after the place of the memory where we want to reallocate the memory
   for (target_node = heap; target_node != NULL && target_node->address < end_address; target_node = target_node->next)
      previous_node = target_node;

   if (new_mem_len < mem_len)
   {
      // If the length shrinks we can mantain the memory location.
      // Add a new node of free memory in the new free space: from where the new length ends til where it used to end
      p_node new_node = malloc(sizeof(Node));
      if (new_node == NULL)
      {
         printf("Not enough memory!\n");
         exit(1);
      }

      new_node->address = new_end_address + 1;
      new_node->length = mem_len - new_mem_len;
      new_node->next = target_node;
      new_node->prev = previous_node;

      if (previous_node == NULL)
         heap = new_node;
      else
         previous_node->next = new_node;

      if (target_node != NULL)
         target_node->prev = new_node;
   }
   else if (target_node != NULL && end_address == target_node->address - 1 && new_end_address <= target_node->address + target_node->length - 1)
   {
      // If the memory is getting larger but there is a chunck of free space right next to it and it fits the extra memory, expand it
      // Shrink the first node right next to the memory located by the extra memory
      int diff = new_mem_len - mem_len;
      target_node->address += diff;
      target_node->length  -= diff;
   }
   else
   {
      // Else deallocate it and allocate with the new length
      heap = dealloc_memory(heap, mem_address, mem_len);
      heap = alloc_memory(heap, new_mem_len);
   }

   // Only return a valid heap
   return format_heap(heap);   
}

// Deallocating the memory is the same as reallocating it to 0
p_node dealloc_memory(p_node heap, int mem_address, int mem_len)
{
   return realloc_memory(heap, mem_address, mem_len, 0);
}

// Make the list a valid list for the problem
p_node format_heap(p_node heap)
{
   heap = remove_empty_nodes(heap);             // Remove any node with length 0
   heap = group_adjacent_segments(heap);        // Group together nodes that overlap (Eg: 5-10 and 11-14 should be 5-14)

   return heap;
}

p_node remove_empty_nodes(p_node heap)
{
   // If the heap is empty, do nothing
   if (heap == NULL)
      return NULL;

   // Remove recursively "length 0" nodes
   heap->next = remove_empty_nodes(heap->next);

   // If the current node has length 0, remove itself before returning
   if (heap->length == 0)
      return remove_node(heap);
   else
      return heap;
}

p_node group_adjacent_segments(p_node heap)
{
   // If the heap has less than 2 elements, do nothing
   if (heap == NULL || heap->next == NULL)
      return heap;
   
   // Group together recursively
   heap->next = group_adjacent_segments(heap->next);

   // If the current node should be grouped, group it with the next node
   if (heap->address + heap->length >= heap->next->address)
   {
      heap->next->address = heap->address;
      heap->next->length += heap->length;
      return remove_node(heap);
   }
   else
      return heap;
}

p_node remove_node(p_node node)
{
   p_node next_node = node->next;

   if (next_node != NULL)
      next_node->prev = node->prev;
   free(node);

   return next_node;
}

void print_heap(p_node heap)
{
   printf("heap:\n");
   recursive_list_print(heap);
}

// Recursively print the list
void recursive_list_print(p_node node)
{
   if (node != NULL)
   {
      printf("%d %d\n", node->address, node->length);
      recursive_list_print(node->next);
   }
}

// Recursively free nodes
void free_heap(p_node heap)
{
   if (heap != NULL)
   {
      free_heap(heap->next);
      free(heap);
   }
}