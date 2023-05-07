#define MAX_SETS_NUMBER 8
#define MAX_SET_LENGTH 10

struct setsAttributes {
  int values[MAX_SETS_NUMBER][MAX_SET_LENGTH];
  int counter;
  int fillingStatus[MAX_SETS_NUMBER];
};

void enterToContinue() {
  printf("\n\n>> Pressione enter para continuar...");
  getch();
}

void message(char message[]) {
  printf("\n%s", message);
  enterToContinue();
}

void clearScreen() { system("cls"); }
