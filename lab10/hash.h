#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_STR_LEN 40001

typedef struct Data
{
   char pattern[MAX_STR_LEN];
   int index;
   int count;
} Data;

typedef Data * p_data;

typedef struct HashTable
{
   p_data *table;
   int M;
} HashTable;

typedef HashTable * p_hashTable;

p_hashTable create_hash_table(int n);

void insert(p_hashTable ht, char *key, int index);

void search_by_key(p_hashTable ht, char *key);

int get_count_by_index(p_hashTable ht, int index);

#endif
