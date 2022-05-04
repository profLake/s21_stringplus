#include "s21_string.h"

char* s21_strchr(const char *str, int c) {
    char * ret = s21_NULL;
    for (int i = 0; str[i]; i++) {
        if (str[i] == (char)c) {
            ret = (char*)(str + i);
            break;
        }
    }
    return ret;
}
