#include "../munit/munit.h"
#include "snekobject.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_inc_refcount(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(10);
  munit_assert_int(obj->refcount, ==, 1);

  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);

  free(obj);
  
 return MUNIT_OK;
}

static MunitResult test_inc_refcount_more(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(4.20);
  munit_assert_int(obj->refcount, ==, 1);

  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 6);

  free(obj);
  
 return MUNIT_OK;
}

static MunitResult test_null_obj(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  refcount_inc(NULL);
  munit_assert(1);
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/test_inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_inc_refcount_more", test_inc_refcount_more, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_null_obj", test_null_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("refcount", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

