#include <stdio.h>

// Constants
#define TAM_NAME_ARQ 50
#define TAM_MAX_NAME 50
#define TAM_MAX_CPF 15 
#define TAM_DATE 11 //yyyy/mm/dd + '\0'
#define TAM_HOURS 9 //12:51:11 + '\0


// Structs/New variable types
// Type Itens sold
struct product {
  int code;
  char name[TAM_MAX_NAME];
  float price;
  int qty;
};

struct itens {
  product *itens_sold;
  struct itens *prox;
};

// Sale type
struct sale {
  char sale_date[TAM_DATE];
  char sale_time[TAM_HOURS];
  char CPF[TAM_MAX_CPF];
  itens *v;
};

// Prototypes

// Features
bool register_sale(product *products, int qty_products);

void list_sales_by_date();

void change_product_stock_and_price();

void remove_product_from_stock();

// Auxiliary functions

// Functions for opening the file
void open_file(char name_arq[], int *qty_products, product **products);
void opening_option(char name_arq[], int *qty_products, product **products);

// Functions for sorting
void marge(int p, int q, int r, product *products);
void marg_sort(int p, int r, product *products);

// Functions for sales registration
void list_stock_products(product *products, int qty_products);
int find_product(product *products, int code, int qty_products);
void get_date_hour(char date[], char hour[]);
void format_CPF(char cpf[]);

int menu(int option, product *products, int qty_products);