#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SETS_NUMBER 8
#define MAX_SET_LENGTH 10
#define OPTIONS_LENGTH 9

struct setsAttributes {
  int values[MAX_SETS_NUMBER][MAX_SET_LENGTH];
  int counter;
  int fillingStatus[MAX_SETS_NUMBER];
};

const char MENU_OPTIONS[OPTIONS_LENGTH][50] = {
    "Criar um novo conjunto vazio",
    "Inserir dados em um conjunto",
    "Remover um conjunto",
    "Fazer a uniao entre dois conjuntos",
    "Fazer a interseccao entre dois conjuntos",
    "Mostrar um conjunto",
    "Mostrar todos os conjuntos",
    "Fazer busca por um valor",
    "Sair do programa"};

void clearScreen() { system("cls"); }

void enterToContinue() {
  printf("\n\n>> Pressione enter para continuar...");
  getch();
}

void message(char message[]) {
  printf("\n%s", message);
  enterToContinue();
}

void invalidOption() { message("Opcao invalida!"); }

boolean existSet(struct setsAttributes *sets) { return sets->counter >= 0; }

boolean canAddNewSet(int *numberOfSets) {
  if (*numberOfSets < MAX_SETS_NUMBER - 1) return true;
  message("Numero maximo de conjuntos atingido!");
  return false;
}

boolean canUnionSets(struct setsAttributes *sets) { return sets->counter >= 1; }
void incrementSetsCounter(struct setsAttributes *sets) { sets->counter++; }
void decrementSetsCounter(struct setsAttributes *sets) { sets->counter--; }
void updateFilingStatus(struct setsAttributes *sets, int index, int newStatus) {
  sets->fillingStatus[index] = newStatus;
}

void unionOrIntersection(bool isUnion, struct setsAttributes *sets) {
  if (!canUnionSets(sets)) return message("Numero de conjuntos insuficiente!");

  int *setsFillingStatus = sets->fillingStatus;
  int setsCounter = sets->counter;

  const int currentSetsQuantity = 2;
  int currentSetsIndex[currentSetsQuantity];

  for (int index = 0; index < currentSetsQuantity; index++) {
    do {
      printf("\n>> Selecione o %d conjunto [0-%d]: ", index + 1, sets->counter);
      scanf("%d", &currentSetsIndex[index]);
    } while (currentSetsIndex[index] > setsCounter ||
             currentSetsIndex[index] < 0);
    printf("\n");
  }

  int setALength = setsFillingStatus[currentSetsIndex[0]],
      setBLength = setsFillingStatus[currentSetsIndex[1]];
  int newSetMaxLength = setALength + setBLength;

  int *setA = sets->values[currentSetsIndex[0]],
      *setB = sets->values[currentSetsIndex[1]];
  int newSet[newSetMaxLength];

  int duplicatedValues = 0;
  for (int setIndex = 0; setIndex < newSetMaxLength; setIndex++) {
    if (setIndex < setALength) {
      newSet[setIndex] = setA[setIndex];
    } else {
      bool hasDuplication = false;
      for (int column = 0; column < setIndex - duplicatedValues; column++) {
        if (newSet[column] != setB[setIndex - setALength]) continue;
        int finalPosition = newSetMaxLength - duplicatedValues++;
        newSet[finalPosition] = newSet[column];
        hasDuplication = true;
        break;
      }
      if (!hasDuplication) {
        int indexB = setIndex - setALength;
        int adjustedIndex = setIndex - duplicatedValues;
        newSet[adjustedIndex] = setB[indexB];
      }
    }
  }

  incrementSetsCounter(sets);
  int newSetIndex = sets->counter;

  if (isUnion) {
    int newSetRealLength = newSetMaxLength - duplicatedValues;
    if (newSetRealLength > MAX_SET_LENGTH) {
      message("A uniao dos conjuntos ultrapassa o limite permitido!");
      decrementSetsCounter(sets);
      return;
    }

    updateFilingStatus(sets, newSetIndex, newSetRealLength);
    for (int column = 0; column < newSetRealLength; column++) {
      sets->values[newSetIndex][column] = newSet[column];
    }
  } else {
    updateFilingStatus(sets, newSetIndex, duplicatedValues);
    int reverseIndex = newSetMaxLength;
    for (int column = 0; column < duplicatedValues; column++) {
      sets->values[newSetIndex][column] = newSet[reverseIndex--];
    }
  }
}

void createNewSet(struct setsAttributes *sets) {
  if (!canAddNewSet(&sets->counter)) return;
  incrementSetsCounter(sets);
  message("Novo conjunto adicionado com sucesso");
}

void insertValues(struct setsAttributes *sets) {
  if (!existSet(sets)) return message("Nenhum conjunto encontrado!");

  int setsCounter = sets->counter;
  int setIndex = 0;

  clearScreen();
  do {
    printf(">> Digite o numero do conjunto que deseja inserir dados: ");
    scanf("%d", &setIndex);

    if (setIndex < 0 || setIndex > setsCounter) {
      printf("Valor invalido!\n\n");
    }
  } while (setIndex < 0 || setIndex > setsCounter);

  int usedColumns = sets->fillingStatus[setIndex];
  while (true) {
    if (usedColumns >= MAX_SETS_NUMBER) {
      message("Numero maximo de valores atingido!");
      break;
    }

    boolean duplicatedValue = false;
    int value = 0;

    printf("\nInsira o %d valor [0 = parar]: ", usedColumns + 1);
    scanf("%d", &value);

    if (value == 0) break;

    for (int column = 0; column < usedColumns; column++) {
      if (value == sets->values[setIndex][column]) {
        message("Valor duplicado");
        break;
      }
    }

    if (duplicatedValue) continue;
    sets->values[setIndex][usedColumns++] = value;
  }

  sets->fillingStatus[setIndex] += usedColumns;
}

