#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "../s21_string.h"
#include <stdarg.h>

#include <stdio.h>


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
    s21_memcpy(dest, "hello", 5);
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

START_TEST(test_s21_strerror)
{
    ck_assert_str_eq(s21_strerror(1), strerror(1));
    ck_assert_str_eq(s21_strerror(ENOSYS), strerror(ENOSYS));
    ck_assert_str_eq(s21_strerror(EEXIST), strerror(EEXIST));
    //ck_assert_str_eq(s21_strerror(ENOTUNIQ), strerror(ENOTUNIQ));
    /*  ****ENOTUNIQ --- only on linux */
}
END_TEST

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
    char str[28] = "So many test/000/ f*hh..",
         str1[28] = "So many test/000/ f*hh..",
         //src[100] = "   /00never gonna give you up, never gonna let them down...",
         // src[100] = "..." --- превышает 80 символов
         src1[10] = "",
         src11[2] = "",
         src2[9] = "/000/",
         src3[6] = "/0",
         src33[6] = "/0",
         src4[20] = "just like that";
    
    //ck_assert_str_eq(s21_strncpy(src, str1, 28), strncpy(src, str, 28));
    /*  ****src[100] закомментирован */
    ck_assert_str_eq(s21_strncpy(str1, src1, 4), strncpy(str, src1, 4));
    ck_assert_str_eq(s21_strncpy(src1, str1, 1), strncpy(src11, str, 1));
    ck_assert_str_eq(s21_strncpy(str1, src2, 5), strncpy(str, src2, 5));
    ck_assert_str_eq(s21_strncpy(src3, str1, 2), strncpy(src33, str, 2));
    ck_assert_str_eq(s21_strncpy(str1, src4, 16), strncpy(str, src4, 16));
    //ck_assert_str_eq(s21_strncpy(str1, "3oi", 0), strncpy(str, "3oi", 0));
    /*  ****error: ‘strncpy’ destination unchanged after copying no bytes from
     *      a string of length 3
     */
    ck_assert_str_eq(s21_strncpy(str1, "hhah\0\nheh", 10), strncpy(str, "hhah\0\nheh", 10));
    ck_assert_str_eq(s21_strncpy(str1, "\0hmm..\n", 7), strncpy(str, "\0hmm..\n", 7));
}
END_TEST

START_TEST(test_s21_strncat)
{
    char str[108] = "IT's fin,I p_se", str1[108] = "IT's fin,I p_se";
   char src[] = "Fi3", src1[] = "Fi3";
    ck_assert_str_eq(s21_strncat(str, "\0r\n", 7), strncat(str1, "\0r\n", 7));
    //ck_assert_str_eq(s21_strncat(str, "0", 1), strncat(str1, "0", 1));
    /* ****error: ‘strncat’ specified bound 1 equals source length */
    ck_assert_str_eq(s21_strncat(str, "TU, s-ly", 12), strncat(str1, "TU, s-ly", 12));
    ck_assert_str_eq(s21_strncat(str, src, 3), strncat(str1, src1, 3));
    ck_assert_str_eq(s21_strncat(str, "\000/", 2), strncat(str1, "\000/", 2));
    //ck_assert_str_eq(s21_strncat(str, "GAGA, rama", 10), strncat(str1, "GAGA, rama", 10));
    /* ****error: ‘strncat’ specified bound 10 equals source length */
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
    const char *h = "h",
          *gh = "GHTH",
          *empty = "",
          *empty1 = "",
          *ichni = "1234SZR",
          *end = "\0", *end1 = "\0";
    ck_assert_int_eq(s21_strcmp(h, "!fvgb9876"), strcmp(h, "!fvgb9876"));
    ck_assert_int_eq(s21_strcmp(gh, "!.76"), strcmp(gh, "!.76"));
    ck_assert_int_eq(s21_strcmp(empty, "ryhEF"), strcmp(empty, "ryhEF"));
    ck_assert_int_eq(s21_strcmp(ichni, empty), strcmp(ichni, empty));
    ck_assert_int_eq(s21_strcmp("Sold it!", "Sold it!"),
            strcmp("Sold it!", "Sold it!"));
    ck_assert_int_eq(s21_strcmp(empty, empty1), strcmp(empty, empty1));
    ck_assert_int_eq(s21_strcmp(end, end1), strcmp(end, end1));
}
END_TEST

START_TEST(test_s21_strncmp)
{
    char h[10] = "hello", *hr = "hellr", *p = "PRISE", *s = "shitty", *sh = "sh...", *shout = "shout, shout", *t = ".", *otchet = ".0123", *end = " endOFsPAACE", *empty = "";
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
    const char *nine = "1 2", *str = "1 aaaa  1";
    char * new = s21_trim(str, nine);
    char *right = "aaaa";
    ck_assert_str_eq(new, right);
    free(new);
}
END_TEST

START_TEST(test_s21_insert)
{
    char * q = "aaabbbccc", * k = "baz", * qk = "aaabazbbbccc", * p = " ",
    * qp = "aaab bbccc";
    char * new = s21_insert(q, k, 3);
    char * new1 = s21_insert(q, p, 4);
    char * new3 = s21_insert(q, p, 11);
    ck_assert_str_eq(new, qk);
    free(new);
    ck_assert_str_eq(new1, qp);
    free(new1);
    ck_assert_ptr_eq(new3, s21_NULL);
    free(new3);
}
END_TEST

