#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../s21_string.h"

#include <stdio.h>

START_TEST(test_s21_strcat)
{
    char str[15] = "Hi", str1[15] = "Hi", src[25] = "It's ", src1[25] = "It's ", pl[20] = "Please, be gentl",
    pl1[20] = "Please, be gentl";
    ck_assert_str_eq(s21_strcat(str, ", People!"),  strcat(str1, ", People!"));
    ck_assert_str_eq(s21_strcat(str, ""), strcat(str1, ""));
    ck_assert_str_eq(s21_strcat(src, "\0ur 1st\n\0team work"), strcat(src1, "\0ur 1st\n\0team work"));
    ck_assert_str_eq(s21_strcat(pl, "e"), strcat(pl1, "e"));
    ck_assert_str_eq(s21_strcat(pl, "e\0\n"), strcat(pl1, "e\0\n"));
    ck_assert_str_eq(s21_strcat(pl, "\0e\n"), strcat(pl1, "\0e\n"));
}
END_TEST

START_TEST(test_s21_memset)
{
    char str[30] = "____ zelenoglazoe taksi";
    char str1[30] = "____ zelenoglazoe taksi";

    ck_assert_str_eq(memset(str, 'O', 3), s21_memset(str1, 'O', 3));
    ck_assert_str_eq(memset(str, '0', 3), s21_memset(str1, '0', 3));
    ck_assert_str_eq(memset(str, 'g', 15), s21_memset(str1, 'g', 15));
    ck_assert_str_eq(memset(str, '\0', 20), s21_memset(str1, '\0', 20));
    ck_assert_str_eq(memset(str, '\n', 5), s21_memset(str1, '\n', 5));
    ck_assert_str_eq(memset(str, '.', 30), s21_memset(str1, '.', 30));
}
END_TEST

START_TEST(test_s21_memmove)
{
    char src[200] = "88, 89, 90";
    char src1[200] = "88, 89, 90";
    
    ck_assert_str_eq(memmove(src, "86, 87", 5), s21_memmove(src1, "86, 87", 5));
    ck_assert_str_eq(memmove(&src[5], "Q", 1), s21_memmove(&src1[5], "Q", 1));
    ck_assert_str_eq(memmove(&src[11], "\n\0!", 4), s21_memmove(&src1[11], "\n\0!", 4));
    ck_assert_str_eq(memmove(&src[0], "\0.)\0", 4), s21_memmove(&src1[0], "\0.)\0", 4));
    ck_assert_str_eq(memmove(&src[0], "One question... when it \0will end???TU!\n\0", 25), s21_memmove(&src1[0], "One question... when it \0will end???TU!\n\0", 25));
    ck_assert_str_eq(memmove(&src[25], "\0\nwill never gon\0 na be QA\n\0", 24), s21_memmove(&src1[0], "\0\nwill never gon\0 na be QA\n\0", 24));
}
END_TEST


START_TEST(test_s21_strchr)
{
    const char str[102] = "1234a5E,",  empt[] = "";
    ck_assert_ptr_eq(s21_strchr(str, '3'), strchr(str, '3'));
    ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
    ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
    ck_assert_ptr_eq(s21_strchr(empt, '4'), strchr(empt, '4'));
    ck_assert_ptr_eq(s21_strchr("ques\0\ntion", '\n'), strchr("ques\0\ntion", '\n'));
    ck_assert_ptr_eq(s21_strchr("1\0\n2", '2'), strchr("1\0\n2", '2'));
    ck_assert_ptr_eq(s21_strchr("\0i\02p", 'i'), strchr("\0i\02p", 'i'));
    
}
END_TEST

START_TEST(test_s21_strcpy)
{
    char sp[] = "ahh, so boring..", sp1[] = "ahh, so boring..";
    
    ck_assert_str_eq(s21_strcpy(sp, "sp"), strcpy(sp1, "sp"));
    ck_assert_str_eq(s21_strcpy(sp, "dc\0b"), strcpy(sp1, "dc\0b"));
    ck_assert_str_eq(s21_strcpy(sp, "WE12\0\n#@!yu."), strcpy(sp1, "WE12\0\n#@!yu."));
    ck_assert_str_eq(s21_strcpy(sp, "\0o012"), strcpy(sp1, "\0o012"));
    ck_assert_str_eq(s21_strcpy(sp, ""), strcpy(sp1, ""));
    ck_assert_str_eq(s21_strcpy(sp, "y\0\n"), strcpy(sp1, "y\0\n"));
    ck_assert_str_eq(s21_strcpy(sp, "\n0\0"), strcpy(sp1, "\n0\0"));
}
END_TEST

