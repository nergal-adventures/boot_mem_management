#include "../munit/munit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snekobject.h"

static MunitResult test_integer_add(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_integer(1);
  snek_object_t *three = new_snek_integer(3);
  snek_object_t *four = snek_add(one, three);

  munit_assert_not_null(four);
  munit_assert_int(four->kind, ==, INTEGER);
  munit_assert_int(four->data.v_int, ==, 4);

  free(one);
  free(three);
  free(four);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_float_add(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_float(1.5);
  snek_object_t *three = new_snek_float(3.5);
  snek_object_t *five = snek_add(one, three);

  munit_assert_not_null(five);
  munit_assert_int(five->kind, ==, FLOAT);
  munit_assert_float(five->data.v_float, ==, 1.5 + 3.5);

  free(one);
  free(three);
  free(five);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_string_add(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *hello = new_snek_string("hello");
  snek_object_t *world = new_snek_string(", world");
  snek_object_t *greeting = snek_add(hello, world);

  munit_assert_not_null(greeting);
  munit_assert_int(greeting->kind, ==, STRING);
  printf("\n### Size: %zu\n", strlen(greeting->data.v_string));
  printf("\n### Sizeof: %zu\n", sizeof(greeting->data.v_string));
  munit_assert_int(strlen(greeting->data.v_string), ==, 12);
  munit_assert_string_equal(greeting->data.v_string, "hello, world");

  free(hello->data.v_string);
  free(hello);
  free(world->data.v_string);
  free(world);
  free(greeting->data.v_string);
  free(greeting);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_string_add_self(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *repeated = new_snek_string("(repeated)");
  snek_object_t *result = snek_add(repeated, repeated);

  munit_assert_not_null(result);
  munit_assert_int(result->kind, ==, STRING);
  munit_assert_string_equal(result->data.v_string, "(repeated)(repeated)");

  free(repeated->data.v_string);
  free(repeated);
  free(result->data.v_string);
  free(result);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_vector3_add(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_float(1.0);
  snek_object_t *two = new_snek_float(2.0);
  snek_object_t *three = new_snek_float(3.0);
  snek_object_t *four = new_snek_float(4.0);
  snek_object_t *five = new_snek_float(5.0);
  snek_object_t *six = new_snek_float(6.0);

  snek_object_t *v1 = new_snek_vector3(one, two, three);
  snek_object_t *v2 = new_snek_vector3(four, five, six);
  snek_object_t *result = snek_add(v1, v2);

  munit_assert_not_null(result);
  munit_assert_int(result->kind, ==, VECTOR3);

  munit_assert_float(result->data.v_vector3.x->data.v_float, ==, 5.0);
  munit_assert_float(result->data.v_vector3.y->data.v_float, ==, 7.0);
  munit_assert_float(result->data.v_vector3.z->data.v_float, ==, 9.0);

  free(v1->data.v_vector3.x);
  free(v1->data.v_vector3.y);
  free(v1->data.v_vector3.z);
  free(v1);

  free(v2->data.v_vector3.x);
  free(v2->data.v_vector3.y);
  free(v2->data.v_vector3.z);
  free(v2);

  free(result->data.v_vector3.x);
  free(result->data.v_vector3.y);
  free(result->data.v_vector3.z);
  free(result);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_array_add(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_integer(1);
  snek_object_t *ones = new_snek_array(2);
  munit_assert(snek_array_set(ones, 0, one));
  munit_assert(snek_array_set(ones, 1, one));

  snek_object_t *hi = new_snek_string("hi");
  snek_object_t *hellos = new_snek_array(3);
  munit_assert(snek_array_set(hellos, 0, hi));
  munit_assert(snek_array_set(hellos, 1, hi));
  munit_assert(snek_array_set(hellos, 2, hi));

  snek_object_t *result = snek_add(ones, hellos);

  munit_assert_not_null(result);
  munit_assert_int(result->kind, ==, ARRAY);

  snek_object_t *first = snek_array_get(result, 0);
  munit_assert_not_null(first);
  munit_assert_int(first->data.v_int, ==, 1);

  snek_object_t *third = snek_array_get(result, 2);
  munit_assert_not_null(third);
  munit_assert_string_equal(third->data.v_string, "hi");

  free(one);
  free(ones->data.v_array.elements);
  free(ones);

  free(hi->data.v_string);
  free(hi);
  free(hellos->data.v_array.elements);
  free(hellos);
  free(result->data.v_array.elements);
  free(result);

  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/integer", test_integer_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/float", test_float_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/string", test_string_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/string_repeated", test_string_add_self, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/array", test_array_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/vector3", test_vector3_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    munit_null_test
  };
  

  MunitSuite suite = munit_suite("object-add", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

