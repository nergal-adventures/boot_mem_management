#include "snekobject.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  if (a == NULL || b == NULL) { return NULL; }

  switch (a->kind) {
    case INTEGER: {
                    switch (b->kind) {
                      case INTEGER:
                        return new_snek_integer(a->data.v_int + b->data.v_int);
                      case FLOAT:
                        return new_snek_float((float)a->data.v_int + b->data.v_float);
                      default:
                        return NULL;
                    }
                  }
    case FLOAT: 
                  {
                    switch (b->kind) {
                      case INTEGER:
                        return new_snek_float(a->data.v_float + (float)b->data.v_int);
                      case FLOAT:
                        return new_snek_float(a->data.v_float + b->data.v_float);
                      default:
                        return NULL;
                    }
                  }
    case STRING: 
                {
                   if (b->kind != STRING) { return NULL; }
                   size_t new_length = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
                   char *tmp_str = calloc(sizeof(char *), new_length);
                   strcat(tmp_str, a->data.v_string);
                   strcat(tmp_str, b->data.v_string);
                   snek_object_t *new_str = new_snek_string(tmp_str);
                   free(tmp_str);
                   return new_str;
                 }
    case VECTOR3: 
                 {
                    if (b->kind != VECTOR3) { return NULL; }
                    snek_object_t *new_vector3 = new_snek_vector3(
                        snek_add(a->data.v_vector3.x, b->data.v_vector3.x), 
                        snek_add(a->data.v_vector3.y, b->data.v_vector3.y), 
                        snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
                        );
                    return new_vector3;
                  }
    case ARRAY: 
                  {
                    if (b->kind != ARRAY) { return NULL; }
                    snek_object_t *new_array = 
                      new_snek_array(a->data.v_array.size + b->data.v_array.size);
                    for (size_t index = 0; index < a->data.v_array.size; index++) {
                      snek_array_set(
                          new_array, 
                          index, 
                          snek_array_get(a, index)
                          );
                    }
                    for (size_t index = 0; index < b->data.v_array.size; index++) {
                      snek_array_set(
                          new_array, 
                          index + a->data.v_array.size, 
                          snek_array_get(b, index)
                          );
                    }
                    return new_array;
                  }
    default:
      return NULL;
  }
}

size_t snek_length(snek_object_t *object) {
  if (object == NULL) { return -1; }
  switch (object->kind) {
    case INTEGER:
      return 1;
    case FLOAT:
      return 1;
    case STRING:
      return strlen(object->data.v_string);
    case VECTOR3:
      return 3;
    case ARRAY:
      return object->data.v_array.size;
    default:
      return -1;
  }

  return -1;
}

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
