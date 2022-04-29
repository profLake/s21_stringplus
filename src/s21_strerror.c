#include "s21_string.h"

char *s21_strerror(int errnum) {
    static const char *strerr[] = s21_error;
    return (char*)(strerr[errnum - 1]);
}
