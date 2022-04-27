#include "s21_string.h"

char *strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    int m;
    
    m = 0;
    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}
