#include "s21_string.h"

char* s21_strchr(const char *str, int c) {
    char *ret = s21_NULL;
    while (*str) {
        if (*str == (char)c) {
            ret = (char*)str;
            break;
        }
        str++;
    }

    return ret;
}
