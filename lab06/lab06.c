#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"

#define MAXCHAR_NUMBER 500

int main()
{
   int m, n;
   char number[MAXCHAR_NUMBER];

   scanf("%d", &m);

   for (int i = 0; i < m; i ++)
   {
      p_stack stack = create_stack();

      scanf(" %s %d", number, &n);
      populate_stack(stack, number);
      invert_stack(stack);
      delete_digits(stack, n);

      destroy_stack(stack);
      printf("\n");
   }

   return EXIT_SUCCESS;
}