START_TEST(test_s21_sprintf)
{
    char buff[500];
    char buff_right[500];

    char *format;
    int right;
    int out;

    format = "hello, %c !";
//  buff_right = "hello, r !";
    right = sprintf(buff_right, format, 'r');
    out = s21_sprintf(buff, format, 'r');
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%c'!";
//  buff_right = "hello, 'r'!";
    right = sprintf(buff_right, format, 'r', 149);
    out = s21_sprintf(buff, format, 'r', 149);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%d'!";
//  buff_right = "hello, '115'!";
    right = sprintf(buff_right, format, 115);
    out = s21_sprintf(buff, format, 115);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%d'!";
//  buff_right = "hello, '-119'!";
    right = sprintf(buff_right, format, -119);
    out = s21_sprintf(buff, format, -119);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%05d'!";
//  buff_right = "hello, '00003'!";
    right = sprintf(buff_right, format, 3);
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%-05d'!";
//  buff_right = "hello, '3    '!";
    right = sprintf(buff_right, format, 3);
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%-+05d'!";
//  buff_right = "hello, '+3   '!";
    right = sprintf(buff_right, format, 3);
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%u'!";
//  buff_right = "hello, '3'!";
    right = sprintf(buff_right, format, 3);
    out = s21_sprintf(buff, format, 3);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%u'!";
//  buff_right = "hello, '4294967290'!";
    right = sprintf(buff_right, format, -6);
    out = s21_sprintf(buff, format, -6);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%05u'!";
//  buff_right = "hello, '00005'!";
    right = sprintf(buff_right, format, 5);
    out = s21_sprintf(buff, format, 5);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '% 5u'!";
//  buff_right = "hello, '    5'!";
    right = sprintf(buff_right, format, 5);
    out = s21_sprintf(buff, format, 5);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%%'!";
//  buff_right = "hello, '%'!";
    right = sprintf(buff_right, format, 9);
    /*  9 --- без этого sprintf может стать целью эксплойта.
     *      ****тебе следует защититься от этого
     */
    out = s21_sprintf(buff, format);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%s'!";
//  buff_right = "hello, 'A Telegram'!";
    right = sprintf(buff_right, format, "A Telegram");
    out = s21_sprintf(buff, format, "A Telegram");
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%lu'!";
    right = sprintf(buff_right, format, 99999999199);
    out = s21_sprintf(buff, format, 99999999199);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%080u'!";
    right = sprintf(buff_right, format, 4);
    out = s21_sprintf(buff, format, 4);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%08f'!";
    right = sprintf(buff_right, format, 2.13);
    out = s21_sprintf(buff, format, 2.13);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%-03f'!";
    right = sprintf(buff_right, format, -8.16);
    out = s21_sprintf(buff, format, -8.16);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%-09f'!";
    right = sprintf(buff_right, format, -8.16);
    out = s21_sprintf(buff, format, -8.16);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%0*f'!";
    right = sprintf(buff_right, format, 8, 10.45);
    out = s21_sprintf(buff, format, 8, 10.45);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%0*f' and also '%d'!";
    right = sprintf(buff_right, format, 12, 10.45, 112);
    out = s21_sprintf(buff, format, 12, 10.45, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%*.*f' and also '%d'!";
    right = sprintf(buff_right, format, 12, 4, 10.45, 112);
    out = s21_sprintf(buff, format, 12, 4, 10.45, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%f' and also '%d'!";
    right = sprintf(buff_right, format, 15, 4);
    out = s21_sprintf(buff, format, 15, 4);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    /*
    format = "hello, '%*.*Lf' and also '%d'!";
    right = sprintf(buff_right, format, 12, 4, 10.45, 112);
    out = s21_sprintf(buff, format, 12, 4, 10.45, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);
    */
    /*  ****Наш s21_sprintf вед>т себя при такой ошибке иначе. */

    format = "hello, '%*.*Lf' and also '%d'!";
    right = sprintf(buff_right, format, 12, 4, (long double)10.45, 112);
    out = s21_sprintf(buff, format, 12, 4, (long double)10.45, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    /*
    format = "hello, '%.50Lf' and also '%d'!";
    right = sprintf(buff_right, format, (long double)1/3, 112);
    out = s21_sprintf(buff, format, (long double)1/3, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%.50Lf' and also '%d'!";
    right = sprintf(buff_right, format, (long double)1/3 + 5, 112);
    out = s21_sprintf(buff, format, (long double)1/3 + 5, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);
    */
    /* Известная ошибка в точности */

    format = "hello, '%p' and also '%d'!";
    right = sprintf(buff_right, format, &right, 112);
    out = s21_sprintf(buff, format, &right, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%20p' and also '%d'!";
    right = sprintf(buff_right, format, &right, 112);
    out = s21_sprintf(buff, format, &right, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%e' and also '%d'!";
    right = sprintf(buff_right, format, 45.98, 112);
    out = s21_sprintf(buff, format, 45.98, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%E' and also '%d'!";
    right = sprintf(buff_right, format, 45.98, 112);
    out = s21_sprintf(buff, format, 45.98, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%*.*E' and also '%d'!";
    right = sprintf(buff_right, format, 9, 3, 45.98, 112);
    out = s21_sprintf(buff, format, 9, 3, 45.98, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%*x' and also '%d'!";
    right = sprintf(buff_right, format, 9, 14, 112);
    out = s21_sprintf(buff, format, 9, 14, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%#*x' and also '%d'!";
    right = sprintf(buff_right, format, 9, 14, 112);
    out = s21_sprintf(buff, format, 9, 14, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%*X' and also '%d'!";
    right = sprintf(buff_right, format, 9, 14, 112);
    out = s21_sprintf(buff, format, 9, 14, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%#*X' and also '%d'!";
    right = sprintf(buff_right, format, 9, 14, 112);
    out = s21_sprintf(buff, format, 9, 14, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%o' and also '%d'!";
    right = sprintf(buff_right, format, -9, 112);
    out = s21_sprintf(buff, format, -9, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    format = "hello, '%#*o' and also '%d'!";
    right = sprintf(buff_right, format, 9, 14, 112);
    out = s21_sprintf(buff, format, 9, 14, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(right, out);

    int hint;
    int hint_right;

    format = "hello, '%o' %n*hinted* and also '%d'!";
    hint_right = 12;
    right = sprintf(buff_right, format, 9, &hint, 112);
    out = s21_sprintf(buff, format, 9, &hint, 112);
    ck_assert_str_eq(buff_right, buff);
    ck_assert_int_eq(hint_right, hint);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_base_unum_get_str_len)
{
    unsigned long n;
    char *base;
    int right;
    int out;

    n = 19;
    base = DIGITS;
    right = 2;
    out = s21_base_unum_get_str_len(n, base);
    ck_assert_int_eq(right, out);

    n = 199;
    base = DIGITS;
    right = 3;
    out = s21_base_unum_get_str_len(n, base);
    ck_assert_int_eq(right, out);

    n = 294967290;
    base = DIGITS;
    right = 9;
    out = s21_base_unum_get_str_len(n, base);
    ck_assert_int_eq(right, out);

    n = 99999999999;
    base = DIGITS;
    right = 11;
    out = s21_base_unum_get_str_len(n, base);
    ck_assert_int_eq(right, out);

    n = 110; /* 6e */
    base = BASE16LOW;
    right = 2;
    out = s21_base_unum_get_str_len(n, base);
    ck_assert_int_eq(right, out);

    n = 9; /* 9 */
    base = BASE16LOW;
    right = 1;
    out = s21_base_unum_get_str_len(n, base);
    ck_assert_int_eq(right, out);

    n = 91; /* 5b */
    base = BASE16LOW;
    right = 2;
    out = s21_base_unum_get_str_len(n, base);
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

    str = "%*.*f";
    right = 1;
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
   
    token  = "0*.*f";
    i = 4;
    right = token + 4;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
   
    token  = "i";
    i = 2;
    right = token + 1;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);
   
    token  = ".05d";
    i = 2;
    right = token + 0;
    out = s21_tokn_skip_part(token, i);
    ck_assert_ptr_eq(right, out);

    token = "%*.*f";
    i = 2;
    right = token + 1;
    out = s21_tokn_skip_part(token, i);
    ck_assert_str_eq(right, out);
}
END_TEST

START_TEST(test_s21_tokn_get_str_len)
{
    char * token;
    int right;
    int out;

    token = "d";
    right = 1;
    out = s21_tokn_get_str_len(token);
    ck_assert_int_eq(right, out);

    token = "c";
    right = 1;
    out = s21_tokn_get_str_len(token);
    ck_assert_int_eq(right, out);

    token = ".5f";
    right = 3;
    out = s21_tokn_get_str_len(token);
    ck_assert_int_eq(right, out);

    token = "*.*f";
    right = 4;
    out = s21_tokn_get_str_len(token);
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
    right = -1;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);

    token = "00d";
    right = -1;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);

    token = "05d";
    right = 5;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);

    token = "ld";
    right = -1;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);

    token = "*ld";
    right = -2;
    out = s21_tokn_get_width(token);
    ck_assert_int_eq(right, out);
}
END_TEST

/*
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
*/

START_TEST(test_s21_ulong_get_pow)
{
    int n;
    int pow;
    int right;
    int out;

    n = 10;
    pow = 0;
    right = 1;
    out = s21_ulong_get_pow(n, pow);
    ck_assert_int_eq(right, out);

    n = 10;
    pow = 1;
    right = 10;
    out = s21_ulong_get_pow(n, pow);
    ck_assert_int_eq(right, out);

    n = 10;
    pow = 2;
    right = 100;
    out = s21_ulong_get_pow(n, pow);
    ck_assert_int_eq(right, out);

    n = 10;
    pow = 5;
    right = 100000;
    out = s21_ulong_get_pow(n, pow);
    ck_assert_int_eq(right, out);
}
END_TEST

int vatest_s21_trgt_print_tokn_num(char *target, const char *token, ...) {
    va_list args;
    va_start(args, token);
    int result;
    result =s21_trgt_print_tokn_num(target, token, &args);
    va_end(args);
    return result;
}
START_TEST(test_s21_trgt_print_tokn_num)
{
    char target[500] = { 0 };

    char *token;
    char *target_right;
    int right;
    int out;

    token = "d";
    target_right = "115";
    right = 3;
    out = vatest_s21_trgt_print_tokn_num(target, token, 115);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "d";
    target_right = "-115";
    right = 4;
    out = vatest_s21_trgt_print_tokn_num(target, token, -115);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "05d";
    target_right = "00091";
    right = 5;
    out = vatest_s21_trgt_print_tokn_num(target, token, 91);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "-05d";
    target_right = "3    ";
    right = 5;
    out = vatest_s21_trgt_print_tokn_num(target, token, 3);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "-05i";
    target_right = "3    ";
    right = 5;
    out = vatest_s21_trgt_print_tokn_num(target, token, 3);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "ld";
    target_right = "8";
    right = 1;
    out = vatest_s21_trgt_print_tokn_num(target, token, 8);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "o";
    target_right = "12";
    right = 2;
    out = vatest_s21_trgt_print_tokn_num(target, token, 10);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);
}
END_TEST

START_TEST(test_s21_to_lower)
{
    char str[20] = "HELLO";
    char stx[20] = "hello";
    char *src = s21_to_lower(str);
    ck_assert_str_eq(src, stx);
}
END_TEST

START_TEST(test_s21_to_upper)
{
    char str[20] = "hello";
    char stx[20] = "HELLO";
    char *src = s21_to_upper(str);
    ck_assert_str_eq(src, stx);
}
END_TEST

/*
START_TEST(test_s21_trgt_print_tokn_str)
{
    char target[500];
    char *target_right;

    char *token;
    char *tokn_str;

    int right;
    int out;

    token = "s";
    tokn_str = "A Telegram";
    target_right = "A Telegram";
    right = 10;
    out = s21_trgt_print_tokn_str(target, token, tokn_str);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    token = "30s";
    tokn_str = "A Telegram";
    target_right = "                    A Telegram";
    right = 30;
    out = s21_trgt_print_tokn_str(target, token, tokn_str);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    token = ".30s";
    tokn_str = "A Telegram";
    target_right = "A Telegram";
    right = 10;
    out = s21_trgt_print_tokn_str(target, token, tokn_str);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    token = "-30s";
    tokn_str = "A Telegram";
    target_right = "A Telegram                    ";
    right = 30;
    out = s21_trgt_print_tokn_str(target, token, tokn_str);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
}
END_TEST
*/  // The func is changed after these times

START_TEST(test_s21_trgt_print_ulong)
{
    char target[500] = { 0 };
    char *target_right;

    unsigned long n;

    int right;
    int out;

    target_right = "98";
    n = 98;
    right = 2;
    out = s21_trgt_print_ulong(target, n);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);

    target_right = "99999999999";
    n = 99999999999;
    right = 11;
    out = s21_trgt_print_ulong(target, n);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(test_s21_trgt_print_uldouble)
{
    char target[500] = { 0 };
    char *target_right;

    long double ld;
    int precis_len;
    int right;
    int out;

    ld = 51.52;
    target_right = "51.520";
    precis_len = 3;
    right = 6;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);

    ld = 51.52;
    target_right = "51.52000";
    precis_len = 5;
    right = 8;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);

    ld = 51.52;
    target_right = "51.5";
    precis_len = 1;
    right = 4;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);

    ld = 51;
    target_right = "51";
    precis_len = 0;
    right = 2;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);

    ld = 0.3;
    target_right = "0.30000";
    precis_len = 5;
    right = 7;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);

    /*
    long double ld;

    ld = (long double)1/3;
    target_right = "0.33333333333333333334236835143737920361672877334058";
    precis_len = 50;
    right = 52;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);
    */
    /* Известная ошибка в точности */

    /*
    ld = 15;
    target_right = "0.000000";
    precis_len = 6;
    right = 8;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);
    */
    /* Известная ошибка в принятии int как float. */

    ld = 0;
    target_right = "0.000000";
    precis_len = 6;
    right = 8;
    out = s21_trgt_print_uldouble(target, ld, precis_len);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(out, right);
    memset(target, 0, 500);
}
END_TEST

int vatest_s21_trgt_print_tokn_ratio(char *target, char *token, ...) {
    va_list args;
    va_start(args, token);
    int result = s21_trgt_print_tokn_ratio(target, token, &args);
    va_end(args);
    return result;
}
START_TEST(test_s21_trgt_print_tokn_ratio)
{
    char target[500] = {0};
    char *target_right;

    char *token;

    int right;
    int out;

    token = "0*.*f";
    target_right = "0000000000015.45";
    right = 16;
    out = vatest_s21_trgt_print_tokn_ratio(target, token, 16, 2, 15.45);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "*.*f";
    target_right = "           15.45";
    right = 16;
    out = vatest_s21_trgt_print_tokn_ratio(target, token, 16, 2, 15.45);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "*.*e";
    target_right = "            1.54e+01";
    right = 20;
    out = vatest_s21_trgt_print_tokn_ratio(target, token, 20, 2, 15.45);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "*.*E";
    target_right = "            1.54E+01";
    right = 20;
    out = vatest_s21_trgt_print_tokn_ratio(target, token, 20, 2, 15.45);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    token = "f";
    target_right = "0.000000";
    right = 8;
    out = vatest_s21_trgt_print_tokn_ratio(target, token, 0.0);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);
}
END_TEST

START_TEST(test_s21_trgt_print_base_ulong)
{
    char target[500] = {0};
    unsigned long n;
    char *base;
    char *target_right;
    int right;
    int out;

    n = 11;
    base = BASE16LOW;
    target_right = "b";
    right = 1;
    out = s21_trgt_print_base_ulong(target, n, base);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    n = 14;
    base = BASE16LOW;
    target_right = "e";
    right = 1;
    out = s21_trgt_print_base_ulong(target, n, base);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    n = 11;
    base = BASE2;
    target_right = "1011";
    right = 4;
    out = s21_trgt_print_base_ulong(target, n, base);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    n = 171616;
    base = BASE16LOW;
    target_right = "29e60";
    right = 5;
    out = s21_trgt_print_base_ulong(target, n, base);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);

    n = 10;
    base = BASE8;
    target_right = "12";
    right = 2;
    out = s21_trgt_print_base_ulong(target, n, base);
    ck_assert_str_eq(target, target_right);
    ck_assert_int_eq(right, out);
    memset(target, 0, 500);
}
END_TEST

int vatest_s21_trgt_print_tokn_ptr(char *target, const char *token, ...) {
    int result;
    va_list args;
    va_start(args, token);
    result = s21_trgt_print_tokn_ptr(target, token, &args);
    va_end(args);
    return result;
}
START_TEST(test_s21_trgt_print_tokn_ptr)
{
    char target[500];
    char *token;
    char target_right[500];
    int right;
    int out;
    
    token = "p";
    right = sprintf(target_right, "%p", &right);
    out = vatest_s21_trgt_print_tokn_ptr(target, token, &right);
    ck_assert_str_eq(target_right, target);
    ck_assert_int_eq(right, out);
}
END_TEST

// THE BEGINNING OF SEVEN THOUSAND SPRINTF UNIT_TEST FILE

START_TEST(SPRINTFTestLaslhyn1) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", 1, 1);
    sprintf(data1, "|%0*.*%|\n", 1, 1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn2) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", 12, 0);
    sprintf(data1, "|%0*.*%|\n", 12, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn3) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", 0, 10);
    sprintf(data1, "|%0*.*%|\n", 0, 10);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn4) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", 0, 0);
    sprintf(data1, "|%0*.*%|\n", 0, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn5) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*%|\n", -12, -15);
    sprintf(data1, "|%*.*%|\n", -12, -15);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn6) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*%|\n", -12, -15);
    sprintf(data1, "|%*.*%|\n", -12, -15);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn7) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*%|\n", 12, -15);
    sprintf(data1, "|%*.*%|\n", 12, -15);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn8) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.%|\n", -12);
    sprintf(data1, "|%*.%|\n", -12);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn9) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0.*%|\n", -12);
    sprintf(data1, "|%0.*%|\n", -12);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn10) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*%|\n", -12);
    sprintf(data1, "|%0*%|\n", -12);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn11) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", -12, -5);
    sprintf(data1, "|%0*.*%|\n", -12, -5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn12) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", -12, -15);
    sprintf(data1, "|%0*.*%|\n", -12, -15);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn13) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", -12, -1);
    sprintf(data1, "|%0*.*%|\n", -12, -1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn14) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", -1, -5);
    sprintf(data1, "|%0*.*%|\n", -1, -5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn15) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", -1, -1);
    sprintf(data1, "|%0*.*%|\n", -1, -1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn16) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", -12, 0);
    sprintf(data1, "|%0*.*%|\n", -12, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn17) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", 0, -10);
    sprintf(data1, "|%0*.*%|\n", 0, -10);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn18) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*%|\n", 0, 0);
    sprintf(data1, "|%0*.*%|\n", 0, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn19) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-05%|\n");
    sprintf(data1, "|%-05%|\n");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn20) {
    char data[100];
    char data1[100];
    int a1 = sprintf(data, "|%20% this is good|\n");
    int b1 = s21_sprintf(data1, "|%20% this is good|\n");
    ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn21) {
    char data[100];
    char data1[100];
    int a1 = sprintf(data, "|%020% this is good|\n");
    int b1 = s21_sprintf(data1, "|%020% this is good|\n");
    ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn22) {
    char data[100];
    char data1[100];
    sprintf(data, "|%32s|\n", "111");
    s21_sprintf(data1, "|%32s|\n", "111");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn23) {
    char data[100];
    char data1[100];
    sprintf(data, "|%32s|\n", "abc");
    s21_sprintf(data1, "|%32s|\n", "abc");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn24) {
    char data[100];
    char data1[100];
    sprintf(data, "|%-32s|\n", "abc");
    s21_sprintf(data1, "|%-32s|\n", "abc");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn25) {
    char data[100];
    char data1[100];
    sprintf(data, "|%16s|\n", "nark nark");
    s21_sprintf(data1, "|%16s|\n", "nark nark");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn26) {
    char data[100];
    char data1[100];
    sprintf(data, "|%16s|\n", "nark nark");
    s21_sprintf(data1, "|%16s|\n", "nark nark");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn27) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%.03s|\n", "hello");
    int d = sprintf(data1, "|%.03s|\n", "hello");
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn28) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%.3s| kushat nado |%20s|\n", "MneEEEEEEEEE", "arbuz");
    int d = sprintf(data1, "|%.3s| kushat nado |%20s|\n", "MneEEEEEEEEE", "arbuz");
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn29) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%08.5X|\n", 0);
    int d = sprintf(data1, "|%08.5X|\n", 0);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn30) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%03.7d|\n", -2375);
    int d = sprintf(data1, "|%03.7d|\n", -2375);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn31) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%-20.18u|\n", -345);
    int d = sprintf(data1, "|%-20.18u|\n", -345);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn32) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%-20.18d|\n", -345);
    int d = sprintf(data1, "|%-20.18d|\n", -345);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn33) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%020.2d|\n", -345);
    int d = sprintf(data1, "|%020.2d|\n", -345);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn34) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%020d|\n", -345);
    int d = sprintf(data1, "|%020d|\n", -345);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn35) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|%%|\n");
    int d = sprintf(data1, "|%%|\n");
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn36) {
    char data[100];
    char data1[100];
    int a, b;
    int c = s21_sprintf(data, "%----24p et hello %2p %12p\n", &a, &b, NULL);
    int d = sprintf(data1, "%----24p et hello %2p %12p\n", &a, &b, NULL);
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn37) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|test %-12i et %24s !|\n", 0, "coco");
    int d = sprintf(data1, "|test %-12i et %24s !|\n", 0, "coco");
    ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn38) {
    char data[100];
    char data1[100];
    int c = s21_sprintf(data, "|test %-12i et %--2.4d %24s !|\n", 0, 25, "coco");
    int d = sprintf(data1, "|test %-12i et %--2.4d %24s !|\n" , 0, 25, "coco");
    ck_assert_int_eq(c, d);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn39) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%c|\n", 'a');
    sprintf(data1, "01)SPRINTF : |%c|\n", 'a');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn40) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-c|\n", 'z');
    sprintf(data1, "01)SPRINTF : |%-c|\n", 'z');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn41) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-----c|\n", '!');
    sprintf(data1, "01)SPRINTF : |%-----c|\n", '!');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn42) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%5c|\n", 'R');
    sprintf(data1, "01)SPRINTF : |%5c|\n", 'R');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn43) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-5c|\n", 'R');
    sprintf(data1, "01)SPRINTF : |%-5c|\n", 'R');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn44) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%1c|\n", '3');
    sprintf(data1, "01)SPRINTF : |%1c|\n", '3');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn45) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%c|\n", '\0');
    sprintf(data1, "01)SPRINTF : |%c|\n", '\0');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn46) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%5c|\n", '\0');
    sprintf(data1, "01)SPRINTF : |%5c|\n", '\0');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn47) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-5c|\n", '\0');
    sprintf(data1, "01)SPRINTF : |%-5c|\n", '\0');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn48) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%1c|\n", '\0');
    sprintf(data1, "01)SPRINTF : |%1c|\n", '\0');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn49) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%s|\n", "salut");
    sprintf(data1, "01)SPRINTF : |%s|\n", "salut");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn50) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-s|\n", "test");
    sprintf(data1, "01)SPRINTF : |%-s|\n", "test");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn51) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%---------s|\n", "test2");
    sprintf(data1, "01)SPRINTF : |%---------s|\n", "test2");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn52) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%10s|\n", "42");
    sprintf(data1, "01)SPRINTF : |%10s|\n", "42");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn53) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-10s|\n", "42");
    sprintf(data1, "01)SPRINTF : |%-10s|\n", "42");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn54) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%2s|\n", "string");
    sprintf(data1, "01)SPRINTF : |%2s|\n", "string");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn55) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-2s|\n", "string");
    sprintf(data1, "01)SPRINTF : |%-2s|\n", "string");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn56) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%.15s|\n", "precision");
    sprintf(data1, "01)SPRINTF : |%.15s|\n", "precision");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn57) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%.4s|\n", "precision");
    sprintf(data1, "01)SPRINTF : |%.4s|\n", "precision");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn58) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%.0s|\n", "precision");
    sprintf(data1, "01)SPRINTF : |%.0s|\n", "precision");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn59) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%s|\n", "\0\0\0\0\0");
    sprintf(data1, "01)SPRINTF : |%s|\n", "\0\0\0\0\0");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn60) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%10s|\n", "\0\0\0\0\0");
    sprintf(data1, "01)SPRINTF : |%10s|\n", "\0\0\0\0\0");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn61) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%s|\n", "");
    sprintf(data1, "01)SPRINTF : |%s|\n", "");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn62) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-.2s|\n", "boom");
    sprintf(data1, "01)SPRINTF : |%-.2s|\n", "boom");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn63) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%10.8s|\n", "google");
    sprintf(data1, "01)SPRINTF : |%10.8s|\n", "google");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn64) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%10.2s|\n", "twitter");
    sprintf(data1, "01)SPRINTF : |%10.2s|\n", "twitter");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn65) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%2.10s|\n", "samsung");
    sprintf(data1, "01)SPRINTF : |%2.10s|\n", "samsung");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn66) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%2.5s|\n", "sprintf");
    sprintf(data1, "01)SPRINTF : |%2.5s|\n", "sprintf");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn67) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-10.2s|\n", "424242424242");
    sprintf(data1, "01)SPRINTF : |%-10.2s|\n", "424242424242");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn68) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%1.0s|\n", "123456789");
    sprintf(data1, "01)SPRINTF : |%1.0s|\n", "123456789");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn69) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-1.0s|\n", "123456789");
    sprintf(data1, "01)SPRINTF : |%-1.0s|\n", "123456789");
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn70) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%.1s|\n", "covid-19");
    sprintf(data1, "01)SPRINTF : |%.1s|\n", "covid-19");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn71) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%10.2s|\n", "covid-19");
    sprintf(data1, "01)SPRINTF : |%10.2s|\n", "covid-19");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn72) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%2.5s|\n", "covid-19");
    sprintf(data1, "01)SPRINTF : |%2.5s|\n", "covid-19");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn73) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%-10.2s|\n", "covid-19");
    sprintf(data1, "01)SPRINTF : |%-10.2s|\n", "covid-19");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn74) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01)SPRINTF : |%1.4s| et |%-6.8s| et |%4.2s|\n", "tuuu", "12345", "hu");
    sprintf(data1, "01)SPRINTF : |%1.4s| et |%-6.8s| et |%4.2s|\n", "tuuu", "12345", "hu");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn75) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "01) standart PRINTF : |%p|\n", "salut");
    sprintf(data1, "01) standart PRINTF : |%p|\n", "salut");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn76) {
    char data[100];
    char data1[100];
    int num1 = 0;
    s21_sprintf(data, "02) standart PRINTF : |%-p|\n", &num1);
    sprintf(data1, "02) standart PRINTF : |%-p|\n", &num1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn77) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%---------p|\n", "test2");
    sprintf(data1, "02) standart PRINTF : |%---------p|\n", "test2");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn78) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10p|\n", "21");
    sprintf(data1, "02) standart PRINTF : |%10p|\n", "21");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn79) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-10p|\n", "21");
    sprintf(data1, "02) standart PRINTF : |%-10p|\n", "21");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn80) {
    char data[100];
    char data1[100];
    int num1;
    s21_sprintf(data, "02) standart PRINTF : |%2p|\n", &num1);
    sprintf(data1, "02) standart PRINTF : |%2p|\n", &num1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn81) {
    char data[100];
    char data1[100];
    int num1;
    s21_sprintf(data, "02) standart PRINTF : |%-2p|\n", &num1);
    sprintf(data1, "02) standart PRINTF : |%-2p|\n", &num1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn82) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%p|\n", "\0\0\0\0\0");
    sprintf(data1, "02) standart PRINTF : |%p|\n", "\0\0\0\0\0");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn83) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%20p|\n", "\0\0\0\0\0");
    sprintf(data1, "02) standart PRINTF :|%20p|\n", "\0\0\0\0\0");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn84) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%p|\n", "");
    sprintf(data1, "02) standart PRINTF :|%p|\n", "");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn85) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%p|\n", NULL);
    sprintf(data1, "02) standart PRINTF :|%p|\n", NULL);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn86) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%10p|\n", NULL);
    sprintf(data1, "02) standart PRINTF :|%10p|\n", NULL);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn87) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%-10p|\n", NULL);
    sprintf(data1, "02) standart PRINTF :|%-10p|\n", NULL);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn88) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%1.1d|\n", -20);
    sprintf(data1, "02) standart PRINTF :|%1.1d|\n", -20);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn89) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%-10d|\n", -50);
    sprintf(data1, "02) standart PRINTF :|%-10d|\n", -50);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn90) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%2d|\n", -20);
    sprintf(data1, "02) standart PRINTF :|%2d|\n", -20);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn91) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%.2d|\n", -20);
    sprintf(data1, "02) standart PRINTF :|%.2d|\n", -20);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn92) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%d|\n", 42);
    sprintf(data1, "02) standart PRINTF :|%d|\n", 42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn93) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%i|\n", 42);
    sprintf(data1, "02) standart PRINTF :|%i|\n", 42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn94) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%-d|\n", 42);
    sprintf(data1, "02) standart PRINTF :|%-d|\n", 42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn95) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%10d|\n", 100);
    sprintf(data1, "02) standart PRINTF :|%10d|\n", 100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn96) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%-10d|\n", 100);
    sprintf(data1, "02) standart PRINTF :|%-10d|\n", 100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn97) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%.10d|\n", 100);
    sprintf(data1, "02) standart PRINTF :|%.10d|\n", 100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn98) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%10.5d|\n", 100);
    sprintf(data1, "02) standart PRINTF :|%10.5d|\n", 100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn99) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%5.10d|\n", 64);
    sprintf(data1, "02) standart PRINTF :|%5.10d|\n", 64);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn100) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%1.1d|\n", 16);
    sprintf(data1, "02) standart PRINTF :|%1.1d|\n", 16);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn101) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%d|\n", -42);
    sprintf(data1, "02) standart PRINTF :|%d|\n", -42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn102) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%10d|\n", -42);
    sprintf(data1, "02) standart PRINTF :|%10d|\n", -42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn103) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%.10d|\n", -42);
    sprintf(data1, "02) standart PRINTF :|%.10d|\n", -42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn104) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%10.5d|\n", -16);
    sprintf(data1, "02) standart PRINTF :|%10.5d|\n", -16);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn105) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%5.10d|\n", -16);
    sprintf(data1, "02) standart PRINTF :|%5.10d|\n", -16);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn106) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.2d|\n", -1);
    sprintf(data1, "02) standart PRINTF : |%.2d|\n", -1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn107) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-10d|\n", -80);
    sprintf(data1, "02) standart PRINTF : |%-10d|\n", -80);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn108) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-.10d|\n", -80);
    sprintf(data1, "02) standart PRINTF : |%-.10d|\n", -80);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn109) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%06d|\n", 35);
    sprintf(data1, "02) standart PRINTF : |%06d|\n", 35);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn110) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%06d|\n", -35);
    sprintf(data1, "02) standart PRINTF : |%06d|\n", -35);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn111) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%05.3d|\n", 5);
    sprintf(data1, "02) standart PRINTF : |%05.3d|\n", 5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn112) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%03.5d|\n", 5);
    sprintf(data1, "02) standart PRINTF : |%03.5d|\n", 5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn113) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%05.3d|\n", -5);
    sprintf(data1, "02) standart PRINTF : |%05.3d|\n", -5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn114) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%03.5d|\n", -5);
    sprintf(data1, "02) standart PRINTF : |%03.5d|\n", -5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn115) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.d|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%.d|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn116) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.d|\n", 100);
    sprintf(data1, "02) standart PRINTF : |%.d|\n", 100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn117) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%x|\n", 34);
    sprintf(data1, "02) standart PRINTF : |%x|\n", 34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn118) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%x|\n", -34);
    sprintf(data1, "02) standart PRINTF : |%x|\n", -34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn119) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-x|\n", 50);
    sprintf(data1, "02) standart PRINTF : |%-x|\n", 50);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn120) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10x|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%10x|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn121) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.10x|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%.10x|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn122) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15x|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%15x|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn123) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.15x|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%.15x|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn124) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10.5x|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%10.5x|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn125) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%5.10x|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%5.10x|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn126) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%20.15x|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%20.15x|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn127) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15.20x|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%15.20x|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn128) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-10x|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-10x|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn129) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-.10x|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-.10x|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn130) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-20x|\n", -20000000);
    sprintf(data1, "02) standart PRINTF : |%-20x|\n", -20000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn131) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%08x|\n", 64);
    sprintf(data1, "02) standart PRINTF : |%08x|\n", 64);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn132) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.x|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%.x|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn133) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.x|\n", 88);
    sprintf(data1, "02) standart PRINTF : |%.x|\n", 88);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn134) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%x| |%x|\n", (unsigned int)-1,  1);
    sprintf(data1, "02) standart PRINTF : |%x| |%x|\n", (unsigned int)-1, 1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn135) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%X|\n", 34);
    sprintf(data1, "02) standart PRINTF : |%X|\n", 34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn136) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%X|\n", 34);
    sprintf(data1, "02) standart PRINTF : |%X|\n", 34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn137) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%X|\n", -34);
    sprintf(data1, "02) standart PRINTF : |%X|\n", -34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn138) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-X|\n", 50);
    sprintf(data1, "02) standart PRINTF : |%-X|\n", 50);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn139) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10X|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%10X|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn140) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.10X|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%.10X|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn141) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15X|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%15X|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn142) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.15X|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%.15X|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn143) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10.5X|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%10.5X|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn144) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%5.10X|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%5.10X|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn145) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%20.15X|\n", 10000);
    sprintf(data1, "02) standart PRINTF : |%20.15X|\n", 10000);
    ck_assert_str_eq(data, data1);
}
END_TEST



