#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

p_queue initialize_queue(int size)
{
   p_queue queue = malloc(sizeof(Queue));
   if (queue == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   queue->v = malloc(size * sizeof(int));
   if (queue->v == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   queue->start = 0;
   queue->end = 0;
   queue->length = 0;
   queue->arr_size = size;

   return queue;
}

int is_empty(p_queue queue)
{
   if (queue->length == 0)
      return 1;
   else
      return 0;
}

void enqueue(p_queue queue, int n)
{
   queue->v[queue->end] = n;
   queue->end = (queue->end + 1) % queue->arr_size;
   queue->length ++;
}

int dequeue(p_queue queue)
{
   int ret = 0;

   if (!is_empty(queue))
   {
      ret = queue->v[queue->start];
      queue->start = (queue->start + 1) % queue->arr_size;
      queue->length --;
   }

   return ret;
}

void destroy_queue(p_queue queue)
{
   free(queue->v);
   free(queue);
}