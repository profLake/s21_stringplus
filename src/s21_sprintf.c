#include "s21_string.h"
#include <stdarg.h>

int s21_sprintf(char *target, const char *format, ...) {
    char *target_saved = target;
    va_list args;
    va_start(args, format);

    int is_token = 0;
    while (*format) {
        if (s21_frmt_is_tokn(format) == 1) {
            is_token = 1;
            format++;
        }
        if (is_token == 0) {
            *target = *format;
            target++;
            format++;
        }
        if (is_token == 1) {
            const char *token = format;
            char specif = s21_tokn_get_specif(token);

            if (specif == SPECIFS[0]) {
                char tokn_c = va_arg(args, int);
                *target = tokn_c;
                target++;
            } else if (specif == SPECIFS[1] || specif == SPECIFS[2]) {
                int tokn_int = va_arg(args, int);
                s21_int_to_str(target, tokn_int);
                target += s21_int_get_str_len(tokn_int);
            } else if (specif == SPECIFS[5]) {
            } else if (specif == SPECIFS[9]) {
            } else if (specif == SPECIFS[10]) {
            } else if (specif == SPECIFS[15]) {
            }

            format += s21_tokn_get_len(token);
            is_token = 0;
        }
    }
    *target = '\0';

    va_end(args);
    return target - target_saved;
}

/*
void s21_tokn_insert_specif(char *target, char *token, void *thing) {
}
*/
char *s21_tokn_skip_part(const char *token, unsigned int i) {
    if (i--)
        while (s21_strchr(FLAGS, *token))
            token++;
    if (i--)
        while (s21_strchr(DIGITS, *token))
            token++;
    if (i--)
        if (*token == PRECIS_SIGN)
            token++;
    if (i--)
        while (s21_strchr(DIGITS, *token))
            token++;
    if (i--)
        if (s21_strchr(SPECIFS_LENS, *token))
            token++;
    if (i--)
        if (s21_strchr(SPECIFS, *token))
            token++;
    return (char*)token;
}

char s21_tokn_get_flag(const char *token) {
    if (s21_strchr(FLAGS, *token)) {
        return *token;
    }
    return '\0';
}

int s21_tokn_get_width(const char *token) {
    token = s21_tokn_skip_part(token, 1);
    return atoi(token);
}

int s21_tokn_get_precision(const char *token) {
    token = s21_tokn_skip_part(token, 2);
    if (*token != PRECIS_SIGN) {
        return 0;
    }
    token++;
    return atoi(token);
}

char s21_tokn_get_specif_len_descr(const char *token) {
    token = s21_tokn_skip_part(token, 3);
    if (s21_strchr(SPECIFS_LENS, *token)) {
        return *token;
    }
    return '\0';
}

char s21_tokn_get_specif(const char *token) {
    token = s21_tokn_skip_part(token, 4);
    if (s21_strchr(SPECIFS, *token)) {
        return *token;
    }
    return '\0';
}

int s21_tokn_get_len(const char *token) {
    const char *token_saved = token;
    while (s21_strchr(FLAGS, *token)) {
        token++;
    }
    while (s21_strchr(DIGITS, *token)) {
        token++;
    }
    if (*token == PRECIS_SIGN) {
        token++;
    }
    while (s21_strchr(DIGITS, *token)) {
        token++;
    }
    if (s21_strchr(SPECIFS, *token)) {
        token++;
        return token - token_saved;
    }
    return 0;
}

int s21_int_get_str_len(int n) {
    int result = 0;
    if (n < 0) {
        n = -n;
        result++;
    }
         if (n <         10) result += 1;
    else if (n <        100) result += 2;
    else if (n <       1000) result += 3;
    else if (n <      10000) result += 4;
    else if (n <     100000) result += 5;
    else if (n <    1000000) result += 6;
    else if (n <   10000000) result += 7;
    else if (n <  100000000) result += 8;
    else if (n < 1000000000) result += 9;
    return result;
}

int s21_frmt_is_tokn(const char *format) {
    int result = 0;
    if (*format == TOKN_SIGN) {
        format++;
        if (s21_tokn_get_len(format) > 0) {
            result = 1;
        }
    }
    return result;
}

char* s21_int_to_str(char *target, int n) {
    static char *buff = NULL;
    int is_first = 0;
    if (n < 0) {
        *target++ = '-';
        n = -n;
    }
    if (buff == NULL) {
        buff = target;
        is_first = 1;
    }
    if (n / 10) {
        s21_int_to_str(buff, n / 10);
        n %= 10;
    }
    *buff++ = '0' + n;

    if (is_first) {
        *buff = '\0';
        buff = NULL;
    }
    return target;
}

