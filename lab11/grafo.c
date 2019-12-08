#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"
#include "lista.h"
#include "queue.h"

p_graph initialize_graph(int num_vert)
{
   p_graph graph = malloc(sizeof(Graph));
   if (graph == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   graph->n = num_vert;
   graph->adjacency = malloc(num_vert * sizeof(p_node));
   if (graph->adjacency == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }
   
   // Initialize to null
   for (int i = 0; i < num_vert; i ++)
      graph->adjacency[i] = NULL;
   
   return graph;
}

void insert_edge(p_graph graph, int vertA, int vertB)
{
   if (!has_element(graph->adjacency[vertA], vertB))
      graph->adjacency[vertA] = insert_at_start(graph->adjacency[vertA], vertB);
}

void insert_bidirect_edge(p_graph graph, int vertA, int vertB)
{
   insert_edge(graph, vertA, vertB);
   insert_edge(graph, vertB, vertA);
}

// BFS implemented using a queue
int * BFS(p_graph graph, int start)
{
   // Holds the parent of each vertex that makes the shortest path
   int *parent = malloc(graph->n * sizeof(int));
   if (parent == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   // Holds which vertices have been added to the queue
   int *discovered = malloc(graph->n * sizeof(int));
   if (discovered == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   // Initialize the arrays
   for (int i = 0; i < graph->n; i ++)
   {
      parent[i] = -1;
      discovered[i] = 0;
   }

   // Initialize the queue
   p_queue queue = initialize_queue(graph->n);
   enqueue(queue, start);
   discovered[start] = 1;

   // Go though the queue adding each neighboor to the queue
   while (!is_empty(queue))
   {
      int vertex = dequeue(queue);

      for (p_node node = graph->adjacency[vertex]; node != NULL; node = node->next)
         if (!discovered[node->n])
         {
            discovered[node->n] = 1;
            parent[node->n] = vertex;
            enqueue(queue, node->n);
         }
   }

   destroy_queue(queue);
   free(discovered);
   return parent;
}

void destroy_graph(p_graph graph)
{
   for (int i = 0; i < graph->n; i ++)
      destroy_list(graph->adjacency[i]);
   
   free(graph->adjacency);
   free(graph);
}