#include "../include/sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Features
void register_sale(sales_cell **sales, product *products, int qty_products) {
  // Lista todos os produtos que estão disponíveis no estoque
  list_stock_products(products, qty_products);

  // Cria dinamicamento o vetor de vendas e insere os dados de cada venda
  sales_cell *new_sale;
  new_sale = (sales_cell *)calloc(1, sizeof(sales_cell));

  // Pega os dados do usuário
  get_data(&new_sale->content);

  // Inicializando a cabeça de produtos vendidos
  celula *lst_products = new_sale->content.itens_sold.prox = NULL;

  // Preenche a lista de itens vendidos
  buy_product(products, qty_products, &lst_products);

  // Calcula o valor da compra
  purchase_value(&lst_products);

  // Encadeia a vendas, inserindo sempre a nova venda na primeira posição da
  // lista
  new_sale->prox = *sales;
  *sales = new_sale;
}

void list_sales_by_date(sales_cell **sales) {
  char date[TAM_DATE];
  printf("Informe a data aaaa/mm/dd: ");
  scanf(" %[^\n]", date);

  bool find = false;

  for (sales_cell *p = *sales; p != NULL; p = p->prox) {
    if (strcmp(p->content.sale_date, date) == 0) {
      find = true;
      printf("\nHora: %s\n", p->content.sale_time);
      printf("CPF: %s\n", p->content.CPF);

      float total_value = 0;
      for (celula *item = p->content.itens_sold.prox; item != NULL;
           item = item->prox) {
        printf("Produto %d - Qtd: %d - Preço: %.2f\n", item->itens.code,
               item->itens.qty, item->itens.price);
        total_value += item->itens.price * item->itens.qty;
      }
      printf("Total da venda: %.2f\n", total_value);
    }
  }
  if (!find)
    printf(VERMELHO "Nenhuma venda encontrada para a data %s.\n" RESET, date);
};

void change_product_stock_and_price(sales_cell **sale, product *products,
                                    int qty_products) {
  int code, index, new_qty;
  float new_price;
  scanf("%d", &code);

  index = find_product(products, code, qty_products);
  if (index == -1) {
    printf(VERMELHO "Produto nao encontrado!\n" RESET);
    return;
  }
  printf("Informe o novo preço: ");
  scanf("%f", &new_price);

  printf("Informe a nova quantidade: ");
  scanf("%d", &new_qty);
}

void remove_product_from_stock() { printf("Entrou em 4"); };

// Auxiliary functions
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
        printf(VERMELHO "Opcao invalida! Por favor, digite uma opcao valida "
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
    printf(VERMELHO "Opcao invalida! Insira o valor novamente [1, 2]\n" RESET);
    opening_option(name_arq, qty_products, products);
  }
}

