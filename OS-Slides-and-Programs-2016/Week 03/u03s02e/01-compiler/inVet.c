#include "my.h"

void
inputVet (int *vet, int *dim){
  int i;

  fprintf (stdout, "Read dimension (<100): ");
  scanf ("%d", dim);

  fprintf (stdout, "Read array:\n");
  for (i=0; i<(*dim); i++) {
    fprintf (stdout, "vet (%d) = ", i);
    scanf ("%d", &vet[i]);
  }

  return;
}
