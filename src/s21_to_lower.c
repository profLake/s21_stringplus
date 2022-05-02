#include <stdio.h>
#include <stdlib.h>

char *s21_to_upper(const char *str) {
    int i;
    i = 0;
    int j;
    j = 0;
    
    while (str[i] != '\0') {
        i++;
    }

    char *strcopy = malloc(i * sizeof(char));
    
    int q;
    for (q=0; str[q] != '\0'; q++) {
        strcopy[q] = str[q];
    }
    while (strcopy[j]) {
        if (strcopy[j] >= 65 && str[j] <= 90) {
            strcopy[j] = strcopy[j] + 32;
        }
        j++;
    }
    return strcopy;
    free(strcopy);
}

int main(){
    char str[20];
    scanf("%s", str);
    char *src = s21_to_upper(str);
    printf("%s", src);
    free(src);
    return 0;
}