START_TEST(SPRINTFTestLaslhyn146) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15.20X|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%15.20X|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn147) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-10X|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-10X|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn148) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-.10X|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-.10X|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn149) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-20X|\n", -20000000);
    sprintf(data1, "02) standart PRINTF : |%-20X|\n", -20000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn150) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%08X|\n", 64);
    sprintf(data1, "02) standart PRINTF : |%08X|\n", 64);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn151) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%03.4X|\n", 10);
    sprintf(data1, "02) standart PRINTF : |%03.4X|\n", 10);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn152) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.X|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%.X|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn153) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.X|\n", 88);
    sprintf(data1, "02) standart PRINTF : |%.X|\n", 88);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn154) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%X|\n", 2147483647);
    sprintf(data1, "02) standart PRINTF : |%X|\n", 2147483647);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn155) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%u|\n", 34);
    sprintf(data1, "02) standart PRINTF : |%u|\n", 34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn156) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%u|\n", -34);
    sprintf(data1, "02) standart PRINTF : |%u|\n", -34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn157) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-u|\n", 50);
    sprintf(data1, "02) standart PRINTF : |%-u|\n", 50);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn158) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10u|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%10u|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn159) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.10u|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%.10u|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn160) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15u|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%15u|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn161) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10.5u|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%10.5u|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn162) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%5.10u|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%5.10u|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn163) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%20.15u|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%20.15u|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn164) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15.20u|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%15.20u|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn165) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-10u|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-10u|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn166) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-.10u|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-.10u|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn167) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-20u|\n", -20000000);
    sprintf(data1, "02) standart PRINTF : |%-20u|\n", -20000000);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn168) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%08u|\n", 64);
    sprintf(data1, "02) standart PRINTF : |%08u|\n", 64);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn169) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%03.4u|\n", 10);
    sprintf(data1, "02) standart PRINTF : |%03.4u|\n", 10);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn170) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF :|%u|\n", 0);
    sprintf(data1, "02) standart PRINTF :|%u|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn171) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.u|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%.u|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn172) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10u|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%10u|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn173) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.u|\n", 88);
    sprintf(data1, "02) standart PRINTF : |%.u|\n", 88);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn174) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.*s|\n", 5, "bratok");
    sprintf(data1, "02) standart PRINTF : |%.*s|\n", 5, "bratok");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn175) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.*d|\n", 5, 5);
    sprintf(data1, "02) standart PRINTF : |%.*d|\n", 5, 5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn176) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.*d|\n", 5, 0);
    sprintf(data1, "02) standart PRINTF : |%.*d|\n", 5, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn177) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.3s|\n", "21");
    sprintf(data1, "02) standart PRINTF : |%.3s|\n", "21");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn178) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.3X|\n", 17);
    sprintf(data1, "02) standart PRINTF : |%.3X|\n", 17);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn179) {
    char data[100];
    char data1[100];
    char c;
    s21_sprintf(data, "|%s%d%p%%%i%u%x%X%c|\n", "bonjour", 42, &c, 42, 42, 42, 42, 'c');
    sprintf(data1, "|%s%d%p%%%i%u%x%X%c|\n", "bonjour", 42, &c, 42, 42, 42, 42, 'c');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn180) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%x|\n", -42);
    sprintf(data1, "|%x|\n", -42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn181) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%X|\n", -42);
    sprintf(data1, "|%X|\n", -42);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn182) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%lx|\n", 4294967296);
    sprintf(data1, "|%lx|\n", 4294967296);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn183) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%u|\n", -1);
    sprintf(data1, "|%u|\n", -1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn184) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%u|\n", -1);
    sprintf(data1, "|%u|\n", -1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn185) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%f|\n", 324.34);
    sprintf(data1, "|%f|\n", 324.34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn186) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10f|\n", 324.343);
    sprintf(data1, "|%10f|\n", 324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn187) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10.3f|\n", 324.343);
    sprintf(data1, "|%10.3f|\n", 324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn188) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%1.30f|\n", 324.343);
    sprintf(data1, "|%1.30f|\n", 324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn189) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-1.10f|\n", 324.343);
    sprintf(data1, "|%-1.10f|\n", 324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn190) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-1.10f|\n", -324.343);
    sprintf(data1, "|%-1.10f|\n", -324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn191) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%.10f|\n", -324.343);
    sprintf(data1, "|%.10f|\n", -324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn192) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%.10f|\n", 324.343);
    sprintf(data1, "|%.10f|\n", 324.343);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn193) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|% 10f|\n", 324.1);
    sprintf(data1, "|% 10f|\n", 324.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn194) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+10f|\n", 324.1);
    sprintf(data1, "|%+10f|\n", 324.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn195) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#10f|\n", 324.1);
    sprintf(data1, "|%#10f|\n", 324.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn196) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#10f|\n", 324.1123132);
    sprintf(data1, "|%#10f|\n", 324.1123132);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn197) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#10.15f|\n", 324.1123132);
    sprintf(data1, "|%#10.15f|\n", 324.1123132);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn198) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%.0f|\n", 324.1123132);
    sprintf(data1, "|%.0f|\n", 324.1123132);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn199) {
    //
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#10.0f|\n", 3.14);
    sprintf(data1, "|%#10.0f|\n", 3.14);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn200) {
    //
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10.10f|\n", 320.3);
    sprintf(data1, "|%10.10f|\n", 320.3);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn201) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-10.10f|\n", 320.3);
    sprintf(data1, "|%-10.10f|\n", 320.3);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn202) {
    //
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-10.10f|\n", 320.3);
    sprintf(data1, "|%-10.10f|\n", 320.3);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn203) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-10.10f|\n", -320.3);
    sprintf(data1, "|%-10.10f|\n", -320.3);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn204) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%.0f|\n", -320.3);
    sprintf(data1, "|%.0f|\n", -320.3);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn205) {
    char data[100];
    char data1[100];

    s21_sprintf(data, "|%.0f|\n", -320.3);
    sprintf(data1, "|%.0f|\n", -320.3);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn206) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%05.0f|\n", -320.3);
    sprintf(data1, "|%05.0f|\n", -320.3);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn207) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%05.0f|\n", 3.141592653589793);
    sprintf(data1, "|%05.0f|\n", 3.141592653589793);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn208) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%05.0f|\n", 3.141592653589793);
    sprintf(data1, "|%05.0f|\n", 3.141592653589793);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn209) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|% -5.1f|\n", 0.001);
    sprintf(data1, "|% -5.1f|\n", 0.001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn210) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%5.1f|\n", 324.324);
    sprintf(data1, "|%5.1f|\n", 324.324);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn211) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%5.3f|\n", 0.0001);
    sprintf(data1, "|%5.3f|\n", 0.0001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn212) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%5.*f|\n", 10 , 0.0001);
    sprintf(data1, "|%5.*f|\n", 10, 0.0001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn213) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%5.*f|\n", -10 , 0.0001);
    sprintf(data1, "|%5.*f|\n", -10, 0.0001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn214) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*f|\n", 23, -10 , 0.0001);
    sprintf(data1, "|%*.*f|\n", 23, -10, 0.0001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn215) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*f|\n", -23, -10 , 0.0001);
    sprintf(data1, "|%*.*f|\n", -23, -10, 0.0001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn216) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*f|\n", 0, -10 , 0.0001);
    sprintf(data1, "|%*.*f|\n", 0, -10, 0.0001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn217) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#x|\n", 123);
    sprintf(data1, "|%#x|\n", 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn218) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*x|\n", 10, 123);
    sprintf(data1, "|%#*x|\n", 10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn219) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*x|\n", 10, -123);
    sprintf(data1, "|%#*x|\n", 10, -123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn220) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*x|\n", -10, 123);
    sprintf(data1, "|%#*x|\n", -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn221) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.10x|\n", 10, 123);
    sprintf(data1, "|%#*.10x|\n", 10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn222) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*x|\n", 10, -10, 123);
    sprintf(data1, "|%#*.*x|\n", 10, -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn223) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*x|\n", 10, -10, 123);
    sprintf(data1, "|%0*.*x|\n", 10, -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn224) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*x|\n", 10, -10, 123);
    sprintf(data1, "|%*.*x|\n", 10, -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn225) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-*.*x|\n", 10, -10, 123);
    sprintf(data1, "|%-*.*x|\n", 10, -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST



START_TEST(SPRINTFTestLaslhyn226) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*x|\n", 10, -10, 123);
    sprintf(data1, "|%#*.*x|\n", 10, -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn227) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*x|\n", 10, -10, 123);
    sprintf(data1, "|%0*.*x|\n", 10, -10, 123);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn228) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*x|\n", 10, -10, 0);
    sprintf(data1, "|%*.*x|\n", 10, -10, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn229) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*x|\n", 10, -10, 0);
    sprintf(data1, "|%#*.*x|\n", 10, -10, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn230) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*x|\n", 10, -10, 0);
    sprintf(data1, "|%0*.*x|\n", 10, -10, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn231) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%g|\n", 10.1);
    sprintf(data1, "|%g|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn232) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%g|\n", 0.001);
    sprintf(data1, "|%g|\n", 0.001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn233) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10g|\n", 10.1);
    sprintf(data1, "|%10g|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn234) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10.5g|\n", 10.1);
    sprintf(data1, "|%10.5g|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn235) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10.5g|\n", 10.1);
    sprintf(data1, "|%10.5g|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn236) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#10.5g|\n", 10.1123213);
    sprintf(data1, "|%#10.5g|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn237) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|% 10.5g|\n", 10.1123213);
    sprintf(data1, "|% 10.5g|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn238) {
    //
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-10.5g|\n", 10.1123213);
    sprintf(data1, "|%-10.5g|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn239) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+10.5g|\n", 10.1123213);
    sprintf(data1, "|%+10.5g|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn240) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%010.5g|\n", 10.1123213);
    sprintf(data1, "|%010.5g|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn241) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%0*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn242) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%#*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn243) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|% *.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|% *.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn244) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%-*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn245) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%+*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn246) {
        char data[100];
         char data1[100];
         s21_sprintf(data, "|%+*.*g|\n", 10, 10, 0.0000001);
         sprintf(data1, "|%+*.*g|\n", 10, 10, 0.0000001);
         ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn247) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+#*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%+#*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn248) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%+*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn249) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*g|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%*.*g|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn250) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*o|\n", 10, -10, 0);
    sprintf(data1, "|%#*.*o|\n", 10, -10, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn251) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*o|\n", -10, -10, 0);
    sprintf(data1, "|%#*.*o|\n", -10, -10, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn252) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*o|\n", -10, -10, 0);
    sprintf(data1, "|%*.*o|\n", -10, -10, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn253) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*o|\n", -10, -10, -10);
    sprintf(data1, "|%*.*o|\n", -10, -10, -10);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn254) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*o|\n", 10, 10, -10);
    sprintf(data1, "|%*.*o|\n", 10, 10, -10);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn255) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*o|\n", 0, 0, 0);
    sprintf(data1, "|%*.*o|\n", 0, 0, 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn256) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*o|\n", 0, 0, -10);
    sprintf(data1, "|%*.*o|\n", 0, 0, -10);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn257) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%G|\n", 10.1);
    sprintf(data1, "|%G|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn258) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%G|\n", 0.001);
    sprintf(data1, "|%G|\n", 0.001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn259) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10G|\n", 10.1);
    sprintf(data1, "|%10G|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn260) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10.5G|\n", 10.1);
    sprintf(data1, "|%10.5G|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn261) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%10.5G|\n", 10.1);
    sprintf(data1, "|%10.5G|\n", 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn262) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#10.5G|\n", 10.1123213);
    sprintf(data1, "|%#10.5G|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn263) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|% 10.5G|\n", 10.1123213);
    sprintf(data1, "|% 10.5G|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn264) {
    //
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-10.5G|\n", 10.1123213);
    sprintf(data1, "|%-10.5G|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn265) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+10.5G|\n", 10.1123213);
    sprintf(data1, "|%+10.5G|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn266) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%010.5G|\n", 10.1123213);
    sprintf(data1, "|%010.5G|\n", 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn267) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%0*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%0*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn268) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%#*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%#*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn269) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|% *.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|% *.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn270) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%-*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%-*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn271) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%+*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn272) {
        char data[100];
        char data1[100];
        s21_sprintf(data, "|%+*.*G|\n", 10, 10, 0.0000001);
        sprintf(data1, "|%+*.*G|\n", 10, 10, 0.0000001);
        ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn273) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+#*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%+#*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn274) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%+*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%+*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn275) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "|%*.*G|\n", -10, -10, 10.1123213);
    sprintf(data1, "|%*.*G|\n", -10, -10, 10.1123213);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn276) {
    char data[100];
    char data1[100];
    int num;
    s21_sprintf(data, "%n", &num);
    sprintf(data1, "%n", &num);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn277) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%e", -0.1);
    sprintf(data1, "%e", -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn278) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10e", 332.34);
    sprintf(data1, "%#10e", 332.34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn279) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10.5e", 332.34);
    sprintf(data1, "%#10.5e", 332.34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn280) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", 10, 10, 10.1);
    sprintf(data1, "%#*.*e", 10, 10, 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn281) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", -10, -10, -10.1);
    sprintf(data1, "%#*.*e", -10, -10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn282) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", -10, 10, 10.1);
    sprintf(data1, "%#*.*e", -10, 10, 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn283) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", 10, -10, 10.1);
    sprintf(data1, "%#*.*e", 10, -10, 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn284) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", 10, 10, -10.1);
    sprintf(data1, "%#*.*e", 10, 10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn285) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", 10, -10, -10.1);
    sprintf(data1, "%#*.*e", 10, -10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn286) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", -10, 10, -10.1);
    sprintf(data1, "%#*.*e", -10, 10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn287) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*e", 0, 0, -0.1);
    sprintf(data1, "%#*.*e", 0, 0, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn288) {
    char data[100];
    char data1[100];
    float a = -0.1;
    s21_sprintf(data, "%#*.*e", 10, 10, a);
    sprintf(data1, "%+*.*e", 10, 10, a);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn289) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "% *.*e", 10, 10, -0.1);
    sprintf(data1, "% *.*e", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn290) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%+*.*e", 10, 10, -0.1);
    sprintf(data1, "%+*.*e", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn291) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%-*.*e", 10, 10, -0.1);
    sprintf(data1, "%-*.*e", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn292) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%0*.*e", 10, 10, -0.1);
    sprintf(data1, "%0*.*e", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn293) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%*.*e", 0, 0, -0.1);
    sprintf(data1, "%*.*e", 0, 0, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn294) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%E", 0.1);
    sprintf(data1, "%E", 0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn295) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10E", 332.34);
    sprintf(data1, "%#10E", 332.34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn296) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10.5E", 332.34);
    sprintf(data1, "%#10.5E", 332.34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn297) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 10, 10, 10.1);
    sprintf(data1, "%#*.*E", 10, 10, 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn298) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", -10, -10, -10.1);
    sprintf(data1, "%#*.*E", -10, -10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn299) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", -10, 10, 10.1);
    sprintf(data1, "%#*.*E", -10, 10, 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn300) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 10, -10, 10.1);
    sprintf(data1, "%#*.*E", 10, -10, 10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn301) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 10, 10, -10.1);
    sprintf(data1, "%#*.*E", 10, 10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn302) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 10, -10, -10.1);
    sprintf(data1, "%#*.*E", 10, -10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn303) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", -10, 10, -10.1);
    sprintf(data1, "%#*.*E", -10, 10, -10.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn304) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 0, 0, -0.1);
    sprintf(data1, "%#*.*E", 0, 0, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn305) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 10, 10, -0.1);
    sprintf(data1, "%+*.*E", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn306) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "% *.*E", 10, 10, -0.1);
    sprintf(data1, "% *.*E", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn307) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%+*.*E", 10, 10, -0.1);
    sprintf(data1, "%+*.*E", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn308) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%-*.*E", 10, 10, -0.1);
    sprintf(data1, "%-*.*E", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn309) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%0*.*E", 10, 10, -0.1);
    sprintf(data1, "%0*.*E", 10, 10, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn310) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%*.*E", 0, 0, -0.1);
    sprintf(data1, "%*.*E", 0, 0, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn311) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", 0, 0, -0.1);
    sprintf(data1, "%#*.*E", 0, 0, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn312) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%*.*E", 0, 4, -0.1);
    sprintf(data1, "%*.*E", 0, 4, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn313) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%*.*E", -7, 0, -0.1);
    sprintf(data1, "%*.*E", -7, 0, -0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn314) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%E", 1234.323);
    sprintf(data1, "%E", 1234.323);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn315) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10E", 1234.323);
    sprintf(data1, "%#10E", 1234.323);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn316) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10.3E", 1234.32333);
    sprintf(data1, "%#10.3E", 1234.32333);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn317) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10.2E", 1234.0000);
    sprintf(data1, "%#10.2E", 1234.0000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn318) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#10.*E", -5, 0.00001);
    sprintf(data1, "%#10.*E", -5, 0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn319) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", -5, -5, 0.00001);
    sprintf(data1, "%#*.*E", -5, -5, 0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn320) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#*.*E", -5, -5, -0.00001);
    sprintf(data1, "%#*.*E", -5, -5, -0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn321) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%0*.*E", -5, -5, -0.00001);
    sprintf(data1, "%0*.*E", -5, -5, -0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestLaslhyn322) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "% *.*E", -5, -5, -0.00001);
    sprintf(data1, "% *.*E", -5, -5, -0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn323) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%+#*.*E", -5, -5, -0.00001);
    sprintf(data1, "%+#*.*E", -5, -5, -0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn324) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "% #*.*E", -5, -5, 0.00001);
    sprintf(data1, "% #*.*E", -5, -5, 0.00001);
    ck_assert_str_eq(data, data1);
}
END_TEST


