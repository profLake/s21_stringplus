#include <stdio.h>
#include <string.h>
#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        *((char*)dest + i) = *((char*)src + i);
    }
    return (char*)dest;
}
/*int main (void) {
   // Исходный массив данных
   char src[11]="1234567890";
    char str[20];
   // Вывод массива src на консоль
   printf ("%s\n",src);
   // Копируем 3 байт
   s21_memmove (&str[0], &src[1], 7);
   // Вывод массива src на консоль
    printf ("%s\n",str);
   return 0;
}
*/
