#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

#define MAX_CHAR_BUFFER 100

int main()
{
   int m, value;
   int reading = 1;
   char buffer[MAX_CHAR_BUFFER];
   p_tree tree;

   scanf("%d", &m);

   for(int i = 0; i < m; i ++)
   {
      // Reset the tree
      tree = create_tree();
      
      // Read and fill the tree
      reading = 1;
      while (reading)
      {
         scanf(" %s", buffer);

         // If it is a start of parenthesis then expand the tree because it will have more terms
         if (buffer[0] == '(')
            expand_tree(tree);
         // The buffer holds a number if the first char is a digit or if its longer than 2 chars
         else if ((buffer[0] >= '0' && buffer[0] <= '9') || buffer[1] != '\0')
         {
            value = atoi(buffer);
            add_ivalue(tree, value);
         }
         // If it is an operation add it as such
         else if (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')
            add_operator(tree, buffer[0]);
         // If it is an end of parenthesis, check if the tree is already completed. If yes, stop the while
         else if (buffer[0] == ')')
            reading = !is_filled(tree);
         // Else its a "variable"
         else
            add_cvalue(tree, buffer[0]);
      }

      simplify_tree(tree);

      print_tree(tree);
      printf(" \n");

      destroy_tree(tree);
   }

   return EXIT_SUCCESS;
}