START_TEST(test_s21_strncpy)
{
    char str[28] = "So many test/000/ f*hh..", str1[28] = "So many test/000/ f*hh..", src[100] = "   /00never gonna give you up, never gonna let them down...", src1[10] = "", src11[2] = "",src2[9] = "/000/", src3[6] = "/0", src33[6] = "/0", src4[20] = "just like that";
    
    ck_assert_str_eq(s21_strncpy(src, str1, 28), strncpy(src, str, 28));
    ck_assert_str_eq(s21_strncpy(str1, src1, 4), strncpy(str, src1, 4));
    ck_assert_str_eq(s21_strncpy(src1, str1, 1), strncpy(src11, str, 1));
    ck_assert_str_eq(s21_strncpy(str1, src2, 5), strncpy(str, src2, 5));
    ck_assert_str_eq(s21_strncpy(src3, str1, 2), strncpy(src33, str, 2));
    ck_assert_str_eq(s21_strncpy(str1, src4, 16), strncpy(str, src4, 16));
    ck_assert_str_eq(s21_strncpy(str1, "3oi", 0), strncpy(str, "3oi", 0));
    ck_assert_str_eq(s21_strncpy(str1, "hhah\0\nheh", 10), strncpy(str, "hhah\0\nheh", 10));
    ck_assert_str_eq(s21_strncpy(str1, "\0hmm..\n", 7), strncpy(str, "\0hmm..\n", 7));
}
END_TEST

START_TEST(test_s21_strncat)
{
    char str[108] = "IT's fin,I p_se", str1[108] = "IT's fin,I p_se";
   char src[] = "Fi3", src1[] = "Fi3";
    ck_assert_str_eq(s21_strncat(str, "\0r\n", 7), strncat(str1, "\0r\n", 7));
    ck_assert_str_eq(s21_strncat(str, "0", 1), strncat(str1, "0", 1));
    ck_assert_str_eq(s21_strncat(str, "TU, s-ly", 12), strncat(str1, "TU, s-ly", 12));
    ck_assert_str_eq(s21_strncat(str, src, 3), strncat(str1, src1, 3));
    ck_assert_str_eq(s21_strncat(str, "\000/", 2), strncat(str1, "\000/", 2));
    ck_assert_str_eq(s21_strncat(str, "GAGA, rama", 10), strncat(str1, "GAGA, rama", 10));
    ck_assert_str_eq(s21_strncat(str, "\nOuPS", 10), strncat(str1, "\nOuPS", 10));
}
END_TEST

START_TEST(test_s21_strspn)
{
    char src[] = "WE ARE THE CHAMPIONS!", src1[] = "WE ", src2[] = "no we're not", src3[] = "oprs", src4[] = "sroopsrrops";
    
    ck_assert_int_eq(strspn(src,src1), s21_strspn(src, src1));
    ck_assert_int_eq(strspn(src,src2), s21_strspn(src, src2));
    ck_assert_int_eq(strspn(src4, src3), s21_strspn(src4, src3));
    ck_assert_int_eq(strspn("aaaaeeeerrrrAER", "aerB"), s21_strspn("aaaaeeeerrrrAER", "aerB"));
    ck_assert_int_eq(strspn(".!...!...??", "!."), s21_strspn(".!...!...??", "!."));
    ck_assert_int_eq(strspn("what?\n\0", "ahat\0"), s21_strspn("what?\n\0", "ahat\0"));
    ck_assert_int_eq(strspn("TheesaIm\n\0", "TheeSAImee\n\0"), s21_strspn("TheeSAImee\n\0", "TheesaIm\n\0"));
    ck_assert_int_eq(strspn("Z\0", "Z\0"), s21_strspn("Z\0", "Z\0"));
}
END_TEST

