#include "../include/sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Features
void register_sale(product *products, int qty_products) {
  sales_cell sales;
  int code, qty, op, index, choise, i = 0;
  bool stop = false;

  // Inicializando a cabeça de produtos vendidos e de vendas
  celula *lst = sales.content.itens_sold.prox = NULL;
  sales.prox = NULL;

  // Lista todos os produtos que estão disponíveis no estoque
  list_stock_products(products, qty_products);

  // Pega os dados do usuário
  get_data(products, qty_products, &sales.content);

  printf("\n=-=-= COMPRA DE PRODUTOS =-=-=\n");
  while (!stop) {
    i++;
    printf("Dados da compra do produto [%d]\n", i);
    printf("Informe o codigo do produto: ");
    scanf("%d", &code);
    printf("Informe a quantidade do produto: ");
    scanf("%d", &qty);

    // Busca o indice que o produto está no vetor de products
    index = find_product(products, code, qty_products);

    if (index == -1)
      printf("Produto nao encontrado.\n");

    if (qty > products[index].qty) {
      printf("A quatidade desejada excede o quatidade em estoque!");
      printf("\nDeseja comprar a quatidade que tem no estoque? 1 - sim ou 2 - "
             "nao.");
      printf("\nEscolha: ");
      scanf("%d", &op);

      if (op == 1)
        insert_itens_sold(products, index, &lst, products[index].qty);
    } else
      insert_itens_sold(products, index, &lst, qty);

    printf("\nDeseja continuar comprando? 1 - sim ou 2 - nao.\nEscolha: ");
    scanf("%d", &choise);
    if (choise == 2) {
      printf("\nCompra realizada com SUCESSO.\n");
      break;
    }
  }
  purchase_value(&lst);
}

void list_sales_by_date() {
  printf("Informe a data aaaa/mm/dd: ");
  scanf(" %[^\n]");
}

void change_product_stock_and_price() { printf("Entrou em 3"); }

void remove_product_from_stock() { printf("Entrou em 4"); };

// Auxiliary functions
// File opening functions
void opening_option(char name_arq[], int *qty_products, product **products) {
  int arq, choise; // arq = escolha do arquivo existente na pasta de tests
                   // choise = escolha da onde quer carregar o arquivo
  printf("\n=-=-= Bem-vindo ao Sistema de Vendas do Supermercado Produtos++ "
         "=-=-=");
  printf("\n\nO que deseja fazer:\n\t[1] - Carregar um arquivo ja "
         "existente\n\t[2] - Carregar um novo arquivo\n\tEscolha: ");
  scanf("%d", &choise);

  if (choise == 1) {
    do {
      printf("\nQual arquivo deseja carregar:\n\t[1] - 5 Produtos\n\t[2] - 20 "
             "Produtos\n\t[3] - 100 Produtos\n\tEscolha: ");
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
        printf("Opcao invalida! Por favor, digite uma opcao valida [1, 3]!\n");
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

    strcpy(name_arq, "tests/");
    strcat(name_arq, name_arq_aux);
    open_file(name_arq, qty_products, products);
  } else {
    printf("Opcao invalida! Insira o valor novamente [1, 2]\n");
    opening_option(name_arq, qty_products, products);
  }
}

void open_file(char name_arq[], int *qty_products, product **products) {
  FILE *p = fopen(name_arq, "r");

  if (p == NULL) {
    printf("Erro na  abertura do arquivo! Tente novamente!\n");
    opening_option(name_arq, qty_products, products);
  } else {
    fscanf(p, "%d", qty_products);
    *products = (product *)calloc(*qty_products, sizeof(product));

    if (products == NULL) {
      printf("Erro ao alocar memoria!\n");
      fclose(p);
      return;
    }

    // Salvando os dados do arquivo no vertor de produtos
    for (int i = 0; i < *qty_products; i++) {
      fscanf(p, "%d", &(*products)[i].code);
      fgetc(p); // limpa o '\n' depois do número

      fgets((*products)[i].name, TAM_MAX_NAME, p);
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
bool get_data(product *products, int qty_products, sale *sales) {
  // Pegando a data e a hora atual da venda
  get_date_hour(sales->sale_date, sales->sale_time);

  printf("\nInforme o CPF (Somente numeros): ");
  scanf(" %[^\n]", sales->CPF);
  if (strlen(sales->CPF) != 11) {
    get_data(products, qty_products, sales);
  }
  format_CPF(sales->CPF);
  return false;
}

void list_stock_products(product *products, int qty_products) {
  printf("\n=-=-= Lista de Produtos =-=-=\n");
  for (int i = 0; i < qty_products; i++) {
    printf("%d, %s, %.2f\n", products[i].code, products[i].name,
           products[i].price);
  }
}

int find_product(product *products, int code, int qty_products) {
  for (int i = 0; i < qty_products; i++)
    if (products[i].code == code)
      return i;
  return -1;
}

void get_date_hour(char date[], char hour[]) {
  time_t t;
  struct tm *tm_info;

  time(&t);                // pega o tempo atual
  tm_info = localtime(&t); // converte para hora local

  strftime(date, TAM_DATE, "%Y/%m/%d", tm_info);
  strftime(hour, TAM_HOURS, "%H:%M:%S", tm_info);
}

void format_CPF(char cpf[]) {
  char cpf_formated[TAM_MAX_CPF];
  snprintf(cpf_formated, TAM_MAX_CPF, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3,
           cpf + 6, cpf + 9);
  strcpy(cpf, cpf_formated);
}

void insert_itens_sold(product *products, int index, celula **lst, int qty) {
  celula *novo;

  novo = (celula *)calloc(1, sizeof(celula));
  novo->itens.code = products[index].code;
  novo->itens.price = products[index].price;
  novo->itens.qty = qty;
  novo->prox = *lst;
  *lst = novo;
}

void insert_sold() {}

void purchase_value(celula **lst) {
  float soma = 0;
  for (celula *p = *lst; p != NULL; p = p->prox)
    soma += p->itens.price * p->itens.qty;
  printf("\nSoma: %.2f\n", soma);
}

// Functions for listing sales by date

int menu(int option, product *products, int qty_products) {
  printf("\n=-=-= MENU =-=-=\n");
  printf("[1] Cadastrar venda\n[2] Listar vendas por data\n[3] Alterar estoque "
         "e preco de produto\n");
  printf("[4] Remover produto do estoque\n[5] Sair\nEscolha: ");
  scanf("%d", &option);

  switch (option) {
  case 1:
    register_sale(products, qty_products);
    break;

  case 2:
    list_sales_by_date();
    break;

  case 3:
    change_product_stock_and_price();
    break;

  case 4:
    remove_product_from_stock();
    break;

  case 5:
    printf("Saiu!\n");
    break;

  default:
    printf("Opção inválida!\n");
    break;
  }

  return option;
}