// MARK: - SPrintf tests by dogletho

START_TEST(SPRINTFTestdogletho1) {
    char str[100];
    char str1[100];
    int a = 10, b = 20, c;
    c = a + b;
    sprintf(str, "Sum of %d and %d is %d", a, b, c);
    s21_sprintf(str1, "Sum of %d and %d is %d", a, b, c);
    ck_assert_str_eq(str, str1);
    sprintf(str, "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is |%%|. And now unsigned: |%u|\n",
            "abra", 'e', 56, -43);
    s21_sprintf(str1, "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is |%%|. And now unsigned: |%u|\n",
                "abra", 'e', 56, -43);
    ck_assert_str_eq(str, str1);
    sprintf(str, "Sum of %d and %d is %d", a, b, c);
    s21_sprintf(str1, "Sum of %d and %d is %d", a, b, c);
}
END_TEST

// --------------General check-------------
START_TEST(SPRINTFTestdogletho2) {
    char str[100];
    char str1[100];
    sprintf(str, "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is |%%|. And now unsigned: |%u|\n",
            "abra", 'e', 56, -43);
    s21_sprintf(str1, "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is |%%|. And now unsigned: |%u|\n",
                "abra", 'e', 56, -43);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho3) {
    char str[100];
    char str1[100];
    sprintf(str, "and now heximal: |%8x|, |%X|\n", 5554645, -123);
    s21_sprintf(str1, "and now heximal: |%8x|, |%X|\n", 5554645, -123);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho4) {
    char str[100];
    char str1[100];
    sprintf(str, "%p", NULL);
    s21_sprintf(str1, "%p", NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho5) {
    char str[100];
    char str1[100];
    char *ptr = NULL;
    sprintf(str, "%p", ptr);
    s21_sprintf(str1, "%p", ptr);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for i-------------

START_TEST(SPRINTFTestdogletho6) {
    char str[100];
    char str1[100];
    sprintf(str, "|%i|\n",   10);
    s21_sprintf(str1, "|%i|\n",   10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho7) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", 8, 5, 15);
    s21_sprintf(str1, "|%*.*i|\n", 8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho8) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", 8, 5, 152352352);
    s21_sprintf(str1, "|%*.*i|\n", 8, 5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho9) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*i|\n", 18, 152352352);
    s21_sprintf(str1, "|%0*i|\n", 18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho10) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*i|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho11) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*i|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%-*.*i|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho12) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*i|", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho13) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*i|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*i|\n", 3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho14) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*i|\n", 18, 4, 152352352);
    s21_sprintf(str1, "|%0*.*i|\n", 18, 4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for negative width and accuracy: i-------------

START_TEST(SPRINTFTestdogletho15) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*i|\n", -10, -5, 10);
    s21_sprintf(str1, "|%-*.*i|\n", -10, -5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho16) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", -8, -5, 15);
    s21_sprintf(str1, "|%*.*i|\n", -8, -5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho17) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", -8, -5, 152352352);
    s21_sprintf(str1, "|%*.*i|\n", -8, -5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho18) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*i|\n", -18, 152352352);
    s21_sprintf(str1, "|%0*i|\n", -18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho19) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", -18, -10, 152352352);
    s21_sprintf(str1, "|%*.*i|\n", -18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho20) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*i|\n", -18, -10, 152352352);
    s21_sprintf(str1, "|%-*.*i|\n", -18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho21) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", -18, -15, -152352352);
    s21_sprintf(str1, "|%*.*i|\n", -18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho22) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", -18, 10, 152352352);
    s21_sprintf(str1, "|%*.*i|\n", -18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho23) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*i|\n", 18, -15, -152352352);
    s21_sprintf(str1, "|%*.*i|\n", 18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho24) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*i|\n", -3, -15, -152352352);
    s21_sprintf(str1, "|%-*.*i|\n", -3, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho25) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*i|\n", -18, -4, 152352352);
    s21_sprintf(str1, "|%0*.*i|\n", -18, -4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for d-------------

START_TEST(SPRINTFTestdogletho26) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", 10, 5, 10);
    s21_sprintf(str1, "|%-*.*d|\n", 10, 5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho27) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", 8, 5, 15);
    s21_sprintf(str1, "|%*.*d|\n", 8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho28) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", 8, 5, 152352352);
    s21_sprintf(str1, "|%*.*d|\n", 8, 5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho29) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*d|\n", 18, 152352352);
    s21_sprintf(str1, "|%0*d|\n", 18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho30) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*d|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho31) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%-*.*d|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho32) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*d|\n", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho33) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*d|\n", 3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho34) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", 15, 3, -152352352);
    s21_sprintf(str1, "|%-*.*d|\n", 15, 3, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho35) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*d|\n", 18, 4, 152352352);
    s21_sprintf(str1, "|%0*.*d|\n", 18, 4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Tests with negative width and accuracy for d-------------

START_TEST(SPRINTFTestdogletho36) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", -10, -5, 10);
    s21_sprintf(str1, "|%-*.*d|\n", -10, -5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho37) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", -8, 5, 15);
    s21_sprintf(str1, "|%*.*d|\n", -8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho38) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", 8, -5, 152352352);
    s21_sprintf(str1, "|%*.*d|\n", 8, -5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho39) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*d|\n", -18, 152352352);
    s21_sprintf(str1, "|%0*d|\n", -18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho40) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", -18, 10, 152352352);
    s21_sprintf(str1, "|%*.*d|\n", -18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho41) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", 18, -10, 152352352);
    s21_sprintf(str1, "|%-*.*d|\n", 18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho42) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", -18, -15, -152352352);
    s21_sprintf(str1, "|%*.*d|\n", -18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho43) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", 18, -10, 152352352);
    s21_sprintf(str1, "|%*.*d|\n", 18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho44) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", -18, 15, -152352352);
    s21_sprintf(str1, "|%*.*d|\n", -18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho45) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", 3, -15, -152352352);
    s21_sprintf(str1, "|%-*.*d|\n", 3, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho46) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", -15, 3, -152352352);
    s21_sprintf(str1, "|%-*.*d|\n", -15, 3, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho47) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*d|\n", -18, -4, 152352352);
    s21_sprintf(str1, "|%0*.*d|\n", -18, -4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho48) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*d|\n", -18, 10, 152352352);
    s21_sprintf(str1, "|%0*.*d|\n", -18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho49) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*d|\n", 18, -15, -152352352);
    s21_sprintf(str1, "|%0*.*d|\n", 18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho50) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*d|\n", -3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*d|\n", -3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho51) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*d|\n", 18, -4, 152352352);
    s21_sprintf(str1, "|%0*.*d|\n", 18, -4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Other tests for d-------------

START_TEST(SPRINTFTestdogletho52) {
    char str[100];
    char str1[100];
    sprintf(str, "|%.d|\n", 0);
    s21_sprintf(str1, "|%.d|\n", 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho53) {
    char str[100];
    char str1[100];
    sprintf(str, "|%5.d|\n", 0);
    s21_sprintf(str1, "|%5.d|\n", 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho54) {
    char str[100];
    char str1[100];
    sprintf(str, "|%5.0d|\n", 0);
    s21_sprintf(str1, "|%5.0d|\n", 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho55) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-5.d|\n", 0);
    s21_sprintf(str1, "|%-5.d|\n", 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho56) {
    char str[100];
    char str1[100];
    sprintf(str, "|%.0d|\n", 0);
    s21_sprintf(str1, "|%.0d|\n", 0);
    ck_assert_str_eq(str, str1);
}
END_TEST


// --------------Check for u-------------

START_TEST(SPRINTFTestdogletho57) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 10, 5, 10);
    s21_sprintf(str1, "|%-*.*u|\n", 10, 5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho58) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 8, 5, 15);
    s21_sprintf(str1, "|%*.*u|\n", 8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho59) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 8, 5, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", 8, 5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho60) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*u|\n", 18, 152352352);
    s21_sprintf(str1, "|%0*u|\n", 18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho61) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho62) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%-*.*u|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho63) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*u|\n", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho64) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho65) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*u|\n", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho66) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*u|\n", 3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho67) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", 18, 4, 152352352);
    s21_sprintf(str1, "|%0*.*u|\n", 18, 4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho68) {
    char str[100];
    char str1[100];
    sprintf(str, "|%020.18u|\n", -345);
    s21_sprintf(str1, "|%020.18u|\n", -345);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho69) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-20.18u|\n", -345);
    s21_sprintf(str1, "|%-20.18u|\n", -345);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho70) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-20.*u|\n", -18, -345);
    s21_sprintf(str1, "|%-20.*u|\n", -18, -345);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check with negative width and accuracy for u-------------

