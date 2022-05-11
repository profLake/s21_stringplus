
#include "../s21_string.h"
#include <stdlib.h>
#include <string.h>
#include <check.h>

START_TEST(test_memchr) {
    char str[] = "Hello, how are you?";
    char *empty = "";
    ck_assert_ptr_eq(s21_memchr(str, 'h', 3), memchr(str, 'h', 3));
    ck_assert_ptr_eq(s21_memchr(str, 'l', 1), memchr(str, 'l', 1));
    ck_assert_ptr_eq(s21_memchr(str, 'h', 0), memchr(str, 'h', 0));
    ck_assert_ptr_eq(s21_memchr("h", 'h', 3), memchr("h", 'h', 3));
    ck_assert_ptr_eq(s21_memchr(str, 500, 2), memchr(str, 500, 2));
    ck_assert_ptr_eq(s21_memchr(empty, 500, 1), memchr(empty, 500, 1));
    ck_assert_ptr_eq(s21_memchr(empty, 'l', 10), memchr(empty, 'l', 10));
}
END_TEST

START_TEST(test_memcmp) {
    unsigned char str1[] = "1, 2, 3, 4, 5, 6, 7, 8, 9";
    unsigned char str2[] = "1, 2, 3, 4, 5, 6, 7, 8, 9";
    ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
    ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
    ck_assert_int_eq(s21_memcmp(str1, "", 10), memcmp(str1, "", 10));
    ck_assert_int_eq(s21_memcmp("", str2, 10), memcmp("", str2, 10));
    ck_assert_int_eq(s21_memcmp("", "", 10), memcmp("", "", 10));
    unsigned char str3[] = "1, 2, 3, 4, 6, 6, 7, 8, 9";
    unsigned char str4[] = "1, 2, 3, 4, 5, 6, 7, 8, 9";
    ck_assert_int_eq(s21_memcmp(str3, str4, 10), memcmp(str3, str4, 10));
    unsigned char str5[] = "1, 2, 3, 4, 6, 6, 7, 8, 9";
    unsigned char str6[] = "1, 2, 3, 4, 7, 6, 7, 8, 9";
    ck_assert_int_eq(s21_memcmp(str5, str6, 10), memcmp(str5, str6, 10));
    unsigned char str7[] = "1, 2, 3, 4, 6, 6, 7, 8, 9";
    unsigned char str8[] = "1, 2, 3, 4, 7, 6, 7";
    ck_assert_int_eq(s21_memcmp(str7, str8, 10), memcmp(str7, str8, 10));
    ck_assert_int_eq(s21_memcmp(str8, str7, 10), memcmp(str8, str7, 10));
    unsigned char str9[] = "1, 3, 4";
    unsigned char str10[] = "1, 2, 3";
    ck_assert_int_eq(s21_memcmp(str9, str10, 10), memcmp(str9, str10, 10));
}
END_TEST

