#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"


int max(int a, int b)
{
   return (a > b) ? a : b;
}

// Calculate the vertex index of a given floor in a given elevator
// Floor: n | elevator: A = vertex: 2 * n
// Floor: n | elevator: B = vertex: 2 * n - 1
// Floor 0 is vertex 0 for both elevator A and B, as its the end. Thats why use max(vertex, 0)
int floor_to_vertex(int floor, char elevator)
{
   switch (elevator)
   {
   case 'A':
      return max(2 * floor, 0);
      break;
   
   case 'B':
      return max(2 * floor - 1, 0);
      break;
   
   default:
      return 0;
      break;
   }
}

// Given a vertex, return the elevator associated.
// Even vertices are elevator A. Odd vertices are elevator B
// As there is no interpretation for floor 0 we can default to 'B'
char vertex_to_elevator(int vertex)
{
   if (vertex % 2 == 0)
      return 'A';
   else
      return 'B';
}

// Given an elevator A or B on a given floor and its paremeters, create the edges on the graph that represent the elevator
void insert_elevator_edges(char elevator, p_graph graph, int floor, int down, int up)
{
   insert_edge(graph, floor_to_vertex(floor, elevator), floor_to_vertex(floor + up, elevator));    // Going up connections
   insert_edge(graph, floor_to_vertex(floor, elevator), floor_to_vertex(floor - down, elevator));  // Going down connections
}

// Recursively print the path in pos order, so it goes in the right order
void print_path(int *path, int end, int curr_vert)
{
   int prev_vert = path[curr_vert];    // Path[i] holds the previous vertex of vertex[i] from the perspective of Top -> Bottom

   // If the previous vertex is the top of the tower then we can stop
   if (prev_vert != end)
   {
      // Recursion
      print_path(path, end, prev_vert);

      char curr_elevator = vertex_to_elevator(curr_vert);
      char prev_elevator = vertex_to_elevator(prev_vert);

      // Dont print if it is a change of elevator
      if (curr_vert == 0 || curr_elevator == prev_elevator)
      {
         if (prev_elevator == 'A')
         {
            if (prev_vert > curr_vert)
               printf("A X\n");
            else
               printf("A Y\n");
         }
         else
         {
            if (prev_vert > curr_vert)
               printf("B W\n");
            else
               printf("B Z\n");
         }
      }
   }
}

int main()
{
   int num_scenarios, num_floors;
   int x, y, w, z;
   p_graph graph;

   scanf("%d", &num_scenarios);

   for (int scenario = 1; scenario <= num_scenarios; scenario ++)
   {
      scanf("%d", &num_floors);

      // Number of vertices on the graph: 2 * (n + 1)
      // Each of the n floors has 2 elevators and 1 vertex for the start and 1 for the end
      graph = initialize_graph(2 * (num_floors + 1));

      // Connect the start to both elevators
      insert_edge(graph, 2 * num_floors + 1, floor_to_vertex(num_floors, 'B'));
      insert_edge(graph, 2 * num_floors + 1, floor_to_vertex(num_floors, 'A'));

      for (int floor = num_floors; floor > 0; floor --)
      {
         scanf("%d %d %d %d", &x, &y, &w, &z);

         // Insert the edges that represent it floor
         // The order matters. From top to bottom of the edges added is low priority to high priority
         insert_elevator_edges('B', graph, floor, w, z);                                           // Edges for elevator B
         insert_bidirect_edge(graph, floor_to_vertex(floor, 'A'), floor_to_vertex(floor, 'B'));    // Edges between elevators(change elevator)
         insert_elevator_edges('A', graph, floor, x, y);                                           // Edges for elevator A
      }

      // Calculate the path using BFS approach
      int *path = BFS(graph, 2 * num_floors + 1);

      printf("Cenário #%d\n", scenario);
      print_path(path, 2 * num_floors + 1, 0);  // Start printing til reaching the top from the bottom

      free(path);
      destroy_graph(graph);
   }

   return EXIT_SUCCESS;
}
