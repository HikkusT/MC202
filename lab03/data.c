#include "data.h"

Data criar_data(int dia, int mes, int ano)
{
   Data data;
   data.dia = dia;
   data.mes = mes;
   data.ano = ano;

   return data;
}

int eh_nula(Data data)
{
   if (data.dia == 0 && data.mes == 0 && data.ano == 0)
      return 1;
   else
      return 0; 
}

int eh_menor_que(Data data1, Data data2)
{
   // Compare two equivalent numbers in the form yyyymmdd
   int data1_int_value = 10000 * data1.ano + 100 * data1.mes + data1.dia;
   int data2_int_value = 10000 * data2.ano + 100 * data2.mes + data2.dia;

   if (data1_int_value < data2_int_value)
      return 1;
   else
      return 0;
}
