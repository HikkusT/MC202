#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int hash(p_hashTable ht, char *key)
{
   int ret = 0;
   for (int i = 0; i < strlen(key); i ++)
      ret = (256 * ret + key[i]) % ht->M;
    
   return ret;
}

int is_empty(p_hashTable ht, int i)
{
   if (ht->table[i]->index == -1)
      return 1;
   else
      return 0;
}

p_hashTable create_hash_table(int n)
{
   p_hashTable ht = malloc(sizeof(HashTable));
   if (ht == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   ht->M = n;
   ht->table = malloc(ht->M * sizeof(p_data));
   if (ht->table == NULL)
   {
      printf("Not enough memory!\n");
      exit(1);
   }

   for (int i = 0; i < ht->M; i ++)
   {
      ht->table[i] = malloc(sizeof(Data));
      ht->table[i]->count = 0;
      ht->table[i]->index = -1;
   }

   return ht;
}

void insert(p_hashTable ht, char *key, int index)
{
   int n = hash(ht, key);
   int count = 0;

   while (!is_empty(ht, n))
   {
      n = (n + 1) % ht->M;
      count ++;

      if (count >= ht->M)
      {
         exit(1);
      }
   }
   
   strcpy(ht->table[n]->pattern, key);
   ht->table[n]->index = index;
}

void search_by_key(p_hashTable ht, char *key)
{
   int n = hash(ht, key);
   int count = 0;

   while (!is_empty(ht, n))
   {
      if (strcmp(ht->table[n]->pattern, key) == 0)
      {
         ht->table[n]->count ++;
         break;
      }

      n = (n + 1) % ht->M;
      count ++;

      if (count >= ht->M)
      {
         printf("Collision looped!\n");
         exit(1);
      }
   }
}

int get_count_by_index(p_hashTable ht, int index)
{
   int i;
   for (i = 0; i < ht->M; i ++)
      if (ht->table[i]->index == index)
         break;

   return ht->table[i]->count;
}