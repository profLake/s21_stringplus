#include "s21_string.h"

char* s21_strchr(const char *str, int c) {
    char *ret = s21_NULL;

    char r = (char)c;
    while (*str && *str != r)
        str++;
    if (*str && *str == r)
        ret = (char*)str;

    return ret;
}
