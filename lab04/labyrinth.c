#include <stdio.h>
#include <stdlib.h>

#include "labyrinth.h"
#include "coord.h"

Labyrinth create_labyrinth(char** matrix, int rows, int columns)
{
   Labyrinth Labyrinth;
   Labyrinth.rows = rows;
   Labyrinth.columns = columns;
   Labyrinth.matrix = matrix;

   return Labyrinth;
}

int get_labyrinth_width(Labyrinth labyrinth)
{
   return labyrinth.columns;
}

int get_labyrinth_height(Labyrinth labyrinth)
{
   return labyrinth.rows;
}

char get_element(Labyrinth labyrinth, Coord pos)
{
   int i = get_ypos(pos);        // i index is used for rows, which represents the y axis
   int j = get_xpos(pos);        // j index is used for columns, which represents the x axis

   return labyrinth.matrix[i][j];
}

void set_element(Labyrinth labyrinth, Coord pos, char c)
{
   int i = get_ypos(pos);        // i index is used for rows, which represents the y axis
   int j = get_xpos(pos);        // j index is used for columns, which represents the x axis

   labyrinth.matrix[i][j] = c;
}

// Finds the 'E' mark in the matrix
Coord get_labyrinth_entrance(Labyrinth labyrinth)
{
   int width = get_labyrinth_width(labyrinth);

   for (int i = 0; i < width; i ++)
   {
      Coord pos = create_coord(i, 0);
      if (get_element(labyrinth, pos) == 'E')
         return pos;
   }
   
   return create_coord(-1, -1);
}

// Finds the 'S' mark in the matrix
Coord get_sword_pos(Labyrinth labyrinth)
{
   int width = get_labyrinth_width(labyrinth);
   int height = get_labyrinth_height(labyrinth);

   for (int i = 0; i < height; i ++)
      for (int j = 0; j < width; j ++)
      {
         Coord pos = create_coord(j, i);
         if (get_element(labyrinth, pos) == 'S')
            return pos;
      }
   
   return create_coord(-1, -1);
}

// Replaces all path marks from both paths to '*'
void format_markers(Labyrinth labyrinth, char first_marker, char second_marker)
{
   int width = get_labyrinth_width(labyrinth);
   int height = get_labyrinth_height(labyrinth);

   for (int i = 0; i < height; i ++)
      for (int j = 0; j < width; j ++)
      {
         Coord pos = create_coord(j, i);
         if (get_element(labyrinth, pos) == first_marker || get_element(labyrinth, pos) == second_marker)
            set_element(labyrinth, pos, '*');
      }
}

void print_labyrinth(Labyrinth labyrinth)
{
   int width = get_labyrinth_width(labyrinth);
   int height = get_labyrinth_height(labyrinth);

   for (int i = 0; i < height; i ++)
   {
      for (int j = 0; j < width; j ++)
      {
         Coord pos = create_coord(j, i);
         printf("%c", get_element(labyrinth, pos));
      }
      printf("\n");
   }
}

// Free the matrix on the labyrinth struct
void free_labyrinth(Labyrinth labyrinth)
{
   int height = get_labyrinth_height(labyrinth);

   for (int i = 0; i < height; i ++)
   {
      free(labyrinth.matrix[i]);
   }
   free(labyrinth.matrix);
}