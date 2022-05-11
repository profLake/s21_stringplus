
#include "../s21_string.h"

#include <check.h>
#include <stdlib.h>
#include <string.h>

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
  char *s1 = "This is a s21_memchr test";

  ck_assert_ptr_eq(s21_memchr(s1, 's', 0), memchr(s1, 's', 0));
  ck_assert_ptr_eq(s21_memchr(s1, 's', 2), memchr(s1, 's', 2));
  ck_assert_ptr_eq(s21_memchr(s1, 's', 50), memchr(s1, 's', 50));
  ck_assert_ptr_eq(s21_memchr(s1, 'u', 50), memchr(s1, 'u', 50));
  ck_assert_ptr_eq(s21_memchr(s1, 'u', 32), memchr(s1, 'u', 32));
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
  char *s1 = "This is a 1st string s21_memcmp test";
  char *s2 = "This is a 2nd string s21_memcmp test";

  ck_assert_msg(s21_memcmp(s1, s2, 256) == memcmp(s1, s2, 256),
                "1st memcmp test failed.");
  ck_assert_msg(s21_memcmp(s1, s2, 2) == memcmp(s1, s2, 2),
                "2nd memcmp test failed.");
  ck_assert_msg(s21_memcmp(s1, s2, 123) == memcmp(s1, s2, 123),
                "3rd memcmp test failed.");
  ck_assert_msg(s21_memcmp(s1, s2, 36) == memcmp(s1, s2, 36),
                "4rth memcmp test failed.");
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
  char *src1 = "schesrdsfdsfdsfesr";
  int len = s21_strlen(src1);
  char dest1[100] = {0};
  char dest2[100] = {0};
  char dest3[100] = {0};
  char dest4[100] = {0};
  char dest5[100] = {0};
  char dest6[100] = {0};
  char dest7[100] = {0};
  char dest8[100] = {0};
  char dest9[100] = {0};
  char dest10[100] = {0};

  s21_memcpy(dest1, src1, len + 1);
  memcpy(dest2, src1, len + 1);

  s21_memcpy(dest3, src1, 5);
  memcpy(dest4, src1, 5);

  s21_memcpy(dest5, src1, 0);
  memcpy(dest6, src1, 0);

  s21_memcpy(dest7, src1, 18);
  memcpy(dest8, src1, 18);

  s21_memcpy(dest9, src1, 1);
  memcpy(dest10, src1, 1);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest3, dest4);
  ck_assert_str_eq(dest5, dest6);
  ck_assert_str_eq(dest7, dest8);
  ck_assert_str_eq(dest9, dest10);
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
  char *src1 = "schesrdsfdsfdsfesr";
  int len = s21_strlen(src1);
  char dest1[100] = {0};
  char dest2[100] = {0};
  char dest3[100] = {0};
  char dest4[100] = {0};
  char dest5[100] = {0};
  char dest6[100] = {0};
  char dest7[100] = {0};
  char dest8[100] = {0};
  char dest9[100] = {0};
  char dest10[100] = {0};

  s21_memmove(dest1, src1, len + 1);
  memmove(dest2, src1, len + 1);

  s21_memmove(dest3, src1, 5);
  memmove(dest4, src1, 5);

  s21_memmove(dest5, src1, 0);
  memmove(dest6, src1, 0);

  s21_memmove(dest7, src1, 18);
  memmove(dest8, src1, 18);

  s21_memmove(dest9, src1, 1);
  memmove(dest10, src1, 1);

  ck_assert_msg(memcmp(dest1, dest2, len) == 0, "1st memmove test failed.");
  ck_assert_msg(memcmp(dest3, dest4, 5) == 0, "2nd memmove test failed.");
  ck_assert_msg(memcmp(dest5, dest6, 0) == 0, "3rd memmove test failed.");
  ck_assert_msg(memcmp(dest7, dest8, 18) == 0, "4rth memmove test failed.");
  ck_assert_msg(memcmp(dest9, dest10, 1) == 0, "5rth memmove test failed.");
}

END_TEST