void open_file(char name_arq[], int *qty_products, product **products) {
  FILE *p = fopen(name_arq, "r");

  if (p == NULL) {
    printf(VERMELHO "Erro na  abertura do arquivo! Tente novamente!\n" RESET);
    opening_option(name_arq, qty_products, products);
  } else {
    fscanf(p, "%d", qty_products);
    *products = (product *)calloc(*qty_products, sizeof(product));

    if (products == NULL) {
      printf(VERMELHO "Erro ao alocar memoria!\n" RESET);
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

// Functions for sales registration
void list_stock_products(product *products, int qty_products) {
  printf(NEGRITO "\n╔═════════════ LISTA DE PRODUTOS ════════════╗\n");
  printf("║   ID   ║          NOME         ║   VALOR   ║\n");
  printf("║════════════════════════════════════════════║\n" RESET);
  for (int i = 0; i < qty_products; i++) {
    char *format_name = format_product_name(products[i].name);
    printf("║  %-5d ║  %s ║ R$ %6.2f ║\n", products[i].code, format_name,
           products[i].price);
    free(format_name);
  };
  printf(NEGRITO "╚════════════════════════════════════════════╝\n" RESET);
};

void insert_itens_sold(product *products, int index, celula **lst_products,
                       int qty) {
  celula *new_product;
  new_product = (celula *)calloc(1, sizeof(celula));
  new_product->itens.code = products[index].code;
  new_product->itens.price = products[index].price;
  new_product->itens.qty = qty;
  new_product->prox = *lst_products;
  *lst_products = new_product;
};

bool get_data(sale *sales) {
  // Pegando a data e a hora atual da venda
  get_date_hour(sales->sale_date, sales->sale_time);

  printf(VERDE "\nInforme o CPF" RESET VERMELHO "(Somente números): " RESET);
  scanf(" %[^\n]", sales->CPF);
  if (strlen(sales->CPF) != 11) {
    get_data(sales);
  };
  format_CPF(sales->CPF);
  return false;
};

void get_date_hour(char date[], char hour[]) {
  time_t t;
  struct tm *tm_info;

  time(&t);                // pega o tempo atual
  tm_info = localtime(&t); // converte para hora local

  strftime(date, TAM_DATE, "%Y/%m/%d", tm_info);
  strftime(hour, TAM_HOURS, "%H:%M:%S", tm_info);
};

void format_CPF(char cpf[]) {
  char cpf_formated[TAM_MAX_CPF];
  snprintf(cpf_formated, TAM_MAX_CPF, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3,
           cpf + 6, cpf + 9);
  strcpy(cpf, cpf_formated);
};

void buy_product(product *products, int qty_products, celula **lst_products) {
  bool stop = false, one_product = false;
  int code, qty, choise, op, index = -1;

  while (!stop) {
    printf(VERDE "\n════════════════ SETOR DE COMPRA ═════════════\n");
    printf("Informe o código do produto: " RESET);
    scanf("%d", &code);

    // Busca o indice que o produto está no vetor de products
    index = find_product(products, code, qty_products);

    if (index == -1) {
      printf(VERMELHO "╔════════════════════════════════════════════╗\n");
      printf("║           Produto não encontrado!          ║\n");
      printf("╚════════════════════════════════════════════╝\n" RESET);
    } else {
      one_product = true;
      printf(VERDE "Informe a quantidade do produto: " RESET);
      scanf("%d", &qty);

      if (qty > products[index].qty) {
        printf(VERMELHO "╔════════════════════════════════════════════╗\n");
        printf("║    Quatidade desejada excede o estoque!    ║\n");
        printf("╚════════════════════════════════════════════╝\n" RESET);
        printf(VERDE "╔════════════════════════════════════════════╗\n");
        printf("║ Deseja comprar apenas oque tem no estoque? ║\n");
        printf("║  [1] - Sim                                 ║\n");
        printf("║  [2] - Não                                 ║\n");
        printf("╚════════════════════════════════════════════╝\n" RESET);
        printf(AMARELO "Escolha: " RESET);
        scanf("%d", &op);

        if (op == 1) {
          insert_itens_sold(products, index, lst_products, products[index].qty);
          products[index].qty = 0;
          printf(VERDE "╔════════════════════════════════════════════╗\n");
          printf("║        Produto comprado com SUCESSO!       ║\n");
          printf("╚════════════════════════════════════════════╝\n" RESET);
        };
      } else {
        insert_itens_sold(products, index, lst_products, qty);
        products[index].qty -= qty;
      };
    };
    printf(VERDE "╔════════════════════════════════════════════╗\n");
    printf("║ Deseja continuar comprando?                ║\n");
    printf("║  [1] - Sim                                 ║\n");
    printf("║  [2] - Não                                 ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    printf(AMARELO "Escolha: " RESET);
    scanf("%d", &choise);

    if (choise == 2) {
      if (one_product) {
        printf(VERDE "╔════════════════════════════════════════════╗\n");
        printf("║        Compra realizada com SUCESSO!       ║\n");
        printf("╚════════════════════════════════════════════╝\n" RESET);
      };
      printf(VERDE "\n═══════════ SAIU DO SETOR DE COMPRA ══════════\n");
      break;
    };
  };
};

int find_product(product *products, int code, int qty_products) {
  for (int i = 0; i < qty_products; i++)
    if (products[i].code == code)
      return i;
  return -1;
};

void purchase_value(celula **lst) {
  float soma = 0;
  for (celula *p = *lst; p != NULL; p = p->prox)
    soma += p->itens.price * p->itens.qty;
  printf(VERDE "\nSoma: %.2f\n" RESET, soma);
};

// Functions for listing sales by date

// Functions to end the program
// Está incompleta, ainda não consegui fazer tudo
void save_sales_to_file(sales_cell *sales) {
  if (sales == NULL) {
    printf(VERMELHO "Nenhuma venda para salvar.\n" RESET);
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
    printf(VERMELHO "╔════════════════════════════════════════════╗\n");
    printf("║                Opção inválida!             ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    break;
  };

  return option;
};

// Cabecalho
void print_header() {
  system("chcp 65001"); // Define UTF-8 (não é garantia, mas ajuda)
  system("cls");
  printf(AZUL_CLARO);
  printf("╔════════════════════════════════════════════╗\n");
  printf("║       SISTEMA DE VENDAS - PRODUTOS++       ║\n");
  printf("╚════════════════════════════════════════════╝\n");
  printf(RESET);
}

// Menu inicial
void print_home_menu() {
  printf(VERDE "\n╔════════════ OQUE DESEJA FAZER? ════════════╗\n" RESET);
  printf(VERDE "║" RESET "  [1] Carregar um arquivo já existente      " VERDE
               "║\n" RESET);
  printf(VERDE "║" RESET "  [2] Carregar um novo arquivo              " VERDE
               "║\n" RESET);
  printf(VERDE "╚════════════════════════════════════════════╝\n" RESET);
  printf(AMARELO "Escolha: " RESET);
};

// Meus arquivos
void print_files_menu() {
  printf(VERDE "\n╔══════ QUAL ARQUIVO DESEJA CARREGAR? ═══════╗\n");
  printf(VERDE "║" RESET "  [1] 5 Produtos                            " VERDE
               "║\n" RESET);
  printf(VERDE "║" RESET "  [2] 20 Produtos                           " VERDE
               "║\n" RESET);
  printf(VERDE "║" RESET "  [3] 100 Produtos                          " VERDE
               "║\n" RESET);
  printf(VERDE "╚════════════════════════════════════════════╝\n" RESET);
  printf(AMARELO "Escolha: " RESET);
}

// Menu principal
void print_menu() {
  printf(AZUL_CLARO "\n╔══════════════ MENU PRINCIPAL ══════════════╗\n" RESET);
  printf(AZUL_CLARO "║" RESET
                    "  [1] Cadastrar venda                       " AZUL_CLARO
                    "║\n" RESET);
  printf(AZUL_CLARO "║" RESET
                    "  [2] Listar vendas por data                " AZUL_CLARO
                    "║\n" RESET);
  printf(AZUL_CLARO "║" RESET
                    "  [3] Alterar estoque e preço de produto    " AZUL_CLARO
                    "║\n" RESET);
  printf(AZUL_CLARO "║" RESET
                    "  [4] Remover produto do estoque            " AZUL_CLARO
                    "║\n" RESET);
  printf(AZUL_CLARO "║" RESET
                    "  [5] Sair                                  " AZUL_CLARO
                    "║\n" RESET);
  printf(AZUL_CLARO "╚════════════════════════════════════════════╝\n" RESET);
  printf(AMARELO "Escolha: " RESET);
}
int count_chars(char *str) {
  int count = 0;
  while (*str) {
    char c = (char)*str;
    if ((c & 0x80) == 0x00)
      str += 1; // ASCII
    else if ((c & 0xE0) == 0xC0)
      str += 2; // 2 bytes
    else if ((c & 0xF0) == 0xE0)
      str += 3; // 3 bytes
    else if ((c & 0xF8) == 0xF0)
      str += 4; // 4 bytes
    else
      str += 1; // fallback
    count++;
  }
  return count;
}

char *format_product_name(char *product_name) {
  int spaces = 20 - count_chars(product_name);

  if (spaces < 0)
    spaces = 0; // evita valores negativos

  int len = strlen(product_name);

  char *product_name_aux = (char *)calloc(len + spaces + 1, sizeof(char));
  if (!product_name_aux)
    return NULL; // falha de alocação

  memcpy(product_name_aux, product_name, len);

  memset(product_name_aux + len, ' ', spaces);

  return product_name_aux;
}
