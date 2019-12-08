#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

p_stack create_stack()
{
   p_stack stack;

   stack = malloc(sizeof(Stack));
   if (stack == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   // Initialize to NULL and 0
   stack->top = NULL;
   stack->size = 0;

   return stack;
}

void populate_stack(p_stack stack, char number[])
{
   Data data;

   for (int i = 0; number[i] != '\0'; i ++)
   {
      // Store the digit and its position 
      data.digit = number[i];
      data.pos = i;
      push(stack, data);
   }
}

void invert_stack(p_stack stack)
{
   p_stack aux_stack = create_stack();

   // Dump everything in an auxiliar stack
   while (!is_empty(stack))
      pop_and_push(stack, aux_stack);
   
   // Make it the new stack, as it inverts when we pop all elements
   stack->top = aux_stack->top;
   stack->size = aux_stack->size;
   free(aux_stack);
}

int is_empty(p_stack stack)
{
   // Check if its null
   return (stack->top == NULL) ? 1 : 0;
}

int get_size(p_stack stack)
{
   return stack->size;
}

Data peek(p_stack stack)
{
   return stack->top->data;
}

void push(p_stack stack, Data data)
{
   p_node node;

   // Allocate a node with the data
   node = malloc(sizeof(Node));
   if (node == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }
   node->data = data;
   node->next = stack->top;

   // Push to the stack
   stack->top = node;
   stack->size ++;
}

Data pop(p_stack stack)
{
   // Keep reference to free it later
   p_node top = stack->top;

   // Remove the element
   Data data = top->data;
   stack->top = stack->top->next;
   stack->size --;

   // Free the memory
   free(top);
   return data;
}

void pop_and_push(p_stack src, p_stack dest)
{
   // Push do dest what whas popped from src
   push(dest, pop(src));
}

void pop_and_print(p_stack stack)
{
   Data data = pop(stack);
   printf("%c", data.digit);
}

void delete_digits(p_stack stack, int n)
{
   // If we want to delete n digits from a n digit number then there is nothing more to print
   if (stack->size <= n)
      return;
   
   // Keep track of the biggest digit from the n + 1 first digits
   char biggest_digit = 0;
   int target_pos;
   p_stack aux_stack = create_stack();

   // Iterate through the n + 1 first digits to find the biggest digit
   for (int i = 0; i < n + 1; i ++)
   {
      pop_and_push(stack, aux_stack);

      if (peek(aux_stack).digit > biggest_digit)
      {
         biggest_digit = peek(aux_stack).digit;
         target_pos = peek(aux_stack).pos;
      }
   }

   // Put back to the remaining digits everything that goes after the biggest one
   while (peek(aux_stack).pos != target_pos)
      pop_and_push(aux_stack, stack);

   // Print the biggest one
   pop_and_print(aux_stack);

   // Delete the ones that are before the biggest one and store how many were deleted
   int deleted_digits = get_size(aux_stack);
   destroy_stack(aux_stack);
   
   // Repeat the process to the remaining digits and update the number of digits to delete
   delete_digits(stack, n - deleted_digits);
}

void destroy_stack(p_stack stack)
{
   destroy_list(stack->top);
   free(stack);
}

void destroy_list(p_node list)
{
   // Recursivelly destroy the list
   if (list != NULL)
   {
      destroy_list(list->next);
      free(list);
   }
}