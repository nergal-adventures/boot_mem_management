#include "exercise.h"
#include <stdlib.h>

snek_stack_t *stack_new(size_t capacity) {
  snek_stack_t *new_stack = malloc(sizeof(snek_stack_t));

  if (new_stack == NULL) { return NULL;}

  new_stack->count = 0;
  new_stack->capacity = capacity;
  new_stack->data = malloc(sizeof(void *) * capacity);
  
  if (new_stack->data == NULL) {
    free(new_stack);
    return NULL;
  }

  return new_stack;
}
