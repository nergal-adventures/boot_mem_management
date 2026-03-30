#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void *stack_pop(snek_stack_t *stack) {
  if (stack->count == 0) {
    return NULL;
  }
  
  stack->count--;
  return stack->data[stack->count];
}

void stack_push(snek_stack_t *stack, void *obj) {
  if (stack->count == stack->capacity) {
    stack->capacity *= 2;
    void **tmp = realloc(stack->data, stack->capacity * sizeof(void *));

    if (tmp == NULL) {
      stack->capacity /= 2;
      return;
    }
    stack->data = tmp;
  }

  stack->data[stack->count] = obj;
  stack->count++;
  return;
}

// don't touch below this line

snek_stack_t *stack_new(size_t capacity) {
  snek_stack_t *stack = malloc(sizeof(snek_stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(stack->capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}

