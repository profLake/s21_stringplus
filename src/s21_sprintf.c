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
                       || specif == SPECIFS[2]
                       || specif == SPECIFS[10]) {
                int tokn_int = va_arg(args, int);
                int printed = s21_trgt_print_tokn_decim(target, token,
                        tokn_int);
                target += printed;
            } else if (specif == SPECIFS[5]) {
            } else if (specif == SPECIFS[9]) {
                char *tokn_str  = va_arg(args, char*);
                int printed = s21_trgt_print_tokn_str(target, token, tokn_str);
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

int s21_udecim_get_str_len(unsigned long n) {
    int result = 0;
    while (n / (unsigned long)10) {
        result++;
        n /= (unsigned long)10;
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

int s21_trgt_print_uint(char *target, unsigned int n) {
    const char *target_saved = target;

    int n_len = s21_udecim_get_str_len(n);
    while (n_len > 0) {
        int divisor = s21_int_get_pow(10, n_len - 1);
        int curr_d = n / divisor;
        char curr_c = '0' + curr_d;
        *target = curr_c;
        target++;
        n %= divisor;
        n_len--;
    }

    return target - target_saved;
}

int s21_trgt_print_ushort(char *target, unsigned short n) {
    const char *target_saved = target;

    int n_len = s21_udecim_get_str_len(n);
    while (n_len > 0) {
        int divisor = s21_int_get_pow(10, n_len - 1);
        int curr_d = n / divisor;
        char curr_c = '0' + curr_d;
        *target = curr_c;
        target++;
        n %= divisor;
        n_len--;
    }

    return target - target_saved;
}

int s21_trgt_print_ulong(char *target, unsigned long n) {
    const char *target_saved = target;

    int n_len = s21_udecim_get_str_len(n);
    while (n_len > 0) {
        int divisor = s21_int_get_pow(10, n_len - 1);
        int curr_d = n / divisor;
        char curr_c = '0' + curr_d;
        *target = curr_c;
        target++;
        n %= divisor;
        n_len--;
    }

    return target - target_saved;
}

int s21_int_get_pow(int n, int pow) {
    int result = 0;
    if (pow == 0) {
        result = 1;
    }
    if (pow) {
        result = n;
        pow--;
    }
    while (pow) {
        result *= n;
        pow--;
    }
    return result;
}

int s21_trgt_print_tokn_char(char *target, const char *token, char tokn_c) {
    const char *target_saved = target;

    /* Just to avoid compiler error */
    token++;

    *target = tokn_c;
    target++;
    return target - target_saved;
}

int s21_trgt_print_tokn_decim(char *target, const char *token,
            long tokn_decim) {
    const char *target_saved = target;

    int is_prequel = s21_tokn_have_flag(token, FLAGS[0]);

    char sign = '\0';
    if (s21_tokn_have_flag(token, FLAGS[1])) {
        sign = '+';
    }
    if (tokn_decim < 0 && s21_tokn_get_specif(token) != SPECIFS[10]) {
        sign = '-';
    }

    long tokn_udecim;
    if (s21_tokn_get_specif(token) == SPECIFS[10]) {
        tokn_udecim = tokn_decim;
    } else {
        tokn_udecim = tokn_decim >= 0 ? tokn_decim : -tokn_decim;
    }

    int width = s21_tokn_get_width(token);
    int tokn_udecim_len = s21_udecim_get_str_len(tokn_udecim);
    int fill_len = 0;
    if (width) {
        fill_len = width - tokn_udecim_len;
        if (sign) {
            fill_len--;
        }
        if (fill_len < 0) {
            fill_len = 0;
        }
    }

    char fill_symb = ' ';
    if (s21_tokn_have_flag(token, FLAGS[4]) && is_prequel == 0) {
        fill_symb = '0';
    }

    if (is_prequel == 0) {
        if (fill_symb == '0' && sign) {
            *target = sign;
            target++;
        }
        while (fill_len--) {
            *target = fill_symb;
            target++;
        }
    }
    if (fill_symb == ' ' && sign) {
        *target = sign;
        target++;
    }
    if (s21_tokn_get_len(token) == SPECIFS_LENS[0]) {
        int printed = s21_trgt_print_ushort(target, tokn_udecim);
        target+= printed;
    }
    if (s21_tokn_get_len(token) == SPECIFS_LENS[1]) {
        int printed = s21_trgt_print_ulong(target, tokn_udecim);
        target+= printed;
    } else {
        int printed = s21_trgt_print_uint(target, tokn_udecim);
        target+= printed;
    }
    if (is_prequel) {
        while (fill_len) {
            *target = fill_symb;
            target++;
            fill_len--;
        }
    }

    return target - target_saved;
}

int s21_trgt_print_tokn_str(char *target, const char *token,
        const char *tokn_str) {
    const char *target_saved = target;

    int is_prequel = s21_tokn_have_flag(token, FLAGS[0]);

    int width = s21_tokn_get_width(token);
    int tokn_str_len = s21_strlen(tokn_str);
    int fill_len = width - tokn_str_len;
    if (fill_len < 0) {
        fill_len = 0;
    }

    if (is_prequel == 0) {
        while (fill_len) {
            *target = ' ';
            target++;
            fill_len--;
        }
    }
    s21_strcpy(target, tokn_str);
    target += tokn_str_len;
    if (is_prequel) {
        while (fill_len) {
            *target = ' ';
            target++;
            fill_len--;
        }
    }

    return target - target_saved;
}

