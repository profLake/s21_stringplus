#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    for (s21_size_t i = 0; *(str1 + i) != '\0'; i++) {
        for (s21_size_t k = 0; *(str2 + k) != '\0'; k++) {
            if (*(str1 + i) == *(str2 + k)) {
                return (char*)(str1 + i);
            }
        }
    }
    return s21_NULL;
}
