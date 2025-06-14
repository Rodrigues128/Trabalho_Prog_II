#include "../include/header.h"

void remove_product_by_code(product **products, int *qty_products, int code) {
  int index = -1;

  // 1. Busca o índice do produto com o código informado
  index = find_product(*products, code, *qty_products);

  if (index == -1) {
    printf("Produto com código %d não encontrado.\n", code);
    return;
  }

  // 2. Move os elementos à frente para trás, sobrescrevendo o produto removido
  for (int i = index; i < *qty_products - 1; i++) {
    (*products)[i] = (*products)[i + 1];
  }

  // 3. Realoca o vetor para reduzir o tamanho
  product *temp =
      (product *)realloc(*products, (*qty_products - 1) * sizeof(product));
  int new_size = *qty_products - 1;
  if (temp != NULL || new_size == 0) {
    *products = temp;
    (*qty_products)--;
    printf("Produto com código %d removido com sucesso.\n", code);
  } else {
    printf("Erro ao realocar memória após remoção.\n");
  }
}