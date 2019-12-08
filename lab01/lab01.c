#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Rotates a vector 90 degrees counter clockwise around the origin using (x,y) -> (-y,x)
void rotate_left(int vec[2])
{
   int aux;

   aux = vec[0];
   vec[0] = -vec[1];
   vec[1] = aux;
}

// Walks from a position pos towards a direction dir
void update_position(int pos[], int dir[])
{
   pos[0] += dir[0];
   pos[1] += dir[1];
}

int is_next_pos_valid(double matrix[][MAX], int curr_pos[], int dir[], int rows, int columns)
{
   int next_pos[2] = {curr_pos[0], curr_pos[1]};
   update_position(next_pos, dir);

   // Check if new position is out of bounds
   if (next_pos[0] < 0 || next_pos[0] >= rows || next_pos[1] < 0 || next_pos[1] >= columns)
      return 0;
   
   // If the new postion has been filled(!= -1) it is not valid
   if (matrix[next_pos[0]][next_pos[1]] > 0)
      return 0;
   else
      return 1;
}

void print_matrix(double matrix[][MAX], int rows, int columns)
{
   for (int i = 0; i < rows; i ++)
   {
      for (int j = 0; j < columns - 1; j ++)
         printf("%.1lf ", matrix[i][j]);

      printf("%.1lf\n", matrix[i][columns - 1]);
   }
}

int main()
{
   int rows, columns;

   double matrix[MAX][MAX] = {{-1.}};
   double v[MAX * MAX] = {0};

   // Read from input
   scanf("%d %d", &rows, &columns);
   for (int i = 0; i < rows * columns; i ++)
      scanf(" %lf", &v[i]);
   
   // Fill the matrix by iterating through it with a direction
   int pos[2] = {rows - 1, columns - 1};  // Start to fll it from the bottom right corner
   int dir[2] = {-1, 0}; // Initial direction is "up", which in matrix interations translates to decresaing the row index
   for (int i = 0; i < rows * columns; i ++)
   {
      matrix[pos[0]][pos[1]] = v[i];

      if (!is_next_pos_valid(matrix, pos, dir, rows, columns))
         rotate_left(dir);

      update_position(pos, dir);
   }

   print_matrix(matrix, rows, columns);
   
   return EXIT_SUCCESS;
}
