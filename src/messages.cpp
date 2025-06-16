#include "../include/header.h"

// Cabecalho
void print_header()
{
    system("chcp 65001"); // Define o padrão UTF-8 (Para aceitar as acentuações no terminal)
    system("cls");
    printf(LIGHT_BLUE);
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               SISTEMA DE VENDAS - PRODUTOS++             ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

// Menu principal
void print_menu()
{
    printf(LIGHT_BLUE "\n╔═════════════════════ MENU PRINCIPAL ═════════════════════╗\n" RESET);
    printf(LIGHT_BLUE "║" RESET "  [1] Cadastrar venda                                     " LIGHT_BLUE "║\n" RESET);
    printf(LIGHT_BLUE "║" RESET "  [2] Listar vendas por data                              " LIGHT_BLUE "║\n" RESET);
    printf(LIGHT_BLUE "║" RESET "  [3] Alterar estoque e preço de produto                  " LIGHT_BLUE "║\n" RESET);
    printf(LIGHT_BLUE "║" RESET "  [4] Remover produto do estoque                          " LIGHT_BLUE "║\n" RESET);
    printf(LIGHT_BLUE "║" RESET "  [5] Sair                                                " LIGHT_BLUE "║\n" RESET);
    printf(LIGHT_BLUE "╚══════════════════════════════════════════════════════════╝\n" RESET);
    printf(YELLOW "Escolha: " RESET);
};

// Menu inicial
void print_home_menu()
{
    printf(GREEN "\n╔═══════════════════ OQUE DESEJA FAZER? ═══════════════════╗\n" RESET);
    printf(GREEN "║" RESET "  [1] Carregar um arquivo já existente                    " GREEN "║\n" RESET);
    printf(GREEN "║" RESET "  [2] Carregar um novo arquivo                            " GREEN "║\n" RESET);
    printf(GREEN "╚══════════════════════════════════════════════════════════╝\n" RESET);
    printf(YELLOW "Escolha: " RESET);
};

// Meus arquivos
void print_files_menu()
{
    printf(GREEN "\n╔═════════════ QUAL ARQUIVO DESEJA CARREGAR? ══════════════╗\n");
    printf(GREEN "║" RESET "  [1] 5 Produtos                                          " GREEN "║\n" RESET);
    printf(GREEN "║" RESET "  [2] 20 Produtos                                         " GREEN "║\n" RESET);
    printf(GREEN "║" RESET "  [3] 100 Produtos                                        " GREEN "║\n" RESET);
    printf(GREEN "╚══════════════════════════════════════════════════════════╝\n" RESET);
    printf(YELLOW "Escolha: " RESET);
}