START_TEST(SPRINTFTestdogletho71) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, -10, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", -18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho72) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 18, -10, 152352352);
    s21_sprintf(str1, "|%-*.*u|\n", 18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho73) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, 15, -152352352);
    s21_sprintf(str1, "|%*.*u|\n", -18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho74) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", -18, 10, 152352352);
    s21_sprintf(str1, "|%0*.*u|\n", -18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho75) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", 18, -15, -152352352);
    s21_sprintf(str1, "|%0*.*u|\n", 18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho76) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", -3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*u|\n", -3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho77) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", 18, -4, 152352352);
    s21_sprintf(str1, "|%0*.*u|\n", 18, -4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho78) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, -10, 0);
    s21_sprintf(str1, "|%*.*u|\n", -18, -10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho79) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 18, -10, 0);
    s21_sprintf(str1, "|%-*.*u|\n", 18, -10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho80) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, 15, -0);
    s21_sprintf(str1, "|%*.*u|\n", -18, 15, -0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho81) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", -18, 10, 0);
    s21_sprintf(str1, "|%0*.*u|\n", -18, 10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho82) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", 18, -15, -0);
    s21_sprintf(str1, "|%0*.*u|\n", 18, -15, -0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho83) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", -3, 15, -0);
    s21_sprintf(str1, "|%-*.*u|\n", -3, 15, -0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho84) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", 18, -4, 0);
    s21_sprintf(str1, "|%0*.*u|\n", 18, -4, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for x-------------

START_TEST(SPRINTFTestdogletho85) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 10, 5, 10);
    s21_sprintf(str1, "|%-*.*x|\n", 10, 5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho86) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 5, 15);
    s21_sprintf(str1, "|%*.*x|\n", 8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho87) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 5, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", 8, 5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho88) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*x|\n", 18, 152352352);
    s21_sprintf(str1, "|%0*x|\n", 18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho89) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 10, 0, 0);
    s21_sprintf(str1, "|%-*.*x|\n", 10, 0, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho90) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 0, 0);
    s21_sprintf(str1, "|%*.*x|\n", 8, 0, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho91) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 5, 0);
    s21_sprintf(str1, "|%*.*x|\n", 8, 5, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho92) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*x|\n", 18, 0);
    s21_sprintf(str1, "|%0*x|\n", 18, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho93) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho94) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%-*.*x|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho95) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*x|\n", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho96) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho97) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*x|\n", 3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho98) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", 18, 4, 152352352);
    s21_sprintf(str1, "|%0*.*x|\n", 18, 4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check with negative width and accuracy for x-------------

START_TEST(SPRINTFTestdogletho99) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", -18, -10, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", -18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho100) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 18, -10, 152352352);
    s21_sprintf(str1, "|%-*.*x|\n", 18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho101) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", -18, 15, -152352352);
    s21_sprintf(str1, "|%*.*x|\n", -18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho102) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", -18, 10, 152352352);
    s21_sprintf(str1, "|%0*.*x|\n", -18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho103) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", 18, -15, -152352352);
    s21_sprintf(str1, "|%0*.*x|\n", 18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho104) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", -3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*x|\n", -3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho105) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", 18, -4, 152352352);
    s21_sprintf(str1, "|%0*.*x|\n", 18, -4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho106) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", -18, -10, 0);
    s21_sprintf(str1, "|%*.*x|\n", -18, -10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho107) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 18, -10, 0);
    s21_sprintf(str1, "|%-*.*x|\n", 18, -10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho108) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", -18, 15, -0);
    s21_sprintf(str1, "|%*.*x|\n", -18, 15, -0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho109) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", -18, 10, 0);
    s21_sprintf(str1, "|%0*.*x|\n", -18, 10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho110) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", 18, -15, -0);
    s21_sprintf(str1, "|%0*.*x|\n", 18, -15, -0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho111) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", -3, 15, -0);
    s21_sprintf(str1, "|%-*.*x|\n", -3, 15, -0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho112) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", 18, -4, 0);
    s21_sprintf(str1, "|%0*.*x|\n", 18, -4, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for X-------------

START_TEST(SPRINTFTestdogletho113) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 10, 5, 10);
    s21_sprintf(str1, "|%-*.*x|\n", 10, 5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho114) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 5, 15);
    s21_sprintf(str1, "|%*.*x|\n", 8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho115) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 5, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", 8, 5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho116) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*x|\n", 18, 152352352);
    s21_sprintf(str1, "|%0*x|\n", 18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho117) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 10, 0, 0);
    s21_sprintf(str1, "|%-*.*x|\n", 10, 0, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho118) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 0, 0);
    s21_sprintf(str1, "|%*.*x|\n", 8, 0, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho119) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 8, 5, 0);
    s21_sprintf(str1, "|%*.*x|\n", 8, 5, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho120) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*x|\n", 18, 0);
    s21_sprintf(str1, "|%0*x|\n", 18, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho121) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho122) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%-*.*x|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho123) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*x|\n", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho124) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*x|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*x|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho125) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*x|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*x|\n", 3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho126) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*x|\n", 18, 4, 152352352);
    s21_sprintf(str1, "|%0*.*x|\n", 18, 4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for s-------------

START_TEST(SPRINTFTestdogletho127) {
    char str[100];
    char str1[100];
    sprintf(str, "|%8s|\n", "abra");
    s21_sprintf(str1, "|%8s|\n", "abra");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho128) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-8s|\n", "abrafdefgbr");
    s21_sprintf(str1, "|%-8s|\n", "abrafdefgbr");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho129) {
    char str[100];
    char str1[100];
    sprintf(str, "|%8s|\n", "abra");
    s21_sprintf(str1, "|%8s|\n", "abra");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho130) {
    char str[100];
    char str1[100];
    sprintf(str, "|%8s|\n", "abrafdefgbr");
    s21_sprintf(str1, "|%8s|\n", "abrafdefgbr");
    ck_assert_str_eq(str, str1);
}
END_TEST


