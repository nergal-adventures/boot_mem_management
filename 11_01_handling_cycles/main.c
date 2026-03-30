#include "../munit/munit.h"
#include "snekobject.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult correctly_free(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *first = new_snek_array(1);
  snek_object_t *second = new_snek_array(1);
  // refcounts: first = 1, second = 1
  snek_array_set(first, 0, second);
  // refcounts: first = 1, second = 2
  snek_array_set(second, 0, first);
  // refcounts: first = 2, second = 2
  refcount_dec(first);
  refcount_dec(second);
  munit_assert_int(first->refcount, ==, 1);
  munit_assert_int(second->refcount, ==, 1);
  
 return MUNIT_OK;
}

// Don't touch below this line

int main() {
  MunitTest tests[] = {
    {"/correctly_free", correctly_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("refcount", tests);

  int result = munit_suite_main(&suite, NULL, 0, NULL);

  printf("*** NOTE: A memory leak warning is EXPECTED here ***\n");
  printf("*** We'll fix the circular reference problem soon ***\n");

  return result;
}

