//#include "bootlib.h"
#include "../munit/munit.h"
#include "snekstack.h"

static MunitResult create_stack(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(10);
  munit_assert_int(s->capacity, ==, 10);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  // Clean up our allocated data.
  free(s->data);
  free(s);

  // Should be nothing left that is allocated.
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult push_stack(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(2);
  munit_assert_ptr_not_null(s);

  munit_assert_int(s->capacity, ==, 2);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  int a = 1;

  stack_push(s, &a);
  stack_push(s, &a);

  munit_assert_int(s->capacity, ==, 2);
  munit_assert_int(s->count, ==, 2);
  munit_assert_ptr_equal(s->data[0], &a);

  // Clean up our allocated data.
  free(s->data);
  free(s);

  // Should be nothing left that is allocated.
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult push_double_capacity(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(2);
  munit_assert_ptr_not_null(s);

  munit_assert_int(s->capacity, ==, 2);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  int a = 1;

  stack_push(s, &a);
  stack_push(s, &a);

  munit_assert_int(s->capacity, ==, 2);
  munit_assert_int(s->count, ==, 2);

  stack_push(s, &a);
  munit_assert_int(s->capacity, ==, 4);
  munit_assert_int(s->count, ==, 3);
  munit_assert_ptr_equal(s->data[0], &a);

  // assert_size(boot_last_realloc_size(), ==, 4 * sizeof(void *), "realloc requested correct size");

  // Should reallocate memory.
  //assert_int_equal(boot_realloc_count(), 1, "Must reallocate memory for stack");

  // Clean up our allocated data.
  free(s->data);
  free(s);

  // Should be nothing left that is allocated.
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/create_stack", create_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/push_stack", push_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/push_double_capacity", push_double_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("snekstack", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

