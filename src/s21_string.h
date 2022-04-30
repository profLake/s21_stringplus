#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef unsigned long s21_size_t;
#define s21_NULL (void*)0


/* The order is keeped from the task. There are 20. НЕ МЕНЯТЬ */
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char* s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);


int sprintf(char *str, const char *format, ...);


/* Для s21_sprintf() и s21_scanf */

typedef struct P_Token {
    int width;
    int precision;
    int pres_flag;
    int null_flag;
    int str_len;
    int hex;
    int oct;
    int exp;
    int g;
} P_Token;

typedef struct float_el {
    int decnpt;
    int sign;
    int i;
    int end;
    int float_len;
} float_el;

#define FORMAT_MAX 256
#define SIZE_CHAR 5
void s21_clear(char *str);
int get_format_token(char *format, char *token_str);
int check_specs(char c);
int is_dec(char c);
int get_presicion(char *str);
int get_num_len(long long number);
int get_float_len_sprintf(char *str, int start_index);
int start_processing_p(char *str, char*format, va_list argptr);
int check_string(const char *str);
int generate_plus_expo(int decnpt);
int generate_minus_expo(int decnpt);
int get_more_than_null(char *tmp_str);
int skip_nulls(char *str);
int check_nan(char *str);
int get_dec_length(char *str);
int is_expo_str(char *str);
int get_e_index(char *str);

char *s21_wcharcat(char *destination, const wchar_t *source);
char *s21_itoa(long num);
char *s21_parser(const char *format, char *token_str, int *counter);
char* get_float_copy(char *dest, const char *source, int start_index, int end);
void *get_hexarr(char *arr, unsigned long num, int x);

void check_flags(char *token_str);
void processing_f(char *str, va_list argptr, P_Token t);
void processing_s(char *str, char *token_str, va_list argptr, P_Token t);
void processing_c(char *str, char *token_str, va_list argptr, P_Token t);
void processing_d(char *str, char *token_str, va_list argptr, P_Token t);
void processing_u(char *str, char *token_str, va_list argptr, P_Token t);
void processing_x(char *str, char *token_str, va_list argptr, P_Token t, int x);
void processing_o(char *str, char *token_str, va_list argptr, P_Token t);
void processing_p(char *str, va_list argptr, P_Token t, int x);
void processing_e(char *str, va_list argptr, P_Token t);
void processing_g(char *str, va_list argptr, P_Token t);
void processing_n(char *str, va_list argptr);
void processing_percent(char *str, P_Token t);
void main_process(char *str, char *token_str, va_list argptr);
void write_d_to_string(char *str, char *arg, int len, P_Token t);
void write_u_to_string(char *str, char *arg, int len, P_Token t);
void write_f_to_string(char *str, char *num, int sign, P_Token *t);
void write_f_nothing(char *str, char *num, int sign, int len, P_Token *t);
void write_f_pluses(char *str, char *num, int sign, int len, P_Token *t);
void write_f_pluses_spaces(char *str, char *num, int sign, int len, P_Token *t);
void write_f_minuses_pluses(char *str, char *num, int sign, int len, P_Token *t);
void write_f_minuses_spaces(char *str, char *num, int sign, int len, P_Token *t);
void write_f_pluses_(char *str, char *num, int sign, int len, P_Token *t);
void write_p_to_string(char *str, char *result, int len, P_Token t);
void write_width_to_str(char *str, int len, P_Token *t);
void write_pres_to_str(char *str, P_Token *t);
void write_plus_to_str(char *str, P_Token *t);
void write_minus_to_str(char *str, int sign, P_Token *t);
void write_space_to_str(char *str, P_Token *t);
void add_nulls_to_str(char *str, int float_len, P_Token t);
void init_parameters(P_Token *t, int len);
void make_expo_str(double arg, char *str, int decnpt, int *sign, P_Token t);
void make_double_str(double arg, char *num_str, float_el *f_el, P_Token t);
void make_long_double_str(long double arg, char *num_str, float_el *f_el, P_Token t);
void add_lt_ten(char *str, int index, int e);
void add_gt_ten(char *str, int e);
void change_letter_e(char *str);
void round_double_str(double arg, char *num_arr, float_el *f_el);
void round_long_double_str(long double arg, char *num_arr, float_el *f_el);
void make_nan_str(char *num_str, float_el f_el, P_Token t);
void make_notnan_str(char *tmp_str, char *num_str, float_el f_el, P_Token t);
void remove_dot(char *dest, char *str);
void copy_e_str(char *dest, char *src);
void write_e_grid_and_nulls(char *str, char *num, int decs, int sign, P_Token t);
void init_flags();
int get_dot_index(char *str);
int no_dot(char *str);

float_el init_f_el();
P_Token init_token();

void check_precision(P_Token *t);
void get_width_pres(char *token_str, va_list argptr, P_Token *t);
void read_star_width_pres(char *token_str, va_list argptr, P_Token *t);
void read_nostar_width_pres(char *token_str, P_Token *t);
void copy_zero_float(char *num_str, const char *tmp_str, int decnpt, int sign, P_Token t);
void s21_reverse_array(char *a, int n);
void check_grid_u(char *str, int len, P_Token *t);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void s21_clear(char *str);
int del_check(char c, const char *delim);
int get_first_index(const char *src, const char *trim_chars, int src_len, int chars_len);
int get_last_index(const char *src, const char *trim_chars, int src_len, int chars_len);
int chrcmp(char c1, char c2);

