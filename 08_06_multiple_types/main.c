//#include "bootlib.h"
#include "../munit/munit.h"
#include "exercise.h"

static MunitResult multiple_types_stack(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(4);
  munit_assert_ptr_not_null(s);

  stack_push_multiple_types(s);
  munit_assert_int(s->count, ==, 2);

  float *f = s->data[0];
  munit_assert_float(*f, ==, 3.14);

  char *string = s->data[1];
  munit_assert_string_equal(string, "Sneklang is blazingly slow!");

  free(f);
  free(string);
  stack_free(s);
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/multiple_types_stack", multiple_types_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("snekstack", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

