//#include "bootlib.h"
#include "../munit/munit.h"
#include "exercise.h"

static MunitResult create_stack_small(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(3);
  munit_assert_int(s->capacity, ==, 3);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  free(s->data);
  free(s);

  //assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult create_stack_large(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(100);
  munit_assert_int(s->capacity, ==, 100);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  free(s->data);
  free(s);

  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/create_stack_small", create_stack_small, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/create_stack_large", create_stack_large, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("snekstack", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

