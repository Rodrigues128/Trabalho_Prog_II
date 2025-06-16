#include "../include/header.h"

// Functions for sorting
void marge(int p, int q, int r, product *products)
{
  int i, j, k;
  product aux[r - p];

  i = p;
  j = q;
  k = 0;

  while (i < q && j < r)
  {
    if (strcmp(products[i].name, products[j].name) < 0)
    {
      aux[k] = products[i];
      i++;
    }
    else
    {
      aux[k] = products[j];
      j++;
    }
    k++;
  };
  while (i < q)
  {
    aux[k] = products[i];
    i++;
    k++;
  };
  while (j < r)
  {
    aux[k] = products[j];
    j++;
    k++;
  };

  for (i = p; i < r; i++)
    products[i] = aux[i - p];
};

void marg_sort(int p, int r, product *products)
{
  int q;
  if (p < r - 1)
  {
    q = (p + r) / 2;
    marg_sort(p, q, products);
    marg_sort(q, r, products);
    marge(p, q, r, products);
  };
};
