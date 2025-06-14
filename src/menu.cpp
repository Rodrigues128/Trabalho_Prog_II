#include "../include/header.h"
// Cabecalho
void print_header() {
  system("chcp 65001"); // Define UTF-8 (não é garantia, mas ajuda)
  system("cls");
  printf(LIGHT_BLUE);
  printf("╔════════════════════════════════════════════╗\n");
  printf("║       SISTEMA DE VENDAS - PRODUTOS++       ║\n");
  printf("╚════════════════════════════════════════════╝\n");
  printf(RESET);
}

// Menu inicial
void print_home_menu() {
  printf(GREEN "\n╔════════════ OQUE DESEJA FAZER? ════════════╗\n" RESET);
  printf(GREEN "║" RESET "  [1] Carregar um arquivo já existente      " GREEN
               "║\n" RESET);
  printf(GREEN "║" RESET "  [2] Carregar um novo arquivo              " GREEN
               "║\n" RESET);
  printf(GREEN "╚════════════════════════════════════════════╝\n" RESET);
  printf(YELLOW "Escolha: " RESET);
};

// Meus arquivos
void print_files_menu() {
  printf(GREEN "\n╔══════ QUAL ARQUIVO DESEJA CARREGAR? ═══════╗\n");
  printf(GREEN "║" RESET "  [1] 5 Produtos                            " GREEN
               "║\n" RESET);
  printf(GREEN "║" RESET "  [2] 20 Produtos                           " GREEN
               "║\n" RESET);
  printf(GREEN "║" RESET "  [3] 100 Produtos                          " GREEN
               "║\n" RESET);
  printf(GREEN "╚════════════════════════════════════════════╝\n" RESET);
  printf(YELLOW "Escolha: " RESET);
}

// Menu principal
void print_menu() {
  printf(LIGHT_BLUE "\n╔══════════════ MENU PRINCIPAL ══════════════╗\n" RESET);
  printf(LIGHT_BLUE "║" RESET
                    "  [1] Cadastrar venda                       " LIGHT_BLUE
                    "║\n" RESET);
  printf(LIGHT_BLUE "║" RESET
                    "  [2] Listar vendas por data                " LIGHT_BLUE
                    "║\n" RESET);
  printf(LIGHT_BLUE "║" RESET
                    "  [3] Alterar estoque e preço de produto    " LIGHT_BLUE
                    "║\n" RESET);
  printf(LIGHT_BLUE "║" RESET
                    "  [4] Remover produto do estoque            " LIGHT_BLUE
                    "║\n" RESET);
  printf(LIGHT_BLUE "║" RESET
                    "  [5] Sair                                  " LIGHT_BLUE
                    "║\n" RESET);
  printf(LIGHT_BLUE "╚════════════════════════════════════════════╝\n" RESET);
  printf(YELLOW "Escolha: " RESET);
};

int menu(sales_cell **sales, product *products, int qty_products, char *name_arq) {
  int option = 0;
  print_menu();
  scanf("%d", &option);

  switch (option) {
  case 1:
    register_sale(sales, products, qty_products);
    break;

  case 2:
    list_sales_by_date(sales);
    break;

  case 3:
    change_product_stock_and_price(sales, products, qty_products);
    break;

  case 4:
    int code;
    printf("Informe o código do produto a ser removido: ");
    scanf("%d", &code);

    if (was_product_sold(code, *sales))
      printf(RED "Produto já foi vendido e não pode ser removido.\n" RESET);
    else
      remove_product_by_code(&products, &qty_products, code);
    break;

  case 5:
    save_sales_to_file(*sales);
    save_products_to_file(name_arq, products, qty_products);
    printf(GREEN "\nDados salvos com sucesso. Encerrando o programa...\n" RESET);
    break;

  default:
    printf(RED "╔════════════════════════════════════════════╗\n");
    printf("║                Opção inválida!             ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    break;
  };

  return option;
};
