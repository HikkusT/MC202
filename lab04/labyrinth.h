#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "coord.h"

typedef struct {
   char **matrix;
   int rows;
   int columns;
} Labyrinth;

/**
 * This function returns a Labyrinth intialized with the given parameters
 */
Labyrinth create_labyrinth(char** matrix, int rows, int columns);

/**
 * This function returns a Labyrinth's width (number of columns)
 */
int get_labyrinth_width(Labyrinth labyrinth);

/**
 * This function returns a Labyrinth's height (number of rows)
 */
int get_labyrinth_height(Labyrinth labyrinth);

/**
 * This function returns the element of a Labyrinth in a given coord(position)
 */
char get_element(Labyrinth labyrinth, Coord pos);

/**
 * This function sets the element of a Labyrinth in a given coord(position)
 */
void set_element(Labyrinth labyrinth, Coord pos, char c);

/**
 * Returns the Coord(pos) of the entrance('E' mark)
 */
Coord get_labyrinth_entrance(Labyrinth labyrinth);

/**
 * Returns the Coord(pos) of the sword('S' mark)
 */
Coord get_sword_pos(Labyrinth labyrinth);

/**
 * Formats the labyrinth changing all the path markers to '*'
 */
void format_markers(Labyrinth labyrinth, char first_marker, char second_marker);

/**
 * Prints the labyrinth
 */
void print_labyrinth(Labyrinth labyrinth);

/**
 * Free memory allocated dynamically
 */
void free_labyrinth(Labyrinth labyrinth);


#endif
