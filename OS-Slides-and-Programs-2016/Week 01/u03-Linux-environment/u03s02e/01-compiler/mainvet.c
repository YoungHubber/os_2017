#include "my.h"

int
main (void){
  int dim;
  int vet[VET_DIM_MAX];

  inputVet (vet, &dim);

  outputVet (vet, dim);

  return 0;
}
