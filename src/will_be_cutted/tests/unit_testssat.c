#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../s21_string.h"

#include <stdio.h>


START_TEST(test_s21_strrchr)
{
    const char str[12] = "1534a5E,";
    char * empt = "";
    ck_assert_ptr_eq(s21_strrchr(str, '3'), strrchr(str, '3'));
    ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
    ck_assert_ptr_eq(s21_strrchr(str, 'e'), strrchr(str, 'e'));
    ck_assert_ptr_eq(s21_strrchr(str, '5'), strrchr(str, '5'));
    ck_assert_ptr_eq(s21_strrchr(empt, '4'), strrchr(empt, '4'));
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
    suite_add_tcase(s21, tc_core);
    tcase_add_test(tc_core, test_s21_strrchr);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
