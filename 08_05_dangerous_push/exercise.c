#include "exercise.h"
#include <stdlib.h>

void scary_double_push(snek_stack_t *s) {
  stack_push(s, (void *) 1337);
  int *int_mem = malloc(sizeof(int));
  *int_mem = 1024;
  stack_push(s, int_mem);
}

