#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// ANSI codes for colors
#define RESET "\033[0m"
#define LIGHT_BLUE "\033[1;36m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define BOLD "\033[1m"

// Constants
#define TAM_NAME_ARQ 50
#define TAM_NAME_PRODUCT 50
#define TAM_MAX_CPF 15
#define TAM_DATE 11 // yyyy/mm/dd + '\0'
#define TAM_HOURS 9 // 12:51:11 + '\0

struct product {
  int code;
  char name[TAM_NAME_PRODUCT];
  float price;
  int qty;
};

// Cells
struct celula {
  product itens;
  struct celula *prox;
};

struct sale {
  char sale_date[TAM_DATE];
  char sale_time[TAM_HOURS];
  char CPF[TAM_MAX_CPF];
  celula itens_sold;
};

struct sales_cell {
  sale content;
  struct sales_cell *prox;
};

// Features
void register_sale(sales_cell **sales, product *products, int qty_products);

void list_sales_by_date(sales_cell **sales);

void change_product_stock_and_price(sales_cell **sale, product *products,
                                    int qty_products);

void remove_product_by_code(product **products, int *qty_products, int code);

void save_sales_to_file(sales_cell *sales);
void save_products_to_file(const char *filename, product *products, int qty_products);

// Auxiliary functions:
// Functions for opening the file
void opening_option(char name_arq[], int *qty_products, product **products);
void open_file(char name_arq[], int *qty_products, product **products);

// Functions for sorting
void marge(int p, int q, int r, product *products);
void marg_sort(int p, int r, product *products);

// Functions for sales registration
void list_stock_products(product *products, int qty_products);
bool get_data(sale *sales);
void get_date_hour(char date[], char hour[]);
void format_CPF(char cpf[]);
void buy_product(product *products, int qty_products, celula **lst_products);
int find_product(product *products, int code, int qty_products);
void insert_itens_sold(product *products, int index, celula **lst, int qty);
void purchase_value(celula **lst);

int menu(sales_cell **sales, product *products, int qty_products,
         char *name_arq);

void print_header();
void print_home_menu();
void print_files_menu();
void print_menu();
char *format_product_name(char *product_name);
int count_chars(char *str);

bool was_product_sold(int code, sales_cell *sales);