#include "../include/sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Features
bool register_sale(product *products, int qty_products) {
  // Lista todos os procutos que estão dispiníveis no estoque
  list_stock_products(products, qty_products);
  sale sales;

  int code, qty, index, op;
  system("date /t");
  system("date /t");

  printf("Infome os seguintes dados:");
  scanf("\tData: %d %d %d", &sales.sale_date.year, &sales.sale_date.month,
         &sales.sale_date.day);
  scanf("\tHora: %d %d %d", &sales.sale_time.h, &sales.sale_time.m,
          &sales.sale_time.s);
   scanf("\tCPF: %[^\n]", sales.CPF);

  printf("Informe o codigo e a quatidade do produto:\n");
  printf("Resposta: ");
  scanf("%d %d", &code, &qty);

  index = find_product(products, code, qty_products);

  printf("\n%d\n", products[index].qty);
  if (qty > products[index].qty) {
    printf("Esse produto temos somente %d unidades em estoque.\n",
           products[index].qty);
    printf("Deseja comprar todas as unidades existentes:");
    printf("\n\t[1] - Sim\n\t[2] - Nao\n");
    printf("Sua resposta: ");
    scanf("%d", &op);

    if (op == 1)
      products[index].qty = 0;
    else {
      printf("Deseja comprar outro produto:\n");
      printf("\t[1] - Sim\n");
      printf("\t[2] - Nao\n");
      printf("\tSua resposta: ");
      scanf("%d", &op);

      if (op == 2)
        return false;
    }
  } else {
    products[index].qty = products[index].qty - qty;
  }
  return true;
}

void list_sales_by_date() { printf("Entrou em 2"); }

void change_product_stock_and_price() { printf("Entrou em 3"); }

void remove_product_from_stock() { printf("Entrou em 4"); };

// Auxiliary functions

// File opening functions
void open_file(char name_arq[], int *qty_products, product **products) {
  FILE *p = fopen(name_arq, "r");

  if (p == NULL) {
    printf("Erro na  abertura do arquivo! Tente novamente!\n");
    opening_option(name_arq, qty_products, products);
  } else {
    fscanf(p, "%d", qty_products);
    *products = (product *)calloc(*qty_products, sizeof(product));

    if (products == NULL) {
      printf("Erro ao alocar memória!\n");
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

void opening_option(char name_arq[], int *qty_products, product **products) {
  int arq, choise; // arq = escolha do arquivo existente na pasta de tests
                   // choise = escolha da onde quer carregar o arquivo
  printf("O que deseja fazer:\n");
  printf("\t[1] - Carregar um arquivo ja existente\n");
  printf("\t[2] - Carregar um novo arquivo\n");
  printf("\tSua resposta: ");
  scanf("%d", &choise);

  if (choise == 1) {
    do {
      printf("Qual arquivo deseja carregar:\n");
      printf("\t[1] - 5 Produtos\n");
      printf("\t[2] - 20 Produtos\n");
      printf("\t[3] - 100 Produtos\n");
      printf("\tSua resposta: ");
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

void format_CPF(char cpf[]) {
  // se na posição 3 e 7 tiver . e na posição 11 tiver - o cpf está formatado
  // caso contrário tem que formatar
  int i = 0;
  char cpf_formated[TAM_MAX_CPF];
  for(i; i < 3; i++){
    strcpy(cpf_formated, cpf[i]);
  }
}

int menu(int option, product *products, int qty_products) {
  printf("[1] Cadastrar venda \n");
  printf("[2] Listar vendas por data \n");
  printf("[3] Alterar estoque e preço de produto \n");
  printf("[4] Remover produto do estoque\n");
  printf("[5] Sair\n");
  printf("Sua resposta: ");
  scanf("%d", &option);

  switch (option) {
  case 1:
    while (register_sale(products, qty_products))
      ;
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