unsigned long get_unsigned_arg(char *token_str, va_list argptr);


/* Для s21_strerror() */
#ifdef __APPLE__
#define s21_error { "Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"Input/output error", \
"Device not configured", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child processes", \
"Resource deadlock avoided", \
"Cannot allocate memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Resource busy", \
"File exists", \
"Cross-device link", \
"Operation not supported by device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"Too many open files", \
"Inappropriate ioctl for device", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Illegal seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Numerical argument out of domain", \
"Result too large", \
"Resource temporarily unavailable", \
"Operation now in progress", \
"Operation already in progress", \
"Socket operation on non-socket", \
"Destination address required", \
"Message too long", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Operation not supported", \
"Protocol family not supported", \
"Address family not supported by protocol family", \
"Address already in use", \
"Can't assign requested address", \
"Network is down", \
"Network is unreachable", \
"Network dropped connection on reset", \
"Software caused connection abort", \
"Connection reset by peer", \
"No buffer space available", \
"Socket is already connected", \
"Socket is not connected", \
"Can't send after socket shutdown", \
"Too many references: can't splice", \
"Operation timed out", \
"Connection refused", \
"Too many levels of symbolic links", \
"File name too long", \
"Host is down", \
"No route to host", \
"Directory not empty", \
"Too many processes", \
"Too many users", \
"Disc quota exceeded", \
"Stale NFS file handle", \
"Too many levels of remote in path", \
"RPC struct is bad", \
"RPC version wrong", \
"RPC prog. not avail", \
"Program version wrong", \
"Bad procedure for program", \
"No locks available", \
"Function not implemented", \
"Inappropriate file type or format", \
"Authentication error", \
"Need authenticator", \
"Device power is off", \
"Device error", \
"Value too large to be stored in data type", \
"Bad executable (or shared library)", \
"Bad CPU type in executable", \
"Shared library version mismatch", \
"Malformed Mach-o file", \
"Operation canceled", \
"Identifier removed", \
"No message of desired type", \
"Illegal byte sequence", \
"Attribute not found", \
"Bad message", \
"EMULTIHOP (Reserved)", \
"No message available on STREAM", \
"ENOLINK (Reserved)", \
"No STREAM resources", \
"Not a STREAM", \
"Protocol error", \
"STREAM ioctl timeout", \
"Operation not supported on socket", \
"Policy not found", \
"State not recoverable", \
"Previous owner died", \
"Interface output queue is full"}
#endif

#ifdef __linux__
#define s21_error { "Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"Input/output error", \
"No such device or address", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child processes", \
"Resource temporarily unavailable", \
"Cannot allocate memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Device or resource busy", \
"File exists", \
"Invalid cross-device link", \
"No such device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"Too many open files", \
"Inappropriate ioctl for device", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Illegal seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Numerical argument out of domain", \
"Numerical result out of range", \
"Resource deadlock avoided", \
"File name too long", \
"No locks available", \
"Function not implemented", \
"Directory not empty", \
"Too many levels of symbolic links", \
"Unknown error 41", \
"No message of desired type", \
"Identifier removed", \
"Channel number out of range", \
"Level 2 not synchronized", \
"Level 3 halted", \
"Level 3 reset", \
"Link number out of range", \
"Protocol driver not attached", \
"No CSI structure available", \
"Level 2 halted", \
"Invalid exchange", \
"Invalid request descriptor", \
"Exchange full", \
"No anode", \
"Invalid request code", \
"Invalid slot", \
"Unknown error 58", \
"Bad font file format", \
"Device not a stream", \
"No data available", \
"Timer expired", \
"Out of streams resources", \
"Machine is not on the network", \
"Package not installed", \
"Object is remote", \
"Link has been severed", \
"Advertise error", \
"Srmount error", \
"Communication error on send", \
"Protocol error", \
"Multihop attempted", \
"RFS specific error", \
"Bad message", \
"Value too large for defined data type", \
"Name not unique on network", \
"File descriptor in bad state", \
"Remote address changed", \
"Can not access a needed shared library", \
"Accessing a corrupted shared library", \
".lib section in a.out corrupted", \
"Attempting to link in too many shared libraries", \
"Cannot exec a shared library directly", \
"Invalid or incomplete multibyte or wide character", \
"Interrupted system call should be restarted", \
"Streams pipe error", \
"Too many users", \
"Socket operation on non-socket", \
"Destination address required", \
"Message too long", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Operation not supported", \
"Protocol family not supported", \
"Address family not supported by protocol", \
"Address already in use", \
"Cannot assign requested address", \
"Network is down", \
"Network is unreachable", \
"Network dropped connection on reset", \
"Software caused connection abort", \
"Connection reset by peer", \
"No buffer space available", \
"Transport endpoint is already connected", \
"Transport endpoint is not connected", \
"Cannot send after transport endpoint shutdown", \
"Too many references: cannot splice", \
"Connection timed out", \
"Connection refused", \
"Host is down", \
"No route to host", \
"Operation already in progress", \
"Operation now in progress", \
"Stale file handle", \
"Structure needs cleaning", \
"Not a XENIX named type file", \
"No XENIX semaphores available", \
"Is a named type file", \
"Remote I/O error", \
"Disk quota exceeded", \
"No medium found", \
"Wrong medium type", \
"Operation canceled", \
"Required key not available", \
"Key has expired", \
"Key has been revoked", \
"Key was rejected by service", \
"Owner died", \
"State not recoverable", \
"Operation not possible due to RF-kill", \
"Memory page has hardware error"}
#endif
