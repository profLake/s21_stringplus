#include <stdio.h>
#include <string.h>
char *s21_strncat(char *dest, const char *src, size_t n) {
    size_t k = 0;
   for (size_t i = 0; *(dest + i) != '\0'; i++) {
       k++;
   }
    for (size_t i = 0; i < n; i++) {
        *((char*)dest + i + k) =  *((char*)src + i);
        if (((char*)src + i) == NULL) {
            break;
       }
    }
    return (char*)dest;
}
int main() {
    char ruk[5] = "joui";
   char dob[5] = "lah_";
    s21_strncat(ruk, dob, 4);
    for (int i = 0; ruk[i] != '\0'; i++) {
        printf("%c", ruk[i]);
    }
   
    return 0;
}
