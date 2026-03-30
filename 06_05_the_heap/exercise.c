#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

char *get_full_greeting(char *greeting, char *name, int size) {
  char *full_greeting = malloc(size * sizeof(char));
  if (full_greeting == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  snprintf(full_greeting, size * sizeof(char), "%s %s", greeting, name);
  return full_greeting;
}

