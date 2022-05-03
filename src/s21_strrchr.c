#include "s21_string.h"

char* s21_strrchr(const char *str, int c) {
    int j = 0;
    char* ret = s21_NULL;
        while (str[j] != '\0')
            j++;
    for (int i = j - 1; i > - 1; i--) {
        if (*(str + i) == (char)c) {
            ret =(char*)(str + i);
            break;
        }
    }
    return ret;
}
