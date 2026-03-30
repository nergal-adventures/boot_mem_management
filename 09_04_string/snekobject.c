#include "snekobject.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj_ptr = malloc(sizeof(snek_object_t));
  if (obj_ptr == NULL) { return NULL; }


  size_t str_len = strlen(value);
  char *str_ptr = malloc(str_len + 1);
  if (str_ptr == NULL ) {
    free(obj_ptr);
    return NULL;
  }
  strcpy(str_ptr, value);
  
  obj_ptr->kind = STRING;
  obj_ptr->data.v_string = str_ptr;

  return obj_ptr;
}

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
