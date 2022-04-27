#include <stdio.h>
#include <string.h>
size_t s21_strspn(const char *str1, const char *str2) {
    int pol = 0;
    size_t l = 0, k = 0;
   
    for (size_t i = 0; *(str2 + i) != '\0'; i++) {
        k++;
    }
    for (size_t i = 0; *(str1 + i) != '\0'; i++) {
        pol = 0;
        if (l == i) {
            for (size_t j = 0; *(str2 + j) != '\0'; j++) {
                if (*(str2 + j) == *(str1 + i)) {
                    pol++;
                }
            }
            if (pol != 0) {
                l++;
            }
        }
    }
    return l;
}
int main() {
    char str1[20] = "0123456789";
    char str2[20] = "210";
    printf("%ld",  s21_strspn(str1, str2));
    return 0;
}
