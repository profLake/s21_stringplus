#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "../s21_string.h"


START_TEST(test_s21_strstr)
{
    char *str1;
    char *str2;

    str1 = "Simple string";
    str2 = "ple";
    ck_assert_str_eq(strstr(str1, str2), s21_strstr(str1, str2));
    str2 = "in";
    ck_assert_str_eq(strstr(str1, str2), s21_strstr(str1, str2));

    str1 = "Simple string";
    str2 = "595";
    ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_memchr)
{
    char *ptr;
    int value;
    int n;

    ptr = "123344\0er";
    value = 'e';
    n = 50;
    ck_assert_ptr_eq(memchr(ptr, value, n), s21_memchr(ptr, value, n));
    n = 5;
    ck_assert_ptr_eq(memchr(ptr, value, n), s21_memchr(ptr, value, n));
}
END_TEST

START_TEST(test_s21_memcmp)
{
    char *str1;
    char *str2;
    int n;
    int out;
    int right;

    str1 = "12345";
    str2 = "12342";
    n = 5;
    right = memcmp(str1, str2, n);
    out = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(right, out);

    str1 = "12345";
    str2 = "12342";
    n = 4;
    right = memcmp(str1, str2, n);
    out = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(right, out);

    str1 = "hello";
    str2 = "hello";
    n = 5;
    right = memcmp(str1, str2, n);
    out = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(right, out);

    str1 = "bravo!";
    str2 = "merci,";
    n = 50;
    right = memcmp(str1, str2, n);
    out = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(right, out);

    str1 = "bravo!";
    str2 = "merci,";
    n = 2;
    right = memcmp(str1, str2, n);
    out = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(right, out);

    str1 = "1234567";
    str2 = "";
    n = 6;
    right = memcmp(str1, str2, n);
    out = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(right, out);
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

START_TEST(test_s21_strerror)
{
    ck_assert_str_eq(s21_strerror(1), strerror(1));
    ck_assert_str_eq(s21_strerror(ENOSYS), strerror(ENOSYS));
    ck_assert_str_eq(s21_strerror(EEXIST), strerror(EEXIST));
    ck_assert_str_eq(s21_strerror(ENOTUNIQ), strerror(ENOTUNIQ));
}
END_TEST

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

START_TEST(test_s21_sprintf)
{
    char *format;
    char *buff_right;
    int right;
    char buff[500];
    int out;

    format = "hello, %c !";
    buff_right = "hello, r !";
    right = 10;
    out = s21_sprintf(buff, format, 'r');
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%c'!";
    buff_right = "hello, 'r'!";
    right = 11;
    out = s21_sprintf(buff, format, 'r');
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%d'!";
    buff_right = "hello, '115'!";
    right = 13;
    out = s21_sprintf(buff, format, 115);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%d'!";
    buff_right = "hello, '-119'!";
    right = 14;
    out = s21_sprintf(buff, format, -119);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%05d'!";
    buff_right = "hello, '00003'!";
    right = 15;
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%-05d'!";
    buff_right = "hello, '3    '!";
    right = 15;
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%-+05d'!";
    buff_right = "hello, '+3   '!";
    right = 15;
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%u'!";
    buff_right = "hello, '3'!";
    right = 11;
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%u'!";
    buff_right = "hello, '4294967290'!";
    right = 20;
    out = s21_sprintf(buff, format, -6);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%05u'!";
    buff_right = "hello, '00005'!";
    right = 15;
    out = s21_sprintf(buff, format, 5);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%%'!";
    buff_right = "hello, '%'!";
    right = 11;
    out = s21_sprintf(buff, format);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_udecim_get_str_len)
{
    int n;
    int right;
    int out;

    n = 19;
    right = 2;
    out = s21_udecim_get_str_len(n);
    ck_assert_int_eq(right, out);

    n = 199;
    right = 3;
    out = s21_udecim_get_str_len(n);
    ck_assert_int_eq(right, out);

    n = 294967290;
    right = 9;
    out = s21_udecim_get_str_len(n);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_frmt_is_tokn)
{
    char *str;
    int right;
    int out;
   
    str  = "%i";
    right = 1;
    out = s21_frmt_is_tokn(str);
    ck_assert_int_eq(right, out);
   
    str  = "%-";
    right = 0;
    out = s21_frmt_is_tokn(str);
    ck_assert_int_eq(right, out);
   
    str  = "%0.5f";
    right = 1;
    out = s21_frmt_is_tokn(str);
    ck_assert_int_eq(right, out);
   
    str  = "%0.^5f";
    right = 0;
    out = s21_frmt_is_tokn(str);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_tokn_skip_part)
{
    char *token;
    unsigned int i;
    char *right;
    char *out;
   
    token  = "c";
    i = 4;
    right = token + 0;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
   
    token  = ".5s";
    i = 4;
    right = token + 2;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
   
    /*
    token  = "0*.*f";
    i = 4;
    right = token + 1;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
    */
   
    token  = "i";
    i = 2;
    right = token + 1;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
   
    /*
    token  = ".05d";
    i = 2;
    right = token + 1;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
    */
}
END_TEST

START_TEST(test_s21_tokn_get_len)
{
    char * token;
    int right;
    int out;

    token = "d";
    right = 1;
    out = s21_tokn_get_len(token);
    ck_assert_int_eq(right, out);

    token = "c";
    right = 1;
    out = s21_tokn_get_len(token);
    ck_assert_int_eq(right, out);

    token = ".5f";
    right = 3;
    out = s21_tokn_get_len(token);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_tokn_have_flag)
{
    char *token;
    char flag;
    int right;
    int out;

    token = "c";
    flag = FLAGS[0];
    right = 0;
    out = s21_tokn_have_flag(token, flag);
    ck_assert_int_eq(right, out);

    token = "c hello!";
    flag = FLAGS[0];
    right = 0;
    out = s21_tokn_have_flag(token, flag);
    ck_assert_int_eq(right, out);

    token = "-0d";
    flag = FLAGS[0];
    right = 1;
    out = s21_tokn_have_flag(token, flag);
    ck_assert_int_eq(right, out);

    token = "-0d";
    flag = FLAGS[4];
    right = 1;
    out = s21_tokn_have_flag(token, flag);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_tokn_get_width)
{
    char *token;
    int right;
    int out;

    token = "d";
    right = 0;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);

    token = "05d";
    right = 5;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_trgt_print_uint)
{
    char target[500] = { 0 };
    for (int i = 0; i < 500; i++) {
        target[i] = 0;
    }

    unsigned int n;
    char *target_right;
    int right;
    int out;

    n = 8;
    target_right = "8";
    right = 1;
    out = s21_trgt_print_uint(target, n);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    n = 81;
    target_right = "81";
    right = 2;
    out = s21_trgt_print_uint(target, n);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_int_get_pow)
{
    int n;
    int pow;
    int right;
    int out;

    n = 10;
    pow = 0;
    right = 1;
    out = s21_int_get_pow(n, pow);
    ck_assert_int_eq(right, out);

    n = 10;
    pow = 1;
    right = 10;
    out = s21_int_get_pow(n, pow);
    ck_assert_int_eq(right, out);

    n = 10;
    pow = 2;
    right = 100;
    out = s21_int_get_pow(n, pow);
    ck_assert_int_eq(right, out);

    n = 10;
    pow = 5;
    right = 100000;
    out = s21_int_get_pow(n, pow);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_trgt_print_tokn_decim)
{
    char target[500] = { 0 };

    char *token;
    long tokn_decim;
    char *target_right;
    int right;
    int out;

    token = "d";
    tokn_decim = 115;
    target_right = "115";
    right = 3;
    out = s21_trgt_print_tokn_decim(target, token, tokn_decim);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    token = "d";
    tokn_decim = -115;
    target_right = "-115";
    right = 4;
    out = s21_trgt_print_tokn_decim(target, token, tokn_decim);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    token = "05d";
    tokn_decim = 91;
    target_right = "00091";
    right = 5;
    out = s21_trgt_print_tokn_decim(target, token, tokn_decim);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    token = "-05d";
    tokn_decim = 3;
    target_right = "3    ";
    right = 5;
    out = s21_trgt_print_tokn_decim(target, token, tokn_decim);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
}
END_TEST


