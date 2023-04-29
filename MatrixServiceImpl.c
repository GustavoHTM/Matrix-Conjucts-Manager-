#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <stdbool.h>
#include "MatrixService.h"

boolean newRow(int *numberOfRows)
{
  if (*numberOfRows >= ROWS - 1)
  {
    printf("O numero de conjuntos permitidos ja esta no limite, tente novamente...");
    Sleep(3000);
    return false;
  }
  else
  {
    return true;
  }
}

void unionXIntersection(bool verifier, struct MatrixAttributes *obj)
{
  int *columnsUsed = obj->numberOfColumnsUsed;

  if (obj->numberOfRowsUsed < 1)
  {
    printf("Numero de conjuntos insuficiente, tente novamente...");
    Sleep(3000);
    return;
  }

  obj->numberOfRowsUsed++;
  int numberOfRows = obj->numberOfRowsUsed;
  int junct[2];

  do
  {
    printf("Selecione o 1 conjunto: ");
    scanf("%d", &junct[0]);
    if (junct[0] > numberOfRows || junct[0] < 0)
    {
      printf("\nValor invalido, tente novamente...\n\n");
    }
  } while (junct[0] > numberOfRows || junct[0] < 0);

  do
  {
    printf("\n\nSelecione o 2 conjunto: ");
    scanf("%d", &junct[1]);
    if (junct[1] > numberOfRows || junct[1] < 0)
    {
      printf("\nValor invalido, tente novamente...\n\n");
    }
  } while (junct[1] > numberOfRows || junct[1] < 0);

  int length1 = columnsUsed[junct[0]], length2 = columnsUsed[junct[1]];
  int length = length1 + length2;

  int *vector1 = obj->matrix[junct[0]], *vector2 = obj->matrix[junct[1]];
  int vector[length];

  int count = 0;
  bool aux = false;

  for (int i = 0; i < length; i++)
  {
    if (i < length1)
      vector[i] = vector1[i];
    else
    {
      for (int j = 0; j < i; j++)
      {
        if (vector[j] == vector2[i - length1])
        {
          count++;
          vector[length - count] = vector[j];
          aux = true;
          break;
        }
      }
      if (aux)
        vector[i - count] = vector2[i];
    }
  }

  if (verifier)
  {
    if (length - count > COLUMNS)
    {
      printf("\n\nOs dois conjuntos juntos ultrapassam o limite de espacos, tente novamente...");
      Sleep(3000);
      return;
    }

    for (int i = 0; i < length - count; i++)
    {
      obj->matrix[numberOfRows][i] = vector[i];
    }
  }
  else
  {
    for (int i = 0; i < count; i++)
    {
      obj->matrix[numberOfRows][i] = vector[length - i - 1];
    }
  }
}

void invalid()
{
  printf("Essa nao e uma resposta valida, tente novamente...");
  Sleep(3000);
}

void option1(struct MatrixAttributes *obj)
{
  boolean validator = newRow(&obj->numberOfRowsUsed);
  if (validator)
  {
    obj->numberOfRowsUsed++;
    printf("Novo conjunto adicionado com sucesso");
    Sleep(3000);
  }
}

void insertValues(struct MatrixAttributes *obj)
{
  int numberOfRows = obj->numberOfRowsUsed;
  int columns = 0, row = 0;
  boolean aux = false;

  if (numberOfRows < 0)
  {
    printf("\nAinda nao ha nenhum conjunto, tente novamente...");
    Sleep(3000);
    return;
  }
  system("cls");

  do
  {
    printf(">> Digite o numero do conjunto que deseja inserir dados: ");
    scanf("%d", &row);
    if (row < 0 || row > numberOfRows)
    {
      printf("Valor invalido, tente novamente...\n\n");
    }

  } while (row < 0 || row > numberOfRows);

  int columnsUsed = obj->numberOfColumnsUsed[row];

  do
  {
    printf("\n>> Digite a quantidade de algarismos que deseja inserir no conjunto: ");
    scanf("%d", &columns);
    if ((columns < 0 || columns > (COLUMNS - columnsUsed)))
    {
      printf("Valor ivalido ou ultrapassa o limite permitido, tente novamente...\n\n");
    }

  } while (columns < 0 || columns > (COLUMNS - columnsUsed));

  for (int i = 0; i < columns; i++)
  {
    int value = 0;
    do
    {
      aux = false;
      printf("\nInsira o %d valor: ", i + 1);
      scanf("%d", &value);

      if (value == 0)
      {
        printf("Nao e possivel inserir o valor 0 no conjunto, tente novamente...\n");
        aux = true;
      }

      if (!aux)
        for (int j = 0; j < i + columnsUsed; j++)
          if (value == obj->matrix[row][j])
          {
            printf("Esse valor ja foi inserido no conjunto, tente novamente...\n");
            aux = true;
            break;
          }

    } while (aux == true);
    obj->matrix[row][i + columnsUsed] = value;
  }
  obj->numberOfColumnsUsed[row] += columns;
}

