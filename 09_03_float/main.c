#include "../munit/munit.h"
#include "snekobject.h"
#include <stdlib.h>

static MunitResult test_positive(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(42);
  munit_assert_float(obj->data.v_float, ==, 42);

  free(obj);
  //assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_zero(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(0.0);

  munit_assert_float(obj->kind, ==, FLOAT);
  munit_assert_float(obj->data.v_float, ==, 0.0);

  free(obj);
  //assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_negative(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(-5.0);

  munit_assert_float(obj->kind, ==, FLOAT);
  munit_assert_float(obj->data.v_float, ==, -5.0);

  free(obj);
  //assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/positive", test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/negative", test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("object-float", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

