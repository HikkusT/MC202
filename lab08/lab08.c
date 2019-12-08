#include <stdio.h>
#include <stdlib.h>

#include "abb.h"
#include "data.h"

int main()
{
   int index = -1;
   char buffer;
   char message[MESSAGE_LEN];
   p_tree root = NULL;

   while (index != 0)
   {
      scanf("%d", &index);

      if (index != 0)
      {
         scanf("%c", &buffer); // Clear space buffer
         scanf("%[^\n]", message);
         
         // If it hasnt been added to the tree, add it
         if (find(root, index) == NULL)
            root = insert(root, create_data(index, message));
      }
   }

   // Print every message in order till a index is not found(end of msg)
   for (int i = 1; find(root, i) != NULL; i ++)
      print_data(get_data(find(root, i)));
   printf("\n");

   // Free the allocated memory
   destroy_tree(root);
   
   return EXIT_SUCCESS;
}
