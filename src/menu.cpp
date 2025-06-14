#include "../include/header.h"

// Features


// File opening functions
void opening_option(char name_arq[], int *qty_products, product **products) {
  int arq, choise; // arq = escolha do arquivo existente na pasta de tests
                   // choise = escolha da onde quer carregar o arquivo
  print_header();
  print_home_menu();
  scanf("%d", &choise);

  if (choise == 1) {
    do {
      print_files_menu();
      scanf("%d", &arq);

      switch (arq) {
      case 1:
        strcpy(name_arq, "tests/5_produtos.txt");
        break;

      case 2:
        strcpy(name_arq, "tests/20_produtos.txt");
        break;

      case 3:
        strcpy(name_arq, "tests/100_produtos.txt");
        break;

      default:
        printf(RED "Opcao invalida! Por favor, digite uma opcao valida "
                   "[1, 3]!\n" RESET);
        break;
      }
    } while (arq != 1 && arq != 2 && arq != 3);
    open_file(name_arq, qty_products, products);
  } else if (choise == 2) {
    char name_arq_aux[TAM_NAME_ARQ];
    printf("Informe o nome do arquivo: ");

    while ((getchar()) != '\n')
      ; // limpa o buffer após scanf

    fgets(name_arq_aux, TAM_NAME_ARQ, stdin);
    name_arq_aux[strcspn(name_arq_aux, "\n")] = '\0';

    strcat(name_arq_aux, ".txt");
    strcpy(name_arq, "tests/");
    strcat(name_arq, name_arq_aux);
    open_file(name_arq, qty_products, products);
  } else {
    printf(RED "Opcao invalida! Insira o valor novamente [1, 2]\n" RESET);
    opening_option(name_arq, qty_products, products);
  }
}

void open_file(char name_arq[], int *qty_products, product **products) {
  FILE *p = fopen(name_arq, "r");

  if (p == NULL) {
    printf(RED "Erro na  abertura do arquivo! Tente novamente!\n" RESET);
    opening_option(name_arq, qty_products, products);
  } else {
    fscanf(p, "%d", qty_products);
    *products = (product *)calloc(*qty_products, sizeof(product));

    if (products == NULL) {
      printf(RED "Erro ao alocar memoria!\n" RESET);
      fclose(p);
      return;
    }

    // Salvando os dados do arquivo no vertor de produtos
    for (int i = 0; i < *qty_products; i++) {
      fscanf(p, "%d", &(*products)[i].code);
      fgetc(p); // limpa o '\n' depois do número

      fgets((*products)[i].name, TAM_NAME_PRODUCT, p);
      (*products)[i].name[strcspn((*products)[i].name, "\n")] =
          '\0'; // remove '\n'

      fscanf(p, "%f", &(*products)[i].price);
      fscanf(p, "%d", &(*products)[i].qty);
      fgetc(p); // consome o '\n' após estoque ou linha em branco
    }
  }
  fclose(p);
}

// Functions for sorting
void marge(int p, int q, int r, product *products) {
  int i, j, k;
  product aux[r - p];

  i = p;
  j = q;
  k = 0;

  while (i < q && j < r) {
    if (strcmp(products[i].name, products[j].name) < 0) {
      aux[k] = products[i];
      i++;
    } else {
      aux[k] = products[j];
      j++;
    }
    k++;
  }
  while (i < q) {
    aux[k] = products[i];
    i++;
    k++;
  }
  while (j < r) {
    aux[k] = products[j];
    j++;
    k++;
  }

  for (i = p; i < r; i++)
    products[i] = aux[i - p];
}

void marg_sort(int p, int r, product *products) {
  int q;
  if (p < r - 1) {
    q = (p + r) / 2;
    marg_sort(p, q, products);
    marg_sort(q, r, products);
    marge(p, q, r, products);
  }
}

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
    fprintf(fp, "%s\n", v->content.sale_date); // data
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
}



int menu(sales_cell **sales, product *products, int qty_products) {
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
    remove_product_from_stock();
    break;

  case 5:
    save_sales_to_file(*sales); // Aqui salva corretamente
    printf("Saiu!\n");
    break;

  default:
    printf(RED "╔════════════════════════════════════════════╗\n");
    printf("║                Opção inválida!             ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    break;
  };

  return option;
};
