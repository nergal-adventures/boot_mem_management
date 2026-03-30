#include "../munit/munit.h"
#include "snekobject.h"
#include <stdlib.h>

static MunitResult test_str_copied(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  char *input = "Hello, World!";
  snek_object_t *obj = new_snek_string(input);

  munit_assert_int(obj->kind, ==, STRING);

  // Should not have pointers be the same, otherwise we didn't copy the value.
  munit_assert_ptr_not_equal(obj->data.v_string, input);

  // But should have the same data!
  //  This way the object can free it's own memory later.
  munit_assert_string_equal(obj->data.v_string, input);

  // Should allocate memory for the string with null terminator.
  // munit_assert_int_equal(boot_alloc_size(), 22);

  // Free the string, and then free the object.
  free(obj->data.v_string);
  free(obj);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/copies_value", test_str_copied, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("object-string", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

