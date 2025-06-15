#include "../include/header.h"

void remove_product_by_code(product **products, int *qty_products, int code) {
  int index = find_product(*products, code, *qty_products);

  if (index == -1) {
    printf(RED "╔══════════════════════════════════════════════════════════╗\n");
    printf("║                 Produto não encontrado!                  ║\n", code);
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    return;
  }

  // Desloca os produtos para "tapar o buraco"
  for (int i = index; i < *qty_products - 1; i++) {
    (*products)[i] = (*products)[i + 1];
  }

  int new_size = *qty_products - 1;
  product *temp = (product *)realloc(*products, new_size * sizeof(product));

  // realloc pode retornar NULL se new_size for 0 (e isso é válido)
  if (temp != NULL || new_size == 0) {
    *products = temp;
    *qty_products = new_size;
    printf(RED "╔══════════════════════════════════════════════════════════╗\n");
    printf("║              Produto removido com sucesso!               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
  } else {
    printf(RED
           "╔══════════════════════════════════════════════════════════╗\n");
    printf("║          Erro ao realocar memória após remoção!          ║\n");
    printf(
        "╚══════════════════════════════════════════════════════════╝\n" RESET);
  }
}

bool was_product_sold(int code, sales_cell *sales) {
  for (sales_cell *venda = sales; venda != NULL; venda = venda->prox) {
    for (celula *item = venda->content.itens_sold.prox; item != NULL;
         item = item->prox) {
      if (item->itens.code == code) {
        return true; // Encontrou o produto em alguma venda
      }
    }
  }
  return false; // Produto nunca foi vendido
}