START_TEST(test_memset) {
  char s1[] = "This is string.h library function";
  ck_assert_str_eq(s21_memset(s1, '$', 7), memset(s1, '$', 7));
  ck_assert_str_eq(s21_memset(s1, '$', 0), memset(s1, '$', 0));
  ck_assert_str_eq(s21_memset(s1, 7, 7), memset(s1, 7, 7));
  ck_assert_str_eq(s21_memset(s1, '\0', 7), memset(s1, '\0', 7));
  void *s21_mem = malloc(10);
  void *mem = malloc(10);
  s21_memset(s21_mem, '$', 10);
  memset(mem, '$', 10);
  ck_assert_mem_eq(s21_mem, mem, 10);
  free(mem);
  free(s21_mem);
  char str1[] = "School is cool";
  char str2[] = "School-21";
  char str3[] = "amogus";
  char str4[] = "This is a string!";
  char str5[] = "Shrek";
  char res1[] = "School is cool";
  char res2[] = "School-21";
  char res3[] = "amogus";
  char res4[] = "This is a string!";
  char res5[] = "Shrek";

  s21_memset(str1, '_', 5);
  s21_memset(str2, '_', 4);
  s21_memset(str3, 'M', 2);
  s21_memset(str4, '-', 1);
  s21_memset(str5, 'S', 1);

  memset(res1, '_', 5);
  memset(res2, '_', 4);
  memset(res3, 'M', 2);
  memset(res4, '-', 1);
  memset(res5, 'S', 1);

  ck_assert_msg(memcmp(str1, res1, sizeof(str1)) == 0,
                "1st memset test failed");
  ck_assert_msg(memcmp(str2, res2, sizeof(str2)) == 0,
                "2nd memset test failed");
  ck_assert_msg(memcmp(str3, res3, sizeof(str3)) == 0,
                "3rd memset test failed");
  ck_assert_msg(memcmp(str4, res4, sizeof(str4)) == 0,
                "4rth memset test failed");
  ck_assert_msg(memcmp(str5, res5, sizeof(str5)) == 0,
                "5rth memset test failed");
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
  char str1[21] = "TEST";
  char str2[8] = "strcat";
  char str3[9] = "function";
  char str4[1] = "";
  char str5[2] = " ";

  s21_strcat(str1, str5);
  ck_assert_msg(!memcmp(str1, "TEST ", 6), "1st strcat test failed");

  s21_strcat(str1, str2);
  ck_assert_msg(!memcmp(str1, "TEST strcat", 12), "2nd strcat test failed");

  s21_strcat(str1, str5);
  ck_assert_msg(!memcmp(str1, "TEST strcat ", 13), "3rd strcat test failed");

  s21_strcat(str1, str3);
  ck_assert_msg(!memcmp(str1, "TEST strcat function", 21),
                "4rth strcat test failed");

  s21_strcat(str1, str4);
  ck_assert_msg(!memcmp(str1, "TEST strcat function", 21),
                "5th strcat test failed");
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
  char str1[25] = "TEST";
  char str2[8] = "strncat";
  char str3[35] = "function";
  char str4[1] = "";
  char str5[30] = "amogus";

  s21_strncat(str1, str2, 3);
  ck_assert_msg(!memcmp(str1, "TESTstr", 8), "1st strncat test failed");

  s21_strncat(str1, str4, 3);
  ck_assert_msg(!memcmp(str1, "TESTstr", 8), "2nd strncat test failed");

  s21_strncat(str2, str4, 1);
  ck_assert_msg(!memcmp(str2, "strncat", 8), "3rd strncat test failed");

  s21_strncat(str5, str3, 3);
  ck_assert_msg(!memcmp(str5, "amogusfun", 10), "4rth strncat test failed");
}
END_TEST

