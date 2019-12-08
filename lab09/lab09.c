#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "med_heap.h"

int main()
{
   int n, m;
   char id[CHAR_ID_SIZE];

   scanf("%d", &n);

   for (int i = 1; i <= n; ++i) {

      scanf("%d", &m);
      p_medheap medheap = create_medheap(m);

      for (int j = 0; j < m; j ++)
      {
         scanf(" %s", id);
         insert(medheap, id);

         // Print median for every 5 ids
         if (get_num_elements(medheap) % 5 == 0)
         {
            printf("%d ", i);
            print_median(medheap);
         }
      }

      // If it ended on a not multiple of 5, print the median too
      if (get_num_elements(medheap) % 5 != 0)
      {
         printf("%d ", i);
         print_median(medheap);
      }

      free_medheap(medheap);
   }

   return EXIT_SUCCESS;

}
