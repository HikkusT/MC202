#ifndef PILHA_H
#define PILHA_H

typedef struct
{
   char digit;
   int pos;
} Data;

typedef struct Node
{
   Data data;
   struct Node *next;
} Node;

typedef Node * p_node;

typedef struct
{
   p_node top;
   int size;
} Stack;

typedef Stack * p_stack;


/**
 * Create an empty stack
 */
p_stack create_stack();

/**
 * Populates a stack with the digits(char) of a number string
 */
void populate_stack(p_stack stack, char number[]);

/**
 * Invert the order of elements of a stack
 */
void invert_stack(p_stack stack);

/**
 * Checks if a stack is empty
 */
int is_empty(p_stack stack);

/**
 * Returns the size of the stack
 */
int get_size(p_stack stack);

/**
 * Peeks at the top of the stack(see the element but does not pop it)
 */
Data peek(p_stack stack);

/**
 * Add an element data to the stack
 */
void push(p_stack stack, Data data);

/**
 * Removes the element at the top of the stack and returns it
 */
Data pop(p_stack stack);

/**
 * Removes the element at the top of the stack src and pushes it to the stack dest
 */
void pop_and_push(p_stack src, p_stack dest);

/**
 * Removes the element at the top of the stack and prints it
 */
void pop_and_print(p_stack stack);

/**
 * Removes n digits of the stack to make the biggest number possible
 */
void delete_digits(p_stack stack, int n);

/**
 * Destroy a stack
 */
void destroy_stack(p_stack stack);

/**
 * Destroy a list
 */
void destroy_list(p_node list);

#endif
