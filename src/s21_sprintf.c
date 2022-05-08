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
            } if (specif == SPECIFS[1]
                    || specif == SPECIFS[2]
                    || specif == SPECIFS[10]
                    || specif == SPECIFS[11]
                    || specif == SPECIFS[12]) {
                int printed = s21_trgt_print_tokn_num(target, token, &args);
                target += printed;
            } if (specif == SPECIFS[3]
                    || specif == SPECIFS[4]
                    || specif == SPECIFS[5]) {
                int printed = s21_trgt_print_tokn_ratio(target, token, &args);
                target += printed;
            } if (specif == SPECIFS[9]) {
                char *tokn_str  = va_arg(args, char*);
                int printed = s21_trgt_print_tokn_str(target, token, tokn_str);
                target += printed;
            } if (specif == SPECIFS[13]) {
                int printed = s21_trgt_print_tokn_ptr(target, token, &args);
                target += printed;
            } if (specif == SPECIFS[15]) {
                char tokn_c = TOKN_SIGN;
                int printed = s21_trgt_print_tokn_char(target, token, tokn_c);
                target += printed;
            }

            format += s21_tokn_get_str_len(token);
            is_token = 0;
        }
    }
    *target = '\0';

    va_end(args);
    return target - target_saved;
}

char *s21_tokn_skip_part(const char *token, unsigned int i) {
    if (i--)    /* flags */
        while (s21_strchr(FLAGS, *token))
            token++;
    if (i--) {  /* width */
        if (*token == ADDIT_INT_SIGN)
            token++;
        else
            while (s21_strchr(DIGITS, *token))
                token++;
    }
    if (i--)    /* precision */
        if (*token == PRECIS_SIGN) {
            token++;
            if (*token == ADDIT_INT_SIGN)
                token++;
            else
                while (s21_strchr(DIGITS, *token))
                    token++;
        }
    if (i--)    /* length-specifier */
        if (s21_strchr(TOKN_LENS, *token))
            token++;
    if (i--)    /* specifier */
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
    int result = -1;
    if (*token == ADDIT_INT_SIGN) {
        result = -2;
    }
    if (s21_atol(token)) {
        result = s21_atol(token);
    }
    return result;
}

int s21_tokn_get_precision(const char *token) {
    token = s21_tokn_skip_part(token, 2);
    int result = -1;
    if (*token == PRECIS_SIGN) {
        token++;
        if (*token == ADDIT_INT_SIGN) {
            result = -2;
        }
        if (s21_atol(token)) {
            result = s21_atol(token);
        }
    }
    return result;
}

