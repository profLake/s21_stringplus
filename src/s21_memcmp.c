#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const char *p1 = str1;
    const char *p2 = str2;
    int ret = 0;
    for (s21_size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            ret = p1[i] - p2[i];
            break;
        }
    }
    return ret;
}
