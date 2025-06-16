#include "../include/header.h"

void change_product_stock_and_price(sales_cell **sale, product *products, int qty_products) {
  int code, index, new_qty;
  float new_price;
  list_stock_products(products, qty_products);
  printf(GREEN "Informe o código: " RESET);
  scanf("%d", &code);

  index = find_product(products, code, qty_products);
  if (index == -1) {
    printf(RED"╔══════════════════════════════════════════════════════════╗\n");
    printf("║                 Produto não encontrado!                  ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    return;
  }
  printf(GREEN "Informe o novo preço: R$ " RESET);
  scanf("%f", &new_price);

  printf(GREEN "Qual a quantidade deseja adicionar ao estoque? " RESET);
  scanf("%d", &new_qty);

  products[index].price = new_price;
  products[index].qty += new_qty;

  printf(GREEN
         "╔══════════════════════════════════════════════════════════╗\n");
  printf("║              Produto atualizado com sucesso!             ║\n");
  printf(
      "╚══════════════════════════════════════════════════════════╝\n" RESET);
};