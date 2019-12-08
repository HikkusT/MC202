#include <stdio.h>
#include <string.h>
#include "data.h"

Data create_data(int index, char message[])
{
   Data data;
   data.index = index;
   strcpy(data.message, message);

   return data;
}

void print_data(Data data)
{
   printf("%s", data.message);
}