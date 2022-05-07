#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void *s21_to_lower(const char *str) {
    int i;
    i = 0;
    int j;
    j = 0;
    
    while (str[i] != '\0') {
        i++;
    }

    char *scopy = malloc(i * sizeof(char));
    
    int q;
    for (q=0; str[q] != '\0'; q++) {
        scopy[q] = str[q];
    }
    while (scopy[j]) {
        if (scopy[j] >= 65 && str[j] <= 90) {
            scopy[j] = scopy[j] + 32;
        }
        j++;
    }
    return scopy;
}

/*
int main(){
    char str[20];
    scanf("%s", str);
    char *src = s21_to_lower(str);
    printf("%s", src);
    free(src);
    return 0;
}
*/
