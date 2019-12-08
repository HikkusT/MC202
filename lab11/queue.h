#ifndef QUEUE_H
#define QUEUE_H

/**
 * Queue implemented as a circular array
 */
typedef struct Queue
{
   int start, end, arr_size, length;
   int *v;
} Queue;

typedef Queue * p_queue;

/**
 * Initialize the queue with a max size of size
 */
p_queue initialize_queue(int size);

/**
 * Checks wether the queue is empty
 */
int is_empty(p_queue queue);

/**
 * Add n to the end of the queue
 */
void enqueue(p_queue queue, int n);

/**
 * Remove and returns the first element of the queue
 */
int dequeue(p_queue queue);

/**
 * Destroy the queue
 */
void destroy_queue(p_queue queue);

#endif // QUEUE_H