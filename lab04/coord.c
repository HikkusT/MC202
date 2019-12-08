#include "coord.h"

Coord create_coord(int x, int y)
{
   Coord coord;
   coord.x = x;
   coord.y = y;

   return coord;
}

int get_xpos(Coord coord)
{
   return coord.x;
}

int get_ypos(Coord coord)
{
   return coord.y;
}

// The bellow funcions are based on matrix indices
// So y axis is pointed downwards and x axis is as expected
Coord east_from(Coord coord)
{
   int xpos = get_xpos(coord) + 1;
   int ypos = get_ypos(coord);

   return create_coord(xpos, ypos);
}

Coord south_from(Coord coord)
{
   int xpos = get_xpos(coord);
   int ypos = get_ypos(coord) + 1;     // South means to get the row bellow which means row + 1

   return create_coord(xpos, ypos);
}

Coord west_from(Coord coord)
{
   int xpos = get_xpos(coord) - 1;
   int ypos = get_ypos(coord);

   return create_coord(xpos, ypos);
}

Coord north_from(Coord coord)
{
   int xpos = get_xpos(coord);
   int ypos = get_ypos(coord) - 1;     // North means to get the row above which means row - 1


   return create_coord(xpos, ypos);
}

int is_in_boundaries(Coord coord, int width, int height)
{
   int xpos = get_xpos(coord);
   int ypos = get_ypos(coord);

   // Check if its inside the matrix
   if ((xpos < 0 || xpos >= width) || (ypos < 0 || ypos >= height))
      return 0;
   else
      return 1;
}