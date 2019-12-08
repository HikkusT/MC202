#include <stdio.h>
#include <stdlib.h>

#include "labyrinth.h"
#include "coord.h"

// Bactracking algorithm to find the path
int find_path(Labyrinth labyrinth, Coord pos, char goal, char marker)
{
   char old_char = get_element(labyrinth, pos);

   // If its the goal, we found it
   if (old_char == goal)
      return 1;

   // If its a wall, somewhere already on the path or the minotaur(when finding the sword), go back
   if (old_char == '#' || old_char == marker || old_char == 'M')
      return 0;

   // Mark the position as walked (except if its the sword or the entrance)
   if (old_char != 'S' && old_char != 'E')
      set_element(labyrinth, pos, marker);

   // Test for each direction, and if it found the goal, return 1(True)
   // -----------------------------------------------------------------
   int width = get_labyrinth_width(labyrinth);
   int height = get_labyrinth_height(labyrinth);

   if (is_in_boundaries(east_from(pos), width, height))
      if (find_path(labyrinth, east_from(pos), goal, marker))
         return 1;

   if (is_in_boundaries(south_from(pos), width, height))
      if (find_path(labyrinth, south_from(pos), goal, marker))
         return 1;

   if (is_in_boundaries(west_from(pos), width, height))
      if (find_path(labyrinth, west_from(pos), goal, marker))
         return 1;

   if (is_in_boundaries(north_from(pos), width, height))
      if (find_path(labyrinth, north_from(pos), goal, marker))
         return 1;

   // If no direction worked, set back to the old char to mark as not walked
   // and mantain the matrix
   set_element(labyrinth, pos, old_char);
   return 0;
}

int main()
{
   // Read matrix from input
   // ---------------
   int m, n;
   char **matrix;

   scanf("%d %d ", &m, &n);
   matrix = malloc(m * sizeof(char *));
   if (matrix == NULL)
   {
      printf("Nao ha memoria suficente!\n");
      exit(1);
   }

   for (int i = 0; i < m; i++)
   {
      matrix[i] = malloc(n * sizeof(char));
      if(matrix[i] == NULL)
      {
         printf("Nao ha memoria suficente!\n");
         exit(1);
      }

      for (int j = 0; j < n; j ++)
         scanf("%c", &matrix[i][j]);

      scanf(" ");    // Clear buffer for \n
   }
   Labyrinth labyrinth = create_labyrinth(matrix, m, n);

   // Find the path to the sword, marking with '.'
   // --------------------------------------------
   Coord start_pos = get_labyrinth_entrance(labyrinth);
   find_path(labyrinth, start_pos, 'S', '.');

   // Find the path to the minotaur, marking with '@'
   // -----------------------------------------------
   Coord sword_pos = get_sword_pos(labyrinth);
   find_path(labyrinth, sword_pos, 'M', '@');

   // Format all the markers to '*' and print
   // ---------------------------------------
   format_markers(labyrinth, '.', '@');
   print_labyrinth(labyrinth);
   free_labyrinth(labyrinth);

   return EXIT_SUCCESS;
}
