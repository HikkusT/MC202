#include <string.h>
#include "aluno.h"

Aluno criar_aluno(int registro_academico, float desempenho)
{
   Aluno aluno;

   aluno.registro_academico = registro_academico;
   aluno.desempenho = desempenho;
   aluno.num_disciplinas = 0;

   return aluno;
}

Aluno adicionar_disciplina(Aluno aluno, const char disciplina[])
{
   strcpy(aluno.disciplinas[aluno.num_disciplinas], disciplina);
   aluno.num_disciplinas ++;

   return aluno;
}

float obter_desempenho(Aluno aluno)
{
   return aluno.desempenho;
}

int validar_matricula(Aluno aluno, const char disciplina[])
{
   for (int i = 0; i < aluno.num_disciplinas; i++)
      if (strcmp(aluno.disciplinas[i], disciplina) == 0)
         return 1;

   return 0;
}
