#include <stdio.h>
#include <string.h>
char *s21_strpbrk(const char *str1, const char *str2) {
    char* num = NULL;
    for (size_t i = 0; *(str2 + i) != '\0'; i++) {
            for (size_t j = 0; *(str1 + j) != '\0'; j++) {
                if (*(str2 + i) == *(str1 + j)) {
                    num = (char*)str1 + j;
                }
            }
            if (num != NULL) {
                break;
        }
    }
    return num;
}
int main() {
    char str1[20] = "0123456789";
    char str2[20] = "369";
    char* isym = s21_strpbrk(str1, str2);
    printf ("%ld\n", isym - str1 + 1);
    return 0;
}
