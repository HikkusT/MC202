#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "leitor.h"

int main()
{
   char titulo[MAXCHAR_TITULO]; // string para a leitura do título
   char nome[MAXCHAR_LNOME];    // string para a leitura do nome

   Livro* livros = NULL;        // ponteiro para o vetor de livros
   Leitor* leitores = NULL;     // ponteiro para o vetor de leitores

   int num_livros = 0;
   int num_leitores = 0;

   int dia, mes, ano;
   Data data;
   Data data_consulta;

   int index, num_indices;

   // Read from input
   // ---------------
   scanf("%d %d", &num_livros, &num_leitores);

   livros   = malloc(num_livros * sizeof(Livro));
   leitores = malloc(num_leitores * sizeof(Leitor));

   if(livros == NULL || leitores == NULL)
   {
      printf("Nao ha memoria suficente!\n");
      exit(1);
   }

   // Get books
   for (int i = 0; i < num_livros; i ++)
   {
      scanf("%d-%d-%d ", &dia, &mes, &ano);
      scanf(" %[^\n]", titulo);

      data = criar_data(dia, mes, ano);
      livros[i] = criar_livro(titulo, data);
   }

   // Get readers
   for (int i = 0; i < num_leitores; i ++)
   {
      scanf(" %s", nome);
      scanf("%d", &num_indices);

      leitores[i] = criar_leitor(nome, num_indices);

      for (int j = 0; j < num_indices; j ++)
      {
         scanf("%d", &index);

         if (index > 0)
            registrar_restituicao(&leitores[i], index);
         else
            registrar_devolucao(&leitores[i], -index);
      }
   }

   // Get query date
   scanf("%d-%d-%d", &dia, &mes, &ano);
   data_consulta = criar_data(dia, mes, ano);


   // Print output
   // ------------
   for (int i = 0; i < num_leitores; i ++)
   {
      const int* restituicoes = obter_restituicoes(&leitores[i]);
      const int* devolucoes   = obter_devolucoes(&leitores[i]);

      printf("%s\n", obter_nome(&leitores[i]));

      for (int j = 0; j < obter_num_restituicoes(&leitores[i]); j ++)
      {
         index = restituicoes[j] - 1;   // Index goes from 0 to n-1 instead of 1 to n
         data = obter_data_emprestimo(&livros[index]);

         if (!eh_nula(data) && eh_menor_que(data, data_consulta))
            printf("Restituição: %s\n", obter_titulo(&livros[index]));
      }

      for (int j = 0; j < obter_num_devolucoes(&leitores[i]); j ++)
      {
         index = devolucoes[j] - 1;   // Index goes from 0 to n-1 instead of 1 to n
         data = obter_data_emprestimo(&livros[index]);

         if (!eh_nula(data) && eh_menor_que(data, data_consulta))
            printf("Devolução: %s\n", obter_titulo(&livros[index]));
      }

      desalocar_memoria(&leitores[i]);
   }

   free(livros);
   free(leitores);

   return 0;
}