void removeSet(struct setsAttributes *sets) {
  if (!existSet(sets)) return message("Nenhum conjunto encontrado!");

  clearScreen();
  int setsCounter = sets->counter;
  int toRemoveSetIndex = 0;

  do {
    printf("Digite o indice do conjunto que deseja remover: ");
    scanf("%d", &toRemoveSetIndex);
    if (toRemoveSetIndex > setsCounter || toRemoveSetIndex < 0) {
      printf("Valor invalido!\n\n");
    }
  } while (toRemoveSetIndex > setsCounter || toRemoveSetIndex < 0);

  for (int setIndex = toRemoveSetIndex; setIndex <= setsCounter; setIndex++) {
    for (int column = 0; column < MAX_SET_LENGTH; column++) {
      sets->values[setIndex][column] =
          (setIndex == setsCounter) ? 0 : sets->values[setIndex + 1][column];
    }
    sets->fillingStatus[setIndex] =
        (setIndex == setsCounter) ? 0 : sets->fillingStatus[setIndex + 1];
  }
  decrementSetsCounter(sets);
}

void joinSets(struct setsAttributes *sets) {
  if (canAddNewSet(&sets->counter)) unionOrIntersection(true, sets);
}

void intersectSets(struct setsAttributes *sets) {
  if (canAddNewSet(&sets->counter)) unionOrIntersection(false, sets);
}

void showSet(struct setsAttributes *sets) {
  if (!existSet(sets)) return message("Nenhum conjunto encontrado!");

  int setsCounter = sets->counter;
  int setIndex = 0;
  do {
    printf("Selecione o conjunto que deseja ver [0-%d]:", setsCounter);
    scanf("%d", &setIndex);
    if (setIndex > setsCounter || setIndex < 0) {
      printf("Valor invalido, tente novamente...\n\n");
    }
  } while (setIndex > setsCounter || setIndex < 0);

  int usedColumns = sets->fillingStatus[setIndex];

  printf("Conjunto %d: ", setIndex);

  if (usedColumns == 0) {
    printf("vazio");
  } else {
    printf("{");
    for (int column = 0; column < usedColumns; column++) {
      if (sets->values[setIndex][column] != 0) {
        if (column < usedColumns - 1)
          printf("%d, ", sets->values[setIndex][column]);
        else
          printf("%d", sets->values[setIndex][column]);
      }
    }
    printf("}");
    printf(" [%d]", usedColumns);
  }
  enterToContinue();
}

void showAllSets(struct setsAttributes *sets) {
  if (!existSet(sets)) return message("Nenhum conjunto encontrado!");

  int setsCounter = sets->counter;
  int *fillingStatus = sets->fillingStatus;

  for (int setIndex = 0; setIndex < setsCounter + 1; setIndex++) {
    printf("\nConjunto %d: ", setIndex);

    if (fillingStatus[setIndex] == 0) {
      printf("vazio");
    } else {
      printf("{");
      for (int column = 0; column < fillingStatus[setIndex]; column++) {
        (column < fillingStatus[setIndex] - 1)  //
            ? printf("%d, ", sets->values[setIndex][column])
            : printf("%d", sets->values[setIndex][column]);
      }
      printf("}");
      printf(" [%d] ", fillingStatus[setIndex]);
    }
  }
  enterToContinue();
}

void searchValue(struct setsAttributes *sets) {
  if (!existSet(sets)) return message("Nenhum conjunto encontrado!");

  int value = 0;
  printf(">> Digite o valor que deseja buscar: ");
  scanf("%d", &value);

  bool found = false;
  for (int index = 0; index <= sets->counter; index++) {
    for (int column = 0; column < sets->fillingStatus[index]; column++) {
      if (sets->values[index][column] == value) {
        printf("Conjunto %d;\n", index);
        found = true;
      }
    }
  }

  if (!found) message("Valor nao encontrado!");
}

void showMenu() {
  clearScreen();
  printf("Gerenciamento de conjuntos\n\n");

  for (int i = 0; i < OPTIONS_LENGTH; i++)
    printf("[%d] - %s\n", i + 1, MENU_OPTIONS[i]);
  printf("\n>> Escolha uma opcao: ");
}

int getOption() {
  int option;
  scanf("%d", &option);
  return option;
}

bool isValidOption(int option) { return option > 0 && option < 10; }

const void (*FUNCTIONS[])() = {invalidOption, createNewSet, insertValues,
                               removeSet,     joinSets,     intersectSets,
                               showSet,       showAllSets,  searchValue};

int main() {
  struct setsAttributes sets;
  memset(sets.values, 0, sizeof sets.values);
  memset(sets.fillingStatus, 0, sizeof sets.fillingStatus);

  sets.counter = -1;

  while (true) {
    showMenu();
    int option = getOption();

    if (!isValidOption(option)) {
      invalidOption();
      continue;
    }
    if (option == 9) break;
    (*FUNCTIONS[option])(&sets);
  };

  clearScreen();
  printf(">> Fim da Execucao do programa <<\n");
  printf("Equipe: Gustavo HTM e Jezreel KM");
  return 0;
}
