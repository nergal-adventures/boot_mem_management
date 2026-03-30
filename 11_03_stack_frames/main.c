// #include "bootlib.h"
#include "../munit/munit.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_vm_new(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  vm_new_frame(vm);
  munit_assert_int(vm->frames->count, ==, 1);
  vm_free(vm);
  
 return MUNIT_OK;
}

static MunitResult test_vm_new_frame(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);
  munit_assert_ptr(frame->references, !=, NULL);
  munit_assert_int(frame->references->count, ==, 0);
  munit_assert(frame->references->capacity > 0); // references stack must have capacity > 0
  munit_assert_ptr(frame->references->data, !=, NULL);
  vm_free(vm);
  
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
    {"/test_vm_new_frame", test_vm_new_frame, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("mark-and-sweep", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

