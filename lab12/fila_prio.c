#include <stdlib.h>
#include <stdio.h>

#include "fila_prio.h"

// Macros for navigating the heap
#define PARENT(i) ((i - 1) / 2)
#define L_CHILD(i) (2 * i + 1)
#define R_CHILD(i) (2 * i + 2)

void swap_item(Item *a, Item *b)
{
   Item aux = *a;
   *a = *b;
   *b = aux;
}

void swap_int(int *a, int *b)
{
   int aux = *a;
   *a = *b;
   *b = aux;
}

void swap(p_priorityQueue pq, int posA, int posB)
{
   swap_item(&pq->v[posA], &pq->v[posB]);
   swap_int(&pq->indices[pq->v[posA].vertex], &pq->indices[pq->v[posB].vertex]);
}

p_priorityQueue initialize_priority_queue(int size)
{
   p_priorityQueue pq = malloc(sizeof(PriorityQueue));
   if (pq == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   pq->v = malloc(size * sizeof(Item));
   if (pq->v == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   pq->indices = malloc(size * sizeof(int));
   if (pq->indices == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   pq->count = 0;
   pq->arr_size = size;

   return pq;
}

int is_empty(p_priorityQueue pq)
{
   if (pq->count == 0)
      return 1;
   else
      return 0;
}

int peek_minimum(p_priorityQueue pq)
{
   return pq->v[0].vertex;
}

int get_priority(p_priorityQueue pq, int v)
{
   // Get the position
   int pos = pq->indices[v];

   return pq->v[pos].priority;
}

void push_element(p_priorityQueue pq, int v, int priority)
{
   // Create an item
   Item item;
   item.vertex = v;
   item.priority = priority;

   // Insert it at the end(as a leaf)
   pq->v[pq->count] = item;
   pq->indices[pq->count] = pq->count;
   pq->count++;

   // Float it to its correct position
   heapify_up(pq, pq->count - 1);
}

// Return the element by assigning it to ret.
// Move last leaf to top and balance the heap
int pop_minimum(p_priorityQueue pq)
{
   // Get the top element
   int ret = peek_minimum(pq);

   // Swap the top and the last leaf
   swap(pq, 0, pq->count - 1);
   pq->count--;

   // Sink it to its correct position
   heapify_down(pq, 0);

   return ret;
}

// As we are only lowering the priority, change it and float it to the top
void lower_priority(p_priorityQueue pq, int v, int new_priority)
{
   // Get the position of the element
   int pos = pq->indices[v];

   // Float it
   pq->v[pos].priority = new_priority;
   heapify_up(pq, pos);
}

// While we can swap the element to the top, do it
void heapify_up(p_priorityQueue pq, int k)
{
   if (k > 0 && pq->v[k].priority < pq->v[PARENT(k)].priority)
   {
      swap(pq, k, PARENT(k));
      heapify_up(pq, PARENT(k));
   }
}

// While we can swap the element to the botton, do it
void heapify_down(p_priorityQueue pq, int k)
{
   int child;
   if (L_CHILD(k) < pq->count)
   {
      child = L_CHILD(k);
      if (R_CHILD(k) < pq->count && pq->v[R_CHILD(k)].priority < pq->v[L_CHILD(k)].priority)
         child = R_CHILD(k);

      if (pq->v[child].priority < pq->v[k].priority)
      {
         swap(pq, k, child);
         heapify_down(pq, child);
      }
   }
}

void destroy_priority_queue(p_priorityQueue pq)
{
   free(pq->v);
   free(pq->indices);
   free(pq);
}