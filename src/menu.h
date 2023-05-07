#define OPTIONS_LENGTH 9

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
