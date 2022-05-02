#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>

void * s21_trim(const char *src, const char *trim_chars) {
    
    char *correct_str = (char*)malloc(100 * sizeof(char));
    int srck = 0, tcharsk = 0, i = 0, sch = 0, schk, l;
    
    while(*(src + i)) {
        srck++;
        i++;
    }
    i = 0;
    while(*(trim_chars + i)) {
        tcharsk++;
        i++;
    }
   for (int k = 0; k < srck; k++) {
        for (l = 0; l < tcharsk; l++) {
            if (*(src + k) == *(trim_chars +l)) {
                sch++;
                break;
            }
        }
        if (sch == 0 || l == tcharsk) {
            break;
        }
    }
    for (int o = srck - 1; o > sch - 1; o-- ) {
        for (l = 0; l < tcharsk; l++) {
            
            
            if (*(src + o) == *(trim_chars +l)) {
                schk++;
                break;
            }
        }
        if (schk == 0 || l == tcharsk) {
            break;
        }
    }
    for (int m = sch, n = 0; m < (srck - schk); m++, n++) {
    
        *(correct_str + n) = *(src + m);
    }
    if (*src == '\0') {
        correct_str = s21_NULL;
    }
        
    src = correct_str;
        return (void *)src;
    free((void *)src);
    }

/*int main() {
     // Тестовые данные
    char *z = "1 2";
    char str[40] = "1    aa2aa  1";
// Обратите внимание, что \ r возвращается в начало текущей строки, использование \ r может перезаписать напечатанные символы
    char *res = s21_trim(str, z);
    for (int i = 0; *(res+i) != '\0'; i++) {
    printf("%c", *(res+i));
    }
    return 0;

}
*/
