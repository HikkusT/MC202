#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

// Problem constraints
#define TIME_TO_DEFUSE_BOMB 600
#define TIME_TO_DEFUSE_GAS 120
#define VELOCITY 20
#define MAX_TIME 3600

// Start from vertex start and transverse the path vector printing till getting to the end, whose parent is itself
void print_path(int *path, int start)
{
   for (int vertex = start; vertex != path[vertex]; vertex = path[vertex])
      printf("%d ", vertex);
}

// Start from vertex start and transverse the path vector adding to distance till getting to the end, whose parent is itself
int calculate_distance(p_graph graph, int *path, int start)
{
   int distance = 0;

   for (int vertex = start; vertex != path[vertex]; vertex = path[vertex])
      distance += get_edge_weight(graph, vertex, path[vertex]); // Add the weight of the edge between the curr vertex and next vertex

   return distance;
}

int main()
{
   int total_time = 0;

   // Graph variables
   int num_vertices, num_edges;
   int vertA, vertB, weight;
   int web_length;
   int start, bomb, mj;
   p_graph graph;

   scanf("%d %d", &num_vertices, &num_edges);
   graph = initialize_graph(num_vertices);

   // Build the graph
   for (int edge = 0; edge < num_edges; edge ++)
   {
      scanf("%d %d %d", &vertA, &vertB, &weight);
      insert_bidirect_edge(graph, vertA, vertB, weight);
   }

   scanf("%d %d %d %d", &web_length, &start, &bomb, &mj);

   // Remove edges limited by the length of the web
   remove_bigger_edges(graph, 2 * web_length);

   int *path_to_bomb = dijkstra(graph, bomb);
   int *path_to_mj = dijkstra(graph, mj);

   // travel_time_x_y representing the time to travel the distance between x and y
   float travel_time_start_bomb = calculate_distance(graph, path_to_bomb, start) / (float) VELOCITY;
   float travel_time_start_mj = calculate_distance(graph, path_to_mj, start) / (float) VELOCITY;
   float travel_time_bomb_mj = calculate_distance(graph, path_to_bomb, mj) / (float) VELOCITY;

   // Cases where we can visit both the bomb and mj on time
   if (travel_time_start_bomb < travel_time_start_mj)
   {
      // When it is faster to visit the bomb first
      total_time = travel_time_start_bomb + TIME_TO_DEFUSE_BOMB + travel_time_bomb_mj + TIME_TO_DEFUSE_GAS;

      if (total_time <= MAX_TIME)
      {
         print_path(path_to_bomb, start);
         print_path(path_to_mj, bomb);
         printf("%d\n", mj);
      }
   }
   else
   {
      // When it is faster to visit mj first
      total_time = travel_time_start_mj + TIME_TO_DEFUSE_GAS + travel_time_bomb_mj + TIME_TO_DEFUSE_BOMB;

      if (total_time <= MAX_TIME)
      {
         print_path(path_to_mj, start);
         print_path(path_to_bomb, mj);
         printf("%d\n", bomb);
      }
   }
   
   // Cases where we can only visit one of the locations on time
   if (total_time > MAX_TIME)
   {
      if (travel_time_start_bomb + TIME_TO_DEFUSE_BOMB < travel_time_start_mj + TIME_TO_DEFUSE_GAS)
      {
         // When we can only visit the bomb
         print_path(path_to_bomb, start);
         printf("%d\n", bomb);
      }
      else
      {
         // When we can only visit mj
         print_path(path_to_mj, start);
         printf("%d\n", mj);
      }
   }

   // Free the resources
   free(path_to_bomb);
   free(path_to_mj);
   destroy_graph(graph);

   return EXIT_SUCCESS;
}
