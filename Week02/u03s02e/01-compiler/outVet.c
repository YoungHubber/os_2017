#include "my.h"

void
outputVet (int *vet, int dim){
  int i;

  fprintf (stdout, "Display array:\n");
  for (i=0; i<dim; i++) {
    fprintf (stdout, "vet (%d) = %d\n", i, vet[i]);
  }

  return;
}