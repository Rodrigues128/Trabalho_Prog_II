#include <stdio.h>

// Constants
#define TAM_NAME_ARQ 50
#define TAM_MAX_NAME 50
#define TAM_MAX_CPF 11

// Structs/New variable types
// Date type
struct date {
  int year;
  int month;
  int day;
};

// Time type
struct time {
  int h; // hours
  int m; // minute
  int s; // seconds
};

// Type Itens sold
struct product {
  int code;
  char name[TAM_MAX_NAME];
  float price;
  int qty;
};

// Sale type
struct sale {
  date sale_date;
  time sale_time;
  char CPF[TAM_MAX_CPF];
  product itens_sold[];
};

// Prototypes

// Features
void register_sale();

void list_sales_by_date();

void change_product_stock_and_price();

void remove_product_from_stock();

// Auxiliary functions

// Functions for opening the file
void open_file(char name_arq[], int *qty_products,
               product **products);

void opening_option(char name_arq[], int *qty_products,
                    product **products);

// Functions for sorting
void marge(int p, int q, int r, product *products);

void marg_sort(int p, int r, product *products);

int menu(int option);