#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../s21_string.h"

#include <stdio.h>

START_TEST(test_s21_strcat)
{
    char str[15] = "Hi";
    char str1[15] = "Hi";
    const char str2[] = ", People!";
    s21_strcat(str, str2);
    strcat(str1, str2);
    ck_assert_str_eq(str, str1);
    
}
END_TEST

START_TEST(test_s21_memcmp)
{
    int out;
    out = s21_memcmp("12347", "12345", 5);
    ck_assert_int_eq(out, 2);
}
END_TEST

START_TEST(test_s21_strchr)
{
    const char str[12] = "1234a5E,";
    char * empt = "";
    ck_assert_ptr_eq(s21_strchr(str, '3'), strchr(str, '3'));
    ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
    ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
    ck_assert_ptr_eq(s21_strchr(empt, '4'), strchr(empt, '4'));
    
    
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
    ck_assert(s21_strncmp("hello", "hellr", 5) < 0);
}
END_TEST

START_TEST(test_s21_strlen)
{
    int out;
    out = s21_strlen("1969");
    ck_assert_int_eq(out, 4);
}
END_TEST

START_TEST(test_s21_strpbrk)
{
    char *str1 = "0123456789";
    char *str2 = "369";

    ck_assert(s21_strpbrk(str1, str2) == str1 + 3);
    ck_assert(s21_strpbrk("hello", "llo") == "hello" + 2);
    ck_assert(s21_strpbrk("hello", "!.c") == NULL);

    str1 = "This, a simple";
    str2 = "!? ";
    ck_assert(s21_strpbrk(str1, str2) == str1 + 5);
    str2 = "!? T";
    ck_assert(s21_strpbrk(str1, str2) == str1 + 0);
}
END_TEST

START_TEST(test_s21_strtok)
{
    char str1[500];
    char str2[500];
    char right[500];
    char *out;
    strcpy(str1, "This, a simple string.");
    strcpy(str2, ",.- ");

    out = s21_strtok(str1, str2);
    strcpy(right, "This");
    ck_assert_str_eq(out, right);

    out = s21_strtok(NULL, str2);
    strcpy(right, "a");
    ck_assert_str_eq(out, right);

    out = s21_strtok(NULL, str2);
    strcpy(right, "simple");
    ck_assert_str_eq(out, right);

    out = s21_strtok(NULL, str2);
    strcpy(right, "string");
    ck_assert_str_eq(out, right);

    out = s21_strtok(NULL, str2);
    ck_assert_pstr_eq(out, NULL);
}
END_TEST

int main(void)
{
    int number_failed;
    Suite *s21 = suite_create("s21_string");
    TCase *tc_core = tcase_create("Core");;
    SRunner *sr;
    sr = srunner_create(s21);
    /* Core test case */
    suite_add_tcase(s21, tc_core);
    tcase_add_test(tc_core, test_s21_memcmp);
    tcase_add_test(tc_core, test_s21_strcat);
    tcase_add_test(tc_core, test_s21_strchr);
    tcase_add_test(tc_core, test_s21_memcpy);
    tcase_add_test(tc_core, test_s21_strncmp);
    tcase_add_test(tc_core, test_s21_strlen);
    tcase_add_test(tc_core, test_s21_strpbrk);
    tcase_add_test(tc_core, test_s21_strtok);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
