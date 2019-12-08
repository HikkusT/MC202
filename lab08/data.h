#ifndef DATA_H
#define DATA_H

#define MESSAGE_LEN 9

typedef struct Data
{
   int index;
   char message[MESSAGE_LEN];
} Data;

/**
 * Create a data with a given index and message
 */
Data create_data(int index, char message[]);

/**
 * Print a data
 */
void print_data(Data data);

#endif