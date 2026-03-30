#include "exercise.h"
#include "../munit/munit.h"

static MunitResult test_zero_out_integer(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_int_t integer;
  integer.value = 42;
  snek_zero_out(&integer, INTEGER);
  munit_assert_int(integer.value, ==, 0);

  return MUNIT_OK;
}

static MunitResult test_zero_out_float(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_float_t float_num;
  float_num.value = 3.14;
  snek_zero_out(&float_num, FLOAT);
  munit_assert_float(float_num.value, ==, 0.0);
  
 return MUNIT_OK;
}

static MunitResult test_zero_out_bool(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_bool_t boolean;
  boolean.value = 1;
  snek_zero_out(&boolean, BOOL);
  munit_assert_int(boolean.value, ==, 0);
  
 return MUNIT_OK;
}

static MunitResult test_zero_out_nonzero_values(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_int_t integer;
  snek_float_t float_num;
  snek_bool_t boolean;

  integer.value = -100;
  float_num.value = -99.99;
  boolean.value = 255;

  snek_zero_out(&integer, INTEGER);
  snek_zero_out(&float_num, FLOAT);
  snek_zero_out(&boolean, BOOL);

  munit_assert_int(integer.value, ==, 0);
  munit_assert_float(float_num.value, ==, 0.0);
  munit_assert_int(boolean.value, ==, 0);
  
 return MUNIT_OK;
}

static MunitTest tests[] = {
  {"/test_zero_out_integer", test_zero_out_integer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  {"/test_zero_out_float", test_zero_out_float, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  {"/test_zero_out_bool", test_zero_out_bool, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  {"/test_zero_out_nonzero_values", test_zero_out_nonzero_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  munit_null_test,
};

static MunitSuite suite = munit_suite("snek_zero_out", tests);

int main() {
  return munit_suite_main(&suite, NULL, 0, NULL);
}

