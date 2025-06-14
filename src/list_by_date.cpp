#include "../include/header.h"

void list_sales_by_date(sales_cell **sales) {
  char date[TAM_DATE];
  printf(GREEN "\nInforme a data aaaa/mm/dd: " RESET);
  scanf(" %[^\n]", date);

  bool find = false;

  for (sales_cell *p = *sales; p != NULL; p = p->prox) {
    if (strcmp(p->content.sale_date, date) == 0) {
      find = true;

      printf(GREEN "╔════════════════════════════════════════════╗\n");
      printf("║" RESET "  Hora: %s                             " GREEN "║\n",
             p->content.sale_time);
      printf("║" RESET "  CPF: %s                        " GREEN "║\n" RESET,
             p->content.CPF);

      float total_value = 0;
      for (celula *item = p->content.itens_sold.prox; item != NULL;
           item = item->prox) {
        printf("Produto %d - Qtd: %d - Preço: %.2f\n", item->itens.code,
               item->itens.qty, item->itens.price);
        total_value += item->itens.price * item->itens.qty;
      }
      printf(GREEN "║" RESET
                   "  Total da venda: %.2f                      " GREEN "║\n",
             total_value);
      printf("╚════════════════════════════════════════════╝\n" RESET);
    }
  }
  if (!find) {
    printf(RED "╔════════════════════════════════════════════╗\n");
    printf("║     Nenhuma venda no dia: %s.      ║\n", date);
    printf("╚════════════════════════════════════════════╝\n" RESET);
  }
};