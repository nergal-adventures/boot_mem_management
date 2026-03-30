#include "../munit/munit.h"
#include "snekobject.h"

static MunitResult test_integer(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(42);
  munit_assert_int(snek_length(obj), ==, 1);

  free(obj);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_float(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(3.14);
  munit_assert_int(snek_length(obj), ==, 1);

  free(obj);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_string(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *shorter = new_snek_string("hello");
  munit_assert_int(snek_length(shorter), ==, 5);

  snek_object_t *longer = new_snek_string("hello, world");
  munit_assert_int(snek_length(longer), ==, strlen("hello, world"));
  free(shorter->data.v_string);
  free(shorter);
  free(longer->data.v_string);
  free(longer);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_vector3(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *i = new_snek_integer(1);
  snek_object_t *vec = new_snek_vector3(i, i, i);
  munit_assert_int(snek_length(vec), ==, 3);

  free(i);
  free(vec);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_array(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *i = new_snek_integer(1);
  snek_object_t *arr = new_snek_array(4);
  munit_assert(snek_array_set(arr, 0, i));
  munit_assert(snek_array_set(arr, 1, i));
  munit_assert(snek_array_set(arr, 2, i));

  munit_assert_int(snek_length(arr), ==, 4);

  free(i);
  free(arr->data.v_array.elements);
  free(arr);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/integer", test_integer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }, 
    {"/float", test_float, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/string", test_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },   
    {"/vector", test_vector3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/array", test_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },     
    munit_null_test 
  };

  MunitSuite suite = munit_suite("object-length", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

