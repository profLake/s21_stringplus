#include "s21_string.h"

char *s21_strerror(int errnum) {
    if (errnum < 0 || errnum >= ERR_MSGS_COUNT) {
        static char unknown_str[50];
#ifdef __APPLE__
        s21_sprintf(unknown_str, "Unknown error: %d", errnum);
#else
        s21_sprintf(unknown_str, "Unknown error %d", errnum);
#endif
        return unknown_str;
    }
    static const char *strerr[] = ERR_MSGS;
    return (char*)(strerr[errnum]);
}
