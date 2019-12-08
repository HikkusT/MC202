#include <string.h>
#include "livro.h"

Livro criar_livro(const char* titulo, Data emprestimo)
{
   Livro livro;

   strcpy(livro.titulo, titulo);
   livro.emprestimo = emprestimo;

   return livro;
}

Data obter_data_emprestimo(const Livro* livro)
{
   return livro->emprestimo;
}

const char* obter_titulo(const Livro* livro)
{
   return livro->titulo;
}
