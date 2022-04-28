#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../s21_string.h"


START_TEST(test_s21_memcmp)
{
    int out;
    out = s21_memcmp("12347", "12345", 5);
    ck_assert_int_eq(out, 2);
}
END_TEST

START_TEST(test_s21_strchr)
{
    ck_assert(s21_strchr("12347", '4') == "12347" + 3);
}
END_TEST

START_TEST(test_s21_memcpy)
{
    char dest[50];
    s21_memcpy(dest, "hello", 4);
    ck_assert(strncmp(dest, "hellr", 4) == 0);
    ck_assert(strncmp(dest, "hellr", 5) != 0);
}
END_TEST

START_TEST(test_s21_strncmp)
{
    ck_assert(s21_strncmp("hello", "hellr", 4) == 0);
    ck_assert(s21_strncmp("hello", "hellr", 5) == 'o' - 'r');
}
END_TEST

START_TEST(test_s21_strlen)
{
    int out;
    out = s21_strlen("1969");
    ck_assert_int_eq(out, 4);
}
END_TEST


Suite* s21_string_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("s21_string");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_s21_memcmp);
    tcase_add_test(tc_core, test_s21_strchr);
    tcase_add_test(tc_core, test_s21_memcpy);
    tcase_add_test(tc_core, test_s21_strncmp);
    tcase_add_test(tc_core, test_s21_strlen);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
    /*tc_limits = tcase_create("Limits");

    tcase_add_test(tc_limits, test_money_create_neg);
    tcase_add_test(tc_limits, test_money_create_zero);
    suite_add_tcase(s, tc_limits);
    */

    return s;
}


int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = s21_string_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
