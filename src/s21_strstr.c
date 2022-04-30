#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
    /* Пропускаем неподходящую часть str */
    while (*haystack && *haystack != *needle) {
        haystack++;
    }
    if (*haystack == '\0') {
        return s21_NULL;
    }

    int i = 0;
    while (haystack[i] && needle[i] && haystack[i] == needle[i]) {
        i++;
    }
    if (needle[i] == '\0') {
        return (char*)haystack;
    }
    haystack += i;
    return s21_strstr(haystack, needle);
}
