#include "s21_string.h"
#include <stdarg.h>

#define TOKN_SIGN '%'
#define SPECIFS "cdieEfgGosuxXpn%"
#define DIGITS "0123456789"
#define FLAGS "-+ #0"
#define PRECIS_SIGN '.'

char s21_tokn_get_flag_(const char *token);
int s21_tokn_get_width_(const char *token);
int s21_tokn_get_precision_(const char *token);
char s21_tokn_get_specif_(const char *token);
int s21_tokn_get_len(const char *token);

int s21_sprintf_(char *target, const char *format, ...) {
    char *target_saved = target;
    va_list args;
    va_start(args, format);

    int under_token = 0;
    while (*format) {
        if (*format == TOKN_SIGN) {
            under_token = 1;
            format++;
        }
        if (under_token == 0) {
            *target = *format;
            target++;
            format++;
        }
        if (under_token == 1) {
            const char *token = format;

            char specif = s21_tokn_get_specif_(token);

            if (specif == SPECIFS[0]) {
                *target = va_arg(args, int);
                target++;
            }
            under_token = 0;
        }
    }

    va_end(args);
    return target - target_saved;
}

/*
void s21_tokn_insert_specif(char *target, char *token, void *thing) {
}
*/

char s21_tokn_get_flag_(const char *token) {
    if (s21_strchr(FLAGS, *token)) {
        return *token;
    }
    return 0;
}

int s21_tokn_get_width_(const char *token) {
   return atoi(token);
}

int s21_tokn_get_precision_(const char *token) {
    while (s21_strchr(DIGITS, *token)) {
        token++;
    }
    if (*token != PRECIS_SIGN) {
        return 0;
    }
    token++;
    return atoi(token);
}

char s21_tokn_get_specif_(const char *token) {
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
        return *token;
    }
    return 0;
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
