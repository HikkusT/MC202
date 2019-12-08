#ifndef COORD_H
#define COORD_H

typedef struct {
   int x;
   int y;
} Coord;

/**
 * This function returns a Coord intialized with the given parameters
 */
Coord create_coord(int x, int y);

/**
 * This function returns the x coordinate of a Coord
 */
int get_xpos(Coord coord);

/**
 * This function returns the y coordinate of a Coord
 */
int get_ypos(Coord coord);

/**
 * This function returns a Coord east from a given Coord
 */
Coord east_from(Coord coord);

/**
 * This function returns a Coord south from a given Coord
 */
Coord south_from(Coord coord);

/**
 * This function returns a Coord west from a given Coord
 */
Coord west_from(Coord coord);

/**
 * This function returns a Coord north from a given Coord
 */
Coord north_from(Coord coord);

/**
 * This function checks if a coord is inside a boundary box
 * of a given width and height
 */
int is_in_boundaries(Coord coord, int width, int height);


#endif