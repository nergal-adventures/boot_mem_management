#include <stdio.h>
#include <stdlib.h>
void swap_strings(char **a, char **b) {
 char *aux = *a;
 *a = *b;
 *b = aux;
}
