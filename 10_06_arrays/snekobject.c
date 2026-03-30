#include "snekobject.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
  if (snek_obj == NULL || value == NULL) {
    return false;
  }
  if (snek_obj->kind != ARRAY) {
    return false;
  }
  if (index >= snek_obj->data.v_array.size) {
    return false;
  }

  if (snek_obj->data.v_array.elements[index] != NULL) {
    refcount_dec(snek_obj->data.v_array.elements[index]);
  }

  value->refcount++;
  snek_obj->data.v_array.elements[index] = value;
  return true;
}


snek_object_t *_new_snek_object();

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
  refcount_inc(x);
  refcount_inc(y);
  refcount_inc(z);

  return obj;
}

void refcount_free(snek_object_t *obj) {
  if (obj == NULL) { return; }
  switch (obj->kind) {
    case INTEGER || FLOAT:
      break;
    case STRING:
      free(obj->data.v_string);
      break;
    case VECTOR3:
      refcount_dec(obj->data.v_vector3.x);
      refcount_dec(obj->data.v_vector3.y);
      refcount_dec(obj->data.v_vector3.z);
      break;
    case ARRAY:
      for (size_t index = 0; index < obj->data.v_array.size; index++) {
        refcount_dec(obj->data.v_array.elements[index]);
      }
      free(obj->data.v_array.elements);
    default:
      break;
  }
  free(obj);
}

void refcount_dec(snek_object_t *obj) {
  if (obj != NULL) {
    obj->refcount--;
    if (obj->refcount == 0) {
      refcount_free(obj);
    }
  }
}

void refcount_inc(snek_object_t *obj) {
  if (obj != NULL) {
    obj->refcount++;
  }
}

snek_object_t *_new_snek_object() {
  snek_object_t *object = calloc(1, sizeof(snek_object_t));
  if (object == NULL) { return NULL; }
  object->refcount = 1;

  return object;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value);
  char *dst = malloc(len + 1);
  if (dst == NULL) {
    free(obj);
    return NULL;
  }

  strcpy(dst, value);

  obj->kind = STRING;
  obj->data.v_string = dst;
  return obj;
}

