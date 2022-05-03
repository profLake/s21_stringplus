#include <stdio.h>
#include <string.h>
#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    
    s21_size_t i = 0;
    s21_size_t q = 0;
    
    while (src[i] != '\0') {
        i++;
    }
    
   while (str[q] != '\0') {
        q++;
    }
    
    char *m = malloc((i+q)*sizeof(char));
    
    s21_size_t r;
    s21_size_t k;
    
    for (r = 0; src[r-k] != '\0'; r++) {
        if (r < start_index) {
        m[r] = str[r];
        }
        if (r >= start_index && str[k] != '\0') {
            m[r] = str[k];
            k++;
        }
        if (r == start_index+q && src[r-k] != '\0')
            m[r] = src[r-k];
    }
}

/*
int main() {
    
    char a[20] = "hello";
    char b[20] = "world";
    
    char *c = s21_insert(a,b, 2);
    puts(c);
} */
