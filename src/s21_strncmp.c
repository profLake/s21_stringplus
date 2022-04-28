#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    
    s21_size_t i;
    
    i = 0;
    while ((str1[i] || str2[i]) && (i < n))
    {
        if (str1[i] < str2[i])
            return -1;
        if (str1[i] > str2[i])
            return 1;
        i++;
    }
    return 0;
}
