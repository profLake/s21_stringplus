#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
    static char* str_saved = s21_NULL;
    if (str == s21_NULL) {
        str = str_saved;
    } else {
        str_saved = str;
    }
    if (str == s21_NULL) {
        return s21_NULL;
    }

    /* Пропускаем неподходящую часть str */
    while (*str && s21_strpbrk(str, delim) == str) {
        str++;
    }
    if (*str == '\0') {
        return s21_NULL;
    }

    /* Ищем конец токена. Если находим, то ставим '\0' на его
     * месте. Также сдвигаем str_saved на этот конец для будущих
     * вызовов
     */
    char *token_end = s21_strpbrk(str, delim);
    if (token_end) {
        *token_end = '\0';
        str_saved = token_end + 1;
    }

    return str;
}
