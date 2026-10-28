#include "test_suites.h"

static MunitSuite suites[] = {
    {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE},
};

static const MunitSuite suite = {
    (char *)"", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[]) {
    suites[0] = math_utils_suite;
    return munit_suite_main(&suite, NULL, argc, argv);
}
