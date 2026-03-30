#include "snekobject.h"
#include <stdlib.h>

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj_ptr = malloc(sizeof(snek_object_t));
  if (obj_ptr == NULL) { return  NULL; }

  obj_ptr->kind = FLOAT;
  obj_ptr->data.v_float = value;

  return obj_ptr;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj_ptr = malloc(sizeof(snek_object_t));
  if (obj_ptr == NULL) {
    return NULL;
  }

  obj_ptr->kind = INTEGER;
  obj_ptr->data.v_int = value;

  return obj_ptr;
}
