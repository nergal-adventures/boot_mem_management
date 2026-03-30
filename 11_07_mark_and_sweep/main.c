// #include "bootlib.h"
#include "../munit/munit.h"
#include "sneknew.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_field_exists(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  snek_object_t *lane_courses = new_snek_integer(vm, 20);
  snek_object_t *teej_courses = new_snek_integer(vm, 1);
  (void)lane_courses->is_marked;
  (void)teej_courses->is_marked;
  vm_free(vm);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_marked_is_false(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  snek_object_t *lane_courses = new_snek_integer(vm, 20);
  snek_object_t *teej_courses = new_snek_integer(vm, 1);
  munit_assert_false(lane_courses->is_marked);
  munit_assert_false(teej_courses->is_marked);
  vm_free(vm);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/test_field_exists", test_field_exists, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_marked_is_false", test_marked_is_false, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("mark-and-sweep", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

