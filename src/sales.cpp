#include "../include/sales.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void register_sale()
{
    printf("Entrou em 1");
}

void list_sales_by_date()
{
    printf("Entrou em 2");
}

void change_product_stock_and_price()
{
    printf("Entrou em 3");
}

void remove_product_from_stock()
{
    printf("Entrou em 4");
};

// File opening functions
void open_file(char name_arq[], FILE **p, int *qty_products, product **products)
{
    *p = fopen(name_arq, "r");
    int n;

    if (*p == NULL)
    {
        printf("Erro na  abertura do arquivo! Tente novamente!\n");
        opening_option(name_arq, p, qty_products, products);
    }
    else
    {
        fscanf(*p, "%d", qty_products);
        *products = (product *)calloc(*qty_products, sizeof(product));

        if (products == NULL)
        {
            printf("Erro ao alocar memória!\n");
            fclose(*p);
            return;
        }

        // Salvando os dados do arquivo no vertoe de produtos
        for (int i = 0; i < *qty_products; i++)
        {
            fscanf(*p, "%d", &(*products)[i].code);
            fgetc(*p); // limpa o '\n' depois do número

            fgets((*products)[i].name, TAM_MAX_NAME, *p);
            (*products)[i].name[strcspn((*products)[i].name, "\n")] = '\0'; // remove '\n'

            fscanf(*p, "%f", &(*products)[i].price);
            fscanf(*p, "%d", &(*products)[i].qty);
            fgetc(*p); // consome o '\n' após estoque ou linha em branco
        }
    }
}

void opening_option(char name_arq[], FILE **p, int *qty_products, product **products)
{
    int arq, choise; // arq = escolha do arquivo existente na pasta de tests
                     // choise = escolha da onde quer carregar o arquivo

    printf("O que deseja fazer:\n");
    printf("[1] - Carregar um arquivo ja existente\n");
    printf("[2] - Carregar um novo arquivo\n");
    printf("Sua resposta: ");
    scanf("%d", &choise);

    if (choise == 1)
    {
        do
        {
            printf("Qual arquivo deseja carregar:\n");
            printf("[1] - 5 Produtos\n");
            printf("[2] - 20 Produtos\n");
            printf("[3] - 100 Produtos\n");
            printf("Sua resposta: ");
            scanf("%d", &arq);

            switch (arq)
            {
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
        open_file(name_arq, p, qty_products, products);
    }
    else if (choise == 2)
    {
        printf("Informe o nome do arquivo: ");

        while ((getchar()) != '\n')
            ; // limpa o buffer após scanf

        fgets(name_arq, TAM_NAME_ARQ, stdin);
        name_arq[strcspn(name_arq, "\n")] = '\0';
        open_file(name_arq, p, qty_products, products);
    }
    else
    {
        printf("Opcao invalida! Insira o valor novamente [1, 2]\n");
        opening_option(name_arq, p, qty_products, products);
    }
}

int menu(int option)
{
    char name_arq[TAM_NAME_ARQ];
    FILE *p = NULL;
    product *products = NULL;
    int qty_products = 0;

    // Opção para abertura do arquivo
    opening_option(name_arq, &p, &qty_products, &products);

    printf("[1] Cadastrar venda \n");
    printf("[2] Listar vendas por data \n");
    printf("[3] Alterar estoque e preço de produto \n");
    printf("[4] Remover produto do estoque\n");
    printf("[5] Sair\n");
    printf("Sua resposta: ");
    scanf("%d", &option);

    switch (option)
    {
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
        printf("Saiu!\n");
        break;

    default:
        printf("Opção inválida!\n");
        break;
    }

    if (p != NULL)
        fclose(p); // Boa prática: fecha o arquivo após uso
    return option;
}