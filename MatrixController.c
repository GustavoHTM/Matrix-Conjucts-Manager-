#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <Windows.h>
#include <stdbool.h>
#include "MatrixService.h"

#define ROWS 8
#define COLUMNS 10

int main()
{
  void (*funcoes[])() = {invalid, option1, insertValues, removeRow, option4, option5, printRow, printMatrix, searchValue};

  struct MatrixAttributes objMatrix;
  memset(objMatrix.matrix, 0, sizeof objMatrix.matrix);
  memset(objMatrix.numberOfColumnsUsed, 0, sizeof objMatrix.numberOfColumnsUsed);
  objMatrix.numberOfRowsUsed = -1;

  int option = 0;

  do
  {
    system("cls");
    printf("Gerenciamento de conjuntos\n\n");
    printf("Menu\n\n");
    printf("1 - Criar um novo conjunto vazio\n");
    printf("2 - Inserir dados em um conjunto\n");
    printf("3 - Remover um conjunto\n");
    printf("4 - Fazer a uniao entre dois conjuntos\n");
    printf("5 - Fazer a interseccao entre dois conjuntos\n");
    printf("6 - Mostrar um conjunto\n");
    printf("7 - Mostrar todos os conjuntos\n");
    printf("8 - Fazer busca por um valor\n");
    printf("9 - Sair do programa\n");
    printf("\n>> Escolha uma opcao: ");
    scanf("%d", &option);

    if (option < 1 || option > 9)
    {
      (*funcoes[0])();
    }
    else if (option < 9)
    {
      (*funcoes[option])(&objMatrix);
    }

  } while (option != 9);
  system("cls");
  printf("\n>> Fim da Execucao do programa <<\nEquipe: Gustavo HTM e Jezreel KM\n\n");
  return 1;
}