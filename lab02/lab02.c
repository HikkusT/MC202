#include <stdio.h>

#include "aluno.h"
#include "professor.h"

#define MAX_M 100 // nº máximo de professores
#define MAX_N 200 // nº máximo de alunos

void processar_aumento(Professor professores[], Aluno alunos[], int m, int n);

int main()
{
    /** ***********************************************************************
    *          ATENÇÃO: A função principal não deve ser modificada!           *
    *********************************************************************** **/

   Professor professores[MAX_M];  // vetor para o conjunto de professores
   Aluno alunos[MAX_N];           // vetor para o conjunto de alunos

   char nome[MAXCHAR_PNOME], disciplina[MAXCHAR_CODIGO];
   float salario, desempenho;
   int registro_academico, num_disciplinas;

   int m, n;

   scanf("%d", &m); // lê o nº de professores

   for (int i = 0; i < m; ++i) { // segue com a leitura dos professores
      scanf(" %s %f %s", nome, &salario, disciplina);
      professores[i] = criar_professor(nome, salario, disciplina);
   }

	scanf("%d", &n);  // lê o nº de alunos

   for (int i = 0; i < n; ++i) { // segue com a leitura dos alunos

      scanf("%d %f %d", &registro_academico, &desempenho, &num_disciplinas);
      alunos[i] = criar_aluno(registro_academico, desempenho);

      while (num_disciplinas > 0) {
         scanf(" %s", disciplina);
         alunos[i] = adicionar_disciplina(alunos[i], disciplina);
         num_disciplinas -= 1;
      }
   }

	processar_aumento(professores, alunos, m, n); // processa a bonificação

   for (int i = 0; i < m; ++i) { // segue com a impressão da saída
      obter_nome(professores[i], nome);
      printf("%s %.2f\n", nome, obter_salario(professores[i]));
   }

	return 0;
}

/**
 * Esta função recebe como parâmetro um conjunto de variáveis que abstraem a
 * entrada do problema e realiza a bonificação salarial dos professores
 * conforme especificado no enunciado da tarefa.
 */

void processar_aumento(Professor professores[], Aluno alunos[], int m, int n)
{
   float menor_desempenho;
   char disciplina[MAXCHAR_CODIGO];
   int disciplina_vazia = 1;

   for (int i = 0; i < m; i ++)
   {
      obter_disciplina(professores[i], disciplina);
      menor_desempenho = 11.f;
      disciplina_vazia = 1;

      for (int j = 0; j < n; j++)
         if (validar_matricula(alunos[j], disciplina))
         {
            disciplina_vazia = 0;
            if (obter_desempenho(alunos[j]) <= menor_desempenho)
               menor_desempenho = obter_desempenho(alunos[j]);
         }
      
      if (!disciplina_vazia)
      {
         if (menor_desempenho == 10.f)
            professores[i] = aplicar_aumento(professores[i], 0.15f);
         else if (menor_desempenho >= 9.f)
            professores[i] = aplicar_aumento(professores[i], 0.1f);
         else if (menor_desempenho >= 8.5f)
            professores[i] = aplicar_aumento(professores[i], 0.05f);
      }
   }
}
