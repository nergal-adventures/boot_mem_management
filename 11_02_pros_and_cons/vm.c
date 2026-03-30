#include "vm.h"
#include <stdlib.h>

vm_t *vm_new() {
  vm_t *new_vm = malloc(sizeof(vm_t *));
  if (new_vm == NULL) { return NULL; }
  
  new_vm->frames = stack_new(8);
  if (new_vm->frames == NULL) {
    free(new_vm);
    return NULL;
  }

  new_vm->objects = stack_new(8);
  if (new_vm->objects == NULL) {
    free(new_vm);
    return NULL;
  }

  return new_vm;
}

void vm_free(vm_t *vm) {
  if (vm == NULL) { return; }
  stack_free(vm->frames);
  stack_free(vm->objects);
  free(vm);
}

