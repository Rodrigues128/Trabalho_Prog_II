#include "../include/header.h"

void list_sales_by_date(sales_cell **sales) {
  char date[TAM_DATE];
  printf(GREEN "\nInforme a data aaaa/mm/dd: " RESET);
  scanf(" %[^\n]", date);

  bool find = false;

  for (sales_cell *p = *sales; p != NULL; p = p->prox) {
    if (strcmp(p->content.sale_date, date) == 0) {
      find = true;

      float total_value = 0;
      for (celula *item = p->content.itens_sold.prox; item != NULL; item = item->prox) {
        total_value += item->itens.price * item->itens.qty;
      }

      printf(GREEN "╔════════════════════════════════════════════╗\n");
      printf("║" RESET "  Hora: %-36s " GREEN "║\n", p->content.sale_time);
      printf("║" RESET "  CPF: %-37s" GREEN "║\n", p->content.CPF);
      printf("║" RESET "  Total da venda: R$ %-22.2f" GREEN "║\n", total_value);
      printf("╚════════════════════════════════════════════╝\n" RESET);
    }
  }

  if (!find) {
    printf(RED "╔════════════════════════════════════════════╗\n");
    printf("║     Nenhuma venda no dia: %s.      ║\n", date);
    printf("╚════════════════════════════════════════════╝\n" RESET);
  }
}
