#include <stdio.h>
#include <string.h>
#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
    char *c;
    c = dest;
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return c;
}

 int main() {
     char str[200] = "cdefasf";
     char str1[20000] = "cdefasf";
     char ch[] = "wsfd";
    strcat(str, ch);
         printf("%s\n", str);
   s21_strcat(str1, ch);
     printf("%s\n", str1);
     return 0;
 }
