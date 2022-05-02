//#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>


void *s21_to_upper(const char *str) {
    int t = 0;
    while(str[t] != 0) {
        t++;
    }
    t++;
    char *srr = (char*)malloc(t * sizeof(char));
    for(int q = 0; str[q] != 0; q++) {
        srr[q] = str[q];
        if(srr[q] >= 97 && srr[q] <= 122) {
            srr[q] -= 'a' - 'A';
        }
    }
    return srr;
    free(srr);
}

/*
int main() {
    char str[20];
    scanf("%s", str);
    char *src = s21_to_upper(str);
    printf("%s\n", src);
    printf("%s", str);
    return 0;
}
*/
