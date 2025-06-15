#include "../include/header.h"

/*
Nova implementação:
*- Após mostrar todas as vendas na determinada data, pergunte "deseja consultar
a compra de alguém?" Se sim, "Qual CPF deseja consultar? " {CPF} Após informar o
CPF, ele busca e mostra todos os produtos daquele CPF...mostrando a quantidade e
valor de cada produto. Essa exibição será em forma de tabela. Exemplo: Lista de
produtos do usuário
--------------------------------------
|ID| Nome| quant.| valor  |
| x | xxxxx |  5        |  25,00|
---------------------------------------
Valor total: R$ 25,00
 */
void list_sales_by_date(sales_cell **sales) {
  char date[TAM_DATE];
  printf(GREEN "\nInforme a data aaaa/mm/dd: " RESET);
  scanf(" %[^\n]", date);

  bool find = false;

  for (sales_cell *p = *sales; p != NULL; p = p->prox) {
    if (strcmp(p->content.sale_date, date) == 0) {
      find = true;

      float total_value = 0;
      for (celula *item = p->content.itens_sold.prox; item != NULL;
           item = item->prox) {
        total_value += item->itens.price * item->itens.qty;
      };
      printf(GREEN
             "╔══════════════════════════════════════════════════════════╗\n");
      printf("║" RESET "  Hora: %-50s" GREEN "║\n", p->content.sale_time);
      printf("║" RESET "  CPF: %-51s" GREEN "║\n", p->content.CPF);
      printf("║" RESET "  Total da venda: R$ %-37.2f" GREEN "║\n", total_value);
      printf("╚══════════════════════════════════════════════════════════╝"
             "\n" RESET);
    };
  };

  if (!find) {
    printf(RED
           "╔══════════════════════════════════════════════════════════╗\n");
    printf("║            Nenhuma venda no dia: %s.             ║\n", date);
    printf(
        "╚══════════════════════════════════════════════════════════╝\n" RESET);
    return;
  };

  int show_products = 0;
  printf(GREEN
         "╔══════════════════════════════════════════════════════════╗\n");
  printf("║ Deseja consultar a compra de alguém?                     ║\n");
  printf("║  [1] - Sim                                               ║\n");
  printf("║  [2] - Não                                               ║\n");
  printf(
      "╚══════════════════════════════════════════════════════════╝\n" RESET);
  printf(YELLOW "Escolha: " RESET);
  scanf("%d", &show_products);

  char CPF[TAM_MAX_CPF];
  if (show_products == 1) {
    get_CPF(CPF);
    format_CPF(CPF);

    printf(BOLD "\n╔═══════════════════════════════════════════════════════════"
                "══════════════════════════╗\n");
    printf("║   ID   ║           NOME DO PRODUTO           ║   QTD   ║   VALOR "
           "UNI.  ║    VALOR   ║\n");
    printf("║════════║═════════════════════════════════════║═════════║═════════"
           "══════║════════════║\n" RESET);
    float total_value = 0;
    for (sales_cell *p = *sales; p != NULL; p = p->prox) {
      if (strcmp(CPF, p->content.CPF) == 0) {
        for (celula *item = p->content.itens_sold.prox; item != NULL;
             item = item->prox) {
          printf("║  %-5d ║  %s ║   %-5d ║  R$ %8.2f  ║ R$ %7.2f ║\n",
                 item->itens.code, format_product_name(item->itens.name),
                 item->itens.qty, item->itens.price,
                 item->itens.qty * item->itens.price);
          total_value += item->itens.qty * item->itens.price;
        }
      };
    };
    printf(
        BOLD
        "╚═════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);
    printf(GREEN "Total da compra: %.2f\n" RESET, total_value);
  };
};