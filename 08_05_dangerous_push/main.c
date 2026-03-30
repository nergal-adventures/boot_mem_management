//#include "bootlib.h"
#include "../munit/munit.h"
#include "exercise.h"

static MunitResult heterogenous_stack(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_stack_t *s = stack_new(2);
  munit_assert_ptr_not_null(s);

  scary_double_push(s);
  munit_assert_int(s->count, ==, 2);

  int value = (int)s->data[0];
  munit_assert_int(value, ==, 1337);

  int *pointer = s->data[1];
  munit_assert_int(*pointer, ==, 1024);

  free(pointer);
  stack_free(s);
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/heterogenous_stack", heterogenous_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("snekstack", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

