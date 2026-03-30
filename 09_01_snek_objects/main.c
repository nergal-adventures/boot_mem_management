#include "../munit/munit.h"
#include "snekobject.h"
#include <stdlib.h>

static MunitResult test_integer_constant(const MunitParameter params[], void *data) { 
  (void)params;
  (void)data;

    munit_assert_int(INTEGER, ==, 0); 
    
 return MUNIT_OK;
    }

static MunitResult test_integer_obj(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  obj->kind = INTEGER;
  obj->data.v_int = 0;
  munit_assert_int(obj->kind, ==, INTEGER);
  munit_assert_int(obj->data.v_int, ==, 0);

  free(obj);
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/integer_constant", test_integer_constant, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/integer_obj", test_integer_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("object-integer-def", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