START_TEST(test_memcpy) {
    char dst1[] = "32123";
    char str1[] = "12367";
    ck_assert_str_eq(s21_memcpy(dst1, str1, 5), memcpy(dst1, str1, 5));
    ck_assert_str_eq(s21_memcpy(dst1, str1, 0), memcpy(dst1, str1, 0));
    ck_assert_str_eq(s21_memcpy("", "", 0), memcpy("", "", 0));
    char dst2[] = "32123dfgdf";
    char str2[] = "12367";
    ck_assert_str_eq(s21_memcpy(dst2, str2, 5), memcpy(dst2, str2, 5));
    char dst3[] = "32123";
    char str3[] = "12367asdfg";
    ck_assert_str_eq(s21_memcpy(dst3, str3, 5), memcpy(dst3, str3, 5));
    void *s21_mem = malloc(10);
    void *mem = malloc(10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 10);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(test_memmove) {
    char dst1[10] = "OldText";
    char str1[10] = "NewText";
    ck_assert_str_eq(s21_memmove(dst1, str1, 8), memmove(dst1, str1, 8));
    ck_assert_str_eq(s21_memmove(dst1, str1, 0), memmove(dst1, str1, 0));
    ck_assert_str_eq(s21_memmove(dst1, "", 0), memmove(dst1, "", 0));
    ck_assert_str_eq(s21_memmove("", str1, 0), memmove("", str1, 0));
    ck_assert_str_eq(s21_memmove("", "", 0), memmove("", "", 0));
    void *s21_mem = malloc(5);
    void *mem = malloc(10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 5);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(test_memset) {
    char str1[] = "This is string.h library function";
    ck_assert_str_eq(s21_memset(str1, '$', 7), memset(str1, '$', 7));
    ck_assert_str_eq(s21_memset(str1, '$', 0), memset(str1, '$', 0));
    ck_assert_str_eq(s21_memset(str1, 7, 7), memset(str1, 7, 7));
    ck_assert_str_eq(s21_memset(str1, '\0', 7), memset(str1, '\0', 7));
    void *s21_mem = malloc(10);
    void *mem = malloc(10);
    s21_memset(s21_mem, '$', 10);
    memset(mem, '$', 10);
    ck_assert_mem_eq(s21_mem, mem, 10);
    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(test_strcat) {
    char src1[150] = "This is source";
    char dest1[150] = "This is destination";
    char *empty = "";
    ck_assert_str_eq(strcat(src1, dest1), strcat(src1, dest1));
    ck_assert_str_eq(s21_strcat(src1, "\0"), strcat(src1, "\0"));
    ck_assert_str_eq(s21_strcat(src1, "\n"), strcat(src1, "\n"));
    ck_assert_str_eq(s21_strcat(src1, empty), strcat(src1, empty));
}
END_TEST

START_TEST(test_strncat) {
    char src1[50] = "This is source";
    char dest1[50] = "This is destination";
    ck_assert_str_eq(s21_strncat(src1, dest1, 5), strncat(src1, dest1, 5));
    ck_assert_str_eq(s21_strncat(src1, "", 5), strncat(src1, "", 5));
    ck_assert_str_eq(s21_strncat(src1, "\n", 5), strncat(src1, "\n", 5));
    ck_assert_str_eq(s21_strncat(src1, "", 0), strncat(src1, "", 0));
    ck_assert_str_eq(s21_strncat(src1, "\n", 0), strncat(src1, "\n", 0));
    ck_assert_str_eq(s21_strncat(src1, dest1, 0), strncat(src1, dest1, 0));
}
END_TEST

START_TEST(test_strchr) {
    const char str1[] = "Doing some.tests here";
    char *empty = "";
    const char ch1 = '.';
    ck_assert_str_eq(s21_strchr(str1, ch1), strchr(str1, ch1));
    ck_assert_ptr_eq(s21_strchr(empty, ch1), strchr(empty, ch1));
    ck_assert_ptr_eq(s21_strchr(empty, 0), strchr(empty, 0));
    ck_assert_str_eq(s21_strchr(str1, ch1), ".tests here");
}
END_TEST

START_TEST(test_strcmp) {
    char str1[15] = "abcdef";
    char str2[15] = "ABCDEF";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
    ck_assert_int_eq(s21_strcmp(str1, ""), strcmp(str1, ""));
    ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));
    ck_assert_int_eq(s21_strcmp("", str2), strcmp("", str2));
    ck_assert_int_eq(s21_strcmp(str1, "ab"), strcmp(str1, "ab"));
    ck_assert_int_eq(s21_strcmp("ab", str2), strcmp("ab", str2));
    ck_assert_int_eq(s21_strcmp("4321", "1234"), 3);
}
END_TEST

START_TEST(test_strncmp) {
    char str1[15] = "abcdef";
    char str2[15] = "ABCDEF";
    ck_assert_int_eq(s21_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
    ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
    ck_assert_int_eq(s21_strncmp(str1, "", 3), strncmp(str1, "", 3));
    ck_assert_int_eq(s21_strncmp("", "", 3), strncmp("", "", 3));
    ck_assert_int_eq(s21_strncmp("", str2, 3), strncmp("", str2, 3));
    ck_assert_int_eq(s21_strncmp("4321", "1234", 3), 3);
    ck_assert_int_eq(s21_strncmp(str1, "ab", 2), strncmp(str1, "ab", 2));
    ck_assert_int_eq(s21_strncmp("ab", str2, 2), strncmp("ab", str2, 2));
    ck_assert_int_eq(s21_strncmp("ab", str2, 2), strncmp("ab", str2, 2));
    ck_assert_int_eq(s21_strncmp("ab", "ABCDEF", 4), strncmp("ab", "ABCDEF", 4));
}
END_TEST

START_TEST(test_strcpy) {
    char src1[104] = "This is for strcpy";
    char *s21_dest = malloc(10);
    char dest1[104];
    ck_assert_str_eq(s21_strcpy(dest1, ""), strcpy(dest1, ""));
    ck_assert_str_eq(s21_strcpy(dest1, src1), strcpy(dest1, src1));
    ck_assert_str_eq(s21_strcpy(s21_dest, src1), src1);
    ck_assert_str_eq(s21_strcpy(s21_dest, ""), s21_dest);
    free(s21_dest);
}
END_TEST

START_TEST(test_strncpy) {
    char src1[104] = "This is for strncpy";
    char *s21_dest = malloc(10);
    char dest1[104];
    ck_assert_str_eq(s21_strncpy(dest1, "", 7), strncpy(dest1, "", 7));
    ck_assert_str_eq(s21_strncpy(dest1, src1, 7), strncpy(dest1, src1, 7));
    ck_assert_str_eq(s21_strncpy(dest1, src1, 0), strncpy(dest1, src1, 0));
    ck_assert_str_eq(s21_strncpy(dest1, "", 0), strncpy(dest1, "", 0));
    ck_assert_str_eq(s21_strncpy(s21_dest, src1, 7), "This is");
    ck_assert_str_eq(s21_strncpy(s21_dest, src1, 0), "");
    ck_assert_str_eq(s21_strncpy(s21_dest, "", 7), s21_dest);
    ck_assert_str_eq(s21_strncpy(s21_dest, "", 0), s21_dest);
    free(s21_dest);
}
END_TEST

START_TEST(test_strcspn) {
    const char str1[] = "ABCDEF4960910";
    const char str2[] = "013";
    const char str3[] = "J";
    const char str4[] = "609";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    ck_assert_int_eq(s21_strcspn(str1, ""), strcspn(str1, ""));
    ck_assert_int_eq(s21_strcspn("", str2), strcspn("", str2));
    ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
    ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));
    ck_assert_int_eq(s21_strcspn(str1, str4), strcspn(str1, str4));
}
END_TEST

