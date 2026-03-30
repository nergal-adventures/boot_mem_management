#include "../munit/munit.h"
#include "snekobject.h"
#include <stdlib.h>

static MunitResult test_returns_null(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *vec = new_snek_vector3(NULL, NULL, NULL);

  munit_assert_null(vec);

  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

static MunitResult test_vec_multiple_objects(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *x = new_snek_integer(1);
  snek_object_t *y = new_snek_integer(2);
  snek_object_t *z = new_snek_integer(3);
  snek_object_t *vec = new_snek_vector3(x, y, z);

  munit_assert_ptr_not_null(vec);

  // Vectors should not copy objects, they get the reference to the objects.
  munit_assert_ptr(x, ==, vec->data.v_vector3.x);
  munit_assert_ptr(y, ==, vec->data.v_vector3.y);
  munit_assert_ptr(z, ==, vec->data.v_vector3.z);

  // Assert we have integer values correct
  munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 1);
  munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 2);
  munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 3);

  // Free all of our objects.
  free(x);
  free(y);
  free(z);
  free(vec);
  // assert(boot_all_freed());
  return MUNIT_OK;
}

static MunitResult test_vec_same_object(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  snek_object_t *i = new_snek_integer(1);
  snek_object_t *vec = new_snek_vector3(i, i, i);

  munit_assert_ptr_not_null(vec);

  // Vectors should not copy objects, they get the reference to the objects.
  munit_assert_ptr(i, ==, vec->data.v_vector3.x);
  munit_assert_ptr(i, ==, vec->data.v_vector3.y);
  munit_assert_ptr(i, ==, vec->data.v_vector3.z);

  // Assert we have integer values correct
  munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 1);
  munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 1);
  munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 1);

  i->data.v_int = 2;

  // Assert we have integer values correct, after update
  munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 2);
  munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 2);
  munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 2);

  // Free all of our objects.
  free(i);
  free(vec);
  // assert(boot_all_freed());
  
 return MUNIT_OK;
}

int main() {
  MunitTest tests[] = {
    {"/returns_null", test_returns_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/multiple_objects", test_vec_multiple_objects, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    {"/same_object", test_vec_same_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
      munit_null_test,
  };

  MunitSuite suite = munit_suite("object-vector", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}

