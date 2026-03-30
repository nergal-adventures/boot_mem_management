#include "vm.h"
#include "snekobject.h"
#include "stack.h"
#include <stdlib.h>


void mark(vm_t *vm) {
  if (vm == NULL) { return; }

  for (int index = 0; index < vm->frames->count; index++) {
    frame_t *frame = vm->frames->data[index];

    for (int frame_index = 0; frame_index < frame->references->count; frame_index++) {
      snek_object_t *obj =  (snek_object_t *)frame->references->data[frame_index];
      obj->is_marked = true;
    }
  }
}

void frame_reference_object(frame_t *frame, snek_object_t *obj) {
  if (frame == NULL || obj == NULL) { return; }

  stack_push(frame->references, (void *)obj);
}


void vm_free(vm_t *vm) {
  if (vm == NULL) { return; }
  for (int index = 0; index < vm->frames->count; index++) {
    frame_t *frame = (frame_t *)vm->frames->data[index];
    frame_free(frame);
  }
  stack_free(vm->frames);

  for (int index = 0; index < vm->objects->count; index++) {
    snek_object_t *object = (snek_object_t *)vm->objects->data[index];
    snek_object_free(object);
  }
  stack_free(vm->objects);
  free(vm);
}

// don't touch below this line

vm_t *vm_new() {
  vm_t *vm = malloc(sizeof(vm_t));
  if (vm == NULL) {
    return NULL;
  }

  vm->frames = stack_new(8);
  vm->objects = stack_new(8);
  return vm;
}

void vm_track_object(vm_t *vm, snek_object_t *obj) {
  stack_push(vm->objects, obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) { stack_push(vm->frames, frame); }

frame_t *vm_new_frame(vm_t *vm) {
  frame_t *frame = malloc(sizeof(frame_t));
  frame->references = stack_new(8);

  vm_frame_push(vm, frame);
  return frame;
}

void frame_free(frame_t *frame) {
  stack_free(frame->references);
  free(frame);
}

