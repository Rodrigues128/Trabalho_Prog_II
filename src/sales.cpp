#include "../include/sales.h"
#include <stdio.h>


void register_sale() {
    printf("Entrou em 1");
}

void list_sales_by_date() {
    printf("Entrou em 2");

}

void change_product_stock_and_price() {
    printf("Entrou em 3");

}

void remove_product_from_stock() {
    printf("Entrou em 4");
    
};

int menu(int option) {
    
    printf("[1] Cadastrar venda \n");
    printf("[2] Listar vendas por data \n");
    printf("[3] Alterar estoque e preço de produto \n");
    printf("[4] Remover produto do estoque\n");
    printf("[5] Sair\n");
    printf("Sua resposta: ");
    scanf("%d", &option);
    

    switch (option) {
    case 1:
        register_sale();
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
        printf("Saiu");
        return option;
        break;    

    default:
        printf("Opção inválida!");
        break;
    }
}