#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../s21_string.h"

#include <stdio.h>

START_TEST(test_s21_strcat)
{
    char str[15] = "Hi";
    char str1[15] = "Hi";
    ck_assert_str_eq(s21_strcat(str, ", People!"),  strcat(str1, ", People!"));
    ck_assert_str_eq(s21_strcat(str, ""), strcat(str1, ""));
}
END_TEST

START_TEST(test_s21_memset)
{
    char str[30] = "____ zelenoglazoe taksi";
    char str1[30] = "____ zelenoglazoe taksi";
    memset(str, 'O', 3);
    s21_memset(str1, 'O', 3);
    
    ck_assert_str_eq(str, str1);
   
}
END_TEST

START_TEST(test_s21_memmove)
{
    char src[20] = "88, 89, 90";
    char src1[20] = "88, 89, 90";
    memmove(src, "86, 87", 5);
    s21_memmove(src1, "86, 87", 5);
    
    ck_assert_str_eq(src, src1);
    
    memmove(&src[3], "Q", 1);
    s21_memmove(&src1[5], "Q", 1);
    
    ck_assert_str_ne(src, src1);
}
END_TEST

START_TEST(test_s21_memcmp)
{
}
END_TEST

START_TEST(test_s21_strcspn)
{
    char str1[20] = "1234567890", str2[20] = "098", str[] = "edr";
    
    ck_assert_int_eq(strcspn(str1, str2),s21_strcspn(str1, str2));
    ck_assert_int_eq(strcspn(str, str2),s21_strcspn(str, str2));
    
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
    TCase *tc_core = tcase_create("Core");
    SRunner *sr;
    sr = srunner_create(s21);
    /* Core test case */
    suite_add_tcase(s21, tc_core);
    tcase_add_test(tc_core, test_s21_memcmp);
    tcase_add_test(tc_core, test_s21_memset);
    tcase_add_test(tc_core, test_s21_memmove);
    tcase_add_test(tc_core, test_s21_strcat);
    tcase_add_test(tc_core, test_s21_strspn);
    tcase_add_test(tc_core, test_s21_strcspn);
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
