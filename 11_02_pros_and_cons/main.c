// #include "bootlib.h"
#include "../munit/munit.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_vm_new(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  munit_assert_int(vm->frames->capacity, ==, 8);
  munit_assert_int(vm->objects->capacity, ==, 8);
  vm_free(vm);
  
 return MUNIT_OK;
}

static MunitResult test_vm_new_free(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  vm_free(vm);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/vm", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/vm", test_vm_new_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("mark-and-sweep", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

