#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

// Check if the element at index n of an array hasnt appeared before
int is_first_occurrence(int *arr, int n)
{
   int element = arr[n];

   for (int i = 0; i < n; i ++)
      if (arr[i] == element)
         return 0;

   return 1;
}

int main()
{
   p_hashTable hashTable;
   int *lengths;

   int n;
   char pattern[MAX_STR_LEN];
   char text[MAX_STR_LEN];

   // Read number of patterns and initialize arrays
   scanf("%d", &n);
   lengths = malloc(n * sizeof(int));
   hashTable = create_hash_table(151);

   // Read each pattern, save its length and insert it in the hashtable
   for (int i = 0; i < n; i ++)
   {
      scanf(" %s", pattern);
      lengths[i] = strlen(pattern);
      insert(hashTable, pattern, i);
   }

   // Read the text
   scanf(" %s", text);

   // Iterate through array of lenghts without going through repetitive lenghts
   for (int i = 0; i < n; i ++)
   {
      if (is_first_occurrence(lengths, i))
      {
         for (int start = 0; start < (strlen(text) - lengths[i] + 1); start ++)
         {
            strncpy(pattern, text + start, lengths[i]);
            pattern[lengths[i]] = '\0';
            search_by_key(hashTable, pattern);
         }
      }
   }

   for (int i = 0; i < n; i ++)
   {
      printf("%d\n", get_count_by_index(hashTable, i));
   }

   return EXIT_SUCCESS;

}
