#include <stdio.h>
#include <string.h>
#include "s21_string.h"
size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t j, k = 0, l = 0;
    for (s21_size_t i = 0; *(str2 + i) != '\0'; i++) {
        k++;
    }
    for (s21_size_t i = 0; *(str1 + i) != '\0'; i++) { j = 0;
        if (l == i) {
            for (j = 0; *(str2 + j) != '\0'; j++) {
                if (*(str2 + j) == *(str1 + i)) {
                    break;
                }
            }
            if (j == k) {
                l++;
            }
        }
    }
    return l;
}
/*int main() {
    char str1[20] = "1234567890";
    char str2[20] = "7890";
  
    printf("%ld",  s21_strcspn(str1, str2));
    return 0;
}*/

