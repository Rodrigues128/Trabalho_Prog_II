#include "../include/header.h"

// Salva todas as vendas em um arquivo nomeado pela data atual
void save_sales_to_file(sales_cell *sales) {
  if (sales == NULL) {
    printf(RED "╔══════════════════════════════════════════════════════════╗\n");
    printf("║                Nenhuma venda para salvar.                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    return;
  }

  setlocale(LC_NUMERIC, "C");

  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);
  char file_name[64];

  // Verifica se a pasta sales existe se existir, cria
   if (_access("sales", 0) != 0) {
    _mkdir("sales");
  }
  
  strftime(file_name, sizeof(file_name), "sales/vendas%d%m%Y.txt", tm_info);

  FILE *fp = fopen(file_name, "a"); // modo append
  if (fp == NULL) {
    printf(RED "╔══════════════════════════════════════════════════════════╗\n");
    printf("║            Erro ao abrir o arquivo de vendas!            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    return;
  }

  for (sales_cell *v = sales; v != NULL; v = v->prox) {
    fprintf(fp, "%s\n", v->content.sale_date);
    fprintf(fp, "%s\n", v->content.sale_time);
    fprintf(fp, "%s\n", v->content.CPF);

    float total = 0;
    for (celula *p = v->content.itens_sold.prox; p != NULL; p = p->prox) {
      fprintf(fp, "%-5d %-20s %4d %7.2f\n", p->itens.code, p->itens.name,
              p->itens.qty, p->itens.price);
      total += p->itens.qty * p->itens.price;
    }

    fprintf(fp, "%.2f\n\n", total); // ✅ sempre imprime duas \n após total
  }

  fclose(fp);
  printf(GREEN "Vendas adicionadas a '%s'.\n" RESET, file_name);
}

// Salva o vetor de produtos no arquivo de entrada original

void save_products_to_file(const char *filename, product *products,
                           int qty_products) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf(RED "╔══════════════════════════════════════════════════════════╗\n");
    printf("║          Erro ao salvar o arquivo de produtos!           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
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
      fprintf(fp, "%d", products[i].qty); // Último sem \n final
    }
  }

  fclose(fp);
  printf(GREEN "Arquivo '%s' atualizado com sucesso!\n" RESET, filename);
}
