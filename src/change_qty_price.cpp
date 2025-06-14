#include "../include/header.h"

void change_product_stock_and_price(sales_cell **sale, product *products,
                                    int qty_products) {
  int code, index, new_qty;
  float new_price;
  list_stock_products(products, qty_products);
  printf("Informe o código: ");
  scanf("%d", &code);

  index = find_product(products, code, qty_products);
  if (index == -1) {
    printf(RED "╔════════════════════════════════════════════╗\n");
    printf("║           Produto não encontrado!          ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    return;
  }
  printf(GREEN "Informe o novo preço: " RESET);
  scanf("%f", &new_price);

  printf(GREEN "Informe a nova quantidade: " RESET);
  scanf("%d", &new_qty);

  products[index].price = new_price;
  products[index].qty = new_qty;
};