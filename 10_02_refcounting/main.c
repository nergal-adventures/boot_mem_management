#include "../munit/munit.h"
#include "snekobject.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_int_has_refcount(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(10);
  munit_assert_int(obj->refcount, ==, 1);
  free(obj);
  
 return MUNIT_OK;
}

static MunitResult test_float_has_refcount(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(42.0);
  munit_assert_int(obj->refcount, ==, 1);
  free(obj);
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"test_int_has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"test_float_has_refcount", test_float_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("refcount", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

