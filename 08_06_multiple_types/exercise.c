#include "exercise.h"
#include <stdlib.h>
#include <string.h>

void stack_push_multiple_types(snek_stack_t *s) {
  float *float_ptr = malloc(sizeof(float));
  *float_ptr = 3.14;
  stack_push(s, (void*)float_ptr);

  char str[] = "Sneklang is blazingly slow!";

  size_t str_size = sizeof(str);
  char *str_ptr = malloc(sizeof(char) * str_size);
  strcpy(str_ptr, str);

  stack_push(s, (void *)str_ptr);
}
