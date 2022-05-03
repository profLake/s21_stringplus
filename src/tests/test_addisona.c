#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "../s21_string.h"
#include <stdio.h>

START_TEST(test_s21_to_lower)
{
    char str[20] = "HELLO", stx[20] = "hello";
    char *src = s21_to_lower(str);
    ck_assert_str_eq(src, stx);
}
END_TEST

int main(void)
{
    int number_failed;
    Suite *s21 = suite_create("s21_string");
    TCase *tc_core = tcase_create("Core");
    SRunner *sr;
    sr = srunner_create(s21);
    /* Core test case */
    tcase_add_test(tc_core, test_s21_to_lower);
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

