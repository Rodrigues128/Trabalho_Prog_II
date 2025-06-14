#include "../include/header.h"

// Salva todas as vendas em um arquivo nomeado pela data atual
#include <locale.h>

void save_sales_to_file(sales_cell *sales) {
  if (sales == NULL) {
    printf(RED "Nenhuma venda para salvar.\n" RESET);
    return;
  }

  setlocale(LC_NUMERIC, "C"); // garante ponto decimal para salvar internamente

  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);
  char file_name[64];
  strftime(file_name, sizeof(file_name), "vendas%d%m%Y.txt", tm_info);

  FILE *fp = fopen(file_name, "w");
  if (fp == NULL) {
    printf("Erro ao criar o arquivo de vendas!\n");
    return;
  }

  sales_cell *v = sales;
  while (v != NULL) {
    fprintf(fp, "%s\n", v->content.sale_date);
    fprintf(fp, "%s\n", v->content.sale_time);
    fprintf(fp, "%s\n", v->content.CPF);

    float total = 0;
    for (celula *p = v->content.itens_sold.prox; p != NULL; p = p->prox) {
      // Alinhamento: código, nome (20), qtd (4), preço (6)
      fprintf(fp, "%-5d %-20s %4d %7.2f\n",
              p->itens.code,
              p->itens.name,
              p->itens.qty,
              p->itens.price);

      total += p->itens.qty * p->itens.price;
    }

    // Valor total da venda
    fprintf(fp, "%.2f", total);

    if (v->prox != NULL)
      fprintf(fp, "\n\n");

    v = v->prox;
  }

  fclose(fp);
  printf(GREEN "Arquivo de vendas '%s' salvo com sucesso.\n" RESET, file_name);
}

// Salva o vetor de produtos no arquivo de entrada original
void save_products_to_file(const char *filename, product *products,
                           int qty_products) {
    FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf(RED "Erro ao salvar o arquivo de produtos.\n" RESET);
    return;
  }

  fprintf(fp, "%d\n", qty_products);

  for (int i = 0; i < qty_products; i++) {
    fprintf(fp, "%d\n", products[i].code);
    fprintf(fp, "%s\n", products[i].name);
    fprintf(fp, "%.2f\n", products[i].price);

    if (i < qty_products - 1) {
      fprintf(fp, "%d\n\n", products[i].qty); // Linha em branco entre produtos
    } else {
      fprintf(fp, "%d", products[i].qty);     // Último sem \n final
    }
  }

  fclose(fp);
  printf(GREEN "Arquivo '%s' atualizado com sucesso!\n" RESET, filename);
}