START_TEST(test_strchr) {
  const char s1[] = "Doing some.tests here";
  char *empty = "";
  const char ch1 = '.';
  ck_assert_str_eq(s21_strchr(s1, ch1), strchr(s1, ch1));
  ck_assert_ptr_eq(s21_strchr(empty, ch1), strchr(empty, ch1));
  ck_assert_ptr_eq(s21_strchr(empty, 0), strchr(empty, 0));
  ck_assert_str_eq(s21_strchr(s1, ch1), ".tests here");
  char *str1 = "TEST";
  char *str2 = "strchr";
  char *str3 = "function";
  char *str4 = "";
  char *str5 = "amogus";
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_ptr_eq(s21_strchr(str2, 'E'), strchr(str2, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_ptr_eq(s21_strchr(str4, ' '), strchr(str4, ' '));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
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
  char t1[] = "Sample Text";
  char t2[] = "Sample Text Plus Some Text";
  ck_assert_msg(s21_strcmp(t1, t2) == -32, "1st strcmp test failed");

  char t3[] = "AAA";
  char t4[] = "B";
  ck_assert_msg(s21_strcmp(t3, t4) == -1, "2nd strcmp test failed");

  char t5[] = "A\0BCD";
  char t6[] = "A";
  ck_assert_msg(s21_strcmp(t5, t6) == 0, "3rd strcmp test failed");

  char t7[] = "amogus";
  char t8[] = "m";
  ck_assert_msg(s21_strcmp(t7, t8) == -12, "4rth strcmp test failed");

  char t9[] = "shrek";
  char t10[] = "as";
  ck_assert_msg(s21_strcmp(t9, t10) == 18, "5th strcmp test failed");

  char t11[] = "бг";
  char t12[] = "бг";
  ck_assert_msg(s21_strcmp(t11, t12) == 0, "5th strcmp test failed");
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
  char *t1 = "Sample Text";
  char *t2 = "Sample Text Plus Some Text";
  // int r1 = strncmp(t1, t2, 10);
  // int r2 = s21_strncmp(t1, t2, 10);
  ck_assert_msg(!s21_strncmp(t1, t2, 10) && !strncmp(t1, t2, 10),
                "1st strncmp test failed");
  // int r3 = strncmp(t1, t2, 14);
  // int r4 = s21_strncmp(t1, t2, 14);
  ck_assert_msg(s21_strncmp(t1, t2, 14) < 0 && strncmp(t1, t2, 14) < 0,
                "2nd strncmp test failed");
  char *t3 = "";
  char *t4 = "A";
  // int r5 = strncmp(t3, t4, 0);
  // int r6 = s21_strncmp(t3, t4, 0);
  ck_assert_msg(s21_strncmp(t3, t4, 0) == 0 && strncmp(t3, t4, 0) == 0,
                "3rd strncmp test failed");
  ck_assert_msg(s21_strncmp(t3, t4, 1) < 0 && strncmp(t3, t4, 1) < 0,
                "3rd strncmp test failed");
  char *t5 = "ShrekAmogus";
  char *t6 = "Shr";
  // int r7 = strncmp(t5, t6, 5);
  // int r8 = s21_strncmp(t5, t6, 5);
  ck_assert_msg(s21_strncmp(t5, t6, 5) > 0 && strncmp(t5, t6, 5) > 0,
                "4rth strncmp test failed");
  ck_assert_msg(s21_strncmp(t5, t6, 0) == 0 && strncmp(t5, t6, 0) == 0,
                "5th strncmp test failed");
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
  char s1[50] = "Sample Text";
  char d1[50] = "";
  s21_strcpy(d1, s1);
  ck_assert_msg(!strcmp(d1, s1), "1st  strcpy test failed");

  char s2[50] = "AAAAA";
  char d2[50] = "NO";
  s21_strcpy(d2, s2);
  ck_assert_msg(!strcmp(d2, s2), "2nd strcpy test failed");

  char s3[50] = "";
  char d3[50] = "HELLO";
  s21_strcpy(d3, s3);
  ck_assert_msg(!strcmp(d3, s3), "3rd strcpy test failed");

  char s4[50] = "amogus";
  char d4[50] = "HELLO";
  s21_strcpy(d4, s4);
  ck_assert_msg(!strcmp(d4, s4), "4rth strcpy test failed");

  char s5[50] = "Shrek";
  char d5[50] = "what";
  s21_strcpy(d5, s5);
  ck_assert_msg(!strcmp(d5, s5), "5th strcpy test failed");
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
  char s1[50] = "Sample Text";
  char d1[50] = "";
  s21_strncpy(d1, s1, 2);
  ck_assert_msg(!strcmp(d1, "Sa"), "1st strncpy test failed");

  char s2[50] = "AAAAA";
  char d2[50] = "NO";
  s21_strncpy(d2, s2, 0);
  ck_assert_msg(!strcmp(d2, "NO"), "2nd strncpy test failed");

  char s3[50] = "H";
  char d3[50] = "fELLO";
  s21_strncpy(d3, s3, 1);
  ck_assert_msg(!strcmp(d3, "HELLO"), "3rd strncpy test failed");

  char s4[50] = "amo";
  char d4[50] = "qwegus";
  s21_strncpy(d4, s4, 3);
  ck_assert_msg(!strcmp(d4, "amogus"), "4rth strncpy test failed");

  char s5[50] = "shrek";
  char d5[50] = "s";
  s21_strncpy(d5, s5, 5);
  ck_assert_msg(!strcmp(d5, "shrek"), "5th strncpy test failed");
}
END_TEST

START_TEST(test_strcspn) {
  const char s1[] = "ABCDEF4960910";
  const char s2[] = "013";
  const char s3[] = "J";
  const char s5[] = "609";
  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
  ck_assert_int_eq(s21_strcspn(s1, ""), strcspn(s1, ""));
  ck_assert_int_eq(s21_strcspn("", s2), strcspn("", s2));
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
  ck_assert_int_eq(s21_strcspn(s1, s3), strcspn(s1, s3));
  ck_assert_int_eq(s21_strcspn(s1, s5), strcspn(s1, s5));
  char *str1 = "0123456789";
  char *str2 = "9876";
  ck_assert_msg(s21_strcspn(str1, str2) == strcspn(str1, str2),
                "1st strcspn test failed");

  char *str3 = "0123456789";
  char *str4 = "";
  ck_assert_msg(s21_strcspn(str3, str4) == strcspn(str3, str4),
                "2nd strcspn test failed");

  char *str5 = "";
  char *str6 = "123";
  ck_assert_msg(s21_strcspn(str5, str6) == strcspn(str5, str6),
                "3rd strcspn test failed");

  char *str7 = "1337";
  char *str8 = "228";
  ck_assert_msg(s21_strcspn(str7, str8) == strcspn(str7, str8),
                "4rth strcspn test failed");

  char *str9 = "19642";
  char *str10 = "64";
  ck_assert_msg(s21_strcspn(str9, str10) == strcspn(str9, str10),
                "5th strcspn test failed");
}
END_TEST

START_TEST(test_strerror) {
  char *str1 = s21_strerror(20);
  char *str2 = strerror(20);
  ck_assert_str_eq(str1, str2);

  char *str3 = s21_strerror(12);
  char *str4 = strerror(12);
  ck_assert_str_eq(str3, str4);

  char *str5 = s21_strerror(1337);
  char *str6 = strerror(1337);
  ck_assert_str_eq(str5, str6);

  char *str7 = s21_strerror(1);
  char *str8 = strerror(1);
  ck_assert_str_eq(str7, str8);

  char *str9 = s21_strerror(25);
  char *str10 = strerror(25);
  ck_assert_str_eq(str9, str10);
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
  char *s1 = "0123456789";
  ck_assert_msg(s21_strlen(s1) == strlen(s1), "1st strlen test failed");

  char *s2 = "";
  ck_assert_msg(s21_strlen(s2) == strlen(s2), "2nd strlen test failed");

  char *s3 = "amogus";
  ck_assert_msg(s21_strlen(s3) == strlen(s3), "3rd strlen test failed");

  char *s4 = "shrek";
  ck_assert_msg(s21_strlen(s4) == strlen(s4), "4rth strlen test failed");

  char *s5 = "is love";
  ck_assert_msg(s21_strlen(s5) == strlen(s5), "5th strlen test failed");
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
  char *str = "hello";
  char *str2 = "hel";
  char *res1, *res2;
  res1 = s21_strpbrk(str, str2);
  res2 = strpbrk(str, str2);
  ck_assert_str_eq(res1, res2);

  char *str4 = "ab";
  res1 = s21_strpbrk(str, str4);
  res2 = strpbrk(str, str4);
  ck_assert_ptr_eq(res1, res2);

  char *str5 = "o";
  res1 = s21_strpbrk(str, str5);
  res2 = strpbrk(str, str5);
  ck_assert_str_eq(res1, res2);

  char *str6 = "abcdefghjkl";
  char *str7 = "abcd";
  res1 = s21_strpbrk(str6, str7);
  res2 = strpbrk(str6, str7);
  ck_assert_str_eq(res1, res2);

  char *str8 = "amogus is shrek?";
  char *str9 = "is";
  res1 = s21_strpbrk(str8, str9);
  res2 = s21_strpbrk(str8, str9);
  ck_assert_str_eq(res1, res2);
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
  char *s1 = "School-21";
  char *s2 = "";
  char *s3 = "amogus";

  ck_assert_msg(s21_strrchr(s1, 'm') == strrchr(s1, 'm'),
                "1st strrchr test failed");
  ck_assert_msg(s21_strrchr(s1, 'o') == strrchr(s1, 'o'),
                "2nd strrchr test failed");
  ck_assert_msg(s21_strrchr(s2, 'o') == strrchr(s2, 'o'),
                "3rd strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, ' ') == strrchr(s3, ' '),
                "4rth strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, 's') == strrchr(s3, 's'),
                "5th strrchr test failed");
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
  char *s1 = "School-21";
  char *s2 = "ho";
  char *s3 = "";

  ck_assert_msg(s21_strspn(s1, s2) == strspn(s1, s2), "1st strspn test failed");
  ck_assert_msg(s21_strspn(s3, s2) == strspn(s3, s2), "2nd strspn test failed");
  ck_assert_msg(s21_strspn(s2, s3) == strspn(s2, s3), "3rd strspn test failed");
  ck_assert_msg(s21_strspn(s1, s3) == strspn(s1, s3),
                "4rth strspn test failed");
  ck_assert_msg(s21_strspn(s3, s1) == strspn(s3, s1), "5th strspn test failed");
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
  ck_assert_ptr_eq(s21_strstr(haystack1, "Something"),
                   strstr(haystack1, "Something"));
  ck_assert_ptr_null(s21_strstr(haystack1, "Something"));
  ck_assert_ptr_eq(s21_strstr(haystack1, "\0"), strstr(haystack1, "\0"));
  char *s1 = "School-21";
  char *s2 = "ho";
  char *s3 = "";

  ck_assert_msg(s21_strstr(s1, s2) == strstr(s1, s2), "1st strstr test failed");
  ck_assert_msg(s21_strstr(s1, s3) == strstr(s1, s3), "2nd strstr test failed");
  ck_assert_msg(s21_strstr(s3, s2) == strstr(s3, s2), "3rd strstr test failed");
  ck_assert_msg(s21_strstr(s2, s3) == strstr(s2, s3),
                "4rth strstr test failed");
  ck_assert_msg(s21_strstr(s3, s1) == strstr(s3, s1), "5th strstr test failed");
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
  char test1[50] = "aboba,hello,world,trim";
  char test2[50] = "aboba,hello,world,trim";
  char delim1[10] = "123,";
  char *orig1, *copy1;
  orig1 = strtok(test1, delim1);
  copy1 = s21_strtok(test2, delim1);
  char orig_res1[1000] = {0};
  char copy_res1[1000] = {0};
  while (orig1 != NULL) {
    strcat(orig_res1, orig1);
    orig1 = strtok(NULL, delim1);
  }
  while (copy1 != NULL) {
    strcat(copy_res1, copy1);
    copy1 = s21_strtok(NULL, delim1);
  }
  ck_assert_str_eq(orig_res1, copy_res1);

  char str1[] = "School-21";
  char *tok1 = s21_strtok(str1, "-");
  char *tok2 = strtok(str1, "-");
  char *tok3 = s21_strtok(str1, "");
  char *tok4 = strtok(str1, "");
  char *tok5 = s21_strtok(str1, "oo");
  char *tok6 = strtok(str1, "oo");
  char *tok7 = s21_strtok(str1, "Sc");
  char *tok8 = strtok(str1, "Sc");
  char *tok9 = s21_strtok(str1, "21");
  char *tok10 = strtok(str1, "21");

  ck_assert_msg(!strcmp(tok1, tok2), "1st strtok test failed");
  ck_assert_msg(!strcmp(tok3, tok4), "2nd strtok test failed");
  ck_assert_msg(!strcmp(tok5, tok6), "3rd strtok test failed");
  ck_assert_msg(!strcmp(tok7, tok8), "4rth strtok test failed");
  ck_assert_msg(!strcmp(tok9, tok10), "5th strtok test failed");
}

START_TEST(to_upper_test) {
  char *s1 = "";
  char *s2 = "School is Cool";
  char *s3 = "amogus";
  char *s4 = "Shrek is amogus";
  char *s5 = "what";

  char *r1 = s21_to_upper(s1);
  char *r2 = s21_to_upper(s2);
  char *r3 = s21_to_upper(s3);
  char *r4 = s21_to_upper(s4);
  char *r5 = s21_to_upper(s5);

  ck_assert_str_eq(r1, "");
  ck_assert_str_eq(r2, "SCHOOL IS COOL");
  ck_assert_str_eq(r3, "AMOGUS");
  ck_assert_str_eq(r4, "SHREK IS AMOGUS");
  ck_assert_str_eq(r5, "WHAT");

  free(r1);
  free(r2);
  free(r3);
  free(r4);
  free(r5);
}
END_TEST

START_TEST(to_lower_test) {
  char s1[] = "SChOOl-21";
  char s2[] = "ScHool is CoOl";
  char s3[] = "amogus";
  char s4[] = "ShrEK is Amogus";
  char s5[] = "what";

  char *r1 = s21_to_lower(s1);
  char *r2 = s21_to_lower(s2);
  char *r3 = s21_to_lower(s3);
  char *r4 = s21_to_lower(s4);
  char *r5 = s21_to_lower(s5);

  ck_assert_msg(!strcmp(r1, "school-21"), "1st to_lower test failed");
  ck_assert_msg(!strcmp(r2, "school is cool"), "2nd to_lower test failed");
  ck_assert_msg(!strcmp(r3, "amogus"), "3rd to_lower test failed");
  ck_assert_msg(!strcmp(r4, "shrek is amogus"), "4rth to_lower test failed");
  ck_assert_msg(!strcmp(r5, "what"), "5th to_lower test failed");

  free(r1);
  free(r2);
  free(r3);
  free(r4);
  free(r5);
}
END_TEST

START_TEST(insert_test) {
  char *s1 = "School-21 test";
  char *s2 = "insert ";
  char *s3 = "amogus";
  char *s4 = "is";
  char *s5 = "shrek";
  char *res1 = s21_insert(s1, " ", 3);
  char *res2 = s21_insert(s5, s3, 5);
  char *res3 = s21_insert(s3, s5, 0);
  char *res4 = s21_insert(s5, s4, 5);
  char *res5 = s21_insert(s2, s1, 4);

  ck_assert_str_eq(res1, "Sch ool-21 test");
  ck_assert_str_eq(res2, "shrekamogus");
  ck_assert_str_eq(res3, "shrekamogus");
  ck_assert_str_eq(res4, "shrekis");
  ck_assert_str_eq(res5, "inseSchool-21 testrt ");

  free(res1);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
}
END_TEST

START_TEST(trim_test) {
  char *s1 = "School-21";
  char *s2 = "";
  char *s3 = "S";
  char *s4 = "Sch";
  char *s5 = "School";
  char *s6 = "School-21";
  char *s7 = NULL;
  char *r1 = s21_trim(s1, s2);
  char *r2 = s21_trim(s1, s3);
  char *r3 = s21_trim(s1, s4);
  char *r4 = s21_trim(s1, s5);
  char *r5 = s21_trim(s1, s6);
  char *r6 = s21_trim(s1, s7);
  ck_assert_msg(!strcmp(r1, "School-21"), "1st trim test failed");
  ck_assert_msg(!strcmp(r2, "chool-21"), "2nd trim test failed");
  ck_assert_msg(!strcmp(r3, "ool-21"), "3rd trim test failed");
  ck_assert_msg(!strcmp(r4, "-21"), "4rth trim test failed");
  ck_assert_msg(!strcmp(r5, ""), "5th trim test failed");
  ck_assert_msg(!strcmp(r6, "School-21"), "6th trim test failed");
  free(r1);
  free(r2);
  free(r3);
  free(r4);
  free(r5);
  free(r6);
}
END_TEST

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
  tcase_add_test(tc_core, to_upper_test);
  tcase_add_test(tc_core, to_lower_test);
  tcase_add_test(tc_core, insert_test);
  tcase_add_test(tc_core, trim_test);
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

