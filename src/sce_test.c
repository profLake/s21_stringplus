#include "s21_string.h"
#include <stdio.h>
#include "string.h"

int main() {
    char *str1 = "12347";
    char *str2 = "12345";

    puts("S21_MEMCMP");

    if (s21_memcmp(str1, str2, 5) == 2) {
        puts("PASSED");
    } else {
        puts("NOT PASSED");
    }

    puts("S21_STRCHR");

    if (            s21_strchr(str1, '4') == str1 + 3) {
        puts("PASSED");
    } else {
        puts("NOT PASSED");
    }

    puts("S21_MEMCPY");

    char dest[50];
    s21_memcpy(dest, "hello", 4);
    if (            strncmp(dest, "hellr", 4) == 0) {
        puts("PASSED");
    } else {
        puts("NOT PASSED");
    }
    if (            strncmp(dest, "hellr", 5) != 0) {
        puts("PASSED");
    } else {
        puts("NOT PASSED");
    }

    puts("S21_STRNCMP");

    if (            s21_strncmp("hello", "hellr", 4) == 0) {
        puts("PASSED");
    } else {
        puts("NOT PASSED");
    }
    if (            s21_strncmp("hello", "hellr", 5) == 'o' - 'r') {
        puts("PASSED");
    } else {
        puts("NOT PASSED");
    }

    return 0;
}

