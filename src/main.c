#include "functions.h"

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
