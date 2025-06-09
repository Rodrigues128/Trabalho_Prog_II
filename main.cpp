#include "include/sales.h"
#include <stdio.h>

int main() {
  int option = 0;

  // Variáveis para abertura do arquivo
  char name_arq[TAM_NAME_ARQ];
  int qty_products = 0;

  // Variavéis que vão ser usadas em todo código
  product *products = NULL;

  // Opção para abertura do arquivo
  opening_option(name_arq, &qty_products, &products);

  // Ordenando o vetor de produtos
  marg_sort(0, qty_products, products);

  while (menu(option, products, qty_products) != 5);

  return 0;
}