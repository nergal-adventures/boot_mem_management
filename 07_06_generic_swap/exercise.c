#include "exercise.h"
#include <stdlib.h>
#include <string.h>

void swap(void *vp1, void *vp2, size_t size) {
  void *aux = malloc(size);

  if (aux == NULL) {
    return;
  }

  memcpy(aux, vp1, size);
  memcpy(vp1, vp2, size);
  memcpy(vp2, aux, size);

  free(aux);
}
