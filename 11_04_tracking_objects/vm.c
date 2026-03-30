#include "vm.h"
#include "snekobject.h"
#include <stdlib.h>

void vm_track_object(vm_t *vm, snek_object_t *obj) {
  if (vm == NULL || obj == NULL) { return; }
  stack_push(vm->objects, (void *)obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
  if (vm == NULL || frame == NULL) { return; }
  stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm) {
  frame_t *new_frame = malloc(sizeof(frame_t));
  if (new_frame == NULL) { return NULL; }

  new_frame->references = stack_new(8);
  if (new_frame->references == NULL) {
    free(new_frame);
    return NULL;
  }

  vm_frame_push(vm, new_frame);
  return new_frame;
}

void frame_free(frame_t *frame) {
  if (frame == NULL) { return; }
  stack_free(frame->references);
  free(frame);
}

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

