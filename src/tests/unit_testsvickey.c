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
    int out;
    out = s21_memcmp("12347", "12345", 5);
    ck_assert_int_eq(out, 1);
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

START_TEST(test_s21_strcpy)
{
    char empty[] = "", empty1[] = "", spaces[] = "    ", spaces1[] = "    ";
    ck_assert_str_eq(s21_strcpy(empty, ""), strcpy(empty1, ""));
    ck_assert_str_eq(s21_strcpy(spaces, "/00"), strcpy(spaces1, "/00"));
    ck_assert_str_eq(s21_strcpy("abc", "dcb"), strcpy("abc", "dcb"));
    ck_assert_str_eq(s21_strcpy("qwertyuiopasdfg", "WE12#@!hyui."), strcpy("qwertyuiopasdfg", "WE12#@!hyui."));
    ck_assert_str_eq(s21_strcpy("something", "/0"), strcpy("something", "/0"));
    ck_assert_str_eq(s21_strcpy("what??", ""), strcpy("what??", ""));
}
END_TEST

START_TEST(test_s21_strncpy)
{
    char str[28] = "So many test/000/ fu*hh..", str1[28] = "So many test/000/ fu*hh..", src[100] = "   /00never gonna give you up, never gonna let them down...", src1[10] = "", src11[2] = "",src2[9] = "/000/", src3[6] = "/0", src33[6] = "/0", src4[20] = "just like that";
    
    ck_assert_str_eq(s21_strncpy(src, str1, 28), strncpy(src, str, 28));
    ck_assert_str_eq(s21_strncpy(str1, src1, 4), strncpy(str, src1, 4));
    ck_assert_str_eq(s21_strncpy(src1, str1, 1), strncpy(src11, str, 1));
    ck_assert_str_eq(s21_strncpy(str1, src2, 5), strncpy(str, src2, 5));
    ck_assert_str_eq(s21_strncpy(src3, str1, 2), strncpy(src33, str, 2));
    ck_assert_str_eq(s21_strncpy(str1, src4, 16), strncpy(str, src4, 16));
    ck_assert_str_eq(s21_strncpy(str1, "3oi", 0), strncpy(str, "3oi", 0));
}
END_TEST

START_TEST(test_s21_strspn)
{
    char src[] = "WE ARE THE CHAMPIONS!", src1[] = "WE ", src2[] = "no we're not";
    
    ck_assert_int_eq(strcspn(src,src1), s21_strcspn(src, src1));
    ck_assert_int_eq(strcspn(src,src2), s21_strcspn(src, src2));
    
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

START_TEST(test_s21_strcmp)
{
    ck_assert_int_eq(s21_strcmp("h", "!fvgb9876"), strcmp("h", "!fvgb9876"));
    ck_assert_int_eq(s21_strcmp("GHTH", "!.76"), strcmp("GHTH", "!.76"));
    ck_assert_int_eq(s21_strcmp("", "ryhEF"), strcmp("", "ryhEF"));
    ck_assert_int_eq(s21_strcmp("1234SZR", ""), strcmp("1234SZR", ""));
    ck_assert_int_eq(s21_strcmp("Sold it!", "Sold it!"), strcmp("Sold it!", "Sold it!"));
    ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));
    ck_assert_int_eq(s21_strcmp("\0", "\0"), strcmp("\0", "\0"));
}
END_TEST

START_TEST(test_s21_strncmp)
{
    ck_assert_int_eq(s21_strncmp("hello", "hellr", 4), strncmp("hello", "hellr", 4));
    ck_assert_int_eq(s21_strncmp("hello", "hellr", 5), strncmp("hello", "hellr", 5));
    ck_assert_int_eq(s21_strncmp("PRISE", "shitty", 5), strncmp("PRISE", "shitty", 5));
    ck_assert_int_eq(s21_strncmp("sh...", "shout, shout", 5), strncmp("sh...", "shout, shout", 5));
    ck_assert_int_eq(s21_strncmp(".", ".0123", 3), strncmp(".", ".0123", 3));
    ck_assert_int_eq(s21_strncmp("", "   endOFemmpty", 3), strncmp("", "   endOFemmpty", 3));
    ck_assert_int_eq(s21_strncmp("", " endOFsPAACE", 1), strncmp("", " endOFsPAACE", 1));
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
    tcase_add_test(tc_core, test_s21_strcmp);
    tcase_add_test(tc_core, test_s21_strncmp);
    tcase_add_test(tc_core, test_s21_strcpy);
    tcase_add_test(tc_core, test_s21_strncpy);
    tcase_add_test(tc_core, test_s21_strlen);
    tcase_add_test(tc_core, test_s21_strpbrk);
    tcase_add_test(tc_core, test_s21_strtok);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