void removeRow(struct MatrixAttributes *obj)
{
  int numberOfRows = obj->numberOfRowsUsed;
  int row = 0;

  if (numberOfRows < 0)
  {
    printf("\nAinda nao ha nenhum conjunto, tente novamente...");
    Sleep(3000);
    return;
  }
  system("cls");

  do
  {
    printf("Digite o valor da linha que deseja remover: ");
    scanf("%d", &row);
    if (row > numberOfRows || row < 0)
    {
      printf("Valor invalido, tente novamente...\n\n");
    }
  } while (row > numberOfRows || row < 0);

  for (int i = row; i <= numberOfRows; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (i == numberOfRows)
        obj->matrix[i][j] = 0;
      else
        obj->matrix[i][j] = obj->matrix[i + 1][j];
    }
    if (i == numberOfRows)
      obj->numberOfColumnsUsed[i] = 0;
    else
      obj->numberOfColumnsUsed[i] = obj->numberOfColumnsUsed[i + 1];
  }
  obj->numberOfRowsUsed -= 1;
}

void option4(struct MatrixAttributes *obj)
{
  if (newRow(&obj->numberOfRowsUsed))
    unionXIntersection(true, obj);
}

void option5(struct MatrixAttributes *obj)
{
  if (newRow(&obj->numberOfRowsUsed))
    unionXIntersection(false, obj);
}

void printRow(struct MatrixAttributes *obj)
{
  int numberOfRows = obj->numberOfRowsUsed;
  if (numberOfRows < 0)
  {
    printf("\nAinda nao ha nenhum conjunto, tente novamente...");
    Sleep(3000);
    return;
  }
  int row = 0;
  do
  {
    printf("Selecione o conjunto que deseja ver: ");
    scanf("%d", &row);
    if (row > numberOfRows || row < 0)
    {
      printf("Valor invalido, tente novamente...\n\n");
    }
  } while (row > numberOfRows || row < 0);

  int columnsUsed = obj->numberOfColumnsUsed[row];

  printf("Conjunto %d: ", row);

  if (columnsUsed == 0)
  {
    printf("vazio");
  }
  else
  {

    printf("{");
    for (int i = 0; i < columnsUsed; i++)
    {
      if (obj->matrix[row][i] != 0)
      {
        if (i < columnsUsed - 1)
          printf("%d, ", obj->matrix[row][i]);
        else
          printf("%d", obj->matrix[row][i]);
      }
    }
    printf("}");
    printf(" [%d]", columnsUsed);
  }
  Sleep(3000);
}

void printMatrix(struct MatrixAttributes *obj)
{
  int rowsUsed = obj->numberOfRowsUsed;
  int *columnsUsed = obj->numberOfColumnsUsed;
  if (rowsUsed < 0)
  {
    printf("\nAinda nao ha nenhum conjunto, tente novamente...");
    Sleep(3000);
    return;
  }
  for (int i = 0; i < rowsUsed + 1; i++)
  {
    printf("\nConjunto %d: ", i);

    if (columnsUsed[i] == 0)
    {
      printf("vazio");
    }
    else
    {
      printf("{");
      for (int j = 0; j < columnsUsed[i]; j++)
      {
        if (j < columnsUsed[i] - 1)
          printf("%d, ", obj->matrix[i][j]);
        else
          printf("%d", obj->matrix[i][j]);
      }
      printf("}");
      printf(" [%d] ", columnsUsed[i]);
    }
  }
  Sleep(7000);
}

void searchValue(struct MatrixAttributes *obj)
{
  if (obj->numberOfRowsUsed < 0)
  {
    printf("\nAinda nao ha nenhum conjunto, tente novamente...");
    Sleep(3000);
    return;
  }
  int value = 0;
  printf(">> Digite o valor que deseja buscar: ");
  scanf("%d", &value);
  bool found = false;

  for (int i = 0; i <= obj->numberOfRowsUsed; i++)
  {
    for (int j = 0; j < obj->numberOfColumnsUsed[i]; j++)
    {
      if (obj->matrix[i][j] == value)
      {
        printf("Conjunto %d;\n", i);
        found = true;
      }
    }
  }
  if (!found)
  {
    printf("\nValor nao encontrado");
  }
  Sleep(3000);
}