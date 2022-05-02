#include "s21_string.h"
#include <stdarg.h>

int s21_sprintf(char *target, const char *format, ...) {
    const char *target_saved = target;
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
                int printed = s21_trgt_print_tokn_char(target, token, tokn_c);
                target += printed;
            } else if (   specif == SPECIFS[1]
                       || specif == SPECIFS[2]) {
                int tokn_int = va_arg(args, int);
                int printed = s21_trgt_print_tokn_int(target, token, tokn_int);
                target += printed;
            } else if (specif == SPECIFS[5]) {
            } else if (specif == SPECIFS[9]) {
                /*
                char *tokn_str = va_arg(args, char*);
                int printed = s21_trgt_print_tokn_str(target, token, tokn_str);
                target += printed;
                */
            } else if (specif == SPECIFS[10]) {
                uint tokn_uint = va_arg(args, uint);
                int printed = s21_trgt_print_tokn_uint(
                        target, token, tokn_uint);
                target += printed;
            } else if (specif == SPECIFS[15]) {
                char tokn_c = TOKN_SIGN;
                int printed = s21_trgt_print_tokn_char(target, token, tokn_c);
                target += printed;
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
        if (*token == PRECIS_SIGN) {
            token++;
            while (s21_strchr(DIGITS, *token))
                token++;
        }
    if (i--)
        if (s21_strchr(SPECIFS_LENS, *token))
            token++;
    if (i--)
        if (s21_strchr(SPECIFS, *token))
            token++;
    return (char*)token;
}

char s21_tokn_get_flag(const char *token, int i) {
    token += i;
    if (s21_strchr(FLAGS, *token)) {
        return *token;
    }
    return '\0';
}

int s21_tokn_have_flag(const char *token, char flag) {
    while (s21_strchr(FLAGS, *token)) {
        if (*token == flag)
            return 1;
        token++;
    }
    return 0;
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

int s21_uint_get_str_len(unsigned int n) {
    int result = 0;
    while (n / 10) {
        result++;
        n /= 10;
    }
    result++;
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

char* s21_trgt_print_uint(char *target, unsigned int n) {
    static char *buff = NULL;
    int is_first = 0;
    if (buff == NULL) {
        buff = target;
        is_first = 1;
    }
    if (n / 10) {
        s21_trgt_print_uint(buff, n / 10);
        n %= 10;
    }
    *buff++ = '0' + n;

    if (is_first) {
        *buff = '\0';
        buff = NULL;
    }
    return target;
}

int s21_trgt_print_tokn_char(char *target, const char *token, char tokn_c) {
    const char *target_saved = target;

    /* Just to avoid compiler error */
    token++;

    *target = tokn_c;
    target++;
    return target - target_saved;
}

int s21_trgt_print_tokn_int(char *target, const char *token, int tokn_int) {
    const char *target_saved = target;

    int tokn_width = s21_tokn_get_width(token);
    char int_sign = '\0';
    if (tokn_int < 0) {
        int_sign = '-';
    }
    if (s21_tokn_have_flag(token, FLAGS[1]) && tokn_int >= 0) {
        int_sign = '+';
    }
    uint tokn_uint = tokn_int >= 0 ? tokn_int : -tokn_int;
    int uint_width = s21_uint_get_str_len(tokn_uint);
    char fill_sign = ' ';
    if (    s21_tokn_have_flag(token, FLAGS[4]) == 1
        &&  s21_tokn_have_flag(token, FLAGS[0]) == 0) {
        fill_sign = '0';
    }

    if (int_sign) {
        *target = int_sign;
        target++;
        tokn_width--;
    }
    if (s21_tokn_have_flag(token, FLAGS[0])) {
        s21_trgt_print_uint(target, tokn_uint);
        target += uint_width;
        tokn_width -= uint_width;
        while (tokn_width > 0) {
            *target = fill_sign;
            target++;
            tokn_width--;
        }
    }
    if (s21_tokn_have_flag(token, FLAGS[0]) == 0) {
        tokn_width -= uint_width;
        while (tokn_width > 0) {
            *target = fill_sign;
            target++;
            tokn_width--;
        }
        s21_trgt_print_uint(target, tokn_uint);
        target += uint_width;
    }

    return target - target_saved;
    /* CLEAN THIS FUNC */
}

int s21_trgt_print_tokn_uint(char *target, const char *token, uint tokn_uint) {
    const char *target_saved = target;

    int tokn_width = s21_tokn_get_width(token);
    char int_sign = '\0';
    if (s21_tokn_have_flag(token, FLAGS[1])) {
        int_sign = '+';
    }
    int uint_width = s21_uint_get_str_len(tokn_uint);
    char fill_sign = ' ';
    if (    s21_tokn_have_flag(token, FLAGS[4]) == 1
        &&  s21_tokn_have_flag(token, FLAGS[0]) == 0) {
        fill_sign = '0';
    }

    if (int_sign) {
        *target = int_sign;
        target++;
        tokn_width--;
    }
    if (s21_tokn_have_flag(token, FLAGS[0])) {
        s21_trgt_print_uint(target, tokn_uint);
        target += uint_width;
        tokn_width -= uint_width;
        while (tokn_width > 0) {
            *target = fill_sign;
            target++;
            tokn_width--;
        }
    }
    if (s21_tokn_have_flag(token, FLAGS[0]) == 0) {
        tokn_width -= uint_width;
        while (tokn_width > 0) {
            *target = fill_sign;
            target++;
            tokn_width--;
        }
        s21_trgt_print_uint(target, tokn_uint);
        target += uint_width;
    }

    return target - target_saved;
}

/*
int s21_trgt_print_tokn_str(target, token, tokn_str) {

}
*/