START_TEST(test_strerror) {
    for (int i = -5; i <= 155; i++) {
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
}
END_TEST

START_TEST(test_strlen) {
    char str[] = "Hello";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
    ck_assert_int_eq(s21_strlen(str), 5);
    ck_assert_int_eq(s21_strlen(""), strlen(""));
    ck_assert_int_eq(s21_strlen(""), 0);
    ck_assert_int_eq(s21_strlen("Hola \n"), strlen("Hola \n"));
    ck_assert_int_eq(s21_strlen("Hola \0"), strlen("Hola \0"));
}
END_TEST

START_TEST(test_strpbrk) {
    const char str1[] = "abcde2fghi3jk4l";
    const char *empty = "";
    ck_assert_ptr_eq(s21_strpbrk(str1, "34"), strpbrk(str1, "34"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "abcd"), strpbrk(str1, "abcd"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "ABCD"), strpbrk(str1, "ABCD"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "a"), strpbrk(str1, "a"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "3"), strpbrk(str1, "3"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "000"), strpbrk(str1, "000"));
    ck_assert_ptr_eq(s21_strpbrk(str1, empty), strpbrk(str1, empty));
    ck_assert_ptr_null(s21_strpbrk(str1, empty));
    ck_assert_ptr_eq(s21_strpbrk(empty, "34"), strpbrk(empty, "34"));
    ck_assert_ptr_eq(s21_strpbrk(empty, empty), strpbrk(empty, empty));
}
END_TEST

START_TEST(test_strrchr) {
    const char str1[] = "Some.words.for.the.test";
    const char ch1 = '.';
    ck_assert_str_eq(s21_strrchr(str1, ch1), strrchr(str1, ch1));
    ck_assert_str_eq(s21_strrchr(str1, ch1), ".test");
    ck_assert_ptr_eq(s21_strrchr(str1, '-'), strrchr(str1, '-'));
    ck_assert_ptr_null(s21_strrchr(str1, '-'));
    ck_assert_ptr_eq(s21_strrchr(str1, 0), strrchr(str1, 0));
    ck_assert_ptr_eq(s21_strrchr("", '-'), strrchr("", '-'));
}
END_TEST

START_TEST(test_strspn) {
    const char str1[] = "ABCDEFG019874";
    ck_assert_int_eq(s21_strspn(str1, "ABCD"), strspn(str1, "ABCD"));
    ck_assert_int_eq(s21_strspn(str1, "19"), strspn(str1, "19"));
    ck_assert_int_eq(s21_strspn(str1, "Hola!"), strspn(str1, "Hola!"));
    ck_assert_int_eq(s21_strspn(str1, "F!"), strspn(str1, "F!"));
    ck_assert_int_eq(s21_strspn(str1, "\0"), strspn(str1, "\0"));
    ck_assert_int_eq(s21_strspn(str1, ""), strspn(str1, ""));
    ck_assert_int_eq(s21_strspn("", str1), strspn("", str1));
    ck_assert_int_eq(s21_strspn("", ""), strspn("", ""));
}
END_TEST

START_TEST(test_strstr) {
    const char haystack1[30] = "TutorialsPointYouGotThePoint";
    const char needle1[10] = "Point";
    const char *empty = "";
    ck_assert_str_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));
    ck_assert_str_eq(s21_strstr(haystack1, empty), strstr(haystack1, empty));
    ck_assert_ptr_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));
    ck_assert_ptr_eq(s21_strstr(haystack1, empty), strstr(haystack1, empty));
    ck_assert_ptr_eq(s21_strstr(empty, haystack1), strstr(empty, haystack1));
    ck_assert_ptr_eq(s21_strstr(empty, empty), strstr(empty, empty));
    ck_assert_ptr_eq(s21_strstr(haystack1, "Something"), strstr(haystack1, "Something"));
    ck_assert_ptr_null(s21_strstr(haystack1, "Something"));
    ck_assert_ptr_eq(s21_strstr(haystack1, "\0"), strstr(haystack1, "\0"));
}
END_TEST

START_TEST(test_strtok) {
    char str[20] = "Hello.World";
    char delim[20] = ".";
    char *empty = "";
    ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
    ck_assert_str_eq(s21_strtok(str, delim), "Hello");
    ck_assert_str_eq(s21_strtok(str, "\0"), strtok(str, "\0"));
    ck_assert_str_eq(s21_strtok(str, "asdf"), strtok(str, "asdf"));
    ck_assert_str_eq(s21_strtok(str, "1234"), strtok(str, "1234"));
    ck_assert_str_eq(s21_strtok(str, empty), strtok(str, empty));
    ck_assert_ptr_eq(s21_strtok(empty, empty), strtok(empty, empty));
    ck_assert_ptr_eq(s21_strtok(empty, delim), strtok(empty, delim));
    ck_assert_ptr_null(s21_strtok(empty, delim));
}
END_TEST


Suite *strlen_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_strlen");
  tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memmove);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strcat);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strcmp);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strcpy);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strerror);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strspn);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = strlen_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
