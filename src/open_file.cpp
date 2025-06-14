#include "../include/header.h"

void opening_option(char name_arq[], int *qty_products, product **products) {
  int arq, choise;

  print_header();
  print_home_menu();
  scanf("%d", &choise);

  if (choise == 1) {
    do {
      print_files_menu();
      scanf("%d", &arq);

      switch (arq) {
      case 1:
        strcpy(name_arq, "products/5_produtos.txt");
        break;
      case 2:
        strcpy(name_arq, "products/20_produtos.txt");
        break;
      case 3:
        strcpy(name_arq, "products/100_produtos.txt");
        break;
      default:
        printf(RED "Opcao invalida! Por favor, digite uma opcao valida [1, "
                   "3]!\n" RESET);
        break;
      }
    } while (arq < 1 || arq > 3);

    open_file(name_arq, qty_products, products);
  } else if (choise == 2) {
    char name_arq_aux[TAM_NAME_ARQ];
    printf("Informe o nome do arquivo: ");

    while ((getchar()) != '\n')
      ; // limpa o buffer

    fgets(name_arq_aux, TAM_NAME_ARQ, stdin);
    name_arq_aux[strcspn(name_arq_aux, "\n")] = '\0';

    snprintf(name_arq, TAM_NAME_ARQ, "products/%s.txt", name_arq_aux);

    open_file(name_arq, qty_products, products);
  } else {
    printf(RED "Opcao invalida! Insira o valor novamente [1, 2]\n" RESET);
    opening_option(name_arq, qty_products, products); // chamada recursiva
  }
}

void open_file(char name_arq[], int *qty_products, product **products) {
  FILE *p = fopen(name_arq, "r");

  if (p == NULL) {
    printf(RED "Erro na abertura do arquivo! Tente novamente!\n" RESET);
    opening_option(name_arq, qty_products, products);
    return;
  }

  // Lê a quantidade de produtos
  fscanf(p, "%d", qty_products);
  fgetc(p); // Consome o '\n'

  // Aloca o vetor
  *products = (product *)calloc(*qty_products, sizeof(product));
  if (*products == NULL) {
    printf(RED "Erro ao alocar memória!\n" RESET);
    fclose(p);
    return;
  }

  // Lê os produtos
  for (int i = 0; i < *qty_products; i++) {
    fscanf(p, "%d", &(*products)[i].code);
    fgetc(p); // Consome '\n'

    fgets((*products)[i].name, TAM_NAME_PRODUCT, p);
    (*products)[i].name[strcspn((*products)[i].name, "\n")] = '\0';

    fscanf(p, "%f", &(*products)[i].price);
    fscanf(p, "%d", &(*products)[i].qty);
    fgetc(p); // Consome '\n'
  }

  fclose(p);
}
