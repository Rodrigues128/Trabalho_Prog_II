#include "../include/header.h"

// Está incompleta, ainda não consegui fazer tudo
void save_sales_to_file(sales_cell *sales) {
  if (sales == NULL) {
    printf(RED "Nenhuma venda para salvar.\n" RESET);
    return;
  }

  // Obter a data atual para criar o nome do arquivo
  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);
  char file_name[64];
  strftime(file_name, sizeof(file_name), "vendas%d%m%Y.txt", tm_info);

  FILE *fp = fopen(file_name, "w");
  if (fp == NULL) {
    printf("Erro ao criar o arquivo de vendas!\n");
    return;
  }

  for (sales_cell *v = sales; v != NULL; v = v->prox) {
    fprintf(fp, "%s\n", v->content.sale_time); // hora
    fprintf(fp, "%s\n", v->content.CPF);       // CPF

    float total = 0;
    for (celula *p = v->content.itens_sold.prox; p != NULL; p = p->prox) {
      fprintf(fp, "%d %d %.2f\n", p->itens.code, p->itens.qty, p->itens.price);
      total += p->itens.qty * p->itens.price;
    }

    fprintf(fp, "%.2f\n\n", total); // total da venda
  }

  fclose(fp);
  printf("Arquivo de vendas '%s' salvo com sucesso.\n", file_name);
};