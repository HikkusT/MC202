#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "grafo.h"
#include "lista.h"
#include "fila_prio.h"

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

void insert_edge(p_graph graph, int vertA, int vertB, int weight)
{
   if (!has_element(graph->adjacency[vertA], vertB))
      graph->adjacency[vertA] = insert_at_start(graph->adjacency[vertA], vertB, weight);
}

void insert_bidirect_edge(p_graph graph, int vertA, int vertB, int weight)
{
   insert_edge(graph, vertA, vertB, weight);
   insert_edge(graph, vertB, vertA, weight);
}

int get_edge_weight(p_graph graph, int vertA, int vertB)
{
   return get_element_weight(graph->adjacency[vertA], vertB);
}

int * dijkstra(p_graph graph, int start)
{
   // Holds the parent of each vertex that makes the shortest path
   int *parent = malloc(graph->n * sizeof(int));
   if (parent == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   p_priorityQueue priority_queue = initialize_priority_queue(graph->n);

   // Initialize the arrays and set every element as infinite weight
   for (int v = 0; v < graph->n; v ++)
   {
      parent[v] = -1;
      push_element(priority_queue, v, INT_MAX);
   }

   // Set the path as starting on the vertex start
   parent[start] = start;
   lower_priority(priority_queue, start, 0);

   // Go though the priority queue updating each neighboor weight when appopriated til the end of the queue
   while (!is_empty(priority_queue))
   {
      int vertex = pop_minimum(priority_queue);

      // Only update if the vertex is reachable
      if (get_priority(priority_queue, vertex) != INT_MAX)
         for (p_node node = graph->adjacency[vertex]; node != NULL; node = node->next)
         {
            // For every neighboor, check if the path going through the current vertex is shorter
            int new_weight = get_priority(priority_queue, vertex) + node->weight;

            if (new_weight < get_priority(priority_queue, node->v))
            {
               lower_priority(priority_queue, node->v, new_weight);
               parent[node->v] = vertex;
            }
         }
   }

   destroy_priority_queue(priority_queue);
   return parent;
}

void remove_bigger_edges(p_graph graph, int threshold)
{
   for (int v = 0; v < graph->n; v ++)
      graph->adjacency[v] = remove_bigger_elements(graph->adjacency[v], threshold);
}

void destroy_graph(p_graph graph)
{
   for (int i = 0; i < graph->n; i ++)
      destroy_list(graph->adjacency[i]);
   
   free(graph->adjacency);
   free(graph);
}