START_TEST(test_s21_strcspn)
{
    char str1[20] = "1234567890", str2[20] = "098", str[] = "edr";
    
    ck_assert_int_eq(strcspn(str1, str2),s21_strcspn(str1, str2));
    ck_assert_int_eq(strcspn(str, str2),s21_strcspn(str, str2));
    ck_assert_int_eq(strcspn(str, "EDR.;e"), s21_strcspn(str, "EDR.;e"));
    ck_assert_int_eq(strcspn("", "  "), s21_strcspn("", "  "));
    ck_assert_int_eq(strcspn("\00", "0"), s21_strcspn("\00", "0"));
    ck_assert_int_eq(strcspn("a\n", "a a"), s21_strcspn("a\n", "a a"));
    ck_assert_int_eq(strcspn("'wow\0\n", "'wow\0\n"), s21_strcspn("'wow\0\n", "'wow\0\n"));
    ck_assert_int_eq(strcspn("Oomph!\0\n", "0oh\0\n"), s21_strcspn("Oomph!\0\n", "0oh\0\n"));
}
END_TEST


START_TEST(test_s21_strcmp)
{
    const char *h = "h", *gh = "GHTH", *empty = "", *empty1 = "", *ichni = "1234SZR", *end = "\0", *end1 = "\0";
    ck_assert_int_eq(s21_strcmp(h, "!fvgb9876"), strcmp(h, "!fvgb9876"));
    ck_assert_int_eq(s21_strcmp(gh, "!.76"), strcmp(gh, "!.76"));
    ck_assert_int_eq(s21_strcmp(empty, "ryhEF"), strcmp(empty, "ryhEF"));
    ck_assert_int_eq(s21_strcmp(ichni, empty), strcmp(ichni, empty));
    ck_assert_int_eq(s21_strcmp("Sold it!", "Sold it!"), strcmp("Sold it!", "Sold it!"));
    ck_assert_int_eq(s21_strcmp(empty, empty1), strcmp(empty, empty1));
    ck_assert_int_eq(s21_strcmp(end, end1), strcmp(end, end1));
}
END_TEST

START_TEST(test_s21_to_upper)
{
    char *str = "hello", *stx = "HELLO";
    char *src = s21_to_upper(str);
    ck_assert_str_eq(src, stx);
}
END_TEST

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

    str1 = "Simpl";
    str2 = "Simple";
    ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));

}
END_TEST



START_TEST(test_s21_strncmp)
{
    char *h = "hello", *hr = "hellr", *p = "PRISE", *s = "shitty", *sh = "sh...", *shout = "shout, shout", *t = ".", *otchet = ".0123", *end = " endOFsPAACE", *empty = "";
    ck_assert_int_eq(s21_strncmp(h, hr, 4), strncmp(h, hr, 4));
    ck_assert_int_eq(s21_strncmp(h, hr, 5), strncmp(h, hr, 5));
    ck_assert_int_eq(s21_strncmp(hr, hr, 5), strncmp(hr, hr, 5));
    ck_assert_int_eq(s21_strncmp(p, s, 5), strncmp(p, s, 5));
    ck_assert_int_eq(s21_strncmp(sh, shout, 5), strncmp(sh, shout, 5));
    ck_assert_int_eq(s21_strncmp(t, otchet, 3), strncmp(t, otchet, 3));
    ck_assert_int_eq(s21_strncmp(empty, end, 1), strncmp(empty, end, 1));
}
END_TEST

START_TEST(test_s21_trim)
{
    char nine[20] = "1 2", str[20] = "1 aaaa  1", corr[20] = "aaaa";
    char *new = s21_trim(str, nine);
    ck_assert_str_eq(new, corr);

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
    tcase_add_test(tc_core, test_s21_memset);
    tcase_add_test(tc_core, test_s21_memmove);
    tcase_add_test(tc_core, test_s21_strcat);
    tcase_add_test(tc_core, test_s21_strncat);
    tcase_add_test(tc_core, test_s21_strspn);
    tcase_add_test(tc_core, test_s21_strcspn);
    tcase_add_test(tc_core, test_s21_strchr);
    tcase_add_test(tc_core, test_s21_strcmp);
    tcase_add_test(tc_core, test_s21_strncmp);
    tcase_add_test(tc_core, test_s21_strcpy);
    tcase_add_test(tc_core, test_s21_strncpy);
    tcase_add_test(tc_core, test_s21_trim);
    tcase_add_test(tc_core, test_s21_to_upper);
    tcase_add_test(tc_core,  test_s21_strstr);
       
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
