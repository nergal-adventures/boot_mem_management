#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

int *allocate_scalar_array(int size, int multiplier) {
  int *array_int = malloc(size * sizeof(int));
  if (array_int == NULL) {
    printf("Allocation falied\n");
    return NULL;
  }

  for(int index = 0; index < size; index ++) {
      array_int[index] = index * multiplier;  
    }

  return array_int;
}