START_TEST(SPRINTFTestdogletho131) {
    char str[100];
    char str1[100];
    sprintf(str, "|%8s|\n", "abra");
    s21_sprintf(str1, "|%8s|\n", "abra");
    ck_assert_str_eq(str, str1);
}

START_TEST(SPRINTFTestdogletho132) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*s|\n", 20, 5, "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%*.*s|\n", 20, 5, "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho133) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*s|\n", 20, 5, "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%-*.*s|\n", 20, 5, "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho134) {
    char str[100];
    char str1[100];
    sprintf(str, "|%.*s|\n",  5, "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%.*s|\n",  5, "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho135) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.s|\n", 20, "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%*.s|\n", 20, "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho136) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%-*.s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho137) {
    char str[100];
    char str1[100];
    sprintf(str, "|%.s|\n",  "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%.s|\n",  "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho138) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*s|\n",  40, "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%*s|\n",  40, "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho139) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%-*.s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho140) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.0s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%-*.0s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho141) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.1s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%*.1s|\n", 20,  "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho142) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*s|\n", 2, 20, "1234567890123fsfbdfbdfvbbdvbvb");
    s21_sprintf(str1, "|%-*.*s|\n", 2, 20, "1234567890123fsfbdfbdfvbbdvbvb");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho143) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*s|\n",  40, p);
    s21_sprintf(str1, "|%*s|\n",  40, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho144) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*s|\n",  20, 2, p);
    s21_sprintf(str1, "|%*.*s|\n",  20, 2, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho145) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*s|\n",  20, 6, p);
    s21_sprintf(str1, "|%*.*s|\n",  20, 6, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho146) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%-*s|\n",  20,  p);
    s21_sprintf(str1, "|%-*s|\n",  20,  p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho147) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*s|\n",  20, 2, p);
    s21_sprintf(str1, "|%*.*s|\n",  20, 2, p);
    ck_assert_str_eq(str, str1);
}
END_TEST


START_TEST(SPRINTFTestdogletho148) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*s|\n",  20, 3, p);
    s21_sprintf(str1, "|%-*.*s|\n",  20, 3, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho149) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*s|\n",  -40, p);
    s21_sprintf(str1, "|%*s|\n",  -40, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho150) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*s|\n",  -20, -5, p);
    s21_sprintf(str1, "|%*.*s|\n",  -20, -5, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho151) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*s|\n",  -20, -6, p);
    s21_sprintf(str1, "|%*.*s|\n",  -20, -6, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho152) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%-*s|\n",  -20,  p);
    s21_sprintf(str1, "|%-*s|\n",  -20,  p);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho153) {
    char p[100] = { 0 };
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*s|\n",  -20, -5, p);
    s21_sprintf(str1, "|%-*.*s|\n",  -20, -5, p);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for p-------------

START_TEST(SPRINTFTestdogletho154) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  20, NULL);
    s21_sprintf(str1, "|%-*p|\n",  20, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho155) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  20, NULL);
    s21_sprintf(str1, "|%-*p|\n",  20, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho156) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  20, NULL);
    s21_sprintf(str1, "|%*p|\n",  20, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho157) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  1, NULL);
    s21_sprintf(str1, "|%*p|\n",  1, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho158) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  1, NULL);
    s21_sprintf(str1, "|%-*p|\n",  1, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho159) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  0, NULL);
    s21_sprintf(str1, "|%-*p|\n",  0, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho160) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  16, NULL);
    s21_sprintf(str1, "|%*p|\n",  16, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho161) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  -20, NULL);
    s21_sprintf(str1, "|%-*p|\n",  -20, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho162) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  -20, NULL);
    s21_sprintf(str1, "|%*p|\n",  -20, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho163) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  -1, NULL);
    s21_sprintf(str1, "|%*p|\n",  -1, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho164) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  -1, NULL);
    s21_sprintf(str1, "|%-*p|\n",  -1, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho165) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*d|\n", -18, -10, 0);
    s21_sprintf(str1, "|%*.*d|\n", -18, -10, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho166) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  -16, NULL);
    s21_sprintf(str1, "|%*p|\n",  -16, NULL);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check with . for p-------------

