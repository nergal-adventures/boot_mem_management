#include <stdlib.h>
#include <stdio.h>

void swap_ints(int *a, int *b) {
 int *aux = malloc(sizeof(int));
 *aux = *a;
 *a = *b;
 *b = *aux;

 free(aux);
}
