#include "../include/header.h"

void get_CPF(char *CPF) {
  do {
    printf(GREEN "\nInforme o CPF" RESET RED " (Somente números): " RESET);
    scanf(" %[^\n]", CPF);
    if (strlen(CPF) != 11) {
      printf(RED
             "╔══════════════════════════════════════════════════════════╗\n");
      printf("║              CPF inválido! Insira novamente.             ║\n");
      printf("╚══════════════════════════════════════════════════════════╝"
             "\n" RESET);
    };
  } while (strlen(CPF) != 11);
}

void format_CPF(char cpf[]) {
  char cpf_formated[TAM_MAX_CPF];
  snprintf(cpf_formated, TAM_MAX_CPF, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3,
           cpf + 6, cpf + 9);
  strcpy(cpf, cpf_formated);
};

int find_product(product *products, int code, int qty_products) {
  for (int i = 0; i < qty_products; i++)
    if (products[i].code == code)
      return i;
  return -1;
};

void list_stock_products(product *products, int qty_products) {
  printf(BOLD
         "\n╔══════════════════════════════════════════════════════════╗\n");
  printf("║   ID   ║           NOME DO PRODUTO           ║   VALOR   ║\n");
  printf(
      "║════════║═════════════════════════════════════║═══════════║\n" RESET);
  for (int i = 0; i < qty_products; i++) {
    printf("║  %-5d ║  %s ║ R$ %6.2f ║\n", products[i].code,
           format_product_name(products[i].name), products[i].price);
  };
  printf(
      BOLD
      "╚══════════════════════════════════════════════════════════╝\n" RESET);
};