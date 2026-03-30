#include "exercise.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
  const int num_list = 50000;
  for (int i = 0; i < num_list; i++) {
    int *lst = allocate_scalar_list(50000, 2);
    if (lst == NULL) {
      printf("Failed to allocate list\n");
      return 1;
    } else {
      printf("Allocated list %d\n", i);
    }
    free(lst);
  }
  return 0;
}
