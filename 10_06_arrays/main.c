#include "../munit/munit.h"
#include "snekobject.h"
#include <stdio.h>
#include <stdlib.h>

static MunitResult test_array_set(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *foo = new_snek_integer(1);

  snek_object_t *array = new_snek_array(1);
  snek_array_set(array, 0, foo);
  munit_assert_int(foo->refcount, ==, 2);

  // munit_assert(!boot_is_freed(foo));

  refcount_dec(foo);
  refcount_dec(array);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_array_free(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *bar = new_snek_integer(2);
  snek_object_t *baz = new_snek_integer(3);

  snek_object_t *array = new_snek_array(2);
  snek_array_set(array, 0, foo);
  snek_array_set(array, 1, bar);
  munit_assert_int(foo->refcount, ==, 2);
  munit_assert_int(bar->refcount, ==, 2);
  munit_assert_int(baz->refcount, ==, 1);

  // `foo` is stil referenced in the `array`, so it should not be freed.
  refcount_dec(foo);
  // munit_assert(!boot_is_freed(foo));

  // Overwrite index 0, which is `foo`, with `baz`.
  //  Now `foo` is not referenced by `array`, so it should be freed.
  snek_array_set(array, 0, baz);
  // munit_assert(boot_is_freed(foo));

  refcount_dec(bar);
  refcount_dec(baz);
  refcount_dec(array);
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_vector3_refcounting(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *bar = new_snek_integer(2);
  snek_object_t *baz = new_snek_integer(3);

  snek_object_t *vec = new_snek_vector3(foo, bar, baz);
  munit_assert_int(foo->refcount, ==, 2);
  munit_assert_int(bar->refcount, ==, 2);
  munit_assert_int(baz->refcount, ==, 2);

  // `foo` is stil referenced in the `vec`, so it should not be freed.
  refcount_dec(foo);
  // munit_assert(!boot_is_freed(foo));

  refcount_dec(vec);
  // munit_assert(boot_is_freed(foo));

  // These are still alive, they have the original reference still.
  // munit_assert(!boot_is_freed(bar));
  // munit_assert(!boot_is_freed(baz));

  // Decrement the last reference to the objects, so they will be freed.
  refcount_dec(bar);
  refcount_dec(baz);

  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_int_has_refcount(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(10);
  munit_assert_int(obj->refcount, ==, 1);

  free(obj);
  
 return MUNIT_OK;
}

static MunitResult test_inc_refcount(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(4.20);
  munit_assert_int(obj->refcount, ==, 1);

  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);

  free(obj);
  
 return MUNIT_OK;
}

static MunitResult test_dec_refcount(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(4.20);

  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);

  refcount_dec(obj);
  munit_assert_int(obj->refcount, ==, 1);

  // munit_assert(!boot_is_freed(obj));

  // Object is still alive, so we will free manually.
  free(obj);
  
 return MUNIT_OK;
}

static MunitResult test_refcount_free_is_called(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(4.20);

  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);

  refcount_dec(obj);
  munit_assert_int(obj->refcount, ==, 1);

  refcount_dec(obj);
  // munit_assert(boot_is_freed(obj));
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_allocated_string_is_freed(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_string("Hello @wagslane!");

  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);

  refcount_dec(obj);
  munit_assert_int(obj->refcount, ==, 1);
  munit_assert_string_equal(obj->data.v_string, "Hello @wagslane!");

  refcount_dec(obj);
  // munit_assert(boot_is_freed(obj));
  // munit_assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/array_set", test_array_set, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/array_free", test_array_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/dec_refcount", test_dec_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/free_refcount", test_refcount_free_is_called, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/string_freed", test_allocated_string_is_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/vector3", test_vector3_refcounting, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    munit_null_test,
  };

  MunitSuite suite = munit_suite("refcount", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