Suite* s21_string_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("s21_string");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_s21_strstr);
    tcase_add_test(tc_core, test_s21_memchr);
    tcase_add_test(tc_core, test_s21_memcmp);
    tcase_add_test(tc_core, test_s21_memcpy);
    tcase_add_test(tc_core, test_s21_strlen);
    tcase_add_test(tc_core, test_s21_strpbrk);
    tcase_add_test(tc_core, test_s21_strtok);
    tcase_add_test(tc_core, test_s21_strerror);
    tcase_add_test(tc_core, test_s21_strcat);

    tcase_add_test(tc_core, test_s21_sprintf);
    tcase_add_test(tc_core, test_s21_udecim_get_str_len);
    tcase_add_test(tc_core, test_s21_frmt_is_tokn);
    tcase_add_test(tc_core, test_s21_tokn_skip_part);
    tcase_add_test(tc_core, test_s21_tokn_get_len);
    tcase_add_test(tc_core, test_s21_tokn_have_flag);
    tcase_add_test(tc_core, test_s21_tokn_get_width);
    tcase_add_test(tc_core, test_s21_trgt_print_uint);
    tcase_add_test(tc_core, test_s21_int_get_pow);
    tcase_add_test(tc_core, test_s21_trgt_print_tokn_decim);

    suite_add_tcase(s, tc_core);

    return s;
}

int main()
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
