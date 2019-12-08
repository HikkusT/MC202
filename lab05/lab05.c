#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main()
{
   int m, n;
   char operation;
   int mem_address, mem_len, new_mem_len;

   p_node heap;

   scanf("%d %d ", &m, &n);

   // Create heap of given size
   heap = create_heap(n);

   // Apply the input operations
   for (int i = 0; i < m; i ++)
   {
      scanf(" %c", &operation);

      switch (operation)
      {
      case 'A':
         scanf(" %d", &mem_len);
         heap = alloc_memory(heap, mem_len);
         break;

      case 'D':
         scanf(" %d %d", &mem_address, &mem_len);
         heap = dealloc_memory(heap, mem_address, mem_len);
         break;

      case 'R':
         scanf(" %d %d %d", &mem_address, &mem_len, &new_mem_len);
         heap = realloc_memory(heap, mem_address, mem_len, new_mem_len);
         break;

      case 'P':
         print_heap(heap);
         break;
      
      default:
         printf("Error, input operation not expected");
         exit(1);
         break;
      }
   }

   // Free the used memory
   free_heap(heap);

   return EXIT_SUCCESS;
}
