// #include "bootlib.h"
#include "../munit/munit.h"
#include "sneknew.h"
#include "snekobject.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_new_object(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  snek_object_t *obj = new_snek_integer(vm, 5);
  munit_assert_int(obj->kind, ==, INTEGER);
  munit_assert_ptr_equal(vm->objects->data[0], obj);
  free(obj);
  vm_free(vm);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_vm_new(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  munit_assert_ptr_not_null(vm->frames);
  munit_assert_ptr_not_null(vm->objects);
  vm_free(vm);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_frames_are_freed(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  vm_new_frame(vm);
  vm_free(vm);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/test_vm_new", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_new_object", test_new_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("mark-and-sweep", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

