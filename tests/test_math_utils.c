#include "math_utils.h"
#include "munit.h"

static MunitResult test_add_two_positive_numbers(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    munit_assert_int(add(2, 3), ==, 5);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/add_two_positive_numbers", test_add_two_positive_numbers, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

const MunitSuite math_utils_suite = {
    (char *)"/math_utils", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};
