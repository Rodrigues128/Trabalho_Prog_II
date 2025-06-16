#include "../include/header.h"

int menu(sales_cell **sales, product **products, int *qty_products, char *name_arq)
{
       int option = 0;
       print_menu();
       scanf("%d", &option);

       switch (option)
       {
       case 1:
       {
              if (qty_equal_zero(*qty_products) == false)
              {
                     printf(GREEN "\n═════════════════════ CADASTRAR VENDA ══════════════════════\n" RESET);
                     register_sale(sales, *products, *qty_products);
                     break;
              }
              break;
       }

       case 2:
       {
              printf(GREEN "\n══════════════════ LISTAR VENDAS POR DATA ══════════════════\n" RESET);
              list_sales_by_date(sales);
              break;
       }
       case 3:
       {
              if (qty_equal_zero(*qty_products) == false)
              {
                     printf(GREEN "\n════════════ ALTERAR ESTOQUE E PREÇO DO PRODUTO ════════════\n" RESET);
                     change_product_stock_and_price(sales, *products, *qty_products);
                     break;
              }
              break;
       }

       case 4:
       {

              if (qty_equal_zero(*qty_products) == false)
              {
                     remove_product_by_code(products, qty_products, *sales);
                     break;
              }
              break;
       }

       case 5:
       {
              save_data(*sales, name_arq, *products, *qty_products);
              break;
       }

       default:
       {
              printf(RED "╔══════════════════════════════════════════════════════════╗\n");
              printf("║                     Opção inválida!                      ║\n");
              printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
              break;
       }
       };

       return option;
};

bool qty_equal_zero(int qty)
{
       if (qty == 0)
       {
              printf(RED
                     "╔══════════════════════════════════════════════════════════╗\n");
              printf("║              Nenhum produto cadastrado!                  ║\n");
              printf("╚══════════════════════════════════════════════════════════╝"
                     "\n" RESET);
              return true;
       }
       return false;
}