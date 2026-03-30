#include "../munit/munit.h"
#include "snekobject.h"
#include <stdlib.h>

static MunitResult test_array(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  // Create an array
  snek_object_t *obj = new_snek_array(2);

  // Create some objects to put in the array
  // Can store objects, even though they have different types (just like Python)
  snek_object_t *first = new_snek_string("First");
  snek_object_t *second = new_snek_integer(3);

  munit_assert(snek_array_set(obj, 0, first));
  munit_assert(snek_array_set(obj, 1, second));

  snek_object_t *retrieved_first = snek_array_get(obj, 0);
  munit_assert_not_null(retrieved_first);
  munit_assert_int(retrieved_first->kind, ==, STRING);
  munit_assert_ptr(first, ==, retrieved_first);

  snek_object_t *retrieved_second = snek_array_get(obj, 1);
  munit_assert_not_null(retrieved_second);
  munit_assert_int(retrieved_second->kind, ==, INTEGER);
  munit_assert_ptr(second, ==, retrieved_second);

  free(first->data.v_string);
  free(first);
  free(second);
  free(obj->data.v_array.elements);
  free(obj);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_set_outside_bounds(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  // Create an array
  snek_object_t *obj = new_snek_array(2);

  snek_object_t *outside = new_snek_string("First");
  snek_object_t *outside_2 = new_snek_string("Second");

  // Inside of bound
  munit_assert(snek_array_set(obj, 0, outside));
  munit_assert(snek_array_set(obj, 1, outside));

  // Outside of bound
  munit_assert_false(snek_array_set(obj, 2, outside_2));
  munit_assert_false(snek_array_set(obj, 100, outside));

  // Free memory
  free(outside->data.v_string);
  free(outside);
  free(obj->data.v_array.elements);
  free(obj);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_get_outside_bounds(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  // Create an array
  snek_object_t *obj = new_snek_array(1);
  snek_object_t *first = new_snek_string("First");
  munit_assert(snek_array_set(obj, 0, first));

  // Outside of bound
  munit_assert_null(snek_array_get(obj, 1));

  free(first->data.v_string);
  free(first);
  free(obj->data.v_array.elements);
  free(obj);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/set_and_get", test_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/set_outside", test_set_outside_bounds, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/get_outside", test_get_outside_bounds, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("object-array", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}
