#include "../include/header.h"

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
  new_sale->content.itens_sold.prox = lst_products;

  // Verifica se um produto foi comprado
  if (lst_products == NULL) {
    free(new_sale);
    return;
  }

  // Calcula o valor da compra
  purchase_value(&lst_products);

  // Encadeia a vendas, inserindo sempre a nova venda na primeira posição da
  new_sale->prox = *sales;
  *sales = new_sale;
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

bool get_data(sale *sales) {
  // Pegando a data e a hora atual da venda
  get_date_hour(sales->sale_date, sales->sale_time);

  get_CPF(sales->CPF);

  format_CPF(sales->CPF);
  return false;
};

void get_CPF(char *CPF) {
  do {
    printf(GREEN "\nInforme o CPF" RESET RED " (Somente números): " RESET);
    scanf(" %[^\n]", CPF);
    if (strlen(CPF) != 11) {
      printf(RED "╔══════════════════════════════════════════════════════════╗\n");
      printf("║              CPF inválido! Insira novamente.             ║\n");
      printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    };
  } while (strlen(CPF) != 11);
}

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
    printf(GREEN "\n═══════════════════════ SETOR DE COMPRA ════════════════════\n");
    printf("Informe o código do produto: " RESET);
    scanf("%d", &code);

    // Busca o indice que o produto está no vetor de products
    index = find_product(products, code, qty_products);

    if (index == -1) {
      printf(RED "╔══════════════════════════════════════════════════════════╗\n");
      printf("║                  Produto não encontrado!                 ║\n");
      printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    } else {
      if (products[index].qty == 0) {
        printf(RED "╔══════════════════════════════════════════════════════════╗\n");
        printf("║            Produto não disponível do estoque!            ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
      } else {
        printf(GREEN "Informe a quantidade do produto: " RESET);
        scanf("%d", &qty);

        if (qty > products[index].qty) {
          printf(RED "╔══════════════════════════════════════════════════════════╗\n");
          printf("║           Quatidade desejada excede o estoque!           ║\n");
          printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
      
          printf(GREEN "╔══════════════════════════════════════════════════════════╗\n");
          printf("║ Deseja comprar apenas oque tem no estoque?               ║\n");
          printf("║  [1] - Sim                                               ║\n");
          printf("║  [2] - Não                                               ║\n");
          printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
          printf(YELLOW "Escolha: " RESET);
          scanf("%d", &op);

          if (op == 1) {
            one_product = true;
            insert_itens_sold(products, index, lst_products,
                              products[index].qty);
            products[index].qty = 0;
            printf(GREEN "╔══════════════════════════════════════════════════════════╗\n");
            printf("║              Produto comprado com SUCESSO!               ║\n");
            printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
          };
        } else {
          one_product = true;
          insert_itens_sold(products, index, lst_products, qty);
          products[index].qty -= qty;

          printf(GREEN "╔══════════════════════════════════════════════════════════╗\n");
          printf("║              Produto comprado com SUCESSO!               ║\n");
          printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
        };
      };
    };

    printf(GREEN "╔══════════════════════════════════════════════════════════╗\n");
    printf("║ Deseja continuar comprando?                              ║\n");
    printf("║  [1] - Sim                                               ║\n");
    printf("║  [2] - Não                                               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    printf(YELLOW "Escolha: " RESET);
    scanf("%d", &choise);

    if (choise == 2) {
      if (one_product) {
        printf(GREEN "╔══════════════════════════════════════════════════════════╗\n");
        printf("║              Compra realizada com SUCESSO!               ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
      }; 
      printf(GREEN "\n═════════════════ SAIU DO SETOR DE COMPRA ════════════════\n");
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

void insert_itens_sold(product *products, int index, celula **lst_products,
                       int qty) {
  celula *new_product;
  new_product = (celula *)calloc(1, sizeof(celula));
  new_product->itens.code = products[index].code;
  new_product->itens.price = products[index].price;
  new_product->itens.qty = qty;
  strcpy(new_product->itens.name, products[index].name);
  new_product->prox = *lst_products;
  *lst_products = new_product;
};

void purchase_value(celula **lst) {
  float soma = 0;
  for (celula *p = *lst; p != NULL; p = p->prox)
    soma += p->itens.price * p->itens.qty;
  printf(GREEN "\nSoma: %.2f\n" RESET, soma);
};

char *format_product_name(char *product_name) {
  int spaces = 34 - count_chars(product_name);

  if (spaces < 0)
    spaces = 0; // evita valores negativos

  int len = strlen(product_name);

  char *product_name_aux = (char *)calloc(len + spaces + 1, sizeof(char));
  if (!product_name_aux)
    return NULL; // falha de alocação

  memcpy(product_name_aux, product_name, len);

  memset(product_name_aux + len, ' ', spaces);

  return product_name_aux;
};

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
};
