// #include "bootlib.h"
#include "../munit/munit.h"
#include "sneknew.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_reference_object(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  new_snek_integer(vm, 5);
  new_snek_string(vm, "hello");
  vm_free(vm);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_frames_are_freed(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  vm_new_frame(vm);
  vm_new_frame(vm);
  vm_free(vm);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/test_reference_object", test_reference_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("mark-and-sweep", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

