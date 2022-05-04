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
    ck_assert_str_eq(s21_strerror(ENOTUNIQ), strerror(ENOTUNIQ));
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
        puts(new);
    ck_assert_str_eq(new, "aa2aa");
    
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
    ck_assert_str_eq(new1, qp);
    ck_assert_str_eq(new3, s21_NULL);
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
    right = sprintf(buff_right, format, "A telegram");
    out = s21_sprintf(buff, format, "A Telgeram");
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
    tcase_add_test(tc_core, test_s21_udecim_get_str_len);
    tcase_add_test(tc_core, test_s21_frmt_is_tokn);
    tcase_add_test(tc_core, test_s21_tokn_skip_part);
    tcase_add_test(tc_core, test_s21_tokn_get_len);
    tcase_add_test(tc_core, test_s21_tokn_have_flag);
    tcase_add_test(tc_core, test_s21_tokn_get_width);
    tcase_add_test(tc_core, test_s21_trgt_print_uint);
    tcase_add_test(tc_core, test_s21_int_get_pow);
    tcase_add_test(tc_core, test_s21_trgt_print_tokn_decim);
    tcase_add_test(tc_core, test_s21_trgt_print_tokn_str);

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
