#include "snekobject.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


snek_object_t *snek_array_get(snek_object_t *array, size_t index) {
  if (array == NULL) { return NULL; }
  if (array->kind != ARRAY) { return NULL; }
  if (array->data.v_array.size < index) { return NULL; }

  return array->data.v_array.elements[index];
}

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
  if (array == NULL || value == NULL) { return false; }
  if (array->kind != ARRAY) { return false; }
  if (array->data.v_array.size <= index) { return false; }

  array->data.v_array.elements[index] = value;

  return true;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *array_ptr = malloc(sizeof(snek_object_t));
  if (array_ptr == NULL) { return NULL; }

  snek_object_t **array_objects = calloc(size, sizeof(snek_object_t *));
  if (array_objects == NULL) {
    free(array_ptr);
    return NULL;
  }

  snek_array_t array = {
    .size = size,
    .elements = array_objects
  };

  array_ptr->kind = ARRAY;
  array_ptr->data.v_array = array;

  return array_ptr;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
    ) {
  if (x == NULL || y == NULL || z == NULL) { return NULL; }

  snek_object_t *vector_ptr = malloc(sizeof(snek_object_t));
  if (vector_ptr == NULL) { return NULL; }

  vector_ptr->kind = VECTOR3;

  vector_ptr->data.v_vector3.x = x;
  vector_ptr->data.v_vector3.y = y;
  vector_ptr->data.v_vector3.z = z;

  return vector_ptr;
}

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