char s21_tokn_get_len(const char *token) {
    token = s21_tokn_skip_part(token, 3);
    if (s21_strchr(TOKN_LENS, *token)) {
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

int s21_tokn_get_str_len(const char *token) {
    return s21_tokn_skip_part(token, 5) - token;
}

int s21_frmt_is_tokn(const char *format) {
    int result = 0;
    if (*format == TOKN_SIGN) {
        format++;
        if (s21_tokn_get_specif(format)) {
            result = 1;
        }
    }
    return result;
}

/*
int s21_trgt_print_uint(char *target, unsigned int n) {
    const char *target_saved = target;

    int n_len = s21_udecim_get_str_len(n);
    while (n_len > 0) {
        int divisor = s21_ulong_get_pow(10, n_len - 1);
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
        int divisor = s21_ulong_get_pow(10, n_len - 1);
        int curr_d = n / divisor;
        char curr_c = '0' + curr_d;
        *target = curr_c;
        target++;
        n %= divisor;
        n_len--;
    }

    return target - target_saved;
}
*/

int s21_trgt_print_ulong(char *target, unsigned long n) {
    const char *target_saved = target;

    int n_len = s21_udecim_get_str_len(n);
    while (n_len > 0) {
        unsigned long divisor = s21_ulong_get_pow(10, n_len - 1);
        unsigned long curr_d = n / divisor;
        char curr_c = '0' + curr_d;
        *target = curr_c;
        target++;
        n %= divisor;
        n_len--;
    }

    return target - target_saved;
}

int s21_trgt_print_uldouble(char *target, long double ld, int precis_len) {
    const char *target_saved = target;

    unsigned long decim_part = (long)ld;
    target += s21_trgt_print_ulong(target, decim_part);
    ld -= decim_part;

    if (precis_len > 0) {
        *target = '.';
        target++;
        if (precis_len < s21_udecim_get_str_len(LONG_MAX) - 1) {
            long double after_part;
            after_part = ld * s21_ulong_get_pow(10, precis_len);
            after_part = round(after_part);
            target += s21_trgt_print_ulong(target, (long)after_part);
        } else {
            while (precis_len) {
                ld *= 10;
                *target = '0' + (int)ld;
                target++;
                ld -= (int)ld;
                precis_len--;
            }
        }
    }

    return target - target_saved;
}

int s21_trgt_print_e_uldouble(char *target, long double ld, int precis_len,
        char e_sign) {
    const char *target_saved = target;

    int e = 0;
    while (ld < 1) {
        e--;
        ld *= 10;
    }
    while (ld > 10) {
        e++;
        ld /= 10;
    }
    target += s21_trgt_print_uldouble(target, ld, precis_len);

    *target = e_sign;
    target++;
    if (e < 0) {
        *target = '-';
        target++;
    } else {
        *target = '+';
        target++;
    }
    *target = '0' + e / 10;
    target++;
    *target = '0' + e % 10;
    target++;

    return target - target_saved;
}

int s21_trgt_print_base_ulong(char *target, unsigned long n,
        const char *base) {
    const char *target_saved = target;

    int base_n = s21_strlen(base);
    if (n / base_n) {
        target += s21_trgt_print_base_ulong(target, n / base_n, base);
    }
    *target = base[n % base_n];
    target++;

    return target - target_saved;
}

int s21_trgt_print_tokn_char(char *target, const char *token, char tokn_c) {
    const char *target_saved = target;

    /* Just to avoid compiler error */
    token++;

    *target = tokn_c;
    target++;
    return target - target_saved;
}

int s21_trgt_print_tokn_num(char *target, const char *token, va_list *pargs) {
    const char *target_saved = target;

    int width = s21_tokn_get_width(token);
    if (width == -2) {
        width = va_arg(*pargs, int);
    }

    long tokn_num = va_arg(*pargs, long);

    if (s21_tokn_get_specif(token) == SPECIFS[1]
            || s21_tokn_get_specif(token) == SPECIFS[2]) {
        tokn_num = (int)tokn_num;
    }
    if (s21_tokn_get_len(token) == TOKN_LENS[0]) {
        tokn_num = (short)tokn_num;
    }
    int is_prequel = s21_tokn_have_flag(token, FLAGS[0]);

    char sign = '\0';
    if (s21_tokn_have_flag(token, FLAGS[1])) {
        sign = '+';
    }
    if (tokn_num < 0 && s21_tokn_get_specif(token) != SPECIFS[10]) {
        sign = '-';
    }

    unsigned long tokn_udecim;
    if (s21_tokn_get_specif(token) == SPECIFS[10]) {
        tokn_udecim = tokn_num;
    } else {
        tokn_udecim = tokn_num >= 0 ? tokn_num : -tokn_num;
    }

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
    if (s21_tokn_get_specif(token) == SPECIFS[11]) {
        int printed = s21_trgt_print_base_ulong(target, tokn_udecim, BASE16);
        target+= printed;
    } else {
        int printed = s21_trgt_print_base_ulong(target, tokn_udecim, DIGITS);
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

int s21_trgt_print_tokn_ratio(char *target, const char *token,
            va_list *pargs) {
    const char *target_saved = target;

    int is_prequel = s21_tokn_have_flag(token, FLAGS[0]);

    int width = s21_tokn_get_width(token);
    if (width == -2) {
        width = va_arg(*pargs, int);
    }
    if (width < 0) {
        width = 0;
    }

    int precis_len = s21_tokn_get_precision(token);
    if (precis_len == -1) {
        precis_len = 6;
    }
    if (precis_len == -2) {
        precis_len = va_arg(*pargs, int);
    }
    if (precis_len < 0) {
        precis_len = 0;
    }
 
    long double tokn_ratio;
    if (s21_tokn_get_len(token) == TOKN_LENS[2]) {
        tokn_ratio = va_arg(*pargs, long double);
    } else {
        tokn_ratio = va_arg(*pargs, double);
    }

    char sign = '\0';
    if (tokn_ratio >= 0 && s21_tokn_have_flag(token, FLAGS[1])) {
        sign = '+';
    }
    if (tokn_ratio < 0) {
        sign = '-';
        tokn_ratio = -tokn_ratio;
    }

    int non_precis_part_len;
    if (s21_tokn_get_specif(token) == SPECIFS[5]) {
        non_precis_part_len = s21_udecim_get_str_len((unsigned long)tokn_ratio);
    } else {
        non_precis_part_len = 5;
        /*  Числа, наподобие 1.54+e01, имеют 1 символ до запятой и 4 символа
         *      после дробной части
         */
    }
    int fill_len = width - precis_len - non_precis_part_len;
    if (precis_len) {
        /* For a common */
        fill_len--;
    }
    if (sign) {
        fill_len--;
    }
    if (fill_len < 0) {
        fill_len = 0;
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
        s21_memset(target, fill_symb, fill_len);
        target += fill_len;
    }
    if (fill_symb == ' ' && sign) {
        *target = sign;
        target++;
    }
    if (s21_tokn_get_specif(token) == SPECIFS[5]) {
        target += s21_trgt_print_uldouble(target, tokn_ratio, precis_len);
    }
    if (s21_tokn_get_specif(token) == SPECIFS[3]) {
        target += s21_trgt_print_e_uldouble(target, tokn_ratio, precis_len,
                'e');
    }
    if (s21_tokn_get_specif(token) == SPECIFS[4]) {
        target += s21_trgt_print_e_uldouble(target, tokn_ratio, precis_len,
                'E');
    }
    if (is_prequel) {
        s21_memset(target, fill_symb, fill_len);
        target += fill_len;
    }

    return target - target_saved;
}

int s21_trgt_print_tokn_ptr(char *target, const char *token,
        va_list *pargs) {
    const char *target_saved = target;

    int is_prequel = s21_tokn_have_flag(token, FLAGS[0]);

    int width = s21_tokn_get_width(token);
    if (width == -2) {
        width = va_arg(*pargs, int);
    }
    if (width < 0) {
        width = 0;
    }

    int fill_len = width - PTR_LEN_WITH_0X;
    if (fill_len < 0) {
        fill_len = 0;
    }

    void *p = va_arg(*pargs, void *);

    if (is_prequel == 0) {
        s21_memset(target, ' ', fill_len);
        target += fill_len;
    }
    *target++ = '0';
    *target++ = 'x';
    target += s21_trgt_print_base_ulong(target, (unsigned long)p, BASE16);
    if (is_prequel) {
        s21_memset(target, ' ', fill_len);
        target += fill_len;
    }

    return target - target_saved;
}

int s21_base_unum_get_str_len(unsigned long n, char *base) {
    int result = 0;
    while (n >= (unsigned long)s21_strlen(base)) {
        result++;
        n /= (unsigned long)s21_strlen(base);
    }
    result++;
    return result;
}

int s21_udecim_get_str_len(unsigned long n) {
    return s21_base_unum_get_str_len(n, DIGITS);
}

unsigned long s21_ulong_get_pow(unsigned long n, int pow) {
    unsigned long result = 0;
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

long s21_atol(const char *str) {
    long result = 0;
    int is_minus = 0;
    if (*str == '-') {
        is_minus = 1;
        str++;
    }
    while (s21_strchr(DIGITS, *str)) {
        result *= 10;
        result += *str - '0';
        str++;
    }
    return is_minus ? -result : result;
}

