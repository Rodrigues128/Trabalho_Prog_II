#include "include/header.h"

int main() {
  int option = 0;
  char name_arq[TAM_NAME_ARQ];
  int qty_products = 0;

  // Variáveis para manipulação do arquivo
  product *products = NULL;      // Lista de produtos no estoque
  sales_cell *head_sales = NULL; // Lista de vendas

  // Abertura do arquivo
  opening_option(name_arq, &qty_products, &products);

  // Ordena o vetor de produtos disponíveis no estoque
  marg_sort(0, qty_products, products);

  do {
    option = menu(&head_sales, products, qty_products, name_arq);
  } while (option != 5);
  return 0;
}