START_TEST(SPRINTFTestdogletho167) {
        char str[100];
        char str1[100];
        sprintf(str, "|%.p|\n", NULL);
        s21_sprintf(str1, "|%.p|\n", NULL);
        ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho168) {
    char a[100];
    s21_sprintf(a, "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is |%%|. And now unsigned: |%u|\n",
                "abra", 'e', 56, -43);
    char str[100];
    char str1[100];
    sprintf(str, "|%.p|\n", &a);
    s21_sprintf(str1, "|%.p|\n", &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho169) {
        char str[100];
        char str1[100];
        sprintf(str, "|%20.p|\n", NULL);
        s21_sprintf(str1, "|%20.p|\n", NULL);
        ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho170) {
    char a[100];
    s21_sprintf(a, "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is |%%|. And now unsigned: |%u|\n",
                "abra", 'e', 56, -43);
    char str[100];
    char str1[100];
    sprintf(str, "|%20.p|\n", &a);
    s21_sprintf(str1, "|%20.p|\n", &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho171) {
    int a = 23;
    char *str2 = "aa";
    char str[100];
    char str1[100];
    sprintf(str, "And now address: |%p| |%p|\n", &a, str2);
    s21_sprintf(str1, "And now address: |%p| |%p|\n", &a, str2);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho172) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  20, &a);
    s21_sprintf(str1, "|%-*p|\n",  20, &a);
    ck_assert_str_eq(str, str1);;
}
END_TEST
START_TEST(SPRINTFTestdogletho173) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  20, &a);
    s21_sprintf(str1, "|%*p|\n",  20, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho174) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  1, &a);
    s21_sprintf(str1, "|%*p|\n",  1, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho175) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  -1, &a);
    s21_sprintf(str1, "|%*p|\n",  -1, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho176) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  1, &a);
    s21_sprintf(str1, "|%-*p|\n",  1, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho177) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  0, &a);
    s21_sprintf(str1, "|%-*p|\n",  0, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho178) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  16, &a);
    s21_sprintf(str1, "|%*p|\n",  16, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho179) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  -20, &a);
    s21_sprintf(str1, "|%*p|\n",  -20, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho180) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  -20, &a);
    s21_sprintf(str1, "|%-*p|\n",  -20, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho181) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%-*p|\n",  -1, &a);
    s21_sprintf(str1, "|%-*p|\n",  -1, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho182) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*p|\n",  -16, &a);
    s21_sprintf(str1, "|%*p|\n",  -16, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho183) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*.p|\n",  16, &a);
    s21_sprintf(str1, "|%*.p|\n",  16, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho184) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.p|\n",  -20, &a);
    s21_sprintf(str1, "|%-*.p|\n",  -20, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho185) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*.p|\n",  -20, &a);
    s21_sprintf(str1, "|%*.p|\n",  -20, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho186) {
    int a = 23;
    char str[100];
    char str1[100];
    sprintf(str, "|%*.p|\n",  -1, &a);
    s21_sprintf(str1, "|%*.p|\n",  -1, &a);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho187) {
    char str[100];
    char str1[100];
    sprintf(str, "%i", 0);
    s21_sprintf(str1, "%i", 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for c-------------

START_TEST(SPRINTFTestdogletho188) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n", 40, 'a');
    s21_sprintf(str1, "|%*c|\n", 40, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho189) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  0, 'a');
    s21_sprintf(str1, "|%*c|\n",  0, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho190) {
    char str[100];
    char str1[100];
    sprintf(str, "|%c|\n", 'a');
    s21_sprintf(str1, "|%c|\n", 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho191) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 0,   'a');
    s21_sprintf(str1, "|%-*c|\n", 0,   'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho192) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n",  40, 'a');
    s21_sprintf(str1, "|%-*c|\n",  40, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho193) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  5, 'a');
    s21_sprintf(str1, "|%*c|\n",  5, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho194) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 5,   'a');
    s21_sprintf(str1, "|%-*c|\n", 5,   'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho195) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 1, 'a');
    s21_sprintf(str1, "|%-*c|\n", 1, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho196) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 0,   'a');
    s21_sprintf(str1, "|%-*c|\n", 0,   'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho197) {
    char str[100];
    char str1[100];
    sprintf(str, "|%.c|\n", 'a');
    s21_sprintf(str1, "|%.c|\n", 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho198) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-.c|\n", 'a');
    s21_sprintf(str1, "|%-.c|\n", 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check with negative width for c-------------

START_TEST(SPRINTFTestdogletho199) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  -40, 'a');
    s21_sprintf(str1, "|%*c|\n",  -40, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho200) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  -1, 'a');
    s21_sprintf(str1, "|%*c|\n",  -1, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho201) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 0,   'a');
    s21_sprintf(str1, "|%-*c|\n", 0,   'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho202) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n",  -40, 'a');
    s21_sprintf(str1, "|%-*c|\n",  -40, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho203) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  -5, 'a');
    s21_sprintf(str1, "|%*c|\n",  -5, 'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho204) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", -5,   'a');
    s21_sprintf(str1, "|%-*c|\n", -5,   'a');
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for empty c-------------

START_TEST(SPRINTFTestdogletho205) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  40, '\0');
    s21_sprintf(str1, "|%*c|\n",  40, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho206) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  0, '\0');
    s21_sprintf(str1, "|%*c|\n",  0, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho207) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 0,  '\0');
    s21_sprintf(str1, "|%-*c|\n", 0,  '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho208) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n",  40, '\0');
    s21_sprintf(str1, "|%-*c|\n",  40, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho209) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 5,   '\0');
    s21_sprintf(str1, "|%-*c|\n", 5,   '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho210) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  1, '\0');
    s21_sprintf(str1, "|%*c|\n",  1, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho211) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", 1,   '\0');
    s21_sprintf(str1, "|%-*c|\n", 1,   '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check with negative width for empty c-------------

START_TEST(SPRINTFTestdogletho212) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  -40, '\0');
    s21_sprintf(str1, "|%*c|\n",  -40, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho213) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  -1, '\0');
    s21_sprintf(str1, "|%*c|\n",  -1, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho214) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", -1,  '\0');
    s21_sprintf(str1, "|%-*c|\n", -1,  '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho215) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n",  -40, '\0');
    s21_sprintf(str1, "|%-*c|\n",  -40, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho216) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*c|\n",  -5, '\0');
    s21_sprintf(str1, "|%*c|\n",  -5, '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho217) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*c|\n", -5,   '\0');
    s21_sprintf(str1, "|%-*c|\n", -5,   '\0');
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for %%-------------

START_TEST(SPRINTFTestdogletho218) {
    char str[100];
    char str1[100];
    sprintf(str, "|%5%|\n");
    s21_sprintf(str1, "|%5%|\n");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho219) {
    char str[100];
    char str1[100];
    sprintf(str, "|%5.%|\n");
    s21_sprintf(str1, "|%5.%|\n");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho220) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-5%|\n");
    s21_sprintf(str1, "|%-5%|\n");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho221) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-5.%|\n");
    s21_sprintf(str1, "|%-5.%|\n");
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho222) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*%|\n", 12, 15);
    s21_sprintf(str1, "|%*.*%|\n", 12, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho223) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.%|\n", 12);
    s21_sprintf(str1, "|%*.%|\n", 12);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho224) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0.*%|\n", 12);
    s21_sprintf(str1, "|%0.*%|\n", 12);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho225) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*%|\n", 12, 15);
    s21_sprintf(str1, "|%*.*%|\n", 12, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho226) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*%|\n", 12);
    s21_sprintf(str1, "|%0*%|\n", 12);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho227) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*%|\n", 12, 5);
    s21_sprintf(str1, "|%0*.*%|\n", 12, 5);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho228) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*%|\n", 12, 15);
    s21_sprintf(str1, "|%0*.*%|\n", 12, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho229) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*%|\n", 12, 1);
    s21_sprintf(str1, "|%0*.*%|\n", 12, 1);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho230) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*%|\n", 1, 5);
    s21_sprintf(str1, "|%0*.*%|\n", 1, 5);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho231) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*%|\n", 1, 5);
    s21_sprintf(str1, "|%0*.*%|\n", 1, 5);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check with + -------------

START_TEST(SPRINTFTestdogletho232) {
    char str[100];
    char str1[100];
    for (int i = -101; i <= 101; i++) {
        sprintf(str, "%+i", i);
        s21_sprintf(str1, "%+i", i);
        ck_assert_str_eq(str, str1);
    }
}
END_TEST

START_TEST(SPRINTFTestdogletho233) {
    char str[100];
    char str1[100];
    for (int i = -101; i <= 101; i++) {
        sprintf(str, "%+d", i);
        s21_sprintf(str1, "%+d", i);
        ck_assert_str_eq(str, str1);
    }
}
END_TEST



START_TEST(SPRINTFTestdogletho234) {
    char str[100];
    char str1[100];
    sprintf(str, " %+d %+i %+d %+d", 2147483647, -2147483647, 21, 0);
    s21_sprintf(str1, " %+d %+i %+d %+d", 2147483647, -2147483647, 21, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho235) {
    char str[100];
    char str1[100];
    sprintf(str, " %+li ", 9223372036854775807);
    s21_sprintf(str1, " %+li ", 9223372036854775807);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho236) {
    char str[100];
    char str1[100];
    sprintf(str, " %+ld ", 9223372036854775807);
    s21_sprintf(str1, " %+ld ", 9223372036854775807);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho237) {
    char str[100];
    char str1[100];
    sprintf(str, " %+-5d %+-5i", -7, 0);
    s21_sprintf(str1, " %+-5d %+-5i", -7, 0);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho238) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%lo\n", 100000000000000000);
    sprintf(data1, "%lo\n", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

// --------------Check u-------------

START_TEST(SPRINTFTestdogletho239) {
    char str[100];
    char str1[100];
    sprintf(str, "|%u|\n",   10);
    s21_sprintf(str1, "|%u|\n",   10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho240) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 8, 5, 15);
    s21_sprintf(str1, "|%*.*u|\n", 8, 5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho241) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 8, 5, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", 8, 5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho242) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*u|\n", 18, 152352352);
    s21_sprintf(str1, "|%0*u|\n", 18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho243) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho244) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 18, 10, 152352352);
    s21_sprintf(str1, "|%-*.*u|\n", 18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho245) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|", 18, 15, -152352352);
    s21_sprintf(str1, "|%*.*u|", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho246) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*u|\n", 3, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho247) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", 18, 4, 152352352);
    s21_sprintf(str1, "|%0*.*u|\n", 18, 4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for negative width and accuracy: u-------------

START_TEST(SPRINTFTestdogletho248) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", -10, -5, 10);
    s21_sprintf(str1, "|%-*.*u|\n", -10, -5, 10);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho249) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -8, -5, 15);
    s21_sprintf(str1, "|%*.*u|\n", -8, -5, 15);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho250) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -8, -5, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", -8, -5, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho251) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*u|\n", -18, 152352352);
    s21_sprintf(str1, "|%0*u|\n", -18, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho252) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, -10, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", -18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho253) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", -18, -10, 152352352);
    s21_sprintf(str1, "|%-*.*u|\n", -18, -10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho254) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, -15, -152352352);
    s21_sprintf(str1, "|%*.*u|\n", -18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho255) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", -18, 10, 152352352);
    s21_sprintf(str1, "|%*.*u|\n", -18, 10, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho256) {
    char str[100];
    char str1[100];
    sprintf(str, "|%*.*u|\n", 18, -15, -152352352);
    s21_sprintf(str1, "|%*.*u|\n", 18, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho257) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*u|\n", -3, -15, -152352352);
    s21_sprintf(str1, "|%-*.*u|\n", -3, -15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST
START_TEST(SPRINTFTestdogletho258) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*u|\n", -18, -4, 152352352);
    s21_sprintf(str1, "|%0*.*u|\n", -18, -4, 152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check space -------------

START_TEST(SPRINTFTestdogletho259) {
    char str[100];
    char str1[100];
    for (int i = -101; i <= 101;) {
        sprintf(str, "% d", i);
        s21_sprintf(str1, "% d", i);
        i = i+7;
        ck_assert_str_eq(str, str1);
    }
}
END_TEST

START_TEST(SPRINTFTestdogletho260) {
        char str[100];
        char str1[100];
            sprintf(str, " %#x ", 0);
            s21_sprintf(str1, " %#x ", 0);
            ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho261) {
    char str[100];
    char str1[100];
    for (int i = -101; i <= 101;) {
        sprintf(str, "% -i % -d % -5d", i, i+1, 143646235);
        s21_sprintf(str1, "% -i % -d % -5d", i, i+1, 143646235);
        i = i+7;
        ck_assert_str_eq(str, str1);
    }
}
END_TEST

START_TEST(SPRINTFTestdogletho262) {
    char str[100];
    char str1[100];
        sprintf(str, "%#o", 143646235);
        s21_sprintf(str1, "%#o", 143646235);
        ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho263) {
    char str[100];
    char str1[100];
        sprintf(str, "%0*.o", 10, 143646235);
        s21_sprintf(str1, "%0*.o", 10, 143646235);
        ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho264) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%o|\n", 34);
    sprintf(data1, "02) standart PRINTF : |%o|\n", 34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho265) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%o|\n", -34);
    sprintf(data1, "02) standart PRINTF : |%o|\n", -34);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho266) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-o|\n", 50);
    sprintf(data1, "02) standart PRINTF : |%-o|\n", 50);
    ck_assert_str_eq(data, data1);
}
END_TEST


START_TEST(SPRINTFTestdogletho267) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10o|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%10o|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho268) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.10o|\n", 90);
    sprintf(data1, "02) standart PRINTF : |%.10o|\n", 90);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho269) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15o|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%15o|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho270) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.15o|\n", -100);
    sprintf(data1, "02) standart PRINTF : |%.15o|\n", -100);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho271) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%10.5o|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%10.5o|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho272) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%5.10o|\n", 52);
    sprintf(data1, "02) standart PRINTF : |%5.10o|\n", 52);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho273) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%20.15o|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%20.15o|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho274) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%15.20o|\n", -100000);
    sprintf(data1, "02) standart PRINTF : |%15.20o|\n", -100000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho275) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-10o|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-10o|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho276) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-.10o|\n", 144);
    sprintf(data1, "02) standart PRINTF : |%-.10o|\n", 144);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho277) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%-20o|\n", -20000000);
    sprintf(data1, "02) standart PRINTF : |%-20o|\n", -20000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho278) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%08o|\n", 64);
    sprintf(data1, "02) standart PRINTF : |%08o|\n", 64);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho279) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.o|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%.o|\n", 0);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho280) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.o|\n", 88);
    sprintf(data1, "02) standart PRINTF : |%.o|\n", 88);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho281) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%o| |%o|\n", (unsigned int)-1,  1);
    sprintf(data1, "02) standart PRINTF : |%o| |%o|\n", (unsigned int)-1, 1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho282) {
    char data[100];
    char data1[100];
    int t = 50;
    s21_sprintf(data, "%s %n", "hello world", &t);
    sprintf(data1, "%s %n", "hello world", &t);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho283) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%-3.1s", "\0");
    sprintf(data1, "%-3.1s", "\0");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho284) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "this -%g scientific notation", -1.5);
    sprintf(data1, "this -%g scientific notation", -1.5);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho285) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%.0g", 0.1);
    sprintf(data1, "%.0g", 0.1);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho286) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%g", 9999999999.9);
    sprintf(data1, "%g", 9999999999.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho287) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%e", 9999999999.9);
    sprintf(data1, "%e", 9999999999.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho288) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%0*.e", 10, 0.9);
    sprintf(data1, "%0*.e", 10, 0.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho289) {
    char data[100];
    char data1[100];
    s21_sprintf(data, "%#05x", 21);
    sprintf(data1, "%#05x", 21);
    ck_assert_str_eq(data, data1);
}
END_TEST


// MARK: - Sprintf tests by rleopard

