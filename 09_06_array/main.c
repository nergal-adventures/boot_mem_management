#include "../munit/munit.h"
#include "snekobject.h"
#include <stdlib.h>

static MunitResult test_create_empty_array(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_array(2);

  munit_assert_int(obj->kind, ==, ARRAY);
  munit_assert_int(obj->data.v_array.size, ==, 2);

  free(obj->data.v_array.elements);
  free(obj);
 // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_used_calloc(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_array(2);

  munit_assert_ptr_null(obj->data.v_array.elements[0]);
  munit_assert_ptr_null(obj->data.v_array.elements[1]);

  free(obj->data.v_array.elements);
  free(obj);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/empty", test_create_empty_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/calloc", test_used_calloc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("object-array", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

