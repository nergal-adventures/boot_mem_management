#include "color.h"
#include "../munit/munit.h"

static MunitResult test_colors_defined(const MunitParameter params[], void *data) {
    (void)params;
    (void)data;

    munit_assert_int(RED, ==, 55);
    munit_assert_int(GREEN, ==, 176);
    munit_assert_int(BLUE, ==, 38);

    return MUNIT_OK;
}

static MunitResult test_colors_defined_correctly(const MunitParameter params[], void *data) {
    (void)params;
    (void)data;

    munit_assert_int(RED, !=, 0);
    munit_assert_int(GREEN, !=, 120);
    munit_assert_int(BLUE, !=, 215);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/defined", test_colors_defined, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/defined_vscode", test_colors_defined_correctly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/colors",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