START_TEST(SPRINTFTestRleonard1) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%li", 100000000000000000);
    sprintf(data1, "%li", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard2) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%lo", 100000000000000000);
    sprintf(data1, "%lo", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard3) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%lu", 100000000000000000);
    sprintf(data1, "%lu", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard4) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%lx", 100000000000000000);
    sprintf(data1, "%lx", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard5) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%lX", 100000000000000000);
    sprintf(data1, "%lX", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard6) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%ld", 100000000000000000);
    sprintf(data1, "%ld", 100000000000000000);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard7) {
    char data[200];
    char data1[200];
    short int i = -30000;
    s21_sprintf(data, "%hi", i);
    sprintf(data1, "%hi", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard8) {
    char data[200];
    char data1[200];
    short int i = -30000;
    s21_sprintf(data, "%ho", i);
    sprintf(data1, "%ho", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard9) {
    char data[200];
    char data1[200];
    short int i = -30000;
    s21_sprintf(data, "%hu", i);
    sprintf(data1, "%hu", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard10) {
    char data[200];
    char data1[200];
    short int i = -30000;
    s21_sprintf(data, "%hx", i);
    sprintf(data1, "%hx", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard11) {
    char data[200];
    char data1[200];
    short int i = -30000;
    s21_sprintf(data, "%hX", i);
    sprintf(data1, "%hX", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard12) {
    char data[200];
    char data1[200];
    short int i = -30000;
    s21_sprintf(data, "%hd", i);
    sprintf(data1, "%hd", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard13) {
    char data[200];
    char data1[200];
    s21_sprintf(data, "%lc", 'c');
    sprintf(data1, "%lc", 'c');

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard14) {
    char data[200];
    char data1[200];
    wchar_t buf[100] = L"hello";
    s21_sprintf(data, "%ls", buf);
    sprintf(data1, "%ls", buf);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard15) {
    char data[200];
    char data1[200];
    long double i = 0.00000000000000000000000000000000000000000000000001;
    s21_sprintf(data, "%Lf", i);
    sprintf(data1, "%LF", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard16) {
    char data[200];
    char data1[200];
    long double i = 1.1e+49;
    s21_sprintf(data, "%Le", i);
    sprintf(data1, "%Le", i);

    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard17) {
    char data[200];
    char data1[200];
    long double i = 1.1e+49;
    s21_sprintf(data, "%LE", i);
    sprintf(data1, "%LE", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard18) {
    char data[200];
    char data1[200];
    long double i = 0.00000000000000000000000000000000000000000000000001;
    s21_sprintf(data, "%Lg", i);
    sprintf(data1, "%Lg", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard19) {
    char data[200];
    char data1[200];
    long double i = 0.00000000000000000000000000000000000000000000000001;
    s21_sprintf(data, "%LG", i);
    sprintf(data1, "%LG", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

// THE END OF SEVEN THOUSAND SPRINTF UNIT_TEST FILE

// THE BEGINNING OF STSUF SUITE

Suite *example_suite_create() {
    Suite *s1 = suite_create("Test_sprintf");
    TCase *sprintftest = tcase_create("SPRINTF2");

    suite_add_tcase(s1, sprintftest);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn1);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn2);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn3);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn4);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn5);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn6);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn7);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn8);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn9);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn10);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn11);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn12);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn13);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn14);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn15);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn16);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn17);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn18);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn19);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn20);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn21);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn22);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn23);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn24);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn25);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn26);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn27);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn28);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn29);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn30);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn31);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn32);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn33);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn34);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn35);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn36);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn37);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn38);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn39);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn40);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn41);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn42);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn43);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn44);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn45);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn46);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn47);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn48);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn49);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn50);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn51);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn52);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn53);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn54);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn55);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn56);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn57);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn58);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn59);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn60);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn61);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn62);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn63);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn64);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn65);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn66);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn67);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn68);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn69);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn70);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn71);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn72);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn73);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn74);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn75);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn76);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn77);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn78);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn79);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn80);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn81);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn82);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn83);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn84);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn85);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn86);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn87);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn88);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn89);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn90);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn91);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn92);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn93);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn94);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn95);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn96);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn97);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn98);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn99);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn100);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn101);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn102);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn103);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn104);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn105);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn106);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn107);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn108);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn109);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn110);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn111);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn112);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn113);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn114);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn115);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn116);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn117);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn118);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn119);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn120);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn121);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn122);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn123);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn124);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn125);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn126);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn127);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn128);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn129);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn130);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn131);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn132);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn133);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn134);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn135);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn136);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn137);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn138);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn139);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn140);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn141);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn142);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn143);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn144);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn145);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn146);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn147);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn148);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn149);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn150);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn151);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn152);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn153);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn154);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn155);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn156);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn157);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn158);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn159);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn160);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn161);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn162);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn163);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn164);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn165);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn166);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn167);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn168);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn169);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn170);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn171);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn172);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn173);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn174);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn175);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn176);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn177);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn178);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn179);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn180);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn181);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn182);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn183);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn184);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn185);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn186);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn187);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn188);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn189);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn190);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn191);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn192);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn193);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn194);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn195);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn196);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn197);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn198);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn199);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn200);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn201);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn202);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn203);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn204);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn205);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn206);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn207);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn208);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn209);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn210);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn211);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn212);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn213);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn214);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn215);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn216);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn217);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn218);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn219);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn220);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn221);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn222);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn223);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn224);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn225);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn226);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn227);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn228);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn229);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn230);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn231);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn232);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn233);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn234);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn235);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn236);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn237);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn238);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn239);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn240);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn241);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn242);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn243);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn244);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn245);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn246);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn247);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn248);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn249);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn250);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn251);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn252);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn253);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn254);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn255);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn256);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn257);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn258);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn259);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn260);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn261);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn262);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn263);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn264);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn265);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn266);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn267);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn268);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn269);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn270);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn271);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn272);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn273);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn274);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn275);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn276);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn277);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn278);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn279);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn280);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn281);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn282);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn283);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn284);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn285);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn286);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn287);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn288);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn289);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn290);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn291);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn292);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn293);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn294);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn295);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn296);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn297);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn298);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn299);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn300);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn301);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn302);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn303);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn304);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn305);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn306);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn307);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn308);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn309);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn310);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn311);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn312);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn313);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn314);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn315);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn316);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn317);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn318);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn319);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn320);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn321);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn322);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn323);
    tcase_add_test(sprintftest, SPRINTFTestLaslhyn324);

    return s1;
}

Suite *example_suite_create2() {
    Suite *s1 = suite_create("Test_sprintf_part2");
    TCase *sprintftest1 = tcase_create("SPRINTF1");
    TCase *sprintftest3 = tcase_create("SPRINTF3");
    suite_add_tcase(s1, sprintftest1);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho1);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho2);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho3);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho4);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho5);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho6);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho7);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho8);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho9);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho10);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho11);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho12);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho13);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho14);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho15);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho16);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho17);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho18);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho19);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho20);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho21);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho22);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho23);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho24);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho25);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho26);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho27);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho28);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho29);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho30);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho31);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho32);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho33);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho34);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho35);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho36);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho37);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho38);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho39);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho40);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho41);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho42);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho43);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho44);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho45);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho46);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho47);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho48);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho49);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho50);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho51);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho52);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho53);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho54);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho55);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho56);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho57);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho58);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho59);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho60);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho61);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho62);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho63);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho64);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho65);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho66);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho67);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho68);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho69);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho70);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho71);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho72);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho73);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho74);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho75);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho76);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho77);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho78);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho79);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho80);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho81);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho82);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho83);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho84);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho85);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho86);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho87);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho88);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho89);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho90);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho91);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho92);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho93);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho94);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho95);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho96);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho97);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho98);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho99);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho100);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho101);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho102);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho103);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho104);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho105);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho106);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho107);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho108);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho109);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho110);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho111);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho112);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho113);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho114);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho115);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho116);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho117);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho118);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho119);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho120);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho121);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho122);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho123);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho124);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho125);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho126);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho127);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho128);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho129);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho130);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho131);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho132);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho133);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho134);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho135);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho136);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho137);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho138);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho139);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho140);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho141);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho142);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho143);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho144);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho145);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho146);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho147);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho148);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho149);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho150);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho151);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho152);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho153);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho154);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho155);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho156);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho157);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho158);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho159);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho160);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho161);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho162);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho163);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho164);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho165);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho166);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho167);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho168);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho169);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho170);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho171);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho172);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho173);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho174);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho175);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho176);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho177);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho178);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho179);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho180);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho181);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho182);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho183);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho184);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho185);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho186);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho187);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho188);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho189);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho190);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho191);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho192);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho193);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho194);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho195);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho196);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho197);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho198);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho199);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho200);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho201);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho202);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho203);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho204);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho205);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho206);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho207);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho208);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho209);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho210);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho211);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho212);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho213);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho214);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho215);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho216);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho217);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho218);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho219);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho220);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho221);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho222);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho223);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho224);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho225);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho226);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho227);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho228);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho229);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho230);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho231);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho232);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho233);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho234);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho235);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho236);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho237);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho238);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho239);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho240);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho241);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho242);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho243);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho244);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho245);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho246);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho247);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho248);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho249);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho250);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho251);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho252);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho253);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho254);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho255);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho256);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho257);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho258);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho259);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho260);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho261);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho262);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho263);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho264);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho265);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho266);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho267);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho268);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho269);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho270);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho271);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho272);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho273);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho274);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho275);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho276);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho277);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho278);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho279);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho280);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho281);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho282);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho283);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho284);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho285);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho286);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho287);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho288);
    tcase_add_test(sprintftest1, SPRINTFTestdogletho289);

    suite_add_tcase(s1, sprintftest3);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard1);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard2);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard3);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard4);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard5);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard6);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard7);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard8);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard9);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard10);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard11);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard12);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard13);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard14);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard15);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard16);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard17);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard18);
    tcase_add_test(sprintftest3, SPRINTFTestRleonard19);
    return s1;
}

// THE END OF STSUF SUITE
    
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
    tcase_add_test(tc_core, test_s21_strrchr);
    tcase_add_test(tc_core, test_s21_strchr);
    tcase_add_test(tc_core, test_s21_memset);
    tcase_add_test(tc_core, test_s21_memmove);
    tcase_add_test(tc_core, test_s21_strcpy);
    tcase_add_test(tc_core, test_s21_strncpy);
    tcase_add_test(tc_core, test_s21_strncat);
    tcase_add_test(tc_core, test_s21_strspn);
    tcase_add_test(tc_core, test_s21_strcspn);
    tcase_add_test(tc_core, test_s21_strcmp);
    tcase_add_test(tc_core, test_s21_strncmp);
    
    tcase_add_test(tc_core, test_s21_to_lower);
    tcase_add_test(tc_core, test_s21_to_upper);
    tcase_add_test(tc_core, test_s21_trim);
    tcase_add_test(tc_core, test_s21_insert);
    
    tcase_add_test(tc_core, test_s21_sprintf);
    tcase_add_test(tc_core, test_s21_base_unum_get_str_len);
    tcase_add_test(tc_core, test_s21_frmt_is_tokn);
    tcase_add_test(tc_core, test_s21_tokn_skip_part);
    tcase_add_test(tc_core, test_s21_tokn_get_str_len);
    tcase_add_test(tc_core, test_s21_tokn_have_flag);
    tcase_add_test(tc_core, test_s21_tokn_get_width);
//  tcase_add_test(tc_core, test_s21_trgt_print_uint);
    tcase_add_test(tc_core, test_s21_ulong_get_pow);
    tcase_add_test(tc_core, test_s21_trgt_print_tokn_num);
//    tcase_add_test(tc_core, test_s21_trgt_print_tokn_str);
    tcase_add_test(tc_core, test_s21_trgt_print_ulong);
    tcase_add_test(tc_core, test_s21_trgt_print_uldouble);
    tcase_add_test(tc_core, test_s21_trgt_print_tokn_ratio);
    tcase_add_test(tc_core, test_s21_trgt_print_base_ulong);
    tcase_add_test(tc_core, test_s21_trgt_print_tokn_ptr);
    
    

    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    // STSUF BEGINNING
    Suite *s1 = example_suite_create();
    Suite *s4 = example_suite_create2();

    SRunner *runner = srunner_create(s1);
    SRunner *runner2 = srunner_create(s4);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    
    srunner_run_all(runner2, CK_NORMAL);
    number_failed = number_failed + srunner_ntests_failed(runner2);
    srunner_free(runner2);
    //STSUF END
    
    s = s21_string_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

