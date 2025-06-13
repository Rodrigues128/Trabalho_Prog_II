#include "include/sales.h"
#include <stdio.h>

int main() {
  int option = 0;
  char name_arq[TAM_NAME_ARQ];
  int qty_products = 0;
  product *products = NULL;
  sales_cell *sales = NULL;

  opening_option(name_arq, &qty_products, &products);
  marg_sort(0, qty_products, products);

  do {
    option = menu(&sales, products, qty_products);
  } while (option != 5);

  // save_sales_to_file(sales); // ← salva as vendas ao final, conforme
  // enunciado
  return